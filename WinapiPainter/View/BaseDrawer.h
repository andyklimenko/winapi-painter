#pragma once

#include <windef.h>

/*
 * Base class responsible for drawing primitives. 
 * Can be extended by implementation of any concrete primitive: line, rectangle, etc
 */
class BaseDrawer
{
public:
	BaseDrawer() {};
	virtual ~BaseDrawer() {};

	/*
	 * A method to be implemented for drawing concrete primitive in an 
	 * imaginary rectangle specified with two given points
	 *  from------------------
	 *  |                    |
	 *  |-------------------to
	 */
	virtual void Draw(const PPOINT from, const PPOINT to) = 0;
};

