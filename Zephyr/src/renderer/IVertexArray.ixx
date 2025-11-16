export module zephyr.renderer.IVertexArray;

export import zephyr.core.coreTypes;
export import zephyr.renderer.IBuffer;
export import zephyr.renderer.VertexLayout;
export import zephyr.renderer.IndexTypes;

export namespace zephyr
{
	struct VertexArrayCreateInfo
	{
		VertexArrayCreateInfo(
			const Ref<IBuffer>& vertexBuffer,
			VertexLayout layout,
			const Ref<IBuffer>& indexBuffer,
			IndexType indexType)
			: VertexBuffer(std::move(vertexBuffer))
			, Layout(std::move(layout))
			, IndexBuffer(std::move(indexBuffer))
			, IndexType(indexType)
		{
			Assert(!VertexBuffer || Layout.GetAttributes().size() > 0,
				"VertexArrayCreateInfo::VertexArrayCreateInfo: Vertex layout must be provided with vertex buffer!");
			Assert(VertexBuffer->GetType() == BufferType::Vertex,
				"VertexArrayCreateInfo::VertexArrayCreateInfo: Provided buffer is not a vertex buffer!");

			Assert(IndexBuffer->GetType() == BufferType::Index,
				"VertexArrayCreateInfo::VertexArrayCreateInfo: Provided buffer is not an index buffer!");
		}

		const Ref<IBuffer> VertexBuffer{};
		const VertexLayout Layout{};

		const Ref<IBuffer> IndexBuffer{};
		const IndexType IndexType{};
	};

	class IVertexArray
	{
	public:
		IVertexArray() = default;
		virtual ~IVertexArray() = default;

		IVertexArray(const IVertexArray&) = delete;
		IVertexArray& operator=(const IVertexArray&) = delete;

	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const Ref<IBuffer>& GetVertexBuffer() const = 0;
		virtual const Ref<IBuffer>& GetIndexBuffer() const = 0;

		virtual uint32_t GetIndexCount() const = 0;
		virtual IndexType GetIndexType() const = 0;

		// Factory – implemented per backend
		static Ref<IVertexArray> Create(const VertexArrayCreateInfo& info);
	};
}