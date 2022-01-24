#ifndef MONITORLOCONETACTION_H
#define MONITORLOCONETACTION_H
#include "abstractaction.h"

class LocoNetMenuStartupAction : public AbstractAction
{
 Q_OBJECT
public:
 LocoNetMenuStartupAction(QObject *parent = 0);
 LocoNetMenuStartupAction(QString title, QObject *parent = 0);
 ~LocoNetMenuStartupAction() {}
 LocoNetMenuStartupAction(const LocoNetMenuStartupAction& that) : AbstractAction(that.parent()){}
 void setTitle(QString);

public slots:
 void actionPerformed(JActionEvent* = 0);

private:
 QString title;
};
Q_DECLARE_METATYPE(LocoNetMenuStartupAction)
#endif // MONITORLOCONETACTION_H
