#include "icondialog.h"
#include <QBoxLayout>
#include "itempalette.h"
#include "itempanel.h"
#include "jtextfield.h"
#include "familyitempanel.h"
#include "flowlayout.h"
#include "gridbagconstraints.h"
#include <QGridLayout>
#include "namedicon.h"
#include "dropjlabel.h"
#include "catalogpanel.h"
#include "QMessageBox"
#include <QGroupBox>

//IconDialog::IconDialog(QWidget *parent) :
//    ItemDialog(parent)
//{
//}
/**
 *
 * @author Pete Cressman  Copyright (c) 2010, 2011
 */

// /*public*/ class IconDialog extends ItemDialog {


/**
* Constructor for existing family to change icons, add/delete icons, or to delete the family
*/
/*public*/ IconDialog::IconDialog(QString type, QString family, ItemPanel* parent, QHash <QString, NamedIcon*>* iconMap ) : ItemDialog(type, family,                                                                                                                          tr("Show Icons for %1").arg(type), parent, true)
{
//    super(type, family,
//          tr("Show Icons for %1").arg(type), parent, true);

 setLayout(new QVBoxLayout);
 _newIconSet = false;
 log = new Logger("IconDialog");
 QFont f = font();
 f.setPointSize(8);
 setFont(f);

 _iconMap = clone(iconMap);
 QWidget* panel = new QWidget();
 QVBoxLayout* pl;
 panel->setLayout(pl = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
 pl->addStrut(ItemPalette::STRUT_SIZE);

 bool isUpdate = parent->isUpdate();
 _familyName = new JTextField(family);
 if (_family=="")
 {
  _newIconSet = true;
//        	_familyName.setText(tr("Unnamed"));
 }
 _familyName->setEnabled(!isUpdate);
 pl->addWidget(ItemPalette::makeBannerPanel("Icon Set Name", _familyName));

 QWidget* buttonPanel = new QWidget();
 buttonPanel->setLayout(new QVBoxLayout); //(buttonPanel/*, BoxLayout.Y_AXIS*/));
 if (_iconMap != NULL)
 {
  makeAddIconButtonPanel(buttonPanel, tr("Add an additional Sensor position to this icon set "), tr("Delete the last Sensor position from this icon set"));
  if (!isUpdate)
  {
   makeAddSetButtonPanel(buttonPanel);
  }
  makeDoneButtonPanel(buttonPanel);
 }
// else
// {
//  _iconMap = ItemPanel::makeNewIconMap(type);
//  makeCreateButtonPanel(buttonPanel);
// }

 _iconPanel = makeIconPanel(_iconMap);
 pl->addWidget(_iconPanel);	// put icons above buttons
 pl->addWidget(buttonPanel);

 _catalog = CatalogPanel::makeDefaultCatalog();
 _catalog-> setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 pl->addWidget(/*new JScrollPane*/(_catalog));

 //setContentPane(panel);
 layout()->addWidget(panel);
}

/**
* Add/Delete icon family for types that may have more than 1 family
*/
/*protected*/ void IconDialog::makeAddSetButtonPanel(QWidget* buttonPanel)
{
 QWidget* panel1 = new QWidget();
 panel1->setLayout(new FlowLayout());
 _addFamilyButton = new QPushButton(tr("Add New Icon Set"));
//    _addFamilyButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                addFamilySet();
//                dispose();
//            }
//    });
 connect(_addFamilyButton, SIGNAL(clicked()), this, SLOT(addFamilyButtonAction()));
 _addFamilyButton->setToolTip(tr("Create an additonal set of icons for this device"));
 panel1->layout()->addWidget(_addFamilyButton);
 if (_newIconSet)
 {
  _addFamilyButton->setEnabled(false);
 }

 _deleteButton = new QPushButton(tr("Delete Icon Set"));
//    _deleteButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                deleteFamilySet();
//                dispose();
//            }
//    });
 connect(_deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonAction()));
 _deleteButton->setToolTip(tr("Delete this set of icons"));
 panel1->layout()->addWidget(_deleteButton);
 buttonPanel->layout()->addWidget(panel1);
}
void IconDialog::addFamilyButtonAction()
{
 addFamilySet();
 close();
}
void IconDialog::deleteButtonAction()
{
 deleteFamilySet();
 close();
}

// Only multiSensor adds and deletes icons
/*protected*/ void IconDialog::makeAddIconButtonPanel(QWidget* buttonPanel, QString addTip, QString deleteTip)
{
}

/**
* Action for both create new family and change existing family
*/
/*protected*/ bool IconDialog::doDoneAction()
{
 //check text
 QString family = _familyName->text();
 _parent->reset();
 checkIconSizes();
 ((FamilyItemPanel*)_parent)->_currentIconMap = _iconMap;
 if (_parent->isUpdate())
 {  // don't touch palette's maps.  just modify individual device icons
  return true;
 }
 if (!_newIconSet && family==(_family))
 {
   ItemPalette::removeIconMap(_type, _family);
 }
 while (!ItemPalette::addFamily(_parent->_paletteFrame, _type, family, _iconMap))
 {
        /*
        family = JOptionPane.showInputDialog(_parent._paletteFrame, tr("EnterFamilyName"),
                tr("questionTitle"), JOptionPane.QUESTION_MESSAGE);
        if (family==NULL || family.trim().length()==0) {
            // bail out
            return false;
        }*/
  return false;
 }
 _parent->_family = family;
 _parent->updateFamiliesPanel();
 _parent->setFamily(family);
 return true;
}

/**
* Action item for add new family. set up a dialog with new icons
*/
/*protected*/ void IconDialog::addFamilySet()
{
 setVisible(false);
//        _parent.createNewFamilySet(_type);
 IconDialog* dialog = new IconDialog(_type, NULL, _parent, NULL);
 dialog->sizeLocate();
}

/**
* Action item for add delete family
*/
/*protected*/ void IconDialog::deleteFamilySet()
{
 ItemPalette::removeIconMap(_type, _familyName->text());
 _parent->_family = "";
 ((FamilyItemPanel*)_parent)->_currentIconMap = NULL;
 _parent->updateFamiliesPanel();
}

/*protected*/ void IconDialog::makeDoneButtonPanel(QWidget* buttonPanel)
{
 QWidget* panel0 = new QWidget();
 FlowLayout* fl;
 panel0->setLayout(fl = new FlowLayout());
 QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (doDoneAction()) {
//                    dispose();
//                }
//            }
//    });
 connect(doneButton, SIGNAL(clicked()), this, SLOT(doneAction()));
 fl->addWidget(doneButton);

 QPushButton* cancelButton = new QPushButton(tr("cancelButton"));
//    cancelButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _parent.updateFamiliesPanel();
//                dispose();
//            }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
 fl->addWidget(cancelButton);
 buttonPanel->layout()->addWidget(panel0);
}
void IconDialog::doneAction()
{
 if (doDoneAction())
 {
  //dispose();
  close();
 }
}
#if 0
/*protected*/ void IconDialog::makeCreateButtonPanel(QWidget* buttonPanel)
{
 QWidget* panel = new QWidget();
 FlowLayout* fl;
 panel->setLayout(fl = new FlowLayout());
 QPushButton* newFamilyButton = new QPushButton(tr("Create Icon Set"));
//    newFamilyButton.addActionListener(new ActionListener() {
//            //IconDialog dialog; never used?
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (doDoneAction()) {
//                    dispose();
//                }
//            }
//    });
 connect(newFamilyButton, SIGNAL(clicked()), this, SLOT(doneAction()));
 newFamilyButton->setToolTip(tr("Create an additonal set of icons for this device"));
 fl->addWidget(newFamilyButton);

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                dispose();
//            }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
 buttonPanel->layout()->addWidget(panel);
 fl->addWidget(cancelButton);
}
#endif
/*protected*/ QWidget* IconDialog::makeIconPanel(QHash<QString, NamedIcon*>* iconMap)
{
 if (iconMap==NULL)
 {
  log->error("iconMap is NULL for type "+_type+" family "+_family);
  return NULL;
 }
 QWidget* iconPanel = new QWidget();
 QGridLayout* gridbag = new QGridLayout();
 iconPanel->setLayout(gridbag);

 int cnt = _iconMap->size();
 int numCol = 2;
 if (cnt>6)
 {
  numCol = 3;
 }
 GridBagConstraints c;// =  GridBagConstraints();
 c.fill = GridBagConstraints::NONE;
 c.anchor = GridBagConstraints::CENTER;
 c.weightx = 1.0;
 c.weighty = 1.0;
 int gridwidth = cnt%numCol == 0 ? 1 : 2 ;
 c.gridwidth = gridwidth;
 c.gridheight = 1;
 c.gridx = -gridwidth;
 c.gridy = 0;

 if (log->isDebugEnabled()) log->debug("makeIconPanel: for "+QString::number(iconMap->size())+" icons. gridwidth= "+QString::number(gridwidth));
 int panelWidth = 0;
 QHashIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  double scale = icon->reduceTo(100, 100, 0.2);
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  QGroupBox* panel = new QGroupBox();
  QVBoxLayout* panelLayout;
  panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
  QString borderName = ItemPalette::convertText(it.key());
//  panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
//               borderName));
  panel->setTitle(borderName);
  panel->setStyleSheet(gbStyleSheet);

  //panel.add(Box.createHorizontalStrut(100));
  panelLayout->addStrut(100);
  DropJLabel* image = new DropJLabel(icon, _iconMap, _parent->isUpdate());
  image->setName(it.key());
  image->setAcceptDrops(true);
  if (icon->getIconWidth()<1 || icon->getIconHeight()<1)
  {
   image->setText(tr("invisibleIcon"));
//   image->setForeground(QColor(Qt::lightGray));
  }
  image->setToolTip(icon->getName());
  QWidget* iPanel = new QWidget();
  iPanel->setLayout(new QVBoxLayout);
  iPanel->layout()->addWidget(image);
//  iPanel->setAcceptDrops(true);
//  panel->setAcceptDrops(true);


  c.gridx += gridwidth;
  if (c.gridx >= numCol*gridwidth)
  { //start next row
   c.gridy++;
   if (cnt < numCol)
   { // last row
    QWidget* p =  new QWidget();
    QVBoxLayout* pl1;
    p->setLayout(pl1 = new QVBoxLayout(p/*, BoxLayout.X_AXIS*/));
    panelWidth = panel->sizeHint().width();
    //p.add(Box.createHorizontalStrut(panelWidth));
    pl1->addStrut(panelWidth);
    c.gridx = 0;
    c.gridwidth = 1;
    //gridbag.setConstraints(p, c);
    gridbag->addWidget(p, c.gridy, c.gridx, c.rowSpan(), c.colSpan());
   //if (log-> isDebugEnabled()) log-> debug("makeIconPanel: gridx= "+c.gridx+" gridy= "+c.gridy);
//    iconPanel->layout()->addWidget(p);
    c.gridx = numCol-cnt;
    c.gridwidth = gridwidth;
   //c.fill = GridBagConstraints.NONE;
   }
   else
   {
    c.gridx = 0;
   }
  }
  cnt--;

  if (log-> isDebugEnabled()) log-> debug("makeIconPanel: icon width= "+QString::number(icon->getIconWidth())+" height= "+QString::number(icon->getIconHeight()));
  if (log-> isDebugEnabled()) log-> debug("makeIconPanel: gridx= "+QString::number(c.gridx)+" gridy= "+QString::number(c.gridy));
  panelLayout->addWidget(iPanel,0,Qt::AlignCenter);
  JLabel* label = new JLabel(tr("scale %1:1").arg( CatalogPanel::printDbl(scale,2)));
//  QWidget* sPanel = new QWidget();
//  sPanel->setLayout(new QHBoxLayout);
  QHBoxLayout* sPanelLayout = new QHBoxLayout;
  sPanelLayout->addWidget(label);
  panelLayout->addLayout(sPanelLayout);
  panelLayout->addStrut(20);
  //gridbag.setConstraints(panel, c);
  gridbag->addWidget(panel, c.gridy, c.gridx, c.rowSpan(), c.colSpan());
//  iconPanel->layout()->addWidget(panel);
 }
 if (panelWidth > 0)
 {
  QWidget* p =  new QWidget();
  QHBoxLayout* phl;
  p->setLayout(phl = new QHBoxLayout(p/*, BoxLayout.X_AXIS*/));
  phl->addStrut(panelWidth);
  c.gridx = numCol*gridwidth-1;
  c.gridwidth = 1;
  //gridbag.setConstraints(p, c);
  gridbag->addLayout(phl, c.gridy, c.gridx, c.rowSpan(), c.colSpan());
       //if (log-> isDebugEnabled()) log-> debug("makeIconPanel: gridx= "+c.gridx+" gridy= "+c.gridy);
  //iconPanel->layout()->addWidget(p);
 }
 return iconPanel;
}

void IconDialog::checkIconSizes()
{
 QListIterator <NamedIcon*> iter(_iconMap->values());
 int lastWidth = 0;
 int lastHeight = 0;
 bool first = true;
 while (iter.hasNext())
 {
  NamedIcon* icon = iter.next();
  if (first)
  {
   lastWidth = icon->getIconWidth();
   lastHeight = icon->getIconHeight();
   first = false;
   continue;
  }
  int nextWidth = icon->getIconWidth();
  int nextHeight = icon->getIconHeight();
  if ((qAbs(lastWidth - nextWidth) > 3 || qAbs(lastHeight - nextHeight) > 3))
  {
//   JOptionPane.showMessageDialog(_parent._paletteFrame,
//                                         tr("IconSizeDiff"), tr("warnTitle"),
//                                         JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(_parent, tr("Warning"), tr("Icon size difference"));
   return;
  }
  lastWidth = nextWidth;
  lastHeight = nextHeight;
 }
 if (log-> isDebugEnabled()) log-> debug("Size: width= "+QString::number(lastWidth)+", height= "+QString::number(lastHeight));
}

/*protected*/ QHash<QString, NamedIcon*>* IconDialog::clone(QHash<QString, NamedIcon*>* map)
{
 QHash<QString, NamedIcon*>* clone = NULL;
 if (map!=NULL)
 {
  clone = new QHash<QString, NamedIcon*>();
  QHashIterator<QString, NamedIcon*> it(*map);
  while (it.hasNext())
  {
   it.next();
   clone->insert(it.key(), new NamedIcon(it.value()));
  }
 }
 return clone;
}

