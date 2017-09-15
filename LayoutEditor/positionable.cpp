#include "positionable.h"
#include <QGraphicsItemGroup>

Positionable::Positionable(QWidget *parent) :
    QLabel(parent)
{
 _itemGroup = new QGraphicsItemGroup;
 _handleGroup = new QGraphicsItemGroup;
}

Positionable::Positionable(QString text, QWidget *parent) : QLabel(text, parent)
{
 _itemGroup = new QGraphicsItemGroup;
 _handleGroup = new QGraphicsItemGroup;
}

QGraphicsItem* Positionable::getItem()
{
 return _itemGroup;
}

void Positionable::setItem(QGraphicsTextItem* item)
{
 _itemGroup->addToGroup(item);
}
