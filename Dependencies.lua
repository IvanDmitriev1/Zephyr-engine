IncludeDir = {}

IncludeDir["glfw"] = "%{wks.location}/Zephyr/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Zephyr/vendor/glad/include"
IncludeDir["glm"] = "%{wks.location}/Zephyr/vendor/glm"

Library = {}
Library["glfw"] = "%{wks.location}/Zephyr/vendor/glfw/lib/glfw3.lib"