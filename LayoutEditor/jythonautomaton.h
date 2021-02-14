#ifndef JYTHONAUTOMATON_H
#define JYTHONAUTOMATON_H

#include "abstractautomaton.h"
#include "PythonQt_QtAll.h"
#include "PythonQt.h"

class PythonQtObjectPtr;
class JythonAutomaton : public AbstractAutomaton
{
 Q_OBJECT
public:
 //explicit JythonAutomaton(QObject *parent = 0);
 /*public*/ JythonAutomaton(QString file, QObject *parent = 0);

signals:

public slots:
 void On_stdErr(QString);
private:
     PythonQtObjectPtr interp;
     QString filename;
     Logger * log;
     bool bHasError = false;
    QString _stdErr;
protected:
     /*protected*/ void init();
     /*protected*/ bool handle();

};

#endif // JYTHONAUTOMATON_H
