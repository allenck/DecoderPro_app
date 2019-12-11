#ifndef POSITIONABLEICONTEST_H
#define POSITIONABLEICONTEST_H
#include "positionabletestbase.h"

class PositionableIconTest : public PositionableTestBase
{
 Q_OBJECT
public:
 PositionableIconTest();
 /*public*/ void setUp() override;
public slots:
 /*public*/ void testCtor();

};

#endif // POSITIONABLEICONTEST_H
