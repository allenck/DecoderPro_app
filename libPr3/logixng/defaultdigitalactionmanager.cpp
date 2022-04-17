#include "defaultdigitalactionmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"
#include "actionfactory.h"
#include "actionfactory_loconet.h"
#include "actions/digitalfactory.h"
#include "digitalactionmanager.h"
#include "debuggermaledigitalactionsocketfactory.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "defaultmaledigitalactionsocket.h"
#include "defaultfemaledigitalactionsocket.h"

/**
 * Class providing the basic logic of the DigitalActionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultDigitalActionManager extends AbstractBaseManager<MaleDigitalActionSocket>
//        implements DigitalActionManager {

/*public*/  DefaultDigitalActionManager::DefaultDigitalActionManager(QObject *parent) : AbstractBaseManager(parent){
  setObjectName("DefaultDigitalActionManager");
  registerSelf();
    ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);

//        for (DigitalActionFactory* actionFactory : ServiceLoader.load(DigitalActionFactory.class)) {
//            actionFactory.init();
//        }
    (new ActionFactory())->init();
    (new DigitalFactory())->init();
    (new ActionFactory_LocoNet())->init();

    for (Category* category : Category::values()) {
        actionClassList.insert(category, QList<QString>());
    }

//        for (DigitalActionFactory actionFactory : ServiceLoader.load(DigitalActionFactory.class)) {
//            actionFactory.getActionClasses().forEach((entry) -> {
////                System.out.format("Add action: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                actionClassList.get(entry.getKey()).add(entry.getValue());
//            });
//        }
    QList<DigitalActionFactory*> factories = {(DigitalActionFactory*) new ActionFactory(), (DigitalActionFactory*)new DigitalFactory()};
    for(DigitalActionFactory* actionFactory : factories)
    {
     QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> sets = actionFactory->getActionClasses();
     for (QHash<Category*, /*Class<? extends DigitalActionBean>*/QString> set : sets)
     {
      QHashIterator<Category*, QString> entry(set);
      while(entry.hasNext())
      {
       entry.next();
       QStringList list = actionClassList.value(entry.key());
       list.append(entry.value());
       //actionClassList.value(entry.key()).append(entry.value());
       actionClassList.insert(entry.key(), list); // will replace!
      }
     }
    }
//        for (MaleDigitalActionSocketFactory* maleSocketFactory : ServiceLoader.load(MaleDigitalActionSocketFactory.class)) {
//            _maleSocketFactories.add(maleSocketFactory);
//        }
    _maleSocketFactories.append(new DebuggerMaleDigitalActionSocketFactory());
}

/** {@inheritDoc} */
//@Override
/*public*/  /*Class<? extends MaleSocket>*/QString DefaultDigitalActionManager::getMaleSocketClass() {
    return "DefaultMaleDigitalActionSocket";
}

/*protected*/ MaleDigitalActionSocket* DefaultDigitalActionManager::createMaleActionSocket(DigitalActionBean* action) {
    MaleDigitalActionSocket* socket = new DefaultMaleDigitalActionSocket(this, action);
    action->setParent(socket);
    return socket;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* DefaultDigitalActionManager::getLastRegisteredMaleSocket() {
    return _lastRegisteredBean;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket *DefaultDigitalActionManager::registerBean(/*MaleDigitalActionSocket*/MaleSocket *maleSocket) {
    MaleSocket* bean = AbstractBaseManager::registerBean(maleSocket);
    _lastRegisteredBean = (MaleSocket*)maleSocket;
    return bean;
}

/**
 * Remember a NamedBean Object created outside the manager.
 * This method creates a MaleDigitalActionSocket for the action.
 *
 * @param action the bean
 */
//@Override
/*public*/  MaleDigitalActionSocket* DefaultDigitalActionManager::registerAction(/*@Nonnull*/ DigitalActionBean* action)
        /*throws IllegalArgumentException*/ {

    if (qobject_cast<MaleDigitalActionSocket*>(action->bself())) {
        throw new IllegalArgumentException("registerAction() cannot register a MaleDigitalActionSocket. Use the method register() instead.");
    }

    // Check if system name is valid
    if (this->validSystemNameFormat(((AbstractNamedBean*)action->self())->getSystemName()) != NameValidity::VALID) {
        log->warn("SystemName " + ((AbstractNamedBean*)action->self())->getSystemName() + " is not in the correct format");
        throw new IllegalArgumentException(tr("System name is invalid: %1").arg(((AbstractNamedBean*)action->self())->getSystemName()));
    }

    // Keep track of the last created auto system name
    updateAutoNumber(((AbstractNamedBean*)action->self())->getSystemName());

    // save in the maps
    MaleDigitalActionSocket* maleSocket = createMaleActionSocket(action);
    //return (MaleDigitalActionSocket*)registerBean(maleSocket);
    registerBean(maleSocket);
    return maleSocket;
}

//@Override
/*public*/  int DefaultDigitalActionManager::getXMLOrder() const {
    return LOGIXNG_DIGITAL_ACTIONS;
}

//@Override
/*public*/  QChar DefaultDigitalActionManager::typeLetter() const {
    return 'Q';
}

//@Override
/*public*/  FemaleDigitalActionSocket* DefaultDigitalActionManager::createFemaleSocket(
        Base* parent, FemaleSocketListener* listener, QString socketName) {
    return new DefaultFemaleDigitalActionSocket(parent, listener, socketName);
}

//@Override
/*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> DefaultDigitalActionManager::getActionClasses() {
    return actionClassList;
}

/** {@inheritDoc} */
//@Override
/*public*/  QString DefaultDigitalActionManager::getBeanTypeHandled(bool plural) const {
    return plural ? tr("Digital actions") : tr("Digital action");
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultDigitalActionManager::deleteDigitalAction(MaleDigitalActionSocket* x) {
    // delete the MaleDigitalActionSocket
    deregister(x);
    x->Base::dispose();
}

/*static*/ /*volatile*/ DefaultDigitalActionManager* DefaultDigitalActionManager::_instance = nullptr;

//@InvokeOnGuiThread  // this method is not thread safe
/*static*/ /*public*/  DefaultDigitalActionManager* DefaultDigitalActionManager::instance() {
    if (!ThreadingUtil::isGUIThread()) {
        LoggingUtil::warnOnce(log, "instance() called on wrong thread");
    }

    if (_instance == nullptr) {
        _instance = new DefaultDigitalActionManager();
    }
    return (_instance);
}

//@Override
/*public*/  /*Class<MaleDigitalActionSocket>*/QString DefaultDigitalActionManager::getNamedBeanClass() const {
    return "MaleDigitalActionSocket";
}

//@Override
/*protected*/ MaleDigitalActionSocket* DefaultDigitalActionManager::castBean(MaleSocket* maleSocket) {
    return (MaleDigitalActionSocket*)maleSocket->bself();
}


/*private*/ /*final*/ /*static*/ Logger* DefaultDigitalActionManager::log = LoggerFactory::getLogger("DefaultDigitalActionManager");
