#include "itempanel.h"
#include "namedicon.h"
#include "jmrijframe.h"
#include <QVBoxLayout>
#include "borderlayout.h"
#include <QComboBox>
#include "box.h"
#include "itempalette.h"
#include <QLabel>
#include "imagepanel.h"
#include "displayframe.h"
#include "loggerfactory.h"
#include "flowlayout.h"
#include "editor.h"
#include "bufferedimage.h"
#include "drawsquares.h"
#include <QGroupBox>
#include "portalicon.h"
#include "jpanel.h"
#include "familyitempanel.h"
#include "iconitempanel.h"
#include "borderfactory.h"

//ItemPanel::ItemPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
*  JPanels for the various item types that come from tool Tables - e.g. Sensors, Turnouts, etc.
*
*  Devices such as these have sets of icons to display their various states.  such sets are called
*  a "family" in the code.  These devices then may have sets of families to provide the user with
*  a choice of the icon set to use for a particular device.  The subclass FamilyItemPanel.java
*  and its subclasses handles these devices.
*trtrtr
*  Other devices, e.g. backgrounds or memory, may use only one or no icon to display.  The subclass
*  IconItemPanel.java and its subclasses handles these devices.
*/
///*public*/ abstract class ItemPanel extends JPanel {


    /**
    * Constructor for all table types.  When item is a bean, the itemType is the name key
    * for the item in jmri.NamedBeanBundle.properties
    */
/*public*/ ItemPanel::ItemPanel(JmriJFrame *parentFrame, QString  type, Editor* editor, QWidget* parent)
    : JPanel(parent)
{
 _update = false;    // Editing existing icon, do not allow icon dragging. set in init()
 _initialized = false;    // Has init() been run
 _linkName = new JTextField(30);

  _paletteFrame = parentFrame;
  _itemType = type;
  _editor = editor;
  setLayout(thisLayout = new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
  thisLayout->setObjectName("ItemPanelLayout");
 }

/**
 * Initializes panel for selecting a new control panel item or for updating an existing item.
 * Adds table if item is a bean.  i.e. customizes for the item type
 */
/*public*/ void ItemPanel::init() {
 _initialized = true;
}

/*protected*/ void ItemPanel::initLinkPanel() {
    JPanel* panel = new JPanel();
    panel->setLayout(new FlowLayout());  //new BoxLayout(p, BoxLayout.Y_AXIS)
    panel->layout()->addWidget(new JLabel(tr("Panel or URL Name")));
    panel->layout()->addWidget(_linkName);
    _linkName->setToolTip(tr("Enter link to JMRI panel or http URL (optional)"));
    panel->setToolTip(tr("ToolTEnter link to JMRI panel or http URL (optional)ipLink"));

    layout()->addWidget(panel);
}

/*public*/ void ItemPanel::closeDialogs() {
}

/*protected*/ void ItemPanel::reset() {
    _paletteFrame->repaint();
}

/*protected*/ /*final*/ bool ItemPanel::isUpdate() {
    return _update;
}

/******** Default family icon names ********/
/*static*/ /*final*/ QStringList ItemPanel::TURNOUT = QStringList() << "TurnoutStateClosed"<< "TurnoutStateThrown" <<
                                     "BeanStateInconsistent" <<  "BeanStateUnknown";
/*static*/ /*final*/ QStringList ItemPanel::SENSOR = QStringList() << "SensorStateActive" << "SensorStateInactive"<<
                                    "BeanStateInconsistent" << "BeanStateUnknown" ;
/*static*/ /*final*/ QStringList ItemPanel::SIGNALHEAD = QStringList() <<"SignalHeadStateRed"<< "SignalHeadStateYellow"<<
                                    "SignalHeadStateGreen"<< "SignalHeadStateDark"<<
                                    "SignalHeadStateHeld"<< "SignalHeadStateLunar"<<
                                    "SignalHeadStateFlashingRed"<< "SignalHeadStateFlashingYellow"<<
                                    "SignalHeadStateFlashingGreen"<< "SignalHeadStateFlashingLunar";
/*static*/ /*final*/ QStringList ItemPanel::LIGHT  = QStringList() <<"LightStateOff"<< "LightStateOn"<<
                                   "BeanStateInconsistent"<< "BeanStateUnknown";
/*static*/ /*final*/ QStringList ItemPanel::MULTISENSOR  = QStringList() <<"SensorStateInactive"<< "BeanStateInconsistent" <<
                                         "BeanStateUnknown"<< "first"<< "second"<< "third";

/*static*/ /*final*/ QStringList ItemPanel::RPSREPORTER  = QStringList() <<"active"<< "error";
/*static*/ /*final*/ QStringList ItemPanel::ICON  = QStringList() << "Icon";
/*static*/ /*final*/ QStringList ItemPanel::BACKGROUND  = QStringList() <<"Background";
/*static*/ /*final*/ QStringList ItemPanel::INDICATOR_TRACK  = QStringList() <<"ClearTrack"<< "OccupiedTrack" << "AllocatedTrack" <<"PositionTrack"<< "DontUseTrack"<< "ErrorTrack";
/*static*/ /*final*/ QStringList ItemPanel::PORTAL = QStringList() << PortalIcon::HIDDEN << PortalIcon::VISIBLE << PortalIcon::PATH <<
            PortalIcon::TO_ARROW<< PortalIcon::FROM_ARROW;
/*static*/ QString ItemPanel::redX = ":/resources/icons/misc/X-red.gif";

/*static*/ /*private*/ QStringList ItemPanel::getNames(QString type) {
    if (type == ("Turnout")) {
        return TURNOUT;
    } else if (type == ("Sensor")) {
        return SENSOR;
    } else if (type == ("SignalHead")) {
        return SIGNALHEAD;
    } else if (type == ("Light")) {
        return LIGHT;
    } else if (type == ("MultiSensor")) {
        return MULTISENSOR;
    } else if (type == ("Icon")) {
        return ICON;
    } else if (type == ("Background")) {
        return BACKGROUND;
    } else if (type == ("RPSReporter")) {
        return RPSREPORTER;
    } else if (type == ("IndicatorTrack")) {
        return INDICATOR_TRACK;
    } else if (type == ("IndicatorTO")) {
        return INDICATOR_TRACK;
    } else if (type == ("Portal")) {
        return PORTAL;
    } else {
        log->error(tr("Item type \"%1\" cannot create icon sets!").arg(type));
        return QStringList();
    }
}


/*static*/ /*protected*/ QMap<QString, NamedIcon*>* ItemPanel::makeNewIconMap(QString type)
{
Logger* log = new Logger("ItemPanel");

    QMap <QString, NamedIcon*>* newMap = new QMap <QString, NamedIcon*>();
    QStringList names = QStringList();
    if (type==("Turnout")) {
        names = TURNOUT;
    } else if (type==("Sensor")) {
        names = SENSOR;
    } else if (type==("SignalHead")) {
        names = SIGNALHEAD;
    } else if (type==("Light")) {
        names = LIGHT;
    } else if (type==("MultiSensor")) {
        names = MULTISENSOR;
    } else if (type==("Icon")) {
        names = ICON;
    } else if (type==("Background")) {
        names = BACKGROUND;
    } else if (type==("RPSReporter")) {
        names = RPSREPORTER;
    } else if (type==("IndicatorTrack")) {
        names = INDICATOR_TRACK;
    } else if (type==("IndicatorTO")) {
        names = INDICATOR_TRACK;
    } else {
        log->error("Item type \""+type+"\" cannot create icon sets!");
        return NULL;
    }
    for (int i=0; i<names.length(); i++) {
       QString fileName = "resources/icons/misc/X-red.gif";
       NamedIcon* icon = new NamedIcon(fileName, fileName);
       newMap->insert(names.at(i), icon);
    }
    return newMap;
}

/*static*/ /*protected*/ void ItemPanel::checkIconMap(QString type, QMap<QString, NamedIcon*>* map)
{
    QStringList names = getNames(type);
    for (int i = 0; i < names.length(); i++) {
        if (map->value(names[i]) == nullptr) {
            NamedIcon* icon = new NamedIcon(redX, redX);
            // store RedX as default icon if icon not set
            map->insert(names[i], icon);
        }
    }
}

/*private*/ /*final*/ /*static*/ Logger* ItemPanel::log = LoggerFactory::getLogger("ItemPanel");
