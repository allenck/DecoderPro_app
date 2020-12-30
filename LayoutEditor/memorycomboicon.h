#ifndef MEMORYCOMBOICON_H
#define MEMORYCOMBOICON_H
#include "positionablejpanel.h"
#include "namedbeanhandle.h"
#include "../libPr3/memory.h"
#include "jtextfield.h"
#include "iconadder.h"
#include "actionlistener.h"

class DefaultListModel;
class QListView;
class JTextField;
class QPushButton;
class JComboBox;
class MemoryComboIcon : public PositionableJPanel
{
    Q_OBJECT
public:
    //explicit MemoryComboIcon(QWidget *parent = 0);
    /*public*/ MemoryComboIcon(Editor* editor, QStringList list, QWidget *parent = 0);
    /*public*/ Positionable* deepClone();
    /*public*/ Positionable* finishClone(Positionable* p);
     /*public*/ void setMemory(QString pName);
    /*public*/ void setMemory(NamedBeanHandle<Memory*>* m);
    /*public*/ NamedBeanHandle<Memory*>* getNamedMemory();
    /*public*/ Memory* getMemory();
    /*public*/ /*ComboModel*/QStringList getComboModel() ;
    // update icon as state of Memory changes
    /*public*/ QString getNameString();
    /*private*/ void updateMemory();
    /*public*/ bool setEditIconMenu(QMenu* popup);
    //DefaultListModel _listModel;
    void editMemory();
    /*public*/ void displayState();
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent* e);
    void cleanup();
    /*public*/ MyGraphicsProxyWidget* getWidget() {return widget;}

signals:

public slots:
    /*public*/ void actionPerformed(/*ActionEvent e*/);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    JComboBox*	_comboBox;
//    ComboModel	_model;
    QStringList  _model;

    // the associated Memory object
    /*private*/ NamedBeanHandle<Memory*>* namedMemory;
 Logger* log;

protected slots:
    /*protected*/ void edit() ;
 friend class Editor;
 friend class MCIIconAdder;
 friend class MemoryItemPanel;
};
class MCIIconAdder : public IconAdder
{
    Q_OBJECT
    MemoryComboIcon* parent;
    QListView* list;
    QPushButton* bDel;// = new QPushButton(tr("deleteSelection"));
    QPushButton* bAdd;// = new QPushButton(tr("addItem"));
    JTextField* textfield;// = new JTextField(30);
    DefaultListModel* _listModel;
public:
    MCIIconAdder(QString type, MemoryComboIcon* parent);
public slots:
    void bDel_clicked();
    void bAdd_clicked();
protected:
    /*protected*/ void addAdditionalButtons(QWidget* p);
    friend class MemoryComboIcon;
};
class MCIActionListener : public ActionListener
{
 Q_OBJECT
    MemoryComboIcon* parent;
public:
    MCIActionListener(MemoryComboIcon*);
public slots:
    void actionPerformed(JActionEvent *e);
};

#endif // MEMORYCOMBOICON_H
