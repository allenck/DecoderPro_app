#ifndef LONGADDRVARIABLEVALUE_H
#define LONGADDRVARIABLEVALUE_H
#include "variablevalue.h"
#include "cvvalue.h"
#include "actionevent.h"
#include <QtXml>
class JTextField;
class LIBPR3SHARED_EXPORT LongAddrVariableValue : public VariableValue
{
    Q_OBJECT
public:
 //explicit LongAddrVariableValue(QObject *parent = 0);
 /*public*/ LongAddrVariableValue(QString name, QString comment, QString cvName,
                                 bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                 QString cvNum, QString mask, int minVal, int maxVal,
                                 QMap<QString, CvValue*>* v, QLabel* status, QString stdname, QObject *parent = 0);
    /*public*/ QVector<CvValue*>* usesCVs() ;
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVariant rangeVal();

    void enterField();
    void exitField();
    void updatedTextField() ;
    // to complete this class, fill in the routines to handle "Value" parameter
    // and to read/write/hear parameter changes.
    /*public*/ QString getValueString();
    /*public*/ void setIntValue(int i);
    /*public*/ int getIntValue();
    /*public*/ QVariant getValueObject();
    /*public*/ QWidget* getCommonRep() ;
    /*public*/ void setValue(int value);
    // implement an abstract member to set colors
    void setColor(QColor c);
    /*public*/ QWidget* getNewRep(QString format);
    /*public*/ void setCvState(int state);
    /*public*/ bool isChanged();
    /*public*/ void setToRead(bool state);
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state);
    /*public*/ bool isToWrite();
    /*public*/ void readChanges();
    /*public*/ void writeChanges();
    /*public*/ void readAll();
    /*public*/ void writeAll();
    /*public*/ void dispose();

signals:

public slots:
    void textChanged();
    // handle incoming parameter notification
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void actionPerformed(JActionEvent* e = 0);
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e = 0);
    /*public*/ void focusLost(/*FocusEvent*/QEvent* e = 0) ;

private:

    int _maxVal;
    int _minVal;
    QString oldContents;// = "";
    /*private*/ int _progState;// = 0;
    /*private*/ static /*final*/ const int IDLE = 0;
    /*private*/ static /*final*/ const int READING_FIRST = 1;
    /*private*/ static /*final*/ const int READING_SECOND = 2;
    /*private*/ static /*final*/ const int WRITING_FIRST = 3;
    /*private*/ static /*final*/ const int WRITING_SECOND = 4;
    QColor _defaultColor;
    JTextField* _value;
    Logger* logit;
    friend class VarTextField;
friend class DccAddressPanel;
friend class MyDccAddressVarHandler1;
friend class MyDccAddressVarHandler2;

};

#endif // LONGADDRVARIABLEVALUE_H
