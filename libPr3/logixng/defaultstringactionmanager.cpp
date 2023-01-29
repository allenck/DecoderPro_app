#include "defaultstringactionmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "stringactionbean.h"
#include "defaultmalestringactionsocket.h"
#include "defaultfemalestringactionsocket.h"
#include "actions/stringfactory.h"
#include "debuggermalestringactionsocketfactory.h"
#include "namedbean.h"
/**
 * Class providing the basic logic of the ActionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultStringActionManager extends AbstractBaseManager<MaleStringActionSocket>
//        implements StringActionManager {



    /*public*/  DefaultStringActionManager::DefaultStringActionManager(QObject* parent): AbstractBaseManager(parent) {
     setObjectName("DefaultStringActionManager");
     registerSelf();
     ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);


//        for (StringActionFactory actionFactory : ServiceLoader.load(StringActionFactory.class)) {
//            actionFactory.init();
//        }

//        for (Category category : Category.values()) {
//            actionClassList.put(category, new ArrayList<>());
//        }
        (new Actions::StringFactory())->init();

//        for (StringActionFactory actionFactory : ServiceLoader.load(StringActionFactory.class)) {
//            actionFactory.getClasses().forEach((entry) -> {
////                System.out.format("Add action: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                actionClassList.get(entry.getKey()).add(entry.getValue());
//            });
//        }
          QSet<QHash<Category, /*Class<? extends Base>*/QString>> classes = (new Actions::StringFactory())->getClasses();

//        for (MaleStringActionSocketFactory* maleSocketFactory : ServiceLoader.load(MaleStringActionSocketFactory.class)) {
//            _maleSocketFactories.add(maleSocketFactory);
//        }
          DebuggerMaleStringActionSocketFactory* maleSocketFactory = new DebuggerMaleStringActionSocketFactory();
          _maleSocketFactories.append(maleSocketFactory);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<? extends MaleSocket>*/QString DefaultStringActionManager::getMaleSocketClass() {
        return "DefaultMaleStringActionSocket";
    }

    /*protected*/ MaleStringActionSocket* DefaultStringActionManager::createMaleActionSocket(StringActionBean* action) {
        MaleStringActionSocket* socket = new DefaultMaleStringActionSocket(this, action);
        action->setParent(socket);
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultStringActionManager::getLastRegisteredMaleSocket() {
        return _lastRegisteredBean;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultStringActionManager::registerBean(/*MaleStringActionSocket*/MaleSocket* maleSocket) {
        MaleSocket* bean = AbstractBaseManager::registerBean(maleSocket);
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
    /*public*/  MaleStringActionSocket* DefaultStringActionManager::registerAction(/*@Nonnull*/ StringActionBean* action)
            /*throws IllegalArgumentException*/ {

        if (qobject_cast<MaleStringActionSocket*>(action->bself())) {
            throw new IllegalArgumentException("registerAction() cannot register a MaleStringActionSocket. Use the method register() instead.");
        }

        // Check if system name is valid
        QString sn = ((AbstractBase*)action->self())->AbstractNamedBean::getSystemName();
        if (this->validSystemNameFormat(((AbstractBase*)action->self())->AbstractNamedBean::getSystemName()) != NameValidity::VALID) {
            log->warn("SystemName " + ((AbstractBase*)action->self())->AbstractNamedBean::getSystemName() + " is not in the correct format");
            throw new IllegalArgumentException(tr("System name is invalid: %1").arg(((AbstractBase*)action->self())->AbstractNamedBean::getSystemName()));
        }

        // Keep track of the last created auto system name
        updateAutoNumber(((AbstractBase*)action->self())->AbstractNamedBean::getSystemName());

        MaleStringActionSocket* maleSocket = createMaleActionSocket(action);
        registerBean(maleSocket);
        return  maleSocket;
    }

    //@Override
    /*public*/  int DefaultStringActionManager::getXMLOrder() const {
        return LOGIXNG_STRING_ACTIONS;
    }

    //@Override
    /*public*/  QChar DefaultStringActionManager::typeLetter() const{
        return 'Q';
    }

    /*.*
     * Test if parameter is a properly formatted system name.
     *
     * @param systemName the system name
     * @return enum indicating current validity, which might be just as a prefix
     *./
    //@Override
    public  NameValidity validSystemNameFormat(String systemName) {
        return LogixNG_Manager.validSystemNameFormat(
                getSubSystemNamePrefix(), systemName);
    }
*/
    //@Override
    /*public*/  FemaleStringActionSocket* DefaultStringActionManager::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {
        return new DefaultFemaleStringActionSocket(parent, listener, socketName);
    }

    //@Override
    /*public*/  QHash<Category, QList<QString> > DefaultStringActionManager::getActionClasses() {
        return actionClassList;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultStringActionManager::getBeanTypeHandled(bool plural) const {
        return plural ? tr("StringActions") : tr("StringAction");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultStringActionManager::deleteStringAction(MaleStringActionSocket* x) {
        // delete the StringAction
        deregister(x);
        x->NamedBean::dispose();
    }

    /*static*/ /*volatile*/ DefaultStringActionManager* DefaultStringActionManager::_instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultStringActionManager* DefaultStringActionManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultStringActionManager();
        }
        return (_instance);
    }

    //@Override
    /*public*/  /*Class<MaleStringActionSocket>*/QString DefaultStringActionManager::getNamedBeanClass() const{
        return "MaleStringActionSocket";
    }

    //@Override
    /*protected*/ MaleStringActionSocket* DefaultStringActionManager::castBean(MaleSocket* maleSocket) {
        return (MaleStringActionSocket*)maleSocket->bself();
    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultStringActionManager::log = LoggerFactory::getLogger("DefaultStringActionManager");

