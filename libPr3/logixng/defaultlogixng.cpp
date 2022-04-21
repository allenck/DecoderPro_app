#include "defaultlogixng.h"
#include "category.h"
#include "conditionalng.h"
#include "loggerfactory.h"
#include "defaultconditionalngmanager.h"
#include "defaultlogixngmanager.h"
/**
 * The default implementation of LogixNG.
 *
 * @author Daniel Bergqvist Copyright 2018
 * @author Dave Sand        Copyright 2021
 */
///*public*/ class DefaultLogixNG extends AbstractNamedBean
//        implements LogixNG {



/*public*/ DefaultLogixNG::DefaultLogixNG(QString sys, QString user, QObject *parent) /*throw (BadUserNameException, BadSystemNameException)*/
  : AbstractNamedBean(sys, user, parent)
{
    //super(sys, user);
 setObjectName("DefaultLogixNG");
    // Do this test here to ensure all the tests are using correct system names
    Manager::NameValidity isNameValid = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->validSystemNameFormat(mSystemName);
    if (isNameValid != Manager::NameValidity::VALID) {
        throw  IllegalArgumentException("system name is not valid");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ Base* DefaultLogixNG::getParent() const {
    return nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::setParent(Base* parent) {
    throw new UnsupportedOperationException("A LogixNG cannot have a parent");
}

//@Override
/*public*/ QString DefaultLogixNG::getBeanType() {
    return tr("LogixNG");
}

//@Override
/*public*/ void DefaultLogixNG::setState(int s) /*throw (JmriException)*/ {
    log->warn("Unexpected call to setState in DefaultLogixNG.");  // NOI18N
}

//@Override
/*public*/ int DefaultLogixNG::getState() {
    log->warn("Unexpected call to getState in DefaultLogixNG.");  // NOI18N
    return UNKNOWN;
}

//@Override
/*public*/ QString DefaultLogixNG::getShortDescription(QLocale locale) {
    return "LogixNG";
}

//@Override
/*public*/ QString DefaultLogixNG::getLongDescription(QLocale locale) {
    return "LogixNG: "+AbstractNamedBean::getDisplayName();
}

//@Override
/*public*/ FemaleSocket* DefaultLogixNG::getChild(int index) /*throw (IllegalArgumentException, UnsupportedOperationException)*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/ int DefaultLogixNG::getChildCount() {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/ Category* DefaultLogixNG::getCategory() {
    throw new UnsupportedOperationException("Not supported.");
}

/** {@inheritDoc} */
//@Override
/*final*/ /*public*/ void DefaultLogixNG::setup() {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        if ( entry->_conditionalNG == nullptr
                || entry->_conditionalNG->AbstractNamedBean::getSystemName()
                        !=(entry->_systemName)) {

            QString systemName = entry->_systemName;
            if (systemName != nullptr) {
                entry->_conditionalNG =
                        (DefaultConditionalNG*)((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
                                ->getBySystemName(systemName);
                if (entry->_conditionalNG != nullptr) {
                    entry->_conditionalNG->setup();
                } else {
                    log->error("cannot load conditionalNG " + systemName);
                }
            }
        } else {
            entry->_conditionalNG->setup();
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::setEnabled(bool enable) {
    _enabled = enable;
    if (isActive()) {
        registerListeners();
        execute(true);
    } else {
        unregisterListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ bool DefaultLogixNG::isEnabled() {
    return _enabled;
}

/** {@inheritDoc} */
//@Override
/*public*/ QString DefaultLogixNG::getConditionalNG_SystemName(int index) {
    return _conditionalNG_Entries.at(index)->_systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::setConditionalNG_SystemName(int index, QString systemName) {
    if (index == _conditionalNG_Entries.size()) {
        _conditionalNG_Entries.append(new ConditionalNG_Entry(systemName));
    } else {
        ConditionalNG_Entry* entry = _conditionalNG_Entries.at(index);
        entry->_systemName = systemName;
        entry->_conditionalNG = nullptr;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ int DefaultLogixNG::getNumConditionalNGs() {
    return _conditionalNG_Entries.size();
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::swapConditionalNG(int nextInOrder, int row) {
    if (row <= nextInOrder) {
        return;
    }
    ConditionalNG_Entry* temp = _conditionalNG_Entries.at(row);
    for (int i = row; i > nextInOrder; i--) {
        _conditionalNG_Entries.replace(i, _conditionalNG_Entries.at(i - 1));
    }
    _conditionalNG_Entries.replace(nextInOrder, temp);
}

/** {@inheritDoc} */
//@Override
/*public*/ ConditionalNG* DefaultLogixNG::getConditionalNG(int order) {
    try {
     if(order < 0 || order>=_conditionalNG_Entries.size())
      throw new IndexOutOfBoundsException();
        return _conditionalNG_Entries.at(order)->_conditionalNG;
    } catch (IndexOutOfBoundsException* ioob) {
        return nullptr;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ bool DefaultLogixNG::addConditionalNG(DefaultConditionalNG* conditionalNG) {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        if (((AbstractNamedBean*)conditionalNG->self())->getSystemName() == (entry->_systemName)) {
            if (entry->_conditionalNG == nullptr) {
                // Normally this will be during xml loading
                entry->_conditionalNG = conditionalNG;
                return true;
            } else {
                log->error(tr("ConditionalNG '%1' has already been added to LogixNG '%2'").arg(conditionalNG->AbstractNamedBean::getSystemName(), getSystemName()));  // NOI18N
                return false;
            }
        }

    }

    ConditionalNG_Entry* entry = new ConditionalNG_Entry(conditionalNG, ((AbstractNamedBean*)conditionalNG->self())->getSystemName());
    _conditionalNG_Entries.append(entry);
    conditionalNG->setParent(this);
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/ ConditionalNG* DefaultLogixNG::getConditionalNG(QString systemName) {
    for (int i = 0; i < getNumConditionalNGs(); i++) {
        if (systemName ==(_conditionalNG_Entries.at(i)->_systemName)) {
            return _conditionalNG_Entries.at(i)->_conditionalNG;
        }
    }
    return nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ ConditionalNG* DefaultLogixNG::getConditionalNGByUserName(QString userName) {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        if (userName == (((AbstractNamedBean*)entry->_conditionalNG->self())->getUserName())) {
            return entry->_conditionalNG;
        }
    }
    return nullptr;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::deleteConditionalNG(ConditionalNG* conditionalNG) {
    if (_conditionalNG_Entries.size() <= 0) {
        log->error(tr("attempt to delete ConditionalNG not in LogixNG: %1").arg(((AbstractNamedBean*)conditionalNG->self())->getSystemName()));  // NOI18N
        return;
    }

    bool found = false;
    // Remove Conditional from this logix
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        if (conditionalNG == entry->_conditionalNG) {
            _conditionalNG_Entries.removeOne(entry);
            found = true;
            break;
        }
    }
    if (!found) {
        log->error(tr("attempt to delete ConditionalNG not in LogixNG: %1").arg(((AbstractNamedBean*)conditionalNG->self())->getSystemName()));  // NOI18N
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ bool DefaultLogixNG::isActive() {
    return _enabled && _manager->isActive();
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::execute() {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        entry->_conditionalNG->execute();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::execute(bool allowRunDelayed) {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        entry->_conditionalNG->execute(allowRunDelayed);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ ConditionalNG* DefaultLogixNG::getConditionalNG() {
    throw new UnsupportedOperationException("Not supported.");
}

/** {@inheritDoc} */
//@Override
/*public*/ LogixNG* DefaultLogixNG::getLogixNG() {
    return this;
}

/** {@inheritDoc} */
//@Override
/*public*/ /*final*/ Base* DefaultLogixNG::getRoot() {
    return this;
}

/** {@inheritDoc} */
//@Override
/*public*/ bool DefaultLogixNG::setParentForAllChildren(QList<QString> *errors) {
    bool result = true;
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        if (entry->_conditionalNG != nullptr) {
            entry->_conditionalNG->setParent(this);
            result = result && entry->_conditionalNG->AbstractBase::setParentForAllChildren(errors);
        }
    }
    return result;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::registerListeners() {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        entry->_conditionalNG->AbstractBase::registerListeners();
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::unregisterListeners() {
    for (ConditionalNG_Entry* entry : _conditionalNG_Entries) {
        entry->_conditionalNG->AbstractBase::unregisterListeners();
    }
}

/*protected*/ void DefaultLogixNG::printTreeRow(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString currentIndent,
        int* lineNumber) {

    if (settings->_printLineNumbers) {
        writer->write(QString(PRINT_LINE_NUMBERS_FORMAT).arg(*lineNumber/*.addAndGet(1)*/,8));
    }
    writer->write(currentIndent);
    writer->write(getLongDescription(locale));
    writer->println();
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::printTree(
        PrintTreeSettings* settings,
        PrintWriter* writer,
        QString indent,
        int* lineNumber) {

    printTree(settings, QLocale(), writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        int* lineNumber) {

    printTree(settings, locale, writer, indent, "", lineNumber);
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::printTree(
        PrintTreeSettings* settings,
        QLocale locale,
        PrintWriter* writer,
        QString indent,
        QString currentIndent,
        int* lineNumber) {

    printTreeRow(settings, locale, writer, currentIndent, lineNumber);

    for (int i=0; i < this->getNumConditionalNGs(); i++) {
        //getConditionalNG(i)->printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
     ConditionalNG* conditionalNG = getConditionalNG(i);
     conditionalNG->printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
//            writer.println();
    }
}

//@Override
/*public*/ Base* DefaultLogixNG::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
    throw new UnsupportedOperationException("Not supported yet.");
}

//@Override
/*public*/ Base* DefaultLogixNG::deepCopyChildren(Base* original, QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
    throw new UnsupportedOperationException("Not supported");
}

//    private static class ConditionalNG_Entry {
//        private String _systemName;
//        private ConditionalNG _conditionalNG;

//        private ConditionalNG_Entry(ConditionalNG conditionalNG, String systemName) {
//            _systemName = systemName;
//            _conditionalNG = conditionalNG;
//        }

//        private ConditionalNG_Entry(ConditionalNG conditionalNG) {
//            this._conditionalNG = conditionalNG;
//        }

//        private ConditionalNG_Entry(String systemName) {
//            this._systemName = systemName;
//        }

//        @Override
//        /*public*/ String toString() {
//            StringBuilder sb = new StringBuilder("ConditionalNG_Entry: name =");
//            sb.append(_systemName);
//            sb.append(", cdl = ");
//            sb.append(_conditionalNG == null ? "----" : _conditionalNG.getDisplayName());
//            return sb.toString();
//        }
//    }

/** {@inheritDoc} */
//@Override
/*public*/ QList<NamedBeanUsageReport *> *DefaultLogixNG::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*>* report = new QList<NamedBeanUsageReport*>();
    if (bean != nullptr) {
        getUsageTree(0, bean, report, nullptr);
    }
    return report;
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("** %1 :: %2").arg(level).arg(/*this.getClass().getName()*/ metaObject()->className()));

    level++;
    for (int i=0; i < this->getNumConditionalNGs(); i++) {
        getConditionalNG(i)->getUsageTree(level, bean, report, (NamedBean*)getConditionalNG(i));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
}

/** {@inheritDoc} */
//@Override
/*public*/ void DefaultLogixNG::getListenerRefsIncludingChildren(QList<QString> list) {
    //list.addAll(getListeneDefaultLogixNG::rRefs());
    foreach(QString s, Base::getListenerRefs())
    {
     list.append(s);
    }
    for (int i=0; i < getNumConditionalNGs(); i++) {
        getConditionalNG(i)->getListenerRefsIncludingChildren(list);
    }
}

/*private*/ /*final*/ /*static*/ Logger* DefaultLogixNG::log = LoggerFactory::getLogger("DefaultLogixNG");
