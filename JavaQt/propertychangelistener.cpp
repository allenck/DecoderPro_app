#include "propertychangelistener.h"

PropertyChangeListener::PropertyChangeListener(QObject *parent) :
    QObject(parent)
{
 //handleChange = NULL;

}
//@Override
void PropertyChangeListener::propertyChange(PropertyChangeEvent* e) {
#if 0
 if ((e->getPropertyName() == ("RosterGroupRemoved"))
           || (e->getPropertyName()==("RosterGroupAdded"))
           || (e->getPropertyName()==("RosterGroupRenamed")))
 {
  setRosterGroups(_groups);
  _model.reload(_groups);
  setSelectionToGroup(selectedRosterGroup);
 }
#endif
 //qDebug() << tr("Property change received");
}
