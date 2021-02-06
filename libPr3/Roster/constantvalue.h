#ifndef CONSTANTVALUE_H
#define CONSTANTVALUE_H
#include "variablevalue.h"
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>

class LIBPR3SHARED_EXPORT ConstantValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit ConstantValue(QObject *parent = 0);
    /*public*/ ConstantValue(QString name, QString comment, QString cvName,
                         bool readOnly, bool infoOnly, bool writeOnly,  bool opsOnly,
                         QString cvNum, QString mask, int minVal, int maxVal,
                         QMap<QString,CvValue*>* v, JLabel *status, QString stdname, QObject *parent = 0);
    /*public*/ ConstantValue(QObject *parent = 0);
    /*public*/ QVector<CvValue*> usesCVs() ;
    /*public*/ void setToolTipText(QString t) ;
    /*public*/ QVariant rangeVal();
    /*public*/ QString getValueString();
    /*public*/ void setIntValue(int i);
    /*public*/ int getIntValue() ;
    /*public*/ QVariant getValueObject();
    /*public*/ QWidget* getCommonRep();
    /*public*/ void setValue(int value);
    /*public*/ QWidget* getNewRep(QString format);
    void setColor(QColor c);
    /*public*/ void setCvState(int state);
    /*public*/ bool isChanged();
    /*public*/ void setToRead(bool state) ;
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state);
    /*public*/ bool isToWrite() ;
    /*public*/ void readChanges();
    /*public*/ void writeChanges();
    /*public*/ void readAll();
    /*public*/ void writeAll() ;
    /*public*/ void dispose();

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) ;
private:
    // place to keep the items
    QStringList* _itemArray;// = NULL;
    int _nstored;

    /*private*/ int _maxVal;
    /*private*/ int _minVal;
    QColor _defaultColor;

    // stored value
    QComboBox* _value;// = null;
    QList<QCheckBox*>* comboCBs;// = new QList<QCheckBox*>();
    QList<QRadioButton*>* comboRBs;// = new QList<QRadioButton*>();
 Logger* logit;
};

#endif // CONSTANTVALUE_H
