#ifndef PREFERENCESBEAN_H
#define PREFERENCESBEAN_H
#include "bean.h"

class Profile;
/*public*/ /*abstract*/ class PreferencesBean : public Bean 
{
Q_OBJECT
public:
 /**
  * Property indicating preferences item do/do not need to be saved.
  *
  * {@value #DIRTY}
  */
 /*public*/ static /*final*/ QString DIRTY;// = "dirty"; // NOI18N
 /*public*/ static /*final*/ QString RESTART_REQUIRED;// = "restartRequired"; // NOI18N
 /*public*/ PreferencesBean(Profile* profile, QObject* parent = nullptr);
 /*public*/ Profile* getProfile();
 /*public*/ bool isDirty();
 /*public*/ bool isRestartRequired();

  private:
 /**
  * Property indicating preferences item requires restart to be applied.
  *
  * {@value #RESTART_REQUIRED}
  */
 /*private*/ bool restartRequired;// = false;
 /*private*/ bool _isDirty;// = false;
 /*private*/ /*final*/ Profile* profile;

protected:
    /*protected*/ void setRestartRequired();
    /*protected*/ void setIsDirty(bool value);
    /*protected*/ virtual void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
    /*protected*/ void firePropertyChange(QString propertyName, bool oldValue, bool newValue) ;
    /*protected*/ void firePropertyChange(QString propertyName, int oldValue, int newValue);
};
#endif // PREFERENCESBEAN_H
