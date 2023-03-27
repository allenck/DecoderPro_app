#ifndef DEFAULTMALEANALOGEXPRESSIONSOCKETSWING_H
#define DEFAULTMALEANALOGEXPRESSIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

class DefaultMaleAnalogExpressionSocketSwing : public AbstractMaleSocketSwing
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultMaleAnalogExpressionSocketSwing(QObject *parent = nullptr);
    ~DefaultMaleAnalogExpressionSocketSwing() {}
    DefaultMaleAnalogExpressionSocketSwing(const DefaultMaleAnalogExpressionSocketSwing&) : AbstractMaleSocketSwing() {}
    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DefaultMaleAnalogExpressionSocketSwing)
#endif // DEFAULTMALEANALOGEXPRESSIONSOCKETSWING_H
