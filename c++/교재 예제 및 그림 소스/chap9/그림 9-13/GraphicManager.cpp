#include <iostream>
#include "GraphicManager.h"
#include "Shape.h"
#include "Circle.h"
#include "Rect.h"

using namespace std;

void GraphicManager::run() {
	Shape *pStart=NULL; // 링크드 리스트의 헤더
	Shape *pNext=NULL; // 마지막에 달리 도형 객체에 대한 포인터
	Shape *newShape=NULL; // 새로 생성된 도형 객체에 대한 포인터

	while(true) {
		int shape = readShape(); // 사용자로부터 도형 종류 입력
		switch(shape) {
		case 0: // Circle
			newShape = new Circle();
			break;
		case 1: // Rect
			newShape = new Rect();
			break;
		}
		if(pStart == NULL) { // 처음으로 도형을 달 때
			pStart = newShape;
			pNext = pStart;
		}
		else {
			pNext->add(newShape);
		}


	}
}

int GraphicManager::readShape() {
	int shape;
	prompt();
	cin >> shape;
	return shape;
}

void GraphicManager::prompt() {
	cout << "그리고자 하는 도형, 원(0), 사각형(1)";
}