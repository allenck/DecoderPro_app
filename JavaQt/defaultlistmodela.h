#ifndef DEFAULTLISTMODEAL_H
#define DEFAULTLISTMODELA_H

#include <QAbstractListModel>
#include "javaqt_global.h"

template <class T>
class JAVAQTSHARED_EXPORT DefaultListModelA : public QAbstractListModel
{

public:
    explicit DefaultListModelA(QObject *parent = 0)
 {
  delegate = new QVector<T>();
 }
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    /*public*/ void add(int index, T element);
    /*public*/ void removeElementAt(int index);
    /*public*/ int indexOf(QString elem);
    /*public*/ int getSize();
    /*public*/ T getElementAt(int index);
    /*public*/ void addElement(T element);
    /*public*/ T remove(int index);
    /*public*/ T elementAt(int index);

signals:

public slots:
private:
    /*private*/ QVector<T>* delegate;// = new QVector<QString>();

};

#endif // DEFAULTLISTMODEL_H
