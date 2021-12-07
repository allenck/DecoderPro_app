#ifndef MEMORYSPINNERICON_H
#define MEMORYSPINNERICON_H
#include "positionablejpanel.h"
#include <QSpinBox>
#include <namedbeanhandle.h>
#include "../libPr3/memory.h"
#include "actionlistener.h"
#include "propertychangelistener.h"

class JActionEvent;
class JSpinner;
class MemorySpinnerIcon : public PositionableJPanel, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit MemorySpinnerIcon(QWidget *parent = 0);
    /*public*/ MemorySpinnerIcon(Editor* editor, QWidget *parent = 0);
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(MemorySpinnerIcon* p);
    ///*public*/ JComponent getTextComponent();
    /*public*/ QSize getSize();
     /*public*/ void setMemory(QString pName);
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ QString getNameString() override ;
    /*public*/ void setSelectable(bool b);
    /*public*/ bool isSelectable();
    /*public*/ bool setEditIconMenu(QMenu* popup) override;
    void editMemory();
    /*public*/ void displayState();
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e) override;
    /*protected*/ void spinnerUpdated();
    /*public*/ QString getValue();
    void cleanup();
    /*public*/ MyGraphicsProxyWidget* getWidget() override {return widget;}
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
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

class MSIActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
    MemorySpinnerIcon* parent;
public:
    MSIActionListener(MemorySpinnerIcon* parent);
    QObject* self() override {return (QObject*)this;}
public slots:
    /*public*/ void actionPerformed(JActionEvent* a = 0)override;
};

#endif // MEMORYSPINNERICON_H
