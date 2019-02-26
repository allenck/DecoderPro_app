#ifndef JYTHONSIGLETACTION_H
#define JYTHONSIGLETACTION_H

#include "abstractaction.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT JythonSigletAction : public AbstractAction
{
 Q_OBJECT
public:
 //explicit JythonSigletAction(QObject *parent = 0);
 /*public*/ JythonSigletAction(QString s, QWidget* who);

signals:

public slots:
 /*public*/ void actionPerformed();

private:
 QWidget* _who;

};

#endif // JYTHONSIGLETACTION_H
