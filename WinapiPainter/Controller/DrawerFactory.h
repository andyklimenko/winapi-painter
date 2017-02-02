#pragma once

#include <BaseDrawer.h>

enum PrimitiveToDraw
{
	Line = 0,
	EllipsePrimitive,
	RectanglePrimitive
};

/*
 * A factory designated to create drawer-objects
 */
class DrawerFactory
{
public:
	DrawerFactory() = delete;
	~DrawerFactory() = delete;

	static BaseDrawer* CreateDrawer(PrimitiveToDraw primitive);
};

