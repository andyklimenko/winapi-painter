#include "stdafx.h"

#include "LineDrawer.h"
#include "RectDrawer.h"
#include "EllipseDrawer.h"
#include "DrawerFactory.h"

BaseDrawer * DrawerFactory::CreateDrawer(PrimitiveToDraw primitive)
{
	switch (primitive)
	{
	case LinePrimitive:
		return new LineDrawer();
	case RectanglePrimitive:
		return new RectDrawer();
	case EllipsePrimitive:
		return new EllipseDrawer();
	default:
		break;
	}
	//not implemented
	return nullptr;
}
