#ifndef PREFERENCECHANGEEVENT_H
#define PREFERENCECHANGEEVENT_H
#include "eventobject.h"

class Preferences;
class PreferenceChangeEvent : public EventObject
{
 Q_OBJECT
public:
 /*public*/ PreferenceChangeEvent(Preferences* node, QString key,
                              QString newValue);
 /*public*/ Preferences* getNode();
 /*public*/ QString getKey();
 /*public*/ QString getNewValue();

private:

//  /*private*/ void writeObject(java.io.ObjectOutputStream out)
//                                            throws NotSerializableException;
//  /*private*/ void readObject(java.io.ObjectInputStream in)
//                                            throws NotSerializableException {
 // Defined so that this class isn't flagged as a potential problem when
 // searches for missing serialVersionUID fields are done.
 /*private*/ static /*final*/ long serialVersionUID;// = 793724513368024975L;

 /**
  * Key of the preference that changed.
  *
  * @serial
  */
 /*private*/ QString key;

 /**
  * New value for preference, or <tt>null</tt> if it was removed.
  *
  * @serial
  */
 /*private*/ QString newValue;


};

#endif // PREFERENCECHANGEEVENT_H
