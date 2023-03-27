#ifndef MODULEEDITORMALESOCKETSWING_H
#define MODULEEDITORMALESOCKETSWING_H

#include "abstractmalesocketswing.h"

/**
 * Configures an ModuleEditorMaleSocket object with a Swing JPanel.
 */
/*public*/ class ModuleEditorMaleSocketSwing : public AbstractMaleSocketSwing {
 Q_OBJECT
 public:
  Q_INVOKABLE ModuleEditorMaleSocketSwing(QObject* parent = nullptr) : AbstractMaleSocketSwing(parent)
  {
   setObjectName("ModuleEditorMaleSocketSwing");
  }
    ~ModuleEditorMaleSocketSwing() {}
    ModuleEditorMaleSocketSwing(const ModuleEditorMaleSocketSwing&) : AbstractMaleSocketSwing() {}

  QObject* sself() override {return this;}
};
Q_DECLARE_METATYPE(ModuleEditorMaleSocketSwing)
#endif // MODULEEDITORMALESOCKETSWING_H
