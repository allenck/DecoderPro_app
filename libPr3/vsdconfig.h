#ifndef VSDCONFIG_H
#define VSDCONFIG_H

#include <QObject>
#include "libPr3_global.h"

class DccLocoAddress;
class LocoAddress;
class PhysicalLocation;
class RosterEntry;
class LIBPR3SHARED_EXPORT VSDConfig : public QObject
{
 Q_OBJECT
public:
 explicit VSDConfig(QObject *parent = 0);
 /*public*/ QString getID();
 /*public*/ QString getVSDPath();
 /*public*/ QString getProfileName();
 /*public*/ LocoAddress* getLocoAddress();
 /*public*/ DccLocoAddress* getDccAddress() ;
 /*public*/ float getVolume();
 /*public*/ PhysicalLocation* getPhysicalLocation();
 /*public*/ RosterEntry* getRosterEntry();
 /*public*/ void setID(QString id);
 /*public*/ void setVSDPath(QString path);
 /*public*/ void setProfileName(QString name);
 /*public*/ void setLocoAddress(LocoAddress* a) ;
 /*public*/ void setVolume(float v);
 /*public*/ void setPhysicalLocation(PhysicalLocation* p);
 /*public*/ void setRosterEntry(RosterEntry* r);
 /*public*/ QString toString();

signals:

public slots:

private:
 /*private*/ float DEFAULT_VOLUME;// = 0.8f;

 /*private*/ QString my_id;
 /*private*/ QString vsd_path;
 /*private*/ QString profile_name;
 /*private*/ LocoAddress* address;
 /*private*/ float volume;
 /*private*/ PhysicalLocation* location;
 /*private*/ RosterEntry* roster;
 friend class VSDecoder;
};

#endif // VSDCONFIG_H
