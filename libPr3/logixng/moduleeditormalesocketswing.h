#ifndef MODULEEDITORMALESOCKETSWING_H
#define MODULEEDITORMALESOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an ModuleEditorMaleSocket object with a Swing JPanel.
 */
/*public*/ class ModuleEditorMaleSocketSwing : public AbstractMaleSocketSwing {
 Q_OBJECT
 public:
  ModuleEditorMaleSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent)
  {
   setObjectName("ModuleEditorMaleSocketSwing");
  }
//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(ModuleEditorMaleSocketSwing.class);

};

#endif // MODULEEDITORMALESOCKETSWING_H
