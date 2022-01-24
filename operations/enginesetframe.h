#ifndef ENGINESETFRAME_H
#define ENGINESETFRAME_H
#include "rollingstocksetframe.h"
#include "appslib_global.h"

namespace Operations
{
 class ESResourceBundle : public ResourceBundle
 {
  public:
   ESResourceBundle();
   QString getMessage(QString key)
   {
    return map.value(key);
   }
  private:
   QMap<QString, QString> map = QMap<QString, QString>();
 };
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
  /*public*/ QString getClassName();
  /*public*/ ResourceBundle* getRb();

 private:
  EngineManager* manager;// = EngineManager.instance();
  EngineManagerXml* managerXml;// = EngineManagerXml.instance();

  Engine* _engine;
  ESResourceBundle* rb = new ESResourceBundle();
 protected:
  /*protected*/ bool save();

 };


}
#endif // ENGINESETFRAME_H
