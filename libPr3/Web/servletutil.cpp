#include "servletutil.h"
#include "instancemanager.h"
#include "webserverpreferences.h"
#include "fileutil.h"
#include "stringutil.h"

ServletUtil::ServletUtil(QObject *parent) : QObject(parent)
{

}
/**
 * Utility methods to reduce code duplication in servlets.
 *
 * @author Randall Wood
 */
///*public*/ class ServletUtil {

/*public*/ /*static*/ /*final*/ QString ServletUtil::UTF8 = "UTF-8"; // NOI18N
// media types
/*public*/ /*static*/ /*final*/ QString ServletUtil::APPLICATION_JSON = "application/json"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ServletUtil::APPLICATION_XML = "application/xml"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ServletUtil::IMAGE_PNG = "image/png"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ServletUtil::TEXT_HTML = "text/html"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ServletUtil::UTF8_APPLICATION_JSON = APPLICATION_JSON + "; charset=utf-8"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ServletUtil::UTF8_APPLICATION_XML = APPLICATION_XML + "; charset=utf-8"; // NOI18N
/*public*/ /*static*/ /*final*/ QString ServletUtil::UTF8_TEXT_HTML = ServletUtil::TEXT_HTML + "; charset=utf-8"; // NOI18N

/**
 * Get the railroad name for HTML documents.
 *
 * @param inComments Return the railroad name prepended and appended by
 *                   closing and opening comment markers
 * @return the Railroad name, possibly with formatting
 */
/*public*/ QString ServletUtil::getRailroadName(bool inComments) {
    if (inComments) {
        return "-->" + WebServerPreferences::getDefault()->getRailRoadName() + "<!--"; // NOI18N
    }
    return WebServerPreferences::getDefault()->getRailRoadName();
}

/**
 * Create a common footer.
 *
 * @param locale  If a template is not available in locale, will return US
 *                English.
 * @param context divs included in footer template with class
 *                {@code context-<context>-only} will be shown.
 * @return an HTML footer
 * @throws IOException if template cannot be located
 */
/*public*/ QString ServletUtil::getFooter(QLocale locale, QString context) throw (IOException) {
    // Should return a built NavBar with li class for current context set to "active"
    QString footer = StringUtil::stringFormat(locale,
            QString("-->") + FileUtil::readURL(FileUtil::findURL(StringUtil::stringFormat(locale, "web/servlet/Footer.html"))) + "<!--").arg( // NOI18N
            this->getRailroadName(true));
    QString clazz = "context" + context.replace("/", "-"); // NOI18N
    // replace class "context-<this-context>-only" with class "show"
    footer = footer.replace(clazz + "-only", "show"); // NOI18N
    // replace class "context-<some-other-context>-only" with class "hidden"
    footer = footer.replace("context-[\\w-]*-only", "hidden"); // NOI18N
    // replace class "context-<this-context>" with class "active"
    footer = footer.replace(clazz, "active"); // NOI18N
    return footer;
}

/**
 * Create a common navigation header.
 *
 * @param locale  If a template is not available in locale, will return US
 *                English.
 * @param context divs included in navigation bar template with class
 *                {@code context-<context>-only} will be shown.
 * @return an HTML navigation bar
 * @throws IOException if template cannot be located
 */
/*public*/ QString ServletUtil::getNavBar(QLocale /*locale*/, QString context) throw (IOException)
{
    // Should return a built NavBar with li class for current context set to "active"
//    QString navBar = StringUtil::stringFormat(locale,
//            "-->" + FileUtil::readURL(FileUtil::findURL(StringUtil::stringFormat(locale, "web/servlet/NavBar.html"))) + "<!--").arg( // NOI18N
//            this->getRailroadName(true));
 QString navBar = "-->" + FileUtil::readURL(FileUtil::findURL("web/servlet/NavBar.html")) + "<!--";
 navBar = navBar.replace("%1$s", this->getRailroadName(true) );
    QString clazz = "context" + context.replace("/", "-"); // NOI18N
    // replace class "context-<this-context>-only" with class "show"
    navBar = navBar.replace(clazz + "-only", "show"); // NOI18N
    // replace class "context-<some-other-context>-only" with class "hidden"
    navBar = navBar.replace("context-[\\w-]*-only", "hidden"); // NOI18N
    // replace class "context-<this-context>" with class "active"
    navBar = navBar.replace(clazz, "active"); // NOI18N
    if (WebServerPreferences::getDefault()->allowRemoteConfig()) {
        navBar = navBar.replace("config-enabled-only", "show"); // NOI18N
        navBar = navBar.replace("config-disabled-only", "hidden"); // NOI18N
    } else {
        navBar = navBar.replace("config-enabled-only", "hidden"); // NOI18N
        navBar = navBar.replace("config-disabled-only", "show"); // NOI18N
    }
    if (!WebServerPreferences::getDefault()->isReadonlyPower()) {
        navBar = navBar.replace("data-power=\"readonly\"", "data-power=\"readwrite\""); // NOI18N
    }
    return navBar;
}

/*public*/ /*static*/ ServletUtil* ServletUtil::getInstance() {
    ServletUtil* instance = (ServletUtil*)InstanceManager::getNullableDefault("ServletUtil");
    if (instance == NULL) {
        instance = new ServletUtil();
        InstanceManager::setDefault("ServletUtil", instance);
    }
    return instance;
}

/**
 * Set HTTP headers to prevent caching.
 *
 * @param response the response to set headers in
 */
/*public*/ void ServletUtil::setNonCachingHeaders(HttpServletResponse* response) {
    QDateTime now = QDateTime();
    response->setDateHeader("Date", now.currentMSecsSinceEpoch()); // NOI18N
    response->setDateHeader("Last-Modified", now.currentMSecsSinceEpoch()); // NOI18N
    response->setDateHeader("Expires", now.currentMSecsSinceEpoch()); // NOI18N
    response->setHeader("Cache-control", "no-cache, no-store"); // NOI18N
    response->setHeader("Pragma", "no-cache"); // NOI18N
}

/**
 * Write a file to the given response->
 *
 * @param response    the response to write the file into
 * @param file        file to write
 * @param contentType file mime content type
 * @throws java.io.IOException if communications lost with client
 */
/*public*/ void ServletUtil::writeFile(HttpServletResponse* response, File* file, QString contentType) throw (IOException)
{
 if (file->exists())
 {
  if (file->canRead())
  {
#if 1
   response->setContentType(contentType);
   response->setStatus(HttpServletResponse::SC_OK);
//   response->setContentLength((int) file->length());
#endif
//            try (FileInputStream fileInputStream = new FileInputStream(file))
//            {
//                int bytes = fileInputStream.read();
//                while (bytes != -1) {
//                    response->getOutputStream().write(bytes);
//                    bytes = fileInputStream.read();
//                }
//            }
   QFile f(file->getPath());
   if(f.open(QIODevice::ReadOnly))
   {
#if 1
    while (!f.atEnd() && !f.error())
    {
        QByteArray buffer=f.read(65536);
        response->resp->write(buffer, buffer.size() != 65536);
    }
    return;
#endif
   }
   else
    throw (IOException());
  }
  else {
      response->sendError(HttpServletResponse::SC_FORBIDDEN);
  }
 }
 else {
  response->sendError(HttpServletResponse::SC_NOT_FOUND);
 }
}

/**
 * Return the complete title for an HTML document given the portion of the
 * title specific to the document.
 *
 * @param locale The requested Locale
 * @param title  Portion of title specific to page
 * @return The complete title
 */
/*public*/ QString ServletUtil::getTitle(QLocale locale, QString title) {
    return StringUtil::stringFormat(locale, "%2$s | %1$s").arg(this->getRailroadName(false)).arg(title);
}
