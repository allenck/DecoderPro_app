#ifndef CONTROLPANELEDITORACTION_H
#define CONTROLPANELEDITORACTION_H

#include <QAction>

class ControlPanelEditorAction : public QAction
{
 Q_OBJECT
public:
 explicit ControlPanelEditorAction(QObject *parent = 0);
 /*public*/ ControlPanelEditorAction(QString s, QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
 void common();
};

#endif // CONTROLPANELEDITORACTION_H
