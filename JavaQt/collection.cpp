#include "collection.h"

Collection::Collection() : QVariantList() {}

void Collection::addFirst(QVariant o)
{
 prepend(o);
}

void Collection::addLast(QVariant o)
{
 append(o);
}

QVariant Collection::peekFirst()
{
 if(isEmpty()) return QVariant();
 return first();
}

QVariant Collection::peekLast()
{
 if(isEmpty()) return QVariant();
 return last();
}

QVariant Collection::removeFirst()
{
 if(isEmpty()) return QVariant();
 return takeFirst();
}

QVariant Collection::removeLast()
{
 if(isEmpty()) return QVariant();
 return takeLast();
}
