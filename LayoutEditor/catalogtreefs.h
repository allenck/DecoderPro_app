#ifndef CATALOGTREEFS_H
#define CATALOGTREEFS_H
#include "abstractcatalogtree.h"

class CatalogTreeFS : public AbstractCatalogTree
{
    Q_OBJECT
public:
    //explicit CatalogTreeFS(QObject *parent = 0);
    /*public*/ CatalogTreeFS(QString sysName, QString userName, QObject *parent = 0);
    /*public*/ void setFilter(QStringList filter);
    /*public*/ QStringList getFilter();
    bool filter(QString ext);
    /*public*/ void insertNodes(QString pName, QString pPath, CatalogTreeNode* pParent);
    /*public*/ void setProperty(QString key, QString value);
    /*public*/ QVariant getProperty(QString key) ;
    /*public*/ QList<QString> getPropertyKeys();


signals:

public slots:
private:
    QStringList _filter;
    QMap<QString, QString>* parameters;// = null;
};

#endif // CATALOGTREEFS_H
