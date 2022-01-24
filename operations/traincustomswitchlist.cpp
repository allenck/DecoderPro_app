#include "traincustomswitchlist.h"
#include "trainmanagerxml.h"
#include "xml.h"

namespace Operations {

 TrainCustomSwitchList::TrainCustomSwitchList(QObject *parent)
  : TrainCustomCommon(TrainManagerXml::CSV_SWITCH_LISTS, Xml::SWITCHLIST_CREATOR, parent)
 {

 }

} // namespace Operations
