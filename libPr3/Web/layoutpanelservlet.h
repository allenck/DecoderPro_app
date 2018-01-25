#ifndef LAYOUTPANELSERVLET_H
#define LAYOUTPANELSERVLET_H
#include "abstractpanelservlet.h"

class Logger;
class LayoutPanelServlet : public AbstractPanelServlet
{
public:
 LayoutPanelServlet();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("LayoutPanelServlet");

protected:
 /*protected*/  QString getPanelType();
 /*protected*/  QString getJsonPanel(QString name);
 /*protected*/  QByteArray getXmlPanel(QString name);

};

#endif // LAYOUTPANELSERVLET_H
