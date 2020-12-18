#ifndef DEFAULTLISTMODEL_H
#define DEFAULTLISTMODEL_H

#include "abstractlistmodel.h"
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT DefaultListModel : public AbstractListModel
{
    Q_OBJECT
public:
    explicit DefaultListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    /*public*/ void add(int index, QVariant element);
    /*public*/ void set(int index, QVariant element);
    /*public*/ void removeElementAt(int index);
    /*public*/ int indexOf(QVariant elem);
    /*public*/ int getSize();
    /*public*/ int size() {return getSize();}
    /*public*/ QVariant getElementAt(int index);
    /*public*/ QVariant get(int index);
    /*public*/ void addElement(QVariant element);
    /*public*/ bool removeElement(QVariant obj);
    /*public*/ void removeAllElements();
    /*public*/ QVariant remove(int index);
//    /*public*/ QString toString();
    /*public*/ QVariant elementAt(int index);
    /*public*/ QListIterator<QVariant> elements();
    /*public*/ bool contains(QVariant elem);
    /*public*/ void clear();

signals:

public slots:
private:
    /*private*/ QVector<QVariant>* delegate;// = new QVector<QString>();

};

#endif // DEFAULTLISTMODEL_H
