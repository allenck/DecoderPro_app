#ifndef LOGGINGUTIL_H
#define LOGGINGUTIL_H

#include <QObject>
#include <QSet>

class Logger;
class LoggingUtil : public QObject
{
  Q_OBJECT
 public:
  explicit LoggingUtil(QObject *parent = nullptr);
  /*public*/ static bool warnOnce(/*@Nonnull*/ Logger* logger, /*@Nonnull*/ QString msg/*, Object... args*/);
  /*public*/ static void deprecationWarning(/*@Nonnull*/ Logger* logger, /*@Nonnull*/ QString methodName);

 signals:

 public slots:

 protected:
  /*protected*/ static QMap<Logger*, QSet<QString> > warnedOnce;// = QMap<Logger, QSet<QString> >();
  /*protected*/ static bool logDeprecations;// = true;

};

#endif // LOGGINGUTIL_H
