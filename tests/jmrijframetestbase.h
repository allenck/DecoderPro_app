#ifndef JMRIJFRAMETESTBASE_H
#define JMRIJFRAMETESTBASE_H

#include <QObject>

class JmriJFrame;
class JmriJFrameTestBase : public QObject
{
 Q_OBJECT
public:
 explicit JmriJFrameTestBase(QObject *parent = nullptr);
 virtual /*abstract*/ /*public*/ void setUp() =0;  // set the value of frame.
 virtual /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testShowAndClose();

protected:
 /*protected*/ JmriJFrame* frame = nullptr;

};

#endif // JMRIJFRAMETESTBASE_H
