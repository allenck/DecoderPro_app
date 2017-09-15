#ifndef INDEXEDENUMVARIABLEVALUE_H
#define INDEXEDENUMVARIABLEVALUE_H
#include "cvvalue.h"
#include "variablevalue.h"
#include <QComboBox>
#include "indexedcombocheckbox.h"
#include "comboboxmodel.h"
#include "comboradiobuttons.h"

class IVCBPropertyChangeListener;
class IVarComboBox;
class CvValue;
class ActionEvent;
class ComboRadioButtons;
class IndexedComboCheckBox;
class LIBPR3SHARED_EXPORT IndexedEnumVariableValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit IndexedEnumVariableValue(QObject *parent = 0);
    /*public*/ IndexedEnumVariableValue(int row, QString name, QString comment, QString cvName,
                                    bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                    QString cvNum, QString mask,
                                    QMap<QString, CvValue*>* v, QLabel* status, QString stdname, QObject *parent = 0);
    /*public*/ QVector<CvValue*>* usesCVs();
    /*public*/ void nItems(int n);
    /*public*/ void addItem(QString s);
    /*public*/ void addItem(QString s, int value);
    /*public*/ void lastItem();
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVariant rangeVal();
    /*public*/ void actionPerformed(ActionEvent* /*e*/);
    /*public*/ QString getValueString();
    /*public*/ void setIntValue(int i);
    /*public*/ QString getTextValue();
    /*public*/ int getIntValue();
    /*public*/ QVariant getValueObject();
    /*public*/ QWidget* getCommonRep();
    /*public*/ void setValue(int value);
    /*public*/ QWidget* getNewRep(QString format);
    void setColor(QColor c);
    /*public*/ void setAvailable(bool a);
    /*public*/ void setCvState(int state);
    /*public*/ void setToRead(bool state);
    /*public*/ bool isToRead() ;
    /*public*/ void setToWrite(bool state);
    /*public*/ bool isToWrite();
    /*public*/ bool isChanged();
    /*public*/ void readChanges();
    /*public*/ void writeChanges();
    /*public*/ void readAll() ;
    /*public*/ void writeAll() ;
    /*public*/ void confirmAll();
    // handle incoming parameter notification
    /*public*/ void dispose();
    // implement an abstract member to set colors
    QColor getBackground();
    void setBackground(QColor c);

signals:

public slots:
    void on_currentIndex_changed(int);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
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
    int _row;
    int _minVal;
    int _maxVal;
    // place to keep the items & associated numbers
    QStringList* _itemArray;// = NULL;
    QVector<int>* _valueArray;// = NULL;
    int _nstored;

    QColor _defaultColor;
    // stored value
    QComboBox* _value;// = NULL;
    QList<IndexedComboCheckBox*>* comboCBs;// = new QList<IndexedComboCheckBox*>();
    QList<IVarComboBox*>* comboVars;// = new QList<IVarComboBox*>();
    /*private*/ QList<ComboRadioButtons*>* comboRBs;// = new QList<ComboRadioButtons>();
 Logger* logit;
 /**
  * Count number of retries done
  */
 /*private*/ int retries;// = 0;

 /**
  * Define maximum number of retries of read/write operations before moving on
  */
 /*private*/ static /*final*/ const int RETRY_MAX = 2;
protected:
    /*protected*/ IndexedEnumVariableValue(QObject *parent = 0);
    /*protected*/ void selectValue(int value);
 friend class ComboRadioButtons;
 friend class IndexedComboCheckBox;
};
class IVCBPropertyChangeListener : public PropertyChangeListener
{
    Q_OBJECT
    IVarComboBox* self;
public:
    IVCBPropertyChangeListener(IVarComboBox* self);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

/* Internal class extends a JComboBox so that its color is consistent with
 * an underlying variable; we return one of these in getNewRep.
 *<P>
 * Unlike similar cases elsewhere, this doesn't have to listen to
 * value changes.  Those are handled automagically since we're sharing the same
 * model between this object and the real JComboBox value.
 *
 * @author  Bob Jacobsen   Copyright (C) 2001
 * @version $Revision: 17977 $
 */
/*public*/ class IVarComboBox : public  QComboBox {
private:
    IndexedEnumVariableValue* _var;
    /*transient*/ IVCBPropertyChangeListener* _l;// = NULL;
    Logger* log;
public:
    IVarComboBox(/*ComboBoxModel* m,*/ IndexedEnumVariableValue* var);
    void originalPropertyChanged(PropertyChangeEvent* e);
    /*public*/ void dispose();
    friend class IVCBPropertyChangeListener;
};

#endif // INDEXEDENUMVARIABLEVALUE_H
