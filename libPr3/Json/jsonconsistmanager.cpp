#include "jsonconsistmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "consistfile.h"
#include "jsonutil.h"

/**
 * ConsistManager for the JSON services. This consist manager passes requests
 * for CS consisting to the
 *
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class JsonConsistManager extends Bean implements ConsistManager {

/*private*/ /*final*/ /*static*/ Logger* JsonConsistManager::log = LoggerFactory::getLogger("JsonConsistManager");

/*public*/ JsonConsistManager::JsonConsistManager(QObject* parent)  : Bean(parent)
{
    //super();
//    InstanceManager.addPropertyChangeListener((PropertyChangeEvent evt) -> {
//        if (evt.getPropertyName().equals(InstanceManager.getDefaultsPropertyName(ConsistManager.class))) {
//            this->manager = InstanceManager.getDefault(ConsistManager.class);
//            this->manager.addConsistListListener(() -> {
//                this->notifyConsistListChanged();
//            });
//            this->manager.requestUpdateFromLayout();
//            try {
//                (new ConsistFile()).readFile();
//            } catch (JDOMException | IOException ex) {
//                log.warn("Error reading consist file {} due to {}", ConsistFile.defaultConsistFilename(), ex.getMessage());
//            }
//        }
//    });
    this->manager = (ConsistManager*)InstanceManager::getNullableDefault("ConsistManager");
    if (this->manager != NULL) {
//        this->manager->addConsistListListener(() -> {
//            this->notifyConsistListChanged();
//        });
     connect((AbstractConsistManager*)manager, SIGNAL(consistListChanged()), this, SLOT(notifyConsistListChanged()));
        this->manager->requestUpdateFromLayout();
        try {
            (new ConsistFile())->readFile();
        }
     catch (JDOMException ex ) {
            log->warn(tr("Error reading consist file %1 due to %2").arg( ConsistFile::defaultConsistFilename()).arg(ex.getMessage()));
        }
     catch ( IOException ex) {
            log->warn(tr("Error reading consist file %1 due to %2").arg( ConsistFile::defaultConsistFilename()).arg(ex.getMessage()));
        }

    }
}

//@Override
/*public*/ DccConsist *JsonConsistManager::getConsist(DccLocoAddress* address) {
    if (this->manager != NULL) {
        return this->manager->getConsist(address);
    }
    return NULL;
}

//@Override
/*public*/ void JsonConsistManager::delConsist(DccLocoAddress* address) {
    if (this->manager != NULL) {
        this->manager->delConsist(address);
    }
}

//@Override
/*public*/ bool JsonConsistManager::isCommandStationConsistPossible() {
    if (this->manager != NULL) {
        return this->manager->isCommandStationConsistPossible();
    }
    return false;
}

//@Override
/*public*/ bool JsonConsistManager::csConsistNeedsSeparateAddress() {
    if (this->manager != NULL) {
        return this->manager->csConsistNeedsSeparateAddress();
    }
    return false;
}

//@Override
/*public*/ DccLocoAddressList *JsonConsistManager::getConsistList() {
    if (this->manager != NULL) {
        return this->manager->getConsistList();
    }
    return new DccLocoAddressList();
}

//@Override
/*public*/ QString JsonConsistManager::decodeErrorCode(int errorCode) {
    if (this->manager != NULL) {
        return this->manager->decodeErrorCode(errorCode);
    }
    return "Unknown Status Code: " + errorCode;
}

//@Override
/*public*/ void JsonConsistManager::requestUpdateFromLayout() {
    if (this->manager != NULL) {
        this->manager->requestUpdateFromLayout();
    }
}

//@Override
/*public*/ void JsonConsistManager::addConsistListListener(ConsistListListener* listener) {
    this->listeners->insert(listener);
 //connect((AbstractConsistManager*)this->manager, SIGNAL(consistListChanged()), listener, SLOT(notifyConsistListChanged()));
}

//@Override
/*public*/ void JsonConsistManager::removeConsistListListener(ConsistListListener* listener) {
    this->listeners->remove(listener);
 //connect(this, SIGNAL(), listener, SLOT());
}

//@Override
/*public*/ void JsonConsistManager::notifyConsistListChanged()
{
 emit consistListChanged();
}


/**
 * Test if a real ConsistManager is available.
 *
 * @return true if a real consist manager is available, false otherwise.
 */
/*public*/ bool JsonConsistManager::isConsistManager() {
    return this->manager != NULL;
}
void JsonConsistManager::propertyChange(PropertyChangeEvent* evt)
{
 if (evt->getPropertyName() == (InstanceManager::getDefaultsPropertyName("ConsistManager")))
 {
  this->manager = (ConsistManager*)InstanceManager::getDefault("ConsistManager");
//  this->manager.addConsistListListener(() -> {
//      this->notifyConsistListChanged();
//  });
  connect(this->manager->self(), SIGNAL(notifyConsistListChanged()), this, SLOT(notifyConsistListChanged()));
  this->manager->requestUpdateFromLayout();
  try {
      (new ConsistFile())->readFile();
  } catch (JDOMException  ex) {
      log->warn(tr("Error reading consist file %1 due to %2").arg(ConsistFile::defaultConsistFilename()).arg(ex.getMessage()));
  }
  catch ( IOException ex) {
        log->warn(tr("Error reading consist file %1 due to %2").arg(ConsistFile::defaultConsistFilename()).arg(ex.getMessage()));
    }
 }
}
