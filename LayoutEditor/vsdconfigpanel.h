#ifndef VSDCONFIGPANEL_H
#define VSDCONFIGPANEL_H
#include "jmripanel.h"
#include "liblayouteditor_global.h"

class VSDecoder;
class ActionEvent;
class PropertyChangeEvent;
class VSDManagerEvent;
class RosterEntry;
class VSDecoderManager;
class VSDecoderPane;
class BusyDialog;
class NullProfileBoxItem;
class QComboBox;
class QLabel;
class QPushButton;
class DccLocoAddressSelector;
class RosterEntrySelectorPanel;
class LIBLAYOUTEDITORSHARED_EXPORT VSDConfigPanel : public JmriPanel
{
 Q_OBJECT
public:
 explicit VSDConfigPanel(QWidget *parent = 0);
 /*public*/ VSDConfigPanel(QString dec, VSDecoderPane* dad,QWidget *parent = 0);
 /*public*/ void setMainPane(VSDecoderPane* dad);
 /*public*/ VSDecoderPane* getMainPane();
 /*public*/ void init() ;
 /*public*/ void initContext(QObject* context);
 /*public*/ void handleDecoderListChange(VSDManagerEvent* e);
 /*public*/ void updateProfileList(QStringList s);
 /*public*/ void setProfileList(QStringList s);
 /*public*/ void initComponents();
 /*public*/ void setRosterEntry(RosterEntry* entry);

signals:

public slots:
 void /*public*/ eventAction(VSDManagerEvent* e);
 void /*public*/ propertyChange(PropertyChangeEvent*);


private:
 // Local References
 VSDecoderManager* decoder_mgr; // local reference to the VSDecoderManager instance
 VSDecoderPane* main_pane;      // local reference to the parent VSDecoderPane
 /*private*/ RosterEntry* rosterEntry; // local reference to the selected RosterEntry

 // GUI Elements
 /*private*/ QLabel* addressLabel;
 /*private*/ QPushButton* addressSetButton;
 /*private*/ DccLocoAddressSelector* addressSelector;
 /*private*/ RosterEntrySelectorPanel* rosterSelector;
 /*private*/ QLabel* rosterLabel;
 /*private*/ QPushButton* rosterSaveButton;
 /*private*/ QComboBox* profileComboBox;
 /*private*/ QLabel* profileLabel;

 // Panels for the tabbed pane.
 /*private*/ QWidget* rosterPanel;
 /*private*/ QWidget* profilePanel;
 /*private*/ QWidget* addressPanel;

 // Local variables
 /*private*/ bool profile_selected;  // true if a user has selected a Profile
 /*private*/ NullProfileBoxItem* loadProfilePrompt; // dummy profileComboBox entry

 /*private*/ BusyDialog* busy_dialog;
 Logger* log;
 /*protected*/ bool storeFile(RosterEntry* _rosterEntry);
 /*protected*/ VSDecoder* getNewDecoder();


private slots:
 /*private*/ void addressSetButtonActionPerformed(ActionEvent* evt = 0);
 /*private*/ void profileComboBoxActionPerformed(ActionEvent* evt = 0);
 /*private*/ void rosterSaveButtonAction(ActionEvent* e = 0);
 /*private*/ void rosterItemSelectAction(ActionEvent* e = 0);


protected:
 /*protected*/ void updateAddress();

};
// class NullComboBoxItem
//
// little object to insert into profileComboBox when it's empty
/*static*/ class NullProfileBoxItem
{
 //Q_OBJECT
    //@Override
 NullProfileBoxItem() {}
    /*public*/ QString toString();
 friend class VSDConfigPanel;
};

#endif // VSDCONFIGPANEL_H
