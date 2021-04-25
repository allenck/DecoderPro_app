#include "transittableaction.h"
#include "instancemanager.h"
#include "transitmanager.h"
#include "sectionmanager.h"
#include "jtextfield.h"
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QBoxLayout>
#include <QMessageBox>
#include "flowlayout.h"
#include "userpreferencesmanager.h"
#include "jseparator.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "transitsection.h"
#include "section.h"
#include "inputdialog.h"
#include "transitsectionaction.h"
#include <QRadioButton>
#include <QButtonGroup>

//TransitTableAction::TransitTableAction()
//{

//}

/**
 * Swing action to create and register a TransitTable GUI.
 *
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Dave Duchamp Copyright (C) 2008, 2010, 2011
 */
///*public*/ class TransitTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame. Perhaps this should be changed? @param actionName
 */
/*public*/ TransitTableAction::TransitTableAction(QString actionName, QObject* parent)
    : AbstractTableAction(actionName, parent)
{
    //super(actionName);
    common();
    // set manager - no need to use InstanceManager here
    transitManager = (TransitManager*)InstanceManager::getNullableDefault("TransitManager");
    // disable ourself if there is no Transit manager available
    if (sectionManager == NULL) {
        setEnabled(false);
    }

}

/*public*/ TransitTableAction::TransitTableAction(QObject* parent)
    : AbstractTableAction(tr("Transit Table"), parent)
{
    //this(tr("TitleTransitTable"));
    common();
}
void TransitTableAction::common()
{
 log = new Logger("TransitTableAction");

 // instance variables
 editMode = false;
 duplicateMode = false;
 transitManager = NULL;
 sectionManager = ((SectionManager*)InstanceManager::getDefault("SectionManager"));
 curTransit = NULL;
 sectionTableModel = NULL;
 sectionList = new QList<Section*>();
 direction = new QVector<int>(150);
 sequence = new QVector<int>(150);
 action =  QVector<QList<TransitSectionAction*>*>(150);
 alternate = new QVector<bool>(150);
 maxSections = 150;  // must be equal to the dimension of the above arrays
 primarySectionBoxList = new QList<Section*>();
 priSectionDirection = new QVector<int>(150);
 alternateSectionBoxList = new QList<Section*>();
 altSectionDirection = new QVector<int>(150);
 insertAtBeginningBoxList = new QList<Section*>();
 insertAtBeginningDirection = new QVector<int>(150);
 curSection = NULL;
 curSectionDirection = 0;
 prevSection = NULL;
 prevSectionDirection = 0;
 curSequenceNum = 0;

    // add/create variables
 addFrame = NULL;
 sysName = new JTextField(5);
 sysNameFixed = new QLabel("");
 userName = new JTextField(17);
 sysNameLabel = new QLabel(tr("SystemName:"));
 userNameLabel = new QLabel(tr("UserName:"));
 create = NULL;
 update = NULL;
 deleteSections = NULL;
 primarySectionBox = new QComboBox();
 addNextSection = NULL;
 removeLastSection = NULL;
 removeFirstSection = NULL;
 insertAtBeginning = NULL;
 insertAtBeginningBox = new QComboBox();
 seqNumLabel = new QLabel(tr("Order Number"));
 seqNum = new JTextField(5);
 replacePrimaryForSequence = NULL;
 deleteAlternateForSequence = NULL;
 addAlternateForSequence = NULL;
 alternateSectionBox = new QComboBox();
 addAlternateSection = NULL;
 _autoSystemName = new QCheckBox(tr("Auto Sys Name"));
 systemNameAuto = getClassName() + ".AutoSystemName";

 // variables for view actions window
 activeRow = 0;
 actionTableModel = NULL;
 actionTableFrame = NULL;
 fixedSectionLabel = new QLabel("X");

 // variables for add/edit action window
 editActionMode = false;
 addEditActionFrame = NULL;
 curTSA = NULL;
 whenBox = new QComboBox();
 whenDataField = new JTextField(7);
 whenStringField = new JTextField(17);
 whatBox = new QComboBox();
 whatData1Field = new JTextField(7);
 whatData2Field = new JTextField(7);
 whatStringField = new JTextField(17);
 updateActionButton = NULL;
 createActionButton = NULL;
 cancelAddEditActionButton = NULL;
 blockBox = new QComboBox();
 onButton = new QRadioButton(tr("On"));
 offButton = new QRadioButton(tr("Off"));
 doneSensorLabel = new QLabel(tr("Done Sensor (optional)"));
 doneSensorField = new JTextField(17);

 // temporary action variables
 tWhen = 0;
 tWhenData = 0;
 tWhenString = "";
 tWhat = 0;
 tWhatData1 = 0;
 tWhatData2 = 0;
 tWhatString = "";

}


//static final ResourceBundle rbx = ResourceBundle.getBundle("jmri.jmrit.beantable.SectionTransitTableBundle");

/**
 * Create the JTable DataModel, along with the changes for the specific case
 * of Transit objects
 */
/*protected*/ void TransitTableAction::createModel()
{
    m = new TransitTableDataModel(this);
}

TransitTableDataModel::TransitTableDataModel(TransitTableAction* act)
{
 this->act = act;
 log = new Logger("TransitTableDataModel");
 init();
}

/*public*/ QString TransitTableDataModel::getValue(QString name) const
{
    if (name == NULL) {
        log->warn("requested getValue(NULL)");
        return "(no name)";
    }
    Transit* z = ((TransitManager*)InstanceManager::getNullableDefault("TransitManager"))->getBySystemName(name);
    if (z == NULL) {
        log->debug("requested getValue(\"" + name + "\"), Transit doesn't exist");
        return "(no Transit)";
    }
    return "Transit";
}

/*public*/ AbstractManager *TransitTableDataModel::getManager() {
    return ((AbstractManager*)InstanceManager::getNullableDefault("TransitManager"));
}

/*public*/ NamedBean* TransitTableDataModel::getBySystemName(QString name) const {
    return ((TransitManager*)InstanceManager::getNullableDefault("TransitManager"))->getBySystemName(name);
}

/*public*/ NamedBean* TransitTableDataModel::getByUserName(QString name) {
    return ((TransitManager*)InstanceManager::getNullableDefault("TransitManager"))->getByUserName(name);
}
/*public int getDisplayDeleteMsg() { return InstanceManager::getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
 public void setDisplayDeleteMsg(int boo) { InstanceManager::getDefault(jmri.UserPreferencesManager.class).setMultipleChoiceOption(getClassName(), "delete", boo); }*/

/*protected*/ QString TransitTableDataModel::getMasterClassName() {
    return act->getClassName();
}

/*public*/ void TransitTableDataModel::clickOn(NamedBean* t) {
}

/*public*/ int TransitTableDataModel::columnCount(const QModelIndex &parent) const
{
    return DUPLICATECOL + 1;
}

/*public*/ QVariant TransitTableDataModel::data(const QModelIndex &index, int role) const
{
    int col = index.column();
    int row = index.row();
    if(role == Qt::DisplayRole)
    {
    if (col == VALUECOL) {
        // some error checking
        if (row >= sysNameList.size()) {
            log->debug("row is greater than name list");
            return "";
        }
        Transit* z = (Transit*) getBySystemName(sysNameList.at(row));
        if (z == NULL) {
            return "";
        } else {
            int state = z->getState();
            if (state == Transit::IDLE) {
                return (tr("Idle"));
            } else if (state == Transit::ASSIGNED) {
                return (tr("Assigned"));
            }
        }
    } else if (col == EDITCOL) {
        return tr("Edit");
    } else if (col == DUPLICATECOL) {
        return tr("Duplicate");
    }
 }
 return BeanTableDataModel::data(index, role);
}

/*public*/ bool TransitTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
        int col = index.column();
        int row = index.row();

    if (col == EDITCOL)
    {
//        class WindowMaker implements Runnable {

//            int row;

//            WindowMaker(int r) {
//                row = r;
//            }

//            /*public*/ void run() {
                QString sName = data(this->index(row, SYSNAMECOL),Qt::DisplayRole).toString();
                act->editPressed(sName);
//            }
//        }
//        WindowMaker t = new WindowMaker(row);
//        javax.swing.SwingUtilities.invokeLater(t);
    } else if (col == DUPLICATECOL) {
        // set up to duplicate
//        class WindowMaker implements Runnable {

//            int row;

//            WindowMaker(int r) {
//                row = r;
//            }

//            /*public*/ void run() {
                QString sName = data(index, Qt::DisplayRole).toString();
                act->duplicatePressed(sName);
//            }
//        }
//        WindowMaker t = new WindowMaker(row);
//        javax.swing.SwingUtilities.invokeLater(t);
    }
 }
  return BeanTableDataModel::setData(index, value, role);

}

/*public*/ QVariant TransitTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 int col = section;
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (col == EDITCOL) {
        return "";   // no namne on Edit column
    }
    if (col == DUPLICATECOL) {
        return "";   // no namne on Duplicate column
    }
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == VALUECOL) {
//        return String.class;  // not a button
//    }
//    if (col == EDITCOL) {
//        return JButton.class;
//    }
//    if (col == DUPLICATECOL) {
//        return JButton.class;
//    } else {
//        return super.getColumnClass(col);
//    }
//}

/*public*/ Qt::ItemFlags TransitTableDataModel::flags(const QModelIndex &index) const
{
 int col = index.column();
 if (col == VALUECOL) {
    return Qt::ItemIsEnabled;
 }
 if (col == EDITCOL) {
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
 }
 if (col == DUPLICATECOL) {
    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
 }
 return BeanTableDataModel::flags(index);
}

/*public*/ int TransitTableDataModel::getPreferredWidth(int col) {
    // override default value for SystemName and UserName columns
    if (col == SYSNAMECOL) {
        return  JTextField(9).sizeHint().width();
    }
    if (col == USERNAMECOL) {
        return  JTextField(17).sizeHint().width();
    }
    if (col == VALUECOL) {
        return  JTextField(6).sizeHint().width();
    }
    // new columns
    if (col == EDITCOL) {
        return JTextField(6).sizeHint().width();
    }
    if (col == DUPLICATECOL) {
        return  JTextField(10).sizeHint().width();
    } else {
        return BeanTableDataModel::getPreferredWidth(col);
    }
}

/*public*/ void TransitTableDataModel::configValueColumn(JTable* table) {
    // value column isn't button, so config is NULL
}

/*protected*/ bool TransitTableDataModel::matchPropertyName(PropertyChangeEvent* e) {
    return true;
    // return (e.getPropertyName().indexOf("alue")=0);
}

/*public*/ QPushButton* TransitTableDataModel::configureButton() {
    log->error("configureButton should not have been called");
    return NULL;
}

/*protected*/ QString TransitTableDataModel::getBeanType() {
    return "Transit";
}


#
/*protected*/ void TransitTableAction::setTitle() {
    f->setTitle(tr("Transit Table"));
}

/*protected*/ QString TransitTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.TransitTable";
}


/**
 * Responds to the Add... button and the Edit buttons in Transit Table
 */
/*protected*/ void TransitTableAction::addPressed(ActionEvent* /*e*/) {
    editMode = false;
    duplicateMode = false;
    if ((sectionManager->getSystemNameList().size()) > 0) {
        addEditPressed();
    } else {
//        javax.swing.JOptionPane.showMessageDialog(NULL, rbx
//                .getString("Message21"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(NULL, tr("Error"), tr("Transits require Sections. Please define Sections before attempting to create Transits."));
    }
}

void TransitTableAction::editPressed(QString sName) {

    curTransit = transitManager->getBySystemName(sName);
    if (curTransit == NULL) {
        // no transit - should never happen, but protects against a $%^#@ exception
        return;
    }
    sysNameFixed->setText(sName);
    editMode = true;
    duplicateMode = false;
    addEditPressed();

}

void TransitTableAction::duplicatePressed(QString sName)
{
    curTransit = transitManager->getBySystemName(sName);
    if (curTransit == NULL) {
        // no transit - should never happen, but protects against a $%^#@ exception
        return;
    }
    duplicateMode = true;
    editMode = false;
    addEditPressed();
}

void TransitTableAction::addEditPressed()
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");

 if (addFrame == NULL)
 {
  addFrame = new JmriJFrameX(tr("Add Transit"));
    addFrame->addHelpMenu("package.jmri.jmrit.beantable.TransitAddEdit", true);
    addFrame->setMinimumWidth(700);
    QVBoxLayout* contentPaneLayout;
    addFrame->getContentPane()->setLayout(contentPaneLayout = new QVBoxLayout); //(addFrame.getContentPane(), BoxLayout.Y_AXIS));
    QWidget* p;
    p = new QWidget();
    FlowLayout* pLayout;
    p->setLayout(pLayout = new FlowLayout());
    pLayout->addWidget(sysNameLabel);
    pLayout->addWidget(sysNameFixed);
    pLayout->addWidget(sysName);
    sysName->setToolTip(tr("Enter system name for new Transit, e.g. IZ13"));
    pLayout->addWidget(new QLabel("     "));
    pLayout->addWidget(userNameLabel);
    pLayout->addWidget(userName);
    userName->setToolTip(tr("Enter user name for Transit, e.g. Passenger Run"));
    contentPaneLayout->addWidget(p);
    p = new QWidget();
//        ((FlowLayout*) p->getLayout())->setVgap(0);
    pLayout->addWidget(_autoSystemName);
//        _autoSystemName.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                autoSystemName();
//            }
//        });
    connect(_autoSystemName, SIGNAL(toggled(bool)), this, SLOT(autoSystemName()));
    if (pref->getSimplePreferenceState(systemNameAuto)) {
        _autoSystemName->setChecked(true);
    }
    contentPaneLayout->addWidget(p);
    contentPaneLayout->addWidget(new JSeparator());
    QWidget* p1 = new QWidget();
    //p1.setLayout(new BoxLayout(p1, BoxLayout.Y_AXIS));
    QVBoxLayout* p1Layout = new QVBoxLayout(p1);
    QWidget* p11 = new QWidget();
    //p11.setLayout(new FlowLayout());
    FlowLayout* p11Layout = new FlowLayout(p11);
    p11Layout->addWidget(new QLabel(tr("Sections in Transit (at least 2 are required)")));
    p1Layout->addWidget(p11);
    QWidget* p12 = new QWidget();
    QGridLayout* p12Layout = new QGridLayout(p12);
    // initialize table of sections
    sectionTableModel = new SectionTableModel(this);
    JTable* sectionTable = new JTable(sectionTableModel);
//        sectionTable.setRowSelectionAllowed(false);
//        sectionTable.setPreferredScrollableViewportSize(new java.awt.Dimension(650, 150));
    TableColumnModel* sectionColumnModel = sectionTable->getColumnModel();
    TableColumn* sequenceColumn = sectionColumnModel->getColumn(SectionTableModel::SEQUENCE_COLUMN);
//        sequenceColumn->setResizable(true);
//        sequenceColumn->setMinWidth(50);
//        sequenceColumn->setMaxWidth(70);
    TableColumn* sectionColumn = sectionColumnModel->getColumn(SectionTableModel::SECTIONNAME_COLUMN);
//        sectionColumn->setResizable(true);
//        sectionColumn->setMinWidth(150);
//        sectionColumn->setMaxWidth(210);
    TableColumn* actionColumn = sectionColumnModel->getColumn(SectionTableModel::ACTION_COLUMN);
    // install button renderer and editor
//        ButtonRenderer buttonRenderer = new ButtonRenderer();
//        sectionTable.setDefaultRenderer(JButton.class, buttonRenderer);
//        TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//        sectionTable.setDefaultEditor(JButton.class, buttonEditor);
    QPushButton* testButton = new QPushButton(tr("Edit Actions"));
//        sectionTable->setRowHeight(testButton->sizeHint().height());
//        actionColumn->setResizable(false);
//        actionColumn->setMinWidth(testButton.sizeHint().width());
    TableColumn* alternateColumn = sectionColumnModel->getColumn(SectionTableModel::ALTERNATE_COLUMN);
//        alternateColumn->setResizable(true);
//        alternateColumn->setMinWidth(140);
//        alternateColumn->setMaxWidth(170);
    //JScrollPane sectionTableScrollPane = new JScrollPane(sectionTable);
    p12Layout->addWidget(/*sectionTableScrollPane*/sectionTable/*, BorderLayout.CENTER*/,0, 0);
    p1Layout->addWidget(p12);
    QWidget* p13 = new QWidget();
    //p13.setLayout(new FlowLayout());
    FlowLayout* p13Layout = new FlowLayout(p13);
    p13Layout->addWidget(primarySectionBox);
    primarySectionBox->setToolTip(tr("Select a Section to add from this list, then press Add Next  Section::"));
    p13Layout->addWidget(addNextSection = new QPushButton(tr("Add Next Section")));
//        addNext Section::addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addNextSectionPressed(e);
//            }
//        });
    connect(addNextSection, SIGNAL(clicked(bool)), this, SLOT(addNextSectionPressed()));
    addNextSection->setToolTip(tr("Press to add the Section selected at the left to this Transit."));
    p1Layout->addWidget(p13);
    QWidget* p14 = new QWidget();
    //p14.setLayout(new FlowLayout());
    FlowLayout* p14Layout = new FlowLayout(p14);
    p14Layout->addWidget(alternateSectionBox);
    alternateSectionBox->setToolTip(tr("Select a Section to add as an alternate to the above  Section::"));
    p14Layout->addWidget(addAlternateSection = new QPushButton(tr("Add Alternate Section")));
//        addAlternate Section::addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addAlternateSectionPressed(e);
//            }
//        });
    connect(addAlternateSection, SIGNAL(clicked(bool)), this, SLOT(addAlternateSectionPressed()));
    addAlternateSection->setToolTip(tr("Press to add the Section selected at the left as an alternate to the above  Section::"));
    p14Layout->addWidget(new QLabel("        "));
    p14Layout->addWidget(insertAtBeginningBox);
    insertAtBeginningBox->setToolTip(tr("Select a Section to insert at beginning of this Transit, then press Insert As First  Section::."));
    p14Layout->addWidget(insertAtBeginning = new QPushButton(tr("Insert As First Section")));
//        insertAtBeginning.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                insertAtBeginningPressed(e);
//            }
//        });
    connect(insertAtBeginning, SIGNAL(clicked(bool)), this, SLOT(insertAtBeginningPressed()));
    insertAtBeginning->setToolTip(tr("Press to insert the Section selected as the first Section in this Transit."));
    p1Layout->addWidget(p14);
    p1Layout->addWidget(new JSeparator());
    QWidget* p15 = new QWidget();
    //p15.setLayout(new FlowLayout());
    FlowLayout* p15Layout = new FlowLayout(p15);
    p15Layout->addWidget(deleteSections = new QPushButton(tr("Delete All Sections")));
//        deleteSections.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                deleteAllSections(e);
//            }
//        });
    connect(deleteSections, SIGNAL(clicked(bool)), this, SLOT(deleteAllSections()));
    deleteSections->setToolTip(tr("Press to delete all Sections in above table and start again."));
    p15Layout->addWidget(new QLabel("     "));
    p15Layout->addWidget(removeLastSection = new QPushButton(tr("Remove Last Section")));
//        removeLast Section::addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                removeLastSectionPressed(e);
//            }
//        });
    connect(removeLastSection, SIGNAL(clicked(bool)),this, SLOT(removeLastSectionPressed()));
    removeLastSection->setToolTip(tr("Press to delete the bottom-most Section from this Transit."));
    p15Layout->addWidget(new QLabel("     "));
    p15Layout->addWidget(removeFirstSection = new QPushButton(tr("Remove First Section")));
//        removeFirst Section::addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                removeFirstSectionPressed(e);
//            }
//        });
    connect(removeFirstSection, SIGNAL(clicked(bool)), this, SLOT(removeFirstSectionPressed()));
    removeFirstSection->setToolTip(tr("Press to delete the top-most Section and its Alternates from this Transit."));
    p1Layout->addWidget(p15);
    QWidget* p16 = new QWidget();
    //p16.setLayout(new FlowLayout());
    FlowLayout* p16Layout = new FlowLayout(p16);
    p16Layout->addWidget(seqNumLabel);
    p16Layout->addWidget(new QLabel("   "));
    p16Layout->addWidget(seqNum);
    seqNum->setToolTip(tr("Enter order number of Section to be replaced, added, or deleted by buttons below."));
    p1Layout->addWidget(p16);
    QWidget* p17 = new QWidget();
    //p17.setLayout(new FlowLayout());
    FlowLayout* p17Layout = new FlowLayout(p17);
    p17Layout->addWidget(replacePrimaryForSequence = new QPushButton(tr("Replace Primary For Order")));
//        replacePrimaryForSequence.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                replacePrimaryForSeqPressed(e);
//            }
//        });
    connect(replacePrimaryForSequence, SIGNAL(clicked(bool)), this, SLOT(replacePrimaryForSeqPressed()));
    replacePrimaryForSequence->setToolTip(tr("Press to replace the primary Section at the entered order number, if possible."));
    p17Layout->addWidget(new QLabel("     "));
    p17Layout->addWidget(deleteAlternateForSequence = new QPushButton(tr("Delete Alternate For Order")));
//        deleteAlternateForSequence.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                deleteAlternateForSeqPressed(e);
//            }
//        });
    connect(deleteAlternateForSequence, SIGNAL(clicked(bool)), this, SLOT(deleteAlternateForSeqPressed()));
    deleteAlternateForSequence->setToolTip(tr("Press to delete all alternate Sections at the entered order number, if any."));
    p17Layout->addWidget(new QLabel("     "));
    p17Layout->addWidget(addAlternateForSequence = new QPushButton(tr("Add Alternate For Order")));
//        addAlternateForSequence.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addAlternateForSeqPressed(e);
//            }
//        });
    connect(addAlternateForSequence, SIGNAL(clicked(bool)), this, SLOT(addAlternateForSeqPressed()));
    addAlternateForSequence->setToolTip(tr("Press to add an alternate Section at the entered order number, if possible."));
    p1Layout->addWidget(p17);
    contentPaneLayout->addWidget(p1);
    // set up bottom buttons
    contentPaneLayout->addWidget(new JSeparator());
    QPushButton* cancel = NULL;
    QWidget* pb = new QWidget();
    //pb.setLayout(new FlowLayout());
    FlowLayout* pbLayout = new FlowLayout(pb);
    pbLayout->addWidget(cancel = new QPushButton(tr("Cancel")));
//        cancel.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelPressed(e);
//            }
//        });
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancelPressed()));
    cancel->setToolTip(tr("Press to cancel without creating or updating."));
    pbLayout->addWidget(create = new QPushButton(tr("Create")));
//        create.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                createPressed(e);
//            }
//        });
    connect(create, SIGNAL(clicked(bool)), this, SLOT(createPressed()));
    create->setToolTip(tr("Press to check entries and create a new  Section::"));
    pbLayout->addWidget(update = new QPushButton(tr("Update")));
//        update.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updatePressed(e);
//            }
//        });
    connect(update, SIGNAL(clicked(bool)), this, SLOT(updatePressed()));
    update->setToolTip(tr("Press to update this  Section::"));
    contentPaneLayout->addWidget(pb);
   }
   if (editMode)
   {
    // setup for edit window
    _autoSystemName->setVisible(false);
    sysNameLabel->setEnabled(true);
    create->setVisible(false);
    update->setVisible(true);
    sysName->setVisible(false);
    sysNameFixed->setVisible(true);
    initializeEditInformation();
   }
   else
   {
    // setup for create window
    _autoSystemName->setVisible(true);
    _autoSystemName->setEnabled(true);
    autoSystemName();
    create->setVisible(true);
    create->setEnabled(true);
    update->setVisible(false);
    sysName->setVisible(true);
    sysNameFixed->setVisible(false);
    if (duplicateMode)
    {
     // setup with information from previous Transit
     initializeEditInformation();
     sysName->setText(curTransit->getSystemName());
     curTransit = NULL;
    }
    else
    {
     deleteAllSections(NULL);
    }
   }
   initializeSectionCombos();
   addFrame->pack();
   addFrame->setVisible(true);
}

/*private*/ void TransitTableAction::initializeEditInformation() {
    sectionList->clear();
    curSection = NULL;
    curSectionDirection = 0;
    curSequenceNum = 0;
    prevSection = NULL;
    prevSectionDirection = 0;
    if (curTransit != NULL)
    {
        userName->setText(curTransit->getUserName());
        QList<TransitSection*> tsList = curTransit->getTransitSectionList();
        for (int i = 0; i < tsList.size(); i++) {
            TransitSection* ts = tsList.at(i);
            if (ts != NULL) {
                sectionList->append(ts->getSection());
                sequence->replace(i, ts->getSequenceNumber());
                direction->replace(i,  ts->getDirection());
                action.replace(i, ts->getTransitSectionActionList());
                alternate->replace(i, ts->isAlternate());
                safe.replace(i, ts->isSafe());
                sensorStopAllocation[i] = ts->getStopAllocatingSensor();}
        }
        int index = sectionList->size() - 1;
        while (alternate->at(index) && (index > 0)) {
            index--;
        }
        if (index >= 0) {
            curSection = sectionList->at(index);
            curSequenceNum = sequence->at(index);
            if (index > 0) {
                curSectionDirection = direction->at(index);
            }
            index--;
            while ((index >= 0) && alternate->at(index)) {
                index--;
            }
            if (index >= 0) {
                prevSection = sectionList->at(index);
                prevSectionDirection = direction->at(index);
            }
        }
    }
    sectionTableModel->fireTableDataChanged();
}

/*private*/ void TransitTableAction::deleteAllSections(ActionEvent* ) {
    sectionList->clear();
    for (int i = 0; i < maxSections; i++) {
        direction->replace(i,  Section::FORWARD);
        sequence->replace(i,  0);
        action.replace(i,  NULL);
        alternate->replace(i,  false);
    }
    curSection = NULL;
    curSectionDirection = 0;
    prevSection = NULL;
    prevSectionDirection = 0;
    curSequenceNum = 0;
    initializeSectionCombos();
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::addNextSectionPressed(ActionEvent* /*e*/) {
    if (sectionList->size() > maxSections) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message23"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("A Transit may not have more than 150 Sections assigned to it."));
        return;
    }
    if (primarySectionBoxList->size() == 0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message25"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - No section to add."));

        return;
    }
    int index = primarySectionBox->currentIndex();
    Section* s = primarySectionBoxList->at(index);
    if (s != NULL) {
        int j = sectionList->size();
        sectionList->append(s);
        direction->replace(j, priSectionDirection->at(index));
        curSequenceNum++;
        sequence->replace(j, curSequenceNum);
        action.replace(j, NULL);
        alternate->replace(j, false);
        if ((sectionList->size() == 2) && (curSection != NULL)) {
            if (forwardConnected(curSection, s, 0)) {
                direction->replace(0,  Section::REVERSE);
            }
            curSectionDirection = direction->at(0);
        }
        prevSection = curSection;
        prevSectionDirection = curSectionDirection;
        curSection = s;
        if (prevSection != NULL) {
            curSectionDirection = direction->at(j);
        }
        initializeSectionCombos();
    }
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::removeLastSectionPressed(ActionEvent* /*e*/) {
    if (sectionList->size() <= 1) {
        deleteAllSections(/*e*/);
    } else {
        int j = sectionList->size() - 1;
        if (!alternate->at(j)) {
            curSequenceNum--;
            curSection = sectionList->at(j - 1);
            curSectionDirection = direction->at(j - 1);
            int k = j - 2;
            while ((k >= 0) && alternate->at(k)) {
                k--;
            }
            prevSection = sectionList->at(k);
            prevSectionDirection = direction->at(k);
        }
        sectionList->removeAt(j);
        initializeSectionCombos();
    }
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::insertAtBeginningPressed(ActionEvent* /*e*/) {
    if (sectionList->size() > maxSections) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message23"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("A Transit may not have more than 150 Sections assigned to it."));
        return;
    }
    if (insertAtBeginningBoxList->size() == 0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message35"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Message35"));
        return;
    }
    int index = insertAtBeginningBox->currentIndex();
    Section* s = insertAtBeginningBoxList->at(index);
    if (s != NULL) {
        sectionList->replace(0, s);
        for (int i = sectionList->size() - 2; i > 0; i--) {
            direction->replace(i + 1, direction->at(i));
            alternate->replace(i + 1, alternate->at(i));
            action.replace(i + 1, action.at(i));
            sequence->replace(i + 1, sequence->at(i) + 1);
        }
        direction->replace(0, insertAtBeginningDirection->at(index));
        curSequenceNum++;
        sequence->replace(0, 1);
        alternate->replace(0, false);
        action.replace(0, NULL);
        if (curSequenceNum == 2) {
            prevSectionDirection = direction->at(0);
            prevSection = s;
        }
        initializeSectionCombos();
    }
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::removeFirstSectionPressed(ActionEvent* /*e*/) {
    if (curSequenceNum <= 1) {
        deleteAllSections(/*e*/);
    } else {
        int keep = 1;
        while (alternate->at(keep)) {
            keep++;
        }
        for (int i = keep, j = 0; i < sectionList->size(); i++, j++) {
            sequence->replace(j, sequence->at(i) - 1);
            direction->replace(j, direction->at(i));
            action.replace(j, action.at(i));
            alternate->replace(j, alternate->at(i));
        }
        for (int k = 0; k < keep; k++) {
            sectionList->removeAt(0);
        }
        curSequenceNum--;
        initializeSectionCombos();
    }
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::replacePrimaryForSeqPressed(ActionEvent* /*e*/) {
    int seq = getSeqNum();
    if (seq == 0) {
        return;
    }
    Section* sOld = NULL;
    QList<Section*> altOldList =  QList<Section*>();
    Section* beforeSection = NULL;
    int beforeSectionDirection = 0;
    Section* afterSection = NULL;
    int afterSectionDirection = 0;
    int index = -1;
    for (int i = 0; i < sectionList->size(); i++)
    {
        if ((sequence->at(i) == seq) && (!alternate->at(i)))
        {
            sOld = sectionList->at(i);
            index = i;
        }
        if ((sequence->at(i == seq) && alternate->at(i))) {
            altOldList.append(sectionList->at(i));
        }
        if ((sequence->at(i == (seq - 1)) && (!alternate->at(i)))) {
            beforeSection = sectionList->at(i);
            beforeSectionDirection = direction->at(i);
        }
        if ((sequence->at(i == (seq + 1)) && (!alternate->at(i)))) {
            afterSection = sectionList->at(i);
            afterSectionDirection =  Section::FORWARD;
            if (afterSectionDirection == direction->at(i)) {
                afterSectionDirection =  Section::REVERSE;
            }
        }
    }
    if (sOld == NULL) {
        log->error("Missing primary Section for seq = " + QString::number(seq));
        return;
    }
    QList<Section*> possibles =  QList<Section*>();
    QVector<int> possiblesDirection =  QVector<int>(150);
    QList<QString> possibleNames = QStringList();
    QList<QString> allSections = sectionManager->getSystemNameList();
    for (int i = 0; i < allSections.size(); i++) {
        Section* mayBeSection = NULL;
        QString mayBeName = allSections.at(i);
        int mayBeDirection = 0;
        Section* s = (Section*)sectionManager->getBySystemName(mayBeName);
        if ((s != NULL) && (s != sOld) && (s != beforeSection)
                && (s != afterSection) && (!inSectionList(s, altOldList))) {
            if (beforeSection != NULL) {
                if (forwardConnected(s, beforeSection, beforeSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::FORWARD;
                } else if (reverseConnected(s, beforeSection, beforeSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::REVERSE;
                }
                if ((mayBeSection != NULL) && (afterSection != NULL)) {
                    if (mayBeDirection ==  Section::REVERSE) {
                        if (!forwardConnected(s, afterSection, afterSectionDirection)) {
                            mayBeSection = NULL;
                        }
                    } else {
                        if (!reverseConnected(s, afterSection, afterSectionDirection)) {
                            mayBeSection = NULL;
                        }
                    }
                }
            } else if (afterSection != NULL) {
                if (forwardConnected(s, afterSection, afterSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::REVERSE;
                } else if (reverseConnected(s, afterSection, afterSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::FORWARD;
                }
            } else {
                mayBeSection = s;
                mayBeDirection =  Section::FORWARD;
            }
            if (mayBeSection != NULL) {
                possibles.append(mayBeSection);
                possiblesDirection.replace(possibles.size() - 1, mayBeDirection);
                possibleNames.append(mayBeName);
            }
        }
    }
    if (possibles.size() == 0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame,
//                java.text.MessageFormat.format(tr("Message36"),
//                        new Object[]{"" + seq}), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Message36"));
        return;
    }
    int k = 0;
#if 1 // TODO:
    if (possibles.size() > 1)
    {
        QVector<QVariant>* choices = new QVector<QVariant>(possibles.size());
        for (int j = 0; j < possibles.size(); j++) {
            choices->replace(j, possibleNames.at(j));
        }
//        Object selName = JOptionPane.showInputDialog(addFrame,
//                tr("ReplacePrimaryChoice"),
//                tr("ReplacePrimaryTitle"),
//                JOptionPane.QUESTION_MESSAGE, NULL, choices, choices[0]);
        InputDialog* dlg = new InputDialog(tr("Please select a Section to replace\nthe current Primary Selection."), choices->toList(), 0, tr("Select"));
        dlg->exec();
        QVariant selName = dlg->value();
        if (selName == QVariant() || selName.toString().isEmpty()) {
            return;
        }
        for (int j = 0; j < possibles.size(); j++) {
            if (selName == (choices->at(j))) {
                k = j;
            }
        }
    }
#endif
    sectionList->removeAt(index);
    sectionList->insert(index, possibles.at(k));
    direction->replace(index, possiblesDirection.at(k));
    if (index == (sectionList->size() - 1)) {
        curSection = sectionList->at(index);
        curSectionDirection = direction->at(index);
    } else if (index == (sectionList->size() - 2)) {
        prevSection = sectionList->at(index);
        prevSectionDirection = direction->at(index);
    }
    initializeSectionCombos();
    sectionTableModel->fireTableDataChanged();
}

bool TransitTableAction::inSectionList(Section* s, QList<Section*> sList) {
    for (int i = 0; i < sList.size(); i++) {
        if (sList.at(i) == s) {
            return true;
        }
    }
    return false;
}

int TransitTableAction::getSeqNum() {
    int n = 0;
    bool bOk;
        n = seqNum->text().toInt(&bOk);
    if(!bOk){
        log->error("Unable to convert " + seqNum->text() + " to a number");
    }
    if ((n < 1) || (n > curSequenceNum)) {
//        javax.swing.JOptionPane.showMessageDialog(NULL, rbx
//                .getString("Message34"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Message34"));
        return 0;
    }
    return n;
}

void TransitTableAction::deleteAlternateForSeqPressed(ActionEvent* /*e*/) {
    if (sectionList->size() <= 1) {
        deleteAllSections(/*e*/);
    } else {
        int seq = getSeqNum();
        if (seq == 0) {
            return;
        }
        for (int i = sectionList->size(); i >= seq; i--) {
            if ((sequence->at(i) == seq) && !alternate->at(i)) {
                for (int j = i; j < sectionList->size() - 1; j++) {
                    sequence->replace(j,sequence->at(j + 1));
                    direction->replace(j, direction->at(j + 1));
                    action.replace(j, action.at(j + 1));
                    alternate->replace(j, alternate->at(j + 1));
                }
                sectionList->removeAt(i);
            }
        }
        initializeSectionCombos();
    }
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::addAlternateForSeqPressed(ActionEvent* /*e*/) {
    if (sectionList->size() > maxSections) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message23"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("A Transit may not have more than 150 Sections assigned to it."));
        return;
    }
    int seq = getSeqNum();
    if (seq == 0) {
        return;
    }
    Section* primarySection = NULL;
    QList<Section*> altOldList = QList<Section*>();
    Section* beforeSection = NULL;
    int beforeSectionDirection = 0;
    Section* afterSection = NULL;
    int afterSectionDirection = 0;
    int index = -1;
    for (int i = 0; i < sectionList->size(); i++) {
        if ((sequence->at(i) == seq) && (!alternate->at(i))) {
            primarySection = sectionList->at(i);
            index = i;
        }
        if ((sequence->at(i) == seq) && alternate->at(i)) {
            altOldList.append(sectionList->at(i));
        }
        if ((sequence->at(i) == (seq - 1)) && (!alternate->at(i))) {
            beforeSection = sectionList->at(i);
            beforeSectionDirection = direction->at(i);
        }
        if ((sequence->at(i) == (seq + 1)) && (!alternate->at(i))) {
            afterSection = sectionList->at(i);
            afterSectionDirection =  Section::FORWARD;
            if (afterSectionDirection == direction->at(i)) {
                afterSectionDirection =  Section::REVERSE;
            }
        }
    }
    if (primarySection == NULL) {
        log->error("Missing primary Section for seq = " + QString::number(seq));
        return;
    }
    QList<Section*> possibles =  QList<Section*>();
    QVector<int> possiblesDirection =  QVector<int>(150);
    QList<QString> possibleNames = QList<QString>();
    QList<QString> allSections = sectionManager->getSystemNameList();
    for (int i = 0; i < allSections.size(); i++) {
        Section* mayBeSection = NULL;
        QString mayBeName = allSections.at(i);
        int mayBeDirection = 0;
        Section* s = (Section*)sectionManager->getBySystemName(mayBeName);
        if ((s != NULL) && (s != primarySection) && (s != beforeSection)
                && (s != afterSection) && (!inSectionList(s, altOldList))) {
            if (beforeSection != NULL) {
                if (forwardConnected(s, beforeSection, beforeSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::FORWARD;
                } else if (reverseConnected(s, beforeSection, beforeSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::REVERSE;
                }
                if ((mayBeSection != NULL) && (afterSection != NULL)) {
                    if (mayBeDirection ==  Section::REVERSE) {
                        if (!forwardConnected(s, afterSection, afterSectionDirection)) {
                            mayBeSection = NULL;
                        }
                    } else {
                        if (!reverseConnected(s, afterSection, afterSectionDirection)) {
                            mayBeSection = NULL;
                        }
                    }
                }
            } else if (afterSection != NULL) {
                if (forwardConnected(s, afterSection, afterSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::REVERSE;
                } else if (reverseConnected(s, afterSection, afterSectionDirection)) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        mayBeName = mayBeName + "( " + s->getUserName() + " )";
                    }
                    mayBeSection = s;
                    mayBeDirection =  Section::FORWARD;
                }
            } else {
                mayBeSection = s;
                mayBeDirection =  Section::FORWARD;
            }
            if (mayBeSection != NULL) {
                possibles.append(mayBeSection);
                possiblesDirection[possibles.size() - 1] = mayBeDirection;
                possibleNames.append(mayBeName);
            }
        }
    }
    if (possibles.size() == 0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame,
//                java.text.MessageFormat.format(tr("Message37"),
//                        new Object[]{"" + seq}), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Sorry, no new alternate Section found for the Primary Section at \"%1\".").arg(seq));
        return;
    }
    int k = 0;
    if (possibles.size() > 1) {
        QVector<QVariant> choices =  QVector<QVariant>(possibles.size());
        for (int j = 0; j < possibles.size(); j++) {
            choices.replace(j,  possibleNames.at(j));
        }
//        Object selName = JOptionPane.showInputDialog(addFrame,
//                tr("AddAlternateChoice"),
//                tr("AddAlternateTitle"),
//                JOptionPane.QUESTION_MESSAGE, NULL, choices, choices[0]);
        InputDialog* dlg = new InputDialog(tr("Please select an alternate Section to add."),choices.toList(),0,tr("Choose Alternate Section"));
        dlg->exec();
        QString selName = dlg->value();

        if (selName == "") {
            return;
        }
        for (int j = 0; j < possibles.size(); j++) {
            if (selName == (choices.at(j))) {
                k = j;
            }
        }
    }
    index = index + 1 + altOldList.size();
    sectionList->replace(index, possibles.at(k));
    for (int i = sectionList->size() - 2; i >= index; i--) {
        direction->replace(i + 1, direction->at(i));
        alternate->replace(i + 1, alternate->at(i));
        action.replace(i + 1, action.at(i));
        sequence->replace(i + 1, sequence->at(i));
    }
    direction->replace(index, possiblesDirection.at(k));
    sequence->replace(index, sequence->at(index - 1));
    alternate->replace(index, true);
    action.replace(index, new QList<TransitSectionAction*>());
    initializeSectionCombos();

    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::addAlternateSectionPressed(ActionEvent* /*e*/) {
    if (sectionList->size() > maxSections) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message23"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("A Transit may not have more than 150 Sections assigned to it."));
        return;
    }
    if (alternateSectionBoxList->size() == 0) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message24"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - No alternate section to add."));
        return;
    }
    int index = alternateSectionBox->currentIndex();
    Section* s = alternateSectionBoxList->at(index);
    if (s != NULL) {
        int j = sectionList->size();
        sectionList->append(s);
        direction->replace(j, altSectionDirection->at(index));
        sequence->replace(j, curSequenceNum);
        action.replace(j, new QList<TransitSectionAction*>());
        alternate->replace(j, true);
        initializeSectionCombos();
    }
    sectionTableModel->fireTableDataChanged();
}

void TransitTableAction::createPressed(ActionEvent* /*e*/) {
    if (!checkTransitInformation()) {
        return;
    }
    QString uName = userName->text();
    if (uName == ("")) {
        uName = "";
    }

    // attempt to create the new Transit
    if (_autoSystemName->isChecked()) {
        curTransit = transitManager->createNewTransit(uName);
    } else {
        QString sName = sysName->text().toUpper();
        curTransit = transitManager->createNewTransit(sName, uName);
    }
    if (curTransit == NULL) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message22"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("Error - Cannot create a new Transit. System name or user name is not unique."));
        return;
    }
    sysName->setText(curTransit->getSystemName());
    setTransitInformation();
    addFrame->setVisible(false);
    pref->setSimplePreferenceState(systemNameAuto, _autoSystemName->isChecked());
}

void TransitTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();  // remove addFrame from Windows menu
    addFrame = NULL;
}

void TransitTableAction::updatePressed(ActionEvent* /*e*/) {
    if (!checkTransitInformation()) {
        return;
    }
    // check if user name has been changed
    QString uName = userName->text();
    if (uName == ("")) {
        uName = "";
    }
    if ((uName != NULL) && (uName != (curTransit->getUserName()))) {
        // check that new user name is unique
        Transit* tTransit = transitManager->getByUserName(uName);
        if (tTransit != NULL) {
//            javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                    .getString("Message22"), tr("ErrorTitle"),
//                    javax.swing.JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addFrame, tr("Error"), tr("Error - Cannot create a new Transit. System name or user name is not unique."));
            return;
        }
    }
    curTransit->setUserName(uName);
    if (setTransitInformation()) {
        // successful update
        addFrame->setVisible(false);
        addFrame->dispose();  // remove addFrame from Windows menu
        addFrame = NULL;
    }
}

/*private*/ bool TransitTableAction::checkTransitInformation() {
    if ((sectionList->size() <= 1) || (curSequenceNum <= 1)) {
//        javax.swing.JOptionPane.showMessageDialog(addFrame, rbx
//                .getString("Message26"), tr("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addFrame, tr("Error"), tr("A Transit requires at least two primary Sections. Please add Sections before attempting to create/update this Transit."));

        return false;
    }
// djd debugging - need to add code to check Transit Information
// add code here as needed
    return true;
}

/*private*/ bool TransitTableAction::setTransitInformation() {
    if (curTransit == NULL) {
        return false;
    }
    curTransit->removeAllSections();
    for (int i = 0; i < sectionList->size(); i++) {
        TransitSection* ts = new TransitSection(sectionList->at(i),
                sequence->at(i), direction->at(i), alternate->at(i));
        // FIXME: Why is this NULL check here? We just instansiated ts as a new TransitSection, which should keep it from ever being NULL
        if (NULL == ts) {
            log->error("Trouble creating TransitSection");
            return false;
        }
        QList<TransitSectionAction*>* list = action.at(i);
        if (list != NULL) {
            for (int j = 0; j < list->size(); j++) {
                ts->addAction(list->at(j));
            }
        }
        curTransit->addTransitSection(ts);
    }
    return true;
}

/*private*/ void TransitTableAction::initializeSectionCombos() {
    QList<QString> allSections = sectionManager->getSystemNameList();
    primarySectionBox->clear();
    alternateSectionBox->clear();
    insertAtBeginningBox->clear();
    primarySectionBoxList->clear();
    alternateSectionBoxList->clear();
    insertAtBeginningBoxList->clear();
    if (sectionList->size() == 0) {
        // no Sections currently in Transit - all Sections and all Directions OK
        for (int i = 0; i < allSections.size(); i++) {
            QString sName = allSections.at(i);
            Section* s = (Section*)sectionManager->getBySystemName(sName);
            if (s != NULL) {
                if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                    sName = sName + "( " + s->getUserName() + " )";
                }
                primarySectionBox->addItem(sName);
                primarySectionBoxList->append(s);
                priSectionDirection->replace(primarySectionBoxList->size() - 1, Section::FORWARD);
            }
        }
    } else {
        // limit to Sections that connect to the current Section and are not the previous Section
        for (int i = 0; i < allSections.size(); i++) {
            QString sName = allSections.at(i);
            Section* s = (Section*)sectionManager->getBySystemName(sName);
            if (s != NULL) {
                if ((s != prevSection) && (forwardConnected(s, curSection, curSectionDirection))) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        sName = sName + "( " + s->getUserName() + " )";
                    }
                    primarySectionBox->addItem(sName);
                    primarySectionBoxList->append(s);
                    priSectionDirection->replace(primarySectionBoxList->size() - 1, Section::FORWARD);
                } else if ((s != prevSection) && (reverseConnected(s, curSection, curSectionDirection))) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        sName = sName + "( " + s->getUserName() + " )";
                    }
                    primarySectionBox->addItem(sName);
                    primarySectionBoxList->append(s);
                    priSectionDirection->replace(primarySectionBoxList->size() - 1, Section::REVERSE);
                }
            }
        }
        // check if there are any alternate Section choices
        if (prevSection != NULL) {
            for (int i = 0; i < allSections.size(); i++) {
                QString sName = allSections.at(i);
                Section* s = (Section*)sectionManager->getBySystemName(sName);
                if (s != NULL) {
                    if ((notIncludedWithSeq(s, curSequenceNum))
                            && forwardConnected(s, prevSection, prevSectionDirection)) {
                        if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                            sName = sName + "( " + s->getUserName() + " )";
                        }
                        alternateSectionBox->addItem(sName);
                        alternateSectionBoxList->append(s);
                        altSectionDirection->replace(alternateSectionBoxList->size() - 1,  Section::FORWARD);
                    } else if (notIncludedWithSeq(s, curSequenceNum)
                            && reverseConnected(s, prevSection, prevSectionDirection)) {
                        if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                            sName = sName + "( " + s->getUserName() + " )";
                        }
                        alternateSectionBox->addItem(sName);
                        alternateSectionBoxList->append(s);
                        altSectionDirection->replace(alternateSectionBoxList->size() - 1,  Section::REVERSE);
                    }
                }
            }
        }
        // check if there are any Sections available to be inserted at beginning
        Section* firstSection = sectionList->at(0);
        int testDirection =  Section::FORWARD;
        if (direction->at(0) ==  Section::FORWARD) {
            testDirection =  Section::REVERSE;
        }
        for (int i = 0; i < allSections.size(); i++) {
            QString sName = allSections.at(i);
            Section* s = (Section*)sectionManager->getBySystemName(sName);
            if (s != NULL) {
                if ((s != firstSection) && (forwardConnected(s, firstSection, testDirection))) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        sName = sName + "( " + s->getUserName() + " )";
                    }
                    insertAtBeginningBox->addItem(sName);
                    insertAtBeginningBoxList->append(s);
                    insertAtBeginningDirection->replace(insertAtBeginningBoxList->size() - 1,  Section::REVERSE);
                } else if ((s != firstSection) && (reverseConnected(s, firstSection, testDirection))) {
                    if ((s->getUserName() != NULL) && (s->getUserName() != (""))) {
                        sName = sName + "( " + s->getUserName() + " )";
                    }
                    insertAtBeginningBox->addItem(sName);
                    insertAtBeginningBoxList->append(s);
                    insertAtBeginningDirection->replace(insertAtBeginningBoxList->size() - 1,  Section::FORWARD);
                }
            }
        }
    }
}
#if 0
//@SuppressWarnings("unused")
/*private*/ boolean connected(Section s1, Section s2) {
    if ((s1 != NULL) && (s2 != NULL)) {
        List<EntryPoint> s1Entries = s1.getEntryPointList();
        List<EntryPoint> s2Entries = s2->getEntryPointList();
        for (int i = 0; i < s1Entries.size(); i++) {
            Block b = s1Entries->get(i).getFromBlock();
            for (int j = 0; j < s2Entries.size(); j++) {
                if (b == s2Entries->get(j).getBlock()) {
                    return true;
                }
            }
        }
    }
    return false;
}
#endif
/*private*/ bool TransitTableAction::forwardConnected(Section* s1, Section* s2, int restrictedDirection) {
    if ((s1 != NULL) && (s2 != NULL)) {
        QList<EntryPoint*>* s1ForwardEntries = s1->getForwardEntryPointList();
        QList<EntryPoint*>* s2Entries =  new QList<EntryPoint*>();
        if (restrictedDirection ==  Section::FORWARD) {
            s2Entries = s2->getReverseEntryPointList();
        } else if (restrictedDirection ==  Section::REVERSE) {
            s2Entries = s2->getForwardEntryPointList();
        } else {
            s2Entries = s2->getEntryPointList();
        }
        for (int i = 0; i < s1ForwardEntries->size(); i++) {
            Block* b1 = s1ForwardEntries->at(i)->getFromBlock();
            for (int j = 0; j < s2Entries->size(); j++) {
                Block* b2 = s2Entries->at(j)->getFromBlock();
                if ((b1 == s2Entries->at(j)->getBlock())
                        && (b2 == s1ForwardEntries->at(i)->getBlock())) {
                    return true;
                }
            }
        }
    }
    return false;
}

/*private*/ bool TransitTableAction::reverseConnected(Section* s1, Section* s2, int restrictedDirection) {
    if ((s1 != NULL) && (s2 != NULL)) {
        QList<EntryPoint*>* s1ReverseEntries = s1->getReverseEntryPointList();
        QList<EntryPoint*>* s2Entries = new QList<EntryPoint*>();
        if (restrictedDirection ==  Section::FORWARD) {
            s2Entries = s2->getReverseEntryPointList();
        } else if (restrictedDirection ==  Section::REVERSE) {
            s2Entries = s2->getForwardEntryPointList();
        } else {
            s2Entries = s2->getEntryPointList();
        }
        for (int i = 0; i < s1ReverseEntries->size(); i++) {
            Block* b1 = s1ReverseEntries->at(i)->getFromBlock();
            for (int j = 0; j < s2Entries->size(); j++) {
                Block* b2 = s2Entries->at(j)->getFromBlock();
                if ((b1 == s2Entries->at(j)->getBlock())
                        && (b2 == s1ReverseEntries->at(i)->getBlock())) {
                    return true;
                }
            }
        }
    }
    return false;
}

/*private*/ bool TransitTableAction::notIncludedWithSeq(Section* s, int seq) {
    for (int i = 0; i < sectionList->size(); i++) {
        if ((sectionList->at(i) == s) && (seq == sequence->at(i))) {
            return false;
        }
    }
    return true;
}

/*private*/ void TransitTableAction::autoSystemName() {
    if (_autoSystemName->isChecked()) {
//            create.setEnabled(true);
        sysName->setEnabled(false);
        sysNameLabel->setEnabled(false);
    } else {
//            if (sysName.getText().length() > 0)
//                create.setEnabled(true);
//            else
//                create.setEnabled(false);
        sysName->setEnabled(true);
        sysNameLabel->setEnabled(true);
    }
}


/*private*/ void TransitTableAction::addEditActionsPressed(int r)
{
    activeRow = r;
    if (actionTableModel != NULL) {
        actionTableModel->fireTableStructureChanged();
    }
    if (actionTableFrame == NULL) {
        actionTableFrame = new JmriJFrameX(tr("ViewA ctions"));
        actionTableFrame->addHelpMenu(
                "package.jmri.jmrit.beantable.ViewSpecialActions", true);
        actionTableFrame->setLocation(50, 60);
        QWidget* contentPane = actionTableFrame->getContentPane();
        //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
        QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
        QWidget* panel1 = new QWidget();
        //panel1.setLayout(new FlowLayout());
        FlowLayout* panel1Layout = new FlowLayout(panel1);
        QLabel* sectionNameLabel = new QLabel(tr("Section Name") + ": ");
        panel1Layout->addWidget(sectionNameLabel);
        panel1Layout->addWidget(fixedSectionLabel);
        contentPaneLayout->addWidget(panel1);
        // add table of Actions
        QWidget* pctSpace = new QWidget();
        //pctSpace.setLayout(new FlowLayout());
        FlowLayout* pctSpaceLayout = new FlowLayout(pctSpace);
        pctSpaceLayout->addWidget(new QLabel("   "));
        contentPaneLayout->addWidget(pctSpace);
        QWidget* pct = new QWidget();
        QGridLayout* pctLayout;
        pct->setLayout(pctLayout = new QGridLayout);
        // initialize table of actions
        actionTableModel = new SpecialActionTableModel(this);
        JTable* actionTable = new JTable(actionTableModel);
//        actionTable->setRowSelectionAllowed(false);
//        actionTable->setPreferredScrollableViewportSize(
//                new java.awt.Dimension(750, 200));
        TableColumnModel* actionColumnModel = actionTable
                ->getColumnModel();
        TableColumn* whenColumn = actionColumnModel
                ->getColumn(SpecialActionTableModel::WHEN_COLUMN);
//        whenColumn.setResizable(true);
//        whenColumn.setMinWidth(270);
//        whenColumn.setMaxWidth(300);
        TableColumn* whatColumn = actionColumnModel
                ->getColumn(SpecialActionTableModel::WHAT_COLUMN);
//        whatColumn.setResizable(true);
//        whatColumn.setMinWidth(290);
//        whatColumn.setMaxWidth(350);
        TableColumn* editColumn = actionColumnModel
                ->getColumn(SpecialActionTableModel::EDIT_COLUMN);
        // install button renderer and editor
//        ButtonRenderer buttonRenderer = new ButtonRenderer();
//        actionTable.setDefaultRenderer(JButton.class, buttonRenderer);
//        TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//        actionTable.setDefaultEditor(JButton.class, buttonEditor);
//        JButton testButton = new JButton(tr("ButtonDelete"));
//        actionTable.setRowHeight(testButton.getPreferredSize().height);
//        editColumn.setResizable(false);
//        editColumn.setMinWidth(testButton.sizeHint().width());
        TableColumn* removeColumn = actionColumnModel
                ->getColumn(SpecialActionTableModel::REMOVE_COLUMN);
//        removeColumn.setMinWidth(testButton.sizeHint().width());
//        removeColumn.setResizable(false);
        //JScrollPane actionTableScrollPane = new JScrollPane(
//                actionTable);
        pctLayout->addWidget(/*actionTableScrollPane*/actionTable,0, 0); //BorderLayout.CENTER);
        contentPaneLayout->addWidget(pct);
        pct->setVisible(true);
        // add view action panel buttons
        QWidget* but = new QWidget();
        //but.setLayout(new BoxLayout(but, BoxLayout.Y_AXIS));
        QVBoxLayout* butLayout = new QVBoxLayout(but);
        QWidget* panel4 = new QWidget();
        //panel4.setLayout(new FlowLayout());
        FlowLayout* panel4Layout = new FlowLayout(panel4);
        QPushButton* newActionButton = new QPushButton(tr("Add New Action"));
        panel4Layout->addWidget(newActionButton);
//        newActionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                newActionPressed(e);
//            }
//        });
        connect(newActionButton, SIGNAL(clicked(bool)), this, SLOT(newActionPressed(ActionEvent*)));
        newActionButton->setToolTip(tr("Press to add a new Action"));
        QPushButton* doneButton = new QPushButton(tr("Done"));
        panel4Layout->addWidget(doneButton);
//        doneButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                doneWithActionsPressed(e);
//            }
//        });
        connect(doneButton, SIGNAL(clicked(bool)), this, SLOT(doneWithActionsPressed()));
        doneButton->setToolTip(tr("Press when finished with this window"));
        butLayout->addWidget(panel4);
        contentPaneLayout->addWidget(but);
    }
    fixedSectionLabel->setText(getSectionNameByRow(r) + "    "
            + tr("SequenceAbbrev") + ": " + QString::number(sequence->at(r)));
    // TODO:
//    actionTableFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            if (actionTableFrame != NULL) {
//                actionTableFrame.setVisible(false);
//                actionTableFrame.dispose();
//                actionTableFrame = NULL;
//            }
//            if (addEditActionFrame != NULL) {
//                addEditActionFrame->setVisible(false);
//                addEditActionFrame->dispose();
//                addEditActionFrame = NULL;
//            }
//        }
//    });
    ATWindowListener* windowListener = new ATWindowListener(this);
    actionTableFrame->addWindowListener(windowListener);
    actionTableFrame->pack();
    actionTableFrame->setVisible(true);
}

ATWindowListener::ATWindowListener(TransitTableAction* act)
{
 this->act = act;
}
/*public*/ void ATWindowListener::windowClosing(QCloseEvent*) {
    if (act->actionTableFrame != NULL) {
        act->actionTableFrame->setVisible(false);
        act->actionTableFrame->dispose();
        act->actionTableFrame = NULL;
    }
    if (act->addEditActionFrame != NULL) {
        act->addEditActionFrame->setVisible(false);
        act->addEditActionFrame->dispose();
        act->addEditActionFrame = NULL;
    }
}

/*private*/ void TransitTableAction::doneWithActionsPressed(ActionEvent* /*e*/) {
    actionTableFrame->setVisible(false);
    actionTableFrame->dispose();
    actionTableFrame = NULL;
    if (addEditActionFrame != NULL) {
        addEditActionFrame->setVisible(false);
        addEditActionFrame->dispose();
        addEditActionFrame = NULL;
    }
}

/*private*/ void TransitTableAction::newActionPressed(ActionEvent* /*e*/) {
    editActionMode = false;
    curTSA = NULL;
    addEditActionWindow();
}

/*private*/ void TransitTableAction::addEditActionWindow()
{
 if (addEditActionFrame == NULL)
 {
    // set up add/edit action window
    addEditActionFrame = new JmriJFrameX(tr("Add/Edit Action"));
    addEditActionFrame->addHelpMenu(
            "package.jmri.jmrit.beantable.TransitSectionAddEditAction", true);
    addEditActionFrame->setLocation(120, 80);
    addEditActionFrame->setMinimumWidth(500);
    QWidget* contentPane = addEditActionFrame->getContentPane();
    //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
    QVBoxLayout* contentPaneLayout = new QVBoxLayout(contentPane);
    QWidget* panelx = new QWidget();
    //panelx.setLayout(new BoxLayout(panelx, BoxLayout.Y_AXIS));
    QVBoxLayout* panelxLayout = new QVBoxLayout(panelx);
    QWidget* panel1 = new QWidget();
    //panel1.setLayout(new FlowLayout());
    FlowLayout* panel1Layout = new FlowLayout(panel1);
    panel1Layout->addWidget(new QLabel(tr("When:")));
    initializeWhenBox();
    panel1Layout->addWidget(whenBox);
    whenBox->setToolTip(tr("Select when the action is to be initiated"));
//        whenBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setWhen(whenBox.getSelectedIndex() + 1);
//            }
//        });
    connect(whenBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(On_whenBox_currentIndexChanged()));
    panel1Layout->addWidget(whenStringField);
    initializeBlockBox();
    panel1Layout->addWidget(blockBox);
    panelxLayout->addWidget(panel1);
    QWidget* panel11 = new QWidget();
    //panel11.setLayout(new FlowLayout());
    FlowLayout* panel11Layout = new FlowLayout(panel11);
    panel11Layout->addWidget(new QLabel("    " + tr("Optional Delay") + ": "));
    panel11Layout->addWidget(whenDataField);
    whenDataField->setToolTip(tr("(Optional) Enter time in milliseconds to wait before action is initiated"));
    panel11Layout->addWidget(new QLabel(tr("Milliseconds")));
    panelxLayout->addWidget(panel11);
    QWidget* sp = new QWidget();
    //sp.setLayout(new FlowLayout());
    FlowLayout* spLayout = new FlowLayout(sp);
    spLayout->addWidget(new QLabel("     "));
    panelxLayout->addWidget(sp);
    QWidget* panel2 = new QWidget();
    //panel2.setLayout(new FlowLayout());
    FlowLayout* panel2Layout = new FlowLayout(panel2);
    panel2Layout->addWidget(new QLabel(tr("What:")));
    initializeWhatBox();
    panel2Layout->addWidget(whatBox);
    whatBox->setToolTip(tr("Select what action is requested"));
//        whatBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setWhat(whatBox.getSelectedIndex() + 1);
//            }
//        });
    connect(whatBox, SIGNAL(currentIndexChanged(int)), this, SLOT(On_whatBox_currentIndexChanged()));
    panel2Layout->addWidget(whatStringField);
    panelxLayout->addWidget(panel2);
    QWidget* panel21 = new QWidget();
    //panel21.setLayout(new FlowLayout());
    FlowLayout* panel21Layout = new FlowLayout(panel21);
    panel21Layout->addWidget(whatData1Field);
    panel21Layout->addWidget(whatData2Field);
    QButtonGroup* onOffGroup = new QButtonGroup();
    onOffGroup->addButton(onButton);
    onOffGroup->addButton(offButton);
    panel21Layout->addWidget(onButton);
    panel21Layout->addWidget(offButton);
    panel21Layout->addWidget(doneSensorLabel);
    panel21Layout->addWidget(doneSensorField);
    panelxLayout->addWidget(panel21);
    contentPaneLayout->addWidget(panelx);
    contentPaneLayout->addWidget(new JSeparator());
    // add buttons
    QWidget* but = new QWidget();
    //but.setLayout(new FlowLayout());
    FlowLayout* butLayout = new FlowLayout(but);
    createActionButton = new QPushButton(tr("Create New Action"));
    butLayout->addWidget(createActionButton);
//        createActionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                createActionPressed(e);
//            }
//        });
    connect(createActionButton, SIGNAL(clicked(bool)), this, SLOT(createActionPressed()));
    createActionButton->setToolTip(tr("Press to create new Action"));
    updateActionButton = new QPushButton(tr("Update Action"));
    butLayout->addWidget(updateActionButton);
//        updateActionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                updateActionPressed(e);
//            }
//        });
    connect(updateActionButton, SIGNAL(clicked(bool)), this, SLOT(updatePressed()));
    updateActionButton->setToolTip(tr("Press to update this Action"));
    butLayout->addWidget(cancelAddEditActionButton = new QPushButton(tr("Cancel")));
//        cancelAddEditActionButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelAddEditActionPressed(e);
//            }
//        });
    connect(cancelAddEditActionButton, SIGNAL(clicked(bool)), this, SLOT(cancelAddEditActionPressed()));
    cancelAddEditActionButton->setToolTip(tr("Press to cancel without creating or updating."));
    contentPaneLayout->addWidget(but);
 }
 if (editActionMode)
 {
    // initialize window for the action being edited
    updateActionButton->setVisible(true);
    createActionButton->setVisible(false);
    whenDataField->setText("" + curTSA->getDataWhen());
    whenStringField->setText(curTSA->getStringWhen());
    whatData1Field->setText("" + curTSA->getDataWhat1());
    whatData2Field->setText("" + curTSA->getDataWhat2());
    whatStringField->setText(curTSA->getStringWhat());
    onButton->setChecked(true);
    if (curTSA->getStringWhat() == ("Off")) {
        offButton->setChecked(true);
    }
    setWhen(curTSA->getWhenCode());
    setWhat(curTSA->getWhatCode());
    setBlockBox();
} else {
    // initialize for add new action
    whenDataField->setText("");
    whenStringField->setText("");
    whatData1Field->setText("");
    whatData2Field->setText("");
    whatStringField->setText("");
    onButton->setChecked(true);
    setWhen(1);
    setWhat(1);
    updateActionButton->setVisible(false);
    createActionButton->setVisible(true);
    setBlockBox();
 }
//    addEditActionFrame.addWindowListener(new java.awt.event.WindowAdapter()
//    {
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            if (addEditActionFrame != NULL) {
//                addEditActionFrame.setVisible(false);
//            }
//        }
//    });
 addEditActionFrame->addWindowListener(new AEFWindowListener(this));
 addEditActionFrame->pack();
 addEditActionFrame->setVisible(true);
}

void TransitTableAction::On_whenBox_currentIndexChanged()
{
 setWhen(whenBox->currentIndex() + 1);
}

void TransitTableAction::On_whatBox_currentIndexChanged()
{
 setWhat(whatBox->currentIndex() + 1);
}

AEFWindowListener::AEFWindowListener(TransitTableAction *act) {this->act = act;}
void AEFWindowListener::windowClosing(QCloseEvent *e)
{
    if (act->addEditActionFrame != NULL) {
        act->addEditActionFrame->setVisible(false);
    }

}

/*private*/ void TransitTableAction::setWhen(int code) {
    whenBox->setCurrentIndex(code - 1);
    whenStringField->setVisible(false);
    blockBox->setVisible(false);
    switch (code) {
        case TransitSectionAction::ENTRY:
        case TransitSectionAction::EXIT:
        case TransitSectionAction::TRAINSTOP:
        case TransitSectionAction::TRAINSTART:
            break;
        case TransitSectionAction::BLOCKENTRY:
        case TransitSectionAction::BLOCKEXIT:
            blockBox->setVisible(true);
            blockBox->setToolTip(tr("Select a Block in this Section."));
            break;
        case TransitSectionAction::SENSORACTIVE:
        case TransitSectionAction::SENSORINACTIVE:
            whenStringField->setVisible(true);
            whenStringField->setToolTip(tr("Enter the system name or user name of the Sensor"));
            break;
    }
    addEditActionFrame->pack();
    addEditActionFrame->setVisible(true);
}

/*private*/ void  TransitTableAction::setWhat(int code) {
    whatBox->setCurrentIndex(code - 1);
    whatStringField->setVisible(false);
    whatData1Field->setVisible(false);
    whatData2Field->setVisible(false);
    onButton->setVisible(false);
    offButton->setVisible(false);
    doneSensorLabel->setVisible(false);
    doneSensorField->setVisible(false);
    switch (code) {
        case TransitSectionAction::PAUSE:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter the number of fast clock minutes to pause for."));
            break;
        case TransitSectionAction::SETMAXSPEED:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter target speed percentage (1-99)"));
            break;
        case TransitSectionAction::SETCURRENTSPEED:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter target speed percentage (1-99)"));
            break;
        case TransitSectionAction::RAMPTRAINSPEED:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter target speed percentage (1-99)"));
            break;
        case TransitSectionAction::TOMANUALMODE:
            doneSensorLabel->setVisible(true);
            doneSensorField->setVisible(true);
            doneSensorField->setToolTip(tr("(Optional) Enter name of sensor for notifying dispatcher when done working."));
            break;
        case TransitSectionAction::SETLIGHT:
            onButton->setVisible(true);
            offButton->setVisible(true);
            onButton->setToolTip(tr("Select On or Off to switch light on or off"));
            offButton->setToolTip(tr("Select On or Off to switch light on or off"));
            break;
        case TransitSectionAction::STARTBELL:
            break;
        case TransitSectionAction::STOPBELL:
            break;
        case TransitSectionAction::SOUNDHORN:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter length of time in milliseconds for single blast of horn"));
            break;
        case TransitSectionAction::SOUNDHORNPATTERN:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter length of short sound in milliseconds"));
            whatData2Field->setVisible(true);
            whatData2Field->setToolTip(tr("Enter length of long sound in milliseconds"));
            whatStringField->setVisible(true);
            whatStringField->setToolTip(tr("Enter pattern: 's' for short, 'l' for long, e.g. 'lsl' for long-short-long"));
            break;
        case TransitSectionAction::LOCOFUNCTION:
            whatData1Field->setVisible(true);
            whatData1Field->setToolTip(tr("Enter number (0-28) of decoder function to set."));
            onButton->setVisible(true);
            offButton->setVisible(true);
            onButton->setToolTip(tr("Select On or Off to set specified function on or off."));
            offButton->setToolTip(tr("Select On or Off to set specified function on or off."));
            break;
        case TransitSectionAction::SETSENSORACTIVE:
        case TransitSectionAction::SETSENSORINACTIVE:
            whatStringField->setVisible(true);
            whatStringField->setToolTip(tr("Enter the system name or user name of the Sensor"));
            break;
    }
    addEditActionFrame->pack();
    addEditActionFrame->setVisible(true);
}

// handle button presses in add/edit action window
/*private*/ void TransitTableAction::createActionPressed(ActionEvent* /*e*/) {
    if ((!validateWhenData()) || (!validateWhatData())) {
        return;
    }
    // entered data is OK, create a special action
    curTSA = new TransitSectionAction(tWhen, tWhat, tWhenData, tWhatData1, tWhatData2, tWhenString, tWhatString);
    if (curTSA == NULL) {
        log->error("Failure when creating new TransitSectionAction");
    }
    QList<TransitSectionAction*>* list = action.at(activeRow);
    list->append(curTSA);
    actionTableModel->fireTableDataChanged();
    addEditActionFrame->setVisible(false);
    addEditActionFrame->dispose();
    addEditActionFrame = NULL;
}

/*private*/ void TransitTableAction::updateActionPressed(ActionEvent* /*e*/) {
    if ((!validateWhenData()) || (!validateWhatData())) {
        return;
    }
    // entered data is OK, update the current special action
    curTSA->setWhenCode(tWhen);
    curTSA->setWhatCode(tWhat);
    curTSA->setDataWhen(tWhenData);
    curTSA->setDataWhat1(tWhatData1);
    curTSA->setDataWhat2(tWhatData2);
    curTSA->setStringWhen(tWhenString);
    curTSA->setStringWhat(tWhatString);
    actionTableModel->fireTableDataChanged();
    addEditActionFrame->setVisible(false);
    addEditActionFrame->dispose();
    addEditActionFrame = NULL;
}

/*private*/ void TransitTableAction::cancelAddEditActionPressed(ActionEvent* /*e*/) {
    addEditActionFrame->setVisible(false);
    addEditActionFrame->dispose();  // remove from Window menu
    addEditActionFrame = NULL;
}

/*private*/ bool TransitTableAction::validateWhenData() {
    tWhen = whenBox->currentIndex() + 1;
    QString s = whenDataField->text();
    tWhenData = 0;
    if ((s != NULL) && (s != (""))) {
        bool bOk;
            tWhenData = s.toInt(&bOk);
        if(!bOk) {
//            JOptionPane.showMessageDialog(addEditActionFrame, (tr("DelayError") + "\n" + e),
//                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error in Optional Delay entry -"));

            log->error("Exception when parsing Field: " /*+ e*/);
            return false;
        }
        if ((tWhenData < 0) || (tWhenData > 65500)) {
//            JOptionPane.showMessageDialog(addEditActionFrame, (tr("DelayRangeError")),
//                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Entered Optional Delay is not within the allowed 1 - 65500 millisecond range."));
            return false;
        }
    }
    tWhenString = "";
    if ((tWhen == TransitSectionAction::SENSORACTIVE) || (tWhen == TransitSectionAction::SENSORINACTIVE)) {
        tWhenString = whenStringField->text();
        if (!validateSensor(tWhenString, true)) {
            return false;
        }
    }
    if ((tWhen == TransitSectionAction::BLOCKENTRY) || (tWhen == TransitSectionAction::BLOCKEXIT)) {
        tWhenString = blockList.at(blockBox->currentIndex())->getSystemName();
    }
    return true;
}

/*private*/ bool TransitTableAction::validateSensor(QString sName, bool when) {
    // check if anything entered
    if (sName.length() < 1) {
        // no sensor entered
//        JOptionPane.showMessageDialog(addEditActionFrame, (tr("NoSensorError")),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error - no Sensor name was entered."));

        return false;
    }
    // get the sensor corresponding to this name
    Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(sName);
    if (s == NULL) {
        // There is no sensor corresponding to this name
//        JOptionPane.showMessageDialog(addEditActionFrame, (tr("SensorEntryError")),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Entered Sensor name does not correspond to a Sensor in the Sensor Table."));

        return false;
    }
    if (sName != (s->getUserName())) {
        if (when) {
            tWhenString = sName.toUpper();
        } else {
            tWhatString = sName.toUpper();
        }
    }
    return true;
}

/*private*/ bool TransitTableAction::validateWhatData() {
    tWhat = whatBox->currentIndex() + 1;
    tWhatData1 = 0;
    tWhatData2 = 0;
    tWhatString = "";
    switch (tWhat) {
        case TransitSectionAction::PAUSE:
            if (!readWhatData1(tr("PauseTime"), 1, 65500)) {
                return false;
            }
            break;
        case TransitSectionAction::SETMAXSPEED:
        case TransitSectionAction::SETCURRENTSPEED:
            if (!readWhatData1(tr("SpeedPercentage"), 1, 99)) {
                return false;
            }
            break;
        case TransitSectionAction::RAMPTRAINSPEED:
            if (!readWhatData1(tr("SpeedPercentage"), 1, 99)) {
                return false;
            }
            break;
        case TransitSectionAction::TOMANUALMODE:
            tWhatString = doneSensorField->text();
            if (tWhatString.length() >= 1) {
                if (!validateSensor(tWhatString, false)) {
                    tWhatString = "";
                }
            }
            break;
        case TransitSectionAction::SETLIGHT:
            tWhatString = "On";
            if (offButton->isChecked()) {
                tWhatString = "Off";
            }
            break;
        case TransitSectionAction::STARTBELL:
        case TransitSectionAction::STOPBELL:
            break;
        case TransitSectionAction::SOUNDHORN:
            if (!readWhatData1(tr("HornBlastLength"), 100, 65500)) {
                return false;
            }
            break;
        case TransitSectionAction::SOUNDHORNPATTERN:
            if (!readWhatData1(tr("ShortBlastLength"), 100, 65500)) {
                return false;
            }
            if (!readWhatData2(tr("LongBlastLength"), 100, 65500)) {
                return false;
            }
            tWhatString = whatStringField->text();
            if ((tWhatString == NULL) || tWhatString == "" || (tWhatString.length() < 1)) {
//                JOptionPane.showMessageDialog(addEditActionFrame, (tr("MissingPattern")),
//                        tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
                QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error - pattern for horn sounding was not entered."));

                return false;
            }
            tWhatString = tWhatString.toLower();
            for (int i = 0; i < tWhatString.length(); i++) {
                QChar c = tWhatString.at(i);
                if ((c != 's') && (c != 'l')) {
//                    JOptionPane.showMessageDialog(addEditActionFrame, (tr("ErrorPattern")),
//                            tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
                    QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error - bad character in horn pattern. Only \"s\" and \"l\" are allowed."));
                    return false;
                }
            }
            whatStringField->setText(tWhatString);
            break;
        case TransitSectionAction::LOCOFUNCTION:
            if (!readWhatData1(tr("Function Number"), 0, 28)) {
                return false;
            }
            tWhatString = "On";
            if (offButton->isChecked()) {
                tWhatString = "Off";
            }
            break;
        case TransitSectionAction::SETSENSORACTIVE:
        case TransitSectionAction::SETSENSORINACTIVE:
            tWhatString = whatStringField->text();
            if (!validateSensor(tWhatString, false)) {
                return false;
            }
            break;
    }
    return true;
}

/*private*/ bool TransitTableAction::readWhatData1(QString err, int min, int max) {
    QString s = whatData1Field->text();
    if ((s == NULL) || (s == (""))) {
//        JOptionPane.showMessageDialog(addEditActionFrame,
//                java.text.MessageFormat.format(tr("MissingEntryError"),
//                        new Object[]{err}),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error - the required \"%1\" entry was not found.").arg(err));

        return false;
    }
    bool bOk;
        tWhatData1 = s.toInt(&bOk);
    if(!bOk) {
//        JOptionPane.showMessageDialog(addEditActionFrame,
//                java.text.MessageFormat.format(tr("EntryError") + e,
//                        new Object[]{err}),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error in \"%1\" entry -").arg(err));

        log->error("Exception when parsing " + err + " Field: " /*+ e*/);
        return false;
    }
    if ((tWhatData1 < min) || (tWhatData1 > max)) {
//        JOptionPane.showMessageDialog(addEditActionFrame,
//                java.text.MessageFormat.format(tr("EntryRangeError"),
//                        new Object[]{err, "" + min, "" + max}),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("\"%1\" entry is not in the allowed range of \"%2\" through \"%3\"").arg(err).arg(min).arg(max));

        return false;
    }
    return true;
}

/*private*/ bool TransitTableAction::readWhatData2(QString err, int min, int max) {
    QString s = whatData2Field->text();
    if ((s == NULL) || (s == (""))) {
//        JOptionPane.showMessageDialog(addEditActionFrame,
//                java.text.MessageFormat.format(tr("MissingEntryError"),
//                        new Object[]{err}),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error - the required \"%1\" entry was not found.").arg(err));
        return false;
    }
    bool bOk;
        tWhatData2 = s.toInt(&bOk);
    if(!bOk) {
//        JOptionPane.showMessageDialog(addEditActionFrame,
//                java.text.MessageFormat.format(tr("EntryError") + e,
//                        new Object[]{err}),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("Error in \"%1\" entry -").arg(err));

        log->error("Exception when parsing " + err + " Field: " /*+ e*/);
        return false;
    }
    if ((tWhatData2 < min) || (tWhatData2 > max)) {
//        JOptionPane.showMessageDialog(addEditActionFrame,
//                java.text.MessageFormat.format(tr("EntryRangeError"),
//                        new Object[]{err, "" + min, "" + max}),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(addEditActionFrame, tr("Error"), tr("\"%1\" entry is not in the allowed range of \"%2\" through \"%3\""));

        return false;
    }
    return true;
}

// initialize combos for add/edit action window
/*private*/ void TransitTableAction::initializeWhenBox() {
    whenBox->clear();
    for (int i = 1; i <= TransitSectionAction::NUM_WHENS; i++) {
        whenBox->addItem(getWhenMenuText(i));
    }
}

/*private*/ QString TransitTableAction::getWhenMenuText(int i) {
    switch (i) {
        case TransitSectionAction::ENTRY:
            return tr("On Entry");
        case TransitSectionAction::EXIT:
            return tr("On Exit");
        case TransitSectionAction::BLOCKENTRY:
            return tr("On Block Entry");
        case TransitSectionAction::BLOCKEXIT:
            return tr("On Block Exit");
        case TransitSectionAction::TRAINSTOP:
            return tr("Train Stop");
        case TransitSectionAction::TRAINSTART:
            return tr("Train Start");
        case TransitSectionAction::SENSORACTIVE:
            return tr("On Sensor Active");
        case TransitSectionAction::SENSORINACTIVE:
            return tr("On Sensor Inactive");
    }
    return "WHEN";
}

/*private*/ void TransitTableAction::initializeWhatBox() {
    whatBox->clear();
    for (int i = 1; i <= TransitSectionAction::NUM_WHATS; i++) {
        whatBox->addItem(getWhatMenuText(i));
    }
}

/*private*/ QString TransitTableAction::getWhatMenuText(int i) {
    switch (i) {
        case TransitSectionAction::PAUSE:
            return tr("Pause");
        case TransitSectionAction::SETMAXSPEED:
            return tr("Set Max Speed");
        case TransitSectionAction::SETCURRENTSPEED:
            return tr("Set Train Speed");
        case TransitSectionAction::RAMPTRAINSPEED:
            return tr("Ramp Train Speed");
        case TransitSectionAction::TOMANUALMODE:
            return tr("To Manual Mode");
        case TransitSectionAction::SETLIGHT:
            return tr("Set Light");
        case TransitSectionAction::STARTBELL:
            return tr("Start Bell");
        case TransitSectionAction::STOPBELL:
            return tr("Stop Bell");
        case TransitSectionAction::SOUNDHORN:
            return tr("Sound Horn");
        case TransitSectionAction::SOUNDHORNPATTERN:
            return tr("Sound Horn Pattern");
        case TransitSectionAction::LOCOFUNCTION:
            return tr("Loco Function");
        case TransitSectionAction::SETSENSORACTIVE:
            return tr("Set Sensor Active");
        case TransitSectionAction::SETSENSORINACTIVE:
            return tr("Set Sensor Inactive");
    }
    return "WHAT";
}

/*private*/ void TransitTableAction::initializeBlockBox() {
    blockList = sectionList->at(activeRow)->getBlockList()->toList();
    blockBox->clear();
    for (int i = 0; i < blockList.size(); i++) {
        QString s = blockList.at(i)->getSystemName();
        if ((blockList.at(i)->getUserName() != NULL) && (blockList.at(i)->getUserName() != (""))) {
            s = s + "(" + blockList.at(i)->getUserName() + ")";
        }
        blockBox->addItem(s);
    }
}

/*private*/ void TransitTableAction::setBlockBox() {
    if (editActionMode) {
        if ((curTSA->getWhenCode() == TransitSectionAction::BLOCKENTRY)
                || (curTSA->getWhenCode() == TransitSectionAction::BLOCKEXIT)) {
            // assumes that initializeBlockBox has been called prior to this call
            for (int i = 0; i < blockList.size(); i++) {
                if (curTSA->getStringWhen() == (blockList.at(i)->getSystemName())) {
                    blockBox->setCurrentIndex(i);
                    return;
                }
            }
        }
    }
    blockBox->setCurrentIndex(0);
}

/*private*/ void TransitTableAction::editAction(int r) {
    curTSA = action.at(activeRow)->at(r);
    editActionMode = true;
    addEditActionWindow();
}

/*private*/ void TransitTableAction::deleteAction(int r) {
    TransitSectionAction* tsa = action.at(activeRow)->at(r);
    action.at(activeRow)->removeAt(r);
    tsa->dispose();
    actionTableModel->fireTableDataChanged();
}

/*
 * Notes: For the following, r = row in the Special Actions table.
 *        A TransitSectionAction must be available for this row.
 */

/*private*/ QString TransitTableAction::getWhenText(int r)
{
    TransitSectionAction* tsa = action.at(activeRow)->at(r);
    switch (tsa->getWhenCode()) {
        case TransitSectionAction::ENTRY:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("OnEntryDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen()});
             return tr("\"%1\" ms. after entering this Section").arg(tsa->getDataWhen());
            }
            return tr("OnEntryFull");
        case TransitSectionAction::EXIT:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("OnExitDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen()});
            return tr("\"%1\" ms. after exiting this Section").arg(tsa->getDataWhen());
            }
            return tr("OnExitFull");
        case TransitSectionAction::BLOCKENTRY:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("OnBlockEntryDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen(), tsa.getStringWhen()});
             return tr("\"%1\" ms. after entering Block \"%2\"").arg(tsa->getDataWhen()).arg(tsa->getStringWhen());
            }
//            return java.text.MessageFormat.format(tr("OnBlockEntryFull"),
//                    new Object[]{tsa.getStringWhen()});
            return tr("On Entry to Block \"%1\"").arg(tsa->getStringWhen());
        case TransitSectionAction::BLOCKEXIT:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("OnBlockExitDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen(), tsa.getStringWhen()});
             return tr("\"%1\" ms. after exiting Block \"%2\"").arg(tsa->getDataWhen()).arg(tsa->getStringWhen());
            }
//            return java.text.MessageFormat.format(tr("OnBlockExitFull"),
//                    new Object[]{tsa.getStringWhen()});
            return tr("On Exit from Block \"%1\"").arg(tsa->getStringWhen());
        case TransitSectionAction::TRAINSTOP:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("TrainStopDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen()});
            return tr("\"&1\" ms. after train stops moving").arg(tsa->getDataWhen());
            }
            return tr("When train stops moving");
        case TransitSectionAction::TRAINSTART:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("TrainStartDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen()});
            return tr("\"%1\" ms. after train starts moving").arg(tsa->getDataWhen());
            }
            return tr("When train starts moving");
        case TransitSectionAction::SENSORACTIVE:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("OnSensorActiveDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen(), tsa.getStringWhen()});
            return tr("\"%1\" ms. after Sensor \"%2\" becomes ACTIVE").arg(tsa->getStringWhen());
            }
//            return java.text.MessageFormat.format(tr("OnSensorActiveFull"),
//                    new Object[]{tsa.getStringWhen()});
            return tr("When Sensor \"%1\" becomes ACTIVE").arg(tsa->getStringWhen());
        case TransitSectionAction::SENSORINACTIVE:
            if (tsa->getDataWhen() > 0) {
//                return java.text.MessageFormat.format(tr("OnSensorInactiveDelayedFull"),
//                        new Object[]{"" + tsa.getDataWhen(), tsa.getStringWhen()});
            return tr("\"%1\" ms. after Sensor \"%2\" becomes INACTIVE").arg(tsa->getDataWhen()).arg(tsa->getStringWhen());

            }
//            return java.text.MessageFormat.format(tr("OnSensorInactiveFull"),
//                    new Object[]{tsa.getStringWhen()});
            return tr("When Sensor \"%1\" becomes INACTIVE").arg(tsa->getStringWhen());
    }
    return "WHEN";
}
/*
 * Notes: For the following, r = row in the Special Actions table.
 *        A TransitSectionAction must be available for this row.
 */

/*private*/ QString TransitTableAction::getWhatText(int r) {
    TransitSectionAction* tsa = action.at(activeRow)->at(r);
    switch (tsa->getWhatCode())
    {
        case TransitSectionAction::PAUSE:
//            return java.text.MessageFormat.format(tr("PauseFull"),
//                    new Object[]{tsa.getDataWhat1()});
         return tr("").arg(tsa->getDataWhat1());
        case TransitSectionAction::SETMAXSPEED:
//            return java.text.MessageFormat.format(tr("SetMaxSpeedFull"),
//                    new Object[]{tsa.getDataWhat1()});
         return tr("Set maximum train speed to \"%1\" percent").arg(tsa->getDataWhat1());
//        case TransitSectionAction::SETCURRENTSPEED:
//            return java.text.MessageFormat.format(tr("SetTrainSpeedFull"),
//                    new Object[]{tsa.getDataWhat1()});
            tr("Set train speed to \"%1\" percent").arg(tsa->getDataWhat1());
        case TransitSectionAction::RAMPTRAINSPEED:
//            return java.text.MessageFormat.format(tr("RampTrainSpeedFull"),
//                    new Object[]{"" + tsa.getDataWhat1()});
            tr("Ramp speed to \"%1\" percent.").arg(tsa->getDataWhat1());
        case TransitSectionAction::TOMANUALMODE:
            if (tsa->getStringWhat().length() > 0) {
//                return java.text.MessageFormat.format(tr("ToManualModeAltFull"),
//                        new Object[]{tsa.getStringWhat()});
            return tr("Change to manual throttle. Done Sensor \"%1\"").arg(tsa->getStringWhat());
            }
            return tr("ToManualModeFull");
        case TransitSectionAction::SETLIGHT:
//            return java.text.MessageFormat.format(tr("SetLightFull"),
//                    new Object[]{tr(tsa.getStringWhat())});
            return tr("Set locomotive light \"%1\"").arg(tsa->getStringWhat());
        case TransitSectionAction::STARTBELL:
            return tr("Start bell (if sound decoder)");
        case TransitSectionAction::STOPBELL:
            return tr("Stop bell (if sound decoder)");
        case TransitSectionAction::SOUNDHORN:
            //return java.text.MessageFormat.format(tr("SoundHornFull"),
//                    new Object[]{tsa.getDataWhat1()});
         return tr("Sound horn for \"%1\" ms.").arg(tsa->getDataWhat1());
        case TransitSectionAction::SOUNDHORNPATTERN:
//            return java.text.MessageFormat.format(tr("SoundHornPatternFull"),
//                    new Object[]{tsa.getStringWhat(), "" + tsa.getDataWhat1(), "" + tsa.getDataWhat2()});
            return tr("Sound horn pattern \"%1\", s %2").arg(tsa->getStringWhat()).arg(tsa->getDataWhat1());
        case TransitSectionAction::LOCOFUNCTION:
//            return java.text.MessageFormat.format(tr("LocoFunctionFull"),
//                    new Object[]{"" + tsa.getDataWhat1(), tr(tsa.getStringWhat())});
         return tr("").arg(tsa->getDataWhat1()).arg(tsa->getStringWhat());
        case TransitSectionAction::SETSENSORACTIVE:
//            return java.text.MessageFormat.format(tr("SetSensorActiveFull"),
//                    new Object[]{tsa.getStringWhat()});
         return tr("Set Sensor \"%1\" to ACTIVE").arg(tsa->getStringWhat());
        case TransitSectionAction::SETSENSORINACTIVE:
//            return java.text.MessageFormat.format(tr("SetSensorInactiveFull"),
//                    new Object[]{tsa.getStringWhat()});
      return tr("Set Sensor \"%1\" to INACTIVE").arg(tsa->getStringWhat());
    }
    return "WHAT";
}

/*private*/ QString TransitTableAction::getSectionNameByRow(int r) {
    QString s = sectionList->at(r)->getSystemName();
    QString u = sectionList->at(r)->getUserName();
    if ((u != NULL) && (u != (""))) {
        return (s + "( " + u + " )");
    }
    return s;
}

/**
 * Table model for Sections in Create/Edit Transit window
 */

/*public*/ SectionTableModel::SectionTableModel(TransitTableAction* act)
{
    //super();
    this->act = act;
    //sectionManager.addPropertyChangeListener(this);
    connect(act->sectionManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void SectionTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName() == ("length")) {
        // a new NamedBean is available in the manager
        fireTableDataChanged();
    }
}

///*public*/ Class<?> getColumnClass(int c) {
//    if (c == ACTION_COLUMN) {
//        return JButton.class;
//    }
//    return String.class;
//}

/*public*/ int SectionTableModel::columnCount(const QModelIndex &parent) const
{
    return ALTERNATE_COLUMN + 1;
}

/*public*/ int SectionTableModel::rowCount(const QModelIndex &parent) const
{
    return (act->sectionList->size());
}

/*public*/ Qt::ItemFlags SectionTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == ACTION_COLUMN) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    return Qt::ItemIsEnabled;
}

/*public*/ QVariant SectionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case SEQUENCE_COLUMN:
            return tr("Sequence");
        case SECTIONNAME_COLUMN:
            return tr("Section Name");
        case ACTION_COLUMN:
            return tr("Action ");
        case SEC_DIRECTION_COLUMN:
            return tr("Direction");
        case ALTERNATE_COLUMN:
            return tr("Alternate");
        default:
            break;
    }
 }
 return QVariant();
}

/*public*/ int SectionTableModel::getPreferredWidth(int col) {
    switch (col) {
        case SEQUENCE_COLUMN:
            return  JTextField(8).sizeHint().width();
        case SECTIONNAME_COLUMN:
            return JTextField(17).sizeHint().width();
        case ACTION_COLUMN:
            return  JTextField(12).sizeHint().width();
        case SEC_DIRECTION_COLUMN:
            return JTextField(12).sizeHint().width();
        case ALTERNATE_COLUMN:
            return  JTextField(12).sizeHint().width();
    }
    return  JTextField(5).sizeHint().width();
}

/*public*/ QVariant SectionTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
    int rx = index.row();
    if (rx > act->sectionList->size()) {
        return QVariant();
    }
    switch (index.column()) {
        case SEQUENCE_COLUMN:
            return ("" + act->sequence->at(rx));
        case SECTIONNAME_COLUMN:
            return act->getSectionNameByRow(rx);
        case ACTION_COLUMN:
            return tr("Add Edit Actions");
        case SEC_DIRECTION_COLUMN:
            if (act->direction->at(rx) ==  Section::FORWARD) {
                return tr("Forward");
            } else if (act->direction->at(rx) ==  Section::REVERSE) {
                return tr("Reverse");
            }
            return tr("Unknown");
        case ALTERNATE_COLUMN:
            if (act->alternate->at(rx)) {
                return tr("Alternate");
            }
            return tr("Primary");
        default:
            return tr("Unknown");
    }
 }
 return QVariant();
}

/*public*/ bool SectionTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if(role == Qt::EditRole)
  {
      int col = index.column();
      int row = index.row();
    if (col == ACTION_COLUMN) {
        act->addEditActionsPressed(row);
    }
    return true;
  }
  return false;
}


/**
 * Table model for Actions in Special Actions window
 */
///*public*/ class SpecialActionTableModel extends javax.swing.table.AbstractTableModel implements
//        java.beans.PropertyChangeListener {


/*public*/ SpecialActionTableModel::SpecialActionTableModel(TransitTableAction* act)  : AbstractTableModel()
{
    //super();
 this->act = act;
 //sectionManager.addPropertyChangeListener(this);
 connect(this->act->sectionManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void SpecialActionTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName() == ("length")) {
        // a new NamedBean is available in the manager
        fireTableDataChanged();
    }
}

///*public*/ Class<?> getColumnClass(int c) {
//    if (c == WHEN_COLUMN) {
//        return String.class;
//    }
//    if (c == WHAT_COLUMN) {
//        return String.class;
//    }
//    if (c == EDIT_COLUMN) {
//        return JButton.class;
//    }
//    if (c == REMOVE_COLUMN) {
//        return JButton.class;
//    }
//    return String.class;
//}

/*public*/ int SpecialActionTableModel::columnCount(const QModelIndex &parent) const
{
    return REMOVE_COLUMN + 1;
}

/*public*/ int SpecialActionTableModel::rowCount(const QModelIndex &parent) const
{
    return (act->action.at(act->activeRow)->size());
}

/*public*/ Qt::ItemFlags SpecialActionTableModel::flags(const QModelIndex &index) const
{
 int c = index.column();
    if (c == WHEN_COLUMN) {
        return Qt::ItemIsEnabled;
    }
    if (c == WHAT_COLUMN) {
        return Qt::ItemIsEnabled;
    }
    if (c == EDIT_COLUMN) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    if (c == REMOVE_COLUMN) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

/*public*/ QVariant SpecialActionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
    if (col == WHEN_COLUMN) {
        return tr("When");
    } else if (col == WHAT_COLUMN) {
        return tr("What");
    }
 }
 return QVariant();
}

/*public*/ int SpecialActionTableModel::getPreferredWidth(int col) {
    switch (col) {
        case WHEN_COLUMN:
            return  JTextField(50).sizeHint().width();
        case WHAT_COLUMN:
            return  JTextField(50).sizeHint().width();
        case EDIT_COLUMN:
            return  JTextField(8).sizeHint().width();
        case REMOVE_COLUMN:
            return  JTextField(8).sizeHint().width();
    }
    return  JTextField(8).sizeHint().width();
}

/*public*/ QVariant SpecialActionTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
    int rx = index.row();
    int c = index.column();
    if (rx > act->sectionList->size()) {
        return QVariant();
    }
    switch (c) {
        case WHEN_COLUMN:
            return (act->getWhenText(rx));
        case WHAT_COLUMN:
            return (act->getWhatText(rx));
        case EDIT_COLUMN:
            return tr("ButtonEdit");
        case REMOVE_COLUMN:
            return tr("ButtonDelete");
        default:
            break;
    }
  }
  return QVariant();
}

/*public*/ bool SpecialActionTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int col = index.column();
  int row = index.row();
    if (col == EDIT_COLUMN) {
        // set up to edit
        act->editAction(row);
    }
    if (col == REMOVE_COLUMN) {
        act->deleteAction(row);
    }
  return true;
 }
 return false;
}


/*protected*/ QString TransitTableAction::getClassName() {
    return "jmri.jmrit.beantable.TransitTableAction";
}

/*public*/ QString TransitTableAction::getClassDescription() {
    return tr("Transit Table");
}

