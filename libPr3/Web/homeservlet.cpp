#include "homeservlet.h"
#include "servletutil.h"
#include "fileutil.h"

HomeServlet::HomeServlet()
{

}
/**
 *
 * @author Randall Wood (C) 2014, 2016
 */
//@WebServlet(name = "HomeServlet",
//        urlPatterns = {
//            "/", // default
//            "/index.html", // redirect to default since ~ 1 FEB 2014
//            "/prefs/index.html" // some WiThrottle clients require this URL to show web services
//        })
///*public*/ class HomeServlet extends HttpServlet {

/*protected*/ void HomeServlet::processRequest(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    if (request->getRequestURI() == ("/index.html")
            || request->getRequestURI() == ("/prefs/index.html")) {
        response->sendRedirect("/");
    }
    if (request->getRequestURI()!= ("/")) {
        response->sendError(HttpServletResponse::SC_NOT_FOUND);
        return;
    }
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//    response.getWriter().print(QString.format(request->getLocale(),
//            FileUtil::readURL(FileUtil::findURL(tr(request->getLocale(), "web/servlet/home/Home.html"))),
//            ServletUtil::getInstance()->getRailroadName(false),
//            ServletUtil::getInstance()->getNavBar(request->getLocale(), "/home"),
//            ServletUtil::getInstance()->getRailroadName(false),
//            ServletUtil::getInstance()->getFooter(request->getLocale(), "/home")
//    ));
    QString out = FileUtil::readURL(FileUtil::findURL(tr(/*request->getLocale(),*/ "web/servlet/home/Home.html")));
    out = out.replace("%1$s", ServletUtil::getInstance()->getRailroadName(false));
    out = out.replace("%2$s", ServletUtil::getInstance()->getNavBar(request->getLocale(), "/home"));
    out = out.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false));
    out = out.replace("%4$s", ServletUtil::getInstance()->getFooter(request->getLocale(), "/home"));
    response->resp->write(out.toLocal8Bit(),false);
}

// <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
/**
 * Handles the HTTP <code>GET</code> method.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException      if an I/O error occurs
 */
//@Override
/*protected*/ void HomeServlet::doGet(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Handles the HTTP <code>POST</code> method.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException      if an I/O error occurs
 */
//@Override
/*protected*/ void HomeServlet::doPost(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Returns a short description of the servlet.
 *
 * @return a String containing servlet description
 */
//@Override
/*public*/ QString HomeServlet::getServletInfo() {
    return "Home Servlet";
}// </editor-fold>

