#include <cstdio>
#include <utility>
#include <string>

class Widget{
	int t;

public:
	Widget() : t(1) {};
	Widget(int ti) : t(ti) {};

	void setTime(int ti){
		t = ti;
	}

	int getTime() { return t; }
};

void someFunc(Widget w, int ti){
	printf("address: %p\n", &w);
	w.setTime(ti);
}

int main(){

	int x = 26;
	const int cs = x;
	int& rx = x;

	printf("%d, %p\n", rx, &rx);

	x = 27;

	printf("%d %p\n", rx, &x);

	Widget wid;
	printf("address: %p\n", &wid);
	printf("time: %d\n", wid.getTime());

	someFunc(wid, 2);
	printf("time: %d\n", wid.getTime());

	someFunc(std::move(wid), 2);
	printf("time: %d\n", wid.getTime());

	return 0;
}
