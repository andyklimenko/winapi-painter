#include "stdafx.h"
#include "BaseDrawer.h"

BaseDrawer::BaseDrawer() : m_From{ 0, 0 }, m_To{0, 0}
{
}

BaseDrawer::~BaseDrawer() 
{
}

void BaseDrawer::Draw(HDC hdc)
{
	Draw(hdc, m_From, m_To);
}

void BaseDrawer::setFrom(const POINT from)
{
	m_From.x = from.x;
	m_From.y = from.y;
}

void BaseDrawer::setTo(const POINT to)
{
	m_To.x = to.x;
	m_To.y = to.y;
}
