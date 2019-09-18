#include "assume.h"
#include "assert1.h"
Assume::Assume(QObject *parent) : QObject(parent)
{

}

void Assume::assumeTrue(bool b)
{
    if(!b)
        throw AssertionError("Assue condition not true");
}
