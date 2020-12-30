#include "jmrijtablepersistencemanager.h"
#include "logger.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "xtablecolumnmodel.h"
#include <QTimer>
#include "profilemanager.h"
#include "tablecolumnmodelevent.h"
#include "profileutils.h"
#include "auxiliaryconfiguration.h"
#include <QListIterator>
#include "listselectionevent.h"
#include "rowsorterutil.h"
#include "exceptions.h"

JmriJTablePersistenceManager::JmriJTablePersistenceManager() :JTablePersistenceManager()
{
 log = new Logger("JmriJTablePersistenceManager");
 listeners = new QMap<QString, JTableListener*>();
 columns = new QMap<QString, QMap<QString, TableColumnPreferences*>*>();
 sortKeys = new QMap<QString, QList<SortKey*>*>();
 paused = false;
 dirty = false;
 PAUSED = "paused";

}
/**
 * Default implementation of {@link JTablePersistenceManager}.
 *
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class JmriJTablePersistenceManager extends AbstractPreferencesManager implements JTablePersistenceManager, PropertyChangeListener {

/*public*/ /*final*/ /*static*/ QString JmriJTablePersistenceManager::TABLES_NAMESPACE = "http://jmri.org/xml/schema/auxiliary-configuration/table-details-4-3-5.xsd"; // NOI18N
/*public*/ /*final*/ /*static*/ QString JmriJTablePersistenceManager::TABLES_ELEMENT = "tableDetails"; // NOI18N
/*public*/ /*final*/ /*static*/ QString JmriJTablePersistenceManager::SORT_ORDER = "sortOrder"; // NOI18N

/**
 * {@inheritDoc} Persisting a table that is already persisted may cause the
 * persistence state to be updated, but will not cause additional listeners
 * to be added to the table.
 */
//@Override
/*public*/ void JmriJTablePersistenceManager::persist(/*@NonNULL*/ JTable* table) //throws IllegalArgumentException, NullPointerException
{
//    Objects.requireNonNull(table->getName(), "Table name must be nonNULL");
 if ( this->listeners->contains(table->getName()) && this->listeners->value(table->getName())->getTable() != (table))
 {
  throw  IllegalArgumentException("Table name must be unique");
 }
 if (! this->listeners->contains(table->getName())) {
  JTableListener* listener = new JTableListener(table, this);
   this->listeners->insert(table->getName(), listener);
#if 1
  //if (!Arrays.asList(table->getPropertyChangeListeners()).contains(this))

  {
   //table->addPropertyChangeListener(this);
   connect(table, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   //table->addPropertyChangeListener(listener);
   connect(table, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
   table->getColumnModel()->addColumnModelListener(listener);
#if 1
   RowSorter* sorter = table->getRowSorter();
   if (sorter != NULL) {
       sorter->addRowSorterListener(listener);
   }
#endif
   QListIterator<TableColumn*> e = table->getColumnModel()->getColumns();
   while (e.hasNext())
   {
    TableColumn* column = e.next();
    //column.addPropertyChangeListener(listener);
    connect(column, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
    if (column->getIdentifier() == QVariant()) {
        column->setIdentifier(column->getHeaderValue().toString());
    }
   }
  }
#endif
 }
 if ( this->columns->value(table->getName()) == NULL)
 {
  this->cacheState(table);
 }
}
//@Override
/*public*/ void JmriJTablePersistenceManager::stopPersisting(JTable* table) {
    //Objects.requireNonNull(table->getName(), "table name must be nonNULL");
    //JTableListener* listener =  this->listeners->remove(table->getName());
    JTableListener* listener = listeners->value(table->getName());
    listeners->remove(table->getName());
    //table->removePropertyChangeListener(this);
    disconnect(table, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    //table->removePropertyChangeListener(listener);
    disconnect(table, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
    table->getColumnModel()->removeColumnModelListener(listener);
#if 1
    RowSorter* sorter = table->getRowSorter();
    if (sorter != NULL) {
        sorter->removeRowSorterListener(listener);
    }
#endif
    QListIterator<TableColumn*> e = table->getColumnModel()->getColumns();
    while (e.hasNext()) {
        TableColumn* column = e.next();
        //column->removePropertyChangeListener(listener);
        disconnect(column, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
}

//@Override
/*public*/ void JmriJTablePersistenceManager::clearState(JTable* table) {
    //Objects.requireNonNull(table->getName(), "table name must be nonNULL");
     this->columns->remove(table->getName());
     this->dirty = true;
}

//@Override
/*public*/ void JmriJTablePersistenceManager::cacheState(JTable* table) {
    //Objects.requireNonNull(table->getName(), "table name must be nonNULL");
    TableColumnModel* model = table->getColumnModel();
    //Objects.requireNonNull(model, "table " + table->getName() + " has a NULL columnModel");
    RowSorter* sorter = table->getRowSorter();
    //bool isXModel = model instanceof XTableColumnModel;
    bool isXModel = false;
    if(qobject_cast<XTableColumnModel*>(model) != NULL)
       isXModel = true;
    QListIterator<TableColumn*> e = model->getColumns();
    while (e.hasNext()) {
        TableColumn* column = e.next();
        QString name = column->getHeaderValue().toString();
        int index = column->getModelIndex();
        if (isXModel) {
            index = ((XTableColumnModel*) model)->getColumnIndex(column->getIdentifier(), false);
        }
        int width = column->getPreferredWidth();
        bool hidden = false;
        if (isXModel) {
            hidden = !((XTableColumnModel*) model)->isColumnVisible(column);
        }
#if 1
        SortOrder sorted = UNSORTED;
        if (sorter != NULL) {
            sorted = RowSorterUtil::getSortOrder(sorter, index);
            log->trace(tr("Column %1 (model index %2) is %3").arg(name).arg(index).arg(sorted));
        }
         this->setPersistedState(table->getName(), name, index, width, sorted, hidden);
#endif
    }
#if 1
    if (sorter != NULL) {
         this->sortKeys->insert(table->getName(), new QList<SortKey*>(*sorter->getSortKeys()));
    }
#endif
     this->dirty = true;
}

//@Override
/*public*/ void JmriJTablePersistenceManager::resetState(JTable* table) {
    //Objects.requireNonNull(table->getName(), "table name must be nonNULL");
    bool persisting =  this->listeners->contains(table->getName());
    // while setting table state, don't listen to changes in table state
     this->stopPersisting(table);
    TableColumnModel* model = table->getColumnModel();
    //Objects.requireNonNull(model, "table " + table->getName() + " has a NULL columnModel");
#if 1
    RowSorter* sorter = table->getRowSorter();
#endif
    //bool isXModel = model instanceof XTableColumnModel;
    bool isXModel = qobject_cast<XTableColumnModel*>(model) != NULL;

//    QListIterator<TableColumn*> e = QListIterator<TableColumn*>();
//    if (isXModel) {
//        e = ((XTableColumnModel*) model)->getColumns(false);
//    } else {
//        e = model->getColumns();
//    }
    QListIterator<TableColumn*> e = isXModel?((XTableColumnModel*) model)->getColumns(false):model->getColumns();
    while (e.hasNext()) {
        TableColumn* column = e.next();
        if (column->getIdentifier() == QVariant()) {
            column->setIdentifier(column->getHeaderValue().toString());
        }
    }

    QMap<int, QString> indexes = QMap<int, QString>();
    if ( this->columns->value(table->getName()) == NULL) {
         this->columns->insert(table->getName(), new QMap<QString, TableColumnPreferences*>());
    }
    //this->columns->value(table->getName()).entrySet().stream().forEach((entry) ->
    QMap<QString, TableColumnPreferences*>* tableEntry = this->columns->value(table->getName());
    QMapIterator<QString, TableColumnPreferences*> entry(*tableEntry);
    while(entry.hasNext())
    {
     entry.next();
        int index = entry.value()->getOrder();
        indexes.insert(index, entry.key());
    }//);

    // order columns
    for (int i = 0; i < model->getColumnCount(); i++) {
        QString name = indexes.value(i);
        if (name != NULL) {
            int dataModelIndex = -1;
            for (int j = 0; j < model->getColumnCount(); j++) {
                if (table->getColumnName(j) == (name)) {
                    dataModelIndex = j;
                    break;
                }
            }
            if (dataModelIndex != -1 && (dataModelIndex != i)) {
                model->moveColumn(dataModelIndex, i);
            }
        }
    }

    // configure columns
    if (isXModel) {
        e = ((XTableColumnModel*) model)->getColumns(false);
    } else {
        e = model->getColumns();
    }
    while (e.hasNext()) {
        TableColumn* column = e.next();
        QString name = column->getIdentifier().toString();
        TableColumnPreferences* preferences =  this->columns->value(table->getName())->value(name);
        if (preferences != NULL) {
            column->setPreferredWidth(preferences->getWidth());
            if (isXModel) {
                ((XTableColumnModel*) model)->setColumnVisible(column, !preferences->getHidden());
            }
        }
    }
#if 1
    if (sorter != NULL &&  this->sortKeys->value(table->getName()) != NULL) {
        sorter->setSortKeys( this->sortKeys->value(table->getName()));
    }
#endif
    if (persisting) {
         this->persist(table);
    }
}

/**
 * Set dirty (needs to be saved) state. Protected so that subclasses can
 * manipulate this state.
 *
 * @param dirty true if needs to be saved
 */
/*protected*/ void JmriJTablePersistenceManager::setDirty(bool dirty) {
     this->dirty = dirty;
}

/**
 * Get dirty (needs to be saved) state. Protected so that subclasses can
 * manipulate this state.
 *
 * @return true if needs to be saved
 */
/*protected*/ bool JmriJTablePersistenceManager::getDirty() {
    return  this->dirty;
}

//@Override
/*public*/ void JmriJTablePersistenceManager::setPaused(bool paused) {
    bool old =  this->paused;
     this->paused = paused;
    if (paused != old) {
         this->firePropertyChange(PAUSED, old, paused);
    }
    if (!paused &&  this->dirty) {
         this->savePreferences(ProfileManager::getDefault()->getActiveProfile());
    }
}

//@Override
/*public*/ bool JmriJTablePersistenceManager::isPaused() {
    return  this->paused;
}

//@Override
/*public*/ void JmriJTablePersistenceManager::initialize(Profile* profile) throw (InitializationException)
{
//    try {
  QDomElement element = /*JDOMUtil.toJDOMElement*/(ProfileUtils::getUserInterfaceConfiguration(ProfileManager::getDefault()->getActiveProfile())
          ->getConfigurationFragment(TABLES_ELEMENT, TABLES_NAMESPACE, false));
  //element.getChildren("table").stream().forEach((table) ->
  QDomNodeList nl = element.elementsByTagName("table");
  for(int i = 0; i < nl.size(); i++)
  {
   QDomElement table = nl.at(i).toElement();
   QString tableName = table.attribute("name");
   int sortColumn = -1;
#if 1
   SortOrder sortOrder = UNSORTED;
   QDomElement sortElement = table.firstChildElement(SORT_ORDER);
   if (sortElement != QDomElement())
   {
    QList<SortKey*>* keys = new QList<SortKey*>();
    //for (QDomElement sortKey : sortElement.getChildren())
    QDomNodeList snl = sortElement.childNodes();
    for(int j = 0; j < snl.size(); j++)
    {
     QDomElement sortKey = snl.at(j).toElement();
     //sortOrder = SortOrder::valueOf(sortKey.attribute(SORT_ORDER));
     bool ok;
         sortColumn = sortKey.attribute("column").toInt(&ok);
         SortKey* key =  new SortKey(sortColumn, sortOrder);
         keys->append(key);
     if(!ok) {
         log->error("Unable to get sort column as integer");
     }
    }
     this->sortKeys->insert(tableName, keys);
   }
   log->debug(tr("Table %1 column %2 is sorted %3").arg(tableName).arg(sortColumn).arg(sortOrder));
#else
   SortOrder sortOrder = UNSORTED;
#endif
   //for (QDomElement column : table->getChild("columns").getChildren())
   QDomNodeList cl = table.elementsByTagName("columns");
   for(int i = 0; i < cl.size(); i++)
   {
    QDomElement column = cl.at(i).toElement();
   QString columnName = column.attribute("name");
   int order = -1;
   int width = -1;
   bool hidden = false;
//                try {
   bool ok = true, ok1;
  if (column.attribute("order") != NULL) {
      order = column.attribute("order").toInt(&ok1);
      if(!ok1) ok = false;
  }
  if (column.attribute("width") != NULL) {
      width = column.attribute("width").toInt(&ok1);
      if(!ok1) ok = false;
  }
  if (column.attribute("hidden") != NULL) {
      hidden = column.attribute("hidden")=="true"?true:false;
  }
  if(!ok) {
      log->error(tr("Unable to parse column \"%1\"").arg(columnName));
      continue;
  }
  if (sortColumn == order) {
       this->setPersistedState(tableName, columnName, order, width, sortOrder, hidden);
  }
  else
  {
       this->setPersistedState(tableName, columnName, order, width, UNSORTED, hidden);
  }
 }
     }//);
//    } catch (NullPointerException ex) {
//        log.info("Table preferences not found.\nThis is expected on the first time the \"{}\" profile is used on this computer.",
//                ProfileManager.getDefault().getActiveProfile().getName());
//    }
  this->setInitialized(profile, true);
}

//@Override
/*public*/ /*synchronized*/ void JmriJTablePersistenceManager::savePreferences(Profile* /*profile*/)
{
 log->debug(tr("Saving preferences (dirty=%1)...").arg(this->dirty));
 QDomDocument doc;
 QDomElement element = doc.createElementNS(TABLES_NAMESPACE, TABLES_ELEMENT);
 if (! this->columns->isEmpty())
 {
      //this->columns.entrySet().stream().map((entry) -> {
  QMapIterator<QString, QMap<QString, TableColumnPreferences*>*> entry( *this->columns);
  while(entry.hasNext())
  {
   entry.next();
   QDomElement table = doc.createElement("table");
   table.setAttribute("name", entry.key());
   QDomElement columnsElement = doc.createElement("columns");
//            entry.getValue().entrySet().stream().map((column) -> {
   QMapIterator<QString, TableColumnPreferences*> column(*entry.value());
   while(column.hasNext())
   {
    column.next();
    QDomElement columnElement = doc.createElement("column"); columnElement.setAttribute("name", column.key());
    if (column.value()->getOrder() != -1) {
        columnElement.setAttribute("order", (column.value()->getOrder()));
    }
    if (column.value()->getWidth() != -1) {
        columnElement.setAttribute("width", (column.value()->getWidth()));
    }
    columnElement.setAttribute("hidden", (column.value()->getHidden()?"true":"false"));
//       return columnElement;
//            }).forEach((columnElement) -> {
//                columnsElement.addContent(columnElement);
//            });
    columnsElement.appendChild(columnElement);
   }
   table.appendChild(columnsElement);
#if 1 // TODO:
   QList<SortKey*>* keys =  this->sortKeys->value(entry.key());
   if (keys != NULL)
   {
       QDomElement sorter = doc.createElement(SORT_ORDER);
       //keys.stream().forEach((key) -> {
       foreach(SortKey* key, *keys)
       {
        QDomElement sortKeyElement;
           sorter.appendChild(sortKeyElement = doc.createElement("sortKey"));
                   sortKeyElement.setAttribute("column",key->getColumn());
       }//);
       table.appendChild(sorter);
   }
#endif
//            return table;
//        }).forEach((table) -> {
//            element.appendChild(table);
//        });
   element.appendChild(table);
  }
 }
 try {
     ProfileUtils::getUserInterfaceConfiguration(ProfileManager::getDefault()->getActiveProfile())
             ->putConfigurationFragment(/*JDOMUtil.toW3CElement*/(element), false);
 } catch (JDOMException ex) {
     log->error("Unable to save user preferences"/*, ex*/);
 }
 this->dirty = false;
}
#if 0  // done
//@Override
/*@NonNULL*/
/*public*/ Set<Class<?>> getProvides() {
    Set<Class<?>> provides = super.getProvides();
    provides.add(JTablePersistenceManager.class);
    return provides;
}
#else
/*public*/ QSet<QString>* JmriJTablePersistenceManager::getProvides()
{
 QSet<QString>* provides = AbstractPreferencesManager::getProvides();
 provides->insert("JTablePersistenceManager");
 return provides;
}
#endif
/**
 * Transition support for the standard {@link jmri.UserPreferencesManager}
 * instance (a {@link jmri.managers.JmriUserPreferencesManager}) so it does
 * not need to maintain separate knowledge of table column state.
 *
 * @param table  the requested table name
 * @param column the requested column name
 * @return the preferences for the column or NULL if none have been set
 *
 * @throws NullPointerException if either name is NULL
 * @deprecated since 4.5.2
 */
//@Deprecated
//@CheckForNull
/*public*/ TableColumnPreferences* JmriJTablePersistenceManager::getTableColumnPreferences(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column) {
    return  this->getPersistedState(table, column);
}
#if 1
/**
 * Transition support for the standard {@link jmri.UserPreferencesManager}
 * instance (a {@link jmri.managers.JmriUserPreferencesManager}) so it does
 * not need to maintain separate knowledge of table column state.
 *
 * @param table  the table name
 * @param column the column name
 * @param order  order of the column
 * @param width  column width
 * @param sort   how the column is sorted
 * @param hidden true if column is hidden
 * @throws NullPointerException if either name is NULL
 * @deprecated since 4.5.2
 */
//@Deprecated
/*public*/ void JmriJTablePersistenceManager::setTableColumnPreferences(QString table, QString column, int order, int width, SortOrder sort, bool hidden) {
    //Objects.requireNonNull(table, "table name must be nonNULL")
#if 1
    if (sort != UNSORTED) {
        QList<SortKey*>* keys = new QList<SortKey*>();
        keys->append(new SortKey(order, sort));
         this->sortKeys->insert(table, keys);
    }
#endif
     this->setPersistedState(table, column, order, width, sort, hidden);
# endif
}

/**
 * Transition support for the standard {@link jmri.UserPreferencesManager}
 * instance (a {@link jmri.managers.JmriUserPreferencesManager}) so it does
 * not need to maintain separate knowledge of table column state.
 *
 * @param table name of the table
 * @return a map of TableColumnPreferences indexed by column name
 * @throws NullPointerException if table name is NULL
 * @deprecated since 4.5.2
 */
//@Deprecated
/*@NonNULL*/
/*public*/ QMap<QString, TableColumnPreferences*>* JmriJTablePersistenceManager::getTableColumnPreferences(/*@NonNULL*/ QString table) {
    //Objects.requireNonNull(table, "table name cannot be NULL");
    QMap<QString, TableColumnPreferences*>* map =  this->columns->value(table);
    if (map != NULL) {
        return map;
    }
    return new QMap<QString, TableColumnPreferences*>();
}

/**
 * Transition support for {@link jmri.UserPreferencesManager} instances so
 * they do not need to maintain separate knowledge of table column state.
 *
 * @param table  the requested table name
 * @param column the requested column name
 * @throws NullPointerException if either name is NULL
 * @return the preferences for the column or NULL if none have been set
 */
//@CheckForNull
/*protected*/ TableColumnPreferences* JmriJTablePersistenceManager::getPersistedState(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column) {
//    Objects.requireNonNull(table, "table name must be nonNULL");
//    Objects.requireNonNull(column, "column name must be nonNULL");
    QMap<QString, TableColumnPreferences*>* map =  this->columns->value(table);
    if (map != NULL) {
        return map->value(column);
    }
    return NULL;
}

/**
 * Set the persisted state for the given column in the given table-> The
 * persisted state is not saved until
 * {@link #savePreferences(jmri.profile.Profile)} is called.
 *
 * @param table  the table name
 * @param column the column name
 * @param order  order of the column
 * @param width  column width
 * @param sort   how the column is sorted
 * @param hidden true if column is hidden
 * @throws NullPointerException if either name is NULL
 */
/*protected*/ void JmriJTablePersistenceManager::setPersistedState(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column, int order, int width, SortOrder sort, bool hidden) {
    //Objects.requireNonNull(table, "table name must be nonNULL");
    //Objects.requireNonNull(column, "column name must be nonNULL");
    if (! this->columns->contains(table)) {
         this->columns->insert(table, new QMap<QString, TableColumnPreferences*>());
    }
    QMap<QString, TableColumnPreferences*>* columnPrefs =  this->columns->value(table);
    columnPrefs->insert(column, new TableColumnPreferences(order, width, sort, hidden));
     this->dirty = true;
}

//@Override
/*public*/ void JmriJTablePersistenceManager::propertyChange(PropertyChangeEvent* evt)
{
    if (evt->getPropertyName() == ("name")) { // NOI18N
        QString oldName =  evt->getOldValue().toString();
        QString newName =  evt->getNewValue().toString();
        if (oldName != NULL && ! this->listeners->contains(newName)) {
            if (newName != NULL) {
                 this->listeners->insert(newName,  this->listeners->value(oldName));
                 this->columns->insert(newName,  this->columns->value(oldName));
            } else {
                 this->stopPersisting((JTable*) evt->getSource());
            }
             this->listeners->remove(oldName);
             this->columns->remove(oldName);
             this->dirty = true;
        }
    }
}

///*public*/ /*final*/ static class TableColumnPreferences {

//    int order;
//    int width;
//    SortOrder sort;
//    bool hidden;

/*public*/ TableColumnPreferences::TableColumnPreferences(int order, int preferredWidth, SortOrder sort, bool hidden) {
     this->order = order;
     this->preferredWidth = preferredWidth;
     this->sort = sort;
     this->hidden = hidden;
}

/*public*/ int TableColumnPreferences::getOrder() {
    return  this->order;
}

/*public*/ int TableColumnPreferences::getWidth() {
    return  this->preferredWidth;
}

/*public*/ SortOrder TableColumnPreferences::getSort() {
    return  this->sort;
}

/*public*/ bool TableColumnPreferences::getHidden() {
    return  this->hidden;
}
//};

///*protected*/ /*final*/ static class JTableListener implements PropertyChangeListener, RowSorterListener, TableColumnModelListener {

//    /*private*/ /*final*/ JTable* table;
//    /*private*/ /*final*/ JmriJTablePersistenceManager manager;
//    /*private*/ Timer delay = NULL;

/*public*/ JTableListener::JTableListener(JTable* table, JmriJTablePersistenceManager* manager) {
log = new Logger("JTableListener");
     this->table = table;
     this->manager = manager;
 connect(table->getColumnModel(),SIGNAL(notifycolumnadded(TableColumnModelEvent*)), this, SLOT(columnAdded(TableColumnModelEvent*)));
   connect(table->getColumnModel(),SIGNAL(notifycolumnremoved(TableColumnModelEvent*)), this, SLOT(columnRemoved(TableColumnModelEvent*)));
   connect(table->getColumnModel(),SIGNAL(notifycolumnmoved(TableColumnModelEvent*)), this, SLOT(columnMoved(TableColumnModelEvent*)));

}

/*private*/ JTable* JTableListener::getTable() {
    return  this->table;
}

//@Override
/*public*/ void JTableListener::propertyChange(PropertyChangeEvent* evt)
{
    //if (evt.getSource() instanceof JTable)
 if(qobject_cast<JTable*>(evt->getSource()) != nullptr)
 {
  if(!(evt->getPropertyName() ==  "name" || // NOI18N
     evt->getPropertyName() == "Frame.active" || // NOI18N
     evt->getPropertyName() == "ancestor"|| // NOI18N
     evt->getPropertyName() == "selectionForeground" || // NOI18N
     evt->getPropertyName() == "selectionBackground" || // NOI18N
     evt->getPropertyName() == "JComponent_TRANSFER_HANDLER" || // NOI18N
     evt->getPropertyName() == "transferHandler"))  // NOI18N
   // log unrecognized events
   log->trace(tr("Got propertyChange %1 for table %2 (\"%3\" -> \"%4\")").arg(evt->getPropertyName()).arg(this->table->getName()).arg(evt->getOldValue().toString()).arg(evt->getNewValue().toString()));
 }
 //else if (evt.getSource() instanceof TableColumn)
 else if(qobject_cast<TableColumn*>(evt->getSource())!= nullptr)
 {
        TableColumn* column = ((TableColumn*) evt->getSource());
        QString name = column->getIdentifier().toString();
        //switch (evt->getPropertyName()) {
            if(evt->getPropertyName() == "preferredWidth")
            {
                 this->saveState();
            }
//                case "width": // NOI18N
//                    break;
//                default:
//                    // log unrecognized events
     log->trace(tr("Got propertyChange %1 for column %2 (\"%3\" -> \"%4\")").arg(evt->getPropertyName()).arg(name).arg(evt->getOldValue().toString()).arg(evt->getNewValue().toString()));
//            }
    }
}
#if 1
//@Override
/*public*/ void JTableListener::sorterChanged(RowSorterEvent* e) {
    if (e->getType() == RowSorterEvent::SORT_ORDER_CHANGED) {
         this->saveState();
        log->debug(tr("Sort order changed for %1").arg(this->table->getName()));
    }
}
#endif
//@Override
/*public*/ void JTableListener::columnAdded(TableColumnModelEvent* e) {
     this->saveState();
    log->debug(tr("Got columnAdded for %1 (%2 -> %3)").arg(this->table->getName()).arg(e->getFromIndex()).arg(e->getToIndex()));
}

//@Override
/*public*/ void JTableListener::columnRemoved(TableColumnModelEvent* e) {
     this->manager->clearState( this->table); // deletes column data from xml file
     this->saveState();
    log->debug(tr("Got columnRemoved for %1 (%2 -> %3)").arg(this->table->getName()).arg(e->getFromIndex()).arg(e->getToIndex()));
}

//@Override
/*public*/ void JTableListener::columnMoved(TableColumnModelEvent* e) {
    if (e->getFromIndex() != e->getToIndex())
    {
         this->saveState();
        log->debug(tr("Got columnMoved for %1 (%2 -> %3)").arg(this->table->getName()).arg(e->getFromIndex()).arg(e->getToIndex()));
    }
}

//@Override
/*public*/ void JTableListener::columnMarginChanged(ChangeEvent* e) {
    // do nothing - we don't retain margins
    log->trace(tr("Got columnMarginChanged for %1").arg(this->table->getName()));
}

//@Override
/*public*/ void JTableListener::columnSelectionChanged(ListSelectionEvent* e) {
    // do nothing - we don't retain selections
    log->trace(tr("Got columnSelectionChanged for %1 (%2 -> %3)").arg(this->table->getName()).arg(e->getFirstIndex()).arg( e->getLastIndex()));
}

/**
 * Saves the state after a 1/2 second delay. Every time the listener
 * triggers this method any pending save is canceled and a new delay is
 * created. This is intended to prevent excessive writes to disk while
 * (for example) a column is being resized or moved. Calling
 * {@link JmriJTablePersistenceManager#savePreferences(jmri.profile.Profile)}
 * is not subject to this timer.
 */
/*private*/ void JTableListener::saveState() {

    if (delay != NULL) {
        delay->stop();
        delay = NULL;
    }
    delay = new QTimer();
#if 0
    delay.schedule(new TimerTask() {
        //@Override
        /*public*/ void run() {
            JTableListener. this->manager.cacheState(JTableListener. this->table);
            if (!JTableListener. this->manager.paused && JTableListener. this->manager.dirty) {
                JTableListener. this->manager.savePreferences(ProfileManager.getDefault().getActiveProfile());
            }
        }
    }, 500); // milliseconds
#endif
    delay->singleShot(500, this, SLOT(timerTask()));
}

/*public*/ void JTableListener::timerTask() //SLOT
{
  this->manager->cacheState( this->table);
  if (! this->manager->paused &&  this->manager->dirty) {
       this->manager->savePreferences(ProfileManager::getDefault()->getActiveProfile());
  }
}

/*private*/ void JTableListener::saveTask()
{
  this->manager->cacheState( this->table);
 if (! this->manager->paused &&  this->manager->dirty) {
      this->manager->savePreferences(ProfileManager::getDefault()->getActiveProfile());
 }
}

//};
