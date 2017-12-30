#ifndef SIZESEQUENCE_H
#define SIZESEQUENCE_H
#include <QVector>

class SizeSequence
{
public:
 SizeSequence();
 /*public*/ SizeSequence(int numEntries);
 /*public*/ SizeSequence(int numEntries, int value);
 /*public*/ SizeSequence(QVector<int>* sizes);
 /*public*/ void setSizes(QVector<int>* sizes);
 /*public*/ QVector<int>* getSizes();
 /*public*/ int getPosition(int index);
 /*public*/ int getIndex(int position);
 /*public*/ int getSize(int index);
 /*public*/ void setSize(int index, int size);
 /*public*/ void insertEntries(int start, int length, int value);
 /*public*/ void removeEntries(int start, int length);

private:
 /*private*/ static QVector<int>* emptyArray;// = new int[0];
 /*private*/ QVector<int>* a;
 void setSizes(int length, int size);
 /*private*/ int setSizes(int from, int to, int size);
 /*private*/ int setSizes(int from, int to, QVector<int>* sizes);
 /*private*/ int getSizes(int from, int to, QVector<int>* sizes);
 /*private*/ int getPosition(int from, int to, int index);
 /*private*/ int getIndex(int from, int to, int position);
 /*private*/ void changeSize(int from, int to, int index, int delta);
 friend class SortManager;
};

#endif // SIZESEQUENCE_H
