#ifndef SPROGMESSAGETEST_H
#define SPROGMESSAGETEST_H
#include "abstractmessagetestbase.h"

namespace Sprog
{
    class SprogMessage;
    class SprogMessageTest : public AbstractMessageTestBase
    {
        Q_OBJECT
    public:
        SprogMessageTest();
        /*public*/ void setUp();
        /*public*/ void tearDown();
    public slots:
        /*public*/ void testReadCv();
        /*public*/ void testWriteCV();
        /*public*/ void testReadCvLarge();
        /*public*/ void testWriteCVLarge();
    private:
        /*private*/ SprogMessage* msg = nullptr;

    };
}
#endif // SPROGMESSAGETEST_H
