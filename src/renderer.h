#pragma once

#include "utility/point.hpp"
#include "utility/rect.hpp"

class Renderer {
public:
	static void init();
	
	static void setViewport(const Rect<GLint, GLsizei> &rect);

	static void setDrawColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	static void clear();

	static void renderFrame();

	// TODO(Nicolas): line drawing functions
	//static void drawLine(const Point2<GLfloat> &point);
	//static void drawLine(const Point2<GLfloat> &point, GLfloat thickness);
};