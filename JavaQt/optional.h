#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <QObject>
#include "javaqt_global.h"
#include "consumer.h"
#include "exceptions.h"
#include "consumer.h"

template <class T>
class JAVAQTSHARED_EXPORT Optional : public QObject
{
 //Q_OBJECT
public:
 explicit Optional(QObject *parent = 0) : QObject(parent) {this->value = nullptr;}
 /*public*/  Optional<T> empty()
 {
  Optional<T> t = (Optional<T>) Optional::EMPTY;
  return t;
 }
 /*public*/ T get()
 {
      if (value == NULL) {
          throw  NoSuchElementException("No value present");
      }
      return value;
 }
 /*public*/ bool isPresent() {return value != nullptr;}
 /*public*/ void ifPresent(Consumer</*? super*/ T>* consumer){    if (value != NULL)
   consumer->accept(value);
 }

signals:

public slots:

private:
 /*private*/ static /*final*/ Optional* EMPTY;// = new Optional<>();
 /**
  * If non-NULL, the value; if NULL, indicates no value is present
  */
 /*private*/ /*final*/ T value;
 /*private*/ Optional(T value){this->value = /*Objects.requireNonNull*/(value);}

};

#endif // OPTIONAL_H
