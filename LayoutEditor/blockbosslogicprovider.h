#ifndef BLOCKBOSSLOGICPROVIDER_H
#define BLOCKBOSSLOGICPROVIDER_H

#include <QObject>

class Logger;
class SignalHeadManager;
class SignalHead;
class BlockBossLogic;
class BlockBossLogicProvider : public QObject
{
  Q_OBJECT
 public:
  explicit BlockBossLogicProvider(QObject *parent = nullptr);
  /*public*/ BlockBossLogic* provide(/*@Nonnull*/ QString signalName);
  /*public*/ BlockBossLogic* provide(/*@Nonnull*/ SignalHead* signalHead);
  /*public*/ void _register(BlockBossLogic* blockBossLogic);
  /*public*/ void remove(BlockBossLogic* blockBossLogic);
  /*public*/ QList<BlockBossLogic*> provideAll();
  /*public*/ void dispose();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ SignalHeadManager* signalHeadManager;
  /*private*/ /*final*/ QMap<SignalHead*,BlockBossLogic*>* headToBlockBossLogicMap;
  static Logger* log;
};

#endif // BLOCKBOSSLOGICPROVIDER_H
