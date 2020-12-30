#ifndef MEMORYINPUTICON_H
#define MEMORYINPUTICON_H
#include "positionablejpanel.h"
#include "namedbeanhandle.h"
#include "memory.h"
#include "spinnernumbermodel.h"
#include "iconadder.h"
#include <QSpinBox>
#include "actionlistener.h"

class MyIconAdder;
class JActionEvent;
class QSpinBox;
class QLineEdit;
class JTextField;
class MemoryInputIcon : public PositionableJPanel
{
    Q_OBJECT
public:
    //explicit MemoryInputIcon(QWidget *parent = 0);
    /*public*/ MemoryInputIcon(int nCols, Editor* editor, QWidget *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(MemoryInputIcon *pos);
    /*public*/ JComponent *getTextComponent();
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e);
     /*public*/ void setMemory(QString pName);
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ void setNumColumns(int nCols);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ int getNumColumns();
    /*public*/ QString getNameString();
    /*public*/ bool setEditIconMenu(QMenu* popup) ;
    void editMemory();
    /*public*/ void displayState();
    void cleanup();
    void doMousePressed(QGraphicsSceneMouseEvent*);
    /*public*/ MyGraphicsProxyWidget* getWidget() {return widget;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    //void on_propertyChange(QString sType, QVariant sOld, QVariant sNew);

private:
    //JTextField*  _textBox;// = new JTextField();
    JTextField* _textBox;
    JTextField* _textDisplay;
    int _nCols;
    // the associated Memory object
    /*private*/ NamedBeanHandle<Memory*>* namedMemory;
    SpinnerNumberModel* _spinModel;// = new SpinnerNumberModel(3,1,100,1);
    Logger* log;
    MyIconAdder* _iconEditor;
    //MyGraphicsProxyWidget* widget;

private slots:
    /*private*/ void updateMemory();

protected slots:
    /*protected*/ void edit();
    void textChanged(QString);
friend class Editor;
friend class MyIconAdder;
friend class MemoryItemPanel;
};
class MyIconAdder : public IconAdder
{
    Q_OBJECT
 MemoryInputIcon* parent;
 QSpinBox* spinner;// = new QSpinBox();//JSpinner(_spinModel);
public:
 MyIconAdder(QString type, MemoryInputIcon* parent);
protected:
 /*protected*/ void addAdditionalButtons(QWidget* p);
};
class MiiActionListener : public ActionListener
{
    Q_OBJECT
    MemoryInputIcon* parent;
public:
    MiiActionListener(MemoryInputIcon* parent);
public slots:
  /*public*/ void actionPerformed(JActionEvent* a = 0);
};

#endif // MEMORYINPUTICON_H
