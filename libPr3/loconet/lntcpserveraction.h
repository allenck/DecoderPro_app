#ifndef LNTCPSERVERACTION_H
#define LNTCPSERVERACTION_H

#include "abstractaction.h"

class LnTcpServerAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit LnTcpServerAction(QObject *parent = 0);
 /*public*/ LnTcpServerAction(QString s, QObject *parent);
 ~LnTcpServerAction() {}
 LnTcpServerAction(const LnTcpServerAction&) : AbstractAction() {}

signals:

public slots:
   /*public*/ void actionPerformed(JActionEvent* e = 0);

};
Q_DECLARE_METATYPE(LnTcpServerAction)
#endif // LNTCPSERVERACTION_H
