module;

#include <glad/glad.h>

export module zephyr.opengl.GlUtils;

import zephyr.core.coreTypes;

namespace zephyr
{
	export class GlUtils
	{
		public:
			static void InitOpenGLDebugMessageCallback();
	};
	

	static constexpr std::string_view GLDebugSourceToString(GLenum source)
	{
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:     return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:     return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:
		default:                              return "UNKNOWN";
		}
	}

	static constexpr std::string_view GLDebugTypeToString(GLenum type)
	{
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "UDEFINED BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: 	    return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE:         return "PERFORMANCE";
		case GL_DEBUG_TYPE_OTHER:               return "OTHER";
		case GL_DEBUG_TYPE_MARKER:              return "MARKER";
		default:                                return "UNKNOWN";
		}

	}

	static constexpr std::string_view GLDebugSeverityToString(GLenum severity)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         return "HIGH";
		case GL_DEBUG_SEVERITY_MEDIUM:       return "MEDIUM";
		case GL_DEBUG_SEVERITY_LOW:          return "LOW";
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		default:                             return "UNKNOWN";
		}
	}

	static void GLDebugCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		if (severity != GL_DEBUG_SEVERITY_MEDIUM && severity != GL_DEBUG_SEVERITY_HIGH)
			return;

		const auto sourceStr = GLDebugSourceToString(source);
		const auto typeStr = GLDebugTypeToString(type);
		const auto severityStr = GLDebugSeverityToString(severity);

		std::println("[OpenGL] [{} - {} ({})]: [{}] {}", severityStr, typeStr, id, sourceStr, message);

		DebugBreak();
	}

	void GlUtils::InitOpenGLDebugMessageCallback()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(GLDebugCallback, nullptr);
	}
}
