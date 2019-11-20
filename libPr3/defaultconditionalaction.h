#ifndef DEFAULTCONDITIONALACTION_H
#define DEFAULTCONDITIONALACTION_H
#include "conditionalaction.h"
#include "logger.h"

class Memory;
class Sound;
class NamedBeanHandleManager;
class Conditional;
class LIBPR3SHARED_EXPORT DefaultConditionalAction : public ConditionalAction
{
    Q_OBJECT
public:
    explicit DefaultConditionalAction(QObject *parent = 0);
    /*public*/ DefaultConditionalAction(int option, int type, QString name, int actionData, QString actionStr, QObject *parent = 0);
    /*public*/ bool equals(QObject* obj);
    /*public*/ int hashCode();

    /*public*/ int getType();
    /*public*/ void setType(int type);
    /*public*/ void setType(QString type);
    /*public*/ QString getDeviceName();
    /*public*/ void setDeviceName(QString deviceName);
    /*public*/ NamedBeanHandle<NamedBean*>* getNamedBean();
    /*public*/ NamedBean* getBean();
    /*public*/ int getOption();
    /*public*/ void setOption(int option);
    /*public*/ int getActionData();
    /*public*/ void setActionData(QString actionData);
    /*public*/ void setActionData(int actionData);
    /*public*/ QString getActionString();
    /*public*/ void setActionString(QString actionString) ;
    /*public*/ QTimer* getTimer();
    /*public*/ void setTimer(QTimer* timer);
    /*public*/ bool isTimerActive();
    /*public*/ void startTimer();
    /*public*/ void stopTimer();
    /*public*/ ActionListener* getListener();
    /*public*/ void setListener(ActionListener* listener);
    /*public*/ Sound* getSound();
    /*public*/ QString getTypeString();
    /*public*/ QString getOptionString(bool type);
    /*public*/ QString getActionDataString();
    /*public*/ static QString getItemTypeString(int t);
    /*public*/ static QString getActionTypeString(int t);
    /*public*/ static QString getOptionString(int opt, bool type);
    /*public*/ static int stringToActionType(QString str);
    /*public*/ static int stringToActionData(QString str);
    /*public*/ static QString getActionDataString(int t, int data);
    /*public*/ QString description(bool triggerType);
signals:

public slots:
private:
    /*private*/ int _option;// = Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE;
    /*private*/ int _type;// = Conditional::ACTION_NONE ;
    /*private*/ QString _deviceName;// = " ";
    /*private*/ int _actionData = 0;
    /*private*/ QString _actionString;// = "";
    /*private*/ NamedBeanHandle<NamedBean*>* _namedBean = nullptr;

    /*private*/ QTimer* _timer = nullptr;
    /*private*/ ActionListener* _listener = nullptr;
    /*private*/ bool _timerActive = false;
    /*private*/ bool _indirectAction = false;
    /*private*/ Sound* _sound = nullptr;
    void common();
    /*private*/ Memory* getIndirectBean(QString devName);
    /*private*/ NamedBean* getActionBean(QString devName);

 Logger* log;
 NamedBeanHandleManager* nbhm;
protected:
 /*protected*/ void setSound(Sound* sound) ;

};

#endif // DEFAULTCONDITIONALACTION_H
