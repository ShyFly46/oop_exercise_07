#ifndef FACTORY_H
#define FACTORY_H

#include"figures.h"
#include"point.h"

struct Factory{
	Figure* createTri(const Point& a, const Point& b, const Point& c){
		Triangle* newF = new Triangle;
		newF->a = a;
		newF->b = b;
		newF->c = c;
		return (Figure*) newF;
	}
	
	Figure* createSq(const Point& a, const Point& c){
		Square* newF = new Square;
		newF->a = a;
		newF->c = c;
		
		Point cent = (a+c) * 0.5;
		Point vec = c - cent;
		// rotate by 45 deg clockwise
		float tmp = -vec.x;
		vec.x = vec.y;
		vec.y = tmp;
		
		newF->b = cent - vec;
		newF->d = cent + vec;
		
		return (Figure*) newF;
	}
	
	Figure* createRct(const Point& a, const Point& b, float ratio){
		Rect* newF = new Rect;
		newF->a = a;
		newF->b = b;
		
		Point vec = b - a;
		Point v2 = vec;
		// rotate by 45 deg clockwise
		float tmp = -vec.x;
		vec.x = vec.y;
		vec.y = tmp;
		//length ratio'd
		vec = vec * ratio;
		
		newF->d = a + vec;
		newF->c = newF->d + v2;
		
		return (Figure*) newF;
	}
	
	Figure* createRct(const Point& a, const Point& b, const Point& c){
		Rect* newF = new Rect;
		newF->a = a;
		newF->b = b;
		newF->c = c;
		
		newF->d = a + (c - b);
		
		return (Figure*) newF;
	}
};

#endif