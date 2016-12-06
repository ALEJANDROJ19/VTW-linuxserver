#include "stdafx.h"
#include "controller.h"
Display *dpy;
Window root_window;

//Constructors
controller::controller(int type,CoordinatesXY cord){
	
	this->type=type;
	this->_last_pos = CoordinatesXY(cord.x,cord.y);
	this->_is_last = false;
	
	//this->dpy = XOpenDisplay(0);
	//this->root_window = XRootWindow(dpy, 0);
	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	}
	
controller::controller(const controller& ctr){

	type=ctr.type;
	this->_last_pos = ctr._last_pos;
	this->_is_last = ctr._is_last;
	
	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	
	
	}
	
controller& controller::operator =(const controller& ctr){
	
	if(this!=&ctr){
		
		controller aux(ctr);
		type=aux.type;
		this->_last_pos = aux._last_pos;
		this->_is_last = aux._is_last;

		}
	
	return *this;
}

//Destructor

controller::~controller(){
	
}

//Operations
void controller::move(const CoordinatesXY &coordXY){
	//Move the mouse
	printf("1\t\tex: %f ey: %f\n", coordXY.x, coordXY.y);
	printf("1.1\t\tnx: %f ny: %f\n", this->_last_pos.x, this->_last_pos.y);

	XWarpPointer(dpy, None, root_window, 0, 0, 0, 0,this->_last_pos.x + coordXY.x*5,this->_last_pos.y + coordXY.y*5);
	printf("1.2\t\tnx: %f ny: %f\n", _last_pos.x, _last_pos.y);
	XFlush(dpy);
	
	_last_pos.x += coordXY.x*-5;
	_last_pos.y += coordXY.y*5;
	printf("2\t\tnx: %f ny: %f\n", _last_pos.x, _last_pos.y);
}

void controller::moveAbs(const CoordinatesXY &coordXY) {
	//Move the mouse
	XWarpPointer(dpy, None, root_window, 0, 0, 0, 0,coordXY.x, coordXY.y);
	XFlush(dpy);
	printf("\t\tex: %f ey: %f\n", coordXY.x, coordXY.y);

	this->_last_pos.x = (float) coordXY.x;
	this->_last_pos.y = (float) coordXY.y;
	printf("2\t\tnx: %f ny: %f\n", this->_last_pos.x, this->_last_pos.y);





}
//private methods
