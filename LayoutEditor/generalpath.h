#ifndef GENERALPATH_H
#define GENERALPATH_H
#include <QVector>
#include "path2d.h"

class JShape;
class GeneralPath : public Float
{
public:
 GeneralPath();
 /*public*/ GeneralPath(int rule);
 /*public*/ GeneralPath(int rule, int initialCapacity);
 /*public*/ GeneralPath(JShape* s);

private:

 GeneralPath(int windingRule,
             QVector<char>* pointTypes,
             int numTypes,
             QVector<float>* pointCoords,
             int numCoords);

};


#endif // GENERALPATH_H
