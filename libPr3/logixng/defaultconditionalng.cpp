#include "defaultconditionalng.h"
#include "logixng_thread.h"
#include "conditionalng_manager.h"
#include "instancemanager.h"
#include "defaultfemaledigitalactionsocket.h"
#include "defaultsymboltable.h"
#include  "abortconditionalngexecutionexception.h"
#include "loggerfactory.h"
#include "digitalactionmanager.h"
#include "runtimeexception.h"
#include  "defaultconditionalngmanager.h"
#include "defaultdigitalactionmanager.h"
#include "abstractmalesocket.h"

/**
 * The default implementation of ConditionalNG.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class DefaultConditionalNG extends AbstractBase
//        implements ConditionalNG, FemaleSocketListener {



    /*public*/  DefaultConditionalNG::DefaultConditionalNG(QString sys, QString user, QObject *parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractBase(sys, user, parent) {
        common(sys, user, LogixNG_Thread::DEFAULT_LOGIXNG_THREAD);
    }

    /*public*/  DefaultConditionalNG::DefaultConditionalNG(QString sys, QString user, int threadID, QObject *parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractBase(sys, user, parent) {
        //super(sys, user);
     common(sys, user, threadID);

    }

    void DefaultConditionalNG::common(QString sys, QString user, int threadID)
    {
     setObjectName("DefaultConditionalNG");
        _startupThreadId = threadID;
        _thread = LogixNG_Thread::getThread(threadID);
        _thread->setThreadInUse();

        // Do this test here to ensure all the tests are using correct system names
        Manager::NameValidity isNameValid = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->validSystemNameFormat(mSystemName);
        if (isNameValid != Manager::NameValidity::VALID) {
            throw new IllegalArgumentException("system name is not valid");
        }
        _femaleSocket = new DefaultFemaleDigitalActionSocket((ConditionalNG*)this, this, "A");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  LogixNG_Thread* DefaultConditionalNG::getCurrentThread() {
        return _thread;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int DefaultConditionalNG::getStartupThreadId() {
        return _startupThreadId;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::setStartupThreadId(int threadId) {
        int oldStartupThreadId = _startupThreadId;
        _startupThreadId = threadId;
        firePropertyChange("Thread", oldStartupThreadId, _startupThreadId);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Base* DefaultConditionalNG::getParent() const{
        return _parent;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::setParent(Base* parent) {
        _parent = parent;

        if (AbstractBase::isActive()) AbstractBase::registerListeners();
        else AbstractBase::unregisterListeners();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleDigitalActionSocket* DefaultConditionalNG::getFemaleSocket() {
        return _femaleSocket;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::setRunDelayed(bool value) {
        _runDelayed = value;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultConditionalNG::getRunDelayed() {
        return _runDelayed;
    }

    /*private*/ void DefaultConditionalNG::runOnLogixNG_Thread(
            /*@Nonnull*/ ThreadAction* ta,
            bool allowRunDelayed) {

        if (_runDelayed && allowRunDelayed) {
            _thread->runOnLogixNGEventually(ta);
        } else {
            _thread->runOnLogixNG(ta);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::execute() {
        if (_executeLock->once()) {
            runOnLogixNG_Thread(new ExecuteTask(this, _executeLock, nullptr, this), true);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::execute(bool allowRunDelayed) {
        if (_executeLock->once()) {
            runOnLogixNG_Thread(new ExecuteTask(this, _executeLock, nullptr,this), allowRunDelayed);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::execute(FemaleDigitalActionSocket* socket) {
        //runOnLogixNG_Thread(() -> {internalExecute(this, socket);}, true);
     runOnLogixNG_Thread(new DCThreadAction(socket, this),true);
    }

    /*private*/ /*static*/ void DefaultConditionalNG::internalExecute(ConditionalNG* conditionalNG, FemaleDigitalActionSocket* femaleSocket) {
        if (conditionalNG->isEnabled()) {
            DefaultSymbolTable* newSymbolTable = new DefaultSymbolTable(conditionalNG);

            try {
                conditionalNG->setSymbolTable(newSymbolTable);
                if (femaleSocket != nullptr) {
                    femaleSocket->execute();
                } else {
                    conditionalNG->getFemaleSocket()->execute();
                }
            } catch (AbortConditionalNGExecutionException* e) {
//                LoggingUtil.warnOnce(log, "ConditionalNG {} got an exception during execute: {}",
//                        conditionalNG.getSystemName(), e, e);
                log->warn(tr("ConditionalNG %1 was aborted during execute: %2").arg(
                        conditionalNG->NamedBean::getSystemName(), e->getCause()->getMessage())/*, e*/);
            } catch (JmriException* e) {
//                LoggingUtil.warnOnce(log, "ConditionalNG {} got an exception during execute: {}",
//                        conditionalNG.getSystemName(), e, e);
                log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
                        conditionalNG->NamedBean::getSystemName(), e->getMessage()), e);
            }
            catch (RuntimeException* e) {
//                LoggingUtil.warnOnce(log, "ConditionalNG {} got an exception during execute: {}",
//                        conditionalNG.getSystemName(), e, e);
                log->warn(tr("ConditionalNG %1 got an exception during execute: %2").arg(
                        conditionalNG->NamedBean::getSystemName(), e->getMessage()), e);
            }
            conditionalNG->setSymbolTable(newSymbolTable->getPrevSymbolTable());
        }
    }

//    /*private*/ static class ExecuteTask implements ThreadingUtil.ThreadAction {

//        /*private*/ /*final*/ ConditionalNG _conditionalNG;
//        /*private*/ /*final*/ ExecuteLock _executeLock;
//        /*private*/ /*final*/ FemaleDigitalActionSocket _localFemaleSocket;

//        /*public*/  ExecuteTask(ConditionalNG conditionalNG, ExecuteLock executeLock, FemaleDigitalActionSocket femaleSocket) {
//            _conditionalNG = conditionalNG;
//            _executeLock = executeLock;
//            _localFemaleSocket = femaleSocket;
//        }

//        //@Override
//        /*public*/  void run() {
//            while (_executeLock.loop()) {
//                internalExecute(_conditionalNG, _localFemaleSocket);
//            }
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Stack* DefaultConditionalNG::getStack() {
        return _stack;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  SymbolTable* DefaultConditionalNG::getSymbolTable() {
        return _symbolTable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::setSymbolTable(SymbolTable* symbolTable) {
        _symbolTable = symbolTable;
    }

    //@Override
    /*public*/  QString DefaultConditionalNG::getBeanType() {
        return tr("ConditionalNG");
    }

    //@Override
    /*public*/  void DefaultConditionalNG::setState(int s) /*throws JmriException */{
        log->warn(tr("Unexpected call to setState in DefaultConditionalNG."));  // NOI18N
    }

    //@Override
    /*public*/  int DefaultConditionalNG::getState() {
        log->warn("Unexpected call to getState in DefaultConditionalNG.");  // NOI18N
        return UNKNOWN;
    }

    //@Override
    /*public*/  void DefaultConditionalNG::connected(FemaleSocket* socket) {
     MaleSocket* connectedSocket = socket->getConnectedSocket();
     QString name = connectedSocket->getSystemName();
       //_socketSystemName = socket->getConnectedSocket()->getSystemName();
     _socketSystemName = name;
    }

    //@Override
    /*public*/  void DefaultConditionalNG::disconnected(FemaleSocket* socket) {
        _socketSystemName = nullptr;
    }

    //@Override
    /*public*/  QString DefaultConditionalNG::getShortDescription(QLocale locale) {
        return "ConditionalNG: "+AbstractNamedBean::getDisplayName();
    }

    //@Override
    /*public*/  QString DefaultConditionalNG::getLongDescription(QLocale locale) {
        if (_thread->getThreadId() != LogixNG_Thread::DEFAULT_LOGIXNG_THREAD) {
            return "ConditionalNG: "+AbstractNamedBean::getDisplayName() + " on thread " + _thread->getThreadName();
        }
        return "ConditionalNG: "+AbstractNamedBean::getDisplayName();
    }

    //@Override
    /*public*/  FemaleSocket* DefaultConditionalNG::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        if (index != 0) {
            throw new IllegalArgumentException(
                    tr("index has invalid value: %1").arg(index));
        }

        return _femaleSocket;
    }

    //@Override
    /*public*/  int DefaultConditionalNG::getChildCount() {
        return 1;
    }

    //@Override
    /*public*/  Category* DefaultConditionalNG::getCategory() {
        throw new UnsupportedOperationException("Not supported.");
    }

    /*public*/  void DefaultConditionalNG::setSocketSystemName(QString systemName) {
        if ((systemName == "") || (systemName !=(_socketSystemName))) {
            _femaleSocket->_disconnect();
        }
        _socketSystemName = systemName;
    }

    /*public*/  QString DefaultConditionalNG::getSocketSystemName() {
        return _socketSystemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*final*/ /*public*/  void DefaultConditionalNG::setup() {
        if (!_femaleSocket->isConnected()
                || _femaleSocket->getConnectedSocket()->getSystemName()
                        != (_socketSystemName)) {

            _femaleSocket->_disconnect();

            if (_socketSystemName != nullptr) {
                try {
                    MaleSocket* maleSocket = (MaleSocket*)
                            ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                    ->getBySystemName(_socketSystemName);
                    if (maleSocket != nullptr) {
                        _femaleSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("digital action is not found: " + _socketSystemName);
                    }
                } catch (SocketAlreadyConnectedException* ex) {
                    // This shouldn't happen and is a runtime error if it does.
                    throw new RuntimeException("socket is already connected");
                }
            }
        } else {
            _femaleSocket->FemaleSocket::setup();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*final*/ /*public*/  void DefaultConditionalNG::disposeMe() {
        _femaleSocket->FemaleSocket::dispose();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::setEnabled(bool enable) {
        _enabled = enable;
        if (AbstractBase::isActive()) {
            LogixNG* logixNG = AbstractBase::getLogixNG();
            if ((logixNG != nullptr) && logixNG->isActive()) {
                AbstractBase::registerListeners();
                execute();
            }
        } else {
            AbstractBase::unregisterListeners();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DefaultConditionalNG::isEnabled() {
        return _enabled;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::registerListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DefaultConditionalNG::unregisterListenersForThisClass() {
        // Do nothing
    }

    //@Override
    /*public*/  Base* DefaultConditionalNG::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultConditionalNG::log = LoggerFactory::getLogger("DefaultConditionalNG");
