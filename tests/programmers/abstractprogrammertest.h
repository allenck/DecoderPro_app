#ifndef ABSTRACTPROGRAMMERTEST_H
#define ABSTRACTPROGRAMMERTEST_H
#include "programmertestbase.h"
#include "abstractprogrammer.h"
#include "programmingmode.h"

class AbstractProgrammerTest : public ProgrammerTestBase
{
  Q_OBJECT
 public:
  AbstractProgrammerTest();
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE /*public*/ void tearDown();
 public slots:
  /*public*/ void testDefaultViaBestMode();
  /*public*/ void testRegisterFromCV();

};

class APTAbstractProgrammer : public AbstractProgrammer
{
  Q_OBJECT
  AbstractProgrammerTest* apt;
 public:
  APTAbstractProgrammer(AbstractProgrammerTest* apt) : AbstractProgrammer() {this->apt = apt;}
  //@Override
  /*public*/ QList<QString> getSupportedModes() {
      QList<QString> retval = QList<QString>();

      retval.append("DIRECTMODE");
      retval.append("PAGEMODE");
      retval.append("REGISTERMODE");

      return retval;
  }

  // Programmer implementation that uses getBestMode for setting default
  //@Override
  /*public*/ ProgrammingMode* getBestMode() override{ return ProgrammingMode::DIRECTMODE; }

  //@Override
  /*public*/ void writeCV(QString i, int j, ProgListener* l) throw (ProgrammerException)override{}
  //@Override
  /*public*/ void confirmCV(QString i, int j, ProgListener* l) throw (ProgrammerException)override{}
  //@Override
  /*public*/ void readCV(QString i, ProgListener* l) throw (ProgrammerException)override{}
  //@Override
  /*public*/ void timeout() override{}
  //@Override
  /*public*/ bool getCanRead() override{ return true;}
  QObject* self() {return (QObject*)this;}
};
#endif // ABSTRACTPROGRAMMERTEST_H
