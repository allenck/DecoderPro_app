#ifndef LISTEDTABLEACTION_H
#define LISTEDTABLEACTION_H

#include "abstractaction.h"
#include "libtables_global.h"
#include "runnable.h"
#include "listedtableframe.h"

class ListedTableFrame;
class LibTables;
class LIBTABLESSHARED_EXPORT ListedTableAction : public AbstractAction
{
 Q_OBJECT
public:
 explicit ListedTableAction(QObject *parent = 0);
 /*public*/ ListedTableAction(QString s, QString selection, QObject *parent);
 /*public*/ ListedTableAction(QString s, QString selection, int divider, QObject *parent);
 /*public*/ ListedTableAction(QString s, int divider, QObject *parent);
 /*public*/ ListedTableAction(QString s,QObject *parent);
 ~ListedTableAction() {}
 ListedTableAction(const ListedTableAction&) : AbstractAction() {}
 /*public*/ void addToFrame(ListedTableFrame* f);

signals:

public slots:
 /*public*/ void actionPerformed();

private:
 QString gotoListItem;// = null;
 QString title;// = tr("Listed Table Access");
 void common();
 int dividerLocation;// = 0;
 ListedTableFrame* f;
 QString helpTarget();
 LibTables* libTables;

 friend class LTARunnable;
};

class LTARunnable : public Runnable
{
 Q_OBJECT
 ListedTableAction* lta;
public:
 LTARunnable(ListedTableAction* lta) { this->lta = lta;}
public slots:
 /*public*/ void run() {
     lta->f = new ListedTableFrame(lta->title);
     lta->f->initComponents();
     lta->addToFrame(lta->f);

//     try {
//         javax.swing.SwingUtilities.invokeAndWait(()->{
     dispatchToMainThread([&]{
             lta->f->gotoListItem(lta->gotoListItem);
             lta->f->pack();
             lta->f->setDividerLocation(lta->dividerLocation);
             lta->f->setVisible(true);
     });
//         });
//     } catch (java.lang.reflect.InvocationTargetException ex) {
//         log.error("failed to set ListedTable visible", ex );
//     } catch (InterruptedException ex) {
//         log.error("interrupted while setting ListedTable visible", ex );
//     }
 }
};

#endif // LISTEDTABLEACTION_H
