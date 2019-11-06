#ifndef COMPARATORT_H
#define COMPARATORT_H

#include <QObject>

template<class T>
class ComparatorT //: public QObject
{
public:
 explicit ComparatorT(/*QObject *parent = nullptr*/) {}
 virtual int compare(T o1, T o2) =0;
 virtual bool equals(T /*obj*/) {return false;}

signals:

public slots:
};

#endif // COMPARATORT_H
