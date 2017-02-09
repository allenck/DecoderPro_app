#ifndef CVVALUE_H
#define CVVALUE_H
#include "abstractvalue.h"
#include <QLabel>
#include "logger.h"
#include <QLineEdit>

class Programmer;
class JTextField;
class LIBPR3SHARED_EXPORT CvValue : public AbstractValue
{
    Q_OBJECT
public:
    //explicit CvValue(QObject *parent = 0);
    /*public*/ CvValue(QString num, Programmer* pProgrammer, QObject *parent = 0);
    /*public*/ CvValue(QString num, QString cvName, QString piCv, int piVal, QString siCv, int siVal, QString iCv, Programmer* pProgrammer, QObject *parent = 0);
    /*public*/ QString toString();
    /*public*/ QString number();
    /*public*/ QString cvName();
    /*public*/ Q_DECL_DEPRECATED QString piCv();
    /*public*/ Q_DECL_DEPRECATED int piVal();
    /*public*/ Q_DECL_DEPRECATED QString siCv();
    /*public*/ Q_DECL_DEPRECATED int siVal();
    /*public*/ Q_DECL_DEPRECATED QString iCv();
    /*public*/ int getValue();
    QColor getColor();
    /*public*/ void setValue(int value);
    /*public*/ int getDecoderValue();
    /*public*/ int getState();
//    /*public*/ int getDecoder;
    /*public*/ void setState(int state);
    /*public*/ bool isBusy();
    void setColor(QColor c);
    JTextField* getTableEntry();
    /*public*/ void setReadOnly(bool is);
    /*public*/ bool getReadOnly();
    /*public*/ void setInfoOnly(bool is);
    /*public*/ bool getInfoOnly();
    /*public*/ void setWriteOnly(bool is);
    /*public*/ bool getWriteOnly();
    /*public*/ void setToRead(bool state);
    /*public*/ bool isToRead();
    /*public*/ void setToWrite(bool state) ;
    /*public*/ bool isToWrite();
    // read, write support

    /*public*/ void read(QLabel* status);
    /*public*/ Q_DECL_DEPRECATED void readIcV(QLabel* status);
    /*public*/ Q_DECL_DEPRECATED void confirmIcV(QLabel* status);
    /*public*/ void confirm(QLabel* status);
    /*public*/ void write(QLabel* status);
    /*public*/ Q_DECL_DEPRECATED void writePI(QLabel* status);
    /*public*/ Q_DECL_DEPRECATED void writeSI(QLabel* status);
    /*public*/ Q_DECL_DEPRECATED void writeIcV(QLabel* status);
    // clean up connections when done
    /*public*/ void dispose();
    QString getStateColor();
    void setProgrammer(Programmer* p);
    void resetStatus(int newState);


signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
    /*public*/ void programmingOpReply(int value, int retval);
    void errorTimeout() ;
private:
    /*private*/ QString _num;
    /*private*/ QString _cvName;// = "";
    /*private*/ Q_DECL_DEPRECATED QString _piCv;
    /*private*/ Q_DECL_DEPRECATED int _piVal;
    /*private*/ Q_DECL_DEPRECATED QString _siCv;
    /*private*/ Q_DECL_DEPRECATED int _siVal;
    /*private*/ Q_DECL_DEPRECATED QString _iCv;
    /*private*/ QLabel* _status;// = NULL;

    /*private*/ Programmer* mProgrammer;
    Logger* log;
    /*private*/ int _value;// = 0;
    /*private*/ int _decoderValue;// = 0;
    /*private*/ int _state;// = 0;
    /*private*/ void setBusy(bool busy);
    /*private*/ void notifyBusyChange(bool oldBusy, bool newBusy);
    /*private*/ bool _busy;// = false;
    QColor _defaultColor;
    JTextField* _tableEntry;// = NULL;
    /*private*/ bool _readOnly;// = false;
    /*private*/ bool _infoOnly;// = false;
    /*private*/ bool _writeOnly;// = false;
    /*private*/ bool _toRead;// = false;
    /*private*/ bool _toWrite;// = false;
    /*private*/ bool _reading;// = false;
    /*private*/ bool _confirm;// = false;

protected:
    /*protected*/ void notifyValueChange(int value);
friend class PaneProgPane;
};

#endif // CVVALUE_H
