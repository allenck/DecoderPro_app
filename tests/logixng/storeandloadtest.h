#ifndef STOREANDLOADTEST_H
#define STOREANDLOADTEST_H

#include <QObject>

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

};

#endif // STOREANDLOADTEST_H
