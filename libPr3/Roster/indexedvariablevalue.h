#ifndef INDEXEDVARIABLEVALUE_H
#define INDEXEDVARIABLEVALUE_H
#include "variablevalue.h"
#include "cvvalue.h"
#include "actionevent.h"
#include "indexedvarslider.h"
#include <QtXml>

class IndexedVarSlider;
class VarTextField;
class JTextField;
class LIBPR3SHARED_EXPORT IndexedVariableValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit IndexedVariableValue(QObject *parent = 0);
    /*public*/ IndexedVariableValue(int row, QString name, QString comment, QString cvName,
                                bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                QString cvNum, QString mask, int minVal, int maxVal,
                                QMap<QString,CvValue*>* v, QLabel* status, QString stdname, QObject *parent = 0);
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVector<CvValue*>* usesCVs();
    /*public*/ QVariant rangeVal();
    void enterField();
    void exitField();
    void updatedTextField() ;
    // to complete this class, fill in the routines to handle "Value" parameter
    // and to read/write/hear parameter changes.
    /*public*/ QString getValueString() ;
    /*public*/ void setIntValue(int i) ;
    /*public*/ int getIntValue();
    /*public*/ QVariant getValueObject();
    /*public*/ QWidget* getCommonRep() ;
    /*public*/ QWidget* getNewRep(QString format) ;
    /*public*/ void setAvailable(bool a);
    /*public*/ void setValue(int value);
    // implement an abstract member to set colors
    QColor getColor();
    void setColor(QColor c);
    /*public*/ void setCvState(int state);
    /*public*/ void setToRead(bool state) ;
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state) ;
    /*public*/ bool isToWrite();
    /*public*/ bool isChanged() ;
    /*public*/ void readChanges();
    /*public*/ void writeChanges();
    /*public*/ void readAll();
    /*public*/ void writeAll() ;
    /*public*/ void confirmAll() ;
    // clean up connections when done
    /*public*/ void dispose();

signals:

public slots:
    // handle incoming parameter notification
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /** ActionListener implementations */
    /*public*/ void actionPerformed(ActionEvent* e = 0);
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e = 0);
    /*public*/ void focusLost(/*FocusEvent*/QEvent* e = 0) ;
private:
 Logger* logit;
 int _row;
 int _maxVal;
 int _minVal;
 QString oldContents;// = "";
 QList<IndexedVarSlider*>* sliders;// = new QList<IndexedVarSlider>();
 QList<VarTextField*>* valuereps;// = new QList<VarTextField*>();

 /*private*/ int _progState;// = 0;
 /*private*/ static /*final*/ const int IDLE = 0;
 /*private*/ static /*final*/ const int WRITING_PI4R = 1;
 /*private*/ static /*final*/ const int WRITING_PI4W = 2;
 /*private*/ static /*final*/ const int WRITING_SI4R = 3;
 /*private*/ static /*final*/ const int WRITING_SI4W = 4;
 /*private*/ static /*final*/ const int READING_CV = 5;
 /*private*/ static /*final*/ const int WRITING_CV = 6;
 /*private*/ static /*final*/ const int WRITING_PI4C = 7;
 /*private*/ static /*final*/ const int WRITING_SI4C = 8;
 /*private*/ static /*final*/ const int COMPARE_CV = 9;
 /**
  * Count number of retries done
  */
 /*private*/ int retries;// = 0;
 QColor _defaultColor;
 // stored value
 JTextField* _value;// = null;

 /**
  * Define maximum number of retries of read/write operations before moving on
  */
 /*private*/ static /*final*/ const int RETRY_MAX = 2;

protected:
 /*protected*/ IndexedVariableValue(QObject *parent = 0);

};
#if 0
/* Internal class extends a JTextField so that its color is consistent with
 * an underlying variable
 *
 * @author	Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 21023 $
 */
/*public*/ class VarTextField : public QLineEdit
{
 public:
    VarTextField(QDomDocument doc, QString text, int col, IndexedVariableValue* var, QWidget* parent = 0) : QLineEdit(text, parent)
    {
     //super(doc, text, col);
     _col = col;
     _var = var;
     // get the original color right
     setBackground(_var._value->getBackground());
        // listen for changes to ourself
//        addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                thisActionPerformed(e);
//            }
//        });
//        addFocusListener(new java.awt.event.FocusListener() {
//            /*public*/ void focusGained(FocusEvent e) {
//                if (log->isDebugEnabled()) log->debug("focusGained");
//                enterField();
//            }

//            /*public*/ void focusLost(FocusEvent e) {
//                if (log->isDebugEnabled()) log->debug("focusLost");
//                exitField();
//            }
//        });
        // listen for changes to original state
//        _var->addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                originalPropertyChanged(e);
//            }
//        });
    }

   IndexedVariableValue* _var;
   int _col;

   void thisActionPerformed(ActionEvent* /*e*/) {
       // tell original
       _var->actionPerformed(e);
   }

   void originalPropertyChanged(PropertyChangeEvent* e) {
       // update this color from original state
       if (e->getPropertyName()==("State")) {
        setBackground(_var->_value->getBackground());
       }
   }
};
#endif

#endif // INDEXEDVARIABLEVALUE_H
