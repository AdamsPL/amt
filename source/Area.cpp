#include "Area.h"

#include <QDebug>

bool Area::contains(const QPointF &p) const
{
	if (polygon.size() == 0)
		return false;
	if (polygon.size() == 1)
		return (polygon[0] == p);
	return polygon.containsPoint(p, Qt::WindingFill);
}

void Area::add(const QPointF &p)
{
	if (polygon.size() == 0) {
		polygon << p;
		return;
	}
	if (polygon.size() > 1)
		polygon.pop_back();
	polygon << p;
	polygon << polygon.first();
}

void Area::clear()
{
	polygon = QPolygonF();
}
