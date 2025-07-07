#include "mike.h"

namespace kitae {
	int f() {
		return 1;
	}
	void m() {
		f();
		mike::f();
	}
}