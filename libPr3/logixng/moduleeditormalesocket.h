#ifndef MODULEEDITORMALESOCKET_H
#define MODULEEDITORMALESOCKET_H

#include "abstractmalesocket.h"

class Module;
class ModuleEditorMaleSocket : public AbstractMaleSocket
{
  Q_OBJECT
 public:
  ModuleEditorMaleSocket(BaseManager/*<? extends NamedBean>*/* manager, Module* module, QObject *parent = nullptr);
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  void setEnabledFlag(bool enable)override;
  /*public*/  bool isEnabled() override;
  /*public*/  void setDebugConfig(DebugConfig* config)override;
  /*public*/  DebugConfig* getDebugConfig() override;
  /*public*/  DebugConfig* createDebugConfig()override;
  /*public*/  QString getComment() override;
  /*public*/  void setComment(QString comment)override;
  QString getClassName() {return "jmri.jmrit.logixng.swing.ModuleEditorMaleSocket";}
 private:

 protected:
  /*protected*/ void registerListenersForThisClass() override;
  /*protected*/ void unregisterListenersForThisClass() override;
  /*protected*/ void disposeMe()override;



};

#endif // MODULEEDITORMALESOCKET_H
