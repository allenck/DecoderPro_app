#ifndef LISTEDTABLEACTION_H
#define LISTEDTABLEACTION_H

#include <QAction>
#include "appslib_global.h"

class LibTables;
class APPSLIBSHARED_EXPORT ListedTableAction : public QAction
{
 Q_OBJECT
public:
 explicit ListedTableAction(QObject *parent = 0);
 /*public*/ ListedTableAction(QString s, QString selection, QObject *parent);
 /*public*/ ListedTableAction(QString s, QString selection, int divider, QObject *parent);
 /*public*/ ListedTableAction(QString s, int divider, QObject *parent);
 /*public*/ ListedTableAction(QString s,QObject *parent);

signals:

public slots:
 /*public*/ void actionPerformed();

private:
 QString gotoListItem;// = null;
 QString title;// = tr("Listed Table Access");
 void common();
 int dividerLocation;// = 0;
 //ListedTableFrame f;
 QString helpTarget();
 LibTables* libTables;
};

#endif // LISTEDTABLEACTION_H
