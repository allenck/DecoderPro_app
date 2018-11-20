#include "arithmeticqualifier.h"

//ArithmeticQualifier::ArithmeticQualifier(QObject *parent) :
//    AbstractQualifier(parent)
//{
//}
/**
 * Mechanism to qualify on the value of a number.
 *<p>
 * The usual arithmetic operations are possible: ge, le, gt, lt, eq, ne.
 * The sense of this is comparing "current value" to "constant",
 * for example "current value gt 3".
 *<p>
 * You can also check whether the value "exists" (value of 1) or not (value of 0).
 * Comparisons with the value of a non-existant variable always fail.
 *
 * @author			Bob Jacobsen   Copyright (C) 2010, 2014
 * @version			$Revision: 26654 $
 *
 */
///*public*/ abstract class ArithmeticQualifier extends AbstractQualifier {
#if 0
    /*public*/ enum Test {
        GE("ge"), // greater than or equal
        LE("le"),
        GT("gt"),
        LT("lt"),
        EQ("eq"),
        NE("ne"),
        EXISTS("exists");

        Test(String relation) {
            this.relation = relation;
        }
        String relation;

        static Test decode(String r) {
            for (Test t : Test.values()) {
                if (t.relation.equals(r)) return t;
            }
            return NULL;
        }
    }

    Test test;
#endif
Test::Test(QString relation, QObject *parent) : QObject(parent) {this->relation = relation;}

/*static*/ Test::RELATIONS Test::decode(QString relation)
{
 if(relation =="ge") return GE; // greater than or equal
 if(relation =="le") return LE;
 if(relation =="gt") return GT;
 if(relation =="lt") return LT;
 if(relation =="eq") return EQ;
 if(relation =="ne") return NE;
 if(relation =="exists") return EXISTS;
    Q_ASSERT(false);
 return INVALID;
}
/*static*/ QString Test::toString(RELATIONS test)
{
    switch (test)
    {
     case Test::GE:
        return "ge";
     case Test::LE:
        return "le";
     case Test::GT:
        return "gt";
     case Test::LT:
        return "lt";
     case Test::EQ:
        return "eq";
     case Test::NE:
        return "ne";
    default:
       Logger::error(tr("Unexpected switch value: %1").arg(Test::toString(test)));
        return "invalid";
    }
}

/*public*/ ArithmeticQualifier::ArithmeticQualifier(VariableValue* watchedVal, int value, QString relation, QObject *parent) : AbstractQualifier(watchedVal, parent)
{
 //super(watchedVal);
 log = new Logger("ArithmeticQualifier");
 this->test = Test::decode(relation);
 this->value = value;
 warnedDoesntExist = false;

}

/*public*/ bool ArithmeticQualifier::currentDesiredState()
{
 if (returnFromExistsLogic()) return valueOfExistsLogic();

 return availableStateFromValue(watchedVal->getIntValue());
}

/*protected*/ bool ArithmeticQualifier::availableStateFromValue(int now)
{
 if (returnFromExistsLogic()) return valueOfExistsLogic();

 switch (test)
 {
  case Test::GE:
    return now >= value;
  case Test::LE:
    return now <= value;
  case Test::GT:
    return now > value;
  case Test::LT:
    return now < value;
  case Test::EQ:
    return now == value;
  case Test::NE:
    return now != value;
  default:
    log->error(tr("Unexpected switch value: %1").arg(Test::toString(test)));
    return false;
 }

}

/*public*/ void ArithmeticQualifier::update()
{
 setWatchedAvailable(currentDesiredState());
}

/*private*/ bool ArithmeticQualifier:: returnFromExistsLogic()
{
 if (test == Test::EXISTS) return true;
 if (watchedVal == NULL) return true;
 return false;
}

/*private*/ bool ArithmeticQualifier::valueOfExistsLogic()
{
 if (test == Test::EXISTS)
 {
  if (value == 0 && watchedVal == NULL) return true;
  if (value != 0 && watchedVal != NULL) return true;
  return false;
 }
 // here it's an arithmetic op on a variable
 if (watchedVal == NULL)
 {
  if (!warnedDoesntExist)
  {
   warnedDoesntExist = true;
   log->error("Arithmetic "+Test::toString(test)+" operation when watched value doesn't exist");
  }
  return true;  // this determines default for what happens when qualifier (watched) Variable isn't present
 }
 return false;  // should never be reached, because should only be invoked after returnFromExistsLogic() == true
}

