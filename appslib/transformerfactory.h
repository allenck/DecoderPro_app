#ifndef TRANSFORMERFACTORY_H
#define TRANSFORMERFACTORY_H

#include <QObject>
#include "exceptions.h"

class TransformerFactory : public QObject
{
 Q_OBJECT
public:
 //explicit TransformerFactory(QObject *parent = 0);
 /*public*/ /*abstract*/ virtual void setAttribute(QString name, QVariant value);
 /*public*/ static TransformerFactory newInstance()
     throw (TransformerFactoryConfigurationError);

signals:

public slots:

protected:
 /**
  * Default constructor is protected on purpose.
  */
 /*protected*/ TransformerFactory(QObject* parent = 0);

};

#endif // TRANSFORMERFACTORY_H
