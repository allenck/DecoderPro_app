#ifndef ABSTRACTSTARTUPMODEL_H
#define ABSTRACTSTARTUPMODEL_H
#include "startupmodel.h"

class AbstractStartupModel : public StartupModel
{
public:
 /*public*/ QString getName();
 /*public*/ void setName(QString name);
 /*public*/ QString toString();
 /*public*/ bool isValid();
 /*public*/ QList<Exception*> getExceptions() ;
 /*public*/ void addException(/*@NonNULL*/ Exception* exception);

private:
 /*private*/ QString name;
 /*private*/ /*final*/ QList<Exception*> exceptions;// = new ArrayList<>();

protected:
 AbstractStartupModel(QObject* parent = 0);

};

#endif // ABSTRACTSTARTUPMODEL_H
