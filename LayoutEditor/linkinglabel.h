#ifndef LINKINGLABEL_H
#define LINKINGLABEL_H
#include "positionablelabel.h"
#include "linkingobject.h"

class LinkingLabel : public PositionableLabel, public LinkingObject
{
 Q_OBJECT
 Q_INTERFACES(LinkingObject)
public:
 LinkingLabel(QWidget *parent = nullptr);
 /*public*/ LinkingLabel(/*@Nonnull*/ QString s, /*@Nonnull*/ Editor* editor, /*@Nonnull */QString url, QWidget *parent = nullptr);
 /*public*/ LinkingLabel(NamedIcon* s, /*@Nonnull*/ Editor* editor, /*@Nonnull*/ QString url, QWidget *parent = nullptr);
 /*public*/ Positionable* deepClone();
 /*public*/ QString getURL() ;
 /*public*/ void setULRL(QString u);
 /*public*/ bool setLinkMenu(QMenu* popup);
 /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* event);

private:
 static Logger* log;
 QString url;

protected:
 /*protected*/ Positionable* finishClone(LinkingLabel* pos);

};

#endif // LINKINGLABEL_H
