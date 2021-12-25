#ifndef SCALE_H
#define SCALE_H

#include <QObject>
#include "exceptions.h"
#include "constrainedbean.h"

class Logger;
class Scale : public ConstrainedBean
{
 Q_OBJECT
public:
 explicit Scale(QObject *parent = nullptr);
 /*public*/ Scale(/*@Nonnull*/ QString name, double ratio, QString userName,QObject *parent = nullptr);
 /*public*/ QString getScaleName();
 /*public*/ QString getUserName();
 /*public*/ double getScaleRatio();
 /*public*/ double getScaleFactor();
 /*public*/ void setUserName(/*@Nonnull*/ QString newName) /*throw (IllegalArgumentException, PropertyVetoException)*/;
 /*public*/ void setScaleRatio(double newRatio) /*throw (IllegalArgumentException, PropertyVetoException)*/;
 /*public*/ QString toString();

signals:

public slots:

private:
 /*private*/ QString _name = "HO";  // NOI18N
 /*private*/ QString _userName = "HO";  // NOI18N
 /*private*/ double _ratio = 87.1;
 /*private*/ double _factor = 1 / 87.1;
 static Logger* log;
};

#endif // SCALE_H
