#ifndef SPROGTURNOUTMANAGER_H
#define SPROGTURNOUTMANAGER_H
#include "abstractturnoutmanager.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogTurnoutManager : public AbstractTurnoutManager
 {
  Q_OBJECT

 public:
  SprogTurnoutManager(SprogSystemConnectionMemo*, QObject* parent = 0);
  /*public*/ QString getSystemPrefix() const override;
  /*public*/ Turnout* createNewTurnout(QString systemName, QString userName) override;
  /*public*/ int getBitFromSystemName(QString systemName);
  /*public*/ NameValidity validSystemNameFormat(QString systemName) override;
  /*public*/ bool allowMultipleAdditions(QString systemName) override;
  /*public*/ QString getEntryToolTip() override;
  QT_DEPRECATED
  static /*public*/ SprogTurnoutManager* instance();
  /*public*/ QString getNamedBeanClass()const override {
      return "Turnout";
  }
  /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}

  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogTurnoutManager");
  SprogSystemConnectionMemo* _memo;// = null;

 };
}
#endif // SPROGTURNOUTMANAGER_H
