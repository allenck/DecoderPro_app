#include "externallinkcontentviewerui.h"
#include "loggerfactory.h"
#include <QUrl>
#include <QDesktopServices>
#include "file.h"

ExternalLinkContentViewerUI::ExternalLinkContentViewerUI(QObject *parent) : QObject(parent)
{

}
/**
 * A UI subclass that will open external links (website or mail links) in an
 * external browser
 * <p>
 * To use:
 * SwingHelpUtilities.setContentViewerUI("jmri.util.ExternalLinkContentViewerUI");
 *
 * @since JMRI 2.5.3 (or perhaps later, please check CVS)
 */
///*public*/ class ExternalLinkContentViewerUI extends BasicContentViewerUI {
#if 0
/*public*/ ExternalLinkContentViewerUI(JHelpContentViewer x) {
    super(x);
}

/*public*/ static ComponentUI createUI(JComponent x) {
    return new ExternalLinkContentViewerUI((JHelpContentViewer) x);
}

@Override
/*public*/ void hyperlinkUpdate(HyperlinkEvent he) {
    log.debug("event has type {}", he.getEventType());
    if (he.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
        try {
            log.debug("event has URL {}", he.getURL());
            URL u = he.getURL();
            activateURL(u);
        } catch (IOException | URISyntaxException t) {
            log.error("Error processing request", t);
        }
    }
    super.hyperlinkUpdate(he);
}
#endif
/*public*/ /*static*/ void ExternalLinkContentViewerUI::activateURL(QUrl u) //throw IOException, URISyntaxException
{
    if (u.scheme().toLower() == ("mailto") || u.scheme().toLower() == ("http")
            || u.scheme().toLower() == ("ftp")) {
        //URI uri = new URI(u.toString());
        log->debug(tr("defer protocol %1 to browser via %2").arg(u.scheme()).arg(/*uri*/u.toString()));
        //Desktop.getDesktop().browse(uri);
          QDesktopServices::openUrl(u);
    } else if (u.scheme().toLower() == ("file") && (u.fileName().endsWith("jpg")
            || u.fileName().endsWith("png")
            || u.fileName().endsWith("xml")
            || u.fileName().endsWith("gif"))) {

        // following was
        // ("file:"+System.getProperty("user.dir")+"/"+u.getFile())
        // but that duplicated the path information; JavaHelp seems to provide
        // full pathnames here.
        //URI uri = new URI(u.toString());
        log->debug(tr("defer content of %1 to browser with %2").arg(u.fileName()).arg(/*uri*/u.toString()));
        //Desktop.getDesktop().browse(uri);
          QDesktopServices::openUrl(u);
    } else if (u.scheme().toLower() == ("file")) {
        // if file not present, fall back to web browser
        // first, get file name
        QString pathName = u.fileName();
//        if (pathName.contains("%20") && SystemType.isWindows()) {
//            log.debug("Windows machine with space in path name! {}", pathName);
//            // need to have the actual space in the path name for get file to work properly
//            pathName = pathName.replace("%20", " ");
//        }
        File* file = new File(pathName);
        if (!file->exists()) {
            QUrl uri = QUrl("http://jmri.org/" + u.fileName());
            log->debug(tr("fallback to browser with %1").arg(uri.toString()));
            //Desktop.getDesktop().browse(uri);
              QDesktopServices::openUrl(uri);

        }
    }
}
/*private*/ /*final*/ /*static*/ Logger* ExternalLinkContentViewerUI::log = LoggerFactory::getLogger("ExternalLinkContentViewerUI");
