#ifndef PANELEDITORACTION_H
#define PANELEDITORACTION_H

#include <QAction>
#include "actionevent.h"


class PanelEditorAction : public QAction
{
 Q_OBJECT
public:
 explicit PanelEditorAction(QObject *parent);
 /*public*/ PanelEditorAction(QString s, QObject *parent);


signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = nullptr);
private:
 void common();
};

#endif // PANELEDITORACTION_H
