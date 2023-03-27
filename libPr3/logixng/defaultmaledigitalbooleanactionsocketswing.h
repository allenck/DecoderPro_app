#ifndef DEFAULTMALEDIGITALBOOLEANACTIONSOCKETSWING_H
#define DEFAULTMALEDIGITALBOOLEANACTIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
/*public*/ class DefaultMaleDigitalBooleanActionSocketSwing : public AbstractMaleSocketSwing {
Q_OBJECT
 public:
  DefaultMaleDigitalBooleanActionSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent)
  {
   setObjectName("DefaultMaleDigitalBooleanActionSocketSwing");
  }
  ~DefaultMaleDigitalBooleanActionSocketSwing() {}
  DefaultMaleDigitalBooleanActionSocketSwing(const DefaultMaleDigitalBooleanActionSocketSwing&) : AbstractMaleSocketSwing() {}

  QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(DefaultMaleDigitalBooleanActionSocketSwing)
#endif // DEFAULTMALEDIGITALBOOLEANACTIONSOCKETSWING_H
