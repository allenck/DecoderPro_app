#ifndef JFRAMEINTERFACE_H
#define JFRAMEINTERFACE_H
#include "windowinterface.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT JFrameInterface : public WindowInterface
{
 Q_OBJECT
public:
 //explicit JFrameInterface(QWidget *parent = 0);
 /*public*/ JFrameInterface(JFrame* frame, QWidget *parent = 0);
// JFrameInterface(const JFrameInterface&) : WindowInterface() {}
// ~JFrameInterface() {}
 /*public*/ void show(JmriPanel* child, QAction* action) ;
 /*public*/ void show(JmriPanel* child, QAction* action, WindowInterface::Hint hint);
 /*public*/ bool multipleInstances() ;
 /*public*/ JFrame* getFrame();
 /*public*/ void dispose();

signals:

public slots:
private:
 JFrame* frame;

};

#endif // JFRAMEINTERFACE_H
