#include "stdafx.h"

#include "LineDrawer.h"
#include "RectDrawer.h"

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
	default:
		break;
	}
	//not implemented
	return nullptr;
}
