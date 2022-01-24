#include "shortaddrvariablevalue.h"

//ShortAddrVariableValue::ShortAddrVariableValue(QObject *parent) :
//    VariableValue(parent)
//{
//}
/**
 * Representation of a short address (CV1).
 * <P>
 * This is a decimal value, extended to modify the other CVs when
 * written.  The CVs to be modified and their new values are
 * stored in two arrays for simplicity.
 * <P>
 *
 * The NMRA has decided that writing CV1 causes other CVs to update
 * within the decoder (CV19 for consisting, CV29 for short/long
 * address). We want DP to overwrite those _after_ writing CV1,
 * so that the DP values are forced to be the correct ones.
 *
 * @author	    Bob Jacobsen   Copyright (C) 2001, 2006, 2007
 * @version     $Revision: 17977 $
 *
 */
// /*public*/ class ShortAddrVariableValue extends DecVariableValue {

/*public*/ ShortAddrVariableValue::ShortAddrVariableValue(QString name, QString comment, QString cvName, bool readOnly,
                                                          bool infoOnly, bool writeOnly, bool opsOnly, QString cvNum,
                                                          QString mask, QMap<QString,CvValue*>* v, JLabel* status,
                                                          QString stdname, QObject *parent)
    : DecVariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, 1, 127, v, status, stdname, parent)
{
 // specify min, max value explicitly
 //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, 1, 127, v, status, stdname);
 log = new Logger("ShortAddrVariableValue");
 firstFreeSpace = 0;
 cvNumbers = new QVector<QString>(maxCVs,0);
 newValues = new QVector<int>(maxCVs,0);

 // add default overwrites as per NMRA spec
 firstFreeSpace = 0;
 setModifiedCV("19");         // consisting
 setModifiedCV("29");         // control bits
}

/**
 * Register a CV to be modified regardless of
 * current value
 */
/*public*/ void ShortAddrVariableValue::setModifiedCV(QString cvNum)
{
 if (firstFreeSpace>=maxCVs)
 {
  log->error("too many CVs registered for changes!");
  return;
 }
 cvNumbers->replace(firstFreeSpace,cvNum);
 newValues->replace(firstFreeSpace,-10);
 firstFreeSpace++;
}

/**
 * Change CV values due to change in short address
 */
/*private*/ void ShortAddrVariableValue::updateCvForAddrChange()
{
 for (int i=0; i<firstFreeSpace; i++)
 {
  CvValue* cv = _cvMap->value(cvNumbers->at(i));
  if (cv == NULL) continue;  // if CV not present this decoder...
  if (cvNumbers->at(i)!=cv->number())
   log->error("CV numbers don't match: "
                      +(cvNumbers->at(i))+" "+(cv->number()));
  cv->setToWrite(true);
  cv->setState(EDITED);
  if(log->isDebugEnabled()) log->debug("Mark to write " +(cv->number()));
 }
}


/*public*/ void ShortAddrVariableValue::writeChanges() {
    if (getReadOnly()) log->error("unexpected writeChanges operation when readOnly is set");
    setBusy(true);  // will be reset when value changes
    // mark other CVs as possibly needing write
    updateCvForAddrChange();
    // and change the value of this one
    _cvMap->value(getCvNum())->write(_status);
}

/*public*/ void ShortAddrVariableValue::writeAll() {
    if (getReadOnly()) log->error("unexpected writeAll operation when readOnly is set");
    setBusy(true);  // will be reset when value changes
    // mark other CVs as possibly needing write
    updateCvForAddrChange();
    // and change the value of this one
    _cvMap->value(getCvNum())->write(_status);
}

// clean up connections when done
/*public*/ void ShortAddrVariableValue::dispose() {
    VariableValue::dispose();
}
