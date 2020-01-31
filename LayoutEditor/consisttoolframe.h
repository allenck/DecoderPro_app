#ifndef CONSISTTOOLFRAME_H
#define CONSISTTOOLFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"
#include "consistlistener.h"
#include "consistlistlistener.h"

class JLabel;
class DccLocoAddress;
class ConsistFile;
class AbstractConsistManager;
class JTable;
class ConsistDataModel;
class QCheckBox;
class RosterEntryComboBox;
class DccLocoAddressSelector;
class QLabel;
class QComboBox;
class QRadioButton;
class QPushButton;
class LIBLAYOUTEDITORSHARED_EXPORT ConsistToolFrame : public JmriJFrame, public ConsistListener, public ConsistListListener
{
 Q_OBJECT
 Q_INTERFACES(ConsistListener ConsistListListener)
public:
 explicit ConsistToolFrame(QWidget *parent = 0);
 /*public*/ QString getClassName();
 /*public*/ void canAdd();
 /*public*/ void consistReply(DccLocoAddress* locoaddress, int status);
 /*public*/ void dispose();
 /*public*/ QObject* self() {return (QObject*)this;}

signals:

public slots:
 void consistSelected();
 void on_isAdvancedConsist_checked(bool);
 void on_isCSConsist_checked(bool);
 void deleteButtonActionPerformed();
 void throttleButtonActionPerformed();
 void reverseButtonActionPerformed();
 void locoSelected();
 void addLocoButtonActionPerformed();
 void resetLocoButtonActionPerformed();
 /*public*/ void notifyConsistListChanged();
 /*public*/ void setDefaultStatus();
 /*public*/ void restoreButtonActionPerformed(/*ActionEvent e*/);

private:
 static Logger* log;
 // GUI member declarations

 JLabel* textAdrLabel;// = new QLabel();
 DccLocoAddressSelector* adrSelector;// = new DccLocoAddressSelector();
 QComboBox* consistAdrBox;// = new QComboBox();
 QRadioButton* isAdvancedConsist;// = new QRadioButton(tr("AdvancedConsistButtonText"));
 QRadioButton* isCSConsist;// = new QRadioButton(rb.getString("CommandStationConsistButtonText"));
 QPushButton* deleteButton;// = new QPushButton();
 QPushButton* throttleButton;// = new QPushButton();
 QPushButton* reverseButton;// = new QPushButton();
 QPushButton* restoreButton;// = new JButton();
 JLabel* textLocoLabel;// = new QLabel();
 DccLocoAddressSelector* locoSelector;// = new DccLocoAddressSelector();
 RosterEntryComboBox* locoRosterBox = nullptr;
 QPushButton* addLocoButton;// = new QPushButton();
 QPushButton* resetLocoButton;// = new QPushButton();
 QCheckBox* locoDirectionNormal;// = new QCheckBox(rb.getString("DirectionNormalText"));
 ConsistDataModel* consistModel;// = new ConsistDataModel(1, 4);
 JTable* consistTable;// = new JTable(consistModel);
 AbstractConsistManager* consistManager = nullptr;
 QLabel* _status;// = new QLabel(tr("DefaultStatusText"));
 /*private*/ int _Consist_Type;// = Consist.ADVANCED_CONSIST;
 /*private*/ ConsistFile* consistFile = nullptr;
 /*private*/ void initializeConsistBox();
 /*private*/ void recallConsist();
 // want to read the consist file after the consists have been loaded
 // from the command station.  The _readConsistFile flag tells the
 // notifyConsistListChanged routine to do this.  notifyConsistListChanged
 // sets the value to false after the file is read.
 /*private*/ bool _readConsistFile = true;
 /*private*/ void scanRoster();
 /*private*/ void reportNoConsistSeletected();

 friend class ConsistToolFrameTest;
};

#endif // CONSISTTOOLFRAME_H
