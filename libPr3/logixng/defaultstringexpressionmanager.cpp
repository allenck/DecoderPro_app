#include "defaultstringexpressionmanager.h"
#include "loggerfactory.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "stringfactory.h"
#include "debuggermalestringexpressionsocketfactory.h"
#include "defaultfemalestringexpressionsocket.h"
#include "defaultmalestringexpressionsocket.h"

/**
 * Class providing the basic logic of the ExpressionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultStringExpressionManager extends AbstractBaseManager<MaleStringExpressionSocket>
//        implements StringExpressionManager, InstanceManagerAutoDefault {


    /*public*/  DefaultStringExpressionManager::DefaultStringExpressionManager(QObject* parent) {
        setObjectName("DefaultStringExpressionManager");
        registerSelf();
        ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);

//        for (StringExpressionFactory expressionFactory : ServiceLoader.load(StringExpressionFactory.class)) {
//            expressionFactory.init();
//        }
          (new StringFactory())->init();

        for (Category* category : Category::values()) {
            expressionClassList.insert(category, QList<QString>());
        }


//        System.out.format("Read expressions%n");
//        for (StringExpressionFactory expressionFactory : ServiceLoader.load(StringExpressionFactory.class)) {
//            expressionFactory.getClasses().forEach((entry) -> {
////                System.out.format("Add expression: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                expressionClassList.get(entry.getKey()).add(entry.getValue());
//            });
//        }
        QSet<QHash<Category*, /*Class<? extends Base>*/QString>> classes =(new StringFactory())->getClasses();
        for(QHash<Category*, QString> map : classes)
        {
         QHashIterator<Category*, QString> entry(map);
         while(entry.hasNext())
         {
          entry.next();
          //expressionClassList.value(entry.key()).append(entry.value());
         }
        }

//        for (MaleStringExpressionSocketFactory maleSocketFactory : ServiceLoader.load(MaleStringExpressionSocketFactory.class)) {
//            _maleSocketFactories.add(maleSocketFactory);
//        }
        _maleSocketFactories.append((MaleSocketFactory*)new DebuggerMaleStringExpressionSocketFactory());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<? extends MaleSocket>*/QString DefaultStringExpressionManager::getMaleSocketClass() {
        return "DefaultMaleStringExpressionSocket";
    }

    /*protected*/ MaleStringExpressionSocket* DefaultStringExpressionManager::createMaleStringExpressionSocket(StringExpressionBean* expression) {
        MaleStringExpressionSocket* socket = new DefaultMaleStringExpressionSocket(this, expression);
        expression->setParent((Base*)socket->self());
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultStringExpressionManager::getLastRegisteredMaleSocket() {
        return _lastRegisteredBean;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DefaultStringExpressionManager::registerBean(/*MaleStringExpressionSocket*/MaleSocket* maleSocket) {
        MaleSocket* bean = AbstractBaseManager::registerBean(maleSocket);
        _lastRegisteredBean = (MaleSocket*)maleSocket;
        return bean;
    }

    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleActionSocket for the action.
     *
     * @param expression the bean
     */
    //@Override
    /*public*/  MaleStringExpressionSocket* DefaultStringExpressionManager::registerExpression(/*@Nonnull*/ StringExpressionBean* expression)
            /*throws IllegalArgumentException*/ {

        if(qobject_cast<MaleStringExpressionSocket*>(expression->bself())) {
            throw new IllegalArgumentException("registerExpression() cannot register a MaleStringExpressionSocket. Use the method register() instead.");
        }

        // Check if system name is valid
        if (this->validSystemNameFormat(((AbstractNamedBean*)expression->bself())->getSystemName()) != NameValidity::VALID) {
            log->warn("SystemName " + ((AbstractNamedBean*)expression->bself())->getSystemName() + " is not in the correct format");
            throw new IllegalArgumentException(tr("System name is invalid: %1").arg(((AbstractNamedBean*)expression->bself())->getSystemName()));
        }

        // Keep track of the last created auto system name
        updateAutoNumber(expression->NamedBean::getSystemName());

        // save in the maps
        MaleStringExpressionSocket* maleSocket = createMaleStringExpressionSocket(expression);
         registerBean(maleSocket);
         return maleSocket;
    }

    //@Override
    /*public*/  int DefaultStringExpressionManager::getXMLOrder()  const {
        return LOGIXNG_STRING_EXPRESSIONS;
    }

    //@Override
    /*public*/  QChar DefaultStringExpressionManager::typeLetter() const {
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
    /*public*/  FemaleStringExpressionSocket* DefaultStringExpressionManager::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {

        return new DefaultFemaleStringExpressionSocket(parent, listener, socketName);
    }

    //@Override
    /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> DefaultStringExpressionManager::getExpressionClasses() {
        return expressionClassList;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultStringExpressionManager::getBeanTypeHandled(bool plural)const {
        return plural ? tr("StringExpressions") : tr("StringExpression");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultStringExpressionManager::deleteStringExpression(MaleStringExpressionSocket* x) {
        // delete the MaleStringExpressionSocket
        deregister(x);
        x->NamedBean::dispose();
    }

    /*static*/ /*volatile*/ DefaultStringExpressionManager* DefaultStringExpressionManager::_instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultStringExpressionManager* DefaultStringExpressionManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultStringExpressionManager();
        }
        return (_instance);
    }

    //@Override
    /*public*/  /*Class<MaleStringExpressionSocket>*/QString DefaultStringExpressionManager::getNamedBeanClass() const {
        return "MaleStringExpressionSocket";
    }

    //@Override
    /*protected*/ MaleStringExpressionSocket* DefaultStringExpressionManager::castBean(MaleSocket* maleSocket) {
        return (MaleStringExpressionSocket*)maleSocket->bself();
    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultStringExpressionManager::log = LoggerFactory::getLogger("DefaultStringExpressionManager");
