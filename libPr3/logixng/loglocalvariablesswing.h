#ifndef LOGLOCALVARIABLESSWING_H
#define LOGLOCALVARIABLESSWING_H

#include "abstractdigitalactionswing.h"

class LogLocalVariablesSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LogLocalVariablesSwing(QObject *parent = nullptr);
    ~LogLocalVariablesSwing() {}
    LogLocalVariablesSwing(const LogLocalVariablesSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages) override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object)override;
    /*public*/ QString toString()override;
    /*public*/ void dispose() override;
protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};
Q_DECLARE_METATYPE(LogLocalVariablesSwing)
#endif // LOGLOCALVARIABLESSWING_H
