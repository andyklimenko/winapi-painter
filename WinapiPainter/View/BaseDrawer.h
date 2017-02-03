#pragma once

#include <windef.h>

/*
 * Base class responsible for drawing primitives. 
 * Can be extended by implementation of any concrete primitive: line, rectangle, etc
 */
class BaseDrawer
{
public:
	BaseDrawer();
	virtual ~BaseDrawer();

public:
	void Draw(HDC hdc);
	void setFrom(const POINT from);
	void setTo(const POINT to);
protected:
	/*
	 * A method to be implemented for drawing concrete primitive in an 
	 * imaginary rectangle specified with two given points
	 *  from------------------
	 *  |                    |
	 *  |-------------------to
	 */
	virtual void Draw(HDC hdc, const POINT from, const POINT to) = 0;

private:
	POINT m_From;
	POINT m_To;
};

