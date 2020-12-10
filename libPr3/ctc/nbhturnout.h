#ifndef NBHTURNOUT_H
#define NBHTURNOUT_H

#include <QObject>
#include "namedbeanhandle.h"
#include "ctcexception.h"
#include <QList>

class Turnout;
class NBHTurnout : public QObject
{
  Q_OBJECT
 public:
  explicit NBHTurnout(QString module, QString userIdentifier, QString parameter, QString turnout, bool FeedbackDifferent, QObject *parent = nullptr);
  /*public*/ static /*final*/ int DEFAULT_TURNOUT_STATE_RV;// = Turnout.CLOSED;  // A valid state, just "B.S.".
  /*public*/ static /*final*/ int DEFAULT_INT_RV;// = 0;                // For any function that returns int.
  /*public*/ NBHTurnout(QString module, QString userIdentifier, QString parameter, QObject* parent = nullptr);
  /*public*/ bool valid();// { return _mNamedBeanHandleTurnout != nullptr; }  // For those that want to know the internal state.
  /*public*/ Turnout* getBean();
  /*public*/ NamedBeanHandle<Turnout *> *getBeanHandle();
  /*public*/ int getKnownState();
  /*public*/ void setCommandedState(int s);
  /*public*/ int getFeedbackMode();
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* propertyChangeListener);
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* propertyChangeListener);
  /*public*/ QString getHandleName();
  /*public*/ int testingGetCountOfPropertyChangeListenersRegistered();

 signals:

 public slots:

 private:
  //  The "thing" we're protecting:
      /*private*/ NamedBeanHandle<Turnout*>* _mNamedBeanHandleTurnout;
      /*private*/ /*final*/ QString _mUserIdentifier;
      /*private*/ /*final*/ QString _mParameter;
      /*private*/ /*final*/ bool _mFeedbackDifferent;
      /*private*/ /*final*/ QList<PropertyChangeListener*> _mArrayListOfPropertyChangeListeners = QList<PropertyChangeListener*>();
  /*private*/ static Turnout* getSafeExistingJMRITurnout(QString module, QString userIdentifier, QString parameter, QString turnout);
  static /*private*/ Turnout* getExistingJMRITurnout(QString module, QString userIdentifier, QString parameter, QString turnout) throw (CTCException);

};

#endif // NBHTURNOUT_H
