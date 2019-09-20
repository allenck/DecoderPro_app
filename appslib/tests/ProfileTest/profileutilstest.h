#ifndef PROFILEUTILSTEST_H
#define PROFILEUTILSTEST_H

#include <QObject>

class TemporaryFolder;
class Logger;
class ProfileUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit ProfileUtilsTest(QObject *parent = nullptr);
    /*public*/ void setUp();
    /*public*/ void tearDown();
    /*public*/ void testCopy();
    /*public*/ void testCopyToActive();

signals:

public slots:

private:
    static Logger* log;
    /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();

};

#endif // PROFILEUTILSTEST_H
