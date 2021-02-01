#ifndef DECVARIABLEVALUE_H
#define DECVARIABLEVALUE_H
#include "variablevalue.h"
#include "cvvalue.h"
#include <QList>
#include "actionevent.h"
#include "jtextfield.h"
#include "vartextfield.h"

class DecVarSlider;
class LIBPR3SHARED_EXPORT DecVariableValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit DecVariableValue(QObject *parent = 0);
    /*public*/ DecVariableValue(QString name, QString comment, QString cvName,
                            bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                            QString cvNum, QString mask, int minVal, int maxVal,
                            QMap<QString, CvValue*>* v, QLabel* status, QString stdname, QObject *parent = 0);
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVector<CvValue*>* usesCVs() override;
    /*public*/ QVariant rangeVal()override;
    void updatedTextField();
    /*public*/ QString getValueString() override;
    // to complete this class, fill in the routines to handle "Value" parameter
    // and to read/write/hear parameter changes.
    /*public*/ void setIntValue(int i) override;
    /*public*/ int getIntValue() override;
    /*public*/ QVariant getValueObject() override;
    /*public*/ QWidget* getCommonRep() override;
    /*public*/ void setAvailable(bool a);
    /*public*/ QWidget* getNewRep(QString format) override;
    /*public*/ void setValue(int value);
    QColor getColor();
    void setColor(QColor c);
    /*public*/ void setCvState(int state) override;
    /*public*/ bool isChanged() override;
    /*public*/ void readChanges() override;
    /*public*/ void writeChanges() override;
    /*public*/ void readAll() override;
    /*public*/ void writeAll() override;
    /*public*/ void dispose() override;

signals:

public slots:
    void value_changed();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void actionPerformed(JActionEvent* e = 0);
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e = 0);
    /*public*/ void focusLost(/*FocusEvent*/QEvent* e = 0);

private:
    int _maxVal;
    int _minVal;
    QString oldContents;// = "";
    QList<QWidget*>* reps;// = new QList<QWidget*>();
    QList<DecVarSlider*>* sliders;// = new QList<DecVarSlider>();
    QColor _defaultColor;
    QColor currColor;
    // stored value, read-only Value
    JTextField* _value;// = NULL;
 Logger* log;
 void enterField();
 void exitField();

 friend class HexVariableValue;
 friend class VarTextField;
};
#if 0
/* Internal class extends a JTextField so that its color is consistent with
 * an underlying variable
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version
 */
/*public*/ class VarTextField : public JTextField
{
 public:
    VarTextField(QDomDocument doc, QString text, int col, VariableValue* var, QWidget* parent = 0) : JTextField(doc, text, col,parent)
    {
     //super(doc, text, col);
     this->doc = doc;
     this->col = col;
        _var = var;
        // get the original color right
     setBackground(_var->_value->getBackground());
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
//                }

//                /*public*/ void focusLost(FocusEvent e) {
//                    if (log->isDebugEnabled()) log->debug("focusLost");
//                    exitField();
//                }
//            });
        // listen for changes to original state
        _var->addPropertyChangeListener(new PropertyChangeListener());
//        {
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    originalPropertyChanged(e);
//                }
//            });
    }

    //DecVariableValue* _var;
    VariableValue* _var;
    QDomDocument doc;
    int col;

    void thisActionPerformed(ActionEvent* /*e*/) {
        // tell original
        if(qobject_cast<DecVariableValue*>(_var)!=NULL)
            ((DecVariableValue*)_var)->actionPerformed(e);
//        else
//        _var->actionPerformed(e);
    }

    void originalPropertyChanged(PropertyChangeEvent* e) {
        // update this color from original state
        if (e->getPropertyName()==("State")) {
         setBackground(_var->_value->getBackground());
        }
    }
    QDomDocument getDocument() {return doc;}
};
#endif
#endif // DECVARIABLEVALUE_H
