#include "resettablemodel.h"
#include "variablevalue.h"
#include "actionlistener.h"
#include "rosterentry.h"
#include "programmingmode.h"
#include "joptionpane.h"


//ResetTableModel::ResetTableModel(QObject *parent) :
//    AbstractTableModel(parent)
//{
//}
/**
 * Creates a table of the available factory resets available for a
 * particular decoder.
 *
 * @author    Howard G. Penny    Copyright (C) 2005
 * @version   $Revision: 17977 $
 */
// /*public*/ class ResetTableModel extends AbstractTableModel implements ActionListener, PropertyChangeListener {

/*public*/ ResetTableModel::ResetTableModel(QLabel* status, Programmer* pProgrammer, QObject *parent) : AbstractTableModel(parent)
{
 //super();
 log = new Logger("ResetTableModel");
 headers = new QStringList;
 *headers << "Label"<< "Name"<<
                             "PI"<< "PIvalue"
                             "SI"<< "SIvalue"
                             "CV"<< "Value"
                             "Write"<< "State";

 rowVector   = new QVector<CvValue*>(); // vector of Reset items
  labelVector = new QVector<QString>(); // vector of related labels

 _writeButtons = new QVector<QPushButton*>();

  _iCv = NULL;
 _status = NULL;

 mProgrammer = pProgrammer;
 // save a place for notification
 _status = status;
 _progState = 0;
}

/*public*/ void ResetTableModel::setProgrammer(Programmer* p)
{
 mProgrammer = p;

 // pass on to all contained CVs
 foreach (CvValue* cv, *rowVector) {
     cv->setProgrammer(p);
 }
}
/*public*/ int ResetTableModel::rowCount(const QModelIndex &parent) const
{
 return rowVector->size();
}

/*public*/ int ResetTableModel::columnCount(const QModelIndex &parent) const
{
 return headers->count();
}

/*public*/ QVariant ResetTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
  return dataAt(row, col);
 }
 return QVariant();
}
 QVariant ResetTableModel::dataAt(int row, int col) const
 {
 // if (log->isDebugEnabled()) log->debug("getValueAt "+row+" "+col);
 // some error checking
 if (row >= rowVector->size()){
     log->debug("row greater than row vector");
     return "Error";
 }
 CvValue* cv = rowVector->at(row);
 if (cv == NULL){
     log->debug("cv is NULL!");
     return "Error CV";
 }
 if (headers->at(col)==("Label"))
     return labelVector->at(row);
  else if (headers->at(col)==("Name"))
     return cv->cvName();
  else if (headers->at(col)==("Value"))
     return cv->getValue();
 else if (headers->at(col)==("Write"))
     return VPtr<QPushButton>::asQVariant(_writeButtons->at(row));
 else if (headers->at(col)==("State"))
 {
  int state = cv->getState();
  switch (state) {
      case CvValue::UNKNOWN:
          return "Unknown";
      case CvValue::READ:
          return "Read";
      case CvValue::EDITED:
          return "Edited";
      case CvValue::STORED:
          return "Stored";
      case CvValue::FROMFILE:
          return "From file";
      default:
          break;
  }
 }
}

/*public*/ void ResetTableModel::setRow(int row, QDomElement e, QDomElement p, QString model)
{
 decoderModel = model; // Save for use elsewhere
 //QString label = LocaleSelector.attribute(e, "label"); // Note the name variable is actually the label attribute
 QString label = e.attribute("label");
 if (log->isDebugEnabled()) log->debug("Starting to setRow \"" +
                                     label + "\"");
 QString cv   = e.attribute("CV");
 int cvVal = e.attribute("default").toInt();
 CvValue* resetCV = new CvValue(cv, mProgrammer);
 resetCV->setValue(cvVal);
 resetCV->setWriteOnly(true);
 resetCV->setState(VariableValue::STORED);
 rowVector->append(resetCV);
 labelVector->append(label);
 return;
}


/*protected*/ void ResetTableModel::performReset(int row)
{
 savedMode = mProgrammer->getMode(); // In case we need to change modes
 if (modeVector.at(row) != nullptr) {
     QList<QString> modes = mProgrammer->getSupportedModes();
     QList<QString>* validModes = modeVector.at(row);

     QString programmerModeListBuffer;// = new StringBuilder("");
     //modes.forEach((m) ->
     for(QString m : modes)
     {
         programmerModeListBuffer.append(",").append(m);
     }//);
     QString programmerModeList = programmerModeListBuffer/*.toString()*/;
     if (programmerModeList.length() <= 1) {
         programmerModeList = ""; // NOI18N
     } else if (programmerModeList.startsWith(",")) {
         programmerModeList = programmerModeList.mid(1);
     }

     QString resetModeBuilder;// = new StringBuilder("");
     //validModes.forEach((mode) ->
     for(QString mode : *validModes)
     {
         resetModeBuilder.append(",").append((new ProgrammingMode(mode))->toString());
     }//);
     QString resetModeList = resetModeBuilder/*.toString()*/;
     if (resetModeList.length() <= 1) {
         resetModeList = ""; // NOI18N
     } else if (resetModeList.startsWith(",")) {
         resetModeList = resetModeList.mid(1);
     }

     if (resetModeList.length() > 0) {
         bool modeFound = false;
         search:
         for (QString m : modes) {
          if(modeFound)
           break;
          for (QString mode : *validModes) {
                 if (mode == m/*(m->getStandardName())*/) {
                     mProgrammer->setMode(new ProgrammingMode(m));
                     modeFound = true;
                     break/* search*/;
                 }
             }
         }

         if (mProgrammer->getMode()->getStandardName().startsWith("OPS")) {
             if (!opsResetOk()) {
                 return;
             }
         }

         if (!modeFound) {
             if (!badModeOk((savedMode->toString()), resetModeList, programmerModeList)) {
                 return;
             }
             log->warn(tr("%1 for %2 was attempted in %3 mode.").arg(labelVector->at(row)).arg(decoderModel).arg(savedMode->getStandardName()));
             log->warn(tr("Recommended mode(s) were \"%1\" but available modes were \"%2\"").arg(resetModeList).arg(programmerModeList));
         }
     }
 }
 CvValue* cv = rowVector->at(row);
 log->debug(tr("performReset: %1").arg(cv->toString()));
 _progState = WRITING_CV;
 cv->write(_status);
}

/*public*/ void ResetTableModel::actionPerformed(JActionEvent* e)
 {
  if (log->isDebugEnabled()) log->debug("action command: "+e->getActionCommand());
  QChar b = e->getActionCommand().at(0);
  int row = (e->getActionCommand().mid(1)).toInt();
  if (log->isDebugEnabled()) log->debug("event on "+QString(&b)+" row "+QString::number(row));
  if (b=='W')
  {
   // write command
   performReset(row);
  }
 }


/*public*/ void ResetTableModel::propertyChange(PropertyChangeEvent* e)
 {
 if (log->isDebugEnabled()) log->debug("Property changed: "+e->getPropertyName());
 // notification from Indexed CV; check for Value being changed
 if (e->getPropertyName()==("Busy") && (e->getNewValue().toBool())==(false))
 {
  // busy transitions drive the state
  switch (_progState) {
  case IDLE:  // no, just an Indexed CV update
      if (log->isDebugEnabled()) log->error("Busy goes false with state IDLE");
      return;
  case WRITING_CV:  // now done with the write request
      if (log->isDebugEnabled()) log->debug("Finished writing the Indexed CV");
      _progState = IDLE;
      return;
  default:  // unexpected!
      log->error("Unexpected state found: "+_progState);
      _progState = IDLE;
      return;
  }
 }
}
/**
 * Can provide some mechanism to prompt for user for one last chance to
 * change his/her mind
 * @param currentMode current programming mode
 * @param resetModes representation of reset modes available
 * @param availableModes representation of available modes
 * @return true if user says to continue
 */
bool ResetTableModel::badModeOk(QString currentMode, QString resetModes, QString availableModes) {
    QString resetWarning
            = tr("Warning: Recommended Reset Mode not available")
            + "\n\n"
            + tr("The recommended programming mode(s) for this reset are \"%1\".").arg(resetModes)
            + "\n"
            + tr("The available programming mode(s) are \%1\".").arg(availableModes)
            + "\n"
            + tr("Use of a non-recommended mode may cause an improper reset.")
            + "\n\n"
            + tr("Do you wish to try anyway using the current programming mode ({0})?").arg(currentMode);
    return (JOptionPane::YES_OPTION
            == JOptionPane::showConfirmDialog(nullptr,
                    resetWarning,
                    tr("Caution: Factory Reset"),
                    JOptionPane::YES_NO_OPTION, JOptionPane::WARNING_MESSAGE));
}

 /**
  * Can provide some mechanism to prompt for user for one last chance to
  * change his/her mind
  *
  * @return true if user says to continue
  */
 bool ResetTableModel::opsResetOk() {
     QString resetWarning
             = tr("Warning: For satisfactory Factory Reset on Main of this decoder: ")
             + "\n\n"
             + tr("The Roster Entry must have been set to the current loco address when opened.")
             + "\n"
             + tr("If not, change to current address on the Basic sheet, save the Roster Entry, close and reopen.")
             + "\n"
             + tr("(The manufacturer may specify an alternate address to use.)")
             + "\n\n"
             + tr("The reset will most likely change the loco address, usually (but not always) to short address 3.")
             + "\n"
             + tr("Before doing further Programming On Main, change the Roster Entry to the after-reset address on the Basic sheet, save, close and reopen.")
             + "\n\n"
             + tr("Was the Roster Entry set to the current loco address when opened? Do you wish to continue with Reset on Main?");
     return (JOptionPane::YES_OPTION
             == JOptionPane::showConfirmDialog(nullptr,
                     resetWarning,
                     tr("Caution: Factory Reset"),
                     JOptionPane::YES_NO_OPTION, JOptionPane::WARNING_MESSAGE));
 }

 /*public*/ void ResetTableModel::dispose()
 {
 if (log->isDebugEnabled()) log->debug("dispose");

 // remove buttons
//    for (int i = 0; i<_writeButtons->size(); i++) {
//        _writeButtons->at(i)->removeActionListener((ActionListener*)this);
//    }

 _writeButtons->clear();
 _writeButtons = NULL;

 // remove variables listeners
 for (int i = 0; i<rowVector->size(); i++) {
     CvValue* cv = rowVector->at(i);
     cv->dispose();
 }
 rowVector->clear();
 rowVector = NULL;

 labelVector->clear();
 labelVector = NULL;

 headers = NULL;

 _status = NULL;
}
