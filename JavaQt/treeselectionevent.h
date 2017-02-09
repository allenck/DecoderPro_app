#ifndef TREESELECTIONEVENT_H
#define TREESELECTIONEVENT_H

#include <QObject>

class TreePath;
class TreeSelectionEvent : public QObject
{
 Q_OBJECT
public:
 /*public*/ TreeSelectionEvent(QObject* source, QList<TreePath*>* paths,
                           QList<bool>* areNew, TreePath* oldLeadSelectionPath,
                           TreePath* newLeadSelectionPath);
 /*public*/ TreeSelectionEvent(QObject* source, TreePath* path, bool isNew,
                           TreePath* oldLeadSelectionPath,
                           TreePath* newLeadSelectionPath);

 /*public*/ QList<TreePath*>* getPaths();
 /*public*/ TreePath* getPath();
 /*public*/ bool isAddedPath();
 /*public*/ bool isAddedPath(TreePath* path);
 /*public*/ bool isAddedPath(int index);
 /*public*/ TreePath* getOldLeadSelectionPath();
 /*public*/ TreePath* getNewLeadSelectionPath();
 /*public*/ QObject* cloneWithSource(QObject* newSource);

signals:

public slots:
protected:
 /** Paths this event represents. */
 /*protected*/ QList<TreePath*>*    paths;
 /** For each path identifies if that path is in fact new. */
 /*protected*/ QList<bool>*       areNew;
 /** leadSelectionPath before the paths changed, may be null. */
 /*protected*/ TreePath*        oldLeadSelectionPath;
 /** leadSelectionPath after the paths changed, may be null. */
 /*protected*/ TreePath*        newLeadSelectionPath;

};

#endif // TREESELECTIONEVENT_H
