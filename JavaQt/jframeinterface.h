#ifndef JFRAMEINTERFACE_H
#define JFRAMEINTERFACE_H
#include "windowinterface.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT JFrameInterface : public WindowInterface
{
 Q_OBJECT
public:
 //explicit JFrameInterface(QWidget *parent = 0);
 /*public*/ JFrameInterface(JFrame* frame, QWidget *parent = 0);
 /*public*/ void show(JmriPanel* child, QAction* action) ;
 /*public*/ void show(JmriPanel* child, QAction* action, Hint hint);
 /*public*/ bool multipleInstances() ;
 /*public*/ JFrame* getFrame();
 /*public*/ void dispose();

signals:

public slots:
private:
 JFrame* frame;

};

#endif // JFRAMEINTERFACE_H
