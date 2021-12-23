#include "blocktableaction.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "decimalformat.h"
#include "signalspeedmap.h"
#include "block.h"
#include "blockmanager.h"
#include <QCheckBox>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include "flowlayout.h"
#include <QMessageBox>
#include <QLabel>
#include <QSize>
#include "addnewbeanpanel.h"
#include "oblocktablemodel.h"
#include "blockeditaction.h"
#include "systemnamecomparator.h"
#include "path.h"
#include "guilafpreferencesmanager.h"
#include "bufferedimage.h"
#include "imageio.h"
#include "file.h"
#include <QPointer>
#include "fileutil.h"
#include "joptionpane.h"
#include <QButtonGroup>
#include "loggerfactory.h"
#include "blocktabledatamodel.h"
/**
 * Swing action to create and register a BlockTable GUI.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2008
 * @version $Revision: 29396 $
 */
///*public*/ class BlockTableAction extends AbstractTableAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = 6207247759586108823L;

/*public*/ /*final*/ /*static*/ QString BlockTableAction::BLOCK_METRIC_PREF = /*BlockTableAction.class.getName()*/".jmri.jmrit.beantable.BlockTableAction:LengthUnitMetric"; // NOI18N

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed?
 *
 * @param actionName
 */
/*public*/ BlockTableAction::BlockTableAction(QString actionName, QObject *parent) :
  AbstractTableAction(actionName, parent)
{
    //super(actionName);
 common();
}
void BlockTableAction::common()
{

 systemNameAuto = QString(getClassName()) + ".AutoSystemName";
 log = new Logger("BlockTableAction");


 // disable ourself if there is no primary Block manager available
 if (((BlockManager*)InstanceManager::getDefault("BlockManager")) == NULL)
 {
  setEnabled(false);
 }
}

BlockTableAction::BlockTableAction(QObject *parent) :
  AbstractTableAction(tr("Block Table"), parent)
{
 common();
}


/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Block objects
 */
/*protected*/ void BlockTableAction::createModel()
{
 // load graphic state column display preference
 _graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();

 m = new BlockTableDataModel(getManager());
}

//@Nonnull
//@Override
/*protected*/ Manager/*<Block>*/* BlockTableAction::getManager() {
    return (BlockManager*)InstanceManager::getDefault("BlockManager");
}
#if 0
/*public*/ BlockTableDataModel::BlockTableDataModel(QCheckBox* inchBox, BlockTableAction* blockTableAction)
{
 this->blockTableAction = blockTableAction;
 log = new Logger("BlockTableDataModel");
 this->inchBox = inchBox;
 connect(inchBox, SIGNAL(toggled(bool)), this, SLOT(fireTableDataChanged()));
 twoDigit = new DecimalFormat("0.00");
 rootPath = FileUtil::getProgramPath() +"resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
 beanTypeChar = 'S'; // for Sensor
 onIconPath = rootPath + beanTypeChar + "-on-s.png";
 offIconPath = rootPath + beanTypeChar + "-off-s.png";
 ((BlockManager*)InstanceManager::getDefault("BlockManager"))->PropertyChangeSupport::addPropertyChangeListener((PropertyChangeListener*)this);


 loadIcons();
 updateNameList();
}

/*public*/ QString BlockTableDataModel::getValue(QString name) const
{
 if (name == NULL)
 {
  log->warn("requested getValue(NULL)");
  return "(no name)";
 }
 Block* b = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBySystemName(name);
 if (b == NULL)
 {
  log->debug("requested getValue(\"" + name + "\"), Block doesn't exist");
  return "(no Block)";
 }
 QVariant m = b->getValue();
 if (m != QVariant())
 {
  return m.toString();
 }
 else
 {
  return "";
 }
}

/*public*/ AbstractManager *BlockTableDataModel::getManager()
{
 return ((BlockManager*)InstanceManager::getDefault("BlockManager"));
}

/*public*/ NamedBean* BlockTableDataModel::getBySystemName(QString name) const
{
 return ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBySystemName(name);
}

/*public*/ NamedBean* BlockTableDataModel::getByUserName(QString name)
{
 return ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getByUserName(name);
}

/*protected*/ QString BlockTableDataModel::getMasterClassName()
{
 //return QString(this->metaObject()->className());
 return "jmri.jmrit.beantable.BlockTableAction";
}

/*public*/ void BlockTableDataModel::clickOn(NamedBean* t)
{
    // don't do anything on click; not used in this class, because
    // we override setValueAt
}

//Permissive and speed columns are temp disabled
/*public*/ int BlockTableDataModel::columnCount(const QModelIndex &parent) const
{
 return SPEEDCOL + 1;
}

/*public*/ QVariant BlockTableDataModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 int col = index.column();
 Block* b = (Block*) getBySystemName(sysNameList.at(row));

 if(role == Qt::CheckStateRole)
 {
  if (col == PERMISCOL)
  {
   bool val = b->getPermissiveWorking();
   return val?Qt::Checked:Qt::Unchecked;
  }
  else if (col == CURRENTREPCOL)
  {
   return b->isReportingCurrent()?Qt::Checked:Qt::Unchecked;
  }
 }
 if(role == Qt::DisplayRole)
 {
  // some error checking
  if (row >= sysNameList.size())
  {
      log->debug("requested getValueAt(\"" + QString::number(row) + "\"), row outside of range");
      return "Error table size";
  }
  if (b == NULL) {
      log->debug("requested getValueAt(\"" + QString::number(row) + "\"), Block doesn't exist");
      return "(no Block)";
  }
  if (col == DIRECTIONCOL)
  {
   return Path::decodeDirection(b->getDirection());
  }
  else if (col == CURVECOL)
  {
   //        QComboBox* c = new QComboBox(/*curveOptions*/);
   //        c->addItems(blockTableAction->curveOptions);
   //        if (b->getCurvature() == Block::NONE) {
   //            c->setCurrentIndex(0);
   //        } else if (b->getCurvature() == Block::GRADUAL) {
   //            c->setSelectedItem(blockTableAction->gradualText);
   //        } else if (b->getCurvature() == Block::TIGHT) {
   //            c->setSelectedItem(blockTableAction->tightText);
   //        } else if (b->getCurvature() == Block::SEVERE) {
   //            c->setSelectedItem(blockTableAction->severeText);
   //        }
   //        return c;
   return curveOptions.value(b->getCurvature());
  }
  else if (col == LENGTHCOL)
  {
   double len = 0.0;
   if (inchBox->isChecked())
   {
    len = b->getLengthIn();
   }
   else
   {
    len = b->getLengthCm();
   }
   return (blockTableAction->twoDigit->format(len));
  }
//  else if (col == PERMISCOL) {
//      bool val = b->getPermissiveWorking();
//      return (val);
//  }
  else if (col == SPEEDCOL)
  {
   QString speed = b->getBlockSpeed();
//        if (!blockTableAction->speedList.contains(speed)) {
//            blockTableAction->speedList.append(speed);
//        }
//        QComboBox* c = new QComboBox(/*speedList*/);
//        c->addItems(blockTableAction->speedList.toList());
//        c->setEditable(true);
//        c->setCurrentIndex(c->findText(speed));
      return speed;
  }
  else if (col == STATECOL)
  {
   switch (b->getState())
   {
       case (Block::OCCUPIED):
           return tr("Occupied");
       case (Block::UNOCCUPIED):
           return tr("UnOccupied");
       case (Block::UNKNOWN):
           return tr("Unknown");
       default:
           return tr("Inconsistent");
   }
  }
  else if (col == SENSORCOL)
  {
      Sensor* sensor = b->getSensor();
//        QComboBox* c = new QComboBox(/*sensorList*/);
//        c->addItems(blockTableAction->sensorList);
//        QString name = "";
//        if (sensor != NULL) {
//            name = sensor->getDisplayName();
//        }
//        c->setCurrentIndex(c->findText(name));
//        return c;
      if(sensor == NULL)
       return "";
      return sensor->getDisplayName();
  }
  else if (col == REPORTERCOL)
  {
      Reporter* r = b->getReporter();
      return (r != NULL) ? r->getDisplayName() : NULL;
  }
  else if (col == CURRENTREPCOL)
  {
      return (b->isReportingCurrent());
  }
  else if (col == EDITCOL) {  //
      return tr("Edit");
  }
  else {
   return BeanTableDataModel::data(index, role);
  }
 } // end DisplayRole

 if(blockTableAction->_graphicState && role == Qt::DecorationRole)
 {
  int col = index.column();

  if(col == STATECOL)
  {
   switch (b->getState())
   {
   case Block::OCCUPIED:
    return onIcon;
   case Block::UNOCCUPIED:
    return offIcon;
   case Block::UNKNOWN:
   case Block::INCONSISTENT:
    return QColor(Qt::red);
   default:
    break;
   }
  }
 }
 return QVariant();
}

/*public*/ bool BlockTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 Block* b = (Block*) getBySystemName(sysNameList.at(row));
 int col = index.column();
 if(role == Qt::CheckStateRole)
 {
  if (col == PERMISCOL)
  {
   bool boo =  value.toBool();
   b->setPermissiveWorking(boo);
   fireTableRowsUpdated(row, row);
   return true;
  }
  else if (col == CURRENTREPCOL)
  {
   bool boo =  value.toBool();
   b->setReportingCurrent(boo);
   fireTableRowsUpdated(row, row);
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  if (col == VALUECOL)
  {
   b->setValue(value);
   fireTableRowsUpdated(row, row);
  }
  else if (col == LENGTHCOL)
  {
   float len = 0.0f;
   bool bOk;
   len = value.toFloat(&bOk);
//   } catch (ParseException ex2) {
   if(!bOk)
    log->error(tr("Error parsing length value of \"%1\"").arg( value.toString()));
//  }
   if (blockTableAction->inchBox->isChecked())
   {
    b->setLength(len * 25.4);
   }
   else
   {
    b->setLength(len * 10.0);
   }
   fireTableRowsUpdated(row, row);
  }
  else if (col == CURVECOL)
  {
   //@SuppressWarnings("unchecked")
   QString cName =  /*((QComboBox*) value)->currentText()*/ value.toString();

   if (cName==(tr("None")))
   {
    b->setCurvature(Block::NONE);
   }
   else if (cName==(tr("Gradual")))
   {
    b->setCurvature(Block::GRADUAL);
   }
   else if (cName==(tr("Tight")))
   {
    b->setCurvature(Block::TIGHT);
   }
   else if (cName==(tr("Severe")))
   {
    b->setCurvature(Block::SEVERE);
   }
   fireTableRowsUpdated(row, row);
  }

  else if (col == SPEEDCOL)
  {
   //@SuppressWarnings("unchecked")
   QString speed =  /*(QComboBox*) value.to.getSelectedItem();*/ value.toString();
 //  try {
       b->setBlockSpeed(speed);
 //  } catch (JmriException* ex) {
 //      JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
 //      return;
 //  }
   if (!speedList.contains(speed) && !speed.contains("Global"))
   {
    speedList.append(speed);
   }
   fireTableRowsUpdated(row, row);
  }
  else if (col == REPORTERCOL)
  {
   Reporter* r = NULL;
   if ( value != QVariant())
   {
    r = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter(value.toString());
   }
   b->setReporter(r);
   fireTableRowsUpdated(row, row);
  }
  else if (col == SENSORCOL)
  {
   //@SuppressWarnings("unchecked")
   //QString strSensor = (QString) ((QComboBox*)
   //value).getSelectedItem();
   QString strSensor = value.toString();
   b->setSensor(strSensor);
   return true;
  }
  else if (col == EDITCOL)
  {
 #if 0
         class WindowMaker implements Runnable {

             Block b;

             WindowMaker(Block b) {
                 this.b = b;
             }

             /*public*/ void run() {
                 editButton(b); // don't really want to stop Route w/o user action
             }
         };
         WindowMaker t = new WindowMaker(b);
         javax.swing.SwingUtilities.invokeLater(t);
         //editButton(b);
 #endif
   editButton(b);
  }
  else
  {
   BeanTableDataModel::setData(index, value, role);
  }
 }
 return false;
}

/*public*/ QVariant BlockTableDataModel::headerData(int col, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (col == DIRECTIONCOL) {
        return "Direction";
    }
    if (col == VALUECOL) {
        return "Value";
    }
    if (col == CURVECOL) {
        return tr("Curvature");
    }
    if (col == LENGTHCOL) {
        return tr("Length");
    }
    if (col == PERMISCOL) {
        return tr("Permissive");
    }
    if (col == SPEEDCOL) {
        return tr("Speed");
    }
    if (col == STATECOL) {
        return tr("State");
    }
    if (col == REPORTERCOL) {
        return tr("Reporter");
    }
    if (col == SENSORCOL) {
        return tr("Sensor");
    }
    if (col == CURRENTREPCOL) {
        return tr("Use Current?");
    }
    if (col == EDITCOL) {
        return tr("Edit");
    }
 }
 return BeanTableDataModel::headerData(col, orientation, role);
}

/*public*/ QString BlockTableDataModel::getColumnClass(int col) {
    if (col == DIRECTIONCOL) {
        return "String";
    }
    if (col == VALUECOL) {
        return "String";  // not a button
    }
    if (col == CURVECOL) {
        return "JComboBox";
    }
    if (col == LENGTHCOL) {
        return "String";
    }
    if (col == PERMISCOL) {
        return "Boolean";
    }
    if (col == SPEEDCOL) {
        return "JComboBox";
    }
    if (col == STATECOL) {
      if (blockTableAction->_graphicState) {
          return "JLabel"; // use an image to show block state
      } else {
          return "String";
      }
    }
    if (col == REPORTERCOL) {
        return "String";
    }
    if (col == SENSORCOL) {
        return "JComboBox";
    }
    if (col == CURRENTREPCOL) {
        return "Boolean";
    }
    if (col == EDITCOL) {
        return "JButton";
    } else {
        return BeanTableDataModel::getColumnClass(col);
    }
}

/*public*/ int BlockTableDataModel::getPreferredWidth(int col) {
    if (col == DIRECTIONCOL) {
        return  JTextField(7).sizeHint().width();
    }
    if (col == CURVECOL) {
        return  JTextField(8).sizeHint().width();
    }
    if (col == LENGTHCOL) {
        return  JTextField(7).sizeHint().width();
    }
    if (col == PERMISCOL) {
        return  JTextField(7).sizeHint().width();
    }
    if (col == SPEEDCOL) {
        return  JTextField(7).sizeHint().width();
    }
    if (col == STATECOL) {
        return  JTextField(8).sizeHint().width();
    }
    if (col == REPORTERCOL) {
        return  JTextField(8).sizeHint().width();
    }
    if (col == SENSORCOL) {
        return  JTextField(8).sizeHint().width();
    }
    if (col == CURRENTREPCOL) {
        return  JTextField(7).sizeHint().width();
    }
    if (col == EDITCOL) {
        return  JTextField(7).sizeHint().width();
    } else {
        return BeanTableDataModel::getPreferredWidth(col);
    }
}

/*public*/ void BlockTableDataModel::configValueColumn(JTable* /*table*/) {
    // value column isn't button, so config is NULL
}

/*public*/ Qt::ItemFlags BlockTableDataModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags editable = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
 Qt::ItemFlags notEditable =  Qt::ItemIsSelectable | Qt::ItemIsEnabled;

 int col = index.column();
 if (col == CURVECOL)
 {
  return editable;
 }
 else if (col == LENGTHCOL)
 {
  return editable;
 }
 else if (col == PERMISCOL)
 {
  return  Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
 }
 else if (col == SPEEDCOL)
 {
  return editable;
 }
 else if (col == STATECOL)
 {
  return notEditable;
 }
 else if (col == REPORTERCOL)
 {
  return editable;
 }
 else if (col == SENSORCOL)
 {
  return editable;
 }
 else if (col == CURRENTREPCOL)
 {
  return  Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
 }
 else if (col == EDITCOL)
 {
  return editable;
 }
 else
 {
  return BeanTableDataModel::flags(index);
 }
}

/*public*/ void BlockTableDataModel::configureTable(JTable* table)
{
 #if 0
 table.setDefaultRenderer(JComboBox.class, new jmrit.symbolicprog.ValueRenderer());
 table.setDefaultEditor(JComboBox.class, new jmrit.symbolicprog.ValueEditor());
 table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
#endif
 //curveOptions = QStringList() << tr("None") << tr("Gradual") << tr("Tight") << tr("Severe");
 curveOptions = QMap<int, QString>();
 curveOptions.insert(Block::NONE, tr("None"));
 curveOptions.insert(Block::GRADUAL, tr("Gradual"));
 curveOptions.insert(Block::TIGHT, tr("Tight"));
 curveOptions.insert(Block::SEVERE, tr("Severe"));
 table->setItemDelegateForColumn(CURVECOL, new OBSComboBoxDelegate(this, curveOptions.values() ));
 //buttonMap.append(CURVECOL);

 QString defaultBlockSpeedText = ("Use Global " + ((BlockManager*)((BlockManager*)InstanceManager::getDefault("BlockManager")))->getDefaultSpeed());
 speedList.append(defaultBlockSpeedText);
 QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
 for (int i = 0; i < _speedMap.size(); i++) {
     if (!speedList.contains(_speedMap.at(i))) {
         speedList.append(_speedMap.at(i));
     }
 }
 table->setItemDelegateForColumn(SPEEDCOL, new OBSComboBoxDelegate(this, speedList.toList()));
 //buttonMap.append(SPEEDCOL);

 QStringList nameList = InstanceManager::sensorManagerInstance()->getSystemNameArray();

 QVector<QString> displayList = QVector<QString>(nameList.length());
 for (int i = 0; i < nameList.length(); i++)
 {
  NamedBean* nBean = InstanceManager::sensorManagerInstance()->getBeanBySystemName(nameList[i]);
  if (nBean != NULL) {
      displayList.replace(i, nBean->getDisplayName());
  }
 }
 //java.util.Arrays.sort(displayList);
 qSort(displayList.begin(), displayList.end(), SystemNameComparator::compare);

 QVector<QString> sensorList = QVector<QString>(displayList.size() + 1);
 sensorList.replace(0,"");
 int i = 1;
 foreach (QString name, displayList)
 {
  sensorList.replace(i,name);
  i++;
 }

 table->setItemDelegateForColumn(SENSORCOL, new OBSComboBoxDelegate(this, sensorList.toList()));
 //buttonMap.append(SENSORCOL);

 setColumnToHoldButton(table, EDITCOL);
 setColumnToHoldButton(table, DELETECOL);

 InstanceManager::sensorManagerInstance()->PropertyChangeSupport::addPropertyChangeListener(/*QPointer<PropertyChangeListener>*/((PropertyChangeListener*)this));
 ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->PropertyChangeSupport::addPropertyChangeListener((PropertyChangeListener*)this);
 configStateColumn(table);
 BeanTableDataModel::configureTable(table);
}

/*protected*/ bool BlockTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
 return true;
 // return (e.getPropertyName().indexOf("alue")>=0);
}

/*public*/ QPushButton* BlockTableDataModel::configureButton()
{
    log->error("configureButton should not have been called");
    return NULL;
}

/*public*/ void BlockTableDataModel::propertyChange(PropertyChangeEvent* e)
{
 //if (e->getSource() instanceof SensorManager)
 if(qobject_cast<SensorManager*>(e->getSource()))
 {
  if (e->getPropertyName()==("length") || e->getPropertyName()==("DisplayListName"))
  {
   updateSensorList();
  }
 }
 if (qobject_cast<ReporterManager*>(e->getSource()) ) {
     if (e->getPropertyName() == ("length") || e->getPropertyName() ==("DisplayListName")) { // NOI18N
         updateReporterList();
     }
 }
 if (e->getPropertyName()==("DefaultBlockSpeedChange"))
 {
  updateSpeedList();
 }
 else
 {
  BeanTableDataModel::propertyChange(e);
 }
}

/**
 * Set and refresh the UI to use Metric or Imperial values.
 * @param boo true if metric, false for Imperial.
 */
/*public*/ void BlockTableDataModel::setMetric(bool boo){
    metricUi = boo;
    fireTableDataChanged();
}

/*private*/ void BlockTableDataModel::updateSensorList() {
    QSet<NamedBean*> nameSet = InstanceManager::sensorManagerInstance()->getNamedBeanSet();
    QVector<QString> displayList = QVector<QString>(nameSet.size());
    int i = 0;
    for (NamedBean* nb : nameSet) {
     Sensor* nBean  = (Sensor*)nb;
        if (nBean != nullptr) {
            displayList[i++] = nBean->getDisplayName();
        }
    }
    //Arrays.sort(displayList);
    qSort(displayList.begin(), displayList.end());
    sensorList = QVector<QString>(displayList.length() + 1);
    sensorList[0] = "";
    i = 1;
    for (QString name : displayList) {
        sensorList[i] = name;
        i++;
    }
}

/*private*/ void BlockTableDataModel::updateReporterList() {
 QSet<NamedBean*> nameSet = InstanceManager::sensorManagerInstance()->getNamedBeanSet();
 QVector<QString> displayList = QVector<QString>(nameSet.size());
    int i = 0;
    for (NamedBean* nb : nameSet) {
     Reporter* nBean = (Reporter*)nb;
        if (nBean != nullptr) {
            displayList[i++] = nBean->getDisplayName();
        }
    }
    //Arrays.sort(displayList);
    qSort(displayList.begin(), displayList.end());
    reporterList = QVector<QString>(displayList.length() + 1);
    reporterList[0] = "";
    i = 1;
    for (QString name : displayList) {
        reporterList[i] = name;
        i++;
    }
}

/*private*/ void BlockTableDataModel::updateSpeedList() {
    speedList.removeOne(defaultBlockSpeedText);
    defaultBlockSpeedText = (tr("Use %1").arg("Global") + " " + ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getDefaultSpeed());
    speedList.insert(0, defaultBlockSpeedText);
    fireTableDataChanged();
}

/*public*/ void BlockTableDataModel::setDefaultSpeeds(JFrame* _who) {
    JComboBox* blockSpeedCombo = new JComboBox(speedList.toList());

    blockSpeedCombo->setEditable(true);

    JPanel* block = new JPanel(new FlowLayout());
    block->layout()->addWidget(new JLabel(tr("%1:").arg(tr("Block Speed"))));
    block->layout()->addWidget(blockSpeedCombo);

    blockSpeedCombo->removeItem(blockSpeedCombo->findText(defaultBlockSpeedText));

    blockSpeedCombo->setSelectedItem(((BlockManager*)InstanceManager::getDefault("BlockManager"))->getDefaultSpeed());

    // block of options above row of buttons; gleaned from Maintenance.makeDialog()
    // can be accessed by Jemmy in GUI test
    QString title = tr("Block Speed");
    // build JPanel for comboboxes
    JPanel* speedspanel = new JPanel();
    speedspanel->setLayout(new QVBoxLayout(speedspanel));//, BoxLayout.PAGE_AXIS));
    speedspanel->layout()->addWidget(new JLabel(tr("Select the default values for the speeds through the blocks")));
    //default LEFT_ALIGNMENT
    ((QVBoxLayout*)speedspanel->layout())->addWidget(block,0, Qt::AlignLeft);

    int retval = JOptionPane::showConfirmDialog(
            _who,
            speedspanel->windowTitle(),
            title,
            JOptionPane::OK_CANCEL_OPTION,
            JOptionPane::INFORMATION_MESSAGE);
    log->debug(tr("Retval = %1").arg(retval));
    if (retval != JOptionPane::OK_OPTION) { // OK button not clicked
        return;
    }

    QString speedValue =  blockSpeedCombo->getSelectedItem();
    //We will allow the turnout manager to handle checking if the values have changed
    try {
        ((BlockManager*)InstanceManager::getDefault("BlockManager"))->setDefaultSpeed(speedValue);
    } catch (IllegalArgumentException* ex) {
        JOptionPane::showMessageDialog(_who, ex.getMessage() + "\n" + speedValue);
    }
}

/*synchronized*/ /*public*/ void BlockTableDataModel::dispose()
{
  BeanTableDataModel::dispose();
  //InstanceManager::sensorManagerInstance().removePropertyChangeListener(this);
  disconnect(InstanceManager::sensorManagerInstance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/**
 * Customize the block table State column to show an appropriate
 * graphic for the block occupancy state if _graphicState = true, or
 * (default) just show the localized state text when the
 * TableDataModel is being called from ListedTableAction.
 *
 * @param table a JTable of Blocks
 */
/*protected*/ void BlockTableDataModel::configStateColumn(JTable* table) {
    // have the state column hold a JPanel (icon)
    //setColumnToHoldButton(table, VALUECOL, new JLabel("1234")); // for small round icon, but cannot be converted to JButton
    // add extras, override BeanTableDataModel
    log->debug(tr("Block configStateColumn (I am %1)").arg(BeanTableDataModel::toString()));
//    if (blockTableAction->_graphicState) { // load icons, only once
        //table.setDefaultEditor(JLabel.class, new ImageIconRenderer()); // there's no editor for state column in BlockTable
//        blockTableAction->table->setDefaultRenderer("JLabel", new ImageIconRenderer()); // item class copied from SwitchboardEditor panel
        // else, classic text style state indication, do nothing extra
//    }
}

void BlockTableDataModel::editButton(Block* b)
{
#if 1
 BlockEditAction* beanEdit = new BlockEditAction();
 beanEdit->setBean(b);
 beanEdit->actionPerformed(NULL);
#endif
}
#endif

/*protected*/ void BlockTableAction::setTitle() {
    f->setTitle(tr("Block Table"));
}

/*private*/ void BlockTableAction::initRadioButtons(){

    inchBox->setToolTip(tr("Check to display Length in inches.")); // NOI18N
    centimeterBox->setToolTip(tr("Check to display Length in centimeters.")); // NOI18N

    QButtonGroup* group = new QButtonGroup();
    group->addButton(inchBox);
    group->addButton(centimeterBox);
    inchBox->setChecked(true);
    centimeterBox->setChecked( ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))
        ->getSimplePreferenceState(BLOCK_METRIC_PREF));

    //inchBox.addActionListener(this::metricSelectionChanged);
    connect(inchBox, &QCheckBox::clicked, [=]{metricSelectionChanged();});
    //centimeterBox.addActionListener(this::metricSelectionChanged);
    connect(centimeterBox, &QCheckBox::clicked, [=]{metricSelectionChanged();});

    // disabling keyboard input as when focused, does not fire actionlistener
    // and appears selected causing mismatch with button selected and what the table thinks is selected.
//    inchBox->setFocusable(false);
//    centimeterBox.setFocusable(false);
}

/**
 * Add the checkboxes
 */
/*public*/ void BlockTableAction::addToFrame(BeanTableFrame* f) {
 initRadioButtons();
    //final BeanTableFrame finalF = f;	// needed for anonymous ActionListener class
    f->addToBottomBox(inchBox, this->metaObject()->className());
//    inchBox->setToolTip(tr("Check to display Length in inches."));
//    inchBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(inchBox, &QRadioButton::clicked, [=]{
            metricSelectionChanged();
//        }
    });
    f->addToBottomBox(centimeterBox, this->metaObject()->className());
    centimeterBox->setToolTip(tr("Check to display Length in centimeters."));
//    centimeterBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(centimeterBox, &QRadioButton::clicked, [=]{
            metricSelectionChanged();
//        }
    });
}

/*public*/ void BlockTableAction::setMenuBar(BeanTableFrame* f) {
    finalF = f;			// needed for anonymous ActionListener class
    QMenuBar* menuBar = f->menuBar();
    QMenu* pathMenu = new QMenu("Paths");
    menuBar->addMenu(pathMenu);
    QAction* item = new QAction("Delete Paths...", this);
    pathMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(item, &QAction::triggered, [=]{
            deletePaths(finalF);
//        }
    });
    QMenu* speedMenu = new QMenu("Speeds");
    item = new QAction("Defaults...", this);
    speedMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(item, &QAction::triggered, [=]{
     ((BlockTableDataModel*)m)->setDefaultSpeeds(finalF);
//        }
    });

    menuBar->addMenu(speedMenu);

}

/*private*/ void BlockTableAction::metricSelectionChanged(/*ActionEvent e*/) {
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))
        ->setSimplePreferenceState(BLOCK_METRIC_PREF, centimeterBox->isChecked());
    ((BlockTableDataModel*)m)->setMetric(centimeterBox->isChecked());
}

//@Override
/*protected*/ QString BlockTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.BlockTable";
}


/*protected*/ void BlockTableAction::addPressed(JActionEvent* /*e*/)
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if (addFrame == NULL)
 {
  addFrame = new JmriJFrameX(tr("Add Block"), false, true);
  addFrame->setEscapeKeyClosesWindow(true);
  addFrame->addWindowListener(new ABWindowListener(this));
  addFrame->addHelpMenu("package.jmrit.beantable.BlockAddEdit", true); //IN18N
//        addFrame.getContentPane().setLayout(new BoxLayout(addFrame.getContentPane(), BoxLayout.Y_AXIS));
  QWidget* centralWidget = new QWidget();
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
  ActionListener* oklistener = new BTActionListener(this);
//  {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                okPressed(e);
//            }
//        };
  BTCancelListener* cancellistener = new BTCancelListener(this);

  AddNewBeanPanel* anbp = new AddNewBeanPanel(sysName, userName, numberToAddSpinner, addRangeCheckBox, _autoSystemNameCheckBox, tr("Create"), oklistener, cancellistener, statusBar);
  addFrame->setCentralWidget(centralWidget);
  newButton = anbp->ok;
  sysName->setToolTip(tr("<html>Enter System Name for this new item, e.g. X{0}12<br>where X = the prefix for your connection<br>and %1 = is the letter for the item type.</html>").arg("B")); // override tooltip with bean specific letter
 }

 sysName->setBackground(Qt::white);
 // reset statusBar text
 statusBar->setText(tr("Enter a System Name and (optional) User Name."));
 statusBar->setForeground(Qt::gray);
 if (((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->getSimplePreferenceState(systemNameAuto)) {
     _autoSystemNameCheckBox->setChecked(true);
 }
 if (newButton!=nullptr){
//     addFrame.getRootPane().setDefaultButton(newButton);
     newButton->setDefault(true);
 }
 addRangeCheckBox->setChecked(false);
 addFrame->pack();
 addFrame->setVisible(true);
}

void BlockTableAction::cancelPressed(JActionEvent* /*e*/) {
 if(addFrame){
  addFrame->setVisible(false);
  addFrame->dispose();
  addFrame = NULL;
 }
}

void BlockTableAction::okPressed(JActionEvent* /*e*/)
{
 int numberOfBlocks = 1;

 if (addRangeCheckBox->isChecked()) {
     numberOfBlocks =  numberToAddSpinner->value();
 }
 if (numberOfBlocks >= 65) { // limited by JSpinnerModel to 100
     if (JOptionPane::showConfirmDialog(addFrame,
             tr("You are about to add %1 %2 into the configuration.\nAre you sure?eans").arg(tr("Blocks")).arg(numberOfBlocks),
             tr("Warning"),
             JOptionPane::YES_NO_OPTION) == 1) {
         return;
     }
 }
 QString user = NamedBean::normalizeUserName(userName->text());
 if (user.isNull() || user.isEmpty()) {
  user = QString();
 }
 QString uName = user; // keep result separate to prevent recursive manipulation
 QString system = "";

 if (!_autoSystemNameCheckBox->isChecked()) {
     system = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->makeSystemName(sysName->text());
 }
 QString sName = system; // keep result separate to prevent recursive manipulation
 // initial check for empty entry using the raw name
 if (sName.length() < 3 && !_autoSystemNameCheckBox->isChecked()) {  // Using 3 to catch a plain IB
     statusBar->setText(tr("System Name field can not be left blank."));
     statusBar->setForeground(Qt::red);
     sysName->setBackground(Qt::red);
     return;
 } else {
     sysName->setBackground(Qt::white);
 }

 // Add some entry pattern checking, before assembling sName and handing it to the blockManager
 QString statusMessage = QString(tr("New %1(s) added:").arg(tr("Block")));

 for (int x = 0; x < numberOfBlocks; x++)
 {
  if (x != 0)
  { // start at 2nd Block
   if (!_autoSystemNameCheckBox->isChecked())
   {
    // Find first block with unused system name
    while (true) {
     system = nextName(system);
     // log.warn("Trying " + system);
     Block* blk = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBySystemName(system);
     if (blk == nullptr) {
         sName = system;
         break;
     }
    }
   }
   if (user != "")
   {
    // Find first block with unused user name
    while (true)
    {
     user = nextName(user);
     //log.warn("Trying " + user);
     Block* blk = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->getByUserName(user);
     if (blk == nullptr) {
         uName = user;
         break;
     }
    }
   }
  }
  Block* blk;
  QString xName = "";
  try {
   if (_autoSystemNameCheckBox->isChecked())
   {
      blk = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->createNewBlock(user);
      if (blk == nullptr)
      {
         xName = uName;
         throw new IllegalArgumentException();
      }
   } else {
       blk = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->createNewBlock(sName, user);
       if (blk == nullptr) {
           xName = sName;
           throw new IllegalArgumentException();
       }
   }
  } catch (IllegalArgumentException* ex) {
   // user input no good
   handleCreateException(xName);
   statusBar->setText(tr("Check that number/name is OK and not in use."));
   statusBar->setForeground(Qt::red);
   return; // without creating
  }

 }

 // provide feedback to user
 statusBar->setText(statusMessage/*.toString()*/);
 statusBar->setForeground(Qt::gray);

 pref->setSimplePreferenceState(systemNameAuto, _autoSystemNameCheckBox->isChecked());
 // ((BlockManager*)InstanceManager::getDefault("BlockManager")).createNewBlock(sName, user);
}

void BlockTableAction::handleCreateException(QString sysName)
{
    JOptionPane::showMessageDialog(addFrame,
            tr("Could not create block \%1\" to add it. Check that number/name is OK.").arg(sysName),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

void BlockTableAction::deletePaths(JmriJFrame* f) {
    // Set option to prevent the path information from being saved.

    QVariantList options = {"Remove",
        "Keep"};

    int retval = JOptionPane::showOptionDialog(f, tr("Any path information will not be saved, and will be\nrebuilt by the Layout Editor when the panel is re-opened"), tr("Save Block Path Information"),
            JOptionPane::YES_NO_OPTION,
            JOptionPane::QUESTION_MESSAGE, QIcon(), options, options[1]);
    if (retval != 0) {
        ((BlockManager*)InstanceManager::getDefault("BlockManager"))->setSavedPathInfo(true);
        log->info("Requested to save path information via Block Menu.");
    } else {
        ((BlockManager*)InstanceManager::getDefault("BlockManager"))->setSavedPathInfo(false);
        log->info("Requested not to save path information via Block Menu.");
    }
}

//@Override
/*public*/ QString BlockTableAction::getClassDescription() {
    return tr("Block Table");
}

//@Override
/*protected*/ QString BlockTableAction::getClassName() {
 return "jmri.jmrit.beantable.BlockTableAction";
}

/*private*/ /*final*/ /*static*/ Logger* BlockTableAction::log = LoggerFactory::getLogger("BlockTableAction");
