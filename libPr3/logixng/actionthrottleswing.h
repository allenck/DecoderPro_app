#ifndef ACTIONTHROTTLESWING_H
#define ACTIONTHROTTLESWING_H

#include "abstractdigitalactionswing.h"

class ActionThrottleSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionThrottleSwing(QObject *parent = nullptr);
    ~ActionThrottleSwing() {}
    ActionThrottleSwing(const ActionThrottleSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString() override;
    /*public*/ void dispose()override;

    QObject* sself() override{return this;}

private:

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ActionThrottleSwing)
#endif // ACTIONTHROTTLESWING_H
