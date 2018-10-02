#ifndef STOREDEFAULTXMLTHROTTLESLAYOUTACTION_H
#define STOREDEFAULTXMLTHROTTLESLAYOUTACTION_H
#include "abstractaction.h"

class StoreDefaultXmlThrottlesLayoutAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ StoreDefaultXmlThrottlesLayoutAction(QString s, QObject* parent);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

};

#endif // STOREDEFAULTXMLTHROTTLESLAYOUTACTION_H
