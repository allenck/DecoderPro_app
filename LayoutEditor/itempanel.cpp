#include "itempanel.h"
#include "namedicon.h"
#include "jmrijframe.h"
#include <QVBoxLayout>
#include "borderlayout.h"

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
*
*  Other devices, e.g. backgrounds or memory, may use only one or no icon to display.  The subclass
*  IconItemPanel.java and its subclasses handles these devices.
*/
///*public*/ abstract class ItemPanel extends JPanel {


    /**
    * Constructor for all table types.  When item is a bean, the itemType is the name key
    * for the item in jmri.NamedBeanBundle.properties
    */
/*public*/ ItemPanel::ItemPanel(DisplayFrame* parentFrame, QString  type, QString family, Editor* editor, QWidget* parent)
    : QWidget(parent)
{
 _update = false;    // Editing existing icon, do not allow icon dragging. set in init()
 _initialized = false;    // Has init() been run

  _paletteFrame = parentFrame;
  _itemType = type;
  if (family!=NULL && family.trimmed().length()>0)
  {
   _family = family;
  }
  else
  {
    _family = "";
  }
  _editor = editor;
  setLayout(thisLayout = new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
 }

/**
 * Initializes panel for selecting a new control panel item or for updating an existing item.
 * Adds table if item is a bean.  i.e. customizes for the item type
 */
/*public*/ void ItemPanel::init() {
    _initialized = true;
}

/* Methods used upon return from Icon dialogs
* to update the panel for TableItemPanel item types.
*/
/*protected*/ void ItemPanel::initIconFamiliesPanel(){
}
/*protected*/ void ItemPanel::addIconsToPanel(QHash<QString, NamedIcon*>* iconMap){
}
/*protected*/ void ItemPanel::setFamily(QString family) {
}
/*protected*/ void ItemPanel::removeIconFamiliesPanel() {
}
/*protected*/ void ItemPanel::removeIconMap(QString family) {
}

/*protected*/ void closeDialogs() {
}

/*protected*/ void ItemPanel::reset() {
  _paletteFrame->pack();
//      _paletteFrame.invalidate();
//      invalidate();
//      _paletteFrame.repaint();
}
/*protected*/ void ItemPanel::updateFamiliesPanel() {
}
/*public*/ void ItemPanel::dispose() {
}

/*public*/ QString ItemPanel::getFamilyName() {
    return _family;
}

/*protected*/ /*final*/ bool ItemPanel::isUpdate() {
    return _update;
}

/******** Default family icon names ********/
/*static*/ /*final*/ QStringList ItemPanel::TURNOUT = QStringList() << "TurnoutStateClosed"<< "TurnoutStateThrown" <<
                                     "BeanStateInconsistent" <<  "BeanStateUnknown";
/*static*/ /*final*/ QStringList ItemPanel::SENSOR = QStringList() << "SensorStateActive" << "SensorStateInactive"<<
                                    "BeanStateInconsistent" << "BeanStateUnknown" ;
/*static*/ /*final*/ QStringList ItemPanel::_SIGNAL = QStringList() <<"SignalHeadStateRed"<< "SignalHeadStateYellow"<<
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
/*static*/ /*final*/ QStringList ItemPanel::INDICATOR_TRACK  = QStringList() <<"ClearTrack"<< "OccupiedTrack" << "AllocatedTrack" <<
                                            "PositionTrack"<< "DontUseTrack"<< "ErrorTrack";

/*static*/ /*protected*/ QHash<QString, NamedIcon*>* ItemPanel::makeNewIconMap(QString type)
{
Logger* log = new Logger("ItemPanel");

    QHash <QString, NamedIcon*>* newMap = new QHash <QString, NamedIcon*>();
    QStringList names = QStringList();
    if (type==("Turnout")) {
        names = TURNOUT;
    } else if (type==("Sensor")) {
        names = SENSOR;
    } else if (type==("SignalHead")) {
        names = _SIGNAL;
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
