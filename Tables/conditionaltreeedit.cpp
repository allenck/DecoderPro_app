#include "conditionaltreeedit.h"
#include "instancemanager.h"
#include "signalhead.h"
#include "signalheadmanager.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "conditionalaction.h"
#include "defaultconditional.h"
#include "defaultconditionalaction.h"
#include "warrant.h"
#include "conditional.h"
#include <qobject.h>
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "conditionalvariable.h"
#include "oblock.h"
#include "joptionpane.h"
#include "stringutils.h"
#include "userpreferencesmanager.h"
#include "lroutetableaction.h"
#include "box.h"
#include <QSplitter>
#include "flowlayout.h"
#include "defaulttreeselectionmodel.h"
#include "system.h"
#include "htmldelegate.h"
#include "light.h"

/**
 * A tree based editor for maintaining Logix Conditionals, State Variables and
 * Actions.
 * <p>
 * The tree has 3 levels. The first level are the conditionals contained in the
 * selected Logix. The second level contains the antecedent, logic type and
 * trigger mode settings. The third level contains the detail Variable and
 * Action lines.
 *
 * @author Dave Sand copyright (c) 2017
 */
///*public*/ class ConditionalTreeEdit extends ConditionalEditBase {

 /**
  * Constructor to create a Conditional Tree View editor.
  *
  * @param sName The system name of the current Logix
  */
 /*public*/ ConditionalTreeEdit::ConditionalTreeEdit(QString sName, QObject* parent ) : ConditionalEditBase(sName, parent){
     //super(sName);
 _editLogixFrame =  NULL;
 _curDetailPanel = new QWidget();
 _gridPanelLayout = NULL;
 _editLogixUserName = new JTextField(20);   // Logix User Name field

 // ------------ Edit detail components ------------
 _detailGrid = new QWidget();
 _detailGridLayout = new QVBoxLayout(_detailGrid);
 _detailFooter = new QWidget();
 _detailFooterLayout = new QVBoxLayout(_detailFooter);
 _editActive = false;
 _pickCommand =  "";
 _pickItem = 0;

 // ------------ Tree variables ------------
 _curTreePath =  NULL;

 // ------------ Tree components ------------
 _cdlNode =  NULL;
 _varHead =  NULL;
 _varNode =  NULL;
 _actHead =  NULL;
 _actNode =  NULL;
 _leafNode =  NULL;

 // ------------ Current tree node variables ------------
 _curNode =  NULL;
 _curNodeName =  "";
 _curNodeType =  "";
 _curNodeText =  "";
 _curNodeRow = -1;

 _conditionalLabel = new QLabel(tr("Conditional:"));  // NOI18N
 _antecedentLabel = new QLabel(tr("Antecedent:"));  // NOI18N
 _logicTypeLabel = new QLabel(tr("Logic Type:"));  // NOI18N
 _triggerModeLabel = new QLabel(tr("Trigger Mode:"));  // NOI18N
 _variablesLabel = new QLabel(tr("Variables:"));  // NOI18N
 _variableLabel = new QLabel(tr("Variable:"));  // NOI18N
 _actionsLabel = new QLabel(tr("Action:"));  // NOI18N
 _actionLabel = new QLabel(tr("Action:"));  // NOI18N

 // ------------ Current conditional components ------------
 _curVariableItem = 0;
 _curActionItem = 0;
 _curConditionalName = "";
 _newActionItem = false;
 _newVariableItem = false;
 _oldTargetNames = new QSet<QString>();

 // ------------ Select Conditional Variables ------------
 _selectLogixBox = new QComboBox();
 _selectConditionalBox = new QComboBox();
 _selectLogixList = new QList<QString>();
 _selectConditionalList = new QList<QString>();

 // ------------ Components of Edit Variable pane ------------
 _variableNameLabel = new QLabel(tr("System / User Name"));  // NOI18N
 _variableMemoryValueLabel = new QLabel("");

 // ------------ Components of Edit Action pane ------------
 _actionTypeLabel = new QLabel("Type");  // NOI18N
 _actionNameLabel = new QLabel("Name");  // NOI18N
 _actionBoxLabel = new QLabel("Box");  // NOI18N
 _longActionLabel = new QLabel("Long");  // NOI18N
 _shortActionLabel = new QLabel("Short");  // NOI18N

 _actionTypeListener = new CTEActionTypeListener(this);
 actionSignalHeadNameListener = new ActionSignalHeadNameListener(this);
 actionSignalMastNameListener = new ActionSignalMastNameListener(this);
 variableSignalHeadNameListener = new VariableSignalHeadNameListener(this);
 variableSignalMastNameListener = new VariableSignalMastNameListener(this);
 variableSignalTestStateListener = new CTEVariableSignalTestStateListener(this);
 selectLogixBoxListener = new SelectLogixBoxListener(this);
 selectConditionalBoxListener = new SelectConditionalBoxListener(this);
 compareTypeBoxListener = new CompareTypeBoxListener(this);
 sndFileChooser =  NULL;
 scriptFileChooser =  NULL;
 defaultFileChooser =  NULL;


     buildConditionalComponents();
     buildActionComponents();
     buildVariableComponents();
     makeEditLogixWindow();
     setFocusListeners();
     setEditMode(false);
 }

 /*public*/ ConditionalTreeEdit::ConditionalTreeEdit(QObject* parent) : ConditionalEditBase(parent) {
 }

 // ============  Edit conditionals for the current Logix ============
 /**
  * Create the edit logix window.
  * <p>
  * The left side contains a tree structure containing the conditionals for
  * the current Logix. The right side contains detail edit panes based on the
  * current tree row selection.
  */
 void ConditionalTreeEdit::makeEditLogixWindow()
 {
  _editLogixFrame = new JmriJFrameX(tr("Edit Logix"));  // NOI18N
  _editLogixFrame->addHelpMenu(
          "package.jmri.jmrit.conditional.ConditionalTreeEditor", true);  // NOI18N
  QWidget* contentPane = _editLogixFrame->getContentPane();
  //contentPane->setLayout(new BorderLayout());
  QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);

  // ------------ Header ------------
 QWidget* header = new QWidget();
 QVBoxLayout* headerLayout = new QVBoxLayout(header);
 QWidget* logixNames = new QWidget();
  //logixNames->setLayout(new BoxLayout(logixNames, BoxLayout.X_AXIS));
 QHBoxLayout* logixNamesLayout = new QHBoxLayout(logixNames);

  QLabel* systemNameLabel = new QLabel(tr("System Name") + ":");  // NOI18N
  logixNamesLayout->addWidget(systemNameLabel);
  logixNamesLayout->addWidget(Box::createHorizontalStrut(5));

  QLabel* fixedSystemName = new QLabel(_curLogix->getSystemName());
  logixNamesLayout->addWidget(fixedSystemName);
  logixNamesLayout->addWidget(Box::createHorizontalStrut(20));

  QLabel* userNameLabel = new QLabel(tr("User Name") + ":");  // NOI18N
  logixNamesLayout->addWidget(userNameLabel);
  logixNamesLayout->addWidget(Box::createHorizontalStrut(5));

  _editLogixUserName->setText(_curLogix->getUserName());
  logixNamesLayout->addWidget(_editLogixUserName);
  _editLogixUserName->setToolTip(tr("Enter new user name for Logix, e.g. Signal 2 Control"));  // NOI18N
//     _editLogixUserName.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             String uName = _editLogixUserName->text().trimmed();
//             if (!(uName ==  (_curLogix->getUserName()))) {
//                 // user name has changed - check if already in use
//                 if (uName.length() > 0) {
//                     Logix p = _logixManager.getByUserName(uName);
//                     if (p !=  NULL) {
//                         // Logix with this user name already exists
//                         log->error("Failure to update Logix with Duplicate User Name: " // NOI18N
//                                 + uName);
//                         JOptionPane::showMessageDialog(_editLogixFrame,
//                                 tr("Error6"), tr("ErrorTitle"), // NOI18N
//                                 JOptionPane::ERROR_MESSAGE);
//                         return;
//                     }
//                 }
//                 // user name is unique, change it
//                 logixData.clear();
//                 logixData.put("chgUname", uName);  // NOI18N
//                 fireLogixEvent();
//                 _showReminder = true;
//             }
//         }
//     });
  connect(_editLogixUserName, SIGNAL(editingFinished()), this, SLOT(on_editLogixUserName_editingFinished()));
  headerLayout->addWidget(logixNames);
  contentPaneLayout->addWidget(header, 0, Qt::AlignTop); //BorderLayout.NORTH);

  // ------------ body - tree (left side) ------------
  JTree* treeContent = buildConditionalTree();
//     JScrollPane treeScroll = new JScrollPane(treeContent);

  // ------------ body - detail (right side) ------------
 QWidget* detailPane = new QWidget();
// TODO:     detailPane->setBorder(BorderFactory.createMatteBorder(0, 2, 0, 0, Color.DARK_GRAY));
  //detailPane->setLayout(new BoxLayout(detailPane, BoxLayout.Y_AXIS));
 QVBoxLayout* detailPaneLayout = new QVBoxLayout(detailPane);

  // ------------ Edit Detail Panel ------------
  makeDetailGrid("EmptyGrid");  // NOI18N

 QWidget* panel = new QWidget();
  //panel->setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);

  _cancelAction = new QPushButton(tr("Cancel"));  // NOI18N
  _cancelAction->setToolTip(tr("Close without saving the add/edit changes"));  // NOI18N
  panelLayout->addWidget(_cancelAction);
//     _cancelAction.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             cancelPressed();
//         }
//     });
  connect(_cancelAction, SIGNAL(clicked(bool)), this, SLOT(cancelPressed()));
  panelLayout->addWidget(Box::createHorizontalStrut(10));

  _updateAction = new QPushButton(tr("Update"));  // NOI18N
  _updateAction->setToolTip(tr("Press to keep changes and return to Edit Conditional"));  // NOI18N
  panelLayout->addWidget(_updateAction);
//     _updateAction.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             updatePressed();
//         }
//     });
  connect(_updateAction, SIGNAL(clicked(bool)), this, SLOT(updatePressed()));
  _detailFooterLayout->addWidget(panel);

 QWidget* detailEdit = new QWidget();//new BorderLayout());
 QVBoxLayout* detailEditLayout = new QVBoxLayout(detailEdit);
  detailEditLayout->addWidget(_detailGrid, 0, Qt::AlignTop);;//BorderLayout.NORTH);
  detailEditLayout->addWidget(_detailFooter,  0, Qt::AlignBottom);//BorderLayout.SOUTH);
  detailPaneLayout->addWidget(detailEdit);
  _editLogixUserName->setEnabled(true);

  QSplitter* bodyPane = new QSplitter(Qt::Horizontal);
  bodyPane->insertWidget(0,treeContent);
  bodyPane->insertWidget(1,detailPane);
//     bodyPane->setDividerSize(10);
//     bodyPane->setResizeWeight(.35);
//     bodyPane->setOneTouchExpandable(true);
  contentPaneLayout->addWidget(bodyPane);

  // ------------ footer ------------
 QWidget* footer = new QWidget();//new BorderLayout());
 QHBoxLayout* footerLayout = new QHBoxLayout(footer);
  _labelPanel = new QWidget();
  _labelPanelLayout = new FlowLayout(_labelPanel);
  _labelPanelLayout->addWidget(_conditionalLabel);
  _leftButtonBar = new QWidget();
  QHBoxLayout* _leftButtonBarLayout = new QHBoxLayout(_leftButtonBar);
  _leftButtonBarLayout->addWidget(_labelPanel);

  // ------------ Add Button ------------
  QPushButton* addButton = new QPushButton(tr("Add"));    // NOI18N
  addButton->setToolTip(tr("Add a new item"));       // NOI18N
//     addButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             addPressed();
//         }
//     });
  connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addPressed()));
  _addButtonPanel = new QWidget();
  FlowLayout* _addButtonPanelLayout = new FlowLayout(_addButtonPanel);
  _addButtonPanelLayout->addWidget(addButton);
  _leftButtonBarLayout->addWidget(_addButtonPanel);

  // ------------ Help Button ------------
  QPushButton* helpButton = new QPushButton(tr("Help"));  // NOI18N
  helpButton->setToolTip(tr("Open a help window with detail Antecedent instructions"));     // NOI18N
//     helpButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             helpPressed();
//         }
//     });
  connect(helpButton, SIGNAL(clicked(bool)), this, SLOT(helpPressed()));
  _helpButtonPanel = new QWidget();
  FlowLayout* _helpButtonPanelLayout = new FlowLayout(_helpButtonPanel);
  _helpButtonPanelLayout->addWidget(helpButton);
  _helpButtonPanel->setVisible(false);
  _leftButtonBarLayout->addWidget(_helpButtonPanel);

  // ------------ Toggle Button ------------
  QPushButton* toggleButton = new QPushButton(tr("Toggle"));  // NOI18N
  toggleButton->setToolTip(tr("Toggle the Action trigger mode"));     // NOI18N
//     toggleButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             togglePressed();
//         }
//     });
  connect(toggleButton, SIGNAL(clicked(bool)), this, SLOT(togglePressed()));
  _toggleButtonPanel = new QWidget();
  FlowLayout* _toggleButtonPanelLayout = new FlowLayout(_toggleButtonPanel);
  _toggleButtonPanelLayout->addWidget(toggleButton);
  _toggleButtonPanel->setVisible(false);
  _leftButtonBarLayout->addWidget(_toggleButtonPanel);

  // ------------ Check Button ------------
  QPushButton* checkButton = new QPushButton(tr("Check State"));  // NOI18N
  checkButton->setToolTip(tr("Update the state"));     // NOI18N
//     checkButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             checkPressed();
//         }
//     });
  connect(checkButton, SIGNAL(clicked()), this, SLOT(checkPressed()));
  _checkButtonPanel = new QWidget();
  FlowLayout* _checkButtonPanelLayout = new FlowLayout(_checkButtonPanel);
  _checkButtonPanelLayout->addWidget(checkButton);
  _checkButtonPanel->setVisible(true);
  _leftButtonBarLayout->addWidget(_checkButtonPanel);

  // ------------ Delete Button ------------
  QPushButton* deleteButton = new QPushButton(tr("Delete")); // NOI18N
  deleteButton->setToolTip(tr("Delete the selected item"));    // NOI18N
//     deleteButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             deletePressed();
//         }
//     });
  connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deletePressed()));
  _deleteButtonPanel = new QWidget();
  FlowLayout* _deleteButtonPanelLayout = new FlowLayout(_deleteButtonPanel);
  _deleteButtonPanelLayout->addWidget(deleteButton);
  _deleteButtonPanel->setVisible(false);
  _leftButtonBarLayout->addWidget(_deleteButtonPanel);

  footerLayout->addWidget(_leftButtonBar, 0, Qt::AlignLeft); //BorderLayout.WEST);
 QWidget* rightButtonBar = new QWidget();
 FlowLayout* rightButtonBarLayout = new FlowLayout(rightButtonBar);

  // ------------ Move Buttons ------------
  QLabel* moveLabel = new QLabel(tr("Move:"));      // NOI18N

  upButton = new QPushButton(tr("Up"));      // NOI18N
  upButton->setToolTip(tr("Move the selected item up one row"));         // NOI18N
  downButton = new QPushButton(tr("Down"));  // NOI18N
  downButton->setToolTip(tr("Move the selected item down one row"));     // NOI18N

//     upButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             downButton->setEnabled(false);
//             upButton->setEnabled(false);
//             upPressed();
//         }
//     });
 connect(upButton, SIGNAL(clicked()), this, SLOT(on_upButton_clicked()));
//     downButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             upButton->setEnabled(false);
//             downButton->setEnabled(false);
//             downPressed();
//         }
//     });
   connect(downButton, SIGNAL(clicked(bool)), this, SLOT(on_downButton_clicked()));
  _moveButtonPanel = new QWidget();
  QHBoxLayout* _moveButtonPanelLayout = new QHBoxLayout(_moveButtonPanel);
  _moveButtonPanelLayout->addWidget(moveLabel);
  _moveButtonPanelLayout->addWidget(upButton);
  _moveButtonPanelLayout->addWidget(new QLabel("|"));
  _moveButtonPanelLayout->addWidget(downButton);
  _moveButtonPanel->setVisible(false);
  _leftButtonBarLayout->addWidget(_moveButtonPanel);

  // ------------ Done Button ------------
  QPushButton* doneButton = new QPushButton(tr("Done"));  // NOI18N
  doneButton->setToolTip(tr("Press to save any user name changes and return to Logix Table"));     // NOI18N
//     doneButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             donePressed();
//         }
//     });
  connect(doneButton, SIGNAL(clicked(bool)), this, SLOT(donePressed()));
 QWidget* doneButtonPanel = new QWidget();
 FlowLayout* doneButtonPanelLayout = new FlowLayout(doneButtonPanel);
  doneButtonPanelLayout->addWidget(doneButton);
  rightButtonBarLayout->addWidget(doneButtonPanel);

  footerLayout->addWidget(rightButtonBar, 0, Qt::AlignLeft); //BorderLayout.EAST);
  contentPaneLayout->addWidget(footer, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
// TODO:
//     _editLogixFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//         //@Override
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             donePressed();
//         }
//     });
  _editLogixFrame->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
  _editLogixFrame->pack();
  _editLogixFrame->setVisible(true);
 }

 void ConditionalTreeEdit::on_editLogixUserName_editingFinished()
 {
  QString uName = _editLogixUserName->text().trimmed();
  if (!(uName ==  (_curLogix->getUserName()))) {
      // user name has changed - check if already in use
      if (uName.length() > 0) {
          Logix* p = (Logix*)_logixManager->getByUserName(uName);
          if (p !=  NULL) {
              // Logix with this user name already exists
              log->error("Failure to update Logix with Duplicate User Name: " // NOI18N
                      + uName);
              JOptionPane::showMessageDialog(_editLogixFrame,
                      tr("New user name is already in use. Cannot update this Logix.\nPlease change user name and try again."), tr("ErrorTitle"), // NOI18N
                      JOptionPane::ERROR_MESSAGE);
              return;
          }
      }
      // user name is unique, change it
      logixData->clear();
      logixData->insert("chgUname", uName);  // NOI18N
      fireLogixEvent();
      _showReminder = true;
  }

 }

 /**
  * Initialize conditional components
  */
 void ConditionalTreeEdit::buildConditionalComponents() {
     _editConditionalUserName = new JTextField(20);
     _editAntecedent = new JTextField(20);
     QStringList l = QStringList();
     l << "AND" << "OR" <<"Mixed";

     _editOperatorMode = new QComboBox(); //<>(new String[]{
//             tr("LogicAND"), // NOI18N
//             tr("LogicOR"), // NOI18N
//             tr("LogicMixed")});  // NOI18N
     _editOperatorMode->addItems(l);
 }

 void ConditionalTreeEdit::on_upButton_clicked()
 {
               downButton->setEnabled(false);
               upButton->setEnabled(false);
               upPressed();
}

 void ConditionalTreeEdit::on_downButton_clicked()
 {
               upButton->setEnabled(false);
               downButton->setEnabled(false);
               downPressed();
}
 // ------------ Create Conditional GridBag panels ------------
 /**
  * Build new GridBag content The grid panel is hidden, emptied, re-built and
  * made visible
  *
  * @param gridType The type of grid to create
  */
 void ConditionalTreeEdit::makeDetailGrid(QString gridType) {
     _detailGrid->setVisible(false);
     //_detailGrid.removeAll();
     clearLayout(_detailGridLayout, true);
     _detailFooter->setVisible(true);

     _gridPanel = new QWidget(/*_gridPanelLayout = new GridBagLayout()*/);
     _gridPanel->setLayout(_gridPanelLayout = new GridBagLayout());
     GridBagConstraints c = /*new*/ GridBagConstraints();
     c.gridwidth = 1;
     c.gridheight = 1;
     c.ipadx = 5;

     if(gridType == "EmptyGrid")  // NOI18N
     {
             makeEmptyGrid(c);
             _detailFooter->setVisible(false);
     }
         // ------------ Conditional Edit Grids ------------
     else if(gridType ==  "Conditional")  // NOI18N
             makeConditionalGrid(c);
     else if(gridType ==  "Antecedent")  // NOI18N
             makeAntecedentGrid(c);
     else if(gridType ==  "LogicType")  // NOI18N
             makeLogicTypeGrid(c);


         // ------------ Variable Edit Grids ------------
     else if(gridType == "EmptyVariable")  // NOI18N
             makeEmptyVariableGrid(c);
       else if(gridType == "StandardVariable")  // NOI18N
             makeStandardVariableGrid(c);
        else if(gridType == "SignalAspectVariable")  // NOI18N
             makeSignalAspectVariableGrid(c);
        else if(gridType == "ConditionalVariable")  // NOI18N
             makeConditionalVariableGrid(c);
        else if(gridType == "MemoryVariable")  // NOI18N
             makeMemoryVariableGrid(c);
          else if(gridType == "FastClockVariable")  // NOI18N
             makeFastClockVariableGrid(c);


         // ------------ Action Edit Grids ------------
          else if(gridType =="EmptyAction")  // NOI18N
             makeEmptyActionGrid(c);
          else if(gridType == "NameTypeAction")  // NOI18N
             makeNameTypeActionGrid(c, false);   // Skip change/trigger row
          else if(gridType == "NameTypeActionFinal")  // NOI18N
             makeNameTypeActionGrid(c, true);    // Include change/trigger row
          else if(gridType == "TypeAction")  // NOI18N
             makeTypeActionGrid(c, false);       // Skip change/trigger row
          else if(gridType == "TypeActionFinal")  // NOI18N
             makeTypeActionGrid(c, true);        // Include change/trigger row
          else if(gridType == "TypeShortAction")  // NOI18N
             makeTypeShortActionGrid(c);
           else if(gridType == "StandardAction")  // NOI18N
             makeStandardActionGrid(c, true);    // Include change/trigger row
          else if(gridType == "ShortFieldAction")  // NOI18N
             makeShortFieldActionGrid(c, true);  // Include Action Box
          else if(gridType == "ShortFieldNoBoxAction")  // NOI18N
             makeShortFieldActionGrid(c, false); // Skip Action Box
          else if(gridType == "FileAction")  // NOI18N
             makeFileActionGrid(c);
         else
     {
             log->warn(tr("Invalid grid type: '%1'").arg(gridType));  // NOI18N
             makeEmptyGrid(c);
     }

     _detailGridLayout->addWidget(_gridPanel);
     _detailGrid->setVisible(true);
 }

 /**
  * This grid is used when there are no edit grids required
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeEmptyGrid(GridBagConstraints c) {
     // Variable type box
     c.gridy = 0;
     c.gridx = 0;
     c.anchor = GridBagConstraints::CENTER;
     QLabel* row0Label = new QLabel("This page is intentionally blank");  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
 }

 /**
  * This grid is used to edit the Conditional User Name
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeConditionalGrid(GridBagConstraints c) {
     c.gridy = 0;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row0Label = new QLabel(tr("Conditional User Name"));  // NOI18N
     row0Label->setToolTip(tr("Enter User Name for Conditional, e.g. 'Signal 2 Red'"));  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_editConditionalUserName, c);
 }

 /**
  * This grid is used to edit the Antecedent when the Logic Type is Mixed
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeAntecedentGrid(GridBagConstraints c) {
     c.gridy = 0;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row0Label = new QLabel(tr("Antecedent Logic"));  // NOI18N
     row0Label->setToolTip(tr("Insert parenthesis so the statement satisfies the logic you want"));  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_editAntecedent, c);
 }

 /**
  * This grid is used to edit the Logic Type
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeLogicTypeGrid(GridBagConstraints c) {
     c.gridy = 0;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row0Label = new QLabel(tr("Logic Operator"));  // NOI18N
     row0Label->setToolTip(tr("Choose logic operator joining state variables for the antecedent ('if' part) of this conditional"));  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_editOperatorMode, c);
 }

 // ------------ Process button bar and tree events ------------
 /**
  * Add new items: Conditionals, Variables or Actions
  */
 void ConditionalTreeEdit::addPressed()
 {
  if (_curNode ==  NULL)
  {
   // New conditional with no prior selection
   _curNodeType = "Conditional";  // NOI18N
  }

  if (_curNodeType == "Conditional")     // NOI18N
  {
   // make system name for new conditional
   int num = _curLogix->getNumConditionals() + 1;
   _curConditional =  NULL;
   QString cName =  NULL;
   while (_curConditional ==  NULL)
   {
    cName = _curLogix->getSystemName() + "C" + QString::number(num);
    _curConditional = _conditionalManager->createNewConditional(cName, "");
    num++;
    if (num == 1000)
    {
     break;
    }
   }
   if (_curConditional ==  NULL)
   {
    // should never get here unless there is an assignment conflict
    log->error(tr("Failure to create Conditional with System Name: %1").arg(cName));  // NOI18N
    return;
   }
   // add to Logix at the end of the calculate order
   _curLogix->addConditional(cName, -1);
   _actionList = new QList<ConditionalAction*>();
   _variableList = new QList<ConditionalVariable*>();
   _curConditional->setAction(_actionList);
   _curConditional->setStateVariables(_variableList);
   _showReminder = true;

   // Build tree components
   Conditional* curConditional = _curLogix->getConditional(cName);
   _curNode = new ConditionalTreeNode(buildNodeText("Conditional", curConditional, 0), "Conditional", cName, // NOI18N
           _curLogix->getNumConditionals() - 1);
   _cdlRoot->add(_curNode);
   _leafNode = new ConditionalTreeNode(buildNodeText("Antecedent", curConditional, 0), "Antecedent", cName, 0);   // NOI18N
   _curNode->add(_leafNode);
   _varHead = new ConditionalTreeNode(buildNodeText("Variables", curConditional, 0), "Variables", cName, 0);     // NOI18N
   _curNode->add(_varHead);
   _leafNode = new ConditionalTreeNode(buildNodeText("LogicType", curConditional, 0), "LogicType", cName, 0);      // NOI18N
   _curNode->add(_leafNode);
   _triggerMode = curConditional->getTriggerOnChange();
   _leafNode = new ConditionalTreeNode(buildNodeText("TriggerMode", curConditional, 0), "TriggerMode", cName, 0);      // NOI18N
   _curNode->add(_leafNode);
   _actHead = new ConditionalTreeNode(buildNodeText("Actions", curConditional, 0), "Actions", cName, 0);      // NOI18N
   _curNode->add(_actHead);
   _cdlModel->nodeStructureChanged(_cdlRoot);

   // Switch to new node
   QVector<TreeNode*>* path = _curNode->getPath();
   QVector<QObject*>* pathList = new QVector<QObject*>();
   for(TreeNode* node : *path) { pathList->append((QObject*)node);}
   _cdlTree->setSelectionPath(new TreePath(pathList));
  }
  else if (_curNodeType ==  "Variables")    // NOI18N
  {
   newVariable();
  }
  else if (_curNodeType == "Variable")     // NOI18N
  {
   newVariable();
  }
  else if (_curNodeType == "Actions")    // NOI18N
  {
   newAction();
  }
  else if (_curNodeType == "Action")    // NOI18N
  {
   newAction();
  }
  else
  {
   log->error(tr("Add called for unsupported node type: %1").arg(_curNodeType));  // NOI18N
  }
  ((DefaultTreeModel*)_cdlTree->model())->reload();
 }

 /**
  * Create a new variable Can be invoked by a Variables or Variable node
  */
 void ConditionalTreeEdit::newVariable() {
     if (LRouteTableAction::LOGIX_INITIALIZER ==  (_curLogix->getSystemName())) {
         JOptionPane::showMessageDialog(_editLogixFrame,
                 tr("LRoute Initializer antecedent cannot be edited (The actions may be edited)"), tr("ErrorTitle"), // NOI18N
                 JOptionPane::ERROR_MESSAGE);
         return;
     }

     cancelPressed();    // Make sure that there are no active edit sessions
     _showReminder = true;
     _curVariableItem = 0;
     ConditionalVariable* variable = new ConditionalVariable();
     _variableList->append(variable);
     _newVariableItem = true;
     setMoveButtons();   // Buttons will be disabled

     int size = _variableList->size();
     _curVariable = _variableList->value(size - 1);
     // default of operator for position 0 (row 1) is Conditional::OPERATOR_NONE
     if (size > 1) {
         if (_logicType == Conditional::ALL_OR) {
             _curVariable->setOpern(Conditional::OPERATOR_OR);
         } else {
             _curVariable->setOpern(Conditional::OPERATOR_AND);
         }
     }
     appendToAntecedent(_curVariable);
     size--;

     // Update tree structure
     if (_curNodeType ==  ("Variables")) {  // NOI18N
         _varHead = _curNode;
     } else {
         _varHead = (ConditionalTreeNode*) _curNode->getParent();
     }
     _leafNode = new ConditionalTreeNode(buildNodeText("Variable", _curVariable, size), "Variable", _curNodeName, size);  // NOI18N
     _varHead->add(_leafNode);
     _cdlModel->nodeStructureChanged(_curNode);
     _varHead->setRow(size + 1);
     _cdlModel->nodeStructureChanged(_varHead);

     // Switch to new node
     ConditionalTreeNode* tempNode = (ConditionalTreeNode*) _varHead->getLastChild();
     QVector<TreeNode*>* path = tempNode->getPath();
     QVector<QObject*>* pathList = new QVector<QObject*>();
     for(TreeNode* node : *path) { pathList->append((QObject*)node);}
     TreePath* newPath = new TreePath(pathList);
     _cdlTree->setSelectionPath(newPath);
     _cdlTree->expandPath(newPath);
 }

 /**
  * Create a new action Can be invoked by a Actions or Action node
  */
 void ConditionalTreeEdit::newAction()
 {
     cancelPressed();    // Make sure that there are no active edit sessions
     _showReminder = true;
     _curActionItem = 0;
     ConditionalAction* action = new DefaultConditionalAction();
     _actionList->append(action);
     _newActionItem = true;
     setMoveButtons();   // Buttons will be disabled

     int size = _actionList->     size();
     _curAction = _actionList->     value(size - 1);
     size--;

     // Update tree structure
     if (_curNodeType ==  ("Actions"))
     {  // NOI18N
      _actHead = _curNode;
     }
     else
     {
      _actHead = (ConditionalTreeNode*) _curNode->getParent();
     }
     _leafNode = new ConditionalTreeNode(buildNodeText("Action", _curAction, size), "Action", _curNodeName, size);  // NOI18N
     _actHead->add(_leafNode);
     _cdlModel->nodeStructureChanged(_curNode);
     _actHead->setRow(size + 1);
     _cdlModel->nodeStructureChanged(_actHead);

     // Switch to new node
     ConditionalTreeNode* tempNode = (ConditionalTreeNode*) _actHead->getLastChild();
     QVector<TreeNode*>* path = tempNode->getPath();
     QVector<QObject*>* pathList = new QVector<QObject*>();
     for(TreeNode* node : *path) { pathList->append((QObject*)node);}
     TreePath* newPath = new TreePath(pathList);
     _cdlTree->setSelectionPath(newPath);
     _cdlTree->expandPath(newPath);
 }

 /**
  * Setup the edit environment for the selected node Called from
  * {@link #treeRowSelected} This takes the place of an actual button
  */
 void ConditionalTreeEdit::editPressed()
 {
  if (_curNodeType == "Conditional")     // NOI18N
  {
   _editConditionalUserName->setText(_curConditional->getUserName());
   makeDetailGrid("Conditional");  // NOI18N
  }
  else if (_curNodeType == "Antecedent")     // NOI18N
  {
   int chkLogicType = _curConditional->getLogicType();
   if (chkLogicType != Conditional::MIXED) {
       makeDetailGrid("EmptyGrid");  // NOI18N
       return;
   }
   _labelPanelLayout->addWidget(_antecedentLabel);
   _helpButtonPanel->setVisible(true);
   _editAntecedent->setText(_curConditional->getAntecedentExpression());
   makeDetailGrid("Antecedent");  // NOI18N
  }
  else if (_curNodeType ==  "LogicType")      // NOI18N
  {
   int curLogicType = _curConditional->getLogicType();
   _editOperatorMode->setCurrentIndex(curLogicType - 1);
   makeDetailGrid("LogicType");  // NOI18N
  }
  else if (_curNodeType ==  "Variable")     // NOI18N
  {
   _labelPanelLayout->addWidget(_variableLabel);
   _curVariable = _variableList->value(_curNodeRow);
   _curVariableItem = Conditional::TEST_TO_ITEM[_curVariable->getType()];
   initializeStateVariables();
   if (_logicType != Conditional::MIXED) {
       setMoveButtons();
   }
   _oldTargetNames->clear();
   loadReferenceNames(*_variableList, *_oldTargetNames);
  }
  else if (_curNodeType ==  "Action")     // NOI18N
  {
    _labelPanelLayout->addWidget(_actionLabel);
    _curAction = _actionList->     value(_curNodeRow);
    _actionOptionBox->clear();
    for (int i = 1; i <= Conditional::NUM_ACTION_OPTIONS; i++) {
        _actionOptionBox->addItem(DefaultConditionalAction::getOptionString(i, _triggerMode));
    }
    _curActionItem = Conditional::ACTION_TO_ITEM[_curAction->getType()];
    initializeActionVariables();
    setMoveButtons();
  }
  else
   log->error(tr("Edit called for unsupported node type: '%1'").arg(_curNodeType));  // NOI18N
 }

 /**
  * Apply the updates to the current node
  */
 void ConditionalTreeEdit::updatePressed() {
     if(_curNodeType == "Conditional")    // NOI18N
     {
      userNameChanged(_editConditionalUserName->text().trimmed());
     }
     else if(_curNodeType ==  "Antecedent")      // NOI18N
     {
       antecedentChanged(_editAntecedent->text().trimmed());
     }
       else if(_curNodeType == "LogicType")      // NOI18N
     {
       logicTypeChanged(_editOperatorMode->currentIndex() + 1);
     }
     else if(_curNodeType == "Variable")       // NOI18N
     {
      updateVariable();
     }
     else if(_curNodeType ==  "Action")         // NOI18N
     {
      log->warn("Invalid update button press");  // NOI18N
     }
     setEditMode(false);
     _cdlTree->setSelectionPath(_curTreePath);
//     _cdlTree.grabFocus();
 }

 /**
  * Change the conditional user name
  *
  * @param newName The proposed new name
  */
 void ConditionalTreeEdit::userNameChanged(QString newName)
 {
  // Check if the User Name has been changed
  if (newName !=  (_curConditional->getUserName()))
  {
   // user name has changed - check if already in use
   if (!checkConditionalUserName(newName, _curLogix)) {
       return;
   }
   // user name is unique or blank, change it
   _curConditional->setUserName(newName);
   _curNode->setText(buildNodeText("Conditional", _curConditional, 0));  // NOI18N
   _cdlModel->nodeChanged(_curNode);

   // Update any conditional references
   QList<QString> refList = _conditionalManager->getWhereUsed(_curNodeName);
   if (!refList.isEmpty())
   {
    for (QString ref : refList)
    {
     Conditional* cRef = _conditionalManager->getBySystemName(ref);
     QList<ConditionalVariable*>* varList = cRef->getCopyOfStateVariables();
     int idx = 0;
     for (ConditionalVariable* var : *varList)
     {
      // Find the affected conditional variable
      if (var->getName() ==  (_curNodeName))
      {
       if (newName.length() > 0) {
           var->setGuiName(newName);
       } else {
           var->setGuiName(_curNodeName);
       }

       // Is the reference (ref) in the same Logix as the target (_curNodeName)
       // Skip any cross conditional references
       QString varLogixName = _conditionalManager->getParentLogix(ref)->getSystemName();
       QString curLogixSName = _curLogix->getSystemName();
       if (varLogixName ==  (curLogixSName))
       {
        // Yes, update the tree node
        int cdlCount = _cdlRoot->getChildCount();
        for (int j = 0; j < cdlCount; j++)
        {
         // See if a conditional node contains a reference
         ConditionalTreeNode* cdlNode = (ConditionalTreeNode*) _cdlRoot->getChildAt(j);
         if (cdlNode->getName() ==  (ref))
         {
          // The affected variable node will be down 2 levels
          ConditionalTreeNode* variables = (ConditionalTreeNode*) cdlNode->getChildAt(1);
          ConditionalTreeNode* variable = (ConditionalTreeNode*) variables->getChildAt(idx);
          variable->setText(buildNodeText("Variable", var, idx));    // NOI18N
          _cdlModel->nodeChanged(variable);
         }
        }
       }
      }
      idx++;
     }
     // Commit the changes
     cRef->setStateVariables(varList);
     // Refresh the local copy in case cRef was a parallel copy
     _variableList = _curConditional->getCopyOfStateVariables();
    }
   }
  }
 }

 /**
  * Respond to a change of Logic Type in the dialog window by showing/hiding
  * the _antecedentPanel when Mixed is selected.
  *
  * @param newType The selected logic type
  */
 //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::logicTypeChanged(int newType) {
     if (_logicType == newType) {
         return;
     }

     makeAntecedent();
     int oper;
     if (newType != Conditional::MIXED) {
         oper = Conditional::OPERATOR_OR;
         if (newType == Conditional::ALL_AND) {
             oper = Conditional::OPERATOR_AND;
         }

         // Update the variable list and tree node entries
         ConditionalTreeNode* varHead = (ConditionalTreeNode*) _curNode->getPreviousSibling();
         for (int i = 1; i < _variableList->size(); i++) {
             ConditionalVariable* curVar = _variableList->value(i);
             curVar->setOpern(oper);

             ConditionalTreeNode* varNode = (ConditionalTreeNode*) varHead->getChildAt(i);
             varNode->setText(buildNodeText("Variable", curVar, i));
             _cdlModel->nodeChanged(varNode);
         }
     }

     // update LogicType entry and tree node
     _curConditional->setLogicType(newType, _antecedent);
     _logicType = newType;
     _curNode->setText(buildNodeText("LogicType", _curConditional, 0));  // NOI18N
     _cdlModel->nodeChanged(_curNode);

     // update the variables list
     _curConditional->setStateVariables(_variableList);

     // Update antecedent node text
     ConditionalTreeNode* parentNode = (ConditionalTreeNode*) _curNode->getParent();
     ConditionalTreeNode* antNode = (ConditionalTreeNode*) parentNode->getFirstChild();
     if (antNode->getType() ==  ("Antecedent")) {  // NOI18N
         antNode->setText(buildNodeText("Antecedent", _curConditional, 0));  // NOI18N
         _cdlModel->nodeChanged(antNode);
     } else {
         log->warn("Unable to find the antecedent node");  // NOI18N
     }
 }

 /**
  * Update the antecedent.
  *
  * @param newAntecedent the new antecedent
  */
 void ConditionalTreeEdit::antecedentChanged(QString newAntecedent)
 {
  _antecedent = newAntecedent;
  if (validateAntecedent()) {
      _curConditional->setLogicType(_logicType, _antecedent);
      _curNode->setText(buildNodeText("Antecedent", _curConditional, 0));  // NOI18N
      _cdlModel->nodeChanged(_curNode);
  }
 }

 /**
  * Build the antecedent statement.
  */
 void ConditionalTreeEdit::makeAntecedent()
 {
     QString str = "";
     if (_variableList->size() > 0)
     {
         QString _not = tr("NOT").toLower();   // NOI18N
         QString row = "R"; // NOI18N
         QString _and = " " + tr("AND").toLower() + " ";  // NOI18N
         QString _or = " " + tr("OR").toLower() + " ";    // NOI18N
         if (_variableList->value(0)->isNegated()) {
             str = _not + " ";
         }
         str = str + row + "1";
         for (int i = 1; i < _variableList->size(); i++) {
             ConditionalVariable* variable = _variableList->value(i);
             switch (variable->getOpern()) {
                 case Conditional::OPERATOR_AND:
                     str = str + _and;
                     break;
                 case Conditional::OPERATOR_OR:
                     str = str + _or;
                     break;
                 default:
                     break;
             }
             if (variable->isNegated()) {
                 str = str + _not + " ";
             }
             str = str + row + (i + 1);
             if (i > 0 && i + 1 < _variableList->size()) {
                 str = "(" + str + ")";
             }
         }
     }
     _antecedent = str;
 }

 /**
  * Add a part to the antecedent statement.
  *
  * @param variable the current Conditional Variable, ignored in method
  */
 //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::appendToAntecedent(ConditionalVariable* variable) {
     if (_variableList->size() > 1) {
         if (_logicType == Conditional::OPERATOR_OR) {
             _antecedent = _antecedent + " " + tr("OR").toLower() + " ";   // NOI18N
         } else {
             _antecedent = _antecedent + " " + tr("AND").toLower() + " ";  // NOI18N
         }
     }
     _antecedent = _antecedent + "R" + QString::number(_variableList->size()); // NOI18N
     _curConditional->setLogicType(_logicType, _antecedent);

     // Update antecedent node text
     ConditionalTreeNode* antNode;
     if (_curNodeType ==  ("Variables")) {  // NOI18N
         antNode = (ConditionalTreeNode*) _curNode->getPreviousSibling();
     } else {
         antNode = (ConditionalTreeNode*) ((ConditionalTreeNode*) _curNode->getParent())->getPreviousSibling();
     }

     if (antNode->getType() ==  ("Antecedent")) {  // NOI18N
         antNode->setText(buildNodeText("Antecedent", _curConditional, 0));  // NOI18N
         _cdlModel->nodeChanged(antNode);
     } else {
         log->warn("Unable to find the antecedent node");  // NOI18N
     }
 }

 /**
  * Check the antecedent and logic type.
  *
  * @return false if antecedent can't be validated
  */
bool ConditionalTreeEdit::validateAntecedent() {
     if (_logicType != Conditional::MIXED || LRouteTableAction::LOGIX_INITIALIZER ==  (_curLogix->getSystemName())) {
         return false;
     }
     if (_antecedent ==  NULL || _antecedent.length() == 0) {
         // Create a default antecedent
         makeAntecedent();
     }
     if (_antecedent.length() > 0) {
         QString message = _curConditional->validateAntecedent(_antecedent, *_variableList);
         if (!message.isEmpty()) {
             JOptionPane::showMessageDialog(_editLogixFrame,
                     message + tr("\nIf the above message is 'String index out of range:', the following number is the position in the antecedent where the error occurred."), tr("ErrorTitle"), // NOI18N
                     JOptionPane::ERROR_MESSAGE);
             return false;
         }
     }
     return true;
 }

 /**
  * Update the Actions trigger mode, adjust the Action descriptions
  */
 //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::togglePressed()
 {
  // Toggle the trigger mode
  _curLogix->deActivateLogix();
  _curConditional->setTriggerOnChange(!_curConditional->getTriggerOnChange());
  _triggerMode = _curConditional->getTriggerOnChange();
  _curLogix->activateLogix();

  // Update node text
  _curNode->setText(buildNodeText("TriggerMode", _curConditional, 0));  // NOI18N
  _cdlModel->nodeChanged(_curNode);

  // refresh the action list to get the updated action descriptions
  _actionList = _curConditional->getCopyOfActions();
  // get next sibling and update the children node text
  ConditionalTreeNode* actionsNode = (ConditionalTreeNode*) _curNode->getNextSibling();
  for (int i = 0; i < _actionList->size(); i++) {
      ConditionalAction* action = _actionList->     value(i);
      ConditionalTreeNode* actNode = (ConditionalTreeNode*) actionsNode->getChildAt(i);
      actNode->setText(action->description(_triggerMode));
      _cdlModel->nodeChanged(actNode);
  }
 }

 /**
  * Refresh the Conditional or Variable state
  */
 void ConditionalTreeEdit::checkPressed()
 {
  if (_curNodeType ==  NULL || _curNodeType ==  ("Conditional"))
  {
   for (int i = 0; i < _cdlRoot->getChildCount(); i++) {
       ConditionalTreeNode* cdlNode = (ConditionalTreeNode*) _cdlRoot->getChildAt(i);
       Conditional* cdl = _conditionalManager->getBySystemName(cdlNode->getName());
       cdlNode->setText(buildNodeText("Conditional", cdl, i));  // NOI18N
       _cdlModel->nodeChanged(cdlNode);
   }
  }

  if (_curNodeType ==  ("Variables"))
  {  // NOI18N
   for (int i = 0; i < _variableList->size(); i++) {
       ConditionalVariable* variable = _variableList->value(i);
       ConditionalTreeNode* varNode = (ConditionalTreeNode*) _curNode->getChildAt(i);
       varNode->setText(buildNodeText("Variable", variable, i));  // NOI18N
       _cdlModel->nodeChanged(varNode);
   }
  }
 }

 /**
  * Process the node delete request
  */
 //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::deletePressed() {
     TreePath* parentPath;
     ConditionalTreeNode* parentNode;
     QSet<QString> oldTargetNames = QSet<QString>();
     QSet<QString> newTargetNames = QSet<QString>();
     setEditMode(false);

     // Conditional
     if (_curNodeType == "Conditional")   // NOI18N
     {
             loadReferenceNames(*_variableList, oldTargetNames);
             // Delete the conditional.
             _curLogix->deActivateLogix();
             QStringList msgs = *_curLogix->deleteConditional(_curNodeName);
             _curLogix->activateLogix();
             if (!msgs.isEmpty()) {
                 // Unable to delete due to existing conditional references
                 JOptionPane::showMessageDialog(_editLogixFrame,
                         tr("Conditional \"%1\" (%2) is a Conditional Variable in the Conditional,\n\"%3\" (%4), of Logix, \"%5\" (%6).\nPlease remove that variable first.").arg(msgs.at(0)).arg(msgs.at(1)).arg(msgs.at(2)).arg(msgs.at(3)).arg(msgs.at(5)).arg(msgs.at(5)), // NOI18N
                         tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
                 return;
             }
             updateWhereUsed(oldTargetNames.toList(), newTargetNames.toList(), _curNodeName);
             _showReminder = true;

             // Update the tree
             _cdlRoot->remove(_curNodeRow);
             _cdlModel->nodeStructureChanged(_cdlRoot);

             // Update the row numbers
             int childCount = _cdlRoot->getChildCount();
             for (int i = 0; i < childCount; i++) {
                 _curNode = (ConditionalTreeNode*) _cdlRoot->getChildAt(i);
                 _curNode->setRow(i);
                 _cdlModel->nodeChanged(_curNode);
             }

             if (_curLogix->getNumConditionals() < 1 && !_suppressReminder) {
                 // warning message - last Conditional deleted
                 JOptionPane::showMessageDialog(_editLogixFrame,
                         tr("The last Conditional has been deleted from this Logix."), tr("WarningTitle"), // NOI18N
                         JOptionPane::WARNING_MESSAGE);
             }
             setMoveButtons();
        }
     else if (_curNodeType == "Variable")      // NOI18N
     {
             loadReferenceNames(*_variableList, oldTargetNames);
             if (_variableList->size() < 2 && !_suppressReminder) {
                 // warning message - last State Variable deleted
                 JOptionPane::showMessageDialog(_editLogixFrame,
                         tr("The last State Variable has been deleted from this Conditional.\nA Conditional must have at least one State Variable to do anything useful."), tr("WarningTitle"), // NOI18N
                         JOptionPane::WARNING_MESSAGE);
             }

             // Adjust operator
             if (_curNodeRow == 0 && _variableList->size() > 1) {
                 _variableList->value(1)->setOpern(Conditional::OPERATOR_NONE);
             }

             // Remove the row, update and refresh the Variable list, update references
             _variableList->removeAt(_curNodeRow);
             updateVariableList();
             loadReferenceNames(*_variableList, newTargetNames);
             updateWhereUsed(oldTargetNames.toList(), newTargetNames.toList(), _curNodeName);
             _showReminder = true;

             // Update the tree components
             parentPath = _curTreePath->getParentPath();
             parentNode = (ConditionalTreeNode*) _curNode->getParent();
             parentNode->setRow(_variableList->size());
             _cdlModel->nodeChanged(parentNode);

             // Update the antecedent
             _curNode = (ConditionalTreeNode*) parentNode->getPreviousSibling();
             antecedentChanged("");

             // Update the variable children
             parentNode->removeAllChildren();
             for (int v = 0; v < _variableList->size(); v++) {
                 ConditionalVariable* variable = _variableList->value(v);
                 _leafNode = new ConditionalTreeNode(buildNodeText("Variable", variable, v), // NOI18N
                         "Variable", _curNodeName, v);  // NOI18N
                 parentNode->add(_leafNode);
             }

             _curNode =  NULL;
             _newVariableItem = false;
             cleanUpVariable();

             _cdlModel->nodeStructureChanged(parentNode);
             _cdlTree->setSelectionPath(parentPath);
     }
     else if (_curNodeType ==  "Action")        // NOI18N
     {
             // Remove the row, update and refresh the Action list
             removeActionTimers();
             _actionList->     removeAt(_curNodeRow);
             updateActionList();
             _showReminder = true;

             // Update the tree components
             parentPath = _curTreePath->getParentPath();
             parentNode = (ConditionalTreeNode*) _curNode->getParent();
             parentNode->setRow(_actionList->     size());
             _cdlModel->nodeChanged(parentNode);
             parentNode->removeAllChildren();
             for (int a = 0; a < _actionList->     size(); a++) {
                 ConditionalAction* action = _actionList->     value(a);
                 _leafNode = new ConditionalTreeNode(buildNodeText("Action", action, a), // NOI18N
                         "Action", _curNodeName, a);      // NOI18N
                 parentNode->add(_leafNode);
             }

             _curNode =  NULL;
             _newActionItem = false;
             cleanUpAction();

             _cdlModel->nodeStructureChanged(parentNode);
             _cdlTree->setSelectionPath(parentPath);
         }


             log->error(tr("Delete called for unsupported node type: '%1'").arg(_curNodeType));  // NOI18N
 }

 /**
  * Move a conditional, variable or action row up 1 row
  */
 void ConditionalTreeEdit::upPressed() {
     _showReminder = true;

     if( _curNodeType == "Conditional")         // NOI18N
     {
             // Update Logix index
             _curLogix->deActivateLogix();
             _curLogix->swapConditional(_curNodeRow - 1, _curNodeRow);
             _curLogix->activateLogix();
             moveTreeNode("Up");     // NOI18N
         }
     else if(_curNodeType == "Variable")            // NOI18N
     {
             ConditionalVariable* tempVar = _variableList->value(_curNodeRow);
             int newVarRow = _curNodeRow - 1;
             _variableList->replace(_curNodeRow, _variableList->value(newVarRow));
             _variableList->replace(newVarRow, tempVar);
             // Adjust operator
             if (newVarRow == 0) {
                 _variableList->value(newVarRow)->setOpern(Conditional::OPERATOR_NONE);
                 int newOper = (_logicType == Conditional::ALL_AND)
                         ? Conditional::OPERATOR_AND : Conditional::OPERATOR_OR;
                 _variableList->value(_curNodeRow)->setOpern(newOper);
             }
             updateVariableList();
             moveTreeNode("Up");     // NOI18N
     }
 else if(_curNodeType == "Action")              // NOI18N
     {
             ConditionalAction* tempAct = _actionList->     value(_curNodeRow);
             int newActRow = _curNodeRow - 1;
             _actionList->     replace(_curNodeRow, _actionList->     value(newActRow));
             _actionList->     replace(newActRow, tempAct);
             removeActionTimers();
             updateActionList();
             moveTreeNode("Up");     // NOI18N
     }
else
             log->warn(tr("Move Up called for unsupported node type: '%1'").arg(_curNodeType));  // NOI18N

 }

 /**
  * Move a conditional, variable or action row down 1 row
  */
 void ConditionalTreeEdit::downPressed() {
     _showReminder = true;

     if (_curNodeType == "Conditional")         // NOI18N
     {
             _curLogix->deActivateLogix();
             _curLogix->swapConditional(_curNodeRow, _curNodeRow + 1);
             _curLogix->activateLogix();
             moveTreeNode("Down");   // NOI18N
        }
     else if (_curNodeType == "Variable")            // NOI18N
     {
             ConditionalVariable* tempVar = _variableList->value(_curNodeRow);
             int newVarRow = _curNodeRow + 1;
             _variableList->replace(_curNodeRow, _variableList->value(newVarRow));
             _variableList->replace(newVarRow, tempVar);
             // Adjust operator
             if (_curNodeRow == 0) {
                 _variableList->value(_curNodeRow)->setOpern(Conditional::OPERATOR_NONE);
                 int newOper = (_logicType == Conditional::ALL_AND)
                         ? Conditional::OPERATOR_AND : Conditional::OPERATOR_OR;
                 _variableList->value(newVarRow)->setOpern(newOper);
             }
             updateVariableList();
             moveTreeNode("Down");   // NOI18N
     }
  else if (_curNodeType ==  "Action")              // NOI18N
     {
             ConditionalAction* tempAct = _actionList->     value(_curNodeRow);
             int newActRow = _curNodeRow + 1;
             _actionList->     replace(_curNodeRow, _actionList->     value(newActRow));
             _actionList->     replace(newActRow, tempAct);
             removeActionTimers();
             updateActionList();
             moveTreeNode("Down");   // NOI18N
          }

         else
             log->warn(tr("Move Down called for unsupported node type: '%1'").arg( _curNodeType));  // NOI18N

 }

 /**
  * Remove Action timers and listeners before Action list structure changes.
  * This relates to moving and deleting rows.  New actions at the end are not problem.
  * The issue is that the timer listeners are tied to the action row number.
  * This can result in orphan timers and listeners that keep running.
  * @since 4.11.2
  */
 void ConditionalTreeEdit::removeActionTimers() {
     // Use the real list, not a copy.
     DefaultConditional* cdl = (DefaultConditional*) _curConditional;
     for (ConditionalAction* act : cdl->getActionList()) {
         if (act->getTimer() !=  NULL) {
             act->stopTimer();
             act->setTimer( NULL);
             act->setListener( NULL);
         }
     }
 }

 /**
  * Move a tree node in response to a up or down request
  *
  * @param direction The direction of movement, Up or Down
  */
// @SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::moveTreeNode(QString direction) {
     // Update the node
     int oldRow = _curNodeRow;
     if (direction ==  ("Up")) {    // NOI18N
         _curNodeRow -= 1;
     } else {
         _curNodeRow += 1;
     }
     _curNode->setRow(_curNodeRow);
     if (_curNodeType ==  ("Variable")) {  // NOI18N
         _curNode->setText(buildNodeText("Variable", _variableList->value(_curNodeRow), _curNodeRow));   // NOI18N
     }
     _cdlModel->nodeChanged(_curNode);

     // Update the sibling
     ConditionalTreeNode* siblingNode;
     if (direction ==  ("Up")) {    // NOI18N
         siblingNode = (ConditionalTreeNode*) _curNode->getPreviousSibling();
         siblingNode->setRow(siblingNode->getRow() + 1);
     } else {
         siblingNode = (ConditionalTreeNode*) _curNode->getNextSibling();
         siblingNode->setRow(siblingNode->getRow() - 1);
     }
     if (_curNodeType ==  ("Variable")) {  // NOI18N
         siblingNode->setText(buildNodeText("Variable", _variableList->value(oldRow), oldRow));  // NOI18N
     }
     _cdlModel->nodeChanged(siblingNode);

     // Update the tree
     if (_curNodeType ==  ("Conditional")) {   // NOI18N
         _cdlRoot->insert(_curNode, _curNodeRow);
         _cdlModel->nodeStructureChanged(_cdlRoot);
     } else {
         ConditionalTreeNode* parentNode = (ConditionalTreeNode*) _curNode->getParent();
         parentNode->insert(_curNode, _curNodeRow);
         _cdlModel->nodeStructureChanged(parentNode);
     }
     QVector<TreeNode*>* path = _curNode->getPath();
     QVector<QObject*>* pathList = new QVector<QObject*>();
     for(TreeNode* node : *path) { pathList->append((QObject*)node);}
     _cdlTree->setSelectionPath(new TreePath(pathList));
     setMoveButtons();
 }

 /**
  * Enable/Disable the Up and Down buttons based on the postion in the list
  */
 void ConditionalTreeEdit::setMoveButtons() {
     if (_curNode ==  NULL) {
         return;
     }

     QObjectList compList = _moveButtonPanel->children();
     QPushButton* up = (QPushButton*) compList.at(1);
     QPushButton* down = (QPushButton*) compList.at(3);

     up->setEnabled(true);
     down->setEnabled(true);

     int rows;
     if (_curNodeType ==  ("Conditional")) {       // NOI18N
         rows = _curLogix->getNumConditionals();
     } else {
         ConditionalTreeNode* parent = (ConditionalTreeNode*) _curNode->getParent();
         rows = parent->getRow();
     }

     if (_curNodeRow < 1) {
         up->setEnabled(false);
     }
     if (_curNodeRow >= rows - 1) {
         down->setEnabled(false);
     }

     // Disable move buttons during Variable or Action add or edit processing, or nothing selected
     if ((_newVariableItem && _curNodeType ==  ("Variable")) // NOI18N
             || (_newActionItem && _curNodeType ==  ("Action"))
             || (_editActive)
             || (_cdlTree->getSelectionCount() == 0)) {  // NOI18N
         up->setEnabled(false);
         down->setEnabled(false);
     }

     _moveButtonPanel->setVisible(true);
 }

 /**
  * Respond to Help button press in the Edit Logix menu bar Only visible when
  * using mixed mode and an antecedent node is selected
  */
 void ConditionalTreeEdit::helpPressed()
 {
  QStringList list;
  list << tr("Mixing AND's and OR's may introduce ambiguous evaluations. The antecedent")
  << tr("statement is evaluated from left to right, which corresponds to computing")
  << tr("the innermost variable on the left to the outermost variable on the right.")
  << tr("To modify this order of evaluation, please insert parenthesis to indicate the")
  << tr("logic you want. You may also modify the operators to use. The evaluation")
  << tr("logic of 'Mixed' mode is the content of the antecedent field and not the")
  << tr("operators shown in the rows of the state variable table.");
     JOptionPane::showMessageDialog( NULL,
             list,
             tr("Help"), JOptionPane::INFORMATION_MESSAGE);  // NOI18N
 }

 /**
  * Cancel the current node edit
  */
 void ConditionalTreeEdit::cancelPressed() {
     if (_curNodeType == "Variable")       // NOI18N
     {
             cancelEditVariable();
     }
     else if(_curNodeType == "Action")         // NOI18N
     {
             cancelEditAction();
     }


     makeDetailGrid("EmptyGrid");  // NOI18N
     setEditMode(false);
     _cdlTree->setSelectionPath(_curTreePath);
//     _cdlTree->grabFocus();
 }

 /**
  * Clean up, notify the parent Logix that edit session is done
  */
 void ConditionalTreeEdit::donePressed() {
     if (_curNodeType !=  NULL)
     {
         if(_curNodeType == "Variable")       // NOI18N
                 cancelEditVariable();
          if(_curNodeType == "Action")       // NOI18N
                 cancelEditAction();
     }
     closeSinglePanelPickList();
     if (_pickTables !=  NULL) {
         _pickTables->dispose();
         _pickTables =  NULL;
     }

     _editLogixFrame->setVisible(false);
     _editLogixFrame->dispose();
     _editLogixFrame =  NULL;

     logixData->clear();
     logixData->insert("Finish", _curLogix->getSystemName());  // NOI18N
     fireLogixEvent();
 }

 /*public*/ void ConditionalTreeEdit::bringToFront() {
     _editLogixFrame->toFront();
 }

 // ============  Tree Content and Navigation ============
 /**
  * Create the conditional tree structure using the current Logix
  *
  * @return _cdlTree The tree ddefinition with its content
  */
 JTree* ConditionalTreeEdit::buildConditionalTree() {
     _cdlRoot = new DefaultMutableTreeNode("Root Node");      // NOI18N
     _cdlModel = new DefaultTreeModel(_cdlRoot);
     _cdlTree = new JTree(_cdlModel);
     _cdlTree->setItemDelegate(new HtmlDelegate());
     _cdlTree->setHeaderHidden(true);
     _cdlTree->setMinimumSize(300,200);

//     connect(_cdlTree, SIGNAL(collapsed(QModelIndex)), _cdlTree, SLOT(rowCollapsed(QModelIndex)));
//     connect(_cdlTree, SIGNAL(expanded(QModelIndex)), _cdlTree, SLOT(rowExpanded(QModelIndex)));


     createConditionalContent();

     // build the tree GUI
     _cdlTree->expandPath(new TreePath(_cdlRoot));
     _cdlTree->setRootVisible(false);
     _cdlTree->setShowsRootHandles(true);
     _cdlTree->setScrollsOnExpand(true);
     _cdlTree->setExpandsSelectedPaths(true);
     _cdlTree->getSelectionModel()->setSelectionMode(DefaultTreeSelectionModel::SINGLE_TREE_SELECTION);

     // tree listeners
     CDLTreeSelectionListener* treeSelectionListener = new CDLTreeSelectionListener(this);
//     connect(_cdlTree, SIGNAL(valueChanged(TreeSelectionEvent*)), treeSelectionListener, SLOT(valueChanged(TreeSelectionEvent*)));
//     CDLTreeExpansionListener* treeExpansionListener = new CDLTreeExpansionListener(this);
//     connect(_cdlTree, SIGNAL(treeExpanded(TreeExpansionEvent*)), treeExpansionListener, SLOT(treeExpanded(TreeExpansionEvent*)));
//     connect(_cdlTree, SIGNAL(treeCollapsed(TreeExpansionEvent*)), treeExpansionListener, SLOT(treeCollapsed(TreeExpansionEvent*)));
#if 0
     _cdlTree.addTreeSelectionListener(_cdlListener = new TreeSelectionListener() {
         //@Override
         /*public*/ void valueChanged(TreeSelectionEvent e) {
             if (_editActive) {
                 if (e.getNewLeadSelectionPath() != _curTreePath) {
                     _cdlTree->setSelectionPath(e.getOldLeadSelectionPath());
                     showNodeEditMessage();
                 }
                 return;
             }

             _curTreePath = _cdlTree.getSelectionPath();
             if (_curTreePath !=  NULL) {
                 Object chkLast = _curTreePath.getLastPathComponent();
                 if (chkLast instanceof ConditionalTreeNode) {
                     treeRowSelected((ConditionalTreeNode) chkLast);
                 }
             }
         }
     });

     _cdlTree.addTreeExpansionListener(new TreeExpansionListener() {
         //@Override
         /*public*/ void treeExpanded(TreeExpansionEvent e) {
             ConditionalTreeNode checkNode = (ConditionalTreeNode) e.getPath().getLastPathComponent();
             if (checkNode.getType() ==  ("Variables")) {  // NOI18N
                 // Include the field descriptions in the node name
                 checkNode->setText(buildNodeText("Variables", _curConditional, 1));  // NOI18N
                 _cdlModel->nodeChanged(checkNode);
             }
         }

         //@Override
         /*public*/ void treeCollapsed(TreeExpansionEvent e) {
             ConditionalTreeNode checkNode = (ConditionalTreeNode) e.getPath().getLastPathComponent();
             if (checkNode.getType() ==  ("Variables")) {  // NOI18N
                 // Remove the field descriptions from the node name
                 checkNode->setText(buildNodeText("Variables", _curConditional, 0));  // NOI18N
                 _cdlModel->nodeChanged(checkNode);
             }

             if (_cdlTree.getSelectionCount() == 0) {
                 makeDetailGrid("EmptyGrid");  // NOI18N
             }
         }
     });
#endif
     _cdlTree->addTreeSelectionListener(treeSelectionListener);
     _cdlTree->addTreeExpansionListener(new CDLTreeExpansionListener(this));
     return _cdlTree;
 }

 CDLTreeSelectionListener::CDLTreeSelectionListener(ConditionalTreeEdit *cte){ this->cte = cte;}
 /*public*/ void  CDLTreeSelectionListener::valueChanged(TreeSelectionEvent* e)
 {
  if (cte->_editActive) {
      if (e->getNewLeadSelectionPath() != cte->_curTreePath) {
          cte->_cdlTree->setSelectionPath(e->getOldLeadSelectionPath());
          cte->showNodeEditMessage();
      }
      return;
  }

  cte->_curTreePath = cte->_cdlTree->getSelectionPath();
  if (cte->_curTreePath !=  NULL) {
      QObject* chkLast = cte->_curTreePath->getLastPathComponent();
      if (qobject_cast<ConditionalTreeNode*>(chkLast) != NULL) {
          cte->treeRowSelected((ConditionalTreeNode*) chkLast);
      }
  }
 }

 CDLTreeExpansionListener::CDLTreeExpansionListener(ConditionalTreeEdit *cte)  { this->cte = cte;}

 /*public*/ void CDLTreeExpansionListener::treeExpanded(TreeExpansionEvent* e) {
     ConditionalTreeNode* checkNode = (ConditionalTreeNode*) e->getPath()->getLastPathComponent();
     if (checkNode->getType() ==  ("Variables")) {  // NOI18N
         // Include the field descriptions in the node name
         checkNode->setText(cte->buildNodeText("Variables", cte->_curConditional, 1));  // NOI18N
         cte->_cdlModel->nodeChanged(checkNode);
     }
 }

/*public*/ void CDLTreeExpansionListener::treeCollapsed(TreeExpansionEvent* e) {
    ConditionalTreeNode* checkNode = (ConditionalTreeNode*) e->getPath()->getLastPathComponent();
    if (checkNode->getType() ==  ("Variables")) {  // NOI18N
        // Remove the field descriptions from the node name
        checkNode->setText(cte->buildNodeText("Variables", cte->_curConditional, 0));  // NOI18N
        cte->_cdlModel->nodeChanged(checkNode);
    }

    if (cte->_cdlTree->getSelectionCount() == 0) {
        cte->makeDetailGrid("EmptyGrid");  // NOI18N
    }
}

 /**
  * Create the tree content Level 1 are the conditionals Level 2 includes the
  * antecedent, logic type, trigger mode and parent nodes for Variables and
  * Actions Level 3 contains the detail Variable and Action entries
  */
 void ConditionalTreeEdit::createConditionalContent()
 {
  int _numConditionals = _curLogix->getNumConditionals();
  for (int i = 0; i < _numConditionals; i++)
  {
   QString csName = _curLogix->getConditionalByNumberOrder(i);
   Conditional* curConditional = _curLogix->getConditional(csName);
   ConditionalTreeNode* _cdlNode = new ConditionalTreeNode(buildNodeText("Conditional", curConditional, 0), "Conditional", csName, i);    // NOI18N
   _cdlRoot->add(_cdlNode);

   ConditionalTreeNode* _leafNode = new ConditionalTreeNode(buildNodeText("Antecedent", curConditional, 0), "Antecedent", csName, 0);   // NOI18N
   _cdlNode->add(_leafNode);

   _variableList = curConditional->getCopyOfStateVariables();
   int varCount = _variableList->size();
   ConditionalTreeNode* _varHead = new ConditionalTreeNode(buildNodeText("Variables", _curConditional, 0), "Variables", csName, varCount);     // NOI18N
   _cdlNode->add(_varHead);

   for (int v = 0; v < _variableList->size(); v++) {
       ConditionalVariable* variable = _variableList->value(v);
       _leafNode = new ConditionalTreeNode(buildNodeText("Variable", variable, v), "Variable", csName, v);
       _varHead->add(_leafNode);
   }

   _leafNode = new ConditionalTreeNode(buildNodeText("LogicType", curConditional, 0), "LogicType", csName, 0);      // NOI18N
   _cdlNode->add(_leafNode);

  bool triggerMode = curConditional->getTriggerOnChange();
   _leafNode = new ConditionalTreeNode(buildNodeText("TriggerMode", curConditional, 0), "TriggerMode", csName, 0);      // NOI18N
   _cdlNode->add(_leafNode);

   _actionList = curConditional->getCopyOfActions();
   int actCount = _actionList->     size();
   ConditionalTreeNode* _actHead = new ConditionalTreeNode("Actions", "Actions", csName, actCount);      // NOI18N
   _cdlNode->add(_actHead);
   for (int a = 0; a < _actionList->     size(); a++)
   {
    ConditionalAction* action = _actionList->     value(a);
    _leafNode = new ConditionalTreeNode(action->description(triggerMode), "Action", csName, a);      // NOI18N
    _actHead->add(_leafNode);
   }
   qDebug() << "node at row" << i <<" has " << _cdlNode->getChildCount() << " children";
  }
 }

 /**
  * Change the button row based on the currently selected node type Invoke
  * edit where appropriate
  *
  * @param selectedNode The node object
  */
 void ConditionalTreeEdit::treeRowSelected(ConditionalTreeNode* selectedNode)
 {
  // Set the current node variables
  _curNode = selectedNode;
  _curNodeName = selectedNode->getName();
  _curNodeType = selectedNode->getType();
  _curNodeText = selectedNode->getText();
  _curNodeRow = selectedNode->getRow();

  // Set the current conditional variables if different conditional
  if (_curConditionalName !=  (_curNodeName))
  {
   _curConditional = _conditionalManager->getConditional(_curNodeName);
   _antecedent = _curConditional->getAntecedentExpression();
   _logicType = _curConditional->getLogicType();
   _triggerMode = _curConditional->getTriggerOnChange();
   _variableList = _curConditional->getCopyOfStateVariables();
   _actionList = _curConditional->getCopyOfActions();
   _curConditionalName = _curNodeName;
  }

  // Reset button bar
  _addButtonPanel->setVisible(false);
  _checkButtonPanel->setVisible(false);
  _toggleButtonPanel->setVisible(false);
  _moveButtonPanel->setVisible(false);
  _deleteButtonPanel->setVisible(false);
  _helpButtonPanel->setVisible(false);

 // _labelPanel->removeAll();
  clearLayout(_labelPanelLayout, true);

  if (_curNodeType == "Conditional")     // NOI18N
  {
   _labelPanelLayout->addWidget(_conditionalLabel);
   _addButtonPanel->setVisible(true);
   _checkButtonPanel->setVisible(true);
   _deleteButtonPanel->setVisible(true);
   setMoveButtons();
   editPressed();
  }
  else if (_curNodeType ==  "Antecedent")      // NOI18N
  {
   editPressed();
  }
  else if (_curNodeType == "LogicType")       // NOI18N
  {
   editPressed();
  }
  else if (_curNodeType == "TriggerMode")     // NOI18N
  {
   _labelPanelLayout->addWidget(_triggerModeLabel);
   _toggleButtonPanel->setVisible(true);
   makeDetailGrid("EmptyGrid");  // NOI18N
  }
  else if (_curNodeType == "Variables")       // NOI18N
  {
   _labelPanelLayout->addWidget(_variablesLabel);
   _addButtonPanel->setVisible(true);
   _checkButtonPanel->setVisible(true);
   makeDetailGrid("EmptyGrid");  // NOI18N
  }
  else if (_curNodeType == "Variable")        // NOI18N
  {
   _labelPanelLayout->addWidget(_variableLabel);
   _addButtonPanel->setVisible(true);
   _deleteButtonPanel->setVisible(true);
   if (_logicType != Conditional::MIXED) {
       setMoveButtons();
   }
   editPressed();
  }
  else if (_curNodeType == "Actions")         // NOI18N
  {
   _labelPanelLayout->addWidget(_actionsLabel);
   _addButtonPanel->setVisible(true);
   makeDetailGrid("EmptyGrid");  // NOI18N
  }
  else if (_curNodeType == "Action")          // NOI18N
  {
   _labelPanelLayout->addWidget(_actionLabel);
   _addButtonPanel->setVisible(true);
   _deleteButtonPanel->setVisible(true);
   setMoveButtons();
   editPressed();
  }
  else
   log->warn("Should not be here");  // NOI18N
 }

 void ConditionalTreeEdit::clearLayout(QLayout* layout, bool deleteWidgets)
 {
  if(layout == NULL)
   return;
  while (QLayoutItem* item = layout->takeAt(0))
  {
   QWidget* widget;
   if (  (deleteWidgets)
         && (widget = item->widget())  )
   {
       //delete widget;
    widget->setParent(NULL);
   }
    if (QLayout* childLayout = item->layout())
        clearLayout(childLayout, deleteWidgets);
    delete item;
  }
 }

 /**
  * Create the node text strings based on node type
  *
  * @param nodeType  The type of the node
  * @param component The conditional object or child object
  * @param idx       Optional index value
  * @return nodeText containing the text for the node
  */
 QString ConditionalTreeEdit::buildNodeText(QString nodeType, QObject* component, int idx)
 {
  Conditional* cdl;
  ConditionalAction* act;
  ConditionalVariable* var;

  if (nodeType =="Conditional")  // NOI18N
  {
   cdl = (Conditional*) component;
   QString cdlStatus = (cdl->getState() == Conditional::_TRUE)
           ? tr("True") // NOI18N
           : tr("False");  // NOI18N
   QString cdlNames = cdl->getSystemName() + " -- " + cdl->getUserName();
   QString cdlFill = StringUtils::repeat("&nbsp;", 5);  // NOI18N
   QString cdlLine = "<html>" + cdlNames + cdlFill + "<strong>[ " + cdlStatus + " ]</strong></html>";  // NOI18N
   return cdlLine;
  }
  else if (nodeType == "Antecedent")  // NOI18N
  {
   cdl = (Conditional*) component;
   QString antecedent = cdl->getAntecedentExpression();
   if (cdl->getLogicType() != Conditional::MIXED) {
       antecedent = "- - - - - - - - -";
   }
   return tr("Antecedent:") + " " + antecedent;   // NOI18N
  }
  else if (nodeType == "LogicType")  // NOI18N
  {
   cdl = (Conditional*) component;
   int logicType = cdl->getLogicType();
   QString logicName;
   switch (logicType) {
       case Conditional::ALL_AND:
           logicName = tr("AND");      // NOI18N
           break;
       case Conditional::ALL_OR:
           logicName = tr("OR");       // NOI18N
           break;
       case Conditional::MIXED:
           logicName = tr("Mixed");    // NOI18N
           break;
       default:
           logicName = "None";
   }
   return tr(" Logic Type:") + "  " + logicName;   // NOI18N
  }
  else if (nodeType == "TriggerMode")  // NOI18N
  {
   cdl = (Conditional*) component;
   bool triggerMode = cdl->getTriggerOnChange();
   QString triggerText;
   if (triggerMode)
   {
    triggerText = tr("Execute actions on change of state only"); // NOI18N
   }
   else
   {
    triggerText = tr("Execute Actions whenever triggered");    // NOI18N
   }
   return tr("Trigger Mode:") + "  " + triggerText; // NOI18N
  }
  else if (nodeType == "Variables")  // NOI18N
  {
   if (idx == 0) {
       // The node is not expanded, return plain content
       return tr("Variables");  // NOI18N
   } else {
       // The node is expanded, include the field names
       return tr("%1   [[ %2 || %3 || %4 ]]").arg( // NOI18N
               tr("Variables:")).arg( // NOI18N
               tr("State Variable Description")).arg( // NOI18N
               tr("Trigger Calculation")).arg( // NOI18N
               tr("State")); // NOI18N
   }
  }
  else if (nodeType =="Variable")  // NOI18N
  {
  var = (ConditionalVariable*) component;

  QString rowNum = "R" + QString::number(idx + 1) + (idx > 9 ? " " : "  ");
  QString rowOper = var->getOpernString() + " ";

  QString rowNot = "";
  if (var->isNegated()) {
      rowNot = tr("LogicNOT") + " ";     // NOI18N
  }

  QString boldFormat = "  || <strong>%1</strong>";  // NOI18N
  QString rowTrigger = QString(boldFormat).arg(
          (var->doTriggerActions()) ? tr("Yes") : tr("ButtonNo"));  // NOI18N
  QString rowStatus = QString(boldFormat).arg(
          (var->evaluate()) ? tr("True") : tr("False"));  // NOI18N

  QString varLine = "<html>" + rowNum + rowOper + rowNot + var->toString() + rowTrigger + rowStatus + "</html>";  // NOI18N
  return varLine;
 }
 else if (nodeType == "Actions")  // NOI18N
 {
  return tr("Actions");  // NOI18N
 }
 else if (nodeType == "Action")   // NOI18N
 {
  act = (ConditionalAction*) component;
  return act->description(_triggerMode);
 }
 return "None";
}

 /**
  * Display reminder to save.
  */
 void ConditionalTreeEdit::showNodeEditMessage() {
     if (InstanceManager::getNullableDefault("UserPreferencesManager") !=  NULL) {
         ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                 showInfoMessage(tr("Active Node Edit"), // NOI18N
                         tr("Another node cannot be selected while editing a node. Select Cancel or Update to complete the edit."), // NOI18N
                         getClassName(),
                         "SkipNodeEditMessage"); // NOI18N
     }
 }

 bool ConditionalTreeEdit::eventFilter(QObject *watched, QEvent *event)
 {
  if(event->type() == QEvent::FocusIn)
  {
   if(!_editActive )
    setEditMode(true);
   return true;
  }
//  if(event->type() == QEvent::FocusOut)
//  {}
  // standard event processing
  return QObject::eventFilter(watched, event);
 }

 /**
  * Add the focus listener to each detail edit field
  */
 void ConditionalTreeEdit::setFocusListeners()
 {
     _editConditionalUserName->installEventFilter(this);
     _editAntecedent->installEventFilter(this);
     _editOperatorMode->installEventFilter(this);
     _variableItemBox->installEventFilter(this);
     _variableOperBox->installEventFilter(this);
     _variableNegated->installEventFilter(this);
     _variableTriggerActions->installEventFilter(this);
     _variableNameField->installEventFilter(this);
     _variableStateBox->installEventFilter(this);
     _variableSignalBox->installEventFilter(this);
     _selectLogixBox->installEventFilter(this);
     _selectConditionalBox->installEventFilter(this);
     _variableCompareOpBox->installEventFilter(this);
     _variableCompareTypeBox->installEventFilter(this);
     _variableData1Field->installEventFilter(this);
     _variableData2Field->installEventFilter(this);
     _actionItemBox->installEventFilter(this);
     _actionNameField->installEventFilter(this);
     _actionTypeBox->installEventFilter(this);
     _actionBox->installEventFilter(this);
     _shortActionString->installEventFilter(this);
     _longActionString->installEventFilter(this);
     _actionSetButton->installEventFilter(this);
     _actionOptionBox->installEventFilter(this);
 }

 /**
  * Enable/disable buttons based on edit state.
  * Open pick lists based on the current SelectionMode
  * The edit state controls the ability to select tree nodes.
  * @param active True to make edit active, false to make edit inactive
  */
 void ConditionalTreeEdit::setEditMode(bool active) {
     _editActive = active;
     _cancelAction->setEnabled(active);
     _updateAction->setEnabled(active);
     QObject* delButton = _deleteButtonPanel->children().at(0);
     if (qobject_cast<QPushButton*>(delButton) != NULL)  {
         ((QPushButton*)delButton)->setEnabled(!active);
     }
     QObject* addButton = _addButtonPanel->children().at(0);
     if (qobject_cast<QPushButton*>(addButton) != NULL)  {
         ((QPushButton*)addButton)->setEnabled(!active);
     }
     if (_curNodeType !=  NULL) {
         if (_curNodeType ==  ("Conditional") || _curNodeType ==  ("Variable") || _curNodeType ==  ("Action")) {  // NOI18N
             setMoveButtons();
         }
     }
     if (active) {
         setPickWindow("Activate", 0);  // NOI18N
     } else {
         setPickWindow("Deactivate", 0);  // NOI18N
     }
 }

 /**
  * Ceate tabbed Pick Taba;e or Pick Single based on Selection Mode
  * Called by {@link #setEditMode} when edit mode becomes active.
  * Called by {@link #variableTypeChanged} and {@link #actionItemChanged} when item type changes.
  * @param cmd The source or action to be performed.
  * @param item The item type for Variable or Action or zero
  */
 void ConditionalTreeEdit::setPickWindow(QString cmd, int item) {
     if (_selectionMode ==  SelectionMode::USECOMBO) {
         return;
     }
     // Save the item information
     if (cmd ==  ("Variable") || cmd ==  ("Action")) {  // NOI18N
         _pickCommand = cmd;
         _pickItem = item;
         if (_editActive) {
             if (_selectionMode ==  SelectionMode::USEMULTI) {
                 doPickList();
             } else {
                 doPickSingle();
             }
         }
     }
     if (cmd ==  ("Activate")) {  // NOI18N
         if (_curNodeType ==  ("Variable") || _curNodeType ==  ("Action")) {  // NOI18N
             // Open the appropriate window based on the save values
             if (_selectionMode ==  SelectionMode::USEMULTI) {
                 doPickList();
             } else {
                 doPickSingle();
             }
         }
     }
     if (cmd ==  ("Deactivate")) {  // NOI18N
         // Close/dispose the pick window
         hidePickListTable();
         closeSinglePanelPickList();
     }
 }

 /**
  * Create a Variable or Action based tabbed PickList with appropriate tab selected.
  */
 void ConditionalTreeEdit::doPickList() {
     if (_pickItem == 0) {
         return;
     }
     if (_pickTables ==  NULL) {
         openPickListTable();
     }
     if (_pickCommand ==  ("Variable")) {
         setPickListTab(_pickItem, false);
     } else if (_pickCommand ==  ("Action")) {
         setPickListTab(_pickItem, true);
     }
 }

 /**
  * Create a Variable or Action based single pane PickList
  */
 void ConditionalTreeEdit::doPickSingle() {
     if (_pickCommand ==  ("Variable")) {
         createSinglePanelPickList(_pickItem, new PickSingleListener(_variableNameField, _pickItem, this), false);
     } else if (_pickCommand ==  ("Action")) {
         createSinglePanelPickList(_pickItem, new PickSingleListener(_actionNameField, _pickItem, this), true);
     }
 }

 // ============  Edit Variable Section ============
 /**
  * Called once during class initialization to define the GUI objects Where
  * possible, the combo box content is loaded
  */
 void ConditionalTreeEdit::buildVariableComponents() {
     // Item Type
     _variableItemBox = new QComboBox();
     for (int i = 0; i <= Conditional::ITEM_TYPE_LAST_STATE_VAR; i++) {
         _variableItemBox->addItem(ConditionalVariable::getItemTypeString(i));
     }
//     JComboBoxUtil::setupComboBoxMaxRows(_variableItemBox);
//     _variableItemBox::addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             int newVariableItem = _variableItemBox->currentIndex();
//             if (log->isDebugEnabled()) {
//                 log->debug("_variableItemBox Listener: new = {}, curr = {}, row = {}",  // NOI18N
//                         newVariableItem, _curVariableItem, _curNodeRow);
//             }
//             if (newVariableItem != _curVariableItem) {
//                 if (_curNodeRow >= 0) {
//                     _curVariable = new ConditionalVariable();
//                     _variableList->set(_curNodeRow, _curVariable);
//                 }
//                 _curVariableItem = newVariableItem;
//             }
//             variableTypeChanged(newVariableItem);
//         }
//     });
connect(_variableItemBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_variableItemBox_currentIndexChanged()));
     // Oper type
     _variableOperBox = new QComboBox();
     _variableOperBox->addItem(tr("LogicAND"));  // NOI18N
     _variableOperBox->addItem(tr("LogicOR"));  // NOI18N

     // Negation
     _variableNegated = new QCheckBox();

     // trigger
     _variableTriggerActions = new QCheckBox();

     // Item Name
     _variableNameField = new JTextField(20);

     // Combo box section for selecting conditional reference
     //   First box selects the Logix, the second selects the conditional within the logix
     _selectLogixBox->addItem("XXXXXXXXXXXXXXXXXXXXX");  // NOI18N
     _selectConditionalBox->addItem("XXXXXXXXXXXXXXXXXXXXX");  // NOI18N
     //_selectLogixBox::addActionListener(selectLogixBoxListener);
     connect(_selectLogixBox, SIGNAL(currentIndexChanged(int)), selectLogixBoxListener, SLOT(actionPerformed()));
     //_selectConditionalBox::addActionListener(selectConditionalBoxListener);
     connect(_selectConditionalBox, SIGNAL(currentIndexChanged(int)), selectConditionalBoxListener, SLOT(actionPerformed()));

     // State Box
     _variableStateBox = new QComboBox();
     _variableStateBox->addItem("XXXXXXX");  // NOI18N

     // Aspects
     _variableSignalBox = new QComboBox();
     _variableSignalBox->addItem("XXXXXXXXX");  // NOI18N

     // Compare operator
     _variableCompareOpBox = new QComboBox();
     for (int i = 1; i <= ConditionalVariable::NUM_COMPARE_OPERATIONS; i++) {
         _variableCompareOpBox->addItem(ConditionalVariable::getCompareOperationString(i));
     }

     // Compare type
     _variableCompareTypeBox = new QComboBox();
     for (int i = 0; i < Conditional::ITEM_TO_MEMORY_TEST.length(); i++) {
         _variableCompareTypeBox->addItem(ConditionalVariable::describeState(Conditional::ITEM_TO_MEMORY_TEST[i]));
     }
     //_variableCompareTypeBox::addActionListener(compareTypeBoxListener);
     connect(_variableCompareTypeBox, SIGNAL(currentIndexChanged(int)), compareTypeBoxListener, SLOT(actionPerformed()));

     // Data 1
     _variableData1Field = new JTextField(10);

     // Data 2
     _variableData2Field = new JTextField(10);
 }

 void ConditionalTreeEdit::on_variableItemBox_currentIndexChanged()
 {
  int newVariableItem = _variableItemBox->currentIndex();
  if (log->isDebugEnabled()) {
      log->debug(tr("_variableItemBox Listener: new = %1, curr = %2, row = %3").arg(
              newVariableItem).arg(_curVariableItem).arg(_curNodeRow));
  }
  if (newVariableItem != _curVariableItem) {
      if (_curNodeRow >= 0) {
          _curVariable = new ConditionalVariable();
          _variableList->replace(_curNodeRow, _curVariable);
      }
      _curVariableItem = newVariableItem;
  }
  variableTypeChanged(newVariableItem);
}


 // ------------ Make Variable Edit Grid Panels ------------
 /**
  * Create a one row grid with just the Variable Type box This is the base
  * for larger grids as well as the initial grid for new State Variables
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeEmptyVariableGrid(GridBagConstraints c) {
     // Variable type box
     c.gridy = 0;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row0Label = new QLabel(tr("Variable Type"));  // NOI18N
     row0Label->setToolTip(tr("Select type of state variable for Conditional to test"));  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableItemBox, c);
 }

 /*
  * Create the Oper, Not and Trigger rows
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeOptionsVariableGrid(GridBagConstraints c) {
     makeEmptyVariableGrid(c);

     // Oper Select
     c.gridy = 1;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row1Label = new QLabel(tr("Operator"));  // NOI18N
     row1Label->setToolTip(tr("Select AND or OR for the operator, default is AND"));  // NOI18N
     _gridPanelLayout->addWidget(row1Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableOperBox, c);

     // Not Select
     c.gridy = 2;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row2Label = new QLabel(tr("Negation (Not)"));  // NOI18N
     row2Label->setToolTip(tr("Check to indicate that this variable is to be negated, default is unchecked"));  // NOI18N
     _gridPanelLayout->addWidget(row2Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableNegated, c);

     // Trigger Select
     c.gridy = 3;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row3Label = new QLabel(tr("Trigger Calculation"));  // NOI18N
     row3Label->setToolTip(tr("Check to indicate that this variable is used to trigger actions, default is checked"));  // NOI18N
     _gridPanelLayout->addWidget(row3Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableTriggerActions, c);
 }

 /*
  * Create the standard Name and State rows
  * The name field will be either a text field or a combo box
  * The name field label is a variable to support run time changes
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeStandardVariableGrid(GridBagConstraints c) {
     makeOptionsVariableGrid(c);

     // Name Field
     c.gridy = 4;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_variableNameLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     if (_selectionMode ==  SelectionMode::USECOMBO) {
         _gridPanelLayout->addWidget(_comboNameBox, c);
     } else {
         _gridPanelLayout->addWidget(_variableNameField, c);
     }

     // State Box
     c.gridy = 5;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("Variable State"));  // NOI18N
     row5Label->setToolTip(tr("Select the state of the variable to test"));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableStateBox, c);
 }

 /*
  * Add the Aspect field for signal heads and signal masts
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeSignalAspectVariableGrid(GridBagConstraints c) {
     makeStandardVariableGrid(c);

     // Mast Aspect Box
     c.gridy = 6;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("Variable Aspect"));  // NOI18N
     row5Label->setToolTip(tr("Select the Aspect of the Signal to test"));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableSignalBox, c);
 }

 /*
  * Create the Logix and Conditional rows and the State row
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeConditionalVariableGrid(GridBagConstraints c) {
     makeOptionsVariableGrid(c);

     // Logix Selection ComboBox
     c.gridy = 4;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row4Label = new QLabel(tr("Select Logix"));  // NOI18N
     row4Label->setToolTip(tr("Select the Logix that contains the conditional to be checked"));  // NOI18N
     _gridPanelLayout->addWidget(row4Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_selectLogixBox, c);

     // Conditional Selection ComboBox
     c.gridy = 5;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("Select Conditional"));  // NOI18N
     row5Label->setToolTip(tr("Select the desired condtional"));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_selectConditionalBox, c);

     // State Box
     c.gridy = 6;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row6Label = new QLabel(tr("Variable State"));  // NOI18N
     row6Label->setToolTip(tr("Select the state of the variable to test"));  // NOI18N
     _gridPanelLayout->addWidget(row6Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableStateBox, c);
 }

 /*
  * Create the Memory specific rows
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeMemoryVariableGrid(GridBagConstraints c) {
     makeOptionsVariableGrid(c);

     // Name Field
     c.gridy = 4;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row4Label = new QLabel(tr("System / User Name"));  // NOI18N
     row4Label->setToolTip(tr("Enter name (system or user) of Memory"));  // NOI18N
     _gridPanelLayout->addWidget(row4Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     if (_selectionMode ==  SelectionMode::USECOMBO) {
         _gridPanelLayout->addWidget(_comboNameBox, c);
     } else {
         _gridPanelLayout->addWidget(_variableNameField, c);
     }

     // Comparison Operator
     c.gridy = 5;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("Comparison Operator"));  // NOI18N
     row5Label->setToolTip(tr("Select an operator to compare memory values"));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableCompareOpBox, c);

     // Compare As
     c.gridy = 6;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row6Label = new QLabel(tr("Compare as"));  // NOI18N
     row6Label->setToolTip(tr("Select either a literal value or the value in a memory location"));  // NOI18N
     _gridPanelLayout->addWidget(row6Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableCompareTypeBox, c);

     // Literal Value (default) / Memory Value (name)
     c.gridy = 7;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_variableMemoryValueLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableData1Field, c);
 }

 /*
  * Create the Fast Clock start and end time rows
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeFastClockVariableGrid(GridBagConstraints c) {
     makeOptionsVariableGrid(c);

     // Start Time Field
     c.gridy = 4;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row4Label = new QLabel(tr("Start Time"));  // NOI18N
     row4Label->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));  // NOI18N
     _gridPanelLayout->addWidget(row4Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableData1Field, c);

     // End Time Field
     c.gridy = 5;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("End Time"));  // NOI18N
     row5Label->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_variableData2Field, c);
 }

 // ------------ Main Variable methods ------------
 /**
  * Set display to show current state variable (curVariable) parameters.
  */
 void ConditionalTreeEdit::initializeStateVariables() {
     int testType = _curVariable->getType();
     if (log->isDebugEnabled()) {
         log->debug("initializeStateVariables: testType= " + QString::number(testType));  // NOI18N
     }
     int itemType = Conditional::TEST_TO_ITEM[testType];
     if (log->isDebugEnabled()) {
         log->debug("initializeStateVariables: itemType= " + QString::number(itemType) + ", testType= " + QString::number(testType));  // NOI18N
     }
     if (itemType == _variableItemBox->currentIndex()) {
         // Force a refresh of variableTypeChanged
         variableTypeChanged(itemType);
     }
     _variableItemBox->setCurrentIndex(itemType);
     _variableOperBox->setCurrentText(_curVariable->getOpernString());
     _variableNegated->setChecked(_curVariable->isNegated());
     _variableTriggerActions->setChecked(_curVariable->doTriggerActions());

     switch (itemType) {
         case Conditional::TYPE_NONE:
             _variableNameField->setText("");
             break;

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
             if ((Conditional::TYPE_SIGNAL_HEAD_RED <= testType && testType <= Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN)
                     || Conditional::TYPE_SIGNAL_HEAD_LUNAR == testType
                     || Conditional::TYPE_SIGNAL_HEAD_FLASHLUNAR == testType) {
                 _variableStateBox->setCurrentText( // index 1 = TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS
                         ConditionalVariable::describeState(Conditional::ITEM_TO_SIGNAL_HEAD_TEST[1]));
                 _variableSignalBox->setCurrentText(
                         ConditionalVariable::describeState(_curVariable->getType()));
             }
             break;

         case Conditional::ITEM_TYPE_SIGNALMAST:
             // set display to show current state variable (curVariable) parameters
             _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_SIGNAL_MAST_TEST, testType));
             _variableNameField->setText(_curVariable->getName());
             if (testType == Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS) {
                 _variableSignalBox->setCurrentText(_curVariable->getDataString());
             }
             break;

         case Conditional::ITEM_TYPE_MEMORY:
     {
             _variableCompareTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_MEMORY_TEST, testType));
             _variableNameField->setText(_curVariable->getName());
             int num1 = _curVariable->getNum1() - 1;
             if (num1 == -1) {  // former code was only equals
                 num1 = ConditionalVariable::EQUAL - 1;
             }
             _variableCompareOpBox->setCurrentIndex(num1);
             _variableData1Field->setText(_curVariable->getDataString());
             break;
}
         case Conditional::ITEM_TYPE_CONDITIONAL:
             _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_CONDITIONAL_TEST, testType));
             _variableNameField->setText(_curVariable->getName());
             break;

         case Conditional::ITEM_TYPE_WARRANT:
             _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_WARRANT_TEST, testType));
             _variableNameField->setText(_curVariable->getName());
             break;

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
             //_variableStateBox->clear();
             QStringListIterator names(OBlock::getLocalStatusNames());
             while (names.hasNext()) {
                 _variableStateBox->addItem(names.next());
             }
             _variableStateBox->setCurrentText(OBlock::getLocalStatusName(_curVariable->getDataString()));
             break;
}
         case Conditional::ITEM_TYPE_ENTRYEXIT:
             _variableNameField->setText(_curVariable->getBean()->getUserName());
             _variableStateBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_ENTRYEXIT_TEST, testType));
             break;

         default:
             break;
     }
     _detailGrid->setVisible(true);
 }

 /**
  * Respond to change in variable type chosen in the State Variable combo box
  *
  * @param itemType value representing the newly selected Conditional type,
  *                 i.e. ITEM_TYPE_SENSOR
  */
 /*private*/ void ConditionalTreeEdit::variableTypeChanged(int itemType) {
     int testType = _curVariable->getType();
     if (log->isDebugEnabled()) {
         log->debug("variableTypeChanged: itemType= " + QString::number(itemType) + ", testType= " + QString::number(testType));  // NOI18N
     }
     _variableStateBox->clear();
//     _variableNameField.removeActionListener(variableSignalHeadNameListener);
     disconnect(_variableNameField, SIGNAL(editingFinished()), variableSignalHeadNameListener, SLOT(actionPerformed()));
//     _variableNameField.removeActionListener(variableSignalMastNameListener);
     disconnect(_variableNameField, SIGNAL(editingFinished()), variableSignalMastNameListener, SLOT(actionPerformed()));
//     _variableStateBox::removeActionListener(variableSignalTestStateListener);
     disconnect(_variableNameField, SIGNAL(editingFinished()), variableSignalTestStateListener, SLOT(actionPerformed()));
     _detailGrid->setVisible(false);

     if (_comboNameBox !=  NULL) {
//         for (ActionListener item : _comboNameBox::getActionListeners()) {
//             _comboNameBox::removeActionListener(item);
//         }
//         _comboNameBox::removeFocusListener(detailFocusEvent);
      disconnect(_comboNameBox);
     }
     setPickWindow("Variable", itemType);  // NOI18N

     _variableOperBox->setCurrentText(_curVariable->getOpernString());
     _variableNegated->setChecked(_curVariable->isNegated());
     _variableTriggerActions->setChecked(_curVariable->doTriggerActions());

     switch (itemType) {
         case Conditional::TYPE_NONE:
             makeDetailGrid("EmptyVariable");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_SENSOR:
             _variableNameLabel->setToolTip(tr("Enter Name (system or user) for Sensor (e.g. CS2)"));  // NOI18N
             for (int i = 0; i < Conditional::ITEM_TO_SENSOR_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_SENSOR_TEST[i]));
             }
             setVariableNameBox(itemType);
             makeDetailGrid("StandardVariable");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_TURNOUT:
             _variableNameLabel->setToolTip(tr("Enter Name (system or user) for Turnout (e.g. LT12)"));  // NOI18N
             for (int i = 0; i < Conditional::ITEM_TO_LIGHT_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_TURNOUT_TEST[i]));
             }
             setVariableNameBox(itemType);
             makeDetailGrid("StandardVariable");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_LIGHT:
             _variableNameLabel->setToolTip(tr("Enter Name (system or user) for Light (e.g. CL21)"));  // NOI18N
             for (int i = 0; i < Conditional::ITEM_TO_LIGHT_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_LIGHT_TEST[i]));
             }
             setVariableNameBox(itemType);
             makeDetailGrid("StandardVariable");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_SIGNALHEAD:
             _variableNameLabel->setToolTip(tr("Enter Name (system or user) for Signal Head (e.g. IH34)"));  // NOI18N
             loadJComboBoxWithHeadAppearances(_variableSignalBox, _variableNameField->text().trimmed());

             for (int i = 0; i < Conditional::ITEM_TO_SIGNAL_HEAD_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_SIGNAL_HEAD_TEST[i]));
             }

             setVariableNameBox(itemType);
             if (testType == Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS) {
                 makeDetailGrid("SignalAspectVariable");  // NOI18N
             } else {
                 makeDetailGrid("StandardVariable");  // NOI18N
             }

//             _variableNameField.addActionListener(variableSignalHeadNameListener);
             connect(_variableNameField, SIGNAL(editingFinished()), variableSignalHeadNameListener, SLOT(actionPerformed()));
//             _variableStateBox::addActionListener(variableSignalTestStateListener);
             connect(_variableStateBox, SIGNAL(currentIndexChanged(int)), variableSignalTestStateListener, SLOT(actionPerformed()));
             break;

         case Conditional::ITEM_TYPE_SIGNALMAST:
             _variableNameLabel->setToolTip(tr("Enter Name (system or user) for Signal Mast and hit Enter/Return to load aspects"));  // NOI18N
//             _variableNameField.addActionListener(variableSignalMastNameListener);
             connect(_variableNameField, SIGNAL(editingFinished()), variableSignalMastNameListener, SLOT(actionPerformed()));
//             _variableStateBox::addActionListener(variableSignalTestStateListener);
             connect(_variableStateBox, SIGNAL(currentIndexChanged(int)), variableSignalTestStateListener, SLOT(actionPerformed()));
             loadJComboBoxWithMastAspects(_variableSignalBox, _variableNameField->text().trimmed());

             for (int i = 0; i < Conditional::ITEM_TO_SIGNAL_MAST_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_SIGNAL_MAST_TEST[i]));
             }
             setVariableNameBox(itemType);
             if (testType == Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS) {
                 makeDetailGrid("SignalAspectVariable");  // NOI18N
             } else {
                 makeDetailGrid("StandardVariable");  // NOI18N
             }
             break;

         case Conditional::ITEM_TYPE_MEMORY:
             _variableNameLabel->setToolTip(tr("Enter name (system or user) of Memory"));  // NOI18N
             setVariableNameBox(itemType);
             makeDetailGrid("MemoryVariable");  // NOI18N
             compareTypeChanged(testType);   // Force the label update
             break;

         case Conditional::ITEM_TYPE_CONDITIONAL:
             for (int i = 0; i < Conditional::ITEM_TO_CONDITIONAL_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_CONDITIONAL_TEST[i]));
             }
             loadSelectLogixBox();
             makeDetailGrid("ConditionalVariable");  // NOI18N
//             _selectLogixBox::addActionListener(selectLogixBoxListener);
             connect(_selectLogixBox, SIGNAL(currentIndexChanged(int)), selectLogixBoxListener, SLOT(actionPerformed()));
//             _selectConditionalBox::addActionListener(selectConditionalBoxListener);
             connect(_selectConditionalBox, SIGNAL(currentIndexChanged(int)),selectConditionalBoxListener, SLOT(actionPerformed()) );
             break;

         case Conditional::ITEM_TYPE_WARRANT:
             _variableNameLabel->setToolTip(tr("Enter name (system or user) of Warrant"));  // NOI18N
             for (int i = 0; i < Conditional::ITEM_TO_WARRANT_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_WARRANT_TEST[i]));
             }
             setVariableNameBox(itemType);
             makeDetailGrid("StandardVariable");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_CLOCK:
             makeDetailGrid("FastClockVariable");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_OBLOCK:
         {
             _variableNameLabel->setToolTip(tr("Enter name (system or user) of OBlock"));  // NOI18N
             _variableStateBox->clear();
             QStringListIterator names(OBlock::getLocalStatusNames());
             while (names.hasNext()) {
                 _variableStateBox->addItem(names.next());
             }
             setVariableNameBox(itemType);
             makeDetailGrid("StandardVariable");  // NOI18N
             break;
         }
         case Conditional::ITEM_TYPE_ENTRYEXIT:
             _variableNameLabel->setToolTip(tr("Enter name of Entry/Exit Pair"));  // NOI18N
             _variableNameField->setText(_curVariable->getName());
             for (int i = 0; i < Conditional::ITEM_TO_ENTRYEXIT_TEST.length(); i++) {
                 _variableStateBox->addItem(
                         ConditionalVariable::describeState(Conditional::ITEM_TO_ENTRYEXIT_TEST[i]));
             }
             setVariableNameBox(itemType);
             makeDetailGrid("StandardVariable");  // NOI18N
             break;

         default:
             break;
     }
 }

 /**
  * Update the name combo box selection based on the current contents of the
  * name field. Called by variableItemChanged
  *
  * @since 4.7.3
  * @param itemType The item type, such as sensor or turnout.
  */
 void ConditionalTreeEdit::setVariableNameBox(int itemType) {
     if (_selectionMode !=  SelectionMode::USECOMBO) {
         return;
     }
     _comboNameBox = createNameBox(itemType);
     if (_comboNameBox ==  NULL) {
         return;
     }
     // Select the current entry, add the listener
//     _comboNameBox->setCheckedBeanByName(_curVariable->getName());
//     _comboNameBox::addActionListener(new NameBoxListener(_variableNameField));
     NameBoxListener* listener = new NameBoxListener(_variableNameField, this);
     connect(_comboNameBox, SIGNAL(currentIndexChanged(int)), listener, SLOT(actionPerformed()));
     _comboNameBox->installEventFilter(this);
 }

 // ------------ Variable detail methods ------------
 /**
  * Respond to Cancel variable button
  */
 void ConditionalTreeEdit::cancelEditVariable() {
     if (_newVariableItem) {
         _newVariableItem = false;
         deletePressed();
     }
     cleanUpVariable();
 }

 /**
  * Respond to Update Variable button in the Edit Variable pane.
  */
 void ConditionalTreeEdit::updateVariable() {
     if (!validateVariable()) {
         return;
     }
     _newVariableItem = false;
     _curConditional->setStateVariables(_variableList);

     // Update conditional references
     QSet<QString> newTargetNames = QSet<QString>();
     loadReferenceNames(*_variableList, newTargetNames);
     updateWhereUsed(_oldTargetNames->toList(), newTargetNames.toList(), _curNodeName);

     // Update the tree nodeChanged
     _curNode->setText(buildNodeText("Variable", _curVariable, _curNodeRow));  // NOI18N
     _cdlModel->nodeChanged(_curNode);
     cleanUpVariable();
 }

 /**
  * Clean up: Cancel, Update and Delete Variable buttons.
  */
 void ConditionalTreeEdit::cleanUpVariable() {
     if (_logicType != Conditional::MIXED) {
         setMoveButtons();
     }
 }

 /**
  * Load the Logix selection box. Set the selection to the current Logix
  *
  * @since 4.7.4
  */
 void ConditionalTreeEdit::loadSelectLogixBox() {
     // Get the current Logix name for selecting the current combo box row
     QString cdlName = _curVariable->getName();
     QString lgxName;
     if (cdlName.length() == 0 || (_curVariable->getType() != Conditional::TYPE_CONDITIONAL_TRUE
             && _curVariable->getType() != Conditional::TYPE_CONDITIONAL_FALSE)) {
         // Use the current logix name for "add" state variable
         lgxName = _curLogix->getSystemName();
     } else {
         Logix* x = _conditionalManager->getParentLogix(cdlName);
         if (x ==  NULL) {
             log->error(tr("Unable to find the Logix for %1, using the current Logix").arg( cdlName));  // NOI18N
             lgxName = _curLogix->getSystemName();
         } else {
             lgxName = x->getSystemName();
         }
     }

     _selectLogixBox->clear();
     _selectLogixList->clear();

     QString itemKey = "";
     for (QString xName : _logixManager->getSystemNameList()) {
         if (xName ==  ("SYS")) {  // NOI18N
             // Cannot refer to sensor name groups
             continue;
         }
         Logix* x = _logixManager->getLogix(xName);
         QString uName = x->getUserName();
         QString itemName = "";
         if (uName ==  NULL || uName.length() < 1) {
             itemName = xName;
         } else {
             itemName = uName + " ( " + xName + " )";
         }
         _selectLogixBox->addItem(itemName);
         _selectLogixList->append(xName);
         if (lgxName ==  (xName)) {
             itemKey = itemName;
         }
     }
     _selectLogixBox->setCurrentText(itemKey);
//     JComboBoxUtil::setupComboBoxMaxRows(_selectLogixBox);
     loadSelectConditionalBox(lgxName);
 }

 /**
  * Load the Conditional selection box. The first row is a prompt
  *
  * @since 4.7.4
  * @param logixName The Logix system name for selecting the owned
  *                  Conditionals
  */
 void ConditionalTreeEdit::loadSelectConditionalBox(QString logixName) {
     // Get the current Conditional name for selecting the current combo box row
     QString cdlName = _curVariable->getName();

     _selectConditionalBox->clear();
     _selectConditionalList->clear();

     // Create the first row
     QString itemKey = tr("SelectFirstRow");  // NOI18N
     _selectConditionalBox->addItem(itemKey);
     _selectConditionalList->append("-None-");  // NOI18N

     Logix* x = (Logix*)_logixManager->getBySystemName(logixName);
     if (x ==  NULL) {
         log->error(tr("Logix '%1' not found while building the conditional list").arg( logixName));  // NOI18N
         return;
     }
     if (x->getNumConditionals() == 0) {
         return;
     }
     for (QString cName : _conditionalManager->getSystemNameListForLogix(x)) {
         Conditional* c = _conditionalManager->getConditional(cName);
         if (_curConditional->getSystemName() ==  (c->getSystemName())) {
             // Don't add myself to the list
             continue;
         }
         QString uName = c->getUserName();
         QString itemName = "";
         if (uName ==  NULL || uName.length() < 1) {
             itemName = cName;
         } else {
             itemName = uName + " ( " + cName + " )";
         }
         _selectConditionalBox->addItem(itemName);
         _selectConditionalList->append(cName);
         if (cdlName ==  (cName)) {
             itemKey = itemName;
         }
     }
     _selectConditionalBox->setCurrentText(itemKey);
//     JComboBoxUtil::setupComboBoxMaxRows(_selectConditionalBox);
 }

 /**
  * Check if Memory type in a Conditional was changed by the user.
  * <p>
  * Update GUI if it has.
  *
  * @param testType One of the four types
  */
 /*private*/ void ConditionalTreeEdit::compareTypeChanged(int testType) {
     if ((testType == Conditional::TYPE_MEMORY_COMPARE)
             || (testType == Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE)) {
         _variableMemoryValueLabel->setText(tr("Memory Value"));  // NOI18N
         _variableMemoryValueLabel->setToolTip(tr("Enter Memory name whose value is compared"));  // NOI18N
     } else {
         _variableMemoryValueLabel->setText(tr("Literal Value"));  // NOI18N
         _variableMemoryValueLabel->setToolTip(tr("Enter Value to be compared"));  // NOI18N
     }
 }

 /**
  * Fetch valid appearances for a given Signal Head.
  * <p>
  * Warn if head is not found.
  *
  * @param box            the comboBox on the setup pane to fill
  * @param signalHeadName user or system name of the Signal Head
  */
 void ConditionalTreeEdit::loadJComboBoxWithHeadAppearances(QComboBox* box, QString signalHeadName) {
     box->clear();
     log->debug("loadJComboBoxWithSignalHeadAppearances called with name: " + signalHeadName);  // NOI18N
     SignalHead* h = ((SignalHeadManager*) InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
     if (h ==  NULL) {
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
 void ConditionalTreeEdit::loadJComboBoxWithMastAspects(QComboBox* box, QString mastName) {
     box->clear();
     SignalMast* m =((SignalMastManager*) InstanceManager::getDefault("SignalMastManager"))->getSignalMast(mastName);
     if (m ==  NULL) {
         box->addItem(tr("(Type Signal Mast name in the System/User Name field and hit Enter)"));  // NOI18N
     } else {
         QVector<QString> v = m->getValidAspects();
         for (int i = 0; i < v.size(); i++) {
             box->addItem(v.value(i));
         }
         box->setCurrentText(m->getAspect());
     }
 }

 // ------------ Variable update processes ------------
 /**
  * Validate Variable data from Edit Variable panel, and transfer it to
  * current variable object as appropriate.
  * <p>
  * Messages are sent to the user for any errors found. This routine returns
  * false immediately after finding the first error, even if there might be
  * more errors.
  *
  * @return true if all data checks out OK, otherwise false
  */
bool ConditionalTreeEdit::validateVariable() {
     QString name = _variableNameField->text().trimmed();
     _variableNameField->setText(name);
     _curVariable->setDataString("");
     _curVariable->setNum1(0);
     _curVariable->setNum2(0);

     updateVariableOperator();
     updateVariableNegation();
     _curVariable->setTriggerActions(_variableTriggerActions->isChecked());

     int itemType = _variableItemBox->currentIndex();
     int testType = 0;
     switch (itemType) {
         case Conditional::ITEM_TYPE_SENSOR:
             testType = Conditional::ITEM_TO_SENSOR_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_TURNOUT:
             testType = Conditional::ITEM_TO_TURNOUT_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_LIGHT:
             testType = Conditional::ITEM_TO_LIGHT_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_SIGNALHEAD:
             testType = Conditional::ITEM_TO_SIGNAL_HEAD_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_SIGNALMAST:
             testType = Conditional::ITEM_TO_SIGNAL_MAST_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_MEMORY:
             testType = Conditional::ITEM_TO_MEMORY_TEST[_variableCompareTypeBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_CONDITIONAL:
             testType = Conditional::ITEM_TO_CONDITIONAL_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_WARRANT:
             testType = Conditional::ITEM_TO_WARRANT_TEST[_variableStateBox->currentIndex()];
             break;
         case Conditional::ITEM_TYPE_CLOCK:
             testType = Conditional::TYPE_FAST_CLOCK_RANGE;
             break;
         case Conditional::ITEM_TYPE_OBLOCK:
             testType = Conditional::TYPE_BLOCK_STATUS_EQUALS;
             break;
         case Conditional::ITEM_TYPE_ENTRYEXIT:
             testType = Conditional::ITEM_TO_ENTRYEXIT_TEST[_variableStateBox->currentIndex()];
             break;
         default:
             JOptionPane::showMessageDialog(_editLogixFrame,
                     tr("Select a Variable Type or press [Cancel]."), tr("Error"), // NOI18N
                     JOptionPane::ERROR_MESSAGE);
             return false;
     }
     _curVariable->setType(testType);
     if (log->isDebugEnabled()) {
         log->debug("validateVariable: itemType= " + QString::number(itemType) + ", testType= " + QString::number(testType));  // NOI18N
     }
     switch (itemType) {
         case Conditional::ITEM_TYPE_SENSOR:
             name = validateSensorReference(name);
             if (name ==  NULL) {
                 return false;
             }
             break;
         case Conditional::ITEM_TYPE_TURNOUT:
             name = validateTurnoutReference(name);
             if (name ==  NULL) {
                 return false;
             }
             break;
         case Conditional::ITEM_TYPE_CONDITIONAL:
     {
             name = validateConditionalReference(name);
             if (name ==  NULL) {
                 return false;
             }
             _curVariable->setName(name);
             Conditional* c = _conditionalManager->getBySystemName(name);
             if (c ==  NULL) {
                 return false;
             }
             QString uName = c->getUserName();
             if (uName ==  NULL || uName.isEmpty()) {
                 _curVariable->setGuiName(c->getSystemName());
             } else {
                 _curVariable->setGuiName(uName);
             }
             break;
     }
         case Conditional::ITEM_TYPE_LIGHT:
             name = validateLightReference(name);
             if (name ==  NULL) {
                 return false;
             }
             break;
         case Conditional::ITEM_TYPE_MEMORY:
     {
             name = validateMemoryReference(name);
             if (name ==  NULL) {
                 return false;
             }
             QString name2 = _variableData1Field->text();
             if ((testType == Conditional::TYPE_MEMORY_COMPARE)
                     || (testType == Conditional::TYPE_MEMORY_COMPARE_INSENSITIVE)) {
                 name2 = validateMemoryReference(name2);
                 if (name2 ==  NULL) {
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
             name = "Clock";  // NOI18N
             break;
     }
         case Conditional::ITEM_TYPE_SIGNALHEAD:
     {
             name = validateSignalHeadReference(name);
             if (name ==  NULL) {
                 return false;
             }
             if (testType == Conditional::TYPE_SIGNAL_HEAD_APPEARANCE_EQUALS) {
                 QString appStr = _variableSignalBox->currentText();
                 int type = ConditionalVariable::stringToVariableTest(appStr);
                 if (type < 0) {
                     JOptionPane::showMessageDialog(_editLogixFrame,
                             tr("Select an Appearance. You must hit the Enter/Return key\nafter entering a name with the cursor in the name field."), tr("ErrorTitle"), // NOI18N
                             JOptionPane::ERROR_MESSAGE);
                     return false;
                 }
                 _curVariable->setType(type);
                 _curVariable->setDataString(appStr);
                 if (log->isDebugEnabled()) {
                     log->debug("SignalHead \"" + name + "\"of type '" + QString::number(testType) // NOI18N
                             + "' _variableSignalBox::getSelectedItem()= "
                             + _variableSignalBox->currentText());
                 }
             }
             break;
     }
         case Conditional::ITEM_TYPE_SIGNALMAST:
     {
             name = validateSignalMastReference(name);
             if (name ==  NULL) {
                 return false;
             }
             if (testType == Conditional::TYPE_SIGNAL_MAST_ASPECT_EQUALS) {
                 if (_variableSignalBox->currentIndex() < 0) {
                     JOptionPane::showMessageDialog(_editLogixFrame,
                             tr("Select an Aspect.  You may need to hit the Enter/Return key\nwith the cursor in the name field."), tr("Error"), // NOI18N
                             JOptionPane::ERROR_MESSAGE);
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
             if (name ==  NULL) {
                 return false;
             }
             break;
         case Conditional::ITEM_TYPE_OBLOCK:
     {
             name = validateOBlockReference(name);
             if (name ==  NULL) {
                 return false;
             }
             QString str = _variableStateBox->currentText();
             _curVariable->setDataString(OBlock::getSystemStatusName(str));
             if (log->isDebugEnabled()) {
                 log->debug("OBlock \"" + name + "\"of type '" + QString::number(testType) // NOI18N
                         + "' _variableStateBox::getSelectedItem()= " // NOI18N
                         + _variableStateBox->currentText());
             }
             break;
     }
         case Conditional::ITEM_TYPE_ENTRYEXIT:
             name = validateEntryExitReference(name);
             if (name ==  NULL) {
                 return false;
             }
             break;
         default:
             JOptionPane::showMessageDialog(_editLogixFrame,
                     tr("Select a Variable Type or press [Cancel]."), tr("Error"), // NOI18N
                     JOptionPane::ERROR_MESSAGE);
             return false;
     }
     _curVariable->setName(name);
    bool result = _curVariable->evaluate();
     if (log->isDebugEnabled()) {
         log->debug("State Variable \"" + name + "\"of type '" // NOI18N
                 + ConditionalVariable::getTestTypeString(testType)
                 + "' state= " + result + " type= " + _curVariable->getType());
     }
     if (_curVariable->getType() == Conditional::TYPE_NONE) {
         JOptionPane::showMessageDialog(_editLogixFrame,
                 tr("Select a state for this variable."), tr("ErrorTitle"), // NOI18N
                 JOptionPane::ERROR_MESSAGE);
         return false;
     }
     return (true);
 }

 /**
  * Update the variable operation If a change has occurred, also update the
  * antecedent and antecedent tree node
  */
 //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::updateVariableOperator() {
     int oldOper = _curVariable->getOpern();
     if (_curNodeRow > 0) {
         if (_variableOperBox->currentIndex() == 0) {
             _curVariable->setOpern(Conditional::OPERATOR_AND);
         } else {
             _curVariable->setOpern(Conditional::OPERATOR_OR);
         }
     } else {
         _curVariable->setOpern(Conditional::OPERATOR_NONE);
     }
     if (_curVariable->getOpern() != oldOper) {
         makeAntecedent();
         _curConditional->setLogicType(_logicType, _antecedent);
         ConditionalTreeNode* antLeaf = (ConditionalTreeNode*) ((ConditionalTreeNode*) _curNode->getParent())->getPreviousSibling();
         antLeaf->setText(buildNodeText("Antecedent", _curConditional, 0));  // NOI18N
         _cdlModel->nodeChanged(antLeaf);
     }
 }

 /**
  * Update the variable negation If a change has occurred, also update the
  * antecedent and antecedent tree node
  */
 //@SuppressFBWarnings(value = "BC_UNCONFIRMED_CAST_OF_RETURN_VALUE", justification = "Except for the root node, all nodes are ConditionalTreeNode")  // NOI18N
 void ConditionalTreeEdit::updateVariableNegation() {
    bool state = _curVariable->isNegated();
     if (_variableNegated->isChecked()) {
         _curVariable->setNegation(true);
     } else {
         _curVariable->setNegation(false);
     }
     if (_curVariable->isNegated() != state) {
         makeAntecedent();
         _curConditional->setLogicType(_logicType, _antecedent);
         ConditionalTreeNode* antLeaf = (ConditionalTreeNode*) ((ConditionalTreeNode*) _curNode->getParent())->getPreviousSibling();
         antLeaf->setText(buildNodeText("Antecedent", _curConditional, 0));
         _cdlModel->nodeChanged(antLeaf);
     }
 }

 /**
  * Update the conditional variable list and refresh the local copy.
  * The parent Logix is de-activated and re-activated.  This insures
  * that listeners are properly handled.
  * @since 4.11.2
  */
 void ConditionalTreeEdit::updateVariableList() {
     _curLogix->deActivateLogix();
     _curConditional->setStateVariables(_variableList);
     _variableList = _curConditional->getCopyOfStateVariables();
     _curLogix->activateLogix();
 }

 // ------------ Variable detail listeners ------------
// transient ActionListener  = new ActionListener() {
 VariableSignalHeadNameListener::VariableSignalHeadNameListener(ConditionalTreeEdit *cfe) { this->cte = cte;}
     //@Override
     /*public*/ void VariableSignalHeadNameListener::actionPerformed() {
         // fired when signal head name changes, but only
         // while in signal head mode
         cte->log->debug("variableSignalHeadNameListener fires; _variableNameField : " + cte->_variableNameField->text().trimmed());  // NOI18N
         cte->loadJComboBoxWithHeadAppearances(cte->_variableSignalBox, cte->_variableNameField->text().trimmed());
     }
 //};

 //transient ActionListener variableSignalMastNameListener = new ActionListener() {
 VariableSignalMastNameListener::VariableSignalMastNameListener(ConditionalTreeEdit *cte) { this->cte = cte;}
     //@Override
     /*public*/ void VariableSignalMastNameListener::actionPerformed() {
         // fired when signal mast name changes, but only
         // while in signal mast mode
         cte->log->debug("variableSignalMastNameListener fires; _variableNameField : " + cte->_variableNameField->text().trimmed());  // NOI18N
         cte->loadJComboBoxWithMastAspects(cte->_variableSignalBox, cte->_variableNameField->text().trimmed());
     }
 //};

 //transient ActionListener variableSignalTestStateListener = new ActionListener() {
 CTEVariableSignalTestStateListener::CTEVariableSignalTestStateListener(ConditionalTreeEdit *cte) { this->cte = cte;}
     //@Override
     /*public*/ void CTEVariableSignalTestStateListener::actionPerformed() {
         cte->log->debug("variableSignalTestStateListener fires; _variableItemBox->currentIndex()= " // NOI18N
                 + QString::number(cte->_variableItemBox->currentIndex())
                 + "\" _variableStateBox->currentIndex()= \"" + QString::number(cte->_variableStateBox->currentIndex()) + "\"");

         int itemType = cte->_variableItemBox->currentIndex();

         if (cte->_variableStateBox->currentIndex() == 1) {
             if (itemType == Conditional::ITEM_TYPE_SIGNALHEAD) {
                 cte->loadJComboBoxWithHeadAppearances(cte->_variableSignalBox, cte->_variableNameField->text().trimmed());
                 cte->_detailGrid->setVisible(false);
                 cte->makeDetailGrid("SignalAspectVariable");  // NOI18N
             } else if (itemType == Conditional::ITEM_TYPE_SIGNALMAST) {
                 cte->loadJComboBoxWithMastAspects(cte->_variableSignalBox, cte->_variableNameField->text().trimmed());
                 cte->_detailGrid->setVisible(false);
                 cte->makeDetailGrid("SignalAspectVariable");  // NOI18N
             } else {
                 cte->_detailGrid->setVisible(false);
                 cte->makeDetailGrid("StandardVariable");  // NOI18N
             }
         } else {
             cte->_detailGrid->setVisible(false);
             cte->makeDetailGrid("StandardVariable");  // NOI18N
         }
     }
 //};

 //transient ActionListener selectLogixBoxListener = new ActionListener() {
 SelectLogixBoxListener::SelectLogixBoxListener(ConditionalTreeEdit *cte){this->cte = cte;}
     //@Override
     /*public*/ void SelectLogixBoxListener::actionPerformed() {
         int lgxIndex = cte->_selectLogixBox->currentIndex();
         if (lgxIndex >= 0 && lgxIndex < cte->_selectLogixList->size()) {
             QString lgxName = cte->_selectLogixList->value(lgxIndex);
             cte->loadSelectConditionalBox(lgxName);
         }
     }
 //};

 //transient ActionListener selectConditionalBoxListener = new ActionListener() {
 SelectConditionalBoxListener::SelectConditionalBoxListener(ConditionalTreeEdit *cte) {this->cte = cte;}
     //@Override
     /*public*/ void SelectConditionalBoxListener::actionPerformed() {
         int cdlIndex = cte->_selectConditionalBox->currentIndex();
         if (cdlIndex > 0 && cdlIndex < cte->_selectConditionalList->size()) {
             QString cdlName = cte->_selectConditionalList->value(cdlIndex);
             cte->_variableNameField->setText(cdlName);
         }
     }
 //};

 //transient ActionListener compareTypeBoxListener = new ActionListener() {
 CompareTypeBoxListener::CompareTypeBoxListener(ConditionalTreeEdit *cte){this->cte = cte;}
     //@Override
     /*public*/ void CompareTypeBoxListener::actionPerformed() {
         int selection = cte->_variableCompareTypeBox->currentIndex();
         cte->compareTypeChanged(Conditional::ITEM_TO_MEMORY_TEST[selection]);
     }
 //};

 // ============ Edit Action Section ============
 /**
  * Called once during class initialization to define the GUI objects Where
  * possible, the combo box content is loaded
  */
 void ConditionalTreeEdit::buildActionComponents() {
     // Item Type
     _actionItemBox = new QComboBox();
     for (int i = 0; i <= Conditional::ITEM_TYPE_LAST_ACTION; i++) {
         _actionItemBox->addItem(DefaultConditionalAction::getItemTypeString(i));
     }
     //JComboBoxUtil::setupComboBoxMaxRows(_actionItemBox);
//     _actionItemBox::addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             int newActionItem = _actionItemBox->currentIndex();
//             if (log->isDebugEnabled()) {
//                 log->debug("_actionItemBox Listener: new = {}, curr = {}, row = {}",  // NOI18N
//                         newActionItem, _curActionItem, _curNodeRow);
//             }
//             if (newActionItem != _curActionItem) {
//                 if (_curNodeRow >= 0) {
//                     _curAction = new DefaultConditionalAction();
//                     _actionList->set(_curNodeRow, _curAction);
//                 }
//                 _curActionItem = newActionItem;
//             }
//             actionItemChanged(newActionItem);
//         }
//     });
  connect(_actionItemBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_actionItemBox_currentIndexChanged()));
     // Item Name
     _actionNameField = new JTextField(20);

     // Action Type Box
     _actionTypeBox = new QComboBox();
     _actionTypeBox->addItem("");

     // Action State Box
     _actionBox = new QComboBox();
     _actionBox->addItem("");

     // Short strings: Delay time, memory value/copy target
     _shortActionString = new JTextField(15);

     // On Change / Trigger options
     _actionOptionBox = new QComboBox();

     // File Selector
     _actionSetButton = new QPushButton("..."); // "File" replaced by ...
//     _actionSetButton.addActionListener(new ActionListener() {
//         //@Override
//         /*public*/ void actionPerformed(ActionEvent e) {
//             validateAction();
//             setFileLocation(e);
//         }
//     });
connect(_actionSetButton, SIGNAL(clicked(bool)), this, SLOT(on_actionSetButton_clicked()));
     // File names, etc.
     _longActionString = new JTextField(30);
 }

 void ConditionalTreeEdit::on_actionItemBox_currentIndexChanged()
 {
  int newActionItem = _actionItemBox->currentIndex();
  if (log->isDebugEnabled()) {
      log->debug(tr("_actionItemBox Listener: new = %1, curr = %2, row = %3").arg(newActionItem).arg(_curActionItem).arg(_curNodeRow));
  }
  if (newActionItem != _curActionItem) {
      if (_curNodeRow >= 0) {
          _curAction = new DefaultConditionalAction();
          _actionList->     replace(_curNodeRow, _curAction);
      }
      _curActionItem = newActionItem;
  }
  actionItemChanged(newActionItem);

 }

 void ConditionalTreeEdit::on_actionSetButton_clicked()
 {
  validateAction();
  setFileLocation(/*e*/);
 }
 // ------------ Make Action Edit Grid Panels ------------
 /**
  * Create a one row grid with just the Action Item box This is the base for
  * larger grids as well as the initial grid for new Actions
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeEmptyActionGrid(GridBagConstraints c) {
     // Action item box
     c.gridy = 0;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row0Label = new QLabel(tr("Action Group"));  // NOI18N
     row0Label->setToolTip(tr("Select action item for Conditional to execute"));  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_actionItemBox, c);
 }

 /*
  * Create the standard Name and Type rows
  * The name field will be either a text field or a combo box
  * The name field label is a variable to support run time changes
  * @param c The constraints object used for the grid construction
  * @param finalRow Controls whether the tigger combo box is included
  */
 void ConditionalTreeEdit::makeNameTypeActionGrid(GridBagConstraints c,bool finalRow) {
     makeEmptyActionGrid(c);

     int actionType = _curAction->getType();
     int itemType = Conditional::ACTION_TO_ITEM[actionType];

     // Name Field
     c.gridy = 1;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_actionNameLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     if ((_selectionMode ==  SelectionMode::USECOMBO)
             && (itemType != Conditional::ITEM_TYPE_AUDIO)) {
         _gridPanelLayout->addWidget(_comboNameBox, c);
     } else {
         _gridPanelLayout->addWidget(_actionNameField, c);
     }

     // Action Type Box
     c.gridy = 2;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("Action Type"));  // NOI18N
     row5Label->setToolTip(tr("Select type of action, or select None if no action is needed."));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_actionTypeBox, c);

     if (itemType == 0) {
         // Skip the change/trigger section for new Actions
         return;
     }

     if (finalRow) {
         makeChangeTriggerActionGrid(c);
     }
 }

 /*
  * Create the standard Type row
  * @param c The constraints object used for the grid construction
  * @param finalRow Controls whether the tigger combo box is included
  */
 void ConditionalTreeEdit::makeTypeActionGrid(GridBagConstraints c,bool finalRow) {
     makeEmptyActionGrid(c);

     int actionType = _curAction->getType();
     int itemType = Conditional::ACTION_TO_ITEM[actionType];

     // Action Type Box
     c.gridy = 1;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row5Label = new QLabel(tr("Action Type"));  // NOI18N
     row5Label->setToolTip(tr("Select type of action, or select None if no action is needed."));  // NOI18N
     _gridPanelLayout->addWidget(row5Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_actionTypeBox, c);

     if (itemType == 0) {
         // Skip the change/trigger section for new Actions
         return;
     }

     if (finalRow) {
         makeChangeTriggerActionGrid(c);
     }
 }

 /**
  * Add the action box to the grid
  *
  * @param c        The constraints object used for the grid construction
  * @param finalRow Controls whether the tigger combo box is included
  */
 void ConditionalTreeEdit::makeStandardActionGrid(GridBagConstraints c,bool finalRow) {
     makeNameTypeActionGrid(c, false);

     // Action Box
     c.gridy = 3;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_actionBoxLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_actionBox, c);

     if (finalRow) {
         makeChangeTriggerActionGrid(c);
     }
 }

 /**
  * Add the short name field to the grid
  *
  * @param c          The constraints object used for the grid construction
  * @param includeBox Controls whether the normal action type combo box is
  *                   included
  */
 void ConditionalTreeEdit::makeShortFieldActionGrid(GridBagConstraints c,bool includeBox) {
     if (includeBox) {
         makeStandardActionGrid(c, false);
     } else {
         makeNameTypeActionGrid(c, false);
     }

     // Add the short text field
     c.gridy = 4;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_shortActionLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_shortActionString, c);

     makeChangeTriggerActionGrid(c);
 }

 /**
  * Just a short text field, no name field Used by set clock and jython
  * command
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeTypeShortActionGrid(GridBagConstraints c) {
     makeTypeActionGrid(c, false);

     // Add the short text field
     c.gridy = 2;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_shortActionLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_shortActionString, c);

     makeChangeTriggerActionGrid(c);
 }

 /**
  * Add the file selection components
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeFileActionGrid(GridBagConstraints c) {
     makeTypeActionGrid(c, false);

     // Add the file selecttor
     c.gridy = 2;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     _gridPanelLayout->addWidget(_shortActionLabel, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_actionSetButton, c);

     c.gridwidth = 2;    // span both columns
     // Add the long text field
     c.gridy = 3;
     c.gridx = 0;
     c.anchor = GridBagConstraints::CENTER;
     _gridPanelLayout->addWidget(_longActionString, c);
     c.gridwidth = 1;

     makeChangeTriggerActionGrid(c);
 }

 /**
  * Add the change/trigger box the grid This is the last item in an Action
  * and is usually called from one of the other entry points
  *
  * @param c The constraints object used for the grid construction
  */
 void ConditionalTreeEdit::makeChangeTriggerActionGrid(GridBagConstraints c) {
     // Action item box
     c.gridy = 9;
     c.gridx = 0;
     c.anchor = GridBagConstraints::EAST;
     QLabel* row0Label = new QLabel(tr("Change Option"));  // NOI18N
     row0Label->setToolTip(tr("Select when action should occur"));  // NOI18N
     _gridPanelLayout->addWidget(row0Label, c);
     c.gridx = 1;
     c.anchor = GridBagConstraints::WEST;
     _gridPanelLayout->addWidget(_actionOptionBox, c);
 }

 // ------------ Main Action methods ------------
 /**
  * Set display to show current action (curAction) parameters.
  */
 void ConditionalTreeEdit::initializeActionVariables() {
     int actionType = _curAction->getType();
     int itemType = Conditional::ACTION_TO_ITEM[actionType];
     if (log->isDebugEnabled()) {
         log->debug("initializeActionVariables: itemType= " + QString::number(itemType) + ", actionType= " + QString::number(actionType));  // NOI18N
     }
     _actionItemBox->setCurrentIndex(itemType);
     _actionNameField->setText(_curAction->getDeviceName());
     switch (itemType) {
         case Conditional::TYPE_NONE:
             _actionNameField->setText("");
             break;

         case Conditional::ITEM_TYPE_SENSOR:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_SENSOR_ACTION, actionType) + 1);
             if ((actionType == Conditional::ACTION_RESET_DELAYED_SENSOR)
                     || (actionType == Conditional::ACTION_DELAYED_SENSOR)) {
                 _shortActionString->setText(_curAction->getActionString());
             }
             if (actionType == Conditional::ACTION_SET_SENSOR
                     || actionType == Conditional::ACTION_DELAYED_SENSOR
                     || actionType == Conditional::ACTION_RESET_DELAYED_SENSOR) {
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
                     Conditional::ITEM_TO_TURNOUT_ACTION, actionType) + 1);
             if ((actionType == Conditional::ACTION_RESET_DELAYED_TURNOUT)
                     || (actionType == Conditional::ACTION_DELAYED_TURNOUT)) {
                 _shortActionString->setText(_curAction->getActionString());
             }
             if ((actionType == Conditional::ACTION_SET_TURNOUT)
                     || (actionType == Conditional::ACTION_RESET_DELAYED_TURNOUT)
                     || (actionType == Conditional::ACTION_DELAYED_TURNOUT)) {
                 if (_curAction->getActionData() == Turnout::CLOSED) {
                     _actionBox->setCurrentIndex(0);
                 } else if (_curAction->getActionData() == Turnout::THROWN) {
                     _actionBox->setCurrentIndex(1);
                 } else if (_curAction->getActionData() == Route::TOGGLE) {
                     _actionBox->setCurrentIndex(2);
                 }
             } else if (actionType == Conditional::ACTION_LOCK_TURNOUT) {
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
                     Conditional::ITEM_TO_LIGHT_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_SET_LIGHT) {
                 if (_curAction->getActionData() == Light::ON) {
                     _actionBox->setCurrentIndex(0);
                 } else if (_curAction->getActionData() == Light::OFF) {
                     _actionBox->setCurrentIndex(1);
                 } else if (_curAction->getActionData() == Route::TOGGLE) {
                     _actionBox->setCurrentIndex(2);
                 }
             } else if ((actionType == Conditional::ACTION_SET_LIGHT_INTENSITY)
                     || (actionType == Conditional::ACTION_SET_LIGHT_TRANSITION_TIME)) {
                 _shortActionString->setText(_curAction->getActionString());
             }
             break;

         case Conditional::ITEM_TYPE_SIGNALHEAD:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_SIGNAL_HEAD_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                 loadJComboBoxWithHeadAppearances(_actionBox, _actionNameField->text().trimmed());
             }
             break;

         case Conditional::ITEM_TYPE_SIGNALMAST:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_SIGNAL_MAST_ACTION, actionType) + 1);
             break;

         case Conditional::ITEM_TYPE_CLOCK:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_CLOCK_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                 int time = _curAction->getActionData();
                 _longActionString->setText(formatTime(time / 60, time - ((time / 60) * 60)));
                 _actionNameField->setText("");
             }
             break;

         case Conditional::ITEM_TYPE_MEMORY:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_MEMORY_ACTION, actionType) + 1);
             _shortActionString->setText(_curAction->getActionString());
             break;

         case Conditional::ITEM_TYPE_LOGIX:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_LOGIX_ACTION, actionType) + 1);
             break;

         case Conditional::ITEM_TYPE_WARRANT:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_WARRANT_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_CONTROL_TRAIN) {
                 if (_curAction->getActionData() == Warrant::HALT) {
                     _actionBox->setCurrentIndex(0);
                 } else if (_curAction->getActionData() == Warrant::RESUME) {
                     _actionBox->setCurrentIndex(1);
                 } else if (_curAction->getActionData() == Warrant::ABORT) {
                     _actionBox->setCurrentIndex(2);
                 }
             } else if (actionType == Conditional::ACTION_SET_TRAIN_ID
                     || actionType == Conditional::ACTION_SET_TRAIN_NAME
                     || actionType == Conditional::ACTION_THROTTLE_FACTOR) {
                 _shortActionString->setText(_curAction->getActionString());
             }
             break;

         case Conditional::ITEM_TYPE_OBLOCK:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_OBLOCK_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_SET_BLOCK_VALUE) {
                 _shortActionString->setText(_curAction->getActionString());
             }
             break;

         case Conditional::ITEM_TYPE_ENTRYEXIT:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_ENTRYEXIT_ACTION, actionType) + 1);
             break;

         case Conditional::ITEM_TYPE_AUDIO:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_AUDIO_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_PLAY_SOUND) {
                 _longActionString->setText(_curAction->getActionString());
             } else if (actionType == Conditional::ACTION_CONTROL_AUDIO) {
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
                     default:
                         log->warn(tr("Unexpected _curAction->getActionData() of %1").arg( _curAction->getActionData()));  // NOI18N
                         break;
                 }
             }
             break;

         case Conditional::ITEM_TYPE_SCRIPT:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_SCRIPT_ACTION, actionType) + 1);
             if (actionType == Conditional::ACTION_RUN_SCRIPT) {
                 _longActionString->setText(_curAction->getActionString());
             } else if (actionType == Conditional::ACTION_JYTHON_COMMAND) {
                 _shortActionString->setText(_curAction->getActionString());
             }
             break;

         case Conditional::ITEM_TYPE_OTHER:
             _actionTypeBox->setCurrentIndex(DefaultConditional::getIndexInTable(
                     Conditional::ITEM_TO_OTHER_ACTION, actionType) + 1);
             // ACTION_TRIGGER_ROUTE
             break;

         default:
             log->error("Unhandled type: {}", itemType);  // NOI18N
             break;
     }
     _actionOptionBox->setCurrentIndex(_curAction->getOption() - 1);
 }

 /**
  * Respond to a change in an Action Type comboBox
  * <p>
  * Set components visible for the selected type
  *
  * @param type index of the newly selected Action type
  */
 void ConditionalTreeEdit::actionItemChanged(int type) {
     int actionType = _curAction->getType();
     if (log->isDebugEnabled()) {
         log->debug("actionItemChanged: itemType= " + QString::number(type) + ", actionType= " + QString::number(actionType));  // NOI18N
     }
     _detailGrid->setVisible(false);
     //_actionTypeBox::removeActionListener(_actionTypeListener);
     disconnect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), _actionTypeListener, SLOT(actionPerformed()));
     _shortActionString->setText("");
     _longActionString->setText("");
     _actionTypeBox->clear();
     _actionTypeBox->addItem("");
     _actionBox->clear();
     int itemType = Conditional::ACTION_TO_ITEM[actionType];
     if (type != Conditional::TYPE_NONE) {  // actionItem listener choice overrides current item
         itemType = type;
     }
     if (itemType != Conditional::ACTION_TO_ITEM[actionType]) {
         actionType = Conditional::ACTION_NONE;    // chosen item type does not support action type
     }

     //_actionNameField.removeActionListener(actionSignalHeadNameListener);
     disconnect(_actionNameField, SIGNAL(editingFinished()), actionSignalHeadNameListener, SLOT(actionPerformed()));
     //_actionNameField.removeActionListener(actionSignalMastNameListener);
     disconnect(_actionNameField, SIGNAL(editingFinished()), actionSignalMastNameListener, SLOT(actionPerformed()));

     if (_comboNameBox !=  NULL) {
//         for (ActionListener* item : _comboNameBox::getActionListeners()) {
//             _comboNameBox->removeActionListener(item);
//         }
//         _comboNameBox::removeFocusListener(detailFocusEvent);
      disconnect(_comboNameBox);
     }
     setPickWindow("Action", itemType);  // NOI18N

     switch (itemType) {
         case Conditional::TYPE_NONE:
             makeDetailGrid("EmptyAction");  // NOI18N
             break;

         case Conditional::ITEM_TYPE_TURNOUT:
     {
             _actionNameLabel->setToolTip(tr("Enter Name (system or user) for Turnout (e.g. LT12)"));  // NOI18N
             QString turnoutGrid = "NameTypeAction";  // NOI18N
            bool delayTurnout = false;

             for (int i = 0; i < Conditional::ITEM_TO_TURNOUT_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_TURNOUT_ACTION[i]));
             }

             if ((actionType == Conditional::ACTION_RESET_DELAYED_TURNOUT)
                     || (actionType == Conditional::ACTION_DELAYED_TURNOUT)) {
                 delayTurnout = true;
                 _shortActionLabel->setText(tr("Delay Time"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter time (seconds) to wait before setting turnout"));  // NOI18N
             }
             if ((actionType == Conditional::ACTION_SET_TURNOUT)
                     || (actionType == Conditional::ACTION_RESET_DELAYED_TURNOUT)
                     || (actionType == Conditional::ACTION_DELAYED_TURNOUT)) {
                 turnoutGrid = (delayTurnout) ? "ShortFieldAction" : "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Turnout Position"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select Closed or Thrown depending upon how Turnout is to be set"));  // NOI18N
                 _actionBox->addItem(tr("Closed"));  // NOI18N
                 _actionBox->addItem(tr("Thrown"));  // NOI18N
                 _actionBox->addItem(tr("Toggle"));  // NOI18N
             } else if (actionType == Conditional::ACTION_LOCK_TURNOUT) {
                 turnoutGrid = (delayTurnout) ? "ShortFieldAction" : "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Lock State"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select Lock or Unlock"));  // NOI18N
                 _actionBox->addItem(tr("TurnoutUnlock"));  // NOI18N
                 _actionBox->addItem(tr("TurnoutLock"));  // NOI18N
                 _actionBox->addItem(tr("Toggle"));  // NOI18N
             } else if ((actionType == Conditional::ACTION_CANCEL_TURNOUT_TIMERS)
                     || (actionType == Conditional::ACTION_NONE)) {
                 turnoutGrid = "NameTypeActionFinal";  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(turnoutGrid);
             break;
     }
         case Conditional::ITEM_TYPE_SENSOR:
     {
             _actionNameLabel->setToolTip(tr("Enter Name (system or user) for Sensor (e.g. CS2)"));  // NOI18N
             QString sensorGrid = "NameTypeAction";  // NOI18N
            bool delaySensor = false;

             for (int i = 0; i < Conditional::ITEM_TO_SENSOR_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SENSOR_ACTION[i]));
             }
             if ((actionType == Conditional::ACTION_RESET_DELAYED_SENSOR)
                     || (actionType == Conditional::ACTION_DELAYED_SENSOR)) {
                 delaySensor = true;
                 _shortActionLabel->setText(tr("Delay Time"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter time (seconds) to wait before setting sensor"));  // NOI18N
             }
             if ((actionType == Conditional::ACTION_SET_SENSOR)
                     || (actionType == Conditional::ACTION_RESET_DELAYED_SENSOR)
                     || (actionType == Conditional::ACTION_DELAYED_SENSOR)) {
                 sensorGrid = (delaySensor) ? "ShortFieldAction" : "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Sensor State"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select Active or Inactive depending upon how Sensor is to be set"));  // NOI18N
                 _actionBox->addItem(tr("SensorStateActive"));  // NOI18N
                 _actionBox->addItem(tr("SensorStateInactive"));  // NOI18N
                 _actionBox->addItem(tr("Toggle"));  // NOI18N
             } else if ((actionType == Conditional::ACTION_CANCEL_SENSOR_TIMERS)
                     || (actionType == Conditional::ACTION_NONE)) {
                 sensorGrid = "NameTypeActionFinal";  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(sensorGrid);
             break;
         }
         case Conditional::ITEM_TYPE_SIGNALHEAD:
     {
             _actionNameLabel->setToolTip(tr("Enter Name (system or user) for Signal Head (e.g. IH34)"));  // NOI18N
             QString signalHeadGrid = "NameTypeAction";  // NOI18N
             //_actionNameField.addActionListener(actionSignalHeadNameListener);
             connect(_actionNameField, SIGNAL(editingFinished()), actionSignalHeadNameListener, SLOT(actionPerformed()) );

             for (int i = 0; i < Conditional::ITEM_TO_SIGNAL_HEAD_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SIGNAL_HEAD_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                 signalHeadGrid = "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Signal Head Appearance"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select Signal Head Appearance to set"));  // NOI18N
                 loadJComboBoxWithHeadAppearances(_actionBox, _actionNameField->text().trimmed());
             } else if (actionType != Conditional::ACTION_NONE) {
                 signalHeadGrid = "NameTypeActionFinal";  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(signalHeadGrid);
             break;
}
         case Conditional::ITEM_TYPE_SIGNALMAST:
     {
             _actionNameLabel->setToolTip(tr("Enter Name (system or user) for Signal Mast and hit Enter/Return to load aspects"));  // NOI18N
             QString signalMastGrid = "NameTypeAction";  // NOI18N
             //_actionNameField.addActionListener(actionSignalMastNameListener);
             connect(_actionNameField, SIGNAL(editingFinished()), actionSignalMastNameListener, SLOT(actionPerformed()));

             for (int i = 0; i < Conditional::ITEM_TO_SIGNAL_MAST_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SIGNAL_MAST_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_SET_SIGNALMAST_ASPECT) {
                 signalMastGrid = "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Signal Mast Aspect"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select Signal Mast Aspect to set and hit Enter/Return to load aspects"));  // NOI18N
                 loadJComboBoxWithMastAspects(_actionBox, _actionNameField->text().trimmed());
             } else if (actionType != Conditional::ACTION_NONE) {
                 signalMastGrid = "NameTypeActionFinal";  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(signalMastGrid);
             break;
}
         case Conditional::ITEM_TYPE_LIGHT:
     {
             _actionNameLabel->setToolTip(tr("Enter Name (system or user) for Light (e.g. CL21)"));  // NOI18N
             QString lightGrid = "NameTypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_LIGHT_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_LIGHT_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_SET_LIGHT_INTENSITY) {
                 lightGrid = "ShortFieldNoBoxAction";  // NOI18N
                 _shortActionLabel->setText(tr("Light Intensity"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter intensity percentage as an integer 0 to 100."));  // NOI18N
             } else if (actionType == Conditional::ACTION_SET_LIGHT_TRANSITION_TIME) {
                 lightGrid = "ShortFieldNoBoxAction";  // NOI18N
                 _shortActionLabel->setText(tr("Transition Time"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter number of fast clock minutes to transition between 0% and 100%."));  // NOI18N
             } else if (actionType == Conditional::ACTION_SET_LIGHT) {
                 lightGrid = "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Light State"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select On or Off depending upon how Light is to be set"));  // NOI18N
                 _actionBox->addItem(tr("LightOn"));  // NOI18N
                 _actionBox->addItem(tr("LightOff")); // NOI18N
                 _actionBox->addItem(tr("Toggle"));   // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(lightGrid);
             break;
}
         case Conditional::ITEM_TYPE_MEMORY:
     {
             _actionNameLabel->setToolTip(tr("Enter name (system or user) of Memory"));  // NOI18N
             QString memoryGrid = "NameTypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_MEMORY_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_MEMORY_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_COPY_MEMORY) {
                 memoryGrid = "ShortFieldNoBoxAction";  // NOI18N
                 _shortActionLabel->setText(tr("Memory Name"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter name (system or user) of Memory to receive the copied value"));  // NOI18N
             } else if (actionType == Conditional::ACTION_SET_MEMORY) {
                 memoryGrid = "ShortFieldNoBoxAction";  // NOI18N
                 _shortActionLabel->setText(tr("Value"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter Memory name whose value is compared"));  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(memoryGrid);
             break;
}
         case Conditional::ITEM_TYPE_CLOCK:
     {
             QString clockGrid = "TypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_CLOCK_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_CLOCK_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                 clockGrid = "TypeShortAction";  // NOI18N
                 _shortActionLabel->setText(tr("Set Time"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter time (hh:mm) for a 24-hour clock"));  // NOI18N
             } else if ((actionType == Conditional::ACTION_START_FAST_CLOCK)
                     || (actionType == Conditional::ACTION_STOP_FAST_CLOCK)) {
                 clockGrid = "TypeActionFinal";  // NOI18N
             }

             makeDetailGrid(clockGrid);
             break;
}
         case Conditional::ITEM_TYPE_LOGIX:
     {
             _actionNameLabel->setToolTip(tr("Enter name (system or user) of Logix"));  // NOI18N
             QString logixGrid = "NameTypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_LOGIX_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_LOGIX_ACTION[i]));
             }

             if ((actionType == Conditional::ACTION_ENABLE_LOGIX)
                     || (actionType == Conditional::ACTION_DISABLE_LOGIX)) {
                 logixGrid = "NameTypeActionFinal";  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(logixGrid);
             break;
}
         case Conditional::ITEM_TYPE_WARRANT:
     {
             _actionNameLabel->setToolTip(tr("Enter name (system or user) of Warrant"));  // NOI18N
             QString warrantGrid = "NameTypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_WARRANT_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_WARRANT_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_CONTROL_TRAIN) {
                 warrantGrid = "StandardAction";  // NOI18N
                 _actionBoxLabel->setText(tr("Control Command"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select an option to control the train"));  // NOI18N
                 _actionBox->addItem(tr("WarrantHalt"));   // NOI18N
                 _actionBox->addItem(tr("WarrantResume")); // NOI18N
                 _actionBox->addItem(tr("WarrantAbort"));  // NOI18N
             } else if (actionType == Conditional::ACTION_SET_TRAIN_ID
                     || actionType == Conditional::ACTION_SET_TRAIN_NAME
                     || actionType == Conditional::ACTION_THROTTLE_FACTOR) {
                 warrantGrid = "ShortFieldNoBoxAction";  // NOI18N
                 if (actionType == Conditional::ACTION_SET_TRAIN_ID) {
                     _shortActionLabel->setText(tr("Train ID or Address"));  // NOI18N
                     _shortActionLabel->setToolTip(tr("Enter a train ID from the Roster - or enter a DCC address indicating long or short e.g. 1234(L) or 10(S)"));  // NOI18N
                 } else if (actionType == Conditional::ACTION_SET_TRAIN_NAME) {
                     _shortActionLabel->setText(tr("Train Name"));  // NOI18N
                     _shortActionLabel->setToolTip(tr("Enter a name for the train"));  // NOI18N
                 } else { // must be Conditional::ACTION_THROTTLE_FACTOR, so treat as such
                     _shortActionLabel->setText(tr("Throttle Adjustment Factor"));  // NOI18N
                     _shortActionLabel->setToolTip(tr("Enter a decimal number for the throttle setting ratio."));  // NOI18N
                 }
             }

             setActionNameBox(itemType);
             makeDetailGrid(warrantGrid);
             break;
}
         case Conditional::ITEM_TYPE_OBLOCK:
     {
             _actionNameLabel->setToolTip(tr("Enter name (system or user) of OBlock"));  // NOI18N
             QString oblockGrid = "NameTypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_OBLOCK_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_OBLOCK_ACTION[i]));
             }
             if (actionType == Conditional::ACTION_SET_BLOCK_VALUE) {
                 oblockGrid = "ShortFieldNoBoxAction";  // NOI18N
                 _shortActionLabel->setText(tr("Block Value"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter a value to be set into the block"));  // NOI18N
             } else if ((actionType == Conditional::ACTION_DEALLOCATE_BLOCK)
                     || (actionType == Conditional::ACTION_SET_BLOCK_ERROR)
                     || (actionType == Conditional::ACTION_CLEAR_BLOCK_ERROR)
                     || (actionType == Conditional::ACTION_SET_BLOCK_OUT_OF_SERVICE)
                     || (actionType == Conditional::ACTION_SET_BLOCK_IN_SERVICE)) {
                 oblockGrid = "NameTypeActionFinal";  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(oblockGrid);
             break;
}
         case Conditional::ITEM_TYPE_ENTRYEXIT:
     {
             for (int i = 0; i < Conditional::ITEM_TO_ENTRYEXIT_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_ENTRYEXIT_ACTION[i]));
             }
             setActionNameBox(itemType);
             makeDetailGrid("NameTypeActionFinal");
             break;
}
         case Conditional::ITEM_TYPE_AUDIO:
     {
             _actionNameLabel->setToolTip(tr("Enter name (system or user) of OBlock"));  // NOI18N
             QString audioGrid = "TypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_AUDIO_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_AUDIO_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_PLAY_SOUND) {
                 audioGrid = "FileAction";  // NOI18N
                 _shortActionLabel->setText(tr("Select File"));  // NOI18N
                 _actionSetButton->setToolTip(tr("Click for a file selection dialog for choosing a sound file"));  // NOI18N
             } else if (actionType == Conditional::ACTION_CONTROL_AUDIO) {
                 audioGrid = "StandardAction";  // NOI18N
                 _actionNameLabel->setToolTip(tr("Enter Name (system or user) for AudioSource (e.g. IAS2)"));  // NOI18N
                 _actionBoxLabel->setText(tr("Audio Action"));  // NOI18N
                 _actionBoxLabel->setToolTip(tr("Select action to perform"));  // NOI18N
                 _actionBox->addItem(tr("Play"));        // NOI18N
                 _actionBox->addItem(tr("Stop"));        // NOI18N
                 _actionBox->addItem(tr("Toggle Play"));  // NOI18N
                 _actionBox->addItem(tr("Pause"));       // NOI18N
                 _actionBox->addItem(tr("Resume"));      // NOI18N
                 _actionBox->addItem(tr("PauseToggle")); // NOI18N
                 _actionBox->addItem(tr("Rewind"));      // NOI18N
                 _actionBox->addItem(tr("FadeIn"));      // NOI18N
                 _actionBox->addItem(tr("FadeOut"));     // NOI18N
                 _actionBox->addItem(tr("Reset Position"));     // NOI18N
             }

             makeDetailGrid(audioGrid);
             break;
}
         case Conditional::ITEM_TYPE_SCRIPT:
     {
             QString scriptGrid = "TypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_SCRIPT_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_SCRIPT_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_RUN_SCRIPT) {
                 scriptGrid = "FileAction";  // NOI18N
                 _shortActionLabel->setText(tr("Select File"));  // NOI18N
                 _actionSetButton->setToolTip(tr("Click for a file selection dialog for choosing a script file"));  // NOI18N
             } else if (actionType == Conditional::ACTION_JYTHON_COMMAND) {
                 scriptGrid = "TypeShortAction";  // NOI18N
                 _shortActionLabel->setText(tr("Script Command"));  // NOI18N
                 _shortActionLabel->setToolTip(tr("Enter Jython command text"));  // NOI18N
             }

             makeDetailGrid(scriptGrid);
             break;
}
         case Conditional::ITEM_TYPE_OTHER:
     {
             QString otherGrid = "TypeAction";  // NOI18N

             for (int i = 0; i < Conditional::ITEM_TO_OTHER_ACTION.length(); i++) {
                 _actionTypeBox->addItem(
                         DefaultConditionalAction::getActionTypeString(Conditional::ITEM_TO_OTHER_ACTION[i]));
             }

             if (actionType == Conditional::ACTION_TRIGGER_ROUTE) {
                 otherGrid = "NameTypeActionFinal";  // NOI18N
                 _actionNameLabel->setToolTip(tr("Enter name (system or user) of Route"));  // NOI18N
             }

             setActionNameBox(itemType);
             makeDetailGrid(otherGrid);
             break;
}
         default:
             break;
     }
     _actionTypeListener->setItemType(itemType);
     //_actionTypeBox::addActionListener(_actionTypeListener);
     connect(_actionTypeBox, SIGNAL(currentIndexChanged(int)), _actionTypeListener, SLOT(actionPerformed()));
 }

 /**
  * Update the name combo box selection based on the current contents of the
  * name field.
  *
  * @since 4.7.3
  * @param itemType The item type, such as sensor or turnout.
  */
 void ConditionalTreeEdit::setActionNameBox(int itemType) {
     if (_selectionMode != SelectionMode::USECOMBO) {
         return;
     }
     _comboNameBox = createNameBox(itemType);
     if (_comboNameBox ==  NULL) {
         return;
     }
     // Select the current entry
//     _comboNameBox->setCheckedBeanByName(_curAction->getDeviceName());
     NameBoxListener* nameBoxListener;
     //_comboNameBox::addActionListener(new NameBoxListener(_actionNameField));
     connect(_comboNameBox, SIGNAL(currentIndexChanged(int)), nameBoxListener, SLOT(actionPerformed()));
     _comboNameBox->installEventFilter(this);
 }

 // ------------ Action detail methods ------------
 /**
  * Respond to Cancel action button and window closer of the Edit Action
  * window.
  * <p>
  * Also does cleanup of Update and Delete buttons.
  */
 void ConditionalTreeEdit::cancelEditAction() {
     if (_newActionItem) {
         _newActionItem = false;
         deletePressed();
     }
     cleanUpAction();
 }

 /**
  * Respond to Update button
  */
 void ConditionalTreeEdit::updateAction() {
     if (!validateAction()) {
         return;
     }
     _newActionItem = false;
     updateActionList();

     // Update the Action node
     _curNode->setText(_curAction->description(_triggerMode));
     _cdlModel->nodeChanged(_curNode);
     cleanUpAction();
 }

 /**
  * Clean up Update and Delete Action buttons.
  */
 void ConditionalTreeEdit::cleanUpAction() {
     setMoveButtons();
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
 /*static*/ int ConditionalTreeEdit::getActionTypeFromBox(int itemType, int actionTypeSelection) {
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
         case Conditional::ITEM_TYPE_ENTRYEXIT:
             return Conditional::ITEM_TO_ENTRYEXIT_ACTION[actionTypeSelection];
         default:
             // fall through
             break;
     }
     return Conditional::ACTION_NONE;
 }


 /**
  * Respond to the [...] button in the Edit Action window action section.
  * <p>
  * Ask user to select an audio or python script file on disk.
  *
  * @param e the event heard
  */
 void ConditionalTreeEdit::setFileLocation() {
     ConditionalAction* action = _actionList->     value(_curNodeRow);
     JFileChooser* currentChooser;
     int actionType = action->getType();
#if 0 // TODO:
     if (actionType == Conditional::ACTION_PLAY_SOUND) {
         if (sndFileChooser ==  NULL) {
             sndFileChooser = new JFileChooser(System::getProperty("user.dir") // NOI18N
                     + File::separator + "resources" // NOI18N
                     + File::separator + "sounds");  // NOI18N
             FileChooserFilter filt = new jmri.util.FileChooserFilter("wav sound files");  // NOI18N
             filt.addExtension("wav");  // NOI18N
             sndFileChooser->setFileFilter(filt);
         }
         currentChooser = sndFileChooser;
     } else if (actionType == Conditional::ACTION_RUN_SCRIPT) {
         if (scriptFileChooser ==  NULL) {
             scriptFileChooser = new JFileChooser(FileUtil.getScriptsPath());
             jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("Python script files");  // NOI18N
             filt.addExtension("py");
             scriptFileChooser->setFileFilter(filt);
         }
         currentChooser = scriptFileChooser;
     } else {
         log->warn("Unexpected actionType[" + actionType + "] = " + DefaultConditionalAction::getActionTypeString(actionType));  // NOI18N
         if (defaultFileChooser ==  NULL) {
             defaultFileChooser = new JFileChooser(FileUtil.getUserFilesPath());
             defaultFileChooser->setFileFilter(new jmri.util.NoArchiveFileFilter());
         }
         currentChooser = defaultFileChooser;
     }

     currentChooser.rescanCurrentDirectory();
     int retVal = currentChooser.showOpenDialog( NULL);
     // handle selection or cancel
     if (retVal == JFileChooser.APPROVE_OPTION) {
         // set selected file location in data string
         try {
             _longActionString->setText(FileUtil.getPortableFilename(currentChooser.getSelectedFile().getCanonicalPath()));
         } catch (java.io.IOException ex) {
             if (log->isDebugEnabled()) {
                 log->error("exception setting file location: " + ex);  // NOI18N
             }
             _longActionString->setText("");
         }
     }
#endif
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
bool ConditionalTreeEdit::validateAction() {
     int itemType = _actionItemBox->currentIndex();
     int actionType = Conditional::ACTION_NONE;
     int selection = _actionTypeBox->currentIndex();
     if (selection == 0) {
         JOptionPane::showMessageDialog(
                 _editLogixFrame, tr("Please select an action type."),
                 tr("WarningTitle"), JOptionPane::WARNING_MESSAGE);
         return false;
     }
     QString name = _actionNameField->text().trimmed();
     QString actionString = _shortActionString->text().trimmed();
     _curAction->setActionString("");
     _curAction->setActionData(-1);
    bool referenceByMemory = false;
     if (name.length() > 0 && name.at(0) == '@') {
         QString memName = name.mid(1);
         if (!confirmIndirectMemory(memName)) {
             return false;
         }
         memName = validateMemoryReference(memName);
         if (memName ==  NULL) {
             return false;
         }
         referenceByMemory = true;
     }
     if(itemType == Conditional::ITEM_TYPE_SENSOR)
     {
             if (!referenceByMemory) {
                 name = validateSensorReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_SENSOR_ACTION[selection - 1];
             if ((actionType == Conditional::ACTION_RESET_DELAYED_SENSOR)
                     || (actionType == Conditional::ACTION_DELAYED_SENSOR)) {
                 if (!validateTimeReference(actionType, actionString)) {
                     return (false);
                 }
                 _curAction->setActionString(actionString);
             }
             if ((actionType == Conditional::ACTION_SET_SENSOR)
                     || (actionType == Conditional::ACTION_RESET_DELAYED_SENSOR)
                     || (actionType == Conditional::ACTION_DELAYED_SENSOR)) {
                 if (_actionBox->currentIndex() == 0) {
                     _curAction->setActionData(Sensor::ACTIVE);
                 } else if (_actionBox->currentIndex() == 1) {
                     _curAction->setActionData(Sensor::INACTIVE);
                 } else {
                     _curAction->setActionData(Route::TOGGLE);
                 }
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
           }
     else if(itemType == Conditional::ITEM_TYPE_TURNOUT)
     {
             if (!referenceByMemory) {
                 name = validateTurnoutReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_TURNOUT_ACTION[selection - 1];
             if ((actionType == Conditional::ACTION_RESET_DELAYED_TURNOUT)
                     || (actionType == Conditional::ACTION_DELAYED_TURNOUT)) {
                 if (!validateTimeReference(actionType, actionString)) {
                     return (false);
                 }
                 _curAction->setActionString(actionString);
             }
             if ((actionType == Conditional::ACTION_SET_TURNOUT)
                     || (actionType == Conditional::ACTION_RESET_DELAYED_TURNOUT)
                     || (actionType == Conditional::ACTION_DELAYED_TURNOUT)) {
                 if (_actionBox->currentIndex() == 0) {
                     _curAction->setActionData(Turnout::CLOSED);
                 } else if (_actionBox->currentIndex() == 1) {
                     _curAction->setActionData(Turnout::THROWN);
                 } else {
                     _curAction->setActionData(Route::TOGGLE);
                 }
             } else if (actionType == Conditional::ACTION_LOCK_TURNOUT) {
                 if (_actionBox->currentIndex() == 0) {
                     _curAction->setActionData(Turnout::UNLOCKED);
                 } else if (_actionBox->currentIndex() == 1) {
                     _curAction->setActionData(Turnout::LOCKED);
                 } else {
                     _curAction->setActionData(Route::TOGGLE);
                 }
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
     }
else if(itemType == Conditional::ITEM_TYPE_LIGHT)
     {
             if (!referenceByMemory) {
                 name = validateLightReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_LIGHT_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_SET_LIGHT_INTENSITY) {
                 Light* lgtx = getLight(name);
                 // check if light user name was entered
                 if (lgtx ==  NULL) {
                     return false;
                 }
                 if (!lgtx->isIntensityVariable()) {
                     JOptionPane::showMessageDialog(_editLogixFrame,
                             tr("Light - %1 - does not have variable intensity.\nPlease enter a light with variable intensity or change action type, and try again.").arg(name), // NOI18N
                             tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
                     return (false);
                 }
                 if (!validateIntensityReference(actionType, actionString)) {
                     return (false);
                 }
                 _curAction->setActionString(actionString);
             } else if (actionType == Conditional::ACTION_SET_LIGHT_TRANSITION_TIME) {
                 Light* lgtx = getLight(name);
                 // check if light user name was entered
                 if (lgtx ==  NULL) {
                     return false;
                 }
                 if (!lgtx->isTransitionAvailable()) {
                     JOptionPane::showMessageDialog(_editLogixFrame,

                                     tr("Light - %1 - does not support transition time.\nPlease enter a light with Transition Time or change action type, and try again.").arg(name), // NOI18N
                             tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
                     return (false);
                 }
                 if (!validateTimeReference(actionType, actionString)) {
                     return (false);
                 }
                 _curAction->setActionString(actionString);
             } else if (actionType == Conditional::ACTION_SET_LIGHT) {
                 if (_actionBox->currentIndex() == 0) {
                     _curAction->setActionData(Light::ON);
                 } else if (_actionBox->currentIndex() == 1) {
                     _curAction->setActionData(Light::OFF);
                 } else {
                     _curAction->setActionData(Route::TOGGLE);
                 }
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
     }
else if(itemType ==Conditional::ITEM_TYPE_SIGNALHEAD)
     {
             if (!referenceByMemory) {
                 name = validateSignalHeadReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_SIGNAL_HEAD_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_SET_SIGNAL_APPEARANCE) {
                 QString appStr =  _actionBox->currentText();
                 _curAction->setActionData(DefaultConditionalAction::stringToActionData(appStr));
                 _curAction->setActionString(appStr);
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
     }
else if(itemType == Conditional::ITEM_TYPE_SIGNALMAST)
     {
             if (!referenceByMemory) {
                 name = validateSignalMastReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_SIGNAL_MAST_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_SET_SIGNALMAST_ASPECT) {
                 _curAction->setActionString( _actionBox->currentText());
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
     }
else if(itemType == Conditional::ITEM_TYPE_MEMORY)
     {
             if (referenceByMemory) {
                 JOptionPane::showMessageDialog(_editLogixFrame, tr("Warn6"), tr("WarningTitle"), // NOI18N
                         JOptionPane::WARNING_MESSAGE);
                 return false;
             }
             name = validateMemoryReference(name);
             if (name ==  NULL) {
                 return false;
             }
             actionType = Conditional::ITEM_TO_MEMORY_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_COPY_MEMORY) {
                 actionString = validateMemoryReference(actionString);
                 if (actionString ==  NULL) {
                     return false;
                 }
             }
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
             _curAction->setActionString(actionString);
     }
else if(itemType == Conditional::ITEM_TYPE_LOGIX)
     {
             if (!referenceByMemory) {
                 name = validateLogixReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_LOGIX_ACTION[selection - 1];
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
     }
else if(itemType == Conditional::ITEM_TYPE_WARRANT)
     {
             if (!referenceByMemory) {
                 name = validateWarrantReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_WARRANT_ACTION[selection - 1];
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
             if (actionType == Conditional::ACTION_CONTROL_TRAIN) {
                 if (_actionBox->currentIndex() == 0) {
                     _curAction->setActionData(Warrant::HALT);
                 } else if (_actionBox->currentIndex() == 1) {
                     _curAction->setActionData(Warrant::RESUME);
                 } else {
                     _curAction->setActionData(Warrant::ABORT);
                 }
             } else if (actionType == Conditional::ACTION_SET_TRAIN_ID
                     || actionType == Conditional::ACTION_SET_TRAIN_NAME
                     || actionType == Conditional::ACTION_THROTTLE_FACTOR) {
                 _curAction->setActionString(actionString);
             }
     }
else if(itemType == Conditional::ITEM_TYPE_OBLOCK)
     {
             if (!referenceByMemory) {
                 name = validateOBlockReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_OBLOCK_ACTION[selection - 1];
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
             if (actionType == Conditional::ACTION_SET_BLOCK_VALUE) {
                 _curAction->setActionString(actionString);
             }
     }
else if(itemType == Conditional::ITEM_TYPE_ENTRYEXIT)
     {
             if (!referenceByMemory) {
                 name = validateEntryExitReference(name);
                 if (name ==  NULL) {
                     return false;
                 }
             }
             actionType = Conditional::ITEM_TO_ENTRYEXIT_ACTION[selection - 1];
             _actionNameField->setText(name);
             _curAction->setDeviceName(name);
     }
else if(itemType ==Conditional::ITEM_TYPE_CLOCK)
     {
             actionType = Conditional::ITEM_TO_CLOCK_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_SET_FAST_CLOCK_TIME) {
                 int time = parseTime(_shortActionString->text().trimmed());
                 if (time < 0) {
                     return (false);
                 }
                 _curAction->setActionData(time);
             }
     }
else if(itemType == Conditional::ITEM_TYPE_AUDIO)
     {
             actionType = Conditional::ITEM_TO_AUDIO_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_PLAY_SOUND) {
                 _curAction->setActionString(_longActionString->text().trimmed());
             } else if (actionType == Conditional::ACTION_CONTROL_AUDIO) {
                 if (!referenceByMemory) {
                     name = validateAudioReference(name);
                     if (name ==  NULL) {
                         return false;
                     }
                 }
                 _actionNameField->setText(name);
                 _curAction->setDeviceName(name);
                 switch (_actionBox->currentIndex()) {
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
                     default:
                         log->warn(tr("Unexpected _actionBox->currentIndex() of %1").arg(_actionBox->currentIndex()));  // NOI18N
                         break;
                 }
             }
     }
else if(itemType == Conditional::ITEM_TYPE_SCRIPT)
     {
             actionType = Conditional::ITEM_TO_SCRIPT_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_RUN_SCRIPT) {
                 _curAction->setActionString(_longActionString->text().trimmed());
             } else if (actionType == Conditional::ACTION_JYTHON_COMMAND) {
                 _curAction->setActionString(_shortActionString->text().trimmed());
             }
     }
else if(itemType == Conditional::ITEM_TYPE_OTHER)
     {
             actionType = Conditional::ITEM_TO_OTHER_ACTION[selection - 1];
             if (actionType == Conditional::ACTION_TRIGGER_ROUTE) {
                 if (!referenceByMemory) {
                     name = validateRouteReference(name);
                     if (name ==  NULL) {
                         return false;
                     }
                 }
                 _actionNameField->setText(name);
                 _curAction->setDeviceName(name);
             }

     }
     _curAction->setType(actionType);
     if (actionType != Conditional::ACTION_NONE) {
         _curAction->setOption(_actionOptionBox->currentIndex() + 1);
     } else {
         _curAction->setOption(0);
     }
     return (true);
 }

 /**
  * Update the conditional action list and refresh the local copy.
  * The parent Logix is de-activated and re-activated.  This insures
  * that listeners are properly handled, specifically the delayed sensor
  * and turnout options.
  * @since 4.11.2
  */
 void ConditionalTreeEdit::updateActionList() {
     _curLogix->deActivateLogix();
     _curConditional->setAction(_actionList);
     _actionList = _curConditional->getCopyOfActions();
     _curLogix->activateLogix();
 }

 // ------------ Action detail listeners ------------
 /**
  * Listener for _actionTypeBox::
  */
// class ActionTypeListener implements ActionListener {

//     int _itemType;
CTEActionTypeListener::CTEActionTypeListener(ConditionalTreeEdit *cte) {this->cte = cte;}
     //@Override
     /*public*/ void CTEActionTypeListener::actionPerformed(JActionEvent* /*e*/) {
         int select1 = cte->_actionItemBox->currentIndex();
         int select2 = cte->_actionTypeBox->currentIndex() - 1;
         if (cte->log->isDebugEnabled()) {
             cte->log->debug(tr("ActionTypeListener: itemType = %1, local itemType = %2, actionType = %3").arg(select1).arg(_itemType).arg(select2));
         }
         if (select1 != _itemType) {
             cte->log->error(tr("ActionTypeListener actionItem selection (%1) != expected actionItem (%2)").arg(select1).arg(_itemType));
         }
         if (cte->_curAction !=  NULL) {
             if (select1 > 0 && _itemType == select1) {
                 cte->_curAction->setType(cte->getActionTypeFromBox(_itemType, select2));
                 if (select1 == _itemType) {
                     QString text = cte->_actionNameField->text();
                     if (text !=  NULL && text.length() > 0) {
                        cte-> _curAction->setDeviceName(text);
                     }
                 }
                 cte->actionItemChanged(_itemType);
                 cte->initializeActionVariables();
             }
         }
     }

     /*public*/ void CTEActionTypeListener::setItemType(int type) {
         _itemType = type;
     }
 //}

 ActionSignalHeadNameListener::ActionSignalHeadNameListener(ConditionalTreeEdit *cte) { this->cte = cte;}
     //@Override
     /*public*/ void ActionSignalHeadNameListener::actionPerformed(JActionEvent* /*e*/) {
         // fired when signal head name changes, but only
         // while in signal head mode
         cte->log->debug("actionSignalHeadNameListener fires; _actionNameField : " + cte->_actionNameField->text().trimmed());  // NOI18N
        cte->loadJComboBoxWithHeadAppearances(cte->_actionBox, cte->_actionNameField->text().trimmed());
     }
 //};

ActionSignalMastNameListener::ActionSignalMastNameListener(ConditionalTreeEdit *cte) {this->cte = cte;}

//@Override
/*public*/ void ActionSignalMastNameListener::actionPerformed(JActionEvent* /*e*/) {
    // fired when signal mast name changes, but only
    // while in signal mast mode
    cte->log->debug("actionSignalMastNameListener fires; _actionNameField : " + cte->_actionNameField->text().trimmed());  // NOI18N
    cte->loadJComboBoxWithMastAspects(cte->_actionBox, cte->_actionNameField->text().trimmed());
}
//     };

 // ============ Conditional Tree Node Definition ============
// static class ConditionalTreeNode extends DefaultMutableTreeNode {

//     /*private*/ String cdlText;
//     /*private*/ String cdlType;
//     /*private*/ String cdlName;
//     /*private*/ int cdlRow;

/*public*/ ConditionalTreeNode::ConditionalTreeNode(QString nameText, QString type, QString sysName, int row) {
    this->cdlText = nameText;
    this->cdlType = type;
    this->cdlName = sysName;
    this->cdlRow = row;
}

/*public*/ QString ConditionalTreeNode::getType() {
    return cdlType;
}

/*public*/ QString ConditionalTreeNode::getName() {
    return cdlName;
}

/*public*/ void ConditionalTreeNode::setName(QString newName) {
    cdlName = newName;
}

/*public*/ int ConditionalTreeNode::getRow() {
    return cdlRow;
}

/*public*/ void ConditionalTreeNode::setRow(int newRow) {
    cdlRow = newRow;
}

/*public*/ QString ConditionalTreeNode::getText() {
    return cdlText;
}

/*public*/ void ConditionalTreeNode::setText(QString newText) {
    cdlText = newText;
}

//@Override
/*public*/ QString ConditionalTreeNode::toString() {
    return cdlText;
}
// }

 /*protected*/ QString ConditionalTreeEdit::getClassName() {
     //return ConditionalTreeEdit.class.getName();
  return "jmri.jmrit.conditional.ConditionalTreeEdit";
 }


 /*private*/ /*final*/ /*static*/ Logger* ConditionalTreeEdit::log = LoggerFactory::getLogger("ConditionalTreeEdit");

