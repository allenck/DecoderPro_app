#ifndef MEMORYSPINNERICON_H
#define MEMORYSPINNERICON_H
#include "positionablejpanel.h"
#include <QSpinBox>
#include <namedbeanhandle.h>
#include "../libPr3/memory.h"
#include "actionlistener.h"

class JActionEvent;
class JSpinner;
class MemorySpinnerIcon : public PositionableJPanel
{
    Q_OBJECT
public:
    //explicit MemorySpinnerIcon(QWidget *parent = 0);
    /*public*/ MemorySpinnerIcon(Editor* editor, QWidget *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(MemorySpinnerIcon* p);
    ///*public*/ JComponent getTextComponent();
    /*public*/ QSize getSize();
     /*public*/ void setMemory(QString pName);
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ QString getNameString() ;
    /*public*/ void setSelectable(bool b);
    /*public*/ bool isSelectable();
    /*public*/ bool setEditIconMenu(QMenu* popup);
    void editMemory();
    /*public*/ void displayState();
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e);
    /*protected*/ void spinnerUpdated();
    /*public*/ QString getValue();
    void cleanup();
    /*public*/ MyGraphicsProxyWidget* getWidget() {return widget;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void stateChanged(/*ChangeEvent e*/);

private:
    int _min;// = 0;
    int _max;// = 100;
    JSpinner* spinner;// = new JSpinner(new SpinnerNumberModel(0,_min,_max,1));
    // the associated Memory object
    //Memory memory = null;
    /*private*/ NamedBeanHandle<Memory*>* namedMemory;
    bool selectable;// = false;
 Logger* log;
protected:
 /*protected*/ void edit();
 friend class Editor;
};
class MSIActionListener : public ActionListener
{
 Q_OBJECT
    MemorySpinnerIcon* parent;
public:
    MSIActionListener(MemorySpinnerIcon* parent);
public slots:
    /*public*/ void actionPerformed(JActionEvent* a = 0);
};

#endif // MEMORYSPINNERICON_H
