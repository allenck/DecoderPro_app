#ifndef DEFAULTMALEDIGITALACTIONSOCKETSWING_H
#define DEFAULTMALEDIGITALACTIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

class DefaultMaleDigitalActionSocketSwing : public AbstractMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultMaleDigitalActionSocketSwing(QObject *parent = nullptr);
    ~DefaultMaleDigitalActionSocketSwing() {}
    DefaultMaleDigitalActionSocketSwing(const DefaultMaleDigitalActionSocketSwing&) : AbstractMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DefaultMaleDigitalActionSocketSwing)

#endif // DEFAULTMALEDIGITALACTIONSOCKETSWING_H
