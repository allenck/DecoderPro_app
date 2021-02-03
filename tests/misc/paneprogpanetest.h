#ifndef PANEPROGPANETEST_H
#define PANEPROGPANETEST_H

#include <QObject>
#include <QtXml>
#include "paneprogframe.h"
#include "paneprogpane.h"
#include "jpanel.h"
#include "junitutil.h"

class Logger;
class ProgDebugger;
class PaneProgPaneTest : public QObject
{
 Q_OBJECT
public:
 explicit PaneProgPaneTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp() ;
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testColumn();
 /*public*/ void testVariables();
 /*public*/ void testVarListFill();
 /*public*/ void testPaneRead();
#if 1
 /*public*/ void testPaneWrite();
 /*public*/ void testPaneReadOpCount();
#endif

private:   
 ProgDebugger* p; // = new ProgDebugger();
 static Logger* log;
 // static variables for the test XML structures
 QDomElement root;// = null;
 QDomElement pane1;// = null;
 QDomElement pane2;// = null;
 QDomElement pane3;// = null;
 QDomDocument doc;// = null;
 // static variables for internal classes to report their interpretations
 static QString result;// = null;
 static int colCount;// = -1;
 static int varCount;// = -1;
 void setupDoc();

 friend class PaneProgPaneO1;
 friend class PaneProgPaneO2;

};

class PaneProgFrameO1 : public PaneProgFrame
{
 Q_OBJECT
public:
 PaneProgFrameO1(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle,
               QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent = 0)
  : PaneProgFrame(pDecoderFile, pRosterEntry, frameTitle, programmerFile, pProg, opsMode, parent)
 {
 }

protected:
 // dummy implementations
 //@Override
 /*protected*/ JPanel* getModePane() override;
};


class PaneProgPaneO1 : public PaneProgPane
{
 Q_OBJECT
  PaneProgPaneTest* test;
 public:
  /*public*/ PaneProgPaneO1(PaneContainer* container, QString name,
                          QDomElement pane, CvTableModel* cvModel,
                          VariableTableModel* varModel, QDomElement modelElem,
                          RosterEntry* rosterEntry, bool isProgPane, PaneProgPaneTest* test)
   : PaneProgPane(container, name, pane,cvModel, varModel, modelElem, rosterEntry, isProgPane, nullptr)
  {
   this->test = test;
   qApp->processEvents();

  }
  //@Override
  /*public*/ JPanel* newColumn(QDomElement e, bool a, QDomElement el) override;
};

class PaneProgPaneO2 : public PaneProgPane
{
 Q_OBJECT
  PaneProgPaneTest* test;
 public:
  /*public*/ PaneProgPaneO2(PaneContainer* container, QString name,
                          QDomElement pane, CvTableModel* cvModel,
                          VariableTableModel* varModel, QDomElement modelElem,
                          RosterEntry* rosterEntry, PaneProgPaneTest* test, QWidget *parent = 0)
   : PaneProgPane(container, name, pane,cvModel, varModel, modelElem, rosterEntry, parent)
  {
   this->test = test;
   qApp->processEvents();

  }
  //@Override
  /*public*/ void newVariable(QDomElement /*e*/, JPanel * /*p*/, GridBagLayout* /*g*/,
                              GridBagConstraints* /*c*/, bool /*a*/) override;
};

class ReleaseUntilO14 : public ReleaseUntil
{
    Q_OBJECT
    PaneProgPane* progPane;
public:
    ReleaseUntilO14(PaneProgPane* progPane) {this->progPane = progPane;}
    bool ready() throw (Exception) override
    {
     return (!progPane->isBusy());
    }
};
#endif // PANEPROGPANETEST_H
