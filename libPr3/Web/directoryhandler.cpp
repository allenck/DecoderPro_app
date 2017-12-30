#include "directoryhandler.h"
#include "servletutil.h"
#include "directoryresource.h"
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class DirectoryHandler  : public QObject//extends ResourceHandler {

/**
 * Construct a DirectoryHandler for the named directory with common
 * default settings.
 *
 * This constructor sets directory listings to true and returns the contents
 * of index.html within the directory instead of listing the contents of the
 * directory if index.html exists.
 *
 * @param resourceBase the directory to serve
 */
/*public*/ DirectoryHandler::DirectoryHandler(QString resourceBase, ResourceHandler* /*parentHandler*/, QObject *parent) : ResourceHandler(parent)
{
    //this();
 this->setDirectoriesListed(true);
 QStringList lst = QStringList();
 lst << "index.html";
 this->setWelcomeFiles(lst); // NOI18N
 this->setResourceBase(resourceBase);
}

/**
 * Default handler constructor.
 */
/*public*/ DirectoryHandler::DirectoryHandler(QObject *parent) : ResourceHandler(parent){
    //super();
    this->setDirectoriesListed(true);
 QStringList lst = QStringList();
 lst << "index.html";
 this->setWelcomeFiles(lst); // NOI18N
}

//@Override
/*protected*/ void DirectoryHandler::doDirectory(HttpServletRequest* request, HttpServletResponse* response, Resource* resource) throw (IOException) {
    if (this->isDirectoriesListed()) {
        response->setStatus(HttpServletResponse::SC_OK);
        response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//        response.getWriter().print((new DirectoryHandler(request->getLocale(), resource))->getListHTML(request->getRequestURI(), request->getPathInfo().lastIndexOf("/") > 0)); // NOI18N
        response->resp->write((new DirectoryResource(request->getLocale(), resource))->getListHTML(request->getRequestURI(), request->getPathInfo().lastIndexOf("/") > 0).toLocal8Bit(), true);
    } else {
        response->sendError(HttpServletResponse::SC_FORBIDDEN);
    }
}
