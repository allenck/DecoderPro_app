#include "jmrilocalentityresolver.h"
#include "logger.h"
#include <QUrl>
#include <QTextStream>
#include "fileutil.h"
#include "inputsource.h"
#include "file.h"

JmriLocalEntityResolver::JmriLocalEntityResolver()
{
 log = new Logger("JmriLocalEntityResolver");
}
/**
 * Entity Resolver to locate JMRI DTDs in the local space.
 * <P>
 * For historical reasons, JMRI xml files might have DTD definitions of three
 * forms:
 * <OL>
 * <LI>SYSTEM "../DTD/decoder-config.dtd"
 * <LI>SYSTEM "layout-config.dtd"
 * <LI>SYSTEM "http://jmri.sourceforce.net/xml/DTD/layout-config.dtd"
 * </OL>
 * Only the last of these is preferred now. The first two refer to local files
 * within the JMRI distributions in the xml/DTD directory.
 *
 * @author Bob Jacobsen Copyright 2007, 2009
 */
// /*public*/ class JmriLocalEntityResolver implements EntityResolver {

    //@Override
/*public*/ InputSource* JmriLocalEntityResolver::resolveEntity(QString /*public*/Id, QString systemId) throw (SAXException, IOException)
{
    log->trace(tr("-- got entity request %1").arg(systemId));

    // find local file first
    try {
        /*URI*/QUrl* uri = new QUrl(systemId);
        QTextStream* stream;
        log->trace(tr("systemId: %1").arg(systemId));
        QString scheme = systemId.mid(0,systemId.indexOf(":")); //uri.getScheme();
        QString source = uri->host();//uri.getSchemeSpecificPart();
        QString path = uri->path();

        log->trace(tr("scheme: %1").arg(scheme));
        log->trace(tr("source: %1").arg(source));
        log->trace(tr("path: %1").arg(path));

        // figure out which form we have
        if (scheme == ("http")) {
            if (systemId == ("http://www.w3.org/2001/XInclude.xsd")) {
                path = "/xml/schema/xinclude.xsd";
            }
            // type 3 - find local file if we can
            QString filename = path.mid(1);  // drop leading slash
            log->trace(tr("http finds filename: %1").arg(filename));
            stream = FileUtil::findInputStream(filename);
            if (stream != NULL) {
                return new InputSource(stream);
            } else {
                log->debug(tr("did not find local type 3 DTD file: %1").arg(filename));
                // try to find on web
                return NULL;  // tell parser to use default, which is to find on web
            }
        } else if (path != NULL && path.startsWith("../DTD")) {
            // type 1
            QString filename = "xml" + File::separator + "DTD" + File::separator + path;
            log->trace(tr("starts with ../DTD finds filename: %1").arg(filename));
            stream = FileUtil::findInputStream(filename);
            if (stream != NULL) {
                return new InputSource(stream);
            } else {
                log->error(tr("did not find type 1 DTD file: %1").arg(filename));
                return nullptr;
            }
        } else if (path != NULL && !path.contains("/")) {  // path doesn't contain "/", so is just name
            // type 2
            QString filename = "xml" + File::separator + "DTD" + File::separator + path;
            log->trace(tr("doesn't contain / finds filename: %1").arg(filename));
            stream = FileUtil::findInputStream(filename);
            if (stream != NULL) {
                return new InputSource(stream);
            } else {
                log->error(tr("did not find type 2 entity file: %1").arg(filename));
                return nullptr;
            }
        } else if (scheme == ("file")) {
            if (path != NULL) {
                // still looking for a local file, this must be absolute or full relative path
                log->trace(tr("scheme file finds path: %1").arg(path));
                // now we see if we've got a valid path
                stream = FileUtil::findInputStream(path);
                if (stream != NULL) {
                    log->trace("file exists, used");
                    return new InputSource(stream);
                } else { // file not exist
                    // now do special case for Windows, which might use "/" or "\"
                    // regardless of what File.separator says
                    QString realSeparator = File::separator;
                    // guess! first form is right one
#if 0
                    if (SystemType.isWindows()) {
                        int forIndex = path.indexOf("/");
                        int backIndex = path.indexOf("\\");
                        if (forIndex >= 0 && backIndex < 0) {
                            realSeparator = "/";
                        } else if (forIndex < 0 && backIndex >= 0) {
                            realSeparator = "\\";
                        } else if (forIndex > 0 && backIndex >= forIndex) {
                            realSeparator = "\\";
                        } else if (backIndex > 0 && forIndex >= backIndex) {
                            realSeparator = "/";
                        }
                        log->trace(" forIndex {} backIndex {}", forIndex, backIndex);
                    }
#endif
                    log->trace(tr("File::separator %1 realSeparator %2").arg(File::separator).arg(realSeparator));
                    // end special case
                    if (path.lastIndexOf(realSeparator + "DTD" + realSeparator) >= 0) {
                        log->trace("file not exist, DTD in name, insert xml directory");
                        QString modifiedPath = realSeparator + "xml"
                                + path.mid(path.lastIndexOf(realSeparator + "DTD" + realSeparator), path.length());
                        path = modifiedPath;
                    } else {
                        log->trace("file not exist, no DTD, insert xml/DTD directory");
                        QString modifiedPath = realSeparator + "xml" + realSeparator + "DTD"
                                + path.mid(path.lastIndexOf(realSeparator), path.length());
                        path = modifiedPath;
                    }
                    stream = FileUtil::findInputStream(path);
                    log->trace(tr("attempting : %1").arg(path));
                    if (stream != NULL) {
                        return new InputSource(stream);
                    } else {
                        log->error("did not find direct entity path: " + path);
                        return NULL;
                    }
                }
            } else {
                log->trace("schema file with NULL path");
                try {
                    //return new InputSource(new FileReader(new File(source)));
                 QFile* f = new QFile(source);
                 if(f->open(QIODevice::ReadOnly))
                 return new InputSource(new QTextStream(f));
                 else
                  throw  new FileNotFoundException();
                } catch (FileNotFoundException e2) {
                    log->error("did not find direct entity file: " + source);
                    return NULL;
                }
            }
        } else {
            // not recognized type, return NULL to use default
            log->error("could not parse systemId: " + systemId);
            return NULL;
        }
    }
//    catch (URISyntaxException e1) {
//        log->warn(e1.getLocalizedMessage(), e1);
//        return NULL;
//    }
    catch (NoClassDefFoundError e2) { // working on an old version of java, go with default quietly
        if (!toldYouOnce) {
            log->info("Falling back to default resolver due to JVM version");
        }
        toldYouOnce = true;
        return NULL;
    }
}

/*static*/ /*private*/ bool JmriLocalEntityResolver::toldYouOnce = false;
