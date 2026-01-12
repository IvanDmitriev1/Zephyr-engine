IncludeDir = {}

IncludeDir["glfw"] = "%{wks.location}/Zephyr/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Zephyr/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/Zephyr/vendor/glm"
IncludeDir["spdlog"] = "%{wks.location}/Zephyr/vendor/spdlog/include"
IncludeDir["imgui"] = "%{wks.location}/Zephyr/vendor/imgui/include"
IncludeDir["imguiOpengl"] = "%{wks.location}/Zephyr/vendor/imgui/platform/opengl"

Library = {}
LibraryDir = {}
LibraryDir["glfw"] = "%{wks.location}/Zephyr/vendor/glfw/lib"
