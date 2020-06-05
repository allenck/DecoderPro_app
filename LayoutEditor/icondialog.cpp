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
/*public*/ IconDialog::IconDialog(QString type, QString family, FamilyItemPanel* parent, QMap<QString, NamedIcon *> *iconMap )
 : ItemDialog(type, family, tr("Show Icons for %1").arg(type), parent, true)
{
//    super(type, family,
 QVBoxLayout* thisLayout = new QVBoxLayout(this);
 _newIconSet = false;
 log = new Logger("IconDialog");
 QFont f = font();
 f.setPointSize(8);
 setFont(f);

 if (log->isDebugEnabled())
 {
     log->debug(tr("IconDialog ctor: for %1, family = %2").arg(type).arg(family));
 }
 _family = family;
 QWidget* panel = new QWidget();
 panel->setLayout(new QVBoxLayout()); //(panel, BoxLayout.Y_AXIS));
 panel->layout()->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));

 QWidget* p = new QWidget();
 QHBoxLayout* pLayout = new QHBoxLayout(p);
 _nameLabel = new JLabel(tr("Icon Set \"%1\".").arg(family));
 pLayout->addWidget(_nameLabel);
 panel->layout()->addWidget(p);
 JPanel* buttonPanel = new JPanel();
 buttonPanel->setLayout(new QVBoxLayout()); //(buttonPanel, BoxLayout.Y_AXIS));
 makeDoneButtonPanel(buttonPanel, iconMap);
 // null method for all except multisensor.
 makeAddIconButtonPanel(buttonPanel, "Add an additional Sensor position to this Icon Set", "Delete the last Sensor position from this Icon Set");

 if (!(type==("IndicatorTO") || type==("MultiSensor") || type==("SignalHead"))) {
     ItemPanel::checkIconMap(type, _iconMap);
 }

 _iconEditPanel = new ImagePanel();
 makeIconPanel(_iconMap, _iconEditPanel);
 panel->layout()->addWidget(_iconEditPanel);	// put icons above buttons
 panel->layout()->addWidget(buttonPanel);

 p = new QWidget();
 p->setLayout(new QVBoxLayout());//(p, BoxLayout.Y_AXIS));
 p->layout()->addWidget(panel);
 _catalog = makeCatalog();
 p->layout()->addWidget(_catalog);

 QScrollArea* sp = new QScrollArea();
// setContentPane(sp);
 sp->setWidgetResizable(true);
 sp->setWidget(p);
 thisLayout->addWidget(sp);
 setLocationRelativeTo(_parent);
 setVisible(true);
 pack();
}

/*private*/ CatalogPanel* IconDialog::makeCatalog() {
    CatalogPanel* catalog = CatalogPanel::makeDefaultCatalog(false, false, true);
    catalog->setToolTip(tr("Drag an icon from the Preview pane to add it to the Control Panel"));
    ImagePanel* panel = catalog->getPreviewPanel();
    if (!_parent->isUpdate()) {
        panel->setImage(_parent->_backgrounds->at(_parent->getParentFrame()->getPreviewBg()));
    } else {
        panel->setImage(_parent->_backgrounds->at(0));   //update always should be the panel background
    }
    return catalog;
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

// for _parent to update background of icon editing el
/*protected*/ ImagePanel* IconDialog::getIconEditPanel() {
    return _iconEditPanel;
}

// for _parent to update background of icon editing el
/*protected*/ ImagePanel* IconDialog::getCatalogPreviewPanel() {
    return _catalog->getPreviewPanel();
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
 _parent->setIconMap(_iconMap);
 if (log->isDebugEnabled()) {
     log->debug(tr("doDoneAction: iconMap size= %1 for %2 \"%3\"").arg(_iconMap->size()).arg(_type).arg( _family));
 }
 if (!_parent->isUpdate()) {  // don't touch palette's maps. just modify individual device icons
     ItemPalette::removeIconMap(_type, _family);
     return _parent->addFamily(_type, _family, _iconMap);
 } else if (!_parent->isUnstoredMap()) {
     JOptionPane::showMessageDialog(_parent->_paletteFrame,
             tr("Family name \"%1\" is the name of a\ndifferent icon set for {1}s in the Catalog.\nPlease change the name.").arg(_family).arg(_type),
             tr("Warning"), JOptionPane::WARNING_MESSAGE);
     return false;
 } else {
     _parent->updateFamiliesPanel();
 }
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

/**
 * Action item to rename an icon family.
 */
/*protected*/ void IconDialog::renameFamily() {
    QString family = JOptionPane::showInputDialog(_parent, tr("Enter a name for this icon set."),
            tr("Rename Icon Set"), JOptionPane::QUESTION_MESSAGE);
    family = _parent->getValidFamilyName(family);
    if (!_parent->isUpdate()) {
        if (family != "" && family.trimmed().length() > 0) {
            ItemPalette::removeIconMap(_type, _family);
            _family = family;
            _parent->addFamily(_type, _family, _iconMap);
        }
    } else {
        if (family == "" || family.trimmed().length() == 0) {
            _family = tr("unNamed");
        } else {
            _family = family;
        }
        _parent->setFamily(_family);
        _parent->updateFamiliesPanel();
    }
    _nameLabel->setText(tr("Icon Set \"%1\".").arg(_family));
    update();
    repaint();
}

/*protected*/ void IconDialog::makeDoneButtonPanel(QWidget* buttonPanel, QMap<QString, NamedIcon*>* iconMap)
{
 if (iconMap != nullptr) {
     _iconMap = IconDialog::clone(iconMap);
     makeDoneButtonPanel(buttonPanel, tr("Done"));
 } else {
     _iconMap = ItemPanel::makeNewIconMap(_type);
     makeDoneButtonPanel(buttonPanel, tr("Add New Family"));
 }
}

/*protected*/ void IconDialog::makeDoneButtonPanel(QWidget* buttonPanel, QString text)
{
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());
    QPushButton* doneButton = new QPushButton((text));
//    doneButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            if (doDoneAction()) {
//                dispose();
//            }
//        }
//    });
    connect(doneButton, SIGNAL(clicked()), this, SLOT(doneAction()));
    panel->layout()->addWidget(doneButton);

    QPushButton* renameButton = new QPushButton(tr("Rename Family"));
//    renameButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            renameFamily();
//        }
//    });
    connect(renameButton, SIGNAL(clicked(bool)), this, SLOT(renameFamily()));
    panel->layout()->addWidget(renameButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            dispose();
//        }
//    });
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(dispose()));
    panel->layout()->addWidget(cancelButton);
    buttonPanel->layout()->addWidget(panel);
}

void IconDialog::doneAction()
{
 if (doDoneAction())
 {
  //dispose();
  close();
 }
}
 /*protected*/ void IconDialog::makeIconPanel(QMap<QString, NamedIcon*>* iconMap, ImagePanel* iconPanel)
{
//   TODO: iconPanel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black, 1),
//            tr("PreviewBorderTitle")));
    if (!_parent->isUpdate()) {
        iconPanel->setImage(_parent->_backgrounds->at(_parent->getParentFrame()->getPreviewBg()));
    } else {
        iconPanel->setImage(_parent->_backgrounds->at(0));   //update always should be the panel background
    }
    log->debug(tr("iconMap size = %1").arg(_iconMap->size()));
    _parent->addIconsToPanel(iconMap, iconPanel, true);
    iconPanel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black, 1),
                tr("Preview")));
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

//@Override
/*public*/ void IconDialog::dispose() {
    closeDialogs();
    ItemDialog::dispose();
}
