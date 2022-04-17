#include "defaultanalogactionmanager.h"
#include "loggerfactory.h"
#include "loggingutil.h"
#include "threadingutil.h"
#include "defaultlogixngmanager.h"
#include "instancemanager.h"
#include "defaultmaleanalogactionsocket.h"
#include "defaultfemaleanalogactionsocket.h"
#include "defaultanalogactionmanager.h"
#include "analogfactory.h"
#include "defaultanalogactionmanager.h"
#include "debuggermaleanalogactionsocketfactory.h"

/**
 * Class providing the basic logic of the ActionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultAnalogActionManager extends AbstractBaseManager<MaleAnalogActionSocket>
//        implements AnalogActionManager {



/*public*/  DefaultAnalogActionManager::DefaultAnalogActionManager(QObject* parent)
   : AbstractBaseManager(parent) {
    setObjectName("DefaultAnalogActionManager");
    ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);
    registerSelf();

//        for (AnalogActionFactory actionFactory : ServiceLoader.load(AnalogActionFactory.class)) {
//            actionFactory.init();
//        }
      (new AnalogFactory())->init();

    for (Category* category : Category::values()) {
        actionClassList.insert(category, QList<QString>());
    }

//        for (AnalogActionFactory actionFactory : ServiceLoader.load(AnalogActionFactory.class)) {
//            actionFactory.getClasses().forEach((entry) -> {
////                System.out.format("Add action: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                actionClassList.get(entry.getKey()).add(entry.getValue());
//            });
//        }
// TODO:        (new AnalogFactory())->
      AnalogFactory* actionFactory = new AnalogFactory();
      QSet<QHash<Category*, /*Class<? extends Base>*/QString> > set = actionFactory->getClasses();
      for(QHash<Category*, QString> map : set)
      {
       QHashIterator<Category*, QString> entry(map);
       while (entry.hasNext())
       {
        entry.next();
        //actionClassList.value(entry.key()).append(entry.value());
        QList<QString>  list = actionClassList.value(entry.key());
        list.append(entry.value());
        actionClassList.insert(entry.key(), list);
       }
      }
//        for (MaleAnalogActionSocketFactory* maleSocketFactory : ServiceLoader.load(MaleAnalogActionSocketFactory.class)) {
//            _maleSocketFactories.add(maleSocketFactory);
//        }
// TODO:       _maleSocketFactories.append(new DefaultAnalogActionManager());
           _maleSocketFactories.append(new DebuggerMaleAnalogActionSocketFactory());
}

/** {@inheritDoc} */
//@Override
/*public*/  /*Class<? extends MaleSocket>*/QString DefaultAnalogActionManager::getMaleSocketClass() {
    return "DefaultMaleAnalogActionSocket";
}

/*protected*/ MaleAnalogActionSocket* DefaultAnalogActionManager::createMaleActionSocket(AnalogActionBean* action) {
    MaleAnalogActionSocket* socket = new DefaultMaleAnalogActionSocket(this, action);
    action->setParent(socket);
    return socket;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* DefaultAnalogActionManager::getLastRegisteredMaleSocket() {
    return _lastRegisteredBean;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket *DefaultAnalogActionManager::registerBean(MaleSocket *maleSocket) {
     MaleSocket* bean = AbstractBaseManager::registerBean(maleSocket);
    QString sys = bean->Base::getSystemName();
     _lastRegisteredBean = (MaleSocket*)maleSocket;
    return bean;
}

/**
 * Remember a NamedBean Object created outside the manager.
 * This method creates a MaleActionSocket for the action.
 *
 * @param action the bean
 */
//@Override
/*public*/  MaleAnalogActionSocket* DefaultAnalogActionManager::registerAction(/*@Nonnull*/ AnalogActionBean* action)
        /*throws IllegalArgumentException*/ {

    if (qobject_cast<MaleAnalogActionSocket*>(action->bself())) {
        throw new IllegalArgumentException("registerAction() cannot register a MaleAnalogActionSocket. Use the method register() instead.");
    }

    // Check if system name is valid
    if (this->validSystemNameFormat(((AbstractNamedBean*)action->bself())->getSystemName()) != NameValidity::VALID) {
        log->warn("SystemName " + ((AbstractNamedBean*)action->bself())->getSystemName() + " is not in the correct format");
        throw new IllegalArgumentException(tr("System name is invalid: %1").arg(action->NamedBean::getSystemName()));
    }

    // Keep track of the last created auto system name
    updateAutoNumber(action->NamedBean::getSystemName());

    MaleAnalogActionSocket* maleSocket = createMaleActionSocket(action);
    AbstractNamedBean* nb = (AbstractNamedBean*)action->self();
    QString sys = nb->getSystemName();
    sys = maleSocket->getObject()->getSystemName();
    registerBean(maleSocket);
    return maleSocket;
}

//@Override
/*public*/  int DefaultAnalogActionManager::getXMLOrder() const {
    return LOGIXNG_ANALOG_ACTIONS;
}

//@Override
/*public*/  QString DefaultAnalogActionManager::getBeanTypeHandled() const {
    return tr("AnalogAction");
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultAnalogActionManager::deleteAnalogAction(MaleAnalogActionSocket* x) {
    // delete the MaleAnalogActionSocket
    deregister((AbstractNamedBean*)x->bself());
    x->NamedBean::dispose();
}

//@Override
/*public*/  QChar DefaultAnalogActionManager::typeLetter() const{
    return 'Q';
}

/*.*
 * Test if parameter is a properly formatted system name.
 *
 * @param systemName the system name
 * @return enum indicating current validity, which might be just as a prefix
 **/
//@Override
//    /*public*/  Manager::NameValidity DefaultAnalogActionManager::validSystemNameFormat(QString systemName) {
//        return LogixNG_Manager::validSystemNameFormat(
//                getSubSystemNamePrefix(), systemName);
//    }

//@Override
/*public*/  FemaleAnalogActionSocket* DefaultAnalogActionManager::createFemaleSocket(
        Base* parent, FemaleSocketListener* listener, QString socketName) {
    return new DefaultFemaleAnalogActionSocket(parent, listener, socketName);
}

//@Override
/*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> DefaultAnalogActionManager::getActionClasses() {
    return actionClassList;
}

/** {@inheritDoc} */
//@Override
/*public*/  QString DefaultAnalogActionManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "AnalogActions" : "AnalogAction");
}

/*static*/ /*volatile*/ DefaultAnalogActionManager* DefaultAnalogActionManager::_instance = nullptr;

//@InvokeOnGuiThread  // this method is not thread safe
/*static*/ /*public*/  DefaultAnalogActionManager* DefaultAnalogActionManager::instance() {
    if (!ThreadingUtil::isGUIThread()) {
        LoggingUtil::warnOnce(log, "instance() called on wrong thread");
    }

    if (_instance == nullptr) {
        _instance = new DefaultAnalogActionManager();
    }
    return (_instance);
}

//@Override
/*public*/  /*Class<MaleAnalogActionSocket>*/QString DefaultAnalogActionManager::getNamedBeanClass() const {
    return "MaleAnalogActionSocket";
}

//@Override
/*protected*/ MaleAnalogActionSocket* DefaultAnalogActionManager::castBean(MaleSocket* maleSocket) {
    return (MaleAnalogActionSocket*)maleSocket->bself();
}


/*private*/ /*final*/ /*static*/ Logger* DefaultAnalogActionManager::log = LoggerFactory::getLogger("DefaultAnalogActionManager");
