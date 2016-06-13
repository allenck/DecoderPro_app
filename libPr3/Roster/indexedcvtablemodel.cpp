#include "indexedcvtablemodel.h"
#include "abstracttablemodel.h"
#include "rosterentry.h"

IndexedCvTableModel::IndexedCvTableModel(QObject *parent) :
    AbstractTableModel(parent)
{
    log = new Logger("IndexedTableModel");
    _numRows = 0;                // must be zero until Vectors are initialized
    _indxCvDisplayVector = new QVector<CvValue*>();  // vector of CvValue objects, in display order
    _indxCvAllMap = new QMap<QString, CvValue*>();  // All existing indexed CV objects
    _indxWriteButtons = new QVector<QPushButton*>();
    _indxReadButtons = new QVector<QPushButton*>();
    _indxCompareButtons = new QVector<QPushButton*>();
    _progState = 0;
    retries = 0;
}
/**
 * Table data model for display of IndexedCvValues in symbolic programmer.
 *
 * This represents the contents of a single decoder, so the
 * Programmer used to access it is a data member.
 *
 * @author    Howard G. Penny   Copyright (C) 2005
 * @author 		Daniel Boudreau Copyright (C) 2007
 * @version   $Revision: 18768 $
// */
///*public*/ class IndexedCvTableModel extends javax.swing.table.AbstractTableModel implements ActionListener, PropertyChangeListener {

//    static final java.util.ResourceBundle rbt = jmri.jmrit.symbolicprog.SymbolicProgBundle.bundle();


/*public*/ QLabel* IndexedCvTableModel::getStatusLabel() { return _status;}

/*public*/ IndexedCvTableModel::IndexedCvTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent) : AbstractTableModel(parent)
{
    //super();
    log = new Logger("IndexedTableModel");
    _numRows = 0;                // must be zero until Vectors are initialized
    _indxCvDisplayVector = new QVector<CvValue*>();  // vector of CvValue objects, in display order
    _indxCvAllVector = new QVector<CvValue*>(MAXCVNUM + 1);  // vector of all possible indexed CV objects
    _indxCvAllMap = new QMap<QString, CvValue*>();  // vector of all possible indexed CV objects
    _indxWriteButtons = new QVector<QPushButton*>();
    _indxReadButtons = new QVector<QPushButton*>();
    _indxCompareButtons = new QVector<QPushButton*>();
    mProgrammer = pProgrammer;
    // save a place for notification
    _status = status;
    // initialize the MAXCVNUM+1 long _cvAllVector;
    for (int i=0; i<=MAXCVNUM; i++) _indxCvAllVector->append(NULL);
    _progState = 0;
    retries = 0;
}
/*public*/  QVector<CvValue*>* IndexedCvTableModel::allIndxCvVector() { return _indxCvAllVector; }
/*public*/  QMap<QString, CvValue*>* IndexedCvTableModel::allIndxCvMap() { return _indxCvAllMap; }
/**
 * Find the existing IndexedCV
 * that matches a particular name
 */
/*public*/ CvValue* IndexedCvTableModel::getMatchingIndexedCV(QString name)
{
 for (int i = 0; i<_numRows; i++)
 {
  CvValue* cv = _indxCvAllVector->at(i);
  if (cv == NULL)
  {
   // no longer should run off end
   log->error("cv == NULL in getMatchingIndexedCV");
   break;
  }
  if (cv->cvName()==(name))
  {
   return cv;
  }
 }
 return NULL;
}

/**
 * Gives access to the programmer used to reach these Indexed CVs,
 * so you can check on mode, capabilities, etc.
 * @return Programmer object for the Indexed CVs
 */
/*public*/ Programmer* IndexedCvTableModel::getProgrammer() {
    return mProgrammer;
}
void IndexedCvTableModel::setTable(QTableView * table) {_table = table;}
// basic methods for AbstractTableModel implementation
/*public*/ int IndexedCvTableModel::rowCount(const QModelIndex &/*parent*/) const { return _numRows; }

/*public*/ int IndexedCvTableModel::columnCount(const QModelIndex &/*parent*/) const{ return HIGHESTCOLUMN;}

/*public*/ QVariant IndexedCvTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal)
 {
    switch (section) {
    case NAMECOLUMN:  return tr("Number");
    case PICOLUMN:    return "PI Val";
    case SICOLUMN:    return "SI Val";
    case CVCOLUMN:    return "CV Num";
    case VALCOLUMN:   return tr("Value");
    case STATECOLUMN: return tr("State");
    case READCOLUMN:  return tr("Read");
    case WRITECOLUMN: return tr("Write");
    case COMPARECOLUMN: return tr("Compare");
    default: break;
    }
 }
 return QVariant();
}

/*public*/ QString IndexedCvTableModel::getColumnClass(int col) {
    switch (col) {
    case NAMECOLUMN:  return "QString";
    case PICOLUMN:    return "QString";
    case SICOLUMN:    return "QString";
    case CVCOLUMN:    return "QString";
    case VALCOLUMN:   return "QLineEdit";
    case STATECOLUMN: return "QString";
    case READCOLUMN:  return "QPushButton";
    case WRITECOLUMN: return "QPushButton";
    case COMPARECOLUMN: return "QPushButton";
    default: return "";
    }
}

/*public*/ bool IndexedCvTableModel::isCellEditable(int row, int col) {
    switch (col) {
    case NAMECOLUMN:  return false;
    case PICOLUMN:    return false;
    case SICOLUMN:    return false;
    case CVCOLUMN:    return false;
    case VALCOLUMN:
        if (_indxCvDisplayVector->at(row)->getReadOnly() ||
             _indxCvDisplayVector->at(row)->getInfoOnly() ) {
            return false;
        } else {
            return true;
        }
    case STATECOLUMN: return false;
    case READCOLUMN:  return true;
    case WRITECOLUMN: return true;
    case COMPARECOLUMN: return true;
    default: return false;
    }
}

/*public*/ QString IndexedCvTableModel::getName(int row) {  // name is text number
    return _indxCvDisplayVector->at(row)->cvName();
}

/*public*/ QString IndexedCvTableModel::getValString(int row) {
    return QString::number(_indxCvDisplayVector->at(row)->getValue());
}

/*public*/ int IndexedCvTableModel::getCvByName(QString name) {
    int row = 0;
    while(row < _numRows) {
        if(_indxCvDisplayVector->at(row)->cvName().compare(name) == 0) {
            return row;
        }
        row++;
    }
    return -1;
}

/*public*/ CvValue* IndexedCvTableModel::getCvByRow(int row) { return _indxCvDisplayVector->at(row); }
/*public*/ CvValue* IndexedCvTableModel::getCvByNumber(int row) { return _indxCvAllVector->at(row); }

/*public*/ QVariant IndexedCvTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::EditRole || role == Qt::DisplayRole)
 {
     int row = index.row();
     int col = index.column();
    // some error checking
    if (row >= _indxCvDisplayVector->size()){
        log->debug("row greater than cv index");
        return "Error";
    }
    switch (col) {
        case NAMECOLUMN:
            return (_indxCvDisplayVector->at(row))->cvName();
        case PICOLUMN:
            return QString::number((_indxCvDisplayVector->at(row))->piVal());
        case SICOLUMN:
            return QString::number((_indxCvDisplayVector->at(row))->siVal());
        case CVCOLUMN:
            return ((_indxCvDisplayVector->at(row))->iCv());
        case VALCOLUMN:
            return VPtr<JTextField>::asQVariant(_indxCvDisplayVector->at(row)->getTableEntry());
        case STATECOLUMN:
        {
            int state = (_indxCvDisplayVector->at(row))->getState();
            switch (state) {
                case CvValue::UNKNOWN:  	return tr("CvStateUnknown");
                case CvValue::READ:  		return tr("CvStateRead");
                case CvValue::EDITED:  		return tr("CvStateEdited");
                case CvValue::STORED:  		return tr("CvStateStored");
                case CvValue::FROMFILE:  	return tr("CvStateFromFile");
                case CvValue::SAME:  		return tr("CvStateSame");
                case CvValue::DIFF:  		return tr("CvStateDiff")+ " " +
                                            QString::number(_indxCvDisplayVector->at(row)->getDecoderValue());
                default: return "inconsistent";
            }
        }
        case READCOLUMN:
            return VPtr<QPushButton>::asQVariant(_indxReadButtons->at(row));
        case WRITECOLUMN:
            return VPtr<QPushButton>::asQVariant(_indxWriteButtons->at(row));
        case COMPARECOLUMN:
            return VPtr<QPushButton>::asQVariant(_indxCompareButtons->at(row));
        default: break;
    }
 }
 return QVariant();
}

/*public*/ void IndexedCvTableModel::setValueAt(QVariant value, int row, int col)
{
 switch (col)
 {
  case VALCOLUMN: // Object is actually an Integer
   if ((_indxCvDisplayVector->at(row))->getValue() != value.toInt())
   {
    ( _indxCvDisplayVector->at(row))->setValue(value.toInt());
   }
   break;
  default:
  break;
 }
}

/*public*/ void IndexedCvTableModel::actionPerformed(QEvent /*e*/)
{
#if 0
    if (log->isDebugEnabled()) log->debug("action command: "+e.getActionCommand());
    char b = e.getActionCommand().charAt(0);
    int row = Integer.valueOf(e.getActionCommand().substring(1)).intValue();
    _row = row;
    if (log->isDebugEnabled()) log->debug("event on "+b+" row "+row);
    if (b=='R') {
        // read command
        indexedRead();
    } else if (b=='C'){
        // compare command
        indexedCompare();
    } else {
        // write command
        indexedWrite();
    }
#endif
}



/*public*/ void IndexedCvTableModel::indexedRead() {
    if (_progState != IDLE) log->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    // lets skip the SI step if SI is not used
    if ((_indxCvDisplayVector->at(_row))->siVal() >= 0) {
        _progState = WRITING_PI4R;
    } else {
        _progState = WRITING_SI4R;
    }
    retries = 0;
    if (log->isDebugEnabled()) log->debug("invoke PI write for CV read");
    // to read any indexed CV we must write the PI
    (_indxCvDisplayVector->at(_row))->writePI(_status);
}

/*public*/ void IndexedCvTableModel::indexedWrite() {
    if ((_indxCvDisplayVector->at(_row))->getReadOnly()) {
        log->error("unexpected write operation when readOnly is set");
    }
    if (_progState != IDLE) log->warn("Programming state "+QString::number(_progState)+", not IDLE, in write()");
    // lets skip the SI step if SI is not used
    if ((_indxCvDisplayVector->at(_row))->siVal() >= 0) {
        _progState = WRITING_PI4W;
    } else {
        _progState = WRITING_SI4W;
    }
    retries = 0;
    if (log->isDebugEnabled()) log->debug("invoke PI write for CV write");
    // to write any indexed CV we must write the PI
    (_indxCvDisplayVector->at(_row))->writePI(_status);
}

/*public*/ void IndexedCvTableModel::indexedCompare() {
    if (_progState != IDLE) log->warn("Programming state "+QString::number(_progState)+", not IDLE, in read()");
    // lets skip the SI step if SI is not used
    if ((_indxCvDisplayVector->at(_row))->siVal() >= 0) {
        _progState = WRITING_PI4C;
    } else {
        _progState = WRITING_SI4C;
    }
    retries = 0;
    if (log->isDebugEnabled()) log->debug("invoke PI write for CV compare");
    // to read any indexed CV we must write the PI
    (_indxCvDisplayVector->at(_row))->writePI(_status);
}

/*public*/ void IndexedCvTableModel::propertyChange(PropertyChangeEvent* e) {

    if (log->isDebugEnabled()) log->debug("Property changed: "+e->getPropertyName());
    // notification from Indexed CV; check for Value being changed
    if (e->getPropertyName()==("Busy") && (e->getNewValue().toBool()== false)) {
        // busy transitions drive the state
        switch (_progState) {
        case IDLE:  // no, just an Indexed CV update
            if (log->isDebugEnabled()) log->error("Busy goes false with state IDLE");
            return;
        case WRITING_PI4R:   // have written the PI, now write SI if needed
        case WRITING_PI4C:
        case WRITING_PI4W:
            if (log->isDebugEnabled()) log->debug("Busy goes false with state WRITING_PI");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_indxCvDisplayVector->at(_row))->getState() != CvValue::STORED) ) {
                // need to retry on error; leave progState as it was
                log->debug("retry");
                retries++;
                (_indxCvDisplayVector->at(_row))->writePI(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            if (_progState == WRITING_PI4R )
                _progState = WRITING_SI4R;
            else if (_progState == WRITING_PI4C )
                _progState = WRITING_SI4C;
            else
                _progState = WRITING_SI4W;
            (_indxCvDisplayVector->at(_row))->writeSI(_status);
            return;
        case WRITING_SI4R:  // have written the SI if needed, now read or write CV
        case WRITING_SI4C:
        case WRITING_SI4W:
            if (log->isDebugEnabled()) log->debug("Busy goes false with state WRITING_SI");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_indxCvDisplayVector->at(_row))->getState() != CvValue::STORED) ) {
                // need to retry on error; leave progState as it was
                log->debug("retry");
                retries++;
                (_indxCvDisplayVector->at(_row))->writeSI(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            if (_progState == WRITING_SI4R ) {
                _progState = READING_CV;
                (_indxCvDisplayVector->at(_row))->readIcV(_status);
            } else if (_progState == WRITING_SI4C ) {
                _progState = COMPARE_CV;
                (_indxCvDisplayVector->at(_row))->confirmIcV(_status);
             } else {
                _progState = WRITING_CV;
                (_indxCvDisplayVector->at(_row))->writeIcV(_status);
            }
            return;
        case READING_CV:  // now done with the read request
            if (log->isDebugEnabled()) log->debug("Finished reading the Indexed CV");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_indxCvDisplayVector->at(_row))->getState() != CvValue::READ) ) {
                // need to retry on error; leave progState as it was
                log->debug("retry");
                retries++;
                (_indxCvDisplayVector->at(_row))->readIcV(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            _progState = IDLE;
            return;
        case COMPARE_CV:  // now done with the read request
            if (log->isDebugEnabled()) log->debug("Finished reading the Indexed CV for compare");

            // check for success SAME or DIFF?
            if ((retries < RETRY_MAX)
                    && (( _indxCvDisplayVector->at(_row))
                            ->getState() != CvValue::SAME)
                    && (( _indxCvDisplayVector->at(_row))
                            ->getState() != CvValue::DIFF)) {
                // need to retry on error; leave progState as it was
                log->debug("retry");
                retries++;
                (_indxCvDisplayVector->at(_row))->confirmIcV(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            _progState = IDLE;
            return;
        case WRITING_CV:  // now done with the write request
            if (log->isDebugEnabled()) log->debug("Finished writing the Indexed CV");

            // check for success
            if ((retries < RETRY_MAX)
                && ( (_indxCvDisplayVector->at(_row))->getState() != CvValue::STORED) ) {
                // need to retry on error; leave progState as it was
                log->debug("retry");
                retries++;
                (_indxCvDisplayVector->at(_row))->writeIcV(_status);
                return;
            }
            // success, move on to next
            retries = 0;

            _progState = IDLE;
            return;
        default:  // unexpected!
            log->error("Unexpected state found: "+_progState);
            _progState = IDLE;
            return;
        }
    }
    fireTableDataChanged();
}

/**
 * return is the current row or the row of an existing Indexed CV
 */
/*public*/ int IndexedCvTableModel::addIndxCV(QString cvName,
                     QString piCv, int piVal,
                     QString siCv, int siVal,
                     QString iCv,
                     bool readOnly, bool infoOnly, bool writeOnly) {
    int existingRow = getCvByName(cvName);
    int row = 0;
    if (existingRow == -1) {
        // we'll be adding a new entry or replacing an existing one; where?
        row = _numRows++;

        // create new entry
        CvValue* indxCv = new CvValue(cvName, cvName, piCv, piVal, siCv, siVal, iCv, mProgrammer);
        _indxCvAllMap->insert(cvName, indxCv);
        indxCv->setReadOnly(readOnly);
        indxCv->setInfoOnly(infoOnly);
        //_indxCvAllVector->setElementAt(indxCv, row);
        _indxCvAllVector->replace(row,indxCv);
        _indxCvDisplayVector->append(indxCv);
        // connect to this Indexed CV to ensure the table display updates
        indxCv->addPropertyChangeListener((PropertyChangeListener*)this);

        QPushButton* bw = new QPushButton("Write");
        _indxWriteButtons->append(bw);
        QPushButton* br = new QPushButton("Read");
        _indxReadButtons->append(br);
        QPushButton* bc = new QPushButton("Compare");
        _indxCompareButtons->append(bc);

        if (infoOnly || readOnly) {
            if (writeOnly) {
                bw->setEnabled(true);
//                bw->setActionCommand("W"+row);
//                bw->addActionListener(this);
            } else {
                bw->setEnabled(false);
            }
            if (infoOnly) {
                br->setEnabled(false);
                bc->setEnabled(false);
            } else {
                br->setEnabled(true);
//                br->setActionCommand("R"+row);
//                br->addActionListener(this);
                bc->setEnabled(true);
//                bc->setActionCommand("C"+row);
//                bc->addActionListener(this);
            }
        } else {
            bw->setEnabled(true);
//            bw->setActionCommand("W"+row);
//            bw->addActionListener(this);
            if (writeOnly) {
                br->setEnabled(false);
                bc->setEnabled(false);
            } else {
                br->setEnabled(true);
//                br->setActionCommand("R" + row);
//                br->addActionListener(this);
                bc->setEnabled(true);
//                bc.setActionCommand("C" + row);
//                bc->addActionListener(this);
            }
       }
       if (log->isDebugEnabled()) log->debug("addIndxCV adds row at "+row);
        fireTableDataChanged();
    } else { // this one already exists
       if (log->isDebugEnabled())
            log->debug("addIndxCV finds existing row of "+QString::number(existingRow)+" with numRows "+QString::number(_numRows));
        row = existingRow;
    }
    // make sure readonly set true if required
    if (row > -1 && row < _indxCvAllVector->size() )
    {
        CvValue* indxcv =  _indxCvAllVector->at(row);
        if (readOnly) indxcv->setReadOnly(readOnly);
        if (infoOnly) {
            indxcv->setReadOnly(infoOnly);
            indxcv->setInfoOnly(infoOnly);
        }
        if (writeOnly) indxcv->setWriteOnly(writeOnly);
    }
    return row;
}

/*public*/ bool IndexedCvTableModel::decoderDirty() {
    int len = _indxCvDisplayVector->size();
    for (int i=0; i< len; i++) {
        if (((_indxCvDisplayVector->at(i)))->getState() == CvValue::EDITED ) {
            if (log->isDebugEnabled())
                log->debug("CV decoder dirty due to "+(_indxCvDisplayVector->at(i)->number()));
            return true;
        }
    }
    return false;
}

/*public*/ void IndexedCvTableModel::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");

    // remove buttons
    //    for (int i = 0; i<_indxWriteButtons->size(); i++) {
    //        _indxWriteButtons->at(i)->removeActionListener(this);
    //    }
    //    for (int i = 0; i<_indxReadButtons->size(); i++) {
    //        _indxReadButtons->at(i)->removeActionListener(this);
    //    }
    //    for (int i = 0; i<_indxCompareButtons->size(); i++) {
    //        _indxCompareButtons->at(i)->removeActionListener(this);
    //    }

    // remove CV listeners
    for (int i = 0; i<_indxCvDisplayVector->size(); i++) {
        (_indxCvDisplayVector->at(i))->removePropertyChangeListener((PropertyChangeListener*)this);
    }

    // NULL references, so that they can be gc'd even if this isn't.
    _indxCvDisplayVector->clear();
    _indxCvDisplayVector = NULL;

    _indxCvAllVector->clear();
    _indxCvAllVector = NULL;

    _indxWriteButtons->clear();
    _indxWriteButtons = NULL;

    _indxReadButtons->clear();
    _indxReadButtons = NULL;

    _indxCompareButtons->clear();
    _indxCompareButtons = NULL;

    _status = NULL;
}


/*public*/ void IndexedCvTableModel::setProgrammer(Programmer* p) {
    mProgrammer = p;

    // tell all existing
    foreach(CvValue* cv, *_indxCvDisplayVector)
    {
        if (cv!=NULL) cv->setProgrammer(p);
    }
    foreach (CvValue* cv, *_indxCvAllVector) {
        if (cv!=NULL) cv->setProgrammer(p);
    }
}
