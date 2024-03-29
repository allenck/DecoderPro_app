#include "defaultlogixngmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "defaultlogixng.h"
#include "logixng.h"
#include "module.h"
#include "modulemanager.h"
#include "joptionpane.h"
#include "clipboard.h"
#include "base.h"
#include "conditionalng_manager.h"
#include "vptr.h"
#include "logixng_initializationmanager.h"
#include "defaultnamedtablemanager.h"
#include "defaultlogixnginitializationmanager.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"

/**
 * Class providing the basic logic of the LogixNG_Manager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
// /*public*/ class DefaultLogixNGManager extends AbstractManager<LogixNG>
//        implements LogixNG_Manager {


/*public*/ DefaultLogixNGManager::DefaultLogixNGManager(QObject* parent)
 : AbstractManager(parent) {
   setObjectName("DefaultLogixNGManager");
 // The LogixNGPreferences class may load plugins so we must ensure
    // it's loaded here.
    InstanceManager::getDefault("LogixNGPreferences");
    registerSelf();
}

//@Override
/*public*/ int DefaultLogixNGManager::getXMLOrder() const{
    return LOGIXNGS;
}

//@Override
/*public*/ QChar DefaultLogixNGManager::typeLetter() const {
    return 'Q';
}

/**
 * Test if parameter is a properly formatted system name.
 *
 * @param systemName the system name
 * @return enum indicating current validity, which might be just as a prefix
 */
//@Override
/*public*/ Manager::NameValidity DefaultLogixNGManager::validSystemNameFormat(QString systemName) {
    return LogixNG_Manager::ng_validSystemNameFormat(
            DefaultLogixNGManager::getSubSystemNamePrefix(), systemName);
//        if (systemName.matches(getSubSystemNamePrefix()+"(:AUTO:)?\\d+")) {
//            return NameValidity.VALID;
//        } else {
//            return NameValidity.INVALID;
//        }
}

/**
 * Method to create a new LogixNG if the LogixNG does not exist.
 * <p>
 * Returns null if
 * a Logix with the same systemName or userName already exists, or if there
 * is trouble creating a new LogixNG.
 */
//@Override
/*public*/ LogixNG* DefaultLogixNGManager::createLogixNG(QString systemName, QString userName)
        /*throw new (IllegalArgumentException)*/ {

    // Check that LogixNG does not already exist
    DefaultLogixNG* x =nullptr;
    NamedBean* nb = nullptr;
    if (userName != nullptr && userName !=("")) {
        //x = (DefaultLogixNG*)getByUserName(userName)->bself();
     nb = getByUserName(userName);
     if (nb != nullptr) {
         return nullptr;
     }
    }
    //x = (LogixNG*)getBySystemName(systemName)->self();
    nb = getBySystemName(systemName);
    if (nb != nullptr) {
        return nullptr;
    }
    // Check if system name is valid
    if (this->validSystemNameFormat(systemName) != NameValidity::VALID) {
        throw new  IllegalArgumentException("SystemName " + systemName + " is not in the correct format");
    }
    // LogixNG does not exist, create a new LogixNG
    x = new DefaultLogixNG(systemName, userName);
    // save in the maps
    AbstractManager::Register((AbstractNamedBean*)x);

    // Keep track of the last created auto system name
    updateAutoNumber(systemName);

    return x;
}

//@Override
/*public*/ LogixNG* DefaultLogixNGManager::createLogixNG(QString userName) /*throw new (IllegalArgumentException)*/ {
    return createLogixNG(AbstractManager::getAutoSystemName(), userName);
}

//@Override
/*public*/ LogixNG* DefaultLogixNGManager::getLogixNG(QString name) {
 NamedBean* nb = nullptr;
    nb = getByUserName(name);
    if (nb != nullptr) {
        return (DefaultLogixNG*)nb->self();
    }
    //return (LogixNG*)LogixNG_Manager::getBySystemName(name)->self();
    nb = getBySystemName(name);
    if(nb)
     return (DefaultLogixNG*)nb->self();
    return nullptr;
}

//@Override
/*public*/ NamedBean* DefaultLogixNGManager::getByUserName(QString name) const{
    return _tuser->value(name);
}

//@Override
/*public*/ NamedBean* DefaultLogixNGManager::getBySystemName(QString name)const {
    return _tsys->value(name);
}

/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultLogixNGManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "LogixNGs" : "LogixNG");
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::setupAllLogixNGs() {
    QList<QString>* errors = new QList<QString>();
    bool result = true;
    for (/*LogixNG* logixNG*/NamedBean* nb : _tsys->values()) {
     LogixNG* logixNG = (DefaultLogixNG*)nb->self();
        logixNG->setup();
        result = result && logixNG->setParentForAllChildren(errors);
    }
    for (/*Module* module*/ NamedBean* nb: ((ModuleManager*)InstanceManager::getDefault("ModuleManager"))->getNamedBeanSet()) {
     Module* module = qobject_cast<Module*>(nb->self());
        module->setup();
        result = result && module->setParentForAllChildren(errors);
    }
    _clipboard->setup();
    if (errors->size() > 0) {
        messageDialog("SetupErrorsTitle", errors, nullptr);
    }
    checkItemsHaveParents();
}

/**
 * Display LogixNG setup errors when not running in headless mode.
 * @param titleKey The bundle key for the dialog title.
 * @param messages A ArrayList of messages that have been localized.
 * @param helpKey The bundle key for additional information about the errors
 */
/*private*/ void DefaultLogixNGManager::messageDialog(QString titleKey, QList<QString>* messages, QString helpKey) {
//        if (/*!GraphicsEnvironment.isHeadless() &&*/ !bool->getBoolean("jmri.test.no-dialogs")) {
        QString sb =  QString("<html>");
        //messages.forEach(msg ->
        for(QString msg : *messages)
        {
            sb.append(msg);
            sb.append("<br>");
        }//);
        if (helpKey != "") {
            sb.append("<br>");
            sb.append(/*Bundle.getMessage*/(helpKey));
        }
        sb.append("/<html>");
        JOptionPane::showMessageDialog(nullptr,
                sb/*.toString()*/,
                /*Bundle.getMessage*/(titleKey),
                JOptionPane::WARNING_MESSAGE);
//        }
}

 /*private*/ void DefaultLogixNGManager::checkItemsHaveParents(QSet</*? extends*/ MaleSocket*> set, QList<MaleSocket*> beansWithoutParentList)
 {
    for (MaleSocket* bean : set) {
        if (((Base*)bean)->getParent() == nullptr) beansWithoutParentList.append(bean);
    }
}

/*private*/ void DefaultLogixNGManager::checkItemsHaveParents() {
    QList<MaleSocket*> beansWithoutParentList = QList<MaleSocket*>();
#if 0
    checkItemsHaveParents(InstanceManager.getDefault(AnalogActionManager.class).getNamedBeanSet(), beansWithoutParentList);
    checkItemsHaveParents(InstanceManager.getDefault(DigitalActionManager.class).getNamedBeanSet(), beansWithoutParentList);
    checkItemsHaveParents(InstanceManager.getDefault(DigitalboolActionManager.class).getNamedBeanSet(), beansWithoutParentList);
    checkItemsHaveParents(InstanceManager.getDefault(StringActionManager.class).getNamedBeanSet(), beansWithoutParentList);
    checkItemsHaveParents(InstanceManager.getDefault(AnalogExpressionManager.class).getNamedBeanSet(), beansWithoutParentList);
    checkItemsHaveParents(InstanceManager.getDefault(DigitalExpressionManager.class).getNamedBeanSet(), beansWithoutParentList);
    checkItemsHaveParents(InstanceManager.getDefault(StringExpressionManager.class).getNamedBeanSet(), beansWithoutParentList);
#endif
    if (!beansWithoutParentList.isEmpty()) {
        QList<QString>* errors = new QList<QString>();
        QList<QString>* msgs = new QList<QString>();
        for (Base* b : beansWithoutParentList) {
            b->setup();
            b->setParentForAllChildren(errors);
        }
        for (Base* b : beansWithoutParentList) {
            if (b->getParent() == nullptr) {
                log->error(tr("Item has no parent: %1, %2, %3").arg(
                        b->getSystemName(),
                        b->getUserName(),
                        b->getLongDescription()));
                msgs->append(tr("Item has no parent: %1, %2, %3").arg(
                        b->getSystemName(),
                        b->getUserName(),
                        b->getLongDescription()));

                for (int i=0; i < b->getChildCount(); i++) {
                    if (b->getChild(i)->isConnected()) {
                        log->error(tr("    Child: %1, %2, %3").arg(
                                b->getChild(i)->getConnectedSocket()->getSystemName(),
                                b->getChild(i)->getConnectedSocket()->getUserName(),
                                b->getChild(i)->getConnectedSocket()->getLongDescription()));
                    }
                }
                log->error("                                                                 ");
                QList<QString>* cliperrors = new QList<QString>();
                _clipboard->add((MaleSocket*) b->bself(), cliperrors);
            }
        }
        messageDialog("ParentErrorsTitle", msgs, "NoParentHelp");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::activateAllLogixNGs() {
    activateAllLogixNGs(true, true);
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::activateAllLogixNGs(bool runDelayed, bool runOnSeparateThread) {

    _isActive = true;

    // This may take a long time so it must not be done on the GUI thread.
    // Therefore we create a new thread for this task.
//        Runnable runnable = () -> {
//            QSet<LogixNG*> activeLogixNGs = /*new HashSet<>*/();

//            // Activate and execute the initialization LogixNGs first.
//            QList<LogixNG*> initLogixNGs =
//                    ((LogixNG_InitializationManager*)InstanceManager::getDefault("LogixNG_InitializationManager")
//                            .getList();

//            for (LogixNG logixNG : initLogixNGs) {
//                if (logixNG.isActive()) {
//                    logixNG.registerListeners();
//                    logixNG.execute(false);
//                    activeLogixNGs.add(logixNG);
//                } else {
//                    logixNG.unregisterListeners();
//                }
//            }

//            // Activate and execute all the rest of the LogixNGs.
//            _tsys.values().stream()
//                    .sorted()
//                    .filter((logixNG) -> !(activeLogixNGs.contains(logixNG)))
//                    .forEachOrdered((logixNG) -> {

//                if (logixNG.isActive()) {
//                    logixNG.registerListeners();
//                    logixNG.execute();
//                } else {
//                    logixNG.unregisterListeners();
//                }
//            });
//        };
    Runnable* runnable = new DLMRunnable(this);
#if 1 // TODO:
    if (runOnSeparateThread) //new Thread(runnable)->start();
    {
     //QThreadPool::globalInstance()->start(runnable);
     QThread* newThread = new QThread();
     runnable->moveToThread(newThread);
     connect(newThread, &QThread::started, [=]{ runnable->run();});
     newThread->start();
    }
    else runnable->run();
#endif
}

void DLMRunnable::run()
{
 QSet<LogixNG*> activeLogixNGs = QSet<LogixNG*>();

 // Activate and execute the initialization LogixNGs first.
 QList<LogixNG*> initLogixNGs =
     ((DefaultLogixNGInitializationManager*)InstanceManager::getDefault("LogixNG_InitializationManager"))
             ->getList();

 for (LogixNG* logixNG : initLogixNGs) {
  //DefaultLogixNG* logixNG = (DefaultLogixNG*)lNG->bself();
  if (logixNG->isActive()) {
      logixNG->registerListeners();
      logixNG->execute(false);
      activeLogixNGs.insert(logixNG);
  } else {
      logixNG->unregisterListeners();
  }
 }

// Activate and execute all the rest of the LogixNGs.
// _tsys.values().stream()
//         .sorted()
//         .filter((logixNG) -> !(activeLogixNGs.contains(logixNG)))
//         .forEachOrdered((logixNG) -> {
 foreach(NamedBean* nb, dlm->_tsys->values())
 {
  LogixNG* logixNG = (DefaultLogixNG*)nb->self();

  bool found = false;
  for(LogixNG* l1 : activeLogixNGs)
  {
   if (logixNG->NamedBean::getSystemName() == l1->NamedBean::getSystemName())
   {
    found = true;
    break;
   }
  }

//  if(!(activeLogixNGs.contains(logixNG)))
  if(!found)
  {
   if (logixNG->isActive()) {
       logixNG->registerListeners();
       logixNG->execute();
   } else {
       logixNG->unregisterListeners();
   }
  }
 }
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::deActivateAllLogixNGs() {
    for (/*LogixNG* logixNG*/NamedBean* nb : _tsys->values()) {
     LogixNG* logixNG = (LogixNG*)nb->self();
        logixNG->unregisterListeners();
    }
    _isActive = false;
}

/** {@inheritDoc} */
//@Override
/*public*/ bool DefaultLogixNGManager::isActive() {
    return _isActive;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::deleteLogixNG(LogixNG* x) {
    // delete the LogixNG
    AbstractManager::deregister((NamedBean*)x);
    x->Base::dispose();
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::setLoadDisabled(bool s) {
    throw new UnsupportedOperationException("Not supported yet.");
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::printTree(
        Base::PrintTreeSettings* settings,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {

    printTree(settings, QLocale(), writer, indent, lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::printTree(
        Base::PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        /*MutableInt*/int* lineNumber) {

    int mutableInt =0;

    for (/*LogixNG* logixNG*/NamedBean* nb : AbstractManager::getNamedBeanSet()) {
     LogixNG* logixNG = (DefaultLogixNG*)nb->self();
        logixNG->printTree(settings, locale, writer, indent, "", &mutableInt);
        writer->println();
    }

    ((ModuleManager*)InstanceManager::getDefault("ModuleManager"))->printTree(settings, locale, writer, indent, lineNumber);
    ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->printTree(locale, writer, indent);
    ((DefaultLogixNGInitializationManager*)InstanceManager::getDefault("LogixNG_InitializationManager"))->printTree(locale, writer, indent);
}


/*static*/ /*volatile*/ DefaultLogixNGManager* DefaultLogixNGManager::_instance = nullptr;

//@InvokeOnGuiThread  // this method is not thread safe
/*static*/ /*public*/ DefaultLogixNGManager* DefaultLogixNGManager::instance() {
//        if (!ThreadingUtil.isGUIThread()) {
//            LoggingUtil.warnOnce(log, "instance() called on wrong thread");
//        }

    if (_instance == nullptr) {
        _instance = new DefaultLogixNGManager();
    }
    return (_instance);
}

/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultLogixNGManager::getNamedBeanClass() const{
    return "LogixNG";
}

/** {@inheritDoc} */
//@Override
/*public*/ DefaultClipboard* DefaultLogixNGManager::getClipboard() {
    return _clipboard;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNGManager::registerManager(Manager/*<? extends MaleSocket>*/* manager) {
    _managers.insert(manager->mself()->metaObject()->className(), manager);
}

/** {@inheritDoc} */
//@Override
/*public*/ Manager/*<? extends MaleSocket>*/* DefaultLogixNGManager::getManager(QString className) {
    return _managers.value(className);
}

/**
 * Inform all registered listeners of a vetoable change.If the propertyName
 * is "CanDelete" ALL listeners with an interest in the bean will throw new an
 * exception, which is recorded returned back to the invoking method, so
 * that it can be presented back to the user.However if a listener decides
 * that the bean can not be deleted then it should throw new an exception with
 * a property name of "DoNotDelete", this is thrown back up to the user and
 * the delete process should be aborted.
 *
 * @param p   The programmatic name of the property that is to be changed.
 *            "CanDelete" will inquire with all listeners if the item can
 *            be deleted. "DoDelete" tells the listener to delete the item.
 * @param old The old value of the property.
 * @throws java.beans.PropertyVetoException If the recipients wishes the
 *                                          delete to be aborted (see above)
 */
//@OverridingMethodsMustInvokeSuper
/*public*/ void DefaultLogixNGManager::fireVetoableChange(QString p, QVariant old) /*throw new (PropertyVetoException)*/ {
    PropertyChangeEvent* evt = new PropertyChangeEvent(this, p, old, QVariant());
    for (VetoableChangeListener* vc : *vetoableChangeSupport->getVetoableChangeListeners()) {
        vc->vetoableChange(evt);
    }
}

/** {@inheritDoc} */
//@Override
//    @OverridingMethodsMustInvokeSuper
/*public*/ /*final*/ void DefaultLogixNGManager::deleteBean(/*@Nonnull*/ /*LogixNG*/ NamedBean* nb, /*@Nonnull*/  QString property) /*throw new PropertyVetoException*/ {
 LogixNG*  logixNG =  (DefaultLogixNG*)nb->self();
 for (int i=0; i < logixNG->getNumConditionalNGs(); i++) {
        ConditionalNG* child = logixNG->getConditionalNG(i);
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->deleteBean((AbstractNamedBean*)child->self(), property);
    }

    // throws PropertyVetoException if vetoed
    fireVetoableChange(property, VPtr<LogixNG>::asQVariant(logixNG));
    if (property ==("DoDelete")) { // NOI18N
        AbstractManager::deregister((NamedBean*)logixNG);
        logixNG->Base::dispose();
    }
}


/*private*/ /*final*/ /*static*/ Logger* DefaultLogixNGManager::log = LoggerFactory::getLogger("DefaultLogixNGManager");
