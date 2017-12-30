#ifndef JMRIJTABLEPERSISTENCEMANAGER_H
#define JMRIJTABLEPERSISTENCEMANAGER_H
#include "jtablepersistencemanager.h"
#include "sortorder.h"
#include "tablecolumnmodellistener.h"
#include <QtXml>
#include "rowsorter.h"
#include "rowsorterlistener.h"

class RowSorterEvent;
class QTimer;
class JTable;
class Logger;
class SortKey;
class TableColumnPreferences;
class JTableListener;
class JmriJTablePersistenceManager : public JTablePersistenceManager
{
 Q_OBJECT
public:
#include "sortorder.h"
 JmriJTablePersistenceManager();
 ~JmriJTablePersistenceManager() {}
 JmriJTablePersistenceManager(const JmriJTablePersistenceManager&)  : JTablePersistenceManager() {}
 /*public*/ /*final*/ QString PAUSED;// = "paused";
 /*public*/ /*final*/ static QString TABLES_NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/table-details-4-3-5.xsd"; // NOI18N
 /*public*/ /*final*/ static QString TABLES_ELEMENT;// = "tableDetails"; // NOI18N
 /*public*/ /*final*/ static QString SORT_ORDER;// = "sortOrder"; // NOI18N
 /*public*/ virtual void persist(/*@NonNULL*/ JTable* table); //throws IllegalArgumentException, NullPointerException
 /*public*/ virtual void cacheState(JTable* table);
 /*public*/ TableColumnPreferences* getTableColumnPreferences(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column);
 QT_DEPRECATED /*public*/ QMap<QString, TableColumnPreferences*>* getTableColumnPreferences(/*@NonNULL*/ QString table);
 QT_DEPRECATED /*public*/ void setTableColumnPreferences(QString table, QString column, int order, int width, SortOrder sort, bool hidden);
 /*public*/ void stopPersisting(JTable* table);
 /*public*/ void clearState(JTable* table);
 /*public*/ void initialize(Profile* profile)throw (InitializationException);
 /*public*/ /*synchronized*/ void savePreferences(Profile* profile);
 /*public*/ QSet<QString>* getProvides();
 /*public*/ void resetState(JTable* table);
 /*public*/ void setPaused(bool paused);
 /*public*/ bool isPaused();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 /*private*/ bool paused;// = false;
 /*private*/ bool dirty;// = false;
 Logger* log;

protected:
 /*protected*/ /*final*/ QMap<QString, JTableListener*>* listeners;// = new QMap<QString, JTableListener*>();
 /*protected*/ /*final*/ QMap<QString, QMap<QString, TableColumnPreferences*>*>* columns;// = new QMap<QString, QMap<QString, TableColumnPreferences*>*>();
 /*protected*/ /*final*/ QMap<QString, QList<SortKey*>*>* sortKeys;// = new QMap<QString, QList<SortKey>*>();
 /*protected*/ TableColumnPreferences* getPersistedState(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column);
 /*protected*/ void setPersistedState(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column, int order, int width, SortOrder sort, bool hidden);
 /*protected*/ void setDirty(bool dirty);
 /*protected*/ bool getDirty() ;

 friend class JTableListener;
};
Q_DECLARE_METATYPE(JmriJTablePersistenceManager)

/*public*/ /*final*/ /*static*/ class TableColumnPreferences
{

    int order;
    int width;
    SortOrder sort;
    bool hidden;
 public:
    /*public*/ TableColumnPreferences(int order, int width, SortOrder sort, bool hidden) ;
    /*public*/ int getOrder() ;
    /*public*/ int getWidth();
    /*public*/ SortOrder getSort();
    /*public*/ bool getHidden();
};

/*protected*/ /*final*/ /*static*/ class JTableListener : public RowSorterListener
{
 Q_OBJECT
    /*private*/ /*final*/ JTable* table;
    /*private*/ /*final*/ JmriJTablePersistenceManager* manager;
    /*private*/ QTimer* delay = NULL;
 Logger* log;
public:
    /*public*/ JTableListener(JTable* table, JmriJTablePersistenceManager* manager);
#if 1
    /*public*/ void sorterChanged(RowSorterEvent* e);
#endif
public slots:
    /*public*/ void columnAdded(TableColumnModelEvent* e) ;
    /*public*/ void columnRemoved(TableColumnModelEvent* e);
    /*public*/ void columnMoved(TableColumnModelEvent* e);
    /*public*/ void columnMarginChanged(ChangeEvent* e);
#if 1
    /*public*/ void columnSelectionChanged(ListSelectionEvent* e);
#endif
private:
    /*private*/ JTable* getTable();
    /*private*/ void saveState();

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
 void timerTask();

private slots:
 /*private*/ void saveTask();
 friend class JmriJTablePersistenceManager;
};

#endif // JMRIJTABLEPERSISTENCEMANAGER_H
