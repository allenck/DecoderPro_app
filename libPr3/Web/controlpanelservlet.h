#ifndef CONTROLPANELSERVLET_H
#define CONTROLPANELSERVLET_H
#include "abstractpanelservlet.h"

class Logger;
class ControlPanelServlet : public AbstractPanelServlet
{
 Q_OBJECT
public:
 ControlPanelServlet();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ControlPanelServlet");

protected:
 /*protected*/  QString getPanelType();
 /*protected*/  QString getXmlPanel(QString name);
 /*protected*/  QString getJsonPanel(QString name);


};

#endif // CONTROLPANELSERVLET_H
