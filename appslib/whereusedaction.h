#ifndef WHEREUSEDACTION_H
#define WHEREUSEDACTION_H
#include "abstractaction.h"

class JmriPanel;
class WhereUsedAction : public AbstractAction
{
 Q_OBJECT

public:
 /*public*/ WhereUsedAction(QString s, QObject* parent);
 /*public*/ WhereUsedAction(QObject* parent) ;
 /*public*/ JmriPanel* makePanel();

public slots:
 //@Override
 /*public*/ void actionPerformed(/*ActionEvent */);

};

#endif // WHEREUSEDACTION_H
