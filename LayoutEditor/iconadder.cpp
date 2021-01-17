#include "iconadder.h"
#include "ui_iconadder.h"
#include "catalogtreemanager.h"
#include "instancemanager.h"
#include "catalogtree.h"
#include <QTableView>
#include "jtogglebutton.h"
#include <QBoxLayout>
#include "catalogtreenode.h"
#include "catalogtreeleaf.h"
#include "catalogpanel.h"
#include "namedicon.h"
#include "picklistmodel.h"
#include <QTableView>
#include <signalhead.h>
#include "jtextfield.h"
#include <QFileInfo>
#include <QMessageBox>
#include "flowlayout.h"
#include "imageindexeditor.h"
#include "dataflavor.h"
#include "defaultcatalogtreemanager.h"
#include <QDragEnterEvent>
#include "dndconstants.h"
#include "droptarget.h"
#include "itempalette.h"
#include "borderlayout.h"
#include "file.h"
#include <QHeaderView>
#include "actionlistener.h"

//IconAdder::IconAdder(QString name, QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::IconAdder)
//{
//    ui->setupUi(this);
//}

IconAdder::~IconAdder()
{
    //delete ui;
}
/**
 * Provides a simple editor for selecting N NamedIcons.  Class for
 * Icon Editors implements "Drag n Drop".  Allows
 * drops from icons dragged from a Catalog preview pane.
 * <P>See {@link SensorIcon} for an item
 * that might want to have that type of information, and
 * {@link jmri.jmrit.display.panelEditor.PanelEditor}
 * for an example of how to use this.
 *
 * @author Pete Cressman  Copyright (c) 2009, 2010
 */

///*public*/ class IconAdder extends QWidget* implements ListSelectionListener {

//static final ResourceBundle rbean = ResourceBundle.getBundle("jmri.NamedBeanBundle");

/*public*/ IconAdder::IconAdder(QWidget *parent) : QWidget(parent)
{
 common();
}

void IconAdder::common()
{
 log = new Logger("IconAdder");
 _userDefaults = false;
 _allowDeletes = false;
 _iconMap = new QHash <QString, JToggleButton*>();//10);
 _order = QStringList();
 _table = NULL;
 _changeButton = NULL;
 //QTimer::singleShot(50,this, SLOT(closeCatalog()));

 this->setLayout(thisLayout = new QVBoxLayout()); //this/*, BoxLayout.Y_AXIS*/));
// this->setContentsMargins(0,0,0,0);
// this->layout()->setContentsMargins(0,0,0,0);
// thisLayout->setSpacing(0);
 _buttonPanel = NULL;
 _iconPanel = NULL;
// setMinimumHeight(200);
 _addButton = NULL;
 _pickTablePane = NULL;
}

/*public*/ IconAdder::IconAdder(bool allowDeletes, QWidget *parent) : QWidget(parent)
{
 // this();
 common();
 _allowDeletes = allowDeletes;
}

/*public*/ void IconAdder::reset()
{
 if (_table != NULL)
 {
  _table->currentIndex().row();
  _table->clearSelection();
 }
 closeCatalog();
 if (_defaultIcons != NULL)
 {
  makeIconPanel(true);
 }
 //this->validate();
}

/*public*/ IconAdder::IconAdder(QString type, QWidget *parent) : QWidget(parent)
{
 //this();
 common();
 _type = type;
 initDefaultIcons();
}
//@SuppressWarnings("unchecked")
/*public*/ void IconAdder::initDefaultIcons()
{
 CatalogTreeManager* manager = static_cast<DefaultCatalogTreeManager*>(InstanceManager::getDefault("CatalogTreeManager"));
 CatalogTree* tree = (CatalogTree*)((DefaultCatalogTreeManager*)manager)->getBySystemName("NXDI");
 if (tree != NULL)
 {
  CatalogTreeNode* node = (CatalogTreeNode*)tree->getRoot();
  QVectorIterator<CatalogTreeNode*>* e = (QVectorIterator<CatalogTreeNode*>*)node->children();
  while (e->hasNext())
  {
   CatalogTreeNode* nChild = e->next();
   if (_type==(nChild->toString()))
   {
    _defaultIcons = nChild;
    _userDefaults = true;
   }
  }
 }
 if (log->isDebugEnabled()) log->debug("initDefaultIcons: type= "+_type+", defaultIcons= "+_defaultIcons->objectName());
}

/*private*/ CatalogTreeNode* IconAdder::getDefaultIconNodeFromMap()
{
 if (log->isDebugEnabled()) log->debug("getDefaultIconNodeFromMap for node= "+_type+
                                        ", _order.size()= "+_order.size());
 _defaultIcons =new CatalogTreeNode(_type);
 QHashIterator<QString, JToggleButton*> it(*_iconMap);
 while (it.hasNext())
 {
  //QHash<QString, JToggleButton>* e = it.next();
  it.next();
  NamedIcon* icon = (NamedIcon*)it.value()->getIcon();
  _defaultIcons->addLeaf(new CatalogTreeLeaf(it.key(), icon->getURL(), _order.indexOf(it.key())));
 }
 return _defaultIcons;
}

/*public*/ CatalogTreeNode* IconAdder::getDefaultIconNode()
{
 if (log->isDebugEnabled()) log->debug("getDefaultIconNode for node= "+_type);
 CatalogTreeNode* defaultIcons = new CatalogTreeNode(_type);
 QVector <CatalogTreeLeaf*>* list = _defaultIcons->getLeaves();
 for (int i=0; i<list->size(); i++)
 {
  CatalogTreeLeaf* leaf = list->at(i);
  defaultIcons->addLeaf(new CatalogTreeLeaf(leaf->getName(), leaf->getPath(), i));
 }
 return defaultIcons;
}

/**
*  Build iconMap and orderArray from user's choice of defaults
*/
/*protected*/ void IconAdder::makeIcons(CatalogTreeNode* n)
{
 if (log->isDebugEnabled()) log->debug("makeIcons from node= "+n->toString()+", numChildren= "+
                                        n->getChildCount()+", NumLeaves= "+n->getNumLeaves());
 _iconMap = new QHash <QString, JToggleButton*>(); //(10);
 _order = QStringList();
 QVector <CatalogTreeLeaf*>* list = n->getLeaves();
 // adjust order of icons
 int k = list->size()-1;
 for (int i=list->size()-1; i>=0; i--)
 {
  CatalogTreeLeaf* leaf = list->at(i);
  QString name = leaf->getName();
  QString path = leaf->getPath();
  if ("BeanStateInconsistent"==(name))
  {
   this->setIcon(0, name, new NamedIcon(path, path));
  }
  else if ("BeanStateUnknown"==(name))
  {
   this->setIcon(1, name, new NamedIcon(path, path));
  }
  else
  {
   this->setIcon(k, name, new NamedIcon(path, path));
   k--;
  }
 }
}

/**
* @param order -the index to Sensor's name and the inverse order that icons are drawn in doIconPanel()
* @param label -the Sensor's name displayed in the icon panel and the key to the icon button in _iconMap
* @param icon -the icon displayed in the icon button
*/
/*protected*/ void IconAdder::setIcon(int order, QString label, NamedIcon* icon)
{
 // make a button to change that icon
 if (log->isDebugEnabled()) log->debug("setIcon at order= "+QString::number(order)+", key= "+label);
 JToggleButton* button = (JToggleButton*)new IconButton(label, icon, this);
 if (icon==NULL || icon->getIconWidth()<1 || icon->getIconHeight()<1)
 {
  button->setText(tr("invisible Icon"));
//            button->setForeground(QColor(174,173,172));
 }
 else
 {
  icon->reduceTo(CatalogPanel::ICON_WIDTH, CatalogPanel::ICON_HEIGHT, CatalogPanel::ICON_SCALE);
  button->setToolTip(icon->getName());
 }

 if (_allowDeletes)
 {
  QString fileName = ":/resources/icons/misc/X-red.gif";
  button->setSelectedIcon(new NamedIcon(fileName, fileName));
 }
 if (icon!=NULL)
 {
  icon->reduceTo(CatalogPanel::ICON_WIDTH, CatalogPanel::ICON_HEIGHT, CatalogPanel::ICON_SCALE);
  button->setSelectedIcon(icon);
 }

 _iconMap->insert(label, button);
 // calls may not be in ascending order, so pad array
 if (order >= _order.size())
 {
  for (int i=_order.size(); i<=order; i++)
  {
   //_order.replace(i, "placeHolder");
   _order.insert(i, "placeHolder");
  }
 }
// else
// {
//  if (order < _order.size())
//  {
//    _order.removeAt(order);
//  }
// }
 // _order.replace(order, label);
 _order.replace(order, label);
}

/**
*  install the icons used to represent all the states of the entity being edited
*   @param label - the state name to display, Must be unique from all other
*          calls to this method.
*   @param name - the resource name of the icon image to displa
*   @param order - (reverse) order of display, (0 last, to N first)
*/
/*public*/ void IconAdder::setIcon(int order, QString label, QString name) {
    if (log->isDebugEnabled()) log->debug("setIcon: order= "+ QString::number(order)+", label= "+label+", name= "+name);
    this->setIcon(order, label, new NamedIcon(name, name));
}

/*public*/ void IconAdder::setParent(JFrame* parent) {
    _parent = parent;
}

void IconAdder::pack() {
 _parent->pack();
}

/*public*/ int IconAdder::getNumIcons() {
    return _iconMap->size();
}

/**
* After all the calls to setIcon(...) are made, make the icon
* display.   Two columns to save space for subsequent panels.
*/
/*public*/ void IconAdder::makeIconPanel(bool useDefaults)
{
 if (useDefaults && _userDefaults)
 {
  makeIcons(_defaultIcons);
 }
 clearIconPanel();
 doIconPanel();
}

/*private*/ void IconAdder::clearIconPanel()
{
 if (_iconPanel != NULL)
 {
  thisLayout->removeWidget(_iconPanel);
  _iconPanel->deleteLater();
  _iconPanel = NULL;
 }
 _iconPanel = new QWidget();
 //_iconPanel->setLayout(new QVBoxLayout(_iconPanel/*, BoxLayout.Y_AXIS*/));
 _iconPanel->setLayout(_iconPanelLayout = new QVBoxLayout);
// _iconPanel->layout()->setSpacing(0);
// _iconPanel->setContentsMargins(0,0,0,0);
// _iconPanel->layout()->setContentsMargins(0,0,0,0);
}

/*protected*/ void IconAdder::doIconPanel()
{
 //_iconPanel->setMinimumHeight(100);
// QWidget* panel = NULL;
 QHBoxLayout* panelLayout = NULL;
 int cnt=0;
 for (int i=_order.size()-1; i>=0; i--)
 {
  if(_order.at(i) == "none")
   continue;

  if (panelLayout == NULL)
  {
//   panel = new QWidget();
//   panel->setLayout(panelLayout = new QHBoxLayout(panel/*, BoxLayout.X_AXIS*/));
//   //panel->setMinimumHeight(100);
//   panelLayout->setSpacing(0);
//   panel->setContentsMargins(0,0,0,0);
//   panelLayout->setContentsMargins(0,0,0,0);
   panelLayout = new QHBoxLayout;
   //panel.add(Box.createHorizontalStrut(STRUT_SIZE));
//   ((QHBoxLayout*)panel->layout())->addStrut(STRUT_SIZE);
  }
  QString key = _order.at(i);
//  QWidget* p =new QWidget();
  //p->setMinimumHeight(100);
//  p->setContentsMargins(0,0,0,0);
  QVBoxLayout* pLayout = new QVBoxLayout;
//  p->setLayout(pLayout = new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
//  pLayout->setContentsMargins(0,0,0,0);
//  pLayout->setSpacing(0);
//  QSizePolicy pSp =  QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//  pSp.setHorizontalStretch(0);
//  pSp.setVerticalStretch(0);
//  pSp.setHeightForWidth(p->sizePolicy().hasHeightForWidth());
//  p->setSizePolicy(pSp);
  QString labelName = key;
  try
  {
   labelName = (key); // tr??
  }
  catch (MissingResourceException mre)
  {
  }

  pLayout->addWidget(new QLabel(ItemPalette::convertText( labelName)));
  pLayout->addWidget(_iconMap->value(key));
  panelLayout->addLayout(pLayout);
  //panel.add(Box.createHorizontalStrut(STRUT_SIZE));
  //((QHBoxLayout*)panel->layout())->addStrut(STRUT_SIZE);
  if ((cnt&1)!=0)
  {
   _iconPanelLayout->addLayout(panelLayout);
   //_iconPanel.add(Box.createVerticalStrut(STRUT_SIZE));
//   ((QVBoxLayout*)_iconPanelLayout)->addStrut(STRUT_SIZE);
   panelLayout = NULL;
  }
  cnt++;
 }
 if (panelLayout != NULL)
 {
  _iconPanelLayout->addLayout(panelLayout);
  //_iconPanel.add(Box.createVerticalStrut(STRUT_SIZE));
//  ((QVBoxLayout*)_iconPanelLayout)->addStrut(STRUT_SIZE);
 }
 thisLayout->addWidget(_iconPanel,0, Qt::AlignTop);
}

/**
 * After the calls to makeIconPanel(), optionally.
 * make a pick list table for managed elements.  (Not all
 * Icon Editors use pick lists)
 */
/*public*/ void IconAdder::setPickList(PickListModel* tableModel)
{
 tableModel->init();
 _pickListModel = tableModel;
 _table = new JTable(tableModel);
 _table->setModel(tableModel);
 _pickListModel->makeSorter(_table);

//        _table.setRowSelectionAllowed(true);
//        _table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
 _table->setSelectionBehavior(QAbstractItemView::SelectRows);
 _table->setSelectionMode(QAbstractItemView::SingleSelection);
 ROW_HEIGHT = _table->getRowHeight();
//        _table.setPreferredScrollableViewportSize(new java.awt.Dimension(200,7*ROW_HEIGHT));
 _table->setMinimumSize(200,5*ROW_HEIGHT);
//        _table.setDragEnabled(true);
//        TableColumnModel columnModel = _table.getColumnModel();

//        TableColumn sNameColumnT = columnModel.getColumn(PickListModel.SNAME_COLUMN);
//        sNameColumnT.setResizable(true);
//        sNameColumnT.setMinWidth(50);
 _table->setColumnWidth(PickListModel::SNAME_COLUMN,50);
//        sNameColumnT.setMaxWidth(200);

//        TableColumn uNameColumnT = columnModel.getColumn(PickListModel.UNAME_COLUMN);
//        uNameColumnT.setResizable(true);
//        uNameColumnT.setMinWidth(100);
 _table->setColumnWidth(PickListModel::UNAME_COLUMN,100);
//        uNameColumnT.setMaxWidth(300);
 _table->resizeColumnsToContents();
 QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
 sizePolicy1.setHorizontalStretch(0);
 sizePolicy1.setVerticalStretch(0);
 sizePolicy1.setHeightForWidth(_table->sizePolicy().hasHeightForWidth());
 _table->setSizePolicy(sizePolicy1);
 _table->setMinimumSize(QSize(0, 100));
 _table->horizontalHeader()->setStretchLastSection(true);
 connect(_table, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged()));
 _table->setDragEnabled(true);

 //_pickTablePane = new JScrollPane(_table);
 thisLayout->addWidget(/*_pickTablePane*/_table, 0, Qt::AlignVCenter);
 //this.add(Box.createVerticalStrut(STRUT_SIZE));
 //((QVBoxLayout*)this->layout())->addStrut(STRUT_SIZE);
 adjustSize();
}

/*public*/ void IconAdder::setSelection(NamedBean* bean)
{
 int row = _pickListModel->getIndexOf(bean);
 //        _table.addRowSelectionInterval(row, row);
 _table->selectRow(row);
 _addButton->setEnabled(true);
 //        _pickTablePane.getVerticalScrollBar().setValue(row*ROW_HEIGHT);
 qDebug() << "row = " + QString::number(row) + " selected = " + QString::number(_table->currentIndex().row());
}

/**
*  When a Pick list is installed, table selection controls the Add button
*/
/*public*/ void IconAdder::valueChanged(ListSelectionEvent* /*e*/)
{
 if (_table == NULL)
 {
  return;
 }
 int row = _table->currentIndex().row();
 if (log->isDebugEnabled()) log->debug("Table valueChanged: row= "+row);
 if (row >= 0)
 {
  _addButton->setEnabled(true);
  _addButton->setToolTip(NULL);
  if (_type!=NULL && _type==("Signal Head"))
  {
   makeIconMap(_pickListModel->getBeanAt(row));
   clearIconPanel();
   doIconPanel();
  }
 }
 else
 {
  _addButton->setEnabled(false);
  _addButton->setToolTip(tr("This button will be active after you select a row from the table"));
 }
//validate();
}

void IconAdder::makeIconMap(NamedBean* bean)
{
 if (bean!=NULL && _type!=NULL && _type==("SignalHead"))
 {
  _order =  QList <QString>();
  _iconMap = new QHash <QString, JToggleButton*>(); //(12);
  int k=0;
  QVector <CatalogTreeLeaf*>* list = _defaultIcons->getLeaves();
  QVector<QString> states = ((SignalHead*)bean)->getValidStateNames();
  for (int i=0; i<list->size(); i++)
  {
   CatalogTreeLeaf* leaf = list->at(i);
   QString name = leaf->getName();
   try
   {
    name = /*rbean.getString*/(leaf->getName());
   }
   catch (MissingResourceException mre)
   {
   }
   if (log->isDebugEnabled()) log->debug("makeIconMap: leafName= "+leaf->getName()+", name= "+name);
   for (int j=0; j<states.size(); j++)
   {
    if (name==(states.at(j)) ||
                    leaf->getName()==(tr("Dark")) ||
                    leaf->getName()==(tr("Held")))
    {
     QString path = leaf->getPath();
     this->setIcon(k++, leaf->getName(), new NamedIcon(path, path));
     break;
    }
   }
  }
 }
 else
 {
  makeIcons(_defaultIcons);
 }
 if (log->isDebugEnabled()) log->debug("makeIconMap: _iconMap.size()= "+QString::number(_iconMap->size()));
}

void IconAdder::checkIconSizes()
{
 if (!_addButton->isEnabled())
 {
  return;
 }
 QListIterator <JToggleButton*> iter(_iconMap->values());
 int lastWidth = 0;
 int lastHeight = 0;
 bool first = true;
 while (iter.hasNext())
 {
  JToggleButton* but = iter.next();
  if (first)
  {
   lastWidth = but->getIcon()->getIconWidth();
   lastHeight = but->getIcon()->getIconHeight();
   first = false;
   continue;
  }
  int nextWidth = but->getIcon()->getIconWidth();
  int nextHeight = but->getIcon()->getIconHeight();
  if ((qAbs(lastWidth - nextWidth) > 3 || qAbs(lastHeight - nextHeight) > 3))
  {
//                JOptionPane.showMessageDialog(this, tr("IconSizeDiff"), tr("warnTitle"),
//                                                     JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(this, tr("Warning"), tr("The icons to be installed in the panel are of differing sizes.\nThis may interfere with proper operation."));
   return;
  }
  lastWidth = nextWidth;
  lastHeight = nextHeight;
 }
 if (log->isDebugEnabled()) log->debug("Size: width= "+QString::number(lastWidth)+", height= "+QString::number(lastHeight));
}

/**
* Used by Panel Editor to make the final installation of the icon(s)
* into the user's Panel.
* <P>Note! the selection is cleared. When two successive calls are made, the
* 2nd will always return NULL, regardless of the 1st return.
*/
/*public*/ NamedBean* IconAdder::getTableSelection()
{
 if (ImageIndexEditor::isIndexChanged())
 {
  checkIconSizes();
 }
 int row = _table->currentIndex().row();
 if (row >= 0)
 {
  NamedBean* b = _pickListModel->getBeanAt(row);
  _table->clearSelection();
  _addButton->setEnabled(false);
  _addButton->setToolTip("");
    //this.validate();
  if (log->isDebugEnabled()) log->debug("getTableSelection: row= "+QString::number(row)+", bean= "+b->getDisplayName());
   return b;
  }
 else if (log->isDebugEnabled()) log->debug("getTableSelection: row=0");
 return NULL;
}

/**
* Returns a new NamedIcon object for your own use.
* @param key Name of key (label)
* @return Unique object
*/
/*public*/ NamedIcon* IconAdder::getIcon(QString key)
{
 if (log->isDebugEnabled()) log->debug("getIcon for key= "+ key);
 return new NamedIcon((NamedIcon*)_iconMap->value(key)->getIcon());
//return NULL;
}

/**
* Returns a new QHash of only the icons selected for display.
*/
/*public*/ QMap <QString, NamedIcon*>* IconAdder::getIconMap()
{
 if (log->isDebugEnabled()) log->debug("getIconMap: _allowDeletes= "+_allowDeletes);
 QMap <QString, NamedIcon*>* iconMap = new QMap <QString, NamedIcon*>();
 QStringListIterator iter(_iconMap->keys());
 while (iter.hasNext())
 {
  QString key = iter.next();
  JToggleButton* button = _iconMap->value(key);
  if (log->isDebugEnabled()) log->debug("getIconMap: key= "+key+", button.isSelected()= "+(button->isChecked()?"yes":"no"));
  if (!_allowDeletes || !button->isChecked())
  {
   iconMap->insert(key, new NamedIcon((NamedIcon*)button->getIcon()));
  }
 }
 return iconMap;
}

/*
* Supports selection of NamedBean from a pick list table
* @param addIconAction - ActionListener that adds an icon to the panel -
* representing either an entity a pick list selection, an
* arbitrary image, or a value, such a
* memory value.
* @param changeIconAction - ActionListener that displays sources from
* which to select an image file.
*/
/*public*/ void IconAdder::complete(ActionListener* addIconAction, bool changeIcon, bool addToTable, bool update)
{
 _update = update;
 if (_buttonPanel!=NULL)
 {
  thisLayout->removeWidget(_buttonPanel);
 }
 _buttonPanel = new QWidget();
 QVBoxLayout* buttonPanelLayout;
 _buttonPanel->setLayout(buttonPanelLayout = new QVBoxLayout());//(_buttonPanel/*, BoxLayout.Y_AXIS*/));
// _buttonPanel->setContentsMargins(0,0,0,0);
// buttonPanelLayout->setSpacing(0);
// buttonPanelLayout->setContentsMargins(0,0,0,0);
// QWidget* p = new QWidget();
// p->setContentsMargins(0,0,0,0);
// p->setLayout(new QHBoxLayout());
 QHBoxLayout* pLayout = new QHBoxLayout;
 if (addToTable)
 {
  _sysNametext = new JTextField();
  _sysNametext->setMinimumSize(QSize(150, _sysNametext->getPreferredSize().height()+2));
  connect(_sysNametext, SIGNAL(editingFinished()), this, SLOT(on_sysNametext_editingFinished()));
  _addTableButton = new QPushButton(tr("Add item to table"));
  _addTableButton->setToolTip(tr("This button will be active after you type text into the text box"));
//            _addTableButton.addActionListener(new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent a) {
//                        addToTable();
//                    }
//            });
  connect(_addTableButton, SIGNAL(clicked()), this, SLOT(addToTable()));
  _addTableButton->setEnabled(false);
  _addTableButton->setToolTip(tr("This button will be active after you type text into the text box"));
  pLayout->addWidget(_sysNametext);
//            _sysNametext.addKeyListener(new KeyAdapter() {
//                    /*public*/ void keyReleased(KeyEvent a){
//                        if (_sysNametext.getText().length() > 0) {
//                            _addTableButton.setEnabled(true);
//                            _addTableButton.setToolTipText(NULL);
//                            _table.clearSelection();
//                        }
//                    }
//                });
  pLayout->addWidget(_addTableButton,0, Qt::AlignCenter);
  buttonPanelLayout->addLayout(pLayout); //,0,Qt::AlignCenter);

//  p = new QWidget();
//  p->setLayout(new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
//  p->setContentsMargins(0,0,0,0);
//  p->layout()->setContentsMargins(0,0,0,0);
//  p->setContentsMargins(0,0,0,0);
//  p->layout()->setSpacing(0);
  pLayout = new QHBoxLayout;
 }
 if (update)
 {
  _addButton = new QPushButton(tr("Update Panel"));
 }
 else
 {
  _addButton = new QPushButton(tr("Add to Panel"));
 }
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(_addButton->sizePolicy().hasHeightForWidth());
 _addButton->setSizePolicy(sizePolicy);
 //        _addButton.addActionListener(addIconAction);
 connect(_addButton, SIGNAL(clicked()), addIconAction, SLOT(actionPerformed()));
 _addButton->setEnabled(true);
 if (changeIcon)
 {
  _changeButton = new QPushButton(tr("Change icon..."));
//            _changeButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    addCatalog();
//                }
//            });
  _changeButton->setSizePolicy(sizePolicy);
  connect(_changeButton, SIGNAL(clicked()), this, SLOT(addCatalog()));
  pLayout->addWidget(_changeButton, 0, Qt::AlignHCenter);
  _closeButton = new QPushButton(tr("Close Catalog"));
//            _closeButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    closeCatalog();
//                }
//            });
  connect(_closeButton, SIGNAL(clicked()), this, SLOT(closeCatalog()));
  _closeButton->setVisible(false);
  _closeButton->setSizePolicy(sizePolicy);
  pLayout->addWidget(_closeButton, 0, Qt::AlignHCenter);
 }
 pLayout->setAlignment(Qt::AlignHCenter);
 buttonPanelLayout->addLayout(pLayout);
 if (_table != NULL)
 {
  _addButton->setEnabled(false);
  _addButton->setToolTip(tr("This button will be active after you select a row from the table"));
 }
 addAdditionalButtons(_buttonPanel);
// p = new QWidget();
// p->setContentsMargins(0,0,0,0);
// p->setLayout(new QHBoxLayout);
// p->layout()->setContentsMargins(0,0,0,0);
// p->layout()->setSpacing(0);
 pLayout->addWidget(_addButton);
 buttonPanelLayout->addLayout(pLayout);

 buttonPanelLayout->addStrut(STRUT_SIZE);
 //        _buttonPanel->layout()->add(new JSeparator());
 QFrame* line = new QFrame(/*centralwidget()*/this);
 line->setObjectName(QString::fromUtf8("line"));
 line->setFrameShape(QFrame::HLine);
 line->setFrameShadow(QFrame::Sunken);
 buttonPanelLayout->addWidget(line);
 thisLayout->addWidget(_buttonPanel,0, Qt::AlignBottom);

 if (changeIcon)
 {
  _catalog = CatalogPanel::makeDefaultCatalog();
  _catalog->setVisible(false);
  _catalog->setToolTip(tr("Drag an icon from the Catalog to replace an icon in the item group"));
  thisLayout->addWidget(_catalog, 0, Qt::AlignBottom);
 }
 if (_type != NULL /*&& _defaultIcons == NULL*/)
 {
  getDefaultIconNodeFromMap();
 }
 // Allow initial row to be set without getting callback to valueChanged
 if (_table!=NULL)
 {
 //            _table->getSelectionModel().addListSelectionListener(this);
 }
 pack();
}

/*protected*/ void IconAdder::addAdditionalButtons(QWidget* /*p*/) {}

/*public*/ bool IconAdder::addIconIsEnabled()
{
 return _addButton->isEnabled();
}

void IconAdder::on_sysNametext_editingFinished()
{
 if (_sysNametext->text().length() > 0)
 {
  _addTableButton->setEnabled(true);
  _addTableButton->setToolTip("");
  _table->clearSelection();
 }
}

void IconAdder::addToTable()
{
 QString name = _sysNametext->text();
 if (name != NULL && name.length() > 0)
 {
  NamedBean* bean = _pickListModel->addBean(name);
  int setRow = _pickListModel->getIndexOf(bean);
 //            _table->setRowSelectionInterval(setRow, setRow);
 //            _pickTablePane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
 }
 _sysNametext->setText("");
 _addTableButton->setEnabled(false);
}

/*
* Add panel to change icons
*/
/*public*/ void IconAdder::addCatalog()
{
 if (log->isDebugEnabled()) log->debug("addCatalog called:");
 // add the catalog, so icons can be selected
 if (_catalog == NULL)
 {
  _catalog = CatalogPanel::makeDefaultCatalog();
  _catalog->setToolTip(tr("Drag an icon from the Catalog to replace an icon in the item group"));
 }
 _catalog->setVisible(true);
/*
this.add(new JSeparator());
*/
 if (_changeButton != NULL)
 {
    _changeButton->setVisible(false);
    _closeButton->setVisible(true);
 }
//this.add(_catalog);
 if (_pickTablePane != NULL) {
     _pickTablePane->setVisible(false);
 }
 if(_table != NULL) _table->setVisible(false);
 pack();
}

void IconAdder::closeCatalog()
{
 if (_changeButton != NULL)
 {
  _catalog->setVisible(false);
  _changeButton->setVisible(true);
  _closeButton->setVisible(false);
 }
 if (_pickTablePane != nullptr)
 {
     _pickTablePane->setVisible(true);
 }
 pack();
}

/*public*/ void IconAdder::addDirectoryToCatalog(QDir* dir)
{
 if (_catalog == NULL)
 {
  _catalog = CatalogPanel::makeDefaultCatalog();
 }
 if (_changeButton != NULL)
 {
  _changeButton->setVisible(false);
  _closeButton->setVisible(true);
 }
 QString name = dir->dirName();
 _catalog->createNewBranch("IF"+name, name, dir->absolutePath());
 thisLayout->addWidget(_catalog, 0, Qt::AlignBottom);
 this->pack();
}

/**
* If icons are changed, update global tree
*/
/*private*/ void IconAdder::updateCatalogTree()
{
 CatalogTreeManager* manager = static_cast<DefaultCatalogTreeManager*>(InstanceManager::getDefault("CatalogTreeManager"));
 // unfiltered, xml-stored, default icon tree
 CatalogTree* tree = (CatalogTree*)manager->getBySystemName("NXDI");
 if (tree == NULL)
 {	// build a new Default Icons tree
  tree = manager->newCatalogTree("NXDI", "Default Icons");
 }
 CatalogTreeNode* root = (CatalogTreeNode*)tree->getRoot();
 QVectorIterator<TreeNode*>* e = root->children();
 if(_defaultIcons == NULL) return;
 QString name = _defaultIcons->toString();
 while (e->hasNext())
 {
  CatalogTreeNode* nChild = (CatalogTreeNode*)e->next();
  if (name==(nChild->toString()))
  {
   if (log->isDebugEnabled()) log->debug("Remove node "+nChild->toString());
   root->remove(nChild);
   break;
  }
 }
 root->add(_defaultIcons);
 ImageIndexEditor::indexChanged(true);
}

//    private class IconButton extends DropButton {
//        QString key;
IconAdder::IconButton::IconButton(QString label, NamedIcon* icon, IconAdder* parent) : DropButton(icon, parent)
{  // init icon passed to avoid ref before ctor complete
 //super(icon);
 key = label;
}
//    };
QString IconAdder::IconButton::getKey() { return key;}

/**
* Clean up when its time to make it all go away
*/
void IconAdder::dispose()
{
 // clean up IconAdder::GUI aspects
 //this->clear();
 _iconMap->clear();
 _order = QStringList();
 if(_table != NULL)
 {
  delete _table;
  _table = NULL;
 }
 if(_catalog != NULL)
 {
   _catalog->close();
  _catalog = NULL;
 }
 if(_buttonPanel != NULL)
 {
  delete _buttonPanel;
  _buttonPanel = NULL;
 }
 if(_iconPanel != NULL)
 {
  delete _iconPanel;
  _iconPanel = NULL;
 }
}
//    class DropButton extends JToggleButton implements DropTargetListener {
//        DataFlavor dataFlavor;
DropButton::DropButton (NamedIcon* icon, IconAdder* parent) : JToggleButton(icon)
{
 //super(icon);
 log = new Logger("DropButton");
 this->parent = parent;
 setAcceptDrops(true);
 try
 {
  dataFlavor = new DataFlavor(ImageIndexEditor::IconDataFlavorMime);
 }
 catch (ClassNotFoundException cnfe)
 {
        //cnfe.printStackTrace();
 }
//  /*new*/ DropTarget((Component*)this, DnDConstants::ACTION_COPY_OR_MOVE, (DropTargetListener*)this);
 //if (log->isDebugEnabled()) log->debug("DropJLabel ctor");
}
#if 0
/*public*/ void dragExit(DropTargetEvent dte) {
    //if (log->isDebugEnabled()) log->debug("DropJLabel.dragExit ");
}
/*public*/ void dragEnter(DropTargetDragEvent dtde) {
    //if (log->isDebugEnabled()) log->debug("DropJLabel.dragEnter ");
}
#endif
void DropButton::dragMoveEvent(QDragMoveEvent *de)
{
 // The event needs to be accepted here
 if(de->mimeData()->text().startsWith("DataFlavor["))
  de->accept();
}
void DropButton::dragEnterEvent(QDragEnterEvent *event)
{
 QString data = event->mimeData()->text();
 if(data.startsWith("DataFlavor["))
     event->acceptProposedAction();
 if(event->mimeData()->hasFormat("text/uri-list")) // external file
  event->acceptProposedAction();

}

#if 0
/*public*/ void dragOver(DropTargetDragEvent dtde) {
    //if (log->isDebugEnabled()) log->debug("DropJLabel.dragOver ");
}
/*public*/ void dropActionChanged(DropTargetDragEvent dtde) {
    //if (log->isDebugEnabled()) log->debug("DropJLabel.dropActionChanged ");
}
/*public*/ void drop(DropTargetDropEvent e) {
#endif

void DropButton::dropEvent(QDropEvent *e)
{
// try
// {
//        Transferable tr = e.getTransferable();
//        if(e.isDataFlavorSupported(dataFlavor)) {
 QString mimeData = e->mimeData()->text();
 QString parmsList;
 QStringList parms;
 QString representationClass;
 QString path;
 if(mimeData.startsWith("DataFlavor["))
 {
  parmsList = mimeData.mid(11,mimeData.indexOf("]")-11);
  parms = parmsList.split(";");
  foreach (QString p, parms)
  {
   QStringList sl = p.split("=");

   if(sl.at(0) == "representationclass")
       representationClass = sl.at(1);
   if(sl.at(0)== "path")
       path = sl.at(1);
  }
  if(representationClass == "NamedIcon" && !path.isEmpty())
  {
   //NamedIcon newIcon = (NamedIcon)tr.getTransferData(dataFlavor);
   NamedIcon* newIcon = new NamedIcon(path,path);
   if (newIcon !=NULL)
   {
    //e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
    //DropTarget target = (DropTarget)e.getSource();
    //IconButton iconButton = (IconButton)target.getComponent();
    IconAdder::IconButton* iconButton= (IconAdder::IconButton*)this;
    QString key = iconButton->getKey();
    JToggleButton* button = parent->_iconMap->value(key);
    button->setContentsMargins(0,0,0,0);
    NamedIcon* oldIcon = button->getIcon();
    button->setSelectedIcon(newIcon);
    if (newIcon->getIconWidth()<1 || newIcon->getIconHeight()<1)
    {
     button->setText(tr("invisibleIcon"));
//     button->setForeground(QColor(Qt::lightGray);
    }
    else
    {
     button->setText("");
    }
    parent->_iconMap->insert(key, button);
    if (!parent->_update)
    {
     parent->_defaultIcons->deleteLeaf(key, oldIcon->getURL());
     parent->_defaultIcons->addLeaf(key, newIcon->getURL());
     parent->updateCatalogTree();
    }
    //e.dropComplete(true);
    e->accept();
    if (log->isDebugEnabled()) log->debug("DropJLabel.drop COMPLETED for "+key+ ", "+newIcon->getURL());
    }
    else
    {
     if (log->isDebugEnabled()) log->debug("DropJLabel.drop REJECTED!");
      //e->rejectDrop();
     e->setAccepted(false);
    }
   }
 }
//    } catch(IOException ioe) {
//        if (log->isDebugEnabled()) log->debug("DropPanel.drop REJECTED!");
//        e.rejectDrop();
//    } catch(UnsupportedFlavorException ufe) {
//        if (log->isDebugEnabled()) log->debug("DropJLabel.drop REJECTED!");
//        e.rejectDrop();
//    }
 if (e->mimeData()->hasFormat("text/uri-list"))
 {
         //event->acceptProposedAction();

         // Say we'll take it.
         //evt.acceptDrop ( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
         //evt.acceptDrop(java.awt.dnd.DnDConstants.ACTION_COPY);
 e->accept();
         //log(out, "FileDrop: file list accepted.");
         log->info("FileDrop: file list accepted.");

         // Get a useful list
//            List<File> fileList = (List<File>) tr.getTransferData(java.awt.datatransfer.DataFlavor.javaFileListFlavor);
         QString text = e->mimeData()->text();
         text.replace("\r\n", "");
         QStringList sl = text.split(",");
         QList<File*> fileList = QList<File*>();
         foreach (QString s, sl)
         {
          fileList.append(new File(s.mid(7)));
         }

         // Convert list to array
         QVector<File*> filesTemp = QVector<File*>(fileList.size());
         for(int i = 0; i < fileList.count(); i++) {
          filesTemp.replace(i, fileList.at(i));
         }
         //fileList.toArray(filesTemp);
         QList<File*> files = filesTemp.toList();

         // Alert listener to drop.
//            if (fileDrop->listener != NULL) {
//                fileDrop->listener->filesDropped(files);
//            }
//         emit fileDrop->dropFiles(files);
         File* file = files.at(0);
         NamedIcon* newIcon = new NamedIcon(file->getPath(),file->getPath());
         if (newIcon !=NULL)
         {
          //e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
          //DropTarget target = (DropTarget)e.getSource();
          //IconButton iconButton = (IconButton)target.getComponent();
          IconAdder::IconButton* iconButton= (IconAdder::IconButton*)this;
          QString key = iconButton->getKey();
          JToggleButton* button = parent->_iconMap->value(key);
          button->setContentsMargins(0,0,0,0);
          NamedIcon* oldIcon = button->getIcon();
          button->setSelectedIcon(newIcon);
          if (newIcon->getIconWidth()<1 || newIcon->getIconHeight()<1)
          {
           button->setText(tr("invisibleIcon"));
      //     button->setForeground(QColor(Qt::lightGray);
          }
          else
          {
           button->setText("");
          }
          parent->_iconMap->insert(key, button);
          if (!parent->_update)
          {
           parent->_defaultIcons->deleteLeaf(key, oldIcon->getURL());
           parent->_defaultIcons->addLeaf(key, newIcon->getURL());
           parent->updateCatalogTree();
          }
          //e.dropComplete(true);
          e->accept();
         // Mark that drop is completed.
//            evt.getDropTargetContext().dropComplete(true);
         //log(out, "FileDrop: drop complete.");
         log->info("FileDrop: drop complete.");
     }
 }
}

//    };

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(IconAdder.class.getName());
//}
