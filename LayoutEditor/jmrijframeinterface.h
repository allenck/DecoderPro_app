#ifndef JMRIJFRAMEINTERFACE_H
#define JMRIJFRAMEINTERFACE_H
#include "windowinterface.h"
#include <QHash>
#include "windowlistener.h"
#include "jframe.h"
#include "liblayouteditor_global.h"

class JmriJFrame;
class LIBLAYOUTEDITORSHARED_EXPORT JmriJFrameInterface : public WindowInterface
{
    Q_OBJECT
public:
    explicit JmriJFrameInterface(QWidget *parent = 0);
    /*public*/ void show(/*final*/ JmriPanel* child,
                        QAction* act,
                        Hint hint);
    /*public*/ void show(/*final*/ JmriPanel* child,
                        QAction* act);
    /*public*/ bool multipleInstances();
    /*public*/ void dispose() ;
    /*public*/ JFrame* getFrame();

signals:

public slots:
private:
    QHash<JmriPanel*, JmriJFrame*> frames;// =  QHashMap<JmriPanel*, JmriJFrame*>();

};
class FIWindowListener : public WindowListener
{
 Q_OBJECT
    JmriPanel* c;
    JmriJFrameInterface* _interface;
 public:
    FIWindowListener( JmriPanel* c,JmriJFrameInterface* _interface);
  void windowClosing(QCloseEvent *e);
};

#endif // JMRIJFRAMEINTERFACE_H
