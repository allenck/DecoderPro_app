#ifndef TRAINCUSTOMMANIFEST_H
#define TRAINCUSTOMMANIFEST_H
#include "traincustomcommon.h"
#include "instancemanagerautodefault.h"

namespace  Operations
{
 class TrainCustomManifest : public TrainCustomCommon, public InstanceManagerAutoDefault
 {
   Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)

 public:
  Q_INVOKABLE TrainCustomManifest(QObject* parent = 0);
   ~TrainCustomManifest() {}
   TrainCustomManifest(const TrainCustomManifest&) : TrainCustomCommon() {}
  /*public*/ static /*synchronized*/ TrainCustomManifest* instance();
  /*public*/ QString getDirectoryName();
  /*public*/ void setDirectoryName(QString name);
  /*public*/ void load(QDomElement options);
  /*public*/ void store(QDomElement options);

 private:
  /*private*/ QString directoryName;// = "csvManifests"; // NOI18N

  /**
   * record the single instance *
   */
  /*private*/ static TrainCustomManifest* _instance;// = null;

 };
}
Q_DECLARE_METATYPE(Operations::TrainCustomManifest)
#endif // TRAINCUSTOMMANIFEST_H
