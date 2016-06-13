#ifndef LOCOIOMODE_H
#define LOCOIOMODE_H

#include <QObject>
#include "logger.h"
#include "locoiodata.h"
#include "locoio_global.h"


class LOCOIOSHARED_EXPORT LocoIOMode : public QObject
{
    Q_OBJECT
 friend class LocoIOData;

public:
    explicit LocoIOMode(QObject *parent = 0);
 /**
  * Creates a new instance of LocoIOMode
  */
 /*public*/ LocoIOMode(int isOutput, int opcode, int sv0, int sv2, QString mode);
/*public*/ QString getMode();
/*public*/ QString getFullMode();
/*public*/ int    getOutput();
/*public*/ int    getOpcode();
/*public*/ int    getSV();
/*public*/ int    getV2();

signals:
    
public slots:
    
private:
    /*private*/ int isOutput;
    /*private*/ int opcode;
    /*private*/ int sv0;
    /*private*/ int sv2;
    /*private*/ QString mode;
 Logger log;
};

#endif // LOCOIOMODE_H
