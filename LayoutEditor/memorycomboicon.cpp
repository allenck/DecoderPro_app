#include "memorycomboicon.h"
#include "jcombobox.h"
#include "namedbeanhandlemanager.h"
#include "instancemanager.h"
#include <QGridLayout>
#include "editor.h"
#include "positionablepopuputil.h"
#include "iconadder.h"
#include "abstractmemory.h"
#include "abstractmemorymanager.h"
#include <QGraphicsProxyWidget>
#include "iconadder.h"
#include <QListView>
#include "picklistmodel.h"
#include "defaultlistmodel.h"

//MemoryComboIcon::MemoryComboIcon(QWidget *parent) :
//    PositionalJPanel(parent)
//{
//}
/**
 * An icon to display and input a Memory value in a TextField.
 *<P>
 * Handles the case of either a String or an Integer in the
 * Memory, preserving what it finds.
 *<P>
 * @author Pete Cressman  Copyright (c) 2012
 * @version $Revision: 18229 $
 * @since 2.7.2
 */

///*public*/ class MemoryComboIcon extends PositionableJPanel
//            implements java.beans.PropertyChangeListener,  ActionListener {


/*public*/ MemoryComboIcon::MemoryComboIcon(Editor* editor, QStringList list, QWidget *parent) : PositionableJPanel(editor, parent)
{
 //super(editor);
//    if (list!=NULL) {
//        _model = new ComboModel(list);
//    } else {
//        _model = new ComboModel();
//    }
 log = new Logger("MemoryComboIcon");
 namedMemory = NULL;
 _comboBox = new JComboBox(/*_model*/);
 _comboBox->addItems(list);
 _model = list;

 //_comboBox->addActionListener(this);
 connect(_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(actionPerformed()));
 setLevel(Editor::LABELS);
 widget = new MyGraphicsProxyWidget();
 widget->setWidget(_comboBox);
 _itemGroup = NULL;
//    _itemGroup = new QGraphicsItemGroup();
//    _itemGroup->addToGroup(widget);
// _icon = true;
//    QGridLayout* g;
//    setLayout(g = new QGridLayout());
//    g->addWidget(_comboBox,0,0,1,1);
//    setLayout(new QVBoxLayout);
//    layout()->addWidget(_comboBox);
//    addMouseMotionListener(this);
//    _comboBox.addMouseListener(this);

//    for (int i = 0; i < _comboBox->getComponentCount(); i++) {
//        java.awt.Component component = _comboBox.getComponent(i);
//        if (component instanceof AbstractButton) {
//            component.addMouseListener(this);
//            component.addMouseMotionListener(this);
//        }
//    }
 setPopupUtility(new PositionablePopupUtil((Positionable*)this, _comboBox));
 int width = qMax(100, _comboBox->width()+ 20);
 QSize size = QSize(width, qMax(80, _comboBox->height()));
 setMaximumSize(size);
}
#if 0
class ComboModel extends DefaultComboBoxModel {
    ComboModel() {
        super();
    }
    ComboModel(String[] l) {
        super(l);
    }
    /*public*/ void addElement(Object obj) {
        if (getIndexOf(obj)>=0) {
            return;
        }
        if (obj instanceof String) {
            super.addElement(obj);
            updateMemory();
        }
    }
    /*public*/ void insertElementAt(Object obj, int idx) {
        if (getIndexOf(obj)>=0) {
            return;
        }
        if (obj instanceof String) {
            super.insertElementAt(obj, idx);
            updateMemory();
        }
    }
}
#endif
/*public*/ Positionable* MemoryComboIcon::deepClone() {
    QStringList list =  QStringList(); //[_model.getSize()];
//    for (int i=0; i<_model.getSize(); i++) {
//        list[i] = (String)_model.getElementAt(i);
//    }
    MemoryComboIcon* pos = new MemoryComboIcon(_editor, list);
    return finishClone((Positionable*)pos);
}

/*public*/ Positionable* MemoryComboIcon::finishClone(Positionable* p) {
    MemoryComboIcon* pos = (MemoryComboIcon*)p;
    pos->setMemory(namedMemory->getName());
    return PositionableJPanel::finishClone(pos);
}

/**
 * Attached a named Memory to this display item
  * @param pName Used as a system/user name to lookup the Memory object
 */
 /*public*/ void MemoryComboIcon::setMemory(QString pName) {
     if (debug) log->debug("setMemory for memory= "+pName);
     if (InstanceManager::memoryManagerInstance()!=NULL) {
        Memory* memory = ((AbstractMemoryManager*)InstanceManager::memoryManagerInstance())->
             provideMemory(pName);
         if (memory != NULL) {
             setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, memory));
         } else {
             log->error("Memory '"+pName+"' not available, icon won't see changes");
         }
     } else {
         log->error("No MemoryManager for this protocol, icon won't see changes");
     }
     updateSize();
 }

/**
 * Attached a named Memory to this display item
 * @param m The Memory object
 */
/*public*/ void MemoryComboIcon::setMemory(NamedBeanHandle<Memory*>* m) {
    if (namedMemory != NULL) {
        getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractMemory* m = (AbstractMemory*)getMemory();
//        disconnect(m, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedMemory = m;
    if (namedMemory != NULL) {
        getMemory()->addPropertyChangeListener((PropertyChangeListener*)this, namedMemory->getName(), "Memory Input Icon");
//        AbstractMemory* m = (AbstractMemory*)getMemory();
//        connect(m->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        displayState();
        setName(namedMemory->getName());
    }
}

/*public*/ NamedBeanHandle<Memory*>* MemoryComboIcon::getNamedMemory() { return namedMemory; }

/*public*/ Memory* MemoryComboIcon::getMemory() {
    if (namedMemory==NULL) {
        return NULL;
    }
    return namedMemory->getBean();
}

/*public*/ QStringList MemoryComboIcon::getComboModel() {
    return _model;
}

/**
 * Display
 */
/*public*/ void MemoryComboIcon::actionPerformed(/*ActionEvent e*/) {
    updateMemory();
}

// update icon as state of Memory changes
/*public*/ void MemoryComboIcon::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("value")) {
            displayState();
    }
}

/*public*/ QString MemoryComboIcon::getNameString() {
    QString name;
    if (namedMemory == NULL) name = tr("<Not connected>");
    else if (getMemory()->getUserName()!=NULL)
        name = getMemory()->getUserName()+" ("+getMemory()->getSystemName()+")";
    else
        name = getMemory()->getSystemName();
    return name;
}

/*private*/ void MemoryComboIcon::updateMemory() {
    if (namedMemory == NULL) return;
    getMemory()->setValue(_comboBox->currentText());
}

/*public*/ bool MemoryComboIcon::setEditIconMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Item").arg(tr("Memory"));\
    QAction* act;
    popup->addAction(act = new QAction(txt, this));
//    {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });
    connect(act, SIGNAL(triggered()), this, SLOT(edit()));
    return true;
}

/**
* Poppup menu iconEditor's ActionListener
*/
//DefaultListModel _listModel;
/*protected*/ void MemoryComboIcon::edit() {
#if 1
    _iconEditor = new MCIIconAdder("Memory", this);
#if 0 // done
    {
        JList list;
        JButton bDel = new JButton(Bundle.getMessage("deleteSelection"));
        JButton bAdd = new JButton(Bundle.getMessage("addItem"));
        JTextField textfield = new JTextField(30);
        protected void addAdditionalButtons(JPanel p) {
            _listModel = new DefaultListModel();
            bDel.addActionListener( new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    int idx = list.getSelectedIndex();
                    if (idx>=0) {
                        _listModel.removeElementAt(idx);
                    }
                }
            });
            bAdd.addActionListener( new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    String text = textfield.getText();
                    if (text==NULL || text.length()==0 ||_listModel.indexOf(text)>=0) {
                        return;
                    }
                    int idx = list.getSelectedIndex();
                    if (idx<0) {
                        idx = _listModel.getSize();
                    }
                    _listModel.add(idx, text);
                }
            });
            for (int i=0; i<_model.getSize(); i++) {
                _listModel.add(i, _model.getElementAt(i));
            }
            list = new JList(_listModel);
            JScrollPane scrollPane = new JScrollPane(list);
            JPanel p1 = new JPanel();
            p1.add(new JLabel(Bundle.getMessage("comboList")));
            p.add(p1);
            p.add(scrollPane);
            p1 = new JPanel();
            p1.add(new JLabel(Bundle.getMessage("newItem"), SwingConstants.RIGHT));
            textfield.setMaximumSize(textfield.getPreferredSize());
            p1.add(textfield);
            p.add(p1);
            JPanel p2 = new JPanel();
            //p2.setLayout(new BoxLayout(p2, BoxLayout.Y_AXIS));
            //p2.setLayout(new FlowLayout(FlowLayout.TRAILING));
            p2.add(bDel);
            p2.add(bAdd);
            p.add(p2);
            p.setVisible(true);
        }
    };
#endif
    makeIconEditorFrame(this, "Memory", true, _iconEditor);
    _iconEditor->setPickList(PickListModel::memoryPickModelInstance());
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            editMemory();
//        }
//    };
    MCIActionListener* addIconAction = new MCIActionListener(this);
    _iconEditor->makeIconPanel(false);
    _iconEditor->complete(addIconAction, false, true, true);
    _iconEditor->setSelection(getMemory());
#endif
}
MCIIconAdder::MCIIconAdder(QString type, MemoryComboIcon *parent) : IconAdder(type, parent)
{
 this->parent = parent;
 bDel = new QPushButton(tr("Delete Selection"));
 bAdd = new QPushButton(tr("Add new Item"));
 textfield = new JTextField(30);

}

/*protected*/ void MCIIconAdder::addAdditionalButtons(QWidget* p) {
    _listModel = new DefaultListModel();
//        bDel.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                int idx = list.getSelectedIndex();
//                if (idx>=0) {
//                    _listModel.removeElementAt(idx);
//                }
//            }
//        });
    connect(bDel, SIGNAL(clicked()), this, SLOT(bDel_clicked()));
//        bAdd.addActionListener( new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                String text = textfield.getText();
//                if (text==NULL || text.length()==0 ||_listModel.indexOf(text)>=0) {
//                    return;
//                }
//                int idx = list.getSelectedIndex();
//                if (idx<0) {
//                    idx = _listModel.getSize();
//                }
//                _listModel.add(idx, text);
//            }
//        });
    connect(bAdd, SIGNAL(clicked()), this, SLOT(bAdd_clicked()));
    for (int i=0; i<parent->_model.count(); i++) {
        _listModel->add(i, parent->_model.at(i));
    }
    list = new QListView(/*_listModel*/);
    list->setModel(_listModel);
    //JScrollPane scrollPane = new JScrollPane(list);
    QWidget* p1 = new QWidget();
    p1->setLayout(new QHBoxLayout);
    p1->layout()->addWidget(new QLabel(tr("Edit ComboBox Items")));
    p->layout()->addWidget(p1);
    p->layout()->addWidget(list);
    p1 = new QWidget();
    p1->setLayout(new QHBoxLayout);
    p1->layout()->addWidget(new JLabel(tr("New Item:")/*, SwingConstants.RIGHT*/));
    textfield->setMaximumSize(textfield->getPreferredSize());
    p1->layout()->addWidget(textfield);
    p->layout()->addWidget(p1);
    QWidget* p2 = new QWidget();
    p2->setLayout(new QHBoxLayout(p2/*, BoxLayout.Y_AXIS*/));
    //p2.setLayout(new FlowLayout(FlowLayout.TRAILING));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(bDel->sizePolicy().hasHeightForWidth());
    bDel->setSizePolicy(sizePolicy);
    bAdd->setSizePolicy(sizePolicy);
    p2->layout()->addWidget(bDel);
    p2->layout()->addWidget(bAdd);
    p->layout()->addWidget(p2);
    p->setVisible(true);
}
void MCIIconAdder::bDel_clicked()
{
 int idx = list->currentIndex().row();
 if (idx>=0) {
    _listModel->removeElementAt(idx);
 }
}
void MCIIconAdder::bAdd_clicked()
{
 QString text = textfield->text();
 if (text=="" || text.length()==0 ||_listModel->indexOf(text)>=0) {
    return;
 }
 int idx = list->currentIndex().row();
 if (idx<0) {
    idx = _listModel->getSize();
 }
 _listModel->add(idx, text);
}

void MemoryComboIcon::editMemory() {
    NamedBean* bean = _iconEditor->getTableSelection();
    setMemory(bean->getDisplayName());
//    _model.removeAllElements();
    _comboBox->clear();
//    for (int i=0; i<_listModel.size(); i++) {
//        _model.addElement(_listModel.getElementAt(i));
//    }
    for(int i=0; i <((MCIIconAdder*)_iconEditor)->_listModel->getSize(); i++ )
    {
     _comboBox->addItem(((MCIIconAdder*)_iconEditor)->_listModel->getElementAt(i).toString());
    }
    setSize(size().width()+1, size().height());
    _iconEditor->close();
    _iconEditorFrame->dispose();
    _iconEditorFrame = NULL;
    _iconEditor = NULL;
    //validate();
}

/**
 * Drive the current state of the display from the state of the
 * Memory.
 */
/*public*/ void MemoryComboIcon::displayState() {
    if (debug) log->debug("displayState");
    if (namedMemory == NULL) {  // leave alone if not connected yet
        return;
    }
    //_model.setSelectedItem(getMemory().getValue());
}
/*public*/ void MemoryComboIcon::mouseExited(QGraphicsSceneMouseEvent* e) {
//    _comboBox->setFocusable(false);
//    _comboBox->transferFocus();
    PositionableJPanel::mouseExited(e);
}

void MemoryComboIcon::cleanup() {
    if (namedMemory!=NULL) {
        getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractMemory* m = (AbstractMemory*)getMemory();
//        disconnect(m, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    if (_comboBox!=NULL) {
//            _comboBox.removeMouseMotionListener(this);
        //_comboBox->removeMouseListener(this);
        _comboBox = NULL;
    }
    namedMemory = NULL;
}
MCIActionListener::MCIActionListener(MemoryComboIcon * parent)
{
 this->parent = parent;
}
void MCIActionListener::actionPerformed(JActionEvent */*e*/)
{
 parent->editMemory();
}
