#include "defaultmodule.h"
#include "loggerfactory.h"
#include "femalesocket.h"
#include "loggerfactory.h"
#include "modulemanager.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "defaultsymboltable.h"
#include "defaultmodulemanager.h"
#include "basemanager.h"

/**
 * The default implementation of Module.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class DefaultModule extends AbstractBase
//        implements Module, FemaleSocketListener {




/*public*/  DefaultModule::DefaultModule(QString sys, QString user, FemaleSocketManager::SocketType* socketType, QObject *parent)
        /*throws BadUserNameException, BadSystemNameException*/ : AbstractBase(sys, user, parent) {

    //super(sys, user);

    _rootSocketType = socketType;
    _femaleRootSocket = socketType->createSocket((AbstractBase*)this, (FemaleSocketListener*)this, "Root");

    // Listeners should never be enabled for a module
    _femaleRootSocket->setEnableListeners(false);

    // Do this test here to ensure all the tests are using correct system names
    Manager::NameValidity isNameValid = ((DefaultModuleManager*)InstanceManager::getDefault("ModuleManager"))->validSystemNameFormat(mSystemName);
    if (isNameValid != Manager::NameValidity::VALID) {
        throw new IllegalArgumentException("system name is not valid");
    }
}

//@Override
/*public*/  void DefaultModule::setCurrentConditionalNG(ConditionalNG* conditionalNG) {
    /*synchronized(this)*/ {
        _currentConditionalNG.insert(QThread::currentThread(), conditionalNG);
    }
}

//@Override
/*public*/  ConditionalNG* DefaultModule::getConditionalNG() {
    /*synchronized(this)*/ {
        return _currentConditionalNG.value(QThread::currentThread());
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Base* DefaultModule::getParent() const{
    return nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultModule::setParent(Base* parent) {
    throw new UnsupportedOperationException("A Module cannot have a parent");
}

//@Override
/*public*/  QString DefaultModule::getBeanType() {
    return tr("Module");
}

//@Override
/*public*/  void DefaultModule::setState(int s) /*throws JmriException*/ {
    log->warn("Unexpected call to setState in DefaultModule.");  // NOI18N
}

//@Override
/*public*/  int DefaultModule::getState() {
    log->warn("Unexpected call to getState in DefaultModule.");  // NOI18N
    return UNKNOWN;
}

//@Override
/*public*/  QString DefaultModule::getShortDescription(QLocale locale) {
    return tr("Module");
}

//@Override
/*public*/  QString DefaultModule::getLongDescription(QLocale locale) {
    QString sb = tr("Module: %1").arg(AbstractNamedBean::getDisplayName());
    if (! _parameters.isEmpty()) {
        QList<QString> inParams = QList<QString>();
        QList<QString> outParams = QList<QString>();
        QList<QString> inOutParams = QList<QString>();

        for (Parameter* p : _parameters) {
            if (p->isInput() && p->isOutput()) inOutParams.append(p->getName());
            else if (p->isInput()) inParams.append(p->getName());
            else if (p->isOutput()) outParams.append(p->getName());
            else throw new RuntimeException("Parameter "+p->getName()+" is neither in or out");
        }
        sb.append(" ::: ");

        bool addComma = false;
        for (int i=0; i < inParams.size(); i++) {
            if (i==0) {
                sb.append(tr("In: "));
                addComma = true;
            }
            else sb.append(", ");
            sb.append(inParams.at(i));
        }

        if (addComma) sb.append(", ");
        addComma = false;

        for (int i=0; i < outParams.size(); i++) {
            if (i==0) {
                sb.append(tr("Out: "));
                addComma = true;
            }
            else sb.append(", ");
            sb.append(outParams.at(i));
        }

        if (addComma) sb.append(", ");

        for (int i=0; i < inOutParams.size(); i++) {
            if (i==0) sb.append(tr("In/Out: "));
            else sb.append(", ");
            sb.append(inOutParams.at(i));
        }
    }
    return sb/*.toString()*/;
}

//@Override
/*public*/  FemaleSocket* DefaultModule::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
    if (index != 0) {
        throw new IllegalArgumentException(
                tr("index has invalid value: %1").arg(index));
    }

    return _femaleRootSocket;
}

//@Override
/*public*/  int DefaultModule::getChildCount() {
    return 1;
}

//@Override
/*public*/  Category DefaultModule::getCategory() {
    return Category::OTHER;
}
/*
protected void printTreeRow(Locale locale, PrintWriter writer, String currentIndent) {
    writer.append(currentIndent);
    writer.append(getLongDescription(locale));
    writer.println();
}
*/
/** {@inheritDoc} */
//@Override
/*public*/  void DefaultModule::printTree(
        PrintTreeSettings* settings,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {

    printTree(settings, QLocale(), writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultModule::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {

    printTree(settings, locale, writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultModule::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        QString currentIndent,
        /*MutableInt*/int* lineNumber) {

    printTreeRow(settings, locale, writer, currentIndent, lineNumber);

    _femaleRootSocket->printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
}
/*
//@Override
/*
public  void DefaultModule::setRootSocketType(FemaleSocketManager::SocketType* socketType) {
    if ((_femaleRootSocket != nullptr) && _femaleRootSocket.isConnected()) throw new RuntimeException("Cannot set root socket when it's connected");

    _rootSocketType = socketType;
    _femaleRootSocket = socketType.createSocket(this, this, "Root");

    // Listeners should never be enabled for a module
    _femaleRootSocket.setEnableListeners(false);
}
*/
//@Override
/*public*/  FemaleSocketManager::SocketType* DefaultModule::getRootSocketType() {
    return _rootSocketType;
}

//@Override
/*public*/  FemaleSocket* DefaultModule::getRootSocket() {
    return _femaleRootSocket;
}

//@Override
/*public*/  void DefaultModule::addParameter(QString name, bool isInput, bool isOutput) {
    _parameters.insert(new DefaultSymbolTable::DefaultParameter(name, isInput, isOutput));
}

//@Override
/*public*/  void DefaultModule::addParameter(Module::Parameter* parameter) {
    _parameters.insert(parameter);
}

//    //@Override
//    /*public*/  void removeParameter(String name) {
//        _parameters.remove(name);
//    }

//@Override
/*public*/  void DefaultModule::addLocalVariable(
        QString name,
        InitialValueType::TYPES initialValueType,
        QString initialValueData) {
            _localVariables.insert(new VariableData(
            name,
            initialValueType,
            initialValueData));
}

//    //@Override
//    /*public*/  void removeLocalVariable(String name) {
//        _localVariables.remove(name);
//    }

//@Override
/*public*/  QSet<Module::Parameter*> DefaultModule::getParameters() {
    return _parameters;
}

//@Override
/*public*/  QSet<VariableData*> DefaultModule::getLocalVariables() {
    return _localVariables;
}

//@Override
/*public*/  void DefaultModule::connected(FemaleSocket* socket) {
    _socketSystemName = socket->getConnectedSocket()->getSystemName();
}

//@Override
/*public*/  void DefaultModule::disconnected(FemaleSocket* socket) {
    _socketSystemName = nullptr;
}

/*public*/  void DefaultModule::setSocketSystemName(QString systemName) {
    if ((systemName == "") || (systemName!=(_socketSystemName))) {
        _femaleRootSocket->_disconnect();
    }
    _socketSystemName = systemName;
}

/*public*/  QString DefaultModule::getSocketSystemName() {
    return _socketSystemName;
}

/** {@inheritDoc} */
//@Override
/*final*/ /*public*/  void DefaultModule::setup() {
    if (!_femaleRootSocket->isConnected()
            || _femaleRootSocket->getConnectedSocket()->getSystemName()
                    !=(_socketSystemName)) {

        _femaleRootSocket->_disconnect();

        if (_socketSystemName != nullptr) {
            try {
                MaleSocket* maleSocket =
                        (MaleSocket*)_rootSocketType->getManager()
                                ->getBySystemName(_socketSystemName);
                if (maleSocket != nullptr) {
                    _femaleRootSocket->_connect(maleSocket);
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
        _femaleRootSocket->setup();
    }
}

/** {@inheritDoc} */
//@Override
/*final*/ /*public*/  void DefaultModule::disposeMe() {
    _femaleRootSocket->dispose();
}

//@Override
/*protected*/ void DefaultModule::registerListenersForThisClass() {
    // Do nothing. A module never listen on anything.
}

//@Override
/*protected*/ void DefaultModule::unregisterListenersForThisClass() {
    // Do nothing. A module never listen on anything.
}

//@Override
/*public*/  Base* DefaultModule::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
    throw new UnsupportedOperationException("Not supported yet.");
}

/** {@inheritDoc} */
//@Override
/*public*/  QList<NamedBeanUsageReport*>* DefaultModule::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*>* report = new QList<NamedBeanUsageReport*>();
    if (bean != nullptr) {
        getUsageTree(0, bean, report, nullptr);
    }
    return report;
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultModule::getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
    log->debug(tr("** %1 :: %2").arg(level).arg(this->metaObject()->className()));
    level++;
    _femaleRootSocket->getUsageTree(level, bean, report, cdl);
}

/*private*/ /*final*/ /*static*/ Logger* DefaultModule::log = LoggerFactory::getLogger("DefaultModule");
