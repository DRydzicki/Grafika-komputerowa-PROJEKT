#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Engine/EngineLoader.h"
#include <windows.h>

namespace Exc4 {
	const double PI = 3.1415;
	static std::vector <sf::Vector2i> points;

	static bool ex1, ex2, ex3, ex4, done;
	void DrawWindow();
	void WindowContent(sf::RenderWindow& window);

	int side(Point, Point, Point);
	bool sameSide(Point, Point, Point, Point);
	bool intersect(Point, Point, Point, Point);
	int sign(int);
}
