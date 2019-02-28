#include "testbase.h"
#include <QMenu>
#include <QWidget>

TestBase::TestBase(QObject *parent) : QObject(parent) {}
QString TestBase::base1() { return "base1";}
QString TestBase::base2() { return "base2";}
QString TestBase::base3() { return "base3";}
QString TestBase::base4() { return "base4";}

QWidget* TestBase::getWidget() { return new QWidget();}

TestIntermediate::TestIntermediate(QObject *parent) : TestBase(parent) {}
QString TestIntermediate::intermediate1() { return "intermediate1";}
QString TestIntermediate::intermediate2() { return "intermediate2";}
QString TestIntermediate::intermediate3() { return "intermediate3";}
QString TestIntermediate::base3() { return "base3";}
QMenu* TestIntermediate::getMenu() { return new QMenu("MenuText");}

TestPrimary::TestPrimary(QObject *parent) : TestIntermediate(parent) {}
QString TestPrimary::primary1() { return "primary1";}
QString TestPrimary::primary2() { return "primary2";}
QString TestPrimary::base4() { return "primary4";}

int TestPrimary::getInt() {return 1234;}
