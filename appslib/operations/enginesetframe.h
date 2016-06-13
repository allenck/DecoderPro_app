#ifndef ENGINESETFRAME_H
#define ENGINESETFRAME_H
#include "rollingstocksetframe.h"
#include "appslib_global.h"

namespace Operations
{
 class Engine;
 class EngineManager;
 class EngineManagerXml;
 class APPSLIBSHARED_EXPORT EngineSetFrame : public RollingStockSetFrame
 {
  Q_OBJECT
 public:
  EngineSetFrame(QObject* parent =0);
  /*public*/ void initComponents();
  /*public*/ void loadEngine(Engine* engine);

 private:
  EngineManager* manager;// = EngineManager.instance();
  EngineManagerXml* managerXml;// = EngineManagerXml.instance();

  Engine* _engine;
 protected:
  /*protected*/ bool save();

 };
}
#endif // ENGINESETFRAME_H
