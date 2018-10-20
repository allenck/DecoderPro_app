#include "programmerconfigpanexml.h"
#include "programmerconfigpane.h"
#include "instancemanager.h"
#include "progdefault.h"
#include "combinedlocoselpane.h"
#include "paneprogframe.h"

ProgrammerConfigPaneXml::ProgrammerConfigPaneXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
    log = new Logger("ProgrammerConfigPaneXml");
}
/**
 * Handle XML persistance of symbolic programmer default values.
 * <P>
 * This class is named as being the persistant form of the
 * ProgrammerConfigPane class, but there's no object of that
 * form created when this is read back.  Instead, this persists static members of the
 * symbolicprog.CombinedLocoSelPane class.
 *<P>
 * This class sets the default programmer file in the ProgDefaults class.
 * On MacOS Classic, however, that information was being overwritten
 * by a second initialization of the class; in other words, the clinit
 * class initialization routine was being run later for unknown reasons.
 * The fix to this was to add an explicit construction of a
 * CombinedLocoSelPane object.  It is <b>not</b> known why this works!
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @version $Revision: 27930 $
 */
///*public*/ class ProgrammerConfigPaneXml extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ ProgrammerConfigPaneXml() {
//    }

/**
 * Default implementation for storing the static contents
 * @param o Object to store, of type PositionableLabel
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement ProgrammerConfigPaneXml::store(QObject* o)
{
 ProgrammerConfigPane* p = (ProgrammerConfigPane*) o;
 QDomElement programmer = doc.createElement("programmer");
 if (p->getSelectedItem() != NULL) {
        programmer.setAttribute("defaultFile", p->getSelectedItem());
    }
    programmer.setAttribute("verifyBeforeWrite", "no");
    if (!p->getShowEmptyTabs()) programmer.setAttribute("showEmptyPanes", "no");
    if (p->getShowCvNums()) programmer.setAttribute("showCvNumbers", "yes");
    programmer.setAttribute("class", /*this.getClass().getName()*/ "jmri.jmrit.symbolicprog.configurexml.ProgrammerConfigPaneXml");
    return programmer;
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @return true if successful
  */
/*public*/ bool ProgrammerConfigPaneXml::load(QDomElement element) throw (Exception) {
    bool result = true;

    if (element.attribute("defaultFile") != NULL) {
        if (log->isDebugEnabled()) log->debug("set programmer default file: "+element.attribute("defaultFile"));
ProgDefault::setDefaultProgFile(element.attribute("defaultFile"));
    }

    // ugly hack to avoid static re-initialization, see comment at
    // top of file.
    CombinedLocoSelPane* clsp = new  CombinedLocoSelPane();
    clsp->close();
    delete clsp;

    QString a;
    if (NULL != (a = element.attribute("showEmptyPanes"))){
        if ( a==("no"))
            PaneProgFrame::setShowEmptyPanes(false);
        else
            PaneProgFrame::setShowEmptyPanes(true);
    }
    if (NULL != (a = element.attribute("showCvNumbers"))){
        if ( a==("yes"))
            PaneProgFrame::setShowCvNumbers(true);
        else
            PaneProgFrame::setShowCvNumbers(false);
    }
    ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerPref(new ProgrammerConfigPane(/*true*/));
    return result;
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void ProgrammerConfigPaneXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->warn("unexpected call of 2nd load form");
}
//    // initialize logging
//    static Logger log = LoggerFactory.getLogger(ProgrammerConfigPaneXml.class.getName());
