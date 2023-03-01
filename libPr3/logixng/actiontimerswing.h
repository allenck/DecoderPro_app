#ifndef ACTIONTIMERSWING_H
#define ACTIONTIMERSWING_H

#include "abstractdigitalactionswing.h"

class ActionTimer;
class JCheckBox;
class JComboBox;
class JButton;
class ActionTimerSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionTimerSwing(QObject *parent = nullptr);
    ~ActionTimerSwing() {}
    ActionTimerSwing(const ActionTimerSwing&) :AbstractDigitalActionSwing() {}
    /*public*/ static /*final*/ int MAX_NUM_TIMERS;// = 10;
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;

    QObject* sself() override {return this;}

private:
    /*private*/ JCheckBox* _startImmediately;
    /*private*/ JCheckBox* _runContinuously;
    /*private*/ JComboBox/*<TimerUnit>*/* _unitComboBox;
    /*private*/ JTextField* _numTimers;
    /*private*/ JButton* _addTimer;
    /*private*/ JButton* _removeTimer;
    /*private*/ QVector<JTextField*>* _timerSocketNames;
    /*private*/ QVector<JTextField*>* _timerDelays;
    /*private*/ int numActions = 1;
    /*private*/ QString getNewSocketName(ActionTimer* action);


protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ActionTimerSwing)
#endif // ACTIONTIMERSWING_H
