#ifndef DEFAULTMALEANALOGACTIONSOCKETSWING_H
#define DEFAULTMALEANALOGACTIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
/*public*/ class DefaultMaleAnalogActionSocketSwing : public AbstractMaleSocketSwing {
 Q_OBJECT
 public:
  Q_INVOKABLE DefaultMaleAnalogActionSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent)
  {
   setObjectName("DefaultMaleAnalogActionSocketSwing");
  }
    ~DefaultMaleAnalogActionSocketSwing() {}
    DefaultMaleAnalogActionSocketSwing(const DefaultMaleAnalogActionSocketSwing&) : AbstractMaleSocketSwing() {}

    QObject* sself() override {return this;}

};
Q_DECLARE_METATYPE(DefaultMaleAnalogActionSocketSwing)
#endif // DEFAULTMALEANALOGACTIONSOCKETSWING_H
