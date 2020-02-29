#include "switchboardeditorxml.h"
#include "loggerfactory.h"
#include "switchboardeditor.h"
#include "instancemanager.h"
#include "panelmenu.h"
#include "configxmlmanager.h"
#include "class.h"
#include "guilafpreferencesmanager.h"
#include "userpreferencesmanager.h"

/**
 * Handle configuration for {@link SwitchboardEditor} panes.
 *
 * @author Bob Jacobsen Copyright (c) 2002
 * @author Egbert Broerse Copyright (c) 2017
 */
///*public*/ class SwitchboardEditorXml extends AbstractXmlAdapter {

    /*public*/ SwitchboardEditorXml::SwitchboardEditorXml(QObject *parent )
 : AbstractXmlAdapter (parent)
{
}

/**
 * Default implementation for storing the contents of a SwitchboardEditor.
 * Storing of beanswitch properties for use on web panel
 * {@link SwitchboardEditorXml}
 *
 * @param o Object to store, of type SwitchboardEditor
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement SwitchboardEditorXml::store(QObject* o) {
    SwitchboardEditor* p = (SwitchboardEditor*) o;
    QDomElement panel = doc.createElement("switchboardeditor");

    JFrame* frame = p->getTargetFrame();
    QSize size = frame->size();
    QPoint posn = frame->pos();

     panel.setAttribute("class", "jmri.jmrit.display.switchboardEditor.configurexml.SwitchboardEditorXml");
     panel.setAttribute("name", frame->getTitle());
     panel.setAttribute("x", posn.x());
     panel.setAttribute("y", posn.y());
     panel.setAttribute("height", size.height());
     panel.setAttribute("width", size.width());
     panel.setAttribute("editable", (p->isEditable() ? "yes" : "no"));
     panel.setAttribute("showtooltips", (p->showToolTip() ? "yes" : "no"));
     panel.setAttribute("controlling", (p->allControlling() ? "yes" : "no"));
     panel.setAttribute("hide", p->isVisible() ? "no" : "yes");
     panel.setAttribute("panelmenu", p->isPanelMenuVisible() ? "yes" : "no");
     panel.setAttribute("scrollable", p->getScrollable());
     panel.setAttribute("hideunconnected", (p->getHideUnconnected() ? "yes" : "no"));
     panel.setAttribute("rangemin", p->getPanelMenuRangeMin());
     panel.setAttribute("rangemax", p->getPanelMenuRangeMax());
     panel.setAttribute("type", p->getSwitchType());
     panel.setAttribute("connection", p->getSwitchManu());
     panel.setAttribute("shape", p->getSwitchShape());
     panel.setAttribute("columns", p->getColumns());
     panel.setAttribute("defaulttextcolor", p->getDefaultTextColor());
    if (p->getBackgroundColor() != QColor()) {
         panel.setAttribute("redBackground", p->getBackgroundColor().red());
         panel.setAttribute("greenBackground", p->getBackgroundColor().green());
         panel.setAttribute("blueBackground", p->getBackgroundColor().blue());
    }

    // include contents (not used to store Switchboards on disk as
    // all config is stored at Panel level).
    return panel;
}

//@Override
/*public*/ void SwitchboardEditorXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/**
 * Create a SwitchboardEditor object, then register and fill it, then pop it
 * in a JFrame.
 *
 * @param shared Top level QDomElement to unpack.
 * @return true if successful
 */
//@Override
/*public*/ bool SwitchboardEditorXml::load(QDomElement shared, QDomElement perNode) {
 Q_UNUSED(perNode);
    bool result = true;
    // find coordinates
    int x = 0;
    int y = 0;
    int height = 400;
    int width = 300;
    int rangemin = 1;
    int rangemax = 32;
    int columns = 4;
    QString type = "T";
    QString connection = "I";
    QString shape = "key";
    QString name;

    try {
     bool ok;
        x = shared.attribute("x").toInt(&ok);
        if(!ok) throw DataConversionException();
        y = shared.attribute("y").toInt(&ok);
        if(!ok) throw DataConversionException();
        height = shared.attribute("height").toInt(&ok);
        if(!ok) throw DataConversionException();
        width = shared.attribute("width").toInt(&ok);
        if(!ok) throw DataConversionException();
    } catch (DataConversionException e) {
        log->error("failed to convert Switchboard's attribute");
        result = false;
    }
    // find the name
    name = "Switchboard"; // this will be replaced by the name as stored NOI18N
    if (shared.attribute("name") != "") {
        name = shared.attribute("name");
    }
    // confirm that panel hasn't already been loaded
    if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name)) {
        log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
        result = false;
    }

    // If available, override location and size with machine dependent values
    if (!((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize()) {
        UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getNullableDefault("UserPreferencesManager");
        if (prefsMgr != nullptr) {

            QPoint prefsWindowLocation = prefsMgr->getWindowLocation(name);
            if (!prefsWindowLocation.isNull()) {
                x = (int) prefsWindowLocation.x();
                y = (int) prefsWindowLocation.y();
            }

            QSize prefsWindowSize = prefsMgr->getWindowSize(name);
            if (!prefsWindowSize.isNull() && prefsWindowSize.height() != 0 && prefsWindowSize.width() != 0) {
                height = (int) prefsWindowSize.height();
                width = (int) prefsWindowSize.width();
            }
        }
    }

    SwitchboardEditor* panel = new SwitchboardEditor(name);
    // panel->makeFrame(name);
    static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(panel);
    panel->getTargetFrame()->setLocation(x, y);
    panel->getTargetFrame()->resize(width, height);

    panel->setTitle();

    // Load editor option flags. This has to be done before the content
    // items are loaded, to preserve the individual item settings.
    QString a;
    bool value = true;

    if ((a = shared.attribute("editable")) != nullptr && a == ("no")) {
        value = false;
    }
    panel->setAllEditable(value);

    value = true;
    if ((a = shared.attribute("showtooltips")) != nullptr && a == ("no")) {
        value = false;
    }
// ??    panel->setAllShowToolTip(value);

    value = true;
    if ((a = shared.attribute("controlling")) != nullptr && a == ("no")) {
        value = false;
    }
    panel->setAllControlling(value);

    value = false;
    if ((a = shared.attribute("hide")) != nullptr && a == ("yes")) {
        value = true;
    }
    panel->setShowHidden(value);

    value = true;
    if ((a = shared.attribute("panelmenu")) != nullptr && a == ("no")) {
        value = false;
    }
    panel->setPanelMenuVisible(value);

    QString state = "both";
    if ((a = shared.attribute("scrollable")) != nullptr) {
        state = a;
    }
    panel->setScroll(state);

    value = false;
    if ((a = shared.attribute("hideunconnected")) != nullptr && a == ("yes")) {
        value = true;
    }
    panel->setHideUnconnected(value);

    try {
     bool ok;
        rangemin = shared.attribute("rangemin").toInt(&ok);
        if(!ok) throw DataConversionException();
        rangemax = shared.attribute("rangemax").toInt(&ok);
        if(!ok) throw DataConversionException();
    } catch (DataConversionException e) {
        log->error("failed to convert Switchboard's range");
        result = false;
    }
    panel->setPanelMenuRangeMin(rangemin);
    panel->setPanelMenuRangeMax(rangemax);

    type = shared.attribute("type");
    panel->setSwitchType(type);

    connection = shared.attribute("connection");
     panel->setSwitchManu(connection);

    shape = shared.attribute("shape");
     panel->setSwitchShape(shape);

    try {
      bool ok;
        columns = shared.attribute("columns").toInt(&ok);
        if(!ok) throw DataConversionException();
    } catch (DataConversionException e) {
        log->error("failed to convert Switchboard's column count");
        result = false;
    }
     panel->setColumns(columns);

    QString defaultTextColor = "black";
    if (shared.attribute("defaulttextcolor") != nullptr) {
        defaultTextColor = shared.attribute("defaulttextcolor");
    }
     panel->setDefaultTextColor(defaultTextColor);
    // set color if needed
    try {
      bool ok;
        int red = shared.attribute("redBackground").toInt(&ok);
        if(!ok) throw DataConversionException();
        int blue = shared.attribute("blueBackground").toInt(&ok);
        if(!ok) throw DataConversionException();
        int green = shared.attribute("greenBackground").toInt(&ok);
        // panel.setBackground(new Color(red, green, blue));
        if(!ok) throw DataConversionException();
         panel->setDefaultBackgroundColor( QColor(red, green, blue));
    } catch (DataConversionException e) {
        log->warn("Could not parse color attributes!");
    } catch (NullPointerException e) {  // considered normal if the attributes are not present
    }
    //set the (global) editor display widgets to their flag settings
     panel->initView();

    // load the contents with their individual option settings
    QDomNodeList items = shared.childNodes();
    for (int i = 0; i < items.size(); i++) {
        // get the class, hence the adapter object to do loading
        QDomElement item = items.at(i).toElement();
        QString adapterName = item.attribute("class");
        log->debug(tr("load via %1").arg(adapterName));
        try {
            XmlAdapter* adapter = (XmlAdapter*) Class::forName(adapterName)->newInstance();
            // and do it
            adapter->load(item, panel);
            if (! panel->loadOK()) {
                result = false;
            }
        }
        catch (ClassNotFoundException e) //| InstantiationException | IllegalAccessException
//                | jmri.configurexml.JmriConfigureXmlException
//                | RuntimeException e)
        {
            log->error(tr("Exception while loading %1").arg(adapterName), e);
            result = false;
        }
    }
     panel->disposeLoadData();     // dispose of url correction data

    // display the results, with the editor in back
     panel->pack();
     panel->setAllEditable( panel->isEditable());

    // we don't pack the target frame here, because size was specified
    // TODO: Work out why, when calling this method, panel size is increased
    // vertically (at least on MS Windows)
     panel->getTargetFrame()->setVisible(true);    // always show the panel

    // register the resulting panel for later configuration
    ConfigureManager* cm = static_cast<ConfigureManager*>(InstanceManager::getNullableDefault("ConfigureManager"));
    if (cm != nullptr) {
        cm->registerUser(panel);
    }

    // reset the size and position, in case the display caused it to change
     panel->getTargetFrame()->setLocation(x, y);
     panel->getTargetFrame()->resize(width, height);
     panel->updatePressed();
    return result;
}

//@Override
/*public*/ int SwitchboardEditorXml::loadOrder() const {
    return Manager::PANELFILES;
}

/*private*/ /*final*/ /*static*/ Logger* SwitchboardEditorXml::log = LoggerFactory::getLogger("SwitchboardEditorXml");


