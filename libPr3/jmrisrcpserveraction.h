#ifndef JMRISRCPSERVERACTION_H
#define JMRISRCPSERVERACTION_H
#include "abstractaction.h"

class JmriSRCPServerAction : public AbstractAction
{
 Q_OBJECT
public:
 JmriSRCPServerAction(QWidget* parent);
 /*public*/ JmriSRCPServerAction(QString s, QWidget* parent) ;

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

};

#endif // JMRISRCPSERVERACTION_H
