#ifndef DEFAULTMALEANALOGACTIONSOCKETSWING_H
#define DEFAULTMALEANALOGACTIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
/*public*/ class DefaultMaleAnalogActionSocketSwing : public AbstractMaleSocketSwing {
 Q_OBJECT
 public:
  DefaultMaleAnalogActionSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent)
  {
   setObjectName("DefaultMaleAnalogActionSocketSwing");
  }
};

#endif // DEFAULTMALEANALOGACTIONSOCKETSWING_H
