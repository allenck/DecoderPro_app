#include "conditionallistedit.h"
#include <QBoxLayout>
#include <defaultlogix.h>
#include "defaultconditionalmanager.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "pushbuttondelegate.h"
#include "lroutetableaction.h"
#include <QGroupBox>
#include "defaultconditional.h"
#include "sensorgroupframe.h"
#include "defaultlogixmanager.h"
#include <QMessageBox>
#include "joptionpane.h"
#include <QButtonGroup>
#include "defaultconditionalaction.h"
#include "conditionalaction.h"
#include "signalheadmanager.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "oblock.h"
#include "system.h"
#include "jfilechooser.h"
#include "fileutil.h"
#include "warrant.h"
#include "flowlayout.h"
#include "box.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "variabletablemodel.h"
#include "light.h"
#include "tabledelegates.h"

/**
 * The traditional list based conditional editor based on the original editor
 * included in LogixTableAction.
 * <p>
 * Conditionals now have two policies to trigger execution of their action
 * lists:<br>
 * 1. the previous policy - Trigger on change of state only <br>
 * 2. the new default - Trigger on any enabled state calculation Jan 15, 2011 -
 * Pete Cressman
 * <p>
 * Two additional action and variable name selection methods have been added: 1)
 * Single Pick List 2) Combo Box Selection The traditional tabbed Pick List with
 * text entry is the default method. The Options menu has been expanded to list
 * the 3 methods. Mar 27, 2017 - Dave Sand
 * <p>
 * Add a Browse Option to the Logix Select Menu This will display a window that
 * creates a formatted list of the contents of the selected Logix with each
 * Conditional, Variable and Action. The code is courtesy of Chuck Catania and
 * is used with his permission. Apr 2, 2017 - Dave Sand
 * <p>
 * @author Dave Duchamp Copyright (C) 2007
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011
 * @author Matthew Harris copyright (c) 2009
 * @author Dave Sand copyright (c) 2017
 */
// /*public*/ class ConditionalListEdit extends ConditionalEditBase {

/**
 * Constructor to create a Conditional List View editor.
 *
 * @param sName name of the Logix being edited
 */
/*public*/ ConditionalListEdit::ConditionalListEdit(QString sName, QObject* parent) : ConditionalEditBase(sName, parent) {
    //super(sName);
 common();
 makeEditLogixWindow();
}

/*public*/ ConditionalListEdit::ConditionalListEdit(QObject* parent) : ConditionalEditBase(parent){
 common();
}

void ConditionalListEdit::common()
{
 // ------------ Logix Variables ------------
 _editLogixFrame = NULL;
 editUserName = new JTextField(20);
 status = new QLabel(" ");

 // ------------ Conditional Variables ------------
 conditionalTableModel = NULL;
 _curConditional = NULL;
 _conditionalRowNumber = 0;
 _inReorderMode = false;
 _inActReorder = false;
 _inVarReorder = false;
 _nextInOrder = 0;

 // ------------ Select Logix/Conditional Variables ------------
 _selectLogixPanel = NULL;
 _selectConditionalPanel = NULL;
 _selectLogixBox = new QComboBox();
 _selectConditionalBox = new QComboBox();
 _selectLogixList =  QList<QString>();
 _selectConditionalList =  QList<QString>();

 // ------------ Edit Conditional Variables ------------
 _inEditConditionalMode = false;
 _editConditionalFrame = NULL;
 _conditionalUserName = new JTextField(22);

 _actionTableModel = NULL;
 _variableTableModel = NULL;

 _logicType = Conditional::ALL_AND;
 _antecedent = "";
 _newItem = false; // marks a new Action or Variable object was added

 // ------------ Components of Edit Variable panes ------------
 _editVariableFrame = NULL;


 // ------------ Components of Edit Action panes ------------
 _editActionFrame = NULL;


 // ------------ Current Variable Information ------------
 _curVariableItem = 0;
 _oldTargetNames = QStringList();

 // ------------ Current Action Information ------------

 _curActionItem = 0;
 _actionTypeListener = new ActionTypeListener(this);
 selectLogixBoxListener = new CLESelectLogixBoxListener(this);
 selectConditionalBoxListener = new CLESelectConditionalBoxListener(this);

}


/*static*/ /*final*/ int ConditionalListEdit::STRUT = 10;

// ------------ Methods for Edit Logix Pane ------------
/**
 * Create and/or initialize the Edit Logix pane.
 */
void ConditionalListEdit::makeEditLogixWindow()
{
     //if (log->isDebugEnabled()) log->debug("makeEditLogixWindow ");
     editUserName->setText(_curLogix->getUserName());
     // clear conditional table if needed
     if (conditionalTableModel != NULL)
     {
 //        conditionalTableModel->fireTableStructureChanged();
     }
     _inEditMode = true;
     if (_editLogixFrame == NULL)
     {
      _editLogixFrame = new JmriJFrameX(tr("Edit Logix"), false, false);
      _editLogixFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);

      _editLogixFrame->addHelpMenu(
                 "package.jmri.jmrit.beantable.LogixAddEdit", true);
      _editLogixFrame->setLocation(100, 30);
      QWidget* contentPane = _editLogixFrame->centralWidget();
      if(contentPane == NULL)
      {
       _editLogixFrame->setCentralWidget(contentPane = new QWidget());
      }
      contentPane->setLayout(new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
      QWidget* panel1 = new QWidget();
      panel1->setLayout(new QHBoxLayout());
      QLabel* systemNameLabel = new QLabel(tr("System Name"));
      panel1->layout()->addWidget(systemNameLabel);
      QLabel* fixedSystemName = new QLabel(((DefaultLogix*)_curLogix)->getSystemName());
      panel1->layout()->addWidget(fixedSystemName);
      contentPane->layout()->addWidget(panel1);
      QWidget* panel2 = new QWidget();
      panel2->setLayout(new QHBoxLayout());
      QLabel* userNameLabel = new QLabel(tr("User Name"));
      panel2->layout()->addWidget(userNameLabel);
      panel2->layout()->addWidget(editUserName);
      editUserName->setToolTip(tr("Enter new user name for Logix, e.g. Signal 2 Control"));
      contentPane->layout()->addWidget(panel2);
      // add table of Conditionals
      QWidget* pctSpace = new QWidget();
      pctSpace->setLayout(new QHBoxLayout());
      pctSpace->layout()->addWidget(new QLabel("   "));
      contentPane->layout()->addWidget(pctSpace);
      QWidget* pTitle = new QWidget();
      pTitle->setLayout(new QHBoxLayout());
      pTitle->layout()->addWidget(new QLabel(tr("Conditionals (in Order of Calculation)")));
      contentPane->layout()->addWidget(pTitle);
      // initialize table of conditionals
      conditionalTableModel = new ConditionalTableModel(this);
      QTableView* conditionalTable = new QTableView();
      conditionalTable->setModel(conditionalTableModel);
      conditionalTable->resizeColumnToContents(1);
      conditionalTable->setItemDelegateForColumn(ConditionalTableModel::BUTTON_COLUMN, new PushButtonDelegate());
      //conditionalTable->setRowSelectionAllowed(false);
 //     TableColumnModel conditionalColumnModel = conditionalTable
 //             .getColumnModel();
 //     TableColumn sNameColumn = conditionalColumnModel
 //             .getColumn(ConditionalTableModel.SNAME_COLUMN);
 //     sNameColumn->setResizable(true);
 //     sNameColumn->setMinWidth(100);
 //     sNameColumn->setPreferredWidth(130);
 //     TableColumn uNameColumn = conditionalColumnModel
 //             .getColumn(ConditionalTableModel.UNAME_COLUMN);
 //     uNameColumn->setResizable(true);
 //     uNameColumn->setMinWidth(210);
 //     uNameColumn->setPreferredWidth(260);
 //     TableColumn stateColumn = conditionalColumnModel
 //             .getColumn(ConditionalTableModel.STATE_COLUMN);
 //     stateColumn->setResizable(true);
 //     stateColumn->setMinWidth(50);
 //     stateColumn->setMaxWidth(100);
 //     TableColumn buttonColumn = conditionalColumnModel
 //             .getColumn(ConditionalTableModel.BUTTON_COLUMN);
      conditionalTable->setItemDelegateForColumn(ConditionalTableModel::BUTTON_COLUMN, new ButtonEditor());
  #if 0
      // install button renderer and editor
      ButtonRenderer buttonRenderer = new ButtonRenderer();
      conditionalTable->setDefaultRenderer(QPushButton.class, buttonRenderer);
      TableCellEditor buttonEditor = new ButtonEditor(new QPushButton());
      conditionalTable->setDefaultEditor(QPushButton.class, buttonEditor);
      QPushButton testButton = new QPushButton("XXXXXX");
      conditionalTable->setRowHeight(testButton.getPreferredSize().height);
      buttonColumn->setMinWidth(testButton.getPreferredSize().width);
      buttonColumn->setMaxWidth(testButton.getPreferredSize().width);
      buttonColumn->setResizable(false);
  #endif
      //JScrollPane conditionalTableScrollPane = new JScrollPane(conditionalTable);
      QSize dim = conditionalTable->size();
      dim.setHeight(450);
      //conditionalTableScrollPane.getViewport()->setPreferredSize(dim);
      contentPane->layout()->addWidget(/*conditionalTableScrollPane*/conditionalTable);

      // add message area between table and buttons
      QWidget* panel4 = new QWidget();
      panel4->setLayout(new QVBoxLayout(panel4/*, BoxLayout.Y_AXIS*/));
      QWidget* panel41 = new QWidget();
      panel41->setLayout(new QHBoxLayout());
      panel41->layout()->addWidget(status);
      panel4->layout()->addWidget(panel41);
      QFrame* panel42 = new QFrame();
      panel42->setFrameStyle(QFrame::Box | QFrame::Raised);
      panel42->setLineWidth(2);
      panel42->setLayout(new QHBoxLayout());
      // Conditional panel buttons - New Conditional
      QPushButton* newConditionalButton = new QPushButton(tr("New Conditional"));
      QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
      sizePolicy.setHorizontalStretch(0);
      sizePolicy.setVerticalStretch(0);
      sizePolicy.setHeightForWidth(newConditionalButton->sizePolicy().hasHeightForWidth());
      newConditionalButton->setSizePolicy(sizePolicy);
      panel42->layout()->addWidget(newConditionalButton);
 //     newConditionalButton->layout()->addActionListener(new ActionListener() {
 //         /*public*/ void actionPerformed(ActionEvent e) {
 //             newConditionalPressed(e);
 //         }
 //     });
      connect(newConditionalButton, SIGNAL(clicked()), this, SLOT(newConditionalPressed()));
      newConditionalButton->setToolTip(tr("Press for window to create a new Conditional"));
      // Conditional panel buttons - Reorder
      QPushButton* reorderButton = new QPushButton(tr("Reorder"));
      reorderButton->setSizePolicy(sizePolicy);
      panel42->layout()->addWidget(reorderButton);
 //     reorderButton->layout()->addActionListener(new ActionListener() {
 //         /*public*/ void actionPerformed(ActionEvent e) {
 //             reorderPressed(e);
 //         }
 //     });
      connect(reorderButton, SIGNAL(clicked()), this, SLOT(reorderPressed()));
      reorderButton->setToolTip(tr("Press then click in right column in order desired"));
      // Conditional panel buttons - Calculate
      QPushButton* calculateButton = new QPushButton(tr("Calculate"));
      calculateButton->setSizePolicy(sizePolicy);
      panel42->layout()->addWidget(calculateButton);
 //     calculateButton->layout()->addActionListener(new ActionListener() {
 //         /*public*/ void actionPerformed(ActionEvent e) {
 //             calculatePressed(e);
 //         }
 //     });
      connect(calculateButton, SIGNAL(clicked()), this, SLOT(calculatePressed()));
      calculateButton->setToolTip(tr("Press to calculate Conditional states without action"));
      panel4->layout()->addWidget(panel42);
      //Border panel4Border = BorderFactory.createEtchedBorder();
      QGroupBox* panel4Border = new QGroupBox();
      QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
      panel4Border->setStyleSheet(gbStyleSheet);
      //panel4->setBorder(panel4Border);
      contentPane->layout()->addWidget(panel4);
      // add buttons at bottom of window
      QWidget* panel5 = new QWidget();
      panel5->setLayout(new QHBoxLayout());
      // Bottom Buttons - Done Logix
      QPushButton* done = new QPushButton(tr("Done"));
      done->setSizePolicy(sizePolicy);
      panel5->layout()->addWidget(done);
 //     done->layout()->addActionListener(new ActionListener() {
 //         /*public*/ void actionPerformed(ActionEvent e) {
 //             donePressed(e);
 //         }
 //     });
      connect(done, SIGNAL(clicked()), this, SLOT(donePressed()));
      done->setToolTip(tr("Press to save any user name changes and return to Logix Table"));
      // Delete Logix
      QPushButton* deleteButton = new QPushButton(tr("Delete Logix"));
      deleteButton->setSizePolicy(sizePolicy);
      panel5->layout()->addWidget(deleteButton);
 //     delete->layout()->addActionListener(new ActionListener() {
 //         /*public*/ void actionPerformed(ActionEvent e) {
 //             deletePressed(e);
 //         }
 //     });
      connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
      deleteButton->setToolTip(tr("Press to delete this Logix and all its Conditionals"));
      contentPane->layout()->addWidget(panel5);
     }

 //    editLogixFrame->addWindowListener(new java.awt.event.WindowAdapter() {
 //                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
 //                    if (inEditMode) {
 //                        donePressed(NULL);
 //                    } else {
 //                        finishDone();
 //                    }
 //                }
 //            });
     _editLogixFrame->addWindowListener(editLogixFrameWindowListener = new EditLogixFrameWindowListener(this));
     _editLogixFrame->adjustSize();
     _editLogixFrame->setVisible(true);
}

/*public*/ void ConditionalListEdit::bringToFront() {
    if (_editLogixFrame != NULL) {
        _editLogixFrame->setVisible(true);
    }
}

/**
 * Display reminder to save.
 */
void ConditionalListEdit::showSaveReminder() {
    /*if (_showReminder && !_suppressReminder) {
        javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
                .getString("Reminder1"),
                tr("ReminderTitle"),
                javax.swing.JOptionPane.INFORMATION_MESSAGE);
    }*/
    if (_showReminder){
        if (InstanceManager::getDefault("UserPreferencesManager") != NULL)
            ((UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager"))->
                showInfoMessage(tr("Reminder"),tr("Reminder1"),getClassName(), "remindSaveLogix");
    }
}

/**
 * Check if a string is decimal or references a decimal.
 *
 * @param actionType integer representing the Conditional action type being
 *                   checked, i.e. ACTION_DELAYED_TURNOUT
 * @param ref        entry to check
 * @return true if ref is itself a decimal or user will provide one from a
 *         Memory at run time
 */
bool ConditionalListEdit::validateTimeReference(int actionType, QString ref) {
    if (ref == "" || ref.trimmed().length() == 0) {
        displayBadNumberReference(actionType);
        return false;
    }
    try {
     bool ok;
        bool rslt = validateTime(actionType, ref.toFloat(&ok));
        if(!ok) throw NumberFormatException();
        return rslt;
        // return true if ref is decimal within allowed range
    } catch (NumberFormatException e) {
        QString memRef = ref;
        if (ref.length() > 1 && ref.at(0) == '@') {
            memRef = ref.mid(1);
        }
        if (!confirmIndirectMemory(memRef)) {
            return false;
        }
        memRef = validateMemoryReference(memRef);
        if (memRef != NULL) // memory named 'intReference' exists
        {
            Memory* m = (Memory*)InstanceManager::memoryManagerInstance()->getByUserName(memRef);
            if (m == NULL) {
                m = (Memory*)InstanceManager::memoryManagerInstance()->getBySystemName(memRef);
            }
            try {
                if (m == NULL || m->getValue() == QVariant()) {
                    throw  NumberFormatException();
                }
                bool ok;
                validateTime(actionType,  m->getValue().toFloat(&ok));
                if(!ok) throw NumberFormatException();
            } catch (NumberFormatException ex) {
                JOptionPane::showMessageDialog(
                        NULL, tr("Memory variable \"%1\" currently does not contain a numeric value.\nWhen triggered the action cannot be performed until this value is corrected!").arg(memRef), tr("Warning"), JOptionPane::WARNING_MESSAGE);   // NOI18N
            }
            return true;    // above is a warning to set memory correctly
        }
        displayBadNumberReference(actionType);
    }
    return false;
}
/**
 * Range check time entry (assumes seconds).
 *
 * @param actionType integer representing the Conditional action type being
 *                   checked, i.e. ACTION_DELAYED_TURNOUT
 * @param time       value to be checked
 * @return false if time &gt; 3600 (seconds) or too small
 */
bool ConditionalListEdit::validateTime(int actionType, float time) {
    float maxTime = 3600;     // more than 1 hour
    float minTime = 0.020f;
    if (time < minTime || time > maxTime) {
        QString errorNum = " ";
        switch (actionType) {
            case Conditional::ACTION_DELAYED_TURNOUT:
                errorNum = "Set Delayed Turnout action";       // NOI18N
                break;
            case Conditional::ACTION_RESET_DELAYED_TURNOUT:
                errorNum = "Reset Delayed Set Turnout action";       // NOI18N
                break;
            case Conditional::ACTION_DELAYED_SENSOR:
                errorNum = "Set Delayed Sensor action";       // NOI18N
                break;
            case Conditional::ACTION_RESET_DELAYED_SENSOR:
                errorNum = "Reset Delayed Set Sensor action";       // NOI18N
                break;
            case Conditional::ACTION_SET_LIGHT_TRANSITION_TIME:
                errorNum = "Set Light Transition Time";       // NOI18N
                break;
            default:
                break;
        }
        JOptionPane::showMessageDialog(
                NULL, tr("%1 is an unreasonable amount to %2\nPlease enter a positive percentage, and try again.").arg(time).arg((errorNum)), tr("Error"), JOptionPane::ERROR_MESSAGE);       // NOI18N
        return false;
    }
    return true;
}

/**
 * Responds to the Reorder Button in the Edit Logix window
 */
void ConditionalListEdit::reorderPressed(JActionEvent* /*e*/) {
    if (checkEditConditional())
        return;
    // Check if reorder is reasonable
    _showReminder = true;
    _nextInOrder = 0;
    _inReorderMode = true;
    status->setText(tr("Please press First, then Next, Next,... in desired order."));
    conditionalTableModel->fireTableDataChanged();
}


/**
 * Responds to the First/Next (Delete) Button in the Edit Logix window
 */
void ConditionalListEdit::swapConditional(int row) {
    ((DefaultLogix*)_curLogix)->swapConditional(_nextInOrder, row);
    _nextInOrder++;
    if (_nextInOrder >= _numConditionals)
    {
        _inReorderMode = false;
    }
    //status->setText("");
    conditionalTableModel->fireTableDataChanged();
}

/**
 * Responds to the Calculate Button in the Edit Logix window
 */
void ConditionalListEdit::calculatePressed(JActionEvent* /*e*/)
{
 if (checkEditConditional())
  return;
 // are there Conditionals to calculate?
 if (_numConditionals > 0)
 {
  // There are conditionals to calculate
  QString cName = "";
  Conditional* c = NULL;
  for (int i = 0; i < _numConditionals; i++)
  {
   cName = ((DefaultLogix*)_curLogix)->getConditionalByNumberOrder(i);
   if (cName != NULL)
   {
    c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cName);
    if (c == NULL)
    {
     log->error("Invalid conditional system name when calculating - " + cName);
    }
    else
    {
     // calculate without taking any action
     ((DefaultConditional*)c)->calculate(false, NULL);
    }
   }
   else
   {
    log->error("NULL conditional system name when calculating");
   }
  }
  // force the table to update
  conditionalTableModel->fireTableDataChanged();
 }
}

/**
 * Respond to the Done button in the Edit Logix window.
 * <p>
 * Note: We also get here if the Edit Logix window is dismissed, or if the
 * Add button is pressed in the Logic Table with an active Edit Logix
 * window.
 *
 * @param e The event heard
 */
void ConditionalListEdit::donePressed(JActionEvent* /*e*/) {
    if (checkEditConditional()) {
        return;
    }
    if (_curLogix->getSystemName() == (SensorGroupFrame::logixSysName)) {
        finishDone();
        return;
    }
    // Check if the User Name has been changed
    QString uName = editUserName->text().trimmed();
    if (!(uName  == (_curLogix->getUserName()))) {
        // user name has changed - check if already in use
        if (uName.length() > 0) {
            Logix* p = (Logix*)_logixManager->getByUserName(uName);
            if (p !=  NULL) {
                // Logix with this user name already exists
                log->error("Failure to update Logix with Duplicate User Name: " // NOI18N
                        + uName);
                JOptionPane::showMessageDialog(_editLogixFrame,
                        tr("New user name is already in use. Cannot update this Logix.\nPlease change user name and try again."), tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return;
            }
        }
        // user name is unique, change it
        // user name is unique, change it
        logixData->clear();
        logixData->insert("chgUname", uName);  // NOI18N
        fireLogixEvent();
    }
    // complete update and activate Logix
    finishDone();
} /* donePressed */

void ConditionalListEdit::finishDone()
{
 showSaveReminder();
 _inEditMode = false;
 if (_editLogixFrame!=NULL)
 {
  _editLogixFrame->setVisible(false);
  _editLogixFrame->dispose();
  _editLogixFrame = NULL;
 }
 logixData->clear();
 logixData->insert("Finish", _curLogix->getSystemName());   // NOI18N
 fireLogixEvent();
}


/**
 * Respond to the Delete button in the Edit Logix window.
 *
 * @param e The event heard
 */
void ConditionalListEdit::deletePressed(JActionEvent* e) {
    if (checkEditConditional()) {
        return;
    }
    if (!checkConditionalReferences(_curLogix->getSystemName())) {
        return;
    }
    _showReminder = true;
    logixData->clear();
    logixData->insert("Delete", _curLogix->getSystemName());   // NOI18N
    fireLogixEvent();
    finishDone();
}

/**
 * Responds to the New Conditional Button in Edit Logix Window
 */
void ConditionalListEdit::newConditionalPressed(JActionEvent* /*e*/)
{
 if (checkEditConditional())
  return;
 if (((DefaultLogix*)_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName))
 {
//  javax.swing.JOptionPane.showMessageDialog(
//        editLogixFrame, java.text.MessageFormat.format(tr("Warn8"),
//            new Object[] {SensorGroupFrame.logixUserName, SensorGroupFrame.logixSysName }),
//        rbx .getString("WarnTitle"),
//        javax.swing.JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(_editLogixFrame, tr("Warning"), tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName ));
  return;
 }
 // make system name for new conditional
 int num = ((DefaultLogix*)_curLogix)->getNumConditionals()+1;
 _curConditional = NULL;
 QString cName = NULL;
 while (_curConditional == NULL)
 {
  cName = ((DefaultLogix*)_curLogix)->getSystemName() + "C" + QString::number(num);
  _curConditional = ((DefaultConditionalManager*)_conditionalManager)->createNewConditional(cName, "");
  num++;
  if (num==1000) break;
 }
 if (_curConditional == NULL)
 {
  // should never get here unless there is an assignment conflict
  log->error("Failure to create Conditional with System Name: "
                + cName);
  return;
 }
 // add to Logix at the end of the calculate order
 ((DefaultLogix*)_curLogix)->addConditional(cName, -1);
  conditionalTableModel->fireTableRowsInserted(_numConditionals, _numConditionals);
  _conditionalRowNumber = _numConditionals;
  _numConditionals++;
 _showReminder = true;
  // clear action items
  _actionList = new QList <ConditionalAction*>();
  _variableList = new QList <ConditionalVariable*>();
 makeEditConditionalWindow();
}

/**
 * Responds to Edit Button in the Conditional table of the Edit Logix Window
 */
void ConditionalListEdit::editConditionalPressed(int rx)
{
 if (_inEditConditionalMode)
 {
        // Already editing a Conditional, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                java.text.MessageFormat.format(tr("Error34"),
//                        new Object[] { _curConditional::getSystemName() }),
//                tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Cannot edit two Conditionals at the same time. Please complete edit of Conditional \"%1\" and try again.").arg( _curConditional->getSystemName()));
        return;
    }
    // get Conditional to edit
    _curConditional = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(((DefaultLogix*)_curLogix)->getConditionalByNumberOrder(rx));
    if (_curConditional == NULL) {
        log->error("Attempted edit of non-existant conditional.");
        return;
    }
    _variableList = ((DefaultConditional*)_curConditional)->getCopyOfStateVariables();
    _conditionalRowNumber = rx;
    // get action variables
    _actionList = ((DefaultConditional*)_curConditional)->getCopyOfActions();
    makeEditConditionalWindow();
}  /* editConditionalPressed */

/**
 * Checks if edit of a conditional is in progress Returns true after sending
 * message if this is the case
 */
bool ConditionalListEdit::checkEditConditional()
{
 if (_inEditConditionalMode)
 {
  // Already editing a Conditional, ask for completion of that edit
//  javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                java.text.MessageFormat.format(tr("Error35"),
//                        new Object[] { _curConditional::getSystemName() }),
//                tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Edit conditional in progress. Please complete edit of Conditional \"%1\" and try again.").arg(_curConditional->getSystemName()));
  return true;
 }
 return false;
}

bool ConditionalListEdit::checkConditionalUserName(QString uName, Logix* logix)
{
 if ((uName != NULL) && (!(uName==(""))))
 {
  Conditional* p = ((DefaultConditionalManager*)_conditionalManager)->getByUserName(logix, uName);
  if (p != NULL)
  {
   // Conditional with this user name already exists
   log->error("Failure to update Conditional with Duplicate User Name: "
                    + uName);
//   javax.swing.JOptionPane.showMessageDialog(
//            editConditionalFrame, tr("Error10"), rbx
//                    .getString("Error"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("New user name is already in use. Cannot update this Conditional::\nPlease change user name and try again."));
   return false;
  }
 } // else return false;
 return true;
}

bool ConditionalListEdit::checkConditionalSystemName(QString sName)
{
 if ((sName != NULL) && (!(sName==(""))))
 {
  Conditional* p = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(sName);
  if (p != NULL) return false;
 }
 else return false;
 return true;
}

/*********************** Edit Conditional Window and Methods********************/

/**
 * Creates and/or initializes the Edit Conditional window Note: you can get
 * here via the New Conditional button (newConditionalPressed) or via an
 * Edit button in the Conditional table of the Edit Logix window.
 */
void ConditionalListEdit::makeEditConditionalWindow()
{
 // deactivate this Logix
 ((DefaultLogix*)_curLogix)->deActivateLogix();
 _conditionalUserName->setText(_curConditional->getUserName());
 if (_editConditionalFrame == NULL)
 {
  _editConditionalFrame = new JmriJFrameX(tr("Edit Conditional"), false, false);
  _editConditionalFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  _editConditionalFrame->addHelpMenu(
        "package.jmri.jmrit.conditional.ConditionalListEditor", true);
  _editConditionalFrame->resize(400,600);
  if(_editConditionalFrame->centralWidget() == NULL)
  {
   QWidget* centralWidget = new QWidget();
   _editConditionalFrame->setCentralWidget(centralWidget);
  }
//  _editConditionalFrame->resize(400, 667);
  QFont font;
  font.setPointSize(9);
  _editConditionalFrame->setFont(font);
  QWidget* contentPane = _editConditionalFrame->centralWidget();
  QVBoxLayout* contentPaneLayout;
  contentPane->setLayout(contentPaneLayout = new QVBoxLayout(contentPane/*, BoxLayout.Y_AXIS*/));
  QWidget* panel1 = new QWidget();
  FlowLayout* panel1Layout;
  panel1->setLayout(panel1Layout = new  FlowLayout());
  panel1Layout->addWidget(new QLabel(tr("Conditional System Name")));
  panel1Layout->addWidget(new QLabel(_curConditional->getSystemName()));
  contentPaneLayout->addWidget(panel1);
  QWidget* panel2 = new QWidget();
  FlowLayout* panel2Layout = new FlowLayout(panel2);
  panel2Layout->addWidget(new QLabel(tr("Conditional User Name")));
  panel2Layout->addWidget(_conditionalUserName);
  _conditionalUserName->setToolTip(tr("Enter user name for Conditional, e.g. Signal 2 Red"));
  contentPaneLayout->addWidget(panel2);
  QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  // add Logical Expression Section
  QGroupBox* logicPanel = new QGroupBox(tr("Logical Expression"));
  logicPanel->setLayout(new QVBoxLayout(logicPanel/*, BoxLayout.Y_AXIS)*/));
  logicPanel->setStyleSheet(gbStyleSheet);
  // add Antecedent Expression Panel -ONLY appears for MIXED operator statements
  _antecedent = ((DefaultConditional*)_curConditional)->getAntecedentExpression();
  _logicType = ((DefaultConditional*)_curConditional)->getLogicType();
  _antecedentField = new JTextField(65);
  _antecedentField->setFont( QFont("SansSerif", 14, QFont::Bold));
  _antecedentField->setText(_antecedent);
  _antecedentPanel = makeEditPanel(_antecedentField, tr("Antecedent Expression (the 'if' part of the Conditional)"), tr("Insert parenthesis so the statement satisfies the logic you want"));

  QPushButton* helpButton = new QPushButton(tr("Help"));
  _antecedentPanel->layout()->addWidget(helpButton);
//  helpButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        helpPressed(e);
//    }
//  });
  connect(helpButton, SIGNAL(clicked()), this, SLOT(helpPressed()));
  _antecedentPanel->layout()->addWidget(helpButton);
  _antecedentPanel->setVisible(_logicType == Conditional::MIXED);
  logicPanel->layout()->addWidget(_antecedentPanel);

  // add state variable table title
  QWidget* varTitle = new QWidget();
  varTitle->setLayout(new FlowLayout());
  QFont font2 = varTitle->font();
  font2.setBold(true);
  varTitle->setFont(font2);
  varTitle->layout()->addWidget(new QLabel(tr("Antecedent Variables (the 'if' part)")));
  varTitle->layout()->setAlignment(Qt::AlignHCenter);
  logicPanel->layout()->addWidget(varTitle);
  // set up state variables table
  // initialize and populate Combo boxes for table of state variables
  _notOperatorBox = new QComboBox();
  _notOperatorBox->addItem(" ");
  _notOperatorBox->addItem(tr("NOT"));

  _andOperatorBox = new QComboBox();
  _andOperatorBox->addItem(tr(" AND"));
  _andOperatorBox->addItem(tr(" OR"));
  // initialize table of state variables
  _variableTableModel = new LVariableTableModel(this);
  JTable* variableTable = new JTable();
  variableTable->setModel(_variableTableModel);
  variableTable->setItemDelegateForColumn(LVariableTableModel::EDIT_COLUMN,new PushButtonDelegate());
  variableTable->setItemDelegateForColumn(LVariableTableModel::DELETE_COLUMN,new PushButtonDelegate());
  //variableTable->setRowHeight(_notOperatorBox.getPreferredSize().height);
  //variableTable->setRowSelectionAllowed(false);
  //int rowHeight = variableTable->rowHeight(0);
#if 1
TableColumnModel* variableColumnModel = variableTable->getColumnModel();

TableColumn* rowColumn = variableColumnModel->getColumn(VariableTableModel::ROWNUM_COLUMN);
rowColumn->setResizable(false);
rowColumn->setMaxWidth( JTextField(3).getPreferredSize().width());

TableColumn* andColumn = variableColumnModel->getColumn(VariableTableModel::AND_COLUMN);
andColumn->setResizable(false);
//andColumn->setCellEditor(new DefaultCellEditor(_andOperatorBox));
andColumn->setMaxWidth(_andOperatorBox->sizeHint().width() - 5);

TableColumn* notColumn = variableColumnModel->getColumn(VariableTableModel::NOT_COLUMN);
//notColumn->setCellEditor(new DefaultCellEditor(_notOperatorBox));
notColumn->setMaxWidth(_notOperatorBox->sizeHint().width() - 5);
notColumn->setResizable(false);

TableColumn* descColumn = variableColumnModel->getColumn(VariableTableModel::DESCRIPTION_COLUMN);
descColumn->setPreferredWidth(300);
descColumn->setMinWidth(200);
descColumn->setResizable(true);

TableColumn* stateColumn = variableColumnModel->getColumn(VariableTableModel::STATE_COLUMN);
stateColumn->setResizable(true);
stateColumn->setMinWidth(50);
stateColumn->setMaxWidth(80);

TableColumn* triggerColumn = variableColumnModel->getColumn(VariableTableModel::TRIGGERS_COLUMN);
triggerColumn->setResizable(true);
triggerColumn->setMinWidth(30);
triggerColumn->setMaxWidth(80);

TableColumn* editColumn = variableColumnModel->getColumn(VariableTableModel::EDIT_COLUMN);
//ButtonRenderer buttonRenderer = new ButtonRenderer();
//variableTable->setDefaultRenderer(QPushButton.class, buttonRenderer);
//TableCellEditor buttonEditor = new ButtonEditor(new QPushButton());
//variableTable->setDefaultEditor(QPushButton.class, buttonEditor);
QPushButton* testButton = new QPushButton("XXXXXX");
variableTable->setRowHeight(testButton->sizeHint().height());
editColumn->setMinWidth(testButton->sizeHint().width());
editColumn->setMaxWidth(testButton->sizeHint().width());
editColumn->setResizable(false);

TableColumn* deleteColumn = variableColumnModel->getColumn(VariableTableModel::DELETE_COLUMN);
// ButtonRenderer and TableCellEditor already set
deleteColumn->setMinWidth(testButton->sizeHint().width());
deleteColumn->setMaxWidth(testButton->sizeHint().width());
deleteColumn->setResizable(false);
// add a scroll pane
//JScrollPane variableTableScrollPane = new JScrollPane(variableTable);
#endif
int rowHeight = variableTable->rowHeight();
  QSize dim = variableTable->size();
  dim.setHeight(7*rowHeight);
  //variableTableScrollPane.getViewport()->setPreferredSize(dim);
  variableTable->viewport()->resize(dim);

  logicPanel->layout()->addWidget(variableTable);

  // set up state variable buttons and logic
  QWidget* panel42 = new QWidget();
  panel42->setLayout(new QHBoxLayout());
        //  Add State Variable
  QPushButton*  addVariableButton = new QPushButton(tr("Add State Variable"));
  QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(addVariableButton->sizePolicy().hasHeightForWidth());
  panel42->layout()->addWidget(addVariableButton);
  addVariableButton->setSizePolicy(sizePolicy);
//  addVariableButton->layout()->addActionListener(new ActionListener(){
//    /*public*/ void actionPerformed(ActionEvent e) {
//        addVariablePressed(e);
//    }
//});
  connect(addVariableButton, SIGNAL(clicked()), this, SLOT(addVariablePressed()));

  QPushButton* checkVariableButton = new QPushButton(tr("Check State Variables"));
  checkVariableButton->setSizePolicy(sizePolicy);
  panel42->layout()->addWidget(checkVariableButton);
//checkVariableButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        checkVariablePressed(e);
//    }
//});
  connect(checkVariableButton, SIGNAL(clicked()), this, SLOT(checkVariablePressed()));
  checkVariableButton->setToolTip(tr("Press to evaluate current state of the Variables"));
  logicPanel->layout()->addWidget(panel42);

  // logic type area
  QStringList l = QStringList() << tr("AND") <<
          tr("OR") <<
          tr("Mixed");
 _operatorBox = new QComboBox();
 _operatorBox->addItems(l);
 QWidget* typePanel = makeEditPanel(_operatorBox, tr("Logic Operator"), tr("Choose logic operator joining state variables for the antecedent ('if' part) of this conditional"));
// _operatorBox->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        logicTypeChanged(e);
//    }
//});
 connect(_operatorBox, SIGNAL(currentIndexChanged(int)), this, SLOT(logicTypeChanged()));
 _operatorBox->setCurrentIndex(_logicType-1);
 logicPanel->layout()->addWidget(typePanel);
 //logicPanel->layout()->addWidget(Box.createHorizontalStrut(STRUT));

//Border logicPanelBorder = BorderFactory.createEtchedBorder();
//Border logicPanelTitled = BorderFactory.createTitledBorder(
//        logicPanelBorder, tr("TitleLogicalExpression"));
 //logicPanel->setBorder(logicPanelTitled);
  //logicPanel->layout()->addWidget(logicPanelBorder);
 contentPane->layout()->addWidget(logicPanel);
 // End of Logic Expression Section

 _actionTableModel = new ActionTableModel(this);

  QWidget* triggerPanel = new QWidget();
  triggerPanel->setLayout(new QVBoxLayout(triggerPanel/*, BoxLayout.Y_AXIS*/));
  QButtonGroup* tGroup = new QButtonGroup();
  _triggerOnChangeButton = new QRadioButton(tr("Execute actions on change of state only"));
//  _triggerOnChangeButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        _actionTableModel.fireTableDataChanged();
//    }
//});
  connect(_triggerOnChangeButton, SIGNAL(toggled(bool)), _actionTableModel, SLOT(fireTableDataChanged()));
  tGroup->addButton(_triggerOnChangeButton);
  triggerPanel->layout()->addWidget(_triggerOnChangeButton);
  QRadioButton* triggerOnAny = new QRadioButton(tr("Execute Actions whenever triggered"));
//  triggerOnAny->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        _actionTableModel.fireTableDataChanged();
//    }
//});
  connect(_triggerOnChangeButton, SIGNAL(toggled(bool)), _actionTableModel, SLOT(fireTableDataChanged()));
  tGroup->addButton(triggerOnAny);
  triggerPanel->layout()->addWidget(triggerOnAny);
  triggerOnAny->setChecked(true);
  QWidget* trigPanel = new QWidget();
  trigPanel->setLayout(new QVBoxLayout());
  trigPanel->layout()->addWidget(triggerPanel);
  contentPane->layout()->addWidget(trigPanel);
  _triggerOnChangeButton->setChecked(((DefaultConditional*)_curConditional)->getTriggerOnChange());

  // add Action Consequents Section
  QGroupBox* consequentPanel = new QGroupBox(tr("Actions"));
  consequentPanel->setLayout(new QVBoxLayout(consequentPanel/*, BoxLayout.Y_AXIS*/));
 consequentPanel->setStyleSheet(gbStyleSheet);

  QWidget* actTitle = new QWidget();
  actTitle->setLayout(new QHBoxLayout());
  QFont font3 = actTitle->font();
  font3.setBold(true);
  actTitle->setFont(font3);
  actTitle->layout()->addWidget(new QLabel(tr("Consequent Actions (the 'then' part) ")));
  actTitle->layout()->setAlignment(Qt::AlignHCenter);

  consequentPanel->layout()->addWidget(actTitle);

  // set up action consequents table
  //_actionTableModel = new ActionTableModel(this);
  QTableView* actionTable = new QTableView();
  actionTable->setModel(_actionTableModel);
  //actionTable->setRowSelectionAllowed(false);
  //actionTable->setRowHeight(testButton.getPreferredSize().height);
//  QWidget* actionPanel = new QWidget();
//  actionPanel->setLayout(new QVBoxLayout(actionPanel/*, BoxLayout.Y_AXIS*/));
//  QWidget* actionTitle = new QWidget();
//  actionTitle->setLayout(new QHBoxLayout());
//  consequentPanel->layout()->addWidget(actionPanel);
  consequentPanel->layout()->addWidget(actionTable);
  actionTable->setColumnWidth(ActionTableModel::DESCRIPTION_COLUMN, 300);
#if 0
TableColumnModel actionColumnModel = actionTable.getColumnModel();

TableColumn descriptionColumn = actionColumnModel.getColumn(
    ActionTableModel.DESCRIPTION_COLUMN);
descriptionColumn->setResizable(true);
descriptionColumn->setPreferredWidth(600);
descriptionColumn->setMinWidth(300);
//descriptionColumn->setMaxWidth(760);

TableColumn actionEditColumn = actionColumnModel.getColumn(ActionTableModel.EDIT_COLUMN);
// ButtonRenderer already exists
actionTable->setDefaultRenderer(QPushButton.class, buttonRenderer);
TableCellEditor editButEditor = new ButtonEditor(new QPushButton());
actionTable->setDefaultEditor(QPushButton.class, editButEditor);
actionEditColumn->setMinWidth(testButton.getPreferredSize().width);
actionEditColumn->setMaxWidth(testButton.getPreferredSize().width);
actionEditColumn->setResizable(false);

TableColumn actionDeleteColumn = actionColumnModel.getColumn(ActionTableModel.DELETE_COLUMN);
// ButtonRenderer and TableCellEditor already set
actionDeleteColumn->setMinWidth(testButton.getPreferredSize().width);
actionDeleteColumn->setMaxWidth(testButton.getPreferredSize().width);
actionDeleteColumn->setResizable(false);
// add a scroll pane
JScrollPane actionTableScrollPane = new JScrollPane(actionTable);
#endif

//dim = actionTableScrollPane.getPreferredSize();
//dim.height = 7*rowHeight;
//actionTableScrollPane.getViewport()->setPreferredSize(dim);
  consequentPanel->layout()->addWidget(actionTable);

  // add action buttons to Action Section
  QWidget* panel43 = new QWidget();
  panel43->setLayout(new QHBoxLayout());
  QPushButton* addActionButton = new QPushButton(tr("Add Action"));
  QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
  sizePolicy1.setHorizontalStretch(0);
  sizePolicy1.setVerticalStretch(0);
  sizePolicy1.setHeightForWidth(addActionButton->sizePolicy().hasHeightForWidth());
  addActionButton->setSizePolicy(sizePolicy1);
  panel43->layout()->addWidget(addActionButton);
//  addActionButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        addActionPressed(e);
//    }
//  });
  connect(addActionButton, SIGNAL(clicked()), this, SLOT(addActionPressed()));

  addActionButton->setToolTip(tr("Press to add a new row to Action Table"));
  consequentPanel->layout()->addWidget(panel43);
  //  - Reorder action button
  QPushButton* reorderButton = new QPushButton(tr("Reorder"));
  reorderButton->setSizePolicy(sizePolicy);
  panel43->layout()->addWidget(reorderButton);
//  reorderButton->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        reorderActionPressed(e);
//    }
//  });
  connect(reorderButton, SIGNAL(clicked()), this, SLOT(reorderActionPressed()));
  reorderButton->setToolTip(tr("Press then click in right column in order desired"));
  consequentPanel->layout()->addWidget(panel43);

//  Border conseqentPanelBorder = BorderFactory.createEtchedBorder();
//  Border conseqentPanelTitled = BorderFactory.createTitledBorder(
//        conseqentPanelBorder, tr("TitleAction"));
//  conseqentPanel->setBorder(conseqentPanelTitled);
//  consequentPanel->setFrameStyle(QFrame::Box | QFrame::Raised);
//  consequentPanel->setLineWidth(2);
  contentPane->layout()->addWidget(consequentPanel);
  // End of Action Consequents Section

  // Bottom Buttons - Update Conditional
  QWidget* panel5 = new QWidget();
  panel5->setLayout(new QHBoxLayout());
  QPushButton* updateConditional = new QPushButton(tr("Update Conditional"));
  panel5->layout()->addWidget(updateConditional);
//  updateConditional->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        updateConditionalPressed(e);
//    }
//  });
  connect(updateConditional, SIGNAL(clicked()), this, SLOT(updateConditionalPressed()));
  updateConditional->setToolTip(tr("Press to keep changes and return to Edit Logix"));
  // Cancel
  QPushButton* cancelConditional = new QPushButton(tr("Cancel"));
  panel5->layout()->addWidget(cancelConditional);
//  cancelConditional->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        cancelConditionalPressed(e);
//    }
//  });
  connect(cancelConditional, SIGNAL(clicked()), this, SLOT(cancelConditionalPressed()));
  cancelConditional->setToolTip(tr("Press to return to Edit Logix without any changes"));
  // Delete Conditional
  QPushButton* deleteConditional = new QPushButton(tr("Delete Conditional"));
  panel5->layout()->addWidget(deleteConditional);
//  deleteConditional->layout()->addActionListener(new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
//        deleteConditionalPressed(NULL);
//    }
//  });
  connect(deleteConditional, SIGNAL(clicked()), this, SLOT(on_deleteConditionalPressed()));
  deleteConditional->setToolTip(tr("Press to delete this Conditional and return to Edit Logix"));

  contentPane->layout()->addWidget(panel5);
 }
//    // setup window closing listener
//    editConditionalFrame->layout()->addWidgetWindowListener(
//        new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    cancelConditionalPressed(NULL);
//                }
//            });
 _editConditionalFrame->addWindowListener(new ECFWindowListener(this));
 // initialize state variable table
 _variableTableModel->fireTableDataChanged();
 // initialize action variables
 _actionTableModel->fireTableDataChanged();
 _editConditionalFrame->pack();
 _editConditionalFrame->setVisible(true);
 _inEditConditionalMode = true;
 checkVariablePressed(NULL);     // update variables to their current states
}   /* makeEditConditionalWindow */

ECFWindowListener::ECFWindowListener(ConditionalListEdit *self)
{
 this->self = self;
}
void ECFWindowListener::windowClosing(QCloseEvent */*e*/)
{
 self->cancelConditionalPressed(NULL);
}

void ConditionalListEdit::on_deleteConditionalPressed()
{
 deleteConditionalPressed("");
}

/**
 * Responds to the Add State Variable Button in the Edit Conditional window
 */
void ConditionalListEdit::addVariablePressed(JActionEvent* /*e*/)
{
 if (alreadyEditingActionOrVariable())
 {
  return;
 }
 if (LRouteTableAction::LOGIX_INITIALIZER==(((DefaultLogix*)_curLogix)->getSystemName()))
 {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("Error49"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("LRoute Initializer antecedent cannot be edited.  (The actions may be edited)"));
  return;
 }
 _showReminder = true;
 ConditionalVariable* variable = new ConditionalVariable();
 _variableList->append(variable);
 _newItem = true;
 int size = _variableList->size();
 // default of operator for postion 0 (row 1) is Conditional::OPERATOR_NONE
 if (size > 1)
 {
  if (_logicType == Conditional::ALL_OR)
   variable->setOpern(Conditional::OPERATOR_OR);
  else
   variable->setOpern(Conditional::OPERATOR_AND);
 }
 size--;
 _variableTableModel->fireTableRowsInserted(size, size);
 makeEditVariableWindow(size);
 appendToAntecedent(variable);
}

/**
 * Responds to the Check State Variable Button in the Edit Conditional window
 */
void ConditionalListEdit::checkVariablePressed(JActionEvent* /*e*/) {
    for (int i=0; i<_variableList->size(); i++)
    {
        _variableList->at(i)->evaluate();
    }
    _variableTableModel->fireTableDataChanged();
}

/**
 * Responds to the Negation column in the Edit Conditional window
 */
void ConditionalListEdit::variableNegationChanged(int row, QString oper) {
    ConditionalVariable* variable = _variableList->at(row);
    bool state = variable->isNegated();
    if (oper == NULL)
        variable->setNegation(false);
    else
        variable->setNegation(oper==(tr("NOT")));
    if (variable->isNegated() != state )
        makeAntecedent();
}

/**
 * Responds to the Operator column in the Edit Conditional window
 */
void ConditionalListEdit::variableOperatorChanged(int row, QString oper) {
    ConditionalVariable* variable = _variableList->at(row);
    int oldOper = variable->getOpern();
    if (row > 0)
    {
        if (oper==(tr("OR")))
            variable->setOpern(Conditional::OPERATOR_OR);
        else
            variable->setOpern(Conditional::OPERATOR_AND);
    }
    else
        variable->setOpern(Conditional::OPERATOR_NONE);
    if (variable->getOpern() != oldOper )
        makeAntecedent();

}

/*
* Responds to Add action button in the EditConditional window
*/
void ConditionalListEdit::addActionPressed(JActionEvent* /*e*/) {
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    _showReminder = true;
    _actionList->append(new DefaultConditionalAction());
    _newItem = true;
    _actionTableModel->fireTableRowsInserted(_actionList->size(),
            _actionList->size());
    makeEditActionWindow(_actionList->size() - 1);
}

/**
 * Responds to the Reorder Button in the Edit Conditional window
 */
void ConditionalListEdit::reorderActionPressed(JActionEvent* /*e*/) {
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    _showReminder = true;
    // Check if reorder is reasonable
    if (_actionList->size() <= 1) {
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
//                .getString("Error46"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_editLogixFrame, tr("Error"), tr("At least two Actions are needed to reorder Actions."));
        return;
    }
    _nextInOrder = 0;
    _inReorderMode = true;
    //status->setText(tr("ReorderMessage"));
    _actionTableModel->fireTableDataChanged();
}

/**
 * Responds to the First/Next (Delete) Button in the Edit Conditional window
 */
void ConditionalListEdit::swapActions(int row) {
    ConditionalAction* temp = _actionList->at(row);
    for (int i = row; i > _nextInOrder; i--)
    {
        _actionList->replace(i, _actionList->at(i-1));
    }
    _actionList->replace(_nextInOrder, temp);
    _nextInOrder++;
    if (_nextInOrder >= _actionList->size())
    {
        _inReorderMode = false;
    }
    //status->setText("");
    _actionTableModel->fireTableDataChanged();
}

/**
* Responds to the Update Conditional Button in the Edit Conditional window
*/
void ConditionalListEdit::updateConditionalPressed(/*ActionEvent* e*/) {
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    // clean up empty variable and actions
    if (LRouteTableAction::LOGIX_INITIALIZER!=(((DefaultLogix*)_curLogix)->getSystemName())) {
        for (int i=0; i<_variableList->size(); i++) {
            if (_variableList->at(i)->getType() == Conditional::TYPE_NONE) {
                _variableList->removeAt(i);
                _variableTableModel->fireTableRowsDeleted(i, i);
            }
        }
    }
    for (int i=0; i<_actionList->size(); i++) {
        if (_actionList->at(i)->getType() == Conditional::ACTION_NONE) {
            _actionList->removeAt(i);
            _actionTableModel->fireTableRowsDeleted(i, i);
        }
    }

    if (_variableList->size() <= 0 && _actionList->size() <= 0) {
        deleteConditionalPressed(NULL);
        return;
    }
  /*  if (_curConditional==NULL) {
        return;
    } */
    if (((DefaultLogix*)_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName)) {
//        javax.swing.JOptionPane.showMessageDialog(
//                editConditionalFrame, java.text.MessageFormat.format(tr("Warn8"),
//                    new Object[] {SensorGroupFrame.logixUserName, SensorGroupFrame.logixSysName})+
//                    java.text.MessageFormat.format(tr("Warn11"),
//                    new Object[] {_curConditional::getUserName(), _curConditional::getSystemName() }),
//                    rbx .getString("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_editConditionalFrame, tr("Warning"),tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName));
        cancelConditionalPressed(NULL);
        return;
    }
    // Check if the User Name has been changed
    QString uName = _conditionalUserName->text().trimmed();
    if (uName!=NULL && !(uName==(_curConditional->getUserName()))) {
        // user name has changed - check if already in use
        if (!checkConditionalUserName(uName, _curLogix)) {
            return;
        }
        // user name is unique or blank, change it
        _curConditional->setUserName(uName);
        conditionalTableModel->fireTableDataChanged();
    }
    if (_variableList->size() <= 0 && !_suppressReminder) {
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Warn5"),
//                        new Object[] {_curConditional::getUserName(), _curConditional::getSystemName() }),
//                         tr("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_editLogixFrame, tr("Warning"), tr("The Conditional %1 (%2) has no State Variables.\nA Conditional must have at least one State Variable to do anything useful.").arg(_curConditional->getUserName()).arg(_curConditional->getSystemName()));
    }

    if (!validateAntecedent()) {
        return;
    }
    // complete update
    ((DefaultConditional*)_curConditional)->setStateVariables(_variableList);
    ((DefaultConditional*)_curConditional)->setAction(_actionList);
    ((DefaultConditional*)_curConditional)->setLogicType(_logicType, _antecedent);
    ((DefaultConditional*)_curConditional)->setTriggerOnChange(_triggerOnChangeButton->isChecked());
    cancelConditionalPressed(NULL);
}

/**
 * Responds to the Cancel button in the Edit Conditional frame
 * Does the cleanup from deleteConditionalPressed, updateConditionalPressed
 * and editConditionalFrame window closer.
 */
void ConditionalListEdit::cancelConditionalPressed(JActionEvent* /*e*/) {
    if (_pickTables!=NULL) {
        _pickTables->dispose();
        _pickTables = NULL;
    }
    if (_editActionFrame != NULL) {
        cleanUpAction();
    }
    if (_editVariableFrame != NULL) {
        cleanUpVariable();
    }
    try {
        ((DefaultLogix*)_curLogix)->activateLogix();
    } catch (NumberFormatException nfe) {
        if (log->isDebugEnabled()) log->error("NumberFormatException on activation of Logix "+nfe.getMessage());
        //nfe.printStackTrace();
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                tr("Error4")+nfe.toString()+tr("Error7"),
//                tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_editLogixFrame, tr("Error"), tr("The following error occurred when activating this Logix.")+nfe.getMessage()+tr("Please correct the reference or delete the offending Conditional or Logix."));
    }
    // when user uses the escape key and returns to editing, interaction with
    // window closing event create strange environment
    _inEditConditionalMode = false;
    if (_editConditionalFrame != NULL) {
        //editConditionalFrame->setVisible(false);
        _editConditionalFrame->dispose();
        _editConditionalFrame = NULL;
    }
    if (_editLogixFrame !=NULL) {
        _editLogixFrame->setVisible(true);
    }
}

/**
 * Responds to the Delete Conditional Button in the Edit Conditional window
 */
void ConditionalListEdit::deleteConditionalPressed(QString sName) {
    if (_curConditional==NULL) {
        return;
    }
    // delete this Conditional - this is done by the parent Logix
    if (sName == "") {
        sName = _curConditional->getSystemName();
    }
    if (sName == NULL) {
        if (log->isDebugEnabled()) log->error("Unable to delete Conditional, NULL system name");
        return;
    }
    _showReminder = true;
    _curConditional = NULL;
    _numConditionals--;
    QStringList* msgs = ((DefaultLogix*)_curLogix)->deleteConditional(sName);
    if (msgs != NULL) {
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame,
//                java.text.MessageFormat.format(tr("Error11"), (Object[])msgs),
//                tr("ErrorTitle"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_editLogixFrame, tr("Error"), tr("Conditional \"%1\" (%2) is a Conditional Variable in the Conditional,\n\"%3\" (%4), of Logix, \"%5\" (%6).\n                                                          Please remove that variable first.").arg(msgs->at(0)).arg(msgs->at(1)).arg(msgs->at(2)).arg(msgs->at(3)).arg(msgs->at(4)).arg(msgs->at(5)));
    }
    // complete deletion
    cancelConditionalPressed(NULL);
    conditionalTableModel->fireTableRowsDeleted(_conditionalRowNumber,
            _conditionalRowNumber);
    if (_numConditionals < 1 && !_suppressReminder) {
        // warning message - last Conditional deleted
//        javax.swing.JOptionPane.showMessageDialog(editLogixFrame, rbx
//                .getString("Warn1"), tr("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_editLogixFrame, tr("Warning"), tr("The last Conditional has been deleted from this Logix."));
    }
}


//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
bool ConditionalListEdit::logicTypeChanged(JActionEvent* /*e*/) {
    int type = _operatorBox->currentIndex() + 1;
    if (type == _logicType) {
            return false;
    }
    makeAntecedent();
    int oper = Conditional::OPERATOR_OR;
    switch (type) {
        case Conditional::ALL_AND:
            oper = Conditional::OPERATOR_AND;
            // fall through
        case Conditional::ALL_OR:
            for (int i=1; i<_variableList->size(); i++)
            {
                _variableList->at(i)->setOpern(oper);
            }
            _antecedentPanel->setVisible(false);
            break;
        case Conditional::MIXED:
            _antecedentPanel->setVisible(true);
        default : break;
    }
    _logicType = type;
    _variableTableModel->fireTableDataChanged();
    //editConditionalFrame.repaint();
    return true;
}

void ConditionalListEdit::helpPressed(JActionEvent* /*e*/) {
#if 0
    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
            new String[] {
                tr("LogicHelpText1"),
                tr("LogicHelpText2"),
                tr("LogicHelpText3"),
                tr("LogicHelpText4"),
                tr("LogicHelpText5"),
                tr("LogicHelpText6"),
                tr("LogicHelpText7")
            },
    tr("HelpButton"), javax.swing.JOptionPane.INFORMATION_MESSAGE);
#endif
}

/**
* build the antecedent statement
*/
void ConditionalListEdit::makeAntecedent()
{
 QString str = "";
 if (_variableList->size()!=0)
 {
        QString _not = tr("NOT").toLower();
        QString row = tr("R");
        QString _and = " " + tr("AND").toLower() + " ";
        QString _or = " " + tr("OR").toLower() + " ";
        if (_variableList->at(0)->isNegated())
        {
            str = _not+ " ";
        }
        str = str + row + "1";
        for (int i=1; i<_variableList->size(); i++) {
            ConditionalVariable* variable = _variableList->at(i);
            switch (variable->getOpern() ) {
                case Conditional::OPERATOR_AND:
                    str = str + _and;
                    break;
                case Conditional::OPERATOR_OR:
                    str = str + _or;
                    break;
                default : break;
            }
            if (variable->isNegated())
            {
                str = str + _not;
            }
            str = str + row + (i+1);
            if (i>0 && i+1<_variableList->size()) {
                str = "(" + str  + ")";
            }
        }
    }
    _antecedent = str;
    _antecedentField->setText(_antecedent);
    _showReminder = true;
}

void ConditionalListEdit::appendToAntecedent(ConditionalVariable* /*variable*/)
{
 if (_variableList->size() > 1)
 {
  if (_logicType == Conditional::OPERATOR_OR)
  {
   _antecedent = _antecedent + " " + tr("OR").toLower() + " ";
  }
  else
  {
   _antecedent = _antecedent + " " + tr("AND").toLower() + " ";
  }
 }
  _antecedent = _antecedent + tr("R") + _variableList->size();
  _antecedentField->setText(_antecedent);
}

/**
*  Check the antecedent and logic type
*/
bool ConditionalListEdit::validateAntecedent()
{
 if (_logicType !=Conditional::MIXED || LRouteTableAction::LOGIX_INITIALIZER==(((DefaultLogix*)_curLogix)->getSystemName()))
 {
  return true;
 }
 _antecedent = _antecedentField->text();
 if (_antecedent == "" || _antecedent.trimmed().length() == 0)
 {
  makeAntecedent();
 }
 QString message = ((DefaultConditional*)_curConditional)->validateAntecedent(_antecedent, _variableList);
 if (message != "")
 {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                message+tr("ParseError8"),  tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("If the above message is 'String index out of range:', the following number is the position in the antecedent where the error occurred."));
  return false;
 }
 return true;
}

// ============ Shared Variable and Action Methods ============
/**
 * Check if an editing session is going on.
 * <p>
 * If it is, display a message to user and bring current editing pane to
 * front.
 *
 * @return true if an _editActionFrame or _editVariableFrame exists
 */
bool ConditionalListEdit::alreadyEditingActionOrVariable()
{
 if (_editActionFrame != NULL)
 {
        // Already editing an Action, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(_editActionFrame,
//                tr("Error48"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editActionFrame, tr("Error"), tr("Edit of Action in progress. Please complete edit and try again."));
  _editActionFrame->setVisible(true);
  return true;
 }
 if (_editVariableFrame != NULL)
 {
        // Already editing a state variable, ask for completion of that edit
//        javax.swing.JOptionPane.showMessageDialog(_editVariableFrame,
//                tr("Error47"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(_editActionFrame, tr("Error"), tr("Edit of State Variable in progress. Please complete and try again."));
  _editVariableFrame->setVisible(true);
  return true;
 }
 return false;
}
/**
 * Fetch valid appearances for a given Signal Head.
 * <p>
 * Warn if head is not found.
 *
 * @param box            the comboBox on the setup pane to fill
 * @param signalHeadName user or system name of the Signal Head
 */
void ConditionalListEdit::loadJComboBoxWithHeadAppearances(QComboBox* box, QString signalHeadName) {
    box->clear();
    log->debug("loadJComboBoxWithSignalHeadAppearances called with name: " + signalHeadName);  // NOI18N
    SignalHead* h = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
    if (h == NULL) {
        box->addItem(tr("(Type Signal Head name in the System/User Name field and hit Enter)"));  // NOI18N
    } else {
        QVector<QString> v = h->getValidStateNames();
        for (int i = 0; i < v.length(); i++) {
            box->addItem(v.at(i));
        }
        box->setCurrentText(h->getAppearanceName());
    }
}

/**
 * Fetch valid aspects for a given Signal Mast.
 * <p>
 * Warn if mast is not found.
 *
 * @param box      the comboBox on the setup pane to fill
 * @param mastName user or system name of the Signal Mast
 */
void ConditionalListEdit::loadJComboBoxWithMastAspects(QComboBox* box, QString mastName) {
    box->clear();
    log->debug("loadJComboBoxWithMastAspects called with name: " + mastName);  // NOI18N
    SignalMast* m = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(mastName);
    if (m == NULL) {
        box->addItem(tr("(Type Signal Mast name in the System/User Name field and hit Enter)"));  // NOI18N
    } else {
        QVector<QString> v = m->getValidAspects();
        for (int i = 0; i < v.size(); i++) {
            box->addItem(v.value(i));
        }
        box->setCurrentText(m->getAspect());
    }
}

void ConditionalListEdit::loadJComboBoxWithSignalAspects(QComboBox* box, QString signalName)
{
 box->clear();
 log->debug("loadJComboBoxWithSignalAspects called with name: "+signalName);
 SignalHead* h = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalName);
 if (h == NULL)
 {
  box->addItem(tr("(Type signal name and hit Enter)"));
 }
 else
 {
  QVector<QString> v = h->getValidStateNames();
  for (int i = 0; i<v.size(); i++)
  {
   box->addItem(v.at(i));
  }
  box->setCurrentIndex(box->findText(h->getAppearanceName()));
 }
}
// ------------ Build sub-panels ------------
/**
 * Create Variable and Action editing pane top part.
 *
 * @param frame  JFrame to add to
 * @param title  property key for border title
 * @param width  fixed dimension to use
 * @param height fixed dimension to use
 * @return JPanel containing interface
 */
QWidget* ConditionalListEdit::makeTopPanel(QWidget* /*frame*/, QString title, int width, int /*height*/) {
//    Container contentPane = frame.getContentPane();
//    contentPane->setLayout(new BoxLayout(contentPane, BoxLayout.X_AXIS));
//    contentPane->layout()->addWidget(Box.createRigidArea(new Dimension(0, height)));
    QGroupBox* topPanel = new QGroupBox(title);
    topPanel->setLayout(new QVBoxLayout(topPanel/*, BoxLayout.Y_AXIS*/));
//    Border panelBorder = BorderFactory.createEtchedBorder();
//    Border panelTitled = BorderFactory.createTitledBorder(panelBorder, tr(title));
//    topPanel->setBorder(panelTitled);
    topPanel->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ");
//    topPanel->layout()->addWidget(Box::createRigidArea(QSize(width, 0)));
//    topPanel->layout()->addWidget(Box::createVerticalGlue());
    return topPanel;
}
/**
 * Create Variable and Action editing pane center part.
 *
 * @param comp  Field or comboBox to include on sub pane
 * @param label property key for label
 * @param hint  property key for tooltip for this sub pane
 * @return JPanel containing interface
 */
QWidget* ConditionalListEdit::makeEditPanel(QWidget* comp, QString label, QString hint)
{
    QWidget* panel = new QWidget();
    panel->setObjectName("panel");
    QVBoxLayout* panelLayout;
    panel->setLayout(panelLayout = new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
    panelLayout->setObjectName("editPanelVerticalLayout");
    QWidget* p = new QWidget();
    p->setLayout(new QHBoxLayout());
    QLabel* l = new QLabel(label);
    QFont font1;
    font1.setBold(true);
    font1.setWeight(75);
    l->setFont(font1);
    l->setFrameShape(QFrame::NoFrame);
    l->setAlignment(Qt::AlignCenter);
    l->setObjectName("panelWidgetLabel");
    p->layout()->addWidget(l);
    panelLayout->addWidget(p);
    //editPanelVerticalLayout->addWidget(l);
    if (hint != "")
    {
     panel->setToolTip(hint);
    }
//    comp->setMaximumSize(comp->sizeHint());  // override for  text fields
    panelLayout->addWidget(comp);
    panelLayout->setAlignment(Qt::AlignHCenter);
//    panel->layout()->addWidget(Box::createVerticalGlue());
    return panel;
}

/**
 * Create Variable and Action editing pane bottom part.
 * <p>
 * Called from {@link #makeEditVariableWindow(int)}
 *
 * @param updateListener listener for Update pressed
 * @param cancelListener listener for Cancel pressed
 * @param deleteListener listener for Delete pressed
 * @return JPanel containing Update etc. buttons
 */
QWidget* ConditionalListEdit::makeButtonPanel(QPushButton* updateAction,
                       QPushButton*  cancelAction,
                       QPushButton*  deleteAction)
{
    QWidget* panel3 = new QWidget();
    panel3->setLayout(new FlowLayout(panel3/*, BoxLayout.X_AXIS*/));
    //QPushButton updateAction = new QPushButton(tr("UpdateButton"));
    updateAction->setText(tr("Update"));
//    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(updateAction->sizePolicy().hasHeightForWidth());
//    updateAction->setSizePolicy(sizePolicy);
    panel3->layout()->addWidget(updateAction);
    //panel3->layout()->addWidget(Box.createHorizontalStrut(STRUT));
    //updateAction->layout()->addActionListener(updateListener);
    updateAction->setToolTip(tr("Press to keep changes and return to Edit Conditional"));

    //QPushButton cancelAction = new QPushButton(tr("CancelButton"));
    cancelAction->setText(tr("Cancel"));
    panel3->layout()->addWidget(cancelAction);
    //panel3->layout()->addWidget(Box.createHorizontalStrut(STRUT));
    //cancelAction->layout()->addActionListener(cancelListener);
    cancelAction->setToolTip(tr("Press to return to Edit Conditional without any changes"));

    //QPushButton deleteAction = new QPushButton(tr("DeleteButton"));
    deleteAction->setText(tr("Delete"));
    panel3->layout()->addWidget(deleteAction);
    //deleteAction->layout()->addActionListener(deleteListener);
    deleteAction->setToolTip(tr("Press to delete and return to Edit Conditional "));
    return panel3;
}

// ============ Edit Variable Window and Methods ============
/**
 * Create and/or initialize the Edit a Variable pane.
 * <p>
 * Note: you can get here via the New Variable button (addVariablePressed)
 * or via an Edit button in the Variable table of the EditConditional
 * window.
 *
 * @param row index of item to be edited in _variableList
 */
void ConditionalListEdit::makeEditVariableWindow(int row)
{
 if (alreadyEditingActionOrVariable())
 {
  return;
 }
 _curVariableRowNumber = row;
 _curVariable = _variableList->at(row);
 _editVariableFrame = new JmriJFrameX(tr("Edit Variable"), true, true);
 _editVariableFrame->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
 QWidget* topPanel = makeTopPanel(_editVariableFrame, tr("Antecedent Variable"), 500, 120);
 _editVariableFrame->setAcceptDrops(true);
 //QVBoxLayout* topPanelLayout = new QVBoxLayout(topPanel);

 //Box* panel1 = Box::createHorizontalBox();
 QWidget* panel1 = new QWidget();
 panel1->setLayout(new QHBoxLayout());
// panel1->layout()->addWidget(Box::createHorizontalGlue());
// panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

 // Item Type
 _variableItemBox = new QComboBox();
 _variableItemBox->setLayout(new QVBoxLayout());
 for (int i = 0; i <= Conditional::ITEM_TYPE_LAST_STATE_VAR; i++)
  _variableItemBox->addItem(ConditionalVariable::getItemTypeString(i));
 //JComboBoxUtil.setupComboBoxMaxRows(_variableItemBox);
 panel1->layout()->addWidget(makeEditPanel(_variableItemBox, tr("Variable Type"), tr("Select type of state variable for Conditional to test")));
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

 // Item Name
 _variableNameField = new JTextField(30);
 _variableNameField->setMinimumWidth(150);

 _variableNamePanel = makeEditPanel(_variableNameField, tr("System / User Name"), "");
// _variableNamePanel->setMaximumSize(
//              QSize(50, _variableNamePanel->sizeHint().height()));
 _variableNamePanel->setVisible(false);
//  QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//  sizePolicy.setVerticalStretch(0);
//  sizePolicy.setHorizontalStretch(1);
//  sizePolicy.setHeightForWidth(_variableNamePanel->sizePolicy().hasHeightForWidth());
//  _variableNamePanel->setSizePolicy(sizePolicy);
 panel1->layout()->addWidget(_variableNamePanel);
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

 // Arbitrary name combo box to facilitate the panel construction
 if (_selectionMode == SelectionMode::USECOMBO) {
     _comboNameBox = createNameBox(1);
     _variableComboNamePanel = makeEditPanel(_comboNameBox, "Item Name", "");  // NOI18N
     _variableComboNamePanel->setVisible(false);
     panel1->layout()->addWidget(_variableComboNamePanel);
     //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));
 }

 // Combo box section for selecting conditional reference
 //   First box selects the Logix, the second selects the conditional within the logix
 _selectLogixBox->addItem("XXXXXXXXXXXXXXXXXXXXX");  // NOI18N
 _selectConditionalBox->addItem("XXXXXXXXXXXXXXXXXXXXX");  // NOI18N
 _selectLogixPanel = makeEditPanel(_selectLogixBox, tr("Select Logix"), "");  // NOI18N
 _selectConditionalPanel = makeEditPanel(_selectConditionalBox, "SelectConditional", "");  // NOI18N
 _selectLogixPanel->setVisible(false);
 _selectConditionalPanel->setVisible(false);
 panel1->layout()->addWidget(_selectLogixPanel);
 panel1->layout()->addWidget(_selectConditionalPanel);
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

 // State Box
 _variableStateBox = new QComboBox();
 _variableStateBox->addItem("XXXXXXX");
 _variableStatePanel = makeEditPanel(_variableStateBox, tr("Variable State"), tr("Select the state of the variable to test"));
 _variableStatePanel->setVisible(false);
 panel1->layout()->addWidget(_variableStatePanel);
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

 // Aspects
 _variableSignalBox = new QComboBox();
 _variableSignalBox->addItem("XXXXXXXXX");
 _variableSignalPanel = makeEditPanel(_variableSignalBox, tr("Variable Aspect"), tr("Select the Aspect of the Signal to test"));
 _variableSignalPanel->setVisible(false);
 panel1->layout()->addWidget(_variableSignalPanel);
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

// Compare operator
 _variableComparePanel = new QWidget();
 _variableComparePanel->setLayout(new QHBoxLayout(_variableComparePanel/*, BoxLayout.X_AXIS*/));
 _variableCompareOpBox = new QComboBox();
 for (int i = 1; i <= ConditionalVariable::NUM_COMPARE_OPERATIONS; i++)
 {
  _variableCompareOpBox->addItem(ConditionalVariable::getCompareOperationString(i));
 }
 _variableComparePanel->layout()->addWidget(makeEditPanel(_variableCompareOpBox, tr("Comparison Operator"), tr("Select an operator to compare memory values")));
 //_variableComparePanel->layout()->addWidget(Box::createHorizontalStrut(STRUT));

// Compare type
_variableCompareTypeBox = new QComboBox();
 for (int i = 0; i < Conditional::ITEM_TO_MEMORY_TEST.length(); i++)
 {
     _variableCompareTypeBox->addItem(ConditionalVariable::getStateString(Conditional::ITEM_TO_MEMORY_TEST.at(i)));
 }
 _variableComparePanel->layout()->addWidget(makeEditPanel(_variableCompareTypeBox, tr("Compare as"), tr("Select either a literal value or the value in a memory location")));
 _variableComparePanel->setVisible(false);
//    _variableCompareTypeBox->layout()->addWidgetItemListener(new ItemListener() {
//        /*public*/ void itemStateChanged(ItemEvent e) {
//            compareTypeChanged(_variableCompareTypeBox->currentIndex());
//            _editVariableFrame.pack();
//        }
//    });
 connect(_variableCompareTypeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(itemStateChanged(int)));
 panel1->layout()->addWidget(_variableComparePanel);
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

// Data 1
 _variableData1Field = new JTextField(30);
 _variableData1Panel = makeEditPanel(_variableData1Field, tr("Start Time"), tr("Enter time (hh:mm) for a 24-hour clock"));
 _variableData1Panel->setMaximumSize(
              QSize(45, _variableData1Panel->size().height()));
 _variableData1Panel->setVisible(false);
 panel1->layout()->addWidget(_variableData1Panel);
 //panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));

// Data 2
 _variableData2Field = new JTextField(30);
 _variableData2Panel = makeEditPanel(_variableData2Field, tr("End Time"), tr("Enter time (hh:mm) for a 24-hour clock"));
 _variableData2Panel->setMaximumSize(
             QSize(45, _variableData2Panel->size().height()));
 _variableData2Panel->setVisible(false);
 panel1->layout()->addWidget(_variableData2Panel);
// panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));
// panel1->layout()->addWidget(Box::createHorizontalGlue());
 topPanel->layout()->addWidget(panel1);

// ActionListener updateListener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updateVariablePressed();
//            }
//        };
 QPushButton* updateListener = new QPushButton();
 connect(updateListener, SIGNAL(clicked()), this, SLOT(updateVariablePressed()));
//   ActionListener cancelListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               cancelEditVariablePressed();
//           }cancelListener
//       };
 QPushButton* cancelListener = new QPushButton();
 connect(cancelListener, SIGNAL(clicked()), this, SLOT(cancelEditVariablePressed()));

//   ActionListener deleteListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               deleteVariablePressed();
//           }
//       };
 QPushButton* deleteListener = new QPushButton();
 connect(deleteListener, SIGNAL(clicked()), this, SLOT(deleteVariablePressed()));

 QWidget* panel = makeButtonPanel(updateListener, cancelListener, deleteListener);
 topPanel->layout()->addWidget(panel);
 //topPanel->layout()->addWidget(Box::createVerticalGlue());

 if(_editVariableFrame->centralWidget()== NULL)
 {
     QWidget* centralWidget = new QWidget();
     centralWidget->setLayout(new QVBoxLayout);
     _editVariableFrame->setCentralWidget(centralWidget);
 }
 QWidget* contentPane = _editVariableFrame->getContentPane();
 contentPane->layout()->addWidget(topPanel);
 // note - this listener cannot be added before other action items
 // have been created
//  _variableItemBox->addItemListener(new ItemListener() {
//       /*public*/ void itemStateChanged(ItemEvent e) {
//            variableTypeChanged( _variableItemBox->currentIndex());
//            _editVariableFrame.pack();
//        }
//    });
 connect(_variableItemBox, SIGNAL(currentIndexChanged(int)), this, SLOT(variableItemStateChanged(int)));
    // setup window closing listener
//    _editVariableFrame->addWindowListener(
//        new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    cancelEditVariablePressed();
//                }
//            });
 _editVariableFrame->addWindowListener(editVariableFrameWindowListener = new EditVariableFrameWindowListener(this));
 initializeStateVariables();
 _editVariableFrame->setMinimumSize(300,400);
 _editVariableFrame->adjustSize();
 _editVariableFrame->setVisible(true);
}

void ConditionalListEdit::variableItemStateChanged(int)
{
 int newVariableItem = _variableItemBox->currentIndex();
 if (log->isDebugEnabled())
 {
  log->debug(tr("_variableItemBox Listener: new = %1, curr = %2, row = %3").arg(  // NOI18N
  newVariableItem).arg(_curVariableItem).arg(_curVariableRowNumber));
 }
 if (newVariableItem != _curVariableItem)
 {
  if (_curVariableRowNumber >= 0)
  {
      _curVariable = new ConditionalVariable();
      if (_curVariableRowNumber > 0) {
          if (_logicType == Conditional::ALL_OR) {
              _curVariable->setOpern(Conditional::Operator::OR);
          } else {
              _curVariable->setOpern(Conditional::Operator::AND);
          }
      }
      _variableList->replace(_curVariableRowNumber, _curVariable);
  }
  _curVariableItem = newVariableItem;
 }
 variableItemChanged(newVariableItem);
 _editVariableFrame->pack();


 // setup window closing listener
 //_editVariableFrame.addWindowListener(
 //        new java.awt.event.WindowAdapter() {
 //    @Override
 //    public void windowClosing(java.awt.event.WindowEvent e) {
 //        cancelEditVariablePressed();
 //    }
 // });
 _editVariableFrame->addWindowListener(new EditVariableFrameWindowListener(this));
 _curVariableItem = Conditional::TEST_TO_ITEM[_curVariable->getType()];
 initializeStateVariables();
 _editVariableFrame->pack();
 _editVariableFrame->setVisible(true);
}

void ConditionalListEdit::itemStateChanged(int )
{
 compareTypeChanged(_variableCompareTypeBox->currentIndex());
 _editVariableFrame->pack();
}

/**
 * Creates and/or initializes the Edit a Variable window Note: you can get
 * here via the New Variable button (addVariablePressed) or via an
 * Edit button in the Variable table of the EditConditional window.
 */

EditVariableFrameWindowListener::EditVariableFrameWindowListener(ConditionalListEdit *self)
{
 this->self = self;
}

void EditVariableFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 self->cancelEditVariablePressed();
}

// ------------ Main Variable methods ------------
/**
 * Set display to show current state variable (_curVariable) parameters.
 */
/**
* set display to show current state variable (curVariable) parameters
*/
void ConditionalListEdit::initializeStateVariables()
{
 int testType = (_curVariable)->getType();
 if (log->isDebugEnabled()) log->debug("initializeStateVariables: testType= "+QString::number(testType));
 if (testType==Conditional::TYPE_NONE)
 {
  return;
 }
 int itemType = Conditional::TEST_TO_ITEM.at(testType);
 if (log->isDebugEnabled()) log->debug("initializeStateVariables: itemType= "+QString::number(itemType)+", testType= "+QString::number(testType));
 // set type after call to variableTypeChanged - addItemListener action will call variableTypeChanged
  _variableItemBox->setCurrentIndex(itemType);
 //variableTypeChanged(itemType);
 switch (itemType)
 {
  case Conditional::ITEM_TYPE_SENSOR:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_SENSOR_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
  case Conditional::ITEM_TYPE_TURNOUT:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_TURNOUT_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
 case Conditional::ITEM_TYPE_LIGHT:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_LIGHT_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
  break;
 case Conditional::ITEM_TYPE_SIGNALHEAD:
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                   Conditional::ITEM_TO_SIGNAL_HEAD_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   if ((Conditional::TYPE_SIGNAL_HEAD_RED<=testType && testType<=Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN)
            || Conditional::TYPE_SIGNAL_HEAD_LUNAR==testType
            || Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR==testType)
   {
    _variableStateBox->setCurrentIndex(_variableStateBox->findText( // index 1 = TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS
                                                                        ConditionalVariable::getStateString(Conditional::ITEM_TO_SIGNAL_HEAD_TEST.at(1))));
        loadJComboBoxWithSignalAspects(_variableSignalBox, _curVariable->getName());
        _variableSignalBox->setCurrentIndex(_variableSignalBox->findText(
                    ConditionalVariable::getStateString(_curVariable->getType())));
        _variableSignalPanel->setVisible(true);
   }
   break;
  case Conditional::ITEM_TYPE_SIGNALMAST:
   // set display to show current state variable (curVariable) parameters
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_SIGNAL_MAST_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   if (testType==Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS)
   {
    loadJComboBoxWithMastAspects(_variableSignalBox, _curVariable->getName());
    _variableSignalBox->setCurrentIndex(_variableSignalBox->findText(_curVariable->getDataString()));
    _variableSignalPanel->setVisible(true);
   }
   break;
  case Conditional::ITEM_TYPE_MEMORY:
  {
   _variableCompareTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_MEMORY_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   int num1 = _curVariable->getNum1()-1;
   if (num1==-1)
   {  // former code was only equals
    num1 = ConditionalVariable::EQUAL-1;
   }
   _variableCompareOpBox->setCurrentIndex(num1);
   _variableData1Field->setText(_curVariable->getDataString());
   break;
  }
  case Conditional::ITEM_TYPE_CONDITIONAL:
  {
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_CONDITIONAL_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
  }
  case Conditional::ITEM_TYPE_WARRANT:
  {
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_WARRANT_TEST, testType));
   _variableNameField->setText(_curVariable->getName());
   break;
  }
  case Conditional::ITEM_TYPE_CLOCK:
  {
   int time = _curVariable->getNum1();
   _variableData1Field->setText(formatTime(time / 60, time - ((time / 60) * 60)));
   time = _curVariable->getNum2();
   _variableData2Field->setText(formatTime(time / 60, time - ((time / 60) * 60)));
   _variableNameField->setText("");
   break;
  }

  case Conditional::ITEM_TYPE_OBLOCK:
  {
   _variableNameField->setText(_curVariable->getName());
   _variableStateBox->clear();
   QStringListIterator names = OBlock::getLocalStatusNames();
   while (names.hasNext())
   {
    _variableStateBox->addItem(names.next());
   }
   _variableStateBox->setCurrentIndex(_variableStateBox->findText(OBlock::getLocalStatusName(_curVariable->getDataString())));
   _variableStateBox->setVisible(true);
   break;
  }

  case Conditional::ITEM_TYPE_ENTRYEXIT:
  {
   _variableNameField->setText(_curVariable->getBean()->getUserName());
   _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                    Conditional::ITEM_TO_ENTRYEXIT_TEST, testType));
   _variableStateBox->setVisible(true);
   break;
  }

  default : break;
 }
 _editVariableFrame->adjustSize();
 //_editVariableFrame->transferFocusBackward();
}       /* initializeStateVariables */


/**
 * Respond to change in variable item chosen in the State Variable Table in
 * the Edit Conditional pane.
 * <p>
 * Also used to set up for Edit of a Conditional with state variables.
 *
 * @param itemType value representing the newly selected Conditional type,
 *                 i.e. ITEM_TYPE_SENSOR
 */
/*private*/ void ConditionalListEdit::variableItemChanged(int itemType) {
    int testType = _curVariable->getType();
    if (log->isDebugEnabled()) {
        log->debug(tr("variableItemChanged: itemType = %1, testType = %2").arg(itemType).arg(testType));  // NOI18N
    }
    _variableNamePanel->setVisible(false);
    _variableStatePanel->setVisible(false);
    _variableComparePanel->setVisible(false);
    _variableSignalPanel->setVisible(false);
    _variableData1Panel->setVisible(false);
    _variableData2Panel->setVisible(false);
    _selectLogixPanel->setVisible(false);
    _selectConditionalPanel->setVisible(false);
    _variableStateBox->clear();
//    _variableNameField->removeActionListener(variableSignalHeadNameListener);
//    _variableNameField->removeActionListener(variableSignalMastNameListener);
//    _variableStateBox->removeActionListener(variableSignalTestStateListener);
//    _selectLogixBox->removeActionListener(selectLogixBoxListener);
    disconnect(_selectLogixBox, SIGNAL(currentIndexChanged(int)), selectLogixBoxListener, SLOT());
//    _selectConditionalBox->removeActionListener(selectConditionalBoxListener);
    disconnect(_selectLogixBox, SIGNAL(currentIndexChanged(int)), selectConditionalBoxListener, SLOT());

    if (_selectionMode == SelectionMode::USECOMBO) {
        _variableComboNamePanel->setVisible(false);
    } else if (_selectionMode == SelectionMode::USESINGLE) {
        createSinglePanelPickList(itemType, new PickSingleListener(_variableNameField, itemType, this), false);
    } else {
        // Default and USEMULTINameHintSensor
        setPickListTab(itemType, false);
    }

    switch (itemType) {
        case Conditional::TYPE_NONE:
            return;
        case Conditional::ITEM_TYPE_SENSOR:
            _variableNamePanel->setToolTip(tr("NameHintSensor"));  // NOI18N
            for (int i = 0; i < Conditional::ITEM_TO_SENSOR_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_SENSOR_TEST[i]));
            }
            _variableStatePanel->setVisible(true);
            _variableNamePanel->setVisible(true);
            setVariableNameBox(itemType);
            break;

        case Conditional::ITEM_TYPE_TURNOUT:
            _variableNamePanel->setToolTip(tr("NameHintTurnout"));  // NOI18N
            for (int i = 0; i < Conditional::ITEM_TO_LIGHT_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_TURNOUT_TEST[i]));
            }
            _variableNamePanel->setVisible(true);
            _variableStatePanel->setVisible(true);
            setVariableNameBox(itemType);
            break;

        case Conditional::ITEM_TYPE_LIGHT:
            _variableNamePanel->setToolTip(tr("NameHintLight"));  // NOI18N
            for (int i = 0; i < Conditional::ITEM_TO_LIGHT_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_LIGHT_TEST[i]));
            }
            _variableStatePanel->setVisible(true);
            _variableNamePanel->setVisible(true);
            setVariableNameBox(itemType);
            break;

        case Conditional::ITEM_TYPE_SIGNALHEAD:
            //_variableNameField->addActionListener(variableSignalHeadNameListener);
     connect(_variableNameField, SIGNAL(editingFinished()), this, SLOT(variableSignalHeadNameListener()));
            //_variableStateBox->addActionListener(variableSignalTestStateListener);
     connect(_variableStateBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(variableSignalTestStateListener()));
            loadJComboBoxWithHeadAppearances(_variableSignalBox, _variableNameField->text().trimmed());

            for (int i = 0; i < Conditional::ITEM_TO_SIGNAL_HEAD_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_SIGNAL_HEAD_TEST[i]));
            }
            _variableNamePanel->setToolTip(tr("NameHintSignal"));  // NOI18N
            _variableNamePanel->setVisible(true);
            _variableStatePanel->setVisible(true);
            if (testType == Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS) {
                _variableSignalPanel->setVisible(true);
            } else {
                _variableSignalPanel->setVisible(false);
            }
            setVariableNameBox(itemType);
            break;

        case Conditional::ITEM_TYPE_SIGNALMAST:
            //_variableNameField->addActionListener(variableSignalMastNameListener);
     connect(_variableNameField, SIGNAL(editingFinished()), this, SLOT(variableSignalMastNameListener()) );
            //_variableStateBox->addActionListener(variableSignalTestStateListener);
     connect(_variableStateBox, SIGNAL(currentTextChanged(QString)), this, SLOT(variableSignalTestStateListener()));
            loadJComboBoxWithMastAspects(_variableSignalBox, _variableNameField->text().trimmed());

            for (int i = 0; i < Conditional::ITEM_TO_SIGNAL_MAST_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_SIGNAL_MAST_TEST[i]));
            }
            _variableNamePanel->setToolTip(tr("NameHintSignalMast"));  // NOI18N
            _variableNamePanel->setVisible(true);
            _variableStatePanel->setVisible(true);
            if (testType == Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS) {
                _variableSignalPanel->setVisible(true);
            } else {
                _variableSignalPanel->setVisible(false);
            }
            setVariableNameBox(itemType);
            break;
#if 1
        case Conditional::ITEM_TYPE_MEMORY:
    {
//            QWidget* p = (QWidget*) _variableData1Panel->children().at(0);
//            QWidget* l = (QWidget*) p->children().at(0);
            QWidget* p = _variableData1Panel->findChildren<QWidget*>().at(0);
            QLabel* l = p->findChildren<QLabel*>().at(0);
            if ((testType == Conditional::TYPE_MEMORY_COMPARE)
                    || (testType == Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE)) {
                l->setText(tr("LabelMemoryValue"));  // NOI18N
                _variableData1Panel->setToolTip(tr("Enter Memory name whose value is compared"));  // NOI18N
            } else {
                l->setText(tr("LabelLiteralValue"));  // NOI18N
                _variableData1Panel->setToolTip(tr("Enter Value to be compared"));  // NOI18N
            }
            _variableNamePanel->setToolTip(tr("Enter Name (system or user) of Memory"));  // NOI18N
            _variableNamePanel->setVisible(true);
            _variableData1Panel->setToolTip(tr("Enter Memory name whose value is compared"));  // NOI18N
            _variableData1Panel->setVisible(true);
            _variableComparePanel->setVisible(true);
            setVariableNameBox(itemType);
    }
            break;

        case Conditional::ITEM_TYPE_CONDITIONAL:
            _variableNamePanel->setToolTip(tr("Enter System Name for Conditional (or User Name if in this Logix)"));  // NOI18N
            //_selectLogixBox.addActionListener(selectLogixBoxListener);
            connect(_selectLogixBox, SIGNAL(currentIndexChanged(int)), selectLogixBoxListener, SLOT());
            //_selectConditionalBox.addActionListener(selectConditionalBoxListener);
            connect(_selectConditionalBox, SIGNAL(currentIndexChanged(int)), selectConditionalBoxListener, SLOT());
            for (int i = 0; i < Conditional::ITEM_TO_CONDITIONAL_TEST.length(); i++)
            {
             _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_CONDITIONAL_TEST[i]));
            }
            // Load the Logix and Conditional combo boxes
            loadSelectLogixBox();
            _selectLogixPanel->resize(_selectLogixBox->sizeHint());
            _selectConditionalPanel->resize(_selectConditionalBox->sizeHint());
            _selectLogixPanel->setVisible(true);
            _selectConditionalPanel->setVisible(true);
            _variableStatePanel->setVisible(true);
            break;

        case Conditional::ITEM_TYPE_WARRANT:
            _variableNamePanel->setToolTip(tr("Enter Name (system or user) of Warrant"));  // NOI18N
            for (int i = 0; i < Conditional::ITEM_TO_WARRANT_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_WARRANT_TEST[i]));
            }
            _variableNamePanel->setVisible(true);
            _variableStatePanel->setVisible(true);
            setVariableNameBox(itemType);
            break;

        case Conditional::ITEM_TYPE_CLOCK:
    {
//            p = (JPanel) _variableData1Panel.getComponent(0);
//            l = (JLabel) p.getComponent(0);
     QWidget* p = _variableData1Panel->findChildren<QWidget*>().at(0);
     QLabel* l = p->findChildren<QLabel*>().at(0);
            l->setText(tr("Start Time"));  // NOI18N
            _variableData1Panel->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));  // NOI18N
            _variableData1Panel->setVisible(true);
            _variableData2Panel->setVisible(true);
    }
            break;

        case Conditional::ITEM_TYPE_OBLOCK:
    {
            _variableNamePanel->setToolTip(tr("Enter Name (system or user) of OBlock"));  // NOI18N
            _variableNamePanel->setVisible(true);
            _variableStateBox->clear();
            QStringListIterator names = OBlock::getLocalStatusNames();
            while (names.hasNext()) {
                _variableStateBox->addItem(names.next());
            }
            _variableStatePanel->setVisible(true);
            setVariableNameBox(itemType);
    }
            break;

        case Conditional::ITEM_TYPE_ENTRYEXIT:
            _variableNamePanel->setToolTip(tr("Enter Name of Entry/Exit Pair"));  // NOI18N
            _variableNameField->setText(_curVariable->getName());
            for (int i = 0; i < Conditional::ITEM_TO_ENTRYEXIT_TEST.length(); i++) {
                _variableStateBox->addItem(
                        ConditionalVariable::describeState(Conditional::ITEM_TO_ENTRYEXIT_TEST[i]));
            }
            _variableStatePanel->setVisible(true);
            _variableNamePanel->setVisible(true);
            setVariableNameBox(itemType);
            break;
#endif
        default:
            break;
    }
    _variableStateBox->setMaximumSize(_variableStateBox->sizeHint());
}

/**
 * Update the name combo box selection based on the current contents of the
 * name field. Called by variableItemChanged
 *
 * @since 4.7.3
 * @param itemType The type of name box to be created.
 */
void ConditionalListEdit::setVariableNameBox(int itemType) {
    if (_selectionMode != SelectionMode::USECOMBO) {
        return;
    }
    _comboNameBox = createNameBox(itemType);
    if (_comboNameBox == NULL) {
        return;
    }
    //_comboNameBox.addActionListener(new NameBoxListener(_variableNameField));
    NameBoxListener* nameBoxListener = new NameBoxListener(_variableNameField, this);
    connect(_comboNameBox, SIGNAL(currentIndexChanged(int)), nameBoxListener, SLOT(actionPerformed()));
    _comboNameBox->setSelectedBeanByName(_curVariable->getName());
    //_variableComboNamePanel->remove(1);
    QObjectList children = _variableComboNamePanel->children();
    _variableComboNamePanel->layout()->removeWidget((QWidget*)children.at(1)); //???
    _variableComboNamePanel->layout()->addWidget(_comboNameBox); //, NULL, 1);
    _variableNamePanel->setVisible(false);
    _variableComboNamePanel->setVisible(true);
}

// ------------ Variable detail methods ------------
/*
* Responds to Update action button in the Edit Action window
*/
void ConditionalListEdit::updateVariablePressed() {
    if (!validateVariable() ) {
//        _editVariableFrame->toFront();
        return;
    }
    _variableTableModel->fireTableRowsUpdated(_curVariableRowNumber, _curVariableRowNumber);
    cleanUpVariable();
    if (_editConditionalFrame!=NULL) {
        _editConditionalFrame->setVisible(true);
    }
}


/*
* Responds to Cancel action button and window closer of the
* Edit Action window.  Also does cleanup of Update and Delete
* buttons.
*/
void ConditionalListEdit::cancelEditActionPressed() {
    if (_newItem) {
        deleteActionPressed(_curActionRowNumber);
    } else {
        cleanUpAction();
    }
    if (_editConditionalFrame!=NULL) {
        _editConditionalFrame->setVisible(true);
    }
}

/**
 * Clean up Update and Delete Variable buttons.
 */
void ConditionalListEdit::cleanUpVariable()
{
 _newItem = false;
 if (_editVariableFrame != NULL)
 {
  _editVariableFrame->setVisible(false);
  _editVariableFrame->dispose();
  _editVariableFrame = NULL;
 }
 _curVariableRowNumber = -1;
}

/*
* Responds to Delete action button in the Edit Variable window
*/
void ConditionalListEdit::deleteVariablePressed() {
    deleteVariablePressed(_curVariableRowNumber);
}

/**
 * Responds to the Delete Button in the State Variable Table of the Edit
 * Conditional window
 */
void ConditionalListEdit::deleteVariablePressed(int row)
{
 if (row != _curVariableRowNumber && alreadyEditingActionOrVariable())
 {
  return;
 }
    if (_variableList->size() < 1 && !_suppressReminder) {
        // warning message - last State Variable deleted
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("Warn3"), tr("WarnTitle"),
//                javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_editConditionalFrame, tr("Warning"), tr("A Conditional must have at least one State Variable to do anything useful."));
    }
    // move remaining state variables if needed
    _variableList->removeAt(row);
    _variableTableModel->fireTableRowsDeleted(row, row);
    makeAntecedent();
    cleanUpVariable();
    if (_editConditionalFrame!=NULL) {
        _editConditionalFrame->setVisible(true);
    }
    _showReminder = true;
}


/**
 * Check if Memory type in a Conditional was changed by the user.
 * <p>
 * Update GUI if it has. Called from {@link #makeEditVariableWindow(int)}
 *
 * @param selection index of the currently selected type in the
 *                  _variableCompareTypeBox
 */
/*private*/ void ConditionalListEdit::compareTypeChanged(int selection)
{
 QObjectList ol = _variableData1Panel->children();
 QWidget* p = (QWidget*)ol.at(1);
 QLabel* l = (QLabel*)p->children().at(1);
 int testType = Conditional::ITEM_TO_MEMORY_TEST.at(selection);
 if ((testType==Conditional::TYPE_MEMORY_COMPARE) ||
                (testType==Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE))
 {
  l->setText(tr("Memory Value"));
  _variableData1Panel->setToolTip(tr("Enter Memory whose value is compared"));
 }
 else
 {
  l->setText(tr("Literal Value"));
  _variableData1Panel->setToolTip(tr("Enter Memory whose value is compared"));
 }
}

/**
 * Load the Logix selection box. Set the selection to the current Logix
 *
 * @since 4.7.4
 */
void ConditionalListEdit::loadSelectLogixBox() {
    // Get the current Logix name for selecting the current combo box row
    QString cdlName = _curVariable->getName();
    QString lgxName;
    if (cdlName.length() == 0 || (_curVariable->getType() != Conditional::TYPE_CONDITIONAL_TRUE
            && _curVariable->getType() != Conditional::TYPE_CONDITIONAL_FALSE)) {
        // Use the current logix name for "add" state variable
        lgxName = _curLogix->getSystemName();
    } else {
        Logix* x = _conditionalManager->getParentLogix(cdlName);
        if (x == NULL) {
            log->error(tr("Unable to find the Logix for %1, using the current Logix").arg(cdlName));  // NOI18N
            lgxName = _curLogix->getSystemName();
        } else {
            lgxName = x->getSystemName();
        }
    }

    _selectLogixBox->clear();
    _selectLogixList.clear();

    QString itemKey = "";
    for (QString xName : _logixManager->getSystemNameList()) {
        if (xName == ("SYS")) {  // NOI18N
            // Cannot refer to sensor name groups
            continue;
        }
        Logix* x = _logixManager->getLogix(xName);
        QString uName = x->getUserName();
        QString itemName = "";
        if (uName == NULL || uName.length() < 1) {
            itemName = xName;
        } else {
            itemName = uName + " ( " + xName + " )";
        }
        _selectLogixBox->addItem(itemName);
        _selectLogixList.append(xName);
        if (lgxName == (xName)) {
            itemKey = itemName;
        }
    }
    _selectLogixBox->setCurrentText(itemKey);
//    JComboBoxUtil::setupComboBoxMaxRows(_selectLogixBox);
    loadSelectConditionalBox(lgxName);
}

/**
 * Load the Conditional selection box. The first row is a prompt
 *
 * @since 4.7.4
 * @param logixName The Logix system name for selecting the owned
 *                  Conditionals
 */
void ConditionalListEdit::loadSelectConditionalBox(QString logixName) {
    // Get the current Conditional name for selecting the current combo box row
    QString cdlName = _curVariable->getName();

    _selectConditionalBox->clear();
    _selectConditionalList.clear();

    // Create the first row
    QString itemKey = tr("SelectFirstRow");  // NOI18N
    _selectConditionalBox->addItem(itemKey);
    _selectConditionalList.append("-None-");  // NOI18N

    Logix* x = (Logix*)_logixManager->getBySystemName(logixName);
    if (x == NULL) {
        log->error(tr("Logix '%1' not found while building the conditional list").arg( logixName));  // NOI18N
        return;
    }
    if (x->getNumConditionals() == 0) {
        return;
    }
    for (QString cName : _conditionalManager->getSystemNameListForLogix(x)) {
        Conditional* c = _conditionalManager->getConditional(cName);
        if (_curConditional->getSystemName() == (c->getSystemName())) {
            // Don't add myself to the list
            continue;
        }
        QString uName = c->getUserName();
        QString itemName = "";
        if (uName == NULL || uName.length() < 1) {
            itemName = cName;
        } else {
            itemName = uName + " ( " + cName + " )";
        }
        _selectConditionalBox->addItem(itemName);
        _selectConditionalList.append(cName);
        if (cdlName == (cName)) {
            itemKey = itemName;
        }
    }
    _selectConditionalBox->setCurrentText(itemKey);
//    JComboBoxUtil->setupComboBoxMaxRows(_selectConditionalBox);
}

// ------------ Variable update processes ------------
/**
 * Validate Variable data from Edit Variable Window, and transfer it to
 * current action object as appropriate.
 * <p>
 * Messages are sent to the user for any errors found. This routine returns
 * false immediately after finding the first error, even if there might be
 * more errors.
 *
 * @return true if all data checks out OK, otherwise false
 */
bool ConditionalListEdit::validateVariable() {
    QString name = _variableNameField->text().trimmed();
    _variableNameField->setText(name);
    _curVariable->setDataString("");
    _curVariable->setNum1(0);
    _curVariable->setNum2(0);
    int itemType =  _variableItemBox->currentIndex();
    int testType = 0;
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:
            testType = Conditional::ITEM_TO_SENSOR_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            testType = Conditional::ITEM_TO_TURNOUT_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            testType = Conditional::ITEM_TO_LIGHT_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            testType = Conditional::ITEM_TO_SIGNAL_HEAD_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:
            testType = Conditional::ITEM_TO_SIGNAL_MAST_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_MEMORY:
            testType = Conditional::ITEM_TO_MEMORY_TEST[_variableCompareTypeBox->currentIndex()];
            break;
        case Conditional::ITEM_TYPE_CONDITIONAL:
            testType = Conditional::ITEM_TO_CONDITIONAL_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_WARRANT:
            testType = Conditional::ITEM_TO_WARRANT_TEST.at(_variableStateBox->currentIndex());
            break;
        case Conditional::ITEM_TYPE_CLOCK:
            testType =Conditional::TYPE_FAST_CLOCK_RANGE;
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            testType =Conditional::TYPE_BLOCK_STATUS_EQUALS;
            break;
        case Conditional::ITEM_TYPE_ENTRYEXIT:
            testType = Conditional::ITEM_TO_ENTRYEXIT_TEST.at(_variableStateBox->currentIndex());
            break;
        default:
//            javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                    tr("ErrorVariableType"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Select a Variable Type or Cancel."));
            return false;
    }
    _curVariable->setType(testType);
    if (log->isDebugEnabled()) log->debug("validateVariable: itemType= "+QString::number(itemType)+", testType= "+QString::number(testType));
    switch ( itemType ) {
        case Conditional::ITEM_TYPE_SENSOR:
            name = validateSensorReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            name = validateTurnoutReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_CONDITIONAL:
            name = validateConditionalReference(name);
            if (name == NULL) {
                return false;
            }
            _curVariable->setName(name);
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            name = validateLightReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_MEMORY:
    {
            name = validateMemoryReference(name);
            if (name == NULL) {
                return false;
            }
            QString name2 = _variableData1Field->text();
            if ((testType==Conditional::TYPE_MEMORY_COMPARE) ||
                    (testType==Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE)) {
                name2 = validateMemoryReference(name2);
                if (name2 == NULL) {
                    return false;
                }
            }
            _curVariable->setDataString(name2);
            _curVariable->setNum1(_variableCompareOpBox->currentIndex() + 1);
            break;
    }
        case Conditional::ITEM_TYPE_CLOCK:
    {
            int beginTime = parseTime(_variableData1Field->text());
            if (beginTime < 0) {
                // parse error occurred - message has been sent
                return (false);
            }
            int endTime = parseTime(_variableData2Field->text());
            if (endTime < 0) {
                return (false);
            }
            // set beginning and end time (minutes since midnight)
            _curVariable->setNum1(beginTime);
            _curVariable->setNum2(endTime);
            name = "Clock";
            break;
    }
        case Conditional::ITEM_TYPE_SIGNALHEAD:
    {
            name = validateSignalHeadReference(name);
            if (name == NULL) {
                return false;
            }
            if (testType==Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS) {
                QString appStr = _variableSignalBox->currentText();
                int type = ConditionalVariable::stringToVariableTest(appStr);
                if (type<0) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            tr("ErrorAppearance"), tr("ErrorTitle"),
//                            javax.swing.JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Select an appearance.  You must hit the Enter/Return key\nafter entering a name with the cursor in the name field."));
                    return false;
                }
                _curVariable->setType(type);
                _curVariable->setDataString(appStr);
                if (log->isDebugEnabled()) log->debug("SignalHead \""+name+"\"of type '"+testType+
                                                    "' _variableSignalBox->currentText()= "+
                                                    _variableSignalBox->currentText());
            }
            break;
    }
        case Conditional::ITEM_TYPE_SIGNALMAST:
    {
            name = validateSignalMastReference(name);
            if (name == NULL) {
                return false;
            }
            if (testType==Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS) {
                if (_variableSignalBox->currentIndex()<0) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            tr("ErrorAspect"), tr("ErrorTitle"),
//                            javax.swing.JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Select an aspect.  You may need to hit the Enter/Return key\nwith the cursor in the name field."));
                    return false;
                }
                // save the selected aspect for comparison
                _curVariable->setDataString(_variableSignalBox->currentText());
//                _curVariable->setType(ConditionalVariable::stringToVariableTest(appStr));
            }
            break;
    }

        case Conditional::ITEM_TYPE_WARRANT:
            name = validateWarrantReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
    {
            name = validateOBlockReference(name);
            if (name == NULL) {
                return false;
            }
            QString str = _variableStateBox->currentText();
            _curVariable->setDataString(OBlock::getSystemStatusName(str));
            if (log->isDebugEnabled()) log->debug("OBlock \""+name+"\"of type '"+testType+
                                                "' _variableStateBox->currentText()= "+
                                                _variableStateBox->currentText());
            break;
    }
        case Conditional::ITEM_TYPE_ENTRYEXIT:
            name = validateEntryExitReference(name);
            if (name == NULL) {
                return false;
            }
            break;
        default:
//            javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                    tr("ErrorVariableType"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Select a Variable Type or Cancel."));
            return false;
    }
    _curVariable->setName(name);
    bool result = _curVariable->evaluate();
    if (log->isDebugEnabled()) log->debug("State Variable \""+name+"\"of type '"+
                                        ConditionalVariable::getTestTypeString(testType)+
                                          "' state= "+ (result?"true":"false")+" type= "+QString::number(_curVariable->getType()));
    if (_curVariable->getType()==Conditional::TYPE_NONE) {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("ErrorVariableState"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Select a state for this variable."));

        return false;
    }
    return (true);
}   /* validateVariable */


// ------------ Variable detail listeners ------------
/*public*/ void ConditionalListEdit::variableSignalTestStateListener(JActionEvent* /*e*/) {
    log->debug("variableSignalTestStateListener fires;  _variableItemBox->currentIndex()= "+
              QString::number( _variableItemBox->currentIndex())+
              "\" _variableStateBox->currentIndex()= \""+QString::number(_variableStateBox->currentIndex())+"\"");

    int itemType =  _variableItemBox->currentIndex();
    if (itemType==Conditional::ITEM_TYPE_SIGNALHEAD || itemType==Conditional::ITEM_TYPE_SIGNALMAST) {
        // index 1 is Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS or Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS
        if (_variableStateBox->currentIndex()==1) {
            loadJComboBoxWithMastAspects(_variableSignalBox,_variableNameField->text().trimmed());
            _variableSignalPanel->setVisible(true);
        } else {
            _variableSignalPanel->setVisible(false);
        }
    } else {
        _variableSignalPanel->setVisible(false);
    }
    _variableSignalBox->setMaximumSize(_variableSignalBox->size());
    if (_editVariableFrame!=NULL)
    {
        _editVariableFrame->adjustSize();
    }
}

/*public*/ void ConditionalListEdit::variableSignalHeadNameListener(JActionEvent* /*e*/) {
        // fired when signal mast name changes, but only
        // while in signal mast mode
        log->debug("variableSignalHeadNameListener fires; _variableNameField : "+_variableNameField->text().trimmed());
        loadJComboBoxWithSignalAspects(_variableSignalBox,_variableNameField->text().trimmed());
    }
//transient ActionListener variableSignalMastNameListener = new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
void ConditionalListEdit::variableSignalMastNameListener() // SLOT[]
{
 // fired when signal mast name changes, but only
 // while in signal mast mode
 log->debug("variableSignalMastNameListener fires; _variableNameField : "+_variableNameField->text().trimmed());
 loadJComboBoxWithMastAspects(_variableSignalBox,_variableNameField->text().trimmed());
}
#if 1
//};
///*transient*/ CLESelectLogixBoxListener* selectLogixBoxListener = new CLESelectLogixBoxListener(this);
CLESelectLogixBoxListener::CLESelectLogixBoxListener(ConditionalListEdit *self) {this->self = self;}
     //QOverride
    /*public*/ void CLESelectLogixBoxListener::actionPerformed(/*ActionEvent e*/) {
        int lgxIndex = self->_selectLogixBox->currentIndex();
        if (lgxIndex >= 0 && lgxIndex < self->_selectLogixList.size()) {
            QString lgxName = self->_selectLogixList.at(lgxIndex);
            self->loadSelectConditionalBox(lgxName);
        }
    }
//};

///*transient*/ CLESelectConditionalBoxListener* selectConditionalBoxListener = new CLESelectConditionalBoxListener(this);
CLESelectConditionalBoxListener::CLESelectConditionalBoxListener(ConditionalListEdit *self) {this->self = self;}
     //QOverride
    /*public*/ void CLESelectConditionalBoxListener::actionPerformed(/*ActionEvent e*/) {
        int cdlIndex = self->_selectConditionalBox->currentIndex();
        if (cdlIndex > 0 && cdlIndex < self->_selectConditionalList.size()) {
            QString cdlName = self->_selectConditionalList.at(cdlIndex);
            self->_variableNameField->setText(cdlName);
        }
    }
//};
#endif
// ============ Edit Action Window and Methods ============
/**
 * Creates and/or initializes the Edit Action window Note: you can get
 * here via the New Action button (addActionPressed) or via an
 * Edit button in the Action table of the EditConditional window.
 */
void ConditionalListEdit::makeEditActionWindow(int row)
{
    if (alreadyEditingActionOrVariable()) {
        return;
    }
    _curActionRowNumber = row;
    _curAction = _actionList->at(row);
    _editActionFrame = new JmriJFrameX(tr("Edit Action"), true, true);
    _editActionFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
#if 1
//        _editActionFrame->setLocation(10, 300);
    QWidget* topPanel = makeTopPanel(_editActionFrame, "Consequent Action ", 600, 160);

//    Box panel1 = Box.createHorizontalBox();
//    panel1->layout()->addWidget(Box.createHorizontalGlue());
    QWidget* panel1 = new QWidget();
    panel1->setLayout(new QHBoxLayout());

    _actionItemBox = new QComboBox();
    for (int i = 0; i <= Conditional::ITEM_TYPE_LAST_ACTION; i++) {
        _actionItemBox->addItem(DefaultConditionalAction::getItemTypeString(i));
    }
    panel1->layout()->addWidget(makeEditPanel(_actionItemBox, "Action Group", "Select action item for Conditional to execute"));
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionNameField = new JTextField(30);
    _actionNameField->setMinimumWidth(80);
    _namePanel = makeEditPanel(_actionNameField, "System / User Name", NULL);
    _namePanel->setMaximumSize(
                QSize(50, _namePanel->size().height()));
    _namePanel->setVisible(false);
    panel1->layout()->addWidget(_namePanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    // Arbitrary name combo box to facilitate the panel construction
    if (_selectionMode == SelectionMode::USECOMBO) {
        _comboNameBox = createNameBox(1);
        _actionComboNamePanel = makeEditPanel(_comboNameBox, "LabelItemName", "");  // NOI18N
        _actionComboNamePanel->setVisible(false);
        panel1->layout()->addWidget(_actionComboNamePanel);
        panel1->layout()->addWidget(Box::createHorizontalStrut(STRUT));
    }

    _actionTypeBox = new QComboBox();
    _actionTypeBox->addItem("");
    _actionTypePanel = makeEditPanel(_actionTypeBox, "Action Type", "Select type of action, or select None if no action is needed.");
    _actionTypePanel->setVisible(false);
    panel1->layout()->addWidget(_actionTypePanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionBox = new QComboBox();
    _actionBox->addItem("");
    _actionPanel = makeEditPanel(_actionBox, "Action Type", "Select type of action, or select None if no action is needed.");
    _actionPanel->setVisible(false);
    panel1->layout()->addWidget(_actionPanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _shortActionString = new JTextField(15);
    _shortTextPanel = makeEditPanel(_shortActionString, "Action Data", NULL);
    _shortTextPanel->setMaximumSize(
                QSize(25, _shortTextPanel->size().height()));
    //_shortTextPanel->layout()->addWidget(Box.createVerticalGlue());
    _shortTextPanel->setVisible(false);
    panel1->layout()->addWidget(_shortTextPanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    _actionOptionBox = new QComboBox();
    for (int i = 1; i <= Conditional::NUM_ACTION_OPTIONS; i++) {
        _actionOptionBox->addItem(DefaultConditionalAction::getOptionString(i,_triggerOnChangeButton->isChecked()));
    }
    _optionPanel = makeEditPanel(_actionOptionBox, "Change Option", "Select when action should occur");
    _optionPanel->setVisible(false);
    panel1->layout()->addWidget(_optionPanel);
    //panel1->layout()->addWidget(Box.createHorizontalStrut(STRUT));

    //panel1->layout()->addWidget(Box.createHorizontalGlue());
    topPanel->layout()->addWidget(panel1);
    //topPanel->layout()->addWidget(Box.createVerticalStrut(5));
    //topPanel->layout()->addWidget(Box.createVerticalGlue());

//    Box* panel2 = Box::createHorizontalBox();
//    panel2->layout()->addWidget(Box::createHorizontalGlue());
    //QGroupBox* panel2 = new QGroupBox(/*"xx"*/);
    QWidget* panel2 = new QWidget();
    panel2->setLayout(new QVBoxLayout());

    _setPanel = new QWidget();
    _setPanel->setLayout(new QVBoxLayout(_setPanel/*, BoxLayout.Y_AXIS*/));
    QWidget* p = new QWidget();
    p->setLayout(new QHBoxLayout());
    p->layout()->addWidget(new QLabel(tr("Set File")));
    _setPanel->layout()->addWidget(p);
    _actionSetButton = new QPushButton(tr("File"));
    connect(_actionSetButton, SIGNAL(clicked()), this, SLOT(on_actionSetButton_Pressed()));
    _actionSetButton->setMaximumSize(_actionSetButton->size());
    ((QVBoxLayout*)_setPanel->layout())->addWidget(_actionSetButton, 0, Qt::AlignCenter);
    _actionSetButton->setToolTip(tr("Click to select a file from disk"));  // NOI18N
    //_setPanel->layout()->addWidget(Box.createVerticalGlue());
    _setPanel->setVisible(false);
    panel2->layout()->addWidget(_setPanel);
    panel2->layout()->addWidget(Box::createHorizontalStrut(5));

    _longActionString = new JTextField(/*50*/100);
    _textPanel = makeEditPanel(_longActionString, "Action Text", NULL);
    _textPanel->setMaximumSize(
                 QSize(80, _textPanel->size().height()));
    _textPanel->layout()->addWidget(Box::createVerticalGlue());
    _textPanel->setVisible(false);
    panel2->layout()->addWidget(_textPanel);
    panel2->layout()->addWidget(Box::createHorizontalGlue());
    topPanel->layout()->addWidget(panel2);
    topPanel->layout()->addWidget(Box::createVerticalStrut(5));
    topPanel->layout()->addWidget(Box::createVerticalGlue());

//    ActionListener updateListener = new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updateActionPressed();
//            }
//        };
    QPushButton* updateButton = new QPushButton();
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updateActionPressed()));
//   ActionListener cancelListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               cancelEditActionPressed();
//           }
//       };
    QPushButton* cancelButton = new QPushButton();
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelEditActionPressed()));
//   ActionListener deleteListener = new ActionListener() {
//           /*public*/ void actionPerformed(ActionEvent e) {
//               deleteActionPressed();
//           }
//       };
    QPushButton* deleteButton = new QPushButton();
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteActionPressed()));
    QWidget* panel = makeButtonPanel(updateButton, cancelButton, deleteButton);
    topPanel->layout()->addWidget(panel);
    //topPanel->layout()->addWidget(Box.createVerticalGlue());

    if(_editActionFrame->centralWidget() == NULL)
    {
        QWidget* centralWidget = new QWidget();
        centralWidget->setLayout(new QVBoxLayout());
        _editActionFrame->setCentralWidget(centralWidget);
    }
    QWidget* contentPane = _editActionFrame->centralWidget();
    contentPane->layout()->addWidget(topPanel);
    // note - this listener cannot be added until all items are entered into _actionItemTypeBox
   // _actionItemBox.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            int newActionItem = _actionItemBox.getSelectedIndex();
//            log.debug("_actionItemBox Listener: new = {}, curr = {}, row = {}",  // NOI18N
//                    newActionItem, _curActionItem, _curActionRowNumber);
//            if (newActionItem != _curActionItem) {
//                if (_curActionRowNumber >= 0) {
//                    _curAction = new DefaultConditionalAction();
//                    _actionList.set(_curActionRowNumber, _curAction);
//                }
//                _curActionItem = newActionItem;
//            }
//            actionItemChanged(newActionItem);
//            _editActionFrame.pack();
//        }
//    });
    connect(_actionItemBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_actionItemBox()));
//    // setup window closing listener
//    _editActionFrame->addWindowListener(
//        new java.awt.event.WindowAdapter() {
//                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                    cancelEditActionPressed();
//                }
//            });
    _editActionFrame->addWindowListener(editActionFrameWindowListener = new EditActionFrameWindowListener(this));
    _curActionItem = Conditional::ACTION_TO_ITEM[_curAction->getType()];
    initializeActionVariables();
    _editActionFrame->setVisible(true);
    _editActionFrame->adjustSize();
#endif
} /* makeEditActionWindow */

void ConditionalListEdit::on_actionSetButton_Pressed()
{
  validateAction();
  setFileLocation(0);
}

void ConditionalListEdit::on_actionItemType_changed(int select)
{
  if (log->isDebugEnabled()) log->debug("_actionItemTypeBoxListener: select= "+select);
  actionItemChanged(select);
  _editActionFrame->pack();

}

void ConditionalListEdit::on_actionItemBox()
{
 int newActionItem = _actionItemBox->currentIndex();
 log->debug(tr("_actionItemBox Listener: new = %1, curr = %2, row = %3").arg(  // NOI18N
         newActionItem).arg(_curActionItem).arg(_curActionRowNumber));
 if (newActionItem != _curActionItem) {
     if (_curActionRowNumber >= 0) {
         _curAction = new DefaultConditionalAction();
         _actionList->replace(_curActionRowNumber, _curAction);
     }
     _curActionItem = newActionItem;
 }
 actionItemChanged(newActionItem);
 _editActionFrame->pack();
}


// ------------ Main Action methods ------------
/**
* set display to show current action (curAction) parameters
*/
void ConditionalListEdit::initializeActionVariables() {
    int actionType = _curAction->getType();
    int itemType = Conditional::ACTION_TO_ITEM[actionType];
    if (log->isDebugEnabled()) log->debug("initializeActionVariables: itemType= "+QString::number(itemType)+", actionType= "+QString::number(actionType));
    if (actionType==Conditional::ACTION_NONE) {
        return;
    }
    _actionItemBox->setCurrentIndex(itemType);
    _actionNameField->setText(_curAction->getDeviceName());
    int oldState = _actionTypeBox->blockSignals(true);
    switch (itemType)
    {
        case Conditional::ITEM_TYPE_SENSOR:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SENSOR_ACTION, actionType)+1);
            if ((actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                            (actionType==Conditional::ACTION_DELAYED_SENSOR)) {
                _shortActionString->setText(_curAction->getActionString());
            }
            if (actionType==Conditional::ACTION_SET_SENSOR ||
                    actionType==Conditional::ACTION_DELAYED_SENSOR ||
                    actionType==Conditional::ACTION_RESET_DELAYED_SENSOR ) {
                if (_curAction->getActionData() == Sensor::ACTIVE) {
                    _actionBox->setCurrentIndex(0);
                } else if (_curAction->getActionData() == Sensor::INACTIVE) {
                    _actionBox->setCurrentIndex(1);
                } else if (_curAction->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            }
            break;
        case Conditional::ITEM_TYPE_TURNOUT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_TURNOUT_ACTION, actionType)+1);
            if ((actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                            (actionType==Conditional::ACTION_DELAYED_TURNOUT) ) {
                _shortActionString->setText(_curAction->getActionString());
            }
            if ((actionType==Conditional::ACTION_SET_TURNOUT) ||
                            (actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                            (actionType==Conditional::ACTION_DELAYED_TURNOUT) ) {
                if (_curAction->getActionData() == Turnout::CLOSED) {
                    _actionBox->setCurrentIndex(0);
                } else if (_curAction->getActionData() == Turnout::THROWN) {
                    _actionBox->setCurrentIndex(1);
                } else if (_curAction->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            } else if (actionType==Conditional::ACTION_LOCK_TURNOUT) {
                if (_curAction->getActionData() == Turnout::UNLOCKED) {
                    _actionBox->setCurrentIndex(0);
                } else if (_curAction->getActionData() == Turnout::LOCKED) {
                    _actionBox->setCurrentIndex(1);
                } else if (_curAction->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            }
            break;
        case Conditional::ITEM_TYPE_LIGHT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_LIGHT_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_LIGHT) {
                if (_curAction->getActionData() == Light::ON) {
                    _actionBox->setCurrentIndex(0);
                } else if (_curAction->getActionData() == Light::OFF) {
                    _actionBox->setCurrentIndex(1);
                } else if (_curAction->getActionData() == Route::TOGGLE) {
                    _actionBox->setCurrentIndex(2);
                }
            } else if ((actionType==Conditional::ACTION_SET_LIGHT_INTENSITY) ||
                       (actionType==Conditional::ACTION_SET_LIGHT_TRANSITION_TIME)) {
                _shortActionString->setText(_curAction->getActionString());
            }
            break;
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            /*
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SIGNAL_HEAD_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                _actionBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            AbstractSignalHead.getDefaultValidStates(), _curAction->getActionData()));
            }
            */
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SIGNAL_HEAD_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                loadJComboBoxWithSignalAspects(_actionBox, _actionNameField->text().trimmed());
            }
            break;
        case Conditional::ITEM_TYPE_SIGNALMAST:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SIGNAL_MAST_ACTION, actionType)+1);
           break;
        case Conditional::ITEM_TYPE_CLOCK:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_CLOCK_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                int time = _curAction->getActionData();
                _shortActionString->setText(formatTime(time / 60, time - ((time / 60) * 60)));
                _actionNameField->setText("");
            }
            break;
        case Conditional::ITEM_TYPE_MEMORY:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_MEMORY_ACTION, actionType)+1);
            _shortActionString->setText(_curAction->getActionString());
            break;
        case Conditional::ITEM_TYPE_LOGIX:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_LOGIX_ACTION, actionType)+1);
            break;

        case Conditional::ITEM_TYPE_WARRANT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_WARRANT_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_CONTROL_TRAIN) {
                if (_curAction->getActionData() == Warrant::HALT) {
                    _actionBox->setCurrentIndex(0);
                } else if (_curAction->getActionData() == Warrant::RESUME) {
                    _actionBox->setCurrentIndex(1);
                } else if (_curAction->getActionData() == Warrant::ABORT) {
                    _actionBox->setCurrentIndex(2);
                }
            } else if (actionType==Conditional::ACTION_SET_TRAIN_ID ||
                            actionType==Conditional::ACTION_SET_TRAIN_NAME ||
                            actionType==Conditional::ACTION_THROTTLE_FACTOR) {
                _shortActionString->setText(_curAction->getActionString());
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_OBLOCK_ACTION, actionType)+1);
            break;
        case Conditional::ITEM_TYPE_AUDIO:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_AUDIO_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_PLAY_SOUND) {
                _longActionString->setText(_curAction->getActionString());
            } else if (actionType==Conditional::ACTION_CONTROL_AUDIO) {
                switch (_curAction->getActionData()) {
                    case Audio::CMD_PLAY:
                        _actionBox->setCurrentIndex(0);
                        break;
                    case Audio::CMD_STOP:
                        _actionBox->setCurrentIndex(1);
                        break;
                    case Audio::CMD_PLAY_TOGGLE:
                        _actionBox->setCurrentIndex(2);
                        break;
                    case Audio::CMD_PAUSE:
                        _actionBox->setCurrentIndex(3);
                        break;
                    case Audio::CMD_RESUME:
                        _actionBox->setCurrentIndex(4);
                        break;
                    case Audio::CMD_PAUSE_TOGGLE:
                        _actionBox->setCurrentIndex(5);
                        break;
                    case Audio::CMD_REWIND:
                        _actionBox->setCurrentIndex(6);
                        break;
                    case Audio::CMD_FADE_IN:
                        _actionBox->setCurrentIndex(7);
                        break;
                    case Audio::CMD_FADE_OUT:
                        _actionBox->setCurrentIndex(8);
                        break;
                    case Audio::CMD_RESET_POSITION:
                        _actionBox->setCurrentIndex(9);
                        break;
                }
            }
            break;

        case Conditional::ITEM_TYPE_SCRIPT:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_SCRIPT_ACTION, actionType)+1);
            if (actionType==Conditional::ACTION_RUN_SCRIPT) {
                _longActionString->setText(_curAction->getActionString());
            } else if (actionType==Conditional::ACTION_JYTHON_COMMAND) {
                _shortActionString->setText(_curAction->getActionString());
            }
            break;
        case Conditional::ITEM_TYPE_OTHER:
            _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                            Conditional::ITEM_TO_OTHER_ACTION, actionType)+1);
            // ACTION_TRIGGER_ROUTE
            break;
    }
    _actionTypeBox->blockSignals(oldState);
    _actionOptionBox->setCurrentIndex(_curAction->getOption() - 1);
    _editActionFrame->adjustSize();
   // _editActionFrame->transferFocusBackward();
}   /* initializeActionVariables */


/**
 * Responds to a change in an Action Type Box of Edit Action Window
 * Set components visible for the selected type
 */
void ConditionalListEdit::actionItemChanged(int type)
{
 int actionType = ((DefaultConditionalAction*)_curAction)->getType();
 if (log->isDebugEnabled()) log->debug("actionItemChanged: itemType= "+QString::number(type)+", actionType= "+QString::number(actionType));
 //_actionTypeBox->removeActionListener(_actionTypeListener);
 disconnect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), _actionTypeListener, SLOT(actionPerformed()));
 _actionTypePanel->setVisible(false);
 _setPanel->setVisible(false);
 _shortTextPanel->setVisible(false);
 _shortActionString->setText("");
 _textPanel->setVisible(false);
 _longActionString->setText("");
 _namePanel->setVisible(false);
 _actionPanel->setVisible(false);
 _optionPanel->setVisible(false);
 int itemType = Conditional::ACTION_TO_ITEM.at(actionType);
 if (type==Conditional::TYPE_NONE && itemType==Conditional::TYPE_NONE) {
    return;
 }
 _actionTypePanel->setVisible(true);
 _actionTypeBox->clear();
 _actionBox->clear();
 if (type!=Conditional::TYPE_NONE) {  // actionItem listener choice overrides current item
    itemType = type;
 }
 if (itemType!=Conditional::ACTION_TO_ITEM.at(actionType)) {
    actionType = Conditional::ACTION_NONE;    // chosen item type does not support action type
 }
 if (actionType != Conditional::ACTION_NONE) {
    _optionPanel->setVisible(true);    // item type compatible with action type
 }
 _actionTypeBox->addItem("");
//    _actionNameField.removeActionListener(actionSignalHeadNameListener);
 disconnect(_actionNameField, SIGNAL(editingFinished()), this, SLOT(actionSignalMastNameListener()));
//    _actionNameField.removeActionListener(actionSignalMastNameListener);
 disconnect(_actionNameField, SIGNAL(editingFinished()), this, SLOT(actionSignalMastNameListener()));

 switch (itemType)
 {
  case Conditional::ITEM_TYPE_TURNOUT:
  {
   for(int i=0; i<Conditional::ITEM_TO_TURNOUT_ACTION.length(); i++)
   {
    _actionTypeBox->addItem(
            DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_TURNOUT_ACTION.at(i)));
   }
   if ((actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                    (actionType==Conditional::ACTION_DELAYED_TURNOUT))
   {
    //QWidget* p = (JPanel)_shortTextPanel.getComponent(0);
    QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
    //QLabel* l = (JLabel)p.getComponent(0);
    QLabel* l = (QLabel*)p->children().at(1);
    l->setText(tr("Delay Time"));
    _shortTextPanel->setToolTip(tr("Enter time (seconds) to wait before setting turnout"));
    _shortTextPanel->setVisible(true);
   }
   QWidget* panel = (QWidget*)_actionPanel->children().at(1);
   QLabel* label = (QLabel*)panel->children().at(1);
   if ((actionType==Conditional::ACTION_SET_TURNOUT) ||
                    (actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT)  ||
                    (actionType==Conditional::ACTION_DELAYED_TURNOUT))
   {
    label->setText(tr("Turnout Position"));
    _actionBox->addItem(tr("Closed"));
    _actionBox->addItem(tr("Thrown"));
    _actionBox->addItem( tr("Toggle"));
    _actionPanel->setToolTip(tr("Select Closed or Thrown depending upon how Turnout is to be set"));
    _actionPanel->setVisible(true);
   }
   else if (actionType==Conditional::ACTION_LOCK_TURNOUT)
   {
    label->setText(tr("Lock State"));
    _actionBox->addItem(tr("Unlock"));
    _actionBox->addItem(tr("Lock"));
    _actionBox->addItem( tr("Toggle"));
    _actionPanel->setToolTip(tr("Select Lock or Unlock"));
    _actionPanel->setVisible(true);
   }
   _namePanel->setToolTip(tr("Enter Name (system or user) for Turnout (e.g. LT12)"));
   _namePanel->setVisible(true);
   break;
   }
   case Conditional::ITEM_TYPE_SENSOR:
   {
    for(int i=0; i<Conditional::ITEM_TO_SENSOR_ACTION.length(); i++)
    {
     _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SENSOR_ACTION.at(i)));
    }
    if ((actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                    (actionType==Conditional::ACTION_DELAYED_SENSOR))
    {
     QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
     l->setText(tr("Delay Time"));
     _shortTextPanel->setToolTip(tr("Enter time (seconds) to wait before setting turnout"));
     _shortTextPanel->setVisible(true);
    }
    if ((actionType==Conditional::ACTION_SET_SENSOR) ||
                (actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                (actionType==Conditional::ACTION_DELAYED_SENSOR) )
    {
     QWidget* p = (QWidget*)_actionPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
     l->setText(tr("Sensor State"));
     _actionBox->addItem(tr("Active"));
     _actionBox->addItem(tr("Inactive"));
     _actionBox->addItem( tr("Toggle"));
     _actionPanel->setToolTip(tr("Select Active or Inactive depending upon how Sensor is to be set"));
     _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Sensor (e.g. CS2)"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_SIGNALHEAD:
    {
     //_actionNameField->layout()->addActionListener(actionSignalHeadNameListener);
     connect(_actionNameField, SIGNAL(editingFinished()), this, SLOT(actionSignalHeadNameListener()));

     for(int i=0; i<Conditional::ITEM_TO_SIGNAL_HEAD_ACTION.length(); i++)
     {
      _actionTypeBox->addItem(DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SIGNAL_HEAD_ACTION.at(i)));
     }
     if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE)
     {
      QWidget* p = (QWidget*)_actionPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Action Signal"));

      loadJComboBoxWithSignalAspects(_actionBox,_actionNameField->text().trimmed());

      _actionPanel->setToolTip(tr("Select Signal Head Appearance to set"));
      _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Signal Head (e.g. IH34)"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_SIGNALMAST:
    {
     //_actionNameField->layout()->addActionListener(actionSignalMastNameListener);
     connect(_actionNameField, SIGNAL(editingFinished()), this, SLOT(actionSignalHeadNameListener()));

     for(int i=0; i<Conditional::ITEM_TO_SIGNAL_MAST_ACTION.length(); i++)
     {
      _actionTypeBox->addItem(
        DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SIGNAL_MAST_ACTION.at(i)));
     }
     if (actionType==Conditional::ACTION_SET_SIGNALMAST_ASPECT)
     {
      QWidget* p = (QWidget*)_actionPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Signal Aspect"));

      loadJComboBoxWithMastAspects(_actionBox,_actionNameField->text().trimmed());

      _actionPanel->setToolTip(tr("Select Signal Mast Aspect to set and hit Enter/Return to load aspects"));
      _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Signal Mast and hit Enter/Return to load aspects"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_LIGHT:
    {
     for(int i=0; i<Conditional::ITEM_TO_LIGHT_ACTION.length(); i++)
     {
     _actionTypeBox->addItem(
            DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_LIGHT_ACTION.at(i)));
     }
     if (actionType==Conditional::ACTION_SET_LIGHT_INTENSITY)
     {
      QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Light Intensity"));
     _shortTextPanel->setToolTip(tr("Enter intensity percentage as an integer 0 to 100."));
       _shortTextPanel->setVisible(true);
     }
     else if (actionType==Conditional::ACTION_SET_LIGHT_TRANSITION_TIME)
     {
      QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Transition Time"));
      _shortTextPanel->setToolTip(tr("Enter number of fast clock minutes to transition between 0% and 100%."));
      _shortTextPanel->setVisible(true);
     }
     else if (actionType==Conditional::ACTION_SET_LIGHT)
     {
      QWidget* p = (QWidget*)_actionPanel->children().at(1);
      QLabel* l = (QLabel*)p->children().at(1);
      l->setText(tr("Light State"));
      _actionBox->addItem(tr("On"));
      _actionBox->addItem(tr("Off"));
      _actionBox->addItem( tr("Toggle"));
      _actionPanel->setToolTip(tr("Select On or Off depending upon how Light is to be set"));
      _actionPanel->setVisible(true);
     }
     _namePanel->setToolTip(tr("Enter Name (system or user) for Light (e.g. CL21)"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_MEMORY:
    {
     for(int i=0; i<Conditional::ITEM_TO_MEMORY_ACTION.length(); i++)
     {
      _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_MEMORY_ACTION.at(i)));
     }
     QWidget* p = (QWidget*)_shortTextPanel->children().at(1);
     QLabel* l = (QLabel*)p->children().at(1);
     if (actionType==Conditional::ACTION_COPY_MEMORY)
     {
      _shortTextPanel->setToolTip(tr("Enter name (system or user) of Memory to receive the copied value"));
      l->setText(tr("Memory Name"));
     }
     else
     {
      _shortTextPanel->setToolTip(tr("Enter name (system or user) of Memory to receive the copied value"));
      l->setText(tr("Value"));
     }
     _shortTextPanel->setVisible(true);
     _namePanel->setToolTip(tr("Enter name (system or user) of Memory"));
     _namePanel->setVisible(true);
     break;
    }
    case Conditional::ITEM_TYPE_CLOCK:
    {
        for(int i=0; i<Conditional::ITEM_TO_CLOCK_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                            DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_CLOCK_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                QWidget* p = (QWidget*)_textPanel->children().at(1);
                QLabel* l = (QLabel*)p->children().at(1);
                l->setText(tr("Set Time"));
                _textPanel->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));
                _textPanel->setVisible(true);
            }
            break;
    }
        case Conditional::ITEM_TYPE_LOGIX:
    {
        for(int i=0; i<Conditional::ITEM_TO_LOGIX_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_LOGIX_ACTION.at(i)));
            }
            _namePanel->setToolTip(tr("Enter name (system or user) of Logix"));
            _namePanel->setVisible(true);
            break;
    }

        case Conditional::ITEM_TYPE_WARRANT:
            for(int i=0; i<Conditional::ITEM_TO_WARRANT_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_WARRANT_ACTION.at(i)));
            }
            _namePanel->setToolTip(tr("Enter name (system or user) of Warrant"));
            _namePanel->setVisible(true);
            if (actionType==Conditional::ACTION_CONTROL_TRAIN) {
                //p = (JPanel)_actionPanel->getComponent(0);
//             QWidget* p = (QWidget*)_actionPanel->children().at(0);
//                l = (JLabel)p->getComponent(0);
//             QLabel* l = (QLabel*)p->children().at(0);
             QWidget* p = _actionPanel->findChildren<QWidget*>().at(0);
             QLabel* l = p->findChildren<QLabel*>().at(0);
                _actionBox->layout()->addWidget(new QLabel("Halt"));
                _actionBox->layout()->addWidget(new QLabel("Resume"));
                _actionBox->layout()->addWidget(new QLabel("Abort"));
                l->setText(tr("Control Train"));
               _actionPanel->setVisible(true);
            } else if (actionType==Conditional::ACTION_SET_TRAIN_ID ||
                            actionType==Conditional::ACTION_SET_TRAIN_NAME ||
                            actionType==Conditional::ACTION_THROTTLE_FACTOR) {
                //p = (JPanel)_shortTextPanel->getComponent(0);
//              QWidget* p = (QWidget*)_shortTextPanel->children().at(0);
                //l = (JLabel)p->getComponent(0);
//               QLabel* l = (QLabel*)p->children().at(0);
             QWidget* p = _shortTextPanel->findChildren<QWidget*>().at(0);
             QLabel* l = p->findChildren<QLabel*>().at(0);

                if (actionType==Conditional::ACTION_SET_TRAIN_ID) {
                    _shortTextPanel->setToolTip(tr("Enter a train ID from the Roster - or enter a DCC address indicating long or short e.g. 1234(L) or 10(S)"));
                    l->setText(tr("Train Id"));
                } else if (actionType==Conditional::ACTION_SET_TRAIN_NAME) {
                    _shortTextPanel->setToolTip(tr("Enter a name for the train"));
                    l->setText(tr("Train Name"));
                } else if (actionType==Conditional::ACTION_THROTTLE_FACTOR) {
                    _shortTextPanel->setToolTip(tr("Enter a decimal number for the throttle setting ratio."));
                    l->setText(tr("Throttle Factor"));
                }
                _shortTextPanel->setVisible(true);
            }
            break;
        case Conditional::ITEM_TYPE_OBLOCK:
            //_actionNameField->layout()->addActionListener(actionOBlockPathListener);
//  connect(_actionNameField, SIGNAL(editingFinished()),actionOBlockPathListener, SLOT() );

            for(int i=0; i<Conditional::ITEM_TO_OBLOCK_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_OBLOCK_ACTION.at(i)));
            }
            _namePanel->setToolTip(tr("Enter name (system or user) of OBlock"));
            _namePanel->setVisible(true);
/*
            if (actionType==Conditional::ACTION_ALLOCATE_BLOCK_PATH ||
                    actionType==Conditional::ACTION_SET_BLOCK_PATH_TURNOUTS) {
                p = (JPanel)_actionPanel.getComponent(0);
                l = (JLabel)p.getComponent(0);
                l->setText(tr("Block Path"));

                loadJComboBoxWithBlockPaths(_actionBox,_actionNameField->text().trimmed());

                _actionPanel->setToolTip(tr("Select the path to use"));
                _actionPanel->setVisible(true);
            } else {
            }
*/
            break;
        case Conditional::ITEM_TYPE_AUDIO:
            for(int i=0; i<Conditional::ITEM_TO_AUDIO_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_AUDIO_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_PLAY_SOUND)
            {
                //p = (JPanel)_textPanel.getComponent(0);
             QList<QWidget*> widgets = _textPanel->findChildren<QWidget*>();
                //= (QWidget*)_textPanel->children().at(0);
             QWidget* p = widgets.at(0);
                //l = (JLabel)p.getComponent(0);
             QList<QLabel*> labels = p->findChildren<QLabel*>();
             //QLabel* l = (QLabel*)p->children().at(0);
             QLabel* l = labels.at(0);
             l->setText(tr("Set File"));
             _textPanel->setToolTip(tr("Click for a file selection dialog for choosing a sound file"));
             _textPanel->setVisible(true);
             _setPanel->setVisible(true);
            } else if (actionType==Conditional::ACTION_CONTROL_AUDIO) {
             //p = (JPanel)_textPanel.getComponent(0);
          QList<QWidget*> widgets = _textPanel->findChildren<QWidget*>();
             //= (QWidget*)_textPanel->children().at(0);
          QWidget* p = widgets.at(0);
             //l = (JLabel)p.getComponent(0);
          QList<QLabel*> labels = p->findChildren<QLabel*>();
          //QLabel* l = (QLabel*)p->children().at(0);
          QLabel* l = labels.at(0);

                l->setText(tr("Action Audio"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePlay"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceStop"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePlayToggle"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePause"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceResume"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourcePauseToggle"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceRewind"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceFadeIn"));
                _actionBox->layout()->addWidget(new QLabel("AudioSourceFadeOut"));
                _actionBox->layout()->addWidget(new QLabel("AudioResetPosition"));
                _actionPanel->setToolTip(tr("Select action to perform"));
                _actionPanel->setVisible(true);
                _namePanel->setToolTip(tr("Enter Name (system or user) for AudioSource (e.g. IAS2)"));
                _namePanel->setVisible(true);
            }
            break;
        case Conditional::ITEM_TYPE_SCRIPT:
            for(int i=0; i<Conditional::ITEM_TO_SCRIPT_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SCRIPT_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_RUN_SCRIPT) {
             //p = (JPanel)_textPanel.getComponent(0);
          QList<QWidget*> widgets = _textPanel->findChildren<QWidget*>();
             //= (QWidget*)_textPanel->children().at(0);
          QWidget* p = widgets.at(0);
             //l = (JLabel)p.getComponent(0);
          QList<QLabel*> labels = p->findChildren<QLabel*>();
          //QLabel* l = (QLabel*)p->children().at(0);
          QLabel* l = labels.at(0);
                l->setText(tr("Set File"));
                _textPanel->setToolTip(tr("Click for a file selection dialog for choosing a script file"));
                _textPanel->setVisible(true);
                _setPanel->setVisible(true);
            } else if (actionType==Conditional::ACTION_JYTHON_COMMAND) {
             //p = (JPanel)_textPanel.getComponent(0);
          QList<QWidget*> widgets = _textPanel->findChildren<QWidget*>();
             //= (QWidget*)_textPanel->children().at(0);
          QWidget* p = widgets.at(0);
             //l = (JLabel)p.getComponent(0);
          QList<QLabel*> labels = p->findChildren<QLabel*>();
          //QLabel* l = (QLabel*)p->children().at(0);
          QLabel* l = labels.at(0);
                l->setText(tr("Script Command"));
                _shortTextPanel->setToolTip(tr("Enter Jython command text"));
                _shortTextPanel->setVisible(true);
            }
            break;

        case Conditional::ITEM_TYPE_OTHER:
    {
            for(int i=0; i<Conditional::ITEM_TO_OTHER_ACTION.length(); i++) {
                _actionTypeBox->addItem(
                    DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_OTHER_ACTION.at(i)));
            }
            if (actionType==Conditional::ACTION_TRIGGER_ROUTE) {
                _namePanel->setToolTip(tr("Enter name (system or user) of Route"));
                _namePanel->setVisible(true);
            }
            break;
    }
        default :
    {
        break;
    }
 }
 _actionTypeBox->setMaximumSize(_actionTypeBox->size());
 _actionBox->setMaximumSize(_actionBox->size());
 _actionTypeListener->setItemType(itemType);
 //_actionTypeBox->addActionListener(_actionTypeListener);
 connect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), _actionTypeListener, SLOT(actionPerformed()));
 _editActionFrame->pack();
} /* actionItemChanged */


EditActionFrameWindowListener::EditActionFrameWindowListener(ConditionalListEdit *self)
{
 this->self = self;
}
void EditActionFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 self->cancelEditActionPressed();
}
/**
 * Update the name combo box selection based on the current contents of the
 * name field. Called by actionItemChanged
 *
 * @since 4.7.3
 * @param itemType The type of name box to be created.
 */
void ConditionalListEdit::setActionNameBox(int itemType) {
    if (_selectionMode != SelectionMode::USECOMBO) {
        return;
    }
    _comboNameBox = createNameBox(itemType);
    if (_comboNameBox == NULL) {
        return;
    }
    _comboNameBox->setSelectedBeanByName(_curAction->getDeviceName());
    NameBoxListener* listener = new NameBoxListener(_actionNameField, this);
    //_comboNameBox.addActionListener(new NameBoxListener(_actionNameField));
    connect(_comboNameBox, SIGNAL(currentIndexChanged(QString)), listener, SLOT(actionPerformed()));
//    _actionComboNamePanel->remove(1);
//    _actionComboNamePanel->layout()->addWidget(_comboNameBox, NULL, 1);
    _namePanel->setVisible(false);
    _actionComboNamePanel->setVisible(true);
}

// ------------ Action detail methods ------------
/*
* Responds to Update action button in the Edit Action window
*/
void ConditionalListEdit::updateActionPressed() {
    if (!validateAction() ) {
        _editActionFrame->toFront();
        return;
    }
    _actionTableModel->fireTableRowsUpdated(_curActionRowNumber, _curActionRowNumber);
    cleanUpAction();
    if (_editConditionalFrame!=NULL) {
        _editConditionalFrame->setVisible(true);
    }
}

/*
* Responds to Cancel action button and window closer of the
* Edit Variable window.  Also does cleanup of Update and Delete
* buttons.
*/
void ConditionalListEdit::cancelEditVariablePressed()
{
 if (_newItem)
 {
  deleteVariablePressed(_curVariableRowNumber);
 }
 else
 {
  cleanUpVariable();
 }
 if (_editConditionalFrame!=NULL)
 {
  _editConditionalFrame->setVisible(true);
 }
}

/**
 * Clean up Update and Delete Action buttons.
 */
void ConditionalListEdit::cleanUpAction()
{
 _newItem = false;
 if (_editActionFrame != NULL)
 {
  //_actionTypeBox->removeActionListener(_actionTypeListener);
  disconnect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), _actionTypeListener, SLOT(actionPerformed()));

  _editActionFrame->setVisible(false);
  _editActionFrame->dispose();
  _editActionFrame = nullptr;
  closeSinglePanelPickList();
 }
 _curActionRowNumber = -1;
}


/**
 * Respond to Delete action button in the Edit Action window.
 */
void ConditionalListEdit::deleteActionPressed() {
    deleteActionPressed(_curActionRowNumber);
}

/**
 * Respond to Delete action button in an action row of the Edit Conditional
 * pane.
 *
 * @param row index in table of action to be deleted
 */
/*
* Responds to Delete action button in an action row of the
* Edit Conditional window
*/
void ConditionalListEdit::deleteActionPressed(int row) {
    if (row != _curActionRowNumber && alreadyEditingActionOrVariable()) {
        return;
    }
    _actionList->removeAt(row);
    _actionTableModel->fireTableRowsDeleted(row, row);
    cleanUpAction();
    if (_editConditionalFrame!=NULL) {
        _editConditionalFrame->setVisible(true);
    }
    _showReminder = true;
}

/**
 * Respond to the [...] button in the Edit Action window action section.
 * <p>
 * Ask user to select an audio or python script file on disk.
 *
 * @param e the event heard
 */
void ConditionalListEdit::setFileLocation(JActionEvent* e)
{
 ConditionalAction* action = _actionList->value(_curActionRowNumber);
 JFileChooser* currentChooser;
 int actionType = action->getType();
 if (actionType == Conditional::ACTION_PLAY_SOUND)
 {
  if (sndFileChooser == NULL)
  {
      sndFileChooser = new JFileChooser(System::getProperty("user.dir") // NOI18N
              + File::separator + "resources" // NOI18N
              + File::separator + "sounds");  // NOI18N
//            FileChooserFilter filt = new jmri.util.FileChooserFilter("wav sound files");  // NOI18N
//            filt.addExtension("wav");  // NOI18N
      QString filt = "wav sound files (*.wav)";
      sndFileChooser->setFileFilter(filt);
     }
     currentChooser = sndFileChooser;
 } else if (actionType == Conditional::ACTION_RUN_SCRIPT) {
     if (scriptFileChooser == NULL) {
         scriptFileChooser = new JFileChooser(FileUtil::getScriptsPath());
//            FileChooserFilter filt = new FileChooserFilter("Python script files");  // NOI18N
//            filt.addExtension("py");  // NOI18N
         QString filt = "Python Script files (*.py)";
         scriptFileChooser->setFileFilter(filt);
     }
     currentChooser = scriptFileChooser;
 } else {
      log->warn("Unexpected actionType[" + QString::number(actionType) + "] = " + DefaultConditionalAction::getActionTypeString(actionType));  // NOI18N
     if (defaultFileChooser == NULL) {
         defaultFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
//            defaultFileChooser->setFileFilter(new NoArchiveFileFilter());
     }
     currentChooser = defaultFileChooser;
 }

 //currentChooser.rescanCurrentDirectory();
 int retVal = currentChooser->showOpenDialog(NULL);
 // handle selection or cancel
 if (retVal == JFileChooser::APPROVE_OPTION)
 {
  // set selected file location in data string
  try {
      _longActionString->setText(FileUtil::getPortableFilename(currentChooser->getSelectedFile()->getCanonicalPath()));
  } catch (IOException ex)
  {
   if ( log->isDebugEnabled()) {
        log->error("exception setting file location: " + ex.getMessage());  // NOI18N
   }
   _longActionString->setText("");
  }
 }
}

/**
 * Convert user setting in Conditional Action configuration pane to integer
 * for processing.
 *
 * @param itemType            value for current item type
 * @param actionTypeSelection index of selected item in configuration
 *                            comboBox
 * @return integer representing the selected action
 */
int ConditionalListEdit::getActionTypeFromBox(int itemType, int actionTypeSelection) {
    if (itemType < 0 || actionTypeSelection < 0) {
        return Conditional::ACTION_NONE;
    }
    switch (itemType) {
        case Conditional::ITEM_TYPE_SENSOR:
            return Conditional::ITEM_TO_SENSOR_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_TURNOUT:
            return Conditional::ITEM_TO_TURNOUT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_LIGHT:
            return Conditional::ITEM_TO_LIGHT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_SIGNALHEAD:
            return Conditional::ITEM_TO_SIGNAL_HEAD_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_SIGNALMAST:
            return Conditional::ITEM_TO_SIGNAL_MAST_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_MEMORY:
            return Conditional::ITEM_TO_MEMORY_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_LOGIX:
            return Conditional::ITEM_TO_LOGIX_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_WARRANT:
            return Conditional::ITEM_TO_WARRANT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_OBLOCK:
            return Conditional::ITEM_TO_OBLOCK_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_CLOCK:
            return Conditional::ITEM_TO_CLOCK_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_AUDIO:
            return Conditional::ITEM_TO_AUDIO_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_SCRIPT:
            return Conditional::ITEM_TO_SCRIPT_ACTION[actionTypeSelection];
        case Conditional::ITEM_TYPE_OTHER:
            return Conditional::ITEM_TO_OTHER_ACTION[actionTypeSelection];
    }
    return Conditional::ACTION_NONE;
}

// ------------ Action update processes ------------
/**
 * Validate Action data from Edit Action Window, and transfer it to current
 * action object as appropriate.
 * <p>
 * Messages are sent to the user for any errors found. This routine returns
 * false immediately after finding an error, even if there might be more
 * errors.
 *
 * @return true if all data checks out OK, otherwise false.
 */
bool ConditionalListEdit::validateAction() {
    int itemType = _actionItemBox->currentIndex();
    int actionType = Conditional::ACTION_NONE;
    int selection = _actionTypeBox->currentIndex();
    if (selection==0)
    {
     JOptionPane::showMessageDialog(
           _editConditionalFrame, tr("Please select an action type."),
                    tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    }
    QString name = _actionNameField->text().trimmed();
    QString actionString = _shortActionString->text().trimmed();
    _curAction->setActionString("");
    _curAction->setActionData(-1);
    bool referenceByMemory = false;
    if (name.length() > 0 && name.at(0)== '@')
    {
     QString memName = name.mid(1);
     if (!confirmIndirectMemory(memName))
     {
      return false;
     }
     memName = validateMemoryReference(memName);
     if (memName == nullptr) {
         return false;
     }
     referenceByMemory = true;
    }
    switch (itemType)
    {
     case Conditional::ITEM_TYPE_SENSOR:
         if (!referenceByMemory){
             name = validateSensorReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_SENSOR_ACTION.at(selection-1);
         if ((actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                         (actionType==Conditional::ACTION_DELAYED_SENSOR)) {
             if (!validateTimeReference(actionType, actionString))
             {
                 return (false);
             }
             _curAction->setActionString(actionString);
         }
         if ((actionType==Conditional::ACTION_SET_SENSOR) ||
                         (actionType==Conditional::ACTION_RESET_DELAYED_SENSOR) ||
                         (actionType==Conditional::ACTION_DELAYED_SENSOR)) {
             if (_actionBox->currentIndex() == 0)
                 _curAction->setActionData(Sensor::ACTIVE);
             else if (_actionBox->currentIndex() == 1)
                 _curAction->setActionData(Sensor::INACTIVE);
             else
                 _curAction->setActionData(Route::TOGGLE);
         }
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         break;
     case Conditional::ITEM_TYPE_TURNOUT:
         if (!referenceByMemory){
             name = validateTurnoutReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_TURNOUT_ACTION[selection-1];
         if ((actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                         (actionType==Conditional::ACTION_DELAYED_TURNOUT)) {
             if (!validateTimeReference(actionType, actionString))
             {
                 return (false);
             }
             _curAction->setActionString(actionString);
         }
         if ((actionType==Conditional::ACTION_SET_TURNOUT) ||
                         (actionType==Conditional::ACTION_RESET_DELAYED_TURNOUT) ||
                         (actionType==Conditional::ACTION_DELAYED_TURNOUT)) {
             if (_actionBox->currentIndex() == 0)
                 _curAction->setActionData(Turnout::CLOSED);
             else if (_actionBox->currentIndex() == 1)
                 _curAction->setActionData(Turnout::THROWN);
             else
                 _curAction->setActionData(Route::TOGGLE);
         } else if (actionType==Conditional::ACTION_LOCK_TURNOUT) {
             if (_actionBox->currentIndex() == 0)
                 _curAction->setActionData(Turnout::UNLOCKED);
             else if (_actionBox->currentIndex() == 1)
                 _curAction->setActionData(Turnout::LOCKED);
             else
                 _curAction->setActionData(Route::TOGGLE);
         }
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         break;
     case Conditional::ITEM_TYPE_LIGHT:
         if (!referenceByMemory){
             name = validateLightReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_LIGHT_ACTION[selection-1];
         if (actionType==Conditional::ACTION_SET_LIGHT_INTENSITY) {
             Light* lgtx = getLight(name);
             // check if light user name was entered
             if (lgtx == NULL) {
                 return false;
             }
             if (!lgtx->isIntensityVariable()) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            java.text.MessageFormat.format(
//                            tr("Error45"), new Object[] { name }),
//                            tr("ErrorTitle"),  javax.swing.JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Light - %1 - does not have variable intensity.\nPlease enter a light with variable intensity or change action type, and try again.").arg(name));
                 return (false);
             }
             if (!validateIntensityReference(actionType, actionString))
             {
                 return (false);
             }
             _curAction->setActionString(actionString);
         } else if (actionType==Conditional::ACTION_SET_LIGHT_TRANSITION_TIME) {
             Light* lgtx = getLight(name);
             // check if light user name was entered
             if (lgtx == NULL) {
                 return false;
             }
             if (!(lgtx)->isTransitionAvailable()) {
//                    javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                            java.text.MessageFormat.format(
//                            tr("Error40"), new Object[] { name }),
//                            tr("ErrorTitle"),  javax.swing.JOptionPane.ERROR_MESSAGE);
                 QMessageBox::critical(_editConditionalFrame, tr("Error"), tr("Light - {0} - does not support transition time.\n                                                                                Please enter a light with Transition Time or change action type, and try again.").arg(name));
                 return (false);
             }
             if (!validateTimeReference(actionType, actionString))
             {
                 return (false);
             }
             _curAction->setActionString(actionString);
         } else if (actionType==Conditional::ACTION_SET_LIGHT) {
             if (_actionBox->currentIndex() == 0)
                 _curAction->setActionData(Light::ON);
             else if (_actionBox->currentIndex() == 1)
                 _curAction->setActionData(Light::OFF);
             else
                 _curAction->setActionData(Route::TOGGLE);
         }
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         break;
     case Conditional::ITEM_TYPE_SIGNALHEAD:
         if (!referenceByMemory){
             name = validateSignalHeadReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_SIGNAL_HEAD_ACTION[selection-1];
         if (actionType==Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
             QString appStr = (QString)_actionBox->currentText();
             _curAction->setActionData(DefaultConditionalAction::stringToActionData(appStr));
             _curAction->setActionString(appStr);
         }
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         break;
     case Conditional::ITEM_TYPE_SIGNALMAST:
         if (!referenceByMemory){
             name = validateSignalMastReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_SIGNAL_MAST_ACTION[selection-1];
         if (actionType==Conditional::ACTION_SET_SIGNALMAST_ASPECT) {
             _curAction->setActionString(_actionBox->currentText());
         }
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         break;
     case Conditional::ITEM_TYPE_MEMORY:
         if (referenceByMemory){
//                javax.swing.JOptionPane.showMessageDialog(_editActionFrame, tr("Warn6"), tr("WarnTitle"),
//                        javax.swing.JOptionPane.WARNING_MESSAGE);
             QMessageBox::warning(_editActionFrame, tr("Warning"), tr("A Memory action cannot be referred to indirectly through a memory location."));
             return false;
         }
         name = validateMemoryReference(name);
         if (name == NULL) {
             return false;
         }
         actionType = Conditional::ITEM_TO_MEMORY_ACTION[selection-1];
         if (actionType==Conditional::ACTION_COPY_MEMORY) {
             actionString = validateMemoryReference(actionString);
             if (actionString == "") {
                 return false;
             }
         }
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         _curAction->setActionString(actionString);
         break;
     case Conditional::ITEM_TYPE_LOGIX:
         if (!referenceByMemory){
             name = validateLogixReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_LOGIX_ACTION[selection-1];
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         break;
#if 1
     case Conditional::ITEM_TYPE_WARRANT:
         if (!referenceByMemory){
             name = validateWarrantReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_WARRANT_ACTION[selection-1];
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
         if (actionType==Conditional::ACTION_CONTROL_TRAIN) {
             if (_actionBox->currentIndex() == 0)
                 _curAction->setActionData(Warrant::HALT);
             else if (_actionBox->currentIndex() == 1)
                 _curAction->setActionData(Warrant::RESUME);
             else
                 _curAction->setActionData(Warrant::ABORT);
         } else if (actionType==Conditional::ACTION_SET_TRAIN_ID ||
                         actionType==Conditional::ACTION_SET_TRAIN_NAME ||
                         actionType==Conditional::ACTION_THROTTLE_FACTOR ) {
             _curAction->setActionString(actionString);
         }
         break;
     case Conditional::ITEM_TYPE_OBLOCK:
         if (!referenceByMemory){
             name = validateOBlockReference(name);
             if (name == NULL) {
                 return false;
             }
         }
         actionType = Conditional::ITEM_TO_OBLOCK_ACTION[selection-1];
         _actionNameField->setText(name);
         _curAction->setDeviceName(name);
/*                if (actionType==Conditional::ACTION_ALLOCATE_BLOCK_PATH ||
                     actionType==Conditional::ACTION_SET_BLOCK_PATH_TURNOUTS) {
             _curAction->setActionString(_actionBox->currentText());
         }*/
         break;
#endif
     case Conditional::ITEM_TYPE_CLOCK:
         actionType = Conditional::ITEM_TO_CLOCK_ACTION[selection-1];
         if (actionType==Conditional::ACTION_SET_FAST_CLOCK_TIME) {
             int time = parseTime(actionString);
             if ( time<0 ) {
                 return (false);
             }
             _curAction->setActionData(time);
         }
         break;
#if 1
     case Conditional::ITEM_TYPE_AUDIO:
      actionType = Conditional::ITEM_TO_AUDIO_ACTION[selection-1];
      if (actionType==Conditional::ACTION_PLAY_SOUND)
      {
       _curAction->setActionString(_longActionString->text().trimmed());
      } else if (actionType==Conditional::ACTION_CONTROL_AUDIO)
      {
       if (!referenceByMemory)
       {
        name = validateAudioReference(name);
        if (name == NULL) {
            return false;
        }
       }
       _actionNameField->setText(name);
       _curAction->setDeviceName(name);
       switch (_actionBox->currentIndex())
       {
     case 0:
         _curAction->setActionData(Audio::CMD_PLAY);
         break;
     case 1:
         _curAction->setActionData(Audio::CMD_STOP);
         break;
     case 2:
         _curAction->setActionData(Audio::CMD_PLAY_TOGGLE);
         break;
     case 3:
         _curAction->setActionData(Audio::CMD_PAUSE);
         break;
     case 4:
         _curAction->setActionData(Audio::CMD_RESUME);
         break;
     case 5:
         _curAction->setActionData(Audio::CMD_PAUSE_TOGGLE);
         break;
     case 6:
         _curAction->setActionData(Audio::CMD_REWIND);
         break;
     case 7:
         _curAction->setActionData(Audio::CMD_FADE_IN);
         break;
     case 8:
         _curAction->setActionData(Audio::CMD_FADE_OUT);
         break;
     case 9:
         _curAction->setActionData(Audio::CMD_RESET_POSITION);
         break;
       }
      }
      break;
     case Conditional::ITEM_TYPE_SCRIPT:
         actionType = Conditional::ITEM_TO_SCRIPT_ACTION[selection-1];
         if (actionType==Conditional::ACTION_RUN_SCRIPT) {
             _curAction->setActionString(_longActionString->text().trimmed());
         } else if (actionType==Conditional::ACTION_JYTHON_COMMAND) {
             _curAction->setActionString(_shortActionString->text().trimmed());
         }
         break;
#endif
     case Conditional::ITEM_TYPE_OTHER:
         actionType = Conditional::ITEM_TO_OTHER_ACTION[selection-1];
         if (actionType==Conditional::ACTION_TRIGGER_ROUTE) {
             if (!referenceByMemory){
                 name = validateRouteReference(name);
                 if (name == NULL) {
                     return false;
                 }
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
         }
         break;
     default : break;
    }
    _curAction->setType(actionType);
    if (actionType != Conditional::ACTION_NONE) {
        _curAction->setOption(_actionOptionBox->currentIndex() + 1);
    }
    else {
        _curAction->setOption(0);
    }
    _editActionFrame->adjustSize();
    return (true);
}
#if 0 // Done ...
// ------------ Action detail listeners ------------
/* Listener for _actionTypeBox
*/
//class ActionTypeListener implements ActionListener {
ActionTypeListener::ActionTypeListener(LogixTableAction *self)
{
 this->self = self;
}
/*public*/ void ActionTypeListener::actionPerformed(ActionEvent* /*e*/) {
    int select1 = self->_actionItemTypeBox->currentIndex();
    int select2 = self->_actionTypeBox->currentIndex()-1;
    if (self->log->isDebugEnabled()) self->log->debug("ActionTypeListener: actionItemType= "+QString::number(select1)+", _itemType= "
                                        +QString::number(_itemType)+", action= "+QString::number(select2));
    if (select1 != _itemType) {
        if (self->log->isDebugEnabled()) self->log->error("ActionTypeListener actionItem selection ("+QString::number(select1)+
                                            ") != expected actionItem ("+QString::number(_itemType)+")");
    }
    if (self->_curAction!=NULL) {
        if (select1 > 0 && _itemType==select1) {
                ((ConditionalAction*)self->_curAction)->setType(self->getActionTypeFromBox(_itemType, select2));
                if (select1 == _itemType) {
                    QString text = self->_actionNameField->text();
                    if (text != NULL && text.length()>0) {
                        ((ConditionalAction*)self->_curAction)->setDeviceName(text);
                    }
                }
                self->actionItemChanged(_itemType);
                self->initializeActionVariables();
        }
    }
}
/*public*/ void ActionTypeListener::setItemType(int type) {
    _itemType = type;
}
#endif
//};
ActionTypeListener::ActionTypeListener(ConditionalListEdit* self) // SLOT[]
{
 this->self = self;
}

void ActionTypeListener::setItemType(int type) { this->_itemType = type;}

void ActionTypeListener::actionPerformed()
{
 int select1 = self->_actionItemBox->currentIndex();
 int select2 = self->_actionTypeBox->currentIndex() - 1;
 self->log->debug(tr("ActionTypeListener: actionItemType= %1, _itemType= %2, action= %3").arg(select1).arg(_itemType).arg(select2));  // NOI18N
 if (select1 != _itemType) {
     self->log->debug(tr("ActionTypeListener actionItem selection (%1) != expected actionItem (%2)").arg(select1).arg(_itemType));  // NOI18N
 }
 if (self->_curAction != nullptr) {
     if (select1 > 0 && _itemType == select1) {
         self->_curAction->setType(self->getActionTypeFromBox(_itemType, select2));
         if (select1 == _itemType) {
             QString text = self->_actionNameField->text();
             if (text != "" && text.length() > 0) {
                 self->_curAction->setDeviceName(text);
             }
         }
         self->actionItemChanged(_itemType);
         self->initializeActionVariables();
     }
 }
}

//transient ActionListener actionSignalMastNameListener = new ActionListener() {
//    /*public*/ void actionPerformed(ActionEvent e) {
void ConditionalListEdit::actionSignalMastNameListener() // SLOT[]
{
 // fired when signal mast name changes, but only
 // while in signal mast mode
 log->debug("actionSignalMastNameListener fires; _actionNameField : "+_actionNameField->text().trimmed());
 loadJComboBoxWithMastAspects(_actionBox,_actionNameField->text().trimmed());
}
//};

// ------------ Table Models ------------
/**
 * Table model for Conditionals in Edit Logix window
 */
///*public*/ class ConditionalTableModel extends AbstractTableModel implements
//        PropertyChangeListener {


/*public*/ ConditionalTableModel::ConditionalTableModel(QObject* parent) : AbstractTableModel(parent)
{
 //super();
 self = (ConditionalListEdit*)parent;

 ((DefaultConditionalManager*)self->_conditionalManager)->addPropertyChangeListener((PropertyChangeListener*)this);

 updateConditionalListeners();
}

/*synchronized*/ void ConditionalTableModel::updateConditionalListeners()
{
 // first, remove listeners from the individual objects
 QString sNam = "";
 Conditional* c = NULL;
 self->_numConditionals = ((DefaultLogix*)self->_curLogix)->getNumConditionals();
 for (int i = 0; i < self->_numConditionals; i++) {
     // if object has been deleted, it's not here; ignore it
     sNam = ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(i);
     c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(sNam);
     if (c != NULL)
         ((DefaultConditional*)c)->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 // and add them back in
 for (int i = 0; i < self->_numConditionals; i++) {
     sNam = ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(i);
     c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(sNam);
     if (c != NULL)
         ((DefaultConditional*)c)->addPropertyChangeListener((PropertyChangeListener*)this);
     connect(((DefaultConditional*)c)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ void ConditionalTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("length")) {
        // a new NamedBean is available in the manager
        updateConditionalListeners();
        fireTableDataChanged();
    } else if (matchPropertyName(e)) {
        // a value changed.
        fireTableDataChanged();
    }
}

/**
 * Is this property event announcing a change this table should display?
 * <P>
 * Note that events will come both from the NamedBeans and also from the
 * manager
 */
bool ConditionalTableModel::matchPropertyName(PropertyChangeEvent* e) {
    return (e->getPropertyName().indexOf("State") >= 0 || e
            ->getPropertyName().indexOf("Appearance") >= 0);
}

/*public*/ QString ConditionalTableModel::getColumnClass(int c) {
    if (c == BUTTON_COLUMN) {
        return "JButton";
    } else {
        return "String";
    }
}

/*public*/ int ConditionalTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 4;
}

/*public*/ int ConditionalTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return (self->_numConditionals);
}

/*public*/ Qt::ItemFlags ConditionalTableModel::flags(const QModelIndex &index) const
{
 if (!self->_inReorderMode)
 {
  if ((index.column() == UNAME_COLUMN) || (index.column() == BUTTON_COLUMN))
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  else
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

 }
 else if (index.column() == BUTTON_COLUMN)
 {
  if (index.row() >= self->_nextInOrder)
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
     else
     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
 return Qt::NoItemFlags;
}

/*public*/ QVariant ConditionalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section)
    {
    case SNAME_COLUMN:
        return tr("System Name");
    case UNAME_COLUMN:
        return tr("User Name");
    case BUTTON_COLUMN:
        return ""; // no label
    case STATE_COLUMN:
        return tr("State");
    default:
        break;
   }
 }
 return QVariant();
}

///*public*/ int ConditionalTableModel::getPreferredWidth(int col) {
//    switch (col)
//    {
//    case SNAME_COLUMN:
//        return new JTextField(6).getPreferredSize().width();
//    case UNAME_COLUMN:
//        return new JTextField(17).getPreferredSize().width();
//    case BUTTON_COLUMN:
//        return new JTextField(6).getPreferredSize().width();
//    case STATE_COLUMN:
//        return new JTextField(12).getPreferredSize().width();
//    default:
//        return new JTextField(5).getPreferredSize().width();
//    }
//}

/*public*/ QVariant ConditionalTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int rx = index.row();
  if ((rx > self->_numConditionals) || (self->_curLogix == NULL))
  {
   return QVariant();
  }
  switch (index.column())
  {
  case BUTTON_COLUMN:
   if (!self->_inReorderMode)
   {

    return tr("Edit");
   }
   else if (self->_nextInOrder == 0)
   {
    return tr("First");
   }
   else if (self->_nextInOrder <= index.row())
   {
    return tr("Next");
   }
   else
    return rx + 1;
  case SNAME_COLUMN:
    return ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx);
  case UNAME_COLUMN:
  {
            //log->debug("ConditionalTableModel: "+_curLogix.getConditionalByNumberOrder(rx));
   Conditional* c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(
   ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx));
   if (c!=NULL) return ((DefaultConditional*)c)->getUserName();
   else return "";
  }
  case STATE_COLUMN:
  {
   Conditional* c = ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(
            ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx));
    if (c != NULL)
    {
     int curState = ((DefaultConditional*)c)->getState();
     if (curState == Conditional::_TRUE)
        return tr("True");
     if (curState == Conditional::_FALSE)
        return tr("False");
    }
    return tr("Unknown");
   }
   default:
    return tr("Unknown");
  }
 }
 return QVariant();
}

/*public*/ bool  ConditionalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int rx = index.row();
  if ((rx > self->_numConditionals) || (self->_curLogix == NULL))
  {
   return true;
  }
  if (index.column() == BUTTON_COLUMN)
  {
   if (self->_inReorderMode)
   {
       self->swapConditional(index.row());
   }
   else if (((DefaultLogix*)self->_curLogix)->getSystemName()==(SensorGroupFrame::logixSysName))
   {
//            javax.swing.JOptionPane.showMessageDialog(
//                        editConditionalFrame, java.text.MessageFormat.format(tr("Warn8"),
//                        new Object[] {SensorGroupFrame.logixUserName, SensorGroupFrame.logixSysName}),
//                        rbx .getString("WarnTitle"), javax.swing.JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(self->_editConditionalFrame, tr("Warning"), tr("Conditionals in Logix \"%1\" (%2) cannot be edited.\nGo to the Sensor Group Table to edit sensor groups.").arg(SensorGroupFrame::logixUserName).arg(SensorGroupFrame::logixSysName));
   }
   else
   {
#if 0
    // Use separate Thread so window is created on top
    class WindowMaker : public Runnable
    {
     int row;
     WindowMaker(int index.row())
     {
      row = index.row();
     }
     /*public*/ void run()
     {
      //Thread.yield();
      self->editConditionalPressed(row);
     }
    };
    WindowMaker* t = new WindowMaker(rx);
    invokeLater(t);
#endif
    self->editConditionalPressed(index.row());
   }
  }
  else if (index.column() == UNAME_COLUMN)
  {
   QString uName =  value.toString();
   if ( self->_curLogix != NULL)
   {
    Conditional* cn = ((DefaultConditionalManager*)self->_conditionalManager)->getByUserName(self->_curLogix,
            uName.trimmed());
    if (cn == NULL)
    {
     ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(
               ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx))
                ->setUserName(uName.trimmed());
     fireTableRowsUpdated(rx, rx);
    }
    else
    {
     QString svName = ((DefaultLogix*)self->_curLogix)->getConditionalByNumberOrder(rx);
     if (cn != ((DefaultConditionalManager*)self->_conditionalManager)->getBySystemName(svName))
     {
      self->messageDuplicateConditionalUserName(((DefaultConditional*)cn)->getSystemName());
     }
    }
   }
  }
  return true;
 }
 return false;
}

 void ConditionalTableModel::fireTableRowsUpdated(int /*r1*/, int /*r2*/)
 {
  beginResetModel();
  endResetModel();
 }
void ConditionalTableModel::fireTableDataChanged()
{
    beginResetModel();
    endResetModel();

}
void ConditionalTableModel::fireTableRowsInserted(int /*r1*/, int /*r2*/)
{
    beginResetModel();
    endResetModel();
}
void ConditionalTableModel::fireTableRowsDeleted(int /*r1*/, int /*r2*/)
{
    beginResetModel();
    endResetModel();
}

//};

/**
 * Table model for State Variables in Edit Conditional window
 */
///*public*/ class VariableTableModel extends AbstractTableModel {

LVariableTableModel::LVariableTableModel(QObject* parent) : AbstractTableModel(parent)
{
  self = (ConditionalListEdit*) parent;

}

/*public*/ QString LVariableTableModel::getColumnClass(int c) {
    switch (c)
    {
        case ROWNUM_COLUMN:
            return "String";
        case AND_COLUMN:
            return "JComboBox";
        case NOT_COLUMN:
            return "JComboBox";
        case DESCRIPTION_COLUMN:
            return "String";
        case STATE_COLUMN:
            return "String";
        case TRIGGERS_COLUMN:
            return "Boolean";
        case EDIT_COLUMN:
            return "JButton";
        case DELETE_COLUMN:
            return "JButton";
    }
    return "String";
}

/*public*/ int LVariableTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 8;
}

/*public*/ int LVariableTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return self->_variableList->size();
}

/*public*/ Qt::ItemFlags LVariableTableModel::flags(const QModelIndex &index) const
{
 switch (index.column()) {
        case ROWNUM_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case AND_COLUMN:
            if(self->_logicType == Conditional::MIXED )
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
            else
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case NOT_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        case DESCRIPTION_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case STATE_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        case TRIGGERS_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
        case EDIT_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        case DELETE_COLUMN:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

/*public*/ QVariant LVariableTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
  case ROWNUM_COLUMN:
        return (tr("Row"));
  case AND_COLUMN:
        return (tr("Operator"));
  case NOT_COLUMN:
        return (tr("Not"));
  case DESCRIPTION_COLUMN:
        return (tr("Description"));
  case STATE_COLUMN:
        return (tr("State"));
  case TRIGGERS_COLUMN:
        return (tr("Triggers Calculation"));
  case EDIT_COLUMN:
        return "";
  case DELETE_COLUMN:
    return "";
  default:
            break;
    }
 }
 return QVariant();
}

///*public*/ int getPreferredWidth(int col) {
//    if (col == DESCRIPTION_COLUMN) {
//        return 500;
//    }
//    return 10;
//}

/*public*/ QVariant LVariableTableModel::data(const QModelIndex &index, int role) const
{
  int r = index.row();
  int c = index.column();
  if ( r >= self->_variableList->size() )
  {
   return QVariant();
  }
  ConditionalVariable* variable = self->_variableList->at(r);
  if(role == Qt::DisplayRole)
  {
   switch (c)
   {
        case ROWNUM_COLUMN:
            return (tr("R") + QString::number(r + 1));
        case AND_COLUMN:
            if (r==0 || self->_logicType==Conditional::MIXED) {
                return "";
            }
            return variable->getOpernString();
        case NOT_COLUMN:
            if (variable->isNegated())
                return tr("NOT");
            break;
        case DESCRIPTION_COLUMN:
            return variable->toString();
        case STATE_COLUMN:
            switch (variable->getState()) {
                case Conditional::_TRUE:
                    return tr("True");
                case Conditional::_FALSE:
                    return tr("False");
                case Conditional::UNKNOWN:
                    return tr("Unknown");
            }
            break;
        case EDIT_COLUMN:
            return tr("Edit");
        case DELETE_COLUMN:
            return tr("Delete");
        default : break;
    }
  }
  if(role == Qt::CheckStateRole)
  {
   if(index.column() == TRIGGERS_COLUMN)
    return variable->doTriggerActions()?Qt::Checked:Qt::Unchecked;
  }

 return QVariant();
}

/*public*/ bool LVariableTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  int r = index.row();
  int c = index.column();
  if ( r >= self->_variableList->size() )
  {
   return false;
  }
  ConditionalVariable* variable = self->_variableList->at(r);
  if(role == Qt::EditRole )
  {
   switch (c)
   {
    case AND_COLUMN:
     self->variableOperatorChanged(r,value.toString());
     break;
    case NOT_COLUMN:
     self->variableNegationChanged(r, value.toString());
     break;
    case STATE_COLUMN:
    {
     QString state = value.toString();
     if ( state==(tr("true").toUpper().trimmed()) ) {
        variable->setState(Conditional::_TRUE);
     } else  if ( state==(tr("false").toUpper().trimmed()) )  {
        variable->setState(Conditional::_FALSE);
     } else {
        variable->setState(Conditional::UNKNOWN);
     }
     break;
    }

    case TRIGGERS_COLUMN:
     variable->setTriggerActions(!(variable->doTriggerActions()));
     break;
    case EDIT_COLUMN:
    {
     if (/*LRouteTableAction::LOGIX_INITIALIZER*/"RTXINITIALIZER"==(((DefaultLogix*)self->_curLogix)->getSystemName()))
     {
//        javax.swing.JOptionPane.showMessageDialog(editConditionalFrame,
//                tr("Error49"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(self->_editConditionalFrame,tr("Error"),  tr("LRoute Initializer antecedent cannot be edited.  (The actions may be edited)"));
        break;
    }
//    // Use separate Thread so window is created on top
//    class WindowMaker implements Runnable {
//        int row;
//        WindowMaker(int r){
//            row = r;
//        }
//        /*public*/ void run() {
//                //Thread.yield();
//                makeEditVariableWindow(row);
//            }
//        }
//    WindowMaker t = new WindowMaker(r);
//    javax.swing.SwingUtilities.invokeLater(t);
      self->makeEditVariableWindow(r);
      break;
     }
     case DELETE_COLUMN:
      self->deleteVariablePressed(r);
      break;
     default : break;
    }
   return true;
   }
   if(role == Qt::CheckStateRole)
   {
    if(index.column() == TRIGGERS_COLUMN)
    {
     variable->setTriggerActions(!(variable->doTriggerActions()));
     return true;
    }
   }
 return false;
}
void LVariableTableModel::fireTableRowsDeleted(int /*row1*/, int /*row2*/)
{
 beginResetModel();
 endResetModel();
}
void LVariableTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
}
void LVariableTableModel::fireTableRowsInserted(int /*row1*/, int /*row2*/)
{
 beginResetModel();
 endResetModel();
}
void LVariableTableModel::fireTableRowsUpdated(int /*row1*/, int /*row2*/)
{
 beginResetModel();
 endResetModel();
}
//}

/**
 * Table model for Actions in Edit Conditional window
 */
// /*public*/ class ActionTableModel extends AbstractTableModel {

ActionTableModel::ActionTableModel(QObject *parent) : AbstractTableModel(parent)
{
    this->self = (ConditionalListEdit*)parent;
}

/*public*/ QString ActionTableModel::getColumnClass(int c) {
 if (c == EDIT_COLUMN || c ==DELETE_COLUMN )
 {
     return "JButton";
 }
 return AbstractTableModel::getColumnClass(c);
}

/*public*/ int ActionTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}

/*public*/ int ActionTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return self->_actionList->size();
}

/*public*/ Qt::ItemFlags ActionTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == DESCRIPTION_COLUMN)  {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    if ( self->_inReorderMode && (index.column() ==EDIT_COLUMN || index.row() < self->_nextInOrder) ) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

/*public*/ QVariant ActionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if ( section == DESCRIPTION_COLUMN)
    {
        return tr("Action Description");
    }
 }
 return QVariant();
}

//    /*public*/ int getPreferredWidth(int col) {
//        if (col == DESCRIPTION_COLUMN)
//        {
//            return 680;
//        }
//        return 20;
//    }

/*public*/ QVariant ActionTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  if (index.row() >= self->_actionList->size())
  {
   return QVariant();
  }
  switch (index.column())
  {
  case DESCRIPTION_COLUMN:
  {
   ConditionalAction* action = self->_actionList->at(index.row());
   return action->description(self->_triggerOnChangeButton->isChecked());
  }
        case EDIT_COLUMN:
            return tr("Edit");
        case DELETE_COLUMN:
            if (!self->_inReorderMode) {
                return tr("Delete");
            } else if (self->_nextInOrder == 0) {
                return tr("First");
            } else if (self->_nextInOrder <= index.row()) {
                return tr("Next");
            }
      return (index.row() + 1);
    }
 }
 return QVariant();
}

/*public*/ bool  ActionTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
    if (index.column() == EDIT_COLUMN) {
        // Use separate Thread so window is created on top
//        class WindowMaker implements Runnable {
//            int row;
//            WindowMaker(int r){
//                row = r;
//            }
//            /*public*/ void run() {
//                    //Thread.yield();
//                    makeEditActionWindow(row);
//                }
//            }
//        WindowMaker t = new WindowMaker(row);
//        javax.swing.SwingUtilities.invokeLater(t);
        self->makeEditActionWindow(index.row());
    }
    else if (index.column() == DELETE_COLUMN) {
        if (self->_inReorderMode)
            self->swapActions(index.row());
        else
            self->deleteActionPressed(index.row());
    }
 }
 return false;
}
void ActionTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
}
void ActionTableModel::fireTableRowsDeleted(int, int)
{
 beginResetModel();
 endResetModel();
}
void ActionTableModel::fireTableRowsUpdated(int, int)
{
 beginResetModel();
 endResetModel();
}
void ActionTableModel::fireTableRowsInserted(int, int)
{
 beginResetModel();
 endResetModel();
}

//}

/*protected*/ QString ConditionalListEdit::getClassName() {
   // return ConditionalListEdit.class.getName();
 return "jmri.jmrit.conditonal.ConditionalListEdit";
}

/*private*/ /*final*/ /*static*/ Logger* ConditionalListEdit::log = LoggerFactory::getLogger("ConditionalListEdit");

EditLogixFrameWindowListener::EditLogixFrameWindowListener(ConditionalListEdit *self)
{
 this->self = self;
}
void EditLogixFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 if (self->_inEditMode)
 {
  self->donePressed(NULL);
 }
 {
  self->finishDone();
 }
}
