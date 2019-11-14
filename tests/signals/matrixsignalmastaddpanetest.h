#ifndef MATRIXSIGNALMASTADDPANETEST_H
#define MATRIXSIGNALMASTADDPANETEST_H
#include "abstractsignalmastaddpanetestbase.h"
#include "defaultsignalappearancemap.h"
#include "matrixsignalmast.h"

class QCheckBox;
class MatrixSignalMastAddPaneTest : public AbstractSignalMastAddPaneTestBase
{
 Q_OBJECT
public:
 MatrixSignalMastAddPaneTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testSetMastOK();
 /*public*/ void testSetMastReject();
 /*public*/ void testEditAndDisableViaGui();
private:
 QCheckBox* findBox(QWidget* widget, QString text);


protected:
 //@Override
 /*protected*/ SignalMastAddPane* getOTT();

};

class DefaultSignalAppearanceMapO1 : public DefaultSignalAppearanceMap
{
 Q_OBJECT
 MatrixSignalMastAddPaneTest* test;
public:
 DefaultSignalAppearanceMapO1(QString systemName, QString userName, MatrixSignalMastAddPaneTest* test) : DefaultSignalAppearanceMap(systemName, userName) {this->test = test;}
 //@Override
 /*public*/ QListIterator<QString> getAspects() {
//     return java.util.Collections.enumeration(
//         java.util.Arrays.asList(
  return QStringListIterator(
             QList<QString>() << "Approach"<<"Stop"<<"Unlit");
     }
};
class DefaultSignalAppearanceMapO2 : public DefaultSignalAppearanceMap
{
 Q_OBJECT
 MatrixSignalMast* mast;
public:
 DefaultSignalAppearanceMapO2(QString systemName, MatrixSignalMast* mast) : DefaultSignalAppearanceMap(systemName) {this->mast = mast;}
 //@Override
 /*public*/ QListIterator<QString> getAspects() {
//     return java.util.Collections.enumeration(
//         java.util.Arrays.asList(
  return QStringListIterator(
             QList<QString>() << "Approach"<<"Stop"<<"Unlit");
     }
};

class MatrixSignalMastO1 : public MatrixSignalMast
{
 Q_OBJECT
 MatrixSignalMast* mast;
public:
 MatrixSignalMastO1(QString systemName, QString userName, MatrixSignalMast* mast) : MatrixSignalMast(systemName, userName)
 {
  this->mast = mast;
  setLastRef(3);
 }
 //@Override
 /*public*/ QStringListIterator getAspects() { return QStringListIterator(mast->getAllKnownAspects().toList()); }
};

#endif // MATRIXSIGNALMASTADDPANETEST_H
