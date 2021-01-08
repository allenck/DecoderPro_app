#include "oblocktablemodel.h"
#include "oblockmanager.h"
#include "jtable.h"
#include "instancemanager.h"
#include "treeset.h"
#include "oblock.h"
#include "jtextfield.h"
#include "tableframes.h"
#include "proxyreportermanager.h"
#include "reporter.h"
#include "propertychangelistener.h"
#include <QPushButton>
#include "signaltablemodel.h"
#include "blockportaltablemodel.h"
#include <QComboBox>
#include "warrant.h"
#include "signalspeedmap.h"
#include "portaltablemodel.h"
#include "joptionpane.h"
#include "warrantmanager.h"
#include "guilafpreferencesmanager.h"

//OBlockTableModel::OBlockTableModel(QObject *parent) :
//  BeanTableDataModel(parent)
//{
//}
/**
 * Duplicates the JTable model for BlockTableAction and adds a column for the
 * occupancy sensor. Configured for use within an internal frame.
 */
///*public*/ class OBlockTableModel extends jmri.jmrit.beantable.BeanTableDataModel {

/**
 *
 */

/*static*/ /*public*/ /*final*/ QString OBlockTableModel::noneText = tr("None");
/*static*/ /*public*/ /*final*/ QString OBlockTableModel::gradualText = tr("Gradual");
/*static*/ /*public*/ /*final*/ QString OBlockTableModel::tightText = tr("Tight");
/*static*/ /*public*/ /*final*/ QString OBlockTableModel::severeText = tr("Severe");
/*static*/ /*final*/ QStringList OBlockTableModel::curveOptions = QStringList() << OBlockTableModel::noneText << OBlockTableModel::gradualText << OBlockTableModel::tightText << OBlockTableModel::severeText;

/*static*/ QString OBlockTableModel::ZEROS = "00000000";



/*public*/ OBlockTableModel::OBlockTableModel(TableFrames* parent)
 :  BeanTableDataModel(parent)
{
 //super();
 twoDigit = new DecimalFormat("0.00");
 tempRow = QStringList();
 for(int i=0; i < NUMCOLS; i++)
  tempRow.append("");
 _tempLen = 0.0f;      // mm for length col of tempRow
 log = new Logger("OBlockTableModel");
 noWarnDelete = false;

 _parent = parent;
 _tabbed = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isOblockEditTabbed();
 if (_tabbed) {
     _manager = ((OBlockManager*)InstanceManager::getDefault("OBlockManager")); // TODO also for _desktop?
     _manager->addPropertyChangeListener((PropertyChangeListener*)this);
 }
 updateNameList();
 initTempRow();
 AbstractManager* mgr = (AbstractManager*)getManager();
 connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

void OBlockTableModel::addHeaderListener(JTable* table)
{
 addMouseListenerToHeader(table);
}

void OBlockTableModel::initTempRow()
{
  for (int i = 0; i < NUMCOLS; i++)
  {
   tempRow.replace(i, NULL);
  }
  tempRow[LENGTHCOL] = twoDigit->format(0.0);
  tempRow[UNITSCOL] = tr("in");
  tempRow[CURVECOL] = noneText;
  tempRow[REPORT_CURRENTCOL] = tr("Current");
  tempRow[PERMISSIONCOL] = tr("Permissive");
  tempRow[SPEEDCOL] = "";         // tr("Normal");
  tempRow[DELETE_COL] = tr("Clear");
}

//@Override
/*public*/ Manager* OBlockTableModel::getManager() {
 _manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 return _manager;
}

//@Override
/*public*/ NamedBean* OBlockTableModel::getBySystemName(QString name) const
{
 return _manager->getBySystemName(name);
}

//@Override
/*public*/ NamedBean* OBlockTableModel::getByUserName(QString name) {
    return _manager->getByUserName(name);
}

//@Override
/*protected*/ QString OBlockTableModel:: getBeanType() {
    return "OBlock";
}

//@Override
/*public*/ void OBlockTableModel::clickOn(NamedBean* t) {
}

//@Override
/*protected*/ QString OBlockTableModel::getMasterClassName() {
 return "jmri.jmrit.beantable.OBlockTableModel"/*.class.getName()*/;
}

/*protected*/ QList<NamedBean*> OBlockTableModel::getBeanList() {

    //QSetIterator<NamedBean*> ts = TreeSet<NamedBean*>(/*new NamedBeanComparator()*/);
 QList<NamedBean*> list =  QList<NamedBean*>(/*sysNameList.size()*/);

    QListIterator<QString> iter(sysNameList);
    while (iter.hasNext()) {
        //ts.add(getBySystemName(iter.next()));
     list.append(getBySystemName(iter.next()));
    }

//    QListIterator<NamedBean*> it(ts.toList());
//    while (it.hasNext()) {
//        NamedBean* elt = it.next();
//        list.append(elt);
//    }
    return list;
}

//@Override
/*public*/ QString OBlockTableModel::getValue(QString name) const{
    int state = _manager->getBySystemName(name)->getState();
    return getValue(state);
}

/*static*/ /*protected*/ QString OBlockTableModel::getValue(int state) {
    QString sb;// = new StringBuilder();
    if ((state & OBlock::DARK) != 0) {
        sb.append(tr("Dark"));
    }
    if ((state & OBlock::OCCUPIED) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("Occupied"));
    }
    if ((state & OBlock::UNOCCUPIED) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("Unoccupied"));
    }
    if ((state & OBlock::INCONSISTENT) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("Inconsistent"));
    }
    if ((state & OBlock::ALLOCATED) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("Allocated"));
    }
    if ((state & OBlock::RUNNING) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("Running"));
    }
    if ((state & OBlock::OUT_OF_SERVICE) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("OutOfService"));
    }
    if ((state & OBlock::TRACK_ERROR) != 0) {
        if (sb.length() > 0) {
            sb.append('-');
        }
        sb.append(tr("TrackError"));
    }
    if (sb.length() == 0) {
        sb.append(tr("Unknown"));
    }
    return sb;
}

//@Override
/*public*/ int OBlockTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return BeanTableDataModel::getRowCount() + (_tabbed ? 0 : 1); // + 1 row in _desktop to create entry row

}

//@Override
/*public*/ int OBlockTableModel::rowCount(const QModelIndex &parent) const
{
    return BeanTableDataModel::rowCount(parent) + 1;
}

//@Override
/*public*/ QVariant OBlockTableModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 int col = index.column();
 if (row > sysNameList.size())
 {
    return "";
 }
 OBlock* b = NULL;
 if ((_tabbed && row <= sysNameList.size()) || (!_tabbed && row < sysNameList.size())) {
     QString name = sysNameList.at(row);
     b = (OBlock*)_manager->getBySystemName(name);
 }
 if(role == Qt::DisplayRole)
 {

 switch (col)
 {
  case SYSNAMECOL:
   if (b != NULL) {
       return b->getSystemName();
   }
   return tempRow[col];
  case USERNAMECOL:
   if (b != NULL) {
       return b->getUserName();
   }
   return tempRow[col];
  case COMMENTCOL:
   if (b != NULL) {
       return b->getComment();
   }
   return tempRow[col];
  case STATECOL:
   if (b != NULL)
   {
    int state = b->getState();
    int num = numberOfLeadingZeros(state) - 24;
    if (num>=0) {
        return ZEROS.mid(0, num) + QString::number(state,2);
    }
   }
   return ZEROS;
  case SENSORCOL:
   if (b != NULL)
   {
    Sensor* s = b->getSensor();
    if (s == NULL) {
        return "";
    }
    return s->getDisplayName();
   }
   return tempRow[col];
  case LENGTHCOL:
   if (b != NULL)
   {
    if (b->isMetric())
    {
     return (twoDigit->format(b->getLengthCm()));
    }
    return (twoDigit->format(b->getLengthIn()));
   }
   if (tempRow[UNITSCOL]==(tr("cm")))
   {
    return (twoDigit->format(_tempLen/10));
   }
   return (twoDigit->format(_tempLen/25.4f));
 case UNITSCOL:
  if (b != NULL)
  {
   if (log->isDebugEnabled())
   {
    log->debug("getValueAt: row= "+QString::number(row)+", col= "+QString::number(col)+", "+b->getDisplayName()+" isMetric= "+(b->isMetric()?"true":"false"));
    }
    return b->isMetric()?"cm":"in";
   }
   if (log->isDebugEnabled())
   {
    log->debug(tr("getValueAt: row= ")+QString::number(row)+", col= "+QString::number(col)+", is cm= "+(tempRow[UNITSCOL]==(tr("cm"))?"true":"false"));
  }
  return tempRow[UNITSCOL]==(tr("cm"))?"cm":"in";

 case CURVECOL:
   if (b != NULL)
   {
    QString c = "";
    if (b->getCurvature() == Block::NONE) {
        c = noneText;
    } else if (b->getCurvature() == Block::GRADUAL) {
        c = gradualText;
    } else if (b->getCurvature() == Block::TIGHT) {
        c = tightText;
    } else if (b->getCurvature() == Block::SEVERE) {
        c = severeText;
    }
    return c;
   }
   return tempRow[col];
  case ERR_SENSORCOL:
   if (b != NULL)
   {
    Sensor* s = b->getErrorSensor();
    if (s == NULL) {
        return "";
    }
    return s->getDisplayName();
   }
   return tempRow[col];
  case REPORTERCOL:
   if (b != NULL)
   {
    Reporter* r = b->getReporter();
    if (r == NULL) {
        return "";
    }
    return r->getDisplayName();
   }
   return tempRow[col];
 case REPORT_CURRENTCOL:
  if (b != NULL)
  {
   if (b->getReporter() != NULL)
   {
    return b->isReportingCurrent()?"Current":"Last";
   }
   return "";
  }
  return tempRow[REPORT_CURRENTCOL]==(tr("Current"))?"Current":"Last";
 case PERMISSIONCOL:
  if (b != NULL) {
      return b->getPermissiveWorking()?"Permissive":"Absolute";
  }
  return tempRow[PERMISSIONCOL]==(tr("Permissive"))?"Permissive":"Absolute";

  case SPEEDCOL:
   if (b != NULL) {
       return b->getBlockSpeed();
   }
   return tempRow[col];
   case WARRANTCOL:
    if (b != nullptr) {
        Warrant* w = b->getWarrant();
        if (w != nullptr) {
            return w->getDisplayName();
        }
    }
    return tempRow[col];
   case EDIT_COL:
   if (b != NULL) {
    if (_tabbed)
    {
        return tr("Edit");
    }
    else
    {
     return tr("Edit Paths");
    }
   }
   return "";
  case DELETE_COL:
   if (b != NULL) {
       return tr("Delete");
   }
   return tr("Clear");
  }
  return BeanTableDataModel::data(index, role);
 }
 return QVariant();
}

 /*public*/ /*static*/ int OBlockTableModel::numberOfLeadingZeros(int i)
{
  // HD, Figure 5-6
  if (i == 0)
      return 32;
  int n = 1;
  if (i >> 16 == 0) { n += 16; i <<= 16; }
  if (i >> 24 == 0) { n +=  8; i <<=  8; }
  if (i >> 28 == 0) { n +=  4; i <<=  4; }
  if (i >> 30 == 0) { n +=  2; i <<=  2; }
  n -= i >> 31;
  return n;
}

//@Override
/*public*/ bool OBlockTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int col = index.column();
 int row = index.row();
 if (!_tabbed && (BeanTableDataModel::getRowCount() == row))
 { // editing tempRow

  if(role == Qt::EditRole)
  {
   if (log->isDebugEnabled())
   {
    log-> debug(tr("setValueAt: row= ") + QString::number(row) + ", col= " + QString::number(col) + ", value= " + value.toString());
   }
   if (BeanTableDataModel::rowCount(index) == row)
   {
    switch (col)
    {
     case SYSNAMECOL:
     {
     OBlock* block = _manager->createNewOBlock( value.toString(), tempRow[USERNAMECOL]);
     if (block == NULL)
     {
      block = _manager->getOBlock(tempRow[USERNAMECOL]);
      QString name = value.toString() + " / " + tempRow[USERNAMECOL];
      if (block != NULL)
      {
       name = block->getDisplayName();
      }
      else
      {
       block = _manager->getOBlock(value.toString());
       if (block != NULL)
       {
        name = block->getDisplayName();
       }
      }
      JOptionPane::showMessageDialog(NULL, tr("Duplicate name, Block \"%1\" has been defined. ").arg(name),
              tr("Error"), JOptionPane::WARNING_MESSAGE);
      return true;
     }
     if (tempRow[SENSORCOL] != NULL)
     {
      if (!sensorExists(tempRow[SENSORCOL]))
      {
       JOptionPane::showMessageDialog(NULL, tr("There is no Sensor named \"%1\".").arg(tempRow[SENSORCOL]),
               tr("Error"), JOptionPane::WARNING_MESSAGE);
      }
     }
     block->setComment(tempRow[COMMENTCOL]);
     float len = 0.0f;
     bool bok;
     len = tempRow[LENGTHCOL].toFloat(&bok);
     if(!bok)
     {
      JOptionPane::showMessageDialog(NULL, tr("%1 is not a number.").arg(tempRow[LENGTHCOL]),
              tr("ErrorT"), JOptionPane::WARNING_MESSAGE);
     }
     if (tempRow[UNITSCOL]==(tr("cm"))) {
         block->setLength(len * 10.0f);
         block->setMetricUnits(true);
     } else {
         block->setLength(len * 25.4f);
         block->setMetricUnits(false);
     }
     if (tempRow[CURVECOL]==(noneText)) {
         block->setCurvature(Block::NONE);
     } else if (tempRow[CURVECOL]==(gradualText)) {
         block->setCurvature(Block::GRADUAL);
     } else if (tempRow[CURVECOL]==(tightText)) {
         block->setCurvature(Block::TIGHT);
     } else if (tempRow[CURVECOL]==(severeText)) {
         block->setCurvature(Block::SEVERE);
     }
     block->setPermissiveWorking(tempRow[PERMISSIONCOL]==(tr("Permissive")));
     block->setBlockSpeedName(tempRow[SPEEDCOL]);

     if (tempRow[ERR_SENSORCOL] != NULL) {
      if (tempRow[ERR_SENSORCOL].trimmed().length() > 0)
      {
       if (!sensorExists(tempRow[ERR_SENSORCOL]))
       {
        JOptionPane::showMessageDialog(NULL, tr("There is no Sensor named \"%1\".").arg(tempRow[ERR_SENSORCOL]),
                tr("Error"), JOptionPane::WARNING_MESSAGE);
       }
      }
     }
     if (tempRow[REPORTERCOL] != NULL)
     {
      Reporter* rep = NULL;
      try {
          rep = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(tempRow[REPORTERCOL]);
          if (rep != NULL) {
              block->setReporter(rep);
              block->setReportingCurrent(tempRow[REPORT_CURRENTCOL]==(tr("Current")));
          }
      } catch (Exception ex) {
          log->error("No Reporter named \"" + tempRow[REPORTERCOL] + "\" found. threw exception: " /*+ ex*/);
      }
      if (rep == NULL) {
       JOptionPane::showMessageDialog(NULL, tr("There is no Reporter named \"%1\".").arg(tempRow[REPORTERCOL]),
               tr("ErrorTitle"), JOptionPane::WARNING_MESSAGE);

      }
      block->setReporter(rep);
     }
     initTempRow();
     fireTableDataChanged();
     return true;
    }
    case DELETE_COL:            // clear
    {
     initTempRow();
     fireTableRowsUpdated(row, row);
     return true;
    }
    case LENGTHCOL:
    {
     bool bok;
     _tempLen = value.toFloat(&bok);
     if (tempRow[UNITSCOL]==(tr("cm"))) {
         _tempLen *= 10.0;
     } else {
         _tempLen *= 25.4;
     }
     if(!bok)
     {
      JOptionPane::showMessageDialog(NULL, tr("%1 is not a number.").arg(tempRow[LENGTHCOL]),
              tr("Error"), JOptionPane::WARNING_MESSAGE);
     }
     return true;
    }
    case UNITSCOL:
    {
     if ( value.toBool())
     {
      tempRow[UNITSCOL] = tr("cm");
     }
     else
     {
      tempRow[UNITSCOL] = tr("in");
     }
     fireTableRowsUpdated(row, row);
     return true;
    }
    case REPORT_CURRENTCOL:
    {
     if(value.toBool())
     {//toggle
            tempRow[REPORT_CURRENTCOL] = tr("Current");
        } else {
            tempRow[REPORT_CURRENTCOL] = tr("Last");
        }
        return true;
    }
    case PERMISSIONCOL:
    {
     if ( value.toBool())
     {//toggle
         tempRow[PERMISSIONCOL] = tr("Permissive");
     }
     else
     {
         tempRow[PERMISSIONCOL] = tr("Absolute");
     }
     return true;
    }
    }
    tempRow.replace(col, value.toString());
    return true;
   }
   QString name = sysNameList.at(row);
   OBlock* block = (OBlock*)_manager->getBySystemName(name);
   switch (col)
   {
    case USERNAMECOL:
    {
     OBlock* b = _manager->getOBlock( value.toString());
     if (b != NULL) {
                 JOptionPane::showMessageDialog(NULL, tr("Duplicate name, Block \"%1\" has been defined. ").arg( block->getDisplayName()),
                         tr("Error"), JOptionPane::WARNING_MESSAGE);
        return true;
    }
    block->setUserName( value.toString());
    fireTableRowsUpdated(row, row);
    return true;
   }
   case COMMENTCOL:
    block->setComment( value.toString());
    fireTableRowsUpdated(row, row);
    return true;
   case STATECOL:
    /* currently STATECOL is not editable.  Maybe allow it and (or not) set the sensor?  Why?
    int state = 0;
    try {
        state = Integer.valueOf( value);
    } catch (NumberFormatException nfe) {
    }
    if (state < 0) {
        state = -state;
    }
    block->setState(state % 255);
    fireTableRowsUpdated(row, row); */
    return true;
   case SENSORCOL:
    if (!block->setSensor( value.toString()))
    {
        JOptionPane::showMessageDialog(NULL, tr("There is no Sensor named \"%1\".").arg(value.toString()),
                tr("ErrorTitle"), JOptionPane::WARNING_MESSAGE);
    }
    fireTableRowsUpdated(row, row);
    return true;
   case LENGTHCOL:
   {
    bool bok;
    float len = value.toFloat(&bok);
    if (block->isMetric()) {
        block->setLength(len * 10.0f);
    } else {
        block->setLength(len * 25.4f);
    }
    fireTableRowsUpdated(row, row);
    if(!bok)
    {
     JOptionPane::showMessageDialog(NULL, tr("%1 is not a number.").arg(value.toString()),
             tr("Error"), JOptionPane::WARNING_MESSAGE);
    }
    return true;
   }
   case UNITSCOL:
   {
    block->setMetricUnits( value.toBool());
    fireTableRowsUpdated(row, row);
    return true;
   }
   case CURVECOL:
   {
    QString cName =  value.toString();
    if (cName==(noneText)) {
        block->setCurvature(Block::NONE);
    } else if (cName==(gradualText)) {
        block->setCurvature(Block::GRADUAL);
    } else if (cName==(tightText)) {
        block->setCurvature(Block::TIGHT);
    } else if (cName==(severeText)) {
        block->setCurvature(Block::SEVERE);
    }
    fireTableRowsUpdated(row, row);
    return true;
   }
   case ERR_SENSORCOL:
   {
   bool err = false;
   try {
    if (( value.toString()).trimmed().length() == 0) {
        block->setErrorSensor(NULL);
        err = true;
    } else {
        err = block->setErrorSensor( value.toString());
        fireTableRowsUpdated(row, row);
    }
    } catch (Exception ex) {
        log->error("getSensor(" +  value.toString() + ") threw exception: " /*+ ex*/);
    }
    if (err) {
              JOptionPane::showMessageDialog(NULL, tr("There is no Sensor named \"%1\".").arg(value.toString()),
                      tr("Error"), JOptionPane::WARNING_MESSAGE);
    }
    fireTableRowsUpdated(row, row);
    return true;

   }
  case REPORTERCOL:
  {
    Reporter* rep = NULL;
    try {
        rep = ((ProxyReporterManager*)((ReporterManager*)InstanceManager::getDefault("ReporterManager")))->getReporter( value.toString());
        if (rep != NULL) {
            block->setReporter(rep);
            fireTableRowsUpdated(row, row);
        }
    } catch (Exception ex) {
        log->error("No Reporter named \"" +  value.toString() + "\" found. threw exception: " /*+ ex*/);
    }
    if (rep == NULL) {
        JOptionPane::showMessageDialog(NULL, tr("There is no Reporter named \"%1\".").arg(tempRow[REPORTERCOL]),
                tr("Error"), JOptionPane::WARNING_MESSAGE);
    }
    block->setReporter(rep);
    fireTableRowsUpdated(row, row);
    return true;
   }
  case REPORT_CURRENTCOL:
   {
    if (block->getReporter() != NULL)
    {
     block->setReportingCurrent(value.toBool());
     fireTableRowsUpdated(row, row);
    }
    return true;
   }
  case PERMISSIONCOL:
   {
    block->setPermissiveWorking(value.toBool());
    fireTableRowsUpdated(row, row);
    return true;
   }
   case WARRANTCOL:
   {
     Warrant* warrant = block ->getWarrant();
     WarrantManager* mgr = (WarrantManager*)InstanceManager
                 ::getDefault("WarrantManager");
     Warrant* newWarrant = mgr->getWarrant(value.toString());
     if (warrant != nullptr && !warrant->equals(newWarrant)) {
         block->deAllocate(warrant);
         if (newWarrant != nullptr) {
             QString msg = block->allocate(newWarrant);
             if (msg != nullptr) {
                 JOptionPane::showMessageDialog(nullptr, msg,
                        tr("Error"), JOptionPane::WARNING_MESSAGE);
             }
         }
     }
     fireTableRowsUpdated(row, row);
     return true;
   }
   case SPEEDCOL:
    {
      block->setBlockSpeedName( value.toString());
      fireTableRowsUpdated(row, row);
      return true;
    }
    case EDIT_COL:
    {
     _parent->openBlockPathFrame(block->getSystemName());
     return true;
    }
    case DELETE_COL:
    {
      deleteBean(block);
      block = NULL;
      return true;
    }
   }
   BeanTableDataModel::setData(index, value, role);
  }
 }
 // Edit an existing row
 QString name = sysNameList.at(row);
 OBlock* block = (OBlock*)_manager->getBySystemName(name);
 if (block == nullptr) {
     log->error(tr("OBlock named %1 not found for OBlockTableModel").arg(name));
     return false;
 }
 switch (col) {
     case USERNAMECOL:
     {
         OBlock* b = _manager->getOBlock( value.toString());
         if (b != nullptr) {
             JOptionPane::showMessageDialog(nullptr, tr("Duplicate name. Block \"%1\" has already been defined.").arg(block->getDisplayName()),
                     tr("Error"), JOptionPane::WARNING_MESSAGE);
             return false;
         }
         block->setUserName(value.toString());
         fireTableRowsUpdated(row, row);
         return true;
     }
     case COMMENTCOL:
         block->setComment(value.toString());
         fireTableRowsUpdated(row, row);
         return true;
     case STATECOL:
         return true;     //  STATECOL is not editable
     case SENSORCOL:
         if (!block->setSensor(value.toString())) {
             JOptionPane::showMessageDialog(nullptr, tr("There is no Sensor named \"%1\".").arg(value.toString()),
                     tr("Error"), JOptionPane::WARNING_MESSAGE);
         }
         fireTableRowsUpdated(row, row);
         return true;
     case LENGTHCOL:
     {
         bool ok;
             float len = /*IntlUtilities.floatValue*/(value.toFloat(&ok));
             if (block->isMetric()) {
                 block->setLength(len * 10.0f);
             } else {
                 block->setLength(len * 25.4f);
             }
             fireTableRowsUpdated(row, row);
         if(!ok) {
             JOptionPane::showMessageDialog(nullptr, tr("%1 is not a number.").arg(value.toString()),
                     tr("Error"), JOptionPane::WARNING_MESSAGE);
         }
         return true;
     }
     case UNITSCOL:
         block->setMetricUnits( value.toBool());
         fireTableRowsUpdated(row, row);
         return true;
     case CURVECOL:
     {
         QString cName = value.toString();
         if (cName == "") {
             return true;
         }
         if (cName == (noneText)) {
             block->setCurvature(Block::NONE);
         } else if (cName == (gradualText)) {
             block->setCurvature(Block::GRADUAL);
         } else if (cName == (tightText)) {
             block->setCurvature(Block::TIGHT);
         } else if (cName == (severeText)) {
             block->setCurvature(Block::SEVERE);
         }
         fireTableRowsUpdated(row, row);
         return true;
     }
     case ERR_SENSORCOL:
     {
         bool ok = false;
         try {
             if ((value.toString()).trimmed().length() == 0) {
                 block->setErrorSensor("");
                 ok = true;
             } else {
                 ok = block->setErrorSensor(value.toString());
                 fireTableRowsUpdated(row, row);
             }
         } catch (Exception ex) {
             log->error(tr("getSensor(%1) threw exception: %2").arg(value.toString()).arg(ex.getMessage()));
         }
         if (!ok) {
             JOptionPane::showMessageDialog(nullptr, tr("There is no Sensor named \"%1\".").arg(value.toString()),
                     tr("Error"), JOptionPane::WARNING_MESSAGE);
         }
         fireTableRowsUpdated(row, row);
         return true;
     }
     case REPORTERCOL:
     {
         Reporter* rep = nullptr;
         try {
             rep = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(value.toString());
             if (rep != nullptr) {
                 block->setReporter(rep);
                 fireTableRowsUpdated(row, row);
             }
         } catch (Exception ex) {
             log->error(tr("No Reporter named \"%1\" found. threw exception: %2").arg(value.toString()).arg(ex.getMessage()));
         }
         if (rep == nullptr) {
             JOptionPane::showMessageDialog(nullptr, tr("There is no Reporter named \"%1\.").arg(tempRow[REPORTERCOL]),
                     tr("Error"), JOptionPane::WARNING_MESSAGE);
         }
         block->setReporter(rep);
         fireTableRowsUpdated(row, row);
         return true;
     }
     case REPORT_CURRENTCOL:
         if (block->getReporter() != nullptr) {
             block->setReportingCurrent( value.toBool());
             fireTableRowsUpdated(row, row);
         }
         return true;
     case PERMISSIONCOL:
         block->setPermissiveWorking( value.toBool()); // compare to REPORT_CURRENTCOL
         fireTableRowsUpdated(row, row);
         return true;
     case WARRANTCOL:
     {
         Warrant* warrant = block ->getWarrant();
         WarrantManager* mgr = (WarrantManager*)InstanceManager
                     ::getDefault("WarrantManager");
         Warrant* newWarrant = mgr->getWarrant(value.toString());
         if (warrant != nullptr && !warrant->equals(newWarrant)) {
             block->deAllocate(warrant);
             if (newWarrant != nullptr) {
                 QString msg = block->allocate(newWarrant);
                 if (msg != "") {
                     JOptionPane::showMessageDialog(nullptr, msg,
                             tr("Error"), JOptionPane::WARNING_MESSAGE);
                 }
             }
         }
         fireTableRowsUpdated(row, row);
         return true;
     }
     case SPEEDCOL:
         block->setBlockSpeedName(value.toString());
         fireTableRowsUpdated(row, row);
         return true;
     case EDIT_COL:
         _parent->openBlockPathPane(block->getSystemName(), nullptr); // interface is checked in TableFrames
         return true;
     case DELETE_COL:
         deleteBean(block);
         return true;
     default:
         // fall through
         break;
 }
 BeanTableDataModel::setValueAt(value, row, col);
 return true;
}

/*private*/ /*static*/ bool OBlockTableModel::sensorExists(QString name)
{
 Sensor* sensor = ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->getByUserName(name);
 if (sensor == NULL)
 {
  sensor = ((ProxySensorManager*) InstanceManager::sensorManagerInstance())->getBySystemName(name);
 }
 return (sensor != NULL);
}

//@Override
/*public*/ QVariant OBlockTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal )
 {
  switch (section)
  {
   case COMMENTCOL:
       return tr("Comment");
   case STATECOL:
       return tr("State");
   case SENSORCOL:
       return tr("Sensor");
   case CURVECOL:
       return tr("Curvature");
   case LENGTHCOL:
       return tr("Length");
   case UNITSCOL:
       return "  ";
   case ERR_SENSORCOL:
       return tr("Error Sensor");
   case REPORTERCOL:
       return tr("Reporter");
   case REPORT_CURRENTCOL:
       return tr("Report?");
   case PERMISSIONCOL:
       return tr("Permit?");
   case SPEEDCOL:
       return tr("Speed Notch");
   case EDIT_COL:
       return "  ";
   case DELETE_COL:
       return tr("Delete");
   case WARRANTCOL:
       return tr("Allocated To");
  }
  return BeanTableDataModel::headerData(section,orientation, role);
 }
 return QVariant();
}


void OBlockTableModel::deleteBean(OBlock* bean)
{
 int count = bean->getNumPropertyChangeListeners() - 2; // one is this table, other is manager
 if (log->isDebugEnabled())
 {
     log->debug("Delete with " + QString::number(count) + " remaining listener");
     //java.beans.PropertyChangeSupport pcs = new java.beans.PropertyChangeSupport(bean);
     QVector<PropertyChangeListener*> listener = ((AbstractNamedBean*) bean)->getPropertyChangeListeners();
     for (int i = 0; i < listener.length(); i++) {
         log->debug(QString::number(i) + ") " + QString(listener.at(i)->metaObject()->className()));
     }
 }
 if (!noWarnDelete)
 {
  QString msg;
  if (count > 0) { // warn of listeners attached before delete
      msg = tr("Are you sure you want to delete \"%1\?").arg( bean->getSystemName()) + "\n"
              + tr("It is in use by %1 other objects including.").arg(count);
  } else {
      msg = tr("Are you sure you want to delete %1?").arg(
              bean->getSystemName());
  }

  // verify deletion
        int val = JOptionPane::showOptionDialog(NULL,
                msg, tr("Warning"),
                JOptionPane::YES_NO_CANCEL_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                QVariantList{tr("Yes"),
                    tr("Yes - Stop Warnings"),
                    tr("No")},
                tr("No"));
  if (val == 2) {
      return;  // return without deleting
  }
  if (val == 1) { // suppress future warnings
      noWarnDelete = true;
  }
 }
 // finally OK, do the actual delete
 bean->dispose();
}

//@Override
/*public*/ QString OBlockTableModel::getColumnClass(int col) const {
    switch (col) {
        case CURVECOL:
            return "OBlockTableModel::CurveComboBoxPanel";
        case SPEEDCOL:
            return "OBlockTableModel::SpeedComboBoxPanel"; // apply real combo renderer
        case DELETE_COL:
        case EDIT_COL:
            return "JButton";
        case UNITSCOL:
            return "JToggleButton";
        case REPORT_CURRENTCOL:
            return "JRadioButton";
        case PERMISSIONCOL:
            return "JCheckBox"; // return Boolean.class;
        default:
            return "String";
    }
}

//@Override
/*public*/ int OBlockTableModel::getPreferredWidth(int col)
{
 switch (col)
 {
  case SYSNAMECOL:
      return  JTextField(18).sizeHint().width();
  case USERNAMECOL:
      return  JTextField(18).sizeHint().width();
  case COMMENTCOL:
      return  JTextField(10).sizeHint().width();
  case STATECOL:
      return  JTextField(ZEROS).sizeHint().width();
  case SENSORCOL:
      return  JTextField(15).sizeHint().width();
  case CURVECOL:
      return  JTextField(6).sizeHint().width();
  case LENGTHCOL:
      return  JTextField(5).sizeHint().width();
  case UNITSCOL:
      return  JTextField(2).sizeHint().width();
  case ERR_SENSORCOL:
      return  JTextField(15).sizeHint().width();
  case REPORTERCOL:
      return  JTextField(15).sizeHint().width();
  case REPORT_CURRENTCOL:
      return  JTextField(6).sizeHint().width();
  case PERMISSIONCOL:
      return  JTextField(6).sizeHint().width();
  case SPEEDCOL:
      return  JTextField(8).sizeHint().width();
  case EDIT_COL:
      return  QPushButton("DELETE").sizeHint().width();
  case DELETE_COL:
      return  QPushButton("DELETE").sizeHint().width();
 }
 return 5;
}

//@Override
/*public*/ Qt::ItemFlags OBlockTableModel::flags(const QModelIndex &index) const
{
 if(getRowCount()== index.row()) // the new entry/bottom row is editable in all cells
  return  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 if (BeanTableDataModel::rowCount(QModelIndex()) == index.row())
 {
  if(index.column() == UNITSCOL || index.column() == REPORT_CURRENTCOL || index.row() == PERMISSIONCOL)
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
  return  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 }
 if (index.column() == SYSNAMECOL || index.column() == STATECOL)
 {
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/**
 * Provide a static JComboBox element to display inside the JPanel
 * CellEditor. When not yet present, create, store and return a new one.
 *
 * @param row Index number (in TableDataModel)
 * @return A combobox containing the valid aspect names for this mast
 */
/*static*/ JComboBox* OBlockTableModel::getSpeedEditorBox(int row) {
    // create dummy comboBox, override in extended classes for each bean
    JComboBox* editCombo = new JComboBox(((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames().toList());
#if 0 // TODO:
    editCombo->putClientProperty("JComponent.sizeVariant", "small");
    editCombo->putClientProperty("JComboBox.buttonType", "square");
#endif
    return editCombo;
}

/**
 * Customize the Turnout column to show an appropriate ComboBox of
 * available options.
 *
 * @param table a JTable of beans
 */
/*public*/ void OBlockTableModel::configSpeedColumn(JTable* table) {
    // have the state column hold a JPanel with a JComboBox for Speeds
#if 0
    table->setDefaultEditor("OBlockTableModel::SpeedComboBoxPanel", new OBlockTableModel::SpeedComboBoxPanel());
    table->setDefaultRenderer("OBlockTableModel::SpeedComboBoxPanel", new OBlockTableModel::SpeedComboBoxPanel()); // use same class as renderer
#else
    table->setDefaultEditor("OBlockTableModel::SpeedComboBoxPanel", new JComboBoxEditor(((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames().toList()));
    table->setDefaultRenderer("OBlockTableModel::SpeedComboBoxPanel", new JComboBoxEditor(((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames().toList()));
#endif
    // Set more things?
}
//@Override
/*public*/ void OBlockTableModel::propertyChange(PropertyChangeEvent* e)
{
 BeanTableDataModel::propertyChange(e);
 QString property = e->getPropertyName();
 if (log->isDebugEnabled()) log->debug(tr("PropertyChange = %1").arg(property));
 _parent->getPortalXRefTableModel()->propertyChange(e);
 _parent->getSignalTableModel()->propertyChange(e);
 _parent->getPortalTableModel()->propertyChange(e);

 if (property == ("length") || property ==("UserName")) {
     _parent->updateOBlockTablesMenu();
 }
}

OBSComboBoxDelegate::OBSComboBoxDelegate(QAbstractTableModel* model,  QStringList items, QObject *parent)
:QItemDelegate(parent)
{
 this->model  = model;
 this->items = items;
}

QWidget* OBSComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index ) const
{
 QComboBox* editor = new QComboBox(parent);
 editor->addItems(items);
 return editor;
}

void OBSComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  QString value = index.model()->data(index, Qt::DisplayRole).toString();
  comboBox->setCurrentText(value);
}

void OBSComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void OBSComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

//void OBSComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
// JComboBox* widget = new JComboBox(items);
// setEditorData(widget, index);
// widget->resize(option.rect.size());
// QPixmap pixmap(option.rect.size());
// widget->render(&pixmap);
// painter->save();
// painter->drawPixmap(option.rect,pixmap);
// painter->restore();
//}

/**
* Provide a static JComboBox element to display inside the JPanel
* CellEditor. When not yet present, create, store and return a new one.
*
* @param row Index number (in TableDataModel)
* @return A combobox containing the valid aspect names for this mast
*/
/*static*/ JComboBox/*<String>*/* OBlockTableModel::getCurveEditorBox(int row) {
 // create dummy comboBox, override in extended classes for each bean
 JComboBox/*<String>*/* editCombo = new JComboBox(curveOptions);
#if 0
 editCombo->putClientProperty("JComponent.sizeVariant", "small");
 editCombo->putClientProperty("JComboBox.buttonType", "square");
#endif
 return editCombo;
}

/**
* Customize the Turnout column to show an appropriate ComboBox of
* available options.
*
* @param table a JTable of beans
*/
/*public*/ void OBlockTableModel::configCurveColumn(JTable* table) {
 // have the state column hold a JPanel with a JComboBox for Curvature
#if 0
 table->setDefaultEditor("OBlockTableModel::CurveComboBoxPanel", new OBlockTableModel::CurveComboBoxPanel());
 table->setDefaultRenderer("OBlockTableModel::CurveComboBoxPanel", new OBlockTableModel::CurveComboBoxPanel()); // use same class as renderer
#else
 table->setDefaultEditor("OBlockTableModel::CurveComboBoxPanel", new JComboBoxEditor(curveOptions));
 table->setDefaultRenderer("OBlockTableModel::CurveComboBoxPanel", new JComboBoxEditor(curveOptions)); // use same class as renderer
 // Set more things?
#endif
 // Set more things?
}
