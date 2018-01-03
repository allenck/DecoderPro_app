#ifndef WEBSERVERACTION_H
#define WEBSERVERACTION_H
#include "jmriabstractaction.h"

class ServerThread;
class Logger;
class WebServerAction : public JmriAbstractAction
{
public:
 Q_INVOKABLE /*public*/ WebServerAction(QObject* parent = 0);
 /*public*/ WebServerAction(QString s, WindowInterface* wi);
 /*public*/ WebServerAction(QString s, QIcon i, WindowInterface* wi);
 ~WebServerAction() {}
 WebServerAction(const WebServerAction&) : JmriAbstractAction() {}
 /*public*/ JmriPanel* makePanel(); // not used by this classes actionPerformed, as it doesn't show anything

public slots:
 /*public*/ void actionPerformed(ActionEvent* ev = 0);

private:
 void common();
 ///*private*/ static ServerThread* serverThread;// = null;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(WebServerAction.class);

};
Q_DECLARE_METATYPE(WebServerAction)
#endif // WEBSERVERACTION_H
