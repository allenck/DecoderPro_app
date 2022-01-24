#ifndef PROGOPSMODEPANE_H
#define PROGOPSMODEPANE_H

#include <QWidget>
#include "logger.h"
#include <QButtonGroup>
#include <QBoxLayout>
#include "progmodeselector.h"
#include <QSpinBox>
#include <QLabel>

class AccessoryOpsModeProgrammerFacade;
class JActionEvent;
class PropertyChangeEvent;
class ProgrammingMode;
class QBoxLayout;
class QComboBox;
class AddressedProgrammer;
class Programmer;
class QButtonGroup;
class QRadioButton;
class JTextField;
class QCheckBox;
class ProgOpsModePane : public ProgModeSelector
{
    Q_OBJECT
public:
 /*public*/ ProgOpsModePane(QBoxLayout::Direction direction, QButtonGroup* group, QWidget* parent = 0);
    /*public*/ void dispose();
    /*public*/ bool isSelected();
    /*public*/ Programmer* getProgrammer();

signals:

public slots:
    void programmerSelected();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ void actionPerformed(JActionEvent* /*e*/ = 0);

private:
    QButtonGroup* mModeGroup;
    QRadioButton* mOpsByteButton;//  	= new QRadioButton();
    //JTextField* mAddrField;//           = new JTextField(4);
    // use JSpinner for CV number input
    //SpinnerNumberModel model = new SpinnerNumberModel(0, 0, 10239, 1); // 10239 is highest DCC Long Address documented by NMRA as per 2017
    QSpinBox* mAddrField;// = new JSpinner(model);
    int lowAddrLimit = 0;
    int highAddrLimit = 10239;
    int oldAddrValue = 3; // Default start value
    QButtonGroup* addrGroup = new QButtonGroup(this);
    QRadioButton* shortAddrButton;// = new JRadioButton(Bundle.getMessage("ShortAddress"));
    QRadioButton* longAddrButton;// = new JRadioButton(Bundle.getMessage("LongAddress"));
    QCheckBox* offsetAddrCheckBox;// = new JCheckBox(Bundle.getMessage("DccAccessoryAddressOffSet"));
    QLabel* addressLabel;// = new JLabel(Bundle.getMessage("AddressLabel"));
    bool oldLongAddr = false;
    bool opsAccyMode;// = false;
    bool oldOpsAccyMode;// = false;
    bool opsSigMode;// = false;
    bool oldOpsSigMode;// = false;
    bool oldoffsetAddrCheckBox;// = false;QCheckBox* mLongAddrCheck;//        = new QCheckBox("Long address");
    /*transient*/ /*volatile*/ AddressedProgrammer* programmer;// = null;
    /*transient*/ /*volatile*/ AccessoryOpsModeProgrammerFacade* facadeProgrammer;// = null;

    void init();
    Logger* log;
    /*private*/ int getMode();
//    /*private*/ void setProgrammerMode(int mode);
    QString  oldAddrText;//
    QComboBox/*<AddressedProgrammerManager>*/*   progBox;
    QBoxLayout* layout;
    QList<QRadioButton*> buttonPool;// = new QList<QRadioButton*>();
    QMap<QString, QRadioButton*> buttonMap;// = new QMap<ProgrammingMode*,QRadioButton>();
    QButtonGroup* modeGroup;// 		    = new QButtonGroup();
    void setGuiFromProgrammer();
    void setProgrammerFromGui(Programmer* programmer);
    QBoxLayout* thisLayout;
    void setAddrParams();

};

#endif // PROGOPSMODEPANE_H
