#ifndef CONSISTTOOLFRAME_H
#define CONSISTTOOLFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class ConsistFile;
class ConsistManager;
class JTable;
class ConsistDataModel;
class QCheckBox;
class RosterEntryComboBox;
class DccLocoAddressSelector;
class QLabel;
class QComboBox;
class QRadioButton;
class QPushButton;
class LIBLAYOUTEDITORSHARED_EXPORT ConsistToolFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit ConsistToolFrame(QWidget *parent = 0);
 /*public*/ QString getClassName();

signals:

public slots:
private:
 // GUI member declarations

 QLabel* textAdrLabel;// = new QLabel();
 DccLocoAddressSelector* adrSelector;// = new DccLocoAddressSelector();
 QComboBox* consistAdrBox;// = new QComboBox();
 QRadioButton* isAdvancedConsist;// = new QRadioButton(tr("AdvancedConsistButtonText"));
 QRadioButton* isCSConsist;// = new QRadioButton(rb.getString("CommandStationConsistButtonText"));
 QPushButton* deleteButton;// = new QPushButton();
 QPushButton* throttleButton;// = new QPushButton();
 QPushButton* reverseButton;// = new QPushButton();
 QLabel* textLocoLabel;// = new QLabel();
 DccLocoAddressSelector* locoSelector;// = new DccLocoAddressSelector();
 RosterEntryComboBox* locoRosterBox;
 QPushButton* addLocoButton;// = new QPushButton();
 QPushButton* resetLocoButton;// = new QPushButton();
 QCheckBox* locoDirectionNormal;// = new QCheckBox(rb.getString("DirectionNormalText"));
 ConsistDataModel* consistModel;// = new ConsistDataModel(1, 4);
 JTable* consistTable;// = new JTable(consistModel);
 ConsistManager* ConsistMan;// = null;
 QLabel* _status;// = new QLabel(tr("DefaultStatusText"));
 /*private*/ int _Consist_Type;// = Consist.ADVANCED_CONSIST;
 /*private*/ ConsistFile* consistFile;// = null;

};

#endif // CONSISTTOOLFRAME_H
