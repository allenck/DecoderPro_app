#include "catalogtreeleaf.h"

CatalogTreeLeaf::CatalogTreeLeaf(QObject *parent) :
    QObject(parent)
{
}
/**
 * Leaf of a CatalogTree.
 * <P>
 * Name for the leaf
 * Path to lead.
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
///*public*/ class CatalogTreeLeaf {


    /*public*/ CatalogTreeLeaf::CatalogTreeLeaf(QString name, QString path, int size, QObject *parent) :
        QObject(parent)
    {
        _name = name;
        _path = path;
        _size = size;
    }

    /*public*/ QString CatalogTreeLeaf::getName() {
        return _name;
    }

    /*public*/ void CatalogTreeLeaf::setName(QString name) {
        _name = name;
    }

    /*public*/ QString CatalogTreeLeaf::getPath() {
        return _path;
    }

    /*public*/ int CatalogTreeLeaf::getSize() {
        return _size;
    }
//}
