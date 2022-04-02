#ifndef DEFAULTMALESTRINGEXPRESSIONSOCKETSWING_H
#define DEFAULTMALESTRINGEXPRESSIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
/*public*/ class DefaultMaleStringExpressionSocketSwing : public AbstractMaleSocketSwing {
  Q_OBJECT
 public:
  DefaultMaleStringExpressionSocketSwing(QObject* parent = nullptr) :AbstractMaleSocketSwing(parent){
   setObjectName("DefaultMaleStringExpressionSocketSwing");
  }
};

#endif // DEFAULTMALESTRINGEXPRESSIONSOCKETSWING_H
