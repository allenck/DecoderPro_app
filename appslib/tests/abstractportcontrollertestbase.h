#ifndef ABSTRACTPORTCONTROLLERTESTBASE_H
#define ABSTRACTPORTCONTROLLERTESTBASE_H

#include <QObject>
#include "abstractportcontroller.h"
#include "systemconnectionmemo.h"

class AbstractPortController;
class AbstractPortControllerTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPortControllerTestBase(QObject *parent = nullptr);
    /*public*/ void testisDirtyNotNPE();
    /*public*/ void setUp();
    /*public*/ void tearDown();

signals:

public slots:
        private:
protected:
    /*protected*/ AbstractPortController* apc;

};
/*public*/ /*static*/ class AbstractPortControllerScaffold : public AbstractPortController {
    Q_OBJECT

public:
    /*public*/ AbstractPortControllerScaffold() : AbstractPortController(new SystemConnectionMemo("",""))
    {
//        //super(new SystemConnectionMemo("", "") {

//            //@Override
//            /*protected*/ ResourceBundle getActionModelResourceBundle() {
//                return null;
//            }
//        });
    }

//    //@Override
//    /*public*/ DataInputStream getInputStream() {
//        return null;
//    }

//    //@Override
//    /*public*/ DataOutputStream getOutputStream() {
//        return null;
//    }

    //@Override
    /*public*/ QString getCurrentPortName() {
        return "";
    }

    //@Override
    /*public*/ void dispose() {
        AbstractPortController::dispose();
    }

    //@Override
    /*public*/ void recover() {
    }

    //@Override
    /*public*/ void connect() {
    }

    //@Override
    /*public*/ void configure() {
    }
};

#endif // ABSTRACTPORTCONTROLLERTESTBASE_H
