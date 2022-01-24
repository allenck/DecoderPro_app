#ifndef PANEPROGFRAMETEST_H
#define PANEPROGFRAMETEST_H

#include <QObject>
#include <QtXml>
#include "paneprogframe.h"
#include "jpanel.h"

class DecoderFile;
class PaneProgFrameTest : public QObject
{
 Q_OBJECT
public:
 explicit PaneProgFrameTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testPane();
 /*public*/ void testFrame();

private:
 // static variables for internal classes to report their interpretations
 static QString result;// = null;
 static int colCount;// = -1;
 static int varCount;// = -1;
 // static variables for the test XML structures
 QDomElement root;// = null;
 QDomDocument doc;// = null;
 void setupDoc();

 friend class PaneProgFrameO2;
 friend class PaneProgFrameO3;
};

class PaneProgFrameO2 : public PaneProgFrame
{
 Q_OBJECT
public:
 PaneProgFrameO2(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle,
               QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent = 0)
  : PaneProgFrame(pDecoderFile, pRosterEntry, frameTitle, programmerFile, pProg, opsMode, parent)
 {}

protected:
 // dummy implementations
 //@Override
 /*protected*/ JPanel* getModePane() override;
};

class PaneProgFrameO3 : public PaneProgFrame
{
 Q_OBJECT
public:
 PaneProgFrameO3(DecoderFile* pDecoderFile, RosterEntry* pRosterEntry, QString frameTitle,
               QString programmerFile, Programmer* pProg, bool opsMode, QWidget* parent = 0)
  : PaneProgFrame(pDecoderFile, pRosterEntry, frameTitle, programmerFile, pProg, opsMode, parent)
 {}

protected:
 // dummy implementations
 //@Override
 /*protected*/ JPanel *getModePane() override;
};

#endif // PANEPROGFRAMETEST_H
