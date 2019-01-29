#ifndef CONDITIONALACTION_H
#define CONDITIONALACTION_H
#include <QObject>
#include "namedbeanhandle.h"
#include "libPr3_global.h"

/**
 * The consequent of the antecedent of the conditional proposition.
 * The data for the action to be taken when a Conditional calculates to True
 * <P>
 *
 * @author Pete Cressman Copyright (C) 2009
 * @version   $Revision: 18090 $
 */
class QTimer;
class NamedBean;
class ActionListener;
/*public*/ class LIBPR3SHARED_EXPORT ConditionalAction : public QObject
{
    Q_OBJECT
public:
    ConditionalAction(QObject* parent= 0)
        : QObject(parent) {}
    /**
     * Integer data for action
     */
    virtual int getActionData() = 0;

    virtual QString getActionDataString() = 0;

    /**
     * String data for action
     */
    virtual QString getActionString() = 0;

    /**
     * Name of the device or element that is effected
     */
    virtual QString getDeviceName() {return "";}

    /**
     * Options on when action is taken
     */
    virtual int getOption() = 0;

    /**
     * return String name of the option for this consequent type
     */
    virtual QString getOptionString(bool type) = 0;

    /**
     * The consequent device or element type
     */
    virtual int getType() = 0;

    /**
     * return String name of this consequent type
     */
    virtual QString getTypeString() = 0;

    /**
     * Sets action data from user's name for it
     */
    virtual void setActionData(QString actionData) = 0;

    virtual void setActionData(int actionData) = 0;

    virtual void setActionString(QString actionString) = 0;

    virtual void setDeviceName(QString deviceName) = 0;

    virtual void setOption(int option) = 0;

    /**
     * Sets type from user's name for it
     */
    virtual void setType(QString type) = 0;

    virtual void setType(int type) = 0;

    /*public*/ virtual QString description(bool triggerType) = 0;

    /*
    * get timer for delays and other timed events
    */
    virtual QTimer* getTimer() = 0;

    /*
    * set timer for delays and other timed events
    */
    virtual void setTimer(QTimer* timer) = 0;

    virtual bool isTimerActive() = 0;

    virtual void startTimer() = 0;

    virtual void stopTimer() = 0;

    /*
    * set listener for delays and other timed events
    */
    virtual ActionListener* getListener() = 0;

    /*
    * set listener for delays and other timed events
    */
    virtual void setListener(ActionListener* listener) = 0;

    /**
    * get Sound file
    */
//    /*public*/ virtual Sound getSound() = 0;

    /*public*/ virtual NamedBeanHandle<NamedBean*>* getNamedBean() = 0;
    /*public*/ virtual NamedBean* getBean() {return nullptr;}
};

#endif // CONDITIONALACTION_H
