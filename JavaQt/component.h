#ifndef COMPONENT_H
#define COMPONENT_H

#include "jpanel.h"
//#include <QObject>

class DropTarget;
class Component : public JPanel
{
    Q_OBJECT
public:
    explicit Component(QWidget *parent = 0);
    /*public*/ /*synchronized*/ void setDropTarget(DropTarget* dt);
    /*public*/ /*synchronized*/ DropTarget* getDropTarget();

signals:

public slots:
private:
  DropTarget* dropTarget;
  Component* peer;

  void dragEnterEvent(QDragEnterEvent *);
  void dropEvent(QDropEvent *);


};

#endif // COMPONENT_H
