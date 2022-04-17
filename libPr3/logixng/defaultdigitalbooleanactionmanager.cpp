#include "defaultdigitalbooleanactionmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "defaultmaledigitalbooleanactionsocket.h"
#include "digitalbooleanactionfactory.h"
#include "defaultfemaledigitalbooleanactionsocket.h"
#include "digitalbooleanfactory.h"
#include "debuggermaledigitalbooleanactionsocketfactory.h"

/**
 * Class providing the basic logic of the DigitalBooleanActionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultDigitalBooleanActionManager extends AbstractBaseManager<MaleDigitalBooleanActionSocket>
//        implements DigitalBooleanActionManager {



    /*public*/  DefaultDigitalBooleanActionManager::DefaultDigitalBooleanActionManager(QObject *parent)
     : AbstractBaseManager(parent)
    {
     setObjectName("DefaultDigitalBooleanActionManager");
     registerSelf();

        ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);

//        for (DigitalBooleanActionFactory actionFactory : ServiceLoader.load(DigitalBooleanActionFactory.class)) {
//            actionFactory.init();
//        }
        (new DigitalBooleanFactory())->init();

        for (Category* category : Category::values()) {
            actionClassList.insert(category, QList<QString>());
        }

//        for (DigitalBooleanActionFactory actionFactory : ServiceLoader.load(DigitalBooleanActionFactory.class)) {
//            actionFactory.getClasses().forEach((entry) -> {
////                System.out.format("Add action: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                actionClassList.get(entry.getKey()).add(entry.getValue());
//            });
//        }
        //QSetIterator<QHash<Category*, QString>> entry((new DigitalBooleanFactory())->getClasses());
        for(QHash<Category*, QString> map : (new DigitalBooleanFactory())->getClasses())
        {
         QHashIterator<Category*, QString> entry(map);
         while(entry.hasNext())
         {
          entry.next();
          QList<QString> temp = actionClassList.value(entry.key());
          temp.append(entry.value());
          actionClassList.insert(entry.key(), temp);
         }
        }

//        for (MaleDigitalBooleanActionSocketFactory* maleSocketFactory : ServiceLoader.load(MaleDigitalBooleanActionSocketFactory.class)) {
//            _maleSocketFactories.add(maleSocketFactory);
//        }
        new DebuggerMaleDigitalBooleanActionSocketFactory();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<? extends MaleSocket>*/QString DefaultDigitalBooleanActionManager::getMaleSocketClass() {
        return "DefaultMaleDigitalBooleanActionSocket";
    }

    /*protected*/ MaleDigitalBooleanActionSocket* DefaultDigitalBooleanActionManager::createMaleActionSocket(DigitalBooleanActionBean* action) {
        MaleDigitalBooleanActionSocket* socket = new DefaultMaleDigitalBooleanActionSocket(this, action);
        action->setParent(socket);
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultDigitalBooleanActionManager::getLastRegisteredMaleSocket() {
        return _lastRegisteredBean;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultDigitalBooleanActionManager::registerBean(/*MaleDigitalBooleanActionSocket*/MaleSocket* maleSocket) {
        MaleSocket* bean = AbstractBaseManager::registerBean(maleSocket);
        _lastRegisteredBean = (MaleSocket*)maleSocket;
        return bean;
    }

    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleDigitalBooleanActionSocket for the action.
     *
     * @param action the bean
     */
    //@Override
    /*public*/  MaleDigitalBooleanActionSocket* DefaultDigitalBooleanActionManager::registerAction(/*@Nonnull*/ DigitalBooleanActionBean* action)
            /*throws IllegalArgumentException*/ {

        if (qobject_cast<MaleDigitalBooleanActionSocket*>(action->bself())) {
            throw new IllegalArgumentException("registerAction() cannot register a MaleDigitalBooleanActionSocket. Use the method register() instead.");
        }

        // Check if system name is valid
        if (this->validSystemNameFormat(((AbstractNamedBean*)action->self())->getSystemName()) != NameValidity::VALID) {
            log->warn("SystemName " + ((AbstractNamedBean*)action->self())->getSystemName() + " is not in the correct format");
            throw new IllegalArgumentException(tr("System name is invalid: %1").arg(((AbstractNamedBean*)action->self())->getSystemName()));
        }

        // Keep track of the last created auto system name
        updateAutoNumber(((AbstractNamedBean*)action->self())->getSystemName());

        // save in the maps
        MaleDigitalBooleanActionSocket* maleSocket = createMaleActionSocket(action);
         registerBean(maleSocket);
         return maleSocket;
    }

    //@Override
    /*public*/  int DefaultDigitalBooleanActionManager::getXMLOrder()  const{
        return LOGIXNG_DIGITAL_BOOLEAN_ACTIONS;
    }

    //@Override
    /*public*/  QChar DefaultDigitalBooleanActionManager::typeLetter() const{
        return 'Q';
    }

    /*.*
     * Test if parameter is a properly formatted system name.
     *
     * @param systemName the system name
     * @return enum indicating current validity, which might be just as a prefix
     *./
    //@Override
    public  NameValidity validSystemNameFormat(QString systemName) {
        return LogixNG_Manager.validSystemNameFormat(
                getSubSystemNamePrefix(), systemName);
    }
*/
    //@Override
    /*public*/  FemaleDigitalBooleanActionSocket* DefaultDigitalBooleanActionManager::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {
        return new DefaultFemaleDigitalBooleanActionSocket(parent, listener, socketName);
    }

    //@Override
    /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> DefaultDigitalBooleanActionManager::getActionClasses() {
        return actionClassList;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultDigitalBooleanActionManager::getBeanTypeHandled(bool plural) const {
        return plural ? tr("Digital bool actions") : tr("Digital bool action");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultDigitalBooleanActionManager::deleteDigitalBooleanAction(MaleDigitalBooleanActionSocket* x) {
        // delete the MaleDigitalBooleanActionSocket
        deregister(x);
        x->NamedBean::dispose();
    }

    /*static*/ /*volatile*/ DefaultDigitalBooleanActionManager* DefaultDigitalBooleanActionManager::_instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultDigitalBooleanActionManager* DefaultDigitalBooleanActionManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultDigitalBooleanActionManager();
        }
        return (_instance);
    }

    //@Override
    /*public*/  /*Class<MaleDigitalBooleanActionSocket>*/QString DefaultDigitalBooleanActionManager::getNamedBeanClass() const {
        return "MaleDigitalBooleanActionSocket";
    }

    //@Override
    /*protected*/ MaleDigitalBooleanActionSocket* DefaultDigitalBooleanActionManager::castBean(MaleSocket* maleSocket) {
        return (MaleDigitalBooleanActionSocket*)maleSocket->bself();
    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultDigitalBooleanActionManager::log = LoggerFactory::getLogger("DefaultDigitalBooleanActionManager");
