#ifndef JMRIJTABLEPERSISTENCEMANAGER_H
#define JMRIJTABLEPERSISTENCEMANAGER_H
#include "jtablepersistencemanager.h"
#include "sortorder.h"
#include "tablecolumnmodellistener.h"
#include <QtXml>
#include "rowsorter.h"
#include "rowsorterlistener.h"
#include "propertychangelistener.h"

class RowSorterEvent;
class QTimer;
class JTable;
class Logger;
class SortKey;
class TableColumnPreferences;
class JTableListener;
class JmriJTablePersistenceManager : public AbstractPreferencesManager, public JTablePersistenceManager, public PropertyChangeListener
{
 Q_OBJECT
Q_INTERFACES(JTablePersistenceManager PropertyChangeListener)
public:
#include "sortorder.h"
 JmriJTablePersistenceManager(QObject* parent = nullptr);
 ~JmriJTablePersistenceManager() {}
 JmriJTablePersistenceManager(const JmriJTablePersistenceManager&)  : AbstractPreferencesManager() {}
 /*public*/ /*final*/ QString PAUSED;// = "paused";
 /*public*/ /*final*/ static QString TABLES_NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/table-details-4-3-5.xsd"; // NOI18N
 /*public*/ /*final*/ static QString TABLES_ELEMENT;// = "tableDetails"; // NOI18N
 /*public*/ /*final*/ static QString SORT_ORDER;// = "sortOrder"; // NOI18N
 /*public*/ virtual void persist(/*@NonNULL*/ JTable* table, bool resetState =false)override ; //throws IllegalArgumentException, NullPointerException
 /*public*/ virtual void cacheState(JTable* table) override;
 /*public*/ TableColumnPreferences* getTableColumnPreferences(/*@NonNULL*/ QString table, /*@NonNULL*/ QString column);
 QT_DEPRECATED /*public*/ QMap<QString, TableColumnPreferences*>* getTableColumnPreferences(/*@NonNULL*/ QString table);
 QT_DEPRECATED /*public*/ void setTableColumnPreferences(QString table, QString column, int order, int width, SortOrder sort, bool hidden);
 /*public*/ void stopPersisting(JTable* table) override;
 /*public*/ void clearState(JTable* table) override;
 /*public*/ void initialize(Profile* profile)throw (InitializationException) override;
 /*public*/ /*synchronized*/ void savePreferences(Profile* profile) override;
 /*public*/ QSet<QString> getProvides() override;
 /*public*/ void resetState(JTable* table) override;
 /*public*/ void setPaused(bool paused) override;
 /*public*/ bool isPaused() override;

 QObject* self() override {return (QObject*)this;}
 QObject* pself() override{return (QObject*)this;}

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt) override;

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
    int preferredWidth;
    SortOrder sort;
    bool hidden;
 public:
    /*public*/ TableColumnPreferences(int order, int preferredWidth, SortOrder sort, bool hidden) ;
    /*public*/ int getOrder() ;
    /*public*/ int getWidth();
    /*public*/ SortOrder getSort();
    /*public*/ bool getHidden();
};

/*protected*/ /*final*/ /*static*/ class JTableListener : public QObject, public RowSorterListener
{
 Q_OBJECT
  Q_INTERFACES(RowSorterListener)
    /*private*/ /*final*/ JTable* table;
    /*private*/ /*final*/ JmriJTablePersistenceManager* manager;
    /*private*/ QTimer* delay = NULL;
 Logger* log;
 QObject* self() {return (QObject*)this;}
 QObject* pself() override{return (QObject*)this;}

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
