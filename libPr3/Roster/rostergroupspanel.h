#ifndef ROSTERGROUPSPANEL_H
#define ROSTERGROUPSPANEL_H

#include <QWidget>
#include "actionlistener.h"
#include "libPr3_global.h"
#include <QModelIndex>
#include "treeselectionlistener.h"

class TreeSelectionEvent;
class JmriAbstractAction;
class PropertyChangeSupport;
class PropertyChangeEvent;
class DefaultMutableTreeNode;
class JTree;
class QSignalMapper;
class QToolBar;
//class QScrollArea;
class QMenu;
class MyTreeSelectionListener;
class DefaultTreeModel;
class QTreeView;
class LIBPR3SHARED_EXPORT RosterGroupsPanel : public QWidget
{
 Q_OBJECT
public:
 //explicit RosterGroupsPanel(QWidget *parent = 0);
 /*public*/  RosterGroupsPanel(QString defaultRosterGroup = "", QWidget *parent = 0);
 /*public*/  /*final*/ static QString SELECTED_ROSTER_GROUP;// = "selectedRosterGroup";
 /*public*/  /*final*/ void setSelectedRosterGroup(QString group);

 /*public*/  void setNewWindowMenuAction(JmriAbstractAction* action);
 /*public*/  virtual QString getSelectedRosterGroup();
 /*public*/  /*final*/ void setGroupsMenu(QMenu* menu);
 /*public*/  QMenu* getGroupsMenu();
 /*public*/  /*final*/ void setAllEntriesMenu(QMenu* menu);
 /*public*/  QMenu* getAllEntriesMenu();
 /*public*/  /*final*/ JTree* getTree();
 /*public*/  bool isSelectionUserDefinedRosterGroup();
 PropertyChangeSupport* pcs;
 /*public*/  JmriAbstractAction* getNewWindowMenuAction();

signals:
 void propertyChange(PropertyChangeEvent *e);

public slots:
 /*public*/  void on_propertyChange(PropertyChangeEvent* e);
 void on_addGroupBtn();
 void on_actButton_Clicked();
 void on_clicked(QModelIndex);

private:
 /*private*/ static int GROUPS_MENU;// = 1;
 /*private*/ static int ALL_ENTRIES_MENU;// = 2;
 ///*private*/ QScrollArea* scrollPane;
 /*private*/ JTree* _tree;
 /*private*/ DefaultTreeModel* _model;
 /*private*/ DefaultMutableTreeNode* _root;
 /*private*/ DefaultMutableTreeNode* _groups;
 ///*private*/ DefaultMutableTreeNode _consists;
 /*private*/ MyTreeSelectionListener* _TSL;
 /*private*/ QString selectedRosterGroup;// = "";
 /*private*/ QMenu* groupsMenu;
 /*private*/ QMenu* allEntriesMenu;
 /*private*/ JmriAbstractAction* newWindowMenuItemAction;// = null;
 /*private*/ QWidget* getButtons();
 /*private*/ QMenu* defaultMenu(int menu);
 QSignalMapper* menuMapper;
 /*private*/ void setSelectionToGroup(QString group);
 /*private*/ DefaultTreeModel* getModel();
 /*private*/ DefaultMutableTreeNode* getRoot();
 /*private*/ void setRosterGroups(DefaultMutableTreeNode* root);

protected:
 /*protected*/ void firePropertyChangeAsRGP(QString propertyName, QVariant oldValue, QVariant newValue);


 friend class MenuActionListener;
 friend class MyTreeSelectionListener;
};

class MenuActionListener : public QObject
{
 Q_OBJECT
 RosterGroupsPanel* panel;
 QSignalMapper* mapper;
public:
 MenuActionListener(RosterGroupsPanel* panel);
 void addAction(QAction* act);
 public slots:
    //@Override
    /*public*/  void actionPerformed(QObject * act);
};

/*public*/  class LIBPR3SHARED_EXPORT MyTreeSelectionListener : public TreeSelectionListener//implements javax.swing.event.TreeSelectionListener {
{
 Q_OBJECT
 RosterGroupsPanel* panel;
public:
 MyTreeSelectionListener(RosterGroupsPanel* panel);
    //@Override
    /*public*/  void valueChanged(TreeSelectionEvent* e = 0);
};



#endif // ROSTERGROUPSPANEL_H
