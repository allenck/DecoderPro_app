#include "denialservlet.h"
#include "servletutil.h"

DenialServlet::DenialServlet() : HttpServlet()
{

}
/**
 * Servlet that simply sends an HTTP 403 FORBIDDEN error.
 *
 * Passing requests for certain resources protects those resources from network
 * access.
 *
 * @author rhwood
 */
//@WebServlet(name = "DenialServlet",
//        urlPatterns = {"/prefs/networkServices"})
///*public*/ class DenialServlet extends HttpServlet {

//@Override
/*protected*/ void DenialServlet::doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    response->setContentType(ServletUtil::UTF8_TEXT_HTML);
    response->sendError(HttpServletResponse::SC_FORBIDDEN);
}

//@Override
/*protected*/ void DenialServlet::doPost(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    this->doGet(request, response);
}
