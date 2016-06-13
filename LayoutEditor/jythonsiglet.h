#ifndef JYTHONSIGLET_H
#define JYTHONSIGLET_H

#include "siglet.h"
//#include "PythonQt_QtAll.h"
#include "PythonQt.h"
#include "liblayouteditor_global.h"

class PythonQtObjectPtr;
class LIBLAYOUTEDITORSHARED_EXPORT JythonSiglet : public Siglet
{
 Q_OBJECT
public:
 //explicit JythonSiglet(QObject *parent = 0);
 /*public*/ JythonSiglet(QString file, QObject *parent = 0);
 /*public*/ void defineIO();
 /*public*/ void setOutput();

signals:

public slots:
private:
 PythonQtObjectPtr interp;
 QString filename;
 Logger * log;
};

#endif // JYTHONSIGLET_H
