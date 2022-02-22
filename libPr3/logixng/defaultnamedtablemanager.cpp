#include "defaultnamedtablemanager.h"
#include "loggerfactory.h"
#include "logixng_manager.h"
#include "abstractnamedtable.h"
#include "defaultinternalnamedtable.h"
#include "defaultanonymoustable.h"
#include "defaultcsvnamedtable.h"
#include "threadingutil.h"
#include "loggingutil.h"
#include "vptr.h"

/**
 * Class providing the basic logic of the NamedTable_Manager interface.
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2020
 */
///*public*/  class DefaultNamedTableManager extends AbstractManager<NamedTable>
//        implements NamedTableManager {



/**
 * {@inheritDoc}
 */
//@Override
/*public*/  int DefaultNamedTableManager::getXMLOrder() const {
    return LOGIXNG_TABLES;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  QChar DefaultNamedTableManager::typeLetter() const {
    return 'Q';
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  Manager::NameValidity DefaultNamedTableManager::validSystemNameFormat(QString systemName) {
    return LogixNG_Manager::validSystemNameFormat(
            NamedTableManager::getSubSystemNamePrefix(), systemName);
//        if (systemName.matches(getSubSystemNamePrefix()+"(:AUTO:)?\\d+")) {
//            return NameValidity.VALID;
//        } else {
//            return NameValidity.INVALID;
//        }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::newCSVTable(QString systemName, QString userName, QString fileName)
        /*throws IllegalArgumentException*/ {

    // Check that NamedTable does not already exist
    NamedTable* x;
    if (userName != "" && userName!=("")) {
        x = getByUserName(userName);
        if (x != nullptr) {
            return nullptr;
        }
    }
    x = getBySystemName(systemName);
    if (x != nullptr) {
        return nullptr;
    }
    // Check if system name is valid
    if (this->validSystemNameFormat(systemName) != NameValidity::VALID) {
        throw new IllegalArgumentException("SystemName " + systemName + " is not in the correct format");
    }
    try {
        // NamedTable does not exist, create a new NamedTable
        x = AbstractNamedTable::loadTableFromCSV_File(systemName, userName, fileName, true);
    } catch (IOException* ex) {
//            Exceptions.printStackTrace(ex);
        log->error("Cannot load table due to I/O error", ex);
        return nullptr;
    }
    // save in the maps
    AbstractManager::Register(x);

    // Keep track of the last created auto system name
    updateAutoNumber(systemName);

    return x;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::newInternalTable(QString systemName, QString userName, int numRows, int numColumns)
        /*throws IllegalArgumentException*/ {

    // Check that NamedTable does not already exist
    NamedTable* x;
    if (userName != "" /*&& !userName.equals("")*/) {
        x = getByUserName(userName);
        if (x != nullptr) {
            return nullptr;
        }
    }
    x = getBySystemName(systemName);
    if (x != nullptr) {
        return nullptr;
    }
    // Check if system name is valid
    if (this->validSystemNameFormat(systemName) != NameValidity::VALID) {
        throw new IllegalArgumentException("SystemName " + systemName + " is not in the correct format");
    }
    // Table does not exist, create a new NamedTable
    x = new DefaultInternalNamedTable(systemName, userName, numRows, numColumns);
    // save in the maps
    AbstractManager::Register(x);

    // Keep track of the last created auto system name
    updateAutoNumber(systemName);

    return x;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  AnonymousTable* DefaultNamedTableManager::newAnonymousTable(int numRows, int numColumns)
        /*throws IllegalArgumentException*/ {

    // Check that NamedTable does not already exist
    // NamedTable does not exist, create a new NamedTable
    return new DefaultAnonymousTable(numRows, numColumns);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::loadTableFromCSVData(
        /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, /*@Nonnull*/ QString text)
        /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException*/ {
    return AbstractNamedTable::loadTableFromCSV_Text(sys, user, text, true);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::loadTableFromCSV(
        /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
        /*@Nonnull*/ QString fileName)
        /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/ {
    return AbstractNamedTable::loadTableFromCSV_File(sys, user, fileName, true);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::loadTableFromCSV(
        /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
        /*@Nonnull*/ File* file)
        /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/ {
    return AbstractNamedTable::loadTableFromCSV_File(sys, user, file, true);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::getNamedTable(QString name) {
    NamedTable* x = getByUserName(name);
    if (x != nullptr) {
        return x;
    }
    return getBySystemName(name);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::getByUserName(QString name) {
    return (NamedTable*)_tuser->value(name)->self();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  NamedTable* DefaultNamedTableManager::getBySystemName(QString name) {
    return (NamedTable*)_tsys->value(name)->self();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  QString DefaultNamedTableManager::getBeanTypeHandled(bool plural)const {
    return plural ? tr("NamedTables") : tr("NamedTable");
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  void DefaultNamedTableManager::deleteNamedTable(NamedTable* x) {
    // delete the NamedTable
    AbstractManager::deregister(x);
    x->dispose();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultNamedTableManager::printTree(PrintWriter* writer, QString indent) {
    printTree(QLocale(), writer, indent);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DefaultNamedTableManager::printTree(QLocale locale, PrintWriter* writer, QString indent) {
    for (NamedBean* nb : AbstractManager::getNamedBeanSet()) {
     NamedTable* namedTable = (NamedTable*)nb->self();
        if (qobject_cast<DefaultCsvNamedTable*>(namedTable)) {
            DefaultCsvNamedTable* csvTable = (DefaultCsvNamedTable*)namedTable;
            writer->write(QString(
                    "Named table: System name: %1, User name: %2, File name: %3, Num rows: %4, Num columns: %5").arg(
                    csvTable->getSystemName(), csvTable->getUserName(),
                    csvTable->getFileName()).arg(csvTable->numRows(), csvTable->numColumns()));
        } if (namedTable != nullptr) {
            writer->write(QString(
                    "Named table: System name: %1, User name: %2, Num rows: %3, Num columns: %4").arg(
                    namedTable->getSystemName(), namedTable->getUserName()).arg(
                    namedTable->numRows(), namedTable->numColumns()));
        } else {
            throw new NullPointerException("namedTable is null");
        }
        writer->println();
        writer->println();
    }
}

/*static*/ /*volatile*/ DefaultNamedTableManager* DefaultNamedTableManager::_instance = nullptr;

//@InvokeOnGuiThread  // this method is not thread safe
/*static*/ /*public*/  DefaultNamedTableManager* DefaultNamedTableManager::instance() {
    if (!ThreadingUtil::isGUIThread()) {
        LoggingUtil::warnOnce(log, "instance() called on wrong thread");
    }

    if (_instance == nullptr) {
        _instance = new DefaultNamedTableManager();
    }
    return (_instance);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  /*Class<NamedTable>*/QString DefaultNamedTableManager::getNamedBeanClass() const {
    return "NamedTable";
}

/**
 * Inform all registered listeners of a vetoable change.If the propertyName
 * is "CanDelete" ALL listeners with an interest in the bean will throw an
 * exception, which is recorded returned back to the invoking method, so
 * that it can be presented back to the user.However if a listener decides
 * that the bean can not be deleted then it should throw an exception with
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
/*public*/  void DefaultNamedTableManager::fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException */{
    PropertyChangeEvent* evt = new PropertyChangeEvent(this, p, old, QVariant());
    for (VetoableChangeListener* vc : vetoableChangeSupport->getVetoableChangeListeners()) {
        vc->vetoableChange(evt);
    }
}

/** {@inheritDoc} */
//@Override
//    @OverridingMethodsMustInvokeSuper
/*public*/  /*final*/ void DefaultNamedTableManager::deleteBean(/*@Nonnull*/ NamedTable* namedTable, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/ {
    // throws PropertyVetoException if vetoed
    fireVetoableChange(property, VPtr<NamedTable>::asQVariant(namedTable));
    if (property == ("DoDelete")) { // NOI18N
        AbstractManager::deregister(namedTable);
        namedTable->dispose();
    }
}


/*private*/ /*final*/ /*static*/ Logger* DefaultNamedTableManager::log = LoggerFactory::getLogger("DefaultNamedTableManager");
