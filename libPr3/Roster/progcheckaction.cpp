#include "progcheckaction.h"
#include "xmlfile.h"
#include "jfilechooser.h"
#include "logger.h"
#include "file.h"
#include "joptionpane.h"
#include "namefile.h"

ProgCheckAction::ProgCheckAction()
{

}
/**
 * Check the names in an XML programmer file against the names.xml definitions
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2007
 * @see jmri.jmrit.XmlFile
 */
 ///*public*/ class ProgCheckAction extends AbstractAction {

 /*public*/ ProgCheckAction::ProgCheckAction(QString s, QWidget* who) : AbstractAction(s, who) {
    //super(s);
 log = new Logger("ProgCheckAction");
 fci = NULL;
    _who = who;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


//@Override
 /*public*/ void ProgCheckAction::actionPerformed() {
    if (fci == NULL) {
        fci = XmlFile::userFileChooser("XML files", "xml");
    }
    // request the filename from an open dialog
//    fci.rescanCurrentDirectory();
    int retVal = fci->showOpenDialog(_who);

    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION) {
        File* file = fci->getSelectedFile();
        if (log->isDebugEnabled()) {
            log->debug("located file " + file->getPath() + " for XML processing");
        }

        warnMissingNames(file);

        // as ugly special case, do reverse check for Comprehensive programmer
        if (file->getName().toLower().endsWith("comprehensive.xml")) {
            warnIncompleteComprehensive(file);
        }
    } else {
        log->info("XmlFileCheckAction cancelled in open dialog");
    }
}

/**
 * Find all of the display elements descending from this element
 */
/*static*/ /*protected*/ void ProgCheckAction::expandElement(QDomElement el, QList<QDomElement>* list) {
    // get the leaves here
    //list->addAll(el.elementsByTagName("display"));
    QDomNodeList children = el.elementsByTagName("display");
    for(int i = 0; i << children.size(); i++)
     list->append(children.at(i).toElement());

    children = el.childNodes();
    for (int i = 0; i < children.size(); i++) {
        expandElement(children.at(i).toElement(), list);
    }
}

/**
 * Check for names in programer that are not in names.xml
 */
void ProgCheckAction::warnMissingNames(File* file) {
    QString result = checkMissingNames(file);
    if (result == ("")) {
        JOptionPane::showMessageDialog(_who, "OK, all variables in file are known");
    } else {
        JOptionPane::showMessageDialog(_who, result);
    }
}

//@SuppressFBWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*static*/ QString ProgCheckAction::checkMissingNames(File* file) {
 Logger* log = new Logger("ProgCheckAction");
    try {
        QDomElement root = readFile(file);
        if (log->isDebugEnabled()) {
            log->debug("parsing complete");
        }

        // check to see if there's a programmer element
        if (root.firstChildElement("programmer").isNull()) {
            log->warn("Does not appear to be a programmer file");
            return "Does not appear to be a programmer file";
        }

        // walk the entire tree of elements, saving a reference
        // to all of the "display" elements
        QList<QDomElement>* varList = new QList<QDomElement>();
        expandElement(root.firstChildElement("programmer"), varList);
        if (log->isDebugEnabled()) {
            log->debug("found " + QString::number(varList->size()) + " display elements");
        }
        NameFile* nfile = NameFile::instance();

        QString warnings = "";

        for (int i = 0; i < varList->size(); i++) {
            QDomElement varElement = (varList->at(i));
            // for each variable, see if can find in names file
            QString nameAttr = varElement.attribute("item");
            QString name = NULL;
            if (nameAttr != NULL) {
                name = nameAttr;
            }
            if (log->isDebugEnabled()) {
                log->debug("Variable called \""
                        + ((name != NULL) ? name : "<none>") + "\"");
            }
            if (!(name == NULL ? false : nfile->checkName(name))) {
                log->warn("Variable not found in name list: name=\""
                        + ((name != NULL) ? name : "<none>") + "\"");
                warnings += "Variable not found in name list: name=\""
                        + ((name != NULL) ? name : "<none>") + "\"\n";
            }
        }

        if (warnings != ("")) {
            return "Names missing from Comprehensive.xml\n" + warnings;
        } else {
            return "";
        }

    } catch (Exception* ex) {
        return "Error parsing programmer file: " + ex->getMessage();
    }
}

/**
 * Check for names in names.xml that are not in file
 */
void ProgCheckAction::warnIncompleteComprehensive(File* file) {
    QString result = checkIncompleteComprehensive(file);
    if (result == ("")) {
        JOptionPane::showMessageDialog(_who, "OK, Comprehensive.xml is complete");
    } else {
        JOptionPane::showMessageDialog(_who, result);
    }
}

//@SuppressFBWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*static*/ QString ProgCheckAction::checkIncompleteComprehensive(File* file) {
 Logger* log = new Logger("ProgCheckAction");
    // handle the file (later should be outside this thread?)
    try {
        QDomElement root = readFile(file);
        if (log->isDebugEnabled()) {
            log->debug("parsing complete");
        }

        // check to see if there's a programmer element
        if (root.firstChildElement("programmer").isNull()) {
            log->warn("Does not appear to be a programmer file");
            return "Does not appear to be a programmer file";
        }

        // walk the entire tree of elements, saving a reference
        // to all of the "display" elements
        QList<QDomElement>* varList = new QList<QDomElement>();
        expandElement(root.firstChildElement("programmer"), varList);
        if (log->isDebugEnabled()) {
            log->debug("found " + QString::number(varList->size()) + " display elements");
        }
        NameFile* nfile = NameFile::instance();

        QString warnings = "";

        // for each item in names, see if found in this file
        foreach (QString s, nfile->names()) {
            if (functionMapName(s)) {
                continue;
            }
            bool found = false;
            for (int i = 0; i < varList->size(); i++) {
                QDomElement varElement = varList->at(i);
                // for each variable, see if can find in names file
                QString nameAttr = varElement.attribute("item");
                QString name = NULL;
                if (nameAttr != NULL) {
                    name = nameAttr;
                }
                // now check
                if (name != NULL && name == (s)) {
                    found = true;
                }
            }
            if (!found) {
                log->warn("Variable not in Comprehensive: name=\""
                        + s + "\"");
                warnings += "Variable not in Comprehensive: name=\""
                        + s + "\"\n";
            }
        }

        return warnings;
    } catch (Exception* ex) {
        return "Error parsing programmer file: " + ex->getMessage();
    }
}

/**
 * Check if the name is a function name, e.g. "F5 controls output 8" or
 * "FL(f) controls output 14"
 */
/*static*/ bool ProgCheckAction::functionMapName(QString name) {

//    if (numericPattern == NULL) {
//        numericPattern = Pattern::compile(numericRegex);
//    }
 if(numericPattern == NULL)
  numericPattern = new QRegularExpression(numericRegex);
//    if (ffPattern == NULL) {
//        ffPattern = Pattern::compile(ffRegex);
//    }
 if(ffPattern == NULL)
  ffPattern = new QRegularExpression(ffRegex);
//    if (frPattern == NULL) {
//        frPattern = Pattern::compile(frRegex);
//    }
 if(frPattern == NULL)
  frPattern = new QRegularExpression(frRegex);

//    Matcher matcher = numericPattern.matcher(name);
//    if (matcher.matches()) {
//        return true;
//    }
  if(numericPattern->match(name).hasMatch())
   return true;
//    matcher = ffPattern.matcher(name);
//    if (matcher.matches()) {
//        return true;
//    }
  if(ffPattern->match(name).hasMatch())
   return true;
//    matcher = frPattern.matcher(name);
//    if (matcher.matches()) {
//        return true;
//    }
  if(frPattern->match(name).hasMatch())
   return true;

    return false;
}
/*static*/ /*final*/ QString ProgCheckAction::numericRegex = "^F(\\d++) controls output (\\d++)$";
// /*static*/ Pattern* ProgCheckAction::numericPattern;
QRegularExpression* ProgCheckAction::numericPattern = NULL;
/*static*/ /*final*/ QString ProgCheckAction::ffRegex = "^FL\\(f\\) controls output (\\d++)$";
// /*static*/ Pattern* ProgCheckAction::ffPattern;
/*static*/ QRegularExpression* ProgCheckAction::ffPattern = NULL;
/*static*/ /*final*/ QString ProgCheckAction::frRegex = "^FL\\(r\\) controls output (\\d++)$";
// /*static*/ Pattern* ProgCheckAction::frPattern;
/*static*/ QRegularExpression* ProgCheckAction::frPattern = NULL;

/**
 * Ask SAX to read and verify a file
 */
/*static*/ QDomElement ProgCheckAction::readFile(File* file) throw (JDOMException, IOException) {
    XmlFile* xf = new XmlFile();
//    {
//    };   // odd syntax is due to XmlFile being abstract

    return xf->rootFromFile(file);

}
