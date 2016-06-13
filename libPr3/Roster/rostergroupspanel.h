#ifndef ROSTERGROUPSPANEL_H
#define ROSTERGROUPSPANEL_H

#include <QWidget>

class QMenu;
class TreeSelectionListener;
class DefaultTreeModel;
class QTreeView;
class RosterGroupsPanel : public QWidget
{
 Q_OBJECT
public:
 //explicit RosterGroupsPanel(QWidget *parent = 0);
 /*public*/  RosterGroupsPanel(QString defaultRosterGroup = "", QWidget *parent = 0);
 /*public*/  /*final*/ static QString SELECTED_ROSTER_GROUP;// = "selectedRosterGroup";

 /*public*/  void setNewWindowMenuAction(QAction* action);

signals:

public slots:
private:
 /*private*/ static int GROUPS_MENU;// = 1;
 /*private*/ static int ALL_ENTRIES_MENU;// = 2;
 ///*private*/ JScrollPane scrollPane;
 /*private*/ QTreeView* _tree;
 /*private*/ DefaultTreeModel* _model;
// /*private*/ DefaultMutableTreeNode _root;
// /*private*/ DefaultMutableTreeNode _groups;
 ///*private*/ DefaultMutableTreeNode _consists;
 /*private*/ TreeSelectionListener* _TSL;
 /*private*/ QString selectedRosterGroup;// = "";
 /*private*/ QMenu* groupsMenu;
 /*private*/ QMenu* allEntriesMenu;
 /*private*/ QAction* newWindowMenuItemAction;// = null;

};

#endif // ROSTERGROUPSPANEL_H
