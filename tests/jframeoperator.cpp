#include "jframeoperator.h"
#include "jmrijframe.h"
#include <QRadioButton>
#include "jlabel.h"
#include "namecomponentchooser.h"
#include "jdialog.h"
#include <QDebug>

JFrameOperator::JFrameOperator(QObject *parent) : QObject()
{
 if(qobject_cast<JmriJFrame*>(parent))
  _frame = (JmriJFrame*)parent;
}

JFrameOperator::JFrameOperator(QString chooser) : QObject()
{
 QList<JmriJFrame*>* frameList = JmriJFrame::getFrameList();
 foreach (JmriJFrame* frame, *frameList)
 {
  if(frame->title() == chooser)
  {
   this->_frame = frame;
   break;
  }
 }
 if(this->_frame == nullptr)
  throw Exception(tr("frame title '%1' not found").arg(chooser));
}

JmriJFrame* JFrameOperator::getFrame()
{
 return _frame;
}

JRadioButtonOperator::JRadioButtonOperator(QObject*parent, QString text)
{
 this->text = text;
 this->parent = parent;
  QWidget* frame = parentWidget();
  {
   QList<QRadioButton*> list = frame->findChildren<QRadioButton*>();
   if(list.isEmpty())
    throw Exception(tr("QRadioButton '%1' not found ").arg(text));
   foreach(QRadioButton* b, list)
   {
    if(b->text() == text)
    {
     this->button = b;
    }
   }
  }
}
QWidget* JRadioButtonOperator::parentWidget()
{
 if(qobject_cast<QWidget*>(parent))
 {
  return qobject_cast<QWidget*>(parent);
 }
 else  if(qobject_cast<JFrameOperator*>(parent))
 {
   JFrameOperator* oper = (JFrameOperator*)parent;
   if(oper->getFrame())
    return (oper->getFrame());
 }
 else
  throw Exception("no parent widget defined for JRadioButtonOperator");
}

JButtonOperator::JButtonOperator(QObject* parent, QString text)
{
 this->text = text;
 this->parent = parent;
 list = parentWidget()->findChildren<QPushButton*>();
 if(list.isEmpty())
  throw Exception(tr("QPushButton '%1' not found ").arg(text));
 if(!text.isEmpty())
 {
  foreach(QPushButton* b, list)
  {
   qDebug() <<"button text: " << b->text();
    if(checkComponent((QWidget*)b))
    {
     this->button =b;
     break;
    }
  }
  if(this->button == nullptr)
   throw Exception(tr("QPushButton '%1' not found ").arg(text));
 }
}

/*private*/ void JButtonOperator::findButton()
{
 foreach(QPushButton* b, list)
 {
   if(checkComponent((QWidget*)b))
   {
    this->button =b;
    break;
   }
 }
 if(this->button == nullptr)
  throw Exception(tr("QPushButton '%1' not found ").arg(text));
}

/*private*/ bool JButtonOperator::checkComponent(QWidget* b)
{
 if(((QPushButton*)b)->text() == text)
  return true;
 else
  return false;
}
/*public*/ void JButtonOperator::push()
{
 if(!button)
  findButton();
 if(button)
 {
  //button->click();
   QMetaObject::invokeMethod(button, "click", Qt::QueuedConnection);
 }
}

void JButtonOperator::doClick()
{
 if(!button)
  findButton();
 if(button) button->click();
}

JButtonOperator::JButtonOperator(JDialogOperator*, NameComponentChooser*)
{

}

/*public*/ QString  JButtonOperator::getDescription()
{
 return "";
}

QWidget* JButtonOperator::parentWidget()
{
 if(qobject_cast<QWidget*>(parent))
 {
  return qobject_cast<QWidget*>(parent);
 }
 else  if(qobject_cast<JFrameOperator*>(parent))
 {
   JFrameOperator* oper = (JFrameOperator*)parent;
   if(oper->getFrame())
    return (oper->getFrame());
 }
 else  if(qobject_cast<JDialogOperator*>(parent))
 {
   JDialogOperator* oper = (JDialogOperator*)parent;
    return (oper->getDialog());
 }

 else
  throw Exception("no parent widget defined for JButtonOperator");
}

JCheckBoxOperator::JCheckBoxOperator(QObject*parent, QString text)
{
 this->text = text;
 this->parent = parent;
 QList<QCheckBox*> list = parentWidget()->findChildren<QCheckBox*>();
 if(list.isEmpty())
  throw Exception(tr("QCheckBox '%1' not found ").arg(text));
 foreach(QCheckBox* b, list)
 {
  if(b->text() == text)
  {
   this->checkBox = b;
  }
 }
}

QWidget* JCheckBoxOperator::parentWidget()
{
 if(qobject_cast<QWidget*>(parent))
 {
  return qobject_cast<QWidget*>(parent);
 }
 else  if(qobject_cast<JFrameOperator*>(parent))
 {
   JFrameOperator* oper = (JFrameOperator*)parent;
   if(oper->getFrame())
    return (oper->getFrame());
 }
 else
  throw Exception("no parent widget defined for JCheckBoxOperator");
}

JToggleButtonOperator::JToggleButtonOperator(QObject*parent, QString text)
{
 this->text = text;
 this->parent = parent;
 QList<JToggleButton*> list = parentWidget()->findChildren<JToggleButton*>();
 if(list.isEmpty())
  throw Exception(tr("JToggleButton '%1' not found ").arg(text));
 foreach(JToggleButton* b, list)
 {
  if(b->text() == text)
  {
   this->button = b;
  }
 }
}

QWidget* JToggleButtonOperator::parentWidget()
{
 if(qobject_cast<QWidget*>(parent))
 {
  return qobject_cast<QWidget*>(parent);
 }
 else
  throw Exception("no parent widget defined for JToggleButtonOperator");
}

JToggleButtonOperator::JToggleButtonOperator(FunctionButton *fb)
{

}

bool JButtonOperator::isEnabled()
{
  if(button) return button->isEnabled();
  throw Exception(tr("button %1 not found").arg(text));
}

JLabelOperator::JLabelOperator(QObject *parent, QString text)
{
 this->parent = parent;
 this->text = text;
  QList<QLabel*> list = parentWidget()->findChildren<QLabel*>();
  if(list.isEmpty())
   throw Exception(tr("QLabel '%1' not found ").arg(text));
  foreach(QLabel* b, list)
  {
   if(b->text() == text)
   {
    this->label = b;
    break;
   }
  }
  if(this->label == nullptr)
   throw Exception(tr("QLabel '%1' not found ").arg(text));

}

QWidget *JLabelOperator::getLabelFor()
{
 if(qobject_cast<JLabel*>(label))
 {

  QWidget* labelfor = ((JLabel*)label)->getLabelFor();
  if(labelfor == nullptr)
   throw Exception(tr("no labelFor defined for label %1").arg(text));
  return labelfor;
 }
 throw Exception(tr("no labelFor defined for label %1").arg(text));
}

QWidget* JLabelOperator::parentWidget()
{
 if(qobject_cast<QWidget*>(parent))
 {
  return qobject_cast<QWidget*>(parent);
 }
 else  if(qobject_cast<JFrameOperator*>(parent))
 {
   JFrameOperator* oper = (JFrameOperator*)parent;
   if(oper->getFrame())
    return (oper->getFrame());
 }
 else
  throw Exception("no parent widget defined for JLabelOperator");
}

JMenuBarOperator::JMenuBarOperator(QObject *parent)
{
 this->parent = parent;
}

/*private*/ JmriJFrame* JMenuBarOperator::getFrame()
{
 if(qobject_cast<JmriJFrame*>(parent))
  return (JmriJFrame*)parent;
 throw Exception("no frame defined for JMenuBarOperator");
}

///*public*/ QMenuBar* JMenuBarOperator::menuBar()
//{
// getFrame()->menuBar();
//}

JMenuOperator::JMenuOperator(QMenu* parent, QString text)
{
 QObjectList list = parent->children();
 foreach (QObject* obj, list) {
  if(qobject_cast<QMenu*>(obj) && ((QMenu*)obj)->title() == text)
   menu = (QMenu*)obj;
 }
}

JMenuOperator::JMenuOperator(JMenuBarOperator* jmbo, QString text)
{
 // TODO:
}


void JMenuOperator::push()
{

}
JPopupMenuOperator::JPopupMenuOperator()
{

}
JPopupMenuOperator::JPopupMenuOperator(QMenu* parent, QString text)
{
 QObjectList list = parent->children();
 foreach (QObject* obj, list) {
  if(qobject_cast<QMenu*>(obj) && ((QMenu*)obj)->title() == text)
   menu = (QMenu*)obj;
 }
}

void JPopupMenuOperator::pushMenuNoBlock(QString text)
{

}

JMenuItemOperator::JMenuItemOperator(QMenu* parent, QString text)
{
 QObjectList list = parent->children();
 foreach (QObject* obj, list) {
  if(qobject_cast<QMenu*>(obj) && ((QAction*)obj)->text() == text)
   action = (QAction*)obj;
 }
}

JMenuItemOperator::JMenuItemOperator(JFrameOperator *jmbo, QString text)
{
 // TODO:
}


void JMenuItemOperator::push()
{
 action->toggle();
}

JDialogOperator::JDialogOperator(QString text)
{
 //this->parent = parent;
 this->text = text;

 // look for a window with the title" 'text'
 JDialog* dlg = JDialog::findDialog(text);
 if(dlg == nullptr)
  throw Exception(tr("frame title '%1' not found").arg(text));
 this->frameOperator = new JFrameOperator(dlg);
 this->dialog = dlg;
}

JDialogOperator::JDialogOperator(JFrameOperator* frame, int number)
{
 //this->parent = parent;
 this->number = number;
 this->frameOperator = frame;
}


JTextFieldOperator::JTextFieldOperator(QObject *parent, QString name)
{
 QWidget* w;
 if(qobject_cast<JInternalFrameOperator*>(parent))
  w = ((JInternalFrameOperator*)parent)->result();
 else w = (QWidget*)parent;
 textField = w->findChild<JTextField*>(name);
}

JTextFieldOperator::JTextFieldOperator(QObject *parent)
{
 QWidget* w;
 if(qobject_cast<JInternalFrameOperator*>(parent))
  w = ((JInternalFrameOperator*)parent)->result();
 else w = (QWidget*)parent;

 // only one
 QList<JTextField*> list = w->findChildren<JTextField*>();
 if(list.size()>0)
  textField = list.at(0);
 if(list.size()>1)
  throw Exception("more than one textField found!");
}

void JTextFieldOperator::typeText(QString text)
{
 textField->setText(text);
}

JInternalFrameOperator::JInternalFrameOperator(QObject *parent, QString name)
{
 this->parent = parent;
 this->name = name;
 _result = parent->findChild<QWidget*>(name);
}
void JInternalFrameOperator::clickForPopup()
{
 if(qobject_cast<QMenu*>(_result))
 {
  ((QMenu*)_result)->exec();
 }
}

JSliderOperator::JSliderOperator(QObject *parent)
{
 QWidget* w;
 if(qobject_cast<JInternalFrameOperator*>(parent))
 {
  w = ((JInternalFrameOperator*)parent)->result();
 }
}

QWidget* JSliderOperator::parentWidget()
{
 if(qobject_cast<QWidget*>(parent))
 {
  return qobject_cast<QWidget*>(parent);
 }
 else  if(qobject_cast<JFrameOperator*>(parent))
 {
   JFrameOperator* oper = (JFrameOperator*)parent;
   if(oper->getFrame())
    return (oper->getFrame());
 }
 else
  throw Exception("no parent widget defined for JSliderOperator");
}

void JSliderOperator::scrollToValue(int i)
{
 slider->setValue(i);
}
void JSliderOperator::setValue(int i)
{
 slider->setValue(i);
}
int JSliderOperator::getValue()
{
 return slider->getValue();
}
void JSliderOperator::scrollToMinimum()
{
 slider->setValue(slider->minimum());
}
void JSliderOperator::scrollToMaximum()
{
 slider->setValue(slider->maximum());
}


JSpinnerOperator::JSpinnerOperator(QObject *parent)
{
 QWidget* w;
 if(qobject_cast<JInternalFrameOperator*>(parent))
 {
  w = ((JInternalFrameOperator*)parent)->result();
 }
}
void JSpinnerOperator::scrollToValue(int i)
{
 spinner->setValue(i);
}
void JSpinnerOperator::scrollToMaximum()
{
 spinner->setValue(spinner->maximum());
}
void JSpinnerOperator::scrollToMinimum()
{
 spinner->setValue(spinner->minimum());
}
void JSpinnerOperator::setValue(int i)
{
 spinner->setValue(i);
}
