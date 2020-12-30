#include "layoutblock.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "layouteditor.h"
#include "rosterentry.h"
#include "lnsensor.h"
#include "jseparator.h"
#include "connectivityutil.h"
#include "createeditblock.h"
#include "path.h"
#include "memoryicon.h"
#include "jmricolorchooser.h"
#include "joptionpane.h"

QVector<int>* LayoutBlock::updateReferences = new QVector<int>();
long LayoutBlock::time=0;

//LayoutBlock::LayoutBlock(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * A LayoutBlock is a group of track segments and turnouts on a LayoutEditor panel
 *      corresponding to a 'block'. LayoutBlock is a LayoutEditor specific extension
 *		of the JMRI Block object.
 * <P>
 * LayoutBlocks may have an occupancy Sensor-> The getOccupancy method returns
 *		the occupancy state of the LayoutBlock - OCCUPIED, EMPTY, or UNKNOWN.
 *		If no occupancy sensor is provided, UNKNOWN is returned. The occupancy sensor
 *      if there is one, is the same as the occupancy sensor of the corresponding
 *      JMRI Block.
 * <P>
 * The name of each Layout Block is the same as that of the corresponding block as
 *		defined in Layout Editor . A corresponding JMRI Block object is created when a
 *		LayoutBlock is created. The JMRI Block uses the name of the block defined in
 *      Layout Editor as its user name and a unique IBnnn system name. The JMRI Block
 *		object and its associated Path objects are useful in tracking a train around
 *      the layout. Blocks may be viewed in the Block Table.
 * <P>
 * A LayoutBlock may have an associated Memory object. This Memory object contains a
 *		string representing the current "value" of the corresponding JMRI Block object.
 *		If the value contains a train name, for example, displaying Memory objects
 *		associated with LayoutBlocks, and displayed near each Layout Block can
 *		follow a train around the layout, displaying its name when it is in the
 *.		LayoutBlock.
 * <P>
 * LayoutBlocks are "cross-panel", similar to sensors and turnouts.  A LayoutBlock
 *		may be used by more than one Layout Editor panel simultaneously.  As a consequence,
 *		LayoutBlocks are saved with the configuration, not with a panel.
 * <P>
 * LayoutBlocks are used by TrackSegments, LevelXings, and LayoutTurnouts.
 *		LevelXings carry two LayoutBlock designations, which may be the same.
 *      LayoutTurnouts carry LayoutBlock designations also, one per turnout,
 *			except for double crossovers which can have up to four->
 * <P>
 * LayoutBlocks carry a use count.  The use count counts the number of track
 *		segments, layout turnouts, and levelcrossings which use the LayoutBlock.
 *		Only LayoutBlocks which have a use count greater than zero are saved when
 *		the configuration is saved.
 * <P>
 * @author Dave Duchamp Copyright (c) 2004-2008
 * @version $Revision: 22638 $
 */

///*public*/ class LayoutBlock extends AbstractNamedBean implements java.beans.PropertyChangeListener
//{


/*public*/ void LayoutBlock::enableDeleteRouteLog() { enableDeleteRouteLogging = false; }
/*public*/ void LayoutBlock::disableDeleteRouteLog() { enableDeleteRouteLogging = false; }

    // Defined text resource
    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor->LayoutEditorBundle");



/*
 * Creates a LayoutBlock object.
 *
 * Note: initializeLayoutBlock() must be called to complete the process. They are split
 *       so  that loading of panel files will be independent of whether LayoutBlocks or
 *		 Blocks are loaded first.
 */
/*public*/ LayoutBlock::LayoutBlock(QString sName, QString uName,QObject* parent)
 : AbstractNamedBean(sName.toUpper(), uName, parent)
{
 //super (sName.toUpperCase(),uName);
 log = new Logger("LayoutBlock");
 // variables for Edit Layout Block pane
 editLayoutBlockFrame = NULL;
 sensorNameField = new /*JTextField*/ QLineEdit();
 sensorNameField->setMaxLength(16);
 sensorDebounceInactiveField = new /*JTextField*/ QLineEdit();
 sensorDebounceInactiveField->setMaxLength(5);
 sensorDebounceActiveField = new /*JTextField*/ QLineEdit();
 sensorDebounceActiveField->setMaxLength(5);
 sensorDebounceGlobalCheck = new /*JCheckBox*/ QCheckBox();
 sensorDebounceGlobalCheck->setText(tr("Use Global Debounce Values"));
 memoryComboBox = new NamedBeanComboBox(
             (MemoryManager*)InstanceManager::getDefault("MemoryManager"), nullptr, DisplayOptions::DISPLAYNAME);
 memoryNameField = new /*JTextField*/ QLineEdit();
 memoryNameField->setMaxLength(16);
 metricField = new /*JTextField*/ QLineEdit();
 metricField->setMaxLength(10);
 senseBox = new /*JComboBox*/ QComboBox();
 permissiveCheck = new /*JCheckBox*/ QCheckBox();
 permissiveCheck->setText(tr("Permissive Working Allowed"));
 trackColorBox = new /*JComboBox*/ QComboBox();
 occupiedColorBox = new /*JComboBox*/ QComboBox();
 extraColorBox = new /*JComboBox*/ QComboBox();
 blockSpeedBox = new /*JComboBox*/ QComboBox();
 blockUseLabel= new /*JLabel*/ QLabel();
 blockUseLabel->setText( tr("UseCount"));
// blockEditDone;
// blockEditCancel;
 editOpen = false;
 attachedBlocks = new /*JComboBox*/ QComboBox();
 pathActive = false;
 working <<"Bi-Directional"<< "Receive Only"<< "Send Only";
 active = true;
 defaultMetric = true;
 metric = 100;
 time = 0;
 occupancyNamedSensor = NULL;
 memory = NULL;
 block = NULL;
        ///*private*/ int maxBlockNumber = 0;
 panels = new QVector<LayoutEditor*>();  // panels using this block
 mBlockListener = NULL;
 jmriblknum = 1;
 useExtraColor = false;
 suppressNameUpdate = false;
 actedUponUpdates = new QVector<int>();
 auxTool=NULL;
 ConnectivityUtil* connection=NULL;
 layoutConnectivity = true;

 neighbours = new QVector<Adjacencies*>();

 throughPaths = new QVector<ThroughPaths*>();
 // A sub class that holds valid routes through the block->
 //Possibly want to store the path direction in here as well.
 // or we store the ref to the path, so we can get the directions.
 routes = new QVector<Routes*>();
 listeners = new QVector<PropertyChangeListener*>();

 pcs = new PropertyChangeSupport(this);

 blockName = uName;
 lbSystemName = sName;
 enableAddRouteLogging = false;
 enableUpdateRouteLogging = false;
 enableDeleteRouteLogging = false;
 enableSearchRouteLogging = false;
 occupiedSense = Sensor::ACTIVE;
 blockTrackColor = QColor(Qt::black);
 blockOccupiedColor = QColor(Qt::black);
 blockExtraColor = QColor(Qt::black);
#if 0
 colorText = QStringList()  << tr("Black") << tr("DarkGray") << tr("Gray") << tr( "LightGray") << tr("White") << tr("Red") << tr("Pink") << tr("Orange") << tr("Yellow") << tr("Green") << tr("Blue") << tr("Magenta") << tr("Cyan");
 colorCode = QList<QColor>() <<QColor(Qt::black) << QColor(Qt::darkGray) << QColor(Qt::gray) <<
            QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red) << QColor(255,233,236) << QColor(255,170,0) <<
            QColor(Qt::yellow) << QColor(Qt::green) << QColor(Qt::blue) << QColor(Qt::magenta) << QColor(Qt::cyan);
 numColors = 13;  // number of entries in the above arrays
#endif
}
/*
 * Completes the creation of a LayoutBlock object by adding a Block to it
 */
/*protected*/ void  LayoutBlock::initializeLayoutBlock()
{
 //get/create a Block object corresponding to this LayoutBlock
 block = nullptr;   // assume failure (pessimist!)
 QString userName = getUserName();
 if (!(userName.isNull()) && !userName.isEmpty()) {
     block =(Block*) ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getByUserName(userName);
 }

 if (block == nullptr) {
     // Not found, create a new Block
     BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
     QString s;
     while (true) {
         if (jmriblknum > 50000) {
             throw IndexOutOfBoundsException("Run away prevented while trying to create a block");
         }
         s = "IB" + QString::number(jmriblknum);
         jmriblknum++;

         // Find an unused system name
         block = (Block*)bm->getBySystemName(s);
         if (block != nullptr) {
             log->debug(tr("System name is already used: %1").arg(s));
             continue;
         }

         // Create a new block.  User name is null to prevent user name checking.
         block = bm->createNewBlock(s, QString());
         if (block == nullptr) {
             log->debug(tr("Null block returned: %1").arg(s));
             continue;
         }

         // Verify registration
         if (bm->getSystemNameList().contains(s)) {
             log->debug(tr("Block is valid: %1").arg(s));
             break;
         }
         log->debug(tr("Registration failed: %1").arg(s));
     }
     block->setUserName(getUserName());
 }

 //attach a listener for changes in the Block
// mBlockListener = (PropertyChangeEvent e) -> {
//     handleBlockChange(e);
// };
 HandleBlockChangeListener* mBlockListener = new HandleBlockChangeListener(this);
 block->addPropertyChangeListener(mBlockListener,
         getUserName(), "Layout Block:" + getUserName());
 if (occupancyNamedSensor != nullptr) {
     block->setNamedSensor(occupancyNamedSensor);
 }
}

/*protected*/ void  LayoutBlock::initializeLayoutBlockRouting()
{
 if(!((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
  return;
 setBlockMetric();

 for (int i = 0; i<block->getPaths()->size(); i++)
 {
  addAdjacency(block->getPaths()->at(i));
 }
}

/*
 * Accessor methods
 */
// TODO: deprecate and just use getUserName() directly
/*public*/ QString LayoutBlock::getId() {
    return getUserName();
}

/*public*/ QColor LayoutBlock::getBlockTrackColor() {
    return blockTrackColor;
}

/*public*/ void LayoutBlock::setBlockTrackColor(QColor color) {
    blockTrackColor = color;
    JmriColorChooser::addRecentColor(color);
}

/*public*/ QColor LayoutBlock::getBlockOccupiedColor() {
    return blockOccupiedColor;
}

/*public*/ void LayoutBlock::setBlockOccupiedColor(QColor color) {
    blockOccupiedColor = color;
    JmriColorChooser::addRecentColor(color);
}

/*public*/ QColor LayoutBlock::getBlockExtraColor() {
    return blockExtraColor;
}

/*public*/ void LayoutBlock::setBlockExtraColor(QColor color) {
    blockExtraColor = color;
    JmriColorChooser::addRecentColor(color);
}

//TODO: @Deprecated // Java standard pattern for boolean getters is "UseExtraColor()"
/*public*/ bool LayoutBlock::getUseExtraColor() {
    return useExtraColor;
}

/*public*/ void LayoutBlock::setUseExtraColor(bool b) {
    useExtraColor = b;

    if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()) {
        stateUpdate();
    }
    if (getBlock() != nullptr) {
        getBlock()->setAllocated(b);
    }
}

/* setUseExtraColor */
/*public*/ void LayoutBlock::incrementUse() {
    useCount++;
}

/*public*/ void LayoutBlock::decrementUse() {
    --useCount;
    if (useCount <= 0) {
        useCount = 0;
    }
}

/*public*/ int LayoutBlock::getUseCount() {
    return useCount;
}

/**
 *  Keeps track of LayoutEditor panels that are using this LayoutBlock
 */
/*public*/ void  LayoutBlock::addLayoutEditor(LayoutEditor* panel)
{
 // add to the panels list if not already there
 if (panels->size() > 0)
 {
  for (int i=0;i<panels->size();i++)
  {
   LayoutEditor* ed = panels->at(i);
   // simply return if already in list
   if (ed == panel) return;
  }
 }
 // not found, add it
 panels->append(panel);
}

/*public*/ void  LayoutBlock::deleteLayoutEditor(LayoutEditor* panel)
{
 // remove from the panels list if there
 if (panels->size()>0)
 {
  for (int i=0;i<panels->size();i++)
  {
   LayoutEditor* ed = panels->at(i);
   if (ed == panel)
   {
    panels->remove(i);
    return;
   }
  }
 }
}
/*public*/ bool  LayoutBlock::isOnPanel(LayoutEditor* panel)
{
    // returns true if this Layout Block is used on panel
 if (panels->size()>0)
 {
  for (int i=0;i<panels->size();i++)
  {
   LayoutEditor* ed = panels->at(i);
   if (ed == panel)
   {
    return true;
   }
  }
 }
 return false;
}

/**
 *  Redraws panels using this layout block
 */
/*public*/ void  LayoutBlock::redrawLayoutBlockPanels()
{
 if (panels->size()>0)
 {
  for (int i=0;i<panels->size();i++)
  {
   panels->at(i)->redrawPanel();
  }
  //panels->at(0)->redrawPanel();
 }

}

/**
 * Validates that the supplied occupancy sensor name corresponds to an existing sensor
 *   and is unique among all blocks.  If valid, returns the sensor and sets the block
 *   sensor name in the block->  Else returns NULL, and does nothing to the block->
 * This method also converts the sensor name to upper case if it is a system name.
 */
/*public*/ Sensor*  LayoutBlock::validateSensor(QString sensorName, /*Component*/ QWidget* openFrame)
{
 // check if anything entered
 if (sensorName.length()<1)
 {
  // no sensor entered
  return NULL;
 }
 // get the sensor corresponding to this name
 Sensor* s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sensorName);
 if (s==NULL)
 {
     // There is no sensor corresponding to this name
        JOptionPane::showMessageDialog(openFrame,
                tr("There is no sensor corresponding to this name'%1'").arg(sensorName),
                tr("Error"),JOptionPane::ERROR_MESSAGE);
  return NULL;
 }
 if ( sensorName!=(s->getUserName()) )
 {
  sensorName = sensorName.toUpper();
 }
 // ensure that this sensor is unique among defined Layout Blocks
 NamedBeanHandle<Sensor*>* savedNamedSensor = occupancyNamedSensor;
 occupancyNamedSensor = NULL;
//    LayoutBlock* b = InstanceManager::layoutBlockManagerInstance().
//                                        getBlockWithSensorAssigned(s);
 LayoutBlock* b = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getBlockWithSensorAssigned(s);
 if (b!=NULL)
 {
  // new sensor is not unique, return to the old one
  occupancyNamedSensor = savedNamedSensor;
        JOptionPane::showMessageDialog(openFrame,
                tr("New sensor is not unique, return to the old one '%1'").arg(sensorName),
                tr("Error"),JOptionPane::ERROR_MESSAGE);

  return NULL;
 }
 // sensor is unique
 setOccupancySensorName(sensorName);
 return s;
}

/**
 * Validates that the memory name corresponds to an existing memory.
 *   If valid, returns the memory. Else returns NULL, and notifies the user->
 * This method also converts the memory name to upper case if it is a system name.
 */
/*public*/ Memory*  LayoutBlock::validateMemory(QString memName, /*Component*/ QWidget* openFrame)
{
 // check if anything entered
 if (memName.length()<1)
 {
  // no memory entered
  return NULL;
 }
 // get the memory corresponding to this name
 Memory* m = InstanceManager::memoryManagerInstance()->getMemory(memName);
 if (m==NULL)
 {
        // There is no memory corresponding to this name
//        JOptionPane.showMessageDialog(openFrame,
//                java.text.MessageFormat.format(tr("Error16"),
//                new Object[]{memName}),
//                tr("Error"),JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(panels->at(0), tr("Error"), tr("There is no memory corresponding to this name"));
  return NULL;
 }
 if ( !(memName==(m->getUserName())) )
 {
  memName = memName.toUpper();
 }
 memoryName = memName;
 //Go through the memory icons on the panel and see if any are linked to this layout block
 if (m!=getMemory() && panels->size()>0)
 {
  if (panels->size()>0)
  {
   bool updateall = false;
   bool found = false;
   foreach(LayoutEditor* panel, *panels)
   {
    foreach(LEMemoryIcon* memIcon, *panel->memoryLabelList)
    {
     if(memIcon->getLayoutBlock()==this)
     {
      if(!updateall && !found)
      {
//       int n = JOptionPane.showConfirmDialog(
//                openFrame,
//                "Would you like to update all memory icons on the panel linked to the block to use the new one?",
//                "Update Memory Icons",
//                JOptionPane.YES_NO_OPTION);
          int n = QMessageBox::information(openFrame, tr("Update Memory Icons"),tr("Would you like to update all memory icons on the panel linked to the block to use the new one?"),QMessageBox::Yes | QMessageBox::No);
       found = true;
       if(n==QMessageBox::Yes)
       {
        updateall=true;
       }
      }
      if(updateall)
      {
       memIcon->setMemory(memoryName);
      }
     }
    }
   }
  }
 }
 return m;
}

/**
 * Returns the color for drawing items in this block->  Returns color
 *   based on block occupancy.
 */
/*public*/ QColor  LayoutBlock::getBlockColor()
{
 if (getOccupancy() == OCCUPIED)
 {
  return blockOccupiedColor;
 }
 else
 if (useExtraColor)
 {
  return blockExtraColor;
 }
 else
 {
  return blockTrackColor;
 }
}

/**
 * Get the jmri.Block corresponding to this LayoutBlock
 */
///*public*/ Block getBlock() {return block;}

/**
 * Add Memory by name
 */
/*public*/ void  LayoutBlock::setMemoryName(QString name) {
    memoryName = name;
    memory = InstanceManager::memoryManagerInstance()->
                        getMemory(name);
}

/*public*/ void LayoutBlock::setMemory(Memory* m, QString name) {
    if (m == nullptr) {
        namedMemory = nullptr;
        memoryName = name.isEmpty() ? "" : name;
        return;
    }
    namedMemory = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, m);
}

/**
 * Returns occupancy Sensor name
*/
/*public*/ QString  LayoutBlock::getOccupancySensorName()
{
 if(occupancyNamedSensor!=NULL)
 {
  return occupancyNamedSensor->getName();
 }
 return occupancySensorName;
}

/**
 * Returns occupancy Sensor
*/
/*public*/ Sensor*  LayoutBlock::getOccupancySensor() {
 if (occupancyNamedSensor == nullptr) {
     if (block != nullptr) {
         occupancyNamedSensor = block->getNamedSensor();
     }
 }
 if (occupancyNamedSensor != nullptr) {
     return (Sensor*)occupancyNamedSensor->getBean();
 }
 return nullptr;
}

/**
 * Add occupancy sensor by name
 */
/*public*/ void  LayoutBlock::setOccupancySensorName(QString name)
{
 if ((name.isNull()) || name.isEmpty()) {
       if (occupancyNamedSensor != nullptr) {
           occupancyNamedSensor->getBean()->removePropertyChangeListener(mBlockListener);
       }
       occupancyNamedSensor = nullptr;
       occupancySensorName = "";

       if (block != nullptr) {
           block->setNamedSensor(nullptr);
       }
       return;
   }
   occupancySensorName = name;
   Sensor* sensor = InstanceManager::sensorManagerInstance()->getSensor(name);
   if (sensor != nullptr) {
       occupancyNamedSensor = ((NamedBeanHandleManager*)InstanceManager::getDefault(
               "NamedBeanHandleManager"))->getNamedBeanHandle(name, sensor);
       if (block != nullptr) {
           block->setNamedSensor(occupancyNamedSensor);
       }
   }
}

/**
 * Get/Set occupied sense
 */
/*public*/ int  LayoutBlock::getOccupiedSense() {return occupiedSense;}
/*public*/ void  LayoutBlock::setOccupiedSense(int sense)
{
 occupiedSense = sense;
}

/**
 * Test block occupancy
 */
/*public*/ int  LayoutBlock::getOccupancy()
{
 if(occupancyNamedSensor == NULL)
 {
  Sensor* s = nullptr;
  if (!occupancySensorName.isEmpty()) {
      s = InstanceManager::sensorManagerInstance()->getSensor(occupancySensorName);
  }
  if (s == NULL)
  {
   //no occupancy sensor, so base upon block occupancy state
   if (block != nullptr) {
       return block->getState();
   }
   //if no block or sensor return unknown
   return UNKNOWN;
  }
  qDebug() << QString("SensorObjectName %1").arg(s->objectName());
  occupancyNamedSensor =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(occupancySensorName, s);
  if (block!=NULL)
   block->setNamedSensor(occupancyNamedSensor);
 }

 if (getOccupancySensor() == nullptr) {
     return UNKNOWN;
 }

 if (getOccupancySensor()->getKnownState() != occupiedSense)
 {
  return (EMPTY);
 }
 else if (getOccupancySensor()->getKnownState() == occupiedSense)
 {
  return (OCCUPIED);
 }
 return (UNKNOWN);
}

/*public*/ int LayoutBlock::getState() {return getOccupancy();}

// dummy for completion of NamedBean interface
/*public*/ void LayoutBlock::setState(int i) { log->error(QString("this state does nothing %1 for ").arg(i) + getDisplayName());}

/**
 * Get the Layout Editor panel with the highest connectivity to this Layout Block
 */
/*public*/ LayoutEditor*  LayoutBlock::getMaxConnectedPanel()
{
 LayoutEditor* panel = NULL;
 if ( (block!=NULL) && (panels->size() > 0) )
 {
  // a block is attached and this LayoutBlock is used
  // initialize connectivity as defined in first Layout Editor panel
  panel = panels->at(0);
  QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(this);
  // if more than one panel, find panel with the highest connectivity
  if (panels->size()>1)
  {
   for (int i = 1;i < panels->size();i++)
   {
    if (c->size()<panels->at(i)->auxTools->
                                    getConnectivityList(this)->size())
    {
     panel = panels->at(i);
     c = panel->auxTools->getConnectivityList(this);
    }
   }
  }
 }
 return panel;
}

/**
 * Check/Update Path objects for the attached jmri.Block
 * <P>
 * If multiple panels are present, Paths are set according to the panel with
 *		the highest connectivity (most LayoutConnectivity objects);
 */
/*public*/ void LayoutBlock::updatePaths()
{
//Update paths is called by the panel, turnouts, xings, track segments etc
 if ( (block!=NULL) && (panels->size() > 0) )
 {
  // a block is attached and this LayoutBlock is used
  // initialize connectivity as defined in first Layout Editor panel
  LayoutEditor* panel = panels->at(0);
  QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(this);

  // if more than one panel, find panel with the highest connectivity
  if (panels->size()>1)
  {
   for (int i = 1;i < panels->size();i++)
   {
    if (c->size()<panels->at(i)->auxTools->
                                    getConnectivityList(this)->size())
    {
     panel = panels->at(i);
     c = panel->auxTools->getConnectivityList(this);
    }
   }
   // check that this connectivity is compatible with that of other panels.
   for (int j = 0;j < panels->size();j++)
   {
    LayoutEditor* tPanel = panels->at(j);
    if ( (tPanel!=panel) && ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->
                            warn() && ( !compareConnectivity(c,
                                    tPanel->auxTools->getConnectivityList(this)) )  )
    {
     // send user an error message
//     int response = JOptionPane.showOptionDialog(NULL,
//                            java.text.MessageFormat.format(tr("Warn1"),
//                            new Object[]{blockName,tPanel.getLayoutName(),
//                            panel.getLayoutName()}),tr("WarningTitle"),
//                            JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE,
//                            NULL,new Object[] {tr("ButtonOK"),
//                            tr("ButtonOKPlus")},tr("ButtonOK"));
    int response = QMessageBox::warning(NULL, tr("Warning"), tr("Warning - Connectivities for block \"%1\" in panels \"%2\" and \"%3\" are not compatible.").arg(blockName).arg(tPanel->getLayoutName()).arg(panel->getLayoutName()),QMessageBox::Yes | QMessageBox::No);
    if (response!=0)
      // user elected to disable messages
     ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->turnOffWarning();
    }
   }
  }
  // update block Paths to reflect connectivity as needed
  updateBlockPaths(c,panel);
 }
}

/**
 * Check/Update Path objects for the attached jmri.Block using the
 *		connectivity in the specified Layout Editor panel.
 */
//@SuppressWarnings("NULL")
/*public*/ void  LayoutBlock::updatePathsUsingPanel(LayoutEditor* panel)
{
 if (panel==NULL)
 {
  log->error("Null panel in call to updatePathsUsingPanel");
 }
 QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(this);
 updateBlockPaths(c, panel);
}

/*private*/ void  LayoutBlock::updateBlockPaths(QVector<LayoutConnectivity*>* c, LayoutEditor* panel)
{
 if(enableAddRouteLogging)
  log->info("From " + this->getDisplayName() + " updatePaths Called");
 LayoutEditorAuxTools* auxTools = new LayoutEditorAuxTools(panel);
 QVector<Path*>* paths = block->getPaths();
 QVector<bool> used =  QVector<bool>(c->size(),false);
 QVector<int> need = QVector<int>(paths->size(),-1);
// for (int j=0;j<c->size();j++) {used[j] = false;}
// for (int j=0;j<paths->size();j++) {need[j] = -1;}
 // cycle over existing Paths, checking against LayoutConnectivity
 for (int i = 0;i<paths->size();i++)
 {
  Path* p = paths->at(i);
  // cycle over LayoutConnectivity matching to this Path
  for (int j = 0;((j<c->size())&&(need[i]==-1));j++)
  {
   if (!used[j])
   {
    // this LayoutConnectivity not used yet
    LayoutConnectivity* lc = c->at(j);
    if ( (lc->getBlock1()->getBlock()==p->getBlock()) ||
                (lc->getBlock2()->getBlock()==p->getBlock()) )
    {
     // blocks match - record
     //used[j] = true;
     used.replace(j,true);
     //need[i] = j;
     need.replace(i,j);
    }
   }
  }
 }
 // update needed Paths
 for (int i = 0;i<paths->size();i++)
 {
  if (need[i]>=0)
  {
   Path* p = paths->at(i);
   LayoutConnectivity* lc = c->at(need[i]);
   if (lc->getBlock1()==this)
   {
    p->setToBlockDirection(lc->getDirection());
    p->setFromBlockDirection(lc->getReverseDirection());
   }
   else
   {
    p->setToBlockDirection(lc->getReverseDirection());
    p->setFromBlockDirection(lc->getDirection());
   }
   QList<BeanSetting*> beans = p->getSettings();
   for (int j=0;j<beans.size();j++)
   {
    p->removeSetting(beans.at(j));
   }
   auxTools->addBeanSettings(p,lc,this);
  }
 }
 // delete unneeded Paths
 for (int i = 0;i<paths->size();i++)
 {
  if (need[i]<0)
  {
   block->removePath(paths->at(i));
   if(((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
    removeAdjacency(paths->at(i));
  }
 }
 // add Paths as required
 for (int j = 0; j < c->size(); j++)
 {
  if (!used[j])
  {
   // there is no corresponding Path, add one.
   LayoutConnectivity* lc = c->at(j);
   Path* newp = NULL;
//				LayoutBlock tmpblock;
   if (lc->getBlock1()==this)
   {
    newp = new Path(lc->getBlock2()->getBlock(),lc->getDirection(),
                                lc->getReverseDirection());
//					tmpblock = lc->getBlock2();
   }
   else
   {
    newp = new Path(lc->getBlock1()->getBlock(),lc->getReverseDirection(),
                                lc->getDirection());
//					tmpblock = lc->getBlock1();

   }
   block->addPath(newp);
   if(enableAddRouteLogging)
    log->info("From " + this->getDisplayName() + " updateBlock Paths");
   if(((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
    addAdjacency(newp);
   //else log->error("Trouble adding Path to block '"+blockName+"'.");
   auxTools->addBeanSettings(newp,lc,this);
  }
 }

// djd debugging - lists results of automatic initialization of Paths and BeanSettings
 if (log->isDebugEnabled()) {
     //block->getPaths().stream().forEach((p) ->
  foreach(Path*p, *block->getPaths())
  {
      log->debug(tr("From %1 to %2").arg(getDisplayName()).arg(p->toString()));
  }//);
 }
}

/*private*/ bool  LayoutBlock::compareConnectivity(QVector<LayoutConnectivity*>* main, QVector<LayoutConnectivity*>* test)
{
 bool result = false;     //assume failure (pessimsit!)
 if (!main->isEmpty() && !test->isEmpty())
 {
     result = true;          //assume success (optimist!)
     //loop over connectivities in test list
  for (LayoutConnectivity* tc : *test) {
      LayoutBlock* tlb1 = tc->getBlock1(), *tlb2 = tc->getBlock2();
      //loop over main list to make sure the same blocks are connected
      bool found = false;  //assume failure (pessimsit!)
      for (LayoutConnectivity* mc : *main) {
          LayoutBlock* mlb1 = mc->getBlock1(), *mlb2 = mc->getBlock2();
          if (((tlb1 == mlb1) && (tlb2 == mlb2))
                  || ((tlb1 == mlb2) && (tlb2 == mlb1))) {
              found = true;   //success!
              break;
          }
      }
      if (!found) {
          result = false;
          break;
      }
  }
 } else if (main->isEmpty() && test->isEmpty())
 {
  result = true;          // OK if both have no neighbors, common for turntable rays
 }
 return result;

}

/**
 * Handle tasks when block changes
 */
void  LayoutBlock::handleBlockChange(PropertyChangeEvent* e)
{
 // Update memory object if there is one
 if ( (memory==NULL) && (memoryName!="") )
 {
  // initialize if needed
  memory = InstanceManager::memoryManagerInstance()->
                        getMemory(memoryName);
 }
 if ( (memory!=NULL) && (block!=NULL) && !suppressNameUpdate )
 {
  // copy block value to memory if there is a value
  QVariant val = block->getValue();
  if (!val.isNull())
  {
   //if(!(val instanceof RosterEntry)){
   //RosterEntry* re = VPtr<Roster>::asPtr(val);
   //if(qobject_cast<RosterEntry*>(val)== NULL)
   {
    //val = val->toString();

   }
  }
  memory->setValue(val);
 }
 if(e->getPropertyName() == "state")
 {
  qDebug() << tr("Occupied state = %1, new state = %2").arg(getOccupancy()).arg(e->getNewValue().toInt());
  setState(e->getNewValue().toInt());
 }
 // Redraw all Layout Editor panels using this Layout Block
 redrawLayoutBlockPanels();

//    if(InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled()){
 if(((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
 {
  stateUpdate();
 }
}

void LayoutBlock::handleBlockChange(QString /*pName*/, int /*o*/, int /*val*/)
{
 // Update memory object if there is one
 if ( (memory==NULL) && (memoryName!="") )
 {
  // initialize if needed
  memory = InstanceManager::memoryManagerInstance()->                        getMemory(memoryName);
 }
 if ( (memory!=NULL) && (block!=NULL) && !suppressNameUpdate )
 {
  // copy block value to memory if there is a value
  QVariant val = block->getValue();
  if (val!=QVariant())
  {
   //if(!(val instanceof RosterEntry))
   if(VPtr<RosterEntry>::asPtr(val))
   {
    if(qobject_cast<RosterEntry*>(VPtr<RosterEntry>::asPtr(val))== NULL)
    {
     val = val.toString();
    }
   }
  }
  memory->setValue(val);
 }
 // Redraw all Layout Editor panels using this Layout Block
 redrawLayoutBlockPanels();

//    if(InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled()){
 if(((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
 {
  stateUpdate();
 }
}

/**
 * Deactivate block listener for redraw of panels and update of memories on
 *	change of state
 */
/*private*/ void  LayoutBlock::deactivateBlock() {
    if ( (mBlockListener!=NULL) && (block!=NULL) ) {
        block->removePropertyChangeListener(mBlockListener);
    }
    mBlockListener = NULL;
}

/**
 * Sets/resets update of memory name when block goes from occupied to unoccupied or vice versa.
 * If set is true, name update is suppressed.
 * If set is false, name update works normally.
 */
/*public*/ void  LayoutBlock::setSuppressNameUpdate(bool set) {suppressNameUpdate = set;}

/**
 * Edit a Layout Block
 */
/*protected*/ void  LayoutBlock::editLayoutBlock(/*Component*/ QWidget* /*callingPane*/)
{
#if 1
 if (editOpen)
 {
  editLayoutBlockFrame->setVisible(true);
  return;
 }
#if 0
 // Initialize if needed
 if (editLayoutBlockFrame == NULL)
 {
  editLayoutBlockFrame = new JmriJFrameX( tr("Create/Edit Block"), false, false);
  editLayoutBlockFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutBlock", true);
//  editLayoutBlockFrame->setLocation(80,40);
//  QWidget* contentPane = editLayoutBlockFrame->getContentPane();
//  contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
  QWidget* contentPane = new QWidget;
  editLayoutBlockFrame->setCentralWidget(contentPane);
  QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
  // show block ID (not changeable)
  QWidget* panel1 = new QWidget();
  panel1->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* blockNameLabel = new /*JLabel*/ QLabel( tr("Name")+": "+blockName );
  panel1->layout()->addWidget(blockNameLabel);
  contentPaneLayout->addWidget(panel1);
  // show current use count (not editable)
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new FlowLayout());
  panel2->layout()->addWidget(blockUseLabel);
  contentPaneLayout->addWidget(panel2);
  // set up occupancy sensor (changeable)
  contentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel3 = new QWidget();
  panel3->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* sensorLabel = new /*JLabel*/ QLabel( tr("Occupancy Sensor")+":");
  panel3->layout()->addWidget(sensorLabel);
  panel3->layout()->addWidget(sensorNameField);
  sensorNameField->setToolTip( tr("Enter name of occupancy sensor for this block; no entry means don't change.") );
  contentPaneLayout->addWidget(panel3);

  // set up occupied sense (changeable)
  QWidget* panel4 = new QWidget();
  panel4->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* sensorSenseLabel = new /*JLabel*/ QLabel( tr("Occupied Sense")+":");
  panel4->layout()->addWidget(sensorSenseLabel);
  senseBox->clear();
  senseBox->addItem( tr("Active") );
  senseActiveIndex = 0;
  senseBox->addItem( tr("Inactive") );
  senseInactiveIndex = 1;
  panel4->layout()->addWidget(senseBox);
  senseBox->setToolTip( tr("Select the occupancy sensor state when the block is occupied.") );
  contentPaneLayout->addWidget(panel4);

  contentPaneLayout->addWidget(sensorDebounceGlobalCheck);
  sensorDebounceGlobalCheck->setToolTip(tr("Use Global Debounce Values"));
  QWidget* panel4a = new QWidget();
  QHBoxLayout* panel4aLayout= new QHBoxLayout(panel4a);
  panel4aLayout->addWidget(new /*JLabel*/ QLabel(tr("Sensor InActive Debounce")));
  sensorDebounceInactiveField->setToolTip(tr("Enter in the duration (milli seconds) which the sensor has to be InActive, before the change is acted upon."));
  panel4aLayout->addWidget(sensorDebounceInactiveField);
  contentPaneLayout->addWidget(panel4a);
  QWidget* panel4b = new QWidget();
  QHBoxLayout* panel4bLayout= new QHBoxLayout(panel4b);
  panel4bLayout->addWidget(new /*JLabel*/ QLabel(tr("Sensor Active Debounce")));
  panel4bLayout->addWidget(sensorDebounceActiveField);
  sensorDebounceActiveField->setToolTip(tr("Enter in the duration (milli seconds) which the sensor has to be Active, before the change is acted upon."));
  contentPaneLayout->addWidget(panel4b);

  // set up track color (changeable)
  contentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel6 = new QWidget();
  panel6->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* trackColorLabel = new /*JLabel*/ QLabel( tr("Track Color:") );
  panel6->layout()->addWidget(trackColorLabel);
  initializeColorCombo(trackColorBox, blockTrackColor);
  panel6->layout()->addWidget(trackColorBox);
  trackColorBox->setToolTip( tr("Select the track color when this block is unoccupied.") );
  contentPaneLayout->addWidget(panel6);
  // set up occupied color (changeable)
  QWidget* panel7 = new QWidget();
  panel7->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* occupiedColorLabel = new /*JLabel*/ QLabel( tr("Occupied Track Color:") );
  panel7->layout()->addWidget(occupiedColorLabel);
  initializeColorCombo(occupiedColorBox, blockOccupiedColor);
  panel7->layout()->addWidget(occupiedColorBox);
  occupiedColorBox->setToolTip( tr("Select the track color when this block is occupied.") );
  contentPaneLayout->addWidget(panel7);
  // set up extra color (changeable)
  QWidget* panel7a = new QWidget();
  panel7a->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* extraColorLabel = new /*JLabel*/ QLabel( tr("Alternate Track Color:") );
  panel7a->layout()->addWidget(extraColorLabel);
  initializeColorCombo(extraColorBox, blockExtraColor);
  panel7a->layout()->addWidget(extraColorBox);
  extraColorBox->setToolTip( tr("Select the track color for unoccupied special use, e.g. allocated.") );
  contentPaneLayout->addWidget(panel7a);
  // set up Memory entry (changeable)
  contentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
  QWidget* panel8 = new QWidget();
  panel8->setLayout(new FlowLayout());
  /*JLabel*/ QLabel* memoryLabel = new /*JLabel*/ QLabel( tr("Memory Variable")+":");
  panel8->layout()->addWidget(memoryLabel);
  panel8->layout()->addWidget(memoryNameField);
  memoryNameField->setToolTip( tr("Enter name (system or user) of Memory Variable (optional).") );
  contentPaneLayout->addWidget(panel8);

  //if(InstanceManager::layoutBlockManagerInstance()->isAdvancedRoutingEnabled())
  if(((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
  {
    contentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
    QWidget* panel19 = new QWidget();
    panel19->setLayout(new FlowLayout());
    /*JLabel*/ QLabel* metricLabel = new /*JLabel*/ QLabel("Block Metric");
    panel19->layout()->addWidget(metricLabel);
    panel19->layout()->addWidget(metricField);
    metricField->setToolTip("set the cost for going over this block");
    contentPaneLayout->addWidget(panel19);
    neighbourDir =  QVector<QComboBox*>(getNumberOfNeighbours());
    for(int i = 0; i<getNumberOfNeighbours(); i++)
    {
     QWidget* panel = new QWidget();
     panel->setLayout(new FlowLayout());
     panel->layout()->addWidget(new /*JLabel*/ QLabel("Attached Block: " + getNeighbourAtIndex(i)->getDisplayName()));
     QComboBox* dir = new QComboBox(/*working*/);
     dir->addItems(working);
     Block* blk = neighbours->at(i)->getBlock();
     if(block->isBlockDenied(blk))
      dir->setCurrentIndex(2);
     else if (blk->isBlockDenied(block))
      dir->setCurrentIndex(1);
     else
      dir->setCurrentIndex(0);
     panel->layout()->addWidget(dir);
     neighbourDir.append(dir);
     contentPaneLayout->addWidget(panel);
     }
    }
    contentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
    QWidget* panel20 = new QWidget();
    panel20->setLayout(new FlowLayout());
    panel20->layout()->addWidget(permissiveCheck);
    permissiveCheck->setToolTip("Is another train allowed to enter the block when it is already occupied");
    contentPaneLayout->addWidget(panel20);


    // set up Done and Cancel buttons
    contentPaneLayout->addWidget(new JSeparator(JSeparator::HORIZONTAL));
    QWidget* panel5 = new QWidget();
    panel5->setLayout(new FlowLayout());
    // Done
    panel5->layout()->addWidget(blockEditDone = new QPushButton(tr("Done")));
//        blockEditDone.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                blockEditDonePressed(e);
//            }
//        });
    connect(blockEditDone, SIGNAL(clicked()), this, SLOT(blockEditDonePressed()));
    blockEditDone->setToolTip( tr("Click Done to accept any changes made above and dismiss this dialog->") );
    // Cancel
    panel5->layout()->addWidget(blockEditCancel = new QPushButton(tr("Cancel")));
//        blockEditCancel.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                blockEditCancelPressed(e);
//            }
//        });
    connect(blockEditCancel, SIGNAL(clicked()), this, SLOT(blockEditCancelPressed()));
    blockEditCancel->setToolTip( tr("CancelHint") );
    contentPaneLayout->addWidget(panel5);


    }
    // Set up for Edit
    blockUseLabel->setText(tr("Current Use Count")+": "+QString::number(useCount) );
    sensorNameField->setText(getOccupancySensorName());
    if (occupiedSense==Sensor::ACTIVE)
    {
     senseBox->setCurrentIndex(senseActiveIndex);
    }
    else
    {
     senseBox->setCurrentIndex(senseInactiveIndex);
    }
    if(getOccupancySensor()!=NULL)
    {
     sensorDebounceGlobalCheck->setChecked(getOccupancySensor()->useDefaultTimerSettings());
     sensorDebounceInactiveField->setText(QString::number(getOccupancySensor()->getSensorDebounceGoingInActiveTimer()));
     sensorDebounceActiveField->setText(QString::number(getOccupancySensor()->getSensorDebounceGoingActiveTimer()));
     sensorDebounceGlobalCheck->setChecked(getOccupancySensor()->useDefaultTimerSettings());
    }
//    sensorDebounceGlobalCheck.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e){
//            if(sensorDebounceGlobalCheck.isSelected()){
//                sensorDebounceInactiveField.setEnabled(false);
//                sensorDebounceActiveField.setEnabled(false);
//                sensorDebounceActiveField.setText(QString::number(jmri.InstanceManager::sensorManagerInstance().getDefaultSensorDebounceGoingActive()));
//                sensorDebounceInactiveField.setText(QString::number(jmri.InstanceManager::sensorManagerInstance().getDefaultSensorDebounceGoingInActive()));
//            } else {
//                sensorDebounceInactiveField.setEnabled(true);
//                sensorDebounceActiveField.setEnabled(true);
//            }
//        }
//    });
 connect(sensorDebounceGlobalCheck, SIGNAL(clicked()), this, SLOT(sensorDebounceGlobalCheck_clicked()));
 setColorCombo(trackColorBox,blockTrackColor);
 setColorCombo(occupiedColorBox,blockOccupiedColor);
 setColorCombo(extraColorBox,blockExtraColor);
 memoryNameField->setText(memoryName);
 metricField->setText(QString::number(metric));

 if(block!=NULL)
  permissiveCheck->setChecked(block->getPermissiveWorking());
//    editLayoutBlockFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                blockEditCancelPressed(NULL);
//            }
//        });
 editLayoutBlockFrame->addWindowListener(new LBWindowListener(this));
 editLayoutBlockFrame->adjustSize();
 editLayoutBlockFrame->setVisible(true);
#else
 editLayoutBlockFrame = new CreateEditBlock(this->blockName, (LayoutEditor*)panels->value(0));
 editLayoutBlockFrame->show();
#endif
 editOpen = true;
#else
 LayoutBlockEditAction* beanEdit = new LayoutBlockEditAction(this);
 if (block == nullptr) {
     //Block may not have been initialised due to an error so manually set it in the edit window
     QString userName = getUserName();
     if ((!userName.isNull()) && !userName.isEmpty()) {
         Block* b = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(userName);
         if (b != nullptr) {
             beanEdit->setBean(b);
         }
     }
 } else {
     beanEdit->setBean(block);
 }
 beanEdit->actionPerformed();

#endif
}
#if 0
void LayoutBlock::sensorDebounceGlobalCheck_clicked()
{
 if(sensorDebounceGlobalCheck->isChecked())
 {
  sensorDebounceInactiveField->setEnabled(false);
  sensorDebounceActiveField->setEnabled(false);
  sensorDebounceActiveField->setText(QString::number(InstanceManager::sensorManagerInstance()->getDefaultSensorDebounceGoingActive()));
  sensorDebounceInactiveField->setText(QString::number(InstanceManager::sensorManagerInstance()->getDefaultSensorDebounceGoingInActive()));
 }
 else
 {
  sensorDebounceInactiveField->setEnabled(true);
  sensorDebounceActiveField->setEnabled(true);
 }
}


void LayoutBlock::blockEditDonePressed(ActionEvent* /*a*/)
{
 bool needsRedraw = false;
 // check if Sensor changed
 QString newName = NamedBean::normalizeUserName(sensorNameField->text());
 if ( (getOccupancySensorName())!=(newName) )
 {
  // sensor has changed
  if ((newName.isNull()) || newName.isEmpty())
  {
      setOccupancySensorName(newName);
      sensorNameField->setText("");
      needsRedraw = true;
  } else if (validateSensor(newName, editLayoutBlockFrame) == nullptr) {
      //invalid sensor entered
      occupancyNamedSensor = nullptr;
      occupancySensorName = "";
      sensorNameField->setText("");
      return;
  } else {
      sensorNameField->setText(newName);
      needsRedraw = true;
  }
 }
 if(getOccupancySensor()!=NULL)
 {
  if(sensorDebounceGlobalCheck->isChecked())
  {
   getOccupancySensor()->useDefaultTimerSettings(true);
  }
  else
  {
   getOccupancySensor()->useDefaultTimerSettings(false);
   if(sensorDebounceInactiveField->text().trimmed()!=(""))
    getOccupancySensor()->setSensorDebounceGoingInActiveTimer(sensorDebounceInactiveField->text().trimmed().toLong());
   if(sensorDebounceActiveField->text().trimmed()!=(""))
    getOccupancySensor()->setSensorDebounceGoingActiveTimer((sensorDebounceActiveField->text().trimmed().toLong()));
   }
   if(getOccupancySensor()->getReporter()!=NULL && block!=NULL)
   {
    QString msg = tr("Sensor %1 has reporter %2 associated with it, do you want to use the reporter with this block?").arg( getOccupancySensor()->getDisplayName()).arg(getOccupancySensor()->getReporter()->getDisplayName() );
//            if(JOptionPane.showConfirmDialog(editLayoutBlockFrame,
//                                                 msg,tr("BlockAssignReporterTitle"),
//                                                 JOptionPane.YES_NO_OPTION)==0)
    if(QMessageBox::question(editLayoutBlockFrame, tr("Assign Reporter to Block"),msg, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
     block->setReporter(getOccupancySensor()->getReporter());

   }
  }
  // check if occupied sense changed
  int k = senseBox->currentIndex();
  int oldSense = occupiedSense;
  if (k==senseActiveIndex) occupiedSense = Sensor::ACTIVE;
   else occupiedSense = Sensor::INACTIVE;
  if (oldSense!=occupiedSense)
   needsRedraw = true;

  // check if track color changed
  QColor oldColor = blockTrackColor;
  blockTrackColor = getSelectedColor(trackColorBox);
  if (oldColor!=blockTrackColor)
   needsRedraw = true;

  // check if occupied color changed
  oldColor = blockOccupiedColor;
  blockOccupiedColor = getSelectedColor(occupiedColorBox);
  if (oldColor!=blockOccupiedColor)
   needsRedraw = true;
  // check if extra color changed
  oldColor = blockExtraColor;
  blockExtraColor = getSelectedColor(extraColorBox);
  if (oldColor!=blockExtraColor)
   needsRedraw = true;

  // check if Memory changed
  if ( memoryName!=(memoryNameField->text().trimmed()) )
  {
   // memory has changed
    QString newName = memoryNameField->text().trimmed();
   if ((memory = validateMemory(newName,editLayoutBlockFrame))==NULL)
   {
    // invalid memory entered
    memoryName = "";
    memoryNameField->setText("");
    return;
   }
   else
   {
    memoryNameField->setText(memoryName);
    needsRedraw = true;
   }
  }
  int m = metricField->text().trimmed().toInt();
  if (m!=metric)
   setBlockMetric(m);
  block->setPermissiveWorking(permissiveCheck->isChecked());
  if(!neighbourDir.isEmpty())
  {
   for(int i = 0; i<neighbourDir.size(); i++)
   {
    int neigh = neighbourDir.at(i)->currentIndex();
    neighbours->at(i)->getBlock()->removeBlockDenyList(this->block);
    this->block->removeBlockDenyList(neighbours->at(i)->getBlock());
    switch(neigh)
    {
    case 0 : updateNeighbourPacketFlow(neighbours->at(i), RXTX);
             break;
    case 1 :
            neighbours->at(i)->getBlock()->addBlockDenyList(this->block->getDisplayName());
            updateNeighbourPacketFlow(neighbours->at(i), TXONLY);
            break;
    case 2 :
            this->block->addBlockDenyList(neighbours->at(i)->getBlock()->getDisplayName());
            updateNeighbourPacketFlow(neighbours->at(i), RXONLY);
            break;
     default: break;
    }
   }
  }
  // complete
  editOpen = false;
  editLayoutBlockFrame->setVisible(false);
  //editLayoutBlockFrame->dispose();
  editLayoutBlockFrame = NULL;
  if (needsRedraw)
   redrawLayoutBlockPanels();
}

void LayoutBlock::blockEditCancelPressed(ActionEvent* /*a*/) {
    editOpen = false;
    editLayoutBlockFrame->setVisible(false);
    //editLayoutBlockFrame->dispose();
    editLayoutBlockFrame = NULL;
}

/*private*/ void LayoutBlock::initializeColorCombo(QComboBox* colorCombo, QColor c) {
 colorCombo->clear();
 for (int i = 0;i<numColors;i++)
 {
  QColor desiredColor = colorCode.at(i);
  const QIcon* icon = getColourIcon(desiredColor);
  colorCombo->addItem(*icon, colorText[i] );
  if(desiredColor == c)
   colorCombo->setCurrentIndex(i);
 }
}

/*private*/ void LayoutBlock::setColorCombo(QComboBox* colorCombo, QColor color)
{
 for (int i = 0;i<numColors;i++)
 {
  if (color==colorCode[i])
  {
   colorCombo->setCurrentIndex(i);
   return;
  }
 }
}
/*private*/ QColor LayoutBlock::getSelectedColor(QComboBox* colorCombo) {
    return (colorCode.at(colorCombo->currentIndex()));
}
#endif
/**
 * Utility methods for converting between string and color
 * Note: These names are only used internally, so don't need a resource bundle
 */
/*public*/ /*static*/ QString LayoutBlock::colorToString(QColor color) {
    if(color == QColor(Qt::black)) return "black";
    else if (color == QColor(Qt::darkGray)) return "darkGray";
    else if (color == QColor(Qt::gray)) return "gray";
    else if (color == QColor(Qt::lightGray)) return "lightGray";
    else if (color == QColor(Qt::white)) return "white";
    else if (color == QColor(Qt::red)) return "red";
    else if (color == QColor(255,233,236)) return "pink";
    else if (color == QColor(255, 165, 0)) return "orange";
    else if (color == QColor(Qt::yellow)) return "yellow";
    else if (color == QColor(Qt::green)) return "green";
    else if (color == QColor(Qt::blue)) return "blue";
    else if (color == QColor(Qt::magenta)) return "magenta";
    else if (color == QColor(Qt::cyan)) return "cyan";
    //log->error ("unknown color sent to colorToQString");
    return "black";
}
/*public*/ /*static*/ QColor LayoutBlock::stringToColor(QString string) {
    if(string==("black")) return QColor(Qt::black);
    else if (string==("darkGray")) return QColor(Qt::darkGray);
    else if (string==("gray")) return QColor(Qt::gray);
    else if (string==("lightGray")) return QColor(Qt::lightGray);
    else if (string==("white")) return QColor(Qt::white);
    else if (string==("red")) return QColor(Qt::red);
    else if (string==("pink")) return QColor(255,192,203);
    else if (string==("orange")) return QColor(255,170,0);
    else if (string==("yellow")) return QColor(Qt::yellow);
    else if (string==("green")) return QColor(Qt::green);
    else if (string==("blue")) return QColor(Qt::blue);
    else if (string==("magenta")) return QColor(Qt::magenta);
    else if (string==("cyan")) return QColor(Qt::cyan);
    //log->error("unknown color text '"+string+"' sent to stringToColor");
    return QColor(Qt::black);
}

/**
 * Removes this object from display and persistance
 */
void LayoutBlock::remove() {
    // if an occupancy sensor has been activated, deactivate it
    deactivateBlock();
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool LayoutBlock::isActive() {
    return active;
}

/**
 *  The code below relates to the layout block routing protocol
 */

/**
* Used to set the block metric based upon the track segment that the block is
* associated with if the (200 if Side, 50 if Main).  If the block is assigned
* against multiple track segments all with different types then the highest
* type will be used.
* In theory no reason why it couldn't be a compromise!
*/
void LayoutBlock::setBlockMetric(){
    if (!defaultMetric)
        return;
    if(enableUpdateRouteLogging){
        log->info("From " + this->getDisplayName() + " default set block metric called");
    }
    LayoutEditor* panel = getMaxConnectedPanel();
    if (panel==NULL){
        if(enableUpdateRouteLogging)
            log->info("From " + this->getDisplayName() + " unable to set metric as we are not connected to a panel yet");
        return;
    }
    QList<TrackSegment*> ts = panel->getFinder()->findTrackSegmentByBlock(blockName);
    int mainline = 0;
    int side = 0;
    for (int i = 0; i< ts.size(); i++){
        if (ts.at(i)->isMainline())
            mainline++;
        else
            side++;
    }
    if(mainline>side)
        metric=50;
    else if (mainline<side)
        metric=200;
    else{
        //They must both be equal so will set as a mainline.
        metric=50;
    }
    if(enableUpdateRouteLogging){
        log->info("From " + this->getDisplayName() + " metric set to " + metric);
    }
//    //What we need to do hear, is resend out our routing packets with the new metric.
    RoutingPacket* update = new RoutingPacket(UPDATE, this->getBlock(), -1, metric, -1, -1, getNextPacketID());
    firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(update));
}


/*public*/ bool LayoutBlock::useDefaultMetric() { return defaultMetric; }
/*public*/ void LayoutBlock::useDefaultMetric(bool boo)
{
 if (boo==defaultMetric)
 {
  return;
 }
 defaultMetric = boo;
 if (boo)
 {
  setBlockMetric();
 }
}

/**
* Sets a metric cost against a block, this is used in the calculation of a
* path between two location on the layout, a lower path cost is always preferred
* For Layout blocks defined as Mainline the default metric is 50.
* For Layout blocks defined as a Siding the default metric is 200.
*/
/*public*/ void LayoutBlock::setBlockMetric(int m)
{
 if (metric==m)
     return;
 metric = m;
 defaultMetric = false;
 RoutingPacket* update = new RoutingPacket(UPDATE, this->getBlock(), -1, metric, -1, -1, getNextPacketID());
 firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(update));
}

/**
* Returns the layout block metric cost
*/
/*public*/ int LayoutBlock::getBlockMetric() { return metric; }

//re work this so that is makes beter us of existing code.
//This is no longer required currently, but might be used at a later date.
/*public*/ void LayoutBlock::addAllThroughPaths()
{
 if(enableAddRouteLogging)
  log->info("Add all ThroughPaths " + this->getDisplayName());
 if ( (block!=NULL) && (panels->size()>0) )
 {
  // a block is attached and this LayoutBlock is used
  // initialize connectivity as defined in first Layout Editor panel
  LayoutEditor* panel = panels->at(0);
  QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(this);
  // if more than one panel, find panel with the highest connectivity
  if (panels->size()>1)
  {
   for (int i = 1;i < panels->size();i++)
   {
    if (c->size()<panels->at(i)->auxTools->getConnectivityList(this)->size())
    {
     panel = panels->at(i);
     c = panel->auxTools->getConnectivityList(this);
    }
   }
   // check that this connectivity is compatible with that of other panels.
   for (int j = 0;j < panels->size();j++)
   {
    LayoutEditor* tPanel = panels->at(j);
    if ( (tPanel!=panel) && ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->
                            warn() && ( !compareConnectivity(c,
                                    tPanel->auxTools->getConnectivityList(this)) )  )
    {
     // send user an error message
//     int response = JOptionPane.showOptionDialog(NULL,
//            java.text.MessageFormat.format(tr("Warn1"),
//            new Object[]{blockName,tPanel.getLayoutName(),
//            panel.getLayoutName()}),tr("WarningTitle"),
//            JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE,
//            NULL,new Object[] {tr("ButtonOK"),
//            tr("ButtonOKPlus")},tr("ButtonOK"));
//     if (response!=0)
     QMessageBox messageBox;
     QPushButton*okPlusButton = messageBox.addButton(tr("OK - Stop Warnings"),QMessageBox::ActionRole);
     messageBox.setText(tr("Warning - Connectivities for block \"%1\" in panels \"%2\" and \"%3\" are not compatible.").arg(blockName).arg(tPanel->getLayoutName()).arg(panel->getLayoutName()));
     messageBox.setIcon(QMessageBox::Question);
     messageBox.exec();
     if(messageBox.clickedButton() == okPlusButton)
     {
      // user elected to disable messages
      //InstanceManager::layoutBlockManagerInstance().turnOffWarning();
      ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->turnOffWarning();
     }
    }
   }
  }
  LayoutEditorAuxTools* auxTools = new LayoutEditorAuxTools(panel);
  QVector<LayoutConnectivity*>* d = auxTools->getConnectivityList(this);
  QVector<LayoutBlock*>* attachedBlocks = new QVector<LayoutBlock*>();
  for (int i = 0; i<d->size(); i++)
  {
   if (d->at(i)->getBlock1()!=this)
   {
    attachedBlocks->append(d->at(i)->getBlock1());
   }
   else
   {
    attachedBlocks->append(d->at(i)->getBlock2());
   }
  }
  //Will need to re-look at this to cover both way and single way routes
  QVector<LayoutBlock*>* attachedBlocks2 = attachedBlocks;
  for (int i = 0;i<attachedBlocks->size(); i++)
  {
   if(enableAddRouteLogging)
    log->info("From " + this->getDisplayName() + " block is attached " + attachedBlocks->at(i)->getDisplayName());

   for (int x = 0;x<attachedBlocks2->size(); x++)
   {
    addThroughPath(attachedBlocks->at(i)->getBlock(), attachedBlocks2->at(x)->getBlock(), panel);
   }
  }
 }
}

//TODO - if the block already exists, we still may want to re-work the through paths
//With this bit we need to get our neighbour to send new routes.
void LayoutBlock::addNeighbour(Block* addBlock, int direction, int workingDirection)
{
 bool layoutConnectivityBefore = layoutConnectivity;
 if(enableAddRouteLogging)
  log->info("From " + this->getDisplayName() + " asked to add block " + addBlock->getDisplayName() + " as new neighbour " + decodePacketFlow(workingDirection));
 if (getAdjacency(addBlock)!=NULL)
 {
  if(enableAddRouteLogging)
   log->info("block is already registered");
  addThroughPath(getAdjacency(addBlock));
 }
 else
 {
  Adjacencies* adj = new Adjacencies(addBlock, direction, workingDirection, this);
neighbours->append(adj);
  //Add the neighbor to our routing table.
  //        LayoutBlock* blk = InstanceManager::layoutBlockManagerInstance()->getLayoutBlock(addBlock);
  LayoutBlock* blk = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(addBlock);
  LayoutEditor* editor = getMaxConnectedPanel(); // TODO: ??
  if((editor!=NULL) && (connection==NULL))
  {
   //We should be able to determine block metric now as the tracksegment should be valid
   connection = new ConnectivityUtil(editor);
  }

  //Need to inform our neighbors of our new addition
  //We only add an entry into the routing table if we are able to reach the next working block->
  //If we only transmit routes to it, then we can not route to it therefore it is not added
  Routes* route=NULL;
  if (workingDirection==RXTX || workingDirection==RXONLY)
  {
   if (blk!=NULL)
    route = new Routes(addBlock, this->getBlock(), 1, direction, blk->getBlockMetric(), addBlock->getLengthMm(),this);
   else
    route = new Routes(addBlock, this->getBlock(), 1, direction, 0,0, this);
   routes->append(route);
  }
  if (blk!=NULL)
  {
   bool mutual = blk->informNeighbourOfAttachment(this, this->getBlock(), workingDirection);
   //The propertychange listener will have to be modified depending upon RX or TX selection.
   //if we only transmit routes to this neighbour then we do not want to listen to thier broadcast messages
   if (workingDirection==RXTX || workingDirection==RXONLY)
   {
    blk->addPropertyChangeListener((PropertyChangeListener*)this);
//    connect(blk->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//    connect(blk, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    //log->info("From " + this->getDisplayName() + " add property change " + blk->getDisplayName());
   }
   else
   {
    blk->removePropertyChangeListener((PropertyChangeListener*)this);
    //disconnect(blk->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
   int neighwork = blk->getAdjacencyPacketFlow(this->getBlock());
   if (enableAddRouteLogging)
    log->info("From " + this->getDisplayName() + " " + decodePacketFlow(neighwork) + " " + neighwork);

   if (neighwork!=-1)
   {
    if (enableAddRouteLogging)
    log->info("From " + this->getDisplayName() + " Updating flow direction to " + decodePacketFlow(determineAdjPacketFlow(workingDirection, neighwork)) + " for block " + blk->getDisplayName() + " choice of " + decodePacketFlow(workingDirection) + " " + decodePacketFlow(neighwork));
    int newPacketFlow = determineAdjPacketFlow(workingDirection, neighwork);
    adj->setPacketFlow(newPacketFlow);

    if(newPacketFlow==TXONLY)
    {
     for(int j = routes->size()-1; j>-1; j--)
     {
      if ((routes->at(j)->getDestBlock()==addBlock) && (routes->at(j)->getNextBlock()==this->getBlock()))
      {
       adj->removeRouteAdvertisedToNeighbour(routes->at(j));
       routes->remove(j);
      }
     }
     RoutingPacket* newUpdate = new RoutingPacket(REMOVAL, addBlock, -1, -1, -1, -1, getNextPacketID());
     for(int i=0; i < neighbours->count(); i++)
     {
      Adjacencies* adja = neighbours->at(i);
      adja->removeRouteAdvertisedToNeighbour(addBlock);
     }
     firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(newUpdate));
    }
   }
   else
   {
    if (enableAddRouteLogging)
     log->info("From " + this->getDisplayName() + " neighbour working direction is not valid " + addBlock->getDisplayName());
   }
   adj->setMutual(mutual);

   if (route!=NULL)
   {
    route->stateChange();
   }
   addThroughPath(getAdjacency(addBlock));
   //We get our new neighbour to send us a list of valid routes that they have.
   //This might have to be re-written as a property change event?
   //Also only inform our neighbour if they have us down as a mutual, otherwise it will just reject the packet.
   if ((workingDirection==RXTX || workingDirection==TXONLY) && mutual)
   {
    blk->informNeighbourOfValidRoutes(getBlock());
   }
  }
  else if(enableAddRouteLogging)
  {
   log->info("From " + this->getDisplayName() + " neighbor " + addBlock->getDisplayName() + " has no layoutBlock associated, metric set to " + adj->getMetric());
  }
 }
 /*If the connectivity before had not completed and produced an error with
    setting up through paths, we will cycle through them*/
 if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " layout connectivity before "+ (layoutConnectivityBefore?"yes":"No"));
 if (!layoutConnectivityBefore)
 {
  for (int i = 0; i<neighbours->size(); i++)
  {
   addThroughPath(neighbours->at(i));
  }
 }
 /*We need to send our new neighbour our copy of the routing table however
    we can only send valid routes that would be able to traverse as definded by
    through paths table*/
}

bool LayoutBlock::informNeighbourOfAttachment(LayoutBlock* lBlock, Block* block, int workingDirection){
    Adjacencies* adj = getAdjacency(block);
    if (adj==NULL){
        if(enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " neighbour " + lBlock->getDisplayName() + " has informed us of its attachment to us however we do not yet have it registered");
        return false;
    }
    if(!adj->isMutual())
    {
        if (enableAddRouteLogging){
         log->info(tr("From %1 neighbour %2 wants us to %3; we have it set as %4").arg(
                 this->getDisplayName()).arg(block->getDisplayName()).arg(
                 decodePacketFlow(workingDirection)).arg(decodePacketFlow(adj->getPacketFlow())));
        }
        //Simply if both the neighbour and us both want to do the same thing with sending routing information,
        //in one direction then no routes will be passed.#

        int newPacketFlow = determineAdjPacketFlow(adj->getPacketFlow(), workingDirection);
        if (enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " neighbour " + block->getDisplayName() + " passed " + decodePacketFlow(workingDirection) + " we have " + decodePacketFlow(adj->getPacketFlow()) + " this will be updated to " + decodePacketFlow(newPacketFlow));
        adj->setPacketFlow(newPacketFlow);

        //If we are only set to transmit routing information to the adj, then we will not have it appearing in the routing table
        if(newPacketFlow!=TXONLY){
            Routes* neighRoute = getValidRoute(this->getBlock(), adj->getBlock());
            //log->info("From " + this->getDisplayName() + " neighbour " + adj->getBlock()->getDisplayName() + " valid routes returned as " + neighRoute);
            //log->info("From " + this->getDisplayName() + " neighbour " + adj->getBlock()->getDisplayName() + " " + neighRoute);
            if(neighRoute==NULL){
                log->info("Null route so will bomb out");
                return false;
            }
             if (neighRoute->getMetric()!=adj->getMetric()){
                if(enableAddRouteLogging)
                    log->info("From " + this->getDisplayName() + " The value of the metric we have for this route is not correct " + this->getBlock()->getDisplayName() + ", stored " + neighRoute->getMetric() + " v " + adj->getMetric());
                neighRoute->setMetric(adj->getMetric());
                //This update might need to be more selective
                RoutingPacket* update = new RoutingPacket(UPDATE, adj->getBlock(), -1, (adj->getMetric()+metric), -1, -1, getNextPacketID());
                firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(update));
            }
            if (neighRoute->getMetric()!=adj->getLength()){
                if(enableAddRouteLogging)
                    log->info("From " + this->getDisplayName() + " The value of the length we have for this route is not correct " + this->getBlock()->getDisplayName() + ", stored " + QString("%1").arg(neighRoute->getMetric()) + " v " + adj->getMetric());
                neighRoute->setLength(adj->getLength());
                //This update might need to be more selective
                RoutingPacket* update = new RoutingPacket(UPDATE, adj->getBlock(), -1, -1, adj->getLength()+block->getLengthMm(), -1, getNextPacketID());
                firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(update));
            }
            getRouteByDestBlock(block)->setMetric(lBlock->getBlockMetric());
        }


        if(enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " We were not a mutual adjacency with " + lBlock->getDisplayName() + " but now are");
        if (newPacketFlow==RXTX || newPacketFlow==RXONLY){
            lBlock->addPropertyChangeListener((PropertyChangeListener*)this);
//            connect(lBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//            connect(lBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        } else {
            lBlock->removePropertyChangeListener((PropertyChangeListener*)this);
//            disconnect(lBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }

        if(newPacketFlow==TXONLY)
        {
         for(int j = routes->size()-1; j>-1; j--)
         {
                if ((routes->at(j)->getDestBlock()==block) && (routes->at(j)->getNextBlock()==this->getBlock()))
                {
                    adj->removeRouteAdvertisedToNeighbour(routes->at(j));
                    routes->remove(j);
                }
            }

            for(int j = throughPaths->size()-1; j>-1; j--)
            {
                if ((throughPaths->at(j)->getDestinationBlock()==block))
                {
                    if(enableAddRouteLogging)
                        log->info("From " + this->getDisplayName() + " removed throughpath " + throughPaths->at(j)->getSourceBlock()->getDisplayName() + " " + throughPaths->at(j)->getDestinationBlock()->getDisplayName());
                    throughPaths->remove(j);
                }
            }
            RoutingPacket* newUpdate = new RoutingPacket(REMOVAL, block, -1, -1, -1, -1, getNextPacketID());
            for(int i=0; i < neighbours->count(); i++)
            {
                Adjacencies* adja = neighbours->at(i);
                adja->removeRouteAdvertisedToNeighbour(block);
            }
            firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(newUpdate));
        }

        adj->setMutual(true);
        addThroughPath(adj);
        //As we are now mutual we will send our neigh a list of valid routes.
        if (newPacketFlow==RXTX || newPacketFlow==TXONLY){
            informNeighbourOfValidRoutes(block);
        }
    }
    return true;
}

int LayoutBlock::determineAdjPacketFlow(int our, int neigh)
{
 //Both are the same
 if (enableUpdateRouteLogging)
     log->info("From " + this->getDisplayName() + " values passed our " + decodePacketFlow(our) + " neigh " + decodePacketFlow(neigh));
 if((our==RXTX) && (neigh==RXTX))
 {
  return RXTX;
 }
 /*First off reverse the neighbour flow, as it will be telling us if it will allow or deny traffic from us.
 So if it is set to RX, then we can TX to it.*/
 if(neigh==RXONLY)
  neigh=TXONLY;
 else if(neigh==TXONLY)
  neigh=RXONLY;

 if(our==neigh)
 {
  return our;
 }
 return NONE;
}

void LayoutBlock::informNeighbourOfValidRoutes(Block* newblock)
{
 // java.sql.Timestamp t1 = new java.sql.Timestamp(System.nanoTime());
 QVector<Block*>* validFromPath = new QVector<Block*>();
 if(enableAddRouteLogging)
    log->info("From " + this->getDisplayName() + " new block " + newblock->getDisplayName());

 for(int i= 0; i<throughPaths->size(); i++)
 {
  if(enableAddRouteLogging)
      log->info("From " + this->getDisplayName() + " B through routes " + throughPaths->at(i)->getSourceBlock()->getDisplayName() + " " + throughPaths->at(i)->getDestinationBlock()->getDisplayName());
  if(throughPaths->at(i)->getSourceBlock()==newblock)
  {
   validFromPath->append(throughPaths->at(i)->getDestinationBlock());
  }
  else if (throughPaths->at(i)->getDestinationBlock()==newblock)
  {
   validFromPath->append(throughPaths->at(i)->getSourceBlock());
  }
 }
 if(enableAddRouteLogging)
 {
  log->info("From " + this->getDisplayName() + " ===== valid from size path " + validFromPath->size() + " ====");
  log->info(newblock->getDisplayName());
 }
 //We only send packets on to our neighbor that are registered as being on a valid through path and are mutual.
 LayoutBlock* lBnewblock =NULL;
 Adjacencies* adj = getAdjacency(newblock);
 if(adj->isMutual())
 {
  if(enableAddRouteLogging)
   log->info("From " + this->getDisplayName() + "adj with " + newblock->getDisplayName() + " is mutual");
  //lBnewblock = InstanceManager::layoutBlockManagerInstance()->getLayoutBlock(newblock);
  lBnewblock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(newblock);
 }
 else if(enableAddRouteLogging)
 {
  log->info("From " + this->getDisplayName() + "adj with " + newblock->getDisplayName() + " is NOT mutual");
 }
 if (lBnewblock==NULL)
 {
  return;
 }

 for(int i = 0; i<routes->size(); i++)
 {
  Routes* ro = routes->at(i);
  if(enableAddRouteLogging)
      log->info("source " + ro->getNextBlock()->getDisplayName() + " Dest " + ro->getDestBlock()->getDisplayName());
  if(ro->getNextBlock()==getBlock())
  {
   if(enableAddRouteLogging)
    log->info("From " + this->getDisplayName() + " ro next block is this");
   if(validFromPath->contains(ro->getDestBlock()))
   {
    if(enableAddRouteLogging)
    {
     log->info("From " + this->getDisplayName() + " route to " + ro->getDestBlock()->getDisplayName() + " we have it with a metric of " + ro->getMetric() + " we will add our metric of " + QString("%1").arg(metric) + " this will be sent to " + lBnewblock->getDisplayName() + " a");
    } //we added +1 to hop count and our metric.

    RoutingPacket* update = new RoutingPacket(ADDITION, ro->getDestBlock(), ro->getHopCount()+1, (ro->getMetric()+metric), (ro->getLength()+block->getLengthMm()), -1, getNextPacketID());
    lBnewblock->addRouteFromNeighbour(this, update);
   }
  }
  else
  {
  //Don't know if this might need changing so that we only send out our best route to the neighbour, rather than cycling through them all.
   if(validFromPath->contains(ro->getNextBlock()))
   {
    if(enableAddRouteLogging)
    {
     log->info("From " + this->getDisplayName() + " route to " + ro->getDestBlock()->getDisplayName() + " we have it with a metric of " + ro->getMetric() + " we will add our metric of " + metric + " this will be sent to " + lBnewblock->getDisplayName() + " a");
    } //we added +1 to hop count and our metric.
    if(adj->advertiseRouteToNeighbour(ro))
    {
     //this should keep track of the routes we sent to our neighbour->
     adj->addRouteAdvertisedToNeighbour(ro);
     RoutingPacket* update = new RoutingPacket(ADDITION, ro->getDestBlock(), ro->getHopCount()+1, (ro->getMetric()+metric), (ro->getLength()+block->getLengthMm()), -1, getNextPacketID());
     lBnewblock->addRouteFromNeighbour(this, update);
    }
   }
  }
 }
}


//This works out our direction of route flow correctly
void LayoutBlock::addAdjacency(Path* addPath)
{
 if(enableAddRouteLogging)
  log->info("From " + this->getDisplayName() + " path to be added " + addPath->getBlock()->getDisplayName() + " " + Path::decodeDirection(addPath->getToBlockDirection()));

 Block* destBlockToAdd = addPath->getBlock();
 int ourWorkingDirection = RXTX;
 if (destBlockToAdd == NULL)
 {
  log->error("Found NULL destination block for path from " + this->getDisplayName());
  return;
 }
 if(this->getBlock()->isBlockDenied(destBlockToAdd->getDisplayName()))
 {
  ourWorkingDirection=RXONLY;
 }
 else if(destBlockToAdd->isBlockDenied(this->getBlock()->getDisplayName()))
 {
  ourWorkingDirection=TXONLY;
 }

 if(enableAddRouteLogging)
  log->info("From " + this->getDisplayName() + " to block " + addPath->getBlock()->getDisplayName() + " we should therefore be... " + decodePacketFlow(ourWorkingDirection));
 addNeighbour(addPath->getBlock(), addPath->getToBlockDirection(), ourWorkingDirection);
}

//Might be possible to refactor the removal to use a bit of common code.
void LayoutBlock::removeAdjacency(Path* removedPath)
{
 if(enableDeleteRouteLogging)
  log->info("From " + this->getDisplayName() + " Adjacency to be removed " + removedPath->getBlock()->getDisplayName() + " " + Path::decodeDirection(removedPath->getToBlockDirection()));
    //LayoutBlock* layoutBlock = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(removedPath
 LayoutBlock* layoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(removedPath->getBlock());
 if(layoutBlock!=NULL)
  removeAdjacency(layoutBlock);
}

void LayoutBlock::removeAdjacency(LayoutBlock* layoutBlock){
    if(enableDeleteRouteLogging)
        log->info("From " + this->getDisplayName() + " Adjacency to be removed " + layoutBlock->getDisplayName());
    Block* removedBlock = layoutBlock->getBlock();
    //Work our way backward through the list of neighbours
    //We need to work out which routes to remove first.

    // here we simply remove the routes which are advertised from the removed neighbour
    QVector<Routes*>* tmpBlock = removeRouteRecievedFromNeighbour(removedBlock);

    for (int i = neighbours->size()-1; i>-1; i--){
        //Use to check against direction but don't now.
        if ((neighbours->at(i)->getBlock()==removedBlock)){
             //Was previously before the for loop.
            //Pos move the remove list and remove thoughpath out of this for loop.
            layoutBlock->removePropertyChangeListener((PropertyChangeListener*)this);
            if(enableDeleteRouteLogging)
                log->info("From " + this->getDisplayName() + " block " + removedBlock->getDisplayName() + " found and removed");
            //LayoutBlock* layoutBlockToNotify = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(neighbours->at(i).getBlock());
            LayoutBlock* layoutBlockToNotify = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(neighbours->at(i)->getBlock());
            getAdjacency(neighbours->at(i)->getBlock())->dispose();
            neighbours->remove(i);
            layoutBlockToNotify->notifiedNeighbourNoLongerMutual(this);

        }
    }

    for(int i = throughPaths->size()-1; i>-1; i--){
        if (throughPaths->at(i)->getSourceBlock()==removedBlock){
            //only mark for removal if the source isn't in the adjcency table
            if(getAdjacency(throughPaths->at(i)->getSourceBlock())==NULL){
                if(enableDeleteRouteLogging)
                    log->info("remove " + throughPaths->at(i)->getSourceBlock()->getDisplayName() + " to " + throughPaths->at(i)->getDestinationBlock()->getDisplayName());
                throughPaths->remove(i);
            }
        }
        else if (throughPaths->at(i)->getDestinationBlock()==removedBlock){
            //only mark for removal if the destination isn't in the adjcency table
            if(getAdjacency(throughPaths->at(i)->getDestinationBlock())==NULL){
                if(enableDeleteRouteLogging)
                    log->info("remove " + throughPaths->at(i)->getSourceBlock()->getDisplayName() + " to " + throughPaths->at(i)->getDestinationBlock()->getDisplayName());
                throughPaths->remove(i);
            }
        }
    }
    if(enableDeleteRouteLogging)
        log->info("From " + this->getDisplayName() + " neighbour has been removed - Number of routes to this neighbour removed" + tmpBlock->size());
    notifyNeighboursOfRemoval(tmpBlock, removedBlock);
}

//This is used when a property event change is triggered for a removed route.  Not sure that bulk removals will be necessary
void LayoutBlock::removeRouteFromNeighbour(LayoutBlock* src, RoutingPacket* update)
{
    //InstanceManager::layoutBlockManagerInstance().setLastRoutingChange();
    ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->setLastRoutingChange();
    Block* srcblk = src->getBlock();
    Block* destblk = update->getBlock();
    QString msgPrefix = "From " + this->getDisplayName() + " notify block " + srcblk->getDisplayName() + " ";
    if(enableDeleteRouteLogging)
        log->info(msgPrefix + " remove route from neighbour called");

    //if (InstanceManager::layoutBlockManagerInstance().getLayoutBlock(srcblk)==this){
    if(((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(srcblk))
    {
        if(enableDeleteRouteLogging)
            log->info("From " + this->getDisplayName() + " source block is the same as our block! " + destblk->getDisplayName());
        return;
    }

    if(enableDeleteRouteLogging){
        log->info(msgPrefix+ " (Direct Notification) neighbour " + srcblk->getDisplayName() + " has removed route to " + destblk->getDisplayName());
        log->info(msgPrefix+ " routes in table " + routes->size() + " Remove route from neighbour");
    }
    QVector<Routes*>* routesToRemove = new QVector<Routes*>();
    for (int i = routes->size()-1; i> -1; i--){
        Routes* ro = routes->at(i);
        if((ro->getNextBlock()==srcblk) && ro->getDestBlock()==destblk){
            routesToRemove->append(new Routes(routes->at(i)->getDestBlock(), routes->at(i)->getNextBlock(), 0,0,0,0, this));
            if(enableDeleteRouteLogging)
                log->info(msgPrefix + " route to " + ro->getDestBlock()->getDisplayName() + " from block " + ro->getNextBlock()->getDisplayName() + " to be removed triggered by propertyChange");
            routes->remove(i);
            //We only fire off routing update the once
        }
    }
    notifyNeighboursOfRemoval(routesToRemove, srcblk);
}

QVector<Routes*>* LayoutBlock::removeRouteRecievedFromNeighbour(Block* removedBlock){
    QVector<Routes*>* tmpBlock = new QVector<Routes*>();

    // here we simply remove the routes which are advertised from the removed neighbour
    for(int j = routes->size()-1; j>-1; j--){
        if(enableDeleteRouteLogging)
            log->info("From " + this->getDisplayName()+  " route to check " + routes->at(j)->getDestBlock()->getDisplayName() + " from Block " + routes->at(j)->getNextBlock()->getDisplayName());
        if(routes->at(j)->getDestBlock()==removedBlock){
            if(enableDeleteRouteLogging)
                log->info("From " + this->getDisplayName() + " route to " + routes->at(j)->getDestBlock()->getDisplayName() + " from block " + routes->at(j)->getNextBlock()->getDisplayName() + " to be removed triggered by adjancey removal as dest block has been removed");
            if (!tmpBlock->contains(routes->at(j)))
                tmpBlock->append(routes->at(j));
            routes->remove(j);
            //This will need to be removed fromth directly connected
        } else if (routes->at(j)->getNextBlock()==removedBlock){
            if(enableDeleteRouteLogging)
                log->info("From " + this->getDisplayName() + " route to " + routes->at(j)->getDestBlock()->getDisplayName() + " from block " + routes->at(j)->getNextBlock()->getDisplayName() + " to be removed triggered by adjancey removal");
            if (!tmpBlock->contains(routes->at(j)))
                tmpBlock->append(routes->at(j));
            routes->remove(j);
            //This will also need to be removed from the directly connected list as well.
        }
    }
    return tmpBlock;
}

void LayoutBlock::updateNeighbourPacketFlow(Block* neighbour, int flow){
    //Packet flow from neighbour will need to be reversed.
    Adjacencies* neighAdj = getAdjacency(neighbour);
    if(flow==RXONLY){
        flow = TXONLY;
    } else if (flow==TXONLY) {
        flow = RXONLY;
    }
    if(neighAdj->getPacketFlow()==flow)
    {
        return;
    }
    updateNeighbourPacketFlow(neighAdj, flow);
}

/*protected*/ void LayoutBlock::updateNeighbourPacketFlow(Adjacencies* neighbour, /*final*/ int flow)
{
 if(neighbour->getPacketFlow()==flow)
 {
  return;
 }

 /*final*/ LayoutBlock* neighLBlock = neighbour->getLayoutBlock();

//    Runnable* r = new Runnable(this);
 LBRunnable* r = new LBRunnable(neighLBlock, block, flow, this);
//    {
//      /*public*/ void run()
//      {
//          neighLBlock->updateNeighbourPacketFlow(block, flow);
//      }
//    };
//    QThread* thr = new QThread(r);

 Block* neighBlock = neighbour->getBlock();
 int oldPacketFlow = neighbour->getPacketFlow();

 neighbour->setPacketFlow(flow);
 QThreadPool::globalInstance()->start(r);


 if(flow==LayoutBlock::TXONLY)
 {
  neighBlock->addBlockDenyList(this->block);
  neighLBlock->removePropertyChangeListener((PropertyChangeListener*)this);
  //disconnect(neighLBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //This should remove routes learned from our neighbour
  QVector<Routes*>* tmpBlock = removeRouteRecievedFromNeighbour(neighBlock);

  notifyNeighboursOfRemoval(tmpBlock, neighBlock);

//Need to also remove all through paths to this neighbour
  for(int i = throughPaths->size()-1; i>-1; i--)
  {
   if (throughPaths->at(i)->getDestinationBlock()==neighBlock)
   {
    throughPaths->remove(i);
    firePropertyChange("through-path-removed", QVariant(), QVariant());
   }
  }
  //We potentially will need to re-advertise routes to this neighbour
  if(oldPacketFlow==RXONLY)
  {
   addThroughPath(neighbour);
  }
 }
 else if (flow==RXONLY)
 {
  neighLBlock->addPropertyChangeListener((PropertyChangeListener*)this);
  //connect(neighLBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  neighBlock->removeBlockDenyList(this->block);
  this->block->addBlockDenyList(neighBlock);

  for(int i = throughPaths->size()-1; i>-1; i--)
  {
   if (throughPaths->at(i)->getSourceBlock()==neighBlock)
   {
    throughPaths->remove(i);
    firePropertyChange("through-path-removed", QVariant(), QVariant());
   }
  }
  //Might need to rebuild through paths.
  if(oldPacketFlow==TXONLY)
  {
   routes->append(new Routes(neighBlock, this->getBlock(), 1, neighbour->getDirection(), neighLBlock->getBlockMetric(), neighBlock->getLengthMm(), this));
   addThroughPath(neighbour);
  }
  //We would need to withdraw the routes that we advertise to the neighbour
 } else if (flow ==RXTX)
 {
  neighBlock->removeBlockDenyList(this->block);
  this->block->removeBlockDenyList(neighBlock);
  neighLBlock->addPropertyChangeListener((PropertyChangeListener*)this);
  //connect(neighLBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //Might need to rebuild through paths.
  if(oldPacketFlow==TXONLY)
  {
   routes->append(new Routes(neighBlock, this->getBlock(), 1, neighbour->getDirection(), neighLBlock->getBlockMetric(), neighBlock->getLengthMm(), this));
  }
  addThroughPath(neighbour);
 }
}
LBRunnable::LBRunnable(LayoutBlock* neighLBlock, Block* block, int flow, LayoutBlock *layoutblock) : QRunnable()
{
 this->layoutblock = layoutblock;
 this->neighLBlock = neighLBlock;
 this->block = block;
 this->flow = flow;
}

void LBRunnable::run()
{
 neighLBlock->updateNeighbourPacketFlow(block, flow);
}

void LayoutBlock::notifyNeighboursOfRemoval(QVector<Routes*>* routesToRemove, Block* notifyingblk)
{
    QString msgPrefix = tr("From ") + this->getDisplayName() + " notify block " + notifyingblk->getDisplayName() + " ";
    if(enableDeleteRouteLogging)
        log->info(msgPrefix + " notifyNeighboursOfRemoval called for routes from " + notifyingblk->getDisplayName() + " ===");
    bool notifyvalid=false;
    for (int i = neighbours->size()-1; i>-1; i--){
        if (neighbours->at(i)->getBlock()==notifyingblk){
            notifyvalid=true;
        }
    }
    if(enableDeleteRouteLogging)
        log->info(msgPrefix + " The notifying block is still valid? " + notifyvalid);

    for (int j = routesToRemove->size()-1; j> -1; j--){
        bool stillexist = false;
        Block* destBlock = routesToRemove->at(j)->getDestBlock();
        Block* sourceBlock = routesToRemove->at(j)->getNextBlock();
        RoutingPacket* newUpdate = new RoutingPacket(REMOVAL, destBlock, -1, -1, -1, -1, getNextPacketID());
        if(enableDeleteRouteLogging)
            log->info("From " + this->getDisplayName() + " notify block " + notifyingblk->getDisplayName() + " checking " + destBlock->getDisplayName() + " from " + sourceBlock->getDisplayName());
        QVector<Routes*>* validroute = new QVector<Routes*>();
        QVector<Routes*>* destRoutes = getDestRoutes(destBlock);
        for(int i = 0; i<destRoutes->size(); i++){
            //We now know that we still have a valid route to the dest
            if(destRoutes->at(i)->getNextBlock()==this->getBlock()){
                if(enableDeleteRouteLogging)
                    log->info(msgPrefix + " The destBlock " + destBlock->getDisplayName() + " is our neighbour");
                validroute->append(new Routes(destRoutes->at(i)->getDestBlock(), destRoutes->at(i)->getNextBlock(), 0, 0, 0, 0, this));
                stillexist=true;
            } else {
            //At this stage do we need to check if the valid route comes from a neighbour?
                if(enableDeleteRouteLogging)
                    log->info(msgPrefix + " we still have a route to " + destBlock->getDisplayName() + " via " + destRoutes->at(i)->getNextBlock()->getDisplayName() + " in our list");
                validroute->append(new Routes(destBlock, destRoutes->at(i)->getNextBlock(), 0, 0, 0, 0, this));
                stillexist=true;
            }
        }
        //We may need to find out who else we could of sent the route to by checking in the through paths


        if(stillexist){
            if(enableDeleteRouteLogging) {
                log->info(msgPrefix + "A Route still exists");
                log->info(msgPrefix + " the number of routes installed to block " + destBlock->getDisplayName() + " is " + QString("%1").arg(validroute->size()));
            }
            if (validroute->size()==1){
                //Specific routing update.
                Block* nextHop = validroute->at(0)->getNextBlock();
                LayoutBlock* layoutBlock;
                if(validroute->at(0)->getNextBlock()!=this->getBlock()){
                    //layoutBlock = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(nextHop);
                    layoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(nextHop);
                    if(enableDeleteRouteLogging)
                        log->info(msgPrefix + " We only have a single valid route left to " + destBlock->getDisplayName() + " So will tell " + layoutBlock->getDisplayName() + " we no longer have it");
                    layoutBlock->removeRouteFromNeighbour(this, newUpdate);
                    getAdjacency(nextHop)->removeRouteAdvertisedToNeighbour(routesToRemove->at(j));
                }

                //At this point we could probably do with checking for other valid paths from the notifyingblock
                //Have a feeling that this is pretty much the same as above!
                QVector<Block*>* validNeighboursToNotify = new QVector<Block*>();
                //Problem we have here is that although we only have one valid route, one of our neighbours
                //could still hold a valid through path.
                for (int i = neighbours->size()-1; i>-1; i--){
                    //Need to ignore if the dest block is our neighour in this instance
                    if ((neighbours->at(i)->getBlock()!=destBlock) && (neighbours->at(i)->getBlock()!=nextHop)){
                        if (validThroughPath(notifyingblk, neighbours->at(i)->getBlock())){
                            Block* neighblock = neighbours->at(i)->getBlock();
                            if(enableDeleteRouteLogging)
                                log->info(msgPrefix + " we could of potentially sent the route to " + neighblock->getDisplayName());
                            if(!validThroughPath(nextHop, neighblock)){
                                if(enableDeleteRouteLogging)
                                    log->info(msgPrefix + " there is no other valid path so will mark for removal");
                                validNeighboursToNotify->append(neighblock);
                            } else {
                                if(enableDeleteRouteLogging)
                                    log->info(msgPrefix + " there is another valid path so will NOT mark for removal");
                            }
                        }
                    }
                }
                if(enableDeleteRouteLogging){
                    log->info(msgPrefix + " the next block is our selves so we won't remove!");
                    log->info(msgPrefix + " do we need to find out if we could of send the route to another neighbour such as?");
                }

                for(int i = 0; i<validNeighboursToNotify->size(); i++){
                    //If the neighbour has a valid through path to the dest we will not notify the neighbour of our loss of route
                    if(!validThroughPath(validNeighboursToNotify->at(i), destBlock))
                    {
                        //layoutBlock = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(validNeighboursToNotify->at(i));
                        layoutBlock =((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(validNeighboursToNotify->at(i));
                        if (layoutBlock!=NULL)
                            layoutBlock->removeRouteFromNeighbour(this, newUpdate);
                        getAdjacency(validNeighboursToNotify->at(i))->removeRouteAdvertisedToNeighbour(routesToRemove->at(j));
                    } else {
                        if(enableDeleteRouteLogging)
                            log->info(msgPrefix + validNeighboursToNotify->at(i)->getDisplayName() + " has a valid path to " + destBlock->getDisplayName());
                    }
                }
            }
            else {
                //Need to deal with having multiple routes left.
                if(enableDeleteRouteLogging)
                    log->info(msgPrefix + " routes left to block " + destBlock->getDisplayName());
                for(int i = 0; i<validroute->size(); i++){
                    //We need to see if we have valid routes.
                    if(validThroughPath(notifyingblk, validroute->at(i)->getNextBlock())){
                        if(enableDeleteRouteLogging)
                            log->info(msgPrefix + " to " + validroute->at(i)->getNextBlock()->getDisplayName() + " Is a valid route");
                        //Will mark the route for potential removal
                        validroute->at(i)->setMiscFlags(0x02);
                    }
                    else {
                        if(enableDeleteRouteLogging)
                            log->info(msgPrefix + " to " + validroute->at(i)->getNextBlock()->getDisplayName() + " Is not a valid route");
                        //Mark the route to not be removed.
                        validroute->at(i)->setMiscFlags(0x01);
                        //Given that the route to this is not valid, we do not want to be notifying this next block about the loss of route.
                    }
                }
                //We have marked all the routes for either potential notification of route removal, or definate no removal;
                //Now need to get through the list and cross reference each one.
                for(int i = 0; i<validroute->size(); i++){
                    if (validroute->at(i)->getMiscFlags()==0x02){
                        Block* nextblk = validroute->at(i)->getNextBlock();
                        if(enableDeleteRouteLogging)
                            log->info(msgPrefix + " route from " + nextblk->getDisplayName() + " has been flagged for removal");
                        //Need to cross reference it with the routes that are left.
                        bool leaveroute=false;
                        for(int k = 0; k<validroute->size();k++){
                            if (validroute->at(k)->getMiscFlags()==0x01){
                                if(validThroughPath(nextblk, validroute->at(k)->getNextBlock())){
                                    if(enableDeleteRouteLogging)
                                        log->info(msgPrefix + " we have a valid path from " + nextblk->getDisplayName() + " to " + validroute->at(k)->getNextBlock()->getDisplayName());
                                    leaveroute=true;
                                }
                            }
                        }
                        if (!leaveroute){
                        //LayoutBlock* layoutBlock = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(nextblk);
                        LayoutBlock* layoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(nextblk);
                        if(enableDeleteRouteLogging)
                            log->info(msgPrefix + "############ We need to send notification to " + nextblk->getDisplayName() + " to remove route ########### haven't found an example of this yet!");
                        layoutBlock->removeRouteFromNeighbour(this, newUpdate);
                        getAdjacency(nextblk)->removeRouteAdvertisedToNeighbour(routesToRemove->at(j));

                        } else {
                            if(enableDeleteRouteLogging)
                                log->info(msgPrefix + " a valid path through exists " + nextblk->getDisplayName() + " so we will not remove route.");
                        }
                    }
                }
            }
        } else {
            if(enableDeleteRouteLogging)
                log->info(msgPrefix+ " We have no other routes to " + destBlock->getDisplayName() + " Therefore we will broadast this to our neighbours");
            //for(Adjacencies adj: neighbours){
            for(int i=0; i< neighbours->size(); i++)
            {
                Adjacencies* adj = neighbours->at(i);
                adj->removeRouteAdvertisedToNeighbour(destBlock);
            }
            firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(newUpdate));
        }
    }
    if(enableDeleteRouteLogging)
        log->info(msgPrefix + " finshed check and notifying of removed routes from " + notifyingblk->getDisplayName() + " ===");
    routesToRemove=NULL;
}

void LayoutBlock::addThroughPath(Adjacencies* adj){
    Block* newAdj = adj->getBlock();
    int packetFlow = adj->getPacketFlow();

    if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " addThroughPathCalled with adj " + adj->getBlock()->getDisplayName());
    for (int i = 0; i<neighbours->size(); i++){
    //cycle through all the neighbours
        if(neighbours->at(i)->getBlock()!=newAdj){
            int neighPacketFlow = neighbours->at(i)->getPacketFlow();
            if(enableAddRouteLogging)
                log->info("From " + this->getDisplayName() + " our direction = " +decodePacketFlow(packetFlow) + ", neighbour direction " + decodePacketFlow(neighPacketFlow));
            if ((packetFlow==RXTX) && (neighPacketFlow==RXTX)){
                //if both are RXTX then add flow in both directions
                addThroughPath(neighbours->at(i)->getBlock(), newAdj);
                addThroughPath(newAdj, neighbours->at(i)->getBlock());
            } else if ((packetFlow==RXONLY) && (neighPacketFlow==TXONLY)){
                addThroughPath(neighbours->at(i)->getBlock(), newAdj);
            } else if ((packetFlow==TXONLY) && (neighPacketFlow==RXONLY)){
                addThroughPath(newAdj, neighbours->at(i)->getBlock());
            } else if ((packetFlow==RXTX) && (neighPacketFlow==TXONLY)){ //was RX
                addThroughPath(neighbours->at(i)->getBlock(), newAdj);
            } else if ((packetFlow==RXTX) && (neighPacketFlow==RXONLY)){  //was TX
                addThroughPath(newAdj, neighbours->at(i)->getBlock());
            } else if ((packetFlow==RXONLY) && (neighPacketFlow==RXTX)){
                addThroughPath(neighbours->at(i)->getBlock(), newAdj);
            } else if ((packetFlow==TXONLY) && (neighPacketFlow==RXTX)){
                addThroughPath(newAdj, neighbours->at(i)->getBlock());
            } else {
                if(enableAddRouteLogging)
                    log->info("Invalid combination" + decodePacketFlow(packetFlow) + " " + decodePacketFlow(neighPacketFlow));
            }
        }
    }

}

/*adds a path between two blocks, but without spec a panel*/
void LayoutBlock::addThroughPath(Block* srcBlock, Block* dstBlock){
    if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " Add ThroughPath " + srcBlock->getDisplayName() + " " + dstBlock->getDisplayName());
    if ( (block!=NULL) && (panels->size()>0) ) {
        // a block is attached and this LayoutBlock is used
        // initialize connectivity as defined in first Layout Editor panel
        LayoutEditor* panel = panels->at(0);
        QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(this);
        // if more than one panel, find panel with the highest connectivity
        if (panels->size()>1) {
            for (int i = 1;i < panels->size();i++) {
                if (c->size()<panels->at(i)->auxTools->
                                    getConnectivityList(this)->size()) {
                    panel = panels->at(i);
                    c = panel->auxTools->getConnectivityList(this);
                }
            }
            // check that this connectivity is compatible with that of other panels.
            for (int j = 0;j < panels->size();j++) {
                LayoutEditor* tPanel = panels->at(j);
                if ( (tPanel!=panel) && ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->
                            warn() && ( !compareConnectivity(c,
                                    tPanel->auxTools->getConnectivityList(this)) )  ) {
//                     send user an error message
//                    int response = JOptionPane.showOptionDialog(NULL,
//                            java.text.MessageFormat.format(tr("Warn1"),
//                            new Object[]{blockName,tPanel.getLayoutName(),
//                            panel.getLayoutName()}),tr("WarningTitle"),
//                            JOptionPane.YES_NO_OPTION,JOptionPane.QUESTION_MESSAGE,
//                            NULL,new Object[] {tr("ButtonOK"),
//                            tr("ButtonOKPlus")},tr("ButtonOK"));
//                    if (response!=0)
                             QMessageBox messageBox;
                             QPushButton* okButton = messageBox.addButton(tr("Ok"),QMessageBox::ActionRole);
                             QPushButton*okPlusButton = messageBox.addButton(tr("OK - Stop Warnings"),QMessageBox::ActionRole);
                             messageBox.setText(tr("Warning - Connectivities for block \"%1\" in panels \"%2\" and \"%3\" are not compatible.").arg(blockName).arg(tPanel->getLayoutName()).arg(panel->getLayoutName()));
                             messageBox.setIcon(QMessageBox::Question);
                             messageBox.exec();
                             if(messageBox.clickedButton() == okPlusButton)
                        // user elected to disable messages
                        ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->turnOffWarning();
                }
            }
        }
        // update block Paths to reflect connectivity as needed
        addThroughPath(srcBlock,dstBlock,panel);
    }
}

/**
* This is used to add a through path on this layout block, going from
* the source block to the destination block, using a specific panel.
* Note: That if the reverse path is required, then this need to be added
* seperately.
*/
//Was /*public*/
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="DLS_DEAD_LOCAL_STORE")
void LayoutBlock::addThroughPath(Block* srcBlock, Block* dstBlock, LayoutEditor* panel){
    //Reset connectivity flag.
    layoutConnectivity = true;

    if (srcBlock==dstBlock){
        //Do not do anything if the blocks are the same!
        return;
    }
    if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " Add ThroughPath with panel " +srcBlock->getDisplayName() + " " + dstBlock->getDisplayName());

    //Initally check to make sure that the through path doesn't already exist.
    //no point in going through the checks if the path already exists.
    bool add = true;
    for (int i = 0; i<throughPaths->size(); i++){
        if (throughPaths->at(i)->getSourceBlock()==srcBlock){
            if(throughPaths->at(i)->getDestinationBlock()==dstBlock)
                add=false;
        }
    }
    if(!add)
        return;

    if(enableAddRouteLogging)
        log->info(block->getDisplayName() + " Source " + srcBlock->getDisplayName() + ", dest  " + dstBlock->getDisplayName());
#if 1 // TODO:

    connection = new ConnectivityUtil(panel);
    QList<LayoutTrackExpectedState<LayoutTurnout*>*> stod;
   # if 0
    try {
        MDC.put("loggingDisabled", connection.getClass().getCanonicalName());
        stod = connection.getTurnoutList(block, srcBlock, dstBlock, true);
        MDC.remove("loggingDisabled");
    } catch (java.lang.NullPointerException ex) {
        MDC.remove("loggingDisabled");
        if (enableAddRouteLogging) {
            log.error("Exception (" + ex.toString() + ") caught while trying to discover turnout connectivity\n"
                    + "Block: " + block.getDisplayName()
                    + ", srcBlock (" + srcBlock.getDisplayName()
                    + ") to dstBlock (" + dstBlock.getDisplayName() + ")");
            log.error("@ Line # " + ex.getStackTrace()[1].getLineNumber());
        }
        return;
    }
   # endif
    if (!connection->isTurnoutConnectivityComplete()) {
        layoutConnectivity = false;
    }
    QList<LayoutTrackExpectedState<LayoutTurnout*>*> tmpdtos;
   # if 0
    try {
        MDC.put("loggingDisabled", connection.getClass().getName());
        tmpdtos = connection.getTurnoutList(block, dstBlock, srcBlock, true);
        MDC.remove("loggingDisabled");
    } catch (java.lang.NullPointerException ex) {
        MDC.remove("loggingDisabled");
        if (enableAddRouteLogging) {
            log.error("Exception (" + ex.toString() + ") caught while trying to discover turnout connectivity\n"
                    + "Block: " + block.getDisplayName()
                    + ", dstBlock (" + dstBlock.getDisplayName()
                    + ") to  srcBlock (" + srcBlock.getDisplayName() + ")");
            log.error("@ Line # " + ex.getStackTrace()[1].getLineNumber());
        }
        return;
    }
   # endif
    if (!connection->isTurnoutConnectivityComplete()) {
        layoutConnectivity = false;
    }

 if (stod.size() == tmpdtos.size()) {
     //Need to reorder the tmplist (dst-src) to be the same order as src-dst
     QList<LayoutTrackExpectedState<LayoutTurnout*>*> dtos = QList<LayoutTrackExpectedState<LayoutTurnout*>*>();
     for (int i = tmpdtos.size(); i > 0; i--) {
         dtos.append(tmpdtos.at(i - 1));
     }

     //check to make sure that we pass through the same turnouts
     if (enableAddRouteLogging) {
         log->info(tr("From %1 destination size %2 v source size %3").arg(this->getDisplayName()).arg(dtos.size()).arg(stod.size()));
     }

     for (int i = 0; i < dtos.size(); i++) {
         if (dtos.at(i)->getObject() != stod.at(i)->getObject()) {
             if (enableAddRouteLogging) {
                 log->info(tr("%1 != %2: will quit").arg(dtos.at(i)->getObject()->getName(), stod.at(i)->getObject()->getName()));
             }
             return;
         }
     }

     for (int i = 0; i < dtos.size(); i++) {
         int x = stod.at(i)->getExpectedState();
         int y = dtos.at(i)->getExpectedState();

         if (x != y) {
             if (enableAddRouteLogging) {
                 log->info(tr("%1 not on setting equal will quit %2, %3").arg(block->getDisplayName(), x, y));
             }
             return;
         } else if (x == Turnout::UNKNOWN) {
             if (enableAddRouteLogging) {
                 log->info(tr("%1 turnout state returned as UNKNOWN").arg(block->getDisplayName()));
             }
             return;
         }
     }
     QSet<LayoutTurnout*> set = QSet<LayoutTurnout*>();

     for (int i = 0; i < stod.size(); i++) {
         /*bool val =*/ set.insert(stod.at(i)->getObject());
//         if (val == false) {
//             //Duplicate found. will not add
//             return;
//         }
     }
     //for (LayoutTurnout turn : stod) {
     //    if (turn.type == LayoutTurnout.DOUBLE_XOVER) {
     //        //Further checks might be required.
     //    }
     //}
     addThroughPathPostChecks(srcBlock, dstBlock, stod);
 } else {
     //We know that a path that contains a double cross-over, is not reported correctly,
     //therefore we shall do some additional checks and add it.
     if (enableAddRouteLogging) {
         log->info("sizes are not the same therefore, we will do some further checks");
     }
     QList<LayoutTrackExpectedState<LayoutTurnout*>*> maxt;
     if (stod.size() >= tmpdtos.size()) {
         maxt = stod;
     } else {
         maxt = tmpdtos;
     }

     QSet<LayoutTrackExpectedState<LayoutTurnout*>*> set = QSet<LayoutTrackExpectedState<LayoutTurnout*>*>(maxt.toSet());
     if (set.size() == maxt.size()) {
         if (enableAddRouteLogging) {
             log->info("All turnouts are unique so potentially a valid path");
         }
         bool allowAddition = false;
         for (int i = 0; i < maxt.size(); i++) {
             LayoutTurnout* turn = maxt.at(i)->getObject();
             if (turn->type == LayoutTurnout::DOUBLE_XOVER) {
                 allowAddition = true;
                 //The double crossover gets reported in the opposite setting.
                 if (maxt.at(i)->getExpectedState() == 2) {
                     maxt.at(i)->setExpectedState(4);
                 } else {
                     maxt.at(i)->setExpectedState(2);
                 }
             }
         }

         if (allowAddition) {
             if (enableAddRouteLogging) {
                 log->info("addition allowed");
             }
             addThroughPathPostChecks(srcBlock, dstBlock, maxt);
         } else if (enableAddRouteLogging) {
             log->info("No double cross-over so not a valid path");
         }
     }
 }
#endif
} // addThroughPath

/*private*/ void LayoutBlock::addThroughPathPostChecks(Block* srcBlock, Block* dstBlock, QList<LayoutTrackExpectedState<LayoutTurnout*>*> stod )
{
 QVector<Path*>* paths = block->getPaths();
 Path* srcPath = nullptr;

  for (int i = 0; i < paths->size(); i++) {
      if (paths->at(i)->getBlock() == srcBlock) {
          srcPath = paths->at(i);
      }
  }
  Path* dstPath = nullptr;

  for (int i = 0; i < paths->size(); i++) {
      if (paths->at(i)->getBlock() == dstBlock) {
          dstPath = paths->at(i);
      }
  }
  ThroughPaths* path = new ThroughPaths(srcBlock, srcPath, dstBlock, dstPath, this);
  path->setTurnoutList(stod);

  if (enableAddRouteLogging) {
      log->info("From " + this->getDisplayName() + " added Throughpath "
              + path->getSourceBlock()->getDisplayName() + " " + path->getDestinationBlock()->getDisplayName());
  }
  throughPaths->append(path);
  firePropertyChange("through-path-added", 0, 0);

  //update our neighbours of the new valid paths;
  informNeighbourOfValidRoutes(srcBlock);
  informNeighbourOfValidRoutes(dstBlock);
}


void LayoutBlock::notifiedNeighbourNoLongerMutual(LayoutBlock* srcBlock){
    if(enableDeleteRouteLogging)
        log->info("From " + this->getDisplayName() + "Notification from neighbour that it is no longer our friend " + srcBlock->getDisplayName());
    Block* blk = srcBlock->getBlock();
    for (int i = neighbours->size()-1; i>-1; i--){
        //Need to check if the block we are being informed about has already been removed or not
        if (neighbours->at(i)->getBlock()==blk){
            removeAdjacency(srcBlock);
            break;
        }
    }
}


void LayoutBlock::stateUpdate(){
    //Need to find a way to fire off updates to the various tables
    if(enableUpdateRouteLogging){
        log->info("this is our block state change" + QString("%1").arg(getBlockStatus()));
        log->info("From " + this->getDisplayName() + " A block state change has occured");
    }
    RoutingPacket* update = new RoutingPacket(UPDATE, this->getBlock(), -1, -1, -1, getBlockStatus(), getNextPacketID());
    firePropertyChange("routing", QVariant(),VPtr<RoutingPacket>::asQVariant(update));
}

int LayoutBlock::getBlockStatus(){
    if (getOccupancy() == OCCUPIED) {
        useExtraColor=false;
    //Our section of track is occupied
        return OCCUPIED;
    }
    else if (useExtraColor) {
        return RESERVED;
    }
    else if (getOccupancy() == EMPTY){
        return EMPTY;
    } else {
        return UNKNOWN;
    }
}

//was /*public*/
int LayoutBlock::getNextPacketID(){
    int lastID;
    if (updateReferences->isEmpty()){
        lastID = 0;
    } else {
        int lastIDPos = updateReferences->size()-1;
        lastID = updateReferences->at(lastIDPos) +1;
    }
    updateReferences->append(lastID);
    /*As we are originating a packet, we will added to the acted upion list
    thus making sure if the packet gets back to us we do knowing with it.*/
    actedUponUpdates->append(lastID);
    return lastID;
}

//was /*public*/
bool LayoutBlock::updatePacketActedUpon(int packetID){
    return actedUponUpdates->contains(packetID);
}

/*public*/ QVector<Block*>* LayoutBlock::getActiveNextBlocks(Block* source)
{
    QVector<Block*>* currentPath = new QVector<Block*>();
    for(int i = 0; i<throughPaths->size(); i++){
        ThroughPaths* path = throughPaths->at(i);
        if ((path->getSourceBlock()==source) && (path->isPathActive())){
            currentPath->append(throughPaths->at(i)->getDestinationBlock());
        }
    }
    return currentPath;
}

/*public*/ Path* LayoutBlock::getThroughPathSourcePathAtIndex(int i){
    return throughPaths->at(i)->getSourcePath();
}

/*public*/ Path* LayoutBlock::getThroughPathDestinationPathAtIndex(int i){
    return throughPaths->at(i)->getDestinationPath();
}

/*public*/ bool LayoutBlock::validThroughPath(Block* sourceBlock, Block* destinationBlock){
    for(int i = 0; i<throughPaths->size(); i++){
        if ((throughPaths->at(i)->getSourceBlock()==sourceBlock) && (throughPaths->at(i)->getDestinationBlock()==destinationBlock)){
            return true;
        }else if ((throughPaths->at(i)->getSourceBlock()==destinationBlock) && (throughPaths->at(i)->getDestinationBlock()==sourceBlock)){
            return true;
        }
    }
    return false;
}

/*public*/ int LayoutBlock::getThroughPathIndex(Block* sourceBlock, Block* destinationBlock)
{
    for(int i = 0; i<throughPaths->size(); i++){
        if ((throughPaths->at(i)->getSourceBlock()==sourceBlock) && (throughPaths->at(i)->getDestinationBlock()==destinationBlock))
            return i;
        else if ((throughPaths->at(i)->getSourceBlock()==destinationBlock) && (throughPaths->at(i)->getDestinationBlock()==sourceBlock))
            return i;
    }
    return -1;
}

QString LayoutBlock::decodePacketFlow(int value){
    switch(value){
        case RXTX : return "Bi-Direction Operation";
        case RXONLY : return "Uni-Directional - Trains can only exit to this block (RX) ";
        case TXONLY : return "Uni-Directional - Trains can not be sent down this block (TX) ";
        case NONE : return "None routing updates will be passed";
    }
    return "Unknown";
}

/**
* Provides an output to the console of all the valid paths through this block
*/
/*public*/ void LayoutBlock::printValidThroughPaths(){
    log->info("Through paths in this block");
    log->info("Current Block, From Block, To Block");
    for(int i = 0; i<throughPaths->size(); i++){
        QString activeStr= "";
        if (throughPaths->at(i)->isPathActive()) activeStr = ", *";
        log->info("From " + this->getDisplayName() + ", " + (throughPaths->at(i)->getSourceBlock())->getDisplayName() + ", " + (throughPaths->at(i)->getDestinationBlock())->getDisplayName() + activeStr);
    }
}

/**
* Provides an output to the console of all our neighbouring blocks
*/
/*public*/ void LayoutBlock::printAdjacencies(){
    log->info("");
    log->info("Adjacencies for block " + this->getDisplayName());
    log->info("Neighbour, Direction, mutual, relationship, metric");
    for(int i = 0; i<neighbours->size(); i++){
        log->info(neighbours->at(i)->getBlock()->getDisplayName() + ", " + QString("%1").arg(Path::decodeDirection(neighbours->at(i)->getDirection()))+ ", " +(neighbours->at(i)->isMutual()?"True":"False") + ", " + decodePacketFlow(neighbours->at(i)->getPacketFlow()) + ", " +QString("%1").arg(neighbours->at(i)->getMetric()));
    }
}

/**
* Provides an output to the console of all the remote blocks reachable from our block
*/
/*public*/ void LayoutBlock::printRoutes(){
    log->info("Routes for block " + this->getDisplayName());
    log->info("Destination, Next Block, Hop Count, Direction, State, Metric");
    for(int i = 0; i<routes->size(); i++){
        Routes* r = routes->at(i);
        QString nexthop = r->getNextBlock()->getDisplayName();
        if (r->getNextBlock()==this->getBlock()){
            nexthop = "Directly Connected";
        }
        QString activeQString = "";
        if (r->isRouteCurrentlyValid())
            activeQString = ", *";

        log->info((r->getDestBlock())->getDisplayName() + ", " + nexthop + ", " + r->getHopCount() + ", " + QString("%1").arg(Path::decodeDirection(r->getDirection())) + ", " + QString("%1").arg(r->getState()) + ", " + QString("%1").arg(r->getMetric()) + activeQString);
    }
}

/**
* Provides an output to the console of how to reach a specific block from our block
*/
/*public*/ void LayoutBlock::printRoutes(QString blockName){
    log->info("Routes for block " + this->getDisplayName());
    log->info("Our Block, Destination, Next Block, Hop Count, Direction, Metric");
    for(int i = 0; i<routes->size(); i++){
        if(routes->at(i)->getDestBlock()->getDisplayName()==(blockName))
            log->info("From " + this->getDisplayName() + ", " + (routes->at(i)->getDestBlock())->getDisplayName() + ", " + (routes->at(i)->getNextBlock())->getDisplayName() + ", " + QString("%1").arg(routes->at(i)->getHopCount()) + ", " + QString("%1").arg(Path::decodeDirection(routes->at(i)->getDirection())) + ", " + QString("%1").arg(routes->at(i)->getMetric()));
    }
}

/**
 *   @param destBlock - is the destination of the block we are following
 *   @param direction - is the direction of travel from the previous block
 */
/*public*/ Block* LayoutBlock::getNextBlock(Block* destBlock, int direction){
    int bestMetric=965000;
    Block* bestBlock=NULL;
    for (int i = 0; i<routes->size(); i ++){
        Routes* r = routes->at(i);
        if ((r->getDestBlock()==destBlock) && (r->getDirection()==direction)){
            if (r->getMetric()<bestMetric){
                bestMetric=r->getMetric();
                bestBlock=r->getNextBlock();
                //bestBlock=r->getDestBlock();
            }
        }
    }
    return bestBlock;
}

/**
 *   Used if we already know the block prior to our block, and the destination block->
 *   direction, is optional and is used where the previousBlock is equal to our block->
 */
/*public*/ Block* LayoutBlock::getNextBlock(Block* previousBlock, Block* destBlock){
    int bestMetric=965000;
    Block* bestBlock=NULL;
    for (int i = 0; i<routes->size(); i ++){
        Routes* r = routes->at(i);
        if (r->getDestBlock()==destBlock){
            //Check that the route through from the previous block, to the next hop is valid
            if(validThroughPath(previousBlock, r->getNextBlock())){
                if (r->getMetric()<bestMetric){
                    bestMetric=r->getMetric();
                    //bestBlock=r->getDestBlock();
                    bestBlock=r->getNextBlock();
                }
            }
        }
    }
    return bestBlock;
}

/*public*/ int LayoutBlock::getConnectedBlockRouteIndex(Block* destBlock, int direction)
{
 for(int i = 0; i<routes->size(); i++)
 {
  if (routes->at(i)->getNextBlock()==this->getBlock())
  {
   log->info("Found a block that is directly connected");
   if ((routes->at(i)->getDestBlock()==destBlock))
   {
    log->info(QString("%1").arg((routes->at(i)->getDirection()&direction)));
    if ((routes->at(i)->getDirection()&direction)!=0)
    {
     return i;
    }
   }
  }
  if(log->isDebugEnabled())
            log->debug("From " + this->getDisplayName() + ", " +(routes->at(i)->getDestBlock())->getDisplayName() + ", nexthop " + QString("%1").arg(routes->at(i)->getHopCount()) + ", " + QString("%1").arg(Path::decodeDirection(routes->at(i)->getDirection())) + ", " + QString("%1").arg(routes->at(i)->getState()) + ", " + QString("%1").arg(routes->at(i)->getMetric()));
    }
    return -1;
}

//Need to work on this to deal with the method of routing
/*public*/ int LayoutBlock::getNextBlockByIndex(Block* destBlock, int direction, int offSet)
{
    for (int i = offSet; i<routes->size(); i++){
        Routes* r = routes->at(i);
        if ((r->getDestBlock()==destBlock))
        {
//         log->info((r->getDirection()&direction));
            if ((r->getDirection()&direction)!=0){
                return i;
            }
        }
    }
    return -1;
}

//Need to work on this to deal with the method of routing
/*
*
*/
/*public*/ int LayoutBlock::getNextBlockByIndex(Block* previousBlock, Block* destBlock, int offSet){
    for (int i = offSet; i<routes->size(); i ++){
        Routes* r = routes->at(i);
        //log->info(r->getDestBlock()->getDisplayName() + " vs " + destBlock->getDisplayName());
        if (r->getDestBlock()==destBlock){
            //Check that the route through from the previous block, to the next hop is valid
            if(validThroughPath(previousBlock, r->getNextBlock())){
                log->debug("valid through path");
                return i;
            }
            if (r->getNextBlock()==this->getBlock()){
                log->debug("getNextBlock is this block therefore directly connected");
                return i;
            }
        }
    }
    return -1;
}

/**
* last index - the index of the last block we returned ie we last returned
* index 10, so we don't want to return it again.
* The block returned will have a hopcount or metric equal to or greater than
* the one of the last block returned.
* if the exclude block list is empty this is the first time, it has been used.
* The parameters for the best last block are based upon the last entry in the excludedBlock list
*/

/*public*/ int LayoutBlock::getNextBestBlock(Block* previousBlock, Block* destBlock, QList<int> excludeBlock, int routingMethod){
    if(enableSearchRouteLogging)
        log->info("From " + this->getDisplayName() + " find best route from " + previousBlock->getDisplayName() + " to " + destBlock->getDisplayName() + " index " + QString("%1").arg(excludeBlock.at(0)) + " routingMethod " + QString("%1").arg(routingMethod));
    int bestCount = 965255; //set stupidly high
    int bestIndex = -1;
    int lastValue = 0;
    if(!excludeBlock.isEmpty() && (excludeBlock.at(excludeBlock.size()-1)<routes->size())){
        if (routingMethod==LayoutBlockConnectivityTools::METRIC){
            lastValue = routes->at(excludeBlock.at(excludeBlock.size()-1))->getMetric();
        } else /* if (routingMethod==LayoutBlockManager->HOPCOUNT)*/{
            lastValue = routes->at(excludeBlock.at(excludeBlock.size()-1))->getHopCount();
        }
        if(enableSearchRouteLogging)
            log->info(tr("last index is ") + excludeBlock.at(excludeBlock.size()-1) + " " + routes->at(excludeBlock.at(excludeBlock.size()-1))->getDestBlock()->getDisplayName());
    }
    for (int i = 0; i<routes->size(); i ++){
        if (!excludeBlock.contains(i)){
            Routes* r = routes->at(i);
            int currentValue;
            if (routingMethod==LayoutBlockConnectivityTools::METRIC){
                currentValue = routes->at(i)->getMetric();

            } else /*if (routingMethod==InstanceManager::layoutBlockManagerInstance().HOPCOUNT)*/{
                currentValue = routes->at(i)->getHopCount();  //was lastindex changed to i
            }
            if(currentValue>=lastValue){
                if (r->getDestBlock()==destBlock){
                    if(enableSearchRouteLogging){
                        log->info("Match on dest blocks");
                    //Check that the route through from the previous block, to the next hop is valid
                        log->info("Is valid through path previous block " + previousBlock->getDisplayName() + " to " + r->getNextBlock()->getDisplayName());
                    }
                    if(validThroughPath(previousBlock, r->getNextBlock())){
                        if(enableSearchRouteLogging)
                            log->info("valid through path");
                        if (routingMethod==LayoutBlockConnectivityTools::METRIC){
                            if (r->getMetric()<bestCount){
                                bestIndex = i;
                                bestCount = r->getMetric();
                            }

                        } else /*if (routingMethod==InstanceManager::layoutBlockManagerInstance().HOPCOUNT)*/{
                            if (r->getHopCount()<bestCount){
                                bestIndex = i;
                                bestCount = r->getHopCount();
                            }
                        }
                    }
                    if (r->getNextBlock()==this->getBlock()){
                        if(enableSearchRouteLogging)
                            log->info("getNextBlock is this block therefore directly connected");
                        return i;
                    }
                }
            }
        }
    }
    if(enableSearchRouteLogging)
        log->info("returning " + QString("%1").arg(bestIndex) + " best count " + QString("%1").arg(bestCount)) ;
    return bestIndex;
}

Routes* LayoutBlock::getRouteByDestBlock(Block* blk)
{
    for (int i = routes->size()-1; i> -1; i--){
        if(routes->at(i)->getDestBlock()==blk)
            return routes->at(i);
    }
    return NULL;
}

QVector<Routes*>* LayoutBlock::getRouteByNeighbour(Block* blk){
    QVector<Routes*>* rtr = new QVector<Routes*>();
    for (int i = 0; i<routes->size(); i++){
        if(routes->at(i)->getNextBlock()==blk){
            rtr->append(routes->at(i));
        }
    }
    return rtr;
}

int LayoutBlock::getAdjacencyPacketFlow(Block* blk)
{
 for(int i = 0; i<neighbours->size(); i++)
 {
  if(neighbours->at(i)->getBlock()==blk)
   return neighbours->at(i)->getPacketFlow();
 }
 return -1;
}

bool LayoutBlock::isValidNeighbour(Block* blk){
    for(int i = 0; i<neighbours->size(); i++){
        if(neighbours->at(i)->getBlock()==blk)
            return true;
    }
    return false;
}

//@Override
/*public*/ /*synchronized*/ void LayoutBlock::addPropertyChangeListener(PropertyChangeListener* l)
{
 if (l == NULL) throw new NullPointerException();
 QMutexLocker locker(&mutex);
//    if(l==this){
//        if(enableAddRouteLogging)
//            log->info("adding ourselves as a listener for some strange reason!");
//        return;
//    }
 if (!listeners->contains(l))
 {
  listeners->append(l);
  pcs->addPropertyChangeListener(l);
 }
}
//@Override
/*public*/ /*synchronized*/ void LayoutBlock::removePropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);

 if (listeners->contains(l)) {
     listeners->remove(listeners->indexOf(l));
     pcs->removePropertyChangeListener(l);
 }
}

//@Override
/*protected*/ void LayoutBlock::firePropertyChange(QString p, QVariant old,QVariant n) { pcs->firePropertyChange(p,old,n);}

/*public*/ void LayoutBlock::propertyChange(PropertyChangeEvent* e)
{
 //if(e.getSource() instanceof LayoutBlock){
 if(qobject_cast<LayoutBlock*>(e->getSource()) != NULL)
 {
  LayoutBlock* srcEvent = (LayoutBlock*) e->getSource();
  if (e->getPropertyName()==("NewRoute"))
  {
   LayoutBlock* lbkblock = (LayoutBlock*) VPtr<LayoutBlock*>::asPtr(e->getNewValue());
   if(enableUpdateRouteLogging) log->info("==Event type " + e->getPropertyName() + " New " + lbkblock->getDisplayName());
  }
  else if (e->getPropertyName()==("through-path-added"))
  {
   if(enableUpdateRouteLogging) log->info("neighbour has new through path");
  }
  else if (e->getPropertyName()==("through-path-removed"))
  {
   if(enableUpdateRouteLogging) log->info("neighbour has through removed");
  }
  else if (e->getPropertyName()==("routing"))
  {
   if(enableUpdateRouteLogging)
    log->info("From " + this->getDisplayName() + " we have a routing packet update from neighbor "+ srcEvent->getDisplayName());
   RoutingPacket* update = (RoutingPacket*) VPtr<RoutingPacket>::asPtr(e->getNewValue());
   int updateType = update->getPacketType();
   switch (updateType)
   {
    case ADDITION : if(enableUpdateRouteLogging) log->info("Addition");
                                //InstanceManager::layoutBlockManagerInstance().setLastRoutingChange();
     addRouteFromNeighbour(srcEvent, update);
     break;
    case UPDATE :  if(enableUpdateRouteLogging) log->info("Update");
     updateRoutingInfo(srcEvent, update);
     break;
    case REMOVAL : if(enableUpdateRouteLogging) log->info("Removal");
     ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->setLastRoutingChange();
     removeRouteFromNeighbour(srcEvent, update);
     break;
    default :       break;
   }
  }
 }
}

/**
*   Returns a valid Routes, based upon the next block and destination block
*/
Routes* LayoutBlock::getValidRoute(Block* nxtBlock, Block* dstBlock)
{
 QVector<Routes*>* rtr = getRouteByNeighbour(nxtBlock);
 if (rtr==NULL)
 {
  log->info("From " + this->getDisplayName() + "No routes returned in get valid routes");
  return NULL;
 }
 for (int i = 0; i<rtr->size(); i++){
//            log->info("From " + this->getDisplayName() + ", found dest " + rtr->get(i).getDestBlock()->getDisplayName() + ", required dest " + dstBlock->getDisplayName());
        if (rtr->at(i)->getDestBlock()==dstBlock){
//                log->info("From " + this->getDisplayName() + " matched");
            return rtr->at(i);
        }
    }
    return NULL;
}

/**
* Is the route to the destination block, going via our neighbouring block valid.
* ie Does the block have a route registered via neighbour "protecting" to the
* destination block->
*/
/*public*/ bool LayoutBlock::isRouteToDestValid(Block* protecting, Block* destination){
    if(protecting==destination){
        log->debug("protecting and destination blocks are the same therefore we need to check if we have a valid neighbour");
        //We are testing for a directly connected block->
        if(getAdjacency(protecting)!=NULL)
            return true;
    } else if(getValidRoute(protecting, destination)!=NULL)
        return true;
    return false;
}

/**
*   Returns a list of valid Routes to our destination block
*/
QVector<Routes*>* LayoutBlock::getDestRoutes(Block* dstBlock){
    QVector<Routes*>* rtr = new QVector<Routes*>();
    for (int i = 0; i<routes->size(); i++){
        if(routes->at(i)->getDestBlock()==dstBlock){
            rtr->append(routes->at(i));
        }
    }
    return rtr;
}

/**
*   Returns a list of valid Routes via our next block
*/
QVector<Routes*>* LayoutBlock::getNextRoutes(Block* nxtBlock){
    QVector<Routes*>* rtr = new QVector<Routes*>();
    for (int i = 0; i<routes->size(); i++){
        if(routes->at(i)->getNextBlock()==nxtBlock){
            rtr->append(routes->at(i));
        }
    }
    return rtr;
}

void LayoutBlock::updateRoutingInfo(LayoutBlock* src, RoutingPacket* update)
{
    if(enableUpdateRouteLogging)
        log->info("From " + this->getDisplayName() + " src: " + src->getDisplayName() + " block: " + update->getBlock()->getDisplayName() + " hopCount " + QString("%1").arg(update->getHopCount()) + " metric: " + QString("%1").arg(update->getMetric()) + " status: " + QString("%1").arg(update->getBlockState()) + " packetID: " + QString("%1").arg(update->getPacketId()));
    Block* srcblk = src->getBlock();
    Adjacencies* adj = getAdjacency(srcblk);

    if(adj==NULL)
    {
        if(enableUpdateRouteLogging)
            log->info("From " + this->getDisplayName() + " packet is from a src that is not registered " + srcblk->getDisplayName());
        //If the packet is from a src that is not registered as a neighbor
        //Then we will simply reject it.
        return;
    }
    if (updatePacketActedUpon(update->getPacketId())){
        if(adj->updatePacketActedUpon(update->getPacketId())){
            if(enableUpdateRouteLogging)
                log->info("Reject packet update as we have already acted up on it from this neighbour");
            return;
        }
    }

    if(enableUpdateRouteLogging)
        log->info("From " + this->getDisplayName() + " an Update packet from neighbour " + src->getDisplayName());

    Block* updateBlock = update->getBlock();
    //Block srcblk = src.getBlock();
    //Need to add in a check to make sure that we have a route registered from the source neighbour for the block that they are refering too.
    if(updateBlock==this->getBlock())
    {
        if(enableUpdateRouteLogging)
            log->info("Reject packet update as it is a route advertised by our selves");
        return;
    }

    Routes* ro=NULL;
    bool neighbour = false;
    if (updateBlock==srcblk){
        //Very likely that this update is from a neighbour about its own status.
        ro=getValidRoute(this->getBlock(), updateBlock);
        neighbour=true;
    } else {
        ro = getValidRoute(srcblk, updateBlock);
    }

    if (ro==NULL){
        if(enableUpdateRouteLogging){
            log->info("From " + this->getDisplayName() + " update is from a source that we do not have listed as a route to the destination");
            log->info("From " + this->getDisplayName() + " update packet is for a block that we do not have route registered for " + updateBlock->getDisplayName());
        }
        //If the packet is for a dest that is not in the routing table
        //Then we will simply reject it.
        return;
    }

    /*This prevents us from entering into an update loop.
    We only add it to our list once it has passed through as being a valid
    packet, otherwise we may get the same packet id back, but from a valid source
    which would end up be rejected*/

    actedUponUpdates->append(update->getPacketId());
    adj->addPacketRecievedFromNeighbour(update->getPacketId());

    int hopCount = update->getHopCount();
    int packetmetric = update->getMetric();
    int blockstate = update->getBlockState();
    float length = update->getLength();

    //Need to add in a check for a block that is directly connected.
    if (hopCount!=-1){
          //Was increase hop count before setting it
        if(ro->getHopCount()!=hopCount){
            ro->setHopCount(hopCount);
            hopCount++;
        } else {
            //No point in forwarding on the update if the hopcount hasn't changed
            hopCount=-1;
        }
    }
    if(length!=-1){
        //Length is added at source
        float oldLength = ro->getLength();
        if(oldLength!=length){
            ro->setLength(length);
            if(enableUpdateRouteLogging)
                log->info("From " + this->getDisplayName() + " updating length from " + oldLength + " to " + length);
            if(neighbour){
                length = srcblk->getLengthMm();
                adj->setLength(length);
                ro->setLength(length);
                //Also if neighbour we need to update the cost of the routes via it to reflect the new metric 02/20/2011
                QVector<Routes*>* neighbourRoute = getNextRoutes(srcblk);
                //neighbourRoutes, contains all the routes that have been advertised by the neighbour that will need to have their metric updated to reflect the change.
                for(int i = 0; i<neighbourRoute->size(); i++){
                    Routes* nRo = neighbourRoute->at(i);
                    //Need to remove old metric to the neigbour, then add the new one on
                    float updateLength = nRo->getLength();
                    updateLength = (updateLength-oldLength)+length;
                    if(enableUpdateRouteLogging)
                        log->info("From " + this->getDisplayName() + " update metric for route " + nRo->getDestBlock()->getDisplayName() + " from " + QString("%1").arg(nRo->getLength()) + " to " + QString("%1").arg(updateLength));
                    nRo->setLength(updateLength);
#if 1 // TODO: getThroughPathDestinationBySource is a member of ThroughPaths
                    QVector<Block*>* messageRecipients = getThroughPathDestinationBySource(srcblk);
                    RoutingPacket* newUpdate = new RoutingPacket(UPDATE, nRo->getDestBlock(), -1, -1, updateLength+block->getLengthMm(), -1, getNextPacketID());
                    updateRoutesToNeighbours(messageRecipients, nRo, newUpdate);
#endif
                }
            } else {
                //This can cause a loop, if the layout is in a loop, so we send out the same packetID.
//                QVector<Block*>* messageRecipients = getThroughPathSourceByDestination(srcblk);
//                RoutingPacket* newUpdate = new RoutingPacket(UPDATE, updateBlock, -1, -1, length+block->getLengthMm(), -1, update->getPacketId());
//                updateRoutesToNeighbours(messageRecipients, ro, newUpdate);
            }
            length=length+metric;
        } else {
            length = -1;
        }
    }

    if (packetmetric!=-1){
        //Metric is added at source
        //Keep a reference of the old metric.
        int oldmetric = ro->getMetric();
        if (oldmetric!=packetmetric){
            ro->setMetric(packetmetric);
            if(enableUpdateRouteLogging)
                log->info("From " + this->getDisplayName() + " updating metric from " + oldmetric + " to " + packetmetric);
            //if the metric update is for a neighbour then we will go directly to the neighbour for the value, rather than trust what is in the message at this stage.
            if(neighbour){
                packetmetric = src->getBlockMetric();
                adj->setMetric(packetmetric);
                ro->setMetric(packetmetric);
                //Also if neighbour we need to update the cost of the routes via it to reflect the new metric 02/20/2011
                QVector<Routes*>* neighbourRoute = getNextRoutes(srcblk);
                //neighbourRoutes, contains all the routes that have been advertised by the neighbour that will need to have their metric updated to reflect the change.
                for(int i = 0; i<neighbourRoute->size(); i++){
                    Routes* nRo = neighbourRoute->at(i);
                    //Need to remove old metric to the neigbour, then add the new one on
                    int updatemet = nRo->getMetric();
                    updatemet = (updatemet-oldmetric)+packetmetric;
                    if(enableUpdateRouteLogging)
                        log->info("From " + this->getDisplayName() + " update metric for route " + nRo->getDestBlock()->getDisplayName() + " from " + QString("%1").arg(nRo->getMetric()) + " to " + QString("%1").arg(updatemet));
                    nRo->setMetric(updatemet);
//                    QVector<Block*>* messageRecipients = getThroughPathDestinationBySource(srcblk);
//                    RoutingPacket* newUpdate = new RoutingPacket(UPDATE, nRo->getDestBlock(), -1, updatemet+metric, -1, -1, getNextPacketID());
//                    updateRoutesToNeighbours(messageRecipients, nRo, newUpdate);

                }
            } else {
                //This can cause a loop, if the layout is in a loop, so we send out the same packetID.
//                QVector<Block*>* messageRecipients = getThroughPathSourceByDestination(srcblk);
//                RoutingPacket* newUpdate = new RoutingPacket(UPDATE, updateBlock, -1, packetmetric+metric,-1, -1, update->getPacketId());
//                updateRoutesToNeighbours(messageRecipients, ro, newUpdate);
            }
            packetmetric=packetmetric+metric;
            //Think we need a list of routes that originate from this source neighbour
        } else {
            //No point in forwarding on the update if the metric hasn't changed
            packetmetric = -1;
        //Potentially when we do this we need to update all the routes that go via this block, not just this route.
        }
    }
    if (blockstate!=-1){
        //We will update all the destination blocks with the new state, it
        //saves re-firing off new updates block status
        bool stateUpdated= false;
        QVector<Routes*>* rtr = getDestRoutes(updateBlock);
        for (int i = 0; i<rtr->size(); i++){
            if (rtr->at(i)->getState()!=blockstate){
                stateUpdated = true;
                rtr->at(i)->stateChange();
            }
        }
        if (stateUpdated) {
            RoutingPacket* newUpdate = new RoutingPacket(UPDATE, updateBlock, -1, -1, -1, blockstate, getNextPacketID());
            firePropertyChange("routing", QVariant(), VPtr<RoutingPacket>::asQVariant(newUpdate));
        }
    }

    //We need to expand on this so that any update to routing metric is propergated correctly
    if((packetmetric!=-1)||(hopCount!=-1) || length!=-1){
        //We only want to send the update on to neighbours that we have advertised the route to.
//        QVector<Block*>* messageRecipients = getThroughPathSourceByDestination(srcblk);
//        RoutingPacket* newUpdate = new RoutingPacket(UPDATE, updateBlock, hopCount, packetmetric, length, blockstate, update->getPacketId());
//        updateRoutesToNeighbours(messageRecipients, ro, newUpdate);
    }
    //Was just pass on hop count
}

void LayoutBlock::updateRoutesToNeighbours(QVector<Block*>* messageRecipients, Routes* ro, RoutingPacket* update){
    for (int i = 0; i<messageRecipients->size(); i++){
        Adjacencies* adj = getAdjacency(messageRecipients->at(i));
        if(adj->advertiseRouteToNeighbour(ro)){
            adj->addRouteAdvertisedToNeighbour(ro);
            //LayoutBlock* recipient = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(messageRecipients->at(i));
            LayoutBlock* recipient = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(messageRecipients->at(i));
            if (recipient!=NULL)
                recipient->updateRoutingInfo(this, update);
        }
    }
}

Routes* LayoutBlock::getBestRoute(Block* dest){
    //int bestHopCount = 255;
    int bestMetric = 965000;
    int bestIndex = -1;
    QVector<Routes*>* destRoutes = getDestRoutes(dest);
    for (int i = 0; i<destRoutes->size(); i++){
        if(destRoutes->at(i)->getMetric()<bestMetric){
            bestMetric = destRoutes->at(i)->getMetric();
            bestIndex=i;
        }
    }
    if (bestIndex==-1)
        return NULL;
    return destRoutes->at(bestIndex);
}

void LayoutBlock::addRouteToNeighbours(Routes* ro){
    if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " Add route to neighbour ");
    Block* nextHop = ro->getNextBlock();
    QVector<LayoutBlock*>* validFromPath = new QVector<LayoutBlock*>();
    if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " new block " + nextHop->getDisplayName());
    for(int i= 0; i<throughPaths->size(); i++){
        LayoutBlock* validBlock=NULL;
        if(enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " A through routes " + throughPaths->at(i)->getSourceBlock()->getDisplayName() + " " + throughPaths->at(i)->getDestinationBlock()->getDisplayName());
        /*As the through paths include each possible path, ie 2 > 3 and 3 > 2
        as seperate entries then we only need to forward the new route to those
        source blocks that have a desination of the next hop*/
        if (throughPaths->at(i)->getDestinationBlock()==nextHop){
            if (getAdjacency(throughPaths->at(i)->getSourceBlock())->isMutual()){
                //validBlock = InstanceManager::layoutBlockManagerInstance().getLayoutBlock(throughPaths->at(i)->getSourceBlock());
                validBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(throughPaths->at(i)->getSourceBlock());
            }
        }
        //only need to add it the once.  Not sure if the contains is required.
        if ((validBlock!=NULL) && (!validFromPath->contains(validBlock)))
            validFromPath->append(validBlock);
    }
    if(enableAddRouteLogging){
        log->info("From " + this->getDisplayName() + " ===== valid from size path " + QString("%1").arg(validFromPath->size()) + " ==== (addroutetoneigh)");
        log->info(nextHop->getDisplayName());
    }
    RoutingPacket* update = new RoutingPacket(ADDITION, ro->getDestBlock(), ro->getHopCount()+1, ro->getMetric()+metric, (ro->getLength()+getBlock()->getLengthMm()), -1, getNextPacketID());
    for(int i = 0; i<validFromPath->size(); i++){
        Adjacencies* adj = getAdjacency(validFromPath->at(i)->getBlock());
        if(adj->advertiseRouteToNeighbour(ro)){
            if(enableAddRouteLogging)
                log->info("From " + this->getDisplayName() + " Sending update to " + validFromPath->at(i)->getDisplayName() + " As this has a better hop count or metric");
            adj->addRouteAdvertisedToNeighbour(ro);
            validFromPath->at(i)->addRouteFromNeighbour(this, update);
        }
    }
}

void LayoutBlock::addRouteFromNeighbour(LayoutBlock* src, RoutingPacket* update)
{
    if(enableAddRouteLogging){
        log->info("From " + this->getDisplayName() + " packet to be added from neighbour " + src->getDisplayName());
        log->info("From " + this->getDisplayName() + " src: " + src->getDisplayName() + " block: " + update->getBlock()->getDisplayName() + " hopCount " + QString("%1").arg(update->getHopCount()) + " metric: " + QString("%1").arg(update->getMetric()) + " status: " + QString("%1").arg(update->getBlockState()) + " packetID: " + QString("%1").arg(update->getPacketId()));
    }
    //InstanceManager::layoutBlockManagerInstance().setLastRoutingChange();
    ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->setLastRoutingChange();
    Block* destBlock = update->getBlock();
    Block* srcblk = src->getBlock();
    if(destBlock==this->getBlock()){
        if(enableAddRouteLogging)
            log->info("Reject packet update as it is to a route advertised by our selves");
        return;
    }

    Adjacencies* adj = getAdjacency(srcblk);
    if(adj==NULL){
        if(enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " packet is from a src that is not registered " + srcblk->getDisplayName());
        //If the packet is from a src that is not registered as a neighbor
        //Then we will simply reject it.
        return;
    } else if (adj->getPacketFlow()==TXONLY){
        if(enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " packet is from a src " + src->getDisplayName() + " that is registered as one that we should be transmitting to only");
        // we should only be transmitting routes to this neighbour not receiving them
        return;
    }
    int hopCount = update->getHopCount();
    int updatemetric = update->getMetric();
    float length = update->getLength();

    if (hopCount>255){
        if(enableAddRouteLogging)
            log->info("From " + this->getDisplayName() + " hop count exceeded " + destBlock->getDisplayName());
        return;
    }

    for (int i = 0; i<routes->size(); i++){
        Routes* ro = routes->at(i);
        if((ro->getNextBlock()==srcblk) && ro->getDestBlock()==destBlock){
            if(enableAddRouteLogging)
                log->info("From " + this->getDisplayName() + " Route is already configured");
            return;
        }
    }
    if(enableAddRouteLogging)
        log->info("From " + this->getDisplayName() + " We should be adding route " + destBlock->getDisplayName());
    //We need to propergate out the routes that we have added to our neighbour
    int direction = adj->getDirection();
    Routes* route = new Routes(destBlock, srcblk, hopCount, direction, updatemetric, length, this);
    routes->append(route);
    //Need to propergate the route down to our neighbours
    addRouteToNeighbours(route);
}
/* this should look after removal of a specific next hop from our neighbour*/

/**
* Gets the direction of travel to our neighbouring block->
*/
/*public*/ int LayoutBlock::getNeighbourDirection(LayoutBlock* neigh){
    if(neigh==NULL)
        return Path::NONE;
    Block* neighbourBlock = neigh->getBlock();
    return getNeighbourDirection(neighbourBlock);
}

/*public*/ int LayoutBlock::getNeighbourDirection(Block* neighbourBlock){
    for(int i = 0; i<neighbours->size(); i++){
        if (neighbours->at(i)->getBlock()==neighbourBlock)
            return neighbours->at(i)->getDirection();
    }
    return Path::NONE;
}

Adjacencies* LayoutBlock::getAdjacency(Block* blk)
{
 for(int i = 0; i<neighbours->size(); i++)
 {
  if(neighbours->at(i)->getBlock() == blk)
  {
   return neighbours->at(i);
  }
 }
 return NULL;
}
#if 0

/*private*/ static class RoutingPacket{
    int packetType;
    Block* block;
    int hopCount = -1;
    int packetMetric = -1;
    int blockstate = -1;
    float length = -1;
    int packetRef = -1;

    RoutingPacket(int packetType, Block* blk, int hopCount, int packetMetric, float length, int blockstate, int packetRef)
    {
    this->packetType = packetType;
    this->hopCount = hopCount;
    this->packetMetric = packetMetric;
    this->blockstate = blockstate;
    this->packetRef = packetRef;
    this->length = length;
    }

    int getPacketType() { return packetType; }

    Block* getBlock() { return block; }

    int getHopCount() { return hopCount; }

    int getMetric() { return packetMetric; }

    int getBlockState() { return blockstate; }

    float getLength() { return length; }

    int getPacketId() { return packetRef; }

}
#endif
/**
* Get the number of neighbour blocks attached to this block
*/
/*public*/ int LayoutBlock::getNumberOfNeighbours(){
   return neighbours->size();
}

/**
* Get the neighbouring block at index i
*/
/*public*/ Block* LayoutBlock::getNeighbourAtIndex(int i){
    return neighbours->at(i)->getBlock();
}

/**
* Get the direction of travel to neighbouring block at index i
*/
/*public*/ int LayoutBlock::getNeighbourDirection(int i){
    return neighbours->at(i)->getDirection();
}

/**
* Get the metric/cost to neighbouring block at index i
*/
/*public*/ int LayoutBlock::getNeighbourMetric(int i){
    return neighbours->at(i)->getMetric();
}
#if 1
/**
* Get the flow of traffic to and from neighbouring block at index i
* RXTX - Means Traffic can flow both ways between the blocks
* RXONLY - Means we can only recieve traffic from our neighbour, we can not send traffic to it
* TXONLY - Means we do not recieve traffic from our neighbour, but can send traffic to it.
*/
/*public*/ QString LayoutBlock::getNeighbourPacketFlowAsString(int i){
    return decodePacketFlow(neighbours->at(i)->getPacketFlow());
}

/**
* Is our neighbouring block at index i a mutual neighbour, ie both blocks have
* each other registered as neighbours and are exchaning information.
*/
/*public*/ bool LayoutBlock::isNeighbourMutual(int i){
    return neighbours->at(i)->isMutual();
}
#endif
int LayoutBlock::getNeighbourIndex(Adjacencies* adj){
    for(int i =0; i<neighbours->size(); i++){
        if (neighbours->at(i)==adj)
            return i;
    }
    return -1;
}


///*private*/ class Adjacencies{


Adjacencies::Adjacencies(Block* block, int dir, int packetFlow, LayoutBlock* thisBlock)
{
 log = new Logger("Adjacencies");
 this->thisBlock = thisBlock;
 this->packetFlow = RXTX;
 metric = 100;

 mutualAdjacency=false;

 adjDestRoutes = new QHash<Block*, Routes*>();
 actedUponUpdates = new QVector<int>();

 adjBlock = block;
 direction = dir;
 adjLayoutBlock = NULL;

 this->packetFlow = packetFlow;
}

Block* Adjacencies::getBlock() { return adjBlock; }

LayoutBlock* Adjacencies::getLayoutBlock() { return adjLayoutBlock; }

int Adjacencies::getDirection() { return direction; }

//If a set true on mutual, then we could go through the list of what to send out to neighbour
void Adjacencies::setMutual(bool mut){
    if (mut==mutualAdjacency)//No change will exit
        return;
    mutualAdjacency=mut;
    if (mutualAdjacency)
    {
     adjLayoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(adjBlock);
    }
}

bool Adjacencies::isMutual() { return mutualAdjacency; }

    /*LayoutBlock getLayoutBlock(){
        return adjLayoutBlock;
    }*/

int Adjacencies::getPacketFlow() { return packetFlow; }

void Adjacencies::setPacketFlow(int flow) {

    if(flow!=packetFlow){
        int oldFlow = packetFlow;
        packetFlow=flow;
     thisBlock->firePropertyChange("neighbourpacketflow", oldFlow, packetFlow);
    }

}


//The metric could just be read directly from the neighbour as we have no need to specifically keep a copy of it here this is here just to fire off the change
void Adjacencies::setMetric(int /*met*/)
{
 thisBlock->firePropertyChange("neighbourmetric", QVariant(), thisBlock->getNeighbourIndex(this));
}

int Adjacencies::getMetric()
{
 if(adjLayoutBlock!=NULL)
  return adjLayoutBlock->getBlockMetric();
 adjLayoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(adjBlock);
 if (adjLayoutBlock!=NULL)
  return adjLayoutBlock->getBlockMetric();
 if(log->isDebugEnabled())
  log->debug("Layout Block " + adjBlock->getDisplayName() + " returned as NULL");

 return -1;
}
void Adjacencies::setLength(float /*len*/)
{
    thisBlock->firePropertyChange("neighbourlength", QVariant(), thisBlock->getNeighbourIndex(this));
}

float Adjacencies::getLength() {
    if(adjLayoutBlock!=NULL)
        return adjLayoutBlock->getBlock()->getLengthMm();
    adjLayoutBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(adjBlock);
    if (adjLayoutBlock!=NULL)
        return adjLayoutBlock->getBlock()->getLengthMm();
    if(log->isDebugEnabled())
        log->debug("Layout Block " + adjBlock->getDisplayName() + " returned as NULL");

    return -1;
}

void Adjacencies::removeRouteAdvertisedToNeighbour(Routes* removeRoute){
    Block* dest = removeRoute->getDestBlock();

    if(adjDestRoutes->value(dest)==removeRoute){
        adjDestRoutes->remove(dest);
    }
}

void Adjacencies::removeRouteAdvertisedToNeighbour(Block* block){
    adjDestRoutes->remove(block);
}

void Adjacencies::addRouteAdvertisedToNeighbour(Routes* addedRoute){
    adjDestRoutes->insert(addedRoute->getDestBlock(), addedRoute);
}

bool Adjacencies::advertiseRouteToNeighbour(Routes* routeToAdd){
//Just wonder if this should forward on the new packet to the neighbour?
    Block* dest = routeToAdd->getDestBlock();
    if(!adjDestRoutes->contains(dest)){
        //log->info("We are not currently advertising a route to the destination to this neighbour");
        return true;
    }
    if (routeToAdd->getHopCount()>255){
        log->debug("Hop count is greater than 255 we will therefore do nothing with this route");
        return false;
    }
    Routes* existingRoute = adjDestRoutes->value(dest);
    if(existingRoute==routeToAdd){
        //We return true as the metric might have changed
        return true;
    }
    if(existingRoute->getMetric()>routeToAdd->getMetric()){
        return true;
    }
    return false;
}

bool Adjacencies::updatePacketActedUpon(int packetID){
    return actedUponUpdates->contains(packetID);
}

void Adjacencies::addPacketRecievedFromNeighbour(int packetID){
    actedUponUpdates->append(packetID);
}

void Adjacencies::dispose(){
    adjBlock =NULL;
    adjLayoutBlock = NULL;
    mutualAdjacency=false;
    adjDestRoutes = NULL;
    actedUponUpdates = NULL;
}
//}; // end Adjacencies

/**
* Get the number of routes that the block has registered.
*/
/*public*/ int LayoutBlock::getNumberOfRoutes(){
   return routes->size();
}

/**
* Get the direction of route i.
*/
/*public*/ int LayoutBlock::getRouteDirectionAtIndex(int i){
    return routes->at(i)->getDirection();
}

/**
* Get the destination block at route i
*/
/*public*/ Block* LayoutBlock::getRouteDestBlockAtIndex(int i){
    return routes->at(i)->getDestBlock();
}

/**
* Get the next block at route i
*/
/*public*/ Block* LayoutBlock::getRouteNextBlockAtIndex(int i){
    return routes->at(i)->getNextBlock();
}

/**
* Get the hop count of route i.<br>
* The Hop count is the number of other blocks that we traverse to get to the destination
*/
/*public*/ int LayoutBlock::getRouteHopCountAtIndex(int i){
    return routes->at(i)->getHopCount();
}

/**
* Get the length of route i.<br>
* The length is the combined length of all the blocks that we traverse to get to the destination
*/
/*public*/ float LayoutBlock::getRouteLengthAtIndex(int i){
    return routes->at(i)->getLength();
}

/**
* Get the metric/cost at route i
*/
/*public*/ int LayoutBlock::getRouteMetric(int i){
    return routes->at(i)->getMetric();
}

/**
* Gets the state (Occupied, unoccupied) of the destination layout block at index i
*/
/*public*/ int LayoutBlock::getRouteState(int i){
    return routes->at(i)->getState();
}

/**
* Is the route to the destination potentially valid from our block->
*/
/*public*/ bool LayoutBlock::getRouteValid(int i){
    return routes->at(i)->isRouteCurrentlyValid();
}

/**
* Gets the state of the destination layout block at index i as a string
*/
/*public*/ QString LayoutBlock::getRouteStateAsString(int i)
{
 int state=routes->at(i)->getState();
 switch (state){
     case OCCUPIED: return "Occupied";
     case RESERVED: return "Reserved";
     case EMPTY: return "Free";
     default: return "Unknown";
 }
}

int LayoutBlock::getRouteIndex(Routes* r){
    for(int i =0; i<routes->size(); i++){
        if (routes->at(i)==r)
            return i;
    }
    return -1;
}

/**
* Returns the number of layout blocks to our desintation block going from the
* next directly connected block->  If the destination block and nextblock are
* the same and the block is also registered as a neighbour then 1 is returned.
* If no valid route to the destination block can be found via the next block
* then -1 is returned.  If more than one route exists to the destination then
* the route with the lowest count is returned.
*/
/*public*/ int LayoutBlock::getBlockHopCount(Block* destination, Block* nextBlock){
    if((destination==nextBlock) && (isValidNeighbour(nextBlock)))
        return 1;
    for (int i = 0; i<routes->size();i++){
        if (routes->at(i)->getDestBlock()==destination){
            if(routes->at(i)->getNextBlock()==nextBlock)
                return routes->at(i)->getHopCount();
        }
    }
    return -1;
}

/**
* Returns the metric to our desintation block going from the
* next directly connected block->  If the destination block and nextblock are
* the same and the block is also registered as a neighbour then 1 is returned.
* If no valid route to the destination block can be found via the next block
* then -1 is returned.  If more than one route exists to the destination then
* the route with the lowest count is returned.
*/
/*public*/ int LayoutBlock::getBlockMetric(Block* destination, Block* nextBlock){
    if((destination==nextBlock) && (isValidNeighbour(nextBlock)))
        return 1;
    for (int i = 0; i<routes->size();i++){
        if (routes->at(i)->getDestBlock()==destination){
            if(routes->at(i)->getNextBlock()==nextBlock)
                return routes->at(i)->getMetric();
        }
    }
    return -1;
}

/**
* Returns the distance to our desintation block going from the
* next directly connected block->  If the destination block and nextblock are
* the same and the block is also registered as a neighbour then 1 is returned.
* If no valid route to the destination block can be found via the next block
* then -1 is returned.  If more than one route exists to the destination then
* the route with the lowest count is returned.
*/
/*public*/ float LayoutBlock::getBlockLength(Block* destination, Block* nextBlock){
    if((destination==nextBlock) && (isValidNeighbour(nextBlock)))
        return 1;
    for (int i = 0; i<routes->size();i++){
        if (routes->at(i)->getDestBlock()==destination){
            if(routes->at(i)->getNextBlock()==nextBlock)
                return routes->at(i)->getLength();
        }
    }
    return -1;
}

//This needs a propertychange listener adding
///*private*/ class Routes implements java.beans.PropertyChangeListener{
/*public*/ Routes::Routes(Block* dstBlock, Block* nxtBlock, int hop, int dir, int met, float len, LayoutBlock* block)
{
 this->block = block;
 log = new Logger("Routes");
 miscflags =0x00;
 validCurrentRoute=false;

 destBlock = dstBlock;
 nextBlock = nxtBlock;
 hopCount = hop;
 direction = dir;
 routeMetric = met;
 length = len;
 validCurrentRoute = block->checkIsRouteOnValidThroughPath(this);
 firePropertyChange("length", QVariant(), QVariant());
//    destBlock->addPropertyChangeListener(this);
// connect(destBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
// connect(destBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));

}

/*public*/ void Routes::on_propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("state"))
 {
  stateChange();
 }
}

/*public*/ Block* Routes::getDestBlock(){ return destBlock; }

/*public*/ Block* Routes::getNextBlock() { return nextBlock; }

/*public*/ int Routes::getHopCount() { return hopCount; }

/*public*/ int Routes::getDirection() { return direction; }
/*public*/ int Routes::getMetric() { return routeMetric; }
/*public*/ float Routes::getLength() { return length; }

/*public*/ void Routes::setMetric(int met)
{
 if(met==routeMetric)
     return;
 routeMetric=met;
 firePropertyChange("metric", QVariant(), block->getRouteIndex(this));
}
/*public*/ void Routes::setHopCount(int hop)
{
    if(hopCount==hop)
        return;
    hopCount = hop;
 firePropertyChange("hop", QVariant(), block->getRouteIndex(this));
}

/*public*/ void Routes::setLength(float len) {
    if(len==length)
        return;
    length=len;
 firePropertyChange("length", QVariant(), block->getRouteIndex(this));
}

//This state change is only here for the routing table view
void Routes::stateChange()
{
 firePropertyChange("state", QVariant(), block->getRouteIndex(this));
}

int Routes::getState()
{
    LayoutBlock* destLBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(destBlock);
    if (destLBlock!=NULL)
        return destLBlock->getBlockStatus();
    if(log->isDebugEnabled())
        log->debug("Layout Block " + destBlock->getDisplayName() + " returned as NULL");
    return -1;
}

void Routes::setValidCurrentRoute(bool boo){
    if (validCurrentRoute==boo)
        return;
    validCurrentRoute=boo;
 firePropertyChange("valid", QVariant(), block->getRouteIndex(this));
}

bool Routes::isRouteCurrentlyValid() { return validCurrentRoute; }

//Misc flags is not used in general routing, but is used for determining route removals
void Routes::setMiscFlags(int f) { miscflags = f; }

int Routes::getMiscFlags() { return miscflags; }

void Routes::firePropertyChange(QString propertyName, QVariant oldVal, QVariant newVal)
{
 emit propertyChange(new PropertyChangeEvent((QObject*)this, propertyName, oldVal, newVal));

}

//}; // end class Routes

/**
* Returns the number of valid through paths on this block->
*/
/*public*/ int LayoutBlock::getNumberOfThroughPaths()
{
 return throughPaths->size();
}

/**
* Returns the source block at index i
*/
/*public*/ Block* LayoutBlock::getThroughPathSource(int i)
{
 return throughPaths->at(i)->getSourceBlock();
}

/**
* Returns the destination block at index i
*/
/*public*/ Block* LayoutBlock::getThroughPathDestination(int i)
{
 return throughPaths->at(i)->getDestinationBlock();
}

/**
* Is the through path at index i active
*/
/*public*/ bool LayoutBlock::isThroughPathActive(int i)
{
 return throughPaths->at(i)->isPathActive();
}

///*private*/ class ThroughPaths implements java.beans.PropertyChangeListener{
ThroughPaths::ThroughPaths(Block* srcBlock, Path* srcPath, Block* destBlock, Path* dstPath, LayoutBlock*parent)
{
 log = new Logger("ThroughPaths");
  _turnouts = QHash<Turnout*, int>();
 sourceBlock = srcBlock;
 destinationBlock = destBlock;
 sourcePath = srcPath;
 destinationPath=dstPath;
 this->parent = parent;
}

Block* ThroughPaths::getSourceBlock(){
    return sourceBlock;
}

Block* ThroughPaths::getDestinationBlock(){
    return destinationBlock;
}

Path* ThroughPaths::getSourcePath(){
    return sourcePath;
}

Path* ThroughPaths::getDestinationPath(){
    return destinationPath;
}

bool ThroughPaths::isPathActive(){
    return pathActive;
}

void ThroughPaths::setTurnoutList(QList<LayoutTrackExpectedState<LayoutTurnout*>*> turnouts)
{
 if (!_turnouts.isEmpty()) {
     QSet<Turnout*> en = _turnouts.keys().toSet();
     for (Turnout* listTurnout : en) {
         listTurnout->removePropertyChangeListener((PropertyChangeListener*)this);
      //disconnect(listTurnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 //If we have no turnouts in this path, then this path is always active
 if (turnouts.size() == 0) {
     pathActive = true;
     parent->setRoutesValid(sourceBlock, true);
     parent->setRoutesValid(destinationBlock, true);
     return;
 }
 _turnouts = QHash<Turnout*, int>(/*turnouts.size()*/);
 for (int i = 0; i < turnouts.size(); i++)
 {
     if (qobject_cast<LayoutSlip*>(turnouts.at(i)->getObject())) {
         int slipState = turnouts.at(i)->getExpectedState();
         LayoutSlip* ls = (LayoutSlip*) turnouts.at(i)->getObject();
         int taState = ls->getTurnoutState(slipState);
         _turnouts.insert(ls->getTurnout(), taState);
         ls->getTurnout()->addPropertyChangeListener((PropertyChangeListener*)this, ls->getTurnoutName(), "Layout Block Routing");
         //connect(ls->getTurnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         int tbState = ls->getTurnoutBState(slipState);
         _turnouts.insert(ls->getTurnoutB(), tbState);
         ls->getTurnoutB()->addPropertyChangeListener((PropertyChangeListener*)this, ls->getTurnoutBName(), "Layout Block Routing");
         //connect(ls->getTurnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     } else {
         LayoutTurnout* lt = turnouts.at(i)->getObject();
         if (lt->getTurnout() != nullptr) {
             _turnouts.insert(lt->getTurnout(), turnouts.at(i)->getExpectedState());
             lt->getTurnout()->addPropertyChangeListener((PropertyChangeListener*)this, lt->getTurnoutName(), "Layout Block Routing");
             //connect(lt->getTurnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         } else {
             log->error(tr("%1 has no physical turnout allocated, block = %2").arg(lt->getName()).arg(parent->block->getDisplayName()));
         }
     }
 }
}

/*public*/ QHash<Turnout*, int> ThroughPaths::getTurnoutList(){
    return _turnouts;
}

/*public*/ void ThroughPaths::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("KnownState"))
 {
  Turnout* srcTurnout = (Turnout*) e->getSource();
  int newVal =  e->getNewValue().toInt();
  int values = _turnouts.value(srcTurnout);
  bool allset=false;
  pathActive=false;
  if (newVal==values)
  {
   allset=true;
   if (_turnouts.size()>1)
   {
    //Enumeration<Turnout> en = _turnouts->keys();
    QHashIterator<Turnout*, int> en(_turnouts);
    while (en.hasNext())
    {
     en.next();
     Turnout* listTurnout = en.key();
     if (srcTurnout!=listTurnout)
     {
      int state = listTurnout->getState();
      int required = _turnouts.value(listTurnout);
      if (state!=required)
      {
       allset=false;
      }
     }
    }
   }
  }
  parent->updateActiveThroughPaths(this, allset);
  pathActive=allset;
 }
}
void ThroughPaths::handlePropertyChange(QString propertyName, Turnout* source, int newVal)
{
 if (propertyName==("KnownState"))
 {
  Turnout* srcTurnout = (Turnout*) source;
  //int newVal =  e->getNewValue().toInt();
  int values = _turnouts.value(srcTurnout);
  bool allset=false;
  pathActive=false;
  if (newVal==values)
  {
   allset=true;
   if (_turnouts.size()>1)
   {
    //Enumeration<Turnout> en = _turnouts->keys();
    QHashIterator<Turnout*, int> en(_turnouts);
    while (en.hasNext())
    {
     en.next();
     Turnout* listTurnout = en.key();
     if (srcTurnout!=listTurnout)
     {
      int state = listTurnout->getState();
      int required = _turnouts.value(listTurnout);
      if (state!=required)
      {
       allset=false;
      }
     }
    }
   }
  }
  parent->updateActiveThroughPaths(this, allset);
  pathActive=allset;
 }
}

//}; // end ThroughPaths

QVector<Block*>* LayoutBlock::getThroughPathSourceByDestination(Block* dest){
    QVector<Block*>* a = new QVector<Block*>();
    for(int i = 0; i<throughPaths->size(); i++){
        if (throughPaths->at(i)->getDestinationBlock()==dest)
            a->append(throughPaths->at(i)->getSourceBlock());
    }
    return a;
}

QVector<Block*>* LayoutBlock::getThroughPathDestinationBySource(Block* source)
{
 QVector<Block*>* a = new QVector<Block*>();
 for(int i = 0; i<throughPaths->size(); i++){
     if (throughPaths->at(i)->getSourceBlock()==source)
         a->append(throughPaths->at(i)->getDestinationBlock());
 }
 return a;
}
//When a route is created this will check to see if the through path that this
//route relates to is active
bool LayoutBlock::checkIsRouteOnValidThroughPath(Routes* r)
{
 for(int i = 0; i<throughPaths->size(); i++)
 {
  ThroughPaths* t = throughPaths->at(i);
  if (t->isPathActive()){
      if(t->getDestinationBlock()==r->getNextBlock())
          return true;
      if(t->getSourceBlock()==r->getNextBlock())
          return true;
  }
 }
 return false;
}

//A procedure that will go through all the routes and refresh the valid flag
/*public*/ void LayoutBlock::refreshValidRoutes()
{
 for(int i= 0; i<throughPaths->size(); i++)
 {
  ThroughPaths* t = throughPaths->at(i);
  setRoutesValid(t->getDestinationBlock(), t->isPathActive());
  setRoutesValid(t->getSourceBlock(), t->isPathActive());
  //firePropertyChange("path", NULL, i);
  emit propertyChange(new PropertyChangeEvent((QObject*)this, "path", QVariant(), i));
 }
}


void LayoutBlock::updateActiveThroughPaths(ThroughPaths* tp, bool active)
{
 if(enableUpdateRouteLogging)
  log->info("We have been notified that a through path has changed state");
 if (activePaths==NULL)
 {
  activePaths = new QVector<ThroughPaths*>();
 }
 if (active)
 {
  activePaths->append(tp);
  setRoutesValid(tp->getSourceBlock(), active);
  setRoutesValid(tp->getDestinationBlock(), active);
 }
 else
 {
  //We need to check if either our source or des is in use by another path.
  activePaths->remove(activePaths->indexOf( tp));
  bool SourceInUse = false;
  bool DestinationInUse = false;
  for (int i = 0; i<activePaths->size(); i++)
  {
   Block* testSour = activePaths->at(i)->getSourceBlock();
   Block* testDest = activePaths->at(i)->getDestinationBlock();
   if((testSour==tp->getSourceBlock()) || (testDest==tp->getSourceBlock()))
    SourceInUse=true;
   if((testSour==tp->getDestinationBlock()) || (testDest==tp->getDestinationBlock()))
    DestinationInUse = true;
  }
  if(!SourceInUse)
   setRoutesValid(tp->getSourceBlock(), active);
  if(!DestinationInUse)
   setRoutesValid(tp->getDestinationBlock(), active);
 }
 for (int i = 0; i<throughPaths->size(); i++)
 {
  //This is processed simply for the throughpath table.
  if (tp==throughPaths->at(i))
   //firePropertyChange("path", NULL, i);
   emit propertyChange(new PropertyChangeEvent((QObject*)this, "path", QVariant(), i));
 }
}

//Sets the valid flag for routes that are on a valid through path.
void LayoutBlock::setRoutesValid(Block* nxtHopActive, bool state)
{
 QVector<Routes*>* rtr = getRouteByNeighbour(nxtHopActive);
 for (int i = 0; i<rtr->size(); i++)
 {
  rtr->at(i)->setValidCurrentRoute(state);
 }
}

const QIcon* LayoutBlock::getColourIcon(QColor color)
{
 Q_ASSERT(color.isValid());
 int ICON_DIMENSION = 10;
// BufferedImage image = new BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
// BufferedImage.TYPE_INT_RGB);
 QImage resultImage = QImage(ICON_DIMENSION,ICON_DIMENSION,QImage::Format_ARGB32_Premultiplied);

// Graphics g = image.getGraphics();
 QPainter painter(&resultImage);
//   // set completely transparent
// g.setColor(color);
// g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);
 QBrush brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
//eRect.adjust(0, -3.0, 0, 0);
 painter.fillRect(resultImage.rect(), brBkgnd);
 painter.end();
// ImageIcon icon = new ImageIcon(image);
 QIcon* icon = new QIcon(QPixmap::fromImage(resultImage));
 return icon;
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger->getLogger(LayoutBlock.class.getName());

//}


/*protected*/ void LayoutBlockEditAction::initPanels() {
    BlockEditAction::initPanels();
    BeanItemPanel* ld = layoutDetails();
    if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()) {
        blockRoutingDetails();
    }
    setSelectedComponent(ld);
}


BeanItemPanel* LayoutBlockEditAction::layoutDetails()
{
    BeanItemPanel* layout = new BeanItemPanel();
    layout->setName(tr("Layout Editor"));

    LayoutEditor::setupComboBox(lb->memoryComboBox, false, true, false);

    layout->addItem(new BeanEditItem(new JLabel(QString::number(lb->useCount)), tr("Current Use Count"), QString()));
    layout->addItem(new BeanEditItem(lb->memoryComboBox, tr("Memory"),
            tr("Enter name (system or user) of Memory Variable (optional).")));

    lb->senseBox->clear();
    lb->senseBox->addItem(tr("Active"));
    lb->senseActiveIndex = 0;
    lb->senseBox->addItem(tr("Inactive"));
    lb->senseInactiveIndex = 1;

    layout->addItem(new BeanEditItem(lb->senseBox, tr("Occupied Sense"), tr("Select the occupancy sensor state when the block is occupied.")));

    lb->trackColorChooser = new JColorChooser(lb->blockTrackColor);
    lb->trackColorChooser->setPreviewPanel(new JPanel()); // remove the preview panel
    QVector<AbstractColorChooserPanel*> trackColorPanels = {new SplitButtonColorChooserPanel()};
    lb->trackColorChooser->setChooserPanels(&trackColorPanels);
    layout->addItem(new BeanEditItem(lb->trackColorChooser, tr("Track Color"), tr("Select the track color when this block is unoccupied.")));

    lb->occupiedColorChooser = new JColorChooser(lb->blockOccupiedColor);
    lb->occupiedColorChooser->setPreviewPanel(new JPanel()); // remove the preview panel
    QVector<AbstractColorChooserPanel*> occupiedColorPanels = {new SplitButtonColorChooserPanel()};
    lb->occupiedColorChooser->setChooserPanels(&occupiedColorPanels);
    layout->addItem(new BeanEditItem(lb->occupiedColorChooser, tr("Occupied Track Color:"), tr("Select the track color when this block is occupied.")));

    lb->extraColorChooser = new JColorChooser(lb->blockExtraColor);
    lb->extraColorChooser->setPreviewPanel(new JPanel()); // remove the preview panel
    QVector<AbstractColorChooserPanel*> extraColorPanels = {new SplitButtonColorChooserPanel()};
    lb->extraColorChooser->setChooserPanels(&extraColorPanels);
    layout->addItem(new BeanEditItem(lb->extraColorChooser, tr("Alternate Track Color:"), tr("Select the track color for unoccupied special use, e.g. allocated.")));
#if 0
    layout->setSaveItem(new AbstractAction() {
        @Override
        public void actionPerformed(ActionEvent e) {
            boolean needsRedraw = false;
            int k = senseBox.getSelectedIndex();
            int oldSense = occupiedSense;

            if (k == senseActiveIndex) {
                occupiedSense = Sensor.ACTIVE;
            } else {
                occupiedSense = Sensor.INACTIVE;
            }

            if (oldSense != occupiedSense) {
                needsRedraw = true;
            }
            //check if track color changed
            Color oldColor = blockTrackColor;
            blockTrackColor = trackColorChooser.getColor();
            if (oldColor != blockTrackColor) {
                needsRedraw = true;
                JmriColorChooser.addRecentColor(blockTrackColor);
            }
            //check if occupied color changed
            oldColor = blockOccupiedColor;
            blockOccupiedColor = occupiedColorChooser.getColor();
            if (oldColor != blockOccupiedColor) {
                needsRedraw = true;
                JmriColorChooser.addRecentColor(blockOccupiedColor);
            }
            //check if extra color changed
            oldColor = blockExtraColor;
            blockExtraColor = extraColorChooser.getColor();
            if (oldColor != blockExtraColor) {
                needsRedraw = true;
                JmriColorChooser.addRecentColor(blockExtraColor);
            }
            //check if Memory changed
            String newName = memoryComboBox.getSelectedItemDisplayName();
            if (newName == null) {
                newName = "";
            }
            if (!memoryName.equals(newName)) {
                //memory has changed
                setMemory(validateMemory(newName, editLayoutBlockFrame), newName);
                if (getMemory() == null) {
                    //invalid memory entered
                    memoryName = "";
                    memoryComboBox.setSelectedItem(null);
                    return;
                } else {
                    memoryComboBox.setSelectedItem(getMemory());
                    needsRedraw = true;
                }
            }

            if (needsRedraw) {
                redrawLayoutBlockPanels();
            }
        }
    });

    layout.setResetItem(new AbstractAction() {
        @Override
        public void actionPerformed(ActionEvent e) {
            memoryComboBox.setSelectedItem(getMemory());
            trackColorChooser.setColor(blockTrackColor);
            occupiedColorChooser.setColor(blockOccupiedColor);
            extraColorChooser.setColor(blockExtraColor);
            if (occupiedSense == Sensor.ACTIVE) {
                senseBox.setSelectedIndex(senseActiveIndex);
            } else {
                senseBox.setSelectedIndex(senseInactiveIndex);
            }
        }
    });
#endif
    bei.append(layout);
    return layout;
}
BeanItemPanel* LayoutBlockEditAction::blockRoutingDetails() {
    BeanItemPanel* routing = new BeanItemPanel();
    routing->setName("Routing");

    routing->addItem(new BeanEditItem(lb->metricField, "Block Metric", "set the cost for going over this block"));

    routing->addItem(new BeanEditItem(nullptr, QString(), "Set the direction of the connection to the neighbouring block"));
    lb->neighbourDir = QVector<JComboBox*>(lb->getNumberOfNeighbours());
    for (int i = 0; i < lb->getNumberOfNeighbours(); i++) {
        JComboBox* dir = new JComboBox(lb->working);
        routing->addItem(new BeanEditItem(dir, lb->getNeighbourAtIndex(i)->getDisplayName(), nullptr));
        lb->neighbourDir.append(dir);
    }
#if 0
    routing->setResetItem(new AbstractAction() {
        @Override
        public void actionPerformed(ActionEvent e) {
            metricField.setText(Integer.toString(metric));
            for (int i = 0; i < getNumberOfNeighbours(); i++) {
                JComboBox<String> dir = neighbourDir.get(i);
                Block blk = neighbours.get(i).getBlock();
                if (block.isBlockDenied(blk)) {
                    dir.setSelectedIndex(2);
                } else if (blk.isBlockDenied(block)) {
                    dir.setSelectedIndex(1);
                } else {
                    dir.setSelectedIndex(0);
                }
            }
        }
    });
#endif
//    routing->setResetItem(new RoutingSetResetItemListener(lb));
#if 0
    routing.setSaveItem(new AbstractAction() {
        @Override
        public void actionPerformed(ActionEvent e) {
            int m = Integer.parseInt(metricField.getText().trim());
            if (m != metric) {
                setBlockMetric(m);
            }
            block.setPermissiveWorking(permissiveCheck.isSelected());
            if (neighbourDir != null) {
                for (int i = 0; i < neighbourDir.size(); i++) {
                    int neigh = neighbourDir.get(i).getSelectedIndex();
                    neighbours.get(i).getBlock().removeBlockDenyList(block);
                    block.removeBlockDenyList(neighbours.get(i).getBlock());
                    switch (neigh) {
                        case 0: {
                            updateNeighbourPacketFlow(neighbours.get(i), RXTX);
                            break;
                        }

                        case 1: {
                            neighbours.get(i).getBlock().addBlockDenyList(block.getDisplayName());
                            updateNeighbourPacketFlow(neighbours.get(i), TXONLY);
                            break;
                        }

                        case 2: {
                            block.addBlockDenyList(neighbours.get(i).getBlock().getDisplayName());
                            updateNeighbourPacketFlow(neighbours.get(i), RXONLY);
                            break;
                        }

                        default: {
                            break;
                        }
                    }
                    /* switch */
                }
            }
        }
    });
#endif
    routing->setSaveItem(new RoutingSetSaveItemListener(lb));
    bei.append(routing);
    return routing;
}

/*public*/ void LayoutSetSaveItemListener::actionPerformed() {
    bool needsRedraw = false;
    int k = lb->senseBox->currentIndex();
    int oldSense = lb->occupiedSense;

    if (k == lb->senseActiveIndex) {
        lb->occupiedSense = Sensor::ACTIVE;
    } else {
        lb->occupiedSense = Sensor::INACTIVE;
    }

    if (oldSense != lb->occupiedSense) {
        needsRedraw = true;
    }
    //check if track color changed
    QColor oldColor = lb->blockTrackColor;
    lb->blockTrackColor = lb->trackColorChooser->getColor();
    if (oldColor != lb->blockTrackColor) {
        needsRedraw = true;
        JmriColorChooser::addRecentColor(lb->blockTrackColor);
    }
    //check if occupied color changed
    oldColor = lb->blockOccupiedColor;
    lb->blockOccupiedColor = lb->occupiedColorChooser->getColor();
    if (oldColor != lb->blockOccupiedColor) {
        needsRedraw = true;
        JmriColorChooser::addRecentColor(lb->blockOccupiedColor);
    }
    //check if extra color changed
    oldColor = lb->blockExtraColor;
    lb->blockExtraColor = lb->extraColorChooser->getColor();
    if (oldColor != lb->blockExtraColor) {
        needsRedraw = true;
        JmriColorChooser::addRecentColor(lb->blockExtraColor);
    }
    //check if Memory changed
    QString newName = lb->memoryComboBox->getSelectedItemDisplayName();
    if (newName == "") {
        newName = "";
    }
    if (lb->memoryName!=(newName)) {
        //memory has changed
        lb->setMemory(lb->validateMemory(newName, lb->editLayoutBlockFrame), newName);
        if (lb->getMemory() == nullptr) {
            //invalid memory entered
            lb->memoryName = "";
            lb->memoryComboBox->setSelectedItem(nullptr);
            return;
        } else {
            lb->memoryComboBox->setSelectedItem(lb->getMemory());
            needsRedraw = true;
        }
    }

    if (needsRedraw) {
        lb->redrawLayoutBlockPanels();
    }
}

/*public*/ void LayoutSetResetItemListener::actionPerformed() {
    lb->memoryComboBox->setSelectedItem(lb->getMemory());
    lb->trackColorChooser->setColor(lb->blockTrackColor);
    lb->occupiedColorChooser->setColor(lb->blockOccupiedColor);
    lb->extraColorChooser->setColor(lb->blockExtraColor);
    if (lb->occupiedSense == Sensor::ACTIVE) {
        lb->senseBox->setCurrentIndex(lb->senseActiveIndex);
    } else {
        lb->senseBox->setCurrentIndex(lb->senseInactiveIndex);
    }
}


void RoutingSetResetItemListener::actionPerformed()
{
    lb->metricField->setText(QString::number(lb->metric));
    for (int i = 0; i < lb->getNumberOfNeighbours(); i++) {
        JComboBox* dir = lb->neighbourDir.at(i);
        Block* blk = lb->neighbours->at(i)->getBlock();
        if (lb->block->isBlockDenied(blk)) {
            dir->setCurrentIndex(2);
        } else if (blk->isBlockDenied(lb->block)) {
            dir->setCurrentIndex(1);
        } else {
            dir->setCurrentIndex(0);
        }
    }
}


void RoutingSetSaveItemListener::actionPerformed()
{
 int m = (lb->metricField->text().trimmed().toInt());
 if (m != lb->metric) {
     lb->setBlockMetric(m);
 }
 lb->block->setPermissiveWorking(lb->permissiveCheck->isChecked());
 if (!lb->neighbourDir.isEmpty())
 {
     for (int i = 0; i < lb->neighbourDir.size(); i++) {
         int neigh = lb->neighbourDir.at(i)->currentIndex();
         lb->neighbours->at(i)->getBlock()->removeBlockDenyList(lb->block);
         lb->block->removeBlockDenyList(lb->neighbours->at(i)->getBlock());
         switch (neigh) {
             case 0: {
                 lb->updateNeighbourPacketFlow(lb->neighbours->at(i), lb->RXTX);
                 break;
             }

             case 1: {
                 lb->neighbours->at(i)->getBlock()->addBlockDenyList(lb->block->getDisplayName());
                 lb->updateNeighbourPacketFlow(lb->neighbours->at(i), lb->TXONLY);
                 break;
             }

             case 2: {
                 lb->block->addBlockDenyList(lb->neighbours->at(i)->getBlock()->getDisplayName());
                 lb->updateNeighbourPacketFlow(lb->neighbours->at(i), lb->RXONLY);
                 break;
             }

             default: {
                 break;
             }
         }
         /* switch */
     }
 }
}
