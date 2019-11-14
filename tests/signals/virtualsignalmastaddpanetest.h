#ifndef VIRTUALSIGNALMASTADDPANETEST_H
#define VIRTUALSIGNALMASTADDPANETEST_H
#include "abstractsignalmastaddpanetestbase.h"
#include "virtualsignalmast.h"
#include "defaultsignalappearancemap.h"

class QCheckBox;
class VirtualSignalMastAddPaneTest : public AbstractSignalMastAddPaneTestBase
{
 Q_OBJECT
public:
 VirtualSignalMastAddPaneTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testSetMast();
 /*public*/ void testCreateMast();
 /*public*/ void testCreateAndDisableViaGui();
 /*public*/ void testEditAndDisableViaGui();

private:
 QCheckBox* findBox(QWidget* widget, QString text);

protected:
 /*protected*/ SignalMastAddPane* getOTT();

};
class VirtualSignalMastO1 : public VirtualSignalMast
{
 Q_OBJECT
public:
 VirtualSignalMastO1(QString systemName, QString userName, int ref): VirtualSignalMast(systemName, userName)
 {
  setLastRef(ref);
 }
};

class DefaultSignalAppearanceMapO3 : public DefaultSignalAppearanceMap
{
 Q_OBJECT
 VirtualSignalMastAddPaneTest* test;
public:
 DefaultSignalAppearanceMapO3(QString systemName, VirtualSignalMastAddPaneTest* test) : DefaultSignalAppearanceMap(systemName)
 {
  this->test = test;
 }
 //@Override
 /*public*/ QStringListIterator getAspects() {
     return QStringListIterator(
             QStringList() << "Clear"<<"Approach Medium"<<"Advance Approach");
     }
};

class DefaultSignalAppearanceMapO4 : public DefaultSignalAppearanceMap
{
 Q_OBJECT
 VirtualSignalMast* mast;
public:
 DefaultSignalAppearanceMapO4(QString systemName, VirtualSignalMast* mast) : DefaultSignalAppearanceMap(systemName)
 {
  this->mast = mast;
 }
 //@Override
 /*public*/ QStringListIterator getAspects() {
      return QStringListIterator(mast->getAllKnownAspects().toList());

     }
};

#endif // VIRTUALSIGNALMASTADDPANETEST_H
