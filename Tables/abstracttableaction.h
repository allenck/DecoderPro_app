#ifndef ABSTRACTTABLEACTION_H
#define ABSTRACTTABLEACTION_H

#include "abstractaction.h"
#include "logger.h"
#include "beantableframe.h"
#include "jtable.h"
#include "libtables_global.h"
#include <QSortFilterProxyModel>

class ManagerComboBox;
class AbstractTableTabAction;
class JActionEvent;
class MessageFormat;
//class PrintMode;
class Manager;
class BeanTableFrame;
class BeanTableDataModel;
class LIBTABLESSHARED_EXPORT AbstractTableAction : public AbstractAction
{
    Q_OBJECT
public:
    explicit AbstractTableAction(QObject *parent = 0);
    /*public*/ AbstractTableAction(QString actionName, QObject *parent);
    ~AbstractTableAction() {}
    AbstractTableAction(const AbstractTableAction& that) : AbstractAction(that.text(), that.parent()) {}
    /*public*/ BeanTableDataModel* getTableDataModel();
    virtual /*public*/ void setFrame(BeanTableFrame* frame);
    virtual /*public*/ void addToFrame(BeanTableFrame* f);
//    /*public*/ void addToPanel(AbstractTableTabAction f);
    virtual /*public*/ void setMenuBar(BeanTableFrame* f);
    virtual /*public*/ QWidget* getPanel();
    virtual /*public*/ void dispose();
    virtual /*public*/ QString getClassDescription();
    Q_INVOKABLE virtual /*public*/ void setMessagePreferencesDetails();
    virtual /*public*/ bool includeAddButton();
    virtual /*public*/ void print(JTable::PrintMode mode, QString headerFormat, QString footerFormat);
    virtual /*public*/ void addToPanel(AbstractTableTabAction* f);
    //virtual void buildMenus(BeanTableFrame*) {}
signals:

public slots:
    virtual /*public*/ void actionPerformed(JActionEvent* e = 0);
private:
    static Logger* log;
    JTable* dataTable;
protected:
    /*protected*/ BeanTableDataModel* m;
    virtual /*protected*/ /*abstract*/ void createModel();
    virtual /*protected*/ /*abstract*/ void setTitle();
    /*protected*/ BeanTableFrame* f;
    virtual /*protected*/ void setManager(Manager* man);
    virtual/*protected*/ QString helpTarget();
    virtual /*protected*/ /*abstract*/ QString getClassName();
    /*protected*/ bool _includeAddButton = true;
    /*protected*/ JTable* table;
    /*protected*/ /*@Nonnull*/ QString nextName(/*@Nonnull*/ QString name);
    /*protected*/ void configureManagerComboBox(ManagerComboBox/*<E>*/* comboBox, Manager/*<E>*/* manager,
                                                /*Class<? extends Manager<E>>*/QString managerClass);
    /*protected*/ void removePrefixBoxListener(ManagerComboBox/*<E>*/* prefixBox);
    /*protected*/ void displayHwError(QString curAddress, Exception ex);

  protected slots:
    virtual /*protected*/ /*abstract*/ void addPressed(/*JActionEvent* e = 0*/);
friend class TabbedTableItem;
friend class ATABeanTableFrame;
friend class AbstractTableTabAction;
friend class SensorTableAction;
friend class ListedTableFrame;
friend class OBlockTableActionTest;
};

class ATABeanTableFrame : public BeanTableFrame
{
 Q_OBJECT
 AbstractTableAction* act;
public:
 ATABeanTableFrame(AbstractTableAction* act);
 ATABeanTableFrame(BeanTableDataModel* m, QString helpTarget, JTable* table, AbstractTableAction* act);
 void extras();
 /*public*/ QString getClassName();

};



#endif // ABSTRACTTABLEACTION_H
