#include "namedbeanusernamecomparatortest.h"
#include "junitutil.h"
#include "turnout.h"
#include "assert1.h"
#include "instancemanager.h"
#include "namedbeanusernamecomparator.h"
#include <QSet>

NamedBeanUserNameComparatorTest::NamedBeanUserNameComparatorTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class NamedBeanUserNameComparatorTest {

    //@Test
    /*public*/ void NamedBeanUserNameComparatorTest::testNonNullUserNameCases() {
        NamedBeanUserNameComparator<Turnout*>* t = new NamedBeanUserNameComparator<Turnout*>();

        Turnout*  it1 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        Turnout*  it10 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT10");
        Turnout*  it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");
        it1->setUserName(it1->getSystemName());
        it10->setUserName(it10->getSystemName());
        it2->setUserName(it2->getSystemName());

        Assert::assertEquals("IT1 == IT1", 0, t->compare(it1, it1), __FILE__, __LINE__);

        Assert::assertEquals("IT1 < IT2", -1, t->compare(it1, it2), __FILE__, __LINE__);
        Assert::assertEquals("IT2 > IT1", +1, t->compare(it2, it1), __FILE__, __LINE__);

        Assert::assertEquals("IT10 > IT2", +1, t->compare(it10, it2), __FILE__, __LINE__);
        Assert::assertEquals("IT2 < IT10", -1, t->compare(it2, it10), __FILE__, __LINE__);

        it1->setUserName("A");
        it10->setUserName("B");
        it2->setUserName("C");

        Assert::assertEquals("A == A", 0, t->compare(it1, it1), __FILE__, __LINE__);

        Assert::assertEquals("A < C", -1, t->compare(it1, it2), __FILE__, __LINE__);
        Assert::assertEquals("C > A", +1, t->compare(it2, it1), __FILE__, __LINE__);

        Assert::assertEquals("B < C", -1, t->compare(it10, it2), __FILE__, __LINE__);
        Assert::assertEquals("C > B", +1, t->compare(it2, it10), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void NamedBeanUserNameComparatorTest::testOneLetterCases() {
        NamedBeanUserNameComparator<Turnout*>* t = new NamedBeanUserNameComparator<Turnout*>();

        Turnout*  it1 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        Turnout*  it10 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT10");
        Turnout*  it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");

        Assert::assertEquals("IT1 == IT1", 0, t->compare(it1, it1), __FILE__, __LINE__);

        Assert::assertEquals("IT1 < IT2", -1, t->compare(it1, it2), __FILE__, __LINE__);
        Assert::assertEquals("IT2 > IT1", +1, t->compare(it2, it1), __FILE__, __LINE__);

        Assert::assertEquals("IT10 > IT2", +1, t->compare(it10, it2), __FILE__, __LINE__);
        Assert::assertEquals("IT2 < IT10", -1, t->compare(it2, it10), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void NamedBeanUserNameComparatorTest::testTwoLetterCases() {
        NamedBeanUserNameComparator<Turnout*>* t = new NamedBeanUserNameComparator<Turnout*>();

        Turnout*  i2t1 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I2T1");
        Turnout*  i2t10 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I2T10");
        Turnout*  i2t2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I2T2");

        Assert::assertEquals("I2T1 == I2T1", 0, t->compare(i2t1, i2t1), __FILE__, __LINE__);

        Assert::assertEquals("I2T1 < I2T2", -1, t->compare(i2t1, i2t2), __FILE__, __LINE__);
        Assert::assertEquals("I2T2 > I2T1", +1, t->compare(i2t2, i2t1), __FILE__, __LINE__);

        Assert::assertEquals("I2T10 > I2T2", +1, t->compare(i2t10, i2t2), __FILE__, __LINE__);
        Assert::assertEquals("I2T2 < I2T10", -1, t->compare(i2t2, i2t10), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void NamedBeanUserNameComparatorTest::testThreeLetterCases() {
        NamedBeanUserNameComparator<Turnout*>* t = new NamedBeanUserNameComparator<Turnout*>();

        Turnout*  i23t1 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T1");
        Turnout*  i23t10 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T10");
        Turnout*  i23t2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T2");

        Assert::assertEquals("I23T1 == I23T1", 0, t->compare(i23t1, i23t1), __FILE__, __LINE__);

        Assert::assertEquals("I23T1 < I23T2", -1, t->compare(i23t1, i23t2), __FILE__, __LINE__);
        Assert::assertEquals("I23T2 > I23T1", +1, t->compare(i23t2, i23t1), __FILE__, __LINE__);

        Assert::assertEquals("I23T10 > I23T2", +1, t->compare(i23t10, i23t2), __FILE__, __LINE__);
        Assert::assertEquals("I23T2 < I23T10", -1, t->compare(i23t2, i23t10), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void NamedBeanUserNameComparatorTest::testMixedUserNamesSystemNamesCase() {
        NamedBeanUserNameComparator<Turnout*>* c = new NamedBeanUserNameComparator<Turnout*>();

        Turnout*  i23t1 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T1");
        Turnout*  i23t10 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T10");
        Turnout*  i23t2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T2");
        Turnout*  i23t3 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T3");
        Turnout*  i23t4 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T4");
        Turnout*  i23t5 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T5");
        Turnout*  i23t6 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T6");
        Turnout*  i23t7 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T7");
        Turnout*  i23t8 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T8");
        Turnout*  i23t9 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("I23T9");

        i23t3->setUserName("Name 4");
        i23t4->setUserName("Name 3");
        i23t5->setUserName("A name");

        // expected sort order:
        // i23t5
        // i23t1
        // i23t2
        // i23t6
        // i23t7
        // i23t8
        // i23t9
        // i23t10
        // i23t4
        // i23t3
        Assert::assertEquals("I23T1 == I23T1", 0, c->compare(i23t1, i23t1), __FILE__, __LINE__);
        Assert::assertEquals("I23T2 == I23T2", 0, c->compare(i23t2, i23t2), __FILE__, __LINE__);
        Assert::assertEquals("I23T3 == I23T3", 0, c->compare(i23t3, i23t3), __FILE__, __LINE__);
        Assert::assertEquals("I23T4 == I23T4", 0, c->compare(i23t4, i23t4), __FILE__, __LINE__);
        Assert::assertEquals("I23T5 == I23T5", 0, c->compare(i23t5, i23t5), __FILE__, __LINE__);
        Assert::assertEquals("I23T6 == I23T6", 0, c->compare(i23t6, i23t6), __FILE__, __LINE__);
        Assert::assertEquals("I23T7 == I23T7", 0, c->compare(i23t7, i23t7), __FILE__, __LINE__);
        Assert::assertEquals("I23T8 == I23T8", 0, c->compare(i23t8, i23t8), __FILE__, __LINE__);
        Assert::assertEquals("I23T9 == I23T9", 0, c->compare(i23t9, i23t9), __FILE__, __LINE__);
        Assert::assertEquals("I23T10 == I23T10", 0, c->compare(i23t10, i23t10), __FILE__, __LINE__);

        Assert::assertEquals("I23T1 < I23T2", -1, c->compare(i23t1, i23t2), __FILE__, __LINE__);
        Assert::assertEquals("I23T2 > I23T1", +1, c->compare(i23t2, i23t1), __FILE__, __LINE__);

        Assert::assertEquals("I23T10 > I23T2", +1, c->compare(i23t10, i23t2), __FILE__, __LINE__);
        Assert::assertEquals("I23T2 < I23T10", -1, c->compare(i23t2, i23t10), __FILE__, __LINE__);

        Assert::assertEquals("I23T4 < I23T3", -1, c->compare(i23t4, i23t3), __FILE__, __LINE__);
        Assert::assertEquals("I23T3 > I23T4", +1, c->compare(i23t3, i23t4), __FILE__, __LINE__);

        Assert::assertEquals("I23T5 < I23T1", -1, c->compare(i23t5, i23t1), __FILE__, __LINE__);
        Assert::assertEquals("I23T1 > I23T5", +1, c->compare(i23t1, i23t5), __FILE__, __LINE__);

        QSet<Turnout*> set = QSet<Turnout*>();
#if 0 // TODO:
        set.unite(((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getNamedBeanSet());
        Assert::assertArrayEquals(
                QVector<Turnout*()<<i23t5<< i23t1<< i23t2<< i23t6<< i23t7<< i23t8<< i23t9<< i23t10<< i23t4<< i23t3,
                set.toArray(), __FILE__, __LINE__); //[set->size()]));
#endif
    }


    //@Test
    /*public*/ void NamedBeanUserNameComparatorTest::testSystemSpecificCase() {
        NamedBeanUserNameComparator<Turnout*>* t = new NamedBeanUserNameComparator<Turnout*>();

        // this just checks that the local sort is called
        Turnout*  it1 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        Turnout*  it2 = new AbstractTurnoutO2("IT2", this);
//        {

//            @Override
//            protected void forwardCommandChangeToLayout(int s) {
//            }

//            @Override
//            protected void turnoutPushbuttonLockout(boolean b) {
//            }

//            @Override
//            /*public*/ int compareSystemNameSuffix(String suffix1, String suffix2, jmri.NamedBean n) {
//                hit = true;
//                return super.compareSystemNameSuffix(suffix1, suffix2, n);
//            }
//        };

        hit = false;
        Assert::assertEquals("IT1 < IT2", -1, t->compare(it1, it2), __FILE__, __LINE__);
        Assert::assertFalse(hit, __FILE__, __LINE__);

        hit = false;
        Assert::assertEquals("IT2 < IT1", +1, t->compare(it2, it1), __FILE__, __LINE__);
        Assert::assertTrue(hit, __FILE__, __LINE__);
    }

    //@Before
    /*public*/ void NamedBeanUserNameComparatorTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initInternalTurnoutManager();
    }

    //@After
    /*public*/ void NamedBeanUserNameComparatorTest::tearDown() {
        JUnitUtil::tearDown();
    }
//template class NamedBeanUserNameComparator<Turnout*>;
