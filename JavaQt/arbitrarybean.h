#ifndef ARBITRARYBEAN_H
#define ARBITRARYBEAN_H
#include "bean.h"

class ArbitraryPropertySupport;
class ArbitraryBean : public Bean
{
 Q_OBJECT

public:
 ArbitraryBean(QObject* parent = nullptr);
 ~ArbitraryBean(){}
 ArbitraryBean(const ArbitraryBean&) : Bean() {}
 /*public*/ void setProperty(QString key, QVariant value);
 /*public*/ void setIndexedProperty(QString key, int index, QVariant value);
 /*public*/ QVariant getIndexedProperty(QString key, int index);
 /*public*/ QVariant getProperty(QString key);
 /*public*/ bool hasProperty(QString key);
 /*public*/ bool hasIndexedProperty(QString key);
 /*public*/ QSet<QString> getPropertyNames();

protected:
 /*protected*/ /*final*/ ArbitraryPropertySupport* arbitraryPropertySupport;// = new ArbitraryPropertySupport(this);

};

#endif // ARBITRARYBEAN_H
