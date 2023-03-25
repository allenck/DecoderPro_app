#ifndef DOSTRINGACTIONSWING_H
#define DOSTRINGACTIONSWING_H

#include "abstractdigitalactionswing.h"

class DoStringActionSwing : public AbstractDigitalActionSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DoStringActionSwing(QObject *parent = nullptr);
    ~DoStringActionSwing() {}
    DoStringActionSwing(const DoStringActionSwing&) : AbstractDigitalActionSwing() {}
    /*public*/ bool validate(/*@Nonnull*/ QList<QString>* errorMessages)  override;
    /*public*/ MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)  override;
    /*public*/ void updateObject(/*@Nonnull*/ Base* object) override;
    /*public*/ QString toString()  override;
    /*public*/ void dispose() override;

    QObject* sself() override {return this;}
protected:
    /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) override;

};
Q_DECLARE_METATYPE(DoStringActionSwing)
#endif // DOSTRINGACTIONSWING_H
