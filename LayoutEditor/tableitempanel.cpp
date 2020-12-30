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
#include "defaultlistselectionmodel.h"
#include "joptionpane.h"

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
 setObjectName("TableItemPanel");
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
  thisLayout->insertWidget(0, initTablePanel(_model, _editor), 0, Qt::AlignTop); // top of Panel
  _buttonPosition = 1;
 }
}

/**
 * Init for update of existing indicator turnout _bottom3Panel has "Update
 * Panel" button put into _bottom1Panel
 */
/*public*/ void TableItemPanel::init(ActionListener* doneAction, QMap<QString, NamedIcon*>* iconMap)
{
 FamilyItemPanel::init(doneAction, iconMap);
 thisLayout->insertWidget(0, initTablePanel(_model, _editor));
 _buttonPosition = 1;
}

/**
*  top Panel
*/
/*protected*/ QWidget* TableItemPanel::initTablePanel(PickListModel* model, Editor* /*editor*/)
{
 _table = model->makePickTable();
 _table->setMinimumWidth(300);
 _table->setSelectionBehavior(QAbstractItemView::SelectRows);
 _table->setSelectionMode(QAbstractItemView::SingleSelection);
 QFont font = _table->font();
 font.setPointSize(8);
 _table->setFont(font);
 _table->getSelectionModel()->addListSelectionListener((ListSelectionListener*)this);
 ROW_HEIGHT = _table->getRowHeight();
 JPanel* topPanel = new JPanel();
 QVBoxLayout* topPanelLayout;
 topPanel->setLayout(topPanelLayout = new QVBoxLayout());//BorderLayout());
 topPanelLayout->addWidget(new QLabel(model->getName()), 0, Qt::AlignCenter);//SwingConstants.CENTER), BorderLayout.NORTH);
// _scrollPane = new JScrollPane(_table);
// int cnt = Math.min(8, _table.getRowCount()) + 2;
// _scrollPane.setPreferredSize(new Dimension(_scrollPane.getPreferredSize().width, cnt*ROW_HEIGHT));
 topPanelLayout->addWidget(/*_scrollPane*/_table,2, Qt::AlignHCenter);// BorderLayout.CENTER);
 topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the Panel"));

 JPanel* panel = new JPanel();
 FlowLayout* panelLayout = new FlowLayout(panel);
 _addTableButton = new QPushButton(tr("Add New Table Item..."));
// _addTableButton.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent a) {
 connect(_addTableButton, &QPushButton::clicked, [=] {
         makeAddToTableWindow();
//     }
 });
 _addTableButton->setToolTip(tr("Press to add a new item to the table"));
 panelLayout->addWidget(_addTableButton);
 QPushButton* clearSelectionButton = new QPushButton(tr("Clear Table Selections"));
// clearSelectionButton.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent a) {
 connect(clearSelectionButton, &QPushButton::clicked, [=]{
//         _table.clearSelection();
         hideIcons();
//     }
 });
 clearSelectionButton->setToolTip(tr("Clear selected table rows"));
 panelLayout->addWidget(clearSelectionButton);
 topPanelLayout->addWidget(panel, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
 _table->setToolTip(tr("Drag a row from the table to add a label of the item to the Panel"));
 //_scrollPane.setToolTip(tr("Drag a row from the table to add a label of the item to the Panel"));
 topPanel->setToolTip(tr("Drag a row from the table to add a label of the item to the Panel"));
 return topPanel;
}

AddTableActionListener::AddTableActionListener(TableItemPanel *parent)
{
 this->parent = parent;
}
void AddTableActionListener::actionPerformed(JActionEvent *e)
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
}

AtCancelListener::AtCancelListener(TableItemPanel *self)
{
 this->self = self;
}
void AtCancelListener::actionPerformed()
{
 //self->close();
 self->cancelPressed();
}

void TableItemPanel::cancelPressed(/*ActionEvent e*/) {
    _addTableDialog->setVisible(false);
    _addTableDialog->dispose();
    _addTableDialog = nullptr;
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
 if(qobject_cast<QSortFilterProxyModel*>( _table->model()))
 {
  row = ((QSortFilterProxyModel*)_table->model())->mapToSource(_table->currentIndex()).row();
 }
 if (row >= 0)
 {
  NamedBean* b = _model->getBeanAt(row);
  _table->clearSelection();
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
  valueChanged(new ListSelectionEvent(this, row,row, false));
 }
}

/**
*  ListSelectionListener action
*/
/*public*/ void TableItemPanel::valueChanged(ListSelectionEvent* e)
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
    if (_table == nullptr) {
        return nullptr;
    }
    int row = _table->getSelectedRow();
    if (log->isDebugEnabled()) {
        log->debug("getNamedBean: from table \"" + _itemType + "\" at row " + QString::number(row));
    }
    if (row < 0) {
        return nullptr;
    }
    return _model->getBeanAt(row);
}

/*protected*/ DragJLabel* TableItemPanel::getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon) {
    return new TIconDragJLabel(flavor, map, icon, this);
}

///*protected*/ class IconDragJLabel extends DragJLabel {
//    Hashtable<String, NamedIcon> iconMap;

    //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP2") // icon map is within package
/*public*/ TIconDragJLabel::TIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon,TableItemPanel* self) : DragJLabel(flavor,self)
{
 //DragJLabel(flavor,(QWidget*)self);
 iMap = map;
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
 if (iMap==NULL)
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

 if (self->_itemType==("Turnout"))
 {
  TurnoutIcon* t = new TurnoutIcon(self->_editor);
  t->setTurnout(bean->getDisplayName());
  QMapIterator<QString, NamedIcon*> iter(* iMap);
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
  SensorIcon* s = new SensorIcon(new   NamedIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif",
            "resources/icons/smallschematics/tracksegments/circuit-error.gif"), self->_editor);
  QMapIterator<QString, NamedIcon*> iter(*iMap);
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
  l->setOffIcon(iMap->value("StateOff"));
  l->setOnIcon(iMap->value("StateOn"));
  l->setInconsistentIcon(iMap->value("BeanStateInconsistent"));
  l->setUnknownIcon(iMap->value("BeanStateUnknown"));
  l->setLight((Light*)bean);
  l->setLevel(Editor::LIGHTS);
  return l;
 }
 return NULL;
}

QByteArray TIconDragJLabel::mimeData()
{
 NamedBean* bean = self-> getTableSelection();
 if(bean == NULL)
 {
  QMessageBox::warning(self, tr("Warning"), tr("You must select a %1 from the table").arg(self->_itemType));
     return "";
 }
 //DataFlavor* flavor;
 QByteArray xmldata;
 if(self->_itemType == "Turnout")
 {
  TurnoutIcon* icon;
  _dataFlavor = new DataFlavor(icon = new TurnoutIcon(self->_editor),"TurnoutIcon");
  icon->setTurnout(bean->getSystemName());
  icon->setFamily(self->_family);
  QMapIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
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
  xmldata.append(xml->doc.toString());
  delete icon;
 }
 else  if(self->_itemType == "Sensor")
 {
  //return bean->getSystemName()+ ";SensorIcon";
  SensorIcon* icon;
  _dataFlavor = new DataFlavor(icon = new SensorIcon(self->_editor),"SensorIcon");\
  icon->setSensor(bean->getSystemName());
  icon->setFamily(self->_family);
  QMapIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
  while (iter.hasNext())
  {
    iter.next();
    icon->setIcon(iter.key(), iter.value());
  }
  _dataFlavor->setMimeTypeParameter("sensor", bean->getSystemName());
  SensorIconXml* xml = new SensorIconXml();
  QDomElement e = xml->store((QObject*)icon);
  xml->doc.appendChild(e);
  xmldata.append(xml->doc.toString());
 }
 else  if(self->_itemType == "Light")
 {
  //return bean->getSystemName()+ ";LightIcon";
  LightIcon* icon;
  _dataFlavor = new DataFlavor(icon = new LightIcon(self->_editor),"LightIcon");\
  icon->setLight(bean->getSystemName());
  icon->setFamily(self->_family);
  QMapIterator<QString, NamedIcon*> iter(*self->_currentIconMap);
  while (iter.hasNext())
  {
    iter.next();
    icon->setIcon( iter.value());
  }
  _dataFlavor->setMimeTypeParameter("light", bean->getSystemName());
  LightIconXml* xml = new LightIconXml();
  QDomElement e = xml->store((QObject*)icon);
  xml->doc.appendChild(e);
  xmldata.append(xml->doc.toString());
 }
 delete _dataFlavor;
return xmldata;
}

//};

