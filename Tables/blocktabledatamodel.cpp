#include "blocktabledatamodel.h"
#include "loggerfactory.h"
#include "signalspeedmap.h"
#include "vptr.h"
#include "reportable.h"
#include "blocktableaction.h"
#include "block.h"
#include "path.h"
#include "blockcurvaturejcombobox.h"
//#include "JComboBoxUtil.h"
#include "joptionpane.h"
#include <QVector>
#include "blockeditaction.h"
#include "imageio.h"
#include "file.h"
#include "fileutil.h"

/**
 * Data model for a Block Table.
 * Code originally within BlockTableAction.
 *
 * @author Bob Jacobsen Copyright (C) 2003, 2008
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class BlockTableDataModel extends BeanTableDataModel<Block> {



/*public*/ BlockTableDataModel::BlockTableDataModel(Manager/*<Block>*/* mgr)
 : BeanTableDataModel(){
    //super();
    setManager((AbstractManager*)mgr); // for consistency with other BeanTableModels, default BlockManager always used.
    updateNameList();
    rootPath = FileUtil::getProgramPath() + "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
    beanTypeChar = 'S'; // reuse Sensor icon for block state
    onIconPath = rootPath + beanTypeChar + "-on-s.png";
    offIconPath = rootPath + beanTypeChar + "-off-s.png";

    defaultBlockSpeedText = (tr("Use %1").arg("Global") + " " + ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getDefaultSpeed()); // first entry in drop down list
    speedList->append(defaultBlockSpeedText);
    QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
    for (int i = 0; i < _speedMap.size(); i++) {
        if (! speedList->contains(_speedMap.at(i))) {
             speedList->append(_speedMap.at(i));
        }
    }
    setLegacy(true);

    updateSensorList();
    updateReporterList();
}

//@Override
/*public*/ QString BlockTableDataModel::getValue(QString name) {
    if (name == "") {
        log->warn("requested getValue(null)");
        return "(no name)";
    }
    Block* b = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBySystemName(name);
    if (b == nullptr) {
        log->debug(tr("requested getValue(\"%1\"), Block doesn't exist").arg(name));
        return "(no Block)";
    }
    QVariant m = b->getValue();
    if (m != QVariant()) {
        if (VPtr<Reportable>::asPtr(m)) {
            return (VPtr<Reportable>::asPtr(m)->toReportString());
        }
        else {
            return m.toString();
        }
    } else {
        return "";
    }
}

//@Override
/*public*/ AbstractManager/*<Block>*/* BlockTableDataModel::getManager() {
    return (BlockManager*)InstanceManager::getDefault("BlockManager");
}

//@Override
/*public*/ NamedBean* BlockTableDataModel::getBySystemName(/*@Nonnull*/ QString name) const {
    return (NamedBean*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBeanBySystemName(name);
}

//@Override
/*public*/ NamedBean* BlockTableDataModel::getByUserName(/*@Nonnull*/ QString name) {
    return ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getByUserName(name);
}

//@Override
/*protected*/ QString BlockTableDataModel::getMasterClassName() {
    //return BlockTableAction::getName();
 return "jmri.jmrit.beantable.BlockTableAction";
}

//@Override
/*public*/ void BlockTableDataModel::clickOn(NamedBean* t) {
    // don't do anything on click; not used in this class, because
    // we override setValueAt
}

//@Override
/*public*/ int BlockTableDataModel::getColumnCount() const {
    return SPEEDCOL + 1;
}

//@Override
/*public*/ QVariant BlockTableDataModel::getValueAtX(int row, int col) const {
    // some error checking
    if (row >= sysNameList.size()) {
        log->error(tr("requested getValueAt(\"%1\"), row outside of range").arg(row));
        return "Error table size";
    }
    Block* b = (Block*)getBySystemName(sysNameList.at(row));
    if (b == nullptr) {
        log->error(tr("requested getValueAt(\"%1\"), Block doesn't exist").arg(row));
        return "(no Block)";
    }
    switch (col)
    {
        case DIRECTIONCOL:
            return Path::decodeDirection(b->getDirection());
        case CURVECOL:
        {
//            BlockCurvatureJComboBox* box = new BlockCurvatureJComboBox(b->getCurvature());
//            box->setJTableCellClientProperties();
//            return VPtr<BlockCurvatureJComboBox>::asQVariant(box);
         return b->getCurvature();
        }
        case LENGTHCOL:
            return (twoDigit.format(metricUi ?  b->getLengthCm() : b->getLengthIn()));
        case PERMISCOL:
            return b->getPermissiveWorking();
        case SPEEDCOL:
        {
            QString speed = b->getBlockSpeed();
//            if (! speedList->contains(speed)) {
//                 speedList->append(speed);
//            }
//            JComboBox* c = new JComboBox( speedList->toList());
//            c->setEditable(true);
//            c->setSelectedItem(speed);
////            JComboBoxUtil::setupComboBoxMaxRows(c);
//            return VPtr<JComboBox>::asQVariant(c);
            return speed;
        }
        case STATECOL:
            return blockDescribeState(b->getState());
        case SENSORCOL:
        {
            Sensor* sensor = b->getSensor();
//            JComboBox* cs = new JComboBox(sensorList.toList());
            QString name = "";
            if (sensor != nullptr) {
                name = sensor->getDisplayName();
            }
//            cs->setSelectedItem(name);
////            JComboBoxUtil.setupComboBoxMaxRows(cs);
//            return VPtr<JComboBox>::asQVariant(cs);
            return name;
        }
        case REPORTERCOL:
        {
            Reporter* reporter = b->getReporter();
            JComboBox* rs = new JComboBox(reporterList.toList());
            QString repname = "";
            if (reporter != nullptr) {
                repname = reporter->getDisplayName();
            }
//            rs->setSelectedItem(repname);
////            JComboBoxUtil.setupComboBoxMaxRows(rs);
//            return VPtr<JComboBox>::asQVariant(rs);
            return repname;
        }
        case CURRENTREPCOL:
            return b->isReportingCurrent();
        case EDITCOL:
            return tr("Edit");
        default:
            //return BeanTableDataModel::getValueAt(row, col);
     return QVariant();
    }
}

QVariant BlockTableDataModel::data(const QModelIndex &index, int role) const
{
 QVariant ret;
 if(role == Qt::ToolTipRole)
 {
   return this->getCellToolTip(table(), index.row(), index.column());
 }
 else if(role == Qt::CheckStateRole)
 {
  if(index.column() == PERMISCOL)
   return  this->getValueAtX(index.row(), index.column()).toBool()?Qt::Checked:Qt::Unchecked;
 }
// else if(role == Qt::ToolTipRole)
// {
//  ret = getToolTip(index.column());
// }
 else if(role == Qt::DisplayRole)
 {
  ret = this->getValueAtX(index.row(), index.column());
  if(ret != QVariant())
   return  ret;;
 }
 else if(_graphicState && role == Qt::DecorationRole)
 {
  if(index.column() == STATECOL)
  {
   Block* b = (Block*)getBySystemName(sysNameList.at(index.row()));

   if (b->getState()==Block::UNOCCUPIED && offIcon != QPixmap()) {
    return offIcon;
   }
   else if (b->getState()==Block::OCCUPIED && onIcon != QPixmap()) {
    return onIcon;
   }
   else if (b->getState()==Block::INCONSISTENT) {
//       label = new JLabel("X", JLabel.CENTER); // centered text alignment
//       label.setForeground(Color.red);
//       iconHeight = 0;
   } else { // Unknown Undetected Other
//       label = new JLabel("?", JLabel.CENTER); // centered text alignment
//       iconHeight = 0;
    return  QColor(Qt::red);
   }
  }
 }
  return BeanTableDataModel::data(index, role);
}

/*public*/ void BlockTableDataModel::configureColumnDelegates(JTable* t)
{
 for(int i=0; i < columnCount(QModelIndex()); i++)
 {
  if(getColumnClass(i) == "JButton")
  {
   t->setItemDelegateForColumn(i, new ButtonEditor());
  }
  if(getColumnClass(i) == "JComboBox")
  {
   //t->setItemDelegateForColumn(i, new JComboBoxEditor());
   switch(i)
   {
   case CURVECOL:
   {
     BlockCurvatureJComboBox* box = new BlockCurvatureJComboBox();
     box->setJTableCellClientProperties();
     QStringList list = {"NONE","GRADUAL","TIGHT","SEVERE"};
     t->setItemDelegateForColumn(i, new JComboBoxEditor(list, true));
     break;
   }
   case SPEEDCOL:
      t->setItemDelegateForColumn(i, new JComboBoxEditor(speedList->toList(), false));
    break;
   case SENSORCOL:
    t->setItemDelegateForColumn(i, new JComboBoxEditor(sensorList.toList(), false));
    break;
   case REPORTERCOL:
   t->setItemDelegateForColumn(i, new JComboBoxEditor(reporterList.toList(), false));
    break;
   default:
    break;
   }
  }
 }
}

// TODO : Add Block.UNDETECTED
// TODO : Move to Block.describeState(int)
/*private*/ QString BlockTableDataModel::blockDescribeState(int blockState) const{
    switch (blockState) {
        case (Block::OCCUPIED):
            return  tr("Occupied");
        case (Block::UNOCCUPIED):
            return  tr("UnOccupied");
        case (Block::UNKNOWN):
            return  tr("Unknown");
        default:
            return  tr("Inconsistent");
    }
}

//@Override
///*public*/ void BlockTableDataModel::setValueAt(QVariant value, int row, int col)
/*public*/bool BlockTableDataModel::setData( const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
   // no setting of block state from table
   Block* b = (Block*)getBySystemName(sysNameList.at(row));

 if(role == Qt::CheckStateRole)
 {
  switch (index.column()) {
  case PERMISCOL:
   b->setPermissiveWorking( value.toBool());
   fireTableRowsUpdated(row, row);
   break;
  case CURRENTREPCOL:
   b->setReportingCurrent(value.toBool());
   fireTableRowsUpdated(row, row);
   break;
  }
 }
 if(role == Qt::EditRole)
 {
    switch (index.column()) {
        case VALUECOL:
            b->setValue(value);
            break;
        case LENGTHCOL:
        {
            float len = 0.0f;
            bool ok;
                len = value.toFloat(&ok);//jmri.util.IntlUtilities.floatValue(value.toString());
            if(!ok) {
                log->error(tr("Error parsing length value of \"%1\"").arg(value.toString()));
            }   // block setLength() expecting value in mm, TODO: unit testing around this.
            b->setLength( metricUi ? len * 10.0f : len * 25.4f);
            break;
        }
        case CURVECOL:
            b->setCurvature(value.toInt());//BlockCurvatureJComboBox::getCurvatureFromObject(value));
            break;
//        case PERMISCOL:
//            b->setPermissiveWorking( value.toBool());
//            break;
        case SPEEDCOL:
        {
            //@SuppressWarnings("unchecked")
            QString speed =  value.toString();//(VPtr<JComboBox>::asPtr( value)->getSelectedItem());
            try {
                b->setBlockSpeed(speed);
            } catch (JmriException ex) {
                JOptionPane::showMessageDialog(nullptr, ex.getMessage() + "\n" + speed);
                return false;
            }
            if (! speedList->contains(speed) && !speed.contains("Global")) { // NOI18N
                 speedList->append(speed);
            }
            break;
        }
        case REPORTERCOL:
        {
            //@SuppressWarnings("unchecked")
            QString strReporter = value.toString();//VPtr<JComboBox>::asPtr(value)->getSelectedItem();
            if(strReporter != "")
            {
             Reporter* r = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(strReporter);
             b->setReporter(r);
            }
            break;
        }
        case SENSORCOL:
        {
            //@SuppressWarnings("unchecked")
            QString strSensor = value.toString();//VPtr<JComboBox>::asPtr(value)->getSelectedItem();
            b->setSensor(strSensor);
            break;
        }
//        case CURRENTREPCOL:
//            b->setReportingCurrent(value.toBool());
//            break;
        case EDITCOL:
//            javax.swing.SwingUtilities.invokeLater(() -> {
                editButton(b);
//            });
            break;
        default:
            BeanTableDataModel::setData(index, value, role);
            break;
    }
    fireTableRowsUpdated(row, row);
    return true;
 }
 return false;
}

//@Override
///*public*/ QString BlockTableDataModel::getColumnName(int col) const {
/*public*/ QVariant BlockTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case DIRECTIONCOL:
            return  tr("Direction");
        case VALUECOL:
            return  tr("Value");
        case CURVECOL:
            return  tr("Curvature");
        case LENGTHCOL:
            return  tr("Length");
        case PERMISCOL:
            return  tr("Permissive");
        case SPEEDCOL:
            return  tr("Speed");
        case STATECOL:
            return  tr("State");
        case REPORTERCOL:
            return  tr("Reporter");
        case SENSORCOL:
            return  tr("Sensor");
        case CURRENTREPCOL:
            return  tr("Use Current");
        case EDITCOL:
            return  tr("Edit");
        default:
            break;
    }
 }
 return  BeanTableDataModel::headerData(section, orientation, role);
}

//@Override
/*public*/ QString BlockTableDataModel::getColumnClass(int col) const  {
    switch (col) {
        case DIRECTIONCOL:
        case VALUECOL: // not a button
        case LENGTHCOL:
            return "String";
        case STATECOL: // may use an image to show block state
            if (_graphicState) {
                return "JLabel";
            } else {
                return "String";
            }
        case SPEEDCOL:
        case CURVECOL:
        case REPORTERCOL:
        case SENSORCOL:
            return "JComboBox";
        case CURRENTREPCOL:
        case PERMISCOL:
            return "Boolean";
        case EDITCOL:
            return "JButton";
        default:
            return BeanTableDataModel::getColumnClass(col);
    }
}

//@Override
/*public*/ int BlockTableDataModel::getPreferredWidth(int col) {
    switch (col) {
        case DIRECTIONCOL:
        case LENGTHCOL:
        case PERMISCOL:
        case SPEEDCOL:
        case CURRENTREPCOL:
        case EDITCOL:
            return  JTextField(7).getPreferredSize().width();
        case CURVECOL:
        case STATECOL:
        case REPORTERCOL:
        case SENSORCOL:
            return JTextField(8).getPreferredSize().width();
        default:
            return BeanTableDataModel::getPreferredWidth(col);
    }
}

//@Override
/*public*/ void BlockTableDataModel::configValueColumn(JTable* table) {
    // value column isn't button, so config is null
}

//@Override
///*public*/ bool BlockTableDataModel::isCellEditable(int row, int col) const{
//    switch (col) {
//        case CURVECOL:
//        case LENGTHCOL:
//        case PERMISCOL:
//        case SPEEDCOL:
//        case REPORTERCOL:
//        case SENSORCOL:
//        case CURRENTREPCOL:
//        case EDITCOL:
//            return true;
//        case STATECOL:
//            return false;
//        default:
//            return BeanTableDataModel::isCellEditable(row, col);
//    }
//}
/*private*/ Qt::ItemFlags BlockTableDataModel::flags(const QModelIndex &index) const
{
     switch (index.column()) {
     case PERMISCOL:
      return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
     case CURVECOL:
     case LENGTHCOL:
     case SPEEDCOL:
     case REPORTERCOL:
     case SENSORCOL:
     case CURRENTREPCOL:
     case EDITCOL:
      return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
     case STATECOL:
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
     default:
      return BeanTableDataModel::flags(index);
     }
}


//@Override
/*public*/ void BlockTableDataModel::configureTable(JTable* table) {
    InstanceManager::sensorManagerInstance()->PropertyChangeSupport::addPropertyChangeListener(this);
    ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->PropertyChangeSupport::addPropertyChangeListener(this);
    configStateColumn(table);
    configureColumnDelegates(table);
    BeanTableDataModel::configureTable(table);
}

void BlockTableDataModel::editButton(Block* b) {
    BlockEditAction* beanEdit = new BlockEditAction();
    beanEdit->setBean(b);
    beanEdit->actionPerformed(/*null*/);
}

/**
 * returns true for all Block properties.
 * @param e property event that has changed.
 * @return true as all matched.
 */
//@Override
/*protected*/ bool BlockTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    return true;
}

//@Override
/*public*/ JButton* BlockTableDataModel::configureButton() {
    log->error("configureButton should not have been called");
    return nullptr;
}

//@Override
/*public*/ void BlockTableDataModel::propertyChange(PropertyChangeEvent* e) {
    if (qobject_cast<SensorManager*>(e->getSource())) {
        if (e->getPropertyName() == ("length") || e->getPropertyName() == ("DisplayListName")) { // NOI18N
            updateSensorList();
        }
    }
    if (qobject_cast<ReporterManager*>(e->getSource() )) {
        if (e->getPropertyName() == ("length") || e->getPropertyName() == ("DisplayListName")) { // NOI18N
            updateReporterList();
        }
    }
    if (e->getPropertyName() == ("DefaultBlockSpeedChange")) { // NOI18N
        updateSpeedList();
    } else {
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
     Sensor* nBean = (Sensor*)nb;
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
    QSet<NamedBean*> nameSet = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getNamedBeanSet();
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
     speedList->removeOne(defaultBlockSpeedText);
    defaultBlockSpeedText = ( tr("Use %1").arg("Global") + " " + ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getDefaultSpeed());
     speedList->insert(0, defaultBlockSpeedText);
    fireTableDataChanged();
}

/*public*/ void BlockTableDataModel::setDefaultSpeeds(JFrame* _who) {
    JComboBox* blockSpeedCombo = new JComboBox( speedList->toList());

    blockSpeedCombo->setEditable(true);

    JPanel* block = new JPanel(new FlowLayout());
    block->layout()->addWidget(new JLabel( tr("%1:").arg(tr("Speed"))));
    block->layout()->addWidget(blockSpeedCombo);

    blockSpeedCombo->removeItem(blockSpeedCombo->findText(defaultBlockSpeedText));

    blockSpeedCombo->setSelectedItem(((BlockManager*)InstanceManager::getDefault("BlockManager"))->getDefaultSpeed());

    // block of options above row of buttons; gleaned from Maintenance.makeDialog()
    // can be accessed by Jemmy in GUI test
    QString title =  tr("Block Speed");
    // build JPanel for comboboxes
    JPanel* speedspanel = new JPanel();
    speedspanel->setLayout(new QVBoxLayout());//speedspanel, BoxLayout.PAGE_AXIS));
    speedspanel->layout()->addWidget(new JLabel( tr("Select the default values for the speeds through the blocks")));
    //default LEFT_ALIGNMENT
    //block.setAlignmentX(Component.LEFT_ALIGNMENT);
    ((QVBoxLayout*)speedspanel->layout())->addWidget(block, 0, Qt::AlignLeft);

    int retval = JOptionPane::showConfirmDialog(
            _who,
            VPtr<JPanel>::asQVariant(speedspanel),
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
    } catch (IllegalArgumentException ex) {
        JOptionPane::showMessageDialog(_who, ex.getMessage() + "\n" + speedValue);
    }
}

//@Override
/*synchronized*/ /*public*/ void BlockTableDataModel::dispose() {
    ((SensorManager*)InstanceManager::getDefault("SensorManager"))->PropertyChangeSupport::removePropertyChangeListener(this);
    ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->PropertyChangeSupport::removePropertyChangeListener(this);
    BeanTableDataModel::dispose();
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
    if (_graphicState) { // load icons, only once
     loadIcons();
        //table.setDefaultEditor(JLabel.class, new ImageIconRenderer()); // there's no editor for state column in BlockTable
// TODO       table->setDefaultRenderer("JLabel", new ImageIconRenderer()); // item class copied from SwitchboardEditor panel
        // else, classic text style state indication, do nothing extra
    }
}

// state column may be image so have the tooltip as text version of Block state.
// length column tooltip confirms inches or cm.
//@Override
/*public*/ QString BlockTableDataModel::getCellToolTip(JTable* table, int row, int col) const {
 switch (col) {
  case BlockTableDataModel::STATECOL:
  {
   //QVariant v = getValueAt(row, 0);
   //Block* b = VPtr<Block>::asPtr(v);
   if (row >= sysNameList.size()) {
       log->error(tr("requested getValueAt(\"%1\"), row outside of range").arg(row));
       return "Error table size";
   }
   Block* b = (Block*)getBySystemName(sysNameList.at(row));
   if (b == nullptr) {
       log->error(tr("requested getValueAt(\"%1\"), Block doesn't exist").arg(row));
       return "(no Block)";
   }
   return blockDescribeState(b->getState());
  }
  case BlockTableDataModel::LENGTHCOL:
   return ( metricUi ?  tr("LengthCentimeters"):  tr("LengthInches"));
  default:
   return BeanTableDataModel::getCellToolTip(table, row, col);
 }
}
#if 0
/**
 * Visualize state in table as a graphic, customized for Blocks (2
 * states). Renderer and Editor are identical, as the cell contents
 * are not actually edited.
 *
 */
static class ImageIconRenderer extends AbstractCellEditor implements TableCellEditor, TableCellRenderer {

    protected JLabel label;
    protected String rootPath = "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
    protected char beanTypeChar = 'S'; // reuse Sensor icon for block state
    protected String onIconPath = rootPath + beanTypeChar + "-on-s.png";
    protected String offIconPath = rootPath + beanTypeChar + "-off-s.png";
    protected BufferedImage onImage;
    protected BufferedImage offImage;
    protected ImageIcon onIcon;
    protected ImageIcon offIcon;
    protected int iconHeight = -1;

    @Override
    /*public*/ Component getTableCellRendererComponent(
            JTable table, Object value, boolean isSelected,
            boolean hasFocus, int row, int column) {
        log.debug("Renderer Item = {}, State = {}", row, value);
        if (iconHeight < 0) { // load resources only first time, either for renderer or editor
            loadIcons();
            log.debug("icons loaded");
        }
        Block b = (Block) table.getModel().getValueAt(row, 0);
        return updateLabel(b);
    }

    @Override
    /*public*/ Component getTableCellEditorComponent(
            JTable table, Object value, boolean isSelected,
            int row, int column) {
        log.debug("Renderer Item = {}, State = {}", row, value);
        if (iconHeight < 0) { // load resources only first time, either for renderer or editor
            loadIcons();
            log.debug("icons loaded");
        }
        Block b = (Block) table.getModel().getValueAt(row, 0);
        return updateLabel(b);
    }

    /*public*/ JLabel updateLabel(Block b) {
        //  if (iconHeight > 0) { // if necessary, increase row height;
        //table.setRowHeight(row, Math.max(table.getRowHeight(), iconHeight - 5)); // TODO adjust table row height for Block icons
        //                     }
        if (b.getState()==Block.UNOCCUPIED && offIcon != null) {
            label = new JLabel(offIcon);
            label.setVerticalAlignment(JLabel.BOTTOM);
        } else if (b.getState()==Block.OCCUPIED && onIcon != null) {
            label = new JLabel(onIcon);
            label.setVerticalAlignment(JLabel.BOTTOM);
        } else if (b.getState()==Block.INCONSISTENT) {
            label = new JLabel("X", JLabel.CENTER); // centered text alignment
            label.setForeground(Color.red);
            iconHeight = 0;
        } else { // Unknown Undetected Other
            label = new JLabel("?", JLabel.CENTER); // centered text alignment
            iconHeight = 0;
        }
        label.addMouseListener(new MouseAdapter() {
            @Override
            /*public*/ final void mousePressed(MouseEvent evt) {
                log.debug("Clicked on icon for block {}",b);
                stopCellEditing();
            }
        });
        return label;
    }

    @Override
    /*public*/ Object getCellEditorValue() {
        log.debug("getCellEditorValue, me = {})", this.toString());
        return this.toString();
    }

    /**
     * Read and buffer graphics. Only called once for this table.
     *
     * @see #getTableCellEditorComponent(JTable, Object, boolean,
     * int, int)
     */
    protected void loadIcons() {
        try {
            onImage = ImageIO.read(new File(onIconPath));
            offImage = ImageIO.read(new File(offIconPath));
        } catch (IOException ex) {
            log.error("error reading image from {} or {}", onIconPath, offIconPath, ex);
        }
        log.debug("Success reading images");
        int imageWidth = onImage.getWidth();
        int imageHeight = onImage.getHeight();
        // scale icons 50% to fit in table rows
        Image smallOnImage = onImage.getScaledInstance(imageWidth / 2, imageHeight / 2, Image.SCALE_DEFAULT);
        Image smallOffImage = offImage.getScaledInstance(imageWidth / 2, imageHeight / 2, Image.SCALE_DEFAULT);
        onIcon = new ImageIcon(smallOnImage);
        offIcon = new ImageIcon(smallOffImage);
        iconHeight = onIcon.getIconHeight();
    }

}; // end of ImageIconRenderer class
#endif
/**
 * Read and buffer graphics. Only called once for this table.
 *
 * @see #getTableCellEditorComponent(JTable, Object, boolean, int, int)
 */
/*protected*/ void BlockTableDataModel::loadIcons() {
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

/*private*/ /*final*/ /*static*/ Logger* BlockTableDataModel::log = LoggerFactory::getLogger("BlockTableDataModel");
