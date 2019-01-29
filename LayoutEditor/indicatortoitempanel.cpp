#include "indicatortoitempanel.h"
#include "borderlayout.h"
#include "itempalette.h"
#include <QMessageBox>
#include "detectionpanel.h"
#include "indicatorturnouticon.h"
#include "gridbagconstraints.h"
#include "jtextfield.h"
#include "flowlayout.h"
#include "namedicon.h"
#include "editor.h"
#include <QGroupBox>
#include "dataflavor.h"
#include "indicatorturnouticonxml.h"
#include "manager.h"
#include "imagepanel.h"

//IndicatorTOItemPanel::IndicatorTOItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
/**
*  QWidgets for the various item types that come from tool Tables - e.g. Sensors, Turnouts, etc.
*/
///*public*/ class IndicatorTOItemPanel extends TableItemPanel {

/*final*/ /*static*/ QStringList IndicatorTOItemPanel::STATUS_KEYS = QStringList() << "ClearTrack"<< "OccupiedTrack"<< "PositionTrack" <<
                            "AllocatedTrack"<< "DontUseTrack"<< "ErrorTrack";


/**
* Constructor for all table types.  When item is a bean, the itemType is the name  key
 * for the item in jmri.NamedBeanBundle.properties
 */
/*public*/ IndicatorTOItemPanel::IndicatorTOItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, QWidget *parent) : TableItemPanel(parentFrame, type, family, model, editor, parent)
{
    //super(parentFrame, type, family, model, editor);
 log = new Logger("IndicatorTOItemPanel");
 _iconGroupsMap = NULL;
 _updateGroupsMap = NULL;
 _tablePanel = NULL;
 _detectPanel = NULL;
 setObjectName("IndicatorTOItemPanel");
}

/**
* Init for creation
* _bottom1Panel and _bottom2Panel alternate visibility in bottomPanel depending on
* whether icon families exist.  They are made first because they are referenced in
* initIconFamiliesPanel()
*/
/*public*/ void IndicatorTOItemPanel::init()
{
  TableItemPanel::init();
  _detectPanel= new DetectionPanel(this);
  thisLayout->insertWidget(1,_detectPanel);
  thisLayout->insertWidget(2,_iconFamilyPanel);
}

/**
* Init for conversion of plain track to indicator track
*/
/*public*/ void IndicatorTOItemPanel::init(ActionListener* doneAction)
{
 FamilyItemPanel::init(doneAction);
 thisLayout->insertWidget(0,_iconFamilyPanel);
}

/**
* Init for update of existing indicator turnout
* _bottom3Panel has "Update Panel" button put into _bottom1Panel
*/
/*public*/ void IndicatorTOItemPanel::initUpdate(ActionListener* doneAction, QMap<QString, QMap<QString, NamedIcon*>*>* iconMaps)
{
 checkCurrentMaps(iconMaps);   // is map in families?, does user want to add it? etc
 TableItemPanel::init(doneAction, NULL);
 _detectPanel= new DetectionPanel(this);

 //thisLayout->addWidget(_detectPanel/*, 1*/,0, Qt::AlignCenter);
 thisLayout->insertWidget(1,_detectPanel);
 //thisLayout->addWidget(_iconFamilyPanel/*, 2*/,0, Qt::AlignBottom);
 thisLayout->insertWidget(2,_iconFamilyPanel);
}

/**
* iconMap is existing map of the icon.  Check whether map is one of the
* families. if so, return.  if not, does user want to add it to families?
* if so, add.  If not, save for return when updated.
*/
/*private*/ void IndicatorTOItemPanel::checkCurrentMaps(QMap<QString, QMap<QString, NamedIcon*>*>* iconMaps)
{
 _updateGroupsMap = iconMaps;
 if (_family!=NULL && _family.trimmed().length()>0)
 {
  QMap<QString, QMap<QString, NamedIcon*>*>* map = ItemPalette::getLevel4FamilyMaps(_itemType)->value(_family);
  if (map!=NULL)
  {
   return;     // Must assume no family names were changed
  }
 }
//    int result = JOptionPane.showConfirmDialog(_paletteFrame,tr("NoFamilyName"),
//            ItemPalette.rb.getString("questionTitle"), JOptionPane.YES_NO_OPTION,
//            JOptionPane.QUESTION_MESSAGE);
//    if (result==JOptionPane.NO_OPTION)
 int result = QMessageBox::question(_paletteFrame, tr("Question"), tr("This icon set is not known to the Palette.  Do you want to save it?"),QMessageBox::Yes | QMessageBox::No);
 if(result == QMessageBox::No)
 {
  return;
 }
 if (_family!=NULL && _family.trimmed().length()>0)
 {
  if (ItemPalette::addLevel4Family(_paletteFrame, _itemType, _family, iconMaps))
  {
   return;
  }
 }
 do
 {
//        _family = JOptionPane.showInputDialog(_paletteFrame, tr("EnterFamilyName"),
//                ItemPalette.rb.getString("questionTitle"), JOptionPane.QUESTION_MESSAGE);
  QMessageBox::question(_paletteFrame, tr("Question"), tr("Enter a name for this icon set."));
  if (_family==NULL || _family.trimmed().length()==0)
  {
   // bail out
   return;
  }
 } while (!ItemPalette::addLevel4Family(_paletteFrame, _itemType, _family, iconMaps));
}

/*
* Get a handle in order to change visibility
*/
/*protected*/ QWidget* IndicatorTOItemPanel::initTablePanel(PickListModel* model, Editor* editor, QWidget */*parent*/) {
    _tablePanel = TableItemPanel::initTablePanel(model, editor);
    return _tablePanel;
}

/*public*/ void IndicatorTOItemPanel::dispose() {
    if (_detectPanel!=NULL) {
        _detectPanel->dispose();
    }
}

/**
*  CENTER Panel
*/
/*protected*/ void IndicatorTOItemPanel::initIconFamiliesPanel()
{
 _iconFamilyPanel = new QWidget();
 QVBoxLayout* iconFamilyPanelLayout;
 _iconFamilyPanel->setLayout(iconFamilyPanelLayout = new QVBoxLayout); //(_iconFamilyPanel/*, BoxLayout.Y_AXIS*/));

 QMap <QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* families =
                        ItemPalette::getLevel4FamilyMaps(_itemType);
 if (families!=NULL && families->size()>0)
 {
  _familyButtonPanel = makeFamilyButtons(families->keys());

  if (_iconGroupsMap == nullptr)
  {
      _iconGroupsMap = families->value(_family);
  }
  // make _iconPanel + _dragIconPanel before calls to add icons
  addFamilyPanels(_familyButtonPanel);

  if (_iconGroupsMap == nullptr)
  {
      log->error("_iconGroupsMap is null in initIconFamiliesPanel");
      _family = nullptr;
  } else {
      addIcons2Panel(_iconGroupsMap); // need to have family iconMap identified before calling
      makeDndIconPanel(_iconGroupsMap->value("ClearTrack"), "TurnoutStateClosed");
  }
 } else {
     familiesMissing();
 }
//        updateBackgrounds(); // create array of backgrounds
 log->debug("initIconFamiliesPanel done");
}

///*protected*/ void IndicatorTOItemPanel::updateFamiliesPanel()
//{
// _iconFamilyPanel->layout()->removeWidget(_iconPanel);
// _iconPanel = new QWidget();
//    addIcons2Panel(_iconGroupsMap);
//    ((QVBoxLayout*)_iconFamilyPanel->layout())->addWidget(_iconPanel/*, 0*/);
//    _iconPanel->setVisible(true);
//    reset();
//}

/*protected*/ void IndicatorTOItemPanel::resetFamiliesPanel() {
    layout()->removeWidget(_iconFamilyPanel);
    initIconFamiliesPanel();
    int n = _iconFamilyPanel->layout()->children().count();
    if (n>2) {
        layout()->addWidget(_iconFamilyPanel/*, 2*/);
    } else {
        layout()->addWidget(_iconFamilyPanel/*, 0*/);
    }
    reset();
}

/**
* Make matrix of icons - each row has a button to change icons
*/
/*protected*/ void IndicatorTOItemPanel::addIcons2Panel(QMap<QString, QMap<QString, NamedIcon*>*>* map) {
    QGridLayout* gridbag = new QGridLayout();
    _iconPanel->setLayout(gridbag);

    GridBagConstraints c;// =  GridBagConstraints();
    c.fill = GridBagConstraints::NONE;
    c.anchor = GridBagConstraints::CENTER;
    c.weightx = 1.0;
    c.weighty = 1.0;
    c.gridwidth = 1;
    c.gridheight = 1;
    c.gridy = -1;
    //Iterator<Entry<String, Hashtable<String, NamedIcon>>> it = map.entrySet().iterator();
    QMapIterator<QString, QMap<QString, NamedIcon*>*> it(*map);
    while (it.hasNext()) {
        c.gridx = 0;
        c.gridy++;

        //QHash<QString, NamedIcon*>* entry = it.next();
        it.next();
        QString stateName = it.key();
        QWidget* panel = new QWidget();
        panel->setLayout(new QHBoxLayout);
        panel->layout()->addWidget(new QLabel(ItemPalette::convertText(stateName)));
        //gridbag.setConstraints(panel, c);
        //_iconPanel->layout()->addWidget(panel);
        gridbag->addWidget(panel, c.gridy, c.gridx, 1,1);
        c.gridx++;
        QMap<QString, NamedIcon*>* iconMap = it.value();
        QMapIterator<QString, NamedIcon*> iter(* iconMap);
        QGroupBox* panel1;
        QString  gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
        while(iter.hasNext())
        {
            //QHash<QString, NamedIcon*> ent = iter->next();
            iter.next();
            QString borderName = ItemPalette::convertText(iter.key());
            NamedIcon* icon = new NamedIcon(iter.value());    // make copy for possible reduction
            icon->reduceTo(100, 100, 0.2);
            panel1 = new QGroupBox();
            panel1->setLayout(new QHBoxLayout);
            panel1->setStyleSheet(gbStyleSheet);
            panel1->setTitle(borderName);
//            panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
//                                                             borderName));
            //if (log-> isDebugEnabled()) log-> debug("addIcons2Panel: "+borderName+" icon at ("
            //                                    +c.gridx+","+c.gridy+") width= "+icon.getIconWidth()+
            //                                    " height= "+icon.getIconHeight());
            JLabel* image = new JLabel("", icon, 0);
            if (icon->getIconWidth()<1 || icon->getIconHeight()<1) {
                image->setText(tr("invisibleIcon"));
//                image->setForeground(QColor(Qt::lightGray));
            }
            panel1->layout()->addWidget(image);
            image->setAlignment(Qt::AlignCenter);
            image->setMargin(6);
            int width = qMax(85, panel->sizeHint().width());
            panel1->resize(QSize(width, panel->sizeHint().height()));
//            gridbag.setConstraints(panel, c);
//            _iconPanel->layout()->addWidget(panel);
            gridbag->addWidget(panel1, c.gridy, c.gridx, 1,1);
            c.gridx++;
        }
        panel = new QWidget();
        panel->setLayout(new QHBoxLayout);
        QPushButton* button = new QPushButton(tr("Edit Icons"));
//        button.addActionListener(new ActionListener() {
//                String key;
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    openEditDialog(key);
//                }
//                ActionListener init(String k) {
//                    key = k;
//                    return this;
//                }
//        }.init(stateName));
        EditIconActionListener* eal = new EditIconActionListener();
        eal->init(stateName, this);
        connect(button, SIGNAL(clicked()), eal, SLOT(actionPerformed()));
        button->setToolTip(tr("Press to change the icons of the current icon set or to add and delete icon sets"));
        panel->layout()->addWidget(button);
//        gridbag.setConstraints(panel, c);
//        _iconPanel->layout()->addWidget(panel);
        gridbag->addWidget(panel, c.gridy, c.gridx, 1,1);
        //if (log-> isDebugEnabled()) log-> debug("addIcons2Panel: row "+c.gridy+" has "+iconMap.size()+" icons");
    }
}
void EditIconActionListener::actionPerformed(ActionEvent */*a*/)
{
    parent->openEditDialog(key);
}

void  EditIconActionListener::init(QString k, IndicatorTOItemPanel *parent)
{
 key = k;
 this->parent = parent;
}

/*protected*/ QWidget* IndicatorTOItemPanel::makeBottom2Panel()
{
 QWidget* buttonPanel = new QWidget();
 QVBoxLayout* buttonPanelLayout;
 buttonPanel->setLayout(buttonPanelLayout = new QVBoxLayout); //(buttonPanel/*, BoxLayout.Y_AXIS*/));
 _familyName = new JTextField();
 buttonPanelLayout->addWidget(ItemPalette::makeBannerPanel("IconSetName", _familyName));
//    QWidget* panel = new QWidget();
//    panel->setLayout(new FlowLayout());
 FlowLayout* panelLayout = new FlowLayout;
 QPushButton* newFamilyButton = new QPushButton(tr("createNewFamily"));
//    newFamilyButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                //check text
//                String family = _familyName.getText();
//                if (ItemPalette.addLevel4Family(_paletteFrame, _itemType, family, _iconGroupsMap)) {
//                    _family = family;
//                    resetFamiliesPanel();
//                    setFamily(family);
//                }
//            }
//        });
 connect(newFamilyButton, SIGNAL(clicked()), this, SLOT(onNewFamilyButton()));
 newFamilyButton->setToolTip(tr("Create an additonal set of icons for this device"));
 panelLayout->addWidget(newFamilyButton);

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                resetFamiliesPanel();
//            }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(resetFamiliesPanel()));
 panelLayout->addWidget(cancelButton);
 buttonPanelLayout->addLayout(panelLayout);
 return buttonPanel;
}
void IndicatorTOItemPanel::onNewFamilyButton()
{
 //check text
 QString family = _familyName->text().trimmed();
 if (ItemPalette::addLevel4Family(_paletteFrame, _itemType, family, _iconGroupsMap))
 {
  _family = family;
  resetFamiliesPanel();
  setFamily(family);
 }
}

/*protected*/ QWidget* IndicatorTOItemPanel::makeBottom1Panel()
{
 QWidget* buttonPanel = new QWidget();
 QVBoxLayout* buttonPanelLayout;
 buttonPanel->setLayout(buttonPanelLayout = new QVBoxLayout);
 QHBoxLayout* panel1Layout;
 QWidget* panel1 = new QWidget();
 panel1->setLayout(panel1Layout = new QHBoxLayout());
 QPushButton* addFamilyButton = new QPushButton(tr("Add New Icon Set"));
//    addFamilyButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                createNewFamily();
//            }
//        });
 connect(addFamilyButton, SIGNAL(clicked()), this, SLOT(onNewFamilyButton()));
 addFamilyButton->setToolTip(tr("Create an additonal set of icons for this device"));
 panel1Layout->addWidget(addFamilyButton);
 QPushButton* deleteButton = new QPushButton(tr("Delete Icon Set"));
//    deleteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                ItemPalette.removeLevel4IconMap(_itemType, _family, NULL);
//                _family = NULL;
//                resetFamiliesPanel();
//            }
//        });
 connect(deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteButton()));
 deleteButton->setToolTip(tr("Delete this set of icons"));
 panel1Layout->addWidget(deleteButton);

 _showIconsButton = new QPushButton(tr("Show Icons"));
//    _showIconsButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (_iconPanel.isVisible()) {
//                    hideIcons();
//                } else {
//                    showIcons();
//                }
//            }
//    });
 connect(_showIconsButton, SIGNAL(clicked()), this, SLOT(onShowIconsButtons()));
 _showIconsButton->setToolTip(tr("Press to display the icons for the current icon set"));
 panel1Layout->addWidget(_showIconsButton);
 buttonPanelLayout->addWidget(panel1,0, Qt::AlignCenter);
 return buttonPanel;
}

/*protected*/ void IndicatorTOItemPanel::hideIcons() {
    if (_tablePanel!=NULL) {
        _tablePanel->setVisible(true);
    }
    if (_detectPanel!=NULL) {
        _detectPanel->setVisible(true);
    }
    TableItemPanel::hideIcons();
}

/*protected*/ void IndicatorTOItemPanel::showIcons() {
    if (_detectPanel!=NULL) {
        _detectPanel->setVisible(false);
    }
    if (_tablePanel!=NULL) {
        _tablePanel->setVisible(false);
    }
    TableItemPanel::showIcons();
}
void IndicatorTOItemPanel::onDeleteButton()
{
 ItemPalette::removeLevel4IconMap(_itemType, _family, NULL);
 _family = "";
 resetFamiliesPanel();
}
void IndicatorTOItemPanel::onShowIconsButtons()
{
 if (_iconPanel->isVisible())
 {
  hideIcons();
 }
 else
 {
  showIcons();
 }
}

void IndicatorTOItemPanel::createNewFamily(QString family)
{
 log->debug(tr("createNewFamily for %1. family = \"%2\"").arg(_itemType).arg(family));
         _iconGroupsMap = new QMap<QString, QMap<QString, NamedIcon*>*>();
         for (int i = 0; i < STATUS_KEYS.length(); i++) {
             _iconGroupsMap->insert(STATUS_KEYS[i], makeNewIconMap("Turnout")); // NOI18N
         }
         ItemPalette::addLevel4Family(_editor, _itemType, family, _iconGroupsMap);
         _tablePanel->setVisible(true);
         initIconFamiliesPanel();
         setFamily(family);
         reset();
}

/**
*  _iconGroupsMap holds edit changes when done is pressed
*/
/*protected*/ void IndicatorTOItemPanel::updateIconGroupsMap(QString key, QMap<QString, NamedIcon*>* iconMap) {
    _iconGroupsMap->insert(key, iconMap);
}

/*protected*/ void IndicatorTOItemPanel::setFamily(QString family)
{
 _family = family;
 if (log-> isDebugEnabled()) log-> debug("setFamily: for type \""+_itemType+"\", family \""+family+"\"");
 ((QVBoxLayout*) _iconFamilyPanel->layout())->removeWidget(_iconPanel);
 delete _iconPanel;
 _iconPanel = new ImagePanel();
 _iconPanel->setObjectName("iconPanel");
 //_iconPanel->setLayout(new FlowLayout);
 ((QVBoxLayout*)_iconFamilyPanel->layout())->insertWidget(0, _iconPanel);
 if (!_update)
 {
  ((QVBoxLayout*)_iconFamilyPanel->layout())->removeWidget(_dragIconPanel);
  delete _dragIconPanel;
  _dragIconPanel = new ImagePanel();
  ((QVBoxLayout*)_iconFamilyPanel->layout())->insertWidget(0,_dragIconPanel);
 }
 _iconGroupsMap = ItemPalette::getLevel4Family(_itemType, _family);
 addIcons2Panel(_iconGroupsMap);
 makeDndIconPanel(_iconGroupsMap->value("ClearTrack"), "TurnoutStateClosed");
 hideIcons();
}

/*protected*/ void IndicatorTOItemPanel::openEditDialog(QString key) {
    if (log-> isDebugEnabled()) log-> debug("openEditDialog for family \""+_family+"\" and \""+key+"\"");
    _currentIconMap = _iconGroupsMap->value(key);
//    new IndicatorTOIconDialog(_itemType, _family, this, key, _currentIconMap);
}

/****************** pseudo inheritance *********************/

/*public*/ bool IndicatorTOItemPanel::getShowTrainName() {
    return _detectPanel->getShowTrainName();
}

/*public*/ void IndicatorTOItemPanel::setShowTrainName(bool show) {
    _detectPanel->setShowTrainName(show);
}

/*public*/ QString IndicatorTOItemPanel::getOccSensor() {
    return _detectPanel->getOccSensor();
}

/*public*/ QString IndicatorTOItemPanel::getOccBlock() {
    return _detectPanel->getOccBlock();
}

/*public*/ void IndicatorTOItemPanel::setOccDetector(QString name) {
    _detectPanel->setOccDetector(name);
}

/*public*/ QStringList IndicatorTOItemPanel::getPaths() {
    return _detectPanel->getPaths();
}

/*public*/ void IndicatorTOItemPanel::setPaths(QStringList paths) {
    _detectPanel->setPaths(paths);
}

/*public*/ QMap <QString, QMap<QString, NamedIcon*>*>* IndicatorTOItemPanel::getIconMaps()
{
 if (_iconGroupsMap==NULL)
 {
  _iconGroupsMap = ItemPalette::getLevel4FamilyMaps(_itemType)->value(_family);
  if (_iconGroupsMap==NULL)
  {
//            JOptionPane.showMessageDialog(_paletteFrame,
//                    java.text.MessageFormat.format(tr("FamilyNotFound"),
//                                                   tr(_itemType), _family),
//                    ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(_paletteFrame, tr("Warning"), tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));
  }
 }
 return _iconGroupsMap;
}

/*protected*/ DragJLabel* IndicatorTOItemPanel::getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon *icon) {
    return new ITOIconDragJLabel(flavor, this);
}

///*protected*/ class IconDragJLabel extends DragJLabel {

/*public*/ ITOIconDragJLabel::ITOIconDragJLabel(DataFlavor* flavor, IndicatorTOItemPanel* parent) : DragJLabel(flavor, parent) {
        //super(flavor);
    this->parent = parent;
    }
/*public*/ bool ITOIconDragJLabel::isDataFlavorSupported(DataFlavor* flavor)
{
 return DragJLabel::isDataFlavorSupported(flavor);
}
/*public*/ QObject* ITOIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException)
{
 if (!isDataFlavorSupported(flavor))
 {
  return NULL;
 }
 NamedBean* bean = parent->getDeviceNamedBean();
 if (bean==NULL)
 {
  parent->log-> error("IconDragJLabel.getTransferData: NamedBean is NULL!");
  return NULL;
 }

 QMap <QString, QMap <QString, NamedIcon*>*>* iconMap = parent->getIconMaps();
 if (iconMap==NULL)
 {
  parent->log-> error("IconDragJLabel.getTransferData: iconMap is NULL!");
  return NULL;
 }

 IndicatorTurnoutIcon* t = new IndicatorTurnoutIcon(parent->_editor);

 t->setOccBlock(parent->_detectPanel->getOccBlock());
 t->setOccSensor(parent->_detectPanel->getOccSensor());
 t->setShowTrain(parent->_detectPanel->getShowTrainName());
 t->setTurnout(bean->getSystemName());
 t->setFamily(parent->_family);
#if 1
 QMapIterator<QString, QMap<QString, NamedIcon*>*> it(* iconMap);
 while (it.hasNext())
 {
  /*  QHash<QString, QHash<QString, NamedIcon*>*> entry =*/ it.next();
  QString status = it.key();
  QMapIterator<QString, NamedIcon*> iter( *it.value());
  while (iter.hasNext())
  {
   /*QHash<QString, NamedIcon*>* ent =*/ iter.next();
   t->setIcon(status, iter.key(), new NamedIcon(iter.value()));
  }
 }
#endif
 t->setLevel(Editor::TURNOUTS);
 return t;
}
//};
QString ITOIconDragJLabel::mimeData()
{
 NamedBean* bean = parent-> getTableSelection();
 if(bean == NULL)
 {
  QMessageBox::warning(parent, tr("Warning"), tr("You must select a %1 from the table").arg(parent->_itemType));
  return "";
 }
 IndicatorTurnoutIcon* icon;
 _dataFlavor = new DataFlavor(icon = new IndicatorTurnoutIcon(parent->_editor), "IndicatorTurnoutIcon");
 icon->setTurnout(bean->getSystemName());
 icon->setOccBlock(parent->getOccBlock());
 icon->setOccSensor(parent->getOccSensor());
 icon->setLevel(Editor::TURNOUTS);
 icon->setPaths(parent->getPaths());
 icon->setShowTrain(parent->getShowTrainName());
 icon->setFamily(parent->getFamilyName());
 icon->setStatus(0);
 //QHash<QString, NamedIcon*>* iconMap = parent->getIconMap();
 QMapIterator<QString, QMap<QString, NamedIcon*>*> it(*parent->_iconGroupsMap);
 while(it.hasNext())
 {
  it.next();
  QMapIterator<QString, NamedIcon*> iter(*it.value());
  while (iter.hasNext())
  {
   iter.next();
   icon->setIcon(it.key(),iter.key(), iter.value());
  }
 }

// _dataFlavor->setMimeTypeParameter("turnout", bean->getSystemName());
// if(parent->getOccBlock() != NULL)
//  _dataFlavor->setMimeTypeParameter("occblock", parent->getOccBlock());
// if(parent->getOccSensor() != NULL)
//  _dataFlavor->setMimeTypeParameter("occsensor", parent->getOccSensor());
// _dataFlavor->setMimeTypeParameter("family", parent->_family);

 IndicatorTurnoutIconXml* xml = new IndicatorTurnoutIconXml();
 QDomElement e = xml->store((QObject*)icon);
 xml->doc.appendChild(e);
 QString xmldata = xml->doc.toString();
 _dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));

 return _dataFlavor->toString();

}
