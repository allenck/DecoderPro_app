#include "hexvariablevalue.h"

//HexVariableValue::HexVariableValue(QObject *parent) :
//    DecVariableValue(parent)
//{
//}
/**
 * LIke DecVariableValue, except that the string representation is in hexadecimal
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version $Revision: 17977 $
 */
// /*public*/ class HexVariableValue extends DecVariableValue {

/*public*/ HexVariableValue::HexVariableValue(QString name, QString comment, QString cvName,
                        bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                        QString cvNum, QString mask, int minVal, int maxVal,
                        QMap<QString, CvValue*>* v, JLabel* status, QString stdname, QObject *parent) :    DecVariableValue(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, minVal, maxVal, v, status, stdname, parent)

{
    //super(name, comment, cvName, readOnly, infoOnly, writeOnly, opsOnly, cvNum, mask, minVal, maxVal, v, status, stdname);
    log = new Logger("HexVariableValue");
}

//void HexVariableValue::updatedTextField()
//{
// if (log->isDebugEnabled()) log->debug("updatedTextField");
// // called for new values - set the CV as needed
// CvValue* cv = _cvMap->value(getCvNum());
// // compute new cv value by combining old and request
// int oldCv = cv->getValue();
// int newVal;
////        try {
// newVal = _value->text().toInt(0,16);
////                }
////                catch (java.lang.NumberFormatException ex) { newVal = 0; }
// int newCv = newValue(oldCv, newVal, getMask());
// if (oldCv != newCv)
//  cv->setValue(newCv);
//}

/** ActionListener implementations */
/*public*/ void HexVariableValue::actionPerformed(JActionEvent* /*e*/)
{
 if (log->isDebugEnabled()) log->debug("actionPerformed");
 int newVal = _value->text().toInt(0,16);
 updatedTextField();
 prop->firePropertyChange("Value", QVariant(), QVariant(newVal));
}

/*public*/ void HexVariableValue::setValue(int value)
{
 int oldVal;
//        try {
 oldVal = _value->text().toInt(0,16);
//}
//                catch (java.lang.NumberFormatException ex) { oldVal = -999; }
 if (log->isDebugEnabled()) log->debug("setValue with new value "+QString::number(value)+" old value "+QString::number(oldVal));
 _value->setText(QString("%1").arg(value,0,16));
 if (oldVal != value || getState() == VariableValue::UNKNOWN)
   actionPerformed(NULL);
 prop->firePropertyChange("Value", QVariant(oldVal), QVariant(value));
}
