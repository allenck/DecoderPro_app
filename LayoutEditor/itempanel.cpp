#include "itempanel.h"
#include "namedicon.h"
#include "jmrijframe.h"
#include <QVBoxLayout>
#include "borderlayout.h"
#include <QComboBox>
#include "box.h"
#include "jtextfield.h"
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
/*public*/ ItemPanel::ItemPanel(DisplayFrame* parentFrame, QString  type,  Editor* editor, QWidget* parent)
    : QWidget(parent)
{
 _update = false;    // Editing existing icon, do not allow icon dragging. set in init()
 _initialized = false;    // Has init() been run
 _linkName = new JTextField(30);

  _paletteFrame = parentFrame;
  _itemType = type;
  updateBackgrounds(editor);
  setLayout(thisLayout = new QVBoxLayout(this/*, BoxLayout.Y_AXIS*/));
  thisLayout->setObjectName("ItemPanelLayout");
 }

/**
 * Initializes panel for selecting a new control panel item or for updating an existing item.
 * Adds table if item is a bean.  i.e. customizes for the item type
 */
/*public*/ void ItemPanel::init() {
 if (!_initialized)
 {
//             if (!jmri.util.ThreadingUtil.isGUIThread()) log.error(java.util.ResourceBundle.getBundle("jmri/jmrit/display/palette/PaletteBundle").getString("AllFamiliesDeleted"), new Exception("traceback"));
//             Thread.yield();
     thisLayout->addWidget(Box::createVerticalGlue());
     _initialized = true;
 }
}

/**
 * Initialization for conversion of plain track to indicator track by CircuitBuilder.
 * @param doneAction Callback action for Done button
 */
/*abstract*/ /*public*/ void ItemPanel::init(ActionListener* /*doneAction*/) {}

/*protected*/ void ItemPanel::setEditor(Editor* ed) {
    updateBackgrounds(ed);    // editor change may change panel background
    if (_bgColorBox != nullptr) {
        _bgColorBox->setCurrentIndex(_paletteFrame->getPreviewBg());
    }
}

/*
 * Notification to itemPanel to update child dialogs, if any
 */
/*abstract*/ /*protected*/ void ItemPanel::setPreviewBg(int index) {}

/*abstract*/ /*protected*/ void ItemPanel::updateBackground0(BufferedImage* im) {}

/*public*/ bool ItemPanel::oktoUpdate() {
    return true;
}

/*protected*/ void ItemPanel::initLinkPanel() {
//        Font font = new Font("SansSerif", Font.BOLD, 12);
    QWidget* blurb = new QWidget();
    //blurb.setLayout(new BoxLayout(blurb, BoxLayout.Y_AXIS));
    QVBoxLayout* blurbLayout = new QVBoxLayout(blurb);
    blurbLayout->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
    blurbLayout->addWidget(new QLabel(tr("You can make clicking on this object link to another JMRI Panel or URL, "/*, "Text"*/)));
    blurbLayout->addWidget(new QLabel(tr("-- for a JMRI Panel, type \"frame:<panel name>\" into the field at bottom.")));
    blurbLayout->addWidget(new QLabel(tr("-- for an URL, type the link (i.e. \"http://etc\") into the field at bottom.")));
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("Link Name")));
    panelLayout->addWidget(_linkName);
    _linkName->setToolTip(tr("Enter link to JMRI panel or http URL (optional)"));
    panel->setToolTip(tr("Enter link to JMRI panel or http URL (optional)"));
    blurbLayout->addWidget(panel);
    thisLayout->addWidget(blurb);
}

/**
 * Create panel element containing [Set background:] drop down list.
 *
 * @see DecoratorPanel
 * @param preview1 preview pane1 to set background image on
 * @param preview2 (optional) second preview pane1 to set background image on
 * @return JPanel with label and drop down with actions
 */
/*protected*/ QWidget* ItemPanel::makeBgButtonPanel(ImagePanel* preview1, ImagePanel* preview2) {
 this->preview1 = preview1;
 this->preview2 = preview2;

    if (_bgColorBox == nullptr) {
        _bgColorBox = new QComboBox();
        _bgColorBox->addItem(tr("Panel Color")); // PanelColor key is specific for CPE, but too long for combo
        _bgColorBox->addItem(tr("White"));
        _bgColorBox->addItem(tr("LightGray"));
        _bgColorBox->addItem(tr("DarkGray"));
        _bgColorBox->addItem(tr("Checkers"));
        _bgColorBox->setCurrentIndex(_paletteFrame->getPreviewBg()); // Global field, starts as 0 = panel   bg color
//        _bgColorBox.addActionListener((ActionEvent e) -> {
//            if (_backgrounds != null) {
//                int previewBgSet = _bgColorBox.getSelectedIndex();
//                _paletteFrame.setPreviewBg(previewBgSet); // store user choice in field on parent
//                setPreviewBg(previewBgSet);
//                // load background image
//                log.debug("ItemPalette setImage called {}", previewBgSet);
//                if (preview1 != null) {
//                    preview1.setImage(_backgrounds[previewBgSet]);
//                    preview1.revalidate(); // force redraw
//                }
//                if (preview2 != null) {
//                    preview2.setImage(_backgrounds[previewBgSet]);
//                    preview2.revalidate(); // force redraw
//                }
//            } else {
//                log.debug("imgArray is empty");
//            }
//        });
        connect(_bgColorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_bgColorBox()));
    }
    QWidget* backgroundPanel = new QWidget(); //new FlowLayout(FlowLayout.CENTER));
    FlowLayout* backgroundPanelLayout = new FlowLayout(backgroundPanel);
    backgroundPanelLayout->addWidget(new QLabel(tr("Set Background")));
    backgroundPanelLayout->addWidget(_bgColorBox);
    return backgroundPanel;
}

void ItemPanel::on_bgColorBox()
{
 if (_backgrounds != nullptr)
 {
     int previewBgSet = _bgColorBox->currentIndex();
     _paletteFrame->setPreviewBg(previewBgSet); // store user choice in field on parent
     setPreviewBg(previewBgSet);
     // load background image
     log->debug(tr("ItemPalette setImage called %1").arg(previewBgSet));
     if (preview1 != nullptr) {
         preview1->setImage(_backgrounds->at(previewBgSet));
         preview1->update(); // force redraw
     }
     if (preview2 != nullptr) {
         preview2->setImage(_backgrounds->at(previewBgSet));
         preview2->update(); // force redraw
     }
 } else {
     log->debug("imgArray is empty");
 }

}
/**
 * Create array of backgrounds for preview pane.
 * @param ed Panel editor
 */
/*protected*/ void ItemPanel::updateBackgrounds(Editor* ed) {
    _editor = ed;
    QColor currentBackground;// = ed->getTargetPanel()->getBackground(); // start using Panel background color
    QBrush b = ed->editPanel->backgroundBrush();
    if(b == Qt::NoBrush)
     currentBackground = QColor(Qt::white);
    currentBackground = b.color();

    _backgrounds = makeBackgrounds(_backgrounds, currentBackground);
}

/*static*/ /*protected*/ QVector<BufferedImage*>* ItemPanel::makeBackgrounds(QVector<BufferedImage*>* backgrounds, QColor panelBackground)
{
 if (backgrounds==nullptr)
 { // reduces load but will not redraw for new size
  backgrounds = new QVector<BufferedImage*>(5);
  for (int i = 1; i <= 3; i++)
  {
   backgrounds->replace(i, DrawSquares::getImage(500, 400, 10, colorChoice[i - 1], colorChoice[i - 1]));
      // [i-1] because choice 0 is not in colorChoice[]
  }
  backgrounds->replace(4, DrawSquares::getImage(500, 400, 10, QColor(Qt::white), _grayColor));
 }
 // always update background from Panel Editor
 backgrounds->replace(0, DrawSquares::getImage(500, 400, 10, panelBackground, panelBackground));
 log->debug(tr("makeBackgrounds backgrounds[0] = %1").arg(backgrounds->at(0)->text()));
 return backgrounds;
}

/*static*/ QColor ItemPanel::_grayColor = QColor(235, 235, 235);
/*static*/ QColor ItemPanel::_darkGrayColor = QColor(150, 150, 150);
/*static*/ /*protected*/ QVector<QColor> ItemPanel::colorChoice = QVector<QColor>() <<QColor(Qt::white) << ItemPanel::_grayColor << ItemPanel::_darkGrayColor; // panel bg color picked up directly

/*protected*/ JPanel* ItemPanel::makePreviewPanel(ImagePanel* panel1, ImagePanel* panel2) {
    JPanel* previewPanel = new JPanel();
    QVBoxLayout* previewPanelLayout;
    previewPanel->setLayout(previewPanelLayout =new QVBoxLayout());//(previewPanel, BoxLayout.Y_AXIS));
#if 0 // for testing ACK
    QWidget* testWidget = new QWidget();
    QHBoxLayout* testLayout = new QHBoxLayout(testWidget);
    for(int i=0; i < _backgrounds->size(); i++)
    {
     QLabel* myLabel = new QLabel();
     myLabel->setPixmap(QPixmap::fromImage(((QImage)*_backgrounds->at(i))));
     testLayout->addWidget(myLabel);
    }
    previewPanelLayout->addWidget(testWidget);
#endif
    //previewPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black, 1),
//            tr("PreviewBorderTitle")));
//    previewPanel->setTitle(tr("Preview"));
    makeBgButtonPanel(panel1, panel2);
    if (_bgColorBox != nullptr) {
        QWidget* bkgdBoxPanel = new QWidget();
        QHBoxLayout* bkgdBoxPanelLayout = new QHBoxLayout(bkgdBoxPanel);
        bkgdBoxPanelLayout->addWidget(new QLabel(tr("View on:")), 0, Qt::AlignRight/*SwingConstants.RIGHT*/);
        bkgdBoxPanelLayout->addWidget(_bgColorBox);
        previewPanelLayout->addWidget(bkgdBoxPanel);
        _bgColorBox->setCurrentIndex(_paletteFrame->getPreviewBg());
    }
    if (panel1 != nullptr) {
        previewPanelLayout->addWidget(panel1);
    }
    if (panel2 != nullptr) {
        previewPanelLayout->addWidget(panel2);
    }
    return previewPanel;
}

/*public*/ void ItemPanel::closeDialogs() {
}

/*protected*/ void ItemPanel::reset() {
    closeDialogs();
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
/*static*/ QString ItemPanel::redX = "resources/icons/misc/X-red.gif";

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

/*protected*/ DisplayFrame* ItemPanel::getParentFrame() {
    return _paletteFrame;
}

/*protected*/ void ItemPanel::reSizeDisplay(bool isPalette, QSize oldDim, QSize totalDim) {
    QSize newDim = sizeHint();
    QSize deltaDim = QSize(totalDim.width() - oldDim.width(), totalDim.height() - oldDim.height());
    if (log->isDebugEnabled())
        log->debug(tr("resize by %1 Dim= (%2, %3) \"%4\" OldDim= (%5, %6) NewDim= ({%7, %8)" ).arg(
                (isPalette?"TabPane":"JFrame") ).arg( totalDim.width() ).arg( totalDim.height() ).arg(
                this->_itemType ).arg( oldDim.width() ).arg( oldDim.height() ).arg( newDim.width() ).arg( newDim.height()));
    if (_update) {
        _paletteFrame->reSize(_paletteFrame, deltaDim, newDim, _editor);
    } else if (isPalette && _initialized) {
        _paletteFrame->reSize(ItemPalette::_tabPane, deltaDim, newDim, _editor);
    }
}

/*private*/ /*final*/ /*static*/ Logger* ItemPanel::log = LoggerFactory::getLogger("ItemPanel");
