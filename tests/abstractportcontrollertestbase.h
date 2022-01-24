#ifndef ABSTRACTPORTCONTROLLERTESTBASE_H
#define ABSTRACTPORTCONTROLLERTESTBASE_H

#include <QObject>
#include "abstractportcontroller.h"
#include "defaultsystemconnectionmemo.h"


class AbstractPortController;
class AbstractPortControllerTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPortControllerTestBase(QObject *parent = nullptr);
    virtual /*public*/ void setUp();
    virtual /*public*/ void tearDown();
public slots:
    /*public*/ void testisDirtyNotNPE();


signals:

public slots:
private:
protected:
    /*protected*/ AbstractPortController* apc;

};
/*public*/ /*static*/ class AbstractPortControllerScaffold : public AbstractPortController {
    Q_OBJECT

public:
    /*public*/ AbstractPortControllerScaffold() : AbstractPortController(new DefaultSystemConnectionMemo("",""))
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
    /*public*/ void _connect() {
    }

    //@Override
    /*public*/ void configure() {
    }

    QString className()
    {
     return "AbstractPortControllerScaffold";
    }
};

#endif // ABSTRACTPORTCONTROLLERTESTBASE_H
