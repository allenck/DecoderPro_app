#ifndef CABSIGNALPANE_H
#define CABSIGNALPANE_H
#include "jmripanel.h"
#include "jtable.h"
#include "cabsignaltablemodel.h"

class CabSignalTableModel;
class JLabel;
class QAction;
class JToggleButton;
class DccLocoAddressSelector;
class RosterEntryComboBox;
class QPushButton;
class XTableColumnModel;
class CabSignalManager;
class CabSignalPane : public JmriPanel
{
 Q_OBJECT
public:
 CabSignalPane(QWidget* parent = nullptr);
 /*public*/ void initComponents();
 /*public*/ void init();
 /*public*/ QList<QMenu*> getMenus();
 /*public*/ QString getHelpTarget();
 /*public*/ void dispose();
 /*public*/ void notifyCabSignalListChanged();
 /*public*/ QString getTitle();

public slots:
 /*public*/ void addLocoButtonActionPerformed(/*ActionEvent e*/);
 void onOffset(int i);
 /*public*/ void locoSelected();
 void onResetLocoButton();

private:
 static Logger* log;
 /*private*/ CabSignalManager* cabSignalManager;
 /*private*/ QMenu* cabSigColMenu;// = new QMenu(tr("Signal Data Columns"));
 /*private*/ JToggleButton* masterPauseButton;
 JLabel* textLocoLabel;// = new JLabel();
 DccLocoAddressSelector* locoSelector;// = new DccLocoAddressSelector();
 RosterEntryComboBox* locoRosterBox;
 QPushButton* addLocoButton;// = new QPushButton();
 QPushButton* resetLocoButton;// = new QPushButton();
 /*private*/ int _rotationOffset;

private slots:
 /*private*/ void refreshMasterPauseButton();
 void on_cabSigColMenuMapper(QObject*);

protected:
 ///*protected*/ JScrollPane slotScroll;

 /*protected*/ CabSignalTableModel* slotModel=nullptr;
 /*protected*/ JTable* slotTable=nullptr;
 /*protected*/ /*final*/ XTableColumnModel* tcm;// = new XTableColumnModel();
 /*protected*/ QList<QAction*> colMenuList;// = new ArrayList<JCheckBoxMenuItem>();
 /*protected*/ QList<QAction*> cabSigColMenuList;// = new ArrayList<JCheckBoxMenuItem>();


};
#endif // CABSIGNALPANE_H
