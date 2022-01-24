#ifndef SIGNALDIRECTIONINDICATORINTERFACE_H
#define SIGNALDIRECTIONINDICATORINTERFACE_H

#include <QObject>

class CodeButtonHandler;
/*public*/ /*interface*/ class SignalDirectionIndicatorsInterface : public QObject{
  Q_OBJECT
 public:
  SignalDirectionIndicatorsInterface(QObject* parent = nullptr) : QObject(parent){}
    /*public*/ virtual void setCodeButtonHandler(CodeButtonHandler* codeButtonHandler) = 0;
    /*public*/ virtual void removeAllListeners() = 0;
    /*public*/ virtual bool isNonfunctionalObject() = 0;
    /*public*/ virtual void setPresentSignalDirectionLever(int presentSignalDirectionLever) = 0;
    /*public*/ virtual bool isRunningTime() = 0;
    /*public*/ virtual void osSectionBecameOccupied() = 0;
    /*public*/ virtual void codeButtonPressed(int requestedDirection, bool requestedChangeInSignalDirection) = 0;
    /*public*/ virtual void startCodingTime() = 0;
    /*public*/ virtual bool signalsNormal() = 0;
    /*public*/ virtual bool signalsNormalOrOutOfCorrespondence() = 0;
    /*public*/ virtual int getPresentDirection() = 0;
    /*public*/ virtual bool inCorrespondence() = 0;
    /*public*/ virtual void forceAllSignalsToHeld() =0;
    /*public*/ virtual int getSignalsInTheFieldDirection() = 0;
    /*public*/ virtual void setSignalDirectionIndicatorsToOUTOFCORRESPONDENCE() = 0;
    /*public*/ virtual void setRequestedDirection(int direction) = 0;
    /*public*/ virtual QObject* self() =0;
  friend class CodeButtonHandler;
  friend class CallOn;
};
//Q_DECLARE_INTERFACE(SignalDirectionIndicatorsInterface, "SignalDirectionIndicatorsInterface")
#endif // SIGNALDIRECTIONINDICATORINTERFACE_H
