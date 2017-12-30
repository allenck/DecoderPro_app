#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <QObject>
#include "javaqt_global.h"
#include "consumer.h"

template <class T>
class JAVAQTSHARED_EXPORT Optional : public QObject
{
 //Q_OBJECT
public:
 explicit Optional(QObject *parent = 0);
 /*public*/  Optional<T> empty();
 /*public*/ T get();
 /*public*/ bool isPresent();
 /*public*/ void ifPresent(Consumer</*? super*/ T>* consumer);

signals:

public slots:

private:
 /*private*/ static /*final*/ Optional* EMPTY;// = new Optional<>();
 /**
  * If non-NULL, the value; if NULL, indicates no value is present
  */
 /*private*/ /*final*/ T* value;
 /*private*/ Optional(T* value);

};

#endif // OPTIONAL_H
