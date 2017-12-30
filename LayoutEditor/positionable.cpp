#include "positionable.h"
#include <QGraphicsItemGroup>

Positionable::Positionable(QWidget *parent) :
    QLabel(parent)
{
 _itemGroup = new MyGraphicsItemGroup;
 _itemGroup->setName("positionable");
 _handleGroup = new MyGraphicsItemGroup;
 _handleGroup->setName("positionable_handlegroup");
 setObjectName("positionable");
}

Positionable::Positionable(QString text, QWidget *parent) : QLabel(text, parent)
{
 _itemGroup = new MyGraphicsItemGroup;
 _handleGroup = new MyGraphicsItemGroup;
 setObjectName("positionable");
}

QGraphicsItem* Positionable::getItem()
{
 return _itemGroup;
}

void Positionable::setItem(QGraphicsTextItem* item)
{
 _itemGroup->addToGroup(item);
}
