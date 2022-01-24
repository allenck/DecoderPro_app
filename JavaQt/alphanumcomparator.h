#ifndef ALPHANUMCOMPARATOR_H
#define ALPHANUMCOMPARATOR_H

#include "comparator.h"

/**
 * This is an updated version with enhancements made by Daniel Migowski, Andre
 * Bogus, and David Koelle
 * <p>
 * To use this class: Use the static "sort" method from the
 * java.util.Collections class: Collections.sort(your list, new
 * AlphanumComparator());
 * <p>
 * Note: this code compares numbers one at a time if those numbers are in chunks
 * of the same size. For example, when comparing abc123 to abc184, 123 and 184
 * are the same size, so their values are compared digit-by- digit: 1 equals 1,
 * 2 is less than 8, etc. This was done to solve the problem of numeric chunks
 * that are too large to fit in range of values allowed by the programming
 * language for a particular datatype: in Java, an int is limited to 2147483647.
 * The problem with this approach is doesn't properly handle numbers that have
 * leading zeros. For example, 0001 is seem as larger than 1 because it's the
 * longer number. A version that does not compare leading zeros is forthcoming.
 */
/*public*/ class AlphanumComparator : public Comparator/*T<QString>*/ {

    /*private*/ /*final*/ bool isDigit(QChar ch) {
        return (('0' <= ch) && (ch <= '9'));
    }

    // Length of string is passed in for improved efficiency (only need to calculate it once)
    /*private*/ /*final*/ QString getChunk(QString s, int slength, int marker) {
        QString chunk;// = new StringBuilder();
        int markstart = marker;
        QChar c = s.at(marker);
        bool startIsDigit = isDigit(c);
        if (c == '0') {
            // strip leading zeros - cases:
            //    This is or isn't the only leading zero
            //    There are or aren't more digits after the run of zeros
            while (marker+1 < slength && s.at(marker+1) == '0') {
                marker++; // skip that zero
            }
            // now what's the next character?
            if (marker+1 >= slength) {
                // nothing more, continue with that single zero
            } else if (isDigit(s.at(marker+1))) {
                // number, drop the leading zero
                marker++;
                c = s.at(marker);
            } else {
                // is letter, let the zero go
            }
        }
        chunk.append(c);
        while (++marker < slength) {
            c = s.at(marker);
            if (isDigit(c) != startIsDigit) {
                break;
            }
            chunk.append(c);
        }

        skip = marker - markstart;
        return chunk/*.toString()*/;
    }

    // internal temporary used to efficiently return how many characters were skipped
    int skip;
public:
    //@Override
    /*public*/ int compare(QString s1, QString s2) {
        int length1 = s1.length();
        int length2 = s2.length();
        int result = length1 - length2;

        int marker1 = 0, marker2 = 0;
        while (marker1 < length1 && marker2 < length2) {
            QString chunk1 = getChunk(s1, length1, marker1);
            marker1 += skip;

            QString chunk2 = getChunk(s2, length2, marker2);
            marker2 += skip;

            // If both chunks contain numeric characters, sort them numerically
            if (isDigit(chunk1.at(0)) && isDigit(chunk2.at(0))) {
                // Simple chunk comparison by length.
                int chunkLength1 = chunk1.length();
                result = chunkLength1 - chunk2.length();
                // If lengths equal, the first different number counts
                if (result == 0) {
                    for (int i = 0; i < chunkLength1; i++) {
                        //result = chunk1.at(i) - chunk2.at(i);
//                        bool b;
                        result = 0;
                        if(chunk1.at(i) != chunk2.at(i))
                        {
                         if(chunk1.at(i) < chunk2.at(i))
                          result = -1;
                         else result = 1;
                        }
                        if (result != 0) {
                            break;
                        }
                    }
                }
            } else {
                result = chunk1.compare(chunk2);
            }

            if (result != 0) {
                break;
            }
        }
        if (result == 0 && marker1 == length1 && marker2 < length2) return -1;
        if (result == 0 && marker1 < length1 && marker2 == length2) return +1;

        //return Integer.signum(result);  // limit to -1, 0, 1
        if(result>0)
         return 1;
        if(result<0)
         return -1;
        return 0;
    }
};
#endif // ALPHANUMCOMPARATOR_H
