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
class MemoryInputIcon : public PositionableJPanel, public  PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
    //explicit MemoryInputIcon(QWidget *parent = 0);
    /*public*/ MemoryInputIcon(int nCols, Editor* editor, QWidget *parent = 0);
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(MemoryInputIcon *pos);
    /*public*/ JComponent *getTextComponent() override;
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e) override;
     /*public*/ void setMemory(QString pName);
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ void setNumColumns(int nCols);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ int getNumColumns();
    /*public*/ QString getNameString() override;
    /*public*/ bool setEditIconMenu(QMenu* popup)  override;
    void editMemory();
    /*public*/ void displayState();
    void cleanup();
    void doMousePressed(QGraphicsSceneMouseEvent*) override;
    /*public*/ MyGraphicsProxyWidget* getWidget()  override{return widget;}
    QObject* self() override {return (QObject*)this;}

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
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

class MiiActionListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    MemoryInputIcon* parent;
public:
    MiiActionListener(MemoryInputIcon* parent);
    QObject* self() override {return (QObject*)this;}
public slots:
  /*public*/ void actionPerformed(JActionEvent* a = 0)override;
};

#endif // MEMORYINPUTICON_H
