#ifndef VSDCONFIGDIALOG_H
#define VSDCONFIGDIALOG_H
#include "jdialog.h"
#include "liblayouteditor_global.h"

class PropertyChangeEvent;
class VSDManagerEvent;
class JActionEvent;
class NullProfileBoxItem;
class VSDConfig;
class RosterEntry;
class QTabWidget;
class QComboBox;
class RosterEntrySelectorPanel;
class DccLocoAddressSelector;
class QLabel;
class LIBLAYOUTEDITORSHARED_EXPORT VSDConfigDialog : public JDialog
{
 Q_OBJECT
public:
 //explicit VSDConfigDialog(QWidget *parent = 0);
 /*public*/ VSDConfigDialog(QWidget* parent, QString title, VSDConfig* c);
 /*public*/ static /*final*/ QString CONFIG_PROPERTY;// = "Config";
 /*public*/ void setRosterEntry(RosterEntry* entry);

private:
 // GUI Elements
 /*private*/ QLabel* addressLabel;
 /*private*/ QPushButton* addressSetButton;
 /*private*/ DccLocoAddressSelector* addressSelector;
 /*private*/ RosterEntrySelectorPanel* rosterSelector;
 /*private*/ QLabel* rosterLabel;
 /*private*/ QPushButton* rosterSaveButton;
 /*private*/ QComboBox* profileComboBox;
 /*private*/ QPushButton* profileLoadButton;
 /*private*/ QLabel* profileLabel;
 /*private*/ QWidget* rosterPanel;
 /*private*/ QWidget* profilePanel;
 /*private*/ QWidget* addressPanel;
 /*private*/ QTabWidget* locoSelectPanel;
 /*private*/ QPushButton* closeButton;

 /*private*/ NullProfileBoxItem* loadProfilePrompt; // dummy profileComboBox entry
 /*private*/ VSDConfig* config; // local reference to the config being constructed by this dialog
 /*private*/ RosterEntry* rosterEntry; // local reference to the selected RosterEntry
 /*private*/ static /*final*/ QMap<QString, int> Mnemonics;// = new QMap<QString, int>();
 /*private*/ void updateProfileList(QStringList s);
 Logger* log;
 /*private*/ void enableProfileStuff(bool t);
 QString nullProfileName; // = "Select a profile";
 QString nullRosterSelected;

private slots:
 /*private*/ void vsdecoderManagerEventAction(VSDManagerEvent* evt);
 /*private*/ void profileLoadButtonActionPerformed(JActionEvent* evt = 0);
 /*private*/ void addressSetButtonActionPerformed(JActionEvent* evt = 0);
 /*private*/ void rosterItemSelectAction(JActionEvent* e = 0);
 /*private*/ void profileComboBoxActionPerformed(JActionEvent* evt = 0);

signals:
 void propertyChange(PropertyChangeEvent*);
public slots:
 /*public*/ void cancelButtonActionPerformed(JActionEvent* ae = 0);
 /*public*/ void closeButtonActionPerformed(JActionEvent* ae = 0);
 /*private*/ void rosterSaveButtonAction(JActionEvent* e = 0);

protected:
 /*protected*/ void initComponents();
 /*protected*/ bool storeFile(RosterEntry* _rosterEntry);

};

#endif // VSDCONFIGDIALOG_H
