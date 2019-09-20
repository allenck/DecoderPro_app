#include "assert1.h"
#include "loggerfactory.h"

//Assert::Assert(QObject *parent) : QObject(parent)
//{

//}
///*public*/ class Assert {

    /*protected*/ Assert::Assert(QObject *parent) : QObject(parent) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::assertTrue(QString message, bool condition) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: iload_1
         * 1: ifne          8
         * 4: aload_0
         * 5: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 8: return
         *  */
        // </editor-fold>
    if(!condition)
        throw AssertionError(message);
    }

    /*public*/ /*static*/ void Assert::assertTrue(bool condition) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: iload_0
         * 2: invokestatic  org/junit/Assert.assertTrue:(Ljava/lang/String;Z)V
         * 5: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::assertFalse(QString message, bool condition) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: iload_1
         * 2: ifne          9
         * 5: iconst_1
         * 6: goto          10
         * 9: iconst_0
         * 10: invokestatic  org/junit/Assert.assertTrue:(Ljava/lang/String;Z)V
         * 13: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::assertFalse(bool condition) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: iload_0
         * 2: invokestatic  org/junit/Assert.assertFalse:(Ljava/lang/String;Z)V
         * 5: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::fail(QString message) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: ifnonnull     12
         * 4: new           java/lang/AssertionError
         * 7: dup
         * 8: invokespecial java/lang/AssertionError."<init>":()V
         * 11: athrow
         * 12: new           java/lang/AssertionError
         * 15: dup
         * 16: aload_0
         * 17: invokespecial java/lang/AssertionError."<init>":(Ljava/lang/Object;)V
         * 20: athrow
         *  */
        // </editor-fold>
        if (message.isEmpty())
        {
            throw AssertionError("unknown error");
        }
        qDebug() <<"AssertionError: " + message;
        throw AssertionError(message);
    }

    /*public*/ /*static*/ void Assert::fail() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 4: return
         *  */
        // </editor-fold>
        throw AssertionError(tr("Assert failed"));
    }

    /*public*/ /*static*/ void Assert::assertEquals(QString message, QObject* expected, QObject* actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: aload_2
         * 2: invokestatic  org/junit/Assert.equalsRegardingNull:(Ljava/lang/Object;Ljava/lang/Object;)Z
         * 5: ifeq          9
         * 8: return
         * 9: aload_1
         * 10: instanceof    java/lang/String
         * 13: ifeq          51
         * 16: aload_2
         * 17: instanceof    java/lang/String
         * 20: ifeq          51
         * 23: aload_0
         * 24: ifnonnull     32
         * 27: ldc
         * 29: goto          33
         * 32: aload_0
         * 33: astore_3
         * 34: new           org/junit/ComparisonFailure
         * 37: dup
         * 38: aload_3
         * 39: aload_1
         * 40: checkcast     java/lang/String
         * 43: aload_2
         * 44: checkcast     java/lang/String
         * 47: invokespecial org/junit/ComparisonFailure."<init>":(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
         * 50: athrow
         * 51: aload_0
         * 52: aload_1
         * 53: aload_2
         * 54: invokestatic  org/junit/Assert.failNotEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 57: return
         *  */
        // </editor-fold>
        if(expected != actual)
        {
            fail(message);
        }
        if(actual != nullptr && expected != nullptr)
        {
            if(actual->metaObject()->className() != expected->metaObject()->className())
                fail(tr("%1 message objects not same %2 vs %3").arg(actual->metaObject()->className()).arg(expected->metaObject()->className()));
        }
    }

    /*public*/ /*static*/ void Assert::assertEquals(QString message, bool expected, bool actual)
    {
        if(expected != actual)
            fail(tr("%1 not equal expected '%2' vs '%3'").arg(message).arg(expected?"true":"false").arg(actual?"true":"false"));

    }

    /*public*/ /*static*/ void Assert::assertEquals(QString message, QString expected, QString actual)
    {
    if(expected != actual)
        fail(tr("%1 not equal expected '%2' vs '%3'").arg(message).arg(expected).arg(actual));
    }

    /*public*/ /*static*/ void Assert::assertEquals(QString message, double expected, double actual)
    {
    if(expected != actual)
        fail(tr("%1 not equal expected '%2' vs '%3'").arg(message).arg(expected).arg(actual));

    }

    /*public*/ /*static*/ void Assert::assertEquals(QString message, float expected, float actual)
    {
    if(expected != actual)
        fail(tr("%1 not equal expected '%2' vs '%3'").arg(message).arg(expected).arg(actual));
    }

    /*public*/ /*static*/ void Assert::assertEquals(QString message, int expected, int actual)
    {
    if(expected != actual)
        fail(tr("%1 not equal expected '0x%2' vs '0x%3'").arg(message).arg(expected,0,16).arg(actual,0,16));
    }

    /*public*/ /*static*/ void Assert::assertEquals(QDomElement expected, QDomElement actual, QDomElement delta)
    {
        if(expected.tagName() != actual.tagName())
            fail(tr("unequal elements expected %1 vs %2").arg(expected.tagName()).arg(actual.tagName()));

    }

#if 0
    private static bool equalsRegardingNull(Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: ifnonnull     14
         * 4: aload_1
         * 5: ifnonnull     12
         * 8: iconst_1
         * 9: goto          13
         * 12: iconst_0
         * 13: ireturn
         * 14: aload_0
         * 15: aload_1
         * 16: invokestatic  org/junit/Assert.isEquals:(Ljava/lang/Object;Ljava/lang/Object;)Z
         * 19: ireturn
         *  */
        // </editor-fold>
    }

    private static bool isEquals(Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: invokevirtual java/lang/Object.equals:(Ljava/lang/Object;)Z
         * 5: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertEquals(Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }
#endif
/*public*/ /*static*/ void Assert::assertEquals(QString expected, QString actual) {
    if(expected != actual)
    {
        fail(tr("Strings do not match: expected \"%1\" vs \"%2\"").arg(expected).arg(actual));
    }
}
/*public*/ /*static*/ void Assert::assertEquals(bool expected, bool actual) {
    if(expected != actual)
    {
        fail(tr("Strings do not match: expected \"%1\" vs \"%2\"").arg(expected).arg(actual));
    }
}


/*public*/ /*static*/ void Assert::assertNotEquals(QString message, QObject* unexpected, QObject* actual) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: aload_2
     * 2: invokestatic  org/junit/Assert.equalsRegardingNull:(Ljava/lang/Object;Ljava/lang/Object;)Z
     * 5: ifeq          13
     * 8: aload_0
     * 9: aload_2
     * 10: invokestatic  org/junit/Assert.failEquals:(Ljava/lang/String;Ljava/lang/Object;)V
     * 13: return
     *  */
    // </editor-fold>
    if(actual->metaObject()->className() == unexpected->metaObject()->className())
        fail(tr("%1 message objects same %2 vs %3").arg(actual->metaObject()->className()).arg(unexpected->metaObject()->className()));
    if(unexpected == actual)
    {
        fail(message);
    }
}
/*public*/ /*static*/ void Assert::assertNotEquals(QString message, QString unexpected, QString actual)
{
    if(unexpected == actual)
    {
        fail(tr("%1 equal '%2' vs '%3'").arg(message).arg(unexpected).arg(actual));
    }
}


/*public*/ /*static*/ void Assert::assertNotEquals(QString expected, QString actual) {
    if(expected == actual)
    {
        fail(tr("Strings should not match: \"%1\" vs \"%2\"").arg(expected).arg(actual));
    }
}


/*public*/ /*static*/ void Assert::assertNotEquals(QObject* unexpected, QObject* actual) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aconst_null
     * 1: aload_0
     * 2: aload_1
     * 3: invokestatic  org/junit/Assert.assertNotEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
     * 6: return
     *  */
    // </editor-fold>
    if(actual->metaObject()->className() == unexpected->metaObject()->className())
        fail(tr("%1 message objects same %2 vs %3").arg(actual->metaObject()->className()).arg(unexpected->metaObject()->className()));
    if(unexpected == actual)
    {
        fail(tr("Objects should not be equal"));
    }
}
#if 0
    private static void failEquals(String message, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc           Values should be different.
         * 2: astore_2
         * 3: aload_0
         * 4: ifnull        27
         * 7: new           java/lang/StringBuilder
         * 10: dup
         * 11: invokespecial java/lang/StringBuilder."<init>":()V
         * 14: aload_0
         * 15: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 18: ldc           .
         * 20: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 23: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 26: astore_2
         * 27: new           java/lang/StringBuilder
         * 30: dup
         * 31: invokespecial java/lang/StringBuilder."<init>":()V
         * 34: aload_2
         * 35: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 38: ldc           Actual:
         * 40: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 43: aload_1
         * 44: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
         * 47: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 50: astore_2
         * 51: aload_2
         * 52: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 55: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotEquals(String message, long unexpected, long actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: lload_1
         * 1: lload_3
         * 2: lcmp
         * 3: ifne          14
         * 6: aload_0
         * 7: lload_3
         * 8: invokestatic  java/lang/Long.valueOf:(J)Ljava/lang/Long;
         * 11: invokestatic  org/junit/Assert.failEquals:(Ljava/lang/String;Ljava/lang/Object;)V
         * 14: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotEquals(long unexpected, long actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: lload_0
         * 2: lload_2
         * 3: invokestatic  org/junit/Assert.assertNotEquals:(Ljava/lang/String;JJ)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotEquals(String message, double unexpected, double actual, double delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: dload_1
         * 1: dload_3
         * 2: dload         5
         * 4: invokestatic  org/junit/Assert.doubleIsDifferent:(DDD)Z
         * 7: ifne          18
         * 10: aload_0
         * 11: dload_3
         * 12: invokestatic  java/lang/Double.valueOf:(D)Ljava/lang/Double;
         * 15: invokestatic  org/junit/Assert.failEquals:(Ljava/lang/String;Ljava/lang/Object;)V
         * 18: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotEquals(double unexpected, double actual, double delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: dload_0
         * 2: dload_2
         * 3: dload         4
         * 5: invokestatic  org/junit/Assert.assertNotEquals:(Ljava/lang/String;DDD)V
         * 8: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotEquals(float unexpected, float actual, float delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: fload_0
         * 2: fload_1
         * 3: fload_2
         * 4: invokestatic  org/junit/Assert.assertNotEquals:(Ljava/lang/String;FFF)V
         * 7: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, Object[] expecteds, Object[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(Object[] expecteds, Object[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[Ljava/lang/Object;[Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, bool[] expecteds, bool[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(bool[] expecteds, bool[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[Z[Z)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, byte[] expecteds, byte[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(byte[] expecteds, byte[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[B[B)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, char[] expecteds, char[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(char[] expecteds, char[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[C[C)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, short[] expecteds, short[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(short[] expecteds, short[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[S[S)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, int[] expecteds, int[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(int[] expecteds, int[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[I[I)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, long[] expecteds, long[] actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.internalArrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(long[] expecteds, long[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[J[J)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, double[] expecteds, double[] actuals, double delta) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           org/junit/internal/InexactComparisonCriteria
         * 3: dup
         * 4: dload_3
         * 5: invokespecial org/junit/internal/InexactComparisonCriteria."<init>":(D)V
         * 8: aload_0
         * 9: aload_1
         * 10: aload_2
         * 11: invokevirtual org/junit/internal/InexactComparisonCriteria.arrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 14: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(double[] expecteds, double[] actuals, double delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: dload_2
         * 4: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[D[DD)V
         * 7: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(String message, float[] expecteds, float[] actuals, float delta) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           org/junit/internal/InexactComparisonCriteria
         * 3: dup
         * 4: fload_3
         * 5: invokespecial org/junit/internal/InexactComparisonCriteria."<init>":(F)V
         * 8: aload_0
         * 9: aload_1
         * 10: aload_2
         * 11: invokevirtual org/junit/internal/InexactComparisonCriteria.arrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 14: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertArrayEquals(float[] expecteds, float[] actuals, float delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: fload_2
         * 4: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[F[FF)V
         * 7: return
         *  */
        // </editor-fold>
    }

    private static void internalArrayEquals(String message, Object expecteds, Object actuals) throws ArrayComparisonFailure {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           org/junit/internal/ExactComparisonCriteria
         * 3: dup
         * 4: invokespecial org/junit/internal/ExactComparisonCriteria."<init>":()V
         * 7: aload_0
         * 8: aload_1
         * 9: aload_2
         * 10: invokevirtual org/junit/internal/ExactComparisonCriteria.arrayEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 13: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertEquals(String message, double expected, double actual, double delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: dload_1
         * 1: dload_3
         * 2: dload         5
         * 4: invokestatic  org/junit/Assert.doubleIsDifferent:(DDD)Z
         * 7: ifeq          22
         * 10: aload_0
         * 11: dload_1
         * 12: invokestatic  java/lang/Double.valueOf:(D)Ljava/lang/Double;
         * 15: dload_3
         * 16: invokestatic  java/lang/Double.valueOf:(D)Ljava/lang/Double;
         * 19: invokestatic  org/junit/Assert.failNotEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 22: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertEquals(String message, float expected, float actual, float delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: fload_1
         * 1: fload_2
         * 2: fload_3
         * 3: invokestatic  org/junit/Assert.floatIsDifferent:(FFF)Z
         * 6: ifeq          21
         * 9: aload_0
         * 10: fload_1
         * 11: invokestatic  java/lang/Float.valueOf:(F)Ljava/lang/Float;
         * 14: fload_2
         * 15: invokestatic  java/lang/Float.valueOf:(F)Ljava/lang/Float;
         * 18: invokestatic  org/junit/Assert.failNotEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 21: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotEquals(String message, float unexpected, float actual, float delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: fload_1
         * 1: fload_2
         * 2: fload_3
         * 3: invokestatic  org/junit/Assert.floatIsDifferent:(FFF)Z
         * 6: ifne          17
         * 9: aload_0
         * 10: fload_2
         * 11: invokestatic  java/lang/Float.valueOf:(F)Ljava/lang/Float;
         * 14: invokestatic  org/junit/Assert.failEquals:(Ljava/lang/String;Ljava/lang/Object;)V
         * 17: return
         *  */
        // </editor-fold>
    }

    private static bool doubleIsDifferent(double d1, double d2, double delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: dload_0
         * 1: dload_2
         * 2: invokestatic  java/lang/Double.compare:(DD)I
         * 5: ifne          10
         * 8: iconst_0
         * 9: ireturn
         * 10: dload_0
         * 11: dload_2
         * 12: dsub
         * 13: invokestatic  java/lang/Math.abs:(D)D
         * 16: dload         4
         * 18: dcmpg
         * 19: ifgt          24
         * 22: iconst_0
         * 23: ireturn
         * 24: iconst_1
         * 25: ireturn
         *  */
        // </editor-fold>
    }

    private static bool floatIsDifferent(float f1, float f2, float delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: fload_0
         * 1: fload_1
         * 2: invokestatic  java/lang/Float.compare:(FF)I
         * 5: ifne          10
         * 8: iconst_0
         * 9: ireturn
         * 10: fload_0
         * 11: fload_1
         * 12: fsub
         * 13: invokestatic  java/lang/Math.abs:(F)F
         * 16: fload_2
         * 17: fcmpg
         * 18: ifgt          23
         * 21: iconst_0
         * 22: ireturn
         * 23: iconst_1
         * 24: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertEquals(long expected, long actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: lload_0
         * 2: lload_2
         * 3: invokestatic  org/junit/Assert.assertEquals:(Ljava/lang/String;JJ)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertEquals(String message, long expected, long actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: lload_1
         * 1: lload_3
         * 2: lcmp
         * 3: ifeq          18
         * 6: aload_0
         * 7: lload_1
         * 8: invokestatic  java/lang/Long.valueOf:(J)Ljava/lang/Long;
         * 11: lload_3
         * 12: invokestatic  java/lang/Long.valueOf:(J)Ljava/lang/Long;
         * 15: invokestatic  org/junit/Assert.failNotEquals:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 18: return
         *  */
        // </editor-fold>
    }

    @Deprecated
    /*public*/ static void assertEquals(double expected, double actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: dload_0
         * 2: dload_2
         * 3: invokestatic  org/junit/Assert.assertEquals:(Ljava/lang/String;DD)V
         * 6: return
         *  */
        // </editor-fold>
    }

    @Deprecated
    /*public*/ static void assertEquals(String message, double expected, double actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc           Use assertEquals(expected, actual, delta) to compare floating-point numbers
         * 2: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 5: return
         *  */
        // </editor-fold>
    }
#endif
    /*public*/ /*static*/ void Assert::assertEquals(double expected, double actual, double delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: dload_0
         * 2: dload_2
         * 3: dload         4
         * 5: invokestatic  org/junit/Assert.assertEquals:(Ljava/lang/String;DDD)V
         * 8: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::assertEquals(float expected, float actual, float delta) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: fload_0
         * 2: fload_1
         * 3: fload_2
         * 4: invokestatic  org/junit/Assert.assertEquals:(Ljava/lang/String;FFF)V
         * 7: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::assertNotNull(QString message, QObject* object) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: ifnull        9
         * 5: iconst_1
         * 6: goto          10
         * 9: iconst_0
         * 10: invokestatic  org/junit/Assert.assertTrue:(Ljava/lang/String;Z)V
         * 13: return
         *  */
        // </editor-fold>
    }
    /*public*/ /*static*/ void Assert::assertNotNull(QString message, QDomElement object)
    {
     if(object.isNull())
         fail(message);
    }

    /*public*/ /*static*/ void Assert::assertNotNull(QString message, int object)
    {
     if(object==0)
         fail(message);
    }
    /*public*/ /*static*/ void Assert::assertNotNull(QString message, QString object)
    {
     if(object.isEmpty())
         fail(message);
    }

    /*public*/ /*static*/ void Assert::assertNotNull(QObject* object) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: invokestatic  org/junit/Assert.assertNotNull:(Ljava/lang/String;Ljava/lang/Object;)V
         * 5: return
         *  */
        // </editor-fold>
    }
    /*public*/ /*static*/ void Assert::assertNotNull(QDomElement object)
    {
    if(object.isNull())
        fail("element not empty");
    }

    /*public*/ /*static*/ void Assert::assertNull(QString message, QObject* object) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: ifnonnull     5
         * 4: return
         * 5: aload_0
         * 6: aload_1
         * 7: invokestatic  org/junit/Assert.failNotNull:(Ljava/lang/String;Ljava/lang/Object;)V
         * 10: return
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ void Assert::assertNull(QObject* object) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: invokestatic  org/junit/Assert.assertNull:(Ljava/lang/String;Ljava/lang/Object;)V
         * 5: return
         *  */
        // </editor-fold>
    }
/*public*/ /*static*/ void Assert::assertNull(QString object) {
 if(!object.isEmpty())
     fail("string not empty");
}
/*public*/ /*static*/ void Assert::assertNull(QDomElement object) {
 if(!object.isNull())
     fail("element not empty");
}

/*public*/ /*static*/ void Assert::assertNull(QString message, QString object) {
 if(!object.isNull())
     fail(tr("%1, string not empty").arg(message));
}

#if 0
    private static void failNotNull(String message, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc
         * 2: astore_2
         * 3: aload_0
         * 4: ifnull        27
         * 7: new           java/lang/StringBuilder
         * 10: dup
         * 11: invokespecial java/lang/StringBuilder."<init>":()V
         * 14: aload_0
         * 15: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 18: ldc
         * 20: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 23: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 26: astore_2
         * 27: new           java/lang/StringBuilder
         * 30: dup
         * 31: invokespecial java/lang/StringBuilder."<init>":()V
         * 34: aload_2
         * 35: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 38: ldc           expected null, but was:<
         * 40: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 43: aload_1
         * 44: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
         * 47: ldc           >
         * 49: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 52: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 55: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 58: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertSame(String message, Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: aload_2
         * 2: if_acmpne     6
         * 5: return
         * 6: aload_0
         * 7: aload_1
         * 8: aload_2
         * 9: invokestatic  org/junit/Assert.failNotSame:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 12: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertSame(Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertSame:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotSame(String message, Object unexpected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: aload_2
         * 2: if_acmpne     9
         * 5: aload_0
         * 6: invokestatic  org/junit/Assert.failSame:(Ljava/lang/String;)V
         * 9: return
         *  */
        // </editor-fold>
    }

    /*public*/ static void assertNotSame(Object unexpected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aconst_null
         * 1: aload_0
         * 2: aload_1
         * 3: invokestatic  org/junit/Assert.assertNotSame:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    private static void failSame(String message) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc
         * 2: astore_1
         * 3: aload_0
         * 4: ifnull        27
         * 7: new           java/lang/StringBuilder
         * 10: dup
         * 11: invokespecial java/lang/StringBuilder."<init>":()V
         * 14: aload_0
         * 15: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 18: ldc
         * 20: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 23: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 26: astore_1
         * 27: new           java/lang/StringBuilder
         * 30: dup
         * 31: invokespecial java/lang/StringBuilder."<init>":()V
         * 34: aload_1
         * 35: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 38: ldc           expected not same
         * 40: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 43: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 46: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 49: return
         *  */
        // </editor-fold>
    }

    private static void failNotSame(String message, Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc
         * 2: astore_3
         * 3: aload_0
         * 4: ifnull        27
         * 7: new           java/lang/StringBuilder
         * 10: dup
         * 11: invokespecial java/lang/StringBuilder."<init>":()V
         * 14: aload_0
         * 15: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 18: ldc
         * 20: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 23: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 26: astore_3
         * 27: new           java/lang/StringBuilder
         * 30: dup
         * 31: invokespecial java/lang/StringBuilder."<init>":()V
         * 34: aload_3
         * 35: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 38: ldc           expected same:<
         * 40: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 43: aload_1
         * 44: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
         * 47: ldc           > was not:<
         * 49: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 52: aload_2
         * 53: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
         * 56: ldc           >
         * 58: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 61: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 64: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 67: return
         *  */
        // </editor-fold>
    }

    private static void failNotEquals(String message, Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.format:(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/String;
         * 6: invokestatic  org/junit/Assert.fail:(Ljava/lang/String;)V
         * 9: return
         *  */
        // </editor-fold>
    }

    static String format(String message, Object expected, Object actual) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc
         * 2: astore_3
         * 3: aload_0
         * 4: ifnull        36
         * 7: aload_0
         * 8: ldc
         * 10: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
         * 13: ifne          36
         * 16: new           java/lang/StringBuilder
         * 19: dup
         * 20: invokespecial java/lang/StringBuilder."<init>":()V
         * 23: aload_0
         * 24: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 27: ldc
         * 29: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 32: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 35: astore_3
         * 36: aload_1
         * 37: invokestatic  java/lang/String.valueOf:(Ljava/lang/Object;)Ljava/lang/String;
         * 40: astore        4
         * 42: aload_2
         * 43: invokestatic  java/lang/String.valueOf:(Ljava/lang/Object;)Ljava/lang/String;
         * 46: astore        5
         * 48: aload         4
         * 50: aload         5
         * 52: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
         * 55: ifeq          101
         * 58: new           java/lang/StringBuilder
         * 61: dup
         * 62: invokespecial java/lang/StringBuilder."<init>":()V
         * 65: aload_3
         * 66: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 69: ldc           expected:
         * 71: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 74: aload_1
         * 75: aload         4
         * 77: invokestatic  org/junit/Assert.formatClassAndValue:(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/String;
         * 80: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 83: ldc            but was:
         * 85: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 88: aload_2
         * 89: aload         5
         * 91: invokestatic  org/junit/Assert.formatClassAndValue:(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/String;
         * 94: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 97: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 100: areturn
         * 101: new           java/lang/StringBuilder
         * 104: dup
         * 105: invokespecial java/lang/StringBuilder."<init>":()V
         * 108: aload_3
         * 109: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 112: ldc           expected:<
         * 114: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 117: aload         4
         * 119: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 122: ldc           > but was:<
         * 124: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 127: aload         5
         * 129: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 132: ldc           >
         * 134: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 137: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 140: areturn
         *  */
        // </editor-fold>
    }

    private static String formatClassAndValue(Object value, String valueString) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: ifnonnull     9
         * 4: ldc           null
         * 6: goto          16
         * 9: aload_0
         * 10: invokevirtual java/lang/Object.getClass:()Ljava/lang/Class;
         * 13: invokevirtual java/lang/Class.getName:()Ljava/lang/String;
         * 16: astore_2
         * 17: new           java/lang/StringBuilder
         * 20: dup
         * 21: invokespecial java/lang/StringBuilder."<init>":()V
         * 24: aload_2
         * 25: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 28: ldc           <
         * 30: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 33: aload_1
         * 34: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 37: ldc           >
         * 39: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 42: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 45: areturn
         *  */
        // </editor-fold>
    }

    @Deprecated
    /*public*/ static void assertEquals(String message, Object[] expecteds, Object[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/junit/Assert.assertArrayEquals:(Ljava/lang/String;[Ljava/lang/Object;[Ljava/lang/Object;)V
         * 6: return
         *  */
        // </editor-fold>
    }

    @Deprecated
    /*public*/ static void assertEquals(Object[] expecteds, Object[] actuals) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: invokestatic  org/junit/Assert.assertArrayEquals:([Ljava/lang/Object;[Ljava/lang/Object;)V
         * 5: return
         *  */
        // </editor-fold>
    }

    /*public*/ static <T extends Object> void assertThat(T actual, Matcher<? super T> matcher) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc
         * 2: aload_0
         * 3: aload_1
         * 4: invokestatic  org/junit/Assert.assertThat:(Ljava/lang/String;Ljava/lang/Object;Lorg/hamcrest/Matcher;)V
         * 7: return
         *  */
        // </editor-fold>
    }

    /*public*/ static <T extends Object> void assertThat(String reason, T actual, Matcher<? super T> matcher) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: invokestatic  org/hamcrest/MatcherAssert.assertThat:(Ljava/lang/String;Ljava/lang/Object;Lorg/hamcrest/Matcher;)V
         * 6: return
         *  */
        // </editor-fold>
    }
#endif
    AssertionError::AssertionError(QString s)
    {
     msg = s;
    }

