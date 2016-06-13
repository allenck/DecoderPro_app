#ifndef BITSET_H
#define BITSET_H

#include <QObject>
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT BitSet : public QObject
{
    Q_OBJECT
public:
    explicit BitSet(QObject *parent = 0);
    /*public*/ BitSet(int nbits, QObject *parent = 0);
    /*public*/ static BitSet* valueOf(QList<long> longs);
//    /*public*/ static BitSet valueOf(LongBuffer lb);

    /*public*/ void _or(BitSet* set);
    /*public*/ void set(int bitIndex);
    /*public*/ void set(int bitIndex, bool value);
    /*public*/ void set(int fromIndex, int toIndex);
    /*public*/ void set(int fromIndex, int toIndex, bool value);
    /*public*/ void clear(int bitIndex);
    /*public*/ void clear(int fromIndex, int toIndex) ;
    /*public*/ void clear();
    /*public*/ int length();
    /*public*/ bool isEmpty();
    /*public*/ static int numberOfLeadingZeros(long i);
    /*public*/ int nextClearBit(int fromIndex);
    /*public*/ static int numberOfTrailingZeros(long i);
    /*public*/ bool get(int bitIndex);
    /*public*/ BitSet* get(int fromIndex, int toIndex);
    /*public*/ QString toString();
    /*public*/ int cardinality();
    /*public*/ int nextSetBit(int fromIndex);
    /*public*/ static int bitCount(long i);

signals:

public slots:
private:
    /*private*/ /*final*/ static int ADDRESS_BITS_PER_WORD;// = 6;
    /*private*/ /*final*/ static int BITS_PER_WORD;// = 1 << ADDRESS_BITS_PER_WORD;
    /*private*/ /*final*/ static int BIT_INDEX_MASK;// = BITS_PER_WORD - 1;

    /* Used to shift left or right for a partial word mask */
    /*private*/ static /*final*/ long WORD_MASK;// = 0xffffffffffffffffL;
    /**
     * The internal field corresponding to the serialField "bits".
     */
    /*private*/ QList<long> words;

    /**
     * The number of words in the logical size of this BitSet.
     */
    /*private*/ /*transient*/ int wordsInUse;// = 0;

    /**
     * Whether the size of "words" is user-specified.  If so, we assume
     * the user knows what he's doing and try harder to preserve it.
     */
    /*private*/ /*transient*/ bool sizeIsSticky;// = false;
    /*private*/ static int wordIndex(int bitIndex);
    /*private*/ void checkInvariants();
    /*private*/ void recalculateWordsInUse();
    /*private*/ void initWords(int nbits);
    /*private*/ BitSet(QList<long> words, QObject *parent = 0);
    void common();
    /*private*/ void expandTo(int wordIndex);
    /*private*/ void ensureCapacity(int wordsRequired);
    /*private*/ static void checkRange(int fromIndex, int toIndex);

};

#endif // BITSET_H
