#ifndef STOREANDLOADTEST_H
#define STOREANDLOADTEST_H

#include <QObject>
#include "threadingutil.h"
#include "base.h"
#include "malesocket.h"

class File;
class Logger;
class StoreAndLoadTest : public QObject
{
  Q_OBJECT
 public:
  explicit StoreAndLoadTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setUp();
  Q_INVOKABLE /*public*/  void tearDown();

 signals:

 public slots:
  /*public*/  void testLogixNGs();

 private:
  static Logger* log;
  /*private*/ void addHeader(File* inFile, File* outFile) /*throws FileNotFoundException, IOException*/;
  /*private*/ static /*final*/ QStringList initValues;// = new String[]{
  /*private*/ void addVariables(MaleSocket* maleSocket);

  friend class StoreAndLoadTest_run1;
};

class StoreAndLoadTest_run1 : public RunnableWithBase
{
  Q_OBJECT
  StoreAndLoadTest* t;
 public:
  StoreAndLoadTest_run1(StoreAndLoadTest* t) {this->t = t;}
  void run(Base* b)
  {
   if(qobject_cast<MaleSocket*>(b->bself())) {
       t->addVariables((MaleSocket*) b->bself());
   }
  }
};

#endif // STOREANDLOADTEST_H
