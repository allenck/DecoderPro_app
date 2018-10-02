#include "tableitempanel.h"
#include "jtextfield.h"
#include "jmripanel.h"
#include "picklistmodel.h"
#include "QTableView"
#include "jmrijframe.h"
#include "familyitempanel.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
#include "namedbean.h"
#include <QMessageBox>
#include "turnouticon.h"
#include "editor.h"
#include "sensoricon.h"
#include "lighticon.h"
#include "flowlayout.h"
#include "borderlayout.h"
#include "addnewdevicepanel.h"
#include "jdialog.h"
#include "dataflavor.h"
#include "sensoriconxml.h"
#include "turnouticonxml.h"
#include "lighticonxml.h"

//TableItemPanel::TableItemPanel(QWidget *parent) :
//    FamilyItemPanel(parent)
//{
//}
/**
*  JPanels for the various item types that come from tool Tables - e.g. Sensors, Turnouts, etc.
*/
///*public*/ class TableItemPanel extends FamilyItemPanel implements ListSelectionListener {

    /**
    * Constructor for all table types.  When item is a bean, the itemType is the name key
    * for the item in jmri.NamedBeanBundle.properties
    */
/*public*/ TableItemPanel::TableItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent)
    : FamilyItemPanel(parentFrame,  type, family, editor, parent)
{
 //super(parentFrame,  type, family, editor);
  log = new Logger("TableItemPanel");
  //_table = NULL;
 _model = model;
 _sysNametext = new JTextField();
 _userNametext = new JTextField();
 //_initialized = false;
 _table = NULL;
}

/**
* Init for creation
* insert table
*/
/*public*/ void TableItemPanel::init()
{
 if (!_initialized)
 {
  FamilyItemPanel::init();
  //((QVBoxLayout*)layout())->addWidget(initTablePanel(_model, _editor),0,Qt::AlignTop/*, 0*/);      // top of Panel
  ((QBoxLayout*)layout())->insertWidget(0,initTablePanel(_model, _editor));
  //((BorderLayout*)layout())->addWidget(initTablePanel(_model,_editor),BorderLayout::North);
 }
}

/**
* Init for update of existing indicator turnout
* _bottom3Panel has "Update Panel" button put into _bottom1Panel
*/
/*public*/ void TableItemPanel::init(ActionListener* doneAction, QHash<QString, NamedIcon*>* iconMap)
{
    FamilyItemPanel::init(doneAction, iconMap);
    thisLayout->addWidget(initTablePanel(_model, _editor)/*, 0*/);
}

/**
*  top Panel
*/
/*protected*/ QWidget* TableItemPanel::initTablePanel(PickListModel* model, Editor* editor)
{
 _table = model->makePickTable();
 //_table->setMinimumHeight(100);
 _table->setSelectionBehavior(QAbstractItemView::SelectRows);
 _table->setSelectionMode(QAbstractItemView::SingleSelection);
 QFont font = _table->font();
 font.setPointSize(8);
 _table->setFont(font);
//    _table->getSelectionModel().addListSelectionListener(this);
 ROW_HEIGHT = _table->getRowHeight(0);
 QWidget* topPanel = new QWidget();
 //topPanel->setLayout(new BorderLayout());
 QGridLayout* topPanelLayout;
 topPanel->setLayout(topPanelLayout = new QGridLayout);
// topPanel->setMinimumHeight(60);
 //topPanel->resize(300,120);
    //((BorderLayout*)topPanelLayout)->addWidget(new QLabel(model->getName())/* SwingConstants.CENTER)*/, BorderLayout::North);
 topPanelLayout->addWidget(new QLabel(model->getName()),0,0);
    //_scrollPane = new JScrollPane(_table);
    //((BorderLayout*)topPanelLayout)->addWidget(_table, BorderLayout::Center);
 topPanelLayout->addWidget(_table,1,0);
 topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
// QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
// sizePolicy.setHorizontalStretch(0);
// sizePolicy.setVerticalStretch(0);
// sizePolicy.setHeightForWidth(topPanel->sizePolicy().hasHeightForWidth());
// topPanel->setSizePolicy(sizePolicy);
 QSize dim = _table->sizeHint();
 if(ROW_HEIGHT > 0)
  dim.setHeight( ROW_HEIGHT*6);
    //_scrollPane.getViewport().setPreferredSize(dim);
 //_table->resize(dim);
 _table->setMaximumSize(dim);
 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout;
 panel->setLayout(panelLayout = new QHBoxLayout());
 _addTableButton = new QPushButton(tr("Add New Table Item"));
//    _addTableButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                makeAddToTableWindow();
//            }
//    });
 connect(_addTableButton, SIGNAL(clicked()), this, SLOT(makeAddToTableWindow()));
 _addTableButton->setToolTip(tr("Press to add a new item to the above table"));
 panelLayout->addWidget(_addTableButton);
 QPushButton* clearSelectionButton = new QPushButton(tr("Clear Table Selections"));
//    clearSelectionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _table.clearSelection();
//            }
//    });
 connect(clearSelectionButton, SIGNAL(clicked()), _table, SLOT(clearSelection()));
 clearSelectionButton->setToolTip(tr("ToolTipClearSelection"));
 panelLayout->addWidget(clearSelectionButton);
    //((BorderLayout*)topPanelLayout)->addWidget(panel, BorderLayout::South);
 topPanelLayout->addWidget(panel, 0, Qt::AlignHCenter);
 _table->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
    //_scrollPane->setToolTip(tr("ToolTipDragTableRow"));
 topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the panel"));
 return topPanel;
}
AddTableActionListener::AddTableActionListener(TableItemPanel *parent)
{
 this->parent = parent;
}
void AddTableActionListener::actionPerformed(ActionEvent *e)
{
 parent->addToTable();
}

/*protected*/ void TableItemPanel::makeAddToTableWindow() {
    _addTableDialog = new JDialog(_paletteFrame, tr("Add New Item to Table"), true);
//    ActionListener listener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                addToTable();
//            }
//        };
#if 1
    AddTableActionListener* listener = new AddTableActionListener(this);
    AtCancelListener* cancelListener = new AtCancelListener(this);
    JmriPanel* addPanel = new AddNewDevicePanel(
                _sysNametext, _userNametext, "addToTable", listener, cancelListener);
    _addTableDialog->getContentPane()->layout()->addWidget(addPanel);
    _addTableDialog->pack();
    _addTableDialog->setSize(_paletteFrame->size().width()-20, _addTableDialog->sizeHint().height());
    _addTableDialog->setLocation(10,35);
//    _addTableDialog->setLocationRelativeTo(_paletteFrame);
    _addTableDialog->toFront();
    _addTableDialog->setVisible(true);
#endif
}
AtCancelListener::AtCancelListener(TableItemPanel *self)
{
 this->self = self;
}
void AtCancelListener::actionPerformed()
{
 self->close();
}

/*protected*/ void TableItemPanel::addToTable()
{
 QString sysname = _sysNametext->text();
 if (sysname != NULL && sysname.length() > 1)
 {
  QString uname = _userNametext->text();
  if (uname!=NULL && uname.trimmed().length()==0)
  {
   uname = "";
  }
  try
  {
   NamedBean* bean = _model->addBean(sysname, uname);
   if (bean!=NULL)
   {
    int setRow = _model->getIndexOf(bean);
    if(log->isDebugEnabled()) log->debug("addToTable: row= "+QString::number(setRow)+", bean= "+bean->getDisplayName());
                //_table.setRowSelectionInterval(setRow, setRow);
                //_scrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
   }
//            _addTableDialog->dispose();
  }
  catch(IllegalArgumentException ex)
  {
//            JOptionPane.showMessageDialog(_paletteFrame, ex.getMessage(),
//                    ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(_paletteFrame, tr("Warning"), ex.getMessage());
  }
 }
 _sysNametext->setText("");
 _userNametext->setText("");
}

/**
* Used by Panel Editor to make the final installation of the icon(s)
* into the user's Panel.
* <P>Note! the selection is cleared. When two successive calls are made, the
* 2nd will always return NULL, regardless of the 1st return.
*/
/*public*/ NamedBean* TableItemPanel::getTableSelection()
{
 //int row = _table->getSelectedRow();
 int row = _table->currentIndex().row();
 if (row >= 0)
 {
  NamedBean* b = _model->getBeanAt(row);
  _table->clearSelection();
  _updateButton->setEnabled(false);
  if(log->isDebugEnabled()) log->debug("getTableSelection: row= "+QString::number(row)+", bean= "+b->getDisplayName());
  return b;
 }
 else if(log->isDebugEnabled()) log->debug("getTableSelection: row= "+QString::number(row));
 return NULL;
}

/*public*/ void TableItemPanel::setSelection(NamedBean* bean)
{
 int row = _model->getIndexOf(bean);
 log->debug("setSelection: NamedBean= "+bean->getSystemName()+", row= "+QString::number(row));
 if (row>=0)
 {
//        _table->addRowSelectionInterval(row, row);
       // _scrollPane.getVerticalScrollBar().setValue(row*ROW_HEIGHT);
  _table->selectRow(row);
 }
 else
 {
  valueChanged(/*NULL*/);
 }
}

/**
*  ListSelectionListener action
*/
/*public*/ void TableItemPanel::valueChanged(/*ListSelectionEvent e*/)
{
 if (_table == NULL || _updateButton==NULL)
 {
  return;
 }
 //int row = _table->getSelectedRow();
 int row = _table->currentIndex().row();
 if(log->isDebugEnabled()) log->debug("Table valueChanged: row= "+row);
 if (row >= 0)
 {
  _updateButton->setEnabled(true);
  _updateButton->setToolTip(NULL);

 }
 else
 {
  _updateButton->setEnabled(false);
  _updateButton->setToolTip(tr("ToolTipPickFromTable"));
 }
 hideIcons();
}

void TableItemPanel::OnSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
 if(selected.indexes().count() > 0)
  _updateButton->setEnabled(true);
 else
  _updateButton->setEnabled(false);

}

/*protected*/ NamedBean* TableItemPanel::getNamedBean() {
    if (_table == NULL) {
        return NULL;
    }
    //int row = _table->getSelectedRow();
    int row = _table->currentIndex().row();
    if(log->isDebugEnabled()) log->debug("getNamedBean: from table \""+_itemType+ "\" at row "+QString::number(row));
    if (row<0) {
//        	JOptionPane.showMessageDialog(NULL, tr("noRowSelected"),
//        				ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
        return NULL;
    }
    return _model->getBeanAt(row);
}

/*protected*/ DragJLabel* TableItemPanel::getDragger(DataFlavor* flavor, QHash<QString, NamedIcon*>* map) {
    return new TIconDragJLabel(flavor, map,this);
}

///*protected*/ class IconDragJLabel extends DragJLabel {
//    Hashtable<String, NamedIcon> iconMap;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
/*public*/ TIconDragJLabel::TIconDragJLabel(DataFlavor* flavor, QHash<QString, NamedIcon*>* map, TableItemPanel* self) : DragJLabel(flavor,self)
{
 //DragJLabel(flavor,(QWidget*)self);
 iconMap = map;
 this->self = self;
}
/*public*/ bool TIconDragJLabel::isDataFlavorSupported(DataFlavor* flavor)
{
 return DragJLabel::isDataFlavorSupported(flavor);
}
/*public*/ QObject* TIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException)
{
 Logger* log = new Logger("TIconDragJLabel");
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
  log->error("IconDragJLabel.getTransferData: NamedBean is NULL!");
  return NULL;
 }

 if (self->_itemType==("Turnout"))
 {
  TurnoutIcon* t = new TurnoutIcon(self->_editor);
  t->setTurnout(bean->getDisplayName());
  QHashIterator<QString, NamedIcon*> iter(* iconMap);
  while (iter.hasNext())
  {
   iter.next();
   t->setIcon(iter.key(), new NamedIcon(iter.value()));
  }
  t->setFamily(self->_family);
  t->setLevel(Editor::TURNOUTS);
  return t;
 }
 else if (self->_itemType==("Sensor"))
 {
  SensorIcon* s = new SensorIcon(new   NamedIcon("resources/icons/smallschematics/tracksegments/circuit-error.gif",
            "resources/icons/smallschematics/tracksegments/circuit-error.gif"), self->_editor);
  QHashIterator<QString, NamedIcon*> iter(*iconMap);
  while (iter.hasNext())
  {
   iter.next();
   s->setIcon(iter.key(), new NamedIcon(iter.value()));
  }
  s->setSensor(bean->getDisplayName());
  s->setFamily(self->_family);
  s->setLevel(Editor::SENSORS);
  return s;
 }
 else if (self->_itemType==("Light"))
 {
  LightIcon* l = new LightIcon(self->_editor);
  l->setOffIcon(iconMap->value("LightStateOff"));
  l->setOnIcon(iconMap->value("LightStateOn"));
  l->setInconsistentIcon(iconMap->value("BeanStateInconsistent"));
  l->setUnknownIcon(iconMap->value("BeanStateUnknown"));
  l->setLight((Light*)bean);
  l->setLevel(Editor::LIGHTS);
  return l;
 }
 return NULL;
}
QString TIconDragJLabel::mimeData()
{
 NamedBean* bean = self-> getTableSelection();
 if(bean == NULL)
 {
  QMessageBox::warning(self, tr("Warning"), tr("You must select a %1 from the table").arg(self->_itemType));
     return "";
 }
 //DataFlavor* flavor;
 QString xmldata;
 if(self->_itemType == "Turnout")
 {
     //return bean->getSystemName()+ ";TurnoutIcon";
  TurnoutIcon* icon;
  _dataFlavor = new DataFlavor(icon = new TurnoutIcon(NULL),"TurnoutIcon");
  icon->setTurnout(bean->getSystemName());
  icon->setFamily(self->_family);
  QHashIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
  while (iter.hasNext())
  {
    iter.next();
    icon->setIcon(iter.key(), iter.value());
  }
  _dataFlavor->setMimeTypeParameter("turnout", bean->getSystemName());
  _dataFlavor->setMimeTypeParameter("family", self->_family);
  TurnoutIconXml* xml = new TurnoutIconXml();
  QDomElement e = xml->store((QObject*)icon);
  xml->doc.appendChild(e);
  xmldata = xml->doc.toString();
 }
 else  if(self->_itemType == "Sensor")
 {
  //return bean->getSystemName()+ ";SensorIcon";
  SensorIcon* icon;
  _dataFlavor = new DataFlavor(icon = new SensorIcon(NULL),"SensorIcon");\
  icon->setSensor(bean->getSystemName());
  icon->setFamily(self->_family);
  QHashIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
  while (iter.hasNext())
  {
    iter.next();
    icon->setIcon(iter.key(), iter.value());
  }
  _dataFlavor->setMimeTypeParameter("sensor", bean->getSystemName());
  SensorIconXml* xml = new SensorIconXml();
  QDomElement e = xml->store((QObject*)icon);
  xml->doc.appendChild(e);
  xmldata = xml->doc.toString();
 }
 else  if(self->_itemType == "Light")
 {
  //return bean->getSystemName()+ ";LightIcon";
  LightIcon* icon;
  _dataFlavor = new DataFlavor(icon = new LightIcon(self->_editor),"LightIcon");\
  icon->setLight(bean->getSystemName());
  icon->setFamily(self->_family);
  QHashIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
  while (iter.hasNext())
  {
    iter.next();
    icon->setIcon( iter.value());
  }
  _dataFlavor->setMimeTypeParameter("light", bean->getSystemName());
  LightIconXml* xml = new LightIconXml();
  QDomElement e = xml->store((QObject*)icon);
  xml->doc.appendChild(e);
  xmldata = xml->doc.toString();
 }
 _dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));
 return _dataFlavor->toString();
}

//};

