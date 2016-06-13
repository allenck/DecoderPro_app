#ifndef COMPONENT_H
#define COMPONENT_H

//#include <QWidget>
#include <QObject>

class DropTarget;
class Component : public QObject
{
    Q_OBJECT
public:
    explicit Component(QObject *parent = 0);
    /*public*/ /*synchronized*/ void setDropTarget(DropTarget* dt);
    /*public*/ /*synchronized*/ DropTarget* getDropTarget();

signals:

public slots:
private:
  DropTarget* dropTarget;
  Component* peer;

};

#endif // COMPONENT_H
