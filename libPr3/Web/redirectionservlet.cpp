#include "redirectionservlet.h"
#include "loggerfactory.h"
#include "properties.h"
/**
 * Redirect traffic to another location.
 *
 * @author Randall Wood (C) 2016
 */
//@WebServlet(name = "RedirectionServlet")
//public class RedirectionServlet extends HttpServlet {

/*private*/ /*static*/ /*final*/ Logger* RedirectionServlet::log = LoggerFactory::getLogger("RedirectionServlet");

/*public*/ RedirectionServlet::RedirectionServlet() {
    // do nothing
redirections = new Properties();
}

/*public*/ RedirectionServlet::RedirectionServlet(QString urlPattern, QString redirection) {
    this->redirections->setProperty(urlPattern, redirection);
}

//@Override
/*protected*/ void RedirectionServlet::doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    response->sendRedirect(redirections->getProperty(request->getContextPath()));
}

//@Override
/*protected*/ void RedirectionServlet::doPost(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    this->doGet(request, response);
}
