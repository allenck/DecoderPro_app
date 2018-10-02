#ifndef STOREXMLTHROTTLESLAYOUTACTION_H
#define STOREXMLTHROTTLESLAYOUTACTION_H
#include "abstractaction.h"

class File;
class Logger;
class StoreXmlThrottlesLayoutAction : public AbstractAction
{
 Q_OBJECT
public:
 /*public*/ StoreXmlThrottlesLayoutAction(QString s, QObject* parent);
 /*public*/ StoreXmlThrottlesLayoutAction(QObject* parent);
 /*public*/ void saveThrottlesLayout(File* f);

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("StoreXmlThrottlesLayoutAction");
};

#endif // STOREXMLTHROTTLESLAYOUTACTION_H
