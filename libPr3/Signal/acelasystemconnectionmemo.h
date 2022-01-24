#ifndef ACELASYSTEMCONNECTIONMEMO_H
#define ACELASYSTEMCONNECTIONMEMO_H

#include <defaultsystemconnectionmemo.h>

class AcelaTrafficController;
class ComponentFactory;
class AcelaSystemConnectionMemo : public DefaultSystemConnectionMemo
{
 public:
  /*public*/  AcelaSystemConnectionMemo(QObject* parent = nullptr);
  /*public*/  AcelaSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString userName, QObject* parent = nullptr) ;
  /*public*/  AcelaTrafficController* getTrafficController();


 private:
  static Logger* log;
  void common();
  ComponentFactory* cf = nullptr;
  AcelaTrafficController* tc = nullptr;
};

#endif // ACELASYSTEMCONNECTIONMEMO_H
