#ifndef BORDERFACTORY_H
#define BORDERFACTORY_H

#include <QObject>
#include "border.h"
#include "matteborder.h"
#include <QIcon>
#include <QColor>
#include "lineborder.h"

class BorderFactory : QObject
{
 Q_OBJECT
public:
 /*public*/ static Border* createLineBorder(QColor color);
 /*public*/ static Border* createLineBorder(QColor color, int thickness);
 /*public*/ static Border* createLineBorder(QColor color, int thickness, bool rounded);
 /*public*/ static MatteBorder* createMatteBorder(int top, int left, int bottom, int right,
                                             QColor color);
 /*public*/ static MatteBorder* createMatteBorder(int top, int left, int bottom, int right,
                                             QIcon tileIcon);

private:
 BorderFactory(QObject* parent = 0);
};

#endif // BORDERFACTORY_H
