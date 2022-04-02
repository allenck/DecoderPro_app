#include "abstractmalesocket.h"
#include "femalesocket.h"
#include "logixngpreferences.h"
#include "instancemanager.h"
#include "loggingutil.h"
#include "threadingutil.h"
#include "abortconditionalngexecutionexception.h"
#include "loggerfactory.h"
#include "errorhandlingdialog.h"
#include "errorhandlingdialog_multiline.h"
#include "abstractbase.h"
#include "abstractdigitalaction.h"
#include "defaultconditionalng.h"
#include "abstractbase.h"

/**
 * The abstract class that is the base class for all LogixNG classes that
 * implements the Base interface.
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/ abstract class AbstractMaleSocket implements MaleSocket {


/*public*/ AbstractMaleSocket::AbstractMaleSocket(BaseManager/*<? extends NamedBean>*/* manager, Base* object, QObject* parent)
 //: AbstractNamedBean(object->getSystemName(), object->getUserName(), parent)
 : AbstractBase(parent)
{
 if(objectName().isEmpty())
  setObjectName("AbstractMaleSocket");
 if(mSystemName.isEmpty())
  mSystemName = ((AbstractNamedBean*)object->bself())->getSystemName();

 _manager = manager;
        QObject* obj = (QObject*)object;
        if(static_cast<AbstractMaleSocket*>(obj))
         _object = (AbstractMaleSocket*) obj;
        else
 _object = object;
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ Base* AbstractMaleSocket::getObject() {
    return _object;
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ Base* AbstractMaleSocket::getRoot() {
    return _object->getRoot();
}

/** {@inheritDoc} */
//@Override
/*public*/ bool AbstractMaleSocket::isLocked() {
    if (qobject_cast<AbstractMaleSocket*>(_object->bself())) {
        return ((AbstractMaleSocket*)_object->bself())->isLocked();
    }
    return _locked;
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::setLocked(bool locked) {
    if (qobject_cast<AbstractMaleSocket*>(_object->bself())) {
        ((AbstractMaleSocket*)_object->bself())->setLocked(locked);
    }
    _locked = locked;
}

/** {@inheritDoc} */
//@Override
/*public*/ bool AbstractMaleSocket::isSystem() {
    if (qobject_cast<AbstractMaleSocket*>(_object->bself())) {
        return ((AbstractMaleSocket*)_object->bself())->isSystem();
    }
    return _system;
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::setSystem(bool system) {
    if (qobject_cast<AbstractMaleSocket*>(_object->bself())) {
        ((AbstractMaleSocket*)_object->bself())->setSystem(system);
    }
    _system = system;
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ Category* AbstractMaleSocket::getCategory() {
    return _object->getCategory();
}

//@Override
/*public*/ /*final*/ FemaleSocket* AbstractMaleSocket::getChild(int index)  {
    return _object->getChild(index);
}

//@Override
/*public*/ /*final*/ int AbstractMaleSocket::getChildCount() {
    return _object->getChildCount();
}

//@Override
/*public*/ /*final*/ QString AbstractMaleSocket::getShortDescription(QLocale locale) {
    return _object->getShortDescription(locale);
}

//@Override
/*public*/ /*final*/ QString AbstractMaleSocket::getLongDescription(QLocale locale) {
 QObject* obj = (QObject*)_object->bself();
 QString cn = obj->metaObject()->className();

 if(static_cast<AbstractDigitalAction*>(obj))
  return ((AbstractDigitalAction*)obj)->getLongDescription(locale);

 if(static_cast<AbstractMaleSocket*>(obj))
  return ((AbstractMaleSocket*)obj)->getLongDescription(locale);
 else
    return _object->getLongDescription(locale);
}

//@Override
/*public*/ /*final*/ QString AbstractMaleSocket::getUserName() const{
    return ((AbstractBase*)_object->bself())->AbstractNamedBean::getUserName();
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::setUserName(QString s) throw (NamedBean::BadUserNameException) {
    ((AbstractBase*)_object->bself())->AbstractNamedBean::setUserName(s);
}

//@Override
/*public*/ /*final*/ QString AbstractMaleSocket::getSystemName() const{
 QString sys = ((AbstractMaleSocket*)_object->bself())->AbstractNamedBean::getSystemName();
 if(sys.isEmpty())
    return _object->getSystemName();
// QObject* obj = (QObject*)_object;
 return sys;
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::addPropertyChangeListener(PropertyChangeListener* l, QString name, QString listenerRef) {
    _object->addPropertyChangeListener(l, name, listenerRef);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::addPropertyChangeListener(QString propertyName, PropertyChangeListener* l, QString name, QString listenerRef) {
    _object->addPropertyChangeListener(propertyName, l, name, listenerRef);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::addPropertyChangeListener(PropertyChangeListener* l) {
    _object->PropertyChangeProvider::addPropertyChangeListener(l);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::addPropertyChangeListener(QString propertyName, PropertyChangeListener* l) {
    _object->PropertyChangeProvider::addPropertyChangeListener(propertyName, l);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::removePropertyChangeListener(PropertyChangeListener* l) {
    _object->removePropertyChangeListener(l);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::removePropertyChangeListener(QString propertyName, PropertyChangeListener* l) {
    _object->removePropertyChangeListener(propertyName, l);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::updateListenerRef(PropertyChangeListener* l, QString newName) {
    _object->updateListenerRef(l, newName);
}

//@Override
/*public*/ /*final*/ void AbstractMaleSocket::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) {
    _object->vetoableChange(evt);
}

//@Override
/*public*/ /*final*/ QString AbstractMaleSocket::getListenerRef(PropertyChangeListener* l) {
    return _object->getListenerRef(l);
}

//@Override
/*public*/ /*final*/ QList<QString> AbstractMaleSocket::getListenerRefs() {
    return _object->getListenerRefs();
}

//@Override
/*public*/ /*final*/ int AbstractMaleSocket::getNumPropertyChangeListeners() {
    return _object->getNumPropertyChangeListeners();
}

//@Override
/*public*/ /*final*/ /*synchronized*/ QVector<PropertyChangeListener*> AbstractMaleSocket::getPropertyChangeListeners()const {
    return _object->getPropertyChangeListeners();
}

//@Override
/*public*/ /*final*/ /*synchronized*/ QVector<PropertyChangeListener*> AbstractMaleSocket::getPropertyChangeListeners(QString propertyName) {
    return _object->getPropertyChangeListeners(propertyName);
}

//@Override
/*public*/ /*final*/ QVector<PropertyChangeListener *> AbstractMaleSocket::getPropertyChangeListenersByReference(QString name) {
    return _object->getPropertyChangeListenersByReference(name);
}

//@Override
/*public*/ QString AbstractMaleSocket::getComment() {
    return _object->getComment();
}

//@Override
/*public*/ void AbstractMaleSocket::setComment(QString comment) {
    _object->setComment(comment);
}

//@Override
/*public*/ bool AbstractMaleSocket::getListen() {
//        if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
//            return ((AbstractMaleSocket*)getObject()->bself())->getListen();
 QObject* obj = (QObject*) getObject();
 if(qobject_cast<AbstractMaleSocket*>(obj))
  return ((AbstractMaleSocket*)obj)->getListen();
//        }
    return _listen;
}

//@Override
/*public*/ void AbstractMaleSocket::setListen(bool listen)
{
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        ((AbstractMaleSocket*)getObject()->bself())->setListen(listen);
    }
    _listen = listen;
}

//@Override
/*public*/ bool AbstractMaleSocket::getCatchAbortExecution() {
    return _catchAbortExecution;
}

//@Override
/*public*/ void AbstractMaleSocket::setCatchAbortExecution(bool catchAbortExecution)
{
    _catchAbortExecution = catchAbortExecution;
}

//@Override
/*public*/ void AbstractMaleSocket::addLocalVariable(
        QString name,
        InitialValueType::TYPES initialValueType,
        QString initialValueData) {

    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        ((AbstractMaleSocket*)getObject()->bself())->addLocalVariable(name, initialValueType, initialValueData);
    } else {
        _localVariables.insert(new VariableData(name, initialValueType, initialValueData));
    }
}

//@Override
/*public*/ void AbstractMaleSocket::addLocalVariable(VariableData* variableData) {

    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        ((AbstractMaleSocket*)getObject()->bself())->addLocalVariable(variableData);
    } else {
        _localVariables.insert(variableData);
    }
}

//@Override
/*public*/ void AbstractMaleSocket::clearLocalVariables() {
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        ((AbstractMaleSocket*)getObject()->bself())->clearLocalVariables();
    } else {
        _localVariables.clear();
    }
}

//@Override
/*public*/ QSet<VariableData*> AbstractMaleSocket::getLocalVariables() {
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        return ((AbstractMaleSocket*)getObject()->bself())->getLocalVariables();
    } else {
        return _localVariables;
    }
}

//@Override
/*public*/ Base* AbstractMaleSocket::getParent()const{
    return _parent;
}

//@Override
/*public*/ void AbstractMaleSocket::setParent(Base* parent) {
    _parent = parent;
}

//@Override
/*public*/ /*final*/ ConditionalNG* AbstractMaleSocket::getConditionalNG() {
    if (getParent() == nullptr) return nullptr;
    //return getParent()->getConditionalNG();
    Base* parent = getParent();
    return ((AbstractBase*)parent->bself())->getConditionalNG();
}

//@Override
/*public*/ /*final*/ LogixNG* AbstractMaleSocket::getLogixNG() {
    if (getParent() == nullptr) return nullptr;
    return getParent()->getLogixNG();
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ bool AbstractMaleSocket::setParentForAllChildren(QList<QString> errors) {
    bool result = true;
    for (int i=0; i < getChildCount(); i++) {
        FemaleSocket* femaleSocket = getChild(i);
        femaleSocket->setParent(this);
        if (femaleSocket->isConnected()) {
            MaleSocket* connectedSocket = femaleSocket->getConnectedSocket();
            connectedSocket->Base::setParent(femaleSocket);
            result = result && connectedSocket->setParentForAllChildren(errors);
        }
    }
    return result;
}

/**
 * Register listeners if this object needs that.
 * <P>
 * Important: This method may be called more than once. Methods overriding
 * this method must ensure that listeners are not registered more than once.
 */
///*abstract*/virtual /*protected*/ void registerListenersForThisClass()=0;

/**
 * Unregister listeners if this object needs that.
 * <P>
 * Important: This method may be called more than once. Methods overriding
 * this method must ensure that listeners are not unregistered more than once.
 */
///*abstract*/ /*protected*/virtual void unregisterListenersForThisClass()=0;

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ void AbstractMaleSocket::registerListeners() {
 Base* bo = getObject();
 QObject* obj = (QObject*)bo;
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        //getObject()->registerListeners();
     ((AbstractMaleSocket*)obj)->registerListeners();
    } else {
        if (_listen) {
            registerListenersForThisClass();
            for (int i=0; i < getChildCount(); i++) {
                getChild(i)->registerListeners();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ void AbstractMaleSocket::unregisterListeners() {
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        getObject()->unregisterListeners();
    } else {
        unregisterListenersForThisClass();
        for (int i=0; i < getChildCount(); i++) {
            getChild(i)->unregisterListeners();
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ bool AbstractMaleSocket::isActive() {
    return isEnabled() && ((getParent() == nullptr) || getParent()->isActive());
}

/**
 * Print this row.
 * If getObject() doesn't return an AbstractMaleSocket, print this row.
 * <P>
 * If a male socket that extends AbstractMaleSocket wants to print
 * something here, it needs to override this method.
 * <P>
 * The reason this method doesn't print if getObject() returns an
 * AbstractMaleSocket is to protect so it doesn't print itself twice if
 * it's embedding an other AbstractmaleSocket-> An example of this is the
 * AbstractDebuggerMaleSocket which embeds other male sockets.
 *
 * @param settings settings for what to print
 * @param locale The locale to be used
 * @param writer the stream to print the tree to
 * @param currentIndent the current indentation
 * @param lineNumber the line number
 */
/*protected*/ void AbstractMaleSocket::printTreeRow(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString currentIndent,
        /*MutableInt*/int* lineNumber) {

    if (!qobject_cast<AbstractMaleSocket*>(getObject()->bself() )) {
        QString comment = getComment();
        if (comment != "") {
            comment = comment.replace("\\r\\n", "\\n");
            comment = comment.replace("\\r", "\\n");
            for (QString s : comment.split("\\n"/*, 0*/)) {
                if (settings->_printLineNumbers) {
                 writer->print(QString(PRINT_LINE_NUMBERS_FORMAT).arg(*lineNumber/*->addAndGet(1)*/++, 8));
                }
                writer->print(currentIndent);
                writer->print("// ");
                writer->print(s);
                writer->println();
            }
        }
        if (settings->_printLineNumbers) {
            writer->print(QString(PRINT_LINE_NUMBERS_FORMAT).arg(*lineNumber/*.addAndGet(1)*/++, 8));
        }
        writer->print(currentIndent);
        writer->print(getLongDescription(locale));
        if (getUserName() != "") {
            writer->print(" ::: ");
            writer->print(tr("User Name:"));
            writer->print(" ");
            writer->print(getUserName());
        }

        if (settings->_printErrorHandling) {
            writer->print(" ::: ");
            //writer->print(getErrorHandlingType()->toString());
            writer->print(ErrorHandlingType::toString(getErrorHandlingType()));
        }
        if (!isEnabled()) {
            writer->print(" ::: ");
            writer->print(tr("Disabled"));
        }
        if (isLocked()) {
            writer->print(" ::: ");
            writer->print(tr("Locked"));
        }
        if (isSystem()) {
            writer->print(" ::: ");
            writer->print(tr("System"));
        }
        writer->println();
    }
}

/*protected*/ void AbstractMaleSocket::printLocalVariable(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString currentIndent,
        /*MutableInt*/int* lineNumber,
        VariableData* localVariable) {

    if (settings->_printLineNumbers) {
        writer->print(QString(PRINT_LINE_NUMBERS_FORMAT).arg(*lineNumber/*.addAndGet(1)*/++,8));
    }
    writer->print(currentIndent);
    writer->print("   ::: ");
    writer->print(tr(
            //locale,
            "Local variable \"%1\", init to %2 \"%3\"").arg(
            localVariable->_name,
            InitialValueType::toString(localVariable->_initalValueType),
            localVariable->_initialValueData));
    writer->println();
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::printTree(PrintTreeSettings *settings,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int *lineNumber) {
    printTree(settings, QLocale(), writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {
    printTree(settings, locale, writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        QString currentIndent,
        /*MutableInt*/int* lineNumber) {

    printTreeRow(settings, locale, writer, currentIndent, lineNumber);

    if (settings->_printLocalVariables) {
        for (VariableData* localVariable : _localVariables) {
            printLocalVariable(settings, locale, writer, currentIndent, lineNumber, localVariable);
        }
    }

    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        getObject()->printTree(settings, locale, writer, indent, currentIndent, lineNumber);
    } else {
        for (int i=0; i < getChildCount(); i++) {
            getChild(i)->printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
    if (!(qobject_cast<AbstractMaleSocket*>(getObject()->bself()))) {
        log->debug(tr("*@ %1 :: %2").arg(level).arg(this->getLongDescription(QLocale())));
        _object->getUsageDetail(level, bean, report, cdl);
    }

    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        getObject()->getUsageTree(level, bean, report, cdl);
    } else {
        level++;
        for (int i=0; i < getChildCount(); i++) {
            getChild(i)->getUsageTree(level, bean, report, cdl);
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
}

//@Override
/*public*/ BaseManager/*<? extends NamedBean>*/* AbstractMaleSocket::getManager() {
    return _manager;
}

//@Override
/*public*/ /*final*/ Base* AbstractMaleSocket::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames)
        /*throw (JmriException)*/ {

    MaleSocket* maleSocket = (MaleSocket*)getObject()->getDeepCopy(systemNames, userNames)->bself();

    maleSocket->setComment(this->getComment());
    if (maleSocket->getDebugConfig() != nullptr) {
        maleSocket->setDebugConfig(maleSocket->getDebugConfig()->getCopy());
    }
    maleSocket->setEnabledFlag(isEnabled());
    maleSocket->setListen(getListen());
    maleSocket->setErrorHandlingType(getErrorHandlingType());
    maleSocket->setLocked(isLocked());
    maleSocket->setSystem(false);    // If a system item is copied, the new item is not treated as system
    maleSocket->setCatchAbortExecution(getCatchAbortExecution());

    for (VariableData* data : _localVariables) {
        maleSocket->addLocalVariable(data->_name, data->_initalValueType, data->_initialValueData);
    }

    return maleSocket;
}

//@Override
/*public*/ /*final*/ Base* AbstractMaleSocket::deepCopyChildren(Base* original, QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throw (JmriException)*/ {
    getObject()->deepCopyChildren(original, systemNames, userNames);
    return this;
}

/**
 * Disposes this object.
 * This must remove _all_ connections!
 */
//abstract protected void disposeMe();

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ void AbstractMaleSocket::dispose() {
    for (int i=0; i < getChildCount(); i++) {
        getChild(i)->dispose();
    }
    disposeMe();
}

//@Override
/*public*/ ErrorHandlingType::TYPES AbstractMaleSocket::getErrorHandlingType() {
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        return ((AbstractMaleSocket*)getObject()->bself())->getErrorHandlingType();
    } else {
        return _errorHandlingType;
    }
}

//@Override
/*public*/ void AbstractMaleSocket::setErrorHandlingType(ErrorHandlingType::TYPES errorHandlingType)
{
    if (qobject_cast<AbstractMaleSocket*>(getObject()->bself())) {
        ((AbstractMaleSocket*)getObject()->bself())->setErrorHandlingType(errorHandlingType);
    } else {
        _errorHandlingType = errorHandlingType;
    }
}

/*public*/ void AbstractMaleSocket::handleError(Base* item, QString message, JmriException* e, Logger* log) /*throw (JmriException)*/ {

    // Always throw AbortConditionalNGExecutionException exceptions
    if (!_catchAbortExecution && (static_cast<AbortConditionalNGExecutionException*>(e))) throw e;

    ErrorHandlingType::TYPES errorHandlingType = getErrorHandlingType();
    if (errorHandlingType == ErrorHandlingType::Default) {
        errorHandlingType = ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))
                ->getErrorHandlingType();
    }

    switch (errorHandlingType) {
        case ErrorHandlingType::ShowDialogBox:
        {
#if 0
            bool abort = ThreadingUtil::runOnGUIwithReturn([=]()  {
                ErrorHandlingDialog* dialog = new ErrorHandlingDialog();
                return dialog->showDialog(item, message);
            });

            if (abort) throw  AbortConditionalNGExecutionException(e);
#else
//     bool abort = ThreadingUtil::runOnGUIwithReturn(new AMSRun1(item, message));
#endif
            break;
        }
        case ErrorHandlingType::LogError:
            log->error(tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage()), e);
            break;

        case ErrorHandlingType::LogErrorOnce:
            LoggingUtil::warnOnce(log, tr("item %1, %2 thrown an exception: %3").arg(item->toString(),getObject()->toString(), e->getMessage())/*, *e*/);
            break;

        case ErrorHandlingType::ThrowException:
            throw e;

        case ErrorHandlingType::AbortExecution:
            log->error(tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage()), e);
            throw  AbortConditionalNGExecutionException(e);

        default:
            throw e;
    }
}
#if 0
void AMSRun1::run()
{
 ErrorHandlingDialog* dialog = new ErrorHandlingDialog();
  dialog->showDialog(item, message);
}
#endif

/*public*/ void AbstractMaleSocket::handleError(
        Base* item,
        QString message,
        QList<QString> messageList,
        JmriException* e,
        Logger* log)
        /*throw (JmriException)*/ {

    ErrorHandlingType::TYPES errorHandlingType = getErrorHandlingType();
    if (errorHandlingType == ErrorHandlingType::Default) {
        errorHandlingType = ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))
                ->getErrorHandlingType();
    }

    switch (errorHandlingType) {
    case ErrorHandlingType::ShowDialogBox:
    {
#if 0
            bool abort = ThreadingUtil::runOnGUIwithReturn([=]() {
                ErrorHandlingDialog_MultiLine* dialog = new ErrorHandlingDialog_MultiLine();
                return dialog->showDialog(item, message, messageList);
            });
            if (abort) throw  AbortConditionalNGExecutionException(e);
#endif
            break;
    }
        case ErrorHandlingType::LogError:
            log->error(tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage()), e);
            break;

        case ErrorHandlingType::LogErrorOnce:
            LoggingUtil::warnOnce(log, tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage())/*, *e*/);
            break;

        case ErrorHandlingType::ThrowException:
            throw *e;

        case ErrorHandlingType::AbortExecution:
            log->error(tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage()), e);
            throw new AbortConditionalNGExecutionException(e);

        default:
            throw *e;
    }
}

/*public*/ void AbstractMaleSocket::handleError(Base* item, QString message, RuntimeException* e, Logger* log) /*throw (JmriException)*/ {

    ErrorHandlingType::TYPES errorHandlingType = getErrorHandlingType();
    if (errorHandlingType == ErrorHandlingType::Default) {
        errorHandlingType = ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))
                ->getErrorHandlingType();
    }

    switch (errorHandlingType) {
        case ErrorHandlingType::ShowDialogBox:
        {
#if 0
            bool abort = ThreadingUtil::runOnGUIwithReturn([=]() {
                ErrorHandlingDialog* dialog = new ErrorHandlingDialog();
                return dialog->showDialog(item, message);
            });
            if (abort) throw  AbortConditionalNGExecutionException(e);
#endif
            break;
        }
        case ErrorHandlingType::LogError:
//                e.printStackTrace();
            log->error(tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage()), e);
            break;

        case ErrorHandlingType::LogErrorOnce:
//                e.printStackTrace();
            LoggingUtil::warnOnce(log, tr("item %1, %2 thrown an exception: %3").arg(item->toString(), getObject()->toString(), e->getMessage()));
            break;

        case ErrorHandlingType::ThrowException:
            throw e;

        case ErrorHandlingType::AbortExecution:
            throw new AbortConditionalNGExecutionException(e);

        default:
            throw *e;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractMaleSocket::getListenerRefsIncludingChildren(QList<QString> list) {
    //list.addAll(getListenerRefs());
    for(QString s : getListenerRefs())
      list.append(s);
    for (int i=0; i < getChildCount(); i++) {
        getChild(i)->getListenerRefsIncludingChildren(list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ QString AbstractMaleSocket::toString() {
    return getObject()->toString();
}

/*public*/ bool AbstractMaleSocket::equals(QObject* o ){
 if(o == this) return true;
 if(this->metaObject()->className() != o->metaObject()->className()) return false;
 QString sn1 = this->getSystemName();
 QString sn2 = ((AbstractMaleSocket*)o)->getSystemName();
 return sn1 == sn2;
}
/*private*/ /*static*/ /*final*/ Logger* AbstractMaleSocket::log = LoggerFactory::getLogger("AbstractMaleSocket");
