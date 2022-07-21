#include "renderer.h"

void Renderer::init() {
	// TODO(Nicolas): move shader compilation and creation to somewhere else
	auto programId = glCreateProgram();

	const GLchar *vertexShaderSource =
		"#version 460 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"\n"
		"void main(){\n"
		"	gl_Position = position;\n"
		"}\n"
		"\n";

	const GLchar *fragmentShaderSource =
		"#version 460 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main(){\n"
		"	color = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"}\n"
		"\n";

	auto compileShader = [](auto type, const GLchar *source) {
		auto shaderId = glCreateShader(type);
		glShaderSource(shaderId, 1, &source, nullptr);
		glCompileShader(shaderId);

		auto success = GL_TRUE;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar message[1024];
			glGetShaderInfoLog(shaderId, sizeof(message), nullptr, message);
			fmt::print(stderr, "Failed to compile {}shader: {}",
					   type == GL_VERTEX_SHADER	  ? "vertex " :
					   type == GL_FRAGMENT_SHADER ? "fragment " :
													"",
					   message);
			glDeleteShader(shaderId);
		}

		return shaderId;
	};
	auto vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	auto fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);
	glValidateProgram(programId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	glUseProgram(programId);

	// TODO(Nicolas): move buffer initialization to somewhere else
	GLfloat rectVertices[] = {
		.5F,  .5F,	// 0
		-.5F, .0F,	// 1
		.5F,  .0F,	// 2
		-.5F, -.5F, // 3
	};
	GLuint rectIndicies[] = {
		0,
		1,
		2,
		3,
	};

	GLuint vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	GLuint rectVerticesBufferId;
	glGenBuffers(1, &rectVerticesBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, rectVerticesBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	GLuint rectIndiciesBufferId;
	glGenBuffers(1, &rectIndiciesBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectIndiciesBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndicies), rectIndicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void *)0);
}

void Renderer::setViewport(const Rect<GLint, GLsizei> &rect) {
	const auto [x, y] = rect.pos;
	const auto [w, h] = rect.size;
	glViewport(x, y, w, h);
}

void Renderer::setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	glClearColor(red, green, blue, alpha);
}

void Renderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::renderFrame() {
	glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
}