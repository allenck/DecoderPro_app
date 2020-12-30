#ifndef CONTROLPANELEDITORACTION_H
#define CONTROLPANELEDITORACTION_H

#include <QAction>
#include "actionevent.h"

class ControlPanelEditorAction : public QAction
{
 Q_OBJECT
public:
 explicit ControlPanelEditorAction(QObject *parent = 0);
 /*public*/ ControlPanelEditorAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = 0);
private:
 void common();
};

#endif // CONTROLPANELEDITORACTION_H
