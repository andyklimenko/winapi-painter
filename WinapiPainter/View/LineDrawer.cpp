#include "stdafx.h"
#include "LineDrawer.h"

LineDrawer::LineDrawer()
{
}


LineDrawer::~LineDrawer()
{
}

void LineDrawer::Draw(HDC hdc, const POINT from, const POINT to)
{
	MoveToEx(hdc, from.x, from.y, nullptr);
	LineTo(hdc, to.x, to.y);
}
