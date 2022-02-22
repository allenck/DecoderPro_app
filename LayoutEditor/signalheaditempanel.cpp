#include "signalheaditempanel.h"
#include <QVBoxLayout>
#include "picklistmodel.h"
#include <QLabel>
#include "itempalette.h"
#include <QMessageBox>
#include "signalhead.h"
#include <QHash>
#include "signalheadicon.h"
#include "editor.h"
#include <QHash>
#include "dataflavor.h"
#include "borderlayout.h"
#include "signalheadiconxml.h"
#include "abstractsignalhead.h"
#include "imagepanel.h"
#include "signalheadicondialog.h"
#include "joptionpane.h"

//SignalHeadItemPanel::SignnalHeadItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
///*public*/ class SignalHeadItemPanel extends TableItemPanel {//implements ListSelectionListener {

    /*public*/ SignalHeadItemPanel::SignalHeadItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor *editor, QWidget *parent)
 : TableItemPanel(parentFrame, type, family, model, editor, parent)
{
 //super(parentFrame, type, family, model, editor);
 log = new Logger("SignalHeadItemPanel");
 setObjectName("SignalHeadItemPanel");
}

/*protected*/ QWidget* SignalHeadItemPanel::initTablePanel(PickListModel* model, Editor* /*editor*/)
{
 _table = model->makePickTable();
 ROW_HEIGHT = _table->getRowHeight();
 QWidget* topPanel = new QWidget();
 //topPanel->setLayout(new BorderLayout);
 topPanel->setLayout(new QVBoxLayout);
 //((BorderLayout*)topPanel->layout())->addWidget(new QLabel(model->getName()/*, SwingConstants.CENTER*/), BorderLayout::North);
 ((QVBoxLayout*)topPanel->layout())->addWidget(new QLabel(model->getName()),0, Qt::AlignTop);
    //_scrollPane = new JScrollPane(_table);
 //((BorderLayout*)topPanel->layout())->addWidget(/*_scrollPane,*/_table, BorderLayout::Center);
 ((QVBoxLayout*)topPanel->layout())->addWidget(/*_scrollPane,*/_table, 0, Qt::AlignVCenter);
//    _table->getSelectionModel().addListSelectionListener(this);
 _table->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
    //_scrollPane->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
 topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
 QWidget* panel = new QWidget();
 panel->setLayout(new FlowLayout);
 QPushButton* clearSelectionButton = new QPushButton(tr("Clear Selection"));
//    clearSelectionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _table.clearSelection();
//            }
//    });
 connect(clearSelectionButton, SIGNAL(clicked()), _table, SLOT(clearSelection()));
 clearSelectionButton->setToolTip(tr("Clear selected table rows"));
 panel->layout()->addWidget(clearSelectionButton);
// ((BorderLayout*)topPanel->layout())->addWidget(panel, BorderLayout::South);
 //((BorderLayout*)topPanel->layout())->addWidget(panel, BorderLayout::South);
 ((QVBoxLayout*)topPanel->layout())->addWidget(panel,0, Qt::AlignBottom);
 return topPanel;
}

/*protected*/ void SignalHeadItemPanel::makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString displayKey) {
    TableItemPanel::makeDndIconPanel(iconMap, "SignalHeadStateRed");
}

/*protected*/ void SignalHeadItemPanel::showIcons() {
    //updateFamiliesPanel();
    _iconFamilyPanel->layout()->removeWidget(_iconPanel);
    _iconPanel = new JPanel(new FlowLayout());
    ((QVBoxLayout*)_iconFamilyPanel->layout())->insertWidget(0, _iconPanel);
    addIconsToPanel(_currentIconMap);
    _iconPanel->setVisible(true);
    if (!_update) {
        _dragIconPanel->setVisible(false);
    }
    _showIconsButton->setText(tr("Hide Icons"));
}

/*protected*/ void SignalHeadItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* allIconsMap) {
    QMap<QString, NamedIcon*>* iconMap = getFilteredIconMap(allIconsMap);
    if (iconMap == nullptr) {
        iconMap = ItemPalette::getIconMap(_itemType, _family);
        if (iconMap == nullptr) {
            _updateButton->setEnabled(false);
            _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the panel"));
        }
    } else {
        TableItemPanel::addIconsToPanel(iconMap);
    }
}

/**
*  ListSelectionListener action
*/
/*public*/ void SignalHeadItemPanel::valueChanged(/*ListSelectionEvent e*/)
{
 if (_table == NULL || _updateButton==NULL)
 {
  return;
 }
 //int row = _table.getSelectedRow();
 int row = _table->currentIndex().row();

 if (log->isDebugEnabled()) log->debug("Table valueChanged: row= "+row);
 if (row >= 0)
 {
  _updateButton->setEnabled(true);
        _updateButton->setToolTip(NULL);
        if (_family!=NULL) {
            _currentIconMap = getFilteredIconMap(ItemPalette::getIconMap(_itemType, _family));
        }
    } else {
        _updateButton->setEnabled(false);
        _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the panel"));
    }
    if (_iconPanel->isVisible()) {
        showIcons();
    }
//       hideIcons();
}

/*protected*/ QMap<QString, NamedIcon *> *SignalHeadItemPanel::getFilteredIconMap(QMap<QString, NamedIcon*>* allIconsMap)
{
 if (allIconsMap==NULL)
 {
//        JOptionPane.showMessageDialog(_paletteFrame,
//                java.text.MessageFormat.format(tr("FamilyNotFound"),
//                                               tr(_itemType), _family),
//                ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
  QMessageBox::warning(_paletteFrame, tr("Warning"), tr("Icon Set \"%2\" not found in type \"%1\".").arg(_itemType).arg(_family));
  return NULL;
 }
 if (_table==NULL || /*_table->getSelectedRow()*/_table->currentIndex().row() <0)
 {
  return allIconsMap;
 }

 SignalHead* sh = (SignalHead*)getNamedBean()->self();
 if (sh!=NULL)
 {
  QStringList states = ((AbstractSignalHead*)sh)->getValidStateNames().toList();
  if (states.length() == 0)
  {
   return allIconsMap;
  }
  QMap<QString, NamedIcon*>* iconMap = new QMap<QString, NamedIcon*>();
  QMapIterator<QString, NamedIcon*>  it(*allIconsMap);
  while (it.hasNext())
  {
         //Entry<String, NamedIcon> entry = it.next();
   it.next();
   QString name = it.key();
   QString borderName = (name);
   for (int j=0; j<states.length(); j++)
   {
    if (borderName==(states.at(j)) ||
                name==("SignalHeadStateDark") ||
                name==("SignalHeadStateHeld"))
    {
     iconMap->insert(name, it.value());
     break;
    }
   }
  }
  if (log->isDebugEnabled()) log->debug("filteredMap size= "+QString::number(iconMap->size()));
   return iconMap;
 }
 if (log->isDebugEnabled()) log->debug("Map NOT filtered, size= "+QString::number(allIconsMap->size()));
  return allIconsMap;
}
#if 1
/*protected*/ DragJLabel* SignalHeadItemPanel::getDragger(DataFlavor* flavor, QMap<QString, NamedIcon *> *map, NamedIcon *icon) {
    return new SHIconDragJLabel(flavor, map, this);
}

///*protected*/ class IconDragJLabel* extends DragJLabel {
//    Hashtable <String, NamedIcon> iconMap;

//    @edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
/*public*/ SHIconDragJLabel::SHIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon *> *map, SignalHeadItemPanel* self) : DragJLabel(flavor)
{
    //super(flavor);
    iconMap = map;
    log = new Logger("IconDragJLabel");
    this->self = self;
}

/*public*/ QObject* SHIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException)
{
 if (!isDataFlavorSupported(flavor))
 {
  return NULL;
 }
 if (iconMap==NULL)
 {
  log->error("IconDragJLabel.getTransferData: iconMap is NULL!");
  return NULL;
 }
 NamedBean* bean = self->getNamedBean();
 if (bean==NULL)
 {
  JOptionPane::showMessageDialog(nullptr, tr("Select a row in the table to provide a device for this icon."),
             tr("Warning"), JOptionPane::WARNING_MESSAGE);
     return nullptr;
 }

 SignalHeadIcon* sh = new SignalHeadIcon(self->_editor);
 sh->setSignalHead(bean->getDisplayName());
 QMap <QString, NamedIcon*>* map = self->getFilteredIconMap(iconMap);
 QMapIterator<QString, NamedIcon*> iter(* map);
 while (iter.hasNext())
 {
  iter.next();
  //Entry<String, NamedIcon> ent = iter.next();
  sh->setIcon(iter.key(), new NamedIcon(iter.value()));
 }
 sh->setFamily(self->_family);
 sh->setLevel(Editor::SIGNALS);
 return sh;
}
QByteArray SHIconDragJLabel::mimeData()
{
 NamedBean* bean = self->getNamedBean();
 if (bean==NULL)
 {
  log->error("IconDragJLabel.getTransferData: NamedBean is NULL!");
  return NULL;
 }
 SignalHeadIcon* icon; _dataFlavor = new DataFlavor(icon = new SignalHeadIcon(self->_editor), "SignalHeadIcon");
 icon->setSignalHead(bean->getDisplayName());
 QMap <QString, NamedIcon*>* map = /*self->getFilteredIconMap*/(iconMap);
 QMapIterator<QString, NamedIcon*> iter(* map);
 while (iter.hasNext())
 {
  iter.next();
  //Entry<String, NamedIcon> ent = iter.next();
  icon->setIcon(ItemPalette::convertText(iter.key()), iter.value());
 }
 icon->setFamily(self->_family);
 icon->setLevel(Editor::SIGNALS);

 SignalHeadIconXml* xml = new SignalHeadIconXml();
 QDomElement e = xml->store((QObject*)icon);
 xml->doc.appendChild(e);
 QByteArray xmldata;
 xmldata.append(xml->doc.toString());
 return xmldata;
}

#endif
