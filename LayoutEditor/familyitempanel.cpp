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

//FamilyItemPanel::FamilyItemPanel(QWidget *parent) :
//    ItemPanel(parent)
//{
//}
/**
*  ItemPanel for for plain icons and backgrounds
*/
// /*public*/ abstract class FamilyItemPanel extends ItemPanel {


    /**
    * Constructor types with multiple families and multiple icon families
    */
/*public*/ FamilyItemPanel::FamilyItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent)
    : ItemPanel(parentFrame, type, family, editor, parent)
{
 //super(parentFrame, type, family, editor);
 log = new Logger("FamilyItemPanel");
 _currentIconMap = NULL;
 _dragIconPanel = NULL;
 _updateButton = new QPushButton(tr("Update Panel"));

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
  _bottom1Panel = makeBottom1Panel();
  _bottom2Panel = makeBottom2Panel();
  initIconFamiliesPanel();
  thisLayout->addWidget(_iconFamilyPanel);
  QWidget* bottomPanel = new QWidget();
  FlowLayout* bottomPanelLayout = new FlowLayout;
  bottomPanel->setLayout(bottomPanelLayout);
  bottomPanelLayout->addWidget(_bottom1Panel);
  bottomPanelLayout->addWidget(_bottom2Panel);
  thisLayout->addWidget(bottomPanel, 0, Qt::AlignHCenter);
    //super.init();
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
 if (iconMap!=NULL)
 {
  checkCurrentMap(iconMap);   // is map in families?, does user want to add it? etc
 }
 makeBottomPanel(doneAction);
//    setMinimumSize(getPreferredSize());
}

/**
* Init for conversion of plain track to indicator track
* Skips init() in TableItemPanel
*/
/*public*/ void FamilyItemPanel::init(ActionListener* doneAction) {
    makeBottomPanel(doneAction);
}

/*protected*/ void FamilyItemPanel::makeBottomPanel(ActionListener* doneAction)
{
 _update = true;     // no dragging of a new icon
 _bottom2Panel = makeBottom2Panel();
 _bottom1Panel = makeBottom3Panel(doneAction, makeBottom1Panel());
 initIconFamiliesPanel();
 QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(_iconFamilyPanel->sizePolicy().hasHeightForWidth());
 _iconFamilyPanel->setSizePolicy(sizePolicy);
 thisLayout->addWidget(_iconFamilyPanel);
 QWidget*  bottomPanel = new QWidget(/*new FlowLayout()*/);
 QHBoxLayout* bottomPanelLayout;// = new QHBoxLayout;
 bottomPanel->setLayout(bottomPanelLayout = new QHBoxLayout);
 bottomPanelLayout->addWidget(_bottom1Panel);
 bottomPanelLayout->addWidget(_bottom2Panel);
 thisLayout->addWidget(bottomPanel,0,Qt::AlignCenter);
 if (log->isDebugEnabled()) log->debug("init done for family "+_family);
}

/**
* iconMap is existing map of the icon.  Check whether map is one of the
* families. if so, return.  if not, does user want to add it to families?
* if so, add.  If not, save for return when updated.
*/
/*private*/ void FamilyItemPanel::checkCurrentMap(QMap<QString, NamedIcon*>* iconMap)
{
 _currentIconMap = iconMap;
 if (log->isDebugEnabled()) log->debug("checkCurrentMap: for type \""+_itemType+"\", family \""+_family+"\"");
 if (_family!="" && _family.trimmed().length()>0)
 {
  QMap<QString, NamedIcon*>* map = ItemPalette::getIconMap(_itemType, _family);
  if (map!=NULL)
  {
   return;     // Must assume no family names were changed
  }
 }
 QMap <QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 if(families == NULL)
  return;
 QListIterator<  QMap<QString, NamedIcon*>*>  it(families->values());
#if 1
 while (it.hasNext())
 {
  QMap<QString, NamedIcon*>*  entry = it.next();
  if (entry->values().size()==iconMap->size())
  {
   QMapIterator<QString, NamedIcon*> iter(*entry);
   bool match = true;
   while (iter.hasNext())
   {
    iter.next();
                //Entry<String, NamedIcon*> ent = iter.next();
    NamedIcon* icon = iconMap->value(iter.key());
    if (icon==NULL || icon->getURL()!=(iter.value()->getURL()))
    {
     match = false;
     break;
    }
   }
   if (match)
   {
    _family = iter.key();
    return;
   }
  }
 }
 /*int result = JOptionPane.showConfirmDialog(_paletteFrame,
                        ItemPalette.rbp.getString("NoFamilyName"), t("questionTitle"),
                        JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
    if (result==JOptionPane.NO_OPTION) */
 int result = QMessageBox::question(_paletteFrame, tr("Question"),tr("This icon set is not known to the Palette.  Do you want to save it?"),QMessageBox::Yes, QMessageBox::No );
 if(result == QMessageBox::No)
 {
  return;
 }
 if (_family!=NULL && _family.trimmed().length()>0 && ItemPalette::addFamily(_paletteFrame, _itemType, _family, iconMap))
 {
  return;
 }
 do
 {
//        _family = JOptionPane.showInputDialog(_paletteFrame, ItemPalette.rbp.getString("EnterFamilyName"),
//                ItemPalette.rb.getString("questionTitle"), JOptionPane.QUESTION_MESSAGE);
  InputDialog* dlg = new InputDialog(tr("Enter family name"), _family);
  if(dlg->exec() == QDialog::Accepted)
  {
   _family = dlg->value();
  }
  if (_family==NULL || _family.trimmed().length()==0)
  {
   // bail out
   return;
  }
 } while (!ItemPalette::addFamily((QFrame*)_paletteFrame, _itemType, _family, iconMap));
}
#endif

/*protected*/ void FamilyItemPanel::initIconFamiliesPanel()
{
 _iconFamilyPanel = new QWidget();
 QVBoxLayout* iconFamilyPanelLayout;
 _iconFamilyPanel->setLayout(iconFamilyPanelLayout = new QVBoxLayout);//(_iconFamilyPanel/*, BoxLayout.Y_AXIS*/));
 iconFamilyPanelLayout->setObjectName("iconFamilyPanelLayout");

 QMap<QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 if (families!=NULL && families->size()>0)
 {
  QWidget*  familyPanel = makeFamilyButtons(QStringListIterator(families->keys()), (_currentIconMap==NULL));
  if (_currentIconMap==NULL)
  {
   _currentIconMap = families->value(_family);
  }
  // make _iconPanel & _dragIconPanel before calls to add icons
  addFamilyPanels(familyPanel);
  if (_currentIconMap==NULL)
  {
//            JOptionPane.showMessageDialog(_paletteFrame,
//                    java.text.MessageFormat.format(ItemPalette.rbp.getString("FamilyNotFound"),
//                                                   ItemPalette.rbp.getString(_itemType), _family),
//                    ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_paletteFrame, tr("Warning"), tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));
  }
  else
  {
   addIconsToPanel(_currentIconMap);        // need to have family iconMap identified before calling
   makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
  }
 }
 else
 {
  addCreatePanels();
 }

}

/*protected*/ void FamilyItemPanel::updateFamiliesPanel() {
    if (log->isDebugEnabled()) log->debug("updateFamiliesPanel for "+_itemType);
    removeIconFamiliesPanel();
    initIconFamiliesPanel();
    thisLayout->addWidget(_iconFamilyPanel);
    hideIcons();
//    _iconFamilyPanel.invalidate();
//    invalidate();
    reset();
}

/*protected*/ QWidget* FamilyItemPanel::makeFamilyButtons (QStringListIterator it, bool setDefault) {
    QWidget* familyPanel = new QWidget();
    QVBoxLayout* familyPanelLayout;
    familyPanel->setLayout(familyPanelLayout = new QVBoxLayout) ;//(familyPanel/*, BoxLayout.Y_AXIS*/));
    familyPanelLayout->setObjectName("familyPanelLayout");
//    familypanelLayout->setMargin(0);
//    familypanelLayout->setContentsMargins(0,0,0,0);
//    QString txt = java.text.MessageFormat.format(ItemPalette.rbp.getString("IconFamiliesLabel"),
//                                                ItemPalette.rbp.getString(_itemType));
    QString txt = tr("Icon Sets for %1").arg(_itemType);
//    QWidget*  p = new QWidget(/*new FlowLayout()*/);
//    FlowLayout* pfl;
//    p->setLayout(pfl = new FlowLayout);
    FlowLayout* pLayout = new FlowLayout;
    pLayout->addWidget(new QLabel(txt));
    familyPanelLayout->addLayout(pLayout);
    QButtonGroup* group = new QButtonGroup();
    QWidget*  buttonPanel = new QWidget(/*new FlowLayout()*/);
    buttonPanel->setLayout(new FlowLayout());
    QString family = "";
    QRadioButton* button = NULL;
    int count = 0;
    while (it.hasNext())
    {
     family = it.next();
     count++;
     button = new QRadioButton(ItemPalette::convertText(family));
//        button.addActionListener(new ActionListener() {
//                String family;
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    setFamily(family);
//                }
//                ActionListener init(String f) {
//                    family = f;
//                    if (log->isDebugEnabled()) log->debug("ActionListener.init : for type \""+_itemType+"\", family \""+family+"\"");
//                    return this;
//                }
//            }.init(family));
     ButtonListener* bl = new ButtonListener();
     bl->init(family, this);
     connect(button, SIGNAL(clicked()), bl, SLOT(actionPerformed()));
     if (family==(_family))
     {
      button->setChecked(true);
     }
     if (count>4)
     {
      count = 0;
      familyPanel->layout()->addWidget(buttonPanel);
      buttonPanel = new QWidget(/*new FlowLayout()*/);
      buttonPanel->setLayout(new FlowLayout());  //new BoxLayout(p, BoxLayout.Y_AXIS)
     }
     buttonPanel->layout()->addWidget(button);
     group->addButton(button);
    }
    familyPanel->layout()->addWidget(buttonPanel);
    if (_family==NULL && setDefault) {
        _family = family;       // let last family be the selected one
        if (button != NULL) button->setChecked(true);
        else log->warn("NULL button after setting family");
    }
    familyPanel->layout()->addWidget(buttonPanel);
    return familyPanel;
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
/*protected*/ void FamilyItemPanel::addFamilyPanels(QWidget*  familyPanel) {
    _iconPanel = new QWidget(/*new FlowLayout()*/);
    //_iconPanel->setLayout(new FlowLayout());
    ((QVBoxLayout*)_iconFamilyPanel->layout())->addWidget(_iconPanel,0, Qt::AlignCenter);
    _iconPanel->setVisible(false);
    if (!_update) {
        _dragIconPanel = new QWidget(/*new FlowLayout()*/);
        _dragIconPanel->setLayout(new QHBoxLayout);
        _iconFamilyPanel->layout()->addWidget(_dragIconPanel);
        _dragIconPanel->setVisible(true);
    }
    _iconFamilyPanel->layout()->addWidget(familyPanel);
    _bottom1Panel->setVisible(true);
    _bottom2Panel->setVisible(false);
}

/*protected*/ void FamilyItemPanel::addCreatePanels() {
//    JOptionPane.showMessageDialog(_paletteFrame,
//            java.text.MessageFormat.format(ItemPalette.rbp.getString("AllFamiliesDeleted"),
//                                           ItemPalette.rbp.getString(_itemType)),
//            ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(_paletteFrame, tr("Warning"), tr("All Icon sets for type %1 have been deleted.").arg(_itemType));
 _bottom1Panel->setVisible(false);
 _bottom2Panel->setVisible(true);
}

/*protected*/ void FamilyItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* iconMap)
{
 if (iconMap==NULL)
 {
  log->warn("iconMap is NULL for type "+_itemType+" family "+_family);
  return;
 }
 QGridLayout* gridbag = new QGridLayout();
 _iconPanel->setLayout(gridbag);

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

 int cnt = iconMap->size();
 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  //Entry<String, NamedIcon> entry = it.next();
  it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  icon->reduceTo(100, 100, 0.2);
  QGroupBox*  panel = new QGroupBox(/*new FlowLayout()*/);
  panel->setLayout(/*new FlowLayout()*/new QHBoxLayout);
  QString borderName = ItemPalette::convertText(it.key());
     //panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
//                                                        borderName));
  panel->setTitle(borderName);
  panel->setToolTip(borderName);
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
  panel->setStyleSheet(gbStyleSheet);
  QLabel* image = new QLabel(/*icon*/);
  image->setPixmap(QPixmap::fromImage(icon->getImage()));
  if (icon->getIconWidth()<1 || icon->getIconHeight()<1)
  {
   image->setText(tr("invisible Icon"));
//      image.setForeground(Color.lightGray);
  }
  image->setAlignment(Qt::AlignCenter);
  image->setMargin(6);

  ((/*FlowLayout**/QHBoxLayout*)panel->layout())->addWidget(image,0,Qt::AlignCenter);
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

//abstract protected JLabel getDragger(DataFlavor flavor, QHash <String, NamedIcon> map);

/*protected*/ void FamilyItemPanel::makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString displayKey)
{
 if (_update)
 {
  return;
 }
 _dragIconPanel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 if (iconMap!=NULL)
 {
  if (iconMap->value(displayKey)==NULL)
  {
   displayKey = (QString)iconMap->keys().at(0);
  }
  NamedIcon* ic = iconMap->value(displayKey);
  if (ic!=NULL)
  {
   NamedIcon* icon = new NamedIcon(ic);
   QGroupBox*  panel = new QGroupBox(/*new FlowLayout()*/);
   panel ->setLayout(new QHBoxLayout);
   QString borderName = tr("Drag to Panel");
//  panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
//                                                    borderName));
   QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
   panel->setTitle(borderName);
   panel->setStyleSheet(gbStyleSheet);
   DragJLabel* label;
   try
   {
    label = getDragger(new DataFlavor(Editor::POSITIONABLE_FLAVOR), iconMap);
   } catch (ClassNotFoundException cnfe)
   {
       //cnfe.printStackTrace();
       label = new DragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR));

   }
   label->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));

   //label->setIcon(icon);
   label->setPixmap(QPixmap::fromImage(icon->getImage()));

   label->setObjectName(borderName);
   label->setAlignment(Qt::AlignCenter);
   label->setMargin(6);

   ((QBoxLayout*)panel->layout())->addWidget(label, 0, Qt::AlignCenter);
   int width = qMax(100, panel->minimumSize().width());
   panel->setMinimumSize( QSize(width, panel->minimumSize().height()));
   panel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
   QLayout* l = _dragIconPanel->layout();
   if(l == NULL)
    _dragIconPanel->setLayout(new QHBoxLayout);
   ((QHBoxLayout*)_dragIconPanel->layout())->addWidget(panel,0, Qt::AlignCenter);
   return;
  }
 }
 else
 {
//  JOptionPane.showMessageDialog(_paletteFrame,
//        java.text.MessageFormat.format(ItemPalette.rbp.getString("FamilyNotFound"),
//                                       ItemPalette.rbp.getString(_itemType), _family),
//         ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
  log->warn(tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));
  QMessageBox::warning(_paletteFrame, tr("Warning"), tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));

 }
}

/*protected*/ QWidget*  FamilyItemPanel::makeBottom1Panel()
{
 QWidget*  bottomPanel = new QWidget();
 QHBoxLayout* bottomPanelLayout;
 bottomPanel->setLayout(bottomPanelLayout = new QHBoxLayout);
 _showIconsButton = new QPushButton(tr("Show Icons"));
//    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(_showIconsButton->sizePolicy().hasHeightForWidth());
//    _showIconsButton->setSizePolicy(sizePolicy);
//    _showIconsButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (_iconPanel.isVisible()) {
//                    hideIcons();
//                } else {
//                    showIcons();
//                }
//            }
//    });
 connect(_showIconsButton, SIGNAL(clicked()), this, SLOT(on_showIconsButton_clicked()));
 _showIconsButton->setToolTip(tr("Press to display the icons for the current icon set"));
 bottomPanelLayout->addWidget(_showIconsButton);

 QPushButton* editIconsButton = new QPushButton(tr("Edit Icons"));
    //editIconsButton->setSizePolicy(sizePolicy);
//    editIconsButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                openEditDialog();
//            }
//    });
 connect(editIconsButton, SIGNAL(clicked()), this, SLOT(openEditDialog()));
 editIconsButton->setToolTip(tr("Press to change the icons of the current icon set or to add and delete icon sets"));
 bottomPanelLayout->addWidget(editIconsButton);
 return bottomPanel;
}

void FamilyItemPanel::on_showIconsButton_clicked()
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

/*protected*/ void FamilyItemPanel::hideIcons()
{
 _iconPanel->setVisible(false);
 if (!_update)
 {
  _dragIconPanel->setVisible(true);
//        _dragIconPanel.invalidate();
 }
 _showIconsButton->setText(tr("Show Icons"));
 reset();
}

/*protected*/ void FamilyItemPanel::showIcons()
{
 _iconPanel->setVisible(true);
//    _iconPanel.invalidate();
 if (!_update)
 {
  _dragIconPanel->setVisible(false);
 }
 _showIconsButton->setText(tr("Hide Icons"));
    reset();
}

/**
*  Replacement panel for _bottom1Panel when no icon families exist for _itemType
*/
/*protected*/ QWidget*  FamilyItemPanel::makeBottom2Panel() {
    QWidget*  panel = new QWidget();
    FlowLayout* panelLayout;
    panel->setLayout(panelLayout = new FlowLayout);
    QPushButton* newFamilyButton = new QPushButton(tr("Create Icon Set"));
//    newFamilyButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                createNewFamilySet(_itemType);
//            }
//    });
    connect(newFamilyButton, SIGNAL(clicked()), this, SLOT(on_newFamilyButton_clicked()));
    newFamilyButton->setToolTip(tr("Create an additonal set of icons for this device"));
    panelLayout->addWidget(newFamilyButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                updateFamiliesPanel();
//             }
//    });
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(updateFamiliesPanel()));
    panelLayout->addWidget(cancelButton);
    return panel;
}

void FamilyItemPanel::on_newFamilyButton_clicked()
{
 newFamilyDialog();
}

// add update buttons to  bottom1Panel
/*protected*/ QWidget* FamilyItemPanel::makeBottom3Panel(ActionListener* doneAction, QWidget* bottom1Panel)
{
 QWidget* bottomPanel = new QWidget(/*new FlowLayout()*/);
 QHBoxLayout* bottomPanelLayout;
 bottomPanel->setLayout(bottomPanelLayout = new QHBoxLayout);
 bottomPanelLayout->addWidget(bottom1Panel);
 QWidget*  updatePanel = new QWidget(/*new FlowLayout()*/);
 FlowLayout* updatePanelLayout;
 updatePanel->setLayout(updatePanelLayout = new FlowLayout);
 _updateButton = new QPushButton(tr("Update Panel"));
//    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//     sizePolicy.setHorizontalStretch(0);
//     sizePolicy.setVerticalStretch(0);
//     sizePolicy.setHeightForWidth(_updateButton->sizePolicy().hasHeightForWidth());
//     _updateButton->setSizePolicy(sizePolicy);//    _updateButton.addActionListener(doneAction);
 _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the panel"));
 connect(_updateButton, SIGNAL(clicked()), doneAction, SLOT(actionPerformed()));
 updatePanelLayout->addWidget(_updateButton);
 bottomPanelLayout->addWidget(updatePanel,0,Qt::AlignCenter);
 return bottomPanel;
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
    _dialog = openDialog(_itemType, family, NULL);
    return true;
}

/*protected*/ void FamilyItemPanel::openEditDialog()
{
 if (log->isDebugEnabled()) log->debug("openEditDialog for family \""+_family+"\"");
 IconDialog* dialog = new IconDialog(_itemType, _family, this, _currentIconMap);
 // call super ItemDialog to size and locate dialog
 dialog->sizeLocate();
}

/*protected*/ IconDialog* FamilyItemPanel::openDialog(QString type, QString family, QMap<QString, NamedIcon*>* iconMap)
{
    IconDialog* dialog = new IconDialog(type, family, this, iconMap);
    dialog->sizeLocate();
    return dialog;
}

//@Override
/*protected*/ void FamilyItemPanel::closeDialogs() {
    if (_dialog != NULL) {
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
 if (log->isDebugEnabled()) log->debug("setFamily: for type \""+_itemType+"\", family \""+family+"\"");
 _iconFamilyPanel->layout()->removeWidget(_iconPanel);
 delete _iconPanel;
 _iconPanel= NULL;
 QObjectList l = _iconFamilyPanel->children();
// foreach(QObject* o, l)
// {
//  if(qobject_cast<QWidget*>(o)!= NULL)
//  {
//   if((QWidget*)o == _iconPanel)
//   _iconPanel->deleteLater();
//  }
// }

 _iconPanel = new QWidget(/*new FlowLayout()*/);
 _iconPanel->setObjectName("iconPanel");
 //_dragIconPanel->setLayout(new FlowLayout);
 _iconFamilyPanel->layout()->addWidget(_iconPanel);
 if (!_update)
 {
 _iconFamilyPanel->layout()->removeWidget(_dragIconPanel);
 delete _dragIconPanel;
 _dragIconPanel = NULL;
  QObjectList l = _iconFamilyPanel->children();
//  foreach(QObject* o, l)
//  {
//   if(qobject_cast<QWidget*>(o)!= NULL)
//   {
//    if((QWidget*)o == _dragIconPanel)
//     _dragIconPanel->deleteLater();
//   }
//  }
  _dragIconPanel = new QWidget(/*new FlowLayout()*/);
  _dragIconPanel->setObjectName("dragIconPanel");
  _dragIconPanel->setLayout(new QHBoxLayout);
  ((QVBoxLayout*)_iconFamilyPanel->layout())->addWidget(_dragIconPanel,0,Qt::AlignCenter);
 }
 _currentIconMap = ItemPalette::getIconMap(_itemType, _family);
 addIconsToPanel(_currentIconMap);
 makeDndIconPanel(_currentIconMap, "BeanStateUnknown");
//    _iconFamilyPanel.invalidate();
 hideIcons();
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
