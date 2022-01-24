#include "checkjmriobject.h"
#include "jframe.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"

CheckJMRIObject::CheckJMRIObject(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019
 *
 * The purpose of this object is to take a passed class and by using reflection
 * see if any of the public class Strings in the class has specific patterns in
 * their name(s).
 *
 * If so, that variable's contents then is passed to the JMRIConnection object
 * to see if it is valid.
 *
 */
///*public*/ class CheckJMRIObject {

//  Putting these strings ANYWHERE in a string variable definition (with EXACT case!)
//  will cause this routine to try to validate it against JMRI Simple Server:
    /*public*/ /*static*/ /*final*/ QString CheckJMRIObject::EXTERNAL_TURNOUT = "ExternalTurnout";    // NOI18N
    /*public*/ /*static*/ /*final*/ QString CheckJMRIObject::EXTERNAL_SENSOR = "ExternalSensor";      // NOI18N
    /*public*/ /*static*/ /*final*/ QString CheckJMRIObject::EXTERNAL_BLOCK =  "ExternalBlock";       // NOI18N
    /*public*/ /*static*/ /*final*/ QString CheckJMRIObject::EXTERNAL_SIGNAL = "ExternalSignal";      // NOI18N

    ///*public*/ static enum OBJECT_TYPE { SENSOR, TURNOUT, SIGNAL, BLOCK }



//  Quick and dirty routine for signals only:
    /*public*/ bool CheckJMRIObject::checkSignal(QString signalName) {
        return lowLevelCheck(OBJECT_TYPE::_SIGNAL, signalName);
    }

//  NOTE below on function prefix naming conventions:
//  "valid" just returns boolean if the entire object is valid (true) or not (false).  It stops scanning on first error.
//  "verify" returns a "VerifyClassReturnValue" (invalid) or null (valid) against the entire object.  It stops scanning on first error.
//  "analyze" adds entry(s) to the end of a passed errors array for ALL invalid entries.  No return value.
//  All of these work with String fields ONLY.  If the field is blank or null, it is ignored, it is up to other code
//  to determine whether that is valid or not.

    /*public*/ bool CheckJMRIObject::validClass(QVariant object) {
        return verifyClassCommon("", object) == nullptr;
    }

    /*public*/ bool CheckJMRIObject::validClassWithPrefix(QString prefix, QVariant object) {
        return verifyClassCommon(prefix, object) == nullptr;
    }

    /*public*/ CheckJMRIObject::VerifyClassReturnValue* CheckJMRIObject::verifyClass(QVariant object) {
        return verifyClassCommon("", object);
    }

    /*private*/ CheckJMRIObject::VerifyClassReturnValue* CheckJMRIObject::verifyClassCommon(QString prefix, QVariant object) {
        QString fieldName;
#if 0
        Field[] objFields = object.getClass().getDeclaredFields();
        for (Field field : objFields) { // For all fields in the class
            if (field.getType() == String.class) { // Strings only: need to check variable name:
                if ((fieldName = field.getName()).startsWith(prefix)) {
                    String fieldContent;
                    try {
                        fieldContent = (String)field.get(object);
                        if (ProjectsCommonSubs.isNullOrEmptyString(fieldContent)) continue;    // Skip blank fields
                    } catch (IllegalAccessException e) { continue; }    // Should never happen, if it does, just skip this field.
                    VerifyClassReturnValue verifyClassReturnValue = processField(fieldName, fieldContent);
                    if (verifyClassReturnValue != null) return verifyClassReturnValue;  // Error, stop and return error!
                }
            }
        }
#endif
        return nullptr;    // All fields pass.
    }

//  Function similar to the above, EXCEPT that it is used for form processing.
//  Only JTextField's and JTable's are checked.
//  A LIST of errors is returned, i.e. it checks ALL fields.
//  Gotcha: All JTextField's in a dialog are declared "private" by the IDE, ergo the need for "field.setAccessible(true);"
    /*public*/ void CheckJMRIObject::analyzeForm(QString prefix, JFrame* dialog, QList<QString> errors) {
#if 0
     Field[] objFields = dialog.getClass().getDeclaredFields();
        for (Field field : objFields) { // For all fields in the class
            Class<?> fieldType = field.getType();
            if (fieldType == javax.swing.JTextField.class) { // JTextField: need to check variable name:
                String fieldName;
                if ((fieldName = field.getName()).startsWith(prefix)) {
                    String fieldContent;
                    try {
                        field.setAccessible(true);
                        fieldContent = ((javax.swing.JTextField)field.get(dialog)).getText();
                        if (ProjectsCommonSubs.isNullOrEmptyString(fieldContent)) continue;    // Skip blank fields
                    } catch (IllegalAccessException e) { continue; }    // Should never happen, if it does, just skip this field.
                    VerifyClassReturnValue verifyClassReturnValue = processField(fieldName, fieldContent);
                    if (verifyClassReturnValue != null) { // Error:
                        errors.add(verifyClassReturnValue.toString());
                    }
                }
            }
            else if (fieldType == javax.swing.JTable.class) { // JTable: need to check variable name:
                String fieldName;
                if ((fieldName = field.getName()).startsWith(prefix)) {
                    OBJECT_TYPE objectType;
                    if (fieldName.contains(EXTERNAL_TURNOUT)) objectType = OBJECT_TYPE.TURNOUT;
                    else if (fieldName.contains(EXTERNAL_SENSOR)) objectType = OBJECT_TYPE.SENSOR;
                    else if (fieldName.contains(EXTERNAL_BLOCK)) objectType = OBJECT_TYPE.BLOCK;
                    else if (fieldName.contains(EXTERNAL_SIGNAL)) objectType = OBJECT_TYPE.SIGNAL;
                    else continue;   // Nothing to check in this field, skip it.
                    DefaultTableModel defaultTableModel;
                    try {
                        field.setAccessible(true);
                        defaultTableModel = (DefaultTableModel)((javax.swing.JTable)field.get(dialog)).getModel();
                    } catch (IllegalAccessException e) { continue; }    // Should never happen, if it does, just skip this field.
                    for (int sourceIndex = 0; sourceIndex < defaultTableModel.getRowCount(); sourceIndex++) {
                        Object object = defaultTableModel.getValueAt(sourceIndex, 0);
                        if (object != null) {
                            if (ProjectsCommonSubs.isNullOrEmptyString(object.toString())) continue;    // Skip blank fields
                            String jmriObjectName = object.toString().trim();
                            if (!lowLevelCheck(objectType, jmriObjectName)) { // Invalid:
                                errors.add(new VerifyClassReturnValue(jmriObjectName, objectType).toString());
                            }
                        }
                    }
                }
            }
        }
#endif
    }

    /*private*/ CheckJMRIObject::VerifyClassReturnValue* CheckJMRIObject::processField(QString fieldName, QString fieldContent) {
        OBJECT_TYPE objectType;
        if (fieldName.contains(EXTERNAL_TURNOUT)) objectType = OBJECT_TYPE::TURNOUT;
        else if (fieldName.contains(EXTERNAL_SENSOR)) objectType = OBJECT_TYPE::SENSOR;
        else if (fieldName.contains(EXTERNAL_BLOCK)) objectType = OBJECT_TYPE::BLOCK;
        else if (fieldName.contains(EXTERNAL_SIGNAL)) objectType = OBJECT_TYPE::_SIGNAL;
        else return nullptr;   // Nothing to check in this field, OK.
        if (lowLevelCheck(objectType, fieldContent)) return nullptr;  // Valid, OK.
//  OOPPSS, JMRI don't know about it (at this time):
        return new VerifyClassReturnValue(fieldContent, objectType);
    }

    /*private*/ bool CheckJMRIObject::lowLevelCheck(CheckJMRIObject::OBJECT_TYPE objectType, QString JMRIObjectName) {
        switch(objectType) {
            case CheckJMRIObject::SENSOR:
                if (InstanceManager::sensorManagerInstance()->getSensor(JMRIObjectName) != nullptr) return true;
                break;
            case CheckJMRIObject::TURNOUT:
                if (InstanceManager::turnoutManagerInstance()->getTurnout(JMRIObjectName) != nullptr) return true;
                break;
            case CheckJMRIObject::_SIGNAL:
                if (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(JMRIObjectName) != nullptr) return true; // Try BOTH:
                if (((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(JMRIObjectName) != nullptr) return true;
                break;
            case CheckJMRIObject::BLOCK:
                if (((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(JMRIObjectName) != nullptr) return true;
                break;
            default:
                break;
        }
        return false;   // Either bad objectType or object doesn't exist in JMRI
    }
