#include "vsdfile.h"
#include "quazipfileinfo.h"
#include "quazip.h"
#include "quazipdir.h"
#include "quazipfile.h"
#include "xmlfile.h"
#include <QTextStream>
#include "file.h"

VSDFile::VSDFile(QObject *parent) :
  ZipFile(parent)
{
}
 /*private*/ /*static*/ /*final*/ QString VSDFile::VSDXmlFileName = "config.xml"; // NOI18N
#if 0
///*public*/ class VSDFile extends ZipFile {



    // Dummy class just used to instantiate
    private static class VSDXmlFile extends XmlFile {
    }

    static final ResourceBundle rb = VSDecoderBundle.bundle();



    ZipInputStream zis;
#endif
/*public*/ VSDFile::VSDFile(File* file, QObject *parent) :
ZipFile(file,parent) //throws ZipException, IOException
{
    //super(file);
common();
    initialized = init();
}

/*public*/ VSDFile::VSDFile(File* file, int mode, QObject *parent) :
ZipFile(file, mode, parent) //throws ZipException, IOException
{
    //super(file, mode);
common();
    initialized = init();
}

/*public*/ VSDFile::VSDFile(QString name, QObject *parent) :
ZipFile(name, parent) //throws ZipException, IOException
{
    //super(name);
common();
    initialized = init();
}

/*public*/ bool VSDFile::isInitialized() {
    return (initialized);
}

void VSDFile::common()
{
 initialized = false;
 log = new Logger("VSDFile");
 _statusMsg = tr("OK");
}

/*public*/ QString VSDFile::getStatusMessage() {
    return (_statusMsg);
}

/*protected*/ bool VSDFile::init()
{
    VSDXmlFile* xmlfile = new VSDXmlFile();
    initialized = false;
#if 0
    //try {
        // Debug: List all the top-level contents in the file.
        Enumeration<?> entries = this.entries();
        while (entries.hasMoreElements()) {
            ZipEntry z = (ZipEntry) entries.nextElement();
            log->debug("Entry: " + z.getName());
        }
#endif
        QuaZipDir dir = QuaZipDir(zipper);
        QStringList entryList = dir.entryList();
        foreach (QString name, entryList) {
         //ZipEntry z = (ZipEntry) entries.nextElement();
         log->debug("Entry: " + name);

        }
#if 0
        ZipEntry config = this.getEntry(VSDXmlFileName);
        if (config == NULL) {
            _statusMsg = "File does not contain " + VSDXmlFileName;
            log->error(_statusMsg);
            return (false);
        }
#endif
        if(!dir.exists(VSDXmlFileName))
        {
         _statusMsg = "File does not contain " + VSDXmlFileName;
         log->error(_statusMsg);
         return (false);

        }
        //File f2 = new File(this.getURL(VSDXmlFileName));
        zipper->setCurrentFile(VSDXmlFileName);
        QuaZipFile file(zipper);
        //root = xmlfile.rootFromFile(f2);
        if(!file.open(QIODevice::ReadOnly))
        {
         log->error("error reading: " + VSDXmlFileName);
        }
        QDataStream* stream = new QDataStream(&file);
        root = xmlfile->rootFromInputStream(stream);
#if 1
        ValidateStatus* rv = this->validate(root);
        if (!rv->getValid()) {
            // Need to make this one fancier right here.
            _statusMsg = rv->getMessage();
            log->error("VALIDATE FAILED: File " + VSDXmlFileName);
        }
        initialized = rv->getValid();
#endif
        return (initialized);

//    } catch (java.io.IOException ioe) {
//        _statusMsg = "IO Error auto-loading VSD File: " + VSDXmlFileName + " " + ioe.toString();
//        log->warn(_statusMsg);
//        return (false);
//    } catch (NullPointerException npe) {
//        _statusMsg = "NP Error auto-loading VSD File: path = " + VSDXmlFileName + " " + npe.toString();
//        log->warn(_statusMsg);
//        return (false);
//    } catch (org.jdom2.JDOMException ex) {
//        _statusMsg = "JDOM Exception loading VSDecoder from path " + VSDXmlFileName + " " + ex.toString();
//        log->error(_statusMsg);
//        return (false);
//    }
}

/*public*/ QDomElement VSDFile::getRoot() {
    return (root);
}

/*public*/ QDataStream* VSDFile::getInputStream(QString name) {

//        QDataStream* rv;
//        try {
//            ZipEntry e = this.getEntry(name);
//            if (e == NULL) {
//                e = this.getEntry(name.toLowerCase());
//                if (e == NULL) {
//                    e = this.getEntry(name.toUpperCase());
//                    if (e == NULL) {
//                        // I give up.  Return NULL.
//                        return (NULL);
//                    }
//                }
//            }
//            rv = getInputStream(this.getEntry(name));
//        } catch (IOException e) {
//            log->error("IOException caught " + e);
//            rv = NULL;
//        } catch (NullPointerException ne) {
//            log->error("Null Pointer Exception caught. name=" + name, ne);
//            rv = NULL;
//        }
 if(!zipper->isOpen())
 {
  zipper->open((QuaZip::Mode)mode);
 }
 zipper->setCurrentFile(name);
 file = new QuaZipFile(zipper);
 //root = xmlfile.rootFromFile(f2);
 if(!file->open(QIODevice::ReadOnly))
 {
  log->error("error reading: " + name);
 }
 rv = new QDataStream(file);
 return (rv);
}

/*public*/ File* VSDFile::getFile(QString name)
{
    //try {
#if 1
 // TODO:
            //ZipEntry e = this.getEntry(name);
 zipper->setCurrentFile(name);
 QuaZipFile e(zipper);

 File* f = new File(e.getFileName());
 return (f);
//        } catch (NullPointerException e) {
//            return (NULL);
#else
 return NULL;
#endif
    }
#if 0
    /*public*/ String getURL(String name) {
        try {
            // Grab the entry from the Zip file, and create a tempfile to dump it into
            ZipEntry e = this.getEntry(name);
            File t = File.createTempFile(name, ".wav.tmp");
            t.deleteOnExit();

            // Dump the file from the Zip into the tempfile.
            copyInputStream(this.getInputStream(e), new BufferedOutputStream(new FileOutputStream(t)));

            // return the name of the tempfile.
            return (t.getPath());

        } catch (NullPointerException e) {
            log->warn("Null pointer exception", e);
            return (NULL);
        } catch (IOException e) {
            log->warn("IO exception", e);
            return (NULL);
        }
    }

    private static final void copyInputStream(InputStream in, OutputStream out)
            throws IOException {
        byte[] buffer = new byte[1024];
        int len;

        while ((len = in.read(buffer)) >= 0) {
            out.write(buffer, 0, len);
        }

        in.close();
        out.close();
    }
#endif
    //static class ValidateStatus {

//        QString msg = "";
//        bool valid = false;

        /*public*/ ValidateStatus::ValidateStatus() {
            //this(false, "");
 msg = "";
 valid = false;
        }

        /*public*/ ValidateStatus::ValidateStatus(bool v, QString m) {
            valid = v;
            msg = m;
        }

        /*public*/ void ValidateStatus::setValid(bool v) {
            valid = v;
        }

        /*public*/ void ValidateStatus::setMessage(QString m) {
            msg = m;
        }

        /*public*/ bool ValidateStatus::getValid() {
            return (valid);
        }

        /*public*/ QString ValidateStatus::getMessage() {
            return (msg);
        }
    //};

    /*public*/ ValidateStatus* VSDFile::validate(QDomElement xmlroot) {
        QDomElement e, el;
        // Iterate through all the profiles in the file.
        // Would like to get rid of this suppression, but I think it's fairly safe to assume a list of children
        // returned from an Element is going to be a list of Elements.
        //Iterator<Element> i = xmlroot.getChildren("profile").iterator();
        QDomNodeList nl = xmlroot.elementsByTagName("profile");
        // If no Profiles, file is invalid.
        //if (!i.hasNext()) {
        if(nl.count() == 0)
        {

            log->warn("Validate: No Profiles.");
            return (new ValidateStatus(false, tr("VSD File contains no Profiles")));
        }

        // Iterate through Profiles
        //while (i.hasNext()) {
        for(int i = 0; i < nl.count(); i++)
        {
            e = nl.at(i).toElement(); // e points to a profile.
            log->debug("Validate: Profile " + e.attribute("name"));
            // Get the "Sound" children ... these are the ones that should have files
            // Would like to get rid of this suppression, but I think it's fairly safe to assume a list of children
            // returned from an Element is going to be a list of Elements.
            //Iterator<Element> i2 = (e.getChildren("sound")).iterator();
            QDomNodeList nl2 = e.elementsByTagName("sound");
            if (nl2.count() == 0) {
                log->warn("Validate: Profile " + e.attribute("name") + " has no Sounds");
                return (new ValidateStatus(false, tr("VSDFileStatusNoSounds") + " : " + e.attribute("name")));
            }

            // Iterate through Sounds
            //while (i2.hasNext()) {
            for(int i = 0; i < nl2.count(); i++)
            {
                el = nl2.at(i).toElement(); // e points to a sound.    el = i2.next();
                log->debug("Element: " + el.tagName());
                if (el.attribute("name") == "") {
                    log->debug("Name missing.");
                    return (new ValidateStatus(false, tr("VSDFileStatusNoName") + " : " + e.attribute("name") + "(" + el.tagName() + ")"));
                }
                QString type = el.attribute("type");
                log->debug("  Name: " + el.attribute("name"));
                log->debug("   type: " + type);
                if (type==("configurable")) {
                    // Validate a Configurable Sound
                    // All these elements are optional, so if the element is missing,
                    // that's OK.  But if there is an element, and the FILE is missing,
                    // that's bad.
                    if (!validateOptionalFile(el, "start-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <start-file>"));
                    }
                    if (!validateOptionalFile(el, "mid-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <mid-file>"));
                    }
                    if (!validateOptionalFile(el, "end-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <end-file>"));
                    }
                    if (!validateOptionalFile(el, "short-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <short-file>"));
                    }
                } else if (type==("diesel")) {
                    // Validate a Diesel sound
                    // All these elements are optional, so if the element is missing,
                    // that's OK.  But if there is an element, and the FILE is missing,
                    // that's bad.
                    QStringList file_elements = QStringList() << "file";
                    if (!validateOptionalFile(el, "start-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <start-file>"));
                    }
                    if (!validateOptionalFile(el, "shutdown-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <shutdown-file>"));
                    }
                    if (!validateFiles(el, "notch-sound", file_elements)) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <notch-sound>"));
                    }
                    if (!validateFiles(el, "notch-transition", file_elements, false)) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <notch-transition>"));
                    }
                } else if (type==("diesel2")) {
                    // Validate a diesel2 type sound
                    // Validate a Diesel sound
                    // All these elements are optional, so if the element is missing,
                    // that's OK.  But if there is an element, and the FILE is missing,
                    // that's bad.
                    QStringList file_elements = QStringList() << "file" << "accel-file" << "decel-file";
                    if (!validateOptionalFile(el, "start-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <start-file>"));
                    }
                    if (!validateOptionalFile(el, "shutdown-file")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <shutdown-file>"));
                    }
                    if (!validateFiles(el, "notch-sound", file_elements)) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <notch-sound>"));
                    }
                } else if (type==("steam")) {
                    // Validate a Steam sound
                    QStringList file_elements = QStringList() << "file";
                    if (!validateRequiredElement(el, "top-speed")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <top-speed>"));
                    }
                    if (!validateRequiredElement(el, "driver-diameter")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <driver-diameter>"));
                    }
                    if (!validateRequiredElement(el, "cylinders")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <cylinders>"));
                    }
                    if (!validateRequiredElement(el, "rpm-steps")) {
                        return (new ValidateStatus(false, tr("Sound Element is missing required element") + " : <rpm-steps>"));
                    }
                    if (!validateFiles(el, "rpm-step", file_elements)) {
                        return (new ValidateStatus(false, tr("Sound Element is missing an audio file.") + " : <notch-sound>"));
                    }
                }
            }
        }
        log->debug("File Validation Successful.");
        return (new ValidateStatus(true, tr("VSDFileStatusOK")));
    }

    /*protected*/ bool VSDFile::validateRequiredElement(QDomElement el, QString name) {
 if (el.firstChildElement(name) == QDomElement()) {
            log->debug("Element " + name + " for Element " + el.attribute("name") + " missing.");
            return (false);
        }
        return (true);
    }

    /*protected*/ bool VSDFile::validateOptionalFile(QDomElement el, QString name) {
        return (validateOptionalFile(el, name, true));
    }

    /*protected*/ bool VSDFile::validateOptionalFile(QDomElement el, QString name, bool required) {
        QString s = el.firstChildElement(name).text(); //getChildText
        if ((s != "") && (getFile(s) == NULL)) {
            log->debug("File " + s + " for element " + name + " in Element " + el.attribute("name") + " not found.");
            return (false);
        }
        return (true);
    }

    /*protected*/ bool VSDFile::validateFiles(QDomElement el, QString name, QStringList fnames) {
        return (validateFiles(el, name, fnames, true));
    }

    /*protected*/ bool VSDFile::validateFiles(QDomElement el, QString name, QStringList fnames, bool required) {
        QDomNodeList elist = el.elementsByTagName(name);
        QString s;

        // First, check to see if any elements of this <name> exist.
        if ((elist.size() == 0) && (required)) {
            // Only fail if this type of element is required.
            log->debug("No elements of name " + name);
            return (false);
        }

        // Now, if the elements exist, make sure the files they point to exist.
        // Would like to get rid of this suppression, but I think it's fairly safe to assume a list of children
        // returned from an Element is going to be a list of Elements.
        //Iterator<Element> ns_i = elist.iterator();
        //while (ns_i.hasNext()) {
        for(int i = 0; i < elist.count(); i++)
        {
            QDomElement ns_e = elist.at(i).toElement(); //ns_i.next();
            foreach (QString fn, fnames) {
                s = ns_e.firstChildElement(fn).text(); //getChildText
                if ((s == NULL) || (getFile(s) == NULL)) {
                    log->debug("File " + s + " for element " + fn + " in Element " + ns_e.attribute("name") + " not found.");
                    return (false);
                }
            }
        }
        // Made it this far, all is well.
        return (true);
    }

