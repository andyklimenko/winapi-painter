#include "stdafx.h"
#include "EllipseDrawer.h"

EllipseDrawer::EllipseDrawer()
{
}


EllipseDrawer::~EllipseDrawer()
{
}

void EllipseDrawer::Draw(HDC hdc, const POINT from, const POINT to)
{
	Ellipse(hdc, from.x, from.y, to.x, to.y);
}
