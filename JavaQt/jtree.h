#ifndef JTREE_H
#define JTREE_H

#include <QTreeView>
#include "javaqt_global.h"
#include "treepath.h"


class TreeSelectionListener;
class PropertyChangeSupport;
class TreeSelectionModel;
class TreeModel;
class JAVAQTSHARED_EXPORT JTree : public QTreeView
{
 Q_OBJECT
public:
 explicit JTree(QWidget *parent = 0);
 JTree(TreeModel* tree,QWidget *parent = 0);
 void setShowsRootHandles(bool b);
 void setScrollsOnExpand(bool b);
 void setExpandsSelectedPaths(bool );
 /*public*/ TreePath* getSelectionPath();
 /*public*/ TreeSelectionModel* getSelectionModel();
 /*public*/ void setSelectionModel(TreeSelectionModel* selectionModel);
 /** Bound property name for selectionModel. */
     /*public*/ /*final*/ static QString        SELECTION_MODEL_PROPERTY;// = "selectionModel";
 PropertyChangeSupport* pcs;
 /*public*/ void setSelectionPath(TreePath* path);
 /*public*/ void addTreeSelectionListener(TreeSelectionListener* tsl);
 /*public*/ void removeTreeSelectionListener(TreeSelectionListener* tsl);
 /*public*/ bool isSelectionEmpty();

signals:

public slots:
 void on_clicked(QModelIndex);

private:
 TreeModel* tree;
 TreeSelectionModel* selectionModel;
 TreeSelectionListener* _TSL; // note: only one listener supported at this time.
};

#endif // JTREE_H
