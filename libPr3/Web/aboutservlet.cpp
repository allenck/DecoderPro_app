#include "aboutservlet.h"
#include "connectionconfig.h"
#include "connectionconfigmanager.h"
#include "instancemanager.h"
#include "servletutil.h"
#include "profile.h"
#include "profilemanager.h"
#include "stringutil.h"
#include "fileutil.h"
#include <QApplication>
#include "version.h"

AboutServlet::AboutServlet(QObject* parent) : HttpServlet(parent)
{

}
/**
 *
 * @author Randall Wood (C) 2014, 2016
 * @author mstevetodd (C) 2017
 */
//@WebServlet(name = "AboutServlet",
//        urlPatterns = {"/about"})
//@ServiceProvider(service = HttpServlet.class)
///*public*/ class AboutServlet extends HttpServlet {

/*protected*/ void AboutServlet::processRequest(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {

    //retrieve the list of JMRI connections as a string
    QString connList;// = new StringBuilder("");
    QString comma = "";
    for (ConnectionConfig* conn : ((ConnectionConfigManager*)InstanceManager::getDefault("ConnectionConfigManager"))->getConnections()) {
        if (!conn->getDisabled()) {
            connList.append(comma).append(tr(/*request.getLocale(), */"%1: using %2 on %3").arg( conn->getConnectionName()).arg(conn->name()).arg(conn->getInfo()));
            comma = ", ";
        }
    }

    //print the html, using the replacement values listed to fill in the calculated stuff
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    response->setContentType(ServletUtil::UTF8_TEXT_HTML);
    Profile* profile = ProfileManager::getDefault()->getActiveProfile();
    QString profileName = profile != NULL ? profile->getName() : "";
#if 0
    response.getWriter().print(String.format(request.getLocale(),
            FileUtil.readURL(FileUtil.findURL(Bundle.getMessage(request.getLocale(), "About.html"))),
            Bundle.getMessage(request.getLocale(), "AboutTitle"),                                   // page title is parm 1
            InstanceManager::getDefault("ServletUtil").getNavBar(request.getLocale(), "/about"), // navbar is parm 2
            InstanceManager.getDefault(ServletUtil.class).getRailroadName(false),                   // railroad name is parm 3
            InstanceManager.getDefault(ServletUtil.class).getFooter(request.getLocale(), "/about"), // footer is parm 4
            connList,                                                                               // system connection list is parm 5
            Application.getApplicationName() + " " + jmri.Version.name(),                           // JMRI version is parm 6                                         //JMRI version is parm 6
            jmri.Version.getCopyright(),                                                            // Copyright is parm 7
            System.getProperty("java.version", "<unknown>"),                                        // Java version is parm 8
            Locale.getDefault().toString(),                                                         // locale is parm 9
            profileName                                                                             // active profile name is 10
    ));
#else
    QString out = FileUtil::readURL(FileUtil::findURL(tr(/*request.getLocale(),*/ "web/servlet/about/About.html")));
    out = out.replace("%1$s", tr(/*request.getLocale(), */"About JMRI"));                     // page title is parm 1
    out = out.replace("%2$s",ServletUtil::getInstance()->getNavBar(request->getLocale(), "/about")); // navbar is parm 2
    out = out.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false)); // railroad name is parm 3
    out = out.replace("%4$s", ServletUtil::getInstance()->getFooter( request->getLocale(),   "/about")); // footer is parm 4
    out = out.replace("%5$s", connList);                                                               // system connection list is parm 5
    out = out.replace("%6$s", QApplication::applicationDisplayName() + " " + Version::name());                           // JMRI version is parm 6                                         //JMRI version is parm 6
    out = out.replace("%7$s", Version::getCopyright());                                                            // Copyright is parm 7
    out = out.replace("%8$s", "??");//System.getProperty("java.version", "<unknown>"),                                        // Java version is parm 8
    out = out.replace("%9$s", "QLocale::toString()");                                                         // locale is parm 9
    out = out.replace("%10$s",  profileName);                                                                             // active profile name is 10
    response->resp->write(out.toLocal8Bit(), true);
#endif
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
/*protected*/ void AboutServlet::doGet(HttpServletRequest* request, HttpServletResponse* response)
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
/*protected*/ void AboutServlet::doPost(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Returns a short description of the servlet.
 *
 * @return a String containing servlet description
 */
//@Override
/*public*/ QString AboutServlet::getServletInfo() {
    return "About Servlet";
}// </editor-fold>
