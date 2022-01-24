#ifndef IDENTIFYDECODERTEST_H
#define IDENTIFYDECODERTEST_H

#include <QObject>
#include "progdebugger.h"
#include "identifydecoder.h"

class IdentifyDecoderTest : public QObject
{
  Q_OBJECT
 public:
  explicit IdentifyDecoderTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

 signals:

 public slots:
  /*public*/ void testIdentifyStandard();
  /*public*/ void testIdentifyHarman();
  /*public*/ void testIdentifyTsu2();
  /*public*/ void testIdentifyHornby1();
  /*public*/ void testIdentifyHornby2();
  /*public*/ void testIdentifyHornby3();
  /*public*/ void testIdentifyHornby4();
  /*public*/ void testIdentifyHornby5();

 private:
  static int cvRead;// = -1;
  /*private*/ ProgDebugger* p;

  friend class IDProgDebugger;
};

class IDIdentifyDecoder : public IdentifyDecoder
{
  Q_OBJECT
  IdentifyDecoderTest* test;
 public:
  IDIdentifyDecoder(ProgDebugger* p, IdentifyDecoderTest* test) : IdentifyDecoder(p){
    this->test = test;
  }
  //@Override
  /*public*/ void done(int mfgID, int modelID, int productID) {
  }

  //@Override
  /*public*/ void message(QString m) {
  }

  //@Override
  /*public*/ void error() {
  }
  QObject* self() {return(QObject*)this;}
};

class IDProgDebugger : public ProgDebugger
{
  Q_OBJECT
  IdentifyDecoderTest* test;
 public:
  IDProgDebugger(IdentifyDecoderTest* test) {this->test = test;}
  //@Override
  /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException) {
      test->cvRead = (CV.toInt());
  }

};
#endif // IDENTIFYDECODERTEST_H
