#include "vartextfield.h"
#include "decvariablevalue.h"
#include "actionevent.h"
#include "propertychangeevent.h"
#include <QtXml>
#include "indexedpairvariablevalue.h"
#include "longaddrvariablevalue.h"
#include "splitvariablevalue.h"
#include "shortaddrvariablevalue.h"

//VarTextField::VarTextField(QWidget *parent) :
//    JTextField(parent)
//{
//}
VarTextField::VarTextField(Document* doc, QString text, int col, VariableValue* var, QWidget* parent) : JTextField(doc, text, col,parent)
{
 //super(doc, text, col);
 this->doc = doc;
 this->col = col;
 _var = var;
 QFontMetrics fm(fontMetrics());
 setMaximumWidth((col+1)*fm.width("M"));
 // get the original color right
 //setBackground(_var->_value->getBackground());
 if(qobject_cast<ShortAddrVariableValue*>(_var)!= 0)
     setBackground(((ShortAddrVariableValue*)_var)->_value->getBackground());
 else  if(qobject_cast<LongAddrVariableValue*>(_var)!= 0)
     setBackground(((LongAddrVariableValue*)_var)->_value->getBackground());
 else  if(qobject_cast<DecVariableValue*>(_var)!= 0)
     setBackground(((DecVariableValue*)_var)->_value->getBackground());
 else  if(qobject_cast<SplitVariableValue*>(_var)!= 0)
     setBackground(((SplitVariableValue*)_var)->_value->getBackground());
 else
 {
     logit->debug(tr("Missing cast ")+ _var->metaObject()->className());
     Q_ASSERT(false);
 }

// listen for changes to ourself
//        addActionListener(new ActionListener());
//        {
//                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                    thisActionPerformed(e);
//                }
//            });
//        addFocusListener(new FocusListener() {
//                /*public*/ void focusGained(FocusEvent e) {
//                    if (log->isDebugEnabled()) log->debug("focusGained");
//                    enterField();
//                }+QString::number(PaneProgFrame::iLabel++)

//                /*public*/ void focusLost(FocusEvent e) {
//                    if (log->isDebugEnabled()) log->debug("focusLost");
//                    exitField();
//                }
//            });
 connect(this, SIGNAL(editingFinished()), this, SLOT(thisActionPerformed()));
    // listen for changes to original state
 //_var->addPropertyChangeListener(new PropertyChangeListener());
 _var->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(_var->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//        {
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    originalPropertyChanged(e);
//                }
//            });
}
/*public*/ void VarTextField::propertyChange(PropertyChangeEvent* e)
{
 originalPropertyChanged(e);
}
void VarTextField::thisActionPerformed(ActionEvent* e) {
    // tell original
    if(qobject_cast<DecVariableValue*>(_var)!=NULL)
    {
     ((DecVariableValue*)_var)->_value->setText(this->text());
     ((DecVariableValue*)_var)->actionPerformed(e);
    }
    else
    if(qobject_cast<IndexedPairVariableValue*>(_var)!=NULL)
    {
      ((IndexedPairVariableValue*)_var)->_value->setText(text());
      ((IndexedPairVariableValue*)_var)->actionPerformed(e);
    }
    else
    if(qobject_cast<LongAddrVariableValue*>(_var)!=NULL)
    {
     ((LongAddrVariableValue*)_var)->_value->setText(text());
     ((LongAddrVariableValue*)_var)->actionPerformed(e);
    }
    else
    if(qobject_cast<SplitVariableValue*>(_var)!=NULL)
    {
     ((SplitVariableValue*)_var)->_value->setText(text());
     ((SplitVariableValue*)_var)->actionPerformed(e);
    }
    else
    {
    //        _var->actionPerformed(e);
     logit->error(tr("missing cast for ") + QString(_var->metaObject()->className()));
     Q_ASSERT(false);
    }
}

void VarTextField::originalPropertyChanged(PropertyChangeEvent* e)
{
 // update this color from original state
 if (e->getPropertyName()==("State"))
 {
  // setBackground(_var->_value->getBackground());
  if(qobject_cast<ShortAddrVariableValue*>(_var)!=NULL)
   setBackground(((ShortAddrVariableValue*)_var)->_value->getBackground());
  else if(qobject_cast<LongAddrVariableValue*>(_var)!=NULL)
   setBackground(((LongAddrVariableValue*)_var)->_value->getBackground());
  else if(qobject_cast<DecVariableValue*>(_var)!=NULL)
  setBackground(((DecVariableValue*)_var)->_value->getBackground());
  else
  {
   logit->debug(tr( "missing cast ")+ _var->metaObject()->className());
   Q_ASSERT(false);
  }
 }
 else if(e->getPropertyName() == "Value")
 {
  setText(e->getNewValue().toString());
 }
}
Document* VarTextField::getDocument() {return doc;}
