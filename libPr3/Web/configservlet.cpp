#include "configservlet.h"
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "webserverpreferences.h"

ConfigServlet::ConfigServlet()
{

}
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class ConfigServlet extends HttpServlet {

/**
 * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
 * methods.
 *
 * Always returns a 501 Not Implemented response. This is currently a
 * placeholder for a future capability to move (most) preferences controls
 * into a web service, so that headless systems can be configured without
 * having to copy a configuration from another system.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException      if an I/O error occurs
 */
/*protected*/ void ConfigServlet::processRequest(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    if (!WebServerPreferences::getDefault()->allowRemoteConfig())
    {
        response->sendError(HttpServletResponse::SC_FORBIDDEN);
        return;
    }
    response->sendError(HttpServletResponse::SC_NOT_IMPLEMENTED, tr("Remote configuration of JMRI is not yet implemented.")); // NOI18N
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
/*protected*/ void ConfigServlet::doGet(HttpServletRequest* request, HttpServletResponse* response)
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
/*protected*/ void ConfigServlet::doPost(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Returns a short description of the servlet.
 *
 * @return a String containing servlet description
 */
//@Override
/*public*/ QString ConfigServlet::getServletInfo() {
    return "Short description";
}// </editor-fold>
