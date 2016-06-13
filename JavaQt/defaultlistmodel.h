#ifndef DEFAULTLISTMODEL_H
#define DEFAULTLISTMODEL_H

#include <QAbstractListModel>
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT DefaultListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DefaultListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    /*public*/ void add(int index, QString element);
    /*public*/ void removeElementAt(int index);
    /*public*/ int indexOf(QString elem);
    /*public*/ int getSize();
    /*public*/ QVariant getElementAt(int index);
    /*public*/ void addElement(QVariant element);
    /*public*/ QVariant remove(int index);
    /*public*/ QVariant elementAt(int index);

signals:

public slots:
private:
    /*private*/ QVector<QVariant>* delegate;// = new QVector<QString>();

};

#endif // DEFAULTLISTMODEL_H
