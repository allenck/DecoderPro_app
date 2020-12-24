#include "guilafconfigpanexml.h"
#include "guilafconfigpane.h"
#include "jcheckbox.h"
#include "instancemanager.h"
#include "tabbedpreferences.h"
#include "guilafpreferencesmanager.h"

GuiLafConfigPaneXml::GuiLafConfigPaneXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("GuiLafConfigPanelXml");
}
/**
 * Handle XML persistance of SwingGuiLaf default values.
 * <P>
 * This class is named as being the persistant form of the
 * GuiLafConfigPane class, but there's no object of that
 * form created when this is read back.  Instead, this interacts directly with Swing
 * and the default Locale.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2010
 * @version $Revision: 27930 $
 * @see jmri.GuiLafConfigPane
 * @since 2.9.5
 */
///*public*/ class GuiLafConfigPaneXml extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ GuiLafConfigPaneXml() {
//    }

/**
 * Default implementation for storing the static contents of the Swing LAF
 * @param o Object to store, of type GuiLafConfigPane
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement GuiLafConfigPaneXml::store(QObject* o) {
    QDomElement e = doc.createElement("gui");
    GuiLafConfigPane* g = (GuiLafConfigPane*) o;
#if 1
    QString lafClassName = g->getClassName();

    e.setAttribute("LAFclass", lafClassName);
    e.setAttribute("class", /*this.getClass().getName()*/"apps.configurexml.GuiLafConfigPaneXml");
#endif
    //Locale l = g.getLocale();
    QLocale* l = g->getLocale();
    e.setAttribute("LocaleLanguage",l->language());
    e.setAttribute("LocaleCountry",l->country());
//    e.setAttribute("LocaleVariant",l->variant());

    if (GuiLafConfigPane::getFontSize() != 0)
        e.setAttribute("fontsize", GuiLafConfigPane::getFontSize());

    e.setAttribute("nonStandardMouseEvent",
            (g->mouseEvent->isChecked() ?"yes":"no"));
    e.setAttribute("graphicTableState",
                    (g->graphicStateDisplay->isChecked() ? "yes" : "no"));
    e.setAttribute("tabbedOblockEditor",
                    (g->tabbedOblockEditor->isChecked() ? "yes" : "no"));
    return e;
}

/**
 * Update static data from XML file
 * @param e Top level QDomElement to unpack.
 * @return true if successful
  */
/*public*/ bool GuiLafConfigPaneXml::load(QDomElement shared, QDomElement perNode){
    bool result = true;
#if 0
    UIManager.LookAndFeelInfo[] plafs = UIManager.getInstalledLookAndFeels();
    QHash<QString,QString> installedLAFs = new QHash<QString,QString>(plafs.length());
    for (int i = 0; i < plafs.length(); i++){
        installedLAFs.insert(plafs[i].getName(), plafs[i].getClassName());
    }

    QString name = e.attribute("LAFclass");
    QString className = installedLAFs.get(name);
    log->debug("GUI selection: "+name+" class name: "+className);
    // set the GUI
    if (className != "") {
        try {
            if (!className==(UIManager.getLookAndFeel().getClass().getName())) {
                log->debug("set GUI to "+name+","+className);
                updateLookAndFeel(name, className);
            } else
                log->debug("skip updateLAF as already has className=="+className);
        } catch (Exception ex) {
            log->error("Exception while setting GUI look & feel: "+ex.getMessage());
            result = false;
        }
    }
#endif
    QString langAttr = shared.attribute("LocaleLanguage");
    QString countryAttr = shared.attribute("LocaleCountry");
    QString varAttr = shared.attribute("LocaleVariant");
//    if (countryAttr!="" && langAttr!="" && varAttr!="")
//        Locale.setDefault(new Locale(langAttr,countryAttr,
//                            varAttr));
//     QLocale::setDefault();

    QString clickAttr = shared.attribute("nonStandardMouseEvent");
    if (clickAttr != "") {
        bool nonStandardMouseEvent = clickAttr == ("yes");
        ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->setNonStandardMouseEvent(nonStandardMouseEvent);
    }
    QString graphicAttr = shared.attribute("graphicTableState");
    if (!graphicAttr.isNull())
    {
     bool graphicTableState = graphicAttr == ("yes");
     ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->setGraphicTableState(graphicTableState);
    }
    QString oBlockTable = shared.attribute("tabbedOblockEditor");
    if (oBlockTable != "") {
        bool tabbedOblockEditor = oBlockTable == ("yes");
        ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->setOblockEditTabbed(tabbedOblockEditor);
    }
    GuiLafConfigPane* g = new GuiLafConfigPane();
    ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->registerPref(g);

    QString fontsize = shared.attribute("fontsize");
    if (fontsize != "")
    {
     int size = fontsize.toInt();
     GuiLafConfigPane::setFontSize(size);
     this->setUIFontSize(size);
    }

    return result;
}

/*public*/ void GuiLafConfigPaneXml::setUIFontSize(float size) {
#if 0 // TODO:
 Enumeration<Object> keys = UIManager.getDefaults().keys();
 Font f;
 while (keys.hasMoreElements()) {
     Object key = keys.nextElement();
     Object value = UIManager.get(key);

     if (value instanceof FontUIResource) {
         f = UIManager.getFont(key).deriveFont(((Font) value).getStyle(), size);
         UIManager.put(key, f);
     }
 }
#endif
}
/**
 *  Change the look-and-feel to the specified class.
 *  Alert the user if there were problems loading the PLAF.
 *  @param name (String) the presentable name for the class
 *  @param className (String) the className to be fed to the UIManager
 */
/*public*/ void GuiLafConfigPaneXml::updateLookAndFeel(QString name, QString className)
{
//try {
     // Set the new look and feel, and update the sample message to reflect it.
#if 0
        UIManager.setLookAndFeel(className);
#endif
//    } catch (Exception e) {
//        QString errMsg = "The " + name + " look-and-feel ";
//        if (e instanceof UnsupportedLookAndFeelException){
//            errMsg += "is not supported on this platform.";
//        } else if (e instanceof ClassNotFoundException){
//            errMsg += "could not be found.";
//        } else {
//            errMsg += "could not be loaded.";
//        }

//        log->error(errMsg);

//    }
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void GuiLafConfigPaneXml::load(QDomElement element, QObject* o) throw (Exception){
    log->error("Unexpected call of load(Element, Object)");
}
