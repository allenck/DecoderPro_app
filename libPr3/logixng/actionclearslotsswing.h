#ifndef ACTIONCLEARSLOTSSWING_H
#define ACTIONCLEARSLOTSSWING_H

#include "abstractdigitalactionswing.h"
#include "loconetsystemconnectionmemo.h"


class LocoNetSystemConnectionMemo;
class JComboBox;
class ActionClearSlotsSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ActionClearSlotsSwing(QObject *parent = nullptr);
    ~ActionClearSlotsSwing() {}
    ActionClearSlotsSwing(const ActionClearSlotsSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose()override;

private:
    /*private*/ JComboBox/*<LocoNetConnection>*/* _locoNetConnection;
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
        friend class ActionClearSlotsSwing;
    };
protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ActionClearSlotsSwing)
#endif // ACTIONCLEARSLOTSSWING_H
