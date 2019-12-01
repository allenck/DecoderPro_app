#ifndef ROSTERGROUP_H
#define ROSTERGROUP_H
#include "rosterobject.h"
#include "bean.h"

class RosterEntry;
class RosterGroup : public Bean, public RosterObject
{
 Q_OBJECT
 Q_INTERFACES(RosterObject)
public:
//explicit RosterGroup(QObject *parent = 0);
 /*public*/ RosterGroup(QString name, QObject *parent = 0);
 /*public*/ QList<RosterEntry*> getEntries();
 /*public*/ QString getName();
 /*public*/ void setName(QString newName);
 /*public*/ QString getDisplayName();
 /*public*/ bool canEdit();
 /*public*/ bool canDelete() ;
 /*public*/ bool canCopy() ;
 /*public*/ bool canChangeContents();

signals:

public slots:
private:
 /*private*/ QString name;

};

#endif // ROSTERGROUP_H
