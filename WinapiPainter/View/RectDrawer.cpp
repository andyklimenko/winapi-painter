#include "stdafx.h"
#include "RectDrawer.h"


RectDrawer::RectDrawer()
{
}


RectDrawer::~RectDrawer()
{
}

void RectDrawer::Draw(HDC hdc, const POINT from, const POINT to)
{
	Rectangle(hdc, from.x, from.y, to.x, to.y);
}
