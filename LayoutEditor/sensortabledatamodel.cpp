#include "sensortabledatamodel.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include "abstractsensor.h"
#include "jtextfield.h"
#include "jtable.h"
#include "abstractsensormanager.h"
#include "../Tables/logixtableaction.h" // for PushButtonItemDelegate
#include <QSignalMapper>
#include "systemnamecomparator.h"
#include "guilafpreferencesmanager.h"
#include "imageio.h"
#include "bufferedimage.h"
#include <QIcon>
#include "file.h"
#include "fileutil.h"
#include "jbutton.h"
#include "sensoreditaction.h"

SensorTableDataModel::SensorTableDataModel(QObject *parent) :
    BeanTableDataModel(parent)
{
 common();
}
/**
 * Data model for a SensorTable
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2009
 * @version     $Revision: 20803 $
 */

///*public*/ class SensorTableDataModel extends BeanTableDataModel {


//    /*public*/ SensorTableDataModel() {
//        super();
//    }
void SensorTableDataModel::common()
{
 senManager = (SensorManager*)InstanceManager::sensorManagerInstance();
 setObjectName("SensorTableDataModel");
 log = new Logger("SensorDataModel");
 deleteMapper = new QSignalMapper();
 table = nullptr;
 // load graphic state column display preference
 _graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();
 rootPath = FileUtil::getProgramPath() + "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
 beanTypeChar = 'S'; // for Sensor
 onIconPath = rootPath + beanTypeChar + "-on-s.png";
 offIconPath = rootPath + beanTypeChar + "-off-s.png";

 init();
}

/*public*/ SensorTableDataModel::SensorTableDataModel(SensorManager* manager, QObject *parent) : BeanTableDataModel(parent)
{
 //super();
 common();
 senManager = manager;
 ProxySensorManager* proxy = nullptr;
 AbstractSensorManager* mgr = nullptr;
 if(qobject_cast<ProxySensorManager*>(senManager) != nullptr)
 {
  proxy = (ProxySensorManager*)(senManager);
  proxy->removePropertyChangeListener((PropertyChangeListener*) this);
  //disconnect(proxy->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else
 {
  mgr = static_cast<AbstractSensorManager*>(senManager);
  mgr->removePropertyChangeListener((PropertyChangeListener*) this);
  //disconnect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

// getManager()->removePropertyChangeListener((PropertyChangeListener*)this);
// AbstractSensorManager* mgr = (AbstractSensorManager*)getManager();
// disconnect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b!=nullptr)
   {
    b->removePropertyChangeListener((PropertyChangeListener*)this);
    AbstractNamedBean* anb = (AbstractNamedBean*)b;
//    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }
 senManager = (SensorManager*)manager;
// getManager()->addPropertyChangeListener((PropertyChangeListener*)this);
// //ProxySensorManager* mgr = (ProxySensorManager*)getManager();
// connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if(proxy != nullptr)
 {
  proxy->addPropertyChangeListener((PropertyChangeListener*) this);
  connect(proxy->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 if(mgr != nullptr)
 {
  mgr->addPropertyChangeListener((PropertyChangeListener*) this);
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //connect(aMgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 updateNameList();
 // load graphic state column display preference
 _graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();

}

/*public*/ QString SensorTableDataModel::getValue(QString name) const
{
 Sensor* sen;
 if(qobject_cast<ProxySensorManager*>(senManager)!= nullptr)
  sen = ((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  sen = (Sensor*)senManager->getBeanBySystemName(name);
 int val = sen->getKnownState();
 switch (val) {
 case Sensor::ACTIVE: return tr("Active");
 case Sensor::INACTIVE: return tr("Inactive");
 case Sensor::UNKNOWN: return tr("Unknown");
 case Sensor::INCONSISTENT: return tr("Inconsistent");
 default: return "Unexpected value: "+val;
 }
}
/*protected*/ void SensorTableDataModel::setManager(Manager* manager)
{
 //((AbstractManager*)getManager())->removePropertyChangeListener((PropertyChangeListener*)this);
 ProxySensorManager* mgr = (ProxySensorManager*)getManager();
 disconnect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b!=nullptr)
   {
    b->removePropertyChangeListener((PropertyChangeListener*)this);
    AbstractNamedBean* anb = (AbstractNamedBean*)b;
//    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }
 senManager = (SensorManager*)manager;
 getManager()->addPropertyChangeListener((PropertyChangeListener*)this);
 //ProxySensorManager* mgr = (ProxySensorManager*)getManager();
 //connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 updateNameList();
}
/*protected*/ Manager* SensorTableDataModel::getManager()
{
 if (senManager==nullptr)
  senManager= InstanceManager::sensorManagerInstance();
 return senManager;
}
/*protected*/ NamedBean* SensorTableDataModel::getBySystemName(QString name) const
{
 if(qobject_cast<ProxySensorManager*>(senManager) != nullptr)
  return ((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  return ((SensorManager*)senManager)->getBySystemName(name);
}
/*protected*/ NamedBean* SensorTableDataModel::getByUserName(QString name) { return ((ProxySensorManager*)senManager)->getByUserName(name);}

/*protected*/ QString SensorTableDataModel::getMasterClassName() { return getClassName(); }
/*protected*/ void SensorTableDataModel::clickOn(NamedBean* t)
{
 try {
        int state = ((AbstractSensor*)t)->getKnownState();
        if (state==Sensor::INACTIVE) ((AbstractSensor*)t)->setKnownState(Sensor::ACTIVE);
        else ((AbstractSensor*)t)->setKnownState(Sensor::INACTIVE);
    } catch (JmriException e) { log->warn("Error setting state: "+e.getMessage()); }
}

/*public*/ int SensorTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{
    return QUERYCOL + getPropertyColumnCount() + 1;
}

/*public*/ QVariant SensorTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
  switch (col) {
      case INVERTCOL:
          return tr("Inverted");
      case EDITCOL:
          return "";
      case USEGLOBALDELAY:
          return tr("Use Global Delays");
      case ACTIVEDELAY:
          return tr("Delay to Active");
      case INACTIVEDELAY:
          return tr("Delay to Inactive");
      case PULLUPCOL:
          return tr("Pull-Up/Down");
      case FORGETCOL:
          return tr("State");
      case QUERYCOL:
          return tr("State");
      default:
          //return BeanTableDataModel::getColumnName(col);
          break;
  }
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString SensorTableDataModel::getColumnClass(int col) const {
    switch (col) {
        case INVERTCOL:
            return "Boolean";
        case EDITCOL:
            return "JButton";
        case USEGLOBALDELAY:
            return "Boolean";
        case ACTIVEDELAY:
            return "String";
        case INACTIVEDELAY:
            return "String";
        case PULLUPCOL:
            return "JComboBox";
        case FORGETCOL:
            return "JButton";
        case QUERYCOL:
            return "JButton";
        case VALUECOL:
            if (_graphicState) {
                return "JLabel"; // use an image to show sensor state
            } else {
                return BeanTableDataModel::getColumnClass(col);
            }
        default:
            return BeanTableDataModel::getColumnClass(col);
    }
}
/*public*/ int SensorTableDataModel::getPreferredWidth(int col) {
 switch (col) {
     case INVERTCOL:
         return  JTextField(4).getPreferredSize().width();
     case USEGLOBALDELAY:
     case ACTIVEDELAY:
     case INACTIVEDELAY:
         return  JTextField(8).getPreferredSize().width();
     case EDITCOL:
         return  JTextField(7).getPreferredSize().width();
     case FORGETCOL:
         return  JButton(tr("State"))
                 .sizeHint().width();
     case QUERYCOL:
         return  JButton(tr("State"))
                 .sizeHint().width();
     default:
         return BeanTableDataModel::getPreferredWidth(col);
 }
}
/*public*/ Qt::ItemFlags SensorTableDataModel::flags(const QModelIndex &index) const
{
 int col = index.column();
 int row = index.row();
 //if (col==INVERTCOL) return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
 QString name = sysNameList.at(row);
  Sensor* sen = (Sensor*)senManager->getBySystemName(name);
  if (sen == nullptr) {
      return Qt::ItemIsEnabled;
  }
  if (col == INVERTCOL) {
      return sen->canInvert()? Qt::ItemIsEnabled |Qt::ItemIsUserCheckable: Qt::ItemIsEnabled;
  }
  if (col == EDITCOL) {
      return Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  if (col == USEGLOBALDELAY) {
      return Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  //Need to do something here to make it disable
  if (col == ACTIVEDELAY || col == INACTIVEDELAY) {
      //return !sen.getUseDefaultTimerSettings();
     return sen->getUseDefaultTimerSettings() ? Qt::ItemIsEnabled : Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  if (col == PULLUPCOL) {
      return senManager->isPullResistanceConfigurable()? Qt::ItemIsEnabled : Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  if (col == FORGETCOL) {
      return Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  if (col == QUERYCOL) {
      return Qt::ItemIsEnabled | Qt::ItemIsEditable;
  }
  return BeanTableDataModel::isCellEditable(row, col)? Qt::ItemIsEnabled : Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

/*public*/ QVariant SensorTableDataModel::data(const QModelIndex &index, int role) const
{
 QString name = sysNameList.at(index.row());
 AbstractSensor* s;
 if(qobject_cast<ProxySensorManager*>(senManager) != 0)
  s = (AbstractSensor*)((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  s = (AbstractSensor*)((AbstractSensorManager*)senManager)->getBySystemName(name);

 if(role == Qt::CheckStateRole)
 {
  switch(index.column())
  {
   case INVERTCOL:
    return s->getInverted()?Qt::Checked:Qt::Unchecked;
   case USEGLOBALDELAY:
    return s->useDefaultTimerSettings()?Qt::Checked:Qt::Unchecked;
   default:
    break;
  }
 }
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  if (row >= sysNameList.size())
  {
   log->debug("row is greater than name list");
   return "";
  }
  if (s == nullptr)
  {
   log->debug("error NULL sensor!");
   return "error";
  }
//  if (col==INVERTCOL) {
//        boolean val = s.getInverted();
//        return Boolean.valueOf(val);
//    }
//    else if(col==USEGLOBALDELAY){
//        boolean val = s.useDefaultTimerSettings();
//        return Boolean.valueOf(val);
//    }
  if(col==ACTIVEDELAY)
  {
   return (int)s->getSensorDebounceGoingActiveTimer();
  }
  else if(col==INACTIVEDELAY)
  {
   return (int)s->getSensorDebounceGoingInActiveTimer();
  }
  else if(col == VALUECOL)
  {
   switch (s->getState())
   {
       case (Sensor::ACTIVE):
           return tr("Active");
       case (Sensor::INACTIVE):
           return tr("Inactive");
       case (Sensor::UNKNOWN):
           return tr("Unknown");
       default:
           return tr("Inconsistent");
   }
  }
  else if (col == INVERTCOL || col == USEGLOBALDELAY)
   return "";
  else if(col == EDITCOL) return tr("Edit");
  else if(col == PULLUPCOL)
  {
//   PullResistanceComboBox c = new PullResistanceComboBox(Sensor.PullResistance.values());
//                   c.setSelectedItem(s.getPullResistance());
//                   c.addActionListener(super::comboBoxAction);
  }
  else if(col == FORGETCOL) return tr("Forget");
  else if(col == QUERYCOL) return tr("Query");
 }
 if(_graphicState && role == Qt::DecorationRole)
 {
  int col = index.column();

  if(col == VALUECOL)
  {
   switch (s->getState()) {
   case Sensor::ACTIVE:
    return onIcon;
   case Sensor::INACTIVE:
    return offIcon;
   case Sensor::INCONSISTENT:
   return QColor(Qt::red);
   case Sensor::UNKNOWN:
   default:
    break;
   }
  }
  if(iconHeight > 0)
   _table->setRowHeight(row, offIcon.height());
 }
 return BeanTableDataModel::data(index, role);
}

/*public*/ bool SensorTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
 if (row >= sysNameList.size())
 {
  log->debug("row is greater than name list");
  return false;
 }
 QString name = sysNameList.at(row);
 Sensor* s;
 if(qobject_cast<ProxySensorManager*>(senManager) != nullptr)
  s = ((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  s = ((ProxySensorManager*)senManager)->getBySystemName(name);

 if (s == nullptr)
 {
  log->debug("error NULL sensor!");
  return false;
 }
 if(role == Qt::CheckStateRole)
 {
  if (col==INVERTCOL)
  {
//        boolean b = ((Boolean)value).booleanValue();
   s->setInverted(value.toBool());
   return true;
  }
  else if(col==USEGLOBALDELAY)
  {
//        boolean b = ((Boolean)value).booleanValue();
   s->useDefaultTimerSettings(value.toBool());
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  if(col==ACTIVEDELAY)
  {
//        String val = (String)value;
//        long goingActive = Long.valueOf(val);
   s->setSensorDebounceGoingActiveTimer(value.toInt());
   return true;
  }
  else if(col==INACTIVEDELAY)
  {
//        String val = (String)value;
//        long goingInActive = Long.valueOf(val);
   s->setSensorDebounceGoingInActiveTimer(value.toInt());
   return true;
  }
  else if(col == VALUECOL)
  {
   if (_graphicState)
   { // respond to clicking on ImageIconRenderer CellEditor
       clickOn(s);
       fireTableRowsUpdated(row, row);
   } else {
       BeanTableDataModel::setData(index, value, role);
   }
  }
  else if(EDITCOL)
  {
   editButton(s);
  }
  else if(col == PULLUPCOL)
  {
//   s->setPullResistance(value.toString());
  }
  else if(col == FORGETCOL)
  {
   try {
       s->setKnownState(Sensor::UNKNOWN);
   } catch (JmriException e) {
       log->warn("Failed to set state to UNKNOWN: ", e);
   }
  }
  else if(col == QUERYCOL)
  {
   try {
        s->setKnownState(Sensor::UNKNOWN);
    } catch (JmriException e) {
        log->warn("Failed to set state to UNKNOWN: ", e);
    }
    s->requestUpdateFromLayout();
    //break;
  }
  else if(col == VALUECOL)
  {
   if (_graphicState) { // respond to clicking on ImageIconRenderer CellEditor
       clickOn(s);
       fireTableRowsUpdated(row, row);
   } else {
       BeanTableDataModel::setValueAt(value, row, col);
   }
  }
 }
 return BeanTableDataModel::setData(index, value, role);
}

/*protected*/ QString SensorTableDataModel::getBeanType()
{
 return tr("Sensor");
}

/*protected*/ bool SensorTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
 if ((e->getPropertyName().indexOf("inverted")>=0) || (e->getPropertyName().indexOf("GlobalTimer")>=0) ||
        (e->getPropertyName().indexOf("ActiveTimer")>=0) || (e->getPropertyName().indexOf("InActiveTimer")>=0)){
  return true;
  if(e->getPropertyName() == "KnownState") return true;
 }
 else return BeanTableDataModel::matchPropertyName(e);
}

/**
 * Customize the sensor table Value (State) column to show an appropriate
 * graphic for the sensor state if _graphicState = true, or (default) just
 * show the localized state text when the TableDataModel is being called
 * from ListedTableAction.
 *
 * @param table a JTable of Sensors
 */
//@Override
/*protected*/ void SensorTableDataModel::configValueColumn(JTable* table) {
    // have the value column hold a JPanel (icon)
    //setColumnToHoldButton(table, VALUECOL, new JLabel("1234")); // for small round icon, but cannot be converted to JButton
    // add extras, override BeanTableDataModel
    log->debug(tr("Sensor configValueColumn (I am %1)").arg(this->metaObject()->className()));
    if (_graphicState) { // load icons, only once
     loadIcons();
//        table.setDefaultEditor(JLabel.class, new ImageIconRenderer()); // editor
//        table.setDefaultRenderer(JLabel.class, new ImageIconRenderer()); // item class copied from SwitchboardEditor panel
    } else {
        BeanTableDataModel::configValueColumn(table); // classic text style state indication
    }
}

/**
 * Visualize state in table as a graphic, customized for Sensors (2 states).
 * Renderer and Editor are identical, as the cell contents are not actually
 * edited, only used to toggle state using {@link #clickOn}.
 */
//class ImageIconRenderer extends AbstractCellEditor implements TableCellEditor, TableCellRenderer {

//    /*protected*/ QLabel* label;
//    /*protected*/ QString rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
//    /*protected*/ char beanTypeChar = 'S'; // for Sensor
//    /*protected*/ QString onIconPath = rootPath + beanTypeChar + "-on-s.png";
//    /*protected*/ QString offIconPath = rootPath + beanTypeChar + "-off-s.png";
//    /*protected*/ BufferedImage* onImage;
//    /*protected*/ BufferedImage* offImage;
//    /*protected*/ ImageIcon* onIcon;
//    /*protected*/ ImageIcon* offIcon;
//    /*protected*/ int iconHeight = -1;
#if 0
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Component* getTableCellRendererComponent(
            JTable table, Object value, boolean isSelected,
            boolean hasFocus, int row, int column) {
        log.debug("Renderer Item = {}, State = {}", row, value);
        if (iconHeight < 0) { // load resources only first time, either for renderer or editor
            loadIcons();
            log.debug("icons loaded");
        }
        return updateLabel((String) value, row);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Component* getTableCellEditorComponent(
            JTable table, Object value, boolean isSelected,
            int row, int column) {
        log.debug("Renderer Item = {}, State = {}", row, value);
        if (iconHeight < 0) { // load resources only first time, either for renderer or editor
            loadIcons();
            log.debug("icons loaded");
        }
        return updateLabel((String) value, row);
    }

    /*public*/ JLabel* updateLabel(QString value, int row) {
        if (iconHeight > 0) { // if necessary, increase row height;
            table.setRowHeight(row, Math.max(table.getRowHeight(), iconHeight - 5)); // adjust table row height for Sensor icon
        }
        if (value.equals(Bundle.getMessage("SensorStateInactive")) && offIcon != null) {
            label = new JLabel(offIcon);
            label.setVerticalAlignment(JLabel.BOTTOM);
            log.debug("offIcon set");
        } else if (value.equals(Bundle.getMessage("SensorStateActive")) && onIcon != null) {
            label = new JLabel(onIcon);
            label.setVerticalAlignment(JLabel.BOTTOM);
            log.debug("onIcon set");
        } else if (value.equals(Bundle.getMessage("BeanStateInconsistent"))) {
            label = new JLabel("X", JLabel.CENTER); // centered text alignment
            label.setForeground(Color.red);
            log.debug("Sensor state inconsistent");
            iconHeight = 0;
        } else if (value.equals(Bundle.getMessage("BeanStateUnknown"))) {
            label = new JLabel("?", JLabel.CENTER); // centered text alignment
            log.debug("Sensor state unknown");
            iconHeight = 0;
        } else { // failed to load icon
            label = new JLabel(value, JLabel.CENTER); // centered text alignment
            log.warn("Error reading icons for SensorTable");
            iconHeight = 0;
        }
        label.setToolTipText(value);
        label.addMouseListener(new MouseAdapter() {
            @Override
            public final void mousePressed(MouseEvent evt) {
                log.debug("Clicked on icon in row {}", row);
                stopCellEditing();
            }
        });
        return label;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QVariant getCellEditorValue() {
        log.debug("getCellEditorValue, me = {})", this);
        return this.toString();
    }
#endif
//    /*public*/ ImageIconRenderer::ImageIconRenderer()
//    {
//      rootPath = FileUtil::getProgramPath() + "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
//      beanTypeChar = 'S'; // for Sensor
//      onIconPath = rootPath + beanTypeChar + "-on-s.png";
//      offIconPath = rootPath + beanTypeChar + "-off-s.png";
//      loadIcons();
//    }
    /**
     * Read and buffer graphics. Only called once for this table.
     *
     * @see #getTableCellEditorComponent(JTable, Object, boolean, int, int)
     */
    /*protected*/ void SensorTableDataModel::loadIcons() {
        try {
            onImage = ImageIO::read(new File(onIconPath));
            offImage = ImageIO::read(new File(offIconPath));
        } catch (IOException ex) {
            log->error(tr("error reading image from %1 or %2").arg(onIconPath).arg(offIconPath), ex);
        }
        log->debug("Success reading images");
        int imageWidth = onImage->width();
        int imageHeight = onImage->height();
        // scale icons 50% to fit in table rows
        QImage smallOnImage = onImage->getScaledInstance(imageWidth / 2, imageHeight / 2,0/*, Image.SCALE_DEFAULT*/);
        QImage smallOffImage = offImage->getScaledInstance(imageWidth / 2, imageHeight / 2, 0/*, Image.SCALE_DEFAULT*/);
//        onIcon = new ImageIcon(smallOnImage);
        onIcon = QPixmap::fromImage(smallOnImage);
//        offIcon = new ImageIcon(smallOffImage);
        offIcon = QPixmap::fromImage(smallOffImage);
        iconHeight = onIcon.height();
    }

//} // end of ImageIconRenderer class

///*private*/ /*static*/ Logger* ImageIconRenderer::log = LoggerFactory::getLogger("ImageIconRenderer");

//@Override
/*public*/ void SensorTableDataModel::configureTable(JTable* table)
{
 this->table = table;
 showDebounce(false);
 //setColumnToHoldButton(table, PULLUPCOL, new JComboBoxEditor(QStringList({tr("Pull-up Resistor Enabled"), tr("Pull-down Resistor Enabled"), tr("No Pull-up/Pull-down")})));
 table->setItemDelegateForColumn(PULLUPCOL, new JComboBoxEditor(QStringList({tr("Pull-up Resistor Enabled"), tr("Pull-down Resistor Enabled"), tr("No Pull-up/Pull-down")})));
 BeanTableDataModel::configureTable(table);
 table->resizeRowsToContents();

}
void SensorTableDataModel::editButton(Sensor* s) {
    SensorEditAction* beanEdit = new SensorEditAction();
    beanEdit->setBean(s);
    beanEdit->actionPerformed(/*null*/);
}

/*public*/ void SensorTableDataModel::showDebounce(bool show)
{
 if(table == nullptr) return;
//    XTableColumnModel columnModel = (XTableColumnModel)table.getColumnModel();
//    TableColumn column  = columnModel.getColumnByModelIndex(USEGLOBALDELAY);
//    columnModel.setColumnVisible(column, show);
 table->setColumnHidden(USEGLOBALDELAY, !show);
//    column  = columnModel.getColumnByModelIndex(ACTIVEDELAY);
//    columnModel.setColumnVisible(column, show);
 table->setColumnHidden(ACTIVEDELAY, !show);
//    column  = columnModel.getColumnByModelIndex(INACTIVEDELAY);
//    columnModel.setColumnVisible(column, show);
 table->setColumnHidden(INACTIVEDELAY, !show);
}

/*protected*/ QString SensorTableDataModel::getClassName() { return "jmri.jmrit.beantable.SensorTableAction"; }

// /*public*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
/*public*/ QString SensorTableDataModel::getClassDescription() { return tr("Sensor Table"); }

// /*protected*/ /*synchronized*/ void SensorTableDataModel::updateNameList()
//{
// //Manager* mgr = getManager();
// Manager* mgr = senManager;

// // first, remove listeners from the individual objects
// if (!sysNameList.isEmpty())
// {
//  for (int i = 0; i< sysNameList.size(); i++)
//  {
//   // if object has been deleted, it's not here; ignore it
//   NamedBean* b = getBySystemName(sysNameList.at(i));
//   if (b!=NULL)
//   {
//    b->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractNamedBean* anb = (AbstractNamedBean*)b;
//    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

//   }
//  }
// }
// if(qobject_cast<ProxySensorManager*>(mgr) != NULL)
//  sysNameList = ((ProxySensorManager*)mgr)->getSystemNameList();
// else
//  sysNameList = ((AbstractSensorManager*)mgr)->getSystemNameList();
// qSort(sysNameList.begin(), sysNameList.end(), SystemNameComparator::compare);
// // and add them back in
// for (int i = 0; i< sysNameList.size(); i++)
// {
//  //getBySystemName(sysNameList.at(i))->addPropertyChangeListener((PropertyChangeListener*)this, NULL, "Table View");
////  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//  NamedBean* b = getBySystemName(sysNameList.at(i));
//  if (b!=NULL)
//  {
//   b->addPropertyChangeListener((PropertyChangeListener*)this, NULL, "Table View");
//   AbstractNamedBean* anb = (AbstractNamedBean*)b;
//   connect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//  }
// }
//}
void SensorTableDataModel::OnDelete(int row)
{
 QString name = sysNameList.at(row);
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 NamedBean* bean = mgr->getBeanBySystemName(name);
 if(bean != nullptr)
 {
  mgr->deregister(bean);
  sysNameList.removeAt(row);
  fireTableDataChanged();
 }
}
