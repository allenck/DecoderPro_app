#include "memoryinputicon.h"
#include "editor.h"
#include <QGridLayout>
#include "gridbagconstraints.h"
#include "jtextfield.h"
#include "instancemanager.h"
#include "abstractmemorymanager.h"
#include "positionablepopuputil.h"
#include "abstractmemory.h"
#include "jtextfield.h"
#include "iconadder.h"
#include "spinnernumbermodel.h"
#include <QGraphicsProxyWidget>
#include <QSpinBox>
#include "flowlayout.h"
#include "picklistmodel.h"
#include <QGraphicsLinearLayout>

//MemoryInputIcon::MemoryInputIcon(QWidget *parent) :
//    PositionableJPanel(parent)
//{
//}
/**
 * An icon to display and input a Memory value in a TextField.
 *<P>
 * Handles the case of either a String or an Integer in the
 * Memory, preserving what it finds.
 *<P>
 * @author Pete Cressman  Copyright (c) 2009
 * @version $Revision: 22320 $
 * @since 2.7.2
 */

///*public*/ class MemoryInputIcon extends PositionableJPanel implements java.beans.PropertyChangeListener {




/*public*/ MemoryInputIcon::MemoryInputIcon(int nCols, Editor* editor, QWidget *parent) : PositionableJPanel(editor, parent) {
 //super(editor);
 _textBox = new JTextField(nCols);
 _textBox->setObjectName("JTextField");
 _textBox->setVisible(true);

 _nCols = nCols;
 //_itemGroup = new MyGraphicsItemGroup();
 _itemGroup = NULL;
 widget = new MyGraphicsProxyWidget();
 widget->setWidget(_textBox);
 widget->setFlag(QGraphicsItem::ItemIsFocusable,true) ;
 widget->setFlag(QGraphicsItem::ItemIsMovable, true);
 widget->setFlag(QGraphicsItem::ItemIsSelectable, true);
 widget->setLayout(new QGraphicsLinearLayout());

 _textBox->setEnabled(true);
 //_itemGroup->addToGroup(widget);
 setLevel(Editor::LABELS);
 _spinModel = new SpinnerNumberModel(3,1,100,1);
 log = new Logger("MemoryInputIcon");
 namedMemory = NULL;
 //widget = NULL;
 //_icon = true;


//    QGridLayout* g;
//    GridBagConstraints* c = new GridBagConstraints();
//    setLayout(g = new QGridLayout());
//    g->addWidget(_textBox, c->gridy, c->gridx, 1,1);
 setLayout(new QHBoxLayout);

 layout()->addWidget(_textDisplay = new JTextField(/*_textBox*/));
 _textDisplay->setEnabled(true);
 //_textDisplay->setText(getMemory()->getValue().toString());
 _textDisplay->setText(_textBox->text());
 connect(_textDisplay, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
 connect(_textDisplay, SIGNAL(editingFinished()), this, SLOT(updateMemory()));
//    _textBox.addKeyListener(new KeyAdapter() {
//            /*public*/ void keyReleased(KeyEvent e){
//                int key = e.getKeyCode();
//                if (key==KeyEvent.VK_ENTER || key==KeyEvent.VK_TAB) {
//                    updateMemory();
//                }
//            }
//        });
//    _textBox->setColumns(_nCols);
//    _textBox->addMouseMotionListener(this);
//    _textBox->addMouseListener(this);

 setPopupUtility(new PositionablePopupUtil((Positionable*)this, _textBox));
 int width = qMax(100, _textBox->width()+ 20);
 QSize size = QSize(width, qMax(80, _textBox->height()));
 setMaximumSize(size);
}

void MemoryInputIcon::textChanged(QString text)
{
 _textBox->setText(text);
}

/*public*/ Positionable* MemoryInputIcon::deepClone() {
    MemoryInputIcon* pos = new MemoryInputIcon(_nCols, _editor);
    return finishClone(pos);
}

/*public*/ Positionable* MemoryInputIcon::finishClone(MemoryInputIcon* pos) {
    pos->setMemory(namedMemory->getName());
    return PositionableJPanel::finishClone(pos);
}
/*public*/ JComponent *MemoryInputIcon::getTextComponent() {
    return _textBox;
}

/*public*/ void MemoryInputIcon::mouseExited(QGraphicsSceneMouseEvent* e) {
    updateMemory();
    PositionableJPanel::mouseExited(e);
}

/*public*/ void MemoryInputIcon::doMousePressed(QGraphicsSceneMouseEvent* e) {
    updateMemory();
    PositionableJPanel::mousePressed(e);
}

/**
 * Attached a named Memory to this display item
  * @param pName Used as a system/user name to lookup the Memory object
 */
 /*public*/ void MemoryInputIcon::setMemory(QString pName)
{
 if (debug) log->debug("setMemory for memory= "+pName);
 if (InstanceManager::memoryManagerInstance()!=NULL)
 {
  Memory* memory =((AbstractMemoryManager*) InstanceManager::memoryManagerInstance())->provideMemory(pName);
  if (memory != NULL)
  {
   setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, memory));
  }
  else
  {
   log->error("Memory '"+pName+"' not available, icon won't see changes");
  }
 }
 else
 {
  log->error("No MemoryManager for this protocol, icon won't see changes");
  }
  updateSize();
 }

/**
 * Attached a named Memory to this display item
 * @param m The Memory object
 */
/*public*/ void MemoryInputIcon::setMemory(NamedBeanHandle<Memory*>* m)
{
 if (namedMemory != NULL)
 {
  getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//  AbstractMemory* old = (AbstractMemory*)getMemory();
//  disconnect(old, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 namedMemory = m;
 if (namedMemory != NULL)
 {
  getMemory()->addPropertyChangeListener((PropertyChangeListener*)this, namedMemory->getName(), "Memory Input Icon");
//  AbstractMemory* m = (AbstractMemory*)namedMemory->getBean();
//  connect(m->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//  connect(m->pcs, SIGNAL(propertyChange(QString,QVariant,QVariant)), this, SLOT(on_propertyChange(QString,QVariant,QVariant)));

  displayState();
  setName(namedMemory->getName());
 }
}

/*public*/ void MemoryInputIcon::setNumColumns(int nCols)
{
 _textBox->setColumns(nCols);
 _textDisplay->setColumns(nCols);
 _nCols = nCols;
}

/*public*/ NamedBeanHandle<Memory*>* MemoryInputIcon::getNamedMemory() { return namedMemory; }

/*public*/ Memory* MemoryInputIcon::getMemory()
{
 if (namedMemory==NULL) {
     return NULL;
 }
 return namedMemory->getBean();
}

/*public*/ int MemoryInputIcon::getNumColumns() { return _nCols; }

// update icon as state of Memory changes
/*public*/ void MemoryInputIcon::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("value"))
 {
  displayState();
 }

 if(e->getPropertyName() == "value" && e->getNewValue().type() == QVariant::DateTime)
 {
  //qDebug() <<tr("property change %1 %2 %3").arg(sType).arg(sOld.toString()).arg(sNew.toString());
  QString text = e->getNewValue().toDateTime().toString("hh:mm AP");
  _textBox->setText(text);
  _textDisplay->setText(text);
 }
 else if(e->getPropertyName() == "value" && e->getNewValue().canConvert<QString>())
 {
  _textBox->setText(e->getNewValue().toString());
  _textDisplay->setText(e->getNewValue().toString());

 }
 else
  log->debug("unhandled property change " + getNameString() + " type=" + e->getNewValue().typeName());
}

/*public*/ QString MemoryInputIcon::getNameString()
{
 QString name;
 if (namedMemory == NULL) name = tr("<Not connected>");
 else if (getMemory()->getUserName()!=NULL)
     name = getMemory()->getUserName()+" ("+getMemory()->getSystemName()+")";
 else
     name = getMemory()->getSystemName();
 return name;
}

/*private*/ void MemoryInputIcon::updateMemory()
{
 if (namedMemory == NULL) return;
 QString str = _textBox->text();
 getMemory()->setValue(str);
}

/*public*/ bool MemoryInputIcon::setEditIconMenu(QMenu* popup)
{
 QString txt = QString("Edit %1Item").arg( tr("Memory"));
 QAction* act = new QAction(txt, this);

//    popup.add(new javax.swing.AbstractAction(txt) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                edit();
//            }
//        });

 connect(act, SIGNAL(triggered()), this, SLOT(edit()));\
 popup->addAction(act);
 return true;
}

/**
* Poppup menu iconEditor's ActionListener
*/
/*protected*/ void MemoryInputIcon::edit()
{
 _iconEditor = new MyIconAdder("Memory", this);
 {
//  QSpinBox* spinner = new JSpinner(_spinModel);
//            protected void addAdditionalButtons(JPanel p) {
//                ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField().setColumns(2);
//                spinner.setMaximumSize(spinner.getPreferredSize());
//                spinner.setValue(Integer.valueOf(_textBox.getColumns()));
//                JPanel p2 = new JPanel();
//                //p2.setLayout(new BoxLayout(p2, BoxLayout.X_AXIS));
//                //p2.setLayout(new FlowLayout(FlowLayout.TRAILING));
//                p2.add(new JLabel(Bundle.getMessage("NumColsLabel")));
//                p2.add(spinner);
//                p.add(p2);
//                p.setVisible(true);
//            }
//    };

 makeIconEditorFrame(this, "Memory", true, _iconEditor);
 _iconEditor->setPickList(PickListModel::memoryPickModelInstance());
//    ActionListener addIconAction = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent* a) {
//            editMemory();
//        }
//    };
 MiiActionListener* addIconAction = new MiiActionListener(this);
 _iconEditor->makeIconPanel(false);
 _iconEditor->complete(addIconAction, false, true, true);
 _iconEditor->setSelection(getMemory());
 }
}
MyIconAdder::MyIconAdder(QString type, MemoryInputIcon *parent) : IconAdder(type,parent)
{
 this->parent = parent;
 spinner = new QSpinBox();
}
 /*protected*/ void MyIconAdder::addAdditionalButtons(QWidget* p)
 {
//     ((JSpinner.DefaultEditor)spinner.getEditor()).getTextField().setColumns(2);
  spinner->setMaximumSize(spinner->size());
  spinner->setValue((parent->_textBox->getColumns()));
  QWidget* p2 = new QWidget();
  //p2.setLayout(new BoxLayout(p2, BoxLayout.X_AXIS));
  p2->setLayout(new FlowLayout(/*FlowLayout::TTRAILING*/));
  p2->layout()->addWidget(new QLabel(tr("Col Width")));
  p2->layout()->addWidget(spinner);
  p->layout()->addWidget(p2);
  p->setVisible(true);
 }


void MemoryInputIcon::editMemory()
{
 setMemory(_iconEditor->getTableSelection()->getDisplayName());
 _nCols = _spinModel->getNumber().toInt();
//    _textBox->setColumns(_nCols);
 setSize(size().width()+1, size().height());
 _iconEditorFrame->close();
 _iconEditorFrame = NULL;
 _iconEditor = NULL;
 //validate();
}

/**
 * Drive the current state of the display from the state of the
 * Memory.
 */
/*public*/ void MemoryInputIcon::displayState()
{
 if (debug) log->debug("displayState");
 if (namedMemory == NULL)
 {  // leave alone if not connected yet
  return;
 }
 QVariant show = ((AbstractMemory*)getMemory())->getValue();
 if (show!=QVariant())
 {
  QString text = show.toString();
  if(text.length() > _nCols)
  {
   setNumColumns(text.length());
   _spinModel->setValue(text.length());
  }
  _textDisplay->setText(text);
  _textBox->setText(text);
 }
 else
 {
  _textBox->setText("");
  _textDisplay->setText("");
 }
}

void MemoryInputIcon::cleanup()
{
 if (namedMemory!=NULL) {
     getMemory()->removePropertyChangeListener((PropertyChangeListener*)this);
//     AbstractMemory* m = (AbstractMemory*)getMemory();
//     disconnect(m, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
 if (_textBox!=NULL) {
//        _textBox->removeMouseMotionListener(this);
//        _textBox->removeMouseListener(this);
     _textBox = NULL;
 }
 namedMemory = NULL;
}
MiiActionListener:: MiiActionListener(MemoryInputIcon* parent)
{
 this->parent = parent;
}
/*public*/ void MiiActionListener::actionPerformed(JActionEvent* /*a*/)
{
 parent->editMemory();
}

