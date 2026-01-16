export module ZephyrEditor.TemplateTypes;

export import std;

export namespace ZephyrEditor
{
	struct ProjectTemplateFile
	{
		std::filesystem::path RelativeFilePath{};
	};

	struct ProjectTemplate
	{
		std::string Name{};
		std::filesystem::path TemplateRoot{};
		std::vector<ProjectTemplateFile> Files{};
	};

	class TemplateContext
	{
	public:
		TemplateContext() = default;
		~TemplateContext() = default;

		void Set(std::string key, std::string value)
		{
			auto it = std::ranges::find_if(Tokens, [&](const TemplateToken& t)
			{
				return t.Key == key;
			});

			if (it != Tokens.end())
			{
				it->Value = std::move(value);
				return;
			}

			Tokens.push_back(TemplateToken{ .Key = std::move(key), .Value = std::move(value) });
		}

		bool TryGet(std::string_view key, std::string_view& value) const
		{
			value = std::string_view{};

			auto it = std::ranges::find_if(Tokens, [&](const TemplateToken& t)
			{
				return std::string_view{ t.Key } == key;
			});

			if (it == Tokens.end())
			{
				return false;
			}

			value = it->Value;
			return true;
		}

		std::string_view Get(std::string_view key) const
		{
			std::string_view value{};

			if (!TryGet(key, value))
			{
				throw std::runtime_error(std::format("Token not found: {}", key));
			}

			return value;
		}

	private:
		struct TemplateToken
		{
			std::string Key{};
			std::string Value{};
		};

		std::vector<TemplateToken> Tokens{};
	};
}