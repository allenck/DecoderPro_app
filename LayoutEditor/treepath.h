#ifndef TREEPATH_H
#define TREEPATH_H

#include <QObject>
#include <QList>
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT TreePath : public QObject
{
    Q_OBJECT
public:
    //explicit TreePath(QObject *parent = 0);
    /*public*/  TreePath(QList<QObject*>* path, QObject* parent= 0);
    /*public*/  TreePath(QObject* lastPathComponent, QObject* parent= 0);
    /*public*/  QList<QObject*>* getPath();
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
    /*protected*/ TreePath(QList<QObject*>* path, int length, QObject* parent = 0);
    /*protected*/ TreePath(QObject* parent = 0);


};

#endif // TREEPATH_H
