#pragma once

#include "BaseDrawer.h"

class LineDrawer : public BaseDrawer
{
public:
	LineDrawer();
	~LineDrawer();

private:
	virtual void Draw(HDC hdc, const POINT from, const POINT to);
};

