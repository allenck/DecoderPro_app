#ifndef TREEMODELEVENT_H
#define TREEMODELEVENT_H
#include "eventobject.h"
#include "treepath.h"
#include <qvector.h>

class TreeModelEvent : public EventObject
{
 Q_OBJECT
public:
 TreeModelEvent(QObject* parent = 0);
 /*public*/ TreeModelEvent(QObject* source, QVector<QObject*>* path, QVector<int>* childIndices,
                       QVector<QObject*>* children, QObject* parent = 0);

 /*public*/ TreeModelEvent(QObject* source, TreePath* path, QVector<int>* childIndices,
                       QVector<QObject*>* children, QObject* parent = 0);
 /*public*/ TreeModelEvent(QObject* source, QVector<QObject*>* path, QObject* parent = 0);
 /*public*/ TreeModelEvent(QObject* source, TreePath* path, QObject* parent = 0);
 /*public*/ TreePath* getTreePath();
 /*public*/ QVector<QObject *> *getPath();
 /*public*/ QList<QObject*>* getChildren();
 /*public*/ QVector<int>* getChildIndices();
 /*public*/ QString toString();


private:
 void common(TreePath* path, QVector<int>* childIndices, QVector<QObject*>* children);

protected:
 /** Path to the parent of the nodes that have changed. */
 /*protected*/ TreePath*  path;
 /** Indices identifying the position of where the children were. */
 /*protected*/ QVector<int>* childIndices;
 /** Children that have been removed. */
 /*protected*/ QVector<QObject*>*  children;

};

#endif // TREEMODELEVENT_H
