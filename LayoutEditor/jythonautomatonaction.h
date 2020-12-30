#ifndef JYTHONAUTOMATONACTION_H
#define JYTHONAUTOMATONACTION_H

#include <QAction>
#include "liblayouteditor_global.h"
#include "actionevent.h"

class LIBLAYOUTEDITORSHARED_EXPORT JythonAutomatonAction : public QAction
{
 Q_OBJECT
public:
 //explicit JythonAutomatonAction(QObject *parent = 0);
 /*public*/ JythonAutomatonAction(QString s, QWidget* who);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent*  /*e*/ = 0);

private:
 QWidget* _who;

};

#endif // JYTHONAUTOMATONACTION_H
