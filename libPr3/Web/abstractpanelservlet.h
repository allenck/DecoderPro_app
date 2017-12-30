#ifndef ABSTRACTPANELSERVLET_H
#define ABSTRACTPANELSERVLET_H
#include "httpservlet.h"
#include <QtXml>

class Editor;
class ObjectMapper;
class Logger;
class AbstractPanelServlet : public HttpServlet
{
public:
 AbstractPanelServlet();
 /*public*/ void init() throw (ServletException);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("AbstractPanelServlet");
 QDomElement getSignalMastIconsElement(QString name);

protected:
 /*protected*/  ObjectMapper* mapper;
 /*abstract*/ virtual /*protected*/  QString getPanelType();
 /*protected*/  void doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/  void listPanels(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/  QByteArray getPanelImage(QString name);
 /*protected*/  QWidget* getPanel(QString name);
 /*protected*/  QString getPanelText(QString name, bool useXML);
 /*abstract*/ virtual /*protected*/  QString getJsonPanel(QString name);
 /*abstract*/ virtual /*protected*/  QString getXmlPanel(QString name);
 /*protected*/  Editor* getEditor(QString name);
 /*protected*/  void parsePortableURIs(QDomElement element);
friend class PanelServlet;
friend class RequestHandler;
friend class ControlPanelServlet;
friend class LayoutPanelServlet;
};

#endif // ABSTRACTPANELSERVLET_H
