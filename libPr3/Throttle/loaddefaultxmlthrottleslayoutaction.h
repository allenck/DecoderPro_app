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
 Q_INVOKABLE/*public*/ LoadDefaultXmlThrottlesLayoutAction( QObject* parent =0);
  ~LoadDefaultXmlThrottlesLayoutAction() {}
  LoadDefaultXmlThrottlesLayoutAction(const LoadDefaultXmlThrottlesLayoutAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel()override;

public slots:
 /*public*/ void actionPerformed(JActionEvent* =0)override;

 private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ThrottleCreationAction");


};
Q_DECLARE_METATYPE(LoadDefaultXmlThrottlesLayoutAction)
#endif // LOADDEFAULTXMLTHROTTLESLAYOUTACTION_H
