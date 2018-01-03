#ifndef LISTEDTABLEACTION_H
#define LISTEDTABLEACTION_H

#include "abstractaction.h"
#include "libtables_global.h"

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
};

#endif // LISTEDTABLEACTION_H
