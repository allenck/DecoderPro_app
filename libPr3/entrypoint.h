#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QObject>
#include "block.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT EntryPoint : public QObject
{
    Q_OBJECT
public:
    //explicit EntryPoint(QObject *parent = 0);
    /*public*/ EntryPoint(Block* b, Block* pb, QString fbDir, QObject *parent = 0);
    // special constructor for delayed initialization
    /*public*/ EntryPoint(QString bName, QString fbName, QString fbDir, QObject *parent = 0) ;
    /**
     * Constants representing the Direction of the Entry Point.
     */
    static const int UNKNOWN = 0x02;
    static const int FORWARD = 0x04;
    static const int REVERSE = 0x08;
    /**
     * Access methods
     */
    /*public*/ Block* getBlock();
    /*public*/ QString getFromBlockName();
    /*public*/ Block* getFromBlock();
    /*public*/ void setTypeForward();
    /*public*/ void setTypeReverse();
    /*public*/ void setTypeUnknown();
    /*public*/ bool isForwardType();
    /*public*/ bool isReverseType();
    /*public*/ bool isUnknownType();
    /*public*/ int getDirection();
    /*public*/ void setDirection(int dir);
    /*public*/ void setFixed( bool f ) ;
    /*public*/ bool isFixed();

    /*public*/ QString getFromBlockDirection();

signals:
    
public slots:
private:
    // instance variables
    Block* mBlock = nullptr;
    Block* mFromBlock = nullptr;
    int mDirection = UNKNOWN;
    bool mFixed = false;
    QString mFromBlockDirection;// = "";

    // temporary instance variables
    bool needsInitialize = false;
    QString blockName;// = "";
    QString fromBlockName;// = "";
    void initialize();
    Logger log;
    void common();
};

#endif // ENTRYPOINT_H
