export module zephyr.core.LayerStack;

export import zephyr.core.coreTypes;
export import zephyr.core.Layer;

export namespace zephyr
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
		TLayer& PushLayer(Args&& ... args);

		template<typename TLayer, typename ... Args>
		requires(std::is_base_of_v<Layer, TLayer>)
		TLayer& PushOverlay(Args&& ... args);

		void PopLayer(Layer& layer);
		void Clear();

		void OnEvent(const IEvent& event);
		void OnUpdate(float ts);
		void OnRender();

	private:
		std::vector<Scope<Layer>> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};

	template<typename TLayer, typename ... Args>
	requires(std::is_base_of_v<Layer, TLayer>)
	TLayer& LayerStack::PushLayer(Args&& ...args)
	{
		auto layer = CreateScope<TLayer>(std::forward<Args>(args)...);
		TLayer* raw = layer.get();

		m_Layers.insert(m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsertIndex),
			std::move(layer));
		++m_LayerInsertIndex;
		raw->OnAttach();

		return *raw;
	}

	template<typename TLayer, typename ...Args>
	requires(std::is_base_of_v<Layer, TLayer>)
	TLayer& LayerStack::PushOverlay(Args&& ...args)
	{
		auto layer = CreateScope<TLayer>(std::forward<Args>(args)...);
		TLayer* raw = layer.get();

		m_Layers.emplace_back(std::move(layer));
		raw->OnAttach();

		return *raw;
	}
}