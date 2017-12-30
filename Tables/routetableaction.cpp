#include "routetableaction.h"
#include "instancemanager.h"
#include "defaultroutemanager.h"
#include "abstractturnoutmanager.h"
#include "proxyturnoutmanager.h"
#include "proxysensormanager.h"
#include <QVBoxLayout>
#include "../LayoutEditor/jmrijframe.h"
#include "defaultroute.h"
#include "jmribeancombobox.h"
#include "abstractturnoutmanager.h"
#include "jtextfield.h"
#include <QButtonGroup>
#include <QTableView>
#include "stringutil.h"
#include <QHeaderView>
#include <QMenuBar>
#include <QMenu>
#include <QFont>
#include <QStatusBar>
#include "../LayoutEditor/panelmenu.h"
#include <QApplication>
#include <QDesktopWidget>
#include "jmriuserpreferencesmanager.h"
#include "logix.h"
#include "conditionalaction.h"
#include "defaultconditionalaction.h"
#include "conditionalvariable.h"
#include "defaultconditionalmanager.h"
#include "defaultroutemanager.h"
#include <QMessageBox>
#include "systemnamecomparator.h"

//RouteTableAction::RouteTableAction(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Swing action to create and register a Route Table
 
 * Based in part on SignalHeadTableAction.java by Bob Jacobsen
 *
 * @author	Dave Duchamp    Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2007 
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 *
 * @version     $Revision: 22530 $
 */

///*public*/ class RouteTableAction extends AbstractTableAction {

//	static final ResourceBundle rbx = ResourceBundle
//			.getBundle("jmri.jmrit.beantable.LogixTableBundle");
/*static*/ QString RouteTableAction::createInst = "To create a new Route, enter definition, then click 'Add Route'.";
/*static*/ QString RouteTableAction::editInst = "To edit an existing Route, enter system name, then click 'Edit Route'.";
/*static*/ QString RouteTableAction::updateInst = "To change this Route, make changes above, then click 'Update Route'.";
/*static*/ QString RouteTableAction::cancelInst = "To leave Edit mode, without changing this Route, click 'Cancel',";
/*private*/ /*static*/ QStringList RouteTableAction::COLUMN_NAMES = QStringList() << tr("System Name") <<
                                        tr("User Name") <<
                                        tr("Include") <<
                                        tr("Set State");
/*private*/ /*static*/ QString RouteTableAction::SET_TO_ACTIVE = tr("Set")+" "+tr("Active");
/*private*/ /*static*/ QString RouteTableAction::SET_TO_INACTIVE = tr("Set")+" "+tr("Inactive");
/*private*/ /*static*/ QString RouteTableAction::SET_TO_CLOSED = tr("Set")+" "+
        /*((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();*/ tr("Closed");
/*private*/ /*static*/ QString RouteTableAction::SET_TO_THROWN = tr("Set")+" "+
        /*((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();*/ tr("Thrown");
/*private*/ /*static*/ QString RouteTableAction::SET_TO_TOGGLE = tr("Set")+" "+tr("Toggle");
/*public*/ /*final*/ /*static*/ QString RouteTableAction::LOGIX_SYS_NAME = "RTX";
/*public*/ /*final*/ /*static*/ QString RouteTableAction::CONDITIONAL_SYS_PREFIX = LOGIX_SYS_NAME+"C";
/*private*/ /*static*/ QStringList RouteTableAction::sensorInputModes =  QStringList() << "On Active" << "On Inactive"<< "On Change"<< "Veto Active"<< "Veto Inactive";
/*static*/ QList<int> RouteTableAction::sensorInputModeValues =  QList<int>() <<Route::ONACTIVE << Route::ONINACTIVE << Route::ONCHANGE << Route::VETOACTIVE << Route::VETOINACTIVE;
/*private*/ /*static*/ QStringList RouteTableAction::turnoutInputModes = QStringList() << "On "+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText() <<                                        "On "+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText() <<
"On Change" <<  "Veto Closed" <<  "Veto Thrown";
/*private*/ /*static*/ QList<int> RouteTableAction::turnoutInputModeValues = QList<int>() <<Route::ONCLOSED << Route::ONTHROWN << Route::ONCHANGE << Route::VETOCLOSED << Route::VETOTHROWN;
/*private*/ /*static*/ QStringList RouteTableAction::lockTurnoutInputModes =  QStringList() << "On "+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText() <<                                            "On "+((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText() <<                                            "On Change";
int RouteTableAction::ROW_HEIGHT = 20;
#if 0
bool systemNameComparator(QString o1, QString o2)
{
 if (o1.length() <= 3 && o2.length() <= 3)
 {
  return o1 < (o2);
 }
 else if (/*!o1.regionMatches(0,o2,0,2)*/ o1.mid(0,2) != o2.mid(0,2))
 {
  return o1 < (o2);
 }
 else
 {
  // extract length of digits
 QString ch1 = o1.mid(2);
 QString ch2 = o2.mid(2);
 int numDigit1 = 0;
 int numDigit2 = 0;
 for (int i=0; i < ch1.length(); i++)
 {
  //if (Character.isDigit(ch1[i]))
  if(ch1.at(i).isDigit())
  {
   numDigit1++;
  }
  else
  {
   break;
  }
 }
 for (int i=0; i<ch2.length(); i++)
 {
  if (ch2.at(i).isDigit())
  {
   numDigit2++;
  }
  else
  {
   break;
  }
 }
 if (numDigit1==numDigit2)
 {
  try
  {
   //int diff = Integer.parseInt(new String(ch1, 0, numDigit1)) -                              Integer.parseInt(new String(ch2, 0, numDigit2));
   int diff = ch1.mid(0,numDigit1).toInt() - ch1.mid(0,numDigit2).toInt();
   if (diff != 0)
   {
    //return diff;
       if(diff < 0)
           return true;
       else
           return false;
   }
   if (numDigit1==ch1.length() && numDigit2==ch2.length())
   {
    return diff;
   }
   else
   {
    if (numDigit1==ch1.length())
    {
     return -1;
    }
    // both have non-digit chars remaining
//    return new String(ch1, numDigit1, ch1.length-numDigit1) < (
//                    new String(ch2, numDigit2, ch2.length-numDigit2));
    return ch1.mid(numDigit1, ch1.length()-numDigit1) < ch2.mid(numDigit2, ch2.length()-numDigit2);
   }
  }
  catch (NumberFormatException nfe)
  {
    return o1.compare(o2);
  }
   catch (IndexOutOfBoundsException ioob)
   {
     return o1.compare(o2);
   }
  }
  else
  {
   if ((numDigit1 - numDigit2) < 0)
      return true;
   else return false;
  }
 }
}
#endif
/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param s
 */
//@SuppressWarnings("all")
/*public*/ RouteTableAction::RouteTableAction(QString s, QObject *parent)  : AbstractTableAction(s, parent)
{
 //super(s);
 // disable ourself if there is no primary Route manager available
 if (InstanceManager::routeManagerInstance()==NULL) 
  setEnabled(false);
 init();

 // check a constraint required by this implementation,
 // because we assume that the codes are the same as the index
 // in a JComboBox
 if ( Route::ONACTIVE != 0 || Route::ONINACTIVE != 1
        || Route::VETOACTIVE != 2 || Route::VETOINACTIVE !=3 )
        log->error("assumption invalid in RouteTable implementation");
}

/*public*/ RouteTableAction::RouteTableAction(QObject *parent) : AbstractTableAction(tr("RouteTable"), parent)
{ 
  //this(tr("Route Table"));
 init();

 }
RouteTableAction::RouteTableAction(const RouteTableAction & that)
    : AbstractTableAction(that.text(), that.parent())
{
 init();
}

void RouteTableAction::init()
{
 log = new Logger("RouteTableAction");
 if(parent() == NULL)
     return;
 _systemName = new JTextField(12);
 _userName = new JTextField(22);
 _autoSystemName = new QCheckBox(tr("Automatically Generate System Name"));
 systemNameAuto = QString("")+metaObject()->className()+".AutoSystemName";
//    UserPreferencesManager pref;
 
 addFrame = NULL;
//    RouteTurnoutModel _routeTurnoutModel;
 
 soundFile = new JTextField(20);
 scriptFile = new JTextField(20);
 
 QFont f;
 f.setPointSize(9);
 sensor1mode = new QComboBox(/*sensorInputModes*/);
 sensor1mode->addItems(sensorInputModes);
 sensor1mode->setFont(f);
 sensor2mode = new QComboBox(/*sensorInputModes*/);
 sensor2mode->addItems(sensorInputModes);
 sensor2mode->setFont(f);
 sensor3mode = new QComboBox(/*sensorInputModes*/);
 sensor3mode->addItems(sensorInputModes);
 sensor3mode->setFont(f);
 timeDelay = new JTextField(5);
 
 cTurnoutStateBox = new QComboBox(/*turnoutInputModes*/);
 cTurnoutStateBox->addItems(turnoutInputModes);
 cTurnoutStateBox->setFont(f);
 cLockTurnoutStateBox = new QComboBox(/*lockTurnoutInputModes*/);
 cLockTurnoutStateBox->addItems(turnoutInputModes);
 cLockTurnoutStateBox->setFont(f);
 
 selGroup = NULL;
 allButton = NULL;   
 includedButton = NULL; 
   
 nameLabel = new QLabel("Route System Name:");
 userLabel = new QLabel("Route User Name:");
 fixedSystemName = new QLabel("xxxxxxxxxxx");
 
 createButton = new QPushButton("Add Route");
 editButton = new QPushButton("Edit Route");
 deleteButton = new QPushButton("Delete Route");
 updateButton = new QPushButton("Update Route");
 cancelButton = new QPushButton("Cancel");
 exportButton = new QPushButton("Export to Logix");
 status1 = new QLabel(createInst);
 status1->setFont(f);
 status2 = new QLabel(editInst);
 status2->setFont(f);
 
 p2xt = NULL;   // Turnout list table
 p2xs = NULL;   // Sensor list table
 
 curRoute = NULL;
 routeDirty = false;  // true to fire reminder to save work
 editMode = false;
 showAll = true;
}
#if 1
/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Routes
 */
/*protected*/ void RouteTableAction::createModel()
{
 m = new RouteTableDataModel(this);
}

RouteTableDataModel::RouteTableDataModel(RouteTableAction *parent)
 : BeanTableDataModel(parent)
{
 this->action = parent;
    log = new Logger("RouteTableDataModel");
    init();
}
 /*public*/ int RouteTableDataModel::columnCount(const QModelIndex &/*parent*/) const { return NUMCOLUMN+3;}

/*public*/ QVariant RouteTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
  if (col==VALUECOL) return "";  // no heading on "Set"
  if (col==SETCOL) return "";    // no heading on "Edit"
  if (col==ENABLECOL) return "Enabled";
  if (col==LOCKCOL) return "Locked";
  else return BeanTableDataModel::headerData(section,orientation,role);
 }
 return QVariant();
}
///*public*/ Class<?> getColumnClass(int col) {
//    if (col==SETCOL) return JButton.class;
//    if (col==ENABLECOL) return Boolean.class;
//    if (col==LOCKCOL) return Boolean.class;
//    else return super.getColumnClass(col);
//}
/*public*/ int RouteTableDataModel::getPreferredWidth(int col)
{
    if (col==SETCOL) return JTextField(6).getPreferredSize().width();
    if (col==ENABLECOL) return JTextField(6).getPreferredSize().width();
    if (col==LOCKCOL) return JTextField(6).getPreferredSize().width();
    else return BeanTableDataModel::getPreferredWidth(col);
}
/*public*/ Qt::ItemFlags RouteTableDataModel::flags(const QModelIndex &mindex) const
{
 int col = mindex.column();
 Qt::ItemFlags def = BeanTableDataModel::flags(mindex);
 if (col==USERNAMECOL) return  def | Qt::ItemIsEditable;
 if (col==SETCOL) return def | Qt::ItemIsEditable;
 if (col==ENABLECOL) return def | Qt::ItemIsUserCheckable;
 // Route lock is available if turnouts are lockable
 if (col==LOCKCOL)
 {
  Route* r;
  QString name = data(index(mindex.row(), (int)SYSNAMECOL),Qt::DisplayRole).toString();
  r = getBySystemName(name);
  return r->canLock()? def | Qt::ItemIsUserCheckable: Qt::NoItemFlags;
 }
 else return BeanTableDataModel::flags(mindex);
}

/*public*/ QVariant RouteTableDataModel::data(const QModelIndex &mindex, int role) const
{
 int col = mindex.column();
 int row = mindex.row();
 if(role == Qt::DisplayRole)
 {
    if (col==SETCOL) {
        return "Edit";
    }
 }
 if(role == Qt::CheckStateRole)
 {
  Route* r = (Route*)getBySystemName(data(index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString());
  if (col==ENABLECOL)
  {
//   if(((Route*)getBySystemName(data(createIndex(row, SYSNAMECOL),Qt::DisplayRole).toString()))->getEnabled())
   if(r->getEnabled())
    return Qt::Checked;
   else
    return Qt::Unchecked;
  }
  else if (col==LOCKCOL)
  {
   //   r = (Route*)getBySystemName(data(createIndex(row, SYSNAMECOL),Qt::DisplayRole).toString());
   if (r->canLock())
   {
    if( r->getLocked())
        return Qt::Checked;
    else
     return Qt::Unchecked;
   }
   else
   {
    // this covers the case when route was locked and lockable turnouts were removed from the route
    r->setLocked(false);
    return /*Boolean.valueOf (false)*/0;
   }
  }
 }
 return  BeanTableDataModel::data(mindex,role);
}

/*public*/ bool  RouteTableDataModel::setData(const QModelIndex &mindex, const QVariant &value, int role)
{
 int col = mindex.column();
 int row = mindex.row();
 if(role == Qt::CheckStateRole)
 {
  if (col==ENABLECOL)
  {
   // alternate
   Route* r = (Route*)getBySystemName(data(index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString());
   bool v = r->getEnabled();
   r->setEnabled(!v);
   return true;
  }
  else if (col==LOCKCOL)
  {
   // alternate
       Route* r = (Route*)getBySystemName(data(index(row, (int)SYSNAMECOL),Qt::DisplayRole).toString());
   bool v = r->getLocked();
   r->setLocked(!v);
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  if (col==USERNAMECOL)
  {
   //Directly changing the username should only be possible if the username was previously NULL or ""
   // check to see if user name already exists
   if ((value.toString())==("")) /*value = QVariant("");*/ return false;
   else
   {
    NamedBean* nB = getByUserName(value.toString());
    if (nB != NULL)
    {
     log->error("User name is not unique " + value.toString());
     QString msg;
     msg = tr("User Name \" %1 \" has already been used.").arg(value.toString());
//                JOptionPane.showMessageDialog(NULL, msg,
//                        AbstractTableAction.rb.getString("WarningTitle"),
//                        JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(NULL, tr("Error"), msg);
     return false;
    }
   }
   NamedBean* nBean = getBySystemName(sysNameList.at(mindex.row()));
   nBean->setUserName( value.toString());
   fireTableRowsUpdated(row, row);
  }
  else if (col==SETCOL)
  {
        // set up to edit. Use separate Thread so window is created on top
//        class WindowMaker implements Runnable {
//            int row;
//            WindowMaker(int r){
//                row = r;
//            }
//            /*public*/ void run() {
//                    //Thread.yield();
                    action->addPressed(NULL);
                    action->_systemName->setText(data(this->index(row, SYSNAMECOL),Qt::DisplayRole).toString());
        action->editPressed(); // don't really want to stop Route w/o user action
//                }
//            };
//        WindowMaker* t = new WindowMaker(row, action);
//        javax.swin((DefaultRoute*)g)->SwingUtilities.invokeLater(t);
    }
    else BeanTableDataModel::setData(mindex,value, role);
  }
 return false;
}

  /*public*/ void RouteTableDataModel::configureTable(JTable* table) {
//      table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
//      table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicpro((DefaultRoute*)g)->ValueRenderer());
//      table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicpro((DefaultRoute*)g)->ValueEditor());
//      super.configureTable(table);
   setColumnToHoldButton(table, SETCOL);
   BeanTableDataModel::configureTable(table);
  }

/**
 * Delete the bean after all the checking has been done.
 * <P>
 * Deactivate the light, then use the superclass to delete it.
 */
void RouteTableDataModel::doDelete(NamedBean* bean)
{
    ((Route*)bean)->deActivateRoute();
    BeanTableDataModel::doDelete(bean);
}

// want to update when enabled parameter changes
/*protected*/ bool RouteTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("Enabled")) return true;
    if (e->getPropertyName()==("Locked")) return true;
    else return BeanTableDataModel::matchPropertyName(e);
}

/*public*/ Manager* RouteTableDataModel::getManager() { return InstanceManager::routeManagerInstance(); }
/*public*/ Route* RouteTableDataModel::getBySystemName(QString name) const
{
 return InstanceManager::routeManagerInstance()->getBySystemName(name);
}
/*public*/ Route* RouteTableDataModel::getByUserName(QString name) {
    return InstanceManager::routeManagerInstance()->getByUserName(name);
}

/*protected*/ QString RouteTableDataModel::getMasterClassName()
{
 //return /*getClassName()*/metaObject()->className();
 return "jmri.jmrit.beantable.RouteTableAction";
}


/*public*/ void RouteTableDataModel::clickOn(NamedBean* t) {
   ((Route*)t)->setRoute();
}
/*public*/QString RouteTableDataModel::getValue(QString /*s*/) const
{
    return "Set";
}
/*public*/ QPushButton* RouteTableDataModel::configureButton() {
    return new QPushButton(" Set ");
}

/*protected*/ QString RouteTableDataModel::getBeanType(){
    return tr("BeanNameRoute");
}
/*Routes do not get references by other parts of the code, we therefore
do not need to worry about controlling how the username is changed
*/
/*protected*/ void RouteTableDataModel::showPopup(QMouseEvent* /*e*/){
}
//};
//}

/*protected*/ void RouteTableAction::setTitle() {
 f->setTitle("Route Table");
}

/*protected*/ QString RouteTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.RouteTable";
}
#endif
int RouteTableAction::sensorModeFromBox(QComboBox* box) {
    QString mode = box->currentText();
    int result = StringUtil::getStateFromName(mode, sensorInputModeValues.toVector(), sensorInputModes.toVector());
    
    if (result<0) {
        log->warn("unexpected mode string in sensorMode: "+mode);
        throw new IllegalArgumentException();
    }
    return result;
}

void RouteTableAction::setSensorModeBox(int mode, QComboBox* box) {
    QString result = StringUtil::getNameFromState(mode, sensorInputModeValues.toVector(), sensorInputModes);
    box->setCurrentIndex(box->findText(result));
}
   
int RouteTableAction::turnoutModeFromBox(QComboBox* box) {
    QString mode = box->currentText();
    int result = StringUtil::getStateFromName(mode, turnoutInputModeValues.toVector(), turnoutInputModes.toVector());
    
    if (result<0) {
        log->warn("unexpected mode string in turnoutMode: "+mode);
        throw new IllegalArgumentException();
    }
    return result;
}

void RouteTableAction::setTurnoutModeBox(int mode, QComboBox* box) {
    QString result = StringUtil::getNameFromState(mode, turnoutInputModeValues.toVector(), turnoutInputModes);
    box->setCurrentIndex(box->findText(result));
}



/*protected*/ void RouteTableAction::addPressed(ActionEvent* /*e*/)
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 if (editMode) 
 {
  cancelEdit();
 }
 TurnoutManager* tm = InstanceManager::turnoutManagerInstance();
 QStringList systemNameList = ((ProxyTurnoutManager*)tm)->getSystemNameList();
 qSort(systemNameList.begin(), systemNameList.end(), SystemNameComparator::compare);
 _turnoutList = new QList <RouteTurnout*> (); //systemNameList->size());
 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
  QString systemName = iter.next();
  QString userName = ((ProxyTurnoutManager*)tm)->getBySystemName(systemName)->getUserName();
  _turnoutList->append(new RouteTurnout(systemName, userName));
 }
    
 SensorManager* sm = InstanceManager::sensorManagerInstance();
 systemNameList = ((ProxySensorManager*)sm)->getSystemNameList();
 qSort(systemNameList.begin(), systemNameList.end(), SystemNameComparator::compare);
 _sensorList = new QList <RouteSensor*>(); // (systemNameList.size());
 iter = QStringListIterator(systemNameList);
 while (iter.hasNext())
 {
  QString systemName = iter.next();
  QString userName = ((ProxySensorManager*)sm)->getBySystemName(systemName)->getUserName();
  _sensorList->append(new RouteSensor(systemName, userName));
 }
 initializeIncludedList();
    
 // Set up window
 if (addFrame==NULL)
 {
  turnoutsAlignedSensor = new JmriBeanComboBox((Manager*)InstanceManager::sensorManagerInstance());
  turnoutsAlignedSensor->setFirstItemBlank(true);
  sensor1 = new JmriBeanComboBox((Manager*)InstanceManager::sensorManagerInstance());
  sensor1->setFirstItemBlank(true);
  sensor2 = new JmriBeanComboBox((Manager*)InstanceManager::sensorManagerInstance());
  sensor2->setFirstItemBlank(true);
  sensor3 = new JmriBeanComboBox((Manager*)InstanceManager::sensorManagerInstance());
  sensor3->setFirstItemBlank(true);
  cTurnout = new JmriBeanComboBox((Manager*)InstanceManager::turnoutManagerInstance());
  cTurnout->setFirstItemBlank(true);
  cLockTurnout = new JmriBeanComboBox((Manager*)InstanceManager::turnoutManagerInstance());
  cLockTurnout->setFirstItemBlank(true);

  addFrame = new JmriJFrame("Add/Edit Route", false, true);
  addFrame->setMinimumHeight(500);

  addFrame->addHelpMenu("package.jmri.jmrit.beantable.RouteAddEdit", true);
 #if 0
//  addFrame.setLocation(100,30);
  //addFrame.getContentPane().setLayout(new BoxLayout(addFrame.getContentPane(), BoxLayout.Y_AXIS));
  addFrame->resize(461,721);
  QMenuBar* menubar = new QMenuBar();
  addFrame->setMenuBar(menubar);
  QMenu* windowMenu = new QMenu("Window");
  menubar->addMenu(windowMenu);
  QFont font;
  font.setPixelSize(8);
  addFrame->setFont(font);
  QWidget* centralWidget = new QWidget(addFrame);
  centralWidget->setLayout(new QVBoxLayout());
  //Container contentPane = addFrame.getContentPane();
  centralWidgetLayout = new QVBoxLayout(centralWidget);
  // add system name
  QWidget* ps1 = new QWidget();
  ps1->setLayout(new QHBoxLayout());
  ps1->layout()->addWidget(nameLabel);
  ps1->layout()->addWidget(_systemName);
  ps1->layout()->addWidget(_autoSystemName);
//  _autoSystemName.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            autoSystemName();
//        }
//    });
  connect(_autoSystemName, SIGNAL(toggled(bool)), this, SLOT(autoSystemName()));
//  if(pref.getSimplePreferenceState(systemNameAuto))
//    _autoSystemName.setSelected(true);
  _systemName->setToolTip(tr("Enter system name for new Route, e.((DefaultRoute*)g)-> R12."));
  ps1->layout()->addWidget(fixedSystemName);
  fixedSystemName->setVisible(false);
  centralWidget->layout()->addWidget(ps1);
  // add user name
  QWidget* p = new QWidget();
  p->setLayout(new QHBoxLayout());
  p->layout()->addWidget(userLabel);
  p->layout()->addWidget(_userName);
  _userName->setToolTip("Enter user name for new Route, e.((DefaultRoute*)g)-> Clear Mainline.");
  centralWidget->layout()->addWidget(p);
  // add Turnout Display Choice
  QWidget* py = new QWidget();
  py->setLayout(new QHBoxLayout());
  py->layout()->addWidget(new QLabel("Show "));
  selGroup = new QButtonGroup();
  allButton = new QRadioButton("All");
  allButton->setChecked(showAll);
  selGroup->addButton(allButton);
  py->layout()->addWidget(allButton);
//  allButton.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            // Setup for display of all Turnouts, if needed
//            if (!showAll) {
//                showAll = true;
//                _routeTurnoutModel.fireTableDataChanged();
//                _routeSensorModel.fireTableDataChanged();
//            }
//        }
//    });
  connect(allButton, SIGNAL(toggled(bool)), this, SLOT(on_allButton_toggled(bool)));
 includedButton = new QRadioButton("Included");
 includedButton->setChecked(false);
 selGroup->addButton(includedButton);
 py->layout()->addWidget(includedButton);
//includedButton.addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            // Setup for display of included Turnouts only, if needed
//            if (showAll) {
//                showAll = false;
//                initializeIncludedList();
//                _routeTurnoutModel.fireTableDataChanged();
//                _routeSensorModel.fireTableDataChanged();
//            }
//        }
//    });
 connect(includedButton, SIGNAL(toggled(bool)), this, SLOT(on_includedButton_toggled()));
 py->layout()->addWidget(new QLabel("  Turnouts and Sensors"));
 centralWidget->layout()->addWidget(py);
 centralWidget->layout()->setAlignment(py,Qt::AlignRight);

 // add turnout table
 p2xt = new QHBoxLayout();
 QVBoxLayout* p21t = new QVBoxLayout();
 p21t->addWidget(new QLabel("Please select "));
 p21t->addWidget(new QLabel(" Turnouts to "));
 p21t->addWidget(new QLabel(" be included "));
 p21t->addWidget(new QLabel(" in this Route::"));
 p2xt->addLayout(p21t);
_routeTurnoutModel = new RouteTurnoutModel(this);
            //QTableView routeTurnoutTable* = jmri.util.JTableUtil.sortableDataModel(_routeTurnoutModel);
            //try {
            //    jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)routeTurnoutTable.getModel());
            //    tmodel.setColumnComparator(Strin((DefaultRoute*)g)->class, new jmri.util.SystemNameComparator());
            //    tmodel.setSortingStatus(RouteTurnoutModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
            //} catch (ClassCastException e3) {}  // if not a sortable table model
QTableView* routeTurnoutTable = new QTableView();
routeTurnoutTable->setModel(_routeTurnoutModel);
routeTurnoutTable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
//routeTurnoutTable.setRowSelectionAllowed(false);
//routeTurnoutTable.setPreferredScrollableViewportSize(new
//                                                java.awt.Dimension(480,80));
routeTurnoutTable->setMinimumSize(480,80);
//routeTurnoutTable->resize(480,80);

ROW_HEIGHT = routeTurnoutTable->rowHeight(0);
QComboBox* stateTCombo = new QComboBox();
stateTCombo->addItem(SET_TO_CLOSED);
stateTCombo->addItem(SET_TO_THROWN);
stateTCombo->addItem(SET_TO_TOGGLE);
//TableColumnModel routeTurnoutColumnModel = routeTurnoutTable.getColumnModel();
//TableColumn includeColumnT = routeTurnoutColumnModel.
//                                    getColumn(RouteTurnoutModel.INCLUDE_COLUMN);
//includeColumnT.setResizable(false);
//includeColumnT.setMinWidth(50);
//includeColumnT.setMaxWidth(60);
routeTurnoutTable->setColumnWidth(RouteTurnoutModel::INCLUDE_COLUMN, 50);
//TableColumn sNameColumnT = routeTurnoutColumnModel.
//                                    getColumn(RouteTurnoutModel.SNAME_COLUMN);
//sNameColumnT.setResizable(true);
//sNameColumnT.setMinWidth(75);
//sNameColumnT.setMaxWidth(95);
routeTurnoutTable->setColumnWidth(RouteTurnoutModel::SNAME_COLUMN, 75);
//TableColumn uNameColumnT = routeTurnoutColumnModel.
//                                    getColumn(RouteTurnoutModel.UNAME_COLUMN);
//uNameColumnT.setResizable(true);
//uNameColumnT.setMinWidth(210);
//uNameColumnT.setMaxWidth(260);
routeTurnoutTable->setColumnWidth(RouteTurnoutModel::UNAME_COLUMN, 210);
//TableColumn stateColumnT = routeTurnoutColumnModel.
//                                    getColumn(RouteTurnoutModel.STATE_COLUMN);
//stateColumnT.setCellEditor(new DefaultCellEditor(stateTCombo));
//stateColumnT.setResizable(false);
//stateColumnT.setMinWidth(90);
//stateColumnT.setMaxWidth(100);
routeTurnoutTable->setColumnWidth(RouteTurnoutModel::STATE_COLUMN, 90);
//_routeTurnoutScrollPane = new QScrollArea();
//_routeTurnoutScrollPane->setWidget(routeTurnoutTable);
p2xt->layout()->addWidget(routeTurnoutTable/*,BorderLayout.CENTER*/);
p2xt->layout()->setAlignment(routeTurnoutTable, Qt::AlignHCenter);
centralWidgetLayout->addLayout(p2xt);

 // add sensor table
p2xs = new QHBoxLayout();
QVBoxLayout* p21s = new QVBoxLayout();
p21s->addWidget(new QLabel("Please select "));
p21s->addWidget(new QLabel(" Sensors to "));
p21s->addWidget(new QLabel(" be included "));
p21s->addWidget(new QLabel(" in this Route::"));
p2xs->addLayout(p21s);
_routeSensorModel = new RouteSensorModel(this);
//JTable routeSensorTable = jmri.util.JTableUtil.sortableDataModel(_routeSensorModel);
//try {
//    jmri.util.com.sun.TableSorter tmodel = ((jmri.util.com.sun.TableSorter)routeSensorTable.getModel());
//    tmodel.setColumnComparator(Strin((DefaultRoute*)g)->class, new jmri.util.SystemNameComparator());
//    tmodel.setSortingStatus(RouteSensorModel.SNAME_COLUMN, jmri.util.com.sun.TableSorter.ASCENDING);
//} catch (ClassCastException e3) {}  // if not a sortable table model
//routeSensorTable.setRowSelectionAllowed(false);
//routeSensorTable.setPreferredScrollableViewportSize(new java.awt.Dimension(480,80));
QTableView* routeSensorTable = new QTableView();
routeSensorTable->setModel(_routeSensorModel);
routeSensorTable->setMinimumSize(480,80);
routeSensorTable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Maximum);
//routeSensorTable->resize(480,80);
QComboBox* stateSCombo = new QComboBox();
stateSCombo->addItem(SET_TO_ACTIVE);
stateSCombo->addItem(SET_TO_INACTIVE);
stateSCombo->addItem(SET_TO_TOGGLE);
//TableColumnModel routeSensorColumnModel = routeSensorTable.getColumnModel();
//TableColumn includeColumnS = routeSensorColumnModel.
//                                    getColumn(RouteSensorModel.INCLUDE_COLUMN);
//includeColumnS.setResizable(false);
//includeColumnS.setMinWidth(50);
//includeColumnS.setMaxWidth(60);
routeSensorTable->horizontalHeader()->resizeSection(RouteSensorModel::INCLUDE_COLUMN, 50);
//TableColumn sNameColumnS = routeSensorColumnModel.
//                                    getColumn(RouteSensorModel.SNAME_COLUMN);
//sNameColumnS.setResizable(true);
//sNameColumnS.setMinWidth(75);
//sNameColumnS.setMaxWidth(95);
routeSensorTable->horizontalHeader()->resizeSection(RouteSensorModel::SNAME_COLUMN, 76);
//TableColumn uNameColumnS = routeSensorColumnModel.
//                                    getColumn(RouteSensorModel.UNAME_COLUMN);
//uNameColumnS.setResizable(true);
//uNameColumnS.setMinWidth(210);
//uNameColumnS.setMaxWidth(260);
routeSensorTable->horizontalHeader()->resizeSection(RouteSensorModel::UNAME_COLUMN, 210);
//TableColumn stateColumnS = routeSensorColumnModel.
//                                    getColumn(RouteSensorModel.STATE_COLUMN);
//stateColumnS.setCellEditor(new DefaultCellEditor(stateSCombo));
//stateColumnS.setResizable(false);
//stateColumnS.setMinWidth(90);
//stateColumnS.setMaxWidth(100);
routeSensorTable->horizontalHeader()->resizeSection(RouteSensorModel::STATE_COLUMN, 90);
//_routeSensorScrollPane = new QScrollArea();
p2xs->addWidget(routeSensorTable);
centralWidgetLayout->addLayout(p2xs);
//_routeSensorScrollPane->setWidget(routeSensorTable);

// Enter filenames for sound, script

QHBoxLayout* p25 = new QHBoxLayout();
p25->addWidget(new QLabel("Play sound file:"));
QPushButton* ss = new QPushButton("Set");
//ss.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        setSoundPressed();
//    }
//});
connect(ss, SIGNAL(clicked()), this, SLOT(setSoundPressed()));
p25->addWidget(ss);
p25->addWidget(soundFile);
//            contentPane.add(p25);

//            QWidget* p26 = new QWidget();
//            p26->setLayout(new QHBoxLayout());
p25->addWidget(new QLabel("Run script:"));
ss = new QPushButton("Set");
//ss.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        setScriptPressed();
//    }
//});
p25->addWidget(ss);
p25->addWidget(scriptFile);
centralWidgetLayout->addLayout(p25);

//add turnouts aligned sensor
centralWidgetLayout->addWidget(new QLabel(tr("Enter Sensor that Activates when Route Turnouts are correctly aligned (optional):")));
QHBoxLayout* p31 = new QHBoxLayout();

p31->addWidget(turnoutsAlignedSensor);
turnoutsAlignedSensor->setFirstItemBlank(true);
turnoutsAlignedSensor->setSelectedBean(NULL);
turnoutsAlignedSensor->setToolTip("Enter a Sensor system name or nothing");
centralWidgetLayout->addLayout(p31);

// add control sensor table
QVBoxLayout* p3 = new QVBoxLayout();
QFrame* ps = new QFrame(centralWidget);
ps->setObjectName(QString::fromUtf8("ps"));
ps->setFrameShape(QFrame::Box);
ps->setFrameShadow(QFrame::Raised);
ps->setLineWidth(2);
QVBoxLayout* pv3 = new QVBoxLayout(ps);
pv3->addWidget(new QLabel("Enter Sensors that trigger this Route (optional)"));

QHBoxLayout* p32 = new QHBoxLayout();
p32->addWidget(new QLabel("Sensors: "));
//Border pSBorder = BorderFactory.createEtchedBorder();
QFrame* ps2 = new QFrame();
//pS.setBorder(pSBorder);
ps2->setFrameShape(QFrame::StyledPanel);
ps2->setFrameShadow(QFrame::Raised);
QHBoxLayout* horizontalLayout_8 = new QHBoxLayout(ps2);
QHBoxLayout*horizontalLayout_7 = new QHBoxLayout();

horizontalLayout_7->addWidget(sensor1);
horizontalLayout_7->addWidget(sensor1mode);
horizontalLayout_8->addLayout(horizontalLayout_7);
p32->addWidget(ps2);
pv3->addLayout(p32);

QFrame* pS3 = new QFrame();
pS3->setLayout(new QHBoxLayout());
//pS.setBorder(pSBorder);
pS3->setFrameStyle(QFrame::Box | QFrame::Raised);
pS3->setLineWidth(2);
pS3->layout()->addWidget(sensor2);
pS3->layout()->addWidget(sensor2mode);
p32->layout()->addWidget(pS3);

QFrame* pS4 = new QFrame();
pS4->setLayout(new QHBoxLayout());
//pS.setBorder(pSBorder);
pS4->setFrameStyle(QFrame::Box | QFrame::Raised);
pS4->setLineWidth(2);
pS4->layout()->addWidget(sensor3);
pS4->layout()->addWidget(sensor3mode);
p32->layout()->addWidget(pS4);

sensor1->setFirstItemBlank(true);
sensor2->setFirstItemBlank(true);
sensor3->setFirstItemBlank(true);
sensor1->setSelectedBean(NULL);
sensor2->setSelectedBean(NULL);
sensor3->setSelectedBean(NULL);
QString sensorHint = tr("Enter a Sensor system name or nothing");
sensor1->setToolTip(sensorHint);
sensor2->setToolTip(sensorHint);
sensor3->setToolTip(sensorHint);
p3->addLayout(p32);

// add control turnout
QWidget* p33 = new QWidget();
            p33->setLayout(new QHBoxLayout());
p33->layout()->addWidget(new QLabel("Enter a Turnout that triggers this Route (optional)"));
centralWidgetLayout->addWidget(p33);
QWidget* p34 = new QWidget();
p34->setLayout(new QHBoxLayout());
p34->layout()->addWidget(new QLabel("Turnout: "));
p34->layout()->addWidget(cTurnout);
cTurnout->setFirstItemBlank(true);
cTurnout->setSelectedBean(NULL);
cTurnout->setToolTip(tr("Enter a Turnout system name (real or phantom)"));
p34->layout()->addWidget(new QLabel("   Condition: "));
cTurnoutStateBox->setToolTip(tr("Setting control Turnout to selected state will trigger Route"));
p34->layout()->addWidget(cTurnoutStateBox);
p3->addWidget(p34);
// add added delay
//       QWidget* p35 = new QWidget();
//      p35.add(new QLabel("Enter added delay between Turnout Commands (optional)"));
//       p3.add(p35);
QWidget* p36 = new QWidget();
p36->setLayout(new QHBoxLayout());
p36->layout()->addWidget(new QLabel("Enter additional delay between Turnout Commands (optional), added delay: "));
p36->layout()->addWidget(timeDelay);
timeDelay->setText("0");
timeDelay->setToolTip("Enter time to add to the default of 250 milliseconds between turnout commands");
p36->layout()->addWidget(new QLabel(" (milliseconds) "));
p3->addWidget(p36);

// complete this panel
//Border p3Border = BorderFactory.createEtchedBorder();
//p3.setBorder(p3Border);
centralWidgetLayout->addLayout(p3);

// add lock control table
QWidget* p4 = new QWidget();
p4->setLayout(new QVBoxLayout(p4/*, BoxLayout.Y_AXIS*/));
// add lock control turnout
QWidget* p43 = new QWidget(); p43->setLayout(new QHBoxLayout());
p43->layout()->addWidget(new QLabel("Enter a Turnout that controls the lock for this Route (optional)"));
p4->layout()->addWidget(p43);
QWidget* p44 = new QWidget();
p44->setLayout(new QHBoxLayout());
p44->layout()->addWidget(new QLabel("Turnout: "));
p44->layout()->addWidget(cLockTurnout);
cLockTurnout->setFirstItemBlank(true);
cLockTurnout->setSelectedBean(NULL);
cLockTurnout->setToolTip("Enter a Turnout system name (real or phantom)");
p44->layout()->addWidget(new QLabel("   Condition: "));
cLockTurnoutStateBox->setToolTip("Setting control Turnout to selected state will lock Route");
p44->layout()->addWidget(cLockTurnoutStateBox);
p4->layout()->addWidget(p44);
// complete this panel
//Border p4Border = BorderFactory.createEtchedBorder();
//p4.setBorder(p4Border);
p4->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
centralWidget->layout()->addWidget(p4);

// add notes panel
QWidget* pa = new QWidget();
pa->setLayout(new QVBoxLayout(pa/*, BoxLayout.Y_AXIS*/));
QWidget* p1 = new QWidget();
p1->setLayout(new QHBoxLayout());
p1->layout()->addWidget(status1);
QWidget* p2 = new QWidget();
p2->setLayout(new QHBoxLayout());
p2->layout()->addWidget(status2);
pa->layout()->addWidget(p1);
pa->layout()->addWidget(p2);
//Border pBorder = BorderFactory.createEtchedBorder();
//pa.setBorder(pBorder);
pa->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
centralWidget->layout()->addWidget(pa);
// add buttons - Add Route button
QWidget* pb = new QWidget();
pb->setLayout(new QHBoxLayout());
pb->layout()->addWidget(createButton);
//createButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        createPressed(e);
//    }
//});
connect(createButton, SIGNAL(clicked()), this, SLOT(createPressed()));
createButton->setToolTip("Add a new Route using data entered above");
// Edit Route button
pb->layout()->addWidget(editButton);
//editButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        editPressed(e);
//    }
//});
            connect(editButton, SIGNAL(clicked()), this, SLOT(editPressed()));
editButton->setToolTip("Set up to edit Route in System Name");
// Delete Route button
pb->layout()->addWidget(deleteButton);
//deleteButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        deletePressed(e);
//    }
//});
            connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
deleteButton->setToolTip("Delete the Route in System Name");
// Update Route button
pb->layout()->addWidget(updateButton);
//updateButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        updatePressed(e, false);
//    }
//});
connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(updatePressed(bool)));
updateButton->setToolTip("Change this Route and leave Edit mode");
// Cancel button
pb->layout()->addWidget(cancelButton);
//cancelButton.addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        cancelPressed(e);
//    }
//});
connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));
cancelButton->setToolTip("Leave Edit mode without changing the Route");
// Export button
pb->layout()->addWidget(exportButton);
//exportButton->layout()->addWidgetActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        exportPressed(e);
//    }
//});
exportButton->setToolTip("Export Route to Logix Conditionals for further enhancement");

// Show the initial buttons, and hide the others
addFrame->setCentralWidget(centralWidget);
exportButton->setVisible(false);
cancelButton->setVisible(false);
updateButton->setVisible(true);
editButton->setVisible(true);
createButton->setVisible(true);
deleteButton->setVisible(false);
centralWidget->layout()->addWidget(pb);
// pack and release space
//addFrame.pack();
//p2xsSpace->setVisible(false);
//p2xtSpace->setVisible(false);
}
//    // set listener for window closing
//    addFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                // remind to save, if Route was created or edited
//                if (routeDirty) {
//                    InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                        showInfoMessage("Reminder","Remember to save your Route information.",getClassName(), "remindSaveRoute");
//                    routeDirty = false;
//                }
//                // hide addFrame
//                addFrame->setVisible(false);
//                // if in Edit, cancel edit mode
//                if (editMode) {
//                    cancelEdit();
//                }
//                _routeSensorModel.dispose();
//                _routeTurnoutModel.dispose();
//            }
//        });
    // display the window
    addFrame->setVisible(true);
    autoSystemName();
    //_routeTurnoutModel.fireTableDataChanged();
    //_routeSensorModel.fireTableDataChanged();
#else
  if (addFrame->objectName().isEmpty())
   addFrame->setObjectName(QString::fromUtf8("addFrame"));
  addFrame->resize(461,721);
  QDesktopWidget* screen = new QDesktopWidget();
  addFrame->setMaximumHeight(screen->height()-100);
  QFont font;
  font.setPointSize(9);
  addFrame->setFont(font);
  centralWidget = new QWidget(/*addFrame*/);
  centralWidget->setFont(font);
  centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
  verticalLayout_6 = new QVBoxLayout(centralWidget);
  verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
  horizontalLayout_systemName = new QHBoxLayout();
  horizontalLayout_systemName->setObjectName(QString::fromUtf8("horizontalLayout_systemName"));
  label = new QLabel(centralWidget);
  label->setObjectName(QString::fromUtf8("label"));
  label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

  horizontalLayout_systemName->addWidget(label);

  _systemName = new JTextField(centralWidget);
  _systemName->setObjectName(QString::fromUtf8("_systemName"));
  QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(_systemName->sizePolicy().hasHeightForWidth());
  _systemName->setSizePolicy(sizePolicy);
  _systemName->setMaximumSize(QSize(80, 16777215));
  _systemName->setMaxLength(12);

  horizontalLayout_systemName->addWidget(_systemName);

  fixedSystemName = new QLabel(centralWidget);
  fixedSystemName->setObjectName(QString::fromUtf8("fixedSystemName"));

  horizontalLayout_systemName->addWidget(fixedSystemName);

  _autoSystemName = new QCheckBox(centralWidget);
  _autoSystemName->setObjectName(QString::fromUtf8("_autoSystemName"));

  horizontalLayout_systemName->addWidget(_autoSystemName);


  verticalLayout_6->addLayout(horizontalLayout_systemName);

  horizontalLayout_userName = new QHBoxLayout();
  horizontalLayout_userName->setObjectName(QString::fromUtf8("horizontalLayout_userName"));
  label_2 = new QLabel(centralWidget);
  label_2->setObjectName(QString::fromUtf8("label_2"));
  label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

  horizontalLayout_userName->addWidget(label_2);

  _userName = new JTextField(centralWidget);
  _userName->setObjectName(QString::fromUtf8("_userName"));
  sizePolicy.setHeightForWidth(_userName->sizePolicy().hasHeightForWidth());
  _userName->setSizePolicy(sizePolicy);
  _userName->setMaximumSize(QSize(150, 16777215));
  _userName->setMaxLength(22);

  horizontalLayout_userName->addWidget(_userName);


  verticalLayout_6->addLayout(horizontalLayout_userName);


  horizontalLayout_show = new QHBoxLayout();
  horizontalLayout_show->setObjectName(QString::fromUtf8("horizontalLayout_show"));
  label_3 = new QLabel(centralWidget);
  label_3->setObjectName(QString::fromUtf8("label_3"));
  label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

  horizontalLayout_show->addWidget(label_3);

  allButton = new QRadioButton(centralWidget);
  allButton->setObjectName(QString::fromUtf8("allButton"));

  horizontalLayout_show->addWidget(allButton);

  includedButton = new QRadioButton(centralWidget);
  includedButton->setObjectName(QString::fromUtf8("includeButton"));

  horizontalLayout_show->addWidget(includedButton);

  label_4 = new QLabel(centralWidget);
  label_4->setObjectName(QString::fromUtf8("label_4"));

  horizontalLayout_show->addWidget(label_4);


  verticalLayout_6->addLayout(horizontalLayout_show);
  p2xt = new QHBoxLayout();
  p2xt->setObjectName(QString::fromUtf8("p2xt"));
  p2xtSpace = new QLabel(centralWidget);
  p2xtSpace->setObjectName(QString::fromUtf8("p2xtSpace"));

  p2xt->addWidget(p2xtSpace);

  verticalLayout = new QVBoxLayout();
  verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
  label_9 = new QLabel(centralWidget);
  label_9->setObjectName(QString::fromUtf8("label_9"));

  verticalLayout->addWidget(label_9);

  label_5 = new QLabel(centralWidget);
  label_5->setObjectName(QString::fromUtf8("label_5"));
  label_5->setFont(font);

  verticalLayout->addWidget(label_5);

  label_6 = new QLabel(centralWidget);
  label_6->setObjectName(QString::fromUtf8("label_6"));
  label_6->setFont(font);

  verticalLayout->addWidget(label_6);

  label_7 = new QLabel(centralWidget);
  label_7->setObjectName(QString::fromUtf8("label_7"));
  label_7->setFont(font);

  verticalLayout->addWidget(label_7);

  label_8 = new QLabel(centralWidget);
  label_8->setObjectName(QString::fromUtf8("label_8"));
  label_8->setFont(font);

  verticalLayout->addWidget(label_8);


  p2xt->addLayout(verticalLayout);

  routeTurnoutTable = new QTableView(centralWidget);
  routeTurnoutTable->setObjectName(QString::fromUtf8("routeTurnoutTable"));
  QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(routeTurnoutTable->sizePolicy().hasHeightForWidth());
  routeTurnoutTable->setSizePolicy(sizePolicy1);
  routeTurnoutTable->setFont(font);
  p2xt->addWidget(routeTurnoutTable);

  verticalLayout_6->addLayout(p2xt);

  p2xs = new QHBoxLayout();
  p2xs->setObjectName(QString::fromUtf8("p2xs"));
  p2xsSpace = new QLabel(centralWidget);
  p2xsSpace->setObjectName(QString::fromUtf8("p2xsSpace"));

  p2xt->addWidget(p2xsSpace);

  verticalLayout_2 = new QVBoxLayout();
  verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
  label_10 = new QLabel(centralWidget);
  label_10->setObjectName(QString::fromUtf8("label_10"));

  verticalLayout_2->addWidget(label_10);

  label_11 = new QLabel(centralWidget);
  label_11->setObjectName(QString::fromUtf8("label_11"));
  label_11->setFont(font);

  verticalLayout_2->addWidget(label_11);

  label_12 = new QLabel(centralWidget);
  label_12->setObjectName(QString::fromUtf8("label_12"));
  label_12->setFont(font);

  verticalLayout_2->addWidget(label_12);

  label_13 = new QLabel(centralWidget);
  label_13->setObjectName(QString::fromUtf8("label_13"));
  label_13->setFont(font);

  verticalLayout_2->addWidget(label_13);

  label_14 = new QLabel(centralWidget);
  label_14->setObjectName(QString::fromUtf8("label_14"));
  label_14->setFont(font);

  verticalLayout_2->addWidget(label_14);


  p2xs->addLayout(verticalLayout_2);

  routeSensorTable = new QTableView(centralWidget);
  routeSensorTable->setObjectName(QString::fromUtf8("routeSensorTable"));
  sizePolicy1.setHeightForWidth(routeSensorTable->sizePolicy().hasHeightForWidth());
  routeSensorTable->setSizePolicy(sizePolicy1);
  routeSensorTable->setFont(font);

  p2xs->addWidget(routeSensorTable);


  verticalLayout_6->addLayout(p2xs);

  horizontalLayout_sound_script = new QHBoxLayout();
  horizontalLayout_sound_script->setObjectName(QString::fromUtf8("horizontalLayout_sound_script"));
  label_15 = new QLabel(centralWidget);
  label_15->setObjectName(QString::fromUtf8("label_15"));

  horizontalLayout_sound_script->addWidget(label_15);

  setSound = new QPushButton(centralWidget);
  setSound->setObjectName(QString::fromUtf8("pushButton"));
  setSound->setFont(font);

  horizontalLayout_sound_script->addWidget(setSound);

  soundFile = new JTextField(centralWidget);
  soundFile->setObjectName(QString::fromUtf8("soundFile"));

  horizontalLayout_sound_script->addWidget(soundFile);

  label_16 = new QLabel(centralWidget);
  label_16->setObjectName(QString::fromUtf8("label_16"));

  horizontalLayout_sound_script->addWidget(label_16);

  setScript = new QPushButton(centralWidget);
  setScript->setObjectName(QString::fromUtf8("pushButton_2"));
  setScript->setFont(font);

  horizontalLayout_sound_script->addWidget(setScript);

  scriptFile = new JTextField(centralWidget);
  scriptFile->setObjectName(QString::fromUtf8("scriptFile"));
  scriptFile->setMaxLength(20);

  horizontalLayout_sound_script->addWidget(scriptFile);

  verticalLayout_6->addLayout(horizontalLayout_sound_script);

  sensorThatActivates = new QLabel(centralWidget);
  sensorThatActivates->setObjectName(QString::fromUtf8("sensorThatActivates"));

  verticalLayout_6->addWidget(sensorThatActivates);

  p31 = new QHBoxLayout();
  p31->setObjectName(QString::fromUtf8("p31"));
  //turnoutsAlignedSensor = new QComboBox(centralWidget);
  turnoutsAlignedSensor->setFirstItemBlank(true);
  turnoutsAlignedSensor->setSelectedBean(NULL);
  turnoutsAlignedSensor->setObjectName(QString::fromUtf8("turnoutsAlignedSensor"));
  turnoutsAlignedSensor->setMaximumSize(QSize(100, 16777215));
  turnoutsAlignedSensor->setFont(font);

  p31->addWidget(turnoutsAlignedSensor);


  verticalLayout_6->addLayout(p31);

  ps = new QFrame(centralWidget);
  ps->setFont(font);
  ps->setObjectName(QString::fromUtf8("ps"));
  QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
  sizePolicy2.setHorizontalStretch(0);
  sizePolicy2.setVerticalStretch(0);
  sizePolicy2.setHeightForWidth(ps->sizePolicy().hasHeightForWidth());
  ps->setSizePolicy(sizePolicy2);
  ps->setFrameShape(QFrame::Box);
  ps->setFrameShadow(QFrame::Raised);
  ps->setLineWidth(2);
  verticalLayout_3 = new QVBoxLayout(ps);
  verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
  sensorsThatTrigger = new QLabel(ps);
  sensorsThatTrigger->setObjectName(QString::fromUtf8("sensorsThatTrigger"));
  sensorsThatTrigger->setFont(font);

  verticalLayout_3->addWidget(sensorsThatTrigger);

  horizontalLayout_4 = new QHBoxLayout();
  horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
  label_19 = new QLabel(ps);
  label_19->setObjectName(QString::fromUtf8("label_19"));
  label_19->setFont(font);

  horizontalLayout_4->addWidget(label_19);

  frame_2 = new QFrame(ps);
  frame_2->setObjectName(QString::fromUtf8("frame_2"));
  frame_2->setFrameShape(QFrame::StyledPanel);
  frame_2->setFrameShadow(QFrame::Raised);
  frame_2->setFont(font);
  horizontalLayout_8 = new QHBoxLayout(frame_2);
  horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
  horizontalLayout_7 = new QHBoxLayout();
  horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
  //sensor1 = new JmriBeanComboBox(frame_2);
  sensor1->setObjectName(QString::fromUtf8("sensor1"));
  sensor1->setFont(font);

  horizontalLayout_7->addWidget(sensor1);

  //sensor1mode = new QComboBox(frame_2);
  sensor1mode->setObjectName(QString::fromUtf8("sensor1mode"));
  sensor1mode->setFont(font);

  horizontalLayout_7->addWidget(sensor1mode);


  horizontalLayout_8->addLayout(horizontalLayout_7);


  horizontalLayout_4->addWidget(frame_2);

  frame_3 = new QFrame(ps);
  frame_3->setObjectName(QString::fromUtf8("frame_3"));
  frame_3->setFrameShape(QFrame::StyledPanel);
  frame_3->setFrameShadow(QFrame::Raised);
  frame_3->setFont(font);
  horizontalLayout_9 = new QHBoxLayout(frame_3);
  horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
  horizontalLayout_11 = new QHBoxLayout();
  horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
  //sensor2 = new JmriBeanComboBox(frame_3);
  sensor2->setObjectName(QString::fromUtf8("sensor2"));
  sensor2->setFont(font);

  horizontalLayout_11->addWidget(sensor2);

  //sensor2mode = new QComboBox(frame_3);
  sensor2mode->setObjectName(QString::fromUtf8("s"));
  sensor2mode->setFont(font);

  horizontalLayout_11->addWidget(sensor2mode);


  horizontalLayout_9->addLayout(horizontalLayout_11);


  horizontalLayout_4->addWidget(frame_3);

  frame_4 = new QFrame(ps);
  frame_4->setObjectName(QString::fromUtf8("frame_4"));
  frame_4->setFrameShape(QFrame::StyledPanel);
  frame_4->setFrameShadow(QFrame::Raised);
  frame_4->setFont(font);
  horizontalLayout_12 = new QHBoxLayout(frame_4);
  horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
  horizontalLayout_13 = new QHBoxLayout();
  horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
  //sensor3 = new JmriBeanComboBox(frame_4);
  sensor3->setObjectName(QString::fromUtf8("sensor3"));
  sensor3->setFont(font);

  horizontalLayout_13->addWidget(sensor3);

  //sensor3mode = new QComboBox(frame_4);
  sensor3mode->setObjectName(QString::fromUtf8("sensor3mode"));
  sensor3mode->setFont(font);

  horizontalLayout_13->addWidget(sensor3mode);


  horizontalLayout_12->addLayout(horizontalLayout_13);


  horizontalLayout_4->addWidget(frame_4);


  verticalLayout_3->addLayout(horizontalLayout_4);

  label_20 = new QLabel(ps);
  label_20->setObjectName(QString::fromUtf8("label_20"));
  label_20->setFont(font);

  verticalLayout_3->addWidget(label_20);

  horizontalLayout_10 = new QHBoxLayout();
  horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
  label_21 = new QLabel(ps);
  label_21->setObjectName(QString::fromUtf8("label_21"));
  label_21->setFont(font);

  horizontalLayout_10->addWidget(label_21);

  //cTurnout = new QComboBox(ps);
  cTurnout->setObjectName(QString::fromUtf8("cTurnout"));
  cTurnout->setFont(font);

  horizontalLayout_10->addWidget(cTurnout);

  label_22 = new QLabel(ps);
  label_22->setObjectName(QString::fromUtf8("label_22"));
  label_22->setFont(font);

  horizontalLayout_10->addWidget(label_22);

  //cTurnoutStateBox = new QComboBox(ps);
  cTurnoutStateBox->setObjectName(QString::fromUtf8("comboBox_5"));
  cTurnoutStateBox->setFont(font);

  horizontalLayout_10->addWidget(cTurnoutStateBox);


  verticalLayout_3->addLayout(horizontalLayout_10);

  horizontalLayout = new QHBoxLayout();
  horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
  label_23 = new QLabel(ps);
  label_23->setObjectName(QString::fromUtf8("label_23"));
  label_23->setFont(font);

  horizontalLayout->addWidget(label_23);

  timeDelay = new JTextField(5, ps);
  timeDelay->setObjectName(QString::fromUtf8("timeDelay"));
  QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
  sizePolicy3.setHorizontalStretch(0);
  sizePolicy3.setVerticalStretch(0);
  sizePolicy3.setHeightForWidth(timeDelay->sizePolicy().hasHeightForWidth());
  timeDelay->setSizePolicy(sizePolicy3);
  timeDelay->setMaximumSize(QSize(50, 16777215));
  timeDelay->setAlignment(Qt::AlignCenter);
  timeDelay->setFont(font);

  horizontalLayout->addWidget(timeDelay);


  verticalLayout_3->addLayout(horizontalLayout);


  verticalLayout_6->addWidget(ps);

  frame = new QFrame(centralWidget);
  frame->setFont(font);
  frame->setObjectName(QString::fromUtf8("frame"));
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);
  verticalLayout_4 = new QVBoxLayout(frame);
  verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
  label_17 = new QLabel(frame);
  label_17->setObjectName(QString::fromUtf8("label_17"));
  label_17->setFont(font);

  verticalLayout_4->addWidget(label_17);

  horizontalLayout_2 = new QHBoxLayout();
  horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
  label_18 = new QLabel(frame);
  label_18->setObjectName(QString::fromUtf8("label_18"));
  label_18->setFont(font);

  horizontalLayout_2->addWidget(label_18);

  //cLockTurnout = new QComboBox(frame);
  cLockTurnout->setObjectName(QString::fromUtf8("comboBox"));
  cLockTurnout->setFont(font);

  horizontalLayout_2->addWidget(cLockTurnout);

  label_24 = new QLabel(frame);
  label_24->setObjectName(QString::fromUtf8("label_24"));
  label_24->setFont(font);

  horizontalLayout_2->addWidget(label_24);

  //cLockTurnoutStateBox = new QComboBox(frame);
  cLockTurnoutStateBox->setObjectName(QString::fromUtf8("comboBox_2"));
  cLockTurnoutStateBox->setFont(font);

  horizontalLayout_2->addWidget(cLockTurnoutStateBox);


  verticalLayout_4->addLayout(horizontalLayout_2);


  verticalLayout_6->addWidget(frame);

  verticalLayout_5 = new QVBoxLayout();
  verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

  //status1 = new QLabel(centralWidget);
  status1->setObjectName(QString::fromUtf8("lblUpdateInst"));
  status1->setFont(font);

  verticalLayout_5->addWidget(status1);

  //status2 = new QLabel(centralWidget);
  status2->setObjectName(QString::fromUtf8("lblCancelInst"));
  status2->setFont(font);

  verticalLayout_5->addWidget(status2);


  verticalLayout_6->addLayout(verticalLayout_5);

  horizontalLayout_3 = new QHBoxLayout();
  horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
  //createButton = new QPushButton(centralWidget);
  createButton->setObjectName(QString::fromUtf8("createButton"));
  QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy4.setHorizontalStretch(0);
  sizePolicy4.setVerticalStretch(0);
  sizePolicy4.setHeightForWidth(createButton->sizePolicy().hasHeightForWidth());
  createButton->setSizePolicy(sizePolicy4);

  horizontalLayout_3->addWidget(createButton);

  //editButton = new QPushButton(centralWidget);
  editButton->setObjectName(QString::fromUtf8("btnEditRoute"));
  sizePolicy4.setHeightForWidth(editButton->sizePolicy().hasHeightForWidth());
  editButton->setSizePolicy(sizePolicy4);

  horizontalLayout_3->addWidget(editButton);

  //deleteButton = new QPushButton(centralWidget);
  deleteButton->setObjectName(QString::fromUtf8("btnEditRoute"));

  horizontalLayout_3->addWidget(deleteButton);

  //updateButton = new QPushButton(centralWidget);
  updateButton->setObjectName(QString::fromUtf8("btnUpdateRoute"));

  horizontalLayout_3->addWidget(updateButton);

  //cancelButton = new QPushButton(centralWidget);
  cancelButton->setObjectName(QString::fromUtf8("btnCancelRoute"));

  horizontalLayout_3->addWidget(cancelButton);

  //exportButton = new QPushButton(centralWidget);
  exportButton->setObjectName(QString::fromUtf8("btnEditRoute"));

  horizontalLayout_3->addWidget(exportButton);


  verticalLayout_6->addLayout(horizontalLayout_3);

  addFrame->setCentralWidget(centralWidget);
//    QMenuBar* menubar = new QMenuBar(addFrame);
//    menubar->setObjectName(QString::fromUtf8("menubar"));
//    menubar->setGeometry(QRect(0, 0, 461, 21));
//    addFrame->setMenuBar(menubar);
  addFrame->addHelpMenu("WindowMenu", true);
  QStatusBar* statusbar = new QStatusBar(addFrame);
  statusbar->setObjectName(QString::fromUtf8("statusbar"));
  addFrame->setStatusBar(statusbar);

  addFrame->addWindowListener(addFrameWindowListener = new AddFrameWindowListener2(this));

  retranslateUi(addFrame);

////    windowMenu = new QMenu(tr("Window"));
//    menubar->addMenu(windowMenu);
//    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(on_windowMenu_aboutToShow()));
//    PanelMenu::instance()->addEditorPanel((Editor*)this);

  _routeTurnoutModel = new RouteTurnoutModel(this);
  routeTurnoutTable->setModel(_routeTurnoutModel);
  QStringList turnoutStates;
  turnoutStates <<SET_TO_CLOSED<<SET_TO_THROWN<<SET_TO_TOGGLE;
  routeTurnoutTable->setItemDelegateForColumn(RouteTurnoutModel::STATE_COLUMN,new ComboBoxDelegate(turnoutStates));
//    QComboBox* stateTCombo = new QComboBox();
//    stateTCombo->addItem(SET_TO_CLOSED);
//    stateTCombo->addItem(SET_TO_THROWN);
//    stateTCombo->addItem(SET_TO_TOGGLE);
  sensor1->setFirstItemBlank(true);
  sensor2->setFirstItemBlank(true);
  sensor3->setFirstItemBlank(true);
  sensor1->setSelectedBean(NULL);
  sensor2->setSelectedBean(NULL);
  sensor3->setSelectedBean(NULL);

  _routeSensorModel = new RouteSensorModel(this);
  routeSensorTable->setModel(_routeSensorModel);
  QStringList sensorStates = QStringList()<<SET_TO_INACTIVE<<SET_TO_ACTIVE<<SET_TO_TOGGLE;
  routeSensorTable->setItemDelegateForColumn(RouteSensorModel::STATE_COLUMN, new ComboBoxDelegate(sensorStates));
  connect(_autoSystemName, SIGNAL(toggled(bool)), this, SLOT(autoSystemName()));
  if(pref->getSimplePreferenceState(systemNameAuto))
    _autoSystemName->setChecked(true);

  connect(allButton, SIGNAL(toggled(bool)), this, SLOT(on_allButton_toggled(bool)));
  connect(includedButton, SIGNAL(toggled(bool)), this, SLOT(on_includedButton_toggled()));
  connect(setSound, SIGNAL(clicked()), this, SLOT(setSoundPressed()));
  connect(createButton, SIGNAL(clicked()), this, SLOT(createPressed()));
  connect(editButton, SIGNAL(clicked()), this, SLOT(editPressed()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
  connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(updatePressed()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));
  // pack and release space
  //addFrame->pack();
  addFrame->adjustSize();
  p2xsSpace->setVisible(false);
  p2xtSpace->setVisible(false);

 }

 // display the window
 addFrame->setVisible(true);
 autoSystemName();
#endif
}
AddFrameWindowListener2::AddFrameWindowListener2(RouteTableAction *self)
{
 this->self = self;
}
void AddFrameWindowListener2::windowClosing(QCloseEvent */*e*/)
{
 // remind to save, if Route was created or edited
 if (self->routeDirty)
 {
  ((UserPreferencesManager*)      InstanceManager::getDefault("UserPreferencesManager"))->
        showInfoMessage("Reminder","Remember to save your Route information.",self->getClassName(), "remindSaveRoute");
    self->routeDirty = false;
 }
 // hide addFrame
 self->addFrame->setVisible(false);
 // if in Edit, cancel edit mode
 if (self->editMode)
 {
  self->cancelEdit();
 }
 //self->_routeSensorModel->dispose();
 //self->_routeTurnoutModel->dispose();
}

// addPressed
void RouteTableAction::retranslateUi(JmriJFrame */*addFrame*/)
{
 //addFrame->setText(tr("MainWindow"));
 label->setText(tr( "Route System Name:"));
 _autoSystemName->setText(tr( "Automatically generate System Name"));
 label_2->setText(tr( "Route User Name:"));
 label_3->setText(tr( "Show"));
 allButton->setText(tr( "All"));
 allButton->setChecked(true);
 includedButton->setText(tr( "Included"));
 label_4->setText(tr( "Turnouts and Sensors"));
 label_9->setText(QString());
 label_5->setText(tr( "Please select"));
 label_6->setText(tr( "Turnouts to"));
 label_7->setText(tr( "be included "));
 label_8->setText(tr( "In this route"));
 label_10->setText(QString());
 label_11->setText(tr( "Please select"));
 label_12->setText(tr( "Sensors to"));
 label_13->setText(tr( "be included "));
 label_14->setText(tr( "In this route"));
 label_15->setText(tr( "Play sound file :"));
 setSound->setText(tr( "Set"));
 label_16->setText(tr( "Run script:"));
 setScript->setText(tr( "Set"));
 sensorThatActivates->setText(tr( "Enter Sensor that Activates when Route Turnouts are correctly aligned (optional)."));
 sensorsThatTrigger->setText(tr( "Enter Sensors that trigger this Route (optional)"));
 label_19->setText(tr( "Sensors:"));
 label_20->setText(tr( "Enter a Turnout that triggers this Route (optional)."));
 label_21->setText(tr( "Turnout:"));
 label_22->setText(tr( "Condition:"));
 label_23->setText(tr( "Enter additional delay between Turnout Commands(optional), added delay:"));
 label_17->setText(tr("Enter a Turnout that controls the lock for this Route (optional)."));
 label_18->setText(tr("Turnout:"));
 label_24->setText(tr("Condition:"));
 createButton->setText(tr("Add Route"));
 editButton->setText(tr("Edit Route"));

 _systemName->setToolTip(tr("Enter system name for new Route, e.((DefaultRoute*)g)-> R12."));
 _userName->setToolTip(tr("Enter user name for new Route, e.((DefaultRoute*)g)-> Clear Mainline."));
 turnoutsAlignedSensor->setToolTip("Enter a Sensor system name or nothing");
 QString sensorHint = tr("Enter a Sensor system name or nothing");
 sensor1->setToolTip(sensorHint);
 sensor2->setToolTip(sensorHint);
 sensor3->setToolTip(sensorHint);

 cTurnout->setToolTip(tr("Enter a Turnout system name (real or phantom)"));
 cTurnoutStateBox->setToolTip(tr("Setting control Turnout to selected state will trigger Route"));
 timeDelay->setToolTip(tr("Enter time to add to the default of 250 milliseconds between turnout commands"));
 cLockTurnout->setToolTip(tr("Enter a Turnout system name (real or phantom)"));
 cLockTurnoutStateBox->setToolTip(tr("Setting control Turnout to selected state will lock Route"));
 createButton->setToolTip(tr("Add a new Route using data entered above"));
 editButton->setToolTip(tr("Set up to edit Route in System Name"));
 deleteButton->setToolTip(tr("Delete the Route in System Name"));
 updateButton->setToolTip(tr("Change this Route and leave Edit mode"));
 cancelButton->setToolTip(tr("Leave Edit mode without changing the Route"));
 exportButton->setToolTip(tr("Export Route to Logix Conditionals for further enhancement"));
}

void RouteTableAction::autoSystemName() // SLOT[]
{
 if (_autoSystemName->isChecked())
 {
  createButton->setEnabled(true);
  _systemName->setEnabled(false);
  nameLabel->setEnabled(false);
 }
 else
 {
  if (_systemName->text().length() > 0)
   createButton->setEnabled(true);
  else
   createButton->setEnabled(false);
  _systemName->setEnabled(true);
  nameLabel->setEnabled(true);
 }
 pref->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
}
void RouteTableAction::on_allButton_toggled(bool bState)
{
 // Setup for display of all Turnouts, if needed

 if (!showAll)
 {
  showAll = true;
//  _routeTurnoutModel.fireTableDataChanged();
//  _routeSensorModel.fireTableDataChanged();
 }
 showAll = bState;
 _routeTurnoutModel->reset();
 _routeSensorModel->reset();
}
/**
 * Initialize list of included turnout positions
 */
void RouteTableAction::initializeIncludedList() {
    _includedTurnoutList = new QList <RouteTurnout*> ();
    for (int i=0; i<_turnoutList->size(); i++) {
        if (_turnoutList->at(i)->isIncluded()) {
            _includedTurnoutList->append(_turnoutList->at(i));
        }
    }
    _includedSensorList = new QList <RouteSensor*> ();
    for (int i=0; i<_sensorList->size(); i++) {
        if (_sensorList->at(i)->isIncluded()) {
            _includedSensorList->append(_sensorList->at(i));
        }
    }
}

/**
 * Responds to the Add button
 */
void RouteTableAction::createPressed(/*ActionEvent e*/) {
    
    if (!_autoSystemName->isChecked()) {
        if (!checkNewNamesOK()) {
            return;
        }
    }
    updatePressed(true);
    status2->setText(editInst);
    ((UserPreferencesManager*)pref)->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
    // activate the route
}

bool RouteTableAction::checkNewNamesOK()
{
    // Get system name and user name
    QString sName = _systemName->text();
    QString uName = _userName->text();
    if (sName.length()==0) {
        status1->setText("Please enter a system name and user name.");
        return false;
    }
    Route* g = NULL;
    // check if a Route with the same user name exists
    if (uName!=("")) {
        g = (Route*)((DefaultRouteManager*)InstanceManager::routeManagerInstance())->getByUserName(uName);
        if (g!=NULL) {
            // Route with this user name already exists
            status1->setText("Error - Route with this user name already exists.");
            return false;
        }
        else {
            return true;
        }
    }
    // check if a Route with this system name already exists
    g = (Route*)((DefaultRouteManager*)InstanceManager::routeManagerInstance())->getBySystemName(sName);
    if (g!=NULL) {
        // Route already exists
        status1->setText("Error - Route with this system name already exists.");
        return false;
    }
    return true;
}

//@SuppressWarnings("NULL")
Route* RouteTableAction::checkNamesOK()
{
    // Get system name and user name
    QString sName = _systemName->text();
    QString uName = _userName->text();
    Route* g;
    if (_autoSystemName->isChecked() && !editMode){
        g = (Route*)((DefaultRouteManager*)InstanceManager::routeManagerInstance())->newRoute(uName);
    } else {
        if (sName.length()==0) {
            status1->setText("Please enter a system name and user name.");
            return NULL;
        }
        g = (Route*)((DefaultRouteManager*)InstanceManager::routeManagerInstance())->provideRoute(sName, uName);
    }
    if (g==NULL) {
        // should never get here
        log->error("Unknown failure to create Route with System Name: "+sName);
    }
    ((DefaultRoute*)g)->deActivateRoute();
    return g;
}

/**
 * Sets the Turnout information for adding or editting
 */
int RouteTableAction::setTurnoutInformation(Route* g)
{
 for (int i=0; i<_includedTurnoutList->size(); i++)
 {
  RouteTurnout* t = _includedTurnoutList->at(i);
  ((DefaultRoute*)g)->addOutputTurnout(t->getSysName(), t->getState());
 }
 return _includedTurnoutList->size();
}

/**
 * Sets the Sensor information for adding or editting
 */
int RouteTableAction::setSensorInformation(Route* g)
{
    for (int i=0; i<_includedSensorList->size(); i++)
    {
        RouteSensor* s = _includedSensorList->at(i);
        ((DefaultRoute*)g)->addOutputSensor(s->getDisplayName(), s->getState());
    }
    return _includedSensorList->size();
}

/**
 * Sets the Sensor, Turnout, and delay control information for adding or editting if any
 */
void RouteTableAction::setControlInformation(Route* g) {
    // Get sensor control information if any
    if(sensor1->getSelectedBean()!=NULL){
        if ( (!((DefaultRoute*)g)->addSensorToRoute(sensor1->getSelectedDisplayName(), sensorModeFromBox(sensor1mode))) ) {
            log->error("Unexpected failure to add Sensor '"+sensor1->getSelectedDisplayName()+
                                        "' to Route '"+((DefaultRoute*)g)->getSystemName()+"'.");
        }
    }

    if(sensor2->getSelectedBean()!=NULL){
        if ((!((DefaultRoute*)g)->addSensorToRoute(sensor2->getSelectedDisplayName(), sensorModeFromBox(sensor2mode))) ) {
            log->error("Unexpected failure to add Sensor '"+sensor2->getSelectedDisplayName()+
                                        "' to Route '"+((DefaultRoute*)g)->getSystemName()+"'.");
        }
    }

    if(sensor3->getSelectedBean()!=NULL){
        if ((!((DefaultRoute*)g)->addSensorToRoute(sensor3->getSelectedDisplayName(), sensorModeFromBox(sensor3mode))) ) {
            log->error("Unexpected failure to add Sensor '"+sensor3->getSelectedDisplayName()+
                                        "' to Route '"+((DefaultRoute*)g)->getSystemName()+"'.");
        }
    }
    
    //turnouts aligned sensor
    if(turnoutsAlignedSensor->getSelectedBean()!=NULL){
        ((DefaultRoute*)g)->setTurnoutsAlignedSensor(turnoutsAlignedSensor->getSelectedDisplayName());
    }
    
    // Set turnout information if there is any
    
    if (cTurnout->getSelectedBean()!=NULL) {
        ((DefaultRoute*)g)->setControlTurnout(cTurnout->getSelectedDisplayName());
        // set up control turnout state
        ((DefaultRoute*)g)->setControlTurnoutState(turnoutModeFromBox(cTurnoutStateBox));
    } else {
        // No control Turnout was entered
        ((DefaultRoute*)g)->setControlTurnout("");
    }
    // set delay information
    int addDelay = 0;
    try 
    {
        timeDelay->text().toInt();
    }
    catch (NumberFormatException e)
    {
        addDelay = 0;
        timeDelay->setText("0");
    }
    if (addDelay<0) 
    {
        // added delay must be a positive integer
        addDelay = 0;
        timeDelay->setText("0");
    }
    ((DefaultRoute*)g)->setRouteCommandDelay(addDelay);
    
    // Set lock turnout information if there is any
    if (cLockTurnout->getSelectedBean()!=NULL) {
        ((DefaultRoute*)g)->setLockControlTurnout(cLockTurnout->getSelectedDisplayName());
        // set up control turnout state
        ((DefaultRoute*)g)->setLockControlTurnoutState(turnoutModeFromBox(cLockTurnoutStateBox));
    } else {
        // No control Turnout was entered
        ((DefaultRoute*)g)->setLockControlTurnout("");
    }
}

/**
 * Set the sound file
 */
void RouteTableAction::setSoundPressed() // [slot]
{
#if 0
    if (soundChooser == NULL) {
        soundChooser = new JFileChooser(FileUtil.getUserFilesPath());
        soundChooser.setFileFilter(new jmri.util.NoArchiveFileFilter());
    }
    soundChooser.rescanCurrentDirectory();
    int retVal = soundChooser.showOpenDialog(NULL);
    // handle selection or cancel
    if (retVal == JFileChooser.APPROVE_OPTION) {
        try {
            soundFile->setText(soundChooser.getSelectedFile().getCanonicalPath());
        } catch (java.io.IOException e) {
            log->error("exception setting sound file: "+e);
        }
    }
}

JFileChooser scriptChooser = NULL;

/**
 * Set the script file
 */
void setScriptPressed() {
    if (scriptChooser == NULL) {
        scriptChooser = jmri.jmrit.XmlFile.userFileChooser("Python script files", "py");
    }
    scriptChooser.rescanCurrentDirectory();
    int retVal = scriptChooser.showOpenDialog(NULL);
    // handle selection or cancel
    if (retVal == JFileChooser.APPROVE_OPTION) {
        try {
            scriptFile->setText(scriptChooser.getSelectedFile().getCanonicalPath());
        } catch (java.io.IOException e) {
            log->error("exception setting script file: "+e);
        }
    }
#endif
}
/**
 * Responds to the Edit button
 */
void RouteTableAction::editPressed(/*ActionEvent e*/) // SLOT[]
{
    // identify the Route with this name if it already exists
    QString sName = _systemName->text();
    Route* g = (Route*)((DefaultRouteManager*)InstanceManager::routeManagerInstance())->getBySystemName(sName);
    if (g==NULL) {
        sName = _userName->text();
        g = (Route*)((DefaultRouteManager*)InstanceManager::routeManagerInstance())->getByUserName(sName);
        if(g==NULL){
        // Route does not exist, so cannot be edited
            status1->setText("Route with the entered System or User Name was not found.");
            return;
        }
    }
    // Route was found, make its system name not changeable
    curRoute = g;
    _autoSystemName->setVisible(false);
    fixedSystemName->setText(sName);
    fixedSystemName->setVisible(true);
    _systemName->setVisible(false);
    nameLabel->setEnabled(true);
    _autoSystemName->setVisible(false);
    // deactivate this Route
    ((DefaultRoute*)curRoute)->deActivateRoute();
    // get information for this route
    _userName->setText(((DefaultRoute*)g)->getUserName());
    // set up Turnout list for this route
    int setRow = 0;
    for (int i=_turnoutList->size()-1; i>=0; i--) {
        RouteTurnout* turnout = _turnoutList->at(i);
        QString tSysName = turnout->getSysName();
        if (((DefaultRoute*)g)->isOutputTurnoutIncluded(tSysName) ) {
            turnout->setIncluded(true);
            turnout->setState(((DefaultRoute*)g)->getOutputTurnoutSetState(tSysName));
            setRow = i;
        } else {
            turnout->setIncluded(false);
            turnout->setState(Turnout::CLOSED);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
//    _routeTurnoutScrollPane->getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
//    _routeTurnoutModel.fireTableDataChanged();
    // set up Sensor list for this route
    for (int i=_sensorList->size()-1; i>=0; i--) {
        RouteSensor* sensor = _sensorList->at(i);
        QString tSysName = sensor->getSysName();
        if (((DefaultRoute*)g)->isOutputSensorIncluded(tSysName) ) {
            sensor->setIncluded(true);
            sensor->setState(((DefaultRoute*)g)->getOutputSensorSetState(tSysName));
            setRow = i;
        } else {
            sensor->setIncluded(false);
            sensor->setState(Sensor::INACTIVE);
        }
    }
    setRow -= 1;
    if (setRow < 0) {
        setRow = 0;
    }
    //_routeSensorScrollPane.getVerticalScrollBar().setValue(setRow*ROW_HEIGHT);
    //_routeSensorModel.fireTableDataChanged();
    // get sound, script names
    scriptFile->setText(((DefaultRoute*)g)->getOutputScriptName());
    soundFile->setText(((DefaultRoute*)g)->getOutputSoundName());
    
    // get turnout aligned sensor
    turnoutsAlignedSensor->setSelectedBean(((DefaultRoute*)g)->getTurnoutsAlgdSensor());

    // set up Sensors if there are any
    QVector<Sensor*> temNames =  QVector<Sensor*>(Route::MAX_CONTROL_SENSORS);
    QVector<int> temModes = QVector<int>(Route::MAX_CONTROL_SENSORS);
    for (int k = 0; k<Route::MAX_CONTROL_SENSORS; k++) {
        temNames.replace(k, ((DefaultRoute*)g)->getRouteSensor(k));
        temModes.replace(k, ((DefaultRoute*)g)->getRouteSensorMode(k));
    }
    sensor1->setSelectedBean(temNames.at(0));
    setSensorModeBox(temModes.at(0), sensor1mode);

    sensor2->setSelectedBean(temNames.at(1));
    setSensorModeBox(temModes.at(1), sensor2mode);

    sensor3->setSelectedBean(temNames.at(2));
    setSensorModeBox(temModes.at(2), sensor3mode);

    // set up control Turnout if there is one
    cTurnout->setSelectedBean(((DefaultRoute*)g)->getCtlTurnout());
    
    setTurnoutModeBox(((DefaultRoute*)g)->getControlTurnoutState(), cTurnoutStateBox);
    
    // set up lock control Turnout if there is one
    cLockTurnout->setSelectedBean(((DefaultRoute*)g)->getLockCtlTurnout());
    
    setTurnoutModeBox(((DefaultRoute*)g)->getLockControlTurnoutState(), cLockTurnoutStateBox);
    
    // set up additional delay
    timeDelay->setText(QString::number(((DefaultRoute*)g)->getRouteCommandDelay()));
    // begin with showing all Turnouts   
    // set up buttons and notes
    status1->setText(updateInst);
    status2->setText(cancelInst);
    status2->setVisible(true);
    deleteButton->setVisible(true);
    cancelButton->setVisible(true);
    updateButton->setVisible(true);
    exportButton->setVisible(true);
    editButton->setVisible(false);
    createButton->setVisible(false);
    fixedSystemName->setVisible(true);
    _systemName->setVisible(false);
    editMode = true;

}   // editPressed

/**
 * Responds to the Delete button
 */
void RouteTableAction::deletePressed(/*ActionEvent e*/) // [slot]
{
    // route is already deactivated, just delete it
    ((DefaultRouteManager*)InstanceManager::routeManagerInstance())->deleteRoute(curRoute);

    curRoute = NULL;
    finishUpdate();
}

/**
 * Responds to the Update button - update to Route Table
 */
void RouteTableAction::updatePressed(/*ActionEvent* e,*/ bool newRoute ) // [slot]
{
    // Check if the User Name has been changed
    QString uName = _userName->text();
    //String sName = _systemName->text();
    Route* g = checkNamesOK();
    if (g == NULL) {
        return;
    }
    // user name is unique, change it
    ((DefaultRoute*)g)->setUserName(uName);
    // clear the current output information for this Route
    ((DefaultRoute*)g)->clearOutputTurnouts();
    ((DefaultRoute*)g)->clearOutputSensors();
    // clear the current Sensor information for this Route
    ((DefaultRoute*)g)->clearRouteSensors();
    // add those indicated in the window
    initializeIncludedList();
    setTurnoutInformation(g);
    setSensorInformation(g);
    // set the current values of the filenames
    ((DefaultRoute*)g)->setOutputScriptName(scriptFile->text());
    ((DefaultRoute*)g)->setOutputSoundName(soundFile->text());
    // add control Sensors and a control Turnout if entered in the window
    setControlInformation(g);        
    curRoute = g;
    finishUpdate();
    status1->setText((newRoute ? tr("New Route created: "):tr("Route updated: "))
                    +uName+", "+ QString::number(_includedTurnoutList->size())
                    +" Turnouts, "+QString::number(_includedSensorList->size())+" Sensors");
}

void RouteTableAction::finishUpdate()
{
 // move to show all turnouts if not there
 cancelIncludedOnly();
 // Provide feedback to user
 // switch GUI back to selection mode
 status2->setText(editInst);
 status2->setVisible(true);
 deleteButton->setVisible(false);
 cancelButton->setVisible(false);
 updateButton->setVisible(false);
 exportButton->setVisible(false);
 editButton->setVisible(true);
 createButton->setVisible(true);
 fixedSystemName->setVisible(false);
 _autoSystemName->setVisible(true);
 autoSystemName();
 clearPage();
 _systemName->setVisible(true);
 // reactivate the Route
 routeDirty = true;
 // get out of edit mode
 editMode = false;
 if (curRoute != NULL) {
     ((DefaultRoute*)curRoute)->activateRoute();
 }
}

void RouteTableAction::clearPage()
{
 _systemName->setVisible(true);
 _systemName->setText("");
 _userName->setText("");
 sensor1->setSelectedBean(NULL);
 sensor2->setSelectedBean(NULL);
 sensor3->setSelectedBean(NULL);
 cTurnout->setSelectedBean(NULL);
 cLockTurnout->setSelectedBean(NULL);
 turnoutsAlignedSensor->setSelectedBean(NULL);
 soundFile->setText("");
 scriptFile->setText("");
 for (int i=_turnoutList->size()-1; i>=0; i--) {
     _turnoutList->at(i)->setIncluded(false);
 }
 for (int i=_sensorList->size()-1; i>=0; i--) {
     _sensorList->at(i)->setIncluded(false);
 }
}


/////////////////////// Export to Logix ////////////////////////////
/**
 * Responds to the Update button - update to Logix
 */
void RouteTableAction::exportPressed(/*ActionEvent* e*/)  // SLOT[]
{
#if 1 // TODO: if required.
    curRoute = checkNamesOK();
    QString sName = _systemName->text();
    if (sName.length()==0) {
        sName = fixedSystemName->text();
    }
    QString uName = _userName->text();
    QString logixSystemName = LOGIX_SYS_NAME+sName;
    Logix* logix = InstanceManager::logixManagerInstance()->getBySystemName(logixSystemName);
    if (logix == NULL) {
        logix = InstanceManager::logixManagerInstance()->createNewLogix(logixSystemName, uName);
        if (logix == NULL) {
            log->error("Failed to create Logix "+logixSystemName+", "+uName);
            return;
        }
    }
    logix->deActivateLogix();
    initializeIncludedList();
    
    /////////////////// Construct output actions for change to true //////////////////////
    QList <ConditionalAction*>* actionList = new QList<ConditionalAction*>();

    for (int i=0; i<_includedSensorList->size(); i++) {
        RouteSensor* rSensor = _includedSensorList->at(i);
        QString name = rSensor->getUserName();
        if (name == NULL || name.length() == 0) {
             name = rSensor->getSysName();
        }
        actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                              Conditional::ACTION_SET_SENSOR, name, rSensor->getState(), ""));
    }
    for (int i=0; i<_includedTurnoutList->size(); i++) {
        RouteTurnout* rTurnout = _includedTurnoutList->at(i);
        QString name = rTurnout->getUserName();
        if (name == NULL || name.length() == 0) {
             name = rTurnout->getSysName();
        }
        actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                              Conditional::ACTION_SET_TURNOUT, name, rTurnout->getState(), ""));
    }
    QString file = soundFile->text();
    if (file.length() > 0) {
        actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                              Conditional::ACTION_RUN_SCRIPT, "", -1, file));
    }
    file = scriptFile->text();
    if (file.length() > 0) {
        actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                              Conditional::ACTION_PLAY_SOUND, "", -1, file));
    }

    ///// Construct 'AND' clause from 'VETO' controls ////////
    QList <ConditionalVariable*>* vetoList = new QList<ConditionalVariable*>();

    // String andClause = NULL;
    ConditionalVariable* cVar = makeCtrlSensorVar(sensor1, sensor1mode, true, false);
    if (cVar != NULL) {
        vetoList->append(cVar);
    }
    cVar = makeCtrlSensorVar(sensor2, sensor2mode, true, false);
    if (cVar != NULL) {
        vetoList->append(cVar);
    }
    cVar = makeCtrlSensorVar(sensor3, sensor3mode, true, false);
    if (cVar != NULL) {
        vetoList->append(cVar);
    }
    cVar = makeCtrlTurnoutVar(cTurnout, cTurnoutStateBox, true, false);
    if (cVar != NULL) {
        vetoList->append(cVar);
    }

    // remove old Conditionals for actions (ver 2.5.2 only -remove a bad idea)
    QByteArray ch = sName.toLatin1();
    int hash= 0;
    for (int i=0; i<ch.length(); i++) {
        hash += ch.at(i);
    }
    QString cSystemName = CONDITIONAL_SYS_PREFIX+"T"+hash;
    removeConditionals(cSystemName, logix);
    cSystemName = CONDITIONAL_SYS_PREFIX+"F"+hash;
    removeConditionals(cSystemName, logix);
    cSystemName = CONDITIONAL_SYS_PREFIX+"A"+hash;
    removeConditionals(cSystemName, logix);
    cSystemName = CONDITIONAL_SYS_PREFIX+"L"+hash;
    removeConditionals(cSystemName, logix);

    int n=0;
    do {
        n++;
        cSystemName = logixSystemName+n+"A";
    } while (removeConditionals(cSystemName, logix));
    n = 0;
    do {
        n++;
        cSystemName = logixSystemName+n+"T";
    } while (removeConditionals(cSystemName, logix));
    cSystemName = logixSystemName+"L";
    removeConditionals(cSystemName, logix);

    QString cUserName = "";

    ///////////////// Make Trigger Conditionals //////////////////////
    //QList <ConditionalVariable> onChangeList = new QList<ConditionalVariable>();

    int numConds = 1;
    numConds = makeSensorConditional(sensor1, sensor1mode, numConds, false, 
                                     actionList, vetoList, logix, logixSystemName, uName); 
    numConds = makeSensorConditional(sensor2, sensor2mode, numConds, false, 
                                     actionList, vetoList, logix, logixSystemName, uName); 
    numConds = makeSensorConditional(sensor3, sensor3mode, numConds, false, 
                                     actionList, vetoList, logix, logixSystemName, uName); 
    numConds = makeTurnoutConditional(cTurnout, cTurnoutStateBox, numConds, false, 
                                      actionList, vetoList, logix, logixSystemName, uName); 

    ////// Construct actions for false from the 'any change' controls ////////////
    numConds = makeSensorConditional(sensor1, sensor1mode, numConds, true, actionList, vetoList, 
                                     logix, logixSystemName, uName); 
    numConds = makeSensorConditional(sensor2, sensor2mode, numConds, true, actionList, vetoList, 
                                     logix, logixSystemName, uName); 
    numConds = makeSensorConditional(sensor3, sensor3mode, numConds, true, actionList, vetoList, 
                                     logix, logixSystemName, uName); 
    numConds = makeTurnoutConditional(cTurnout, cTurnoutStateBox, numConds, true, actionList, 
                                      vetoList, logix, logixSystemName, uName); 

    ///////////////// Set up Alignment Sensor, if there is one //////////////////////////
    //String sensorSystemName = turnoutsAlignedSensor->text();
    if (turnoutsAlignedSensor->getSelectedBean()!=NULL) {
        // verify name (logix doesn't use "provideXXX") 
        //Sensor s = turnoutsAlignedSensor->getSelectedBean();
        /*if (s == NULL) {
            s = InstanceManager.sensorManagerInstance().getBySystemName(sensorSystemName);
        }*/
        //if (s != NULL) {
            QString sensorSystemName = turnoutsAlignedSensor->getSelectedDisplayName();
            cSystemName = logixSystemName+"1A";
            cUserName = turnoutsAlignedSensor->getSelectedDisplayName()+"A "+uName;
            
            QList <ConditionalVariable*>* variableList = new QList<ConditionalVariable*>();
            for (int i=0; i<_includedTurnoutList->size(); i++) {
                RouteTurnout* rTurnout = _includedTurnoutList->at(i);
                QString name = rTurnout->getUserName();
                if (name == NULL || name.length() == 0) {
                     name = rTurnout->getSysName();
                }
                // exclude toggled outputs
                switch (rTurnout->getState()) {
                    case Turnout::CLOSED:
                        variableList->append(new ConditionalVariable(false, Conditional::OPERATOR_AND,
                                                   Conditional::TYPE_TURNOUT_CLOSED, name, true));
                        break;
                    case Turnout::THROWN:
                        variableList->append(new ConditionalVariable(false, Conditional::OPERATOR_AND,
                                                   Conditional::TYPE_TURNOUT_THROWN, name, true));
                        break;
                }
            }
            actionList = new QList<ConditionalAction*>();
            actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                                  Conditional::ACTION_SET_SENSOR, sensorSystemName, Sensor::ACTIVE, ""));
            actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE,
                                  Conditional::ACTION_SET_SENSOR, sensorSystemName, Sensor::INACTIVE, ""));

            Conditional* c = ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->createNewConditional(cSystemName, cUserName);
            c->setStateVariables(variableList);
            c->setLogicType(Conditional::ALL_AND, "");
            c->setAction(actionList);
            logix->addConditional(cSystemName, 0);
            c->calculate(true, NULL);
        //}
    }

    ///////////////// Set lock turnout information if there is any //////////////////////////
    if (cLockTurnout->getSelectedBean()!=NULL) {
        QString turnoutLockSystemName = cLockTurnout->getSelectedDisplayName();
        // verify name (logix doesn't use "provideXXX") 
        cSystemName = logixSystemName+"1L";
        cUserName = turnoutLockSystemName+"L "+uName;
        QList <ConditionalVariable*>* variableList = new QList<ConditionalVariable*>();
        //String devName = cTurnout->getText();
        int mode = turnoutModeFromBox(cTurnoutStateBox);
        int type = Conditional::TYPE_TURNOUT_CLOSED;
        if (mode == Route::ONTHROWN) {
            type = Conditional::TYPE_TURNOUT_THROWN;
        }
        variableList->append(new ConditionalVariable(false, Conditional::OPERATOR_NONE,
                                                 type, turnoutLockSystemName, true));

        actionList = new QList<ConditionalAction*>();
        int option = Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE;
        type = Turnout::LOCKED;
        if (mode == Route::ONCHANGE) {
            option = Conditional::ACTION_OPTION_ON_CHANGE;
            type = Route::TOGGLE;
        }
        for (int i=0; i<_includedTurnoutList->size(); i++) {
            RouteTurnout* rTurnout = _includedTurnoutList->at(i);
            QString name = rTurnout->getUserName();
            if (name == NULL || name.length() == 0) {
                 name = rTurnout->getSysName();
            }
            actionList->append(new DefaultConditionalAction(option, Conditional::ACTION_LOCK_TURNOUT,
                                                 name, type, ""));
        }
        if (mode != Route::ONCHANGE) {
            // add non-toggle actions on
            option = Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE;
            type = Turnout::UNLOCKED;
            for (int i=0; i<_includedTurnoutList->size(); i++) {
                RouteTurnout* rTurnout = _includedTurnoutList->at(i);
                QString name = rTurnout->getUserName();
                if (name == NULL || name.length() == 0) {
                     name = rTurnout->getSysName();
                }
                actionList->append(new DefaultConditionalAction(option, Conditional::ACTION_LOCK_TURNOUT,
                                                     name, type, ""));
            }
        }

       // add new Conditionals for action on 'locks'
        Conditional* c = ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->createNewConditional(cSystemName, cUserName);
        c->setStateVariables(variableList);
        c->setLogicType(Conditional::ALL_AND, "");
        c->setAction(actionList);
        logix->addConditional(cSystemName, 0);
        c->calculate(true, NULL);
    }
    logix->activateLogix();
    if (curRoute != NULL) {
        ((DefaultRouteManager*) InstanceManager::routeManagerInstance())->deleteRoute(curRoute);
        curRoute = NULL;
    }
    status1->setText("Route \""+uName+"\" exported to Logix: "+ QString::number(_includedTurnoutList->size())
                    +" Turnouts, "+QString::number(_includedSensorList->size())+" Sensors");
    finishUpdate();
#endif
}

bool RouteTableAction::removeConditionals(QString cSystemName, Logix* logix) {
    Conditional* c = ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->getBySystemName(cSystemName);
    if (c != NULL) {
        logix->deleteConditional(cSystemName);
        ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->deleteConditional(c);
        return true;
    }
    return false;
}

int RouteTableAction::makeSensorConditional(JmriBeanComboBox* jmriBox, QComboBox* sensorbox, int numConds,
                    bool onChange, QList<ConditionalAction*>* actionList,
                    QList<ConditionalVariable*>* vetoList, Logix* logix, QString prefix, QString uName)
{
    ConditionalVariable* cVar = makeCtrlSensorVar(jmriBox, sensorbox, false, onChange);
    if (cVar != NULL) {
        QList <ConditionalVariable*>* varList = new QList<ConditionalVariable*>();
        varList->append(cVar);
        for ( int i=0; i<vetoList->size(); i++) {
            varList->append(cloneVariable(vetoList->at(i)));
        }
        QString cSystemName = prefix+numConds+"T";
        QString cUserName = jmriBox->getSelectedDisplayName()+numConds+"C "+uName;
        Conditional* c = ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->createNewConditional(cSystemName, cUserName);
        c->setStateVariables(varList);
        int option = onChange ? Conditional::ACTION_OPTION_ON_CHANGE : Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE;
        c->setAction(cloneActionList(actionList, option));
        c->setLogicType(Conditional::ALL_AND, "");
        logix->addConditional(cSystemName, 0);
        c->calculate(true, NULL);
        numConds++;
    }
    return numConds;
}

int RouteTableAction::makeTurnoutConditional(JmriBeanComboBox* jmriBox, QComboBox* box, int numConds,
                    bool onChange, QList<ConditionalAction*>* actionList,
                    QList<ConditionalVariable*>* vetoList, Logix* logix, QString prefix, QString uName)
{
    ConditionalVariable* cVar = makeCtrlTurnoutVar(jmriBox, box, false, onChange);
    if (cVar != NULL) {
        QList <ConditionalVariable*>* varList = new QList<ConditionalVariable*>();
        varList->append(cVar);
        for ( int i=0; i<vetoList->size(); i++) {
            varList->append(cloneVariable(vetoList->at(i)));
        }
        QString cSystemName = prefix+numConds+"T";
        QString cUserName = jmriBox->getSelectedDisplayName()+numConds+"C "+uName;
        Conditional* c = ((DefaultConditionalManager*)InstanceManager::conditionalManagerInstance())->createNewConditional(cSystemName, cUserName);
        c->setStateVariables(varList);
        int option = onChange ? Conditional::ACTION_OPTION_ON_CHANGE : Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE;
        c->setAction(cloneActionList(actionList, option));
        c->setLogicType(Conditional::ALL_AND, "");
        logix->addConditional(cSystemName, 0);
        c->calculate(true, NULL);
        numConds++;
    }
    return numConds;
}

ConditionalVariable* RouteTableAction::cloneVariable(ConditionalVariable* v) {
    return new ConditionalVariable(v->isNegated(), v->getOpern(), v->getType(), v->getName(), v->doTriggerActions());
}

QList<ConditionalAction*>* RouteTableAction::cloneActionList(QList<ConditionalAction*>* actionList, int option) {
    QList <ConditionalAction*>* list = new QList <ConditionalAction*> ();
    for (int i = 0; i<actionList->size(); i++) {
        ConditionalAction* action = actionList->at(i);
        ConditionalAction* clone = new DefaultConditionalAction();
        clone->setType(action->getType());
        clone->setOption(option);
        clone->setDeviceName(action->getDeviceName());
        clone->setActionData(action->getActionData());
        clone->setActionString(action->getActionString());
        list->append(clone);
    }
    return list;
}

ConditionalVariable* RouteTableAction::makeCtrlSensorVar(JmriBeanComboBox* jmriBox, QComboBox* sensorbox,
                                       bool makeVeto, bool onChange) {
    QString devName = jmriBox->getSelectedDisplayName();
    if (jmriBox->getSelectedBean() == NULL /*|| devName.length() == 0*/) {
        return NULL;
    }
    int oper = Conditional::OPERATOR_AND;
    int mode = sensorModeFromBox(sensorbox);
    bool trigger = true;
    bool negated = false;
    int type = 0;
    switch (mode) {
        case Route::ONACTIVE:    // route fires if sensor goes active
            if (makeVeto || onChange){
                return NULL;
            }
            type = Conditional::TYPE_SENSOR_ACTIVE;
            break;
        case Route::ONINACTIVE:  // route fires if sensor goes inactive
            if (makeVeto || onChange){
                return NULL;
            }
            type = Conditional::TYPE_SENSOR_INACTIVE;
            break;
        case Route::ONCHANGE:  // route fires if sensor goes active or inactive 
            if (makeVeto || !onChange){
                return NULL;
            }
            type = Conditional::TYPE_SENSOR_ACTIVE;
            break;
        case Route::VETOACTIVE:  // sensor must be active for route to fire
            if (!makeVeto || onChange){
                return NULL;
            }
            type = Conditional::TYPE_SENSOR_ACTIVE;
            negated = true;
            trigger = false;
            break;
        case Route::VETOINACTIVE:
            if (!makeVeto || onChange){
                return NULL;
            }
            type = Conditional::TYPE_SENSOR_INACTIVE;
            negated = true;
            trigger = false;
            break;
        default:
            log->error("Control Sensor "+devName+" has bad mode= "+QString::number(mode));
            return NULL;
    }
    return new ConditionalVariable(negated, oper, type, devName, trigger);
}

ConditionalVariable* RouteTableAction::makeCtrlTurnoutVar(JmriBeanComboBox* jmriBox, QComboBox* box,
                                        bool makeVeto, bool onChange)
{
 if (jmriBox->getSelectedBean() == NULL)
 {
     return NULL;
 }
 QString devName = jmriBox->getSelectedDisplayName();
 int mode = turnoutModeFromBox(box);
 int oper = Conditional::OPERATOR_AND;
 int type = 0;
 bool negated = false;
 bool trigger = true;
 switch (mode)
 {
  case Route::ONCLOSED:    // route fires if turnout goes closed
      if (makeVeto || onChange){
          return NULL;
      }
      type = Conditional::TYPE_TURNOUT_CLOSED;
      break;
  case Route::ONTHROWN:  // route fires if turnout goes thrown
      if (makeVeto || onChange){
          return NULL;
      }
      type = Conditional::TYPE_TURNOUT_THROWN;
      break;
  case Route::ONCHANGE:    // route fires if turnout goes active or inactive
      if (makeVeto || !onChange){
          return NULL;
      }
      type = Conditional::TYPE_TURNOUT_CLOSED;
      break;
  case Route::VETOCLOSED:  // turnout must be closed for route to fire
      if (!makeVeto || onChange){
          return NULL;
      }
      type = Conditional::TYPE_TURNOUT_CLOSED;
      trigger = false;
      negated = true;
      break;
  case Route::VETOTHROWN:  // turnout must be thrown for route to fire
      if (!makeVeto || onChange){
          return NULL;
      }
      type = Conditional::TYPE_TURNOUT_THROWN;
      trigger = false;
      negated = true;
      break;
  default:
      log->error("Control Turnout "+devName+" has bad mode= "+QString::number(mode));
      return NULL;
 }
 return new ConditionalVariable(negated, oper, type, devName, trigger);
}

/**
 * Responds to the Cancel button
 */
void RouteTableAction::cancelPressed(/*ActionEvent e*/) // [slot]
{
    cancelEdit();
}

/** 
 * Cancels edit mode
 */
void RouteTableAction::cancelEdit()
{
 if (editMode)
 {
  status1->setText(createInst);
  status2->setText(editInst);
  finishUpdate();
  // get out of edit mode
  editMode = false;
  curRoute = NULL;
 }
}

/** 
 * Cancels included Turnouts only option
 */
void RouteTableAction::cancelIncludedOnly() {
    if (!showAll) {
        //allButton->doClick();
        on_allButton_toggled(false);
    }
}
void RouteTableAction::on_includedButton_toggled()
{
    // Setup for display of included Turnouts only, if needed
                if (showAll) {
                    showAll = false;
                    initializeIncludedList();
//                    _routeTurnoutModel.fireTableDataChanged();
//                    _routeSensorModel.fireTableDataChanged();
                }
}

/**
 * Base table model for selecting outputs
 */
///*public*/ /*abstract*/ class RouteOutputModel : QAbstractTableModel //implements PropertyChangeListener
//{
//RouteOutputModel::RouteOutputModel(RouteTableAction *self)
//{
// this->self = self;
//}

/////*public*/ QString RouteOutputModel::getColumnClass(int c)
////{QStringList items,
//// if (c == INCLUDE_COLUMN)
//// {
////  return "bool";
//// }
//// else
//// {
////  return "QString";
//// }
////}
//int RouteOutputModel::columnCount(const QModelIndex &/*parent*/) const
//{
// return 4;
//}
//QVariant RouteOutputModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
// if (role != Qt::DisplayRole)
//  return QVariant();
// if (orientation == Qt::Horizontal)
// {
//  return self->COLUMN_NAMES.at(section);
// }QStringList items,
// return QVariant();
//}
//Qt::ItemFlags RouteOutputModel::flags(const QModelIndex &index) const
//{
// if (!index.isValid())
//  return Qt::ItemIsEnabled;
// switch(index.column())
// {
//  case INCLUDE_COLUMN:
// case STATE_COLUMN:
//   return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
// }
// // all other columns non-editable
// return QAbstractTableModel::flags(index);
//}
///*public*/ void RouteOutputModel::propertyChange(PropertyChangeEvent* e)
//{
// if (e->getPropertyName()==("length"))QStringList items,
// {
//            // a new NamedBean is available in the manager
////            fireTableDataChanged();
//        }
//    }
    
// /*public*/ void RouteOutputModel::dispose() {
//        InstanceManager::turnoutManagerInstance().removePropertyChangeListener(this);
//    }

//    /*public*/ QString RouteOutputModel::getColumnName(int c) {return RouteTableAction::COLUMN_NAMES.at(c);}

//    /*public*/ bool RouteOutputModel::isCellEditable(int r,int c) {
//        return ( (c==INCLUDE_COLUMN) || (c==STATE_COLUMN) );
//    }QStringList items,

//};

/**
 * Table model for selecting Turnouts and Turnout State
 */
//class RouteTurnoutModel : public RouteOutputModel
//{
RouteTurnoutModel::RouteTurnoutModel(RouteTableAction* self) : QAbstractTableModel()
{
 this->self = self;

 ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
 Q_UNUSED(mgr);
 //InstanceManager::turnoutManagerInstance().addPropertyChangeListener(this);
 //connect(mgr, SIGNAL())
 log = new Logger("RouteTurnoutModel");
}

/*public*/ int RouteTurnoutModel::rowCount (const QModelIndex &parent) const
{
 if(parent.isValid())
     return 0;
 if (self->showAll)
  return self->_turnoutList->size();
 else
  return self->_includedTurnoutList->size();
}

int RouteTurnoutModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 4;
}

QVariant RouteTurnoutModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
  return QVariant();
 if (orientation == Qt::Horizontal)
 {
  return self->COLUMN_NAMES.at(section);
 }
 return QVariant();
}

Qt::ItemFlags RouteTurnoutModel::flags(const QModelIndex &index) const
{
 if (!index.isValid())
  return Qt::ItemIsEnabled;
 Qt::ItemFlags flags = QAbstractTableModel::flags(index);
 switch(index.column())
 {
  case INCLUDE_COLUMN:
   flags |= Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
   break;
 case STATE_COLUMN:
 case UNAME_COLUMN:
   flags |= Qt::ItemIsEditable;
   break;
 }
 // all other columns non-editable
 return flags;
}
/*public*/ QVariant RouteTurnoutModel::data (const QModelIndex &index, int role) const
{
 if (!index.isValid())
  return QVariant();
 int r = index.row();
 int c = index.column();
 QList <RouteTurnout*>* turnoutList = NULL;
 if (self->showAll)
 {
  turnoutList = self->_turnoutList;
 }
 else
 {
  turnoutList = self->_includedTurnoutList;
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
  {
   return turnoutList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
  }
 }
 if (role == Qt::DisplayRole || role == Qt::EditRole)
 {
  QList <RouteTurnout*>* turnoutList = NULL;
  if (self->showAll)
  {
   turnoutList = self->_turnoutList;
  }
  else
  {
   turnoutList = self->_includedTurnoutList;
  }
  // some error checking
  if (r >= turnoutList->size())
  {
   log->debug("row is greater than turnout list size");
   return QVariant();
  }
  switch (c)
  {
//  case INCLUDE_COLUMN:
//        break;
  case SNAME_COLUMN:  // slot number
        return turnoutList->at(r)->getSysName();
  case UNAME_COLUMN:  //
        return turnoutList->at(r)->getUserName();
  case STATE_COLUMN:  //
  {
   return turnoutList->at(r)->getSetToState();
  }
  default:
   break;
  }
 }
 return QVariant();
}
/*public*/ bool RouteTurnoutModel::setData(const QModelIndex &index, const QVariant &value, int role/*=Qt::EditRole*/)
{
 int c = index.column();
 int r = index.row();
 QList <RouteTurnout*>* turnoutList = NULL;
 if (self->showAll)
  turnoutList = self->_turnoutList;
 else
  turnoutList = self->_includedTurnoutList;
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
  {
   turnoutList->at(r)->setIncluded(value.toBool());
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  switch (c)
  {
//  case INCLUDE_COLUMN:
//   turnoutList->at(r)->setIncluded(value.toBool());
//   break;
  case STATE_COLUMN:
   {
    turnoutList->at(r)->setSetToState(value.toString());
   break;;
   }
  }
  return true;
 }
 return false;
}

void RouteTurnoutModel::reset()
{
 //QAbstractTableModel::reset();
 beginResetModel();
 endResetModel();
}

/**
 * Set up table for selecting Sensors and Sensor State
 */
//class RouteSensorModel : public RouteOutputModel
//{
RouteSensorModel::RouteSensorModel(RouteTableAction* self) : QAbstractTableModel(self)
{
 //InstanceManager.sensorManagerInstance().addPropertyChangeListener(this);
    log = new Logger("RouteSensorModel");
    this->self = self;
}
int RouteSensorModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 4;
}

/*public*/ int RouteSensorModel::rowCount (const QModelIndex &parent) const
{
 if(parent.isValid()) return 0;

 if (self->showAll)
  return self->_sensorList->size();
 else
  return self->_includedSensorList->size();
}

/*public*/ QVariant RouteSensorModel::data (const QModelIndex &index, int role) const
{
 if(!index.isValid()) return QVariant();
 int c = index.column();
 int r = index.row();
 QList <RouteSensor*>* sensorList = NULL;
 if (self->showAll)
 {
  sensorList = self->_sensorList;
 }
 else
 {
  sensorList = self->_includedSensorList;
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
   return sensorList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
 }
 if (role == Qt::DisplayRole || role == Qt::EditRole)
 {
  // some error checking
  if (r >= sensorList->size())
  {
   log->debug("row is greater than turnout list size");
   return QVariant();
  }
  switch (c)
  {
    case INCLUDE_COLUMN:
        break;
    case SNAME_COLUMN:  // slot number
        return sensorList->at(r)->getSysName();
    case UNAME_COLUMN:  //
        return sensorList->at(r)->getUserName();
    case STATE_COLUMN:  //
        return sensorList->at(r)->getSetToState();
    default:
      return QVariant();
  }
 }
 return QVariant();
}

/*public*/ bool RouteSensorModel::setData(const QModelIndex &index, const QVariant &value, int role/*=Qt::EditRole*/)
{
 int c = index.column();
 int r = index.row();
 QList <RouteSensor*>* sensorList = NULL;
 if (self->showAll)
 {
   sensorList = self->_sensorList;
 }
 else
 {
  sensorList = self->_includedSensorList;
 }
 if(role == Qt::CheckStateRole)
 {
  if(c == INCLUDE_COLUMN)
   sensorList->at(r)->setIncluded(value.toBool());
   return true;
 }
 if(role == Qt::EditRole)
 {
  switch (c)
  {
//    case INCLUDE_COLUMN:
//        sensorList->at(r)->setIncluded(value.toBool());
//        break;
    case STATE_COLUMN:
        sensorList->at(r)->setSetToState(value.toString());
        break;
  }
  return true;
 }
 return false;
}

QVariant RouteSensorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
  return QVariant();
 if (orientation == Qt::Horizontal)
 {
  return self->COLUMN_NAMES.at(section);
 }
 return QVariant();
}

Qt::ItemFlags RouteSensorModel::flags(const QModelIndex &index) const
{
 if (!index.isValid())
  return Qt::ItemIsEnabled;
 Qt::ItemFlags flags = QAbstractTableModel::flags(index);
 switch(index.column())
 {
  case INCLUDE_COLUMN:
   flags |= Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
   break;
 case STATE_COLUMN:
 case UNAME_COLUMN:
   flags |= Qt::ItemIsEditable;
   break;
 }
 // all other columns non-editable
 return flags;
}

void RouteSensorModel::reset()
{
 //QAbstractTableModel::reset();
 beginResetModel();
 endResetModel();
}

/*public*/ void RouteTableAction::setMessagePreferencesDetails()
{
#if 1
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->preferenceItemDetails(getClassName(), "remindSaveRoute", tr("Hide Save Message Reminder"));
 AbstractTableAction::setMessagePreferencesDetails();
 QMap< int,QString> options =  QMap< int,QString>();
 options.insert(0x00, tr("Always Ask"));
 options.insert(0x01, tr("Never Delete"));
 options.insert(0x02, tr("Delete Without Prompting"));
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->messageItemDetails(getClassName(), "deleteInUse", tr("When Deleting an item that is in use"), options, 0x00);
#endif
}

/*protected*/ QString RouteTableAction::getClassName() { return "jmri.jmrit.beantable.RouteTableAction";}

/*public*/ QString RouteTableAction::getClassDescription() { return tr("Route Table"); }

//static final or((DefaultRoute*)g)->apache.log4j.Logger log = or((DefaultRoute*)g)->apache.log4j.Logger.getLogger(RouteTableAction.class.getName());
//}
//void RouteTableAction::on_windowMenu_aboutToShow()
//{
// windowMenu->clear();
// PanelMenu::instance()->updatePanelMenu(windowMenu);

//}
ComboBoxDelegate::ComboBoxDelegate(QStringList items, QObject *parent)
:QItemDelegate(parent)
{
Items = items;
}


QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  QComboBox* editor = new QComboBox(parent);
  editor->addItems(Items);
  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  int value = index.model()->data(index, Qt::EditRole).toUInt();
  comboBox->setCurrentIndex(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

//void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//  QStyleOptionViewItemV4 myOption = option;
//  QString text = Items.at(index.row());

//  myOption.text = text;

//  QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
//}
QString RouteTableAction::getName()
{
    return "jmri.jmrit.beantable.RouteTableAction";
}
