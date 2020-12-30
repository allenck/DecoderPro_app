#include "signalgroupsubtableaction.h"
#include "signalgroup.h"
#include <QComboBox>
#include "stringutil.h"
#include "instancemanager.h"
#include "abstractsignalheadmanager.h"
#include "signalgrouptableaction.h"
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "flowlayout.h"
#include "QTableView"
#include "singleturnoutsignalhead.h"
#include "defaultsignalgroup.h"
#include "../LayoutEditor/jmrijframe.h"

//SignalGroupSubTableAction::SignalGroupSubTableAction(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Swing action to create and register a SignalGroup Table

 * Based in part on RouteTableAction.java by Bob Jacobsen
 *
 * @author	Kevin Dickerson    Copyright (C) 2010
 *
 * @version     $Revision: 19870 $
 */

///*public*/ class SignalGroupSubTableAction {

//	static final ResourceBundle rbx = ResourceBundle
//			.getBundle("jmri.jmrit.beantable.LogixTableBundle");
/*private*/ /*static*/ int SignalGroupSubTableAction::ROW_HEIGHT = 0;
/*private*/ /*static*/ QStringList SignalGroupSubTableAction::COLUMN_NAMES = QStringList() << tr("System Name") <<
                                        tr("User Name") <<
                                        tr("Include") <<
                                        tr("Set State");
/*private*/ /*static*/ QString SignalGroupSubTableAction::SET_TO_ACTIVE = tr("Active");
/*private*/ /*static*/ QString SignalGroupSubTableAction::SET_TO_INACTIVE = tr("Inactive");
/*private*/ /*static*/ QString SignalGroupSubTableAction::SET_TO_CLOSED = tr("Closed");// ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
/*private*/ /*static*/ QString SignalGroupSubTableAction::SET_TO_THROWN = tr("Thrown");// ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();

/*private*/ /*static*/ QVector<QString> SignalGroupSubTableAction::sensorInputModes = QVector<QString>() << "Active" << "Inactive";
/*private*/ /*static*/ QVector<int> SignalGroupSubTableAction::sensorInputModeValues = QVector<int>() << SignalGroup::ONACTIVE << SignalGroup::ONINACTIVE;

/*private*/ /*static*/ QVector<QString> SignalGroupSubTableAction::signalStates = QVector<QString>()<< tr("Dark")<< tr("Red")<< tr("Yellow")<< tr("Green")<< tr("Lunar");
/*private*/ /*static*/ QVector<int> SignalGroupSubTableAction::signalStatesValues = QVector<int>()<<SignalHead::DARK<< SignalHead::RED<< SignalHead::YELLOW<< SignalHead::GREEN<< SignalHead::LUNAR;
/*static*/ QString SignalGroupSubTableAction::updateInst = tr("To change this SignalGroup, make changes above, then click 'Done'.");

    /**
     * Create an action with a specific title.
     * <P>
     * Note that the argument is the Action title, not the title of the
     * resulting frame.  Perhaps this should be changed?
     * @param s
     */
     //BeanTableFrame f;
/*public*/ SignalGroupSubTableAction::SignalGroupSubTableAction(QString /*s*/, QObject* parent) : QObject(parent)
{
    log = new Logger("SignalGroupSubTableAction");
    showAll = true;   // false indicates show only included Turnouts
    _SensorTurnoutOper = new QComboBox(/*oper*/);
    _SensorTurnoutOper->addItems(oper.toList());
    addFrame = NULL;
    selGroup = NULL;
    includedButton = NULL;

    nameLabel = new QLabel("Signal Head:");
    signalOnStateLabel = new QLabel("State when conditions are met");
    signalOffStateLabel = new QLabel("State when conditions are not met");
    userLabel = new QLabel("Select the conditions that must be met to set this Signal Head on");

    updateSubButton = new QPushButton("Done");

    status1 = new QLabel(updateInst);

    p2xt = NULL;   // Turnout list table
    p2xs = NULL;   // Sensor list table

    curSignalGroup = NULL;}
//    /*public*/ SignalGroupSubTableAction() { this("SignalGroup Head Edit Table");}

    QString SignalGroupSubTableAction::helpTarget() {
        return "package.jmri.jmrit.beantable.SignalGroupTable";
    }

    void SignalGroupSubTableAction::setoperBox(bool mode, QComboBox* box) {
        int _mode = 0;
        if (mode) _mode = 1;
        QString result = StringUtil::getNameFromState(_mode, operValues, oper.toList());
        box->setCurrentIndex(box->findText(result));
    }

    bool SignalGroupSubTableAction::operFromBox(QComboBox* box) {
        QString mode = box->currentText();
        int result = StringUtil::getStateFromName(mode, operValues, oper);

        if (result<0) {
            log->warn("unexpected mode string in sensorMode: "+mode);
            throw new IllegalArgumentException();
        }
        if (result == 0) return false;
        else return true;
    }

    /*private*/ /*static*/ QVector<QString> SignalGroupSubTableAction::oper = QVector<QString>() <<"AND" << "OR";
    /*private*/ /*static*/ QVector<int>  SignalGroupSubTableAction::operValues = QVector<int>( )<<0x00 << 0x01;

    int SignalGroupSubTableAction::sensorModeFromBox(QComboBox* box) {
        QString mode = box->currentText();
        int result = StringUtil::getStateFromName(mode, sensorInputModeValues, sensorInputModes);

        if (result<0) {
            log->warn("unexpected mode string in signal Appearance: "+mode);
            throw new IllegalArgumentException();
        }
        return result;
    }

    void SignalGroupSubTableAction::setSensorModeBox(int mode, QComboBox* box) {
        QString result = StringUtil::getNameFromState(mode, sensorInputModeValues, sensorInputModes.toList());
        box->setCurrentIndex(box->findText(result));
    }

    int SignalGroupSubTableAction::signalStateFromBox(QComboBox* box) {
        SignalHead* sig = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(curSignal);
        int result;
        QString mode;
        if (sig!=NULL){
            mode = box->currentText();
            result = StringUtil::getStateFromName(mode, ((AbstractSignalHead*)sig)->getValidStates(), ((AbstractSignalHead*)sig)->getValidStateNames());
        }
        else {
            mode = box->currentText();
            result = StringUtil::getStateFromName(mode, signalStatesValues, signalStates);
        }

        if (result<0) {
            log->warn("unexpected mode string in signalMode: "+mode);
            throw new IllegalArgumentException();
        }
        return result;
    }

    void SignalGroupSubTableAction::setSignalStateBox(int mode, QComboBox* box)
    {
        SignalHead* sig = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(curSignal);
        QString result = StringUtil::getNameFromState(mode, ((AbstractSignalHead*)sig)->getValidStates(), ((AbstractSignalHead*)sig)->getValidStateNames().toList());
        box->setCurrentIndex(box->findText(result));
    }



    int SignalGroupSubTableAction::turnoutModeFromBox(QComboBox* box)
    {
        QString mode = box->currentText();
        int result = StringUtil::getStateFromName(mode, turnoutInputModeValues, turnoutInputModes);

        if (result<0) {
            log->warn("unexpected mode string in turnoutMode: "+mode);
            throw new IllegalArgumentException();
        }
        return result;
    }

    void SignalGroupSubTableAction::setTurnoutModeBox(int mode, QComboBox* box) {
        QString result = StringUtil::getNameFromState(mode, turnoutInputModeValues, turnoutInputModes.toList());
        box->setCurrentIndex(box->findText(result));
    }


void SignalGroupSubTableAction::editSignal(SignalGroup* g, QString signal)
{
 curSignalGroup = g;
 curSignal = signal;
 curSignalHead = ((AbstractSignalHeadManager*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")))->getSignalHead(curSignal);
 //SignalHead sig = jmri.static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")).getSignalHead(curSignal);

 _OnAppearance = new QComboBox();
 _OnAppearance->addItems(((AbstractSignalHead*)curSignalHead)->getValidStateNames().toList());
 _OffAppearance = new QComboBox();
 _OffAppearance->addItems(((AbstractSignalHead*)curSignalHead)->getValidStateNames().toList());
 _systemName= new QLabel(signal);
 _systemName->setVisible(true);

 TurnoutManager* tm = InstanceManager::turnoutManagerInstance();
 QStringList systemNameList = ((ProxyTurnoutManager*)tm)->getSystemNameList();
_turnoutList =  QList <SignalGroupTurnout*> (/*systemNameList.size()*/);
 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
  QString systemName = iter.next();
  QString userName = ((ProxyTurnoutManager*)tm)->getBySystemName(systemName)->getUserName();
  _turnoutList.append(new SignalGroupTurnout(systemName, userName));
 }

 SensorManager* sm = InstanceManager::sensorManagerInstance();
 systemNameList = ((ProxySensorManager*)sm)->getSystemNameList();
 _sensorList = QList <SignalGroupSensor*> (/*systemNameList.size()*/);
 iter = QStringListIterator(systemNameList);
 while (iter.hasNext())
 {
  QString systemName = iter.next();
  QString userName = ((ProxySensorManager*)sm)->getBySystemName(systemName)->getUserName();
  _sensorList.append(new SignalGroupSensor(systemName, userName));
 }
 initializeIncludedList();

// Set up window
if (addFrame==NULL)
{
 addFrame = new JmriJFrameX("Add/Edit SignalGroup", false, true);
 addFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalGroupAddEdit", true);
 addFrame->setLocation(100,30);
 addFrame->resize(300,800);
 QVBoxLayout* contentPaneLayout;
 if(addFrame->getContentPane() == NULL)
 {
  QWidget* centralWidget = new QWidget();
  centralWidget->setLayout(contentPaneLayout = new QVBoxLayout);
 }
 //addFrame->getContentPane()->setLayout(contentPaneLayout);
 else
   contentPaneLayout = (QVBoxLayout*)addFrame->getContentPane()->layout();
// QWidget* contentPane = addFrame->getContentPane();
 // add system name
 //QWidget* ps = new QWidget();
 FlowLayout* psFlowLayout = new FlowLayout;
 //ps->setLayout(new FlowLayout());
 psFlowLayout->addWidget(nameLabel);
 psFlowLayout->addWidget(_systemName);
 contentPaneLayout->addLayout(psFlowLayout);
 // add user name
 //QWidget* pc = new QWidget();
 FlowLayout* pcFlowLayout = new FlowLayout;
 //pc->setLayout(new FlowLayout());
 pcFlowLayout->addWidget(signalOnStateLabel);
 pcFlowLayout->addWidget(_OnAppearance);
 pcFlowLayout->addWidget(signalOffStateLabel);
 pcFlowLayout->addWidget(_OffAppearance);
 contentPaneLayout->addLayout(pcFlowLayout);

 //QWidget* p = new QWidget();
 //p->setLayout(new FlowLayout());
 FlowLayout* pFlowLayout = new FlowLayout;
 pFlowLayout->addWidget(userLabel);

 contentPaneLayout->addLayout(pFlowLayout);
 if (QString(curSignalHead->metaObject()->className()).contains("SingleTurnoutSignalHead"))
 {
  SingleTurnoutSignalHead* Signal = (SingleTurnoutSignalHead*) ((AbstractSignalHeadManager*)static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")))->getBySystemName(curSignal);
  if ((((DefaultSignalGroup*)g)->getSignalHeadOnState(curSignalHead)==0x00) && (((DefaultSignalGroup*)g)->getSignalHeadOffState(curSignalHead)==0x00)){
            ((DefaultSignalGroup*)g)->setSignalHeadOnState(curSignalHead, Signal->getOnAppearance());
            ((DefaultSignalGroup*)g)->setSignalHeadOffState(curSignalHead, Signal->getOffAppearance());
 }
}
setSignalStateBox(((DefaultSignalGroup*)g)->getSignalHeadOnState(curSignalHead), _OnAppearance);
setSignalStateBox(((DefaultSignalGroup*)g)->getSignalHeadOffState(curSignalHead), _OffAppearance);
// add Turnout Display Choice
//QWidget* py = new QWidget();
FlowLayout* pyFlowLayout = new FlowLayout;
pyFlowLayout->addWidget(new QLabel("Show "));
selGroup = new QButtonGroup();
allButton = new QRadioButton("All"/*,true*/);
allButton->setChecked(true);
selGroup->addButton(allButton);
pyFlowLayout->addWidget(allButton);
//            allButton.addActionListener(new ActionListener(){
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        // Setup for display of all Turnouts, if needed
//                        if (!showAll) {
//                            showAll = true;
//                            _SignalGroupTurnoutModel.fireTableDataChanged();
//                            _SignalGroupSensorModel.fireTableDataChanged();
//                        }
//                    }
//                });
 connect(allButton, SIGNAL(clicked()), this, SLOT(On_AllButton_clicked()));
 includedButton = new QRadioButton("Included"/*,false*/);
 selGroup->addButton(includedButton);
 pyFlowLayout->addWidget(includedButton);
//            includedButton.addActionListener(new ActionListener(){
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        // Setup for display of included Turnouts only, if needed
//                        if (showAll) {
//                            showAll = false;
//                            initializeIncludedList();
//                            _SignalGroupTurnoutModel.fireTableDataChanged();
//                            _SignalGroupSensorModel.fireTableDataChanged();
//                        }
//                    }
//                });
 connect(includedButton, SIGNAL(clicked()), this, SLOT(On_includedButton_clicked()));
 pyFlowLayout->addWidget(new QLabel("  Turnouts and Sensors"));
 contentPaneLayout->addLayout(pyFlowLayout);

 // add turnout table
 p2xt = new QWidget();
 QHBoxLayout* p2xtLayout = new QHBoxLayout;
 p2xt->setLayout(p2xtLayout);
 QWidget* p2xtSpace = new QWidget();
 QVBoxLayout* p2xtSpaceLayout;
 p2xtSpace->setLayout(p2xtSpaceLayout = new QVBoxLayout(p2xtSpace/*, BoxLayout.Y_AXIS*/));
 p2xtSpaceLayout->addWidget(new QLabel("XXX"));
 p2xtLayout->addWidget(p2xtSpace);

 //QWidget* p21t = new QWidget();
 //p21t->setLayout(new QVBoxLayout(p21t/*, BoxLayout.Y_AXIS*/));
 QVBoxLayout* p21tLayout = new QVBoxLayout;
 p21tLayout->addWidget(new QLabel("Please select "));
 p21tLayout->addWidget(new QLabel("Turnouts to be "));
 p21tLayout->addWidget(new QLabel("included in  "));
 p21tLayout->addWidget(new QLabel("this Signal Group."));
 p2xtLayout->addLayout(p21tLayout);
 _signalGroupTurnoutModel = new SignalGroupTurnoutModel(this);
 QTableView* signalGroupTurnoutTable = /*jmri.util.JTableUtil.sortableDataModel(_SignalGroupTurnoutModel)*/ new QTableView();
    signalGroupTurnoutTable->setModel(_signalGroupTurnoutModel);
//            try {
//                jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)SignalGroupTurnoutTable.getModel());
//                tmodel.setColumnComparator(Strin((DefaultSignalGroup*)g)->class, new jmri.util.SystemNameComparator());
//                tmodel.setSortingStatus(SignalGroupTurnoutModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//            } catch (ClassCastException e3) {}  // if not a sortable table model
//            SignalGroupTurnoutTable.setRowSelectionAllowed(false);
//            SignalGroupTurnoutTable.setPreferredScrollableViewportSize(new
//                                                            java.awt.Dimension(480,80));

//            ROW_HEIGHT = SignalGroupTurnoutTable.getRowHeight();
//            JComboBox stateTCombo = new JComboBox();
//            stateTCombo.addItem(SET_TO_CLOSED);
//            stateTCombo.addItem(SET_TO_THROWN);
//            TableColumnModel SignalGroupTurnoutColumnModel = SignalGroupTurnoutTable.getColumnModel();
//            TableColumn includeColumnT = SignalGroupTurnoutColumnModel.
//                                                getColumn(SignalGroupTurnoutModel.INCLUDE_COLUMN);
//            includeColumnT.setResizable(false);
//            includeColumnT.setMinWidth(50);
//            includeColumnT.setMaxWidth(60);
//            TableColumn sNameColumnT = SignalGroupTurnoutColumnModel.
//                                                getColumn(SignalGroupTurnoutModel.SNAME_COLUMN);
//            sNameColumnT.setResizable(true);
//            sNameColumnT.setMinWidth(75);
//            sNameColumnT.setMaxWidth(95);
//            TableColumn uNameColumnT = SignalGroupTurnoutColumnModel.
//                                                getColumn(SignalGroupTurnoutModel.UNAME_COLUMN);
//            uNameColumnT.setResizable(true);
//            uNameColumnT.setMinWidth(210);
//            uNameColumnT.setMaxWidth(260);
//            TableColumn stateColumnT = SignalGroupTurnoutColumnModel.
//                                                getColumn(SignalGroupTurnoutModel.STATE_COLUMN);
//            stateColumnT.setCellEditor(new DefaultCellEditor(stateTCombo));
//            stateColumnT.setResizable(false);
//            stateColumnT.setMinWidth(90);
//            stateColumnT.setMaxWidth(100);
//            _SignalGroupTurnoutScrollPane = new JScrollPane(SignalGroupTurnoutTable);
    //p2xt.add(_SignalGroupTurnoutScrollPane,BorderLayout.CENTER);
 p2xtLayout->addWidget(signalGroupTurnoutTable);
 contentPaneLayout->addWidget(p2xt);
 p2xt->setVisible(true);

    QWidget* po = new QWidget();
    po->setLayout(new FlowLayout());
    QLabel* operLabel = new QLabel("Do either the Sensors OR Turnouts have to match, or do they both have to Match");
    po->layout()->addWidget(operLabel);
    po->layout()->addWidget( _SensorTurnoutOper);
    contentPaneLayout->addWidget(po);
     // add sensor table
    p2xs = new QWidget();
    p2xs->setLayout(new QHBoxLayout);
    QWidget* p2xsSpace = new QWidget();
    p2xsSpace->setLayout(new QVBoxLayout(p2xsSpace/*, BoxLayout.Y_AXIS*/));
    p2xsSpace->layout()->addWidget(new QLabel("XXX"));
    p2xs->layout()->addWidget(p2xsSpace);

    QWidget* p21s = new QWidget();
    p21s->setLayout(new QVBoxLayout(p21s/*, BoxLayout.Y_AXIS*/));
    p21s->layout()->addWidget(new QLabel("Please select "));
    p21s->layout()->addWidget(new QLabel(" Sensors to "));
    p21s->layout()->addWidget(new QLabel(" be included "));
    p21s->layout()->addWidget(new QLabel(" in this SignalGroup."));
    p2xs->layout()->addWidget(p21s);
    _signalGroupSensorModel = new SignalGroupSensorModel(this);
    QTableView* signalGroupSensorTable = new QTableView();
    /*jmri.util.JTableUtil.sortableDataModel(_SignalGroupSensorModel);*/
    signalGroupSensorTable->setModel(_signalGroupSensorModel);
//            try {
//                jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)SignalGroupSensorTable.getModel());
//                tmodel.setColumnComparator(Strin((DefaultSignalGroup*)g)->class, new jmri.util.SystemNameComparator());
//                tmodel.setSortingStatus(SignalGroupSensorModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//            } catch (ClassCastException e3) {}  // if not a sortable table model
//            SignalGroupSensorTable.setRowSelectionAllowed(false);
//            SignalGroupSensorTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,80));
//            JComboBox stateSCombo = new JComboBox();
//            stateSCombo.addItem(SET_TO_ACTIVE);
//            stateSCombo.addItem(SET_TO_INACTIVE);
//            TableColumnModel SignalGroupSensorColumnModel = SignalGroupSensorTable.getColumnModel();
//            TableColumn includeColumnS = SignalGroupSensorColumnModel.
//                                                getColumn(SignalGroupSensorModel.INCLUDE_COLUMN);
//            includeColumnS.setResizable(false);
//            includeColumnS.setMinWidth(50);
//            includeColumnS.setMaxWidth(60);
//            TableColumn sNameColumnS = SignalGroupSensorColumnModel.
//                                                getColumn(SignalGroupSensorModel.SNAME_COLUMN);
//            sNameColumnS.setResizable(true);
//            sNameColumnS.setMinWidth(75);
//            sNameColumnS.setMaxWidth(95);
//            TableColumn uNameColumnS = SignalGroupSensorColumnModel.
//                                                getColumn(SignalGroupSensorModel.UNAME_COLUMN);
//            uNameColumnS.setResizable(true);
//            uNameColumnS.setMinWidth(210);
//            uNameColumnS.setMaxWidth(260);
//            TableColumn stateColumnS = SignalGroupSensorColumnModel.
//                                                getColumn(SignalGroupSensorModel.STATE_COLUMN);
//            stateColumnS.setCellEditor(new DefaultCellEditor(stateSCombo));
//            stateColumnS.setResizable(false);
//            stateColumnS.setMinWidth(90);
//            stateColumnS.setMaxWidth(100);
//            _SignalGroupSensorScrollPane = new JScrollPane(SignalGroupSensorTable);
//            p2xs.add(_SignalGroupSensorScrollPane,BorderLayout.CENTER);
    p2xs->layout()->addWidget(signalGroupSensorTable);
    contentPaneLayout->addWidget(p2xs);
    p2xs->setVisible(true);


    // add lock control table
    /*QWidget* p4 = new QWidget();
    p4->setLayout(new BoxLayout(p4, BoxLayout.Y_AXIS));

    // complete this panel
    Border p4Border = BorderFactory.createEtchedBorder();
    p4.setBorder(p4Border);
    contentPane.add(p4);*/

    // add notes panel
    QFrame* pa = new QFrame();
    pa->setLayout(new QVBoxLayout(pa/*, BoxLayout.Y_AXIS*/));
    QWidget* p1 = new QWidget();
    p1->setLayout(new FlowLayout());
    p1->layout()->addWidget(status1);
    pa->layout()->addWidget(p1);
//            Border pBorder = BorderFactory.createEtchedBorder();
//            pa.setBorder(pBorder);
    pa->setFrameStyle(QFrame::StyledPanel);
    pa->setFrameShadow(QFrame::Raised);
    pa->setLineWidth(2);
    contentPaneLayout->addWidget(pa);
    // add buttons - Add SignalGroup button
    //QWidget* pb = new QWidget();
    //pb->setLayout(new FlowLayout());
    FlowLayout* pbFlowLayout = new FlowLayout;

    // Update SignalGroup button
    pbFlowLayout->addWidget(updateSubButton);
//            updateSubButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    updateSubPressed(e, false);
//                }
//            });
    connect(updateSubButton, SIGNAL(clicked()), this, SLOT(On_updateSubButton_clicked()));
    updateSubButton->setToolTip("Change this SignalGroup and leave Edit mode");

    p2xtSpace->setVisible(false);
    p2xsSpace->setVisible(false);
    updateSubButton->setVisible(true);
    contentPaneLayout->addLayout(pbFlowLayout);
    addFrame->pack();

}
// set listener for window closing
//        addFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    addFrame.setVisible(false);
//                    cancelEdit();
//                    _SignalGroupSensorModel.dispose();
//                    _SignalGroupTurnoutModel.dispose();
//                }
//            });
addFrame->setVisible(true);
setoperBox(curSignalGroup->getSensorTurnoutOper(curSignalHead), _SensorTurnoutOper);
setSignalStateBox(curSignalGroup->getSignalHeadOnState(curSignalHead), _OnAppearance);
setSignalStateBox(curSignalGroup->getSignalHeadOffState(curSignalHead), _OffAppearance);
int setRow = 0;
for (int i=_turnoutList.size()-1; i>=0; i--)
{
 SignalGroupTurnout* turnout = _turnoutList.at(i);
 Turnout* tTurnout = turnout->getTurnout();
 if (curSignalGroup->isTurnoutIncluded(curSignalHead, tTurnout) )
 {
  turnout->setIncluded(true);
  turnout->setState(((DefaultSignalGroup*)curSignalGroup)->getTurnoutState(curSignalHead, tTurnout));
  setRow = i;
 }
 else
 {
  turnout->setIncluded(false);
  turnout->setState(Turnout::CLOSED);
 }
}
setRow -= 1;
if (setRow < 0)
{
 setRow = 0;
}
//_SignalGroupTurnoutScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
_signalGroupTurnoutModel->fireTableDataChanged();

for (int i=_sensorList.size()-1; i>=0; i--) {
    SignalGroupSensor* sensor = _sensorList.at(i);
    Sensor* tSensor = sensor->getSensor();
    if (((DefaultSignalGroup*)curSignalGroup)->isSensorIncluded(curSignalHead, tSensor) ) {
        sensor->setIncluded(true);
        sensor->setState(((DefaultSignalGroup*)curSignalGroup)->getSensorState(curSignalHead, tSensor));
        setRow = i;
    } else {
        sensor->setIncluded(false);
        sensor->setState(Sensor::INACTIVE);
    }
}

status1->setText(updateInst);
updateSubButton->setVisible(true);

}

void SignalGroupSubTableAction::setColumnToHoldButton(QTableView* /*table*/, int /*column*/, QPushButton* /*sample*/) {
        //TableColumnModel tcm = table.getColumnModel();
        // install a button renderer & editor
//        ButtonRenderer buttonRenderer = new ButtonRenderer();
//        table.setDefaultRenderer(JButton.class,buttonRenderer);
//        TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//        table.setDefaultEditor(JButton.class,buttonEditor);
//        // ensure the table rows, columns have enough room for buttons
//        table.setRowHeight(sample.getPreferredSize().height);
//        table.getColumnModel().getColumn(column)
//            .setPreferredWidth((sample.getPreferredSize().width)+4);
    }

    /**
     * Initialize list of included turnout positions
     */
    void SignalGroupSubTableAction::initializeIncludedList() {
        _includedTurnoutList = QList <SignalGroupTurnout*> ();
        for (int i=0; i<_turnoutList.size(); i++) {
            if (_turnoutList.at(i)->isIncluded( )) {
                _includedTurnoutList.append(_turnoutList.at(i));
            }
        }
        _includedSensorList = QList <SignalGroupSensor*> ();
        for (int i=0; i<_sensorList.size(); i++) {
            if (_sensorList.at(i)->isIncluded()) {
                _includedSensorList.append(_sensorList.at(i));
            }
        }
    }

    /**
     * Sets the Turnout information for adding or editting
     */
    int SignalGroupSubTableAction::setTurnoutInformation(SignalGroup* g) {
        for (int i=0; i<_includedTurnoutList.size(); i++) {
            SignalGroupTurnout* t = _includedTurnoutList.at(i);
            ((DefaultSignalGroup*)g)->setSignalHeadAlignTurnout(curSignalHead, t->getTurnout(), t->getState());
        }
        return _includedTurnoutList.size();
    }

    /**
     * Sets the Sensor information for adding or editting
     */
    int SignalGroupSubTableAction::setSensorInformation(SignalGroup* g) {
        for (int i=0; i<_includedSensorList.size(); i++) {
            SignalGroupSensor* s = _includedSensorList.at(i);
            ((DefaultSignalGroup*)g)->setSignalHeadAlignSensor(curSignalHead, s->getSensor(), s->getState());
        }
        return _includedSensorList.size();
    }

    /**
     * Responds to the Update button - update to SignalGroup Table
     */
    void SignalGroupSubTableAction::updateSubPressed(JActionEvent* /*e*/, bool /*newSignalGroup*/ ) {
        ((DefaultSignalGroup*)curSignalGroup)->clearSignalTurnout(curSignalHead);
        ((DefaultSignalGroup*)curSignalGroup)->clearSignalSensor(curSignalHead);

        initializeIncludedList();
        setTurnoutInformation(curSignalGroup);
        setSensorInformation(curSignalGroup);
        ((DefaultSignalGroup*)curSignalGroup)->setSignalHeadOnState(curSignalHead, signalStateFromBox(_OnAppearance));
        ((DefaultSignalGroup*)curSignalGroup)->setSignalHeadOffState(curSignalHead, signalStateFromBox(_OffAppearance));
        ((DefaultSignalGroup*)curSignalGroup)->setSensorTurnoutOper(curSignalHead, operFromBox(_SensorTurnoutOper));
        // add control Sensors and a control Turnout if entered in the window
        finishUpdate();
    }

    void SignalGroupSubTableAction::finishUpdate() {
        // move to show all turnouts if not there
        cancelIncludedOnly();
        updateSubButton->setVisible(false);

        addFrame->setVisible(false);
    }

    /**
     * Cancels edit mode
     */
    void SignalGroupSubTableAction::cancelEdit() {
        // get out of edit mode
        curSignalGroup = NULL;
        finishUpdate();
    }

    /**
     * Cancels included Turnouts only option
     */
    void SignalGroupSubTableAction::cancelIncludedOnly() {
        if (!showAll) {
            allButton->click();
        }
    }

    /**
     * Base table model for selecting outputs
     */
//    /*public*/ abstract class SignalGroupOutputModel : public AbstractTableModel //implements PropertyChangeListener
//    {
//        /*public*/ Class<?> getColumnClass(int c) {
//            if (c == INCLUDE_COLUMN) {
//                return Boolean.class;
//            }
//            else {
//                return Strin((DefaultSignalGroup*)g)->class;
//            }
//        }

        /*public*/ void SGSTASignalGroupOutputModel::propertyChange(PropertyChangeEvent* e) {
            if (e->getPropertyName()==("length")) {
                // a new NamedBean is available in the manager
                fireTableDataChanged();
            }
        }

        /*public*/ void SGSTASignalGroupOutputModel::dispose() {
            ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->removePropertyChangeListener((PropertyChangeListener*)this);
        }

/*public*/ QVariant SGSTASignalGroupOutputModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
  return SignalGroupSubTableAction::COLUMN_NAMES[section];
 return QVariant();
}

        /*public*/ int SGSTASignalGroupOutputModel::columnCount(const QModelIndex &/*parent*/) const {return 4;}

/*public*/ Qt::ItemFlags SGSTASignalGroupOutputModel::flags(const QModelIndex &index) const
{
 if ( (index.column()==INCLUDE_COLUMN)  )
  return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
 if(index.column()==STATE_COLUMN)
  return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
 return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
}

/*public*/ QVariant SGSTASignalGroupOutputModel::data(const QModelIndex &mindex, int role) const
{
 if(role == Qt::DisplayRole)
 {
  if (( data(index(mindex.row(), UNAME_COLUMN),Qt::DisplayRole)!=QVariant()) /*||(!((String) getValueAt(r, UNAME_COLUMN))==(""))*/ )
  {
   return data(index(mindex.row(), UNAME_COLUMN),Qt::DisplayRole).toString();
  }
  else
  {
   return  data(index(mindex.row(), SNAME_COLUMN),Qt::DisplayRole).toString();
  }
 }
 return QVariant();
}

    //};


/**
 * Table model for selecting Turnouts and Turnout State
 */
//    class SignalGroupTurnoutModel : public SignalGroupOutputModel
//    {
    SignalGroupTurnoutModel::SignalGroupTurnoutModel(SignalGroupSubTableAction* act)
    {
        this->act = act;
        ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->addPropertyChangeListener((PropertyChangeListener*)this);
    }

    /*public*/ int SignalGroupTurnoutModel::rowCount(const QModelIndex &/*parent*/) const
    {
        if (act->showAll)
            return act->_turnoutList.size();
        else
            return act->_includedTurnoutList.size();
    }
    /*public*/ QVariant SignalGroupTurnoutModel::data(const QModelIndex &index, int role) const
    {
        QList <SignalGroupSubTableAction::SignalGroupTurnout*> turnoutList = QList <SignalGroupSubTableAction::SignalGroupTurnout*>();
        if (act->showAll) {
            turnoutList = act->_turnoutList;
        }
        else {
            turnoutList = act->_includedTurnoutList;
        }
        int r = index.row();
        // some error checking
        if (r >= turnoutList.size()){
            act->log->debug("row is greater than turnout list size");
            return QVariant();
        }
        if(role == Qt::CheckStateRole && index.column() == INCLUDE_COLUMN)
        {
            if(turnoutList.at(r)->isIncluded())
                return Qt::Checked;
            else
                return Qt::Unchecked;
        }
        if(role == Qt::DisplayRole)
     {
      switch (index.column())
      {
        case INCLUDE_COLUMN:
                //return Boolean.valueOf(turnoutList.get(r).isIncluded());
          return "";
        case SNAME_COLUMN:  // slot number
            return turnoutList.at(index.row())->getSysName();
        case UNAME_COLUMN:  //
            return turnoutList.at(index.row())->getUserName();
        case STATE_COLUMN:  //
            return turnoutList.at(index.row())->getSetToState();
        default:
          return QVariant();
      }
     }
     return QVariant();
    }
    /*public*/ bool SignalGroupTurnoutModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        QList <SignalGroupSubTableAction::SignalGroupTurnout*> turnoutList = QList <SignalGroupSubTableAction::SignalGroupTurnout*>();
        if (act->showAll) {
            turnoutList = act->_turnoutList;
        }
        else {
            turnoutList = act->_includedTurnoutList;
        }
        if(role == Qt::CheckStateRole && index.column() == INCLUDE_COLUMN)
        {
         turnoutList.at(index.row())->setIncluded(value.toBool());
         return true;
        }
        if(role == Qt::EditRole && index.column() ==  STATE_COLUMN)
        {
         turnoutList.at(index.row())->setSetToState(value.toString());
         return true;
        }
        return false;
    }
//};

/**
 * Set up table for selecting Sensors and Sensor State
 */
//class SignalGroupSensorModel : public SignalGroupOutputModel
//{
    SignalGroupSensorModel::SignalGroupSensorModel(SignalGroupSubTableAction* act)
    {
     this->act = act;
        ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->addPropertyChangeListener((PropertyChangeListener*)this);
    }

    /*public*/ int SignalGroupSensorModel::rowCount(const QModelIndex &/*parent*/) const
    {
        if (act->showAll)
            return act->_sensorList.size();
        else
            return act->_includedSensorList.size();
    }

/*public*/ QVariant SignalGroupSensorModel::data(const QModelIndex &index, int role) const
{
        QList <SignalGroupSubTableAction::SignalGroupSensor*> sensorList = QList <SignalGroupSubTableAction::SignalGroupSensor*> ();
 if (act->showAll)
 {
        sensorList = act->_sensorList;
    }
    else {
        sensorList = act->_includedSensorList;
    }
    // some error checking
    if (index.row() >= sensorList.size())
    {
        act->log->debug("row is greater than turnout list size");
        return QVariant();
    }
    if(role == Qt::CheckStateRole && index.column() == INCLUDE_COLUMN)
    {
        if(sensorList.at(index.row())->isIncluded())
            return Qt::Checked;
        else
            return Qt::Unchecked;
    }
    if(role == Qt::DisplayRole)
    {

    switch (index.column()) {
        case INCLUDE_COLUMN:
            //return Boolean.valueOf(sensorList.get(r).isIncluded());
         return "";
        case SNAME_COLUMN:  // slot number
            return sensorList.at(index.row())->getSysName();
        case UNAME_COLUMN:  //
            return sensorList.at(index.row())->getUserName();
        case STATE_COLUMN:  //
            return sensorList.at(index.row())->getSetToState();
        default:
            //return NULL;
        break;
  }
 }
 return QVariant();
}

    /*public*/ bool SignalGroupSensorModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        QList <SignalGroupSubTableAction::SignalGroupSensor*> sensorList = QList <SignalGroupSubTableAction::SignalGroupSensor*>();
        int r = index.row();
        if (act->showAll) {
            sensorList = act->_sensorList;
        }
        else {
            sensorList = act->_includedSensorList;
        }
        if(role == Qt::CheckStateRole && index.column() == INCLUDE_COLUMN)
        {
         sensorList.at(r)->setIncluded(value.toBool());
         return true;
        }
        if(role == Qt::EditRole && index.column() ==  STATE_COLUMN)
        {
         sensorList.at(r)->setSetToState(value.toString());
         return true;
        }
        return false;
    }
    //};



    /*private*/ /*static*/ QVector<QString> SignalGroupSubTableAction::turnoutInputModes = QVector<QString>() << /*((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText()*/tr("Closed") << /*((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getThrownText()*/ tr("Thrown") ;
    /*private*/ /*static*/ QVector<int> SignalGroupSubTableAction::turnoutInputModeValues = QVector<int>() << SignalGroup::ONCLOSED << SignalGroup::ONTHROWN ;

//    /*private*/ /*abstract*/ class SignalGroupElement : public QObject
//    {
//        QString _sysName;
//        QString _userName;
//        bool _included;
//        int _setToState;

        SignalGroupSubTableAction::SignalGroupElement::SignalGroupElement(QString sysName, QString userName) {
            _sysName = sysName;
            _userName = userName;
            _included = false;
            _setToState = Sensor::INACTIVE;
        }
        QString SignalGroupSubTableAction::SignalGroupElement::getSysName() {
            return _sysName;
        }
        QString SignalGroupSubTableAction::SignalGroupElement::getUserName() {
            return _userName;
        }
        bool SignalGroupSubTableAction::SignalGroupElement::isIncluded() {
            return _included;
        }
        void SignalGroupSubTableAction::SignalGroupElement::setIncluded(bool include) {
            _included = include;
        }
//        /*abstract*/ QString getSetToState();
//        /*abstract*/ void setSetToState(QString state);

        int SignalGroupSubTableAction::SignalGroupElement::getState() {
            return _setToState;
        }
        void SignalGroupSubTableAction::SignalGroupElement::setState(int state) {
            _setToState = state;
        }

    //};

//    /*private*/ class SignalGroupSensor : public SignalGroupElement {
        SignalGroupSubTableAction::SignalGroupSensor::SignalGroupSensor (QString sysName, QString userName) : SignalGroupElement(sysName, userName)
        {
            //super(sysName, userName);
        }
        QString SignalGroupSubTableAction::SignalGroupSensor::getSetToState() {
            switch (_setToState) {
                case Sensor::INACTIVE:
                    return SET_TO_INACTIVE;
                case Sensor::ACTIVE:
                    return SET_TO_ACTIVE;
            }
            return "";
        }
        void SignalGroupSubTableAction::SignalGroupSensor::setSetToState(QString state) {
            if (SET_TO_INACTIVE==(state)) {
                _setToState = Sensor::INACTIVE;
            } else if (SET_TO_ACTIVE==(state)) {
                _setToState = Sensor::ACTIVE;
            }
        }

        Sensor* SignalGroupSubTableAction::SignalGroupSensor::getSensor(){
            return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(_sysName);
        }
    //};

//    /*private*/ class SignalGroupTurnout : public SignalGroupElement
//    {
        SignalGroupSubTableAction::SignalGroupTurnout::SignalGroupTurnout(QString sysName, QString userName) : SignalGroupElement(sysName, userName)
        {
            //super(sysName, userName);
        }
        QString SignalGroupSubTableAction::SignalGroupTurnout::getSetToState() {
            switch (_setToState) {
                case Turnout::CLOSED:
                    return SET_TO_CLOSED;
                case Turnout::THROWN:
                    return SET_TO_THROWN;
            }
            return "";
        }
        void SignalGroupSubTableAction::SignalGroupTurnout::setSetToState(QString state) {
            if (SET_TO_CLOSED==(state)) {
                _setToState = Turnout::CLOSED;
            } else if (SET_TO_THROWN==(state)) {
                _setToState = Turnout::THROWN;
            }
        }

        Turnout* SignalGroupSubTableAction::SignalGroupTurnout::getTurnout(){
            return ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(_sysName);
        }
//    }
void SignalGroupSubTableAction::On_AllButton_clicked()
{
 updateSubPressed(NULL, false);
}
void SignalGroupSubTableAction::On_includedButton_clicked()
{
 if (showAll)
 {
  showAll = false;
  initializeIncludedList();
  _signalGroupTurnoutModel->fireTableDataChanged();
  _signalGroupSensorModel->fireTableDataChanged();
 }
}

void SignalGroupSubTableAction::On_updateSubButton_clicked()
{
   updateSubPressed(NULL, false);
}
