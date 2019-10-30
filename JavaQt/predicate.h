#ifndef PREDICATE_H
#define PREDICATE_H

#include <QVariant>

template<class T>
class Predicate : public QVariant
{
public:
 Predicate();
// /*default*/ Predicate<T> or(/*Predicate<? super*/ T other);
};

#endif // PREDICATE_H
