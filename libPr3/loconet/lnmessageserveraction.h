#ifndef LNMESSAGESERVERACTION_H
#define LNMESSAGESERVERACTION_H
#include "abstractaction.h"

class Logger;
class LnMessageServerAction : public AbstractAction
{
public:
 LnMessageServerAction();
 Q_INVOKABLE LnMessageServerAction(QWidget* parent);
 Q_INVOKABLE /*public*/ LnMessageServerAction(QString s, QWidget* parent);
 ~LnMessageServerAction() {}
 LnMessageServerAction(const LnMessageServerAction&) : AbstractAction() {}

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
 static Logger* log;

};
Q_DECLARE_METATYPE(LnMessageServerAction)
#endif // LNMESSAGESERVERACTION_H
