#ifndef SPLITVARIABLEVALUE_H
#define SPLITVARIABLEVALUE_H
#include "variablevalue.h"
#include "cvvalue.h"
#include "actionevent.h"

class JTextField;
class LIBPR3SHARED_EXPORT SplitVariableValue : public VariableValue
{
    Q_OBJECT
public:
 //explicit SplitVariableValue(QObject *parent = 0);
 /*public*/ SplitVariableValue(QString name, QString comment, QString cvName,
                              bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                              QString cvNum, QString mask, int minVal, int maxVal,
                              QMap<QString, CvValue*>* v, QLabel* status, QString stdname,
                              int pSecondCV, int pFactor, int pOffset, QString uppermask, QObject *parent = 0);
    /*public*/ int getSecondCvNum();
    /*public*/ QVector<CvValue*>* usesCVs();
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVariant rangeVal();
    void enterField() ;
    void exitField();
    void updatedTextField() ;
    /*public*/ QString getValueString();
    /*public*/ void setIntValue(int i) ;
    /*public*/ int getIntValue() ;
    /*public*/ QVariant getValueObject();
    /*public*/ QWidget* getCommonRep() ;
    /*public*/ void setValue(int value);
    void setColor(QColor c);
    /*public*/ QWidget* getNewRep(QString format);
    /*public*/ void setAvailable(bool a);
    /*public*/ void setCvState(int state);
    /*public*/ bool isChanged();
    /*public*/ void readChanges();
    /*public*/ void writeChanges();
    /*public*/ void readAll();
    /*public*/ void writeAll();

    // clean up connections when done
    /*public*/ void dispose();

signals:
    //void notifyPropertyChange(PropertyChangeEvent *e);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /** ActionListener implementations */
    /*public*/ void actionPerformed(ActionEvent* e = 0) ;
    /** FocusListener implementations */
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e = 0);
    /*public*/ void focusLost(/*FocusEvent*/QEvent* e = 0) ;
private:
    int mSecondCV;
    int mFactor;
    int mOffset;

    int lowerbitmask;
    int lowerbitoffset;
    int upperbitmask;
    // number of bits to shift _left_ the 8-16 bits in 2nd CV
    // e.g. multiply by 256, then shift by this
    int upperbitoffset;
    int _maxVal;
    int _minVal;

    QString oldContents;// = "";
    QColor _defaultColor;
    QList<QWidget*>* reps;// = new QList<QWidget*>();

    /*private*/ int _progState;// = 0;
    /*private*/ static /*final*/ const int IDLE = 0;
    /*private*/ static /*final*/ const int READING_FIRST = 1;
    /*private*/ static /*final*/ const int READING_SECOND = 2;
    /*private*/ static /*final*/ const int WRITING_FIRST = 3;
    /*private*/ static /*final*/ const int WRITING_SECOND = 4;
    // stored value
    JTextField* _value;// = null;
 Logger* logit;
 friend class VarTextField;

};

#endif // SPLITVARIABLEVALUE_H
