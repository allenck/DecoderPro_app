#ifndef ADDRESSPANEL_H
#define ADDRESSPANEL_H

#include <QDockWidget>
#include "logger.h"
#include <QtXml>
#include <QComboBox>
#include "throttlelistener.h"

namespace Ui {
class AddressPanel;
}

class BackgroundPanel;
class LocoAddress;
class PropertyChangeEvent;
class RosterEntrySelectorPanel;
class RosterEntry;
class AddressListener;
class DccLocoAddress;
class DccLocoAddressSelector;
class DccThrottle;
class AddressPanel : public QDockWidget, public ThrottleListener
{
    Q_OBJECT
    Q_INTERFACES(ThrottleListener)
public:
    explicit AddressPanel(QWidget *parent = 0);
    ~AddressPanel();
    /*public*/ void destroy(); // Handle disposing of the throttle
    /*public*/ void addAddressListener(AddressListener* l) ;
    /*public*/ void removeAddressListener(AddressListener* l);
    /*public*/ int getRosterSelectedIndex();
    /*public*/ RosterEntry* getRosterEntry();
    /*public*/ void setRosterEntry(RosterEntry* entry);

    /*static*/ class NULLComboBoxConsist {
        //@Override
        /*public*/ static QString toString() {
            return tr("<No Consist Selected>");
        }
        friend class AddressPanel;
    };
    /*public*/ DccThrottle* getThrottle();
    /*public*/ DccLocoAddress* getCurrentAddress() ;
    /*public*/ void setCurrentAddress(DccLocoAddress* currentAddress);
    /*public*/ void setAddress(int consistNumber, bool b);
    /*public*/ DccLocoAddress* getConsistAddress();
    /*public*/ void setConsistAddress(DccLocoAddress* consistAddress);
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);
 /*public*/ void setRosterSelectedIndex(int index);
 /*public*/ void setBackgroundPanel(BackgroundPanel* bp);
 /*public*/ void selectRosterEntry();


public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);
    void OnSetButton_clicked();
//    void OnRosterBox_currentIndexChanged();
    /*public*/ void dispatchAddress();
    /*public*/ void releaseAddress();
    /*public*/ RosterEntrySelectorPanel* getRosterEntrySelector();
    /*public*/ void notifyThrottleFound(DccThrottle* t);
    /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
    /*public*/ void notifyConsistThrottleFound(DccThrottle* t);
    /*public*/ void notifyThrottleDisposed();
    /*public*/QObject* self() {return (QObject*)this;}

signals:
    void notifyAddressReleased(LocoAddress* currentAddress);
    void notifyAddressThrottleFound(DccThrottle* throttle);
    void notifyAddressChosen(LocoAddress* currentAddress);
    void notifyConsistAddressChosen(int, bool);
    void notifyConsistAddressThrottleFound(DccThrottle* throttle);
private:
    Ui::AddressPanel *ui;
    /*private*/ DccThrottle* throttle;
    /*private*/ DccThrottle* consistThrottle;

    /*private*/ DccLocoAddressSelector* addrSelector;// = new DccLocoAddressSelector();
    /*private*/ DccLocoAddress* currentAddress;
    /*private*/ DccLocoAddress* consistAddress;
    /*private*/ QList<AddressListener*>* listeners;

    /*private*/ QWidget* mainPanel = nullptr;

//	/*private*/ JButton releaseButton;
//	/*private*/ JButton dispatchButton;
//	/*private*/ JButton progButton;
//	/*private*/ JButton setButton;
    /*private*/ RosterEntrySelectorPanel* rosterBox;
    /*private*/ QComboBox* conRosterBox;

    /*private*/ RosterEntry* rosterEntry = nullptr;
    /*private*/ void notifyListenersOfThrottleRelease();
    Logger* log;
    /*private*/ void changeOfAddress();
    /*private*/ void changeOfConsistAddress();
    /*private*/ BackgroundPanel* backgroundPanel;
private slots:
    /*private*/ void consistRosterSelected();
    /*private*/ void rosterItemSelected();

protected slots:
    /*protected*/ void openProgrammer();

};

#endif // ADDRESSPANEL_H
