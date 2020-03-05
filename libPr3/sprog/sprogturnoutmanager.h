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
  /*public*/ QString getSystemPrefix()const  override;
  /*public*/ Turnout* createNewTurnout(QString systemName, QString userName)const override;
  /*public*/ int getBitFromSystemName(QString systemName) const;
  /*public*/ NameValidity validSystemNameFormat(QString systemName)const override;
  /*public*/ bool allowMultipleAdditions(QString systemName) override;
  /*public*/ QString getEntryToolTip() override;
  QT_DEPRECATED
  static /*public*/ SprogTurnoutManager* instance();
  /*public*/ QString getNamedBeanClass()const override {
      return "Turnout";
  }

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogTurnoutManager");
  SprogSystemConnectionMemo* _memo;// = null;

 };
}
#endif // SPROGTURNOUTMANAGER_H
