#include "stdafx.h"

#include "LineDrawer.h"

#include "DrawerFactory.h"

BaseDrawer * DrawerFactory::CreateDrawer(PrimitiveToDraw primitive)
{
	switch (primitive)
	{
	case LinePrimitive:
		return new LineDrawer();
	case RectanglePrimitive:
	case EllipsePrimitive:
	default:
		break;
	}
	//not implemented
	return nullptr;
}
