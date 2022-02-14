#include "defaultanalogexpressionmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "maleanalogexpressionsocket.h"
#include "loggingutil.h"
#include "threadingutil.h"
#include "defaultanalogexpressionmanager.h"
#include "analogexpressionanalogio.h"
#include "analogexpressionconstant.h"
#include "analogformula.h"
#include "analogexpressionfactory.h"
#include "category.h"
#include "defaultfemaleanalogexpressionsocketfactory.h"
#include "maleanalogexpressionsocketfactory.h"
#include "defaultfemaleanalogexpressionsocket.h"

/**
 * Class providing the basic logic of the ExpressionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultAnalogExpressionManager extends AbstractBaseManager<MaleAnalogExpressionSocket>
//        implements AnalogExpressionManager, InstanceManagerAutoDefault {


    /*public*/  DefaultAnalogExpressionManager::DefaultAnalogExpressionManager(QObject* parent) : AbstractBaseManager(parent) {
        ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);

        aList = {"AnalogExpressionAnalogIO",
           "AnalogExpressionConstant",
           "AnalogExpressionMemory",
           "AnalogFormula",
           "TimeSinceMidnight"};

        for (AnalogExpressionFactory* expressionFactory : /*ServiceLoader.load("AnalogExpressionFactory")*/aList) {
            expressionFactory->init();
        }

        for (Category::TYPE category : Category::values()) {
            expressionClassList.insert(category, QList</*Class<? extends Base*/Base*>());
        }

//        System.out.format("Read expressions%n");
        for (AnalogExpressionFactory* expressionFactory : /*ServiceLoader.load(AnalogExpressionFactory.class)*/aList) {
            //expressionFactory.getClasses().forEach((entry) ->
             QMapIterator<Category*, QList<Base*> > entry(expressionFactory->getClasses());
            while(entry.hasNext()
)            {
              entry.next();
//                System.out.format("Add expression: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
              expressionClassList.value(entry.key()).append(entry.value());
            }//);
        }

        bList = {new MaleAnalogExpressionSocketFactory()};
        for (MaleAnalogExpressionSocketFactory* maleSocketFactory : /*ServiceLoader.load(MaleAnalogExpressionSocketFactory.class)*/bList) {
            _maleSocketFactories.>append(maleSocketFactory);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<? extends MaleSocket>*/QString DefaultAnalogExpressionManager::getMaleSocketClass() {
        return "DefaultMaleAnalogExpressionSocket";
    }

    /*protected*/ MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::createMaleAnalogExpressionSocket(AnalogExpressionBean* expression) {
        MaleAnalogExpressionSocket* socket = new DefaultMaleAnalogExpressionSocket(this, expression);
        expression->setParent((MaleAnalogExpressionSocket*)socket->self());
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket*DefaultAnalogExpressionManager:: getLastRegisteredMaleSocket() {
        return _lastRegisteredBean;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::registerBean(MaleAnalogExpressionSocket* maleSocket) {
        MaleAnalogExpressionSocket* bean = (MaleAnalogExpressionSocket*)AbstractBaseManager::registerBean(maleSocket);
        _lastRegisteredBean = maleSocket;
        return bean;
    }

    /**
     * Remember a NamedBean Object created outside the manager.
     * This method creates a MaleActionSocket for the action.
     *
     * @param expression the bean
     */
    //@Override
    /*public*/  MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::registerExpression(/*@Nonnull*/ AnalogExpressionBean* expression)
            /*throws IllegalArgumentException*/ {

        if (qobject_cast<MaleAnalogExpressionSocket*>(expression->Base::self())) {
            throw new IllegalArgumentException("registerExpression() cannot register a MaleAnalogExpressionSocket. Use the method register() instead.");
        }

        // Check if system name is valid
        if (this->validSystemNameFormat(expression->NamedBean::getSystemName()) != NameValidity::VALID) {
            log->warn("SystemName " + expression->NamedBean::getSystemName() + " is not in the correct format");
            throw new IllegalArgumentException(QString("System name is invalid: %1").arg(expression->NamedBean::getSystemName()));
        }

        // Keep track of the last created auto system name
        updateAutoNumber(expression->NamedBean::getSystemName());

        // save in the maps
        MaleAnalogExpressionSocket* maleSocket = createMaleAnalogExpressionSocket(expression);
        return registerBean(maleSocket);
    }

    //@Override
    /*public*/  int DefaultAnalogExpressionManager::getXMLOrder() const {
        return LOGIXNG_ANALOG_EXPRESSIONS;
    }

    //@Override
    /*public*/  QString DefaultAnalogExpressionManager::getBeanTypeHandled()const {
        return tr("AnalogExpression");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultAnalogExpressionManager::deleteAnalogExpression(MaleAnalogExpressionSocket* x) {
        // delete the MaleAnalogExpressionSocket
        deregister(x);
        x->NamedBean::dispose();
    }

    //@Override
    /*public*/  QChar DefaultAnalogExpressionManager::typeLetter() const {
        return 'Q';
    }

    /***
     * Test if parameter is a properly formatted system name.
     *
     * @param systemName the system name
     * @return enum indicating current validity, which might be just as a prefix
     **/
    //@Override
    /*public*/  Manager::NameValidity DefaultAnalogExpressionManager::validSystemNameFormat(QString systemName) {
        return LogixNG_Manager::validSystemNameFormat(
                AbstractBaseManager::getSubSystemNamePrefix(), systemName);
    }

    //@Override
    /*public*/  FemaleAnalogExpressionSocket* DefaultAnalogExpressionManager::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {

        return new DefaultFemaleAnalogExpressionSocket(parent, listener, socketName);
    }

    //@Override
    /*public*/  QMap<Category*, QList</*Class<? extends Base>*/Base*>> DefaultAnalogExpressionManager::getExpressionClasses() {
        return expressionClassList;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultAnalogExpressionManager::getBeanTypeHandled(bool plural) {
        return tr(plural ? "AnalogExpressions" : "AnalogExpression");
    }

    /*static*/ /*volatile*/ DefaultAnalogExpressionManager* DefaultAnalogExpressionManager::_instance = nullptr;

    //@InvokeOnGuiThread  // this method is not thread safe
    /*static*/ /*public*/  DefaultAnalogExpressionManager* DefaultAnalogExpressionManager::instance() {
        if (!ThreadingUtil::isGUIThread()) {
            LoggingUtil::warnOnce(log, "instance() called on wrong thread");
        }

        if (_instance == nullptr) {
            _instance = new DefaultAnalogExpressionManager();
        }
        return (_instance);
    }

    //@Override
    /*public*/  /*Class<MaleAnalogExpressionSocket>*/QString getNamedBeanClass() {
        return "MaleAnalogExpressionSocket";
    }

    //@Override
    /*protected*/ MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::castBean(MaleSocket* maleSocket) {
        return (MaleAnalogExpressionSocket*)maleSocket;
    }


    /*private*/ /*final*/ /*static*/ Logger* DefaultAnalogExpressionManager::log = LoggerFactory::getLogger("DefaultAnalogExpressionManager");
