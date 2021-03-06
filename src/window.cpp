#include "window.h"

#include "utility/log.hpp"
#include "utility/tracer.h"

#include "core/assert.h"

GLFWwindow *Window::handle = nullptr;

Size2<GLsizei> Window::size{};
int Window::vsync{};

void Window::init(const char *title, const Size2<GLsizei> &size, const bool vsyncEnabled) {
	auto t = Tracer::trace();

	Window::size = size;

	glfwSetErrorCallback([](int error, const char *description) {
		fmt::print(stderr, "GLFW error ({}): {}", error, description);
	});

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	handle = glfwCreateWindow(size.w, size.h, title, NULL, NULL);
	glfwMakeContextCurrent(handle);
	debugAssert(handle, "Failed to create GLFW window");

	setVsync(vsyncEnabled);

	debugAssert(gladLoadGL((GLADloadfunc)glfwGetProcAddress),
				"Failed to initialize OpenGL context");

	debugLog("OpenGL info:\n");
	debugLog("\tVendor: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
	debugLog("\tRenderer: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
	debugLog("\tVersion: {:s}\n", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
}
void Window::shutdown() {
	auto t = Tracer::trace();

	glfwTerminate();
}

bool Window::closing() {
	auto t = Tracer::trace();
	
	return glfwWindowShouldClose(handle);
}

void Window::showFrame() {
	auto t = Tracer::trace();
	
	glfwSwapBuffers(handle);
}

void Window::setVsync(bool enabled) {
	auto t = Tracer::trace();
	vsync = enabled ? 1 : 0;
	glfwSwapInterval(vsync);
}

void Window::pollEvents() {
	auto t = Tracer::trace();

	glfwPollEvents();
}

void Window::setTitle(const char *title) {
	auto t = Tracer::trace();

	glfwSetWindowTitle(handle, title);
}
