#include "signalheadtableaction.h"
#include "actionevent.h"
#include  "../Tables/beanselectcreatepanel.h"
#include "instancemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "Signal/signalhead.h"
#include <QScrollArea>
#include <QMainWindow>
#include <QFrame>
#include "joptionpane.h"
#include "Signal/se8csignalhead.h"
#include "stringutil.h"
#include "Signal/singleturnoutsignalhead.h"
#include "doubleturnoutsignalhead.h"
#include "virtualsignalhead.h"
#include "../LayoutEditor/panelmenu.h"
#include "QMenuBar"
#include "abstractsignalheadmanager.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "tripleturnoutsignalhead.h"
#include "quadoutputsignalhead.h"
#include "flowlayout.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include "connectionnamefromsystemname.h"
#include "../LayoutEditor/jmrijframe.h"
#include <QPushButton>
#include "dccsignalhead.h"
#include "tripleoutputsignalhead.h"
#include "commandstation.h"
#include "jlabel.h"
#include "loggerfactory.h"
#include "borderlayout.h"
#include "slotmanager.h"
#include "lsdecsignalhead.h"
#include "mergsd2signalhead.h"
#include "acelasignalhead.h"
#include "acelanode.h"
#include "acelaaddress.h"
#include "acelasystemconnectionmemo.h"

SignalHeadTableAction::SignalHeadTableAction(QObject *parent) :
    AbstractTableAction(tr("Signal Head"), parent)
{
}
/**
 * Swing action to create and register a
 * SignalHeadTable GUI.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003,2006,2007, 2008, 2009
 * @author	Petr Koud'a     Copyright (C) 2007
 * @version     $Revision: 22224 $
 */

///*public*/ class SignalHeadTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param s
 */
/*public*/ SignalHeadTableAction::SignalHeadTableAction(QString s, QObject *parent) : AbstractTableAction(s, parent)
{
 //super(s);
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
 // disable ourself if there is no primary Signal Head manager available
 if(InstanceManager::getDefault("SignalHeadManager")==nullptr)
 {
  setEnabled(false);
 }
 addFrame = nullptr;
 acelaAspect = tr("Acela Aspect");
 se8c4Aspect = tr("SE8c 4 Aspect");
 quadOutput = tr("Quad Output");
 tripleOutput = tr("Triple Output");
 tripleTurnout = tr("Triple Turnout");
 doubleTurnout = tr("Double Turnout");
 virtualHead = tr("Virtual");
 grapevine = tr("Grapevine ");
 acela = tr("Acela Aspect");
 lsDec = tr("LDT LS-DEC");
 dccSignalDecoder = tr("DCC Signal Decoder");
 mergSignalDriver = tr("Merg Signal Driver");
 singleTurnout = tr("Single Output");
 systemNameTextField = new JTextField(5);
 systemNameTextField->setMaxLength(10);
 userNameTextField = new JTextField(10);
 ato1TextField = new JTextField(5);
 _curSignal = nullptr;
 editFrame = nullptr;
 enabled = true;

 signalStatesValues =  QVector<int>() <<
            SignalHead::DARK <<
            SignalHead::RED <<
            SignalHead::LUNAR <<
            SignalHead::YELLOW <<
            SignalHead::GREEN;
 signalStates = QVector<QString>() <<
            tr("Dark") <<
            tr("Red") <<
            tr("Lunar") <<
            tr("Yellow")<<
            tr("Green");
 stateThrown = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
 stateClosed = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
 turnoutStates = QStringList() << stateClosed << stateThrown ;
 turnoutStateValues = QList<int>() << Turnout::CLOSED << Turnout::THROWN;
 signalheadSingle = tr("SINGLE");
 signalheadDouble = tr("DOUBLE");
 signalheadTriple = tr("TRIPLE");
 signalheadBiPolar = tr("BPOLAR");
 signalheadWigwag = tr("WIGWAG");
 signalheadTypes =  QStringList() << signalheadDouble << signalheadTriple << signalheadBiPolar << signalheadWigwag;
 signalheadTypeValues = QList<int>() << /*AcelaNode::DOUBLE, AcelaNode::TRIPLE,
                                           AcelaNode::BPOLAR, AcelaNode::WIGWAG;*/ 1 << 2 << 3 << 4;
 ukSignalAspects = QStringList() << "1" << "2" <<"3" << "4";
 ukSignalType = QStringList() << "Home" << "Distant";
 //prefixBox = new QComboBox();
 //prefixBoxLabel = new QLabel("System : ");
 vtLabel = new QLabel("");
 defaultFlow = new FlowLayout();
 s1Box = new QComboBox(/*turnoutStates*/);
 s1Box->addItems(turnoutStates);
 s2Box = new QComboBox(/*turnoutStates*/);
 s2Box->addItems(turnoutStates);
 s2aBox = new QComboBox(/*signalStates*/);
 s2aBox->addItems(signalStates.toList());
 s3Box = new QComboBox(/*turnoutStates*/);
 s3Box->addItems(turnoutStates);
 s3aBox = new QComboBox(/*signalStates*/);
 s3aBox->addItems(signalStates.toList());
 s4Box = new QComboBox(/*turnoutStates*/);
 s4Box->addItems(turnoutStates);
 s5Box = new QComboBox(/*turnoutStates*/);
 s5Box->addItems(turnoutStates);
 s6Box = new QComboBox(/*turnoutStates*/);
 s6Box->addItems(turnoutStates);
 s7Box = new QComboBox(/*turnoutStates*/);
 s7Box->addItems(turnoutStates);
 stBox = new QComboBox(/*signalheadTypes*/); // Acela signal types
 stBox->addItems(signalheadTypes);
 mstBox = new QComboBox(/*ukSignalType*/);
 mstBox->addItems(ukSignalType);
 msaBox = new QComboBox(/*ukSignalAspects*/);
 msaBox->addItems(ukSignalAspects);

 // variables for edit of signal headseditFrame = NULL;
 editingHead = false;
 etot = new JTextField(5);
 signalType = new QLabel("XXXX");
 curS = nullptr;
 className = "";
 eSystemName = new JTextField(5);
 eUserName = new JTextField(10);
 et1 = nullptr;
 et2 = nullptr;
 et3 = nullptr;
 et4 = nullptr;
 et5 = nullptr;
 et6 = nullptr;
 et7 = nullptr;

 eSystemNameLabel = new QLabel("");
 eUserNameLabel = new QLabel("");
 eSysNameLabel = new QLabel ("");

 evtLabel = new QLabel("");
 es1Box = new QComboBox(/*turnoutStates*/);
 es1Box->addItems(turnoutStates);
 es2Box = new QComboBox(/*turnoutStates*/);
 es2Box->addItems(turnoutStates);
 es2aBox = new QComboBox(/*signalStates*/);
 es2aBox->addItems(turnoutStates);
 es3Box = new QComboBox(/*turnoutStates*/);
 es3Box->addItems(turnoutStates);
 es3aBox = new QComboBox(/*signalStates*/);
 es3aBox->addItems(turnoutStates);
 es4Box = new QComboBox(/*turnoutStates*/);
 es4Box->addItems(turnoutStates);
 es5Box = new QComboBox(/*turnoutStates*/);
 es5Box->addItems(turnoutStates);
 es6Box = new QComboBox(/*turnoutStates*/);
 es6Box->addItems(turnoutStates);
 es7Box = new QComboBox(/*turnoutStates*/);
 es7Box->addItems(turnoutStates);
 estBox = new QComboBox(/*signalheadTypes*/);
 estBox->addItems(signalheadTypes);
 emstBox = new QComboBox(/*ukSignalType*/);
 emstBox->addItems(ukSignalType);
 emsaBox = new QComboBox(/*ukSignalAspects*/);
 emsaBox->addItems(ukSignalAspects);
 systemNameTextField = new JTextField(5);
 userNameTextField = new JTextField(10);
 ato1TextField = new JTextField(5);
}

/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of SignalHeads
 */
/*protected*/ void SignalHeadTableAction::createModel()
{
 m = new SHBeanTableDataModel(this);
}

SHBeanTableDataModel::SHBeanTableDataModel(SignalHeadTableAction *self) : BeanTableDataModel()
{
 this->self = self;
 log = new Logger("SHBeanTableDataModel");
 init();
}

/*public*/ int SHBeanTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{return NUMCOLUMN+3;}
/*public*/ QVariant SHBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
    if (col==LITCOL) return tr("Head Lit");
    else if (col==HELDCOL) return tr("Head Held");
    else if (col==EDITCOL) return ""; // no heading on "Edit"
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}
///*public*/ Class<?> getColumnClass(int col) {
//    if (col==LITCOL) return Boolean.class;
//    else if (col==HELDCOL) return Boolean.class;
//    else if (col==EDITCOL) return JButton.class;
//    else return super.getColumnClass(col);
//}
/*public*/ void SHBeanTableDataModel::configureTable(JTable *table)
{
 setColumnToHoldButton(table, EDITCOL);
 BeanTableDataModel::configureTable(table);
}

/*public*/ int SHBeanTableDataModel::getPreferredWidth(int col) {
    if (col==LITCOL) return  JTextField(4).sizeHint().width();
    else if (col==HELDCOL) return  JTextField(4).sizeHint().width();
    else if (col==EDITCOL) return  JTextField(7).sizeHint().width();

    else return BeanTableDataModel::getPreferredWidth(col);
}
/*public*/ Qt::ItemFlags SHBeanTableDataModel::flags(const QModelIndex &index) const
{
    int col = index.column();
    if (col==LITCOL) return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    else if (col==HELDCOL) return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    else if (col==EDITCOL) return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    else return BeanTableDataModel::flags(index);
}

/*public*/ QVariant SHBeanTableDataModel::data(const QModelIndex &index, int role) const
{
 int col = index.column();
 int row = index.row();
 QString name = sysNameList.at(row);
 SignalHead* s = (SignalHead*)qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name)->self();

 if(role == Qt::DisplayRole)
 {
    // some error checking
    if (row >= sysNameList.size()){
        log->debug("row is greater than name list");
        return "error";
    }
    if (s==nullptr) return (false); // if due to race condition, the device is going away
     if (col==EDITCOL) return tr("Edit");
 }
 if(role == Qt::CheckStateRole)
 {
  if (col==LITCOL)
  {
   bool val = s->getLit();
   return val?Qt::Checked:Qt::Unchecked;
  }
  if (col==HELDCOL)
  {
    bool val = s->getHeld();
    return val?Qt::Checked:Qt::Unchecked;
  }

 }
 return BeanTableDataModel::data(index, role);
}

/*public*/ bool SHBeanTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int col = index.column();
 int row = index.row();
 QString name = sysNameList.at(row);
 SignalHead* s = (SignalHead*)qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name)->self();
 if (s==nullptr) return false;  // device is going away anyway
 if(role == Qt::CheckStateRole)
 {
  if (col==LITCOL)
  {
    bool b = value.toBool();
    s->setLit(b);
    return true;
  }
  else if (col==HELDCOL)
  {
    bool b = value.toBool();
    s->setHeld(b);
    return true;
  }
 }
 if(role == Qt::EditRole)
 {
  if (col==EDITCOL)
  {
    // button clicked - edit
    self->editSignal(/*row*/s);
    return true;
  }
 }
 return  BeanTableDataModel::setData(index, value,role);
}

/*public*/ QString SHBeanTableDataModel::getValue(QString name) const
{
    SignalHead* s =(SignalHead*)qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name)->self();
    if (s==nullptr) return "<lost>"; // if due to race condition, the device is going away
    QString val = "";
    try {
        val = s->getAppearanceName();
    } catch (ArrayIndexOutOfBoundsException* e) {
        log->error(e->getMessage(), e);
    }

    if (val != nullptr) return val;
    else return "Unexpected NULL value";

}
/*public*/ AbstractManager *SHBeanTableDataModel::getManager() { return qobject_cast<AbstractManager*>(InstanceManager::getDefault("SignalHeadManager")); }

/*public*/ NamedBean* SHBeanTableDataModel::getBySystemName(QString name) const
{ return static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(name);}

/*public*/ NamedBean* SHBeanTableDataModel::getByUserName(QString name) { return static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getByUserName(name);}

/*public int SHBeanTableDataModel::getDisplayDeleteMsg() { return InstanceManager::getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
public void SHBeanTableDataModel::setDisplayDeleteMsg(int boo) { InstanceManager::getDefault(jmri.UserPreferencesManager.class).setMultipleChoiceOption(getClassName(), "delete", boo); }*/
/*protected*/ QString SHBeanTableDataModel::getMasterClassName() { return /*getClassName();*/ "jmri.jmrit.beantable.SHBeanTableDataModel";}


/*public*/ void SHBeanTableDataModel::clickOn(NamedBean* t) {
    int oldState = ((SignalHead*)t->self())->getAppearance();
    int newState = 99;
    QVector<int> stateList = ((SignalHead*)t->self())->getValidStates();
    for (int i = 0; i < stateList.length(); i++) {
        if (oldState == stateList[i] ) {
            if (i < stateList.length()-1) {
                newState = stateList[i+1];
                break;
            } else {
                newState = stateList[0];
                break;
            }
        }
    }
    if (newState==99){

        if (stateList.length()==0){
            newState=SignalHead::DARK;
            log->warn("New signal state not found so setting to Dark " + t->getDisplayName());
        }
        else{
            newState=stateList[0];
            log->warn("New signal state not found so setting to the first available " + t->getDisplayName());
        }
    }
    log->debug("was "+QString::number(oldState) +" becomes "+QString::number(newState));
   ((SignalHead*)t->self())->setAppearance(newState);
    fireTableDataChanged();

}

/*public*/ QPushButton* SHBeanTableDataModel::configureButton() {
    return new QPushButton(tr("Yellow"));
}

/*public*/ bool SHBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
    if (e->getPropertyName().indexOf("Lit")>=0
        || e->getPropertyName().indexOf("Held")>=0
        || e->getPropertyName().indexOf("ValidStatesChanged")>=0)
     return true;
    else return BeanTableDataModel::matchPropertyName(e);
}

/*protected*/ QString SHBeanTableDataModel::getBeanType(){
    return tr("BeanNameSignalHead");
}
//    };



/*protected*/ void SignalHeadTableAction::setTitle() {
    f->setTitle(f->tr("Signal Table"));
}

/*protected*/ QString SignalHeadTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SignalHeadTable";
}

/*private*/ int SignalHeadTableAction::turnoutStateFromBox(QComboBox* box)
{
     QString mode =  box->currentText();
     int result = StringUtil::getStateFromName(mode, turnoutStateValues.toVector(), turnoutStates.toVector());

     if (result < 0) {
         log->warn("unexpected mode string in turnoutMode: " + mode);
         throw new IllegalArgumentException();
     }
     return result;
}

/*private*/ void SignalHeadTableAction::setTurnoutStateInBox(QComboBox* box, int state, QList<int> iTurnoutStates) {
     if (state == iTurnoutStates[0]) {
         box->setCurrentIndex(0);
     } else if (state == iTurnoutStates[1]) {
         box->setCurrentIndex(1);
     } else {
         log->error("unexpected turnout state value: " + QString::number(state));
     }
}

int SignalHeadTableAction::signalStateFromBox(QComboBox* box) {
 QString mode = box->currentText();
 int result = StringUtil::getStateFromName(mode, signalStatesValues, signalStates);

 if (result<0) {
     log->warn("unexpected mode string in signalMode: "+mode);
     throw  IllegalArgumentException();
 }
 return result;
}

void SignalHeadTableAction::setSignalStateInBox (QComboBox* box, int state) {

    switch(state){
        case SignalHead::DARK : box->setCurrentIndex(0);
                                break;
        case SignalHead::RED : box->setCurrentIndex(1);
                                break;
        case SignalHead::LUNAR : box->setCurrentIndex(2);
                                break;
        case SignalHead::YELLOW : box->setCurrentIndex(3);
                                break;
        case SignalHead::GREEN : box->setCurrentIndex(4);
                                break;
        case SignalHead::FLASHRED : box->setCurrentIndex(5);
                                break;
        case SignalHead::FLASHLUNAR : box->setCurrentIndex(6);
                                break;
        case SignalHead::FLASHYELLOW : box->setCurrentIndex(7);
                                break;
        case SignalHead::FLASHGREEN : box->setCurrentIndex(8);
                                break;
        default : log->error("unexpected Signal state value: "+QString::number(state));
    }

    /*if (state==iSignalStates[0]) box->setCurrentIndex(0);
    else if (state==iSignalStates[1]) box->setCurrentIndex(1);
    else log->error("unexpected  Signal state value: "+state);*/
}

int SignalHeadTableAction::signalheadTypeFromBox(QComboBox* box) {
    QString mode = box->currentText();
    int result = StringUtil::getStateFromName(mode, signalheadTypeValues.toVector(), signalheadTypes.toVector());

    if (result<0) {
        log->warn("unexpected mode string in signalhead aspect type: "+mode);
        throw  IllegalArgumentException();
    }
    return result;
}

void SignalHeadTableAction::setSignalheadTypeInBox (QComboBox* box, int state, QList<int>iSignalheadTypes) {
    if (state==iSignalheadTypes[0]) box->setCurrentIndex(0);
    else if (state==iSignalheadTypes[1]) box->setCurrentIndex(1);
    else if (state==iSignalheadTypes[2]) box->setCurrentIndex(2);
    else if (state==iSignalheadTypes[3]) box->setCurrentIndex(3);
    else log->error("unexpected signalhead type value: "+state);
}

int SignalHeadTableAction::ukSignalAspectsFromBox(QComboBox* box){
    //String mode = (String)box.currentText();
    if(box->currentIndex()==0) return 2;
    else if(box->currentIndex()==1) return 3;
    else if(box->currentIndex()==2) return 4;
    else {
        log->warn("unexpected aspect" + box->currentText());
        throw new IllegalArgumentException();
    }
}

void SignalHeadTableAction::setUkSignalAspectsFromBox(QComboBox* box, int val){
    if (val==2) box->setCurrentIndex(0);
    else if (val==3) box->setCurrentIndex(1);
    else if (val==4) box->setCurrentIndex(2);
    else log->error("Unexpected Signal Aspect" + QString::number(val));
}

QString SignalHeadTableAction::ukSignalTypeFromBox(QComboBox* box){
    //String mode = (String)box.currentText();
    if(box->currentIndex()==0) return "Home";
    else if(box->currentIndex()==1) return "Distant";
    else {
        log->warn("unexpected aspect" + box->currentText());
        throw new IllegalArgumentException();
    }
}

void SignalHeadTableAction::setUkSignalType(QComboBox* box, QString val){
    if (val ==(ukSignalType.at(0))) box->setCurrentIndex(0);
    else if (val ==(ukSignalType.at(1))) box->setCurrentIndex(1);
    else log->error("Unexpected Signal Type " +val);
}

/**
 * Provide GUI for adding a new SignalHead
 * <P>
 * Because there are multiple options,
 * each of which requires different inputs,
 * we directly manipulate which parts of the
 * GUI are displayed when the selected type is
 * changed.
 */
//@Override
/*protected*/ void SignalHeadTableAction::addPressed(JActionEvent* /*e*/)
{
 if (addFrame==nullptr)
 {
  QObjectList* list = InstanceManager::getList("CommandStation");
#if 1
  foreach(QObject* obj, *list)
  {
    if(obj!=NULL){
     if(qobject_cast<SlotManager*>(obj))
     {
      SlotManager* station = (SlotManager*)obj;
      QString user_name = station->getUserName();
      prefixBox->addItem(user_name);
      continue;
     }
     CommandStation* station = (CommandStation*) obj;
     QString user_name = station->getUserName();
     prefixBox->addItem(user_name);
    }
  }
#endif
  dccSignalPanel();


  to1 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  to2 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  to3 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  to4 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  to5 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  to6 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  to7 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  addFrame = new JmriJFrameX(tr("Add New Signal"), false, true);
  addFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalAddEdit", true);
  //BorderLayout* contentPaneLayout;
  QVBoxLayout* contentPaneLayout;
  addFrame->getContentPane()->setLayout(contentPaneLayout = new QVBoxLayout());

  JPanel* panelHeader = new JPanel();
  QVBoxLayout* panelHeaderVLayout = new QVBoxLayout();
  panelHeader->setLayout(panelHeaderVLayout);
  panelHeaderVLayout->addWidget(typeBox = new JComboBox(QStringList{
            acelaAspect, dccSignalDecoder, doubleTurnout, lsDec, mergSignalDriver, quadOutput,
            singleTurnout, se8c4Aspect, tripleTurnout, virtualHead
        }));

    //If no DCC Comand station is found remove the DCC Signal Decoder option.
    if( prefixBox->count()==0){
        typeBox->removeItem(typeBox->findText(dccSignalDecoder));
    }
//        if (jmri.jmrix.grapevine.ActiveFlag.isActive()) type Box->addItem(grapevine);
//        type Box->addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                typeChanged();
//            }
//        });
  connect(typeBox, &JComboBox::currentTextChanged, [=] {typeChanged();});

  JPanel* p = new JPanel();
  p->setLayout(new FlowLayout());
  p->layout()->addWidget(prefixBoxLabel);
  p->layout()->addWidget(prefixBox);
  panelHeader->layout()->addWidget(p);

  p = new JPanel();
  p->setLayout(new FlowLayout());
  p->layout()->addWidget(systemNameLabel);
  systemNameLabel->setLabelFor(systemNameTextField);
  p->layout()->addWidget(systemNameTextField);
  systemNameTextField->setToolTip(tr("Enter system name for this new Signal Head, e.g. LH12"));
  p->layout()->addWidget(dccOffSetAddress);
  dccOffSetAddress->setToolTip(tr("When checked, uses an alternative DCC addressing scheme."));
  p->layout()->addWidget(dccPacketSendCount);
  dccPacketSendCountSpinner->setModel(new SpinnerNumberModel(3, 1, 4, 1));
  p->layout()->addWidget(dccPacketSendCountSpinner);
  dccPacketSendCountSpinner->setToolTip(tr("The number of times that the Command Station will send the DCC packet to the output."));
  panelHeader->layout()->addWidget(p);

  {
  JPanel* p = new JPanel();
  p->setLayout(new FlowLayout());
  p->layout()->addWidget(userNameLabel);
  userNameLabel->setLabelFor(userNameTextField);
  p->layout()->addWidget(userNameTextField);
  userNameTextField->setToolTip(tr("Enter user name for this new Signal Head, e.g. Mast 1 Head 2"));
  panelHeader->layout()->addWidget(p);
  }

  contentPaneLayout->addWidget(panelHeader, 0, Qt::AlignTop);//BorderLayout::North);
  QScrollArea* scrollPane = new QScrollArea(/*centralWidget*/);
  scrollPane->setWidgetResizable(true);
  QWidget* panelCentre = new QWidget();
  QVBoxLayout* panelCentreVLayout = new QVBoxLayout();
  panelCentre->setLayout(panelCentreVLayout);
    //type Box->setCurrentIndex(7);
    //typeChanged();
    // create seven boxes for input information, and put into pane

  v1Panel = new JPanel();
  QVBoxLayout* v1PanelVLayout;
  v1Panel->setLayout(v1PanelVLayout = new QVBoxLayout());
  v1PanelVLayout->addWidget(ato1TextField);
  v1PanelVLayout->addWidget(to1,0, Qt::AlignCenter);
  v1PanelVLayout->addWidget(s1Box,0, Qt::AlignCenter);
  v1PanelVLayout->addWidget(msaBox,0, Qt::AlignCenter);
  v1Panel->setBorder(v1Border);
  QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(v1Panel->sizePolicy().hasHeightForWidth());
  v1Panel->setSizePolicy(sizePolicy);
  panelCentreVLayout->addWidget(v1Panel);

  v2Panel = new JPanel();
  QVBoxLayout* v2PanelLayout;
  v2Panel->setLayout(v2PanelLayout = new QVBoxLayout());
  v2PanelLayout->addWidget(to2,0, Qt::AlignCenter);
  v2PanelLayout->addWidget(s2Box,0, Qt::AlignCenter);
  v2PanelLayout->addWidget(s2aBox,0, Qt::AlignCenter);
  v2PanelLayout->addWidget(mstBox,0, Qt::AlignCenter);
  v2Panel->setBorder(v2Border);
  panelCentreVLayout->addWidget(v2Panel);

  v3Panel = new JPanel();
  QVBoxLayout* v3PanelLayout;
  v3Panel->setLayout(v3PanelLayout = new QVBoxLayout());
  v3PanelLayout->addWidget(to3,0, Qt::AlignCenter);
  v3PanelLayout->addWidget(s3Box,0, Qt::AlignCenter);
  v3PanelLayout->addWidget(s3aBox,0, Qt::AlignCenter);
  v3Panel->setBorder(v3Border);
  panelCentreVLayout->addWidget(v3Panel);

  v4Panel = new JPanel();
  QVBoxLayout* v4PanelLayout;
  v4Panel->setLayout(v4PanelLayout = new QVBoxLayout());
  v4PanelLayout->addWidget(to4,0, Qt::AlignCenter);
  v4PanelLayout->addWidget(s4Box,0, Qt::AlignCenter);
  v4Panel->setBorder(v4Border);
  panelCentreVLayout->addWidget(v4Panel);

  v5Panel = new JPanel();
  QVBoxLayout* v5PanelLayout;
  v5Panel->setLayout(v5PanelLayout = new QVBoxLayout());
  v5PanelLayout->addWidget(to5,0, Qt::AlignCenter);
  v5PanelLayout->addWidget(s5Box,0, Qt::AlignCenter);
  v5Panel->setBorder(v5Border);
  panelCentreVLayout->addWidget(v5Panel);

  v6Panel = new JPanel();
  QVBoxLayout* v6PanelLayout;
  v6Panel->setLayout(v6PanelLayout = new QVBoxLayout());
  v6PanelLayout->addWidget(to6,0, Qt::AlignCenter);
  v6PanelLayout->addWidget(s6Box,0, Qt::AlignCenter);
  v6Panel->setBorder(v6Border);
  panelCentreVLayout->addWidget(v6Panel);

  v7Panel = new JPanel();
  QVBoxLayout* v7PanelLayout;
  v7Panel->setLayout(v7PanelLayout = new QVBoxLayout());
    //v7Panel->layout()->addWidget(v7Label);
  v7PanelLayout->addWidget(to7,0, Qt::AlignCenter);
  v7PanelLayout->addWidget(s7Box,0, Qt::AlignCenter);
  v7Panel->setBorder(v7Border);
  panelCentreVLayout->addWidget(v7Panel);

  {
   JPanel* p = new JPanel();
   p->setLayout(defaultFlow);
   p->layout()->addWidget(vtLabel);
   p->layout()->addWidget(stBox);
   panelCentreVLayout->addWidget(p);
  }

  scrollPane->setWidget(panelCentre);
    //addFrame.getContentPane().add(scrollPane, BorderLayout.CENTER);
  contentPaneLayout->addWidget(scrollPane, 1, Qt::AlignCenter);//BorderLayout::Center);

  // buttons at bottom of panel
  QWidget* panelBottom = new QWidget();
  panelBottom->setLayout(new FlowLayout(panelBottom/*, BoxLayout.Y_AXIS*/));
  // Cancel button
  JButton* cancelNew = new JButton(tr("Cancel"));
  panelBottom->layout()->addWidget(cancelNew);
  connect(cancelNew, &JButton::clicked, [=]{cancelNewPressed();});
  QPushButton* ok;
  panelBottom->layout()->addWidget(ok = new QPushButton(tr("OK")));
//        ok.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                okPressed(e);
//            }
//        });
  connect(ok, SIGNAL(clicked()), this, SLOT(okPressed()));

    //addFrame.getContentPane().add(panelBottom, BorderLayout.PAGE_END);
  contentPaneLayout->addWidget(panelBottom, 0, Qt::AlignBottom);//BorderLayout::South);
 }
 else {
   // clear older entries
   systemNameTextField->setText("");
   userNameTextField->setText("");
  }
  typeBox->setSelectedIndex(2);  // force GUI status consistent. Default set to Double Head type

  addFrame->setEscapeKeyClosesWindow(true);
  addFrame->pack();
  addFrame->setVisible(true);
}

void SignalHeadTableAction::hideAllOptions()
{
 ato1TextField->setVisible(false);
 prefixBoxLabel->setVisible(false);
 prefixBox->setVisible(false);
 systemNameLabel->setVisible(false);
 systemNameTextField->setVisible(false);
 to1->setVisible(false);
 ato1TextField->setVisible(false);
 s1Box->setVisible(false);
 v1Panel->setVisible(false);
 v2Panel->setVisible(false);
 to2->setVisible(false);
 s2Box->setVisible(false);
 s2aBox->setVisible(false);
 v3Panel->setVisible(false);
 to3->setVisible(false);
 s3Box->setVisible(false);
 s3aBox->setVisible(false);
 v4Panel->setVisible(false);
 to4->setVisible(false);
 s4Box->setVisible(false);
 v5Panel->setVisible(false);
 to5->setVisible(false);
 s5Box->setVisible(false);
 v6Panel->setVisible(false);
 to6->setVisible(false);
 s6Box->setVisible(false);
 v7Panel->setVisible(false);
 to7->setVisible(false);
 vtLabel->setVisible(false);
 stBox->setVisible(false);
 mstBox->setVisible(false);
 msaBox->setVisible(false);
}

void SignalHeadTableAction::typeChanged()
{ // SLOT[]
 hideAllOptions();
 if (se8c4Aspect ==(typeBox->currentText()))
 {
  handleSE8cTypeChanged();
 }
 else
#if 1
 if (grapevine ==(typeBox->currentText()))
 {  //Need to see how this works with username
  systemNameLabel->setText(tr("System Name:"));
  systemNameLabel->setVisible(true);
  systemNameTextField->setVisible(true);
  userNameLabel->setText(tr("User Name:"));
  userNameLabel->setVisible(true);
  userNameTextField->setVisible(true);
 } else
 if (acelaAspect ==(typeBox->currentText()))
 {
  userNameLabel->setText(tr("User Name:"));
  userNameLabel->setVisible(true);
  userNameTextField->setVisible(true);
  //v1Label->setText(tr("Signalhead Number:"));
  v1Border->setTitle(tr("Signalhead Number:"));
  v1Panel->setVisible(true);
  ato1TextField->setVisible(true);
  vtLabel->setText(tr("LabelAspectType"));
  vtLabel->setVisible(true);
  stBox->setVisible(true);
 } else
#endif
 if (quadOutput ==(typeBox->currentText()))
 {
  systemNameLabel->setText(tr("System Name:"));
  systemNameLabel->setVisible(true);
  systemNameTextField->setVisible(true);
  userNameLabel->setText(tr("User Name:"));
  v1Border->setTitle(tr("Green output number:"));
  to1->setVisible(true);
  v1Panel->setVisible(true);
  v2Border->setTitle(tr("Yellow output number:"));
  v2Panel->setVisible(true);
  to2->setVisible(true);
  v3Border->setTitle(tr("Red output number:"));
  v3Panel->setVisible(true);
  to3->setVisible(true);
  v4Border->setTitle(tr("Lunar Turnout Number"));
  v4Panel->setVisible(true);
  to4->setVisible(true);
  } else if (tripleTurnout ==(typeBox->currentText()))
 {
  systemNameLabel->setText(tr("System Name:"));
  systemNameLabel->setVisible(true);
  systemNameTextField->setVisible(true);
  userNameLabel->setText(tr("User Name:"));
  v1Border->setTitle(tr("Green output number:"));
  v1Panel->setVisible(true);
  to1->setVisible(true);
  v2Border->setTitle(tr("Yellow output number:"));
  v2Panel->setVisible(true);
  to2->setVisible(true);
  v3Border->setTitle(tr("Red output number:"));
  v3Panel->setVisible(true);
  to3->setVisible(true);
  }
 else if (tripleOutput == (typeBox->currentText()))
 {
      systemNameLabel->setText(tr("System Name"));
      systemNameTextField->setToolTip(tr("Enter system name for this new Signal Head, e.g. LH12"));
      systemNameLabel->setVisible(true);
      systemNameTextField->setVisible(true);
      userNameLabel->setText(tr("User Name"));
      v1Border->setTitle(tr("Green Turnout Number"));
      v1Panel->setVisible(true);
      to1->setVisible(true);
      v2Border->setTitle(tr("Blue Turnout Number"));
      v2Panel->setVisible(true);
      to2->setVisible(true);
      v3Border->setTitle(tr("Red Turnout Number"));
      v3Panel->setVisible(true);
      to3->setVisible(true);
  }
 else
  if (doubleTurnout ==(typeBox->currentText()))
  {
   systemNameLabel->setText(tr("System Name:"));
   systemNameLabel->setVisible(true);
   systemNameTextField->setVisible(true);
   userNameLabel->setText(tr("User Name:"));
   v1Border->setTitle(tr("Green output number:"));
   v1Panel->setVisible(true);
   to1->setVisible(true);
   v2Border->setTitle(tr("Red output number:"));
   v2Panel->setVisible(true);
   to2->setVisible(true);
  } else
  if (singleTurnout ==(typeBox->currentText()))
  {
   systemNameLabel->setText(tr("System Name:"));
   systemNameLabel->setVisible(true);
   systemNameTextField->setVisible(true);
   userNameLabel->setText(tr("User Name:"));
   v1Border->setTitle(tr("Green output number:"));
   v1Panel->setVisible(true);
   to1->setVisible(true);
   v2Border->setTitle(tr("Turnout Thrown Appearance"));
   v2Panel->setVisible(true);
   s2aBox->setVisible(true);
   v3Border->setTitle(tr("Turnout Closed Appearance"));
   s3aBox->setVisible(true);
   v3Panel->setVisible(true);
  } else
  if (virtualHead ==(typeBox->currentText()))
  {
   systemNameLabel->setText(tr("System Name:"));
         systemNameLabel->setVisible(true);
         systemNameTextField->setVisible(true);
        userNameLabel->setText(tr("User Name:"));
  } else
  if (lsDec ==(typeBox->currentText()))
  {
         systemNameLabel->setText(tr("System Name:"));
         systemNameLabel->setVisible(true);
         systemNameTextField->setVisible(true);
        userNameLabel->setText(tr("User Name:"));
        v1Border->setTitle(tr("Green output number:"));
        v1Panel->setVisible(true);
        to1->setVisible(true);
        s1Box->setVisible(true);
        v2Border->setTitle(tr("Yellow output number:"));
        v2Panel->setVisible(true);
        to2->setVisible(true);
        s2Box->setVisible(true);
        v3Border->setTitle(tr("Red output number:"));
        v3Panel->setVisible(true);
        to3->setVisible(true);
        s3Box->setVisible(true);
        s3aBox->setVisible(false);
        v4Border->setTitle(tr("Flash Green output number"));
        v4Panel->setVisible(true);
        to4->setVisible(true);
        s4Box->setVisible(true);
        v5Border->setTitle(tr("Flash Yellow output number"));
        v5Panel->setVisible(true);
        to5->setVisible(true);
        s5Box->setVisible(true);
        v6Border->setTitle(tr("Flash Red output number"));
        v6Panel->setVisible(true);
        to6->setVisible(true);
        s6Box->setVisible(true);
        v7Border->setTitle(tr("Dark output number"));
        v7Panel->setVisible(true);
        to7->setVisible(true);
        s7Box->setVisible(true);
    }
  else if (dccSignalDecoder ==(typeBox->currentText())) {
          // systemNameLabel->setText(tr("System Name:"));
           systemNameLabel->setText("Hardware Address");
           systemNameLabel->setVisible(true);
           systemNameTextField->setVisible(true);
           prefixBox->setVisible(true);
           prefixBoxLabel->setVisible(true);
          userNameLabel->setText(tr("LabelUserName"));
    }
    else
    if (mergSignalDriver ==(typeBox->currentText())) {
         systemNameLabel->setText(tr("System Name:"));
         systemNameLabel->setVisible(true);
         systemNameTextField->setVisible(true);
        userNameLabel->setText(tr("User Name:"));
        v1Border->setTitle("Aspects");
        v1Panel->setVisible(true);
        v2Border->setTitle("Home");
        v2Panel->setVisible(true);
        mstBox->setVisible(true);
        msaBox->setVisible(true);
        setUkSignalAspectsFromBox(msaBox, 2);
        v3Border->setTitle("Input1");
        v3Panel->setVisible(true);
        to3->setVisible(true);
        v4Border->setTitle("Input2");
        v5Border->setTitle("Input3");
//        msaBox->addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(msaBox, &QComboBox::currentTextChanged, [=]{
                ukAspectChange(false);
//            }
        });

 }
    else
 log->error(tr("Unexpected type in typeChanged: ")+typeBox->currentText());

 // make sure size OK
 addFrame->pack();
}

bool SignalHeadTableAction::checkBeforeCreating(QString sysName)
{
 QString sName;
 if (dccSignalDecoder ==(typeBox->currentText()))
 {
  sName=sysName;
  bool bOK;
  sysName.mid(sysName.indexOf("$")+1, sysName.length()).toInt(&bOK);
  if(!bOK)
  {
//        } catch (Exception* ex){
   QString msg = tr("Value entered into \"%1\" must be a whole number").arg("Hardware Address");
   JOptionPane::showMessageDialog(addFrame, msg,
           tr("WarningTitle"), JOptionPane::ERROR_MESSAGE);
    return false;
  }
 }
 else {
        sName = sysName.toUpper();
        if ( (sName.length()<3) || (sName.mid(1,1) !=("H")) ) {
          QString msg = tr("Cannot add signal head because \" %1 \" is not a valid system name, for example, LH5, GH88, IH41.").arg(sName);
            JOptionPane::showMessageDialog(addFrame, msg,
                    tr("WarningTitle"), JOptionPane::ERROR_MESSAGE);
            return false;
        }
    }
    // check for pre-existing signal head with same system name
    SignalHead* s = (SignalHead*)qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(sName)->self();
    // return true if signal head does not exist
    if (s==nullptr){
        //Need to check that the Systemname doesn't already exists as a UserName
        NamedBean* nB = static_cast<AbstractSignalHeadManager*>( InstanceManager::getDefault("SignalHeadManager"))->getByUserName(sName);
        if (nB!=nullptr){
            log->error("System name is not unique " + sName + " It already exists as a User name");
            QString msg = tr("User Name \" %1 \" has already been used as a User Name.").arg(sName) ;
            JOptionPane::showMessageDialog(editFrame, msg,
                        tr("WarningTitle"),
                            JOptionPane::ERROR_MESSAGE);
            return false;
        }
        return true;
    }
    // inform the user if signal head already exists, and return false so creation can be bypassed
    log->warn("Attempt to create signal with duplicate system name "+sName);
    QString msg =  tr("Cannot add because \" %1 \" already exists. To replace an existing signal head, delete it first.").arg(sName);
    JOptionPane::showMessageDialog(addFrame, msg,
            tr("Warning"), JOptionPane::ERROR_MESSAGE);
    return false;
}
/*public*/ bool SignalHeadTableAction::checkIntegerOnly(QString s) {
    QString allowed = "0123456789";
    bool result=true;
    //String result = "";
    for ( int i = 0; i < s.length(); i++ ) {
        if ( allowed.indexOf(s.at(i)) == -1 )
            result=false;
    }
    return result;
}
void SignalHeadTableAction::addTurnoutMessage(QString s1, QString s2) {
    log->warn("Could not provide turnout "+s2);
    QString msg = tr("Cannot add signal head because could not provide \" %1 \" - \" %2 \".").arg(s1).arg(s2);
    JOptionPane::showMessageDialog(addFrame, msg,
            tr("WarningTitle"), JOptionPane::ERROR_MESSAGE);
}

//@TODO We could do with checking the to make sure that the user has entered a turnout into a turnout field if it has been presented. Otherwise an error is recorded in the console window
void SignalHeadTableAction::okPressed(JActionEvent * /*e*/)
{
 if (!checkUserName(userNameTextField->text()))
  return;
 SignalHead* s;
 if (se8c4Aspect ==(typeBox->currentText()))
 {
  handleSE8cOkPressed();
 }
 else if (acelaAspect ==(typeBox->currentText()))
 {
  QString inputusername = userNameTextField->text();
  QString inputsysname =  ato1TextField->text().toUpper();
  int headnumber;
  //int aspecttype;

  if (inputsysname.length() == 0)
  {
   log->warn("must supply a signalhead number (i.e. AH23)");
   return;
  }
  if(inputsysname.length()>2)
  {
   if (inputsysname.mid(0,2) ==("AH"))
    headnumber = inputsysname.mid(2,inputsysname.length()).toInt();
   else if(checkIntegerOnly(inputsysname))
    headnumber = inputsysname.toInt();
   else
   {
    QString msg = tr("Skipping creation of acela signal head because \" %1 \" is not a number or does not start with LT .").arg( ato1TextField->text() );
    JOptionPane::showMessageDialog(addFrame, msg,
        tr("Warning"), JOptionPane::ERROR_MESSAGE);
    return;
   }
  }
  else
   headnumber = inputsysname.toInt();
  if (checkBeforeCreating("AH"+QString::number(headnumber)))
  {
   if (inputusername.length() == 0)
   {
    s = new AcelaSignalHead("AH"+QString::number(headnumber),(AcelaSystemConnectionMemo*) InstanceManager::getDefault("AcelaSystemConnectionMemo"));
   }
   else
   {
    s = new AcelaSignalHead("AH"+QString::number(headnumber), inputusername,(AcelaSystemConnectionMemo*)InstanceManager::getDefault("AcelaSystemConnectionMemo"));
   }
   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }

  int st = signalheadTypeFromBox(stBox);
  //This bit returns NULL i think, will need to check through
  AcelaNode* sh = AcelaAddress::getNodeFromSystemName("AH"+QString::number(headnumber),(AcelaSystemConnectionMemo*) InstanceManager::getDefault("AcelaSystemConnectionMemo"));

  switch (st)
  {
  case 1: sh->setOutputSignalHeadType(headnumber, AcelaNode::DOUBLE);
   break;
  case 2: sh->setOutputSignalHeadType(headnumber, AcelaNode::TRIPLE); break;
  case 3: sh->setOutputSignalHeadType(headnumber, AcelaNode::BPOLAR); break;
  case 4: sh->setOutputSignalHeadType(headnumber, AcelaNode::WIGWAG); break;
  default:
   log->warn("Unexpected Acela Aspect type: "+QString::number(st));
                sh->setOutputSignalHeadType(headnumber, AcelaNode::UKNOWN); break;  // default to triple
  }
 }
#if 0
 else if (grapevine ==(typeBox->currentText()))
 {
  // the turnout field must hold a GH system name
  if ( systemNameTextField->text().length() == 0)
  {
   log->warn("must supply a signalhead number (i.e. GH23)");
   return;
  }
  QString inputsysname =  systemNameTextField->text().toUpper();
  if (inputsysname.mid(0,2) !=("GH"))
  {
   log->warn("skipping creation of signal, "+inputsysname+" does not start with GH");
   QString msg = tr("Skipping creation of Grapvine signal head  because \" %1 \" does not start with GH.").arg( inputsysname );
   JOptionPane::showMessageDialog(addFrame, msg,
       tr("Warning"), JOptionPane::ERROR_MESSAGE);
   return;
  }
  if (checkBeforeCreating(inputsysname))
  {
   s = new SerialSignalHead(inputsysname,userName->text());
   static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(s);
  }
 }
#endif
 else
  if (quadOutput ==(typeBox->currentText()))
 {
  if (checkBeforeCreating( systemNameTextField->text()))
  {
   Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" +  systemNameTextField->text() + ":Green");
   Turnout* t2 = getTurnoutFromPanel(to2, "SignalHead:" +  systemNameTextField->text() + ":Yellow");
   Turnout* t3 = getTurnoutFromPanel(to3, "SignalHead:" +  systemNameTextField->text() + ":Red");
   Turnout* t4 = getTurnoutFromPanel(to4, "SignalHead:" +  systemNameTextField->text() + ":Lunar");

   if (t1==nullptr) addTurnoutMessage(v1Panel->getTitle(), to1->getDisplayName());
   if (t2==nullptr) addTurnoutMessage(v2Panel->getTitle(), to2->getDisplayName());
   if (t3==nullptr) addTurnoutMessage(v3Panel->getTitle(), to3->getDisplayName());
   if (t4==nullptr) addTurnoutMessage(v4Panel->getTitle(), to4->getDisplayName());
   if (t4==nullptr || t3==nullptr || t2==nullptr || t1==nullptr)
   {
    log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
    return;
   }
   s = (SignalHead*) new QuadOutputSignalHead( systemNameTextField->text(),userNameTextField->text(),
   nbhm->getNamedBeanHandle(to1->getDisplayName(),t1),
   nbhm->getNamedBeanHandle(to2->getDisplayName(),t2),
   nbhm->getNamedBeanHandle(to3->getDisplayName(),t3),
   nbhm->getNamedBeanHandle(to4->getDisplayName(),t4));
   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }
 }
 else if (tripleTurnout ==(typeBox->currentText()))
 {
  if (checkBeforeCreating( systemNameTextField->text()))
  {
   Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" +  systemNameTextField->text() + ":Green");
   Turnout* t2 = getTurnoutFromPanel(to2, "SignalHead:" +  systemNameTextField->text() + ":Yellow");
   Turnout* t3 = getTurnoutFromPanel(to3, "SignalHead:" +  systemNameTextField->text() + ":Red");

   if (t1==nullptr) addTurnoutMessage(v1Panel->getTitle(), to1->getDisplayName());
   if (t2==nullptr) addTurnoutMessage(v2Panel->getTitle(), to2->getDisplayName());
   if (t3==nullptr) addTurnoutMessage(v3Panel->getTitle(), to3->getDisplayName());
   if (t3==nullptr || t2==nullptr || t1==nullptr)
   {
    log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
    return;
   }

   s = (SignalHead*) new TripleTurnoutSignalHead( systemNameTextField->text(),userNameTextField->text(),nbhm->getNamedBeanHandle(to1->getDisplayName(),t1),
                nbhm->getNamedBeanHandle(to2->getDisplayName(),t2),
                nbhm->getNamedBeanHandle(to3->getDisplayName(),t3));

   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }
 }
 else if (tripleOutput == (typeBox->currentText()))
 {
      if (checkBeforeCreating(systemNameTextField->text())) {
          Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" + systemNameTextField->text() + ":Green");
          Turnout* t2 = getTurnoutFromPanel(to2, "SignalHead:" + systemNameTextField->text() + ":Blue");
          Turnout* t3 = getTurnoutFromPanel(to3, "SignalHead:" + systemNameTextField->text() + ":Red");

          if (t1 == nullptr) {
              addTurnoutMessage(v1Border->getTitle(), to1->getDisplayName());
          }
          if (t2 == nullptr) {
              addTurnoutMessage(v2Border->getTitle(), to2->getDisplayName());
          }
          if (t3 == nullptr) {
              addTurnoutMessage(v3Border->getTitle(), to3->getDisplayName());
          }
          if (t3 == nullptr || t2 == nullptr || t1 == nullptr) {
              log->warn("skipping creation of signal " + systemNameTextField->text() + " due to error");
              return;
          }

          s = new TripleOutputSignalHead(systemNameTextField->text(), userNameTextField->text(),
                  nbhm->getNamedBeanHandle(to1->getDisplayName(), t1),
                  nbhm->getNamedBeanHandle(to2->getDisplayName(), t2),
                  nbhm->getNamedBeanHandle(to3->getDisplayName(), t3));

          qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
      }
  }
 else if (doubleTurnout ==(typeBox->currentText()))
 {
  if (checkBeforeCreating( systemNameTextField->text()))
  {
   Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" +  systemNameTextField->text() + ":Green");
   Turnout* t2 = getTurnoutFromPanel(to2, "SignalHead:" +  systemNameTextField->text() + ":Red");

   if (t1==nullptr) addTurnoutMessage(v1Panel->getTitle(), to1->getDisplayName());
   if (t2==nullptr) addTurnoutMessage(v1Panel->getTitle(), to2->getDisplayName());
   if (t2==nullptr || t1==nullptr)
   {
    log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
        return;
   }

   s = (SignalHead*)new DoubleTurnoutSignalHead( systemNameTextField->text(),userNameTextField->text(),
   nbhm->getNamedBeanHandle(to1->getDisplayName(),t1),
   nbhm->getNamedBeanHandle(to2->getDisplayName(),t2));
   s->setUserName(userNameTextField->text());
   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }
 }

  else if (singleTurnout ==(typeBox->currentText()))
  {
  if (checkBeforeCreating( systemNameTextField->text()))
  {
   Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" +  systemNameTextField->text() + ":" + s2aBox->currentText() + ":" + s3aBox->currentText());

   int on = signalStateFromBox(s2aBox);
   int off = signalStateFromBox(s3aBox);
   if (t1==nullptr) addTurnoutMessage(v1Panel->getTitle(), to1->getDisplayName());
   if (t1==nullptr)
   {
    log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
    return;
   }

   s = (SignalHead*)new SingleTurnoutSignalHead( systemNameTextField->text(), userNameTextField->text(), nbhm->getNamedBeanHandle(t1->getDisplayName(),t1), on, off);
   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }
 }
 else if (virtualHead ==(typeBox->currentText()))
 {
  if (checkBeforeCreating( systemNameTextField->text()))
  {
   s = (SignalHead*)new VirtualSignalHead( systemNameTextField->text(),userNameTextField->text());
   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }
 }
 else if (lsDec ==(typeBox->currentText()))
 {
  if (checkBeforeCreating( systemNameTextField->text()))
  {
   Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" +  systemNameTextField->text() + ":Green");
   Turnout* t2 = getTurnoutFromPanel(to2, "SignalHead:" +  systemNameTextField->text() + ":Yellow");
   Turnout* t3 = getTurnoutFromPanel(to3, "SignalHead:" +  systemNameTextField->text() + ":Red");
   Turnout* t4 = getTurnoutFromPanel(to4, "SignalHead:" +  systemNameTextField->text() + ":FlashGreen");
   Turnout* t5 = getTurnoutFromPanel(to5, "SignalHead:" +  systemNameTextField->text() + ":FlashYellow");
   Turnout* t6 = getTurnoutFromPanel(to6, "SignalHead:" +  systemNameTextField->text() + ":FlashRed");
   Turnout* t7 = getTurnoutFromPanel(to7, "SignalHead:" +  systemNameTextField->text() + ":Dark");

   int s1 = turnoutStateFromBox(s1Box);
   int s2 = turnoutStateFromBox(s2Box);
   int s3 = turnoutStateFromBox(s3Box);
   int s4 = turnoutStateFromBox(s4Box);
   int s5 = turnoutStateFromBox(s5Box);
   int s6 = turnoutStateFromBox(s6Box);
   int s7 = turnoutStateFromBox(s7Box);

   if (t1==nullptr) addTurnoutMessage(v1Panel->getTitle(), to1->getDisplayName());
   if (t2==nullptr) addTurnoutMessage(v2Panel->getTitle(), to2->getDisplayName());
   if (t3==nullptr) addTurnoutMessage(v3Panel->getTitle(), to3->getDisplayName());
   if (t4==nullptr) addTurnoutMessage(v4Panel->getTitle(), to4->getDisplayName());
   if (t5==nullptr) addTurnoutMessage(v5Panel->getTitle(), to5->getDisplayName());
   if (t6==nullptr) addTurnoutMessage(v6Panel->getTitle(), to6->getDisplayName());
   if (t7==nullptr) addTurnoutMessage(v7Panel->getTitle(), to7->getDisplayName());
   if (t7==nullptr || t6==nullptr || t5==nullptr || t4==nullptr || t3==nullptr || t2==nullptr || t1==nullptr)
   {
    log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
    return;
   }

   s = (SignalHead*)new LsDecSignalHead( systemNameTextField->text(), nbhm->getNamedBeanHandle(t1->getDisplayName(),t1), s1, nbhm->getNamedBeanHandle(t2->getDisplayName(),t2), s2, nbhm->getNamedBeanHandle(t3->getDisplayName(),t3), s3, nbhm->getNamedBeanHandle(t4->getDisplayName(),t4), s4, nbhm->getNamedBeanHandle(t5->getDisplayName(),t5), s5, nbhm->getNamedBeanHandle(t6->getDisplayName(),t6), s6, nbhm->getNamedBeanHandle(t7->getDisplayName(),t7), s7);
   s->setUserName(userNameTextField->text());
   qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
  }
 }
 else if (dccSignalDecoder ==(typeBox->currentText()))
  {
   QString systemNameText = ConnectionNameFromSystemName::getPrefixFromName(prefixBox->currentText());
   //if we return a NULL string then we will set it to use internal, thus picking up the default command station at a later date.
   if(systemNameText ==("\0"))
    systemNameText = "I";
   systemNameText = systemNameText + "H$" +  systemNameTextField->text();

   if (checkBeforeCreating(systemNameText))
   {
    s = new DccSignalHead(systemNameText);
    s->setUserName(userNameTextField->text());
    qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
   }
  }
  else if (mergSignalDriver ==(typeBox->currentText()))
  {
   handleMergSignalDriverOkPressed();
  }
  else log->error("Unexpected type: "+typeBox->currentText());
}

void SignalHeadTableAction::handleSE8cOkPressed() {
    SignalHead* s;

    Turnout* t1 = getTurnoutFromPanel(to1, "SignalHead:" +  systemNameTextField->text() + ":low");
    Turnout* t2 = getTurnoutFromPanel(to2, "SignalHead:" +  systemNameTextField->text() + ":high");

    // check validity
    if (t1 != nullptr && t2 != nullptr) {
        // OK process
        s = (SignalHead*)new SE8cSignalHead(
            nbhm->getNamedBeanHandle(t1->getSystemName(), t1),
            nbhm->getNamedBeanHandle(t2->getSystemName(), t2),
            userNameTextField->text());
        qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);
    } else {
        // couldn't create turnouts, error
        QString msg = tr("Skipping creation of se8c4 signal head because \"%1\" is neither a number nor a valid Turnout name.").arg(to1->getDisplayName());
        JOptionPane::showMessageDialog(addFrame, msg,
            tr("Warning"), JOptionPane::ERROR_MESSAGE);
        return;
    }
}

void SignalHeadTableAction::handleSE8cTypeChanged() {
    hideAllOptions();
    userNameLabel->setText(tr("User Name"));
    //v1Border->setTitle(tr("Turnout Number"));
    v1Border->setTitle(tr("Turnout number:"));
    v1Panel->setVisible(true);
    to1->setVisible(true);
    v2Panel->setVisible(true);
    v2Border->setTitle(tr("LabelSecondNumber"));
    to2->setVisible(true);
}

void SignalHeadTableAction::handleSE8cEditSignal() {
    signalType->setText(se8c4Aspect);
    eSystemNameLabel->setText(tr("System Name"));
    eSysNameLabel->setText(curS->getSystemName());
    eUserNameLabel->setText(tr("User Name"));
    eUserNameLabel->setVisible(true);
    eUserName->setVisible(true);
    eUserName->setText(curS->getUserName());
    eSystemNameLabel->setText(tr("System Name"));
    eSysNameLabel->setText(curS->getSystemName());
    //eSysNameLabel->setVisible(true);
}

void SignalHeadTableAction::handleSE8cUpdatePressed() {
    // user name handled by common code; notthing else to change
}
#if 1
//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
void SignalHeadTableAction::handleMergSignalDriverOkPressed() {
    SignalHead* s;
    // Adding Merg Signal Driver.
    Turnout* t3 = nullptr;
    Turnout* t2 = nullptr;
    Turnout* t1 = nullptr;
    NamedBeanHandle<Turnout*>* nbt1 = nullptr;
    NamedBeanHandle<Turnout*>* nbt2 = nullptr;
    NamedBeanHandle<Turnout*>* nbt3 = nullptr;
    if (checkBeforeCreating( systemNameTextField->text())) {
        switch(ukSignalAspectsFromBox(msaBox)){
            case 4: t3 = getTurnoutFromPanel(to5, "SignalHead:" +  systemNameTextField->text() + ":Input3");
                    if (t3==nullptr) {
                        addTurnoutMessage(v5Panel->getTitle(), to5->getDisplayName());
                        log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
                        return;
                    } else
                        nbt3 = nbhm->getNamedBeanHandle(to5->getDisplayName(),t3);

                    // fall through
            case 3: t2 = getTurnoutFromPanel(to4, "SignalHead:" +  systemNameTextField->text() + ":Input2");
                    if (t2==nullptr) {
                        addTurnoutMessage(v4Panel->getTitle(), to4->getDisplayName());
                        log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
                        return;
                    } else
                        nbt2 = nbhm->getNamedBeanHandle(to4->getDisplayName(),t2);
                    // fall through
            case 2: t1 = getTurnoutFromPanel(to3, "SignalHead:" +  systemNameTextField->text() + ":Input1");
                    if (t1==nullptr) {
                        addTurnoutMessage(v3Panel->getTitle(), to3->getDisplayName());
                        log->warn("skipping creation of signal "+ systemNameTextField->text()+" due to error");
                        return;
                    } else
                        nbt1 = nbhm->getNamedBeanHandle(to3->getDisplayName(),t1);
            default: break;
        }
        bool home;
        if(ukSignalTypeFromBox(mstBox) ==("Distant")) home=false;
        else home=true;

        s = new MergSD2SignalHead( systemNameTextField->text(), ukSignalAspectsFromBox(msaBox), nbt1, nbt2, nbt3, false, home);
        s->setUserName(userNameTextField->text());
        qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->AbstractManager::Register(s);

    }
}


#endif
void SignalHeadTableAction::editSignal(/*int row*/ SignalHead* head) {
//    // Logix was found, initialize for edit
//    QString eSName = (String)m.getValueAt(row,BeanTableDataModel.SYSNAMECOL);
//    _curSignal = static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager")).getBySystemName(eSName);
    _curSignal = head;
    //numConditionals = _curLogix.getNumConditionals();
    // create the Edit Logix Window
    // Use separate Thread so window is created on top
//    Thread t = new Thread() {
//            /*public*/ void run() {
//                //Thread.yield();
                makeEditSignalWindow();
//                }
//            };
    if (log->isDebugEnabled()) log->debug("editPressed Thread started for " + _curSignal->getDisplayName());
    //javax.swing.SwingUtilities.invokeLater(t);
}

void SignalHeadTableAction::makeEditSignalWindow()
{
 QString eSName = _curSignal->getSystemName();
 if (editingHead)
 {
  if (eSName ==(editSysName))
  {
   editFrame->setVisible(true);
  }
  else
  {
   log->error("Attempt to edit two signal heads at the same time-"+editSysName+"-and-"+eSName+"-");
   QString msg = tr("Attempt to edit two signal heads at the same time-")+editSysName+tr("-and-")+eSName+"-";
   JOptionPane::showMessageDialog(editFrame, msg,
               tr("Warning"), JOptionPane::ERROR_MESSAGE);
   editFrame->setVisible(true);
   return;
  }
 }
 // not currently editing a signal head

 editSysName = eSName;
 editingHead = true;
 curS = (SignalHead*)qobject_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(editSysName)->self();
 if (editFrame == nullptr)
 {
  eto1 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  eto2 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  eto3 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  eto4 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  eto5 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  eto6 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  eto7 = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), nullptr);
  // set up a new edit window
  editFrame = new JmriJFrameX("Edit Signal");
  //editFrame->setWindowTitle(tr("Edit Signal"));
  QWidget* centralWidget = new QWidget();
  editFrame->setCentralWidget(centralWidget);
  centralWidget->setLayout(new QVBoxLayout());
  editFrame->addHelpMenu("package.jmri.jmrit.beantable.SignalAddEdit", true);
  QMenuBar* menuBar = new QMenuBar();
  editFrame->setMenuBar(menuBar);
  editWindowMenu = new QMenu("Window");
  menuBar->addMenu(editWindowMenu);
  //connect(editWindowMenu, SIGNAL(aboutToShow()), this, SLOT(on_editMenuWindow_aboutToShow()));
  QFont font = QFont();
  font.setPointSize(8);
  editFrame->setFont(font);
  editFrame->resize(304, 620);

  QWidget* panelHeader = new QWidget(centralWidget);
  QVBoxLayout* panelHeaderVLayout = new QVBoxLayout(panelHeader);
  panelHeader->setLayout(panelHeaderVLayout);

  QWidget* p;
  p = new QWidget();
  p->setLayout(new QVBoxLayout());
  p->layout()->addWidget(signalType);
  panelHeaderVLayout->addWidget(p);
  QFrame* line = new QFrame();
  line->setObjectName(QString::fromUtf8("line"));
  line->setGeometry(QRect(10, 30, 571, 16));
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  panelHeaderVLayout->addWidget(line);
  p = new QWidget();
  p->setLayout(new QVBoxLayout());
  p->layout()->addWidget(eSystemNameLabel);
  p->layout()->addWidget(eSystemName);
  p->layout()->addWidget(eSysNameLabel);
  panelHeaderVLayout->addWidget(p);
  p = new QWidget();
  p->setLayout(new QVBoxLayout());
  p->layout()->addWidget(eUserNameLabel);
  p->layout()->addWidget(eUserName);
  panelHeaderVLayout->addWidget(p);

  editFrame->centralWidget()->layout()->addWidget(panelHeader/*, BorderLayout.PAGE_START*/);
  // create seven boxes for input information, and put into pane

  QWidget* panelCentre = new QWidget();
  QVBoxLayout* panelCentreVLayout;
  panelCentre->setLayout(panelCentreVLayout = new QVBoxLayout(panelCentre/*, BoxLayout.Y_AXIS*/));

  ev1Panel = new JPanel();
  ev1Panel->setLayout(defaultFlow);
  ev1Panel->setMaximumHeight(180);
  ev1Panel->layout()->addWidget(eto1);
  ev1Panel->layout()->addWidget(es1Box);
  ev1Panel->layout()->addWidget(emsaBox);
  ev1Panel->setBorder(ev1Border);
  panelCentreVLayout->addWidget(ev1Panel);
  ev2Panel = new JPanel();
  ev2Panel->setLayout(new QVBoxLayout());
    ev2Panel->setMaximumHeight(180);
    ev2Panel->layout()->addWidget(eto2);
    ev2Panel->layout()->addWidget(es2Box);
    ev2Panel->layout()->addWidget(es2aBox);
    ev2Panel->layout()->addWidget(emstBox);
    ev2Panel->setBorder(ev2Border);
    panelCentreVLayout->addWidget(ev2Panel);
    ev3Panel = new JPanel();
    ev3Panel->setLayout(new QVBoxLayout());
    ev3Panel->setMaximumHeight(180);
    ev3Panel->layout()->addWidget(eto3);
    ev3Panel->layout()->addWidget(es3Box);
    ev3Panel->layout()->addWidget(es3aBox);
    ev3Panel->setBorder(ev3Border);
    panelCentreVLayout->addWidget(ev3Panel);
    ev4Panel = new JPanel();
    ev4Panel->setMaximumHeight(180);
    ev4Panel->layout()->addWidget(eto4);
    ev4Panel->layout()->addWidget(es4Box);
    ev4Panel->setBorder(ev4Border);
    panelCentreVLayout->addWidget(ev4Panel);
    ev5Panel = new JPanel(); ev5Panel->setLayout(new QVBoxLayout());
    ev5Panel->setMaximumHeight(180);
    ev5Panel->layout()->addWidget(eto5);
    ev5Panel->layout()->addWidget(es5Box);
    ev5Panel->setBorder(ev5Border);
    panelCentreVLayout->addWidget(ev5Panel);
    ev6Panel = new JPanel(); ev6Panel->setLayout(new QVBoxLayout());
    ev6Panel->setMaximumHeight(180);
    ev6Panel->layout()->addWidget(eto6);
    ev6Panel->layout()->addWidget(es6Box);
    //ev6Panel->setBorder(ev6Border);
    panelCentreVLayout->addWidget(ev6Panel);
    ev7Panel = new JPanel(); ev7Panel->setLayout(new QVBoxLayout());
    ev7Panel->setMaximumHeight(180);
    ev7Panel->layout()->addWidget(eto7);
    ev7Panel->layout()->addWidget(es7Box);
    ev7Panel->setBorder(ev7Border);
    panelCentreVLayout->addWidget(ev7Panel);

    p = new QWidget();
    p->setLayout(defaultFlow);
    p->layout()->addWidget(evtLabel);
    p->layout()->addWidget(etot);
    p->layout()->addWidget(estBox);
    panelCentreVLayout->addWidget(p);

    QScrollArea* scrollPane = new QScrollArea(panelCentre);
    editFrame->centralWidget()->layout()->addWidget(scrollPane/*, BorderLayout.CENTER*/);

    // buttons at bottom of panel
    QWidget* panelBottom = new QWidget();
    //panelBottom->setLayout(new QVBoxLayout(panelBottom/*, BoxLayout.Y_AXIS*/));
    panelBottom->setLayout(new FlowLayout);
    // add buttons
    p = new QWidget();
    p->setLayout(new QVBoxLayout());
    QPushButton* cancel;
    p->layout()->addWidget(cancel = new QPushButton(tr("Cancel")));
//        cancel.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelPressed(e);
//            }
//        });
    connect(cancel, SIGNAL(clicked()), this, SLOT(cancelPressed()));
    QPushButton* update;
    p->layout()->addWidget(update = new QPushButton(tr("Update")));
//        update.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updatePressed(e);
//            }
//        });
    connect(update, SIGNAL(clicked()), this, SLOT(updatePressed()));
    panelBottom->layout()->addWidget(p);
    editFrame->centralWidget()->layout()->addWidget(panelBottom/*, BorderLayout.PAGE_END*/);
//        editFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                cancelPressed(NULL);
//            }
//        });
    // TODO: handle close request
} else {
    eto1->refresh();
    eto2->refresh();
    eto3->refresh();
    eto4->refresh();
    eto5->refresh();
    eto6->refresh();
    eto7->refresh();
    }
    // default the seven optional items to hidden, and system name to visible
    eSystemName->setVisible(false);
    eSysNameLabel->setVisible(true);
    eUserNameLabel->setVisible(true);
    eUserName->setVisible(true);
    ev1Panel->setVisible(false);
    eto1->setVisible(false);
    es1Box->setVisible(false);
    ev2Panel->setVisible(false);
    eto2->setVisible(false);
    es2Box->setVisible(false);
    es2aBox->setVisible(false);
    ev3Panel->setVisible(false);
    eto3->setVisible(false);
    es3Box->setVisible(false);
    es3aBox->setVisible(false);
    ev4Panel->setVisible(false);
    eto4->setVisible(false);
    es4Box->setVisible(false);
    ev5Panel->setVisible(false);
    eto5->setVisible(false);
    es5Box->setVisible(false);
    ev6Panel->setVisible(false);
    eto6->setVisible(false);
    es6Box->setVisible(false);
    ev7Panel->setVisible(false);
    eto7->setVisible(false);
    es7Box->setVisible(false);
    evtLabel->setVisible(false);
    etot->setVisible(false);
    estBox->setVisible(false);
    emstBox->setVisible(false);
    emsaBox->setVisible(false);
    // determine class name of signal head and initialize this class of signal
    className = curS->metaObject()->className();
    if (className ==("jmri.implementation.QuadOutputSignalHead"))
    {
        signalType->setText(quadOutput);
        eSystemNameLabel->setText(tr("System Name:"));
        eSysNameLabel->setText(curS->getSystemName());
        eUserNameLabel->setText(tr("User Name:"));
        eUserName->setText(curS->getUserName());
        ev1Border->setTitle(tr("Green output number:"));
        ev1Panel->setVisible(true);
        eto1->setVisible(true);
        et1 = ((TripleTurnoutSignalHead*)curS)->getGreen()->getBean();
        eto1->setDefaultNamedBean(et1);

        ev2Border->setTitle(tr("Yellow output number:"));
        ev2Panel->setVisible(true);
        eto2->setVisible(true);
        eto2->setDefaultNamedBean(((TripleTurnoutSignalHead*)curS)->getYellow()->getBean());
        ev3Border->setTitle(tr("Red output number:"));
        ev3Panel->setVisible(true);
        eto3->setVisible(true);
        eto3->setDefaultNamedBean(((TripleTurnoutSignalHead*)curS)->getRed()->getBean());
        ev4Border->setTitle(tr("Lunar output "));
        ev4Panel->setVisible(true);
        eto4->setVisible(true);
        eto4->setDefaultNamedBean(((QuadOutputSignalHead*)curS)->getLunar()->getBean());
    }
    else if (className ==("jmri.implementation.TripleTurnoutSignalHead")) {
        signalType->setText(tripleTurnout);
        eSystemNameLabel->setText(tr("System Name:"));
        eSysNameLabel->setText(curS->getSystemName());
        eUserNameLabel->setText(tr("User Name:"));
        eUserName->setText(curS->getUserName());
        ev1Border->setTitle(tr("Green output number:"));
        ev1Panel->setVisible(true);
        eto1->setVisible(true);
        eto1->setDefaultNamedBean(((TripleTurnoutSignalHead*)curS)->getGreen()->getBean());
        ev2Border->setTitle(tr("Yellow output number:"));
        ev2Panel->setVisible(true);
        eto2->setVisible(true);
        eto2->setDefaultNamedBean(((TripleTurnoutSignalHead*)curS)->getYellow()->getBean());
        ev3Border->setTitle(tr("Red output number:"));
        ev3Panel->setVisible(true);
        eto3->setVisible(true);
        eto3->setDefaultNamedBean(((TripleTurnoutSignalHead*)curS)->getRed()->getBean());
    }
    else if (className ==("DoubleTurnoutSignalHead")) {
        signalType->setText(doubleTurnout);
        eSystemNameLabel->setText(tr("System Name:"));
        eSysNameLabel->setText(curS->getSystemName());
        eUserNameLabel->setText(tr("User Name:"));
        eUserName->setText(curS->getUserName());
        ev1Border->setTitle(tr("Green output number:"));
        ev1Panel->setVisible(true);
        eto1->setVisible(true);
        eto1->setDefaultNamedBean(((DoubleTurnoutSignalHead*)curS)->getGreen()->getBean());
        ev2Border->setTitle(tr("Red output number:"));
        ev2Panel->setVisible(true);
        eto2->setVisible(true);
        eto2->setDefaultNamedBean(((DoubleTurnoutSignalHead*)curS)->getRed()->getBean());
    }
    else
    if (className ==("SingleTurnoutSignalHead"))
    {
        signalType->setText(singleTurnout);
        eSystemNameLabel->setText(tr("System Name"));
        eSysNameLabel->setText(curS->getSystemName());
        eUserNameLabel->setText(tr("User Name"));
        eUserName->setText(curS->getUserName());
        ev1Border->setTitle(tr("Turnout Number"));
        ev1Panel->setVisible(true);
        eto1->setVisible(true);
        eto1->setDefaultNamedBean(((SingleTurnoutSignalHead*)curS)->getOutput()->getBean());
        ev2Border->setTitle("On Appearance");
        ev2Panel->setVisible(true);
        es2aBox->setVisible(true);
        setSignalStateInBox(es2aBox, ((SingleTurnoutSignalHead*)curS)->getOnAppearance());
        ev3Border->setTitle("Off Appearance");
        ev3Panel->setVisible(true);
        es3aBox->setVisible(true);
        setSignalStateInBox(es3aBox, ((SingleTurnoutSignalHead*)curS)->getOffAppearance());
    }
    else if (className ==("VirtualSignalHead")) {
        signalType->setText(virtualHead);
        eSystemNameLabel->setText(tr("System Name"));
        eSysNameLabel->setText(curS->getSystemName());
        eUserNameLabel->setText(tr("User Name"));
        eUserName->setText(curS->getUserName());
    }
#if 1
    else if (className ==("jmri.implementation.LsDecSignalHead")) {
        signalType->setText(lsDec);
        eSystemNameLabel->setText(tr("LabelSystemName"));
        eSysNameLabel->setText(curS->getSystemName());
        eUserNameLabel->setText(tr("LabelUserName"));
        eUserName->setText(curS->getUserName());
        ev1Border->setTitle(tr("Green output number:"));
        ev1Panel->setVisible(true);
        eto1->setVisible(true);
        eto1->setDefaultNamedBean(((LsDecSignalHead*)curS)->getGreen()->getBean());
        es1Box->setVisible(true);
        setTurnoutStateInBox(es1Box, ((LsDecSignalHead*)curS)->getGreenState(), turnoutStateValues);
        ev2Border->setTitle(tr("Yellow output number:"));
        ev2Panel->setVisible(true);
        eto2->setVisible(true);
        eto2->setDefaultNamedBean(((LsDecSignalHead*)curS)->getYellow()->getBean());
        es2Box->setVisible(true);
        setTurnoutStateInBox(es2Box, ((LsDecSignalHead*)curS)->getYellowState(), turnoutStateValues);
        ev3Border->setTitle(tr("Red output number:"));
        ev3Panel->setVisible(true);
        eto3->setVisible(true);
        eto3->setDefaultNamedBean(((LsDecSignalHead*)curS)->getRed()->getBean());
        es3Box->setVisible(true);
        setTurnoutStateInBox(es3Box, ((LsDecSignalHead*)curS)->getRedState(), turnoutStateValues);
        ev4Border->setTitle(tr("LabelFlashGreenTurnoutNumber"));
        ev4Panel->setVisible(true);
        eto4->setVisible(true);
        eto4->setDefaultNamedBean(((LsDecSignalHead*)curS)->getFlashGreen()->getBean());
        es4Box->setVisible(true);
        setTurnoutStateInBox(es4Box, ((LsDecSignalHead*)curS)->getFlashGreenState(), turnoutStateValues);
        ev5Border->setTitle(tr("LabelFlashYellowTurnoutNumber"));
        ev5Panel->setVisible(true);
        eto5->setVisible(true);
        eto5->setDefaultNamedBean(((LsDecSignalHead*)curS)->getFlashYellow()->getBean());
        es5Box->setVisible(true);
        setTurnoutStateInBox(es5Box, ((LsDecSignalHead*)curS)->getFlashYellowState(), turnoutStateValues);
        ev6Border->setTitle(tr("LabelFlashRedTurnoutNumber"));
        ev6Panel->setVisible(true);
        eto6->setVisible(true);
        eto6->setDefaultNamedBean(((LsDecSignalHead*)curS)->getFlashRed()->getBean());
        es6Box->setVisible(true);
        setTurnoutStateInBox(es6Box, ((LsDecSignalHead*)curS)->getFlashRedState(), turnoutStateValues);
        ev7Border->setTitle(tr("LabelDarkTurnoutNumber"));
        ev7Panel->setVisible(true);
        eto7->setVisible(true);
        eto7->setDefaultNamedBean(((LsDecSignalHead*)curS)->getDark()->getBean());
        es7Box->setVisible(true);
        setTurnoutStateInBox(es7Box, ((LsDecSignalHead*)curS)->getDarkState(), turnoutStateValues);
    }
#endif
    else if (className ==("jmri.implementation.SE8cSignalHead")) {
        handleSE8cEditSignal();
    }
#if 0
    else if (className ==("jmri.jmrix.grapevine.SerialSignalHead")) {
        signalType->setText(grapevine);
        eSystemNameLabel->setText(tr("LabelSystemName"));
        eSysNameLabel->setText(curS.getSystemName());
        eUserNameLabel->setText(tr("LabelUserName"));
        eUserName->setText(curS.getUserName());
        /*ev1Border->setTitle(tr("LabelUserName"));
        ev1 Panel->setVisible(true);
        eto1->setVisible(true);
        eto1->setText(curS.getUserName());*/
    }
    else if (className ==("jmri.jmrix.acela.AcelaSignalHead")) {
        signalType->setText(acela);
        eSystemNameLabel->setText(tr("LabelSystemName"));
        eSysNameLabel->setText(curS.getSystemName());
        eUserNameLabel->setText(tr("LabelUserName"));
        eUserName->setText(curS.getUserName());
        /*ev1Border->setTitle(tr("LabelUserName"));
        ev1 Panel->setVisible(true);
        eto1->setVisible(true);
        eto1->setText(curS.getUserName());*/
        evtLabel->setText(tr("LabelAspectType"));
        etot->setVisible(false);
        AcelaNode tNode = AcelaAddress.getNodeFromSystemName(curS.getSystemName());
        if (tNode == nullptr) {
            // node does not exist, ignore call
            log->error("Can't find new Acela Signal with name '"+curS.getSystemName());
            return;
        }
        int headnumber = Integer.parseInt(curS.getSystemName().substring(2,curS.getSystemName().length()));

        est Box->setVisible(true);
        setSignalheadTypeInBox(estBox, tNode.getOutputSignalHeadType(headnumber), signalheadTypeValues);
    }
    else if (className ==("jmri.implementation.DccSignalHead")) {
        signalType->setText(dccSignalDecoder);
        eSystemNameLabel->setText(tr("LabelSystemName"));
        eSysNameLabel->setText(curS.getSystemName());
        eUserNameLabel->setText(tr("LabelUserName"));
        eUserName->setText(curS.getUserName());
    }
    else if (className ==("jmri.implementation.MergSD2SignalHead")) {
    //Edit signal stuff to go here!
        signalType->setText(mergSignalDriver);
        eSystemNameLabel->setText(tr("LabelSystemName"));
        eSysNameLabel->setText(curS.getSystemName());
        eUserNameLabel->setText(tr("LabelUserName"));
        eUserName->setText(curS.getUserName());
        ev1Border->setTitle("Aspects");
        ev1 Panel->setVisible(true);
        setUkSignalAspectsFromBox(emsaBox, ((jmri.implementation.MergSD2SignalHead)curS).getAspects());
        eto1->setVisible(false);
        emsa Box->setVisible(true);
        ev2Border->setTitle("Signal Type");
        ev2 Panel->setVisible(true);
        eto2->setVisible(false);
        emst Box->setVisible(true);
        if (((jmri.implementation.MergSD2SignalHead)curS).getHome())
            setUkSignalType(emstBox, "Home");
        else
            setUkSignalType(emstBox, "Distant");
        //setUKSignalTypeFromBox(emstBox, ((jmri.implementation.MergSD2SignalHead)curS).getAspects());
        ev3Border->setTitle("Input1");
        ev3 Panel->setVisible(true);
        eto3->setVisible(true);
        eto3.setDefaultNamedBean(((jmri.implementation.MergSD2SignalHead)curS).getInput1()->getBean());
        ev4Border->setTitle("Input2");
        ev4 Panel->setVisible(true);
        eto4->setVisible(true);
        if(((jmri.implementation.MergSD2SignalHead)curS).getInput2()!=nullptr)
            eto4.setDefaultNamedBean(((jmri.implementation.MergSD2SignalHead)curS).getInput2()->getBean());
        ev5Border->setTitle("Input3");
        ev5 Panel->setVisible(true);
        eto5->setVisible(true);
        if(((jmri.implementation.MergSD2SignalHead)curS).getInput3()!=nullptr)
            eto5.setDefaultNamedBean(((jmri.implementation.MergSD2SignalHead)curS).getInput3()->getBean());
        emsa Box->addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                ukAspectChange(true);
            }
        });
        ukAspectChange(true);
    }
#endif
    else log->error("Cannot edit SignalHead of unrecognized type: "+className);
    // finish up
    //editFrame.pack();
    editFrame->setVisible(true);
}

void SignalHeadTableAction::cancelPressed(JActionEvent * /*e*/) {
    editFrame->setVisible(false);
    editingHead = false;
}


/*private*/ void SignalHeadTableAction::cancelNewPressed(JActionEvent* /*e*/) {
    addFrame->setVisible(false);
//    addFrame->dispose();
//    addFrame = nullptr;
}

//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
void SignalHeadTableAction::updatePressed(JActionEvent* /*e*/) {
    QString nam = eUserName->text();
    // check if user name changed
    if (!((curS->getUserName()!="") && (curS->getUserName() ==(nam)))) {
        if(checkUserName(nam))
            curS->setUserName(nam);
        else
            return;
    }

    // update according to class of signal head
    if (className ==("QuadOutputSignalHead")) {
        Turnout* t1 = updateTurnoutFromPanel(eto1, "SignalHead:" + eSysNameLabel->text() + ":Green", ((QuadOutputSignalHead*)curS)->getGreen()->getBean(), ev1Panel->getTitle());

        if (t1==nullptr) {
            return;
        }
        else {
            ((QuadOutputSignalHead*)curS)->setGreen(nbhm->getNamedBeanHandle(eto1->getDisplayName(),t1));
        }

        Turnout* t2 = updateTurnoutFromPanel(eto2, "SignalHead:" + eSysNameLabel->text() + ":Yellow", ((QuadOutputSignalHead*)curS)->getYellow()->getBean(), ev2Panel->getTitle());
        if (t2==nullptr) {
            return;
        }
        else ((QuadOutputSignalHead*)curS)->setYellow(nbhm->getNamedBeanHandle(eto2->getDisplayName(),t2));

        Turnout* t3 = updateTurnoutFromPanel(eto3, "SignalHead:" + eSysNameLabel->text() + ":Red", ((QuadOutputSignalHead*)curS)->getRed()->getBean(), ev3Panel->getTitle());
        if (t3==nullptr) {
            return;
        }
        else ((QuadOutputSignalHead*)curS)->setRed(nbhm->getNamedBeanHandle(eto3->getDisplayName(),t3));

        Turnout* t4 = updateTurnoutFromPanel(eto4, "SignalHead:" + eSysNameLabel->text() + ":Lunar", ((QuadOutputSignalHead*)curS)->getLunar()->getBean(), ev4Panel->getTitle());
        if (t4==nullptr) {
            return;
        }
        else ((QuadOutputSignalHead*)curS)->setLunar(nbhm->getNamedBeanHandle(eto4->getDisplayName(),t4));
    }
    else if (className ==("TripleTurnoutSignalHead")) {
        Turnout* t1 = updateTurnoutFromPanel(eto1, "SignalHead:" + eSysNameLabel->text() + ":Green", ((TripleTurnoutSignalHead*)curS)->getGreen()->getBean(), ev1Panel->getTitle());

        if (t1==nullptr) {
            return;
        }
        else ((TripleTurnoutSignalHead*)curS)->setGreen(nbhm->getNamedBeanHandle(eto1->getDisplayName(),t1));

        Turnout* t2 = updateTurnoutFromPanel(eto2, "SignalHead:" + eSysNameLabel->text() + ":Yellow", ((TripleTurnoutSignalHead*)curS)->getYellow()->getBean(), ev2Panel->getTitle());
        if (t2==nullptr) {
            return;
        }
        else ((TripleTurnoutSignalHead*)curS)->setYellow(nbhm->getNamedBeanHandle(eto2->getDisplayName(),t2));

        Turnout* t3 = updateTurnoutFromPanel(eto3, "SignalHead:" + eSysNameLabel->text() + ":Red", ((TripleTurnoutSignalHead*)curS)->getRed()->getBean(), ev3Panel->getTitle());
        if (t3==nullptr) {
            return;
        }
        else ((TripleTurnoutSignalHead*)curS)->setRed(nbhm->getNamedBeanHandle(eto3->getDisplayName(),t3));
    }
    else if (className ==("DoubleTurnoutSignalHead")) {
        Turnout* t1 = updateTurnoutFromPanel(eto1, "SignalHead:" + eSysNameLabel->text() + ":Green", ((DoubleTurnoutSignalHead*)curS)->getGreen()->getBean(), ev1Panel->getTitle());
        Turnout* t2 = updateTurnoutFromPanel(eto2, "SignalHead:" + eSysNameLabel                                             ->text() + ":Red", ((DoubleTurnoutSignalHead*)curS)->getRed()->getBean(), ev2Panel->getTitle());
        if (t1==nullptr) {
            return;
        }
        else ((DoubleTurnoutSignalHead*)curS)->setGreen(nbhm->getNamedBeanHandle(eto1->getDisplayName(),t1));
        if (t2==nullptr) {
            return;
        }
        else ((DoubleTurnoutSignalHead*)curS)->setRed(nbhm->getNamedBeanHandle(eto2->getDisplayName(),t2));
    }

    else if (className ==("SingleTurnoutSignalHead"))
    {

        Turnout* t1 = updateTurnoutFromPanel(eto1,"SignalHead:" + eSysNameLabel->text() + ":" + es2aBox->currentText() + ":" + es3aBox->currentText(), ((SingleTurnoutSignalHead*)curS)->getOutput()->getBean(), ev1Panel->getTitle());
        if (t1==nullptr) {
            noTurnoutMessage(ev1Panel->getTitle(), eto1->getDisplayName());
            return;
        }
        ((SingleTurnoutSignalHead*)curS)->setOutput(nbhm->getNamedBeanHandle(eto1->getDisplayName(),t1));
        ((SingleTurnoutSignalHead*)curS)->setOnAppearance(signalStateFromBox(es2aBox));
        ((SingleTurnoutSignalHead*)curS)->setOffAppearance(signalStateFromBox(es3aBox));
    }
    else if (className ==("LsDecSignalHead")) {
        Turnout* t1 = updateTurnoutFromPanel(eto1, "SignalHead:" + eSysNameLabel->text()+ ":Green", ((LsDecSignalHead*)curS)->getGreen()->getBean(), ev1Panel->getTitle());
        if (t1==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setGreen(nbhm->getNamedBeanHandle(eto1->getDisplayName(),t1));
            ((LsDecSignalHead*)curS)->setGreenState(turnoutStateFromBox(es1Box));
        }

        Turnout* t2 = updateTurnoutFromPanel(eto2, "SignalHead:" + eSysNameLabel->text()+ ":Yellow", ((LsDecSignalHead*)curS)->getYellow()->getBean(), ev2Panel->getTitle());
        if (t2==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setYellow(nbhm->getNamedBeanHandle(eto2->getDisplayName(),t2));
            ((LsDecSignalHead*)curS)->setYellowState(turnoutStateFromBox(es2Box));
        }

        Turnout* t3 = updateTurnoutFromPanel(eto3, "SignalHead:" + eSysNameLabel->text()+ ":Red", ((LsDecSignalHead*)curS)->getRed()->getBean(), ev3Panel->getTitle());
        if (t3==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setRed(nbhm->getNamedBeanHandle(eto3->getDisplayName(),t3));
            ((LsDecSignalHead*)curS)->setRedState(turnoutStateFromBox(es3Box));
        }

        Turnout* t4 = updateTurnoutFromPanel(eto4, "SignalHead:" + eSysNameLabel->text()+ ":FlashGreen", ((LsDecSignalHead*)curS)->getFlashGreen()->getBean(), ev4Panel->getTitle());
        if (t4==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setFlashGreen(nbhm->getNamedBeanHandle(eto4->getDisplayName(),t4));
            ((LsDecSignalHead*)curS)->setFlashGreenState(turnoutStateFromBox(es4Box));
        }

        Turnout* t5 = updateTurnoutFromPanel(eto5, "SignalHead:" + eSysNameLabel->text()+ ":FlashYellow", ((LsDecSignalHead*)curS)->getFlashYellow()->getBean(), ev5Panel->getTitle());
        if (t5==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setFlashYellow(nbhm->getNamedBeanHandle(eto5->getDisplayName(),t5));
            ((LsDecSignalHead*)curS)->setFlashYellowState(turnoutStateFromBox(es5Box));
        }

        Turnout* t6 = updateTurnoutFromPanel(eto6, "SignalHead:" + eSysNameLabel->text()+ ":FlashRed", ((LsDecSignalHead*)curS)->getFlashRed()->getBean(), ev6Panel->getTitle());
        if (t6==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setFlashRed(nbhm->getNamedBeanHandle(eto6->getDisplayName(),t6));
            ((LsDecSignalHead*)curS)->setFlashRedState(turnoutStateFromBox(es6Box));
        }

        Turnout* t7 = updateTurnoutFromPanel(eto7, "SignalHead:" + eSysNameLabel->text()+ ":Dark", ((LsDecSignalHead*)curS)->getDark()->getBean(), ev7Panel->getTitle());
        if (t7==NULL) {
            return;
        }
        else {
            ((LsDecSignalHead*)curS)->setDark(nbhm->getNamedBeanHandle(eto7->getDisplayName(),t7));
            ((LsDecSignalHead*)curS)->setDarkState(turnoutStateFromBox(es7Box));
        }
    }
    else if (className ==("SE8cSignalHead")) {
        handleSE8cUpdatePressed();
    }
#if 0
    else if (className ==("jmri.jmrix.grapevine.SerialSignalHead")) {
        /*String nam = eUserName.->text()();
        // check if user name changed
        if (!((curS.getUserName()!=nullptr) && (curS.getUserName() ==(nam)))) {
            if(checkUserName(nam))
                curS.setUserName(nam);
        }*/
    }
    else if (className ==("jmri.jmrix.acela.AcelaSignalHead")) {
        /*String nam = eUserName.->text()();
            // check if user name changed
        if (!((curS.getUserName()!=nullptr) && (curS.getUserName() ==(nam)))) {
            if(checkUserName(nam))
                curS.setUserName(nam);

        }*/
        AcelaNode tNode = AcelaAddress.getNodeFromSystemName(curS.getSystemName());
        if (tNode == nullptr) {
            // node does not exist, ignore call
            log->error("Can't find new Acela Signal with name '"+curS.getSystemName());
            return;
        }
        int headnumber = Integer.parseInt(curS.getSystemName().substring(2,curS.getSystemName().length()));
        tNode.setOutputSignalHeadTypeString(headnumber, est Box->currentText().toString());
//          setSignalheadTypeInBox(estBox, tNode.getOutputSignalHeadType(headnumber), signalheadTypeValues);
//          ((jmri.AcelaSignalHead)curS).setDarkState(signalheadTypeFromBox(estBox));
    }
#endif
    else if (className ==("jmri.implementation.MergSD2SignalHead")){
        switch(ukSignalAspectsFromBox(emsaBox)){
            case 4:
        {
         Turnout* t3 = updateTurnoutFromPanel(eto5, "SignalHead:" + eSysNameLabel->text()+ ":Input3", ((MergSD2SignalHead*)curS)->getInput3()->getBean(), ev5Panel->getTitle());
                    if (t3==nullptr) {
                        return;
                        }
                    else ((MergSD2SignalHead*)curS)->setInput3(nbhm->getNamedBeanHandle(eto5->getDisplayName(),t3));
        }
                    // fall through
        case 3:
        {
         Turnout* t2 = updateTurnoutFromPanel(eto4, "SignalHead:" + eSysNameLabel->text()+ ":Input2", ((MergSD2SignalHead*)curS)->getInput2()->getBean(), ev4Panel->getTitle());
                    if (t2==nullptr) {
                        return;
                        }
                    else ((MergSD2SignalHead*)curS)->setInput2(nbhm->getNamedBeanHandle(eto4->getDisplayName(),t2));
         }
         // fall through
            case 2:
        {
         Turnout* t1 = updateTurnoutFromPanel(eto3, "SignalHead:" + eSysNameLabel->text()+ ":Input1", ((MergSD2SignalHead*)curS)->getInput1()->getBean(), ev3Panel->getTitle());
                    if (t1==nullptr) {
                        return;
                        }
                    else ((MergSD2SignalHead*)curS)->setInput1(nbhm->getNamedBeanHandle(eto3->getDisplayName(),t1));
                    ((MergSD2SignalHead*)curS)->setAspects(ukSignalAspectsFromBox(emsaBox));
                    if(ukSignalTypeFromBox(emstBox)=="Distant") ((MergSD2SignalHead*)curS)->setHome(false);
                    else ((MergSD2SignalHead*)curS)->setHome(true);
        }
            default: break;
        }
        //Need to add the code here for update!
    }
    else {
        log->error("Internal error - cannot update signal of type "+className);
    }

    // successful
    editFrame->setVisible(false);
    editingHead = false;
}

bool SignalHeadTableAction::checkUserName(QString nam)
{
    if (!((nam==NULL) || (nam ==(""))))
    {
        // user name changed, check if new name already exists
        NamedBean* nB = static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getByUserName(nam);
        if (nB != nullptr) {
            log->error("User name is not unique " + nam);
            QString msg = tr("User Name \" %1 \" has already been used.").arg(nam);
            JOptionPane::showMessageDialog(editFrame, msg,
                                          tr("Warning"),
                                          JOptionPane::ERROR_MESSAGE);
            return false;
        }
        //Check to ensure that the username doesn't exist as a systemname.
        nB = static_cast<AbstractSignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getBySystemName(nam);
        if (nB!=nullptr){
            log->error("User name is not unique " + nam + " It already exists as a System name");
            QString msg = tr("User Name \" %1 \" has already been used as a System Name.").arg(nam);
            JOptionPane::showMessageDialog(editFrame, msg,
                        tr("Warning"),
                            JOptionPane::ERROR_MESSAGE);
            return false;
        }
    }
    return true;

}

void SignalHeadTableAction::noTurnoutMessage(QString s1, QString s2) {
    log->warn("Could not provide turnout "+s2);
    QString msg = tr("Could not provide \" %1 \" - \" %2 \".").arg(s1).arg(s2);
    JOptionPane::showMessageDialog(editFrame, msg,
            tr("Warning"), JOptionPane::ERROR_MESSAGE);
}

void SignalHeadTableAction::ukAspectChange(bool edit){
    if(edit){
        switch (ukSignalAspectsFromBox(emsaBox)){
            case 2 : ev4Panel->setVisible(false);
                     eto4->setVisible(false);
                     ev5Panel->setVisible(false);
                     eto5->setVisible(false);
                     ev2Panel->setVisible(true);
                     emstBox->setVisible(true);
                     break;
            case 3 : ev4Panel->setVisible(true);
                     eto4->setVisible(true);
                     ev5Panel->setVisible(false);
                     eto5->setVisible(false);
                     ev2Panel->setVisible(false);
                     emstBox->setVisible(false);
                     setUkSignalType(emstBox, "Home");
                     break;
            case 4 : ev4Panel->setVisible(true);
                     eto4->setVisible(true);
                     ev5Panel->setVisible(true);
                     eto5->setVisible(true);
                     ev2Panel->setVisible(false);
                     emstBox->setVisible(false);
                     break;
            default: break;
        }
        editFrame->pack();

    } else {
        switch (ukSignalAspectsFromBox(msaBox)){
            case 2 : v4Panel->setVisible(false);
                     to4->setVisible(false);
                     v5Panel->setVisible(false);
                     to5->setVisible(false);
                     v2Panel->setVisible(true);
                     mstBox->setVisible(true);
                     break;
            case 3 : v4Panel->setVisible(true);
                     to4->setVisible(true);
                     v5Panel->setVisible(false);
                     to5->setVisible(false);
                     v2Panel->setVisible(false);
                     mstBox->setVisible(false);
                     setUkSignalType(mstBox, "Home");
                     break;
            case 4 : v4Panel->setVisible(true);
                     to4->setVisible(true);
                     v5Panel->setVisible(true);
                     to5->setVisible(true);
                     v2Panel->setVisible(false);
                     mstBox->setVisible(false);
                     setUkSignalType(mstBox, "Home");
                     break;
            default: break;
        }
        addFrame->pack();
    }

}

/*public*/ void SignalHeadTableAction::dispose(){
    if (to1!=nullptr)
        to1->dispose();
    if (to2!=nullptr)
        to2->dispose();
    if (to3!=nullptr)
        to3->dispose();
    if (to4!=nullptr)
        to4->dispose();
    if (to5!=nullptr)
        to5->dispose();
    if (to6!=nullptr)
        to6->dispose();
    if (to7!=nullptr)
        to7->dispose();
    if (eto1!=nullptr)
        eto1->dispose();
    if (eto1!=nullptr)
        eto2->dispose();
    if (eto1!=nullptr)
        eto3->dispose();
    if (eto1!=nullptr)
        eto4->dispose();
    if (eto1!=nullptr)
        eto5->dispose();
    if (eto1!=nullptr)
        eto6->dispose();
    if (eto1!=nullptr)
        eto7->dispose();
    AbstractTableAction::dispose();
}

/*protected*/ Turnout* SignalHeadTableAction::updateTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference, Turnout* oldTurnout, QString title)
{
 Turnout* newTurnout = getTurnoutFromPanel(bp, reference);
    if (newTurnout==nullptr){
        noTurnoutMessage(title, bp->getDisplayName());
    }
    if(newTurnout!=nullptr && (newTurnout->getComment()==nullptr || newTurnout->getComment() ==("")))
        newTurnout->setComment(reference);
    if (oldTurnout==nullptr || newTurnout==oldTurnout)
        return newTurnout;
    if(oldTurnout->getComment()!=nullptr && oldTurnout->getComment() ==(reference))
        oldTurnout->setComment(nullptr);
    return newTurnout;

}

/*protected*/ Turnout* SignalHeadTableAction::getTurnoutFromPanel(BeanSelectCreatePanel* bp, QString reference)
{
 if (bp==nullptr)
  return nullptr;

 bp->setReference(reference);
 Turnout* t;
// try
// {
 t =  (Turnout*) bp->getNamedBean()->self();
// }
 //catch (JmriException* ex)
 if(t == nullptr)
 {
  log->warn("skipping creation of turnout not found for " + reference);
//        return NULL;
 }
 return t;
}

/*protected*/ QString SignalHeadTableAction::getClassName()
{
    //return SignalHeadTableAction.class.getName();
 return "jmri.jmrit.beantable.SignalHeadTableAction";
}

/*public*/ QString SignalHeadTableAction::getClassDescription() { return tr("Signal Head Table"); }

/*public*/ void SignalHeadTableAction::dccSignalPanel() {

 _dccSignalPanel = new JPanel();
 _dccSignalPanel->setLayout(new QGridLayout());//0, 2));
 dccAspectEdt = QVector< JSpinner*>(DccSignalHead::getDefaultValidStates().length());

 for (int i = 0; i < DccSignalHead::getDefaultValidStates().length(); i++) {
     QString aspect = DccSignalHead::getDefaultValidStateNames()[i];
     _dccSignalPanel->layout()->addWidget(new JLabel(aspect));

     SpinnerNumberModel* dccSpinnerModel = new SpinnerNumberModel(1, 0, 31, 1);
     JSpinner* tmp = new JSpinner(dccSpinnerModel);
     dccAspectEdt[i] = tmp; // store the whole JSpinner
     _dccSignalPanel->layout()->addWidget(tmp); // and display that copy on the JPanel
     tmp->setToolTip(tr("Value for aspect \"%1\" must be between 0 & 31").arg(i));
 }
}

/**
 * Sets whether the {@code Action} is enabled. The default is {@code true}.
 *
 * @param newValue  {@code true} to enable the action, {@code false} to
 *                  disable it
 * @see Action#setEnabled
 */
/*public*/ void SignalHeadTableAction::setEnabled(bool newValue)
{
 bool oldValue = this->enabled;

 if (oldValue != newValue)
 {
  this->enabled = newValue;
//        firePropertyChange("enabled",
//                           QVariant(oldValue), QVariant(newValue));
  emit propertyChange(new PropertyChangeEvent(this, "enabled", QVariant(oldValue), QVariant(newValue )));
 }
}
QString SignalHeadTableAction::getName()
{
 return "jmri.jmrit.beantable.SignalHeadTableAction";
}

/*static*/ /*final*/ Logger* SignalHeadTableAction::log = LoggerFactory::getLogger("SignalHeadTableAction");
