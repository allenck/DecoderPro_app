#include "icondialog.h"
#include <QBoxLayout>
#include "itempalette.h"
#include "itempanel.h"
#include "jtextfield.h"
#include "familyitempanel.h"
#include "flowlayout.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "namedicon.h"
#include "dropjlabel.h"
#include "catalogpanel.h"
#include "QMessageBox"
#include <QGroupBox>
#include "joptionpane.h"
#include "box.h"
#include <QScrollArea>
#include "borderfactory.h"

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
/*public*/ IconDialog::IconDialog(QString type, QString family, FamilyItemPanel* parentPanel, QMap<QString, NamedIcon *> *iconMap, QWidget* parent)
 : ItemDialog(type, tr("Show Icons for %1").arg(family), parent)
{
//    super(type, family,
 //QVBoxLayout* thisLayout = new QVBoxLayout(this);
 log = new Logger("IconDialog");
 QFont f = font();
 f.setPointSize(8);
 setFont(f);

 if (log->isDebugEnabled())
 {
  log->debug(tr("IconDialog ctor: for %1, family = %2").arg(type).arg(family));
 }
 _family = family;
 _parent = parentPanel;
 JPanel* panel = new JPanel();
 panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
 panel->layout()->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));

 JPanel* p = new JPanel(new FlowLayout());
 p->layout()->addWidget(new JLabel(tr("Icon Set \"%1\".").arg(family)));
 panel->layout()->addWidget(p);
 JPanel* buttonPanel = new JPanel();
 buttonPanel->setLayout(new QVBoxLayout());//buttonPanel, BoxLayout.Y_AXIS));
 if (iconMap != nullptr) {
     _iconMap = clone(iconMap);
     makeDoneButtonPanel(buttonPanel, tr("Done"));
 } else {
     _iconMap = ItemPanel::makeNewIconMap(type);
     makeDoneButtonPanel(buttonPanel, tr("Add New Icon Set"));
 }
 // null method for all except multisensor.
 makeAddIconButtonPanel(buttonPanel, "Add an additional Sensor position to this icon set ", "Delete the last Sensor position from this icon set");

 if (!(type == ("IndicatorTO") || type == ("MultiSensor"))) {
     ItemPanel::checkIconMap(type, _iconMap);
 }
 _iconPanel = makeIconPanel(_iconMap);
 panel->layout()->addWidget(_iconPanel);	// put icons above buttons
 panel->layout()->addWidget(buttonPanel);
 //panel.setMaximumSize(panel.getPreferredSize());

 p = new JPanel();
 p->setLayout(new QVBoxLayout());//p, BoxLayout.Y_AXIS));
 p->layout()->addWidget(panel);
 _catalog = CatalogPanel::makeDefaultCatalog();
 _catalog->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 p->layout()->addWidget(_catalog);

 setContentPane(p);
 pack();
}

// Only multiSensor adds and deletes icons
/*protected*/ void IconDialog::makeAddIconButtonPanel(JPanel */*buttonPanel*/, QString /*addTip*/, QString /*deleteTip*/)
{
}

/**
 * Action for both create new family and change existing family
 */
/*protected*/ bool IconDialog::doDoneAction()
{
 _parent->reset();
//        checkIconSizes();
 _parent->_currentIconMap = _iconMap;
 if (!_parent->isUpdate())
 {  // don't touch palette's maps.  just modify individual device icons
     ItemPalette::removeIconMap(_type, _family);
     if (!ItemPalette::addFamily(_parent->_paletteFrame, _type, _family, _iconMap))
     {
         return false;
     } else {
         _parent->updateFamiliesPanel();
         _parent->setFamily(_family);
     }
 }
 return true;
}

/*protected*/ void IconDialog::makeDoneButtonPanel(JPanel* buttonPanel, QString text) {
    JPanel* panel = new JPanel();
    panel->setLayout(new FlowLayout());
    QPushButton* doneButton = new QPushButton(text);
//        doneButton.addActionListener(new ActionListener() {
//            public void actionPerformed(ActionEvent a) {
    connect(doneButton, &QPushButton::clicked, [=] {
            if (doDoneAction()) {
             close();
//                dispose();
            }
//            }
    });
    panel->layout()->addWidget(doneButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//        cancelButton.addActionListener(new ActionListener() {
//            public void actionPerformed(ActionEvent a) {
    connect(cancelButton, &QPushButton::clicked, [=]{
     close();
//            dispose();
//            }
    });
    panel->layout()->addWidget(cancelButton);
    buttonPanel->layout()->addWidget(panel);
}

/*protected*/ JPanel* IconDialog::makeIconPanel(QMap<QString, NamedIcon*>* iconMap)
{
 if (iconMap == nullptr) {
     log->error("iconMap is null for type " + _type + " family " + _family);
     return nullptr;
 }
 JPanel* iconPanel = new JPanel();
 GridBagLayout* gridbag = new GridBagLayout();
 iconPanel->setLayout(gridbag);

 int cnt = _iconMap->size();
 int numCol = cnt;
 if (cnt > 6) {
     numCol = 6;
 }
 GridBagConstraints c = GridBagConstraints();
 c.fill = GridBagConstraints::NONE;
 c.anchor = GridBagConstraints::CENTER;
 c.weightx = 1.0;
 c.weighty = 1.0;
 int gridwidth = cnt % numCol == 0 ? 1 : 2;
 c.gridwidth = gridwidth;
 c.gridheight = 1;
 c.gridx = -gridwidth;
 c.gridy = 0;

 if (log->isDebugEnabled()) {
     log->debug("makeIconPanel: for " + QString::number(iconMap->size()) + " icons. gridwidth= " +  QString::number(gridwidth));
 }
 int panelWidth = 0;
 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext()) {
     /*Entry<String, NamedIcon> entry = */it.next();
     NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
     double scale = icon->reduceTo(100, 100, 0.2);
     JPanel* panel = new JPanel();
     panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
     QString borderName = ItemPalette::convertText(it.key());
     panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
             borderName));
     panel->layout()->addWidget(Box::createHorizontalStrut(100));
     DropJLabel* image = new DropJLabel(icon, _iconMap, _parent->isUpdate());
     image->setName(it.key());
     if (icon->getIconWidth() < 1 || icon->getIconHeight() < 1) {
         image->setText(tr("Invisible Icon"));
         image->setForeground(Qt::lightGray);
     }
     image->setToolTip(icon->getName());
     JPanel* iPanel = new JPanel(new QHBoxLayout());
     iPanel->layout()->addWidget(image);

     c.gridx += gridwidth;
     if (c.gridx >= numCol * gridwidth)
     { //start next row
      c.gridy++;
      if (cnt < numCol)
      { // last row
       JPanel* p = new JPanel();
       p->setLayout(new QHBoxLayout());//p, BoxLayout.X_AXIS));
       panelWidth = panel->sizeHint().width();
       p->layout()->addWidget(Box::createHorizontalStrut(panelWidth));
       c.gridx = 0;
       c.gridwidth = 1;
       //gridbag.setConstraints(p, c);
       ((GridBagLayout*)iconPanel->layout())->addWidget(p, c);
       c.gridx = numCol - cnt;
       c.gridwidth = gridwidth;
       //c.fill = GridBagConstraints.NONE;
      } else {
          c.gridx = 0;
      }
     }
     cnt--;

     panel->layout()->addWidget(iPanel);
     JLabel* label = new JLabel(tr("scale %1:1").arg(
             CatalogPanel::printDbl(scale, 2)));
     JPanel* sPanel = new JPanel(new FlowLayout);
     sPanel->layout()->addWidget(label);
     panel->layout()->addWidget(sPanel);
     panel->layout()->addWidget(Box::createHorizontalStrut(20));
     //gridbag.setConstraints(panel, c);
     panel->setMaximumSize(110, 110);
     ((GridBagLayout*)iconPanel->layout())->addWidget(panel,c);
 }
 if (panelWidth > 0) {
     JPanel* p = new JPanel();
     p->setLayout(new QVBoxLayout());//p, BoxLayout.X_AXIS));
     p->layout()->addWidget(Box::createHorizontalStrut(panelWidth));
     c.gridx = numCol * gridwidth - 1;
     c.gridwidth = 1;
     //gridbag.setConstraints(p, c);
     ((GridBagLayout*)iconPanel->layout())->addWidget(p,c);
 }
 return iconPanel;
}


/*protected*/ QMap<QString, NamedIcon*>* IconDialog::clone(QMap<QString, NamedIcon*>* map)
{
 QMap<QString, NamedIcon*>* clone = NULL;
 if (map!=NULL)
 {
  clone = new QMap<QString, NamedIcon*>();
  QMapIterator<QString, NamedIcon*> it(*map);
  while (it.hasNext())
  {
   it.next();
   clone->insert(it.key(), new NamedIcon(it.value()));
  }
 }
 return clone;
}

/*protected*/ void IconDialog::sizeLocate() {
    resize(_parent->size().width(), this->getPreferredSize().height());
//        setLocationRelativeTo(_parent);
    setVisible(true);
    pack();
}

/*public*/ QString IconDialog::getClassName() {return "jmri.jmrit.display.palette.IconDialog";}
