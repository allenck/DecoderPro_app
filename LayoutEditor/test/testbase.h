#ifndef TESTBASE_H
#define TESTBASE_H

#include <QObject>

class QMenu;
class TestBase : public QObject
{
 Q_OBJECT
public:
 explicit TestBase(QObject *parent = nullptr);
 QString base1();
 QString base2();
 virtual QString base3();
 virtual QString base4();
 QWidget* getWidget();
signals:

public slots:
};

QT_DEPRECATED class TestIntermediate : public TestBase
{
 Q_OBJECT
public:
 explicit TestIntermediate(QObject *parent = nullptr);
 QString intermediate1();
 QString intermediate2();
 Q_INVOKABLE QT_DEPRECATED QString base3();
 virtual QString intermediate3();
 QMenu* getMenu();

};

class TestPrimary : public TestIntermediate
{
 Q_OBJECT
public:
 explicit TestPrimary(QObject *parent = nullptr);
 QString primary1();
 QT_DEPRECATED QString primary2();
 QString base4();
 int getInt();
};



#endif // TESTBASE_H
