#ifndef ACTIONUPDATESLOTSSWING_H
#define ACTIONUPDATESLOTSSWING_H

#include "abstractdigitalactionswing.h"
#include "loconetsystemconnectionmemo.h"

class JComboBox;
class ActionUpdateSlotsSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionUpdateSlotsSwing(QObject *parent = nullptr);
    ~ActionUpdateSlotsSwing() {}
    ActionUpdateSlotsSwing(const ActionUpdateSlotsSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;

    QObject* sself() override {return this;}

private:
    /*private*/ JComboBox/*<LocoNetConnection*>*/* _locoNetConnection= nullptr;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;


};
/*private*/ /*static*/ class LocoNetConnection {

    /*private*/ LocoNetSystemConnectionMemo* _memo;
public:
    /*public*/ LocoNetConnection(LocoNetSystemConnectionMemo* memo) {
        _memo = memo;
    }

    //@Override
    /*public*/ QString toString() {
        return _memo->getUserName();
    }
};

Q_DECLARE_METATYPE(ActionUpdateSlotsSwing)
#endif // ACTIONUPDATESLOTSSWING_H
