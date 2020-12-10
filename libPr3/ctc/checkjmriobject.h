#ifndef CHECKJMRIOBJECT_H
#define CHECKJMRIOBJECT_H

#include <QObject>

class JFrame;
class VerifyClassReturnValue;
class CheckJMRIObject : public QObject
{
  Q_OBJECT
 public:
  explicit CheckJMRIObject(QObject *parent = nullptr);
  /*public*/ static /*final*/ QString EXTERNAL_TURNOUT;// = "ExternalTurnout";    // NOI18N
  /*public*/ static /*final*/ QString EXTERNAL_SENSOR;// = "ExternalSensor";      // NOI18N
  /*public*/ static /*final*/ QString EXTERNAL_BLOCK;// =  "ExternalBlock";       // NOI18N
  /*public*/ static /*final*/ QString EXTERNAL_SIGNAL;// = "ExternalSignal";      // NOI18N

  /*public*/ /*static*/ enum OBJECT_TYPE { SENSOR, TURNOUT, _SIGNAL, BLOCK };
  /*public*/ /*static*/ class VerifyClassReturnValue {
    public:
      /*public*/ /*final*/ QString  _mFieldContents;                                // The contents
      /*public*/ /*final*/ CheckJMRIObject::OBJECT_TYPE _mObjectType;   // What it is.

      /*public*/ VerifyClassReturnValue(QString fieldContents, CheckJMRIObject::OBJECT_TYPE objectType) {
          _mFieldContents = fieldContents;
          _mObjectType = objectType;
      }

      //@Override
      /*public*/ QString toString() {
          switch(_mObjectType) {
              case CheckJMRIObject::SENSOR:
                  return tr("JMRI Sensor") + " " + _mFieldContents + " " + tr("doesn't exist.");  // NOI18N
              case CheckJMRIObject::TURNOUT:
                  return tr("JMRI Turnout") + " " + _mFieldContents + " " + tr("doesn't exist."); // NOI18N
              case CheckJMRIObject::_SIGNAL:
                  return tr("JMRI Signal") + " " + _mFieldContents + " " + tr("doesn't exist.");  // NOI18N
              case CheckJMRIObject::BLOCK:
                  return tr("JMRI Block") + " " + _mFieldContents + " " + tr("doesn't exist.");   // NOI18N
              default:
                  break;
          }
          return "";
      }
  };
  /*public*/ bool checkSignal(QString signalName);
  /*public*/ bool validClass(QVariant object);
  /*public*/ bool validClassWithPrefix(QString prefix, QVariant object);
  /*public*/ VerifyClassReturnValue* verifyClass(QVariant object);
  /*public*/ void analyzeForm(QString prefix, JFrame *dialog, QList<QString> errors);

 signals:

 public slots:

 private:
  /*private*/ VerifyClassReturnValue* verifyClassCommon(QString prefix, QVariant object);
  /*private*/ VerifyClassReturnValue* processField(QString fieldName, QString fieldContent);
  /*private*/ bool lowLevelCheck(CheckJMRIObject::OBJECT_TYPE objectType, QString JMRIObjectName);

};

#endif // CHECKJMRIOBJECT_H
