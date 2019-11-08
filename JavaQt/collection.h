#ifndef COLLECTION_H
#define COLLECTION_H
#include <QVariantList>

class Collection : public QVariantList
{
public:
 Collection();
 void addFirst(QVariant o);
 void addLast(QVariant o);
 QVariant peekFirst();
 QVariant peekLast();
 QVariant removeFirst();
 QVariant removeLast();
};

#endif // COLLECTION_H
