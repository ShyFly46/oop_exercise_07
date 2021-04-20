#ifndef POINT_H
#define POINT_H

struct Point{
	float x, y;
	
	Point(float x = 0, float y = 0)
		: x(x), y(y)
	{}
};

Point operator+ (const Point& a, const Point& b){
	return Point(a.x + b.x , a.y + b.y);
}
Point operator- (const Point& a, const Point& b){
	return Point(a.x - b.x , a.y - b.y);
}
Point operator* (const Point& p, float f){
	return Point(p.x * f, p.y * f);
}

std::ostream& operator<<(std::ostream& out, const Point& p){
	out << "{"
	    << p.x
	    << ", "
	    << p.y
	    << "}";
	return out;
}
std::istream& operator>>(std::istream& in, Point& p){
	in >> p.x >> p.y;
	return in;
}

#endif