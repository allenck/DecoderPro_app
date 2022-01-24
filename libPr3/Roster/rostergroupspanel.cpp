#include "rostergroupspanel.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QToolBar>
#include "fileutil.h"
#include <QSignalMapper>
#include <QMenu>
#include "fileutil.h"
#include <QIcon>
#include <QUrl>
#include "jtree.h"
#include "roster.h"
#include "defaultmutabletreenode.h"
#include "defaulttreemodel.h"
#include "swingpropertychangesupport.h"
#include "flowlayout.h"
#include <QToolButton>
#include "createrostergroupaction.h"
#include "treepath.h"
#include <action.h>
#include "fullbackupexportaction.h"
#include "fullbackupimportaction.h"
#include <QMessageBox>
#include "renamerostergroupaction.h"
#include "copyrostergroupaction.h"
#include "deleterostergroupaction.h"
#include "treenode.h"
#include <QList>
#include "defaulttreeselectionmodel.h"
#include "treeselectionevent.h"

//RosterGroupsPanel::RosterGroupsPanel(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * A JPanel that lists Roster Groups
 * <p>
 * This panel contains a fairly self-contained display of Roster Groups that
 * allows roster groups to be fully manipulated through context menus.
 *
 * @author Randall Wood Copyright (C) 2011
 * @see jmri.jmrit.roster.Roster
 */
///*public*/  class RosterGroupsPanel extends JPanel implements RosterGroupSelector {

/**
 *
 */
//private static final long serialVersionUID = 4617322485702894536L;
/**
 * Property change listeners can listen for property changes with this name
 * from this object to take action when a user selects a roster group.
 */

/**
 * Create a RosterGroupsPanel with default settings
 */
///*public*/  RosterGroupsPanel(QWidget *parent) :
//  QWidget(parent) {
//   // this(NULL);
//}
/*public*/  /*final*/ /*static*/ QString RosterGroupsPanel::SELECTED_ROSTER_GROUP = "selectedRosterGroup";
/*private*/ /*static*/ int RosterGroupsPanel::GROUPS_MENU = 1;
/*private*/ /*static*/ int RosterGroupsPanel::ALL_ENTRIES_MENU = 2;


/**
 * Create a RosterGroupTreePane with the defaultRosterGroup selected.
 *
 * @param defaultRosterGroup
 */
/*public*/  RosterGroupsPanel::RosterGroupsPanel(QString defaultRosterGroup, QWidget *parent) :
    QWidget(parent)
{
 _tree = NULL;
 _model = NULL;
 _root = NULL;
 newWindowMenuItemAction = NULL;
 groupsMenu = NULL;
 allEntriesMenu = NULL;
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 //this->scrollPane = new QScrollArea(/*getTree()*/);
//    this.scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
    setGroupsMenu(defaultMenu(GROUPS_MENU));
    setAllEntriesMenu(defaultMenu(ALL_ENTRIES_MENU));
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(/*new BorderLayout()*/ layout);
    //add(scrollPane, BorderLayout.CENTER);
    layout->addWidget(/*scrollPane*/getTree(),0, Qt::AlignCenter);
    //add(getButtons(), BorderLayout.SOUTH);
    layout->addWidget(getButtons(),0, Qt::AlignBottom);

    setSelectedRosterGroup(defaultRosterGroup);
    adjustSize();
}

/**
 * Get the selected roster group.
 *
 * @return The selected roster group
 */
//@Override
/*public*/  QString RosterGroupsPanel::getSelectedRosterGroup() {
    return selectedRosterGroup;
}

/**
 * Set the selected roster group.
 * <p>
 * If the group is <code>NULL</code>, the selected roster group is set to
 * "All Entries".
 *
 * @param group The name of the group to set the selection to.
 */
/*public*/  /*final*/ void RosterGroupsPanel::setSelectedRosterGroup(QString group) {
    if (group == "" ? selectedRosterGroup != "" : group!=(selectedRosterGroup)) {
        QString oldGroup = selectedRosterGroup;
        selectedRosterGroup = group;
        setSelectionToGroup(group);
        pcs->firePropertyChange(SELECTED_ROSTER_GROUP, oldGroup, group);
    }
}

/**
 * Is the selected roster group user or system defined.
 *
 * @return flag indicating current selection is a user defined roster group.
 */
/*public*/  bool RosterGroupsPanel::isSelectionUserDefinedRosterGroup() {
    return (selectedRosterGroup != "" && selectedRosterGroup!=(Roster::ALLENTRIES));
}

/**
 * Set the context menu for Roster Groups
 *
 * @param menu The new menu for Roster Groups.
 */
/*public*/  /*final*/ void RosterGroupsPanel::setGroupsMenu(QMenu* menu) {
    this->groupsMenu = menu;
}

/**
 * Get the context menu for Roster Groups
 *
 * @return The current groups menu.
 */
/*public*/  QMenu* RosterGroupsPanel::getGroupsMenu() {
    return this->groupsMenu;
}

/**
 * Set the context menu for the "All Entries" roster group
 *
 * @param menu The new menu for All Entries.
 */
/*public*/  /*final*/ void RosterGroupsPanel::setAllEntriesMenu(QMenu* menu) {
    this->allEntriesMenu = menu;
}

/**
 * Get the context menu for "All Entries"
 *
 * @return The menu for All Entries.
 */
/*public*/  QMenu* RosterGroupsPanel::getAllEntriesMenu() {
    return this->allEntriesMenu;
}

/**
 * Set an action that the menu item "Open in New Window" will trigger.
 * <p>
 * Set a {@link JmriAbstractAction} that the "Open in New Window" menu item
 * will trigger. <code>NULL</code> will remove the "Open in New Window" menu
 * item from context menus. The "Open in New Window" menu item will be added
 * or removed from the menu as appropriate.
 * <p>
 * If the action you pass has access to the RosterGroupPanel, it may call
 * RosterGroupPanel.getSelectedRosterGroup to determine which group to open
 * in the new window, otherwise it must accept a String defining the group
 * in JmriAbstractAction.setParameter(String, String).
 *
 * @param action - An action that can work on the current selection
 */
/*public*/  void RosterGroupsPanel::setNewWindowMenuAction(JmriAbstractAction* action)
{
#if 1
 if (action != NULL)
 {
  if (newWindowMenuItemAction == NULL)
  {
   MenuActionListener* ml = new MenuActionListener(this);
      QAction* mi = new QAction(tr("Open in New Window"), this);
//      mi.addActionListener(ml);
//      mi.setActionCommand("newWindow");
      mi->setProperty("action", "newWindow");
      //groupsMenu->insert(mi, 0);
        groupsMenu->addAction(mi);
        ml->addAction(mi);
      //groupsMenu.insert(new JSeparator(), 1);
      groupsMenu->addSeparator();
      // create the menu item twice because a menu item can only
      // be attached to a single menu
      //mi = new JMenuItem(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("MenuOpenInNewWindow"));
      mi = new QAction(tr("Open in New Window"), this);mi->setProperty("action", "newWindow");
//      mi.addActionListener(ml);
      groupsMenu->addAction(mi);
//      mi.setActionCommand("newWindow");
      //allEntriesMenu.insert(mi, 0);
      allEntriesMenu->addAction(mi);
      ml->addAction(mi);
      //allEntriesMenu.insert(new JSeparator(), 1);
      allEntriesMenu->addSeparator();
  }
  newWindowMenuItemAction = action;
 } else if (newWindowMenuItemAction != NULL)
 {
//     groupsMenu->remove(0);
//     groupsMenu.remove(0);
  groupsMenu->clear();
//     allEntriesMenu.remove(0);
//     allEntriesMenu.remove(0);
  allEntriesMenu->clear();
  newWindowMenuItemAction = NULL;
 }
// groupsMenu.revalidate();
// allEntriesMenu.revalidate();
#endif
}
#if 1
/**
 * The action triggered by the "Open in New Window" menu item.
 *
 * @return A JmriAbstractAction or NULL
 */
/*public*/  JmriAbstractAction* RosterGroupsPanel::getNewWindowMenuAction() {
    return newWindowMenuItemAction;
}
#endif
//@SuppressWarnings("unchecked")
/*private*/ void RosterGroupsPanel::setSelectionToGroup(QString group)
{
#if 1
    _tree->removeTreeSelectionListener(_TSL);
    if (group == NULL || group==(Roster::ALLENTRIES) || group==(""))
    {
     QList<TreeNode*>* l = _model->getPathToRoot(_groups->getFirstChild());
     QVector<QObject*>* ol = new QVector<QObject*>();
     foreach(TreeNode* n, *l)
      ol->append((QObject*)n);
     _tree->setSelectionPath(new TreePath(ol));
    } else {
//        for (TreeNode n : new IterableEnumeration<TreeNode>(_groups.children())) {
     //foreach(TreeNode* n, *_groups->children())
     while(_groups->children()->hasNext())
     {
      DefaultMutableTreeNode* n= (DefaultMutableTreeNode*)_groups->children()->next();
     if (n->toString()==(group))
     {
      QList<TreeNode*>* l = _model->getPathToRoot(n);
      QVector<QObject*>* ol = new QVector<QObject*>();
      foreach(TreeNode* n, *l)
        ol->append((QObject*)n);
      _tree->setSelectionPath(new TreePath(/*_model->getPathToRoot(n)*/ ol));
     }
  }
 }
 _tree->addTreeSelectionListener(_TSL);
#endif
}

/*private*/ QWidget* RosterGroupsPanel::getButtons() {
 QWidget* controls = new QWidget;
 FlowLayout* layout = new FlowLayout();
 controls->setLayout(layout);
//    QToolBar* controls = new QToolBar();
//    controls.setLayout(new GridLayout(1, 0, 0, 0));
//    controls.setFloatable(false);
//    /*final*/ JToggleButton addGroupBtn = new JToggleButton(new ImageIcon(FileUtil.findURL("resources/icons/misc/gui3/Add.png")), false);
    QToolButton* addGroupBtn = new QToolButton();
    addGroupBtn->setIcon(QIcon(":/resources/icons/misc/gui3/Add.png"));
    addGroupBtn->setText("Add");
    layout->addWidget(addGroupBtn);
//    /*final*/ JToggleButton actGroupBtn = new JToggleButton(new ImageIcon(FileUtil.findURL("resources/icons/misc/gui3/Action.png")), false);
//    QAction* actGroupBtn = controls->addAction(QIcon(":/resources/icons/misc/gui3/Action.png"), "Action");
    QToolButton* actGroupButton = new QToolButton();
    actGroupButton->setIcon(QIcon(":/resources/icons/misc/gui3/Action.png"));
    actGroupButton->setText("Action");
    layout->addWidget(actGroupButton);
//    addGroupBtn.addActionListener(new ActionListener() {
//        //@Override
//        /*public*/  void actionPerformed(ActionEvent e) {
//            new CreateRosterGroupAction("", scrollPane.getTopLevelAncestor()).actionPerformed(e);
//            addGroupBtn.setSelected(false);
//        }
//    });
 connect(addGroupBtn, SIGNAL(clicked(bool)), this, SLOT(on_addGroupBtn()));
 connect(actGroupButton, SIGNAL(clicked(bool)), this, SLOT(on_actButton_Clicked()));
//    actGroupBtn.addItemListener(new ItemListener() {
//        //@Override
//        /*public*/  void itemStateChanged(ItemEvent ie) {
//            if (ie.getStateChange() == ItemEvent.SELECTED) {
//                TreePath g = new TreePath(_model.getPathToRoot(_groups));
//                if (_tree->getSelectionPath() != NULL) {
//                    if (_tree->getSelectionPath().getLastPathComponent().toString()==(Roster.ALLENTRIES)) {
//                        allEntriesMenu.show((JComponent) ie.getSource(), actGroupBtn.getX() - actGroupBtn.getWidth(), actGroupBtn.getY() - allEntriesMenu.getPreferredSize().height);
//                    } else if (g.isDescendant(_tree->getSelectionPath()) && !_tree->getSelectionPath().isDescendant(g)) {
//                        groupsMenu.show((JComponent) ie.getSource(), actGroupBtn.getX() - actGroupBtn.getWidth(), actGroupBtn.getY() - groupsMenu.getPreferredSize().height);
//                    }
//                }
//            }
//        }
//    });
//    PopupMenuListener PML = new PopupMenuListener() {

//        //@Override
//        /*public*/  void popupMenuWillBecomeVisible(PopupMenuEvent pme) {
//            // do nothing
//        }

//        //@Override
//        /*public*/  void popupMenuWillBecomeInvisible(PopupMenuEvent pme) {
//            actGroupBtn.setSelected(false);
//        }

//        //@Override
//        /*public*/  void popupMenuCanceled(PopupMenuEvent pme) {
//            actGroupBtn.setSelected(false);
//        }
//    };
//    allEntriesMenu.addPopupMenuListener(PML);
//    groupsMenu.addPopupMenuListener(PML);
    //controls.add(addGroupBtn);
    //controls.add(actGroupBtn);
    return controls;
}
void RosterGroupsPanel::on_actButton_Clicked()
{
 //if (ie.getStateChange() == ItemEvent.SELECTED) {
  //TreePath* g = new TreePath(_model->getPathToRoot(_groups));
 QList<TreeNode*>* l = _model->getPathToRoot(_groups);
 QVector<QObject*>* ol = new QVector<QObject*>();
 foreach (TreeNode* n, *l) {
  ol->append((QObject*)n);
 }
 TreePath* g = new TreePath(ol);
  if (_tree->getSelectionPath() != NULL)
  {
#if 1
//   if (_tree->getSelectionPath()->getLastPathComponent().toString()==(Roster::_ALLENTRIES))
   if(_tree->getSelectionPath()->toString() ==(Roster::ALLENTRIES))
   {
//    allEntriesMenu->show((JComponent) ie.getSource(), actGroupBtn.getX() - actGroupBtn.getWidth(), actGroupBtn.getY() - allEntriesMenu.getPreferredSize().height);
    allEntriesMenu->exec(QCursor::pos());
   }
   else
#endif
   if (g->isDescendant(_tree->getSelectionPath()) && !_tree->getSelectionPath()->isDescendant(g))
   {
//    groupsMenu.show((JComponent) ie.getSource(), actGroupBtn.getX() - actGroupBtn.getWidth(), actGroupBtn.getY() - groupsMenu.getPreferredSize().height);
    groupsMenu->exec();
   }
  }
 //}
//}
}

void RosterGroupsPanel::on_addGroupBtn()
{
  CreateRosterGroupAction* act= new CreateRosterGroupAction("", this);
 act->actionPerformed();
}

#if 0 // not needed here since QTreeView handles scrolling
/**
 * Get a JScrollPane containing the JTree that does not display horizontal
 * scrollbars.
 *
 * @return The internal JScrollPane
 */
/*public*/  JScrollPane getScrollPane() {
    return this.scrollPane;
}
#endif
/**
 * Get the JTree containing the roster groups.
 *
 * @return The internal JTree
 */
/*public*/  /*final*/ JTree* RosterGroupsPanel::getTree() {
    if (_tree == NULL)
    {
     TreeSelectionModel* sm = new DefaultTreeSelectionModel();
//        DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer();
     sm->setSelectionMode(TreeSelectionModel::SINGLE_TREE_SELECTION);
//        renderer.setLeafIcon(NULL);
//        renderer.setClosedIcon(NULL);
//        renderer.setOpenIcon(NULL);
        _tree = new JTree(getModel());
        _tree->setEnabled(true);
        _tree->setVisible(true);
        _tree->setSelectionMode(QAbstractItemView::SingleSelection);
//        _tree->setUI(new TreeUI());
//        _tree->putClientProperty("JTree.lineStyle", "None");
//        _tree->setRootVisible(false);
//        _tree->expandRow(0);
        _tree->setSelectionModel(sm);
//        _tree->setCellRenderer(renderer);
//        _tree->addTreeWillExpandListener(new TreeWillExpandListener());
        _TSL = new MyTreeSelectionListener(this);
//        connect(_tree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
        _tree->addTreeSelectionListener(_TSL);
//        _tree->setDragEnabled(true);
//        _tree->setDropMode(DropMode.ON);
//        _tree->setTransferHandler(new TransferHandler());
//        _tree->addMouseListener(new MouseAdapter());
        _tree->setShowsRootHandles(true);
        _tree->setScrollsOnExpand(true);
        _tree->setExpandsSelectedPaths(true);
        _tree->setItemsExpandable(false);
        _tree->setRootIsDecorated(false);
        setSelectionToGroup(selectedRosterGroup);
//        Roster::getDefault().addPropertyChangeListener(new PropertyChangeListener());
        connect(Roster::getDefault()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(on_propertyChange(PropertyChangeEvent*)));
    }
    return _tree;
}

void RosterGroupsPanel::on_clicked(QModelIndex index)
{
 QString selected = index.data().toString();
 qDebug() <<selected;
 QString oldSelection = selectedRosterGroup;
 selectedRosterGroup = selected;
 //firePropertyChangeAsRGP(SELECTED_ROSTER_GROUP, oldSelection, selectedRosterGroup);
}

/*private*/ DefaultTreeModel* RosterGroupsPanel::getModel()
{
 if (_model == NULL) {
     _model = new DefaultTreeModel(getRoot());
 }
 return _model;
}

/*private*/ DefaultMutableTreeNode* RosterGroupsPanel::getRoot()
{
 if (_root == NULL)
 {
  _root = new DefaultMutableTreeNode();
  _groups = new DefaultMutableTreeNode("Roster Groups");
  _root->add(_groups);
  setRosterGroups(_groups);
  // once consists can be displayed in the DP3 table, add them here
  //_consists = new DefaultMutableTreeNode("Consists");
  //setConsists(_consists);
  //_root.add(_consists);
 }
 return _root;
}

/*private*/ QMenu* RosterGroupsPanel::defaultMenu(int menu) {
 menuMapper = new QSignalMapper();
    QMenu* pm = new QMenu();
    MenuActionListener* ml = new MenuActionListener(this);

    QAction* mi = new QAction(tr("Export..."),this);// JMenuItem(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("Exportddd"));
//    mi.addActionListener(ml);

//    mi.setActionCommand("export");
    mi->setProperty("action", "export");
    pm->addAction(mi);
    ml->addAction(mi);
    menuMapper->setMapping(mi, mi);
    mi = new QAction(tr("Import.."),this); // JMenuItem(ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("Importddd"));
//    mi.addActionListener(ml);
//    mi.setActionCommand("import");
   mi->setProperty("action", "import");
   pm->addAction(mi);
   ml->addAction(mi);
   menuMapper->setMapping(mi, "import");
   pm->addAction(mi);
    if (menu == GROUPS_MENU) {
        pm->addSeparator();
        mi = new QAction(tr("Rename..."), this);
//        mi.addActionListener(ml);
//        mi.setActionCommand("rename");
        mi->setProperty("action", "rename");
        pm->addAction(mi);
        ml->addAction(mi);
        menuMapper->setMapping(mi, "rename");
        pm->addAction(mi);
        mi = new QAction(tr("Duplicate"),this);
//        mi.addActionListener(ml);
//        mi.setActionCommand("duplicate");
        mi->setProperty("action", "duplicate");
        pm->addAction(mi);
        ml->addAction(mi);
        menuMapper->setMapping(mi, "duplicate");
        pm->addAction(mi);
        mi = new QAction(tr("Delete"), this);
//        mi.addActionListener(ml);
//        mi.setActionCommand("delete");
        mi->setProperty("action", "delete");
        pm->addAction(mi);
        ml->addAction(mi);
        menuMapper->setMapping(mi, "delete");
        pm->addAction(mi);
    }
    return pm;
}

/*private*/ void RosterGroupsPanel::setRosterGroups(DefaultMutableTreeNode* root) {
    root->removeAllChildren();
    root->add(new DefaultMutableTreeNode(Roster::ALLENTRIES));
    foreach (QString g, Roster::getDefault()->getRosterGroupList()) {
        root->add(new DefaultMutableTreeNode(g));
    }
}

// allow private classes to fire property change events as the RGP
/*protected*/ void RosterGroupsPanel::firePropertyChangeAsRGP(QString propertyName, QVariant oldValue, QVariant newValue) {
    if (propertyName==(SELECTED_ROSTER_GROUP)) {
        selectedRosterGroup = newValue.toString();
    }
    //this.firePropertyChange(propertyName, oldValue, newValue);
    emit propertyChange(new PropertyChangeEvent(this, propertyName, oldValue,newValue));

}

//class MenuActionListener implements ActionListener {

MenuActionListener::MenuActionListener(RosterGroupsPanel *panel)
{
 this->panel = panel;
 mapper = new QSignalMapper();
 connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(actionPerformed(QObject*)));
}

void MenuActionListener::addAction(QAction* act)
{
 mapper->setMapping(act, act);
 connect(act, SIGNAL(triggered(bool)), mapper, SLOT(map()));
}

//@Override
/*public*/  void MenuActionListener::actionPerformed(QObject* o)
{
 QAction* e = (QAction*)o;
 QList<TreeNode*>* l = panel->_model->getPathToRoot(panel->_groups);
 QVector<QObject*>* ol = new QVector<QObject*>();
 foreach (TreeNode* n, *l) {
  ol->append((QObject*)n);
 }
 TreePath* g = new TreePath(ol);
 WindowInterface* wi = (WindowInterface*) panel->window();
 if (g->isDescendant(panel->_tree->getSelectionPath()))
 {
  if (e->property("action").toString()==("export"))
  {
   FullBackupExportAction* act =     new FullBackupExportAction("Export...", wi);
   act->actionPerformed();
  }
  else if (e->property("action").toString()==("import"))
  {
   FullBackupImportAction* act = new FullBackupImportAction("Import...", wi);
   act->actionPerformed();
  }
  else if (e->property("action").toString()==("rename"))
  {
   RenameRosterGroupAction* act =   new RenameRosterGroupAction("Rename", wi);
   act->  actionPerformed();
  }
  else if (e->property("action").toString()==("duplicate"))
  {
   CopyRosterGroupAction* act =    new CopyRosterGroupAction("Duplicate", wi);
   act->  actionPerformed();
  }
  else if (e->property("action").toString()==("delete"))
  {
   DeleteRosterGroupAction* act =   new DeleteRosterGroupAction("Delete", wi);
   act->  actionPerformed();
  }
  else if (e->property("action").toString()==("newWindow") && panel->newWindowMenuItemAction != NULL)
  {
      panel->newWindowMenuItemAction->actionPerformed();
  }
  else
  {
//      JOptionPane.showMessageDialog((JComponent) e.getSource(),
//              ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("NotImplemented"),
//              ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("NotImplemented"),
//              JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(NULL, "Not Implemented", "Not Implemented)");
  }
 }
}
//}
#if 0
class MouseAdapter extends java.awt.event.MouseAdapter {

    //@Override
    /*public*/  void mousePressed(MouseEvent e) {
        if (SwingUtilities.isLeftMouseButton(e)) {
            JTree t = (JTree) e.getSource();
            int closestRow = t.getClosestRowForLocation(e.getX(), e.getY());
            Rectangle closestRowBounds = t.getRowBounds(closestRow);
            if (e.getY() >= closestRowBounds.getY()
                    && e.getY() < closestRowBounds.getY() + closestRowBounds.getHeight()) {
                // test the click is after start of row renderer
                //if (e.getX() > closestRowBounds.getX()
                //        && closestRow < t.getRowCount()) {
                t.setSelectionRow(closestRow);
                // setting selection to -1 removes the selection
                //} else {
                //    t.setSelectionRow(-1);
            }
        } else if (e.isPopupTrigger()) {
            showMenu(e);
        }
    }

    //@Override
    /*public*/  void mouseReleased(MouseEvent e) {
        if (e.isPopupTrigger()) {
            showMenu(e);
        }
    }

    /*public*/  void showMenu(MouseEvent e) {
        JTree t = (JTree) e.getSource();
        int closestRow = t.getClosestRowForLocation(e.getX(), e.getY());
        Rectangle closestRowBounds = t.getRowBounds(closestRow);
        if (e.getY() >= closestRowBounds.getY()
                && e.getY() < closestRowBounds.getY() + closestRowBounds.getHeight()) {
            t.setSelectionRow(closestRow);
            TreePath g = new TreePath(_model.getPathToRoot(_groups));
            if (t.getSelectionPath().getLastPathComponent().toString()==(Roster.ALLENTRIES)) {
                allEntriesMenu.show((JComponent) e.getSource(), e.getX(), e.getY());
            } else if (g.isDescendant(t.getSelectionPath()) && !t.getSelectionPath().isDescendant(g)) {
                groupsMenu.show((JComponent) e.getSource(), e.getX(), e.getY());
            }
        }
    }
}
#endif
//class PropertyChangeListener implements java.beans.PropertyChangeListener {

    //@Override
/*public*/  void RosterGroupsPanel::on_propertyChange(PropertyChangeEvent* e) {
    if ((e->getPropertyName()==("RosterGroupRemoved"))
            || (e->getPropertyName()==("RosterGroupAdded"))
            || (e->getPropertyName()==("RosterGroupRenamed"))) {
        setRosterGroups(_groups);
        _model->reload(_groups);
        setSelectionToGroup(selectedRosterGroup);
    }
}
//}
#if 0
class TransferHandler extends javax.swing.TransferHandler {

    /**
     *
     */
    //private static final long serialVersionUID = 4224992650668284315L;

    //@Override
    /*public*/  bool canImport(QWidget* c, DataFlavor[] transferFlavors) {
        for (DataFlavor flavor : transferFlavors) {
            if (RosterEntrySelection.rosterEntryFlavor==(flavor)) {
                return true;
            }
        }
        return false;
    }

    //@Override
    /*public*/  bool importData(QWidget* c, Transferable t) {
        if (canImport(c, t.getTransferDataFlavors())) {
            // getDropLocation is NULL unless dropping on an existing path
            return importData(c, t, ((JTree) c).getDropLocation().getPath());
        }
        return false;
    }

    /*public*/  bool importData(QWidget* c, Transferable t, TreePath p) {
        JTree l = (JTree) c;
        if (p != NULL) {
            TreePath g = new TreePath(_model.getPathToRoot(_groups));
            // drag onto existing user defined group, but not onto current selection
            if (g.isDescendant(p) && !p.isDescendant(g) && !p.isDescendant(l.getSelectionPath())) {
                try {
                    ArrayList<RosterEntry> REs = RosterEntrySelection.getRosterEntries(t);
                    for (RosterEntry re : REs) {
                        re.putAttribute(Roster.getRosterGroupProperty(p.getLastPathComponent().toString()), "yes");
                        re.updateFile();
                    }
                    Roster.writeRosterFile();
                    setSelectedRosterGroup(p.getLastPathComponent().toString());
                } catch (Exception* e) {
                    log.warn("Exception dragging RosterEntries onto RosterGroups: " + e);
                }
            }
        } else {
            try {
                JmriAbstractAction a = new CreateRosterGroupAction("Create From Selection", scrollPane.getTopLevelAncestor());
                a.setParameter("RosterEntries", RosterEntrySelection.getRosterEntries(t));
                a.actionPerformed(NULL);
            } catch (Exception* e) {
                log.warn("Exception creating RosterGroups from selection: " + e);
            }
        }
        return false;
    }
}

static /*public*/  class TreeCellRenderer extends DefaultTreeCellRenderer {

    /**
     *
     */
    private static final long serialVersionUID = 6470385455791687641L;
}
#endif
 // /*public*/  class TreeSelectionListener implements javax.swing.event.TreeSelectionListener {

MyTreeSelectionListener::MyTreeSelectionListener(RosterGroupsPanel *panel)
{
 this->panel = panel;
}

//@Override
/*public*/  void MyTreeSelectionListener::valueChanged(TreeSelectionEvent* e)
{
 QList<TreeNode*>* list = panel->_model->getPathToRoot(panel->_groups);
 QVector<QObject*>* ol = new QVector<QObject*>();
 foreach(TreeNode* n, *list) ol->append((QObject*)n);
 TreePath* g = new TreePath(ol);
 QString oldGroup = panel->selectedRosterGroup;
 if (e->getNewLeadSelectionPath() == NULL)
 {
  // if there are no Roster Groups set selection to "All Entries"
  if (Roster::getDefault()->getRosterGroupList().isEmpty())
  {
   list =panel->_model->getPathToRoot(panel->_groups->getFirstChild());
   ol->clear();
   foreach(TreeNode* n, *list) ol->append((QObject*)n);
   panel->_tree->setSelectionPath(new TreePath(ol));
  }
 }
 else if (e->getNewLeadSelectionPath()->isDescendant(g))
 {
  // reject user attempts to select the "Roster Groups" header
  panel->_tree->setSelectionPath(e->getOldLeadSelectionPath());
 }
 else if (g->isDescendant(e->getNewLeadSelectionPath()))
 {
  DefaultMutableTreeNode* tp = (DefaultMutableTreeNode*)panel->_tree->getSelectionPath()->getLastPathComponent();
  panel->selectedRosterGroup = ((DefaultMutableTreeNode*)panel->_tree->getSelectionPath()->getLastPathComponent())->toString();
  if (Roster::ALLENTRIES==(panel->selectedRosterGroup))
  {
   panel->selectedRosterGroup = "";
  }
 }
 else
 {
  panel->selectedRosterGroup = "";
 }
 //firePropertyChangeAsRGP(SELECTED_ROSTER_GROUP, oldGroup, selectedRosterGroup);
 panel->firePropertyChangeAsRGP(RosterGroupsPanel::SELECTED_ROSTER_GROUP, oldGroup, panel->selectedRosterGroup);
}
 //};
#if 0
 /*public*/  class TreeWillExpandListener implements javax.swing.event.TreeWillExpandListener {

     //@Override
     /*public*/  void treeWillExpand(TreeExpansionEvent e) throws ExpandVetoException {
         log.debug("Selected rows ", _tree->getSelectionRows());
     }

     //@Override
     /*public*/  void treeWillCollapse(TreeExpansionEvent e) throws ExpandVetoException {
         if (e.getPath().getLastPathComponent().toString()==("Roster Groups")) {
             throw new ExpandVetoException(e);
         }
     }
 }


static /*public*/  class TreeUI extends BasicTreeUI {

    //@Override
    /*public*/  void paint(Graphics g, QWidget* c) {
        // TODO use c.getVisibleRect to trim painting to minimum rectangle.
        // paint the background for the tree.
        g.setColor(UIManager.getColor("Tree.textBackground"));
        g.fillRect(0, 0, c.getWidth(), c.getHeight());

        // TODO use c.getVisibleRect to trim painting to minimum rectangle.
        // paint the background for the selected entry, if there is one.
        int selectedRow = getSelectionModel().getLeadSelectionRow();
        if (selectedRow >= 0 && tree.isVisible(tree.getPathForRow(selectedRow))) {

            Rectangle bounds = tree.getRowBounds(selectedRow);

            Graphics2D selectionBackgroundGraphics = (Graphics2D) g.create();
            selectionBackgroundGraphics.translate(0, bounds.y);
            selectionBackgroundGraphics.setColor(UIManager.getColor("Tree.selectionBackground"));
            selectionBackgroundGraphics.fillRect(0, 0, c.getWidth(), bounds.height);
            selectionBackgroundGraphics.dispose();
        }

        super.paint(g, c);
    }

    //@Override
    /*protected*/ void paintHorizontalLine(Graphics g, QWidget* c, int y, int left, int right) {
        // do nothing - don't paint horizontal lines.
    }

    //@Override
    /*protected*/ void paintVerticalPartOfLeg(Graphics g, Rectangle clipBounds, Insets insets,
            TreePath path) {
        // do nothing - don't paint vertical lines.
    }
}
#endif
