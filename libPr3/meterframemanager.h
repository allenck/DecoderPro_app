#ifndef METERFRAMEMANAGER_H
#define METERFRAMEMANAGER_H

#include <QObject>
#include "meterframe.h"

class Logger;
class MeterFrameManager : public QObject
{
  Q_OBJECT
 public:
  explicit MeterFrameManager(QObject *parent = nullptr);
  /*public*/ static MeterFrameManager* getInstance();
  /*public*/ int getXMLOrder();
  /*public*/ void _register(/*@Nonnull*/ MeterFrame* frame);
  /*public*/ void deregister(/*@Nonnul*/ MeterFrame* frame);
  /*public*/ MeterFrame* getByUUID(/*@Nonnull*/ QUuid uuid);
  /*public*/ QList<MeterFrame*> getMeterFrames();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("MeterFrameManager");

  /*private*/ static /*final*/ MeterFrameManager* _instance;// = new MeterFrameManager();
  /*private*/ /*final*/ QMap<QUuid, MeterFrame*> _meterFrameList = QMap<QUuid, MeterFrame*>();

};

#endif // METERFRAMEMANAGER_H
