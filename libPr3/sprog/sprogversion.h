#ifndef SPROGVERSION_H
#define SPROGVERSION_H
#include "sprogtype.h"
#include <QObject>

namespace Sprog
{
 class SprogVersion : public QObject
 {
  Q_OBJECT
 public:
  explicit SprogVersion(SprogType* t, QObject *parent = nullptr);
  /*public*/ SprogType* sprogType;// = null;
  /*public*/ QString sprogVersion;// = "";
  /*public*/ SprogVersion(SprogType* t, QString s, QObject* parent = nullptr);
  /*public*/ int getMajorVersion();
  /*public*/ int getMinorVersion();
  /*public*/ bool hasExtraFeatures();
  /*public*/ bool hasBlueLine();
  /*public*/ bool hasCurrentLimit();
  /*public*/ bool hasFirmwareLock();
  /*public*/ bool hasZTCMode();
  /*public*/ QString toString();
  /*public*/ QString toString(SprogVersion* s);


 signals:

 public slots:
 private:
  void common();
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(SprogVersion.class);

  friend class SprogSystemConnectionMemo;
 };
}
#endif // SPROGVERSION_H
