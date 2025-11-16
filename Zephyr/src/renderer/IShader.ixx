export module zephyr.renderer.IShader;

export import zephyr.core.coreTypes;
export import glm;

export namespace zephyr
{
    enum class ShaderStage
    {
        Vertex,
        Fragment,
        Geometry,
        TessControl,
        TessEvaluation,
        Compute
    };

    struct ShaderStageDesc
    {
        ShaderStage Stage;
        std::string FilePath;
    };

    struct ShaderCreateInfo
    {
        std::string Name;
        std::vector<ShaderStageDesc> Stages;
    };

    class IShader
    {
    public:
		IShader() = default;
        virtual ~IShader() = default;

        IShader(const IShader&) = delete;
        IShader& operator=(const IShader&) = delete;

    public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetMat4(std::string_view name, const glm::mat4& value) = 0;
        virtual void SetVec3(std::string_view name, const glm::vec3& value) = 0;
        virtual void SetFloat(std::string_view name, float value) = 0;

        // Backend decides how to load/compile.
        static Ref<IShader> Create(const ShaderCreateInfo& info);
    };
}