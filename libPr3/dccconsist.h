#ifndef DCCCONSIST_H
#define DCCCONSIST_H
#include <QList>
#include <QHash>
#include "consist.h"
#include "logger.h"
#include <QVector>
#include <QMutex>

class DecoderFile;
class RosterEntry;
class VariableTableModel;
class DccLocoAddress;
class ConsistListener;
class DccConsist : public Consist
{
    Q_OBJECT
public:
    explicit DccConsist(int address, QObject *parent = 0);
    /*public*/ DccConsist(DccLocoAddress* address, QObject *parent = 0) ;
    /*public*/ void dispose() ;
    /*public*/ void setConsistType(int consist_type);
    /*public*/ int getConsistType()  ;
    /*public*/ DccLocoAddress* getConsistAddress()  ;
    /*public*/ bool isAddressAllowed(DccLocoAddress* address)  ;
    /*public*/ int sizeLimit() const ;
    /*public*/ QList<DccLocoAddress *>* getConsistList();
    /*public*/ bool contains(DccLocoAddress* address) ;
    /*public*/ bool getLocoDirection(DccLocoAddress* address) ;
    /*public*/ void add(DccLocoAddress* LocoAddress,bool directionNormal) ;
    /*public*/ void restore(DccLocoAddress* LocoAddress,bool directionNormal) ;
    /*public*/ void remove(DccLocoAddress* LocoAddress) ;
    /*public*/ void setPosition(DccLocoAddress* address,int position) ;
    /*public*/ int getPosition(DccLocoAddress* address) ;
    /*public*/ void addConsistListener(ConsistListener* Listener) ;
    /*public*/ void removeConsistListener(ConsistListener* Listener) ;
    /*public*/ void setConsistID(QString ID) ;
    /*public*/ QString getConsistID() ;
    /*public*/ void reverse() ;
 /*public*/ void setRosterId(DccLocoAddress* address, QString rosterId);
 /*public*/ QString getRosterId(DccLocoAddress* address);

signals:

public slots:
    /*public*/ void programmingOpReply(int value, int status);
private:
 Logger* log;
 // data member to hold the throttle listener objects
 /*final private */QVector<ConsistListener*>* listeners;// = new Vector<ConsistListener>();
 QMutex mutex;
protected:
    /*protected*/ QList<DccLocoAddress*>* consistList;// = NULL; // A List of Addresses in the consist

    /*protected*/ QHash<DccLocoAddress*, bool>* consistDir;// = NULL; // A Hash table
                                        // containing the directions of
                    // each locomotive in the consist,
                    // keyed by Loco Address.

    /*protected*/ QHash<DccLocoAddress*, int>* consistPosition;// = NULL; // A Hash table
                                        // containing the position of
                    // each locomotive in the consist,
                    // keyed by Loco Address.

    /*protected*/ int consistType;// = ADVANCED_CONSIST;

    /*protected*/ DccLocoAddress* consistAddress;// = NULL;

    /*protected*/ QString ConsistID;// = NULL;
 /*protected*/ virtual void addToAdvancedConsist(DccLocoAddress* LocoAddress, bool directionNormal);
 /*protected*/ virtual void removeFromAdvancedConsist(DccLocoAddress* LocoAddress);
 /*protected*/ void notifyConsistListeners(DccLocoAddress*  LocoAddress, int ErrorCode) ;
 QMap<DccLocoAddress*, QString>* consistRoster;
 /*protected*/ void setRosterEntryCVValue(DccLocoAddress* address);
 /*protected*/ void resetRosterEntryCVValue(DccLocoAddress* address);
 /*protected*/ void updateRosterCV(DccLocoAddress* address,bool direction,int value);
 /*protected*/ void loadDecoderFromLoco(RosterEntry* r,VariableTableModel* varTable);
 /*protected*/ void loadDecoderFile(DecoderFile* df, RosterEntry* re,VariableTableModel* variableModel);

protected:
};

#endif // DCCCONSIST_H
