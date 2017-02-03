#pragma once

enum PrimitiveToDraw
{
	LinePrimitive = 0,
	EllipsePrimitive,
	RectanglePrimitive
};

class BaseDrawer;

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

