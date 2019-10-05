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
void Assume::assumeTrue(QString message, bool b)
{
    if(!b)
        throw AssertionError(tr("%1: Assue condition not true").arg(message));
}
