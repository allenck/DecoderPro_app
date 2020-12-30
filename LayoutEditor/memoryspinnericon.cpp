#include "memoryspinnericon.h"
#include "editor.h"
#include <QGridLayout>
#include "gridbagconstraints.h"
#include "jtextfield.h"
#include "instancemanager.h"
#include "namedbeanhandlemanager.h"
#include "abstractmemorymanager.h"
#include "abstractmemory.h"
#include "picklistmodel.h"
#include "iconadder.h"
#include <QGraphicsProxyWidget>
#include "positionablepopuputil.h"
#include "jspinner.h"

//MemorySpinnerIcon::MemorySpinnerIcon(QWidget *parent) :
//    PositionableJPanel(parent)
//{
//}
/**
 * An icon to display a status of a Memory in a JSpinner.
 *<P>
 * Handles the case of either a String or an Integer in the
 * Memory, preserving what it finds.
 *<P>
 * @author Bob Jacobsen  Copyright (c) 2009
 * @version $Revision: 22320 $
 * @since 2.7.2
 */



/*public*/ MemorySpinnerIcon::MemorySpinnerIcon(Editor* editor, QWidget *parent)
 : PositionableJPanel(editor, parent)
{
 //super(editor);
 _min = 0;
 _max = 100;
  spinner = new JSpinner(new SpinnerNumberModel(0,_min,_max,1));
  setLevel(Editor::LABELS);
  selectable = false;
  log = new Logger("MemorySpinnerIcon");
  namedMemory = NULL;
  widget = new MyGraphicsProxyWidget();
  widget->setWidget(spinner);
  widget->setFlag(QGraphicsItem::ItemIsFocusable,true) ;
  widget->setFlag(QGraphicsItem::ItemIsMovable, true);
  widget->setFlag(QGraphicsItem::ItemIsSelectable, true);
  spinner->setEnabled(true);

  _itemGroup = NULL;
  //  _itemGroup = new QGraphicsItemGroup();
  //  _itemGroup->addToGroup(widget);
  //_icon = true;

//  QGridLayout* g;
//  GridBagConstraints* c= new GridBagConstraints();
//  setLayout(g = new QGridLayout());
//  g->addWidget(spinner, c->gridy, c->gridx,1,1);
//  setLayout(new QVBoxLayout);
//  layout()->addWidget(spinner);
  //spinner.addChangeListener(this);
  connect(spinner, SIGNAL(valueChanged(int)), this, SLOT(stateChanged()));
//  JTextField textBox = ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField();
//  textBox.addMouseMotionListener(this);
//  textBox.addMouseListener(this);
  setPopupUtility(new PositionablePopupUtil(this, spinner));
  int width = qMin(100, spinner->width()+ 20);
  QSize size = QSize(width, qMin(80, spinner->height()));
  setFixedSize(size);
}

/*public*/ Positionable* MemorySpinnerIcon::deepClone() {
    MemorySpinnerIcon* pos = new MemorySpinnerIcon(_editor);
    return finishClone(pos);
}

/*public*/ Positionable* MemorySpinnerIcon::finishClone(MemorySpinnerIcon* p) {
    MemorySpinnerIcon* pos = (MemorySpinnerIcon*)p;
    pos->setMemory(namedMemory->getName());
    return PositionableJPanel::finishClone(pos);
}
///*public*/ JComponent MemorySpinnerIcon::getTextComponent() {
//    return ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField();
//}

/*public*/ QSize MemorySpinnerIcon::getSize() {
    if (debug) {
        QSize d= spinner->size();
        if (debug) log->debug("spinner width= "+QString::number(d.width())+", height= "+QString::number(d.height()));
        QRectF rect= getBounds(QRectF());
        if (debug) log->debug("Bounds rect= ("+QString::number(rect.x())+","+QString::number(rect.y())+
                              ") width= "+QString::number(rect.width())+", height= "+QString::number(rect.height()));
        d= PositionableJPanel::size();
        if (debug) log->debug("Panel width= "+QString::number(d.width())+", height= "+QString::number(d.height()));
    }
    return PositionableJPanel::size();
}

/**
 * Attached a named Memory to this display item
  * @param pName Used as a system/user name to lookup the Memory object
 */
 /*public*/ void MemorySpinnerIcon::setMemory(QString pName) {
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
/*public*/ void MemorySpinnerIcon::setMemory(NamedBeanHandle<Memory*>* m) {
    if (namedMemory != NULL) {
        getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractMemory* m = (AbstractMemory*)getMemory();
//        disconnect(m, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedMemory = m;
    if (namedMemory != NULL) {
        getMemory()->addPropertyChangeListener((PropertyChangeListener*)this, namedMemory->getName(), "Memory Spinner Icon");
//        AbstractMemory* m = (AbstractMemory*)getMemory();
//        connect(m->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        displayState();
        setName(namedMemory->getName());
    }
}

/*public*/ NamedBeanHandle<Memory*>* MemorySpinnerIcon::getNamedMemory() { return namedMemory; }

// update icon as state of Memory changes
/*public*/ void MemorySpinnerIcon::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("value")) {
            displayState();
    }
}

/*public*/ Memory* MemorySpinnerIcon::getMemory() {
    if (namedMemory==NULL) {
        return NULL;
    }
    return namedMemory->getBean();
}

/*public*/ void MemorySpinnerIcon::stateChanged(/*ChangeEvent e*/) {
    spinnerUpdated();
}

/*public*/ QString MemorySpinnerIcon::getNameString() {
    QString name;
    if (namedMemory == NULL) name = tr("<Not connected>");
    else if (getMemory()->getUserName()!=NULL)
        name = getMemory()->getUserName()+" ("+getMemory()->getSystemName()+")";
    else
        name = getMemory()->getSystemName();
    return name;
}

/*public*/ void MemorySpinnerIcon::setSelectable(bool b) {selectable = b;}
/*public*/ bool MemorySpinnerIcon::isSelectable() { return selectable;}

/*public*/ bool MemorySpinnerIcon::setEditIconMenu(QMenu* popup) {
    QString txt = tr("Edit %1 Item").arg(tr("Memory"));
    QAction* act = new QAction(txt, this);
    popup->addAction(act = new QAction(txt, this));
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });
    connect(act, SIGNAL(triggered()), this, SLOT(edit()));
    return true;
}

/*protected*/ void MemorySpinnerIcon::edit() {
#if 1
    makeIconEditorFrame(this, "Memory", true, NULL);
    _iconEditor->setPickList(PickListModel::memoryPickModelInstance());
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            editMemory();
//        }
//    };
    MSIActionListener* addIconAction = new MSIActionListener(this);
    _iconEditor->complete(addIconAction, false, true, true);
    _iconEditor->setSelection(getMemory());
#endif
}
void MemorySpinnerIcon::editMemory() {
    setMemory(_iconEditor->getTableSelection()->getDisplayName());
    setSize(size().width(), size().height());
    _iconEditorFrame->deleteLater();
    _iconEditorFrame = NULL;
    _iconEditor = NULL;
    //invalidate();
}
MSIActionListener::MSIActionListener(MemorySpinnerIcon *parent)
{
 this->parent = parent;
}

/*public*/ void MSIActionListener::actionPerformed(JActionEvent* /*a*/) {
    parent->editMemory();
}

/**
 * Drive the current state of the display from the state of the
 * Memory.
 */
/*public*/ void MemorySpinnerIcon::displayState() {
    if (debug) log->debug("displayState");
    if (namedMemory == NULL) {  // leave alone if not connected yet
        return;
    }
    QVariant v = ((AbstractMemory*)getMemory())->getValue();
    if (v.isNull()) return;
    int num = 0;
    if (v.canConvert<QString>()) {
        try {
            num =v.toInt();
        } catch (NumberFormatException e) {
            return;
        }
    } else if (v.canConvert<int>()) {
        num = v.toInt();
    } else if (v.canConvert<double>()) {
        num = qRound(v.toDouble());
        if (debug) log->debug("num= "+QString::number(num));
    } else {
        //spinner.setValue(getMemory().getValue());
        return;
    }
    int n = num;
    if (n>_max) {
        num =(_max);
    }
    else if (n<_min) {
        num =(_min);
    }
    spinner->setValue(num);
}

/*public*/ void MemorySpinnerIcon::mouseExited(QGraphicsSceneMouseEvent* e) {
    spinnerUpdated();
    PositionableJPanel::mouseExited(e);
}

/*protected*/ void MemorySpinnerIcon::spinnerUpdated() {
    if (namedMemory == NULL) return;
    if (getMemory()->getValue() == QVariant()) {
        getMemory()->setValue(spinner->value());
        return;
    }
    // Spinner is always an Integer, but memory can contain Integer or String
    if (getMemory()->getValue().canConvert<QString>()) {
        QString newValue = QString::number(spinner->value());
        if (getMemory()->getValue().toString()!=(newValue))
            getMemory()->setValue(newValue);
    } else {
        getMemory()->setValue(spinner->value());
    }
}

/*public*/ QString MemorySpinnerIcon::getValue() {
    return QString::number(spinner->value());
}

void MemorySpinnerIcon::cleanup() {
    if (namedMemory!=NULL) {
        getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//        AbstractMemory* m = (AbstractMemory*)getMemory();
//        disconnect(m, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    }
    if (spinner!=NULL) {
//        spinner.removeChangeListener(this);
//        ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField().removeMouseMotionListener(this);
//        ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField().removeMouseListener(this);
    }
    spinner = NULL;
    namedMemory = NULL;
}
