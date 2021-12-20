#ifndef LOADDEFAULTXMLTHROTTLESLAYOUTACTION_H
#define LOADDEFAULTXMLTHROTTLESLAYOUTACTION_H
#include "jmriabstractaction.h"

class LoadDefaultXmlThrottlesLayoutAction : public JmriAbstractAction
{
 Q_OBJECT
public:
 /*public*/ LoadDefaultXmlThrottlesLayoutAction(QString s, WindowInterface* wi);
 /*public*/ LoadDefaultXmlThrottlesLayoutAction(QString s, QIcon i, WindowInterface* wi);
 /*public*/ LoadDefaultXmlThrottlesLayoutAction(QString s, QObject* parent);
 /*public*/ LoadDefaultXmlThrottlesLayoutAction( QObject* parent);
  ~LoadDefaultXmlThrottlesLayoutAction() {}
  LoadDefaultXmlThrottlesLayoutAction(const LoadDefaultXmlThrottlesLayoutAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel();

public slots:
 /*public*/ void actionPerformed(/*ActionEvent e*/);

 private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ThrottleCreationAction");


};
Q_DECLARE_METATYPE(LoadDefaultXmlThrottlesLayoutAction)
#endif // LOADDEFAULTXMLTHROTTLESLAYOUTACTION_H
