#ifndef VARIABLEVALUE_H
#define VARIABLEVALUE_H
#include "abstractvalue.h"
#include "jlabel.h"
#include "logger.h"
#include "cvvalue.h"

class LIBPR3SHARED_EXPORT VariableValue : public AbstractValue
{
    Q_OBJECT
public:
    //explicit VariableValue(QObject *parent = 0);
    /*public*/ QString getTextValue();
    static /*public*/ bool considerChanged(CvValue* c);

    /*public*/ VariableValue(QString label, QString comment, QString cvName, bool readOnly,
                             bool infoOnly, bool writeOnly, bool opsOnly, QString cvNum, QString mask,
                             QMap<QString, CvValue*>* v, JLabel *status, QString item, QObject *parent = 0);
    /*public*/ void confirmAll();
    /*public*/ QString label();
    /*public*/ QString item();
    /*public*/ QString cvName();
    /*public*/ void setToolTipText(QString t);
    /*public*/ QString getComment();
    /*public*/ bool getReadOnly();
    /*public*/ bool getInfoOnly();
    /*public*/ bool getWriteOnly();
    /*public*/ bool getOpsOnly();
    /*public*/ QString getCvNum();
    /*public*/ QString getCvName();
    /*public*/ QString getMask();
    /*public*/ int getState();
    /*public*/ void setState(int state);
    /*public*/ void setToRead(bool state) override;
    /*public*/ bool isToRead() override;
    /*public*/ void setToWrite(bool state) override;
    /*public*/ bool isToWrite() override;
    /*public*/ bool isBusy();

    /*abstract*/ /*public*/ virtual QWidget* getCommonRep() {return NULL;}	// and thus should be called a limited number of times
    /*abstract*/ /*public*/ virtual QWidget* getNewRep(QString format) { Q_UNUSED(format); return NULL;} // this one is returning a new object
    /*abstract*/ /*public*/ virtual QString getValueString() { return "";}
    /*abstract*/ /*public*/ virtual QVariant getValueObject() {return QVariant();}
    /*abstract*/ /*public*/ virtual void setIntValue(int i) {Q_UNUSED(i)}
    /*abstract*/ /*public*/ virtual int getIntValue() {return 0;}
    /*abstract*/ /*public*/ virtual void readAll() {}
    /*abstract*/ /*public*/ virtual void writeAll() {}
    /*abstract*/ /*public*/ virtual void readChanges() {}
    /*abstract*/ /*public*/ virtual void writeChanges() {}
    /*abstract*/ /*public*/ virtual bool isChanged() { return false;}
    /*abstract*/ /*public*/ virtual void dispose() {}
    /*abstract*/ /*public*/ virtual QVariant rangeVal() {return QVariant();}
    /*abstract*/ /*public*/ virtual QVector<CvValue*> usesCVs() = 0;
    /*abstract*/ /*public*/ virtual void setCvState(int state) {Q_UNUSED(state)}
    void setSV(int cv);
    /*public*/ QString getCvDescription();
    /*public*/ void setValue(QString value);

 public slots:
    /*abstract*/ /*public*/ virtual void propertyChange(PropertyChangeEvent *e) =0;

signals:
 //void notifyPropertyChange(PropertyChangeEvent *e);

public slots:
private:
    /*private*/ QString _label;
    /*private*/ QString _item;
    /*private*/ QString _cvName;
 static Logger* logit;
 /*private*/ QString _comment;
 /*private*/ bool _readOnly;
 /*private*/ bool _infoOnly;
 /*private*/ bool _writeOnly;
 /*private*/ bool _opsOnly;
 /*private*/ QString _cvNum;
 /*private*/ QString _mask;
 /*private*/ int _state;// = UNKNOWN;
 /*private*/ bool _busy;// = false;
 QObject *parent;
 void updatedTextField();

protected:
 /*protected*/ QMap<QString, CvValue*>* _cvMap;   // Vector of CV objects used to look up CVs
 /*protected*/ JLabel* _status = nullptr;
 /*protected*/ QString _tooltipText;
 /*protected*/ VariableValue(QObject* parent = 0);
 /*protected*/ QWidget* updateRepresentation(QWidget* c);
 /*protected*/ void setBusy(bool newBusy);
 /*protected*/ void simplifyMask();
 /*protected*/ int maskValAsInt(QString maskString);
 /*protected*/ bool isBitMask(QString mask);
 /*protected*/ int offsetVal(QString maskString);
 /*protected*/ int getValueInCV(int Cv, QString maskString, int maxVal);
 /*protected*/ int setValueInCV(int oldCv, int newVal, QString maskString, int maxVal);

 friend class IndexedPairVariableValue;
 friend class VariableTableModel;
 friend class MyDccAddressVarHandler2;
};

#endif // VARIABLEVALUE_H
