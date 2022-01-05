#ifndef OPERATIONS_TRAINCUSTOMSWITCHLIST_H
#define OPERATIONS_TRAINCUSTOMSWITCHLIST_H

#include "traincustomcommon.h"
#include "instancemanagerautodefault.h"

namespace Operations {

 class TrainCustomSwitchList : public TrainCustomCommon, public InstanceManagerAutoDefault
 {
   Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)
  public:
   explicit TrainCustomSwitchList(QObject *parent = nullptr);
   ~TrainCustomSwitchList() {}
   TrainCustomSwitchList(const TrainCustomSwitchList& ) : TrainCustomCommon("", "") {}
 };

} // namespace Operations
Q_DECLARE_METATYPE(Operations::TrainCustomCommon)
#endif // OPERATIONS_TRAINCUSTOMSWITCHLIST_H
