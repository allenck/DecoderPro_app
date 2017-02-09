#ifndef VARIABLEVALUE_H
#define VARIABLEVALUE_H
#include "abstractvalue.h"
#include <QLabel>
#include "logger.h"
#include "cvvalue.h"

class LIBPR3SHARED_EXPORT VariableValue : public AbstractValue
{
    Q_OBJECT
public:
    //explicit VariableValue(QObject *parent = 0);
    /*public*/ QString getTextValue();
    virtual void updatedTextField();
    static /*public*/ bool considerChanged(CvValue* c);

    /*public*/ VariableValue(QString label, QString comment, QString cvName, bool readOnly,
                             bool infoOnly, bool writeOnly, bool opsOnly, QString cvNum, QString mask,
                             QMap<QString, CvValue*>* v, QLabel* status, QString item,QObject *parent = 0);
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
    /*public*/ void setToRead(bool state);
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state);
    /*public*/ bool isToWrite();
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
    /*abstract*/ /*public*/ virtual void propertyChange(PropertyChangeEvent* e) {Q_UNUSED(e);}
    /*abstract*/ /*public*/ virtual void dispose() {}
    /*abstract*/ /*public*/ virtual QVariant rangeVal() {return QVariant();}
    /*abstract*/ /*public*/ virtual QVector<CvValue*>* usesCVs() { return NULL;}
    /*abstract*/ /*public*/ virtual void setCvState(int state) {Q_UNUSED(state)}
    void setSV(int cv);

signals:
 //void notifyPropertyChange(PropertyChangeEvent *e);

public slots:
private:
    /*private*/ QString _label;
    /*private*/ QString _item;
    /*private*/ QString _cvName;
 Logger* logit;
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
protected:
 /*protected*/ QMap<QString, CvValue*>* _cvMap;   // Vector of CV objects used to look up CVs
 /*protected*/ QLabel* _status;// = null;
 /*protected*/ QString _tooltipText;
 /*protected*/ VariableValue(QObject* parent = 0);
 /*protected*/ QWidget* updateRepresentation(QWidget* c);
 /*protected*/ void setBusy(bool newBusy);
 /*protected*/ int maskVal(QString maskString);
 /*protected*/ int offsetVal(QString maskString);
 /*protected*/ int newValue(int oldCv, int newVal, QString maskString);
 friend class IndexedPairVariableValue;
 friend class VariableTableModel;
};

#endif // VARIABLEVALUE_H
