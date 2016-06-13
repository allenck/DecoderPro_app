#include "multisensoriconadder.h"
#include <QRadioButton>
#include "catalogtreenode.h"
#include "multisensoricon.h"
#include "catalogtreeleaf.h"
#include <QBoxLayout>
#include "namedicon.h"
#include "imageindexeditor.h"
#include "flowlayout.h"
#include "QButtonGroup"
#include "QMessageBox"
#include "sensor.h"
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"

//MultiSensorIconAdder::MultiSensorIconAdder(QWidget *parent) :
//    IconAdder(parent)
//{
//}
/**
 * Provides a simple editor for creating a MultiSensorIcon object.  Allows
 * drops from icons dragged from a Catalog preview pane.  Also implements
 * dragging a row from the Sensor table to be dropped on a Sensor label
 * <p>
 * To work right, the MultiSensorIcon needs to have all
 * images the same size, but this is not enforced here.
 * It should be.  -Done 6/16/09
 *
 * @author  Bob Jacobsen  Copyright (c) 2007
 * @author  Pete Cressman  Copyright (c) 2009
 *
 */

// /*public*/ class MultiSensorIconAdder extends IconAdder {

/*public*/ /*static*/ /*final*/ QString MultiSensorIconAdder::NamedBeanFlavorMime = DataFlavor::javaJVMLocalObjectMimeType +
               ";class=jmri.NamedBean";

//    /*public*/ MultiSensorIconAdder(QWidget *parent) {
//        super();
//        _sensorMap = new QMap <QString, NamedBeanHandle<Sensor*>*>();
//    }

/*public*/ MultiSensorIconAdder::MultiSensorIconAdder(QString type, QWidget *parent) : IconAdder(type, parent)
{
 //super(type);
 _sensorMap = new QMap <QString, NamedBeanHandle<Sensor*>*>();
 log = new Logger("MultiSensorIconAdder");
 log->setDebugEnabled(true);
}

/*public*/ void MultiSensorIconAdder::reset()
{
 _sensorMap = new QMap <QString, NamedBeanHandle<Sensor*>*>();
 IconAdder::reset();
}

/**
*  Build iconMap and orderArray from user's choice of defaults (override)
*/
/*protected*/ void MultiSensorIconAdder::makeIcons(CatalogTreeNode* n)
{
 if (log-> isDebugEnabled()) log-> debug("makeIcons from node= "+n->toString()+", numChildren= "+
                                        QString::number(n->getChildCount())+", NumLeaves= "+QString::number(n->getNumLeaves()));
 _iconMap = new QHash <QString, JToggleButton*>(/*10*/);
 _order =  QStringList();
 QVector <CatalogTreeLeaf*>* list = n->getLeaves();
 // adjust order of icons
 for (int i=list->size()-1; i>=0; i--)
 {
  CatalogTreeLeaf* leaf = list->at(i);
  QString name = leaf->getName();
  QString path = leaf->getPath();
  if ("BeanStateInconsistent"==(name))
  {
   setIcon(0, name, new NamedIcon(path, path));
  }
  else if ("BeanStateUnknown"==(name))
  {
   setIcon(1, name, new NamedIcon(path, path));
  }
  else if ("SensorStateInactive"==(name))
  {
   setIcon(2, name, new NamedIcon(path, path));
  }
  else
  {
   int k = name.mid(name.length()-1).toInt();
   setIcon(k+3, name, new NamedIcon(path, path));
  }
 }
}

/**
 * Only called from MultiSensorIcon popup
 * @param icons
 */
void MultiSensorIconAdder::setMultiIcon(QList <MultiSensorIcon::Entry*>* icons)
{
 for (int i=0; i<icons->size(); i++)
 {
  MultiSensorIcon::Entry* entry = icons->at(i);
  QString label = tr("Position ") + QString::number(i);
  setIcon(i+3, label, entry->icon->getURL());
  _sensorMap->insert(label, entry->namedSensor);
 }
 if (log-> isDebugEnabled()) log-> debug("setMultiIcon: Size: sensors= "+QString::number(_sensorMap->size())+ ", icons= "+QString::number(_iconMap->size()));
}

/**
*  Override.  First look for a table selection to set the sensor.
*   If not, then look to change the icon image (super).
*/
//@SuppressWarnings("NULL")
/*protected*/ void MultiSensorIconAdder::doIconPanel()
{
 if (log-> isDebugEnabled()) log-> debug("doIconPanel: Sizes: _iconMap= "+QString::number(_iconMap->size())+ " _order.size()= "+QString::number(_order.size())+  ", _sensorMap.size()= "+QString::number(_sensorMap->size()));
 QSize dim;
 QWidget* rowPanel = NULL;
 int cnt=0;
 for (int i=3; i<_order.size(); i++)
 {
  QHBoxLayout* rowPanelLayout;
  if (rowPanel == NULL)
  {
   rowPanel = new QWidget;
   rowPanel->setLayout(rowPanelLayout = new QHBoxLayout(rowPanel/*, BoxLayout.X_AXIS*/));
   rowPanelLayout->addStrut(STRUT_SIZE);
  }
  QString key = _order.at(i);
  if (key==("placeHolder"))
  {
   continue;
  }
  QWidget* p1 =new QWidget();
  p1->setLayout(new QVBoxLayout(p1/*, BoxLayout.Y_AXIS*/));
  QString label = tr("Position %1").arg(cnt+1);
  p1->layout()->addWidget(new JLabel(label));
  p1->layout()->addWidget(_iconMap->value(key));

  QWidget* p2 =new QWidget();
  p2->setLayout(new FlowLayout);
  QPushButton* deleteButton = new QPushButton(tr("Delete"));
//        ActionListener action = new ActionListener() {
//                String key;
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    delete(key);
//                }
//                ActionListener init(String k) {
//                    key = k;
//                    return this;
//                }
//        }.init(key);
//        delete.addActionListener(action);
  DeleteActionListener* dal = new DeleteActionListener();
  dal->init(key, this);
  connect(deleteButton, SIGNAL(clicked()), dal, SLOT(actionPerformed()));
  p2->layout()->addWidget(deleteButton);

  DropPanel* p3 = new DropPanel(this);
  p3->setLayout(new QVBoxLayout(p3/*, BoxLayout.Y_AXIS*/));
  QLabel* k = new QLabel(key);
  k->setObjectName("key");
  //k->setName(key);
  k->setVisible(false);
  p3->layout()->addWidget(k);
  QFrame* p4 = new QFrame();
  p4->setLayout(new QHBoxLayout);
  p4->layout()->addWidget(new QLabel(tr("Sensor")));
  p3->layout()->addWidget(p4);
  p4 = new QFrame();
  p4->setLayout(new QHBoxLayout);
  NamedBeanHandle<Sensor*>* sensor = _sensorMap->value(key);
  QString name = tr("undefined");
  QColor color = QColor(Qt::red);
  if (sensor != NULL)
  {
   name = sensor->getName();
        /*name = sensor.getUserName();
        if (name == NULL)  {
            name = sensor.getSystemName();
        }*/
   color = QColor(Qt::black);
  }
  //p4.setBorder(BorderFactory.createLineBorder(color));
  p4->setFrameStyle(QFrame::Panel | QFrame::Plain);
  p4->setLineWidth(2);
  QPalette* palette = new QPalette();
  palette->setColor(QPalette::Foreground,color);
  p4->setPalette(*palette);
  QLabel* sensorName;
  p4->layout()->addWidget(sensorName = new QLabel(name));
  sensorName->setObjectName("SensorName");
  p4->setMaximumSize(p4->sizeHint());
  p3->layout()->addWidget(p4);
  QWidget* p13 =new QWidget();
  p13->setLayout(new QHBoxLayout(p13/*, BoxLayout.X_AXIS*/));
  p13->layout()->addWidget(p3);
  p13->layout()->addWidget(p1);

  QFrame* panel =new QFrame();
  panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
  panel->layout()->addWidget(p13);
  panel->layout()->addWidget(p2);
  //panel.setBorder(BorderFactory.createLineBorder(java.awt.Color.BLACK));
  panel->setFrameStyle(QFrame::Panel | QFrame::Plain);
  panel->setLineWidth(2);

  rowPanelLayout->addWidget(panel);
  rowPanelLayout->addStrut(STRUT_SIZE);

  cnt++;
  if ((cnt%3)==0)
  {
   _iconPanel->layout()->addWidget(rowPanel);
   rowPanel = NULL;
  }
  dim = panel->sizeHint();
 }
 while ((cnt%3)!=0)
 {
  try {
  //rowPanel->layout()->addWidget(Box.createRigidArea(dim));
  cnt++;
  }
  catch (NullPointerException npe) { /* never */}
 }
 if (rowPanel != NULL)
 {
  _iconPanel->layout()->addWidget(rowPanel);
  ((QBoxLayout*)_iconPanel->layout())->addStrut(STRUT_SIZE);
 }
 rowPanel = new QWidget();
 rowPanel->setLayout(new QHBoxLayout(rowPanel/*, BoxLayout.X_AXIS*/));
 ((QHBoxLayout*)rowPanel->layout())->addStrut(STRUT_SIZE);
 for (int i=0; i<3; i++)
 {
  QString key = _order.at(i);
  QWidget* p =new QWidget();
  p->setLayout(new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
  p->layout()->addWidget(new QLabel(/*rbean.getString(key)*/key));
  p->layout()->addWidget(_iconMap->value(key));
  rowPanel->layout()->addWidget(p);
  ((QHBoxLayout*)rowPanel->layout())->addStrut(STRUT_SIZE);
 }
 _iconPanel->layout()->addWidget(rowPanel);
 ((QHBoxLayout*)_iconPanel->layout())->addStrut(STRUT_SIZE);
 this->layout()->addWidget(_iconPanel/*, 0*/);
 valueChanged();
 adjustSize();
}

/**
* Override
*
*/
/*public*/ void MultiSensorIconAdder::complete(ActionListener* addIconAction, bool changeIcon,
                      bool addToTable, bool update)
{
 QButtonGroup* group = new QButtonGroup();
 _updown = new QRadioButton(tr("Up-Down"));
 _rightleft = new QRadioButton(tr("Right-Left"));
 _rightleft->setChecked(true);
 group->addButton(_updown);
 group->addButton(_rightleft);
 QWidget* p = new QWidget();
 p->setLayout(new QHBoxLayout(p/*, BoxLayout.X_AXIS*/));
 p->layout()->addWidget(_updown);
 p->layout()->addWidget(_rightleft);
 ((QBoxLayout*)p->layout())->addStrut(STRUT_SIZE);
 QPushButton* addIconButton = new QPushButton(tr("Add Another Icon"));
//    addIcon.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addIcon();
//            }
//       });
 connect(addIconButton, SIGNAL(clicked()), this, SLOT(addIcon()));
 p->layout()->addWidget(addIconButton);
 this->layout()->addWidget(p);
 //this.add(new JSeparator());
 IconAdder::complete(addIconAction, changeIcon, addToTable, update);
 //TODO: _table.setDragEnabled(true);
//TODO: _table.setTransferHandler(new ExportHandler());
 valueChanged();
}



/*private*/ void MultiSensorIconAdder::addIcon()
{
 int index = _order.size();
 QString path = ":/resources/icons/misc/X-red.gif"; //"resources/icons/USS/plate/levers/l-vertical.gif";
 QString label = tr("Position ") +(index-3);
 IconAdder::setIcon(index, label, new NamedIcon(path, path));
 valueChanged();
 if (!_update)
 {
  _defaultIcons->addLeaf(label, path);
  ImageIndexEditor::indexChanged(true);
 }
 makeIconPanel(!_update);
 //this->invalidate();
}

/**
*  Override.  Activate Add to Panel button when all icons are
*  assigned sensors.
*/
/*public*/ void MultiSensorIconAdder::valueChanged(/*ListSelectionEvent**/)
{
 if (_addButton == NULL)
 {
        return;
 }
 if (_sensorMap->size() == (_iconMap->size()-3))
 {
  _addButton->setEnabled(true);
  _addButton->setToolTip("");
        //checkIconSizes();
 }
 else
 {
  _addButton->setEnabled(false);
  _addButton->setToolTip(tr("This button will be active after you assign sensors to all the icons"));
 }
}

/**
*
*/
void MultiSensorIconAdder::_delete(QString key)
{
 _iconMap->remove(key);
 _sensorMap->remove(key);
 int index = _order.indexOf(key);
 _order.removeOne(key);
 if (!_update)
 {
  _defaultIcons->deleteLeaves(key);
  //  update labels
  for (int k=index; k<_order.size(); k++)
  {
   QString label = _order.at(k);
   QVector <CatalogTreeLeaf*>* leaves = _defaultIcons->getLeaves(label);
   for (int i=0; i<leaves->size(); i++)
   {
    QString path = leaves->value(i)->getPath();
    _defaultIcons->deleteLeaves(label);
    _defaultIcons->addLeaf("MultiSensorPosition " + QString::number(k-3), path);
//                    break;
   }
  }
  ImageIndexEditor::indexChanged(true);
 }
 makeIconPanel(!_update);
}

/**
 * Returns a new NamedIcon object for your own use.
 * see NamedIcon getIcon(String key) in super
 * @param index of key
 * @return Unique object
 */
/*public*/ NamedIcon* MultiSensorIconAdder::getIcon(int index)
{
 if (index>=_order.size())
 {
//  JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                                       tr("NoIconAt"), index-2),
//                                       tr("errorTitle"),
//                                       JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Error"), tr("No icon is specified at position %1.").arg(index-2));
  return NULL;
 }
 return (NamedIcon*)_iconMap->value(_order.value(index))->getIcon();
}

/**
 * Returns a Sensor object for your own use.
 * see NamedIcon getIcon(String key) in super
 * @param index of key
 * @return Unique object
 */
/*public*/ NamedBeanHandle<Sensor*>* MultiSensorIconAdder::getSensor(int index)
{
 if (index>=_order.size())
 {
//        JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                                       tr("NoSensorAt"), index-2),
//                                       tr("errorTitle"),
//                                       JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Error"), tr("No Sensor is specified at position %1.").arg(index-2));
  return NULL;
 }
 return _sensorMap->value(_order.value(index));
}

/*public*/ bool MultiSensorIconAdder::getUpDown() {
    return _updown->isChecked();
}
/*private*/ bool MultiSensorIconAdder::putSensor(QString key, Sensor* sensor)
{
 QString name = sensor->getDisplayName();
 if (log-> isDebugEnabled()) log-> debug("putSensor: key= "+key+" sensor= "+name);
 QListIterator<NamedBeanHandle<Sensor*>*> iter( _sensorMap->values());
 while (iter.hasNext())
 {
  if (name==(iter.next()->getName()))
  {
//            JOptionPane.showMessageDialog(this, java.text.MessageFormat.format(
//                                           tr("DupSensorName"),
//                                           new Object[] {name}),
//                                           tr("errorTitle"),
//                                           JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Error"), tr("Sensor \"%1\" is already defined for an active icon.").arg(name));
            return false;
  }
 }
 _sensorMap->insert(key, ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, sensor));
 return true;
}

