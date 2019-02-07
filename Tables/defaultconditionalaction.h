#ifndef DEFAULTCONDITONALACTION_H
#define DEFAULTCONDITONALACTION_H
#include "conditionalaction.h"

class Sound;
class Logger;
class NamedBeanHandleManager;
class DefaultConditionalAction : public ConditionalAction
{
    Q_OBJECT
public:
    explicit DefaultConditionalAction(QObject *parent = 0);
    /*public*/ DefaultConditionalAction(int option, int type, QString name, int actionData, QString actionStr ,QObject *parent = 0);
    /*public*/ int getType();
    /*public*/ void setType(int type) ;
    /*public*/ void setType(QString type);
    /*public*/ QString getDeviceName();
    /*public*/ void setDeviceName(QString deviceName);
    /*public*/ NamedBeanHandle<NamedBean*>* getNamedBean();
    /*public*/ NamedBean* getBean();
    /*public*/ int getOption();
    /*public*/ void setOption(int option);
    /*public*/ int getActionData();
    /*public*/ void setActionData(int actionData);
    /*public*/ void setActionData(QString actionData) ;
    /*public*/ QString getActionString();
    /*public*/ void setActionString(QString actionString);
    /*public*/ QTimer* getTimer();
    /*public*/ void setTimer(QTimer* timer);
    /*public*/ bool isTimerActive();
    /*public*/ void startTimer();
    /*public*/ void stopTimer();
    /*public*/ ActionListener* getListener();
    /*public*/ void setListener(ActionListener* listener);
    /*public*/ Sound* getSound() ;
    /**** Methods that return user interface strings *****/
    /*public*/ QString getTypeString();
    /*public*/ QString getOptionString(bool type) ;
    /*public*/ QString getActionDataString();
    /*public*/ static QString getItemTypeString(int t);
    /*public*/ static QString getActionTypeString(int t);
    /*public*/ static QString getOptionString(int opt, bool type) ;
    /*public*/ static int stringToActionType(QString str);
    /*public*/ static int stringToActionData(QString str);
    /*public*/ static QString getActionDataString(int t, int data);
    /*public*/ QString description(bool triggerType);

signals:

public slots:
private:
    /*private*/ int _option;// = Conditional.ACTION_OPTION_ON_CHANGE_TO_TRUE;
    /*private*/ int _type;// = Conditional.ACTION_NONE ;
    /*private*/ QString _deviceName;// = " ";
    /*private*/ int _actionData;// = 0;
    /*private*/ QString _actionString;// = "";
    /*private*/ NamedBeanHandle<NamedBean*>* _namedBean;// = null;

    /*private*/ QTimer* _timer;// = null;
    /*private*/ ActionListener* _listener;// = null;
    /*private*/ bool _timerActive;// = false;
    /*private*/ Sound* _sound = nullptr;
    void common();
   Logger* log;

protected:
   /*protected*/ NamedBeanHandleManager* nbhm;// = jmri.InstanceManager::getDefault(jmri.NamedBeanHandleManager.class);

//    void setSound(Sound sound);

};

#endif // DEFAULTCONDITONALACTION_H
