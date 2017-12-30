#ifndef JMRIJFRAMESERVLET_H
#define JMRIJFRAMESERVLET_H
#include "httpservlet.h"
#include "jmrijframe.h"
#include <QTestEventList>

class MyGraphicsItemGroup;
class QGraphicsItem;
class Logger;
class JmriJFrameServlet : public HttpServlet
{
 Q_OBJECT
public:
 JmriJFrameServlet();
 /*public*/ void clickOnEditorPane(QWidget* c, int x, int y, JmriJFrame* f);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("JmriJFrameServlet");
 void sendClick(QString name, QWidget* c, int xg, int yg, QWidget* FrameContentPane);  // global positions
 /*private*/ void doHtml(JmriJFrame* frame, HttpServletRequest* request, HttpServletResponse* response, QMap<QString, QStringList*>* parameters) throw (ServletException, IOException);
 /*private*/ QString getFrameName(QString URI);
 /*private*/ void doClick(JmriJFrame* frame, QString coords);
 /*private*/ void doImage(JmriJFrame* frame, HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*private*/ void doList(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*private*/ bool isAssignable(QString type, QWidget* c);
/*private*/ MyGraphicsItemGroup* findGroup(QGraphicsItem* item);

protected:
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/ QMap<QString, QStringList*>* populateParameterMap(/*@NonNULL*/ QMap<QString, QStringList*>* map);
 friend class RequestHandler;
};

#endif // JMRIJFRAMESERVLET_H
