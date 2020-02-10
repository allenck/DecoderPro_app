#ifndef DEFAULTCABSIGNAL_H
#define DEFAULTCABSIGNAL_H

#include <QObject>
#include "cabsignal.h"

class DefaultCabSignal : public QObject, public CabSignal //, public PropertyChangeListener
{
 Q_OBJECT
 Q_INTERFACES(CabSignal /*PropertyChangeListener*/)
public:
 explicit DefaultCabSignal(LocoAddress* address, QObject *parent = nullptr);
 /*public*/ void dispose();
 /*public*/ LocoAddress* getCabSignalAddress();
 /*synchronized*/ /*public*/ void setBlock(Block* position);
 /*synchronized*/ /*public*/ void setBlock();
 /*synchronized*/ /*public*/ Block* getBlock();
 /*public*/ Block* getNextBlock();
 /*public*/ SignalMast* getNextMast();
 /*public*/ void forwardCabSignalToLayout();
 /*public*/ bool isCabSignalActive();
 /*public*/ void setCabSignalActive(bool active);
 /*public*/ void setMasterCabSigPauseActive (bool active);
 PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
 /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
 /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l) ;
 QObject* self() {return(QObject*)this;}
signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
 static Logger* log;
 /*private*/ LocoAddress* _address = nullptr;
 //@GuardedBy("this")
 /*private*/ Block* _currentBlock = nullptr;
 /*private*/ Block* _nextBlock = nullptr;
 /*private*/ SignalMast* _nextMast = nullptr;
 /*private*/ bool _cabSignalActive = true;
 /*private*/ bool _masterPausedButtonActive = false;
 /*private*/ PropertyChangeListener* _cconSignalMastListener = nullptr;
 /*private*/ Block* nextBlockOnPath(Block* current, int fromdirection);

 protected:
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
 /*protected*/ void forwardAspectToLayout();
 /*protected*/ void resetLayoutCabSignal();

};

#endif // DEFAULTCABSIGNAL_H
