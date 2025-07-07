#ifndef SHAPE
#define SHAPE

class Shape {
	Shape* next;
protected:
	virtual void draw()=0;
public:
	Shape() { next = NULL;}
	virtual ~Shape() { }
	void paint();
	Shape* add(Shape* p);
	Shape* getNext() { return next;}
};

#endif