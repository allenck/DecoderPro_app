#ifndef BORDERFACTORY_H
#define BORDERFACTORY_H

#include <QObject>
#include "border.h"
#include "matteborder.h"
#include <QIcon>
#include <QColor>

class MatteBorder;
class BorderFactory : QObject
{
 Q_OBJECT
public:
#if 0 // TODO:
 /*public*/ static Border* createLineBorder(QColor color, int thickness);
 /*public*/ static Border* createLineBorder(QColor color, int thickness, bool rounded);
#endif
 /*public*/ static MatteBorder* createMatteBorder(int top, int left, int bottom, int right,
                                             QColor color);
 /*public*/ static MatteBorder* createMatteBorder(int top, int left, int bottom, int right,
                                             QIcon tileIcon);

private:
 BorderFactory(QObject* parent = 0);
};

#endif // BORDERFACTORY_H
