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
#include "joptionpane.h"
#include "indicatortoicondialog.h"
#include <QMap>
#include "gridbaglayout.h"
#include "borderfactory.h"

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
/*public*/ IndicatorTOItemPanel::IndicatorTOItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor *editor, QWidget *parent)
 : TableItemPanel(parentFrame, type, family, model, editor, parent)
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
 * Init for creation _bottom1Panel and _bottom2Panel alternate visibility in
 * bottomPanel depending on whether icon families exist. They are made first
 * because they are referenced in initIconFamiliesPanel().
 */
//@Override
/*public*/ void IndicatorTOItemPanel::init() {
    if (!_initialized) {
        _update = false;
        _suppressDragging = false;
        layout()->addWidget(initTablePanel(_model, _editor)); // top of Panel
        _detectPanel = new DetectionPanel(this);
        layout()->addWidget(_detectPanel);
        initIconFamiliesPanel();
        layout()->addWidget(_iconFamilyPanel);
        makeBottomPanel(nullptr);
       _buttonPosition = 2;
       _initialized = true;
    }
    hideIcons();
}

/**
* Init for conversion of plain track to indicator track
*/
/*public*/ void IndicatorTOItemPanel::init(ActionListener* doneAction)
{
 FamilyItemPanel::init(doneAction);
 thisLayout->insertWidget(0,_iconFamilyPanel);
 _buttonPosition = 0;
}

/**
* Init for update of existing indicator turnout
* _bottom3Panel has "Update Panel" button put into _bottom1Panel
*/
/*public*/ void IndicatorTOItemPanel::initUpdate(ActionListener* doneAction, QMap<QString, QMap<QString, NamedIcon*>*>* iconMaps)
{
 _iconGroupsMap = iconMaps;
 checkCurrentMaps(iconMaps);   // is map in families?, does user want to add it? etc
 //        _bottom1Panel.remove(_editIconsButton);
 _detectPanel= new DetectionPanel(this);
 TableItemPanel::init(doneAction, NULL);
 //thisLayout->addWidget(_detectPanel/*, 1*/,0, Qt::AlignCenter);
 thisLayout->insertWidget(1,_detectPanel);
 //thisLayout->addWidget(_iconFamilyPanel/*, 2*/,0, Qt::AlignBottom);
 thisLayout->insertWidget(2,_iconFamilyPanel);
 _buttonPosition = 2;
}

/**
* iconMap is existing map of the icon.  Check whether map is one of the
* families. if so, return.  if not, does user want to add it to families?
* if so, add.  If not, save for return when updated.
*/
/*private*/ void IndicatorTOItemPanel::checkCurrentMaps(QMap<QString, QMap<QString, NamedIcon*>*>* iconMaps)
{
 QString family = "";
 _updateGroupsMap = iconMaps;
 QMap<QString, QMap<QString, QMap<QString, NamedIcon*>*>*>* families
                 = ItemPalette::getLevel4FamilyMaps(_itemType);
 //Iterator<Entry<String, HashMap<String, HashMap<String, NamedIcon>>>> it = families.entrySet().iterator();
 QMapIterator<QString, QMap<QString, QMap<QString, NamedIcon*>*>*> it(*families);
 while (it.hasNext()) {
     //Entry<String, HashMap<String, HashMap<String, NamedIcon>>> entry = it.next();
  it.next();
  //Entry<String, HashMap<String, HashMap<String, NamedIcon>>> entry = it.next();
     family = it.key();
     log->debug(tr("FamilyKey = %1").arg(family));
     QMapIterator<QString, QMap<QString, NamedIcon*>*> iter(*it.value());
     while (iter.hasNext()) {
         //Entry<String, HashMap<String, NamedIcon>> ent = iter.next();
      iter.next();
         QMap<QString, NamedIcon*>* subFamily = iconMaps->value(iter.key());
         if (!mapsAreEqual(iter.value(), subFamily)) {
             family = nullptr;
             break;
         }
     }
     if (family != "") {
         _family = family;
         return;
     }
 }
 if (ItemPalette::getLevel4Family(_itemType, _family) != nullptr) {
     JOptionPane::showMessageDialog(_paletteFrame,
             tr("Family name \"%1\" is the name of a\ndifferent icon set for %1s in the Catalog.\nPlease change the name.").arg(_family).arg(_itemType),
             tr("Warning"), JOptionPane::WARNING_MESSAGE);
     // make sure name does not duplicate a known name
     _family = "";
 }
 if (!_suppressNamePrompts) {
     if (_family == "" || _family.trimmed().length() == 0) {
         _family = JOptionPane::showInputDialog(_paletteFrame, tr("Icon set has no name. If you would like to name it, enter a name."),
                 tr("Question"), JOptionPane::QUESTION_MESSAGE);
         if (_family == "" || _family.trimmed().length() == 0) {
             // bail out
             _family = "";
             _suppressNamePrompts = true;
             return;
         }
     }
     int result = JOptionPane::showConfirmDialog(_paletteFrame,
             tr("Icon set \"%1\" is not known to the Palette. Do you want to add it to the icon sets?").arg(_family), tr("Question"),
             JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE);
     if (result == JOptionPane::YES_OPTION) {
         ItemPalette::addLevel4Family(_paletteFrame, _itemType, _family, iconMaps);
     } else if (result == JOptionPane::NO_OPTION) {
         _suppressNamePrompts = true;
     }
 }
}

/*
* Get a handle in order to change visibility
*/
/*protected*/ QWidget* IndicatorTOItemPanel::initTablePanel(PickListModel* model, Editor* editor) {
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
 _iconFamilyPanel = new JPanel();
      _iconFamilyPanel->setLayout(new QVBoxLayout());//_iconFamilyPanel, BoxLayout.Y_AXIS));

      QMap<QString, QMap<QString,QMap<QString, NamedIcon*>*>*>* families
              = ItemPalette::getLevel4FamilyMaps(_itemType);
      if (families != nullptr && families->size() > 0) {

          JPanel* familyPanel = makeFamilyButtons(QStringListIterator(families->keys()), (_iconGroupsMap == nullptr));

          if (_iconGroupsMap == nullptr) {
              _iconGroupsMap = families->value(_family);
          }
          // make _iconPanel & _dragIconPanel before calls to add icons
          addFamilyPanels(familyPanel);
          if (_iconGroupsMap == nullptr) {
              log->error("_iconGroupsMap is null in initIconFamiliesPanel");
              _family = QString();
          } else {
              addIcons2Panel(_iconGroupsMap);  // need to have family iconMap identified before calling
              makeDndIconPanel(_iconGroupsMap->value("ClearTrack"), "TurnoutStateClosed");
          }
      } else {
          familiesMissing();
          //createNewFamily();
      }
      if (log->isDebugEnabled()) {
          log->debug("initIconFamiliesPanel done");
      }
}

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
    GridBagLayout* gridbag = new GridBagLayout();
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
        JPanel* panel = new JPanel();
        panel->setLayout(new QHBoxLayout);
        //gridbag->setConstraints(panel, c);
        gridbag->addWidget(panel, c);
        c.gridx++;
        QMap<QString, NamedIcon*>* iconMap = it.value();
        QMapIterator<QString, NamedIcon*> iter(* iconMap);
        QString borderName = ItemPalette::convertText(it.key());
        while(iter.hasNext())
        {
            //QHash<QString, NamedIcon*> ent = iter->next();
            iter.next();
            QString borderName = ItemPalette::convertText(iter.key());
            NamedIcon* icon = new NamedIcon(iter.value());    // make copy for possible reduction
            icon->reduceTo(100, 100, 0.2);
            panel = new JPanel();
            panel->setLayout(new QHBoxLayout);
            panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
                                    borderName));
            //if (log-> isDebugEnabled()) log-> debug("addIcons2Panel: "+borderName+" icon at ("
            //                                    +c.gridx+","+c.gridy+") width= "+icon.getIconWidth()+
            //                                    " height= "+icon.getIconHeight());
            JLabel* image = new JLabel("", icon, 0);
            if (icon->getIconWidth()<1 || icon->getIconHeight()<1) {
                image->setText(tr("invisibleIcon"));
//                image->setForeground(QColor(Qt::lightGray));
            }
            panel->layout()->addWidget(image);
            image->setAlignment(Qt::AlignCenter);
            image->setMargin(6);
            int width = qMax(85, panel->sizeHint().width());
            panel->resize(QSize(width, panel->sizeHint().height()));
//            gridbag.setConstraints(panel, c);
//            _iconPanel->layout()->addWidget(panel);
            gridbag->addWidget(panel, c);
            c.gridx++;
        }
        panel = new JPanel();
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
        gridbag->addWidget(panel, c);
        //if (log-> isDebugEnabled()) log-> debug("addIcons2Panel: row "+c.gridy+" has "+iconMap.size()+" icons");
    }
}

//@Override
/*protected*/ JPanel* IndicatorTOItemPanel::makeItemButtonPanel() {
    _bottom1Panel = new JPanel();
    _bottom1Panel->setLayout(new FlowLayout());
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

    if (!_update) {
        addCreateDeleteFamilyButtons();
    }
    return _bottom1Panel;
}

//@Override
/*protected*/ bool IndicatorTOItemPanel::newFamilyDialog() {
    QString family = JOptionPane::showInputDialog(_paletteFrame, tr("Enter a name for this icon set."),
            tr("Create New Icon Set for %1s").arg(_itemType), JOptionPane::QUESTION_MESSAGE);
    if (family.isNull() || family.trimmed().length() == 0) {
        // bail out
        return false;
    }
    QStringListIterator iter(ItemPalette::getLevel4FamilyMaps(_itemType)->keys());
    while (iter.hasNext()) {
        if (family == (iter.next())) {
            JOptionPane::showMessageDialog(_paletteFrame,
                    tr("Family name \"%1\" is the name of a\ndifferent icon set for %2s in the Catalog.\nPlease change the name.").arg(family).arg(_itemType),
                    tr("Warning"), JOptionPane::WARNING_MESSAGE);
            return false;
        }
    }
    createNewFamily(family);
    showIcons();
    return true;
}

void EditIconActionListener::actionPerformed(JActionEvent */*a*/)
{
    parent->openStatusEditDialog(key);
}

void  EditIconActionListener::init(QString k, IndicatorTOItemPanel *parent)
{
 key = k;
 this->parent = parent;
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
        _detectPanel->update();
    }
    if (_tablePanel!=NULL) {
        _tablePanel->setVisible(false);
        _tablePanel->update();
    }
    TableItemPanel::showIcons();
}

//@Override
/*protected*/ void IndicatorTOItemPanel::addCreateDeleteFamilyButtons() {
    FamilyItemPanel::addCreateDeleteFamilyButtons();
    QPushButton* renameButton = new QPushButton(tr("Rename Icon Set"));
//    renameButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
    connect(renameButton, &QPushButton::clicked, [=]{
            renameFamily();
//       }
    });
    _bottom1Panel->layout()->addWidget(renameButton/*, 1*/);
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
 * Action item to rename an icon family.
 */
/*protected*/ void IndicatorTOItemPanel::renameFamily() {
    QString family = JOptionPane::showInputDialog(_paletteFrame, tr("Enter a name for this icon set."),
            tr("Rename Icon Set"), JOptionPane::QUESTION_MESSAGE);
    if (family != nullptr && family.trimmed().length() > 0) {
        ItemPalette::removeLevel4IconMap(_itemType, _family, nullptr);
        _family = family;
        ItemPalette::addLevel4Family(_editor, _itemType, family, _iconGroupsMap);
        _tablePanel->setVisible(true);
        initIconFamiliesPanel();
        setFamily(family);
    }
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
     if (log->isDebugEnabled()) {
         log->debug("setFamily: for type \"" + _itemType + "\", family \"" + family + "\"");
     }
     _iconFamilyPanel->layout()->removeWidget(_iconPanel);
     _iconPanel = new JPanel();
     _iconFamilyPanel->layout()->addWidget(_iconPanel/*, 0*/);
     if (!_supressDragging) {
         _iconFamilyPanel->layout()->removeWidget(_dragIconPanel);
         _dragIconPanel = new JPanel();
         _iconFamilyPanel->layout()->addWidget(_dragIconPanel/*, 0*/);
     }
     _iconGroupsMap = ItemPalette::getLevel4Family(_itemType, _family);
     addIcons2Panel(_iconGroupsMap);
     makeDndIconPanel(_iconGroupsMap->value("ClearTrack"), "TurnoutStateClosed");
     hideIcons();
}

/*private*/ void IndicatorTOItemPanel::openStatusEditDialog(QString key) {
    if (log->isDebugEnabled()) {
        log->debug(tr("openStatusEditDialog for family \"%1\" and \"%2\"").arg(_family).arg(key));
    }
    _currentIconMap = _iconGroupsMap->value(key);
    _dialog = new IndicatorTOIconDialog(_itemType, _family, this, key, _currentIconMap);
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

/*public*/ ITOIconDragJLabel::ITOIconDragJLabel(DataFlavor* flavor, IndicatorTOItemPanel* parent)
 : DragJLabel(flavor, parent) {
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
 NamedBean* bean = parent->getNamedBean();
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
QByteArray ITOIconDragJLabel::mimeData()
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
 QByteArray xmldata;
 xmldata.append(xml->doc.toString());
 return xmldata;

}
