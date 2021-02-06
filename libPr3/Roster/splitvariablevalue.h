#ifndef SPLITVARIABLEVALUE_H
#define SPLITVARIABLEVALUE_H
#include "variablevalue.h"
#include "cvvalue.h"
#include "actionevent.h"
#include <QMap>
#include "jtextfield.h"

class CvItem;
class JLabel;
class LIBPR3SHARED_EXPORT SplitVariableValue : public VariableValue
{
    Q_OBJECT
public:
 //explicit SplitVariableValue(QObject *parent = 0);
  /*public*/ SplitVariableValue(QString name, QString comment, QString cvName,
          bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
          QString cvNum, QString mask, int minVal, int maxVal,
          QMap<QString, CvValue*>* v, JLabel* status, QString stdname,
          QString pSecondCV, int pFactor, int pOffset, QString uppermask, QString extra1, QString extra2,
                                QString extra3, QString extra4, QObject *parent = nullptr);
  /*public*/ void stepOneActions(QString name, QString comment, QString cvName,
          bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
          QString cvNum, QString mask, int minVal, int maxVal,
          QMap<QString, CvValue *> *v, JLabel* status, QString stdname,
          QString pSecondCV, int pFactor, int pOffset, QString uppermask, QString extra1, QString extra2, QString extra3, QString extra4);
  /*public*/ void stepTwoActions();
    /*public*/ QVector<CvValue *> usesCVs();
    /*public*/ QString getCvNum();
    QT_DEPRECATED /*public*/ QString getSecondCvNum();
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVariant rangeVal() override;

    void enterField() ;
    void exitField();
    void updatedTextField() ;
    /*public*/ QString getValueString() override;
    /*public*/ void setIntValue(int i) override ;
    /*public*/ int getIntValue()  override;
    /*public*/ QVariant getValueObject() override;
    /*public*/ QWidget* getCommonRep() override ;
    /*public*/ void setLongValue(long value);
    /*public*/ void setValue(int value);
    void setColor(QColor c) override;
    /*public*/ QWidget* getNewRep(QString format);
    /*public*/ void setAvailable(bool a);
    /*public*/ void setCvState(int state) override;
    /*public*/ bool isChanged() override;
    /*public*/ void readChanges() override;
    /*public*/ void writeChanges() override;
    /*public*/ void readAll() override;
    /*public*/ void writeAll() override;

    // clean up connections when done
    /*public*/ void dispose();

signals:
    //void notifyPropertyChange(PropertyChangeEvent *e);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
    /** ActionListener implementations */
    /*public*/ void actionPerformed() ;
    /** FocusListener implementations */
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e = 0);
    /*public*/ void focusLost(/*FocusEvent*/QEvent* e = 0) ;
private:
    QString mSecondCV;
    QString _uppermask;
    int mFactor;
    int mOffset;
    QString _name;
    QString _mask; // full string as provided, use _maskArray to access one of multiple masks
    QStringList _maskArray = QStringList();
    QString _cvNum;

    QList<CvItem*> cvList;

    int cvCount = 0;
    int currentOffset = 0;

    QString oldContents;// = "";
    QColor _defaultColor;
    QList<QWidget*> reps = QList<QWidget*>();

    // the connection is to cvNum and cvNum+1
    long _minVal;
    long _maxVal;

    // stored reference to the JTextField
    JTextField* _textField = nullptr;
    int _columns = 1;
    bool _fieldShrink = false;

    /*private*/ int retry = 0;
    /*private*/ int _progState = 0;
    /*private*/ static /*final*/ const int IDLE = 0;
    /*private*/ static /*final*/ const int READING_FIRST = 1;
    /*private*/ static /*final*/ const int READING_SECOND = 2;
    /*private*/ static /*final*/ const int WRITING_FIRST = 3;
    /*private*/ static /*final*/ const int bitCount = 32;//Long.bitCount(~0);
    /*private*/ static /*final*/ const long intMask = (quint32)(~0);

    /*private*/ static /*final*/ const int RETRY_COUNT = 2;

    // stored value
    static Logger* logit;
    QString getTextFromValue(long v);
    long getValueFromText(QString s);
    QVector<int> getCvValsFromTextField();
    void updateVariableValue(QVector<int> intVals);
    int priorityValue(int state);

 friend class SPVarTextField;

};

/**
 * Class to hold CV parameters for CVs used.
 */
/*static*/ class CvItem {
 public:

    // class fields
    QString cvName;
    QString cvMask;
    int startOffset;
    CvValue* thisCV;
    CvItem(QString cvNameVal, QString cvMaskVal) {
        cvName = cvNameVal;
        cvMask = cvMaskVal;
    }
};

/*public*/ class SPVarTextField : public JTextField {
 Q_OBJECT
  SplitVariableValue* _var;
 public:

    SPVarTextField(Document* doc, QString text, int col, SplitVariableValue* var);
public slots:
    void thisActionPerformed(/*java.awt.event.ActionEvent e*/);
    void originalPropertyChanged(PropertyChangeEvent* e);
};
#endif // SPLITVARIABLEVALUE_H
