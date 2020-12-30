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
#include <QFontMetrics>
#include "catalogpanel.h"
#include "previewpanel.h"
#include "box.h"

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
 setObjectName("FamilyItemPanel");
 log = new Logger("FamilyItemPanel");
 log->setDebugEnabled(true);

 _family = family;

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

  makeBottomPanel(nullptr);
  ItemPanel::init();
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
 _initialized = true;
}

/*protected*/ void FamilyItemPanel::makeBottomPanel(ActionListener* doneAction)
{
 _bottom2Panel = makeCreateNewFamilyPanel(); // special case for when no families exist for a given itemType
  makeItemButtonPanel();
 if (doneAction != nullptr) {
     addUpdateButtonToBottom(doneAction);
 }
 initIconFamiliesPanel();
 layout()->addWidget(_iconFamilyPanel);
 JPanel* bottomPanel = new JPanel();
 FlowLayout* bottomPanelLayout = new FlowLayout(bottomPanel);
 if(_bottom1Panel) bottomPanelLayout->addWidget(_bottom1Panel);
 bottomPanelLayout->addWidget(_bottom2Panel);
 thisLayout->addWidget(bottomPanel);
 if (log->isDebugEnabled()) {
  log->debug("init done for family " + _family);
 }
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
    connect(_updateButton, SIGNAL(clicked(bool)), doneAction, SLOT(actionPerformed(JActionEvent*)));
    _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the Panel"));
    _bottom1Panel->layout()->addWidget(_updateButton);
}
/*private*/ void FamilyItemPanel::addShowButtonToBottom() {
    _showIconsButton = new QPushButton(tr("Show Icons"));
//    _showIconsButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
    connect(_showIconsButton, &QPushButton::clicked, [=]{
            if (_iconPanel->isVisible()) {
                hideIcons();
            } else {
                showIcons();
            }
//        }
    });
    _showIconsButton->setToolTip(tr("Press to display the icons for the current Icon Set"));
    _bottom1Panel->layout()->addWidget(_showIconsButton);
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
    connect(_editIconsButton, &QPushButton::clicked, [=]{
            openEditDialog();
//        }
    });
//    connect(_editIconsButton, SIGNAL(clicked(bool)), this, SLOT(on_editIconsButton()));
    _editIconsButton->setToolTip(tr("Press to change the icons of the current Icon Set"));
    _bottom1PanelLayout->addWidget(_editIconsButton);

    if (!_update) {
        addCreateDeleteFamilyButtons();
    }
    return _bottom1Panel;
}

//void FamilyItemPanel::on_editIconsButton()
//{
// openDialog(_itemType, _family, _currentIconMap);
//}

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
    _bottom1Panel->layout()->addWidget(createIconsButton);

    QPushButton* deleteButton = new QPushButton(tr("Delete Family"));
//    deleteButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            deleteFamilySet();
//       }
//    });
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteFamilySet()));
    deleteButton->setToolTip(tr("Delete this set of icons"));
    _bottom1Panel->layout()->addWidget(deleteButton);
}

/**
* iconMap is existing map of the icon.  Check whether map is one of the
* families. if so, return.  if not, does user want to add it to families?
* if so, add.  If not, save for return when updated.
*/
/*private*/ void FamilyItemPanel::checkCurrentMap(QMap<QString, NamedIcon*>* iconMap)
{
 if (log->isDebugEnabled()) {
     log->debug("checkCurrentMap: for type \"" + _itemType + "\", family \"" + _family + "\"");
 }
 QString family = findFamilyOfMap(iconMap, ItemPalette::getFamilyMaps(_itemType));
 if (!family.isNull()) {		// icons same as a known family, maybe with another name
     _family = family;
     return;
 } else {	// no match with Palette families
     if (ItemPalette::getIconMap(_itemType, _family) != nullptr) {
//                JOptionPane.showMessageDialog(_paletteFrame,
//                        Bundle.getMessage("DuplicateFamilyName", _family, _itemType),
//                        Bundle.getMessage("warnTitle"), JOptionPane.WARNING_MESSAGE);
         // make sure name does not duplicate a known name
         _family = QString();
     }
 }
 if (!_suppressNamePrompts) {
     if (_family == "" || _family.trimmed().length() == 0) {
         _family = JOptionPane::showInputDialog(_paletteFrame, tr("Icon set has no name.  If you would like to name it, enter a name."),
                 tr("Question"), JOptionPane::QUESTION_MESSAGE);
         if (_family.isNull() || _family.trimmed().length() == 0) {
             // bail out
             _family = "";
//    	        	_suppressNamePrompts = true;
             return;
         }
     }
     int result = JOptionPane::showConfirmDialog(_paletteFrame,
             tr("Icon set \"%1\" is not known to the Palette.  Do you want to add it to the icon sets?\nSelect \"No\" and no further messages will be posted.").arg(_family), tr("Question"),
             JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE);
     if (result == JOptionPane::YES_OPTION) {
         ItemPalette::addFamily(_paletteFrame, _itemType, _family, iconMap);
     } else if (result == JOptionPane::NO_OPTION) {
         _suppressNamePrompts = true;
     }
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
    return QString();
}

/*protected*/ bool FamilyItemPanel::mapsAreEqual(QMap<QString, NamedIcon*>* map1,
                                                 QMap<QString, NamedIcon*>* map2)
{
 if (map1->size() != map2->size()) {
     return false;
 }
 QMapIterator<QString, NamedIcon*> iter(*map1);
 while (iter.hasNext())
 {
  /*Entry<String, NamedIcon> ent =*/ iter.next();
  NamedIcon* icon = map2->value(iter.key());
  if (log->isDebugEnabled()) {
      log->debug(tr("key= ") + iter.key()
              + ", url1= " + icon->getURL() + ", url2= " + iter.value()->getURL());
  }
  if (icon == nullptr || icon->getURL() != (iter.value()->getURL())) {
      return false;
  }
 }
 return true;
}

/*protected*/ void FamilyItemPanel::initIconFamiliesPanel() {
 QMap<QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 if (families != nullptr && families->size() > 0)
 {
     _iconFamilyPanel = new JPanel();
     _iconFamilyPanel->setObjectName("_iconFamilyPanel");
     _iconFamilyPanel->setLayout(new QVBoxLayout());//_iconFamilyPanel, BoxLayout.Y_AXIS));
     JPanel* familyPanel = makeFamilyButtons(QStringListIterator(families->keys()), (_currentIconMap == nullptr));
     familyPanel->setObjectName("familyPanel");
     if (_currentIconMap == nullptr) {
         _currentIconMap = families->value(_family);
     }
     // make _iconPanel & _dragIconPanel before calls to add icons
     addFamilyPanels(familyPanel);
     if (_currentIconMap == nullptr) {
         log->error("currentIconMap is null in initIconFamiliesPanel");
     } else {
         addIconsToPanel(_currentIconMap);        // need to have family iconMap identified before calling
         makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
     }
 } else {
     familiesMissing();
 }
}

/*protected*/ void FamilyItemPanel::updateFamiliesPanel()
{
 if (log->isDebugEnabled()) {
     log->debug("updateFamiliesPanel for " + _itemType);
 }
 if (_iconFamilyPanel != nullptr) {
     removeIconFamiliesPanel();
 }
 initIconFamiliesPanel();
 //layout()->addWidget(_iconFamilyPanel/*, _buttonPostion*/);
 thisLayout->insertWidget(_buttonPosition, _iconFamilyPanel);
 hideIcons();
 _iconFamilyPanel->update();
 update();
 reset();
}

/*
 * Set actions of radioButtons to change family
 */
/*protected*/ JPanel* FamilyItemPanel::makeFamilyButtons(QStringListIterator it, bool setDefault) {
    JPanel* familyPanel = new JPanel();
    familyPanel->setLayout(new QVBoxLayout());//familyPanel, BoxLayout.Y_AXIS));
    QString txt = tr("Icon Sets for %1").arg(_itemType);
    JPanel* p = new JPanel(new FlowLayout());
    p->layout()->addWidget(new JLabel(txt));
    familyPanel->layout()->addWidget(p);
    _familyButtonGroup = new QButtonGroup();
    JPanel* buttonPanel = new JPanel(new FlowLayout());
    QString family = QString();
    QRadioButton* button = nullptr;
    int count = 0;
    while (it.hasNext()) {
        family = it.next();
        count++;
        button = new QRadioButton(ItemPalette::convertText(family));
//        button.addActionListener(new ActionListener() {
//            String fam;

//            public void actionPerformed(ActionEvent e) {
        connect(button, &QRadioButton::clicked, [=]{
                setFamily(family);
            });

//            ActionListener init(String f) {
//                fam = f;
//                if (log.isDebugEnabled()) {
//                    log.debug("ActionListener.init : for type \"" + _itemType + "\", family \"" + fam + "\"");
//                }
//                return this;
//            }
//        }.init(family));
        if (family == (_family)) {
            button->setChecked(true);
        }
        if (count > 4) {
            count = 0;
            familyPanel->layout()->addWidget(buttonPanel);
            buttonPanel = new JPanel(new FlowLayout());
            buttonPanel->setLayout(new FlowLayout());  //new BoxLayout(p, BoxLayout.Y_AXIS)
        }
        buttonPanel->layout()->addWidget(button);
        _familyButtonGroup->addButton(button);
    }
    familyPanel->layout()->addWidget(buttonPanel);
    if (_family != family && setDefault) {
        _family = family;       // let last family be the selected one
        if (button != nullptr) {
            button->setChecked(true);
        } else {
            log->warn("null button after setting family");
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
 _iconPanel = new JPanel(new FlowLayout());
 _iconPanel->setObjectName("_iconPanel");
 _iconFamilyPanel->layout()->addWidget(_iconPanel);
 _iconPanel->setVisible(false);
 if (!_supressDragging) {
     _dragIconPanel = new JPanel(new FlowLayout());
     _dragIconPanel->setObjectName("_dragIconPanel");
     _iconFamilyPanel->layout()->addWidget(_dragIconPanel);
     _dragIconPanel->setVisible(true);
 }
 _iconFamilyPanel->layout()->addWidget(familyPanel);
 if (_bottom1Panel != nullptr) {
     _bottom1Panel->setVisible(true);
 }
 if (_bottom2Panel != nullptr) {
     _bottom2Panel->setVisible(false);
 }
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


/*protected*/ void FamilyItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* iconMap) {
 if (iconMap == nullptr) {
     log->warn("iconMap is null for type " + _itemType + " family " + _family);
     return;
 }
 GridBagLayout* gridbag = new GridBagLayout();
 if(_iconPanel->layout())
  delete _iconPanel->layout();
 _iconPanel->setLayout(gridbag);

 int numCol = 4;
 GridBagConstraints c = GridBagConstraints();
 c.fill = GridBagConstraints::NONE;
 c.anchor = GridBagConstraints::CENTER;
 c.weightx = 1.0;
 c.weighty = 1.0;
 c.gridwidth = 1;
 c.gridheight = 1;
 c.gridx = -1;
 c.gridy = 0;

 int cnt = iconMap->size();
 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext()) {
     /*Entry<String, NamedIcon> entry =*/ it.next();
     NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
     icon->reduceTo(100, 100, 0.2);
     JPanel* panel = new JPanel(new FlowLayout());
     QString borderName = getIconBorderName(it.key());
     panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
             borderName));
     JLabel* image = new JLabel(icon);
     if (icon->getIconWidth() < 1 || icon->getIconHeight() < 1) {
         image->setText(tr("invisible Icon"));
         image->setForeground(Qt::lightGray);
     }
     image->setToolTip(icon->getName());
     panel->layout()->addWidget(image);
     int width = qMax(100, panel->sizeHint().width());
     panel->resize(QSize(width, panel->sizeHint().height()));
     c.gridx += 1;
     if (c.gridx >= numCol) { //start next row
         c.gridy++;
         c.gridx = 0;
         if (cnt < numCol - 1) { // last row
             JPanel* p = new JPanel(new FlowLayout());
             p->setLayout(new QHBoxLayout());//p, BoxLayout.X_AXIS));
             p->layout()->addWidget(Box::createHorizontalStrut(100));
             //gridbag->setConstraints(/*p, */c);
             //if (log.isDebugEnabled()) log.debug("addIconsToPanel: gridx= "+c.gridx+" gridy= "+c.gridy);
             ((GridBagLayout*)_iconPanel->layout())->addWidget(p, c);
             c.gridx = 1;
         }
     }
     cnt--;
     //gridbag->setConstraints(/*panel,*/ c);
     ((GridBagLayout*)_iconPanel->layout())->addWidget(panel,c);
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
 _dragIconPanel->setToolTip(tr("Drag an icon from the Catalog to replace an icon in the item group"));
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
   try
   {
    JLabel* label = getDragger(new DataFlavor(Editor::POSITIONABLE_FLAVOR), iconMap, icon);
    if (label != nullptr)
    {
     label->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
     // label.setIcon(icon);
     label->setName(displayKey);
     label->setOpaque(false);
     label->setIcon(icon);
     label->setPixmap(QPixmap::fromImage(icon->getImage()));

     //label->setObjectName(borderName);
     label->setAlignment(Qt::AlignCenter);
     label->setMargin(6);
     JPanel* panel = makeDragIcon(icon, label);
     if(_dragIconPanel->layout()== nullptr)
      _dragIconPanel->setLayout(new FlowLayout());
     _dragIconPanel->layout()->addWidget(panel);
    }
   } catch (ClassNotFoundException cnfe)
   {
    log->warn(tr("no DndIconPanel for %1, %2 created. %3").arg(_itemType).arg(displayKey).arg(cnfe.getMessage()));
   }

  }
 }
 else
 {
  log->error(tr("No iconMap for makeDndIconPanel of %1").arg(_itemType));
 }
}

/*protected*/ JPanel* FamilyItemPanel::makeDragIcon(NamedIcon* icon, JLabel* label) {
    JPanel* panel = new JPanel(new QHBoxLayout());
    QString borderName = tr("Drag to Pane     "); //ItemPalette.convertText("dragToPanel");
    panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
            borderName));
    panel->setToolTip(tr("Drag an icon from the Preview pane to add it to the Control Panel"));
    panel->setOpaque(false);
    if (label != nullptr) {
        label->setToolTip(tr("Drag an icon from the Preview pane to add it to the Control Panel"));
        label->setIcon(icon);
        label->setName(borderName);
        label->setOpaque(false);
        panel->layout()->addWidget(label);
    }
    QFontMetrics fm(panel->font());
    int width = fm.size(Qt::TextSingleLine, borderName).width();
    width = qMax(CatalogPanel::ICON_WIDTH, qMax(width, icon->getIconWidth())+10);
    //panel->resize(QSize(width, panel->sizeHint().height()));
    panel->setMinimumWidth(width);
    return panel;
}

/*protected*/ void FamilyItemPanel::hideIcons()
{
 if (_iconPanel == nullptr) {
      return;
  }
  _iconPanel->setVisible(false);
  if (!_supressDragging) {
      _dragIconPanel->setVisible(true);
      _dragIconPanel->update();
  }
  _showIconsButton->setText(tr("Show Icons"));
  reset();
  closeDialogs();
}

/*protected*/ void FamilyItemPanel::showIcons() {
 _iconPanel->setVisible(true);
 _iconPanel->update();
 if (!_supressDragging) {
     _dragIconPanel->setVisible(false);
 }
 _showIconsButton->setText(tr("Hide Icons"));
 reset();
 closeDialogs();
}

/**
 * Action item for deletion of an icon family.
 */
/*protected*/ void FamilyItemPanel::deleteFamilySet() {
 ItemPalette::removeIconMap(_itemType, _family);
 _family = QString();
 _currentIconMap = nullptr;
 updateFamiliesPanel();
}

/**
 * Replacement panel for _bottom1Panel when no icon families exist for
 * _itemType.
 */
/*private*/ JPanel* FamilyItemPanel::makeCreateNewFamilyPanel() {
    JPanel* panel = new JPanel();
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
    if (family.isNull() || family.trimmed().length() == 0) {
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

/*private*/ void FamilyItemPanel::openEditDialog() {
    _dialog = openDialog(_itemType, _family, _currentIconMap);
}

/*protected*/ IconDialog* FamilyItemPanel::openDialog(QString type, QString family, QMap<QString, NamedIcon*>* iconMap)
{
 IconDialog* dialog = new IconDialog(type, family, this, iconMap);
 dialog->sizeLocate();
 return dialog;
}

//@Override
/*public*/ void FamilyItemPanel::closeDialogs() {
    if (_dialog != nullptr) {
        _dialog->closeDialogs();
        _dialog->dispose();
        _dialog = nullptr;
    }
}

/*public*/ void FamilyItemPanel::dispose() {
    closeDialogs();
}

/*protected*/ void FamilyItemPanel::removeIconFamiliesPanel() {
    layout()->removeWidget(_iconFamilyPanel);

    QList<QWidget*> widgets = _iconFamilyPanel->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly);
    //foreach(QWidget* widget, widgets)
    for(int i= widgets.size()-1; i >= 0; i--)
    {
     QWidget* widget = widgets.at(i);
//     _iconFamilyPanel->layout()->removeWidget(widget);
//     widget->deleteLater();
     delete widget;
    }
    delete _iconFamilyPanel; //->layout();
    _iconFamilyPanel = nullptr;
}

/**
* Action of family radio button
*/
/*protected*/ void FamilyItemPanel::setFamily(QString family)
{
 _family = family;
 if (log->isDebugEnabled()) {
     log->debug("setFamily: for type \"" + _itemType + "\", family \"" + family + "\"");
 }
 _iconFamilyPanel->layout()->removeWidget(_iconPanel);
  delete _iconPanel;
  _iconPanel = new JPanel(new FlowLayout());
 ((QVBoxLayout*)_iconFamilyPanel->layout())->insertWidget(0, _iconPanel);
 QMap<QString, NamedIcon*>* map = ItemPalette::getIconMap(_itemType, _family);
 if (map != nullptr) {
     _currentIconMap = map;
 }
 if (!_supressDragging) {
     _iconFamilyPanel->layout()->removeWidget(_dragIconPanel);
     delete _dragIconPanel;
     _dragIconPanel = new JPanel(new FlowLayout());
     ((QVBoxLayout*)_iconFamilyPanel->layout())->insertWidget(0,_dragIconPanel);
     makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
 }
 addIconsToPanel(_currentIconMap);
 _iconFamilyPanel->update();
 hideIcons();
 //Enumeration<AbstractButton> en = _familyButtonGroup.getElements();
 QListIterator<QAbstractButton*> en(_familyButtonGroup->buttons());
 while (en.hasNext()) {
     QRadioButton* but = (QRadioButton*) en.next();
     if (_family != nullptr && _family == (but->text())) {
         but->setChecked(true);
         break;
     }
 }
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

/**
 * return icon set to panel icon display class
 * @return updating map
 */
/*public*/ QMap<QString, NamedIcon*>* FamilyItemPanel::getIconMap()
{
 if (_currentIconMap==NULL)
 {
  _currentIconMap = ItemPalette::getIconMap(_itemType, _family);
 }
 return _currentIconMap;
}

/*public*/ QString FamilyItemPanel::getFamilyName() {
    return _family;
}
