#ifndef MANAGERDEFAULTSELECTOR_H
#define MANAGERDEFAULTSELECTOR_H

#include <QObject>
#include "propertychangelistener.h"
#include "logger.h"
#include "libPr3_global.h"
//class Item;
class LIBPR3SHARED_EXPORT ManagerDefaultSelector : public QObject
{
    Q_OBJECT
public:
    explicit ManagerDefaultSelector(QObject *parent = 0);
    /*public*/ static /*final*/ ManagerDefaultSelector* instance;// = new ManagerDefaultSelector();
    /*public*/ /*static*/ class Item
    {
    public:
        /*public*/ QString typeName;
        /*public*/ QString managerClass;
        /*public*/ bool proxy;
     Item(QString typeName,QString managerClass);
    };
    /*final*/ /*public*/ QList<Item*> knownManagers;// = new QList<Item*>();
    /*public*/ QString getDefault(QString managerClass);
    /*public*/ void setDefault(QString managerClass, QString userName);
    /*public*/ void configure();
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);

signals:
    void notifyPropertyChange(PropertyChangeEvent*);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
  Logger* log;
  /*public*/ QMap<QString, QString> defaults;// = new QMap<QString, QString>();
  // data members to hold contact with the property listeners
  /*final*/ /*private*/ static QVector<PropertyChangeListener*> listeners;// = new QVector<PropertyChangeListener*>();
protected:
  /*protected*/ void notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue);
friend class ManagerDefaultSelectorXml;
};
#endif // MANAGERDEFAULTSELECTOR_H
