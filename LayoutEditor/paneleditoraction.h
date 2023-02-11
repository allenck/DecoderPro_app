#ifndef PANELEDITORACTION_H
#define PANELEDITORACTION_H

#include "abstractaction.h"
#include "actionevent.h"


class PanelEditorAction : public AbstractAction
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit PanelEditorAction(QObject *parent = nullptr);
 /*public*/ PanelEditorAction(QString s, QObject *parent);
  ~PanelEditorAction() {}
  PanelEditorAction(const PanelEditorAction&) : AbstractAction(){}

signals:

public slots:
 /*public*/ void actionPerformed(JActionEvent* e = nullptr);
private:
 void common();
};
Q_DECLARE_METATYPE(PanelEditorAction)
#endif // PANELEDITORACTION_H
