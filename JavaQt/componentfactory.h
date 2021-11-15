#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <QObject>
#include <QMenu>

class ComponentFactory : public QObject
{
 Q_OBJECT
public:
 explicit ComponentFactory(QObject *parent = nullptr) : QObject(parent) {}
 /**
      * Provide a menu with all items attached to this system connection
      */
 /*abstract*/ virtual /*public*/ QMenu* getMenu(QWidget* /*frame*/) { return NULL;}
signals:

public slots:
};

#endif // COMPONENTFACTORY_H
