#ifndef SHUTDOWNCOMPUTERSWING_H
#define SHUTDOWNCOMPUTERSWING_H

#include "abstractdigitalactionswing.h"

class JComboBox;
class ShutdownComputerSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ShutdownComputerSwing(QObject *parent = nullptr);
    ~ShutdownComputerSwing() {}
    ShutdownComputerSwing(const ShutdownComputerSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString() override;
    /*public*/ void dispose()override;
private:
    /*private*/ JComboBox/*<Operation>*/* _operationComboBox;
protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(ShutdownComputerSwing)
#endif // SHUTDOWNCOMPUTERSWING_H
