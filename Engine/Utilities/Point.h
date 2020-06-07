#pragma once
class Point
{
public:
	double x, y;

	Point() {
	}
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	Point(sf::Vector2i vec) {
		this->x = vec.x;
		this->y = vec.y;
	}
	~Point(){
	}

private:
	void clear() {
		this->x = 0;
		this->y = 0;
	}

public:
	static void clearArray(Point* points,int size) {
		for (int i = 0; i < size; i++)
			points[i].clear();
	}
	Point fromVector(sf::Vector2i vec) {
		this->x = vec.x;
		this->y = vec.y;
	}
};


