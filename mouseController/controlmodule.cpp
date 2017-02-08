#include "controlmodule.h"

controlmodule::controlmodule() {
    CoordinatesXY init = inicialitzaCoord();
    this->_trans = translate();
	this->_contr = new controller(1, init);
	this->_lastXY = CoordinatesXY();
	this->_lastXYZ = CoordinatesXYZ();

	this->_contr->moveAbs(init);
//	printf("11\t\tnx: %f ny: %f\n", init.x, init.y);

}

controlmodule::~controlmodule() {
	delete _contr;
}

bool controlmodule::input(const CoordinatesXYZ &inp) {
	bool moved = false;
	CoordinatesXY tmp(_trans.trans(inp));
	
	if (this->_lastXY != tmp) {
		this->_contr->move(tmp);
		this->_lastXY = tmp;
		moved = true;
	}

	return moved;
}

bool controlmodule::rawmove(const CoordinatesXY &in) {
	bool moved = false;

	if (true) {
		this->_contr->moveAbs(in);
		moved = true;
	}

	return moved;
}

CoordinatesXY controlmodule::inicialitzaCoord() {
    CoordinatesXY res;
    Display* d = XOpenDisplay(nullptr);
    Screen* s = DefaultScreenOfDisplay(d);
    res.x = s->height;
    res.y = s->width;
	res.x /= 2; res.y /= 2;
    return res;
}
