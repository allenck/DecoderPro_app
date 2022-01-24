#ifndef CODEBUTTONHANDLERDATAROUTINES_H
#define CODEBUTTONHANDLERDATAROUTINES_H

#include <QObject>
#include "programproperties.h"
#include "nbhsensor.h"
#include "programproperties.h"

class CodeButtonHandlerData;
class CodeButtonHandlerDataRoutines : public QObject
{
  Q_OBJECT
 public:
  explicit CodeButtonHandlerDataRoutines(QObject *parent = nullptr);
  /*public*/ static CodeButtonHandlerData* createNewCodeButtonHandlerData(int newUniqueID, int newSwitchNumber, int newSignalEtcNumber, int newGUIColumnNumber, ProgramProperties* programProperties);
  /*public*/ static CodeButtonHandlerData* updateExistingCodeButtonHandlerDataWithSubstitutedData(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData* uECBHDWSD_CodeButton(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData *uECBHDWSD_SIDI(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData* uECBHDWSD_SIDL(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData *uECBHDWSD_SWDI(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData* uECBHDWSD_SWDL(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData* uECBHDWSD_CallOn(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static CodeButtonHandlerData* uECBHDWSD_TUL(ProgramProperties* programProperties, CodeButtonHandlerData* returnValue);
  /*public*/ static NBHSensor* createInternalNBHSensor(int number, QString pattern);

 signals:

 public slots:

 private:
  /*private*/ static QString substituteValueForPoundSigns(int value, QString _template);

};

#endif // CODEBUTTONHANDLERDATAROUTINES_H
