#ifndef DOANALOGACTIONSWING_H
#define DOANALOGACTIONSWING_H

#include "abstractdigitalactionswing.h"

class DoAnalogActionSwing : public AbstractDigitalActionSwing
{
   Q_OBJECT
public:
    Q_INVOKABLE explicit DoAnalogActionSwing(QObject *parent = nullptr);
    ~DoAnalogActionSwing() {}
    DoAnalogActionSwing(const DoAnalogActionSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString() override;
    /*public*/ void dispose() override;

protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(DoAnalogActionSwing)
#endif // DOANALOGACTIONSWING_H
