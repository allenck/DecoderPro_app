#include "defaultlogixng.h"
#include "category.h"
#include "conditionalng.h"
#include "loggerfactory.h"
#include "conditionalng_manager.h"
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
      : LogixNG(sys, user, parent)
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
        throw  UnsupportedOperationException("A LogixNG cannot have a parent");
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
    /*public*/ FemaleSocket* DefaultLogixNG::getChild(int index) throw (IllegalArgumentException, UnsupportedOperationException) {
        throw  UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int DefaultLogixNG::getChildCount() {
        throw  UnsupportedOperationException("Not supported.");
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
                    || entry->_conditionalNG->Base::getSystemName()
                            !=(entry->_systemName)) {

                QString systemName = entry->_systemName;
                if (systemName != nullptr) {
                    entry->_conditionalNG =
                            (ConditionalNG*)((ConditionalNG_Manager*)InstanceManager::getDefault("ConditionalNG_Manager"))
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
#if 0
    /** {@inheritDoc} */
    @Override
    /*public*/ String getConditionalNG_SystemName(int index) {
        return _conditionalNG_Entries.get(index)._systemName;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void setConditionalNG_SystemName(int index, String systemName) {
        if (index == _conditionalNG_Entries.size()) {
            _conditionalNG_Entries.add(new ConditionalNG_Entry(systemName));
        } else {
            ConditionalNG_Entry entry = _conditionalNG_Entries.get(index);
            entry._systemName = systemName;
            entry._conditionalNG = null;
        }
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ int getNumConditionalNGs() {
        return _conditionalNG_Entries.size();
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void swapConditionalNG(int nextInOrder, int row) {
        if (row <= nextInOrder) {
            return;
        }
        ConditionalNG_Entry temp = _conditionalNG_Entries.get(row);
        for (int i = row; i > nextInOrder; i--) {
            _conditionalNG_Entries.set(i, _conditionalNG_Entries.get(i - 1));
        }
        _conditionalNG_Entries.set(nextInOrder, temp);
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ ConditionalNG getConditionalNG(int order) {
        try {
            return _conditionalNG_Entries.get(order)._conditionalNG;
        } catch (java.lang.IndexOutOfBoundsException ioob) {
            return null;
        }
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ boolean addConditionalNG(ConditionalNG conditionalNG) {
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            if (conditionalNG.getSystemName().equals(entry._systemName)) {
                if (entry._conditionalNG == null) {
                    // Normally this will be during xml loading
                    entry._conditionalNG = conditionalNG;
                    return true;
                } else {
                    log.error("ConditionalNG '{}' has already been added to LogixNG '{}'", conditionalNG.getSystemName(), getSystemName());  // NOI18N
                    return false;
                }
            }

        }

        ConditionalNG_Entry entry = new ConditionalNG_Entry(conditionalNG, conditionalNG.getSystemName());
        _conditionalNG_Entries.add(entry);
        conditionalNG.setParent(this);
        return true;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ ConditionalNG getConditionalNG(String systemName) {
        for (int i = 0; i < getNumConditionalNGs(); i++) {
            if (systemName.equals(_conditionalNG_Entries.get(i)._systemName)) {
                return _conditionalNG_Entries.get(i)._conditionalNG;
            }
        }
        return null;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ ConditionalNG getConditionalNGByUserName(String userName) {
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            if (userName.equals(entry._conditionalNG.getUserName())) {
                return entry._conditionalNG;
            }
        }
        return null;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void deleteConditionalNG(ConditionalNG conditionalNG) {
        if (_conditionalNG_Entries.size() <= 0) {
            log.error("attempt to delete ConditionalNG not in LogixNG: {}", conditionalNG.getSystemName());  // NOI18N
            return;
        }

        boolean found = false;
        // Remove Conditional from this logix
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            if (conditionalNG == entry._conditionalNG) {
                _conditionalNG_Entries.remove(entry);
                found = true;
                break;
            }
        }
        if (!found) {
            log.error("attempt to delete ConditionalNG not in LogixNG: {}", conditionalNG.getSystemName());  // NOI18N
        }
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ boolean isActive() {
        return _enabled && _manager.isActive();
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void execute() {
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            entry._conditionalNG.execute();
        }
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void execute(boolean allowRunDelayed) {
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            entry._conditionalNG.execute(allowRunDelayed);
        }
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ ConditionalNG getConditionalNG() {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ LogixNG getLogixNG() {
        return this;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ final Base getRoot() {
        return this;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ boolean setParentForAllChildren(List<String> errors) {
        boolean result = true;
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            if (entry._conditionalNG != null) {
                entry._conditionalNG.setParent(this);
                result = result && entry._conditionalNG.setParentForAllChildren(errors);
            }
        }
        return result;
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void registerListeners() {
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            entry._conditionalNG.registerListeners();
        }
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void unregisterListeners() {
        for (ConditionalNG_Entry entry : _conditionalNG_Entries) {
            entry._conditionalNG.unregisterListeners();
        }
    }

    protected void printTreeRow(
            PrintTreeSettings settings,
            Locale locale,
            PrintWriter writer,
            String currentIndent,
            MutableInt lineNumber) {

        if (settings._printLineNumbers) {
            writer.append(String.format(PRINT_LINE_NUMBERS_FORMAT, lineNumber.addAndGet(1)));
        }
        writer.append(currentIndent);
        writer.append(getLongDescription(locale));
        writer.println();
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void printTree(
            PrintTreeSettings settings,
            PrintWriter writer,
            String indent,
            MutableInt lineNumber) {

        printTree(settings, Locale.getDefault(), writer, indent, "", lineNumber);
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void printTree(
            PrintTreeSettings settings,
            Locale locale,
            PrintWriter writer,
            String indent,
            MutableInt lineNumber) {

        printTree(settings, locale, writer, indent, "", lineNumber);
    }

    /** {@inheritDoc} */
    @Override
    /*public*/ void printTree(
            PrintTreeSettings settings,
            Locale locale,
            PrintWriter writer,
            String indent,
            String currentIndent,
            MutableInt lineNumber) {

        printTreeRow(settings, locale, writer, currentIndent, lineNumber);

        for (int i=0; i < this.getNumConditionalNGs(); i++) {
            getConditionalNG(i).printTree(settings, locale, writer, indent, currentIndent+indent, lineNumber);
//            writer.println();
        }
    }

    @Override
    /*public*/ Base getDeepCopy(Map<String, String> systemNames, Map<String, String> userNames) {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    @Override
    /*public*/ Base deepCopyChildren(Base original, Map<String, String> systemNames, Map<String, String> userNames) throws JmriException {
        throw new UnsupportedOperationException("Not supported");
    }
#endif
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
    /*public*/ QList<NamedBeanUsageReport*> DefaultLogixNG::getUsageReport(NamedBean* bean) {
        QList<NamedBeanUsageReport*> report = QList<NamedBeanUsageReport*>();
        if (bean != nullptr) {
            getUsageTree(0, bean, report, nullptr);
        }
        return report;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLogixNG::getUsageTree(int level, NamedBean* bean, QList<NamedBeanUsageReport *> report, NamedBean* cdl) {
        log->debug(tr("** %1 :: %2").arg(level).arg(/*this.getClass().getName()*/ metaObject()->className()));

        level++;
        for (int i=0; i < this->getNumConditionalNGs(); i++) {
            getConditionalNG(i)->getUsageTree(level, bean, report, (NamedBean*)getConditionalNG(i));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLogixNG::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
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
