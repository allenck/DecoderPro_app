#ifndef TRAINCUSTOMMANIFEST_H
#define TRAINCUSTOMMANIFEST_H
#include "traincustomcommon.h"

namespace  Operations
{


class TrainCustomManifest : public TrainCustomCommon
{
public:
 TrainCustomManifest(QObject* parent = 0);
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
#endif // TRAINCUSTOMMANIFEST_H
