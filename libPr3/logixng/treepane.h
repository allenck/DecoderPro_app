#ifndef TREEPANE_H
#define TREEPANE_H

#include <jpanel.h>
#include "propertychangelistener.h"
#include "jtree.h"
#include "femalesocket.h"
#include "treemodellistener.h"
#include "imageicon.h"
#include "treecellrenderer.h"
#include "defaulttreemodel.h"
#include "threadingutil.h"
#include "abstractfemalesocket.h"
#include "defaultmutabletreenode.h"

class TreeEditor;
class FemaleSocketDecorator;
class FemaleSocketTreeModel;
class TreePane : public JPanel, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 public:
  TreePane(AbstractFemaleSocket *femaleRootSocket, QWidget* parent = nullptr);
  ~TreePane() {}
  TreePane(const TreePane&) : JPanel() {}
  /*public*/  void initComponents();
  /*public*/  void initComponents(FemaleSocketDecorator* decorator);
  /*public*/  bool getRootVisible();
  /*public*/  void setRootVisible(bool rootVisible);
  /*public*/  void updateTree(Base* item);
  /*public*/  void dispose();


  QObject* pself() override {return (QObject*)this; }
 public slots:
  /*public*/  void propertyChange(PropertyChangeEvent* evt)override;

 private:
  /*private*/ bool _rootVisible = true;

  /*private*/ static /*final*/ QMap<QString, QColor> FEMALE_SOCKET_COLORS;// = new HashMap<>();

  JTree* _tree;

 protected:
  /*protected*/ /*final*/ AbstractFemaleSocket* _femaleRootSocket;
  /*protected*/ FemaleSocketTreeModel* femaleSocketTreeModel;
  /*protected*/ void getPath(Base* base, QList<FemaleSocket *> *list);
  /*protected*/ void updateTree(FemaleSocket* currentFemaleSocket, QVector<QObject *> *currentPath);

  friend class FemaleSocketTreeRenderer;
  friend class PopupMenu;
  friend class ThreadAction1;
  friend class ThreadAction2;
  friend class ConditionalNGDebugger;
  friend class TreeEditor;
  friend class DeleteBeanWorker2;
  friend class TEPopupMenu;
  friend class ModuleEditor;
  friend class TreeEditor_run3;
  friend class TreeEditor_run5;

};

class ThreadAction1 : public ThreadAction
{
  Q_OBJECT
  QList<FemaleSocket*>* list;
  TreePane* pane;
 public:
  ThreadAction1(QList<FemaleSocket*>* list, TreePane* pane) : ThreadAction() {this->list = list; this->pane = pane;}
  void run()
  {
   FemaleSocket* femaleSocket = list->at(list->size()-1);
   QVector<QObject*>* oList = new QVector<QObject*>();
   foreach(FemaleSocket* femaleSocket, *list)
    oList->append((AbstractFemaleSocket*)femaleSocket->bself());
   pane->updateTree(femaleSocket, oList);

  }
};

class ThreadAction2 : public ThreadAction
{
  Q_OBJECT
  QList<FemaleSocket*>* list;
  TreePane* pane;
  FemaleSocket* femaleSocket;
 public:
  ThreadAction2(FemaleSocket* femaleSocket, QList<FemaleSocket*>* list, TreePane* pane) : ThreadAction() {
   this->list = list;
   this->pane = pane;
   this->femaleSocket = femaleSocket;
  }
  void run()
  {
   QVector<QObject*>* oList = new QVector<QObject*>();
   foreach(FemaleSocket* femaleSocket, *list)
    oList->append((AbstractFemaleSocket*)femaleSocket->bself());
   pane->updateTree(femaleSocket, oList);
  }
};

class TreePane_FemaleSocketTreeNode : public DefaultMutableTreeNode
{
  Q_OBJECT
  AbstractFemaleSocket* femaleSocket;
 public:
  TreePane_FemaleSocketTreeNode(AbstractFemaleSocket* femaleSocket, QObject* parent = nullptr);
  int getChildCount() override;
};

/*public*/  /*static*/ class FemaleSocketTreeModel : public DefaultTreeModel //, public TreeNode
{
 Q_OBJECT
//Q_INTERFACES(TreeNode)
    /*private*/ /*final*/ AbstractFemaleSocket* _root;
    public:

    /*public*/  FemaleSocketTreeModel(AbstractFemaleSocket* root, QObject* parent = nullptr);
    /*public*/  QObject* getRoot()override;
    /*public*/  bool isLeaf(QObject* node)override;
    /*public*/  int getChildCount(QObject* parent)const override;
    /*public*/  QObject* getChild(QObject* parent, int index) override;
    /*public*/  int getIndexOfChild(QObject* parent, QObject* child)override;
    /*public*/  void valueForPathChanged(TreePath* path, QVariant newvalue)override;
    /*public*/  void addTreeModelListener(TreeModelListener* l)override;
    /*public*/  void removeTreeModelListener(TreeModelListener* l) override;

  int rowCount(const QModelIndex &parent) const override
  {
  // if(QString(metaObject()->className()) == "DefaultTreeModel")
  // {
    MutableTreeNode* parentItem;
    if (parent.column() > 0)
     return 0;
    if (!parent.isValid())
     parentItem = root;
    else
     parentItem = static_cast<DefaultMutableTreeNode*>(parent.internalPointer());
    if(!parentItem)
     parentItem = root;
    return getChildCount(((QObject*)root));
  }

  QVariant headerData(int /*section*/, Qt::Orientation orientation, int role) const override
  {
   if(role == Qt::DisplayRole &&  orientation == Qt::Horizontal)
   {
   return tr("");
   }
   return QVariant();
  }

  //QObject* tself() override {return (QObject*)this;}

protected:
  /*protected*/ /*final*/ QList<TreeModelListener*> listeners = QList<TreeModelListener*>();
  friend class TreePane;
  friend class PopupMenu;
  friend class ConditionalNGDebugger;
  friend class TreeEditor;
  friend class DeleteBeanWorker2;
  friend class TreeEditor_run3;
  friend class TreeEditor_run5;
};

/*private*/ /*static*/ /*final*/ class FemaleSocketTreeRenderer : public QObject, public TreeCellRenderer {
  Q_OBJECT
  Q_INTERFACES(TreeCellRenderer)
    /*private*/ /*final*/ FemaleSocketDecorator* _decorator;
    /*private*/ static ImageIcon* _lockIcon;// = nullptr;
    public:
    /*public*/  FemaleSocketTreeRenderer(FemaleSocketDecorator* decorator);
    //@Override
    /*public*/  QWidget* getTreeCellRendererComponent(JTree* tree, QVariant value, bool selected, bool expanded,
                                                      bool leaf, int row, bool hasFocus)override;
};

/*public*/  /*interface*/ class FemaleSocketDecorator {
 public:
    /*public*/ virtual JPanel* decorate(FemaleSocket* femaleSocket, JPanel* panel)=0;
};
Q_DECLARE_INTERFACE(FemaleSocketDecorator, "FemaleSocketDecorator")

class TreePane_RunnableWithBase : public RunnableWithBase
{
  Q_OBJECT
  TreePane* treePane;
 public:
  TreePane_RunnableWithBase(TreePane* treePane) {
   this->treePane = treePane;
   setObjectName("TreePane_RunnableWithBase");
  }
  void run(Base* b)
  {
   ((AbstractFemaleSocket*)b->bself())->PropertyChangeProvider::addPropertyChangeListener(treePane);
  }
};

class TreePane_FemaleSocketDecorator : public QObject,public FemaleSocketDecorator
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketDecorator)
  FemaleSocket* femaleSocket;
  JPanel* panel;
 public:
  TreePane_FemaleSocketDecorator(FemaleSocket* femaleSocket, JPanel* panel) {
      setObjectName("TreePane_FemaleSocketDecorator");
   this->femaleSocket = femaleSocket;
   this->panel = panel;
  }
  JPanel* decorate(FemaleSocket* femaleSocket, JPanel* panel)
  {
   return panel;
  }
};


#endif // TREEPANE_H
