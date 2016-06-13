#ifndef JYTHONSIGLETACTION_H
#define JYTHONSIGLETACTION_H

#include <QAction>
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT JythonSigletAction : public QAction
{
 Q_OBJECT
public:
 //explicit JythonSigletAction(QObject *parent = 0);
 /*public*/ JythonSigletAction(QString s, QWidget* who);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 QWidget* _who;

};

#endif // JYTHONSIGLETACTION_H
