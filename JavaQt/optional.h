#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <QObject>

template <class T>
class Optional : public QObject
{
 Q_OBJECT
public:
 explicit Optional(QObject *parent = 0);
 /*public*/  Optional<T> empty();

signals:

public slots:

private:
 /*private*/ static /*final*/ Optional* EMPTY;// = new Optional<>();
 /**
  * If non-NULL, the value; if NULL, indicates no value is present
  */
 /*private*/ /*final*/ T value;
 /*private*/ Optional(T value);

};

#endif // OPTIONAL_H
