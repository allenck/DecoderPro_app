#include "defaultdigitalexpressionmanager.h"
#include "loggerfactory.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "digitalfactory.h"
#include "expressionfactory.h"
#include "maledigitalexpressionsocket.h"
#include "defaultmaledigitalexpressionsocket.h"
#include "defaultfemaledigitalexpressionsocket.h"
#include "defaultdigitalexpressionmanager.h"
#include "debuggermaledigitalexpressionsocketfactory.h"

/**
 * Class providing the basic logic of the DigitalExpressionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultDigitalExpressionManager extends AbstractBaseManager<MaleDigitalExpressionSocket>
//        implements DigitalExpressionManager, InstanceManagerAutoDefault {



    /*public*/  DefaultDigitalExpressionManager::DefaultDigitalExpressionManager(QObject *parent) : AbstractBaseManager(parent){
        ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);

//        for (DigitalExpressionFactory expressionFactory : ServiceLoader.load(DigitalExpressionFactory.class)) {
//            expressionFactory.init();
//        }
          (new DigitalFactory())->init();
          (new ExpressionFactory())->init();
        for (Category* category : Category::values()) {
            expressionClassList.insert(category, QList<QString>());
        }

//        System.out.format("Read expressions%n");
//        for (DigitalExpressionFactory expressionFactory : ServiceLoader.load(DigitalExpressionFactory.class)) {
//            expressionFactory.getExpressionClasses().forEach((entry) -> {
////                System.out.format("Add expression: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                expressionClassList.get(entry.getKey()).add(entry.getValue());
//            });
//        }
#if 0 // TODO:
        // for DigitalFactory
        //QSetIterator<QMap<Category*, QString>> map((new DigitalFactory())->getExpressionClasses());
        foreach(QMap<Category* QString> map, (new DigitalFactory())->getExpressionClasses());
        QMapIterator<Category*, QString> entry(map);
        while(entry.hasNext())
        {
         entry.next();
           expressionClassList.value(entry.key()).append(entry.value());
        }
#endif
//        for (MaleDigitalExpressionSocketFactory* maleSocketFactory : ServiceLoader.load(MaleDigitalExpressionSocketFactory.class)) {
//            _maleSocketFactories.add(maleSocketFactory);
//        }
        DebuggerMaleDigitalExpressionSocketFactory();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<? extends MaleSocket>*/QString  DefaultDigitalExpressionManager::getMaleSocketClass() {
        return "DefaultMaleDigitalExpressionSocket";
    }

    /*protected*/ MaleDigitalExpressionSocket*  DefaultDigitalExpressionManager::createMaleExpressionSocket(DigitalExpressionBean* expression) {
        MaleDigitalExpressionSocket* socket = new DefaultMaleDigitalExpressionSocket(this, expression);
        expression->setParent(socket);
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket*  DefaultDigitalExpressionManager::getLastRegisteredMaleSocket() {
        return _lastRegisteredBean;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleDigitalExpressionSocket*  DefaultDigitalExpressionManager::registerBean(/*MaleDigitalExpressionSocket*/NamedBean* maleSocket) {
        MaleDigitalExpressionSocket* bean = (MaleDigitalExpressionSocket*)AbstractBaseManager::registerBean(maleSocket);
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
    /*public*/  MaleDigitalExpressionSocket*  DefaultDigitalExpressionManager::registerExpression(/*@Nonnull*/DigitalExpressionBean* expression)
            /*throws IllegalArgumentException */{

        if (qobject_cast<MaleDigitalExpressionSocket*>(expression->bself())) {
            throw new IllegalArgumentException("registerExpression() cannot register a MaleDigitalExpressionSocket. Use the method register() instead.");
        }

        // Check if system name is valid
        if (this->validSystemNameFormat(expression->NamedBean::getSystemName()) != NameValidity::VALID) {
            log->warn("SystemName " + expression->NamedBean::getSystemName() + " is not in the correct format");
            throw new IllegalArgumentException("System name is invalid: "+expression->NamedBean::getSystemName());
        }

        // Keep track of the last created auto system name
        updateAutoNumber(expression->NamedBean::getSystemName());

        // save in the maps
        MaleDigitalExpressionSocket* maleSocket = createMaleExpressionSocket(expression);
        return registerBean(maleSocket);
    }

    //@Override
    /*public*/  int  DefaultDigitalExpressionManager::getXMLOrder() const {
        return LOGIXNG_DIGITAL_EXPRESSIONS;
    }

    //@Override
    /*public*/  QChar  DefaultDigitalExpressionManager::typeLetter() const {
        return 'Q';
    }

    /*.*
     * Test if parameter is a properly formatted system name.
     *
     * @param systemName the system name
     * @return enum indicating current validity, which might be just as a prefix
     *./
    //@Override
    public  Manager::NameValidity validSystemNameFormat(QString systemName) {
        return LogixNG_Manager::validSystemNameFormat(
                getSubSystemNamePrefix(), systemName);
    }
*/
    //@Override
    /*public*/  FemaleDigitalExpressionSocket*  DefaultDigitalExpressionManager::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {

        return new DefaultFemaleDigitalExpressionSocket(parent, listener, socketName);
    }

    //@Override
    /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>>  DefaultDigitalExpressionManager::getExpressionClasses() {
        return expressionClassList;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString  DefaultDigitalExpressionManager::getBeanTypeHandled(bool plural) const {
        return plural ? tr("DigitalExpressions") : tr("DigitalExpression");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void  DefaultDigitalExpressionManager::deleteDigitalExpression(MaleDigitalExpressionSocket* x) {
        // delete the MaleDigitalExpressionSocket
        deregister(x);
        x->NamedBean::dispose();
    }

    /*static*/ /*volatile*/ DefaultDigitalExpressionManager* DefaultDigitalExpressionManager::_instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultDigitalExpressionManager*  DefaultDigitalExpressionManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultDigitalExpressionManager();
        }
        return (_instance);
    }

    //@Override
    /*public*/  /*Class<MaleDigitalExpressionSocket>*/QString  DefaultDigitalExpressionManager::getNamedBeanClass() const{
        return "MaleDigitalExpressionSocket";
    }

    //@Override
    /*protected*/ MaleDigitalExpressionSocket* DefaultDigitalExpressionManager::castBean(MaleSocket* maleSocket) {
        return (MaleDigitalExpressionSocket*)maleSocket->bself();
    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultDigitalExpressionManager::log = LoggerFactory::getLogger("DefaultDigitalExpressionManager");
