#ifndef ENGINE_H
#define ENGINE_H
#include "rollingstock.h"
#include <QtXml>
#include "appslib_global.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class QDomElement;
class Logger;
namespace Operations
{
 class EngineModels;
 class Consist;
 class APPSLIBSHARED_EXPORT Engine : public RollingStock//, public PropertyChangeListener
 {
  Q_OBJECT
  //Q_INTERFACES(PropertyChangeListener)
 public:
  //explicit Engine(QObject *parent = 0);
  /*public*/ Engine(QString road, QString number, QObject *parent = 0);
  /*public*/ void setModel(QString model);
  /*public*/ QString getModel();
  /*public*/ Engine(QDomElement e);
  /*public*/ QDomElement store(QDomDocument doc);
  /*public*/ Consist* getConsist();
  /*public*/ QString getConsistName();
  /*public*/ void setHp(QString hp);
  /*public*/ QString getHp() ;
  /*public*/ int getHpInteger();
  /*public*/ void setLength(QString length);
  /*public*/ QString getLength();
  /*public*/ void setWeightTons(QString weight);
  /*public*/ QString getWeightTons();
  /*public*/ void setConsist(Consist* consist);
  /*public*/ void setTypeName(QString type);
  /*public*/ QString getTypeName();
  /*public*/ QString testDestination(Location* destination, Track* track);
  /*public*/ void dispose();
  /*public*/ static /*final*/ int NCE_REAR_BLOCK_NUMBER;// = 8;
  /*public*/ static /*final*/ int B_UNIT_BLOCKING;// = 10; // block B Units after NCE Consists
  /*public*/ static /*final*/ QString HP_CHANGED_PROPERTY;// = "hp"; // NOI18N
  /*public*/ void setBunit(bool bUnit) ;
  /*public*/ bool isBunit();

   QObject* pself() override {return (QObject*)this; }
 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  /*private*/ Consist* _consist;// = null;
  /*private*/ QString _model;// = NONE;
  void common();
  EngineModels* engineModels;// = EngineModels::instance();
  Logger* log;
  /*private*/ void addPropertyChangeListeners();
  bool verboseStore = false;

 protected:
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ void moveRollingStock(RouteLocation* old, RouteLocation* next);

 };
}
#endif // ENGINE_H
