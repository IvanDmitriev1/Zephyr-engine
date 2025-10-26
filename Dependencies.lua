IncludeDir = {}

IncludeDir["glfw"] = "%{wks.location}/Zephyr/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Zephyr/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/Zephyr/vendor/glm"
IncludeDir["imgui"] = "%{wks.location}/ZephyrEditor/vendor/imgui/include"
IncludeDir["imguiOpengl"] = "%{wks.location}/ZephyrEditor/vendor/imgui/platform/opengl"

Library = {}
Library["glfw"] = "%{wks.location}/Zephyr/vendor/glfw/lib/glfw3.lib"