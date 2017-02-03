#pragma once

#include "BaseDrawer.h"

class EllipseDrawer : public BaseDrawer
{
public:
	EllipseDrawer();
	~EllipseDrawer();

private:
	virtual void Draw(HDC hdc, const POINT from, const POINT to);
};

