export module Zephyr.Core.LayerStack;

export import Zephyr.Core.CoreTypes;
export import Zephyr.Core.Layer;

export namespace Zephyr
{
	class LayerStack final
	{
	public:
		LayerStack() = default;
		~LayerStack();

		LayerStack(const LayerStack&) = delete;
		LayerStack& operator=(const LayerStack&) = delete;

	public:
		template<typename TLayer, typename ... Args>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer(Args&& ... args);

		template<typename TLayer, typename ... Args>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushOverlay(Args&& ... args);

		void PopByName(std::string_view name);

		void FlushPendingOps();

		void OnEvent(IEvent& event);
		void OnUpdate(float ts);
		void OnRender();
		void OnUiRender();

	private:
		enum class OperationType
		{
			PushLayer,
			PushOverlay,
			PopByName
		};

		struct PendingOperation
		{
			OperationType Type{};
			Scope<Layer> Layer{};
			std::string NameToPop{};
		};

		std::vector<Scope<Layer>> m_Layers;
		std::vector<PendingOperation> m_Pending;
		size_t m_LayerInsertIndex = 0;
	};

	template<typename TLayer, typename ... Args>
	requires(std::is_base_of_v<Layer, TLayer>)
	void LayerStack::PushLayer(Args&& ...args)
	{
		PendingOperation op
		{
			.Type = OperationType::PushLayer,
			.Layer = CreateScope<TLayer>(std::forward<Args>(args)...),
		};

		m_Pending.emplace_back(std::move(op));
	}

	template<typename TLayer, typename ...Args>
	requires(std::is_base_of_v<Layer, TLayer>)
	void LayerStack::PushOverlay(Args&& ...args)
	{
		PendingOperation op
		{
			.Type = OperationType::PushOverlay,
			.Layer = CreateScope<TLayer>(std::forward<Args>(args)...),
		};

		m_Pending.emplace_back(std::move(op));
	}
}