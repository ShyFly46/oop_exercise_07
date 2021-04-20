#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <fstream>
#include "point.h"

using namespace std;

struct Figure {
	virtual void print() = 0;
	virtual void serialize(ofstream &file) = 0;
};

struct Triangle : public Figure{
	Point a, b, c;

	void print() override{
		std::cout
			<< "Tri: \t"
			<< "a"     << a
			<< "   b" << b
			<< "   c" << c
			<< '\n';
	};
	
	void serialize(ofstream &file) override{
		file
			<< "t "
			<< a.x << " " << a.y
			<< " "
			<< b.x << " " << b.y
			<< " "
			<< c.x << " " << c.y
			<< '\n';
	}
};

struct Square : public Figure{
	Point a, b, c, d;

	void print() override{
		std::cout
			<< "Sqr: \t"
			<< "a"     << a
			<< "   b" << b
			<< "   c" << c
			<< "   d" << d
			<< '\n';
	}
	
	void serialize(ofstream &file) override{
		file
			<< "q "
			<< a.x << " " << a.y
			<< " "
			<< c.x << " " << c.y
			<< '\n';
	}
};

struct Rect : public Figure{
	Point a, b, c, d;

	void print() override{
		std::cout
			<< "Rct: \t"
			<< "a"     << a
			<< "   b" << b
			<< "   c" << c
			<< "   d" << d
			<< '\n';
	}
	
	void serialize(ofstream &file) override{
		file
			<< "r "
			<< a.x << " " << a.y
			<< " "
			<< b.x << " " << b.y
			<< " "
			<< c.x << " " << c.y
			<< '\n';
	}
};

#endif