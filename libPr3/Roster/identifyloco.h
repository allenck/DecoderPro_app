#ifndef IDENTIFYLOCO_H
#define IDENTIFYLOCO_H
#include "programmer.h"
#include "abstractidentify.h"
#include "logger.h"

class Programmer;
class LIBPR3SHARED_EXPORT IdentifyLoco : public AbstractIdentify
{
    Q_OBJECT
public:
    explicit IdentifyLoco(Programmer *programmer, QObject *parent = 0);
    /*public*/ bool test1();
    /*public*/ bool test2(int value);
    /*public*/ bool test3(int value);
    /*public*/ bool test4(int value);
    /*public*/ bool test5(int value);
    /*public*/ bool test6(int value);
    /*public*/ bool test7(int value);
    /*public*/ bool test8(int value);
    /*public*/ bool test9(int value);
    virtual void message(QString) {}

signals:

public slots:
  private:
    /*private*/ int cv17val;
    /*private*/ int cv18val;
    int address;// = -1;

    ProgrammingMode* originalMode;// = Programmer::NONE;
    Logger* log;
protected:
    /*protected*/ bool shortAddr;
    /*protected*/ int cv7val;
    /*protected*/ int cv8val;
    /*protected*/ void statusUpdate(QString s);
    /*abstract*/ /*protected*/ virtual void done(int address) {Q_UNUSED(address)}


};

#endif // IDENTIFYLOCO_H
