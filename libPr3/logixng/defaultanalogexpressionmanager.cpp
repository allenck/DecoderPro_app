#include "defaultanalogexpressionmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"
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
#include "defaultmaleanalogexpressionsocket.h"
#include "class.h"
#include "exceptions.h"
#include "debuggermaleanalogexpressionsocketfactory.h"
#include "analogexpressionanalogio.h"
#include "analogfactory_expressions.h"

/**
 * Class providing the basic logic of the ExpressionManager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
///*public*/  class DefaultAnalogExpressionManager extends AbstractBaseManager<MaleAnalogExpressionSocket>
//        implements AnalogExpressionManager, InstanceManagerAutoDefault {


    /*public*/  DefaultAnalogExpressionManager::DefaultAnalogExpressionManager(QObject* parent)
      : AbstractBaseManager(parent) {
     setObjectName("DefaultAnalogExpressionManager");
     registerSelf();
        ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->registerManager(this);

        QList<AnalogExpressionFactory*> factories = {new AnalogFactory_Expressions()};

//        for (AnalogExpressionFactory* expressionFactory : /*ServiceLoader.load("AnalogExpressionFactory")*/aList) {
//            expressionFactory->init();
        foreach(AnalogExpressionFactory* factory, factories)
        {
         factory->init();
        }

        for (Category category : Category::values()) {
            expressionClassList.insert(category,  QList</*Class<? extends Base*/QString>());
        }
//        //        System.out.format("Read expressions%n");
//                for (AnalogExpressionFactory expressionFactory : ServiceLoader.load(AnalogExpressionFactory.class)) {
//                    expressionFactory.getClasses().forEach((entry) -> {
//        //                System.out.format("Add expression: %s, %s%n", entry.getKey().name(), entry.getValue().getName());
//                        expressionClassList.get(entry.getKey()).add(entry.getValue());
//                    });
//                }
        for (AnalogExpressionFactory* expressionFactory : factories)
        {
         QSet<QHash<Category, QString>> classes = expressionFactory->getClasses();
         for(QHash<Category, QString> map : classes )
         {
          QHashIterator<Category, QString> entry(map);
          while(entry.hasNext())
          {
           entry.next();
           QList<QString> temp = expressionClassList.value(entry.key());
           temp.append(entry.value());
           expressionClassList.insert(entry.key(), temp);
          }
         }
        }

//        for (MaleAnalogExpressionSocketFactory* maleSocketFactory : /*ServiceLoader.load(MaleAnalogExpressionSocketFactory.class)*/bList) {
//            _maleSocketFactories.append(maleSocketFactory);
//        }
        _maleSocketFactories.append(new DebuggerMaleAnalogExpressionSocketFactory());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*Class<? extends MaleSocket>*/QString DefaultAnalogExpressionManager::getMaleSocketClass() {
        return "DefaultMaleAnalogExpressionSocket";
    }

    /*protected*/ MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::createMaleAnalogExpressionSocket(AnalogExpressionBean* expression) {
        MaleAnalogExpressionSocket* socket = new DefaultMaleAnalogExpressionSocket(this, expression);
        expression->setParent((MaleAnalogExpressionSocket*)socket->bself());
        return socket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket*DefaultAnalogExpressionManager:: getLastRegisteredMaleSocket() {
        return _lastRegisteredBean;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket *DefaultAnalogExpressionManager::registerBean(/*MaleAnalogExpressionSocket*/MaleSocket* maleSocket) {
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
    /*public*/  MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::registerExpression(/*@Nonnull*/ AnalogExpressionBean* expression)
            /*throws IllegalArgumentException*/ {

        if (qobject_cast<MaleAnalogExpressionSocket*>(expression->bself())) {
            throw new IllegalArgumentException("registerExpression() cannot register a MaleAnalogExpressionSocket. Use the method register() instead.");
        }

        // Check if system name is valid
        if (this->validSystemNameFormat(((AbstractNamedBean*)expression->self())->getSystemName()) != NameValidity::VALID) {
            log->warn("SystemName " + ((AbstractNamedBean*)expression->self())->getSystemName() + " is not in the correct format");
            throw new IllegalArgumentException(QString("System name is invalid: %1").arg(((AbstractNamedBean*)expression->self())->getSystemName()));
        }

        // Keep track of the last created auto system name
        updateAutoNumber(((AbstractNamedBean*)expression->self())->getSystemName());

        // save in the maps
        MaleAnalogExpressionSocket* maleSocket = createMaleAnalogExpressionSocket(expression);
        /*return*/ registerBean(maleSocket);
        return maleSocket;
    }

    //@Override
    /*public*/  int DefaultAnalogExpressionManager::getXMLOrder() const {
        return LOGIXNG_ANALOG_EXPRESSIONS;
    }

    //@Override
    /*public*/  QString DefaultAnalogExpressionManager::getBeanTypeHandled()const {
        return tr("Analog expression");
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
        return DefaultLogixNGManager::ng_validSystemNameFormat(
                getSubSystemNamePrefix(), systemName);
    }

    //@Override
    /*public*/  FemaleAnalogExpressionSocket* DefaultAnalogExpressionManager::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {

        return new DefaultFemaleAnalogExpressionSocket(parent, listener, socketName);
    }

    //@Override
    /*public*/  QHash<Category, QList<QString> > DefaultAnalogExpressionManager::getExpressionClasses() {
        return expressionClassList;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DefaultAnalogExpressionManager::getBeanTypeHandled(bool plural)const {
        return tr(plural ? "Analog expressions" : "Analog expression");
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
    /*public*/  /*Class<MaleAnalogExpressionSocket>*/QString DefaultAnalogExpressionManager::getNamedBeanClass()const {
        return "MaleAnalogExpressionSocket";
    }

    //@Override
    /*protected*/ MaleAnalogExpressionSocket* DefaultAnalogExpressionManager::castBean(MaleSocket* maleSocket) {
        return (MaleAnalogExpressionSocket*)maleSocket->bself();
    }


/*public*/ QString DefaultAnalogExpressionManager::getAutoSystemName() {
    //int nextAutoBlockRef = lastAutoNamedBeanRef.fetchAndAddAcquire(1);//   .incrementAndGet();
    int nextAutoBlockRef = lastAutoNamedBeanRef++;
    QString b = QString(getSubSystemNamePrefix() + ":AUTO:");
    QString nextNumber = paddedNumber.format(nextAutoBlockRef);
    b.append(nextNumber);
    return b;
}

    /*private*/ /*final*/ /*static*/ Logger* DefaultAnalogExpressionManager::log = LoggerFactory::getLogger("DefaultAnalogExpressionManager");
