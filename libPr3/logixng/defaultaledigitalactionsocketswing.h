#ifndef DEFAULTALEDIGITALACTIONSOCKETSWING_H
#define DEFAULTALEDIGITALACTIONSOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
/*public*/ class DefaultMaleDigitalActionSocketSwing : public AbstractMaleSocketSwing {
Q_OBJECT
 public:
  DefaultMaleDigitalActionSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent)
  {
   setObjectName("DefaultMaleDigitalActionSocketSwing");
  }
};

#endif // DEFAULTALEDIGITALACTIONSOCKETSWING_H
