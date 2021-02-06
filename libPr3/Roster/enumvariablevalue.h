#ifndef ENUMVARIABLEVALUE_H
#define ENUMVARIABLEVALUE_H
#include "variablevalue.h"
#include <QLabel>
#include <QComboBox>
#include "combocheckbox.h"
//#include "comboboxmodel.h"
#include "actionevent.h"
#include "comboradiobuttons.h"
#include "propertychangelistener.h"
#include "combocheckbox.h"
#include "defaultmutabletreenode.h"


/* Internal class extends a JComboBox so that its color is consistent with
 * an underlying variable; we return one of these in getNewRep.
 *<P>
 * Unlike similar cases elsewhere, this doesn't have to listen to
 * value changes.  Those are handled automagically since we're sharing the same
 * model between this object and the real JComboBox value.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version         $Revision: 17977 $
 */

class TreePath;
class DefaultMutableTreeNode;
class CvValue;
class VarComboBox;
class ComboCheckBox;
class ComboRadioButtons;
class LIBPR3SHARED_EXPORT EnumVariableValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit EnumVariableValue(QObject *parent = 0);
    /*public*/ EnumVariableValue(QString name, QString comment, QString cvName,
                                 bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                 QString cvNum, QString mask, int minVal, int maxVal,
                                 QMap<QString, CvValue*>* v, JLabel *status, QString stdname, QObject *parent = 0);
    /*public*/ EnumVariableValue(QObject *parent = 0);
    /*public*/ QVector<CvValue*> usesCVs();
    /*public*/ void nItems(int n);
    /*public*/ void addItem(QString s);
    /*public*/ void addItem(QString s, int value);
    /*public*/ void lastItem();
    /*public*/ void setToolTipText(QString t);
    /*public*/ void setAvailable(bool a);
    /*public*/ QVariant rangeVal();
    /*public*/ void actionPerformed(JActionEvent* e = 0);
    /*public*/ QString getValueString();
    /*public*/ void setIntValue(int i);
    /*public*/ QString getTextValue();
    /*public*/ QVariant getValueObject();
    /*public*/ int getIntValue() ;
    /*public*/ QWidget* getCommonRep();
    /*public*/ void setValue(int value);
    /*public*/ QWidget* getNewRep(QString format);
    void setColor(QColor c);
    /*public*/ void setCvState(int state);
    /*public*/ bool isChanged() ;
    /*public*/ void readChanges();
    /*public*/ void writeChanges();
    /*public*/ void readAll();
    /*public*/ void writeAll();
    // handle incoming parameter notification
//    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void dispose();
    void disposeReps();
    QColor getBackground();
    void setBackground( QColor c);
    /*public*/ void startGroup(QString name);
    /*public*/ void endGroup();

signals:
    void valueChanged(int i);
public slots:
    void on_currentIndex_changed(int);
    void propertyChange(PropertyChangeEvent *e);
private:
    // stored value
    QComboBox* _value;// = null;

    // place to keep the items & associated numbers
    /*private*/ QVector<QString>* _itemArray;// = null;
    /*private*/ QVector<int>* _valueArray;//= null;
    /*private*/ QVector<TreePath*>* _pathArray;
    /*private*/ int _nstored;
    QVector<DefaultMutableTreeNode*> treeNodes;

    int _maxVal;
    int _minVal;
    QColor _defaultColor;
    /*private*/ QList<ComboCheckBox*>* comboCBs;// = new ArrayList<ComboCheckBox>();
    /*private*/ QList<VarComboBox*>* comboVars;// = new ArrayList<VarComboBox>();
    /*private*/ QList<ComboRadioButtons*>* comboRBs;// = new ArrayList<ComboRadioButtons>();
    Logger* logit;

protected:
    /*protected*/ void selectValue(int value);
friend class CompositeVariableValue;
friend class ComboRadioButtons;
friend class ComboCheckBox;
friend class VarComboBox;
friend class PropertyChangeSupport;
};


/*public*/ class VarComboBox : public QComboBox
{
 Q_OBJECT
public:

 VarComboBox(/*ComboBoxModel* m,*/ EnumVariableValue* var) //: QComboBox(m)
 {
  //super(m);
  _var = var;
  log = new Logger("VarComboBox");
  connect(this,SIGNAL(currentIndexChanged(int)), this, SLOT(selectionChanged(int)));
//  _l = new PropertyChangeListener();
//        {
//                /*public*/ void propertyChange(PropertyChangeEvent* e) {
//                    if (log.isDebugEnabled()) log.debug("VarComboBox saw property change: "+e);
//                    originalPropertyChanged(e);
//                }
//            };
 // get the original color right
 setBackground(_var->getBackground());
 // listen for changes to original state
 //_var->addPropertyChangeListener(_l);
 _var->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(_var, SIGNAL(valueChanged(int)), this, SLOT(originalPropertyChanged()));
}


/*public*/ void dispose() {
    if (_var != NULL && _l != NULL ) _var->removePropertyChangeListener(_l);
    _l = NULL;
    _var = NULL;
}
public slots:
/*public*/ void propertyChange(PropertyChangeEvent* e)
 {
  if (log->isDebugEnabled()) log->debug("VarComboBox saw property change: "+e->getPropertyName());
  originalPropertyChanged(e);
 }
private:
QColor getBackground()
{
 //return getBackground();
    QColor c;
    QPalette p = palette();
    QString ss = styleSheet();
    c = p.color(QPalette::Background);
    if(ss == "")
      return c;
    int i = ss.indexOf("background");
    int j;
    if(i > 0)
    {
     i= ss.indexOf("rgb(")+4;
     j= ss.indexOf(",",i);
     int red =ss. mid(i,j-i).toInt();
     i=j+1;
     j = ss.indexOf(",",i);
     int green = ss.mid(i,j-i).toInt();
     i=j+1;
     j = ss.indexOf(")");
     int blue =  ss.mid(i,j-i).toInt();
     return QColor(red,green,blue);
    }
    return QColor();
}

void setBackground(QColor c)
{
 QColor oldC = getBackground();
 if(oldC != c)
 {
  QString ss = QString("QComboBox { background : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
  setStyleSheet(ss);
 }
}
public slots:
void selectionChanged(int index)
{
 //_var->on_currentIndex_changed(index);
 _var->_value->setCurrentIndex(index);
 _var->actionPerformed();
}
void originalPropertyChanged(PropertyChangeEvent* e = 0)
{
 if(e != NULL)
 {
  // update this color from original state
  if (e->getPropertyName()==("State"))
  {
   setBackground(_var->getBackground());
  }
 }
 else
 setCurrentIndex(_var->_value->currentIndex());
}

private:
 EnumVariableValue* _var;
 /*transient*/ PropertyChangeListener* _l;// = NULL;
 Logger* log;
};
class TreeLeafNode : public DefaultMutableTreeNode
{
    Q_OBJECT
    /**
     *
     */
    // /*private*/ static final long serialVersionUID = 4826729728567652557L;

    TreeLeafNode(QString name, int index);
private:
    int index;
    friend class EnumVariableValue;
};
#endif // ENUMVARIABLEVALUE_H
