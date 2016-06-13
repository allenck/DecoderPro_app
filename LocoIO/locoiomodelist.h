#ifndef LOCOIOMODELIST_H
#define LOCOIOMODELIST_H

#include <QObject>
#include "locoiomode.h"
#include "locoio_global.h"

class LocoIOMode;
class LOCOIOSHARED_EXPORT LocoIOModeList : public QObject
{
 Q_OBJECT
friend class LocoIOData;
friend class LocoIODialog;
friend class OutputWidget;
public:
 explicit LocoIOModeList(QObject *parent = 0);
/*protected*/ QStringList getValidModes();
/*protected*/ LocoIOMode* getLocoIOModeFor(QString s);
LocoIOMode* getLocoIOModeFor(int cv, int v1, int v2);
signals:
    
public slots:
private:
    /*private*/ QVector<LocoIOMode*> modeList;// = new Vector<LocoIOMode>();
    /*private*/ QStringList validmodes;
    /*private*/ void test();
    Logger log;
    /**
     * Convert bytes from LocoNet packet into a 1-based address for
     * a sensor or turnout.
     * @param a1 Byte containing the upper bits
     * @param a2 Byte containing the lower bits
     * @return 1-4096 address
     */
    static /*private*/ int SENSOR_ADR(int a1, int a2);

protected:
    /*protected*/ bool isValidModeValue(QVariant value);
//    /*protected*/ LocoIOMode* getLocoIOModeFor(int cv, int v1, int v2);
    /**
     * Low bits
     */
    /*protected*/ int addressToValue1(LocoIOMode* lim, int address);
    /**
     * High bits...
     */
    /*protected*/ int addressToValue2(LocoIOMode* lim, int address);
    /*protected*/ int addressToValues(int opcode, int sv, int v2mask, int address);
    /*protected*/ int valuesToAddress(int opcode, int sv, int v1, int v2);
    /*protected*/ int valuesToAddress(LocoIOMode* lim, int sv, int v1, int v2);
friend class LocoIOTableModel;
};

#endif // LOCOIOMODELIST_H
