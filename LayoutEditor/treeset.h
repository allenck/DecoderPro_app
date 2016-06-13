#ifndef TREESET_H
#define TREESET_H

#include <QSet>
#include "navigablemap.h"
#include "comparator.h"

class TreeMap;
template <class E>
class TreeSet : public QSet<E>
{
    //Q_OBJECT
public:
    //explicit TreeSet(QObject *parent = 0);
    TreeSet(NavigableMap<E,QVariant> m, QObject *parent = 0);
//    /*public*/ TreeSet(Comparator<E> comparator, QObject *parent = 0);
    /*public*/ TreeSet(E, QObject *parent = 0);

    /*public*/ bool add(E e);

signals:

public slots:
private:
    /**
     * The backing map.
     */
    /*private*/ /*transient*/ NavigableMap<E,QVariant> m;

    // Dummy value to associate with an Object in the backing Map
    /*private*/ static /*final*/ QVariant PRESENT;// = /*new*/ QVariant();


};

#endif // TREESET_H
