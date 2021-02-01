#ifndef ABSTRACTPROGRAMMER_H
#define ABSTRACTPROGRAMMER_H

#include "programmer.h"
#include <QTimer>
#include "logger.h"
#include "propertychangelistener.h"
#include <QVector>
#include "libPr3_global.h"

/**
 * Common implementations for the Programmer interface.
 *
 * @author	Bob Jacobsen  Copyright (C) 2001, 2012
 * @version     $Revision: 22216 $
 */

class PropertyChangeSupport;
class LIBPR3SHARED_EXPORT AbstractProgrammer : public QObject, public Programmer
{
 Q_OBJECT
 Q_INTERFACES(Programmer)
public:
    explicit AbstractProgrammer(QObject *parent = 0);
    virtual QString decodeErrorCode(int code);
    int registerFromCV(int cv); // throws ProgrammerException
    /*public synchronized */virtual void addPropertyChangeListener(PropertyChangeListener* l);
    /*public synchronized*/ virtual void removePropertyChangeListener(PropertyChangeListener* l);
//    /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ virtual void readCV(QString /*CV*/, ProgListener* /*p*/) throw (ProgrammerException) {}
//    /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ /*final*/ void setMode(ProgrammingMode* m);
    /*public*/ /*final*/ ProgrammingMode* getMode();
    /*abstract*/ /*public*/ virtual QList<QString> getSupportedModes();
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);

signals:
    //void ProgrammerException();
    void programmerException(QString);
    void propertyChange(PropertyChangeEvent*);
private:
    /**
     * Provide a {@link java.beans.PropertyChangeSupport} helper.
     */
    /*private*/ /*final*/ PropertyChangeSupport* propertyChangeSupport;// = new PropertyChangeSupport(this);

protected:

    static int SHORT_TIMEOUT;//=2000;
    static int LONG_TIMEOUT;//=60000;

    QTimer* timer;
    // data members to hold contact with the property listeners


public slots:
    /**
     * Internal routine to handle a timeout, should be synchronized!
     */
    virtual void timeout();
 private:
   Logger* log;
   QObject *parent;
protected:
   // data members to hold contact with the property listeners
   /*protected*/ QVector<PropertyChangeListener*>* propListeners;// = new Vector<PropertyChangeListener>();
   /*protected*/ void notifyPropertyChange(QString key, QVariant oldValue, QVariant value);
   // handle mode
   /*protected*/ ProgrammingMode* mode;// = DefaultProgrammerManager.PAGEMODE;
   /*protected*/ virtual void startShortTimer();
   /*protected*/ virtual void startLongTimer() ;
   /*protected*/ virtual /*synchronized*/ void stopTimer();
   /*protected*/ /*synchronized*/ void restartTimer(int delay);
friend class ProgServiceModeComboBox;
};

#endif // ABSTRACTPROGRAMMER_H
