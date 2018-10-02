#ifndef NCECONSIST_H
#define NCECONSIST_H
#include "dccconsist.h"

class NceConsist : public DccConsist
{
public:
 NceConsist();
 /*public*/ static /*final*/ int CONSIST_MIN;// = 1;    // NCE doesn't use consist 0
 /*public*/ static /*final*/ int CONSIST_MAX;// = 127;

};

#endif // NCECONSIST_H
