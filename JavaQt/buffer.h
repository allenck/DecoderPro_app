#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include "exceptions.h"
class InvalidMarkException : public Exception
{
public:
 InvalidMarkException(QString msg = "") : Exception(msg) {}
};

class Buffer : public QObject
{
 Q_OBJECT
public:
 Buffer(int mark, int pos, int lim, int cap, QObject* parent = nullptr);
 /*public*/ /*final*/ int capacity();
 /*public*/ /*final*/ int position();
 /*public*/ /*final*/ Buffer* position(int newPosition);
 /*public*/ /*final*/ int limit();
 /*public*/ /*final*/ Buffer* limit(int newLimit);
 /*public*/ /*final*/ Buffer* mark();
 /*public*/ /*final*/ Buffer* reset();
 /*public*/ /*final*/ Buffer* clear();
 /*public*/ /*final*/ Buffer* flip();
 /*public*/ /*final*/ Buffer* rewind();
 /*public*/ /*final*/ int remaining();
 /*public*/ /*final*/ bool hasRemaining();
 /*public*/ virtual /*abstract*/ bool isReadOnly();
 /*public*/ /*abstract*/ virtual bool hasArray();
 /*public*/ /*abstract*/ virtual QObject* array();
 /*public*/ /*abstract*/ virtual int arrayOffset();
 /*public*/ /*abstract*/virtual  bool isDirect();

signals:

public slots:

private:
 static /*final*/ int SPLITERATOR_CHARACTERISTICS;
 /*private*/ int _mark;// = -1;
 /*private*/ int _position;// = 0;
 /*private*/ int _limit;
 /*private*/ int _capacity;
 static void checkBounds(int off, int len, int size); // package-/*private*/

friend class CharBuffer;
};

#endif // BUFFER_H
