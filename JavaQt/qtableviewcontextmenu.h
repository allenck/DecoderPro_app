#ifndef QTABLEVIEWCONTEXTMENU_H
#define QTABLEVIEWCONTEXTMENU_H
#include <QTableView>
#include "javaqt_global.h"

class RosterEntry;
class QMenu;
class JAVAQTSHARED_EXPORT QTableViewContextMenu : public QTableView
{
public:
 QTableViewContextMenu(QWidget* parent = 0);


private:
 void contextMenuEvent(QContextMenuEvent *);
 QAction* contextService;
 QAction* contextOps;
 QAction* contextEdit;
 RosterEntry* re;
 bool serviceSelected, opsSelected, editSelected;
signals:
 void callMenu(int);
 QString selectedRosterGroup();

protected slots:
 /*protected*/ void showPopup(int row);

};

#endif // QTABLEVIEWCONTEXTMENU_H
