#ifndef SPROGVERSIONQUERY_H
#define SPROGVERSIONQUERY_H

#include <QObject>
#include "sprogtrafficcontroller.h"
#include <QTimer>
#include "sprogversionlistener.h"

class Logger;
namespace Sprog
{
 class SprogVersion;
 class SprogVersionQuery : public QObject
 {
  Q_OBJECT
 public:
  explicit SprogVersionQuery(SprogSystemConnectionMemo* memo, QObject *parent = nullptr);
  // enum for version query states
  enum QueryState {

      IDLE,
      CRSENT, // awaiting reply to " "
      QUERYSENT, // awaiting reply to "?"
      DONE
  };       // Version has been found
  /*public*/ /*synchronized*/ void removeSprogVersionListener(SprogVersionListener* l);
  QT_DEPRECATED
  static /*public*/ SprogVersionQuery* instance();
  /*synchronized*/ /*public*/ void requestVersion(SprogVersionListener* l);
  /*public*/ void notifyMessage(SprogMessage* m);

 signals:
 void do_notifyVersion(SprogVersion* v);

 public slots:
 /*synchronized*/ /*public*/ void notifyReply(SprogReply* m);

 private:
      /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogVersionQuery");
  QString replyString;
  SprogTrafficController* tc;
  SprogVersion* ver;
  QTimer* timer;// = null;
  QueryState state = QueryState::IDLE;
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  /*private*/ /*synchronized*/ QVector<SprogVersionListener*>* getCopyOfListeners();

 protected:
  /*final*/ /*protected*/ int LONG_TIMEOUT;// = 2000;
  /*protected*/ static /*final*/ QVector<SprogVersionListener*>* versionListeners;// = new Vector<SprogVersionListener>();
  /*protected*/ /*synchronized*/ void addSprogVersionListener(SprogVersionListener* l);
  /*protected*/ /*synchronized*/ void notifyVersion(SprogVersion* v);
  /*protected*/ void startLongTimer();
  /*protected*/ void stopTimer();
  /*protected*/ void restartTimer(int delay);

 protected slots:
  /*synchronized*/ /*protected*/ void timeout();

 };
}
#endif // SPROGVERSIONQUERY_H
