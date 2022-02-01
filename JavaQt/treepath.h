#ifndef TREEPATH_H
#define TREEPATH_H

#include <QObject>
#include <QList>
#include "javaqt_global.h"

class TreeNode;
class JAVAQTSHARED_EXPORT TreePath : public QObject
{
    Q_OBJECT
public:
    //explicit TreePath(QObject *parent = 0);
    /*public*/  TreePath(QVector<QObject*>* path, QObject* parent= 0);
    /*public*/  TreePath(TreeNode* lastPathComponent, QObject* parent= 0);
    /*public*/  QVector<QObject*>* getPath();
    /*public*/  QObject* getLastPathComponent();
    /*public*/  int getPathCount();
    /*public*/  QObject* getPathComponent(int index);
    /*public*/  bool equals(QObject* o) ;
    /*public*/  int hashCode();
    /*public*/  bool isDescendant(TreePath* aTreePath);
    /*public*/  TreePath* pathByAddingChild(QObject* child);
    /*public*/  TreePath* getParentPath();
    /*public*/  QString toString();

signals:

public slots:
private:
    /*private*/ TreePath*           parentPath;
    /** Last path component. */
    /*private*/ QObject* lastPathComponent;
    void common();
 protected:
    /*protected*/ TreePath(TreePath* parentPath, QObject* lastPathComponent, QObject* parent= 0);
    /*protected*/ TreePath(QVector<QObject*>* path, int length, QObject* parent = 0);
    /*protected*/ TreePath(QObject* parent = 0);

    friend class DefaultTreeSelectionModel;
friend class TreeModelEvent;
friend class RosterGroupsPanel;
};

#endif // TREEPATH_H
