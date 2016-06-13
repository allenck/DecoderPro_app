#ifndef CATALOGTREEINDEX_H
#define CATALOGTREEINDEX_H
#include "abstractcatalogtree.h"

class CatalogTreeIndex : public AbstractCatalogTree
{
    Q_OBJECT
public:
    //explicit CatalogTreeIndex(QObject *parent = 0);
    /*public*/ CatalogTreeIndex(QString sysName, QString userName, QObject *parent = 0);
    ~CatalogTreeIndex();
    /*public*/ void insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent);
    /*public*/ void setProperty(QString key, QVariant value);
    /*public*/ QVariant getProperty(QString key);
    /*public*/ QList<QString> getPropertyKeys();
signals:

public slots:
private:
    QHash<QString, QVariant>* parameters;// = NULL;
 Logger* log;

};

#endif // CATALOGTREEINDEX_H
