#include "abstractbase.h"
#include "loggerfactory.h"
#include "femalesocket.h"
#include "runtimeexception.h"
#include "conditionalng.h"
#include "logixng.h"
#include "abstractmalesocket.h"
#include "abstractfemalesocket.h"
#include "defaultlogixng.h"

/**
 * The abstract class that is the base class for all LogixNG classes that
 * implements the Base interface.
 */
///*public*/ abstract class AbstractBase
//        extends AbstractNamedBean
//        implements Base {


/*public*/ AbstractBase::AbstractBase(QString sys, QObject* parent) /*throw (BadSystemNameException)*/
 : AbstractNamedBean(sys, parent){
    //super(sys);
}

/*public*/ AbstractBase::AbstractBase(QString sys, QString user, QObject* parent) : AbstractNamedBean(sys, user, parent)
        /*throw (BadUserNameException, BadSystemNameException)*/{
    //super(sys, user);
}

/** {@inheritDoc} */
//@Override
/*public*/ Base* AbstractBase::deepCopyChildren(Base* original, QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throw (JmriException)*/ {
    for (int i=0; i < original->getChildCount(); i++) {
        // Copy the name of the socket.
        // Ignore duplicate errors since these errors might happen temporary in this loop.
        getChild(i)->setName(original->getChild(i)->getName(), true);

        // Copy the child
        if (original->getChild(i)->isConnected()) {
            Base* childTree = original->getChild(i)->getConnectedSocket()->getDeepCopy(systemNames, userNames);
            getChild(i)->_connect((AbstractMaleSocket*) childTree->bself());
        }
    }
    return this;
}

/** {@inheritDoc} */
//@Override
/*public*/ ConditionalNG* AbstractBase::getConditionalNG() {
    if (qobject_cast<DefaultConditionalNG*>(this->bself() )) return (DefaultConditionalNG*)this;
    if (getParent() == nullptr) return nullptr;
    return getParent()->getConditionalNG();
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ LogixNG* AbstractBase::getLogixNG() {
    if (qobject_cast<LogixNG*>(this )) return (LogixNG*)this;
    if (getParent() == nullptr) return nullptr;
    return getParent()->getLogixNG();
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ Base* AbstractBase::getRoot() {
    Base* item = this;
    while (item->getParent() != nullptr) {
        item = item->getParent();
    }
    return item;
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ bool AbstractBase::setParentForAllChildren(QList<QString>* errors) {
    bool result = true;
    for (int i=0; i < getChildCount(); i++) {
        FemaleSocket* femaleSocket = getChild(i);
        femaleSocket->setParent(this);
        if (femaleSocket->isConnected()) {
            MaleSocket* connectedSocket = femaleSocket->getConnectedSocket();
            Base* p = connectedSocket->getParent();
            if ((connectedSocket->getParent() != nullptr)
                    && (connectedSocket->getParent() != femaleSocket)) {
                errors->append(tr("The child %1 already has the parent %2 so it cannot be added to %3").arg(
                        connectedSocket->getSystemName(),
                        connectedSocket->getParent()->getSystemName(),
                        Base::getSystemName()));
                log->error(tr("The child %1 already has the parent %2 so it cannot be added to %3").arg(
                        connectedSocket->getSystemName(),
                        connectedSocket->getParent()->getSystemName(),
                        Base::getSystemName()));
                femaleSocket->_disconnect();
                result = false;
            } else {
                connectedSocket->Base::setParent(femaleSocket);
                result = result && connectedSocket->setParentForAllChildren(errors);
            }
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
//abstract /*protected*/ void registerListenersForThisClass();

/**
 * Unregister listeners if this object needs that.
 * <P>
 * Important: This method may be called more than once. Methods overriding
 * this method must ensure that listeners are not unregistered more than once.
 */
//abstract /*protected*/ void unregisterListenersForThisClass();

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ void AbstractBase::registerListeners() {
    if (isActive()) {
        registerListenersForThisClass();
        for (int i=0; i < getChildCount(); i++) {
            //getChild(i)->registerListeners();
         Base* b = getChild(i);
         ((AbstractBase*)b->bself())->registerListeners();
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ void AbstractBase::unregisterListeners() {
    unregisterListenersForThisClass();
    for (int i=0; i < getChildCount(); i++) {
     FemaleSocket* child = getChild(i);
     ((AbstractFemaleSocket*)getChild(i)->bself())->unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ bool AbstractBase::isActive() {
// bool enabled = Base::isEnabled();
// AbstractBase* parent = nullptr;
// Base* bp = this->getParent();
// bool pActive = false;
// if(bp)
// {
//   parent = (AbstractBase*)getParent()->bself();
//   pActive = parent->AbstractBase::isActive();
// }
 return isEnabled() && ((getParent() == nullptr) || getParent()->isActive());
 //return (enabled && parent == nullptr) || pActive;
}

/*protected*/ void AbstractBase::printTreeRow(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString currentIndent,
        /*MutableInt*/int* lineNumber) {

    if (settings->_printLineNumbers) {
        writer->print(QString(PRINT_LINE_NUMBERS_FORMAT).arg(*lineNumber/*.addAndGet(1)*/++));
    }
    writer->print(currentIndent);
    writer->print(getLongDescription(locale));
    writer->println();
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractBase::printTree(
        PrintTreeSettings* settings,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {

    printTree(settings, QLocale(), writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractBase::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {

    printTree(settings, locale, writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractBase::printTree(PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        QString currentIndent,
        /*MutableInt*/int *lineNumber) {

    printTreeRow(settings, locale, writer, currentIndent, lineNumber);

    for (int i=0; i < getChildCount(); i++) {
        getChild(i)->printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractBase::getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
    log->debug(tr("## %1 :: %2").arg(level).arg(this->getLongDescription()));
    level++;
    for (int i=0; i < getChildCount(); i++) {
        getChild(i)->getUsageTree(level, bean, report, cdl);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractBase::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
}

/**
 * {@inheritDoc}
 *
 * Do a string comparison.
 */
//@CheckReturnValue
//@Override
/*public*/ int AbstractBase::compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, /*@Nonnull*/ NamedBean* n) {
    return suffix1.compare(suffix2);
}

/**
 * Dispose this class.
 * Listeners do not need to be unregistered by this method since they are
 * unregistered by dispose().
 */
//abstract /*protected*/ void disposeMe();

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ void AbstractBase::dispose() {
    AbstractNamedBean::dispose();
    for (int i=0; i < getChildCount(); i++) {
        getChild(i)->dispose();
    }
    unregisterListeners();
    disposeMe();
}

/*protected*/ void AbstractBase::assertListenersAreNotRegistered(Logger* log, QString method) {
    if (_listenersAreRegistered) {
        RuntimeException* e = new RuntimeException(method + " must not be called when listeners are registered");
        log->error(method + " must not be called when listeners are registered", e);
        throw *e;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractBase::getListenerRefsIncludingChildren(QList<QString> list) {
    //list.addAll(getListenerRefs());
 for(QString s : Base::getListenerRefs())
  list.append(s);
    for (int i=0; i < getChildCount(); i++) {
        getChild(i)->getListenerRefsIncludingChildren(list);
    }
}

/**
 * Is the operation allowed on this child?
 * @param index the index of the child to do the operation on
 * @param oper the operation to do
 * @return true if operation is allowed, false otherwise
 */
/*public*/ /*default*/ bool AbstractBase::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper)
{
 if(qobject_cast<MaleSocket*>(this->bself()))
  return ((MaleSocket*)this)->getObject()->isSocketOperationAllowed(index, oper);

}
/**
 * Do an operation on a child
 * @param index the index of the child to do the operation on
 * @param oper the operation to do
 */
/*public*/  /*default*/  void AbstractBase::doSocketOperation(int index, FemaleSocketOperation::TYPES oper)
{
 if(qobject_cast<MaleSocket*>(this->bself()))
 {
   ((MaleSocket*)this->bself())->getObject()->doSocketOperation(index, oper);
 }
 // By default, do nothing if not a male socket
}

/*private*/ /*static*/ /*final*/ Logger* AbstractBase::log = LoggerFactory::getLogger("AbstractBase");
