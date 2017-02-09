#ifndef CATALOGTREELEAF_H
#define CATALOGTREELEAF_H

#include <QObject>

class CatalogTreeLeaf : public QObject
{
    Q_OBJECT
public:
    explicit CatalogTreeLeaf(QObject *parent = 0);
    /*public*/ CatalogTreeLeaf(QString name, QString path, int size, QObject *parent = 0);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    /*public*/ QString getPath() ;
    /*public*/ int getSize();

signals:

public slots:
private:
    /*private*/ QString _name;
    /*private*/ QString _path;
    /*private*/ int    _size;

};

#endif // CATALOGTREELEAF_H
