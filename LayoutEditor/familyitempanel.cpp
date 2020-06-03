#include "familyitempanel.h"
#include <QVBoxLayout>
#include <QThread>
#include "itempalette.h"
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLabel>
#include "namedicon.h"
#include "gridbagconstraints.h"
#include "QHash"
#include "QHashIterator"
#include "exceptions.h"
#include "editor.h"
#include "dataflavor.h"
#include "flowlayout.h"
#include "inputdialog.h"
#include "icondialog.h"
#include "dragjlabel.h"
#include "joptionpane.h"
#include "imagepanel.h"
#include <QButtonGroup>
#include <QListIterator>
#include "dropjlabel.h"
#include "jpanel.h"
#include "gridbaglayout.h"
#include "placewindow.h"
#include "borderfactory.h"

//FamilyItemPanel::FamilyItemPanel(QWidget *parent) :
//    ItemPanel(parent)
//{
//}
/**
*  ItemPanel for for plain icons and backgrounds
*/
// /*public*/ abstract class FamilyItemPanel extends ItemPanel {

/*protected*/ /*static*/ bool FamilyItemPanel::_suppressNamePrompts = false;

/**
 * Constructor types with multiple families and multiple icon families
 */
/*public*/ FamilyItemPanel::FamilyItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent)
    : ItemPanel(parentFrame, type, editor, parent)
{
 //super(parentFrame, type, family, editor);
 _family = family;
 log = new Logger("FamilyItemPanel");
 _currentIconMap = nullptr;
 _dragIconPanel = nullptr;
 _updateButton = new QPushButton(tr("Update Panel"));
 setObjectName("FamilyItemPanel");
 //gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
 log->setDebugEnabled(true);
}

/**
* Init for creation
* _bottom1Panel and _bottom2Panel alternate visibility in bottomPanel depending on
* whether icon families exist.  They are made first because they are referenced in
* initIconFamiliesPanel()
* subclasses will insert other panels
*/
/*public*/ void FamilyItemPanel::init()
{
 if (!_initialized)
 {
  QThread::yieldCurrentThread();
  _update = false;
  _suppressDragging = false;
  initIconFamiliesPanel();
  thisLayout->addWidget(_iconFamilyPanel);
  makeBottomPanel(nullptr);
  ItemPanel::init();
  if (log->isDebugEnabled()) {
      log->debug(tr("init done for %1, family= %2").arg(_itemType).arg(_family));
  }
 }
}

/**
* Init for update of existing track block
* _bottom3Panel has "Update Panel" button put into _bottom1Panel
*/
/*public*/ void FamilyItemPanel::init(ActionListener* doneAction, QMap<QString, NamedIcon*>* iconMap)
{
 _update = true;
 _suppressDragging = true; // no dragging when updating
 if (iconMap!=NULL)
 {
  checkCurrentMap(iconMap);   // is map in families?, does user want to add it? etc
 }
 initIconFamiliesPanel();
 thisLayout->addWidget(_iconFamilyPanel);
 makeBottomPanel(doneAction);
//    setMinimumSize(getPreferredSize());
}

/**
* Init for conversion of plain track to indicator track
* Skips init() in TableItemPanel
*/
/*public*/ void FamilyItemPanel::init(ActionListener* doneAction) {
 _update = false;
 _suppressDragging = true; // no dragging in circuitBuilder
 _bottom1Panel = new JPanel();
 addShowButtonToBottom();
 addUpdateButtonToBottom(doneAction);
 initIconFamiliesPanel();
 thisLayout->addWidget(_iconFamilyPanel);
 thisLayout->addWidget(_bottom1Panel);
}

/*protected*/ void FamilyItemPanel::makeBottomPanel(ActionListener* doneAction)
{
 _bottom2Panel = makeCreateNewFamilyPanel(); // special case for when no families exist for a given itemType
 _bottom1Panel = makeItemButtonPanel();
 if (doneAction != nullptr) {
     addUpdateButtonToBottom(doneAction);
 }
 JPanel* bottomPanel = new JPanel();
 FlowLayout* bottomPanelLayout = new FlowLayout(bottomPanel);
 bottomPanelLayout->addWidget(_bottom1Panel);
 bottomPanelLayout->addWidget(_bottom2Panel);
 // If families are missing _bottom2Panel will be made visible.
 _bottom2Panel->setVisible(false);
 thisLayout->addWidget(bottomPanel);
}

/*public*/ JPanel* FamilyItemPanel::getBottomPanel() {
    return _bottom1Panel;
}

/*public*/ QPushButton* FamilyItemPanel::getUpdateButton() {
    return _updateButton;
}

/**
 * Add [Update] button to _bottom1Panel.
 * @param doneAction Action for button
 */
/*protected*/ void FamilyItemPanel::addUpdateButtonToBottom(ActionListener* doneAction) {
    _updateButton = new QPushButton(tr("Update")); // custom update label
    //_updateButton->addActionListener(doneAction);
    connect(_updateButton, SIGNAL(clicked(bool)), doneAction, SLOT(actionPerformed(ActionEvent*)));
    _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the Panel"));
    _bottom1Panel->layout()->addWidget(_updateButton);
}
/*private*/ void FamilyItemPanel::addShowButtonToBottom() {
    _showIconsButton = new QPushButton(tr("Hide Icons"));
//    _showIconsButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            if (_iconPanel.isVisible()) {
//                hideIcons();
//            } else {
//                showIcons();
//            }
//        }
//    });
    connect(_showIconsButton, SIGNAL(clicked(bool)), this, SLOT(on_showIconsButton()));
    _showIconsButton->setToolTip(tr("Press to display the icons for the current Icon Set"));
    _bottom1Panel->layout()->addWidget(_showIconsButton);
}

void FamilyItemPanel::on_showIconsButton()
{
 if (_iconPanel->isVisible()) {
     hideIcons();
 } else {
     showIcons();
 }

}
/*protected*/ JPanel* FamilyItemPanel::makeItemButtonPanel()
{
    _bottom1Panel = new JPanel();
    _bottom1Panel->setObjectName("Bottom1Panel");
    QHBoxLayout *_bottom1PanelLayout = new QHBoxLayout(_bottom1Panel);
    addShowButtonToBottom();
    _editIconsButton = new QPushButton(tr("Edit Icons"));
//    _editIconsButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            openDialog(_itemType, _family, _currentIconMap);
//        }
//    });
    connect(_editIconsButton, SIGNAL(clicked(bool)), this, SLOT(on_editIconsButton()));
    _editIconsButton->setToolTip(tr("Press to change the icons of the current Icon Set"));
    _bottom1PanelLayout->addWidget(_editIconsButton);

    if (!_update) {
        addCreateDeleteFamilyButtons();
    }
    return _bottom1Panel;
}

void FamilyItemPanel::on_editIconsButton()
{
 openDialog(_itemType, _family, _currentIconMap);
}

/*protected*/ void FamilyItemPanel::addCreateDeleteFamilyButtons() {
    QPushButton* createIconsButton = new QPushButton(tr("Create New Family"));
//    createIconsButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            newFamilyDialog();
//        }
//    });
    connect(createIconsButton, SIGNAL(clicked(bool)), this, SLOT(newFamilyDialog()));
    createIconsButton->setToolTip(tr("Create an additional set of icons for this device"));
    ((QHBoxLayout*)_bottom1Panel->layout())->addWidget(createIconsButton);

    QPushButton* deleteButton = new QPushButton(tr("Delete Family"));
//    deleteButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            deleteFamilySet();
//       }
//    });
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteFamilySet()));
    deleteButton->setToolTip(tr("Delete this set of icons"));
    ((QHBoxLayout*)_bottom1Panel->layout())->addWidget(deleteButton);
}

/**
* iconMap is existing map of the icon.  Check whether map is one of the
* families. if so, return.  if not, does user want to add it to families?
* if so, add.  If not, save for return when updated.
*/
/*private*/ void FamilyItemPanel::checkCurrentMap(QMap<QString, NamedIcon*>* iconMap)
{
 log->debug(tr("checkCurrentMap: for type \"%1\", family \"%2\"").arg(_itemType).arg(_family));
 QMap<QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 QString family = findFamilyOfMap(iconMap, families);
 if (family != nullptr)
 {  // icons same as a known family, maybe with another name
  if (family == (_family))
  {
      return;
  }
  log->debug(tr("Icon's family \"%1\" found but is called \"%2\".  Change to Catalog name.").arg(_family).arg(family));
  _family = family;
  return;
 } else
 {    // icon set not in catalog
   _unstoredMap = iconMap;
   if (_family == "" || _family.trimmed().length() == 0)
   {
    if (_suppressNamePrompts) {
       _family = "";  // user doesn't want to be bothered
       return;
   }
   _paletteFrame->move(PlaceWindow::nextTo(_editor, nullptr, _paletteFrame));
   _family = JOptionPane::showInputDialog(_paletteFrame, tr("Icon set has no name. If you would like to name it, enter a name."),
            tr("Question"), JOptionPane::QUESTION_MESSAGE);
   }
   if (_family != "" && _family.trimmed().length() > 0)
   {
   // make sure name does not duplicate a known name
   QListIterator<QString> it(families->keys());
   while (!ItemPalette::familyNameOK(_paletteFrame, _itemType, _family, it)) {
       _family = JOptionPane::showInputDialog(_paletteFrame, tr("Enter a name for this icon set."),
               tr("Create New Icon Set for %1s").arg(_itemType), JOptionPane::QUESTION_MESSAGE);
       if (_family == "") {
           return;  // user cancelled
       }
   }
   log->debug(tr("family name \"%1\"").arg(_family));
   // name OK
   if (_suppressNamePrompts) {
       return;     // user not interested in updating catalog
   }
   int result = JOptionPane::showConfirmDialog(_paletteFrame,
           tr("Icon set \"%1\" is not known to the Palette. Do you want to add it to the icon sets?\nSelect \"No\" and no further messages will be posted.\nSelect \"Cancel\" to dismiss message and continue.").arg(_family), tr("QuestionTitle"),
           JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE);
   if (result == JOptionPane::YES_OPTION)
   {
    if (!ItemPalette::addFamily(_paletteFrame, _itemType, _family, iconMap))
    {
        JOptionPane::showMessageDialog(_paletteFrame,
                tr("\"%1\" is an invalid name for type %2.").arg(_family).arg(_itemType),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
    } else {    // icon set added to catalog with name _family
//                        _unstoredMap = null;
    }
   } else if (result == JOptionPane::NO_OPTION)
   {
       _suppressNamePrompts = true;
   }
  }
 }
}

/*protected*/ QString FamilyItemPanel::getValidFamilyName(QString family) {
    QMap<QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
    QListIterator<QString> it(families->keys());
    while (!ItemPalette::familyNameOK(_paletteFrame, _itemType, family, it)) {
        family = JOptionPane::showInputDialog(_paletteFrame, tr("Enter a name for this icon set."),
                tr("Create New Icon Set for %1s").arg(_itemType), JOptionPane::QUESTION_MESSAGE);
        if (family == "") {
            return "";  // user cancelled
        }
    }
    log->debug(tr("getValidFamilyName = \"%1\"").arg(family));
    return family;
}

/*protected*/ bool FamilyItemPanel::addFamily(QString type, QString family, QMap<QString, NamedIcon*>* iconMap) {
    if (!ItemPalette::addFamily(_paletteFrame, type, family, iconMap)) {
        JOptionPane::showMessageDialog(_paletteFrame,
                tr("\"%1\" is an invalid name for type %2.").arg(_family).arg(_itemType),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    } else {
        setIconMap(iconMap);
        setFamily(family);
        return true;
    }
}

/**
 * Find the family name of the map in a families HashMap.
 *
 * @return null if map is not in the family
 */
/*private*/ QString FamilyItemPanel::findFamilyOfMap(QMap<QString, NamedIcon*>* iconMap, QMap<QString, QMap<QString, NamedIcon*>*>* families)
{
    QMapIterator<QString, QMap<QString, NamedIcon*>*> it(*families);
    while (it.hasNext())
    {
     it.next();
     QMap<QString, NamedIcon*>* entry = it.value();
     if (log->isDebugEnabled()) {
         log->debug(tr("FamilyKey = %1").arg(it.key()));
     }
     if (mapsAreEqual(entry, iconMap))
     {
         QString family =it.key();
         log->debug(tr("Icon map found with different name \"%1\"").arg(family));
         return family;
     }
    }
    return nullptr;
}

/*protected*/ bool FamilyItemPanel::mapsAreEqual(QMap<QString, NamedIcon*>* map1, QMap<QString, NamedIcon*>* map2) {
    if (map1->size() != map2->size()) {
        return false;
    }
    QMapIterator<QString, NamedIcon*> iter(*map1);
    while (iter.hasNext()) {
        //QMap<QString, NamedIcon*>* ent = iter.next();
        NamedIcon* icon = map2->value(iter.key());
        if (icon == nullptr) {
            if (log->isDebugEnabled()) {
                log->debug(tr("key = %1, family map url= %1 item icon is null").arg(iter.key()).arg( iter.value()->getURL()));
            }
            return false;
        } else {
            if (log->isDebugEnabled()) {
                log->debug(tr("key = %1, family map url= %2 item icon url= %3").arg(iter.key()).arg( iter.value()->getURL()).arg(icon->getURL()));
            }
            QString url = icon->getURL();
            if (url == "" || url!=(iter.value()->getURL())) {
                return false;
            }
        }
    }
    return true;
}

/*protected*/ void FamilyItemPanel::initIconFamiliesPanel()
{
 if (log->isDebugEnabled()) {
     log->debug(tr("initIconFamiliesPanel for= %1, %2").arg(_itemType).arg(_family));
 }
 QMap<QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 if (families != nullptr && families->size() > 0)
 {
  if (_iconFamilyPanel == nullptr) {
      _iconFamilyPanel = new JPanel();
      _iconFamilyPanel->setLayout(new QVBoxLayout()); //_iconFamilyPanel, BoxLayout.Y_AXIS));
  }
  _familyButtonPanel = makeFamilyButtons(families->keys());
  if (_currentIconMap == nullptr)
  {
   _currentIconMap = families->value(_family);
   if (_currentIconMap == nullptr) {
       _isUnstoredMap = true;
       _currentIconMap = _unstoredMap;
   }
   else
   {
    log->debug(tr("families icon map contains:"));
    for(int i=0; i <  _currentIconMap->keys().size(); i++) {
     QString name = _currentIconMap->keys().at(i);
     log->debug(tr("  %1").arg(name));
    }
   }
  }
  // make _iconPanel & _dragIconPanel before calls to add icons
  addFamilyPanels(_familyButtonPanel);
  if (_currentIconMap == nullptr) {
      log->error("currentIconMap is null in initIconFamiliesPanel");
  } else {
      addIconsToPanel(_currentIconMap, _iconPanel, false); // need to have family iconMap identified before calling
      makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
  }
 } else {
     familiesMissing();
 }
 if (log->isDebugEnabled()) {
     log->debug(tr("initIconFamiliesPanel update=%1, family=%2").arg(_update).arg(_family));
 }
}
// override to update icons in panel
/*public*/ void FamilyItemPanel::updateFamilyIcons() {}

/*protected*/ void FamilyItemPanel::updateFamiliesPanel()
{
 if (log->isDebugEnabled()) log->debug("updateFamiliesPanel for "+_itemType);
 if (_iconFamilyPanel != nullptr)
 {
  if (_iconPanel != nullptr)
  {
//                   _iconPanel.removeAll();
   QList<QWidget*> widgets = _iconPanel->findChildren<QWidget*>();
   foreach(QWidget* widget, widgets)
   {
    _iconPanel->layout()->removeWidget(widget);
    widget->deleteLater();
   }
  }
  if (_dragIconPanel != nullptr) {
      //_dragIconPanel.removeAll();
   QList<QWidget*> widgets = _dragIconPanel->findChildren<QWidget*>();
   foreach(QWidget* widget, widgets)
   {
    _dragIconPanel->layout()->removeWidget(widget);
    widget->deleteLater();
   }
  }
  if (_familyButtonPanel != nullptr) {
   QList<QWidget*> widgets = _familyButtonPanel->findChildren<QWidget*>();
   foreach(QWidget* widget, widgets)
   {
    _familyButtonPanel->layout()->removeWidget(widget);
    widget->deleteLater();
   }
   _iconFamilyPanel->layout()->removeWidget(_familyButtonPanel);
  }
 }
 initIconFamiliesPanel();
 thisLayout->insertWidget(_buttonPosition, _iconFamilyPanel);
 hideIcons();
//    _iconFamilyPanel.invalidate();
//    invalidate();
 reset();
}

/*protected*/ JPanel* FamilyItemPanel::makeFamilyButtons (QStringList keySet)
{
 QListIterator<QString> iter(keySet);
 if (log->isDebugEnabled())
 {
  log->debug(tr("makeFamilyButtons for %1 family= %2").arg(_itemType).arg(_family));
 }
 QString thisType = "";
 JPanel* familyPanel = new JPanel(); // this is only a local object
 familyPanel->setLayout(new QVBoxLayout());//familyPanel, BoxLayout.Y_AXIS));
 // uses NamedBeanBundle property for basic beans like "Turnout" I18N
 if ("Sensor" == (_itemType)) {
     thisType = tr("Sensor");
 } else if ("Turnout" == (_itemType)) {
     thisType =  tr("Turnout");
 } else if ("SignalHead" == (_itemType)) {
     thisType =  tr("SignalHead");
 } else if ("SignalMast" == (_itemType)) {
     thisType =  tr("SignalMast");
 } else if ("Memory" == (_itemType)) {
     thisType =  tr("Memory");
 } else if ("Reporter" == (_itemType)) {
     thisType =  tr("Reporter");
 } else if ("Light" == (_itemType)) {
     thisType =  tr("Light");
 } else if ("Portal" == (_itemType)) {
     thisType =  tr("Portal");
 } else if ("RPSReporter" == (_itemType)) {
     thisType = "RPSreporter"; // adapt for slightly different spelling of Bundle key (2nd r lower case)
 } else {
     thisType = _itemType;
 }
 QString txt = tr("Icon Sets for %1:").arg(thisType);
 JPanel* p = new JPanel();
 FlowLayout* pLayout = new FlowLayout(p);
 pLayout->addWidget(new JLabel(txt));
 //pLayout.setOpaque(false);
 familyPanel->layout()->addWidget(p);
 _familyButtonGroup = new QButtonGroup();

 GridBagLayout* gridbag = new GridBagLayout();
 JPanel* buttonPanel = new JPanel();
 buttonPanel->setLayout(gridbag);

 int numCol = 4;
 GridBagConstraints c = GridBagConstraints();
 c.fill = GridBagConstraints::NONE;
 c.anchor = GridBagConstraints::CENTER;
 c.weightx = 1.0;
 c.weighty = 1.0;
 c.gridwidth = 1;
 c.gridheight = 1;
 c.gridx = 0;
 c.gridy = 0;
 QString family = "";
 QRadioButton* button = nullptr;
 while (iter.hasNext()) {
     family = iter.next();
     button = new QRadioButton(ItemPalette::convertText(family));
     addFamilyButtonListener(button, family);
     if (log->isDebugEnabled()) {
         log->debug(tr("\"%1\" ActionListener and button for family \"%2\" at gridx= %3 gridy= %4").arg(_itemType).arg(family).arg(c.gridx).arg(c.gridy));
     }
     if (family == (_family)) {
         button->setChecked(true);
     }
     //gridbag->setConstraints(button, c);
     gridbag->addWidget(button, c);
     c.gridx++;
     if (c.gridx >= numCol) { //start next row
         c.gridy++;
         c.gridx = 0;
     }
 }
 if (_currentIconMap == nullptr) {
     if (_unstoredMap !=nullptr) {
         if (_family == "") {
             _family = tr("unNamed");
         }
         _isUnstoredMap = true;
         _currentIconMap = _unstoredMap;
     } else if(_family == nullptr || _family.trimmed().length()==0) {
         _family = family; // let last family be the selected one
         if (button != nullptr) {
             button->setChecked(true);
         }
     }
 }
 if (!keySet.contains(_family)) {
     button = new QRadioButton(_family);
     addFamilyButtonListener(button, _family);
     if (log->isDebugEnabled()) {
         log->debug(tr("\"%1\" ActionListener and button for family \"%2\" at gridx= %3 gridy= %4").arg(_itemType).arg(_family).arg(c.gridx).arg(c.gridy));
     }
     //gridbag.setConstraints(button, c);
     gridbag->addWidget(button, c);
     button->setChecked(true);
     if (_unstoredMap == nullptr) {
         _unstoredMap = _currentIconMap;
         _isUnstoredMap = true;
     }
 }
 familyPanel->layout()->addWidget(buttonPanel);
 return familyPanel;
}

/*private*/ void FamilyItemPanel::addFamilyButtonListener (QRadioButton* button, QString family) {
#if 0 // TODO
        button.addActionListener(new ActionListener() {
            String fam;

            @Override
            public void actionPerformed(ActionEvent e) {
                setFamily(fam);
            }

            ActionListener init(String f) {
                fam = f;
                return this;
            }
        }.init(family));
#endif
    ButtonListener* buttonListener = new ButtonListener();
    buttonListener->init(family,this);
    connect(button, SIGNAL(clicked(bool)), buttonListener, SLOT(actionPerformed()));

    _familyButtonGroup->addButton(button);
}

/*public*/ void ButtonListener::actionPerformed() {
    self->setFamily(family);
}
ButtonListener* ButtonListener::init(QString f, FamilyItemPanel* self) {
    family = f;
    this->self = self;
    Logger* log = new Logger("ButtonListener");
    if (log->isDebugEnabled()) log->debug("ActionListener.init : for type \""+self->_itemType+"\", family \""+family+"\"");
    return this;
}
/**
 * Position secondary Preview component on _iconFamilyPanel (visible after [Show Icons]).
 * @param familyPanel panel of family buttons
 */
/*protected*/ void FamilyItemPanel::addFamilyPanels(JPanel* familyPanel) {
    if (log->isDebugEnabled()) {
        log->debug(tr("addFamilyPanels for %1").arg(_itemType));
    }
//    if (!jmri.util.ThreadingUtil.isGUIThread()) log.error("Not on GUI thread", new Exception("traceback"));
    bool makeBgBoxPanel = false;
    if (_iconPanel == nullptr) { // don't overwrite existing _iconPanel
        _iconPanel = new ImagePanel();
        FlowLayout* _iconPanelLayout;
        _iconPanel->setLayout(_iconPanelLayout = new FlowLayout());
        _iconPanel->setBorder(BorderFactory::createLineBorder(Qt::black));
        //QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
        //_iconPanel->setStyleSheet(gbStyleSheet);

        makeBgBoxPanel = true;
    }

    if (!_suppressDragging) {
        makeDragIconPanel(0);
    }
    if (makeBgBoxPanel) {
        if (!_update && !_suppressDragging) {
            _previewPanel = makePreviewPanel(_iconPanel, _dragIconPanel);
        } else {
            _previewPanel = makePreviewPanel(_iconPanel, nullptr);
            _previewPanel->setVisible(false);
        }
        _iconFamilyPanel->layout()->addWidget(_previewPanel);
    } else {
        _iconPanel->setImage(_backgrounds->at(0));
        _iconFamilyPanel->layout()->addWidget(_iconPanel);
    }
    _iconFamilyPanel->layout()->addWidget(familyPanel);
    if (_bottom1Panel != nullptr) {
        _bottom1Panel->setVisible(true);
    }
    if (_bottom2Panel != nullptr) {
        _bottom2Panel->setVisible(false);
    }
    _iconPanel->setVisible(false);
    if (log->isDebugEnabled()) {
        log->debug(tr("addFamilyPanels for %1 update=%2").arg(_family).arg(_update));
    }
}

/**
 * Position initial Preview component on _iconFamilyPanel. If already present, keep and clear it.
 * @param position Positional order of DragIconPanel on IconFamilyPanel
 */
/*protected*/ void FamilyItemPanel::makeDragIconPanel(int position) {
    if (_dragIconPanel == nullptr) {
        _dragIconPanel = new ImagePanel();
        _dragIconPanel->setObjectName("DragIconPanel");
        //_dragIconPanel.setOpaque(true); // to show background color/squares
        FlowLayout* _dragIconPanelLayout;
        _dragIconPanel->
        setLayout(_dragIconPanelLayout = new FlowLayout());
        _dragIconPanelLayout->setObjectName("FlowLayout");
        _dragIconPanel->setBorder(BorderFactory::createLineBorder(Qt::black));
        //_dragIconPanel->setStyleSheet(gbStyleSheet);
        _dragIconPanel->setToolTip(tr("Drag an icon from the Preview pane to add it to the Control Panel"));
        _iconFamilyPanel->layout()->addWidget(_dragIconPanel/*, position*/); // place icons over background
    } else {
        //_dragIconPanel.removeAll();
     QList<QWidget*> widgets = _dragIconPanel->findChildren<QWidget*>();
     foreach(QWidget* widget, widgets)
     {
      _dragIconPanel->layout()->removeWidget(widget);
      widget->deleteLater();
     }
    }
    if (_backgrounds != nullptr) {
        int previewBgSet = _paletteFrame->getPreviewBg();
        _dragIconPanel->setImage(_backgrounds->at(previewBgSet)); // pick up shared setting
        if (_iconPanel != nullptr) {
            _iconPanel->setImage(_backgrounds->at(previewBgSet)); // pick up shared setting
        }
    } else {
        log->error("FamilyItemPanel - no value for previewBgSet");
    }
    _dragIconPanel->setVisible(true);

}

/*protected*/ void FamilyItemPanel::familiesMissing() {
    int result = JOptionPane::showConfirmDialog(_paletteFrame,
            tr("All Icon sets for type %1 have been deleted.\nDo you want to restore the default sets?").arg(_itemType), tr("Question"),
            JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);
    if (result == JOptionPane::YES_OPTION) {
        ItemPalette::loadMissingItemType(_itemType, _editor);
        initIconFamiliesPanel();
        _bottom1Panel->setVisible(true);
        _bottom2Panel->setVisible(false);
    } else {
        _bottom1Panel->setVisible(false);
        _bottom2Panel->setVisible(true);
    }
}


/*protected*/ void FamilyItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* iconMap , ImagePanel* iconPanel, bool dropIcon)
{
 if (iconMap==NULL)
 {
  log->warn("iconMap is NULL for type "+_itemType+" family "+_family);
  return;
 }
 if (iconPanel == nullptr) { // bug for SignalMast icons (is of class ImagePanel)
    log->error(tr("iconPanel is null for type %1").arg(_itemType));
    return;
 }
 QGridLayout* gridbag = new QGridLayout();
 gridbag->setObjectName("gridbag");
 iconPanel->setLayout(gridbag); // QWidget::setLayout: Attempting to set QLayout "gridbag" on ImagePanel "ImagePanel", which already has a layout

 int numCol = 4;
 GridBagConstraints* c = new GridBagConstraints();
 c->fill = GridBagConstraints::NONE;
 c->anchor = GridBagConstraints::CENTER;
 c->weightx = 1.0;
 c->weighty = 1.0;
 c->gridwidth = 1;
 c->gridheight = 1;
 c->gridx = -1;
 c->gridy = 0;
 //QFontMetrics fm = fontMetrics(iconPanel->font());
 int cnt = iconMap->size();
 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  //Entry<String, NamedIcon> entry = it.next();
  it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  icon->reduceTo(100, 100, 0.2);
  JPanel*  panel = new JPanel(new FlowLayout());
  QString borderName = ItemPalette::convertText(it.key());
  panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
                                                        borderName));
  //panel->setTitle(borderName);
  panel->setToolTip(borderName);
  //panel->setStyleSheet(gbStyleSheet);
  QLabel* image;
  if (dropIcon)
  {
      image = new DropJLabel(icon, iconMap, _update);
  } else {
      image = new JLabel(icon);
  }
  image->setPixmap(QPixmap::fromImage(icon->getImage()));

  if (icon->getIconWidth()<1 || icon->getIconHeight()<1)
  {
   image->setText(tr("invisible Icon"));
//      image.setForeground(Color.lightGray);
  }
  image->setAlignment(Qt::AlignCenter);
  image->setMargin(6);

  panel->layout()->addWidget(image);
  int width = qMax(100, panel->minimumSize().width());
  panel->setMinimumSize(QSize(width, panel->minimumSize().height()));
  panel->setMaximumWidth(150);
  c->gridx += 1;
  if (c->gridx >= numCol)
  { //start next row
   c->gridy++;
   c->gridx = 0;
   if (cnt < numCol-1)
   { // last row
    QWidget*  p =  new QWidget(/*new FlowLayout()*/);
    p->setLayout(new FlowLayout);
       //p.add(Box.createHorizontalStrut(100));
       //gridbag.setConstraints(p, c);
               //if (log->isDebugEnabled()) log->debug("addIconsToPanel: gridx= "+c.gridx+" gridy= "+c.gridy);
    //_iconPanel.add(p);
    gridbag->addWidget(p, c->gridy, c->gridx,c->rowSpan(), c->colSpan());
    c->gridx = 1;
   }
  }
  cnt--;
  //gridbag.setConstraints(panel, c);
  gridbag->addWidget(panel, c->gridy, c->gridx,c->rowSpan(), c->colSpan());
 }
}

/*protected*/ QString FamilyItemPanel::getIconBorderName(QString key) {
        return ItemPalette::convertText(key);
}

/*protected*/ DragJLabel* FamilyItemPanel::getDragger(DataFlavor* /*flavor*/, QMap<QString, NamedIcon*>* /*map*/, NamedIcon* /*icon*/) {
    return nullptr;
}

/*protected*/ void FamilyItemPanel::makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString displayKey)
{
 if (_suppressDragging)
 {
  return;
 }
 _dragIconPanel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 if (iconMap!=nullptr)
 {
  if (iconMap->value(displayKey)== nullptr)
  {
   displayKey = iconMap->keys().at(0);
  }
  NamedIcon* ic = iconMap->value(displayKey);
  if (ic!=NULL)
  {
   NamedIcon* icon = new NamedIcon(ic);
   JPanel*  panel = new JPanel(new FlowLayout());
   //panel ->setLayout(new QHBoxLayout());
   QString borderName = tr("Drag to Panel");
   panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
                                                    borderName));
   //QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
   //panel->setTitle(borderName);
   //panel->setStyleSheet(gbStyleSheet);
   DragJLabel* label;
   try
   {
    label = getDragger(new DataFlavor(Editor::POSITIONABLE_FLAVOR), iconMap, icon);
    if (label != nullptr)
    {
     label->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
     // label.setIcon(icon);
     label->setName(displayKey);
     label->setOpaque(false);
     //label->setIcon(icon);
     label->setPixmap(QPixmap::fromImage(icon->getImage()));

     label->setObjectName(borderName);
     label->setAlignment(Qt::AlignCenter);
     label->setMargin(6);
     panel->layout()->addWidget(label);
    }
   } catch (ClassNotFoundException cnfe)
   {
    log->warn(tr("no DndIconPanel %1 created").arg(borderName), cnfe);
   }
   int width = qMax(100, panel->minimumSize().width());
   panel->setMinimumSize( QSize(width, panel->minimumSize().height()));
   panel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
   QLayout* l = _dragIconPanel->layout();
//   if(l == NULL)
//    _dragIconPanel->setLayout(new QHBoxLayout);
//   ((QVBoxLayout*)_dragIconPanel->layout())->addWidget(panel,0, Qt::AlignCenter);
  l->addWidget(panel);
  return;
  }
 }
 else
 {
  JOptionPane::showMessageDialog(_paletteFrame,
        tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family),
         tr("Warning"), JOptionPane::WARNING_MESSAGE);
  log->warn(tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));
 }
}



void FamilyItemPanel::on_newFamilyButton_clicked()
{
 newFamilyDialog();
}


/*protected*/ void FamilyItemPanel::hideIcons()
{
 if (_iconPanel == nullptr) {
     log->debug("hideIcons() _iconPanel = null");
     return;
 }
// if (!jmri.util.ThreadingUtil.isGUIThread()) log.error("Not on GUI thread", new Exception("traceback"));
 if (log->isDebugEnabled()) {
     log->debug(tr("hideIcons for= %1, %2").arg(_itemType).arg(_family));
 }
 bool isPalette = (qobject_cast<ItemPalette*>(_paletteFrame) != nullptr);
 QSize totalDim;
 if (isPalette) {
     totalDim = ItemPalette::_tabPane->size();
 } else {
     totalDim = _paletteFrame->size();
 }
 QSize oldDim = size();
 if (_update) {
     _previewPanel->setVisible(false);
     _previewPanel->update(); // force redraw
 }
 _iconPanel->setVisible(false);
 _iconPanel->update(); // force redraw
 if (!_suppressDragging) {
     _dragIconPanel->setVisible(true);
     _dragIconPanel->update();
 } else {
     _previewPanel->setVisible(false);
     _previewPanel->update(); // force redraw
 }
 reSizeDisplay(isPalette, oldDim, totalDim);
 _showIconsButton->setText(tr("Hide Icons"));
 reset();
}

/*protected*/ void FamilyItemPanel::showIcons() {
//    if (!jmri.util.ThreadingUtil.isGUIThread()) log.error("Not on GUI thread", new Exception("traceback"));
    if (log->isDebugEnabled()) {
        log->debug(tr("showIcons for= %1, %2").arg(_itemType).arg(_family));
    }
    bool isPalette = (qobject_cast<ItemPalette*>(_paletteFrame));
    QSize totalDim;
    if (isPalette) {
        totalDim = ItemPalette::_tabPane->size();
    } else {
        totalDim = _paletteFrame->size();
    }
    QSize oldDim = size();
    if (_update) {
        _previewPanel->setVisible(true);
        _previewPanel->update(); // force redraw
    }
    _iconPanel->setVisible(true);
    _iconPanel->update(); // force redraw
    if (!_suppressDragging) {
        _dragIconPanel->setVisible(false);
        _dragIconPanel->update();
    } else {
        _previewPanel->setVisible(true);
        _previewPanel->update(); // force redraw
    }
    reSizeDisplay(isPalette, oldDim, totalDim);
    _showIconsButton->setText(tr("Show Icons"));
    reset();
}

/**
 * Action item for deletion of an icon family.
 */
/*protected*/ void FamilyItemPanel::deleteFamilySet() {
    ItemPalette::removeIconMap(_itemType, _family);
    _family = "";
    _currentIconMap = NULL;
    updateFamiliesPanel();
}

/**
 * Replacement panel for _bottom1Panel when no icon families exist for
 * _itemType.
 */
/*private*/ QWidget* FamilyItemPanel::makeCreateNewFamilyPanel() {
    QWidget* panel = new QWidget();
    FlowLayout* panelLayout;
    panel->setLayout(panelLayout = new FlowLayout());
    QPushButton* newFamilyButton = new QPushButton(tr("New Icon Set"));
//    newFamilyButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            newFamilyDialog();
//        }
//    });
    connect(newFamilyButton, SIGNAL(clicked(bool)), this, SLOT(newFamilyDialog()));
    newFamilyButton->setToolTip(tr("Create an additional set of icons for this device"));
    panelLayout->addWidget(newFamilyButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            updateFamiliesPanel();
//        }
//    });
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(updateFamiliesPanel()));
    panelLayout->addWidget(cancelButton);
    return panel;
}

/*protected*/ bool FamilyItemPanel::newFamilyDialog() {
    QString family = JOptionPane::showInputDialog(_paletteFrame, tr("Enter a name for this icon set."), tr("Create New Icon Set for %1s").arg(_itemType), JOptionPane::QUESTION_MESSAGE);
    if (family == NULL || family.trimmed().length() == 0) {
        // bail out
        return false;
    }
    QStringListIterator iter(ItemPalette::getFamilyMaps(_itemType)->keys());
//    if (!ThreadingUtil.isGUIThread()) log.error("Not on GUI thread", new Exception("traceback"));
    while (iter.hasNext()) {
        if (family == (iter.next())) {
            JOptionPane::showMessageDialog(_paletteFrame,
                    tr("Family name \"%1\" is the name of another icon set for %2s. Please change the name.").arg(family).arg(_itemType),
                    tr("Warning"), JOptionPane::WARNING_MESSAGE);
            return false;
        }
    }
    openDialog(_itemType, family, NULL);
    return true;
}

///*protected*/ void FamilyItemPanel::openEditDialog()
//{
// if (log->isDebugEnabled()) log->debug("openEditDialog for family \""+_family+"\"");
// IconDialog* dialog = new IconDialog(_itemType, _family, this, _currentIconMap);
// // call super ItemDialog to size and locate dialog
// dialog->sizeLocate();
//}

//@Override
/*protected*/ void FamilyItemPanel::setPreviewBg(int index) {
    if (_dialog != nullptr) {
        ImagePanel* iconPanel = _dialog->getIconEditPanel();
        if (iconPanel != nullptr) {
            iconPanel->setImage((QImage*)_backgrounds->at(index));
        }
        iconPanel = _dialog->getCatalogPreviewPanel();
        if (iconPanel != nullptr) {
            iconPanel->setImage((QImage*)_backgrounds->at(index));
        }
    }
    if (_iconPanel != nullptr) {
        _iconPanel->setImage((QImage*)_backgrounds->at(index));
    }
}

//@Override
/*protected*/ void FamilyItemPanel::updateBackground0(BufferedImage* im) {
    _backgrounds->replace(0, im);
}

/*protected*/ void FamilyItemPanel::openDialog(QString type, QString family, QMap<QString, NamedIcon*>* iconMap)
{
 closeDialogs();
 _dialog = new IconDialog(type, family, this, iconMap);
 _dialog->sizeLocate();
}

//@Override
/*protected*/ void FamilyItemPanel::closeDialogs() {
    if (_dialog != nullptr) {
        _dialog->closeDialogs();
        _dialog->dispose();
    }
}
/**
* Action of family radio button
*/
/*protected*/ void FamilyItemPanel::setFamily(QString family)
{
 _family = family;
 if (log->isDebugEnabled())
   log->debug(tr("setFamily: for type \"%1\", family \"%2\"").arg(_itemType).arg(family));
 if(_iconPanel == nullptr)
 {
  _iconPanel = new ImagePanel();
  _iconFamilyPanel->layout()->addWidget(_iconPanel);
  log->error(tr("setFamily called with _iconPanel == null typs= %1").arg(_itemType));
 }
 else
 {
  //iconPanel.removeAll(); // just clear contents
  QList<QWidget*> widgets = _iconPanel->findChildren<QWidget*>();
  foreach(QWidget* widget, widgets)
  {
   _iconPanel->layout()->removeWidget(widget);
   widget->deleteLater();
  }
 }
 QMap<QString, NamedIcon*>* map = ItemPalette::getIconMap(_itemType, _family);
 if (map == nullptr) {
     map = _unstoredMap;
     _isUnstoredMap = true;
 } else {
     _isUnstoredMap = false;
 }
 if (map != nullptr) {
     _currentIconMap = map;
     if (log->isDebugEnabled())
         log->debug(tr("setFamily: %1 family \"%2\" map has %3 icons").arg(_itemType).arg(_family).arg(map->size()));
 } else {
     log->warn(tr("Family \"%1\" for type \"%2\" for not found in Catalog.").arg(_family).arg( _itemType));
 }
 if (!_suppressDragging) {
     makeDragIconPanel(0);
     makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
 }
 addIconsToPanel(_currentIconMap, _iconPanel, false);
 _iconFamilyPanel->update(); // force redraw
 hideIcons();
 setFamilyButton();
}

/*protected*/ bool FamilyItemPanel::isUnstoredMap() {
    return _isUnstoredMap;
}

/*protected*/ void FamilyItemPanel::setFamilyButton() {
    QListIterator<QAbstractButton*> en(_familyButtonGroup->buttons());
    while (en.hasNext()) {
        QRadioButton* but = (QRadioButton*) en.next();
        if (_family != "" && _family == (but->text())) {
            but->setChecked(true);
            break;
        }
    }
}

//@Override
/*protected*/ void FamilyItemPanel::setEditor(Editor* ed) {
    ItemPanel::setEditor(ed);
    if (_initialized) {
        bool visible = (_iconPanel != nullptr && _iconPanel->isVisible()); // check for invalid _initialized state
        makeDragIconPanel(0);
        makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
        if (_family != "") {
            setFamily(_family);
        }
        if (visible) {
            _showIconsButton->setText(tr("Hide Icons"));
        } else {
            _showIconsButton->setText(tr("Show Icons"));
        }
    }
}

/*protected*/ void FamilyItemPanel::setIconMap(QMap<QString, NamedIcon*>* map) {
    _currentIconMap = map;
    if (_isUnstoredMap) {
        _unstoredMap = map;
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("setIconMap: for %1 \"%2\" _isUnstoredMap=%3").arg(_itemType).arg(_family).arg( _isUnstoredMap?"true":"false"));
    }
    updateFamiliesPanel();
}
/**
 * return icon set to panel icon display class
 * @return updating map
 */
/*public*/ QMap<QString, NamedIcon*>* FamilyItemPanel::getIconMap()
{
 if (_currentIconMap==NULL)
 {
  _currentIconMap = ItemPalette::getIconMap(_itemType, _family);
  if (_currentIconMap==NULL)
  {
//   JOptionPane.showMessageDialog(_paletteFrame,
//                    java.text.MessageFormat.format(ItemPalette.rbp.getString("FamilyNotFound"),
//                                                   ItemPalette.rbp.getString(_itemType), _family),
//                 ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(_paletteFrame, tr("Warning"), tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));
  }
 }
 return _currentIconMap;
}

/*public*/ QString FamilyItemPanel::getFamilyName() {
       return _family;
   }
