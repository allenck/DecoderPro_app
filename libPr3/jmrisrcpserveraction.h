#ifndef JMRISRCPSERVERACTION_H
#define JMRISRCPSERVERACTION_H
#include "abstractaction.h"

class JmriSRCPServerAction : public AbstractAction
{
 Q_OBJECT
public:
 JmriSRCPServerAction() {}
 Q_INVOKABLE JmriSRCPServerAction(QWidget* parent);
 Q_INVOKABLE /*public*/ JmriSRCPServerAction(QString s, QWidget* parent) ;
 ~JmriSRCPServerAction() {}
 JmriSRCPServerAction(const JmriSRCPServerAction&) : AbstractAction() {}

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

};
Q_DECLARE_METATYPE(JmriSRCPServerAction)
#endif // JMRISRCPSERVERACTION_H
