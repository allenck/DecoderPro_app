#ifndef SIGNALMASTADDPANE_H
#define SIGNALMASTADDPANE_H
#include "jpanel.h"
#include "signalappearancemap.h"
#include "signalmast.h"
#include "jmriserviceproviderinterface.h"

class SignalMastAddPane : public JPanel
{
 Q_OBJECT
public:
 explicit SignalMastAddPane(QWidget *parent = nullptr);
 /*abstract*/ virtual /*public*/ void setAspectNames(/*@Nonnull*/ SignalAppearanceMap*, /*@Nonnull*/ SignalSystem*);
 /*abstract*/ virtual /*public*/ bool canHandleMast(/*@Nonnull*/ SignalMast* mast);
 /*abstract*/ virtual /*public*/ void setMast(SignalMast* mast);
 /*abstract*/ virtual /*public*/ bool createMast(/*@Nonnull*/
         QString sigsysname, /*@Nonnull*/
                 QString mastname, /*@Nonnull*/
                         QString username);
 /*@Nonnull*/ /*abstract*/virtual  /*public*/ QString getPaneName();




signals:

public slots:

protected:
 /*final*/ /*protected*/ static int NOTIONAL_ASPECT_COUNT;// = 12;  // size of maps, not critical

};

/*static*/ /*public*/ /*abstract*/ class SignalMastAddPaneProvider : public QObject, public  JmriServiceProviderInterface
{
  Q_OBJECT
  Q_INTERFACES(JmriServiceProviderInterface)
    public:
    /*public*/ bool isAvailable();
    /*@Nonnull*/ /*abstract*/ virtual /*public*/ QString getPaneName();
    /*@Nonnull*/ /*abstract*/ virtual /*public*/ SignalMastAddPane* getNewPane();
    /*final*/ static /*public*/ QMap<QString, SignalMastAddPaneProvider*>* getInstancesMap();
    /*final*/ static /*public*/ QList<SignalMastAddPaneProvider*> getInstancesCollection();
    /*final*/ static /*public*/ void loadInstances();
private:
    static /*volatile*/ QMap<QString, SignalMastAddPaneProvider*>* instanceMap;// = nullptr;
};

Q_DECLARE_INTERFACE(SignalMastAddPaneProvider, "SignalMastAddPaneProvider")
#endif // SIGNALMASTADDPANE_H
