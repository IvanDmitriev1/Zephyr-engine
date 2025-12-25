module;

#include <glad/glad.h>

export module Zephyr.Renderer.OpenGL.Debug;

import std.compat;

namespace Zephyr::RHI::OpenGL::Debug
{
	constexpr std::string_view GLDebugSourceToString(GLenum source);
	constexpr std::string_view GLDebugTypeToString(GLenum type);
	constexpr std::string_view GLDebugSeverityToString(GLenum severity);

	void GLDebugCallback(GLenum source,
						 GLenum type,
						 GLuint id,
						 GLenum severity,
						 GLsizei length,
						 const GLchar* message,
						 const void* userParam);

	export void InitOpenGLDebugMessageCallback();
}