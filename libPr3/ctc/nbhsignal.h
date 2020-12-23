#ifndef NBHSIGNAL_H
#define NBHSIGNAL_H

#include <QObject>
#include "namedbeanhandle.h"
#include "signalappearancemap.h"


class Turnout;
class SignalHead;
class SignalMast;
class Logger;
class NBHSignal : public QObject
{
  Q_OBJECT
 public:
  explicit NBHSignal(QString signal, QObject *parent = nullptr);
  /*public*/ static /*final*/ QObject* DEFAULT_OBJECT_RV;// = null;       // For any function that returns something derived from Java's Object.
  /*public*/ static /*final*/ bool DEFAULT_BOOLEAN_RV;// = false;    // For any function that returns boolean.
  /*public*/ static /*final*/ int DEFAULT_INT_RV;// = 0;                // For any function that returns int.
  /*public*/ static /*final*/ QString DEFAULT_STRING_RV;// = "UNKNOWN";  // NOI18N  For any function that returns String.
  /*public*/ bool valid();
  /*public*/ QObject* getBean();
  /*public*/ QObject* getBeanHandle();
  /*public*/ QString getHandleName();
  /*public*/ QString getDisplayName();
  /*public*/ bool isDanger();
  /*public*/ void setCTCHeld(bool held);
  /*public*/ bool getHeld();
  /*public*/ void setHeld(bool newHeld);
  /*public*/ void allowPermissiveSML();
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* l);
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* l);
  /*public*/ QString getAspect();
  /*public*/ SignalAppearanceMap* getAppearanceMap();
  /*public*/ int getAppearance();
  /*public*/ void setAppearance(int newAppearance);
  /*public*/ QVector<int> getValidStates();
  /*public*/ QVector<QString> getValidStateKeys();
  /*public*/ QVector<QString> getValidStateNames();

 signals:

 public slots:

 private:
  static Logger* log;
  //  The "things" we're protecting:
      /*private*/ /*final*/ NamedBeanHandle<SignalMast*>* _mNamedBeanHandleSignalMast;
      /*private*/ /*final*/ NamedBeanHandle<SignalHead*>* _mNamedBeanHandleSignalHead;

      /*private*/ /*final*/ bool isSignalMast;   // True for signal mast, false for signal head
      /*private*/ /*final*/ QString _mDangerAppearance;  //  The string to determine "Is the Signal all Red":
  /*private*/ bool setSignalType();

  friend class ProjectsCommonSubs;
};

#endif // NBHSIGNAL_H
