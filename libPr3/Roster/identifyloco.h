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
    /*public*/ bool test2(int value) override;
    /*public*/ bool test3(int value) override;
    /*public*/ bool test4(int value) override;
    /*public*/ bool test5(int value) override;
    /*public*/ bool test6(int value) override;
    /*public*/ bool test7(int value) override;
    /*public*/ bool test8(int value) override;
    /*public*/ bool test9(int value) override;
    virtual void message(QString) =0;

signals:

public slots:

private:
    /*private*/ int cv17val;
    /*private*/ int cv18val;
    int address = -1;

    static Logger* log;
protected:
    /*protected*/ bool shortAddr = false;
    /*protected*/ int cv7val;
    /*protected*/ int cv8val;
    /*protected*/ void statusUpdate(QString s) override;
    /*abstract*/ /*protected*/ virtual void done(int address) =0;

};

#endif // IDENTIFYLOCO_H
