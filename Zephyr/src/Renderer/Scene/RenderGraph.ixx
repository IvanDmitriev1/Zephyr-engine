export module Zephyr.Renderer.RenderGraph;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Renderer.Core.ICommandList;
export import std.compat;
import <algorithm>;
import <limits>;
import <queue>;
import <ranges>;

export namespace Zephyr
{
	enum class RenderGraphResourceType : uint8_t
	{
		Texture,
		Buffer,
		External
	};

	struct RenderGraphResourceDesc
	{
		RenderGraphResourceType Type{ RenderGraphResourceType::Texture };
		std::string Name{};
	};

	struct RenderGraphResourceHandle
	{
		uint32_t Index = std::numeric_limits<uint32_t>::max();

		bool IsValid() const { return Index != std::numeric_limits<uint32_t>::max(); }
	};

	class RenderGraph;
	class RenderGraphExecutionContext;

	using RenderGraphExecuteFn = std::function<void(const RenderGraphExecutionContext&, RHI::ICommandList&)>;

	struct RenderGraphResource
	{
		RenderGraphResourceDesc Desc{};
		std::vector<uint32_t> Passes{};
		uint32_t PhysicalIndex = std::numeric_limits<uint32_t>::max();
		bool Imported = false;
	};

	struct RenderGraphPass
	{
		std::string Name{};
		std::vector<RenderGraphResourceHandle> Reads{};
		std::vector<RenderGraphResourceHandle> Writes{};

		RenderGraphExecuteFn Execute{};
	};

	class RenderGraphPassBuilder
	{
	public:
		RenderGraphPassBuilder(RenderGraph& graph, uint32_t passIndex);

		void Read(RenderGraphResourceHandle handle);
		void Write(RenderGraphResourceHandle handle);

	private:
		RenderGraph* m_Graph;
		uint32_t m_PassIndex;
	};

	class RenderGraph
	{
	public:
		RenderGraphResourceHandle CreateResource(RenderGraphResourceDesc desc);
		RenderGraphResourceHandle ImportResource(RenderGraphResourceDesc desc);

		RenderGraphPassBuilder AddPass(std::string name, RenderGraphExecuteFn execute);

		void Compile();
		void Execute(RHI::ICommandList& cmdList);

		const RenderGraphResource& GetResource(RenderGraphResourceHandle handle) const;

	private:
		friend class RenderGraphPassBuilder;
		friend class RenderGraphExecutionContext;

		RenderGraphResourceHandle AddResource(RenderGraphResourceDesc desc, bool imported);
		void MarkResourceUsage(RenderGraphResourceHandle handle, uint32_t passIndex);
		void AddDependency(uint32_t before, uint32_t after);

		std::vector<RenderGraphPass> m_Passes{};
		std::vector<RenderGraphResource> m_Resources{};
		std::vector<std::vector<uint32_t>> m_Dependencies{};

		std::vector<uint32_t> m_ExecutionOrder{};
		bool m_IsCompiled = false;
	};

	class RenderGraphExecutionContext
	{
	public:
		RenderGraphExecutionContext(const RenderGraph& graph);

		const RenderGraphResource& GetResource(RenderGraphResourceHandle handle) const;
		uint32_t GetPhysicalResource(RenderGraphResourceHandle handle) const;

	private:
		const RenderGraph* m_Graph = nullptr;
	};
}

namespace Zephyr
{
	RenderGraphPassBuilder::RenderGraphPassBuilder(RenderGraph& graph, uint32_t passIndex)
		: m_Graph(&graph), m_PassIndex(passIndex)
	{
	}

	void RenderGraphPassBuilder::Read(RenderGraphResourceHandle handle)
	{
		Assert(handle.IsValid(), "RenderGraphPassBuilder::Read called with invalid resource");
		m_Graph->m_Passes[m_PassIndex].Reads.push_back(handle);
		m_Graph->MarkResourceUsage(handle, m_PassIndex);
	}

	void RenderGraphPassBuilder::Write(RenderGraphResourceHandle handle)
	{
		Assert(handle.IsValid(), "RenderGraphPassBuilder::Write called with invalid resource");
		m_Graph->m_Passes[m_PassIndex].Writes.push_back(handle);
		m_Graph->MarkResourceUsage(handle, m_PassIndex);
	}

	RenderGraphResourceHandle RenderGraph::CreateResource(RenderGraphResourceDesc desc)
	{
		return AddResource(std::move(desc), false);
	}

	RenderGraphResourceHandle RenderGraph::ImportResource(RenderGraphResourceDesc desc)
	{
		return AddResource(std::move(desc), true);
	}

	RenderGraphPassBuilder RenderGraph::AddPass(std::string name, RenderGraphExecuteFn execute)
	{
		m_IsCompiled = false;

		auto& pass = m_Passes.emplace_back();
		pass.Name = std::move(name);
		pass.Execute = std::move(execute);
		m_Dependencies.emplace_back();

		return RenderGraphPassBuilder(*this, static_cast<uint32_t>(m_Passes.size() - 1));
	}

	void RenderGraph::Compile()
	{
		m_ExecutionOrder.clear();
		m_Dependencies.assign(m_Passes.size(), {});

		std::vector<int32_t> lastWriter(m_Resources.size(), -1);

		for (uint32_t passIndex = 0; passIndex < m_Passes.size(); ++passIndex)
		{
			const auto& pass = m_Passes[passIndex];

			for (auto handle : pass.Reads)
			{
				Assert(handle.Index < m_Resources.size(), "RenderGraph::Compile encountered invalid read handle");
				if (lastWriter[handle.Index] != -1)
				{
					AddDependency(static_cast<uint32_t>(lastWriter[handle.Index]), passIndex);
				}
			}

			for (auto handle : pass.Writes)
			{
				Assert(handle.Index < m_Resources.size(), "RenderGraph::Compile encountered invalid write handle");
				if (lastWriter[handle.Index] != -1 && lastWriter[handle.Index] != static_cast<int32_t>(passIndex))
				{
					AddDependency(static_cast<uint32_t>(lastWriter[handle.Index]), passIndex);
				}

				lastWriter[handle.Index] = static_cast<int32_t>(passIndex);
			}
		}

		std::vector<uint32_t> indegree(m_Passes.size(), 0);
		for (const auto& edges : m_Dependencies)
		{
			for (auto dependency : edges)
			{
				++indegree[dependency];
			}
		}

		std::queue<uint32_t> ready{};
		for (uint32_t index = 0; index < indegree.size(); ++index)
		{
			if (indegree[index] == 0)
			{
				ready.push(index);
			}
		}

		while (!ready.empty())
		{
			auto node = ready.front();
			ready.pop();

			m_ExecutionOrder.push_back(node);

			for (auto dependency : m_Dependencies[node])
			{
				Assert(indegree[dependency] > 0, "RenderGraph::Compile detected invalid dependency graph");
				if (--indegree[dependency] == 0)
				{
					ready.push(dependency);
				}
			}
		}

		Assert(m_ExecutionOrder.size() == m_Passes.size(), "RenderGraph::Compile failed to produce a valid execution order");

		std::vector<uint32_t> passPosition(m_Passes.size(), 0);
		for (uint32_t i = 0; i < m_ExecutionOrder.size(); ++i)
		{
			passPosition[m_ExecutionOrder[i]] = i;
		}

		std::vector<uint32_t> physicalLastUse{};
		for (auto& resource : m_Resources)
		{
			if (resource.Passes.empty())
			{
				continue;
			}

			uint32_t firstUse = std::numeric_limits<uint32_t>::max();
			uint32_t lastUse = 0;
			for (auto passIndex : resource.Passes)
			{
				auto position = passPosition[passIndex];
				firstUse = std::min(firstUse, position);
				lastUse = std::max(lastUse, position);
			}

			if (resource.Imported)
			{
				resource.PhysicalIndex = static_cast<uint32_t>(physicalLastUse.size());
				physicalLastUse.push_back(std::numeric_limits<uint32_t>::max());
				continue;
			}

			size_t reuseSlot = physicalLastUse.size();
			for (size_t slot = 0; slot < physicalLastUse.size(); ++slot)
			{
				if (physicalLastUse[slot] < firstUse)
				{
					reuseSlot = slot;
					break;
				}
			}

			if (reuseSlot == physicalLastUse.size())
			{
				physicalLastUse.push_back(lastUse);
				resource.PhysicalIndex = static_cast<uint32_t>(physicalLastUse.size() - 1);
			}
			else
			{
				physicalLastUse[reuseSlot] = lastUse;
				resource.PhysicalIndex = static_cast<uint32_t>(reuseSlot);
			}
		}

		m_IsCompiled = true;
	}

	void RenderGraph::Execute(RHI::ICommandList& cmdList)
	{
		if (!m_IsCompiled)
		{
			Compile();
		}

		RenderGraphExecutionContext context(*this);
		for (auto passIndex : m_ExecutionOrder)
		{
			auto& pass = m_Passes[passIndex];
			if (pass.Execute)
			{
				pass.Execute(context, cmdList);
			}
		}
	}

	const RenderGraphResource& RenderGraph::GetResource(RenderGraphResourceHandle handle) const
	{
		Assert(handle.Index < m_Resources.size(), "RenderGraph::GetResource received invalid handle");
		return m_Resources[handle.Index];
	}

	RenderGraphResourceHandle RenderGraph::AddResource(RenderGraphResourceDesc desc, bool imported)
	{
		RenderGraphResourceHandle handle{ static_cast<uint32_t>(m_Resources.size()) };
		auto& resource = m_Resources.emplace_back();
		resource.Desc = std::move(desc);
		resource.Imported = imported;

		m_IsCompiled = false;
		return handle;
	}

	void RenderGraph::MarkResourceUsage(RenderGraphResourceHandle handle, uint32_t passIndex)
	{
		Assert(handle.Index < m_Resources.size(), "RenderGraph::MarkResourceUsage received invalid handle");
		auto& passes = m_Resources[handle.Index].Passes;
		if (passes.empty() || passes.back() != passIndex)
		{
			passes.push_back(passIndex);
		}
	}

	void RenderGraph::AddDependency(uint32_t before, uint32_t after)
	{
		auto& edges = m_Dependencies[before];
		if (std::ranges::find(edges, after) == edges.end())
		{
			edges.push_back(after);
		}
	}

	RenderGraphExecutionContext::RenderGraphExecutionContext(const RenderGraph& graph)
		: m_Graph(&graph)
	{
	}

	const RenderGraphResource& RenderGraphExecutionContext::GetResource(RenderGraphResourceHandle handle) const
	{
		Assert(m_Graph, "RenderGraphExecutionContext used without graph");
		return m_Graph->GetResource(handle);
	}

	uint32_t RenderGraphExecutionContext::GetPhysicalResource(RenderGraphResourceHandle handle) const
	{
		return GetResource(handle).PhysicalIndex;
	}
}
