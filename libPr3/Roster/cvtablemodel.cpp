#include "cvtablemodel.h"
#include "rosterentry.h"
#include "jtable.h"
#include "pushbuttondelegate.h"
#include <QSortFilterProxyModel>
#include "programmer.h"
#include "jtextfield.h"

/**
 * Table data model for display of CvValues in symbolic programmer.
 * <P>This represents the contents of a single decoder, so the
 * Programmer used to access it is a data member.
 *
 * @author    Bob Jacobsen   Copyright (C) 2001, 2002, 2006
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 17977 $
 */
//public class CvTableModel extends javax.swing.table.AbstractTableModel implements ActionListener, PropertyChangeListener {

//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();
/*public*/ QMap<QString, CvValue*>* CvTableModel::allCvMap() { return _cvAllMap; }


/*public*/ QLabel* CvTableModel::getStatusLabel() { return _status;}

/*public*/ CvTableModel::CvTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent) : AbstractTableModel(parent)
{
 //super();
 _numRows = 0;                // must be zero until Vectors are initialized
 log = new Logger("CvTableModel");
 log->setDebugEnabled(true);
 _cvDisplayVector = new QVector<CvValue*>();  // vector of CvValue objects, in display order
 _cvAllMap = new QMap<QString, CvValue*>();
// _writeButtons = new QVector<QPushButton*>();
// _readButtons = new QVector<QPushButton*>();
// _compareButtons = new QVector<QPushButton*>();
// readMapper = new QSignalMapper(this);
// connect(readMapper, SIGNAL(mapped(QString)), this, SLOT(actionPerformed(QString)));
// writeMapper = new QSignalMapper(this);
// connect(writeMapper, SIGNAL(mapped(QString)), this, SLOT(actionPerformed(QString)));
// compareMapper = new QSignalMapper(this);
// connect(compareMapper, SIGNAL(mapped(QString)), this, SLOT(actionPerformed(QString)));

  mProgrammer = pProgrammer;
 // save a place for notification
 _status = status;
 // initialize the MAXCVNUM+1 long _cvAllVector;
 //for (int i=0; i<=MAXCVNUM; i++) _cvAllVector->append(NULL);

    // define just address CV at start, pending some variables
    // boudreau: not sure why we need the statement below,
    // messes up building CV table for CV #1 when in ops mode.
    //addCV("1", false, false, false);
}

/**
 * Gives access to the programmer used to reach these CVs, so
 * you can check on mode, capabilities, etc.
 * @return Programmer object for the CVs
 */
/*public*/ Programmer* CvTableModel::getProgrammer() const{
    return mProgrammer;
}
/*public*/ void CvTableModel::setProgrammer(Programmer* p)
{
 mProgrammer = p;
 // tell all variables
 foreach (CvValue* cv, allCvMap()->values())
 {
  if (cv!=NULL) cv->setProgrammer(p);
 }
 foreach (CvValue* cv, *_cvDisplayVector)
 {
  if (cv!=NULL) cv->setProgrammer(p);
 }
}
// basic methods for AbstractTableModel implementation
/*public*/ int CvTableModel::rowCount(const QModelIndex &parent) const { return _numRows; }

/*public*/ int CvTableModel::columnCount(const QModelIndex &parent) const
{
    if (getProgrammer()!=NULL)
        return HIGHESTCOLUMN;
    else
        return HIGHESTNOPROG;
}

/*public*/ QString CvTableModel::getColumnName(int col) const
{
 switch (col)
 {
    case NUMCOLUMN: return tr("CV Number");
    case VALCOLUMN: return tr("Value (decimal)");
    case STATECOLUMN: return tr("State");
    case READCOLUMN: return tr("Read");
    case WRITECOLUMN: return tr("Write");
    case COMPARECOLUMN: return tr("Compare");
    default: return "unknown";
 }
}

/*public*/ QString CvTableModel::getColumnClass(int col) const {
    switch (col) {
    case NUMCOLUMN: return "QString";
    case VALCOLUMN: return "QLineEdit";
    case STATECOLUMN: return "QString";
    case READCOLUMN: return "QPushButton";
    case WRITECOLUMN: return "QPushButton";
    case COMPARECOLUMN: return "QPushButton";
    default: return "";
    }
}

/*public*/ bool CvTableModel::isCellEditable(int row, int col) const
{
 switch (col)
 {
  case NUMCOLUMN: return false;
  case VALCOLUMN:
   if (_cvDisplayVector->at(row)->getReadOnly() ||
             _cvDisplayVector->at(row)->getInfoOnly() )
   {
    return false;
   }
   else
   {
    return true;
   }
  case STATECOLUMN: return false;
  case READCOLUMN: return true;
  case WRITECOLUMN: return true;
  case COMPARECOLUMN: return true;
   default: return false;
 }
}

/*public*/ QString CvTableModel::getName(int row) {  // name is text number
    return (_cvDisplayVector->at(row)->number());
}

/*public*/ QString CvTableModel::getValString(int row) {
    return QString::number(_cvDisplayVector->at(row)->getValue());
}

/*public*/ CvValue* CvTableModel::getCvByRow(int row) const { return _cvDisplayVector->at(row); }

/*public*/ CvValue* CvTableModel::getCvByNumber(QString number) { return _cvAllMap->value(number); }

/*public*/ QVariant CvTableModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 CvValue* val = getCvByRow(index.row());

 if (role == Qt::BackgroundRole )
 {
  int i = Qt::green;
  switch(index.column())
  {
  case VALCOLUMN:
   return QBrush(val->getColor());
  case STATECOLUMN:
  {
   int state = val->getState();
   switch (state)
   {
    case CvValue::UNKNOWN:  	return QBrush(val->COLOR_UNKNOWN);
    case CvValue::READ:  		return QBrush(val->COLOR_READ);
    case CvValue::EDITED:  		return QBrush(val->COLOR_EDITED);
    case CvValue::STORED:  		return QBrush(val->COLOR_STORED);
    case CvValue::FROMFILE:  	return QBrush(val->COLOR_FROMFILE);
    case CvValue::SAME:  		return QBrush(val->COLOR_SAME);
    case CvValue::DIFF:  		return QBrush(val->COLOR_DIFF);
    default: return QBrush(val->COLOR_UNKNOWN);
   }
  }
  }
  return QVariant();
 }
// if (role == Qt::ForegroundRole )
// {
//  CvValue* val = getCvByRow(index.row());
//  int i = Qt::green;
//  switch(index.column())
//  {
//  case VALCOLUMN:
//   return QColor(Qt::black);
//  }
// }
 if(role == Qt::DisplayRole /*|| role == Qt::EditRole*/)
 {
  switch (index.column())
  {
   case NUMCOLUMN:
    return val->number().toInt();
   case VALCOLUMN:
    return val->getValue();
   case STATECOLUMN:
   {
    int state = val->getState();
    switch (state)
    {
     case CvValue::UNKNOWN:  	return tr("Unknown");
     case CvValue::READ:  		return tr("Read");
     case CvValue::EDITED:  		return tr("Edited");
     case CvValue::STORED:  		return tr("Stored");
     case CvValue::FROMFILE:  	return tr("From File");
     case CvValue::SAME:  		return tr("Same");
     case CvValue::DIFF:  		return tr("Diff")+ " " + _cvDisplayVector->at(row)->getDecoderValue();
     default: return "inconsistent";
    }
   }
   case READCOLUMN:
        return tr("Read");
   case WRITECOLUMN:
        return tr("Write");
   case COMPARECOLUMN:
        return tr("Compare");
   default: break;
  }
 }
 return QVariant();
}

/*public*/ bool CvTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int col = index.column();
  int row = index.row();
  switch (col)
  {
   case VALCOLUMN: // Object is actually an Integer
    if (_cvDisplayVector->at(row)->getValue() != value.toInt())
    {
     _cvDisplayVector->at(row)->setValue(value.toInt());
    }
    break;
   case READCOLUMN:
    _cvDisplayVector->at(row)->read(_status);
    break;
   case WRITECOLUMN:
    _cvDisplayVector->at(row)->write(_status);
    break;
   case COMPARECOLUMN:
    _cvDisplayVector->at(row)->confirm(_status);
    break;
   default:
    break;
  }
  fireTableRowsUpdated(row, row);
  return true;
 }
 return false;
}

///*public*/ void CvTableModel::actionPerformed(QString action)
//{
//    if (log->isDebugEnabled()) log->debug("action command: "+action);
//    QChar b = action.at(0);
//    int row = action.mid(1).toInt();
//    if (log->isDebugEnabled()) log->debug("event on "+QString(b)+" row "+QString::number(row));
//    if (b=='R') {
//        // read command
//        _cvDisplayVector->at(row)->read(_status);
//    } else if (b=='C'){
//        // compare command
//        _cvDisplayVector->at(row)->confirm(_status);
//    } else {
//        // write command
//        _cvDisplayVector->at(row)->write(_status);
//    }
//}

/*public*/ void CvTableModel::propertyChange(PropertyChangeEvent* e)
{
 fireTableDataChanged();
 CvValue* val = (CvValue*)e->getSource();
 int i = _cvDisplayVector->indexOf(val);
 //emit modelChange(val, i);
 QModelIndex m = index(i, 1);
 if(_table == NULL) return;
 if(qobject_cast<QSortFilterProxyModel*>(_table->model()) != NULL)
 {
  QAbstractItemModel * model = (QSortFilterProxyModel*)_table->model();
  _table->scrollTo(((QSortFilterProxyModel*)model)->mapFromSource(m));
 }
 else
  _table->scrollTo(m);
}

/*public*/ void CvTableModel::addCV(QString s, bool readOnly, bool infoOnly, bool writeOnly)
{
 if (_cvAllMap->value(s) == NULL)
 {
  CvValue* cv = new CvValue(s, mProgrammer);
  cv->setReadOnly(readOnly);
  _cvAllMap->insert(s, cv);
  _cvDisplayVector->append(cv);
  // connect to this CV to ensure the table display updates
  cv->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(cv, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  _numRows++;
  fireTableDataChanged();
 }
 // make sure readonly set true if required
 CvValue* cv = _cvAllMap->value(s);
 if (readOnly) cv->setReadOnly(readOnly);
 if (infoOnly)
 {
  cv->setReadOnly(infoOnly);
  cv->setInfoOnly(infoOnly);
 }
 if (writeOnly) cv->setWriteOnly(writeOnly);
}

void CvTableModel::configureTable(JTable *cvTable)
{
 if(_table == NULL)
  _table = cvTable;
 //cvTable->setItemDelegateForColumn(VALCOLUMN, new ValueRenderer());
 setColumnToHoldButton(cvTable,READCOLUMN);
 setColumnToHoldButton(cvTable, WRITECOLUMN);
 setColumnToHoldButton(cvTable, COMPARECOLUMN);
 //setPersistentButtons();
}

/*public*/ bool CvTableModel::decoderDirty()
{
 int len = _cvDisplayVector->size();
 bool bDirty = false;
 for (int i=0; i< len; i++)
 {
  if (_cvDisplayVector->at(i)->getState() == CvValue::EDITED )
  {
   if (log->isDebugEnabled())
    log->debug("CV decoder dirty due to "+(_cvDisplayVector->at(i)->number()));
   //return true;
   bDirty = true;
  }
 }
 return bDirty;
}

/*public*/ void CvTableModel::resetDecoderDirty(int newStatus)
{
 int len = _cvDisplayVector->size();

 for(int i=0; i < len; i++)
 {
  if (_cvDisplayVector->at(i)->getState() == CvValue::EDITED )
  {
   _cvDisplayVector->at(i)->resetStatus(newStatus);
   log->debug("CV  state reset decoder  "+(_cvDisplayVector->at(i)->number()));
  }
 }
}

/*public*/ void CvTableModel::dispose()
{
 if (log->isDebugEnabled()) log->debug("dispose");

 // remove buttons
//    for (int i = 0; i<_writeButtons->size(); i++) {
//        _writeButtons->at(i)->removeActionListener(this);
//    }
//    for (int i = 0; i<_readButtons->size(); i++) {
//        _readButtons->at(i)->removeActionListener(this);
//    }
//    for (int i = 0; i<_compareButtons->size(); i++) {
//        _compareButtons->at(i)->removeActionListener(this);
//    }

 // remove CV listeners
 for (int i = 0; i<_cvDisplayVector->size(); i++)
 {
  _cvDisplayVector->at(i)->removePropertyChangeListener((PropertyChangeListener*)this);
  disconnect(_cvDisplayVector->at(i), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 // NULL references, so that they can be gc'd even if this isn't.
 _cvDisplayVector->clear();
 _cvDisplayVector = NULL;

 _cvAllMap->clear();
 _cvAllMap = NULL;

//    _writeButtons->clear();
//    _writeButtons = NULL;

//    _readButtons->clear();
//    _readButtons = NULL;

//    _compareButtons->clear();
//    _compareButtons = NULL;

 _status = NULL;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CvTableModel.class.getName());
//}
