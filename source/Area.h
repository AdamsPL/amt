#ifndef _AREA_H
#define _AREA_H 

#include <QString>
#include <QPolygonF>

class Area
{
public:
	bool contains(const QPointF &p) const;
	void add(const QPointF &p);
	void clear();

	inline const QString &getName() const { return name; }
	inline void setName(const QString &val) { name = val; }

	inline const QString &getGroup() const { return group; }
	inline void setGroup(const QString &val) { group = val; }

	inline const QPolygonF &getPolygon() const { return polygon; }

private:
	QString name;
	QString group;
	QPolygonF polygon;
};

#endif /* _AREA_H */
