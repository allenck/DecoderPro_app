#ifndef DEFAULTSIGNALHEAD_H
#define DEFAULTSIGNALHEAD_H
#include "abstractsignalhead.h"
#include <QTimer>

class Turnout;
class LIBPR3SHARED_EXPORT DefaultSignalHead : public AbstractSignalHead
{
    Q_OBJECT
public:
    //explicit DefaultSignalHead(QObject *parent = 0);
    /*public*/ DefaultSignalHead(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ DefaultSignalHead(QString systemName, QObject *parent = 0);
    /*public*/ void setAppearance(int newAppearance) ;
    /*public*/ void setLit(bool newLit);
    /*public*/ void setHeld(bool newHeld);
    /*public*/ Q_DECL_DEPRECATED QVector<int> getValidStates();
    /*public*/ Q_DECL_DEPRECATED QVector<QString> getValidStateNames();
    /*public*/ bool isFlashOn();

signals:

private slots:
    void timeout();

private:
    /**
     * On or off time of flashing signal
     */
    int delay;// = 750;
    /*final*/ static /*private*/ QVector<int> validStates;
    /*final*/ static /*private*/ QVector<QString> validStateNames;
protected:
    virtual /*abstract*/ /*protected*/ void updateOutput() {}
    /**
     * Should a flashing signal be on (lit) now?
     */
    /*protected*/ bool mFlashOn;// = true;
    QTimer* timer;// = NULL;
    /*protected*/ void startFlash();
    /*protected*/ void stopFlash();
    bool isTurnoutUsed(Turnout* t);
    /*protected*/ void appearanceSetsFlashTimer(int newAppearance);

 Logger* log;
};

#endif // DEFAULTSIGNALHEAD_H
