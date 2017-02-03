#pragma once

#include "BaseDrawer.h"

class RectDrawer : public BaseDrawer
{
public:
	RectDrawer();
	~RectDrawer();

private:
	virtual void Draw(HDC hdc, const POINT from, const POINT to);
};

