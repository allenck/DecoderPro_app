#ifndef INDEXEDPAIRVARIABLEVALUE_H
#define INDEXEDPAIRVARIABLEVALUE_H
#include "variablevalue.h"
#include "actionevent.h"

class CvValue;
class JTextField;
class LIBPR3SHARED_EXPORT IndexedPairVariableValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit IndexedPairVariableValue(QObject *parent = 0);
    /*public*/ Q_DECL_DEPRECATED IndexedPairVariableValue(QString name, QString comment, QString cvName,
                                         bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                                         QString cvNum, QString mask, int minVal, int maxVal,
                                         QMap<QString, CvValue*>* v, QLabel* status, QString stdname,
                                         QString pSecondCV, int pFactor, int pOffset, QString uppermask,
                                         bool upperFirst, QObject *parent = 0);
    /*public*/ QVector<CvValue*>* usesCVs();
    /*public*/ QString getSecondCvNum();
    /*public*/ void setToolTipText(QString t);
    /*public*/ QVariant rangeVal();
    void enterField();
    void exitField();
    void updatedTextField();
    /*public*/ QString getValueQString() ;
    /*public*/ void setIntValue(int i);
    /*public*/ int getIntValue();
    /*public*/ QVariant getValueObject();
    /*public*/ QWidget* getCommonRep();
    /*public*/ void setValue(int value);
    void setColor(QColor c);
    /*public*/ QWidget* getNewRep(QString format) ;
    /*public*/ void setAvailable(bool a);
    /*public*/ void setCvState(int state);
    /*public*/ void setToRead(bool state);
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state);
    /*public*/ bool isToWrite() ;
    /*public*/ bool isChanged();
    /*public*/ void readChanges() ;
    /*public*/ void writeChanges();
    /*public*/ void readAll() ;
    /*public*/ void writeAll() ;
    /*public*/ void confirmAll();
    // handle incoming parameter notification
    /*public*/ void dispose();
    /*public*/ void doRead();
    /*public*/ void doWrite();

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /** ActionListener implementations */
    /*public*/ void actionPerformed(ActionEvent* /*e*/);
    /*public*/ void focusGained(/*FocusEvent*/QEvent* e);
    /*public*/ void focusLost(/*FocusEvent*/ QEvent* e);
 private:
    QString mSecondCVname;  // string because 1.2.3 form
    int mFactor;
    int mOffset;
    int lowerbitmask;
    int lowerbitoffset;
    int upperbitmask;
    // number of bits to shift _left_ the 8-16 bits in 2nd CV
    // e.g. multiply by 256, then shift by this
    int upperbitoffset;
    int _row;
    int _secondCVrow;
    int _maxVal;
    int _minVal;
    QString _uppermask;
    bool _upperFirst;
    QString oldContents;// = "";
    QList<QWidget*>* reps;// = new QList<QWidget*>();

    /*private*/ int _progState;// = 0;
    /*private*/ bool programmingLow;// = true;
    // these mark which operations are needed
    /*private*/ bool doLow;// = false;
    /*private*/ bool doHigh;// = false;
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

     /* Count number of retries done
     */
    /*private*/ int retries;// = 0;

    /**
     * Define maximum number of retries of read/write operations before moving on
     */
    /*private*/ static /*final*/ const int RETRY_MAX = 2;
    QColor _defaultColor;
    // stored value
    JTextField* _value;// = NULL;
 private:
  Logger* log;
  friend class VarTextField;
};

#endif // INDEXEDPAIRVARIABLEVALUE_H
