#ifndef DEFAULTMALESTRINGACTIONSOCKETSWING_H
#define DEFAULTMALESTRINGACTIONSOCKETSWING_H
#include "abstractmalesocketswing.h"
/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
/*public*/ class DefaultMaleStringActionSocketSwing : public AbstractMaleSocketSwing {
    Q_OBJECT
public:
    Q_INVOKABLE DefaultMaleStringActionSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent){
     setObjectName("DefaultMaleStringActionSocketSwing");
    }
    ~DefaultMaleStringActionSocketSwing() {}
    DefaultMaleStringActionSocketSwing(const DefaultMaleStringActionSocketSwing&) : AbstractMaleSocketSwing() {}

    QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DefaultMaleStringActionSocketSwing)
#endif // DEFAULTMALESTRINGACTIONSOCKETSWING_H
