#ifndef PROGDEBUGGER_H
#define PROGDEBUGGER_H
#include "addressedprogrammer.h"
#include "runnable.h"
#include "logger.h"
#include "libPr3_global.h"

class PropertyChangeSupport;
class LIBPR3SHARED_EXPORT ProgDebugger : public QObject, public AddressedProgrammer
{
    Q_OBJECT
 Q_INTERFACES(AddressedProgrammer)
public:
    explicit ProgDebugger(QObject *parent = 0);
    /*public*/ ProgDebugger(bool pLongAddress, int pAddress, QObject *parent = 0);
    /*public*/ int lastWrite();
    /*public*/ int lastWriteCv();
    /*public*/ int nOperations;// = 0;

    /**
     * Reset the CV to a value so one
     * can detect if it's been written.
     * <p>
     * Does not change the "lastWrite" and "lastWriteCv" results.
     */
    /*public*/ void resetCv(int cv, int val);
    /*public*/ int getCvVal(int cv);
    /*public*/ bool hasBeenWritten(int cv);
    /*public*/ void clearHasBeenWritten(int cv);
    /*public*/ QString decodeErrorCode(int i);
    /*public*/ void writeCV(QString CVName, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void nextRead(int r);
    /*public*/ int lastReadCv();
    /*public*/ void confirmCV(QString CVName, int val, ProgListener* p) throw (ProgrammerException) ;
    /*public*/ void readCV(QString CVName, ProgListener* p) throw (ProgrammerException) ;
    /*public*/ /*final*/ void setMode(ProgrammingMode* m) ;
    /*public*/ /*final*/ ProgrammingMode* getMode();
    /*public*/ QList<QString> getSupportedModes();
    /*public*/ void setTestReadLimit(int lim);
    /*public*/ void setTestWriteLimit(int lim);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ bool getLongAddress() ;
    /*public*/ int getAddressNumber();
    /*public*/ QString getAddress();

signals:

public slots:
private:
    // write CV is recorded for later use
    /*private*/ int _lastWriteVal;// = -1;
    /*private*/ int _lastWriteCv;// = -1;
    void common();
    /*private*/ int _nextRead;// = 123;
    bool longAddr;// = true;
    int address;// = -1;
    // write CV values are remembered for later reads
    QHash<int,int> mValues;// = QHash<int,int>();
    Logger* log;
    class PDRunnable1 : public Runnable
    {
     ProgListener* l;// = m;
     public:
         PDRunnable1(ProgListener* l);
        /*public*/ void run();
    };
    class PDRunnable2 : public Runnable
    {
     ProgListener* l;// = m;
     int result;// = returnResult;
     ProgDebugger* parent;
     public:
         PDRunnable2(int result, ProgListener* l,ProgDebugger* parent);
        /*public*/ void run();
    };
    class PDRunnable3 : public Runnable
    {
     ProgListener* l;// = m;
     int retval;// = returnResult;
     public:
         PDRunnable3(int result, ProgListener* l);
        /*public*/ void run();
    };

    /*private*/ int _lastReadCv;// = -1;
    /**
     * By default, the highest test CV is 256 so that
     * we can test composite operations
     */
    int writeLimit;// = 256;
    int readLimit;// = 256;
    bool confirmOK;  // cached result of last compare
    /**
     * Provide a {@link java.beans.PropertyChangeSupport} helper.
     */
    /*private*/ /*final*/ PropertyChangeSupport* propertyChangeSupport;// = new PropertyChangeSupport(this);
    static const bool IMMEDIATERETURN;// = false;
    static const int DELAY;// = 10;
    void sendReturn(Runnable* run);
    Runnable* run;
    /*public*/ QObject* self() {return (QObject*)this;}

protected:
    // handle mode
    /*protected*/ ProgrammingMode* mode;
    /*protected*/ void notifyPropertyChange(QString key, QVariant oldValue, QVariant value);
protected slots:
    void On_timer();
};

#endif // PROGDEBUGGER_H
