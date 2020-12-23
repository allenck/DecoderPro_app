#ifndef CTCSERIALDATA_H
#define CTCSERIALDATA_H

#include <QObject>

class Turnout;
//class CTCTurnoutData;
class TrafficLockingData;
class CodeButtonHandlerData;
class OtherData;
class CTCSerialData : public QObject
{
  Q_OBJECT
 public:
  explicit CTCSerialData(QObject *parent = nullptr);
  /**
   * "Return" value from function "getCTCTurnoutData":
   */
  /*public*/ /*static*/ class CTCTurnoutData {
      /*public*/ /*final*/ QString   _mOSSectionText;
      /*public*/ /*final*/ int      _mUniqueID;
      /*public*/ CTCTurnoutData(QString OSSectionText, int uniqueID) {
          _mOSSectionText = OSSectionText;
          _mUniqueID = uniqueID;
      }
   friend class CTCSerialData;
   friend class TopologyInfo;
  };
  /*public*/ OtherData* getOtherData();
  /*public*/ int getUniqueNumber();
  /*public*/ CodeButtonHandlerData* getCodeButtonHandlerDataViaUniqueID(int uniqueID);
  /*public*/ QString getMyShortStringNoCommaViaUniqueID(int uniqueID);
  /*public*/ int getIndexOfUniqueID(int uniqueID);
  /*public*/ void setOtherData(OtherData* otherData);
  /*public*/ QList<CodeButtonHandlerData*> getCodeButtonHandlerDataArrayList();
  /*public*/ void addCodeButtonHandlerData(CodeButtonHandlerData* codeButtonHandlerData);
  /*public*/ void removeCodeButtonHandlerData(int index);
  /*public*/ CodeButtonHandlerData* getCodeButtonHandlerData(int index);
  /*public*/ int getCodeButtonHandlerDataSize();
  /*public*/ void moveUp(int index);
  /*public*/ void moveDown(int index);
  /*public*/ void updateSwitchAndSignalEtcNumbersEverywhere(int index, int newSwitchNumber, int newSignalEtcNumber, int newGUIColumnNumber, bool newGUIGeneratedAtLeastOnceAlready);
  /*public*/ void setCodeButtonHandlerData(int index, CodeButtonHandlerData* codeButtonHandlerData);
  /*public*/ int findHighestSwitchNumberUsedSoFar();
  /*public*/ int findHighestColumnNumberUsedSoFar();
  /*public*/ CTCTurnoutData* getCTCTurnoutData(Turnout* turnout);
  /*public*/ QSet<QString> getHashSetOfAllLockedTurnoutsExcludingPassedOne(CodeButtonHandlerData* excludedOne);

 signals:

 public slots:

 private:
  /*private*/ OtherData* _mOtherData;
  /*private*/ QList<CodeButtonHandlerData*> _mCodeButtonHandlerDataArrayList;
  /*private*/ void updateTrlUserText(QList<TrafficLockingData *> *rulesToFix, int uniqueIDBeingModified, QString replacementString);

  friend class FrmMainForm; // for testing
};

#endif // CTCSERIALDATA_H
