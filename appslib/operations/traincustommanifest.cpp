#include "traincustommanifest.h"
#include "xml.h"

using namespace Operations;

TrainCustomManifest::TrainCustomManifest(QObject* parent) : TrainCustomCommon(parent)
{
 directoryName = "csvManifests"; // NOI18N
  QDomDocument doc = QDomDocument();
}
///*public*/ class TrainCustomManifest extends TrainCustomCommon {

/**
 * record the single instance *
 */
/*private*/ /*static*/ TrainCustomManifest* TrainCustomManifest::_instance = NULL;

/*public*/ /*static*/ /*synchronized*/ TrainCustomManifest* TrainCustomManifest::instance()
{
 if (_instance == NULL)
 {
  // create and load
  _instance = new TrainCustomManifest();
 }
 return _instance;
}

//@Override
/*public*/ QString TrainCustomManifest::getDirectoryName() {
    return directoryName;
}

//@Override
/*public*/ void TrainCustomManifest::setDirectoryName(QString name) {
    directoryName = name;
}

//@Override
/*public*/ void  TrainCustomManifest::load(QDomElement options) {
    QDomElement mc = options.firstChildElement(Xml::MANIFEST_CREATOR);
    TrainCustomCommon::load(mc);
}

//@Override
/*public*/ void  TrainCustomManifest::store(QDomElement options) {

    QDomElement mc = doc.createElement(Xml::MANIFEST_CREATOR);
    TrainCustomCommon::store(mc);
    options.appendChild(mc);
}
