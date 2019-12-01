#ifndef ARBITRARYPROPERTYSUPPORT_H
#define ARBITRARYPROPERTYSUPPORT_H

#include <QObject>
#include "beaninterface.h"
#include <QMap>
#include <QVariant>

class UnboundBean;
class ArbitraryPropertySupport : public QObject, public BeanInterface
{
 Q_OBJECT
 Q_INTERFACES(BeanInterface)
public:
 explicit ArbitraryPropertySupport(QObject *parent = nullptr);
 /*public*/ ArbitraryPropertySupport(UnboundBean* bean, QObject *parent);
 /*public*/ void setIndexedProperty(QString key, int index, QVariant value);
 /*public*/ QVariant getIndexedProperty(QString key, int index);
 /*public*/ void setProperty(QString key, QVariant value);
 /*public*/ QVariant getProperty(QString key);
 /*public*/ bool hasProperty(QString key);
 /*public*/ bool hasIndexedProperty(QString key);
 /*public*/ QSet<QString> getPropertyNames();

signals:

public slots:

private:
 /*private*/ /*final*/ QMap<QString, QVariantList> properties;// = new HashMap<>();
 /*private*/ /*final*/ UnboundBean* bean;

};

#endif // ARBITRARYPROPERTYSUPPORT_H
