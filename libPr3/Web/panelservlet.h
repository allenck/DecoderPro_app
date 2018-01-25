#ifndef PANELSERVLET_H
#define PANELSERVLET_H
#include "abstractpanelservlet.h"

class PanelServlet : public AbstractPanelServlet
{
 Q_OBJECT
public:
 PanelServlet();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(PanelServlet.class);

protected:
 /*protected*/  QString getPanelType();
 /*protected*/  QByteArray getXmlPanel(QString name);
 /*protected*/  QString getJsonPanel(QString name);

};

#endif // PANELSERVLET_H
