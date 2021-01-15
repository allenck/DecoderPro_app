#ifndef UNBOUNDBEAN_H
#define UNBOUNDBEAN_H

#include <QObject>
#include "beaninterface.h"

class UnboundBean : public QObject, public BeanInterface
{
 Q_OBJECT
 Q_INTERFACES(BeanInterface)
public:
 explicit UnboundBean(QObject *parent = nullptr);
  ~UnboundBean() {}
  UnboundBean(const UnboundBean&) : QObject() {}
 /*public*/ QVariant getIndexedProperty(QString key, int index) override;
 /*public*/ QVariant getProperty(QString key) override;
 /*public*/ QSet<QString> getPropertyNames();
 /*public*/ bool hasProperty(QString key) ;
 /*public*/ bool hasIndexedProperty(QString key);
 /*public*/ void setIndexedProperty(QString key, int index, QVariant value);
 /*public*/ void setProperty(QString key, QVariant value);

signals:

public slots:
};
Q_DECLARE_METATYPE(UnboundBean)
#endif // UNBOUNDBEAN_H
