#include "paneprogpane.h"
#include "panecontainer.h"
#include "variablevalue.h"
#include "cvvalue.h"
#include "gridbagconstraints.h"
#include "variabletablemodel.h"
#include "propertychangesupport.h"
#include "dccaddresspanel.h"
#include "gridbaglayout.h"
#include "watchinglabel.h"
#include "jtable.h"
#include "fnmappanel.h"
#include "paneprogframe.h"
#include "panecontainer.h"
#include "variablevalue.h"
#include <QSortFilterProxyModel>
#include "../../LayoutEditor/jseparator.h"
#include "field.h"
#include "rosterentry.h"
#include "qualifier.h"
#include "jcomponentqualifier.h"
#include "hardcopywriter.h"
#include <QProgressBar>
#include <QVector>
#include "jlabel.h"
#include <QFont>
#include "slotmanager.h"
#include "jpanel.h"
#include <QTimer>
#include "box.h"
#include "loggerfactory.h"
#include "cvutil.h"
#include "stringutil.h"
#include <QHeaderView>
#include "jslider.h"
#include "jtextfield.h"
class Attribute
{
 public:
  Attribute(QString name, QString value)
  {
   this->name = name;
   this->value = value;
  }

  QString name;
  QString value;
};

class GridGlobals
{
public:
 GridGlobals()
 {
  gridxCurrent = -1;
  gridyCurrent = -1;
 }

 /*public*/ int gridxCurrent = -1;
 /*public*/ int gridyCurrent = -1;
 /*public*/ QVector<Attribute*> gridAttList;
 /*public*/ GridBagConstraints* gridConstraints;
};

/*static*/ /*final*/ QString PaneProgPane::LAST_GRIDX = "last_gridx";
/*static*/ /*final*/ QString PaneProgPane::LAST_GRIDY = "last_gridy";

class PaneProgFrame;

PaneProgPane::PaneProgPane(QWidget *parent) :
    JPanel(parent)
{
 common();
}
/**
 * Provides the individual panes for the TabbedPaneProgrammer.
 * Note that this is not only the panes carrying variables, but also the
 * special purpose panes for the CV table, etc.
 *<P>
 * This class implements PropertyChangeListener so that it can be notified
 * when a variable changes its busy status at the end of a programming read/write operation
 *
 * There are four read and write operation types, all of which have to be handled carefully:
 * <DL>
 * <DT>Write Changes<DD>This must write changes that occur after the operation
 *                      starts, because the act of writing a variable/CV may
 *                      change another.  For example, writing CV 1 will mark CV 29 as changed.
 *           <P>The definition of "changed" is operationally in the
 *              {@link jmri.jmrit.symbolicprog.VariableValue#isChanged} member function.
 *
 * <DT>Write All<DD>Like write changes, this might have to go back and re-write a variable
 *                  depending on what has previously happened.  It should write every
 *              variable (at least) once.
 * <DT>Read All<DD>This should read every variable once.
 * <DT>Read Changes<DD>This should read every variable that's marked as changed.
 *          Currently, we use a common definition of changed with the write operations,
 *      and that someday might have to change.
 *
 * </DL>
 *
 * @author    Bob Jacobsen   Copyright (C) 2001, 2003, 2004, 2005, 2006
 * @author    D Miller Copyright 2003
 * @author    Howard G. Penny   Copyright (C) 2005
 * @version   $Revision: 21951 $
 * @see       jmri.jmrit.symbolicprog.VariableValue#isChanged
 *
 */
// public class PaneProgPane extends javax.swing.JPanel
//    implements java.beans.PropertyChangeListener  {



/**
 * Create a NULL object.  Normally only used for tests and to pre-load classes.
 */
//    /*public*/ PaneProgPane() {}

/**
 * Construct the Pane from the XML definition element.
 *
 * @param name  Name to appear on tab of pane
 * @param pane  The JDOM QDomElement  for the pane definition
 * @param cvModel Already existing TableModel containing the CV definitions
 * @param icvModel Already existing TableModel containing the Indexed CV definitions
 * @param varModel Already existing TableModel containing the variable definitions
 * @param modelElem "model" element from the Decoder Index, used to check what decoder options are present.
 */
//@SuppressWarnings("unchecked")
/*public*/ PaneProgPane::PaneProgPane(PaneContainer* container, QString name, QDomElement  pane,
                                      CvTableModel* cvModel, VariableTableModel* varModel,
                                      QDomElement  modelElem, RosterEntry* rosterEntry,
                                      bool isProgPane, QWidget *parent) : JPanel(parent)
{
 common();
 this->container = container;
 mName = name;
 this->setObjectName(name);
 _cvModel = cvModel;
 //_indexedCvModel = icvModel;
 _varModel = varModel;
 this->rosterEntry = rosterEntry;
 this->isProgPane = isProgPane;
 this->pane = pane;
 this->modelElem = modelElem;
 //QTimer::singleShot(1,this,SLOT(ctorContinue()));
 ctorContinue();
}

void PaneProgPane::common()
{
 log->setDebugEnabled(true);

 readChangesButton  = new JToggleButton(tr("Read changes on sheet"));
 readChangesButton->setCheckable(true);
 readAllButton      = new JToggleButton(tr("Read full sheet"));
 readAllButton->setCheckable(true);
 writeChangesButton = new JToggleButton(tr("Write changes on sheet"));
 writeChangesButton->setCheckable(true);
 writeAllButton     = new JToggleButton(tr("Write full sheet"));
 writeAllButton->setCheckable(true);
 confirmChangesButton = new JToggleButton(tr("Compare changes on sheet"));
 confirmChangesButton->setCheckable(true);
 confirmAllButton     = new JToggleButton(tr("Compare full sheet"));
 confirmAllButton->setCheckable(true);

}
void PaneProgPane::ctorContinue() // continue ctor after subclasses are built.
{

 // when true a cv table with compare was loaded into pane
 _cvTable = false;

 // This is a JPanel containing a JScrollPane, containing a
 // laid-out JPanel
 //setLayout(new BoxLayout(this,BoxLayout.Y_AXIS));
 QVBoxLayout* vLayout1 = new QVBoxLayout(this);
 setLayout(vLayout1);
 vLayout1->setObjectName(QString::fromUtf8("vLayout1"));
 QScrollArea* scrollArea = new QScrollArea();
 //vLayout1->addWidget(scrollArea);
 scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
 scrollArea->setWidgetResizable(true);
 QWidget* scrollAreaWidgetContents = new QWidget();
 scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
 scrollAreaWidgetContents->setGeometry(QRect(0, 0, 758, 364));
 QVBoxLayout* vLayout2 = new QVBoxLayout(scrollAreaWidgetContents);
 vLayout2->setObjectName(QString::fromUtf8("vLayout2"));

 // find out whether to display "label" (false) or "item" (true)
 bool showItem = false;
 QString nameFmt = pane.attribute("nameFmt");
 if (!nameFmt.isNull() && nameFmt==("item"))
 {
  log->debug("Pane "+mName+" will show items, not labels, from decoder file");
  showItem = true;
 }
 // put the columns left to right in a panel
 //QWidget* p = new QWidget();
 panelList->append(scrollArea);
 //p.setLayout(new BoxLayout(p,BoxLayout.X_AXIS));
 QHBoxLayout* hLayout1 = new QHBoxLayout();
 hLayout1->setObjectName("hLayout1");

 // handle the xml definition
 // for all "column" elements ...
 QDomElement rowElem = QDomElement();
 QDomNodeList nodeList= pane.childNodes();
 for(int i=0; i<nodeList.size();i++)
 {
  QDomElement  elem = nodeList.at(i).toElement ();
  if(elem.tagName() == "column")
      hLayout1->addWidget(newColumn( elem, showItem, modelElem));
 }
 for(int i=0; i<nodeList.size();i++)
 {
  QDomElement  elem = nodeList.at(i).toElement ();
  if(elem.tagName() == "row"){
      hLayout1->addWidget(newRow( elem, showItem, modelElem));
      rowElem = elem;
  }
 }
 // for all "grid" elements ...
 QDomNodeList gridList = pane.firstChildElement("row").elementsByTagName("grid");
 for (int i=0; i<gridList.size(); i++)
 {
  // load each grid
  hLayout1->addWidget(newGrid( ((gridList.at(i).toElement ())), showItem, modelElem));
 }

 // for all "group" elements ...
 QDomNodeList groupList = pane.elementsByTagName("group");
 for (int i=0; i<groupList.size(); i++)
 {
  // load each group
  hLayout1->addWidget(newGroup( ((groupList.at(i).toElement ())), showItem, modelElem));
 }

 // explain why pane is empty
 if (cvList->isEmpty() && varList->isEmpty() && isProgPane)
 {
     JPanel* pe = new JPanel();
     pe->setLayout(new QVBoxLayout());//pe, BoxLayout.Y_AXIS));
     int line = 1;
     while (line >= 0) {
      try {
       QString msg;// = SymbolicProgBundle.getMessage("TextTabEmptyExplain" + line);
       switch (line) {
       case 1:
        msg = tr("This tab is empty because there are no options in this category");
        break;
       case 2:
        msg = tr("or they are to be found on another tab.");
        break;
       case 3:
        msg = "";
        break;
       case 4:
        msg = tr("to hide empty tabs, uncheck Preferences -> Roster -> Programmer -> Show empty tabs.");
       default:
        throw MissingResourceException();
        break;
       }
       if (msg.isEmpty()) {
           msg = " ";
       }
       JLabel* l = new JLabel(msg);
       l->setAlignmentX(Qt::AlignHCenter);
       pe->layout()->addWidget(l);
       line++;
      }
      catch (MissingResourceException e) {  // deliberately runs until exception
          line = -1;
      }
  }
  layout()->addWidget(pe);
  panelList->append(pe);
  return;
 }

 // add glue to the right to allow resize - but this isn't working as expected? Alignment?
 layout()->addWidget(Box::createHorizontalGlue());

 vLayout2->addLayout(hLayout1);
 scrollArea->setWidget(scrollAreaWidgetContents);
 vLayout1->addWidget(scrollArea);

 // add buttons in a new panel
 bottom = new QFrame();
 //bottom->setFrameStyle(QFrame::Panel);
 //panelList->append(p);
//    bottom->setLayout(new BoxLayout(bottom, BoxLayout.X_AXIS));
 hLayout_bottom = new QHBoxLayout(bottom);
 hLayout_bottom->setObjectName("hLayoutBottom");
 bottom->setLayout(hLayout_bottom);

 // enable read buttons, if possible, and
 // set their tool tips
 enableReadButtons();
#if 0 // see connect (below)
    // add read button listeners
    readChangesButton.addItemListener(l1 = new ItemListener() {
        /*public*/ void itemStateChanged (ItemEvent e) {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                readChangesButton.setText(tr("ButtonStopReadChangesSheet"));
                if (container.isBusy() == false) {
                    prepReadPane(true);
                    prepGlassPane(readChangesButton);
                    container.getBusyGlassPane().setVisible(true);
                    readPaneChanges();
                }
            } else {
                stopProgramming();
                readChangesButton.setText(tr("ButtonReadChangesSheet"));
                if (container.isBusy()) {
                    readChangesButton.setEnabled(false);
                }
            }
        }
    });
#endif
    connect(readChangesButton, SIGNAL(toggled(bool)), this, SLOT(On_readChangesButton_clicked()));
#if 0
    readAllButton.addItemListener(l2 = new ItemListener() {
        /*public*/ void itemStateChanged (ItemEvent e) {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                readAllButton.setText(tr("ButtonStopReadSheet"));
                if (container.isBusy() == false) {
                    prepReadPane(false);
                    prepGlassPane(readAllButton);
                    container.getBusyGlassPane().setVisible(true);
                    readPaneAll();
                }
            } else {
                stopProgramming();
                readAllButton.setText(tr("ButtonReadFullSheet"));
                if (container.isBusy()) {
                    readAllButton.setEnabled(false);
                }
            }
        }
    });
#endif
 connect(readAllButton, SIGNAL(toggled(bool)), this, SLOT(On_readAllButton_clicked()));
 writeChangesButton->setToolTip(tr("Write highlighted values on this sheet to decoder"));
#if 0 // see below
    writeChangesButton.addItemListener(l3 = new ItemListener() {
        /*public*/ void itemStateChanged (ItemEvent e) {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                writeChangesButton.setText(tr("ButtonStopWriteChangesSheet"));
                if (container.isBusy() == false) {
                    prepWritePane(true);
                    prepGlassPane(writeChangesButton);
                    container.getBusyGlassPane().setVisible(true);
                    writePaneChanges();
                }
            } else {
                stopProgramming();
                writeChangesButton.setText(tr("ButtonWriteChangesSheet"));
                if (container.isBusy()) {
                    writeChangesButton.setEnabled(false);
                }
            }
        }
    });
#endif
    connect(writeChangesButton, SIGNAL(toggled(bool)), this, SLOT(On_writeChangesButton_clicked()));
 writeAllButton->setToolTip(tr("Write all values on this sheet to decoder"));
#if 0 // see below
    writeAllButton.addItemListener(l4 = new ItemListener() {
        /*public*/ void itemStateChanged (ItemEvent e) {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                writeAllButton.setText(tr("ButtonStopWriteSheet"));
                if (container.isBusy() == false) {
                    prepWritePane(false);
                    prepGlassPane(writeAllButton);
                    container.getBusyGlassPane().setVisible(true);
                    writePaneAll();
                }
            } else {
                stopProgramming();
                writeAllButton.setText(tr("ButtonWriteFullSheet"));
                if (container.isBusy()) {
                    writeAllButton.setEnabled(false);
                }
            }
        }
    });
#endif
    connect(writeAllButton, SIGNAL(toggled(bool)), this, SLOT(On_writeAllButton_clicked()));
 // enable confirm buttons, if possible, and
 // set their tool tips
 enableConfirmButtons();
#if 0
    // add confirm button listeners
    confirmChangesButton.addItemListener(l5 = new ItemListener() {
        /*public*/ void itemStateChanged (ItemEvent e) {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                confirmChangesButton.setText(tr("ButtonStopConfirmChangesSheet"));
                if (container.isBusy() == false) {
                    prepConfirmPane(true);
                    prepGlassPane(confirmChangesButton);
                    container.getBusyGlassPane().setVisible(true);
                    confirmPaneChanges();
                }
            } else {
                stopProgramming();
                confirmChangesButton.setText(tr("ButtonConfirmChangesSheet"));
                if (container.isBusy()) {
                    confirmChangesButton.setEnabled(false);
                }
            }
        }
    });
    confirmAllButton.addItemListener(l6 = new ItemListener() {
        /*public*/ void itemStateChanged (ItemEvent e) {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                confirmAllButton.setText(tr("ButtonStopConfirmSheet"));
                if (container.isBusy() == false) {
                    prepConfirmPane(false);
                    prepGlassPane(confirmAllButton);
                    container.getBusyGlassPane().setVisible(true);
                    confirmPaneAll();
                }
            } else {
                stopProgramming();
                confirmAllButton.setText(tr("ButtonConfirmFullSheet"));
                if (container.isBusy()) {
                    confirmAllButton.setEnabled(false);
                }
            }
        }
    });
#endif
 connect(confirmChangesButton, SIGNAL(clicked()), this, SLOT(On_confirmChangesButtonClicked()));
 connect(confirmAllButton, SIGNAL(clicked()), this, SLOT(On_confirmAllButtonClicked()));
        // Only add compare buttons to CV tables
 //bottom.add(readChangesButton);
 hLayout_bottom->addWidget(readChangesButton);
 readChangesButton->setVisible(true);
 //bottom.add(writeChangesButton);
 hLayout_bottom->addWidget(writeChangesButton);
 if (_cvTable)
  //bottom.add(confirmChangesButton);
  hLayout_bottom->addWidget(confirmChangesButton);
 //bottom.add(readAllButton);
 hLayout_bottom->addWidget(readAllButton);
 //bottom.add(writeAllButton);
 hLayout_bottom->addWidget(writeAllButton);
 if (_cvTable)
  //bottom.add(confirmAllButton);
  hLayout_bottom ->addWidget(confirmAllButton);
 // don't show buttons if no programmer at all
 if (_cvModel->getProgrammer()!= NULL)
        //add(bottom);
  vLayout1->addWidget(bottom);
}

/*public*/ QString PaneProgPane::getName() { return mName; }
/*public*/ QString PaneProgPane::toString() { return getName(); }

/**
 * Enable the read all and read changes button if possible.
 * This checks to make sure this is appropriate, given
 * the attached programmer's capability.
 */
void PaneProgPane::enableReadButtons()
{
 readChangesButton->setToolTip(tr("Read highlighted values on sheet."));
 readAllButton->setToolTip(tr("Read all values on this sheet from decoder. Warning: may take a long time!"));
 if (_cvModel->getProgrammer()!= NULL
        && !_cvModel->getProgrammer()->getCanRead())
 {
  // can't read, disable the buttons
  readChangesButton->setEnabled(false);
  readAllButton->setEnabled(false);
  // set tooltip to explain why
  readChangesButton->setToolTip(tr("Button disabled because configured command station can't read CVs"));
  readAllButton->setToolTip(tr("Button disabled because configured command station can't read CVs"));
 }
 else
 {
  readChangesButton->setEnabled(true);
  readChangesButton->setVisible(true);
  readAllButton->setEnabled(true);
 }
}

/**
 * Enable the compare all and compare changes button if possible.
 * This checks to make sure this is appropriate, given
 * the attached programmer's capability.
 */
void PaneProgPane::enableConfirmButtons()
{
 confirmChangesButton->setToolTip(tr("Compare highlighted values on this sheet with decoder. Warning: may take a long time!"));
 confirmAllButton->setToolTip(tr("Compare all values on this sheet with decoder. Warning: may take a long time!"));
 if (_cvModel->getProgrammer()!= NULL
        && !_cvModel->getProgrammer()->getCanRead())
 {
  // can't read, disable the buttons
  confirmChangesButton->setEnabled(false);
  confirmAllButton->setEnabled(false);
  // set tooltip to explain why
  confirmChangesButton->setToolTip(tr("Button disabled because configured command station can't read CVs"));
  confirmAllButton->setToolTip(tr("Button disabled because configured command station can't read CVs"));
 }
 else
 {
  confirmChangesButton->setEnabled(true);
  confirmAllButton->setEnabled(true);
 }
}

/**
 * Estimate the number of CVs that will be accessed when
 * reading or writing the contents of this pane.
 *
 * @param read true if counting for read, false for write
 * @param changes true if counting for a *Changes operation;
 *          false, if counting for a *All operation
 * @return the total number of CV reads/writes needed for this pane
 */

/*public*/ int PaneProgPane::countOpsNeeded(bool read, bool changes) {
    QSet<int>* set = new QSet<int>(/*cvList->size()+varList->size()+50*/);
    set->reserve(cvList->size()+varList->size()+50);
    return makeOpsNeededSet(read, changes, set)->size();
}

/**
 * Produce a set of CVs that will be accessed when
 * reading or writing the contents of this pane.
 *
 * @param read true if counting for read, false for write
 * @param changes true if counting for a *Changes operation;
 *          false, if counting for a *All operation
 * @param set The set to fill.  Any CVs already in here will
 *      not be duplicated, which provides a way to aggregate
 *      a set of CVs across multiple panes.
 * @return the same set as the parameter, for convenient
 *      chaining of operations.
 */
/*public*/ QSet<int>* PaneProgPane::makeOpsNeededSet(bool /*read*/, bool changes, QSet<int>* set)
{
 // scan the variable list
 for (int i =0; i<varList->size(); i++)
 {
  int varNum = varList->at(i);
  VariableValue* var = _varModel->getVariable( varNum );

  // must decide whether this one should be counted

  if ( !changes ||
                ( changes && var->isChanged()) )
  {
   QVector<CvValue*> cvs = var->usesCVs();
   for (int j = 0; j<cvs.count(); j++)
   {
    // always of interest
    CvValue* cv = cvs.at(j);
    if (!changes || VariableValue::considerChanged(cv))
    set->insert(cv->number().toInt());
   }
  }
 }
 return set;
}

/*private*/ void PaneProgPane::prepGlassPane(JToggleButton* activeButton)
{
 container->prepGlassPane(activeButton);
}

void PaneProgPane::enableButtons(bool stat)
{
 if (stat)
 {
  enableReadButtons();
  enableConfirmButtons();
 }
 else
 {
  readChangesButton->setEnabled(stat);
  readAllButton->setEnabled(stat);
  confirmChangesButton->setEnabled(stat);
  confirmAllButton->setEnabled(stat);
 }
 writeChangesButton->setEnabled(stat);
 writeAllButton->setEnabled(stat);
}


/**
 * Invoked by "Read changes on sheet" button, this sets in motion a
 * continuing sequence of "read" operations on the
 * variables & CVs in the Pane.  Only variables in states
 * marked as "changed" will be read.
 *
 * @return true is a read has been started, false if the pane is complete.
 */
/*public*/ bool PaneProgPane::readPaneChanges() {
    if (log->isDebugEnabled()) log->debug("readPane starts with "
                                        +QString::number(varList->size())+" vars, "
                                        +QString::number(cvList->size())+" cvs "
                                        );
    prepReadPane(true);
    return nextRead();
}

/**
 * Prepare this pane for a read operation.
 * <P>The read mechanism only reads
 * variables in certain states (and needs to do that to handle error
 * processing right now), so this is implemented by first
 * setting all variables and CVs on this pane to TOREAD via this method
 *
 */
/*public*/ void PaneProgPane::prepReadPane(bool onlyChanges)
{
 if (log->isDebugEnabled()) log->debug("start prepReadPane with onlyChanges="+QString(onlyChanges?"true":"false"));
 justChanges = onlyChanges;

 if (isCvTablePane) {
     setCvListFromTable();  // make sure list of CVs up to date if table
 }
 enableButtons(false);
 if (justChanges == true)
 {
  readChangesButton->setEnabled(true);
  readChangesButton->setSelected(true);
 }
 else
 {
  readAllButton->setSelected(true);
  readAllButton->setEnabled(true);
 }
 if (container->isBusy() == false)
 {
  container->enableButtons(false);
 }
 setToRead(justChanges, true);
 varListIndex = 0;
 cvListIndex = 0;
 indexedCvListIndex = 0;
}

/**
 * Invoked by "Read Full Sheet" button, this sets in motion a
 * continuing sequence of "read" operations on the
 * variables & CVs in the Pane.  The read mechanism only reads
 * variables in certain states (and needs to do that to handle error
 * processing right now), so this is implemented by first
 * setting all variables and CVs on this pane to TOREAD
 * in prepReadPaneAll, then starting the execution.
 *
 * @return true is a read has been started, false if the pane is complete.
 */
/*public*/ bool PaneProgPane::readPaneAll()
{
 if (log->isDebugEnabled()) log->debug("readAllPane starts with "
                                     +QString::number(varList->size())+" vars, "
                                     +QString::number(cvList->size())+" cvs ");
 prepReadPane(false);
 // start operation
 return nextRead();
}

/**
 * Set the "ToRead" parameter in all variables and CVs on this pane
 */
void PaneProgPane::setToRead(bool justChanges, bool startProcess)
{
 if (!(container->isBusy()) ||  // the frame has already setToRead
       (!startProcess))
 {  // we want to setToRead false if the pane's process is being stopped
  for (int i = 0; i < varList->size(); i++)
  {
   int varNum = varList->at(i);
   VariableValue* var = _varModel->getVariable(varNum);
   if (justChanges)
   {
    if (var->isChanged())
    {
     var->setToRead(startProcess);
    }
    else
    {
     var->setToRead(false);
    }
   }
   else
   {
    var->setToRead(startProcess);
   }
  }

  for (int i = 0; i < cvList->size(); i++)
  {
   int cvNum = cvList->at(i);
   CvValue* cv = _cvModel->getCvByRow(cvNum);
   if (justChanges)
   {
    if (VariableValue::considerChanged(cv))
    {
     cv->setToRead(startProcess);
    }
    else
    {
     cv->setToRead(false);
    }
   }
   else
   {
    cv->setToRead(startProcess);
   }
  }
 }
}

/**
 * Set the "ToWrite" parameter in all variables and CVs on this pane
 */
void PaneProgPane::setToWrite(bool justChanges, bool startProcess)
{
 if (log->isDebugEnabled())
  log->debug(QString("start setToWrite method with ")+(justChanges?"true":"false")+","+(startProcess?"true":"false"));
 if (!container->isBusy() ||  // the frame has already setToWrite
  (!startProcess))
 {  // we want to setToRead false if the pane's process is being stopped
  log->debug("about to start setToWrite of varList");
  for (int i = 0; i < varList->size(); i++)
  {
   int varNum = varList->at(i);
   VariableValue* var = _varModel->getVariable(varNum);
   if (justChanges)
   {
    if (var->isChanged())
    {
     var->setToWrite(startProcess);
    }
    else
    {
     var->setToWrite(false);
    }
   }
   else
   {
    var->setToWrite(startProcess);
   }
  }
  log->debug("about to start setToWrite of cvList");
  for (int i = 0; i < cvList->size(); i++)
  {
   int cvNum = cvList->at(i);
   CvValue* cv = _cvModel->getCvByRow(cvNum);
   if (justChanges)
   {
    if (VariableValue::considerChanged(cv))
    {
     cv->setToWrite(startProcess);
    }
    else
    {
     cv->setToWrite(false);
    }
   }
   else
   {
    cv->setToWrite(startProcess);
   }
  }
 }
 log->debug("end setToWrite method");
}

void PaneProgPane::executeRead(VariableValue* var)
{
 setBusy(true);
 // var->setToRead(false);  // variables set this themselves
 if (_programmingVar != NULL)
  log->error("listener already set at read start");
 _programmingVar = var;
 _read = true;
 // get notified when that state changes so can repeat
 _programmingVar->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(_programmingVar->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 // and make the read request
 if (justChanges)
 {
  _programmingVar->readChanges();
 }
 else
 {
  _programmingVar->readAll();
 }
}

void PaneProgPane::executeWrite(VariableValue* var)
{
 setBusy(true);
 // var->setToWrite(false);   // variables reset themselves when done
 if (_programmingVar != NULL) log->error("listener already set at write start");
 _programmingVar = var;
 _read = false;
 // get notified when that state changes so can repeat
 _programmingVar->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(_programmingVar->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 // and make the write request
 if (justChanges)
 {
  _programmingVar->writeChanges();
 }
 else
 {
  _programmingVar->writeAll();
 }
}

/**
 * If there are any more read operations to be done on this pane,
 * do the next one.
 * <P>
 * Each invocation of this method reads one variable or CV; completion
 * of that request will cause it to happen again, reading the next one, until
 * there's nothing left to read.
 * <P>
 * @return true is a read has been started, false if the pane is complete.
 */
bool PaneProgPane::nextRead()
{
 // look for possible variables
 if (log->isDebugEnabled()) {
     log->debug(tr("nextRead scans %1 variables").arg(varList->size()));
 }
 while ((varList->size() >= 0) && (varListIndex < varList->size()))
 {
  int varNum = varList->at(varListIndex);
  int vState = _varModel->getState( varNum );
  VariableValue* var = _varModel->getVariable(varNum);
  if (log->isDebugEnabled())
   log->debug("nextRead var index "+QString::number(varNum)+" state "+QString::number(vState)+"  label: "+var->label());
  varListIndex++;
  if (var->isToRead() || vState == VariableValue::UNKNOWN)
  {        // always read UNKNOWN state
   if (log->isDebugEnabled()) log->debug("start read of variable "+_varModel->getLabel(varNum));
   executeRead(var);

   if (log->isDebugEnabled()) log->debug("return from starting var read");
   // the request may have instantaneously been satisfied...
   return true;  // only make one request at a time!
  }
 }

 // found no variables needing read, try CVs
 while ((cvList->size() >= 0) && (cvListIndex < cvList->size()))
 {
  int cvNum = cvList->at(cvListIndex);
  CvValue* cv = _cvModel->getCvByRow(cvNum);
  if (log->isDebugEnabled())
   log->debug(tr("nextRead cv index %1 state %2").arg(cvNum).arg(cv->getState()));
  cvListIndex++;
  if (cv->isToRead() || cv->getState() == CvValue::UNKNOWN)
  {  // always read UNKNOWN state
   if (log->isDebugEnabled())
    log->debug("start read of cv "+cvNum);
   setBusy(true);
   if (_programmingCV != NULL)
    log->error("listener already set at read start");
   _programmingCV = _cvModel->getCvByRow(cvNum);
   _read = true;
   // get notified when that state changes so can repeat
   _programmingCV->addPropertyChangeListener((PropertyChangeListener*)this);
   connect(_programmingCV->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   // and make the read request
   // _programmingCV.setToRead(false);  // CVs set this themselves
   _programmingCV->read(_cvModel->getStatusLabel());
   if (log->isDebugEnabled())
    log->debug("return from starting CV read");
   // the request may have instantateously been satisfied...
   return true;  // only make one request at a time!
  }
 }

 // nothing to program, end politely
 if (log->isDebugEnabled()) log->debug("nextRead found nothing to do");
 readChangesButton->setSelected(false);
 readAllButton->setSelected(false);  // reset both, as that's final state we want
 setBusy(false);
 container->paneFinished();
 return false;
}

/**
 * If there are any more compare operations to be done on this pane,
 * do the next one.
 * <P>
 * Each invocation of this method compare one CV; completion
 * of that request will cause it to happen again, reading the next one, until
 * there's nothing left to read.
 * <P>
 * @return true is a compare has been started, false if the pane is complete.
 */
bool PaneProgPane::nextConfirm()
{
 // look for possible CVs
 while ((cvList->size() >= 0) && (cvListIndex < cvList->size()))
 {
  int cvNum = cvList->at(cvListIndex);
  CvValue* cv = _cvModel->getCvByRow(cvNum);
  if (log->isDebugEnabled()) log->debug("nextConfirm cv index "+QString::number(cvNum)+" state "+QString::number(cv->getState()));
  cvListIndex++;
  if (cv->isToRead())
  {
   if (log->isDebugEnabled()) log->debug("start confirm of cv "+QString::number(cvNum));
   setBusy(true);
   if (_programmingCV != NULL) log->error("listener already set at confirm start");
   _programmingCV = _cvModel->getCvByRow(cvNum);
   _read = true;
   // get notified when that state changes so can repeat
   _programmingCV->addPropertyChangeListener((PropertyChangeListener*)this);
   connect(_programmingCV, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   // and make the compare request
   _programmingCV->confirm(_cvModel->getStatusLabel());
   if (log->isDebugEnabled()) log->debug("return from starting CV confirm");
   // the request may have instantateously been satisfied...
   return true;  // only make one request at a time!
  }
 }

 // nothing to program, end politely
 if (log->isDebugEnabled()) log->debug("nextConfirm found nothing to do");
 confirmChangesButton->setSelected(false);
 confirmAllButton->setSelected(false);  // reset both, as that's final state we want
 setBusy(false);
 container->paneFinished();
 return false;
}

/**
 * Invoked by "Write changes on sheet" button, this sets in motion a
 * continuing sequence of "write" operations on the
 * variables in the Pane.  Only variables in isChanged states
 * are written; other states don't
 * need to be.
 * <P>
 * Returns true if a write has been started, false if the pane is complete.
 */
/*public*/ bool PaneProgPane::writePaneChanges()
{
 if (log->isDebugEnabled()) log->debug("writePaneChanges starts");
 prepWritePane(true);
 bool val = nextWrite();
 if (log->isDebugEnabled()) log->debug("writePaneChanges returns "+QString::number(val));
 return val;
}

/**
 * Invoked by "Write full sheet" button to write all CVs.
 * <P>
 * Returns true if a write has been started, false if the pane is complete.
 */
/*public*/ bool PaneProgPane::writePaneAll()
{
 prepWritePane(false);
 return nextWrite();
}

/**
 * Prepare a "write full sheet" operation.
 */
/*public*/ void PaneProgPane::prepWritePane(bool onlyChanges)
{

 if (log->isDebugEnabled()) log->debug("start prepWritePane with "+onlyChanges);
 justChanges = onlyChanges;
 enableButtons(false);
 if (justChanges == true)
 {
     writeChangesButton->setEnabled(true);
     writeChangesButton->setSelected(true);
 } else {
     writeAllButton->setSelected(true);
     writeAllButton->setEnabled(true);
 }
 if (container->isBusy() == false) {
     container->enableButtons(false);
 }
 setToWrite(justChanges, true);
 varListIndex = 0;
 cvListIndex = 0;
 indexedCvListIndex = 0;
 log->debug("end prepWritePane");
}

bool PaneProgPane::nextWrite()
{
 log->debug("start nextWrite");
 // look for possible variables
 while ((varList->size() >= 0) && (varListIndex < varList->size()))
 {
  int varNum = varList->at(varListIndex);
  int vState = _varModel->getState( varNum );
  VariableValue* var = _varModel->getVariable(varNum);
  if (log->isDebugEnabled()) log->debug("nextWrite var index "+QString::number(varNum)+" state "+VariableValue::stateNameFromValue(vState)
                                      +" isToWrite: "+(var->isToWrite()?"true":"false")+" label:"+var->label());
  varListIndex++;
  if (var->isToWrite() || vState == VariableValue::UNKNOWN)
  {
   log->debug("start write of variable "+_varModel->getLabel(varNum));

   executeWrite(var);

   if (log->isDebugEnabled()) log->debug("return from starting var write");
   return true;  // only make one request at a time!
  }
 }
 // check for CVs to handle (e.g. for CV table)
 while ((cvList->size() >= 0) && (cvListIndex < cvList->size()))
 {
  int cvNum = cvList->at(cvListIndex);
  CvValue* cv = _cvModel->getCvByRow( cvNum );
  if (log->isDebugEnabled()) log->debug("nextWrite cv index "+QString::number(cvNum)+" state "+QString::number(cv->getState()));
  cvListIndex++;
  if (cv->isToWrite() /*|| cv->getState()== CvValue::UNKNOWN*/)
  {
   if (log->isDebugEnabled())
    log->debug("start write of cv index "+cvNum);
   setBusy(true);
   if (_programmingCV != NULL)
    log->error("listener already set at write start");
   _programmingCV = _cvModel->getCvByRow(cvNum);
   _read = false;
   // get notified when that state changes so can repeat
   _programmingCV->addPropertyChangeListener((PropertyChangeListener*)this);
   connect(_programmingCV, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   // and make the write request
   // _programmingCV.setToWrite(false);  // CVs set this themselves
   _programmingCV->write(_cvModel->getStatusLabel());
   if (log->isDebugEnabled()) log->debug("return from starting cv write");
    return true;  // only make one request at a time!
  }
 }

 // nothing to program, end politely
 if (log->isDebugEnabled()) log->debug("nextWrite found nothing to do");
 writeChangesButton->setSelected(false);
 writeAllButton->setSelected(false);
 setBusy(false);
 ((PaneProgFrame*) container)->paneFinished();
 log->debug("return from nextWrite with nothing to do");
 return false;
}

/**
 * Prepare this pane for a compare operation.
 * <P>The read mechanism only reads
 * variables in certain states (and needs to do that to handle error
 * processing right now), so this is implemented by first
 * setting all variables and CVs on this pane to TOREAD via this method
 *
 */
/*public*/ void PaneProgPane::prepConfirmPane(bool onlyChanges)
{
 if (log->isDebugEnabled()) log->debug("start prepReadPane with onlyChanges="+QString(onlyChanges?"true":"false"));
 justChanges = onlyChanges;
 enableButtons(false);
 if (justChanges)
 {
  confirmChangesButton->setEnabled(true);
  confirmChangesButton->setSelected(true);
 }
 else
 {
  confirmAllButton->setSelected(true);
  confirmAllButton->setEnabled(true);
 }
 if (container->isBusy() == false)
 {
  container->enableButtons(false);
 }
 // we can use the read prep since confirm has to read first
 setToRead(justChanges, true);
 varListIndex = 0;
 cvListIndex = 0;
 indexedCvListIndex = 0;
}


/**
 * Invoked by "Compare changes on sheet" button, this sets in motion a
 * continuing sequence of "confirm" operations on the
 * variables & CVs in the Pane.  Only variables in states
 * marked as "changed" will be checked.
 *
 * @return true is a confirm has been started, false if the pane is complete.
 */
/*public*/ bool PaneProgPane::confirmPaneChanges()
{
 if (log->isDebugEnabled()) log->debug("confirmPane starts with "
                                        +QString::number(varList->size())+" vars, "
                                        +QString::number(cvList->size())+" cvs ");
  prepConfirmPane(true);
 return nextConfirm();
}

/**
 * Invoked by "Compare Full Sheet" button, this sets in motion a
 * continuing sequence of "confirm" operations on the
 * variables & CVs in the Pane.  The read mechanism only reads
 * variables in certain states (and needs to do that to handle error
 * processing right now), so this is implemented by first
 * setting all variables and CVs on this pane to TOREAD
 * in prepReadPaneAll, then starting the execution.
 *
 * @return true is a confirm has been started, false if the pane is complete.
 */
/*public*/ bool PaneProgPane::confirmPaneAll()
{
 if (log->isDebugEnabled()) log->debug("confirmAllPane starts with "
                                        +QString::number(varList->size())+" vars, "
                                        +QString::number(cvList->size())+" cvs " );
  prepConfirmPane(false);
 // start operation
 return nextConfirm();
}

/*public*/ bool PaneProgPane::isBusy() { return _busy; }

/*protected*/ void PaneProgPane::setBusy(bool busy)
{
 bool oldBusy = _busy;
 _busy = busy;
 if (!busy && !(container->isBusy()))
 {
  enableButtons(true);
 }
 if (oldBusy != busy)
  firePropertyChange("Busy",(oldBusy), (busy));
  //emit notifyPropertyChange(new PropertyChangeEvent(this,"Busy",(oldBusy), (busy) ));
}


/**
 * Get notification of a variable property change, specifically "busy" going to
 * false at the end of a programming operation. If we're in a programming
 * operation, we then continue it by reinvoking the nextRead/writePane operation.
 */
/*public*/ void PaneProgPane::propertyChange(PropertyChangeEvent* e)
{
 emit notifyPropertyChange(e);
 // check for the right event & condition
 if (_programmingVar == NULL && _programmingCV == NULL)
 {
  log->warn("unexpected propertyChange: "+e->getPropertyName());
  return;
 }
 else if (log->isDebugEnabled())
  log->debug("property changed: \""+e->getPropertyName()
                                               +"\" new value: "+e->getNewValue().toString());

 // find the right way to handle this
 if (e->getSource() == _programmingVar &&
        e->getPropertyName()==("Busy") &&
        (e->getNewValue().toBool())==(false) )
 {
  if (_programmingVar->getState() == VariableValue::UNKNOWN)
  {
   if (retry == 0)
   {
    varListIndex--;
    retry++;
   }
   else
   {
    retry = 0;
   }
  }
  replyWhileProgrammingVar();
  return;
 }
 else if (e->getSource() == _programmingCV &&
               e->getPropertyName()==("Busy") &&
               (e->getNewValue().toBool())==false )
 {
  if (_programmingCV->getState() == CvValue::UNKNOWN)
  {
   if (retry == 0)
   {
    cvListIndex--;
    retry++;
   }
   else
   {
    retry = 0;
   }
  }
  replyWhileProgrammingCV();
  return;
 }
 else
 {
  if (log->isDebugEnabled() && e->getPropertyName()==("Busy"))
   log->debug("ignoring change of Busy "+e->getNewValue().toString()
                      +" "+e->getNewValue().toString());
  return;
 }
}

/*public*/ void PaneProgPane::replyWhileProgrammingVar()
{
 if (log->isDebugEnabled()) log->debug("correct event for programming variable, restart operation");
 // remove existing listener
 _programmingVar->removePropertyChangeListener((PropertyChangeListener*)this);
 disconnect(_programmingVar->prop, SIGNAL(propertyChange(PropertyChangeEvent*)));
 _programmingVar = NULL;
 // restart the operation
 restartProgramming();
}

/*public*/ void PaneProgPane::replyWhileProgrammingCV()
{
 if (log->isDebugEnabled()) log->debug("correct event for programming CV, restart operation");
 // remove existing listener
 _programmingCV->removePropertyChangeListener((PropertyChangeListener*)this);
 disconnect(_programmingCV, SIGNAL(propertyChange(PropertyChangeEvent*)));
 _programmingCV = NULL;
 // restart the operation
 restartProgramming();
}

void PaneProgPane::restartProgramming()
{
 log->debug("start restartProgramming");
 if (_read && readChangesButton->isSelected()) nextRead();
 else if (_read && readAllButton->isSelected()) nextRead();
 else if (_read && confirmChangesButton->isSelected()) nextConfirm();
 else if (_read && confirmAllButton->isSelected()) nextConfirm();
 else if (writeChangesButton->isSelected()) nextWrite();   // was writePaneChanges
 else if (writeAllButton->isSelected()) nextWrite();
 else
 {
  if (log->isDebugEnabled()) log->debug("No operation to restart");
  if (isBusy())
  {
   container->paneFinished();
   setBusy(false);
  }
 }
 log->debug("end restartProgramming");
}

/*protected*/ void PaneProgPane::stopProgramming()
{
 log->debug("start stopProgramming");
 setToRead(false, false);
 setToWrite(false, false);
 varListIndex = varList->size();
 cvListIndex = cvList->size();
 if (isBusy())
 {
  container->paneFinished();
  setBusy(false);
 }
// ((SlotManager*)_programmingCV->mProgrammer)->removeSlotListener((SlotListener*)_programmingCV);

 log->debug("end stopProgramming");
}
/**
 * Create a new group from the JDOM group QDomElement
 */
/*protected*/ JPanel* PaneProgPane::newGroup(QDomElement  element, bool showStdName, QDomElement  modelElem)
{
 // create a panel to add as a new column or row
 /*final*/ JPanel* c = new JPanel();
 panelList->append(c);
 GridBagLayout* g = new GridBagLayout();
 GridBagConstraints* cs = new GridBagConstraints();
 c->setLayout(g);

 // handle include/exclude
 if ( !PaneProgFrame::isIncludedFE(element, modelElem, rosterEntry, "", "") )
 {
  return c;
 }

 // handle the xml definition
 // for all elements in the column or row
 QDomNodeList elemList = element.childNodes();
 if (log->isDebugEnabled()) log->debug("newColumn starting with "+QString::number(elemList.size())+" elements");
 for (int i=0; i<elemList.size(); i++)
 {
  QDomElement  e = (elemList.at(i).toElement());
  QString name = e.tagName();
  //log->trace("newGroup processing {} element",name);
  // decode the type
  if (name== ("display"))
  {// its a variable
   // load the variable
   newVariable( e, c, g, cs, showStdName);
  }
  else if (name== ("separator"))
  { // its a separator
   JSeparator* j = new JSeparator(JSeparator::HORIZONTAL);
   cs->fill = GridBagConstraints::BOTH;
   cs->gridwidth = GridBagConstraints::REMAINDER;
   //g.setConstraints(j, *cs);
   g->addWidget(j,*cs);
   cs->gridwidth = 1;
  }
  else if (name== ("label"))
  {
   cs->gridwidth = GridBagConstraints::REMAINDER;
   makeLabel(e, c, g, cs);
  }
  else if (name== ("soundlabel"))
  {
   cs->gridwidth = GridBagConstraints::REMAINDER;
   makeSoundLabel(e, c, g, cs);
  }
  else if (name== ("cvtable"))
  {
   makeCvTable(cs, g, c);
  }
  else if (name== ("fnmapping"))
  {
   pickFnMapPanel(c, g, cs, modelElem);
  }
  else if (name== ("dccaddress"))
  {
   QWidget* l = addDccAddressPanel(e);
   if (l->children().count() > 1)
   {
    cs->gridwidth = GridBagConstraints::REMAINDER;
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridwidth = 1;
   }
  }
  else if (name== ("column"))
  {
   // nested "column" elements ...
   cs->gridheight = GridBagConstraints::REMAINDER;
   QWidget* l = newColumn(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridheight = 1;
   }
  }
  else if (name== ("row"))
  {
   // nested "row" elements ...
   cs->gridwidth = GridBagConstraints::REMAINDER;
   QWidget* l = newRow(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridwidth = 1;
   }
  }
  else if (name== ("grid"))
  {
   // nested "grid" elements ...
   cs->gridwidth = GridBagConstraints::REMAINDER;
   QWidget* l = newGrid(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridwidth = 1;
   }
  }
  else if (name== ("group"))
  {
   // nested "group" elements ...
   QWidget* l = newGroup(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
   }
  }
  else if (name!= ("qualifier"))
  { // its a mistake
   log->error("No code to handle element of type "+e.tagName()+" in newColumn");
  }
 }
 // add glue to the bottom to allow resize
 if (c->children().count() > 1)
 {
  g->addWidget(Box::createVerticalGlue(), *cs);
 }
#if 0
 // handle qualification if any
 MyQualifierAdder* qa = new MyQualifierAdder(1, this);
// {
//       protected Qualifier createQualifier(VariableValue var, String relation, String value) {
//           return new JComponentQualifier(c, var, Integer.parseInt(value), relation);
//       }
//       protected void addListener(java.beans.PropertyChangeListener qc) {
//           c.addPropertyChangeListener(qc);
//       }
// };

 qa->processModifierElements(element, _varModel);
#endif
 return c;
}

/**
* Create a new grid group from the JDOM group QDomElement
*/
/*protected*/ void PaneProgPane::newGridGroup(QDomElement  element, /*final*/ JPanel *c, GridBagLayout *g, GridGlobals* globs, bool showStdName, QDomElement  modelElem)
{

 // handle include/exclude
 if ( !PaneProgFrame::isIncludedFE(element, modelElem, rosterEntry, "", "") )
 {
  return;
 }

 // handle the xml definition
 // for all elements in the column or row
 QDomNodeList elemList = element.childNodes();
 if (log->isDebugEnabled()) log->debug("newColumn starting with "+QString::number(elemList.size())+" elements");
 for (int i=0; i<elemList.size(); i++)
 {

  QDomElement  e = (elemList.at(i).toElement());
  QString name = e.tagName();
  //log->trace("newGroup processing {} element", name);
  // decode the type
  if (name== ("griditem"))
  {
   /*final*/ JPanel* l = newGridItem(e, showStdName, modelElem, globs);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, globs.gridConstraints);
    g->addWidget(l, *globs->gridConstraints);
//                     globs.gridConstraints.gridwidth = 1;
    // handle qualification if any
#if 0
    MyQualifierAdder* qa = new MyQualifierAdder(c, this);
//    {
//               protected Qualifier createQualifier(VariableValue var, String relation, String value) {
//                   return new JComponentQualifier(l, var, Integer.parseInt(value), relation);
//               }
//               protected void addListener(java.beans.PropertyChangeListener qc) {
//                   l.addPropertyChangeListener(qc);
//               }
//    };

    qa->processModifierElements(e, _varModel);
#endif
   }
  }
  else if (name== ("group"))
  {
   // nested "group" elements ...
   newGridGroup(e, c, g, globs, showStdName, modelElem);
  }
  else if (name!= ("qualifier"))
  { // its a mistake
   log->error("No code to handle element of type "+e.tagName()+" in newColumn");
  }
 }
   // add glue to the bottom to allow resize
//         if (c->children().count() > 1) {
//             c.add(Box.createVerticalGlue());
//         }


}
/**
 * Create a single column from the JDOM column QDomElement
 */
//@SuppressWarnings("unchecked")
/*public*/ JPanel *PaneProgPane::newColumn(QDomElement  element, bool showStdName, QDomElement  modelElem)
{
 // create a panel to add as a new column or row
 JPanel* c = new JPanel();
 c->resize(523, 368);
 panelList->append(c);
 GridBagLayout* g = new GridBagLayout();
 GridBagConstraints* cs = new GridBagConstraints();
 g->setContentsMargins(0,0,0,0);
 g->setVerticalSpacing(2);
 g->setHorizontalSpacing(2);
 g->setObjectName("g");
 QFont font;
 font.setPointSize(8);
 setFont(font);
 c->setLayout(g);

// // handle include/exclude
// if (!PaneProgFrame::isIncludedFE(element, modelElem, rosterEntry, "", "")) {
//     return c;
// }

 // handle the xml definition
 // for all elements in the column or row
 QDomNodeList elemList = element.childNodes();
 if (log->isDebugEnabled())
  log->debug("newColumn starting with "+QString::number(elemList.size())+" elements");
 for (int i=0; i<elemList.size(); i++)
 {
  // update the grid position
  cs->gridy++;
  cs->gridx = 0;

  QDomElement  e = (elemList.at(i).toElement ());
  QString name = e.tagName();
  if (log->isDebugEnabled())
   log->debug("newColumn processing "+name+" element");
  // decode the type
  if (name==("display"))
  { // its a variable
    // load the variable
   Q_ASSERT(cs->gridx >=0);
   newVariable( e, c, g, cs, showStdName);
  }
  else if (name==("separator"))
  { // it's a separator
   //JSeparator j = new JSeparator(javax.swing.SwingConstants.HORIZONTAL);
   QFrame* line = new QFrame(c);
   line->setObjectName(QString::fromUtf8("line"));
   line->setGeometry(QRect(10, 30, 571, 16));
   line->setFrameShape(QFrame::HLine);
   line->setFrameShadow(QFrame::Sunken);
   cs->fill = GridBagConstraints::BOTH;
   cs->gridwidth = GridBagConstraints::REMAINDER;
   //g.setConstraints(j, *cs);
   //c.add(j);
   Q_ASSERT(cs->gridx >=0);
   g->addWidget(line, *cs);
   cs->gridwidth = 1;
  }
  else if (name==("label"))
  { // its  a label
   cs->gridwidth = GridBagConstraints::REMAINDER;
   makeLabel(e, c, g, cs);
  }
  else if (name == ("soundlabel"))
  {
   cs->gridwidth = GridBagConstraints::REMAINDER;
   makeSoundLabel(e, c, g, cs);
  }
  else if (name==("cvtable"))
  {
//   log->debug("starting to build CvTable pane");

//   JTable* cvTable = new JTable();
//   Q_ASSERT(cs->gridx >=0);
//   g->addWidget(cvTable, cs->gridy,cs->gridx,cs->rowSpan(), cs->colSpan());
//   //cvTable->setModel(new QtCvTableModel(_cvModel));
//   QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
//   proxyModel->setSourceModel(_cvModel);
//   cvTable->setModel(proxyModel);
//   cvTable->setSortingEnabled(true);
//   //cvTable->setModel(_cvModel);
//   cs->gridheight = GridBagConstraints::REMAINDER;
//   // remember which CVs to read/write
//   for (int j=0; j<_cvModel->rowCount(QModelIndex()); j++) {
//       cvList->append(j);
//   }

//   _cvTable = true;
//   _cvModel->configureTable(cvTable);
//   //connect(_cvModel, SIGNAL(modelChange(CvValue*,int)), this, SLOT(onModelChange(CvValue*,int)));

//   log->debug("end of building CvTable pane");
   makeCvTable(cs, g, c);
  }
  else if (name==("fnmapping"))
  {
    pickFnMapPanel(c, g, cs, modelElem);
  }
  else if (name==("dccaddress"))
  {
   QWidget* l = addDccAddressPanel(e);
   cs->gridwidth = GridBagConstraints::REMAINDER;
//            g->setConstraints(l, *cs);
            //c->layout()->addWidget(l);
   Q_ASSERT(cs->gridx >=0);
   g->addWidget(l, *cs);
   cs->gridwidth = 1;
  }
  else if (name== ("column"))
  {
   // nested "column" elements ...
   cs->gridheight = GridBagConstraints::REMAINDER;
   QWidget* l = newColumn(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridheight = 1;
   }
  }
  else if (name==("row"))
  {
   // nested "row" elements ...
   cs->gridwidth = GridBagConstraints::REMAINDER;
   JPanel* l = newRow(e, showStdName, modelElem);
   panelList->append(l);
//   g->setConstraints(l, *cs);
   //c->layout()->addWidget(l);
   Q_ASSERT(cs->gridx >=0);
   g->addWidget(l, *cs);
   cs->gridwidth = 1;
  }
  else if (name== ("grid"))
  {
   // nested "grid" elements ...
   cs->gridwidth = GridBagConstraints::REMAINDER;
   QWidget* l = newGrid(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridwidth = 1;
   }
  }
  else if (name== ("group"))
  {
   // nested "group" elements ...
   QWidget* l = newGroup(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
   }
  }
  else if (name!=("qualifier"))
  { // its a mistake
   log->error("No code to handle element of type \""+e.tagName()+"\" in newColumn pane=" + objectName());
  }
 }
    // add glue to the bottom to allow resize
//    c.add(Box.createVerticalGlue());
 if (log->isDebugEnabled()) log->debug(tr("grid columns %1 vs  %2").arg(cs->gridx).arg(g->columnCount()));
 Q_ASSERT(cs->gridx >=0);
 return c;
}


/**
 * Create a single row from the JDOM column QDomElement
 */
//@SuppressWarnings("unchecked")
/*public*/ JPanel* PaneProgPane::newRow(QDomElement  element, bool showStdName, QDomElement  modelElem)
{
 // create a panel to add as a new column or row
 JPanel* c = new JPanel();
 c->resize(523, 368);
 panelList->append(c);
 GridBagLayout* g = new GridBagLayout();
 GridBagConstraints* cs = new GridBagConstraints();
 g->setContentsMargins(0,0,0,0);
 g->setVerticalSpacing(2);
 g->setHorizontalSpacing(2);
 g->setObjectName("g");
 QFont font;
 font.setPointSize(8);
 setFont(font);
 c->setLayout(g);

 // handle the xml definition
 // for all elements in the column or row
 QDomNodeList elemList = element.childNodes();
 if (log->isDebugEnabled()) log->debug("newRow starting with "+QString::number(elemList.size())+" elements");
 for (int i=0; i<elemList.size(); i++)
 {
  // update the grid position
  cs->gridy = 0;
//  if(cs->gridx == GridBagConstraints::RELATIVE)
//   cs->gridx = 0;
//  else
  cs->gridx++;

  QDomElement  e = elemList.at(i).toElement();
  QString name = e.tagName();
  if (log->isDebugEnabled())
   log->debug("newRow processing "+name+" element");
  // decode the type
  if (name == ("display"))
  { // its a variable
    // load the variable
      Q_ASSERT(cs->gridx >=0);
   newVariable( e, c, g, cs, showStdName);
  }
  else
  if (name==("separator"))
  { // its a separator
   //JSeparator j = new JSeparator(javax.swing.SwingConstants.VERTICAL);
   cs->fill = GridBagConstraints::BOTH;
   cs->gridheight = GridBagConstraints::REMAINDER;
   //g.setConstraints(j, *cs);
   //c.add(j);
   QFrame* line = new QFrame(c);
      line->setObjectName(QString::fromUtf8("line"));
      line->setGeometry(QRect(10, 30, 16, 200));
      line->setFrameShape(QFrame::VLine);
      line->setFrameShadow(QFrame::Sunken);
      Q_ASSERT(cs->gridx >=0);
   g->addWidget(line, *cs);
   cs->fill = GridBagConstraints::NONE;
   cs->gridheight = 1;
  }
  else if (name==("label"))
  {
   cs->gridheight = GridBagConstraints::REMAINDER;
   makeLabel(e, c, g, cs);
  }
  else if (name==("soundlabel"))
  {
   cs->gridheight = GridBagConstraints::REMAINDER;
   makeSoundLabel(e, c, g, cs);
  }
  else if (name==("cvtable"))
  {
   makeCvTable(cs, g, c);
  }
  else if (name==("fnmapping"))
  {
   pickFnMapPanel(c, g, cs, modelElem);
  }
  else if (name==("dccaddress"))
  {
   QWidget* l = addDccAddressPanel(e);
   cs->gridheight = GridBagConstraints::REMAINDER;
//            g->setConstraints(l, *cs);
        //c->layout()->addWidget(l);
   Q_ASSERT(cs->gridx >=0);
   g->addWidget(l, *cs);
   cs->gridheight = 1;
  }
  else if (name==("column"))
  {
   // nested "column" elements ...
   cs->gridheight = GridBagConstraints::REMAINDER;
   QWidget* l = newColumn(e, showStdName, modelElem);
   panelList->append(l);
//  g->setConstraints(l, *cs);
   //c->layout()->addWidget(l);
   Q_ASSERT(cs->gridx >=0);
   g->addWidget(l, *cs);
   cs->gridheight = 1;
  }
  else if (name== ("row"))
  {
   // nested "row" elements ...
   cs->gridwidth = GridBagConstraints::REMAINDER;
   QWidget* l = newRow(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridwidth = 1;
   }
  }
  else if (name== ("grid"))
  {
   // nested "grid" elements ...
   cs->gridwidth = GridBagConstraints::REMAINDER;
   QWidget* l = newGrid(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
    cs->gridwidth = 1;
   }
  }
  else if (name==("group"))
  {
   // nested "group" elements ...
   QWidget* l = newGroup(e, showStdName, modelElem);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, *cs);
    g->addWidget(l, *cs);
}
  }
  else if (name!=("qualifier"))
  { // its a mistake
   log->error("No code to handle element of type "+e.tagName()+" in newRow");
  }
 }
    // add glue to the bottom to allow resize
//    c.add(Box.createVerticalGlue());
 if(log->isDebugEnabled()) log->debug(tr("grid columns %1 vs  %2").arg(cs->gridx).arg(g->columnCount()));

 Q_ASSERT(cs->gridx >=0);
 return c;
}
/**
 * Create a grid from the JDOM  QDomElement
 */
/*public*/ JPanel* PaneProgPane::newGrid(QDomElement  element, bool showStdName, QDomElement  modelElem)
{
 // create a panel to add as a new grid
 /*final*/ JPanel* c = new JPanel();
 panelList->append(c);
 GridBagLayout* g = new GridBagLayout();
 c->setLayout(g);

 GridGlobals* globs = new GridGlobals();

 // handle the xml definition
 // for all elements in the grid
 QDomNodeList elemList = element.childNodes();
 //globs->gridAttList = element.getAttributes(); // get grid-level attributes
 globs->gridAttList = getAttributeList(element);
 log->trace(tr("newGrid starting with %1 elements").arg(elemList.size()));
 for (int i=0; i<elemList.size(); i++)
 {
  globs->gridConstraints = new GridBagConstraints();
  QDomElement e = elemList.at(i).toElement();
  QString name = e.tagName();
  log->trace(tr("newGrid processing %1 element").arg(name));
  // decode the type
  if (name== ("griditem"))
  {
   QWidget* l = newGridItem(e, showStdName, modelElem, globs);
   if (l->children().count() > 1)
   {
    panelList->append(l);
    //g.setConstraints(l, globs.gridConstraints);
    g->addWidget(l, *globs->gridConstraints);
//                     globs.gridConstraints.gridwidth = 1;
   }
  }
  else if (name== ("group"))
  {
   // nested "group" elements ...
    newGridGroup(e, c, g, globs, showStdName, modelElem);
  }
  else if (name!= ("qualifier"))
  { // its a mistake
   log->error("No code to handle element of type "+e.tagName()+" in newGrid");
  }
 }

 // add glue to the bottom to allow resize
 if (c->children().count() > 1)
 {
  //g->addWidget(Box.createVerticalGlue());
 }

#if 0
 // handle qualification if any
 MyQualifierAdder* qa = new MyQualifierAdder(c, this);
//    {
//        protected Qualifier createQualifier(VariableValue var, String relation, String value) {
//            return new JComponentQualifier(c, var, Integer.parseInt(value), relation);
//        }
//        protected void addListener(java.beans.PropertyChangeListener qc) {
//            c.addPropertyChangeListener(qc);
//        }
//    };

 qa->processModifierElements(element, _varModel);
#endif
 return c;
}

MyQualifierAdder::MyQualifierAdder(JLabel *l, PaneProgPane *self) : QualifierAdder(self)
{
 this->self = self;
 this->l = l;
}

/*protected*/ Qualifier* MyQualifierAdder::createQualifier(VariableValue* var, QString relation, QString value)
{
 return new JComponentQualifier(l, var, value.toInt(), relation);
}
/*protected*/ void MyQualifierAdder::addListener(PropertyChangeListener* qc)
{
 //l->addPropertyChangeListener(qc);
    // TODO:
}

/**
 * Create a griditem from the JDOM  QDomElement
 */
/*public*/ JPanel* PaneProgPane::newGridItem(QDomElement  element, bool showStdName, QDomElement  modelElem, GridGlobals* globs)
{
 QString tagName = element.tagName();
 //QDomNamedNodeMap itemAttList = element.attributes(); // get item-level attributes
 QVector<Attribute*> itemAttList = getAttributeList(element);
 QVector<Attribute*> attList =  QVector<Attribute*>(globs->gridAttList);
 //attList.addAll(itemAttList); // merge grid and item-level attributes
 for(int i = 0; i < itemAttList.size(); i++)
  attList.append(itemAttList.at(i));
//                log->info("New gridtiem -----------------------------------------------");
//                log->info("Attribute list:"+attList);
 attList.append(new Attribute(LAST_GRIDX,""));

 attList.append(new Attribute(LAST_GRIDY,""));
//                log->info("Updated Attribute list:"+attList);
//                 Attribute ax = attList.get(attList.size()-2);
//                 Attribute ay = attList.get(attList.size()-1);
//                log->info("ax="+ax+";ay="+ay);
//                log->info("Previous gridxCurrent="+globs.gridxCurrent+";gridyCurrent="+globs.gridyCurrent);
 for (int j = 0; j < attList.size(); j++)
 {
  //Attribute attrib = attList.get(j);
  Attribute* attrib = attList.at(j);
  QString attribName = attrib->name;
  QString attribRawValue = attrib->value;
  Field* constraint = NULL;
  QString constraintType = "";
  // make sure we only process the last gridx or gridy attribute in the list
  if ( attribName== ("gridx") )
  {
   Attribute* a = new Attribute(LAST_GRIDX,attribRawValue);
   //attList.set(attList.size()-2,a);
   attList.replace(attList.size()-2,a);
   //attList.append(a);
//                        log->info("Moved & Updated Attribute list:"+attList);
   globs->gridConstraints->gridx = attribRawValue.toInt();
   continue; //. don't process now
  }
  if ( attribName == ("gridy") )
  {
   Attribute* a = new Attribute(LAST_GRIDY,attribRawValue);
   //attList.set(attList.size()-1,a);
   attList.append(a);
//                        log->info("Moved & Updated Attribute list:"+attList);
   globs->gridConstraints->gridy = attribRawValue.toInt();
    continue; //. don't process now
  }
  if ( attribName== (LAST_GRIDX) )
  { // we must be at end of original list, restore last gridx
   attribName = "gridx";
   if ( attribRawValue== ("") )
   { // don't process blank (unused)
    continue;
   }
  }
  if ( attribName== (LAST_GRIDY) )
  { // we must be at end of original list, restore last gridy
   attribName = "gridy";
   if ( attribRawValue== ("") ) { // don't process blank (unused)
    continue;
  }
 }
 if ( ( attribName== ("gridx") || attribName== ("gridy") ) && attribRawValue== ("RELATIVE") )
 {
  attribRawValue = "NEXT"; // NEXT is a synonym for RELATIVE
 }
 if ( attribName== ("gridx")  && attribRawValue== ("CURRENT") )
 {
  attribRawValue = QString::number(qMax(0,globs->gridxCurrent));
 }
 if ( attribName== ("gridy")  && attribRawValue== ("CURRENT") )
 {
  attribRawValue = QString::number(qMax(0,globs->gridyCurrent));
 }
 if ( attribName== ("gridx")  && attribRawValue== ("NEXT") )
 {
  attribRawValue = QString::number(++globs->gridxCurrent);
 }
 if ( attribName== ("gridy")  && attribRawValue== ("NEXT") )
 {
  attribRawValue = QString::number(++globs->gridyCurrent);
 }
//                    log->info("attribName="+attribName+";attribRawValue="+attribRawValue);
#if 0
 try
 {
  constraint = globs->gridConstraints.getClass().getDeclaredField(attribName);
  constraintType = constraint->getType().toString();
  constraint->setAccessible(true);
 }
 catch (/*NoSuchFieldException*/ Exception ex)
 {
  log->error("Unrecognised attribute \""+attribName+"\", skipping");
  continue;
 }
#endif
 if ( constraintType== ("int") )
 {
  int attribValue;
  try
  {
   attribValue = attribRawValue.toInt();
   constraint->set((QObject*)globs->gridConstraints, QVariant(attribValue));
  }
  catch (IllegalAccessException ey)
  {
   log->error("Unable to set constraint \""+attribName+". IllegalAccessException error thrown.");
  }
  catch (NumberFormatException ex)
  {
#if 0
   try
   {
    Field* constant = globs->gridConstraints.getClass().getDeclaredField(attribRawValue);
    constant.setAccessible(true);
    attribValue = (Integer) GridBagConstraints::class.getField(attribRawValue).get(constant);
    constraint.set(globs.gridConstraints,attribValue);
   }
   catch (NoSuchFieldException ey)
   {
    log->error("Invalid value \""+attribRawValue+"\" for attribute \""+attribName+"\"");
   }
   catch (IllegalAccessException ey)
   {
    log->error("Unable to set constraint \""+attribName+". IllegalAccessException error thrown.");
   }
#endif
  }
 }
 else if ( constraintType== ("double") )
 {
  double attribValue;
  try
  {
   attribValue = attribRawValue.toDouble();
   constraint->set((QObject*)globs->gridConstraints,QVariant(attribValue));
  }
  catch (IllegalAccessException ey)
  {
   log->error("Unable to set constraint \""+attribName+". IllegalAccessException error thrown.");
  }
  catch (NumberFormatException ex)
  {
   log->error("Invalid value \""+attribRawValue+"\" for attribute \""+attribName+"\"");
  }
 }
  else if ( constraintType== ("class java.awt.Insets") )
  {
   try
   {
    QStringList insetStrings = attribRawValue.split(",");
    if ( insetStrings.length() == 4)
    {
     Insets* attribValue = new Insets(insetStrings[0].toInt(),insetStrings[1].toInt(),insetStrings[2].toInt(),insetStrings[3].toInt());
    constraint->set((QObject*)globs->gridConstraints,VPtr<Insets>::asQVariant(attribValue));
    }
    else
    {
     log->error("Invalid value \""+attribRawValue+"\" for attribute \""+attribName+"\"");
     log->error("Value should be four integers of the form \"top,left,bottom,right\"");
    }
   }
   catch (IllegalAccessException ey)
   {
    log->error("Unable to set constraint \""+attribName+". IllegalAccessException error thrown.");
   }
   catch (NumberFormatException ex)
   {
    log->error("Invalid value \""+attribRawValue+"\" for attribute \""+attribName+"\"");
    log->error("Value should be four integers of the form \"top,left,bottom,right\"");
   }
  }
  else
  {
   log->error("Required \""+constraintType+"\" handler for attribute \""+attribName+"\" not defined in JMRI code");
   log->error("Please file a JMRI bug report at https://sourceforge.net/p/jmri/bugs/new/");
  }
 }
//                log->info("Updated globs.GridBagConstraints::gridx="+globs.gridConstraints.gridx+";globs.GridBagConstraints::gridy="+globs.gridConstraints.gridy);


 // create a panel to add as a new grid item
  /*final*/ JPanel* c = new JPanel();
  panelList->append(c);
  GridBagLayout* g = new GridBagLayout();
  GridBagConstraints* cs = new GridBagConstraints();
  c->setLayout(g);

  // handle the xml definition
  // for all elements in the grid item
  QDomNodeList elemList = element.childNodes();
  if (log->isDebugEnabled())
   log->debug("newGridItem starting with "+QString::number(elemList.size())+" elements");
  for (int i=0; i<elemList.size(); i++)
  {
   // update the grid position
   cs->gridy = 0;
   cs->gridx++;

   QDomElement  e = elemList.at(i).toElement();
   QString name = e.tagName();
   log->trace(tr("newGridItem processing %1 element").arg(name));
   // decode the type
   if (name== ("display"))
   { // its a variable
    // load the variable
    newVariable( e, c, g, cs, showStdName);
   }
   else if (name== ("separator"))
   { // its a separator
    JSeparator* j = new JSeparator(JSeparator::VERTICAL);
    cs->fill = GridBagConstraints::BOTH;
    cs->gridheight = GridBagConstraints::REMAINDER;
    //g.setConstraints(j, *cs);
    g->addWidget(j, *cs);
    cs->fill = GridBagConstraints::NONE;
    cs->gridheight = 1;
   }
   else if (name== ("label"))
   {
    cs->gridheight = GridBagConstraints::REMAINDER;
    makeLabel(e, c, g, cs);
   }
   else if (name== ("soundlabel"))
   {
    cs->gridheight = GridBagConstraints::REMAINDER;
    makeSoundLabel(e, c, g, cs);
   }
   else if (name== ("cvtable"))
   {
    makeCvTable(cs, g, c);
   }
   else if (name== ("column"))
   {
    // nested "column" elements ...
    cs->gridheight = GridBagConstraints::REMAINDER;
    QWidget* l = newColumn(e, showStdName, modelElem);
    if (l->children().count() > 1)
    {
     panelList->append(l);
     //g.setConstraints(l, *cs);
     g->addWidget(l, *cs);
     cs->gridheight = 1;
    }
   }
   else if (name== ("row"))
   {
    // nested "row" elements ...
    cs->gridwidth = GridBagConstraints::REMAINDER;
    QWidget* l = newRow(e, showStdName, modelElem);
    if (l->children().count() > 1)
    {
     panelList->append(l);
     //g.setConstraints(l, *cs);
     g->addWidget(l, *cs);
     cs->gridwidth = 1;
    }
   }
   else if (name== ("grid"))
   {
    // nested "grid" elements ...
    cs->gridwidth = GridBagConstraints::REMAINDER;
    QWidget* l = newGrid(e, showStdName, modelElem);
    if (l->children().count() > 1)
    {
     panelList->append(l);
     //g.setConstraints(l, *cs);
     g->addWidget(l, *cs);
     cs->gridwidth = 1;
    }
   }
   else if (name== ("group"))
   {
    // nested "group" elements ...
    QWidget* l = newGroup(e, showStdName, modelElem);
    if (l->children().count() > 1)
    {
     panelList->append(l);
     //g.setConstraints(l, *cs);
     g->addWidget(l, *cs);
    }
   }
   else if (name!= ("qualifier"))
   { // its a mistake
    log->error("No code to handle element of type "+e.tagName()+" in newGridItem");
   }
  }

  globs->gridxCurrent = globs->gridConstraints->gridx;
  globs->gridyCurrent = globs->gridConstraints->gridy;
//                log->info("Updated gridxCurrent="+globs.gridxCurrent+";gridyCurrent="+globs.gridyCurrent);

  // add glue to the bottom to allow resize
  if (c->children().count() > 1) {
//   g->addWidget(Box.createVerticalGlue());
  }
#if 0
  // handle qualification if any
  MyQualifierAdder* qa = new MyQualifierAdder( l, this);
//  {
//        /*protected*/ Qualifier createQualifier(VariableValue var, String relation, QString value) {
//            return new JComponentQualifier(c, var, Integer.parseInt(value), relation);
//        }
//        /*protected*/ void addListener(PropertyChangeListener* qc) {
//            c.addPropertyChangeListener(qc);
//        }
//    };

 qa->processModifierElements(element, _varModel);
#endif
 return c;
}
/**
 * Create label from Element
 */
/*protected*/ void PaneProgPane::makeLabel(QDomElement e, QWidget* c, GridBagLayout* g, GridBagConstraints* cs)
{
 //QString text = LocaleSelector.getAttribute(e,"text");
 QString text = e.attribute("text");
 if (text.isNull() || text== (""))
  //text = LocaleSelector.getAttribute(e,"label"); // label subelement deprecated 3.7.5
  text = e.attribute("label");
 QDomElement eText= e.firstChildElement("text");
 if(!eText.isNull())
  text= eText.text();
 /*final*/ JLabel* l = new JLabel(text);
 //l.setAlignmentX(1.0f);
 cs->fill = GridBagConstraints::BOTH;
 log->trace(tr("Add label: %1 cs: %2 fill: %3 x: %4 y: %5").arg(
                 l->text()).arg(cs->gridwidth).arg(cs->fill).arg(cs->gridx).arg(cs->gridy));
 //g.setConstraints(l, *cs);
 g->addWidget(l, *cs);
 cs->fill = GridBagConstraints::NONE;
 cs->gridwidth = 1;
 cs->gridheight = 1;

 // handle qualification if any
 MyQualifierAdder* qa = new MyQualifierAdder(l, this);
// {
//        protected Qualifier createQualifier(VariableValue var, String relation, String value) {
//            return new JComponentQualifier(l, var, Integer.parseInt(value), relation);
//        }
//        protected void addListener(java.beans.PropertyChangeListener qc) {
//            l.addPropertyChangeListener(qc);
//        }
//    };

 qa->processModifierElements(e, _varModel);
}
 /**
  * Create sound label from Element
  */
/*protected*/ void PaneProgPane::makeSoundLabel(QDomElement e, QWidget* c, GridBagLayout *g, GridBagConstraints* cs)
{

 QString labelText = rosterEntry->getSoundLabel(e.attribute("num").toInt());
 /*final*/ QLabel* l = new QLabel(labelText);
 //l.setAlignmentX(1.0f);
 cs->fill = GridBagConstraints::BOTH;
 if (log->isDebugEnabled())
 {
  log->debug("Add soundlabel: "+l->text()+" cs: "
                   +QString::number(cs->gridwidth)+" "+QString::number(cs->fill)+" "
                   +QString::number(cs->gridx)+" "+QString::number(cs->gridy));
 }
 //g.setConstraints(l, *cs);
 g->addWidget(l, *cs);
 cs->fill = GridBagConstraints::NONE;
 cs->gridwidth = 1;
 cs->gridheight = 1;
#if 0
 // handle qualification if any
 MyQualifierAdder* qa = new MyQualifierAdder(c, this);
//  {
//         protected Qualifier createQualifier(VariableValue var, String relation, String value) {
//             return new JComponentQualifier(l, var, Integer.parseInt(value), relation);
//         }
//         protected void addListener(java.beans.PropertyChangeListener qc) {
//             l.addPropertyChangeListener(qc);
//         }
//     };


 qa->processModifierElements(e, _varModel);
#endif
}

void PaneProgPane::makeCvTable(GridBagConstraints* cs, GridBagLayout* g, JPanel* c)
{
 log->debug("starting to build CvTable pane");

 //TableRowSorter<TableModel> sorter = new TableRowSorter<TableModel>(_cvModel);

 JTable* cvTable = new JTable();
 //cvTable->setModel(_cvModel);
 cvTable->setSortingEnabled(true);
 QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel;
 proxyModel->setSourceModel(_cvModel);
 cvTable->setModel(proxyModel);
 cvTable->setSortingEnabled(true);
 _cvModel->configureTable(cvTable);
 _cvModel->setTable(cvTable);
 //sorter.setComparator(CvTableModel.NUMCOLUMN, new jmri.util.PreferNumericComparator());
 cvTable->getTableHeader()->setSectionsMovable(false);
 cvTable->getTableHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    List <RowSorter.SortKey> sortKeys
//        = new ArrayList<RowSorter.SortKey>();
//    sortKeys.add(new RowSorter.SortKey(0, SortOrder.ASCENDING));
//    sorter.setSortKeys(sortKeys);

//    cvTable.setRowSorter(sorter);

//    cvTable.setDefaultRenderer(JTextField.class, new ValueRenderer());
//    cvTable.setDefaultRenderer(JButton.class, new ValueRenderer());
//    cvTable.setDefaultEditor(JTextField.class, new ValueEditor());
//    cvTable.setDefaultEditor(JButton.class, new ValueEditor());
//    cvTable.setRowHeight(new JButton("X").getPreferredSize().height);
//    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//    // instead of forcing the columns to fill the frame (and only fill)
    cvTable->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);

//    JScrollPane  cvScroll = new JScrollPane(cvTable);
//    cvScroll.setColumnHeaderView(cvTable.getTableHeader());
 cvTable->resize(600,400);
 cs->gridheight = GridBagConstraints::REMAINDER;
 //g.setConstraints(cvScroll, *cs);
 //c.add(cvScroll);
 g->addWidget(cvTable, *cs);
 cs->gridheight = 1;

 // remember which CVs to read/write
 isCvTablePane = true;
 setCvListFromTable();

 _cvTable = true;
 log->debug("end of building CvTable pane");
}

void PaneProgPane::setCvListFromTable()
{
 // remember which CVs to read/write
 for (int j=0; j<_cvModel->rowCount(QModelIndex()); j++)
 {
  cvList->append((j));
 }
}

/**
 * Pick an appropriate function map panel depending on model attribute.
 *  <dl>
 *  <dt>If attribute extFnsESU="yes":</dt>
 *   <dd>Invoke FnMapPanelESU(VariableTableModel v, List<Integer> varsUsed, Element model)</dd>
 *  <dt>Otherwise:</dt>
 *   <dd>Invoke FnMapPanel(VariableTableModel v, List<Integer> varsUsed, Element model)</dd>
 * </dl>
 */

void PaneProgPane::pickFnMapPanel(QWidget* c, GridBagLayout* g, GridBagConstraints* cs, QDomElement modelElem)
{
 bool extFnsESU = false;
 QString a = modelElem.attribute("extFnsESU");
 try
 {
  if (a!="") extFnsESU = a.compare("yes",Qt::CaseInsensitive);
 }
 catch (Exception ex) {log->error("error handling decoder's extFnsESU value");}
 if (extFnsESU)
 {
  FnMapPanelESU* l = new FnMapPanelESU(_varModel, varList, modelElem, rosterEntry, _cvModel);
  fnMapListESU->append(l); // remember for deletion
  cs->gridwidth = GridBagConstraints::REMAINDER;
  //g.setConstraints(l, *cs);
  g->addWidget(l, *cs);
  cs->gridwidth = 1;
 }
 else
 {
  FnMapPanel* l = new FnMapPanel(_varModel, varList, modelElem);
  fnMapList->append(l); // remember for deletion
  cs->gridwidth = GridBagConstraints::REMAINDER;
  //g.setConstraints(l, *cs);
  g->addWidget(l, *cs);
  cs->gridwidth = 1;
 }
}
/**
 * Add the representation of a single variable.  The
 * variable is defined by a JDOM variable QDomElement  from the XML file.
 */
/*public*/ void PaneProgPane::newVariable(QDomElement  var, JPanel * /*col*/, GridBagLayout* gridLayout, GridBagConstraints* cs, bool showStdName)
{
 // get the name
 QString name = var.attribute("item");

 // if it doesn't exist, do nothing
 int i = _varModel->findVarIndex(name);
 if (i<0)
 {
  if (log->isDebugEnabled()) log->debug("Variable \""+name+"\" not found, omitted");
   return;
 }

 // check label orientation
 QString attr;
 QString layout ="left";  // this default is also set in the DTD
 if ( !(attr = var.attribute("layout")).isNull() /*&& attr != NULL*/)
  layout = attr;

 // load label if specified, else use name
 QString label = name;
 if (!showStdName)
 {
  // get name attribute from variable, as that's the mfg name
  label = _varModel->getLabel(i);
 }
//    QString temp = LocaleSelector.attribute(var, "label");
 QString temp = var.attribute("label");
 if (!temp.isNull()) label = temp;

 // get representation; store into the list to be programmed
 QWidget* rep = getRepresentation(name, var);
// if(rep)
//  rep->setParent(this);
 if (i>=0)
  varList->append(i);

 // create the paired label
 JLabel* l = new WatchingLabel(" "+label+" ", rep);

 // now handle the four orientations
 // assemble v from label, rep
 if (layout==("left"))
 {
  QHBoxLayout* hLayout = new QHBoxLayout();
  Q_ASSERT(cs->gridx >=0);
  gridLayout->addLayout(hLayout, cs->gridy, cs->gridx);
  cs->anchor= GridBagConstraints::EAST;
//        g.setConstraints(l, *cs);
  //col->layout()->addWidget(l);
  hLayout->addWidget(l);

  //cs->gridx = GridBagConstraints::RELATIVE;
  cs->anchor= GridBagConstraints::WEST;
//        g.setConstraints(rep, *cs);
//  col->layout()->addWidget(rep);
  hLayout->addWidget(rep);
 }
 else if (layout==("right"))
 {
  QHBoxLayout* hLayout = new QHBoxLayout();
  Q_ASSERT(cs->gridx >=0);
  gridLayout->addLayout(hLayout, cs->gridy, cs->gridx);
  cs->anchor= GridBagConstraints::EAST;
//        g.setConstraints(rep, *cs);
//        col->layout()->addWidget(rep);
  hLayout->addWidget(rep);

  //cs->gridx = GridBagConstraints::RELATIVE;
  cs->anchor= GridBagConstraints::WEST;
//        g.setConstraints(l, *cs);
//        col->layout()->addWidget(l);
  hLayout->addWidget(l);
 }
 else if (layout==("below"))
 {
  // variable in center of upper line
  cs->anchor=GridBagConstraints::CENTER;
//        g.setConstraints(rep, *cs);
//        col->layout()->addWidget(rep);
  Q_ASSERT(cs->gridx >=0);
  gridLayout->addWidget(rep, *cs);

  // label aligned like others
  cs->gridy++;
  cs->anchor= GridBagConstraints::WEST;
//        g.setConstraints(l, *cs);
//        col->layout()->addWidget(l);
  Q_ASSERT(cs->gridx >=0);
  gridLayout->addWidget(l, *cs);
 }
 else if (layout==("above"))
 {
  // label aligned like others
  cs->anchor= GridBagConstraints::WEST;
//        g.setConstraints(l, *cs);
//        col->layout()->addWidget(l);
  Q_ASSERT(cs->gridx >=0);
  gridLayout->addWidget(l, *cs);

  // variable in center of lower line
  cs->gridy++;
  cs->anchor=GridBagConstraints::CENTER;
//        g.setConstraints(rep, *cs);
//        col->layout()->addWidget(rep);
  Q_ASSERT(cs->gridx >=0);
  gridLayout->addWidget(rep, *cs);
 }
 else
 {
  log->error("layout internally inconsistent: "+layout);
  return;
 }
 if(cs->gridx > 1 )
     qDebug() << tr("gridx = %1, name = %2").arg(cs->gridx).arg(name);
}

/**
 * Get a GUI representation of a particular variable for display.
 * @param name Name used to look up the Variable object
 * @param var XML QDomElement  which might contain a "format" attribute to be used in the {@link VariableValue#getNewRep} call
 * from the Variable object; "tooltip" elements are also processed here.
 * @return JComponent representing this variable
 */
/*public*/ QWidget* PaneProgPane::getRepresentation(QString name, QDomElement  var)
{
 int i = _varModel->findVarIndex(name);
 VariableValue* variable = _varModel->getVariable(i);
 QWidget* rep = NULL;
 QString format = "default";
 QString attr;
 if ( !(attr = var.attribute("format")).isNull() /*&& attr != NULL*/)
  format = attr;

 if (i>= 0)
 {
  QWidget* newRep = getRep(i, format);
  if(newRep)
  rep = newRep;
  Q_ASSERT(newRep != NULL);
//        rep->setMaximumSize(rep->getPreferredSize());
        // set tooltip if specified here & not overridden by defn in Variable
  QString tip = "";
  if ( (tip = /*LocaleSelector.attribute(var, "tooltip")*/var.attribute("tooltip"))!=NULL
              && rep->toolTip()==NULL)
   rep->setToolTip(modifyToolTipText(tip, variable));
  rep->setParent(this);
  //---------------------
//  if(qobject_cast<JSlider*>(rep))
//  {
//   JSlider* slider = (JSlider*)rep;
//   connect(slider, &JSlider::valueChanged, [=]{
//    variable->setIntValue(((JSlider*)rep)->value());
//   });
//   connect(variable->prop, &PropertyChangeSupport::propertyChange, [=](PropertyChangeEvent* e){
//    if(e->getPropertyName() == "Value")
//    {
//     slider->setValue(e->getNewValue().toInt());
//    }
//   });
//  }
//  else if(qobject_cast<JTextField*>(rep))
//  {
//   JTextField* tf = (JTextField*)rep;
//   connect(tf, &JTextField::editingFinished, [=]{
//    variable->setIntValue(((JTextField*)rep)->text().toInt());
//   });
//  }
//   else log->error(tr("unable to determine format type %1").arg(format));
  //---------------------

 }
 else
  log->warn(QString("var index not found for var %1").arg(name));

 return rep;
}

/**
 * Takes default tool tip text, e.g. from the decoder element, and modifies
 * it as needed.
 * <p>
 * Intended to handle e.g. adding CV numbers to variables.
 *
 * @param start    existing tool tip text
 * @param variable the CV
 * @return new tool tip text
 */
QString PaneProgPane::modifyToolTipText(QString start, VariableValue* variable) {
    log->trace(tr("modifyToolTipText: %1").arg(variable->label()));
    // this is the place to invoke VariableValue methods to (conditionally)
    // add information about CVs, etc in the ToolTip text

    // Optionally add CV numbers based on Roster Preferences setting
    start = CvUtil::addCvDescription(start, variable->getCvDescription(), variable->getMask());

    // Indicate what the command station can do
    // need to update this with e.g. the specific CV numbers
    if (_cvModel->getProgrammer() != nullptr
            && !_cvModel->getProgrammer()->getCanRead()) {
        start = StringUtil::concatTextHtmlAware(start, " (Hardware cannot read)");
    }
    if (_cvModel->getProgrammer() != nullptr
            && !_cvModel->getProgrammer()->getCanWrite()) {
        start = StringUtil::concatTextHtmlAware(start, " (Hardware cannot write)");
    }

    // indicate other reasons for read/write constraints
    if (variable->getReadOnly()) {
        start = StringUtil::concatTextHtmlAware(start, " (Defined to be read only)");
    }
    if (variable->getWriteOnly()) {
        start = StringUtil::concatTextHtmlAware(start, " (Defined to be write only)");
    }

    return start;
}

QWidget* PaneProgPane::getRep(int i, QString format) {
    return _varModel->getRep(i, format);
}

/*public*/ void PaneProgPane::dispose()
{
 if (log->isDebugEnabled()) log->debug("dispose");
#if 1 // TODO:

    // remove components
    //removeAll();

//    readChangesButton->removeItemListener(l1);
//    readAllButton->removeItemListener(l2);
//    writeChangesButton->removeItemListener(l3);
//    writeAllButton->removeItemListener(l4);
//    confirmChangesButton->removeItemListener(l5);
//    confirmAllButton->removeItemListener(l6);
    l1 = l2 = l3 = l4 = l5 = l6 = NULL;

    if (_programmingVar != NULL) _programmingVar->removePropertyChangeListener((PropertyChangeListener*)this);
    if (_programmingCV != NULL) _programmingCV->removePropertyChangeListener((PropertyChangeListener*)this);

    _programmingVar = NULL;
    _programmingCV  = NULL;

    varList->clear();
    varList = NULL;
    cvList->clear();
    cvList = NULL;

//    // dispose of any panels
//    for (int i=0; i<panelList.size(); i++) {
//        panelList->at(i)->removeAll();
//    }
    panelList->clear();
    panelList = NULL;

//    // dispose of any fnMaps
//    for (int i=0; i<fnMapList.size(); i++) {
//        fnMapList.get(i).dispose();
//    }
    fnMapList->clear();
    fnMapList = NULL;

    readChangesButton = NULL;
    writeChangesButton = NULL;
#endif
    // these are disposed elsewhere
    _cvModel = NULL;
    _varModel = NULL;
}

/*public*/ bool PaneProgPane::includeInPrint() { return print; }
/*public*/ void PaneProgPane::includeInPrint(bool inc) { print = inc; }

//@edu.umd.cs->findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ void PaneProgPane::printPane(HardcopyWriter* w)
{
#if 1 // TODO:

 // if pane is empty, don't print anything
 if (varList->size() == 0 && cvList->size() == 0) return;
 // future work needed her to print indexed CVs

 // Define column widths for name and value output.
 // Make col 2 slightly larger than col 1 and reduce both to allow for
 // extra spaces that will be added during concatenation
 int col1Width = w->getCharactersPerLine()/2 -3 - 5;
 int col2Width = w->getCharactersPerLine()/2 -3 + 5;

 try
 {
  //Create a string of spaces the width of the first column
  QString spaces = "";
  for (int i=0; i < col1Width; i++)
  {
   //spaces = spaces + " ";
   spaces = spaces.append(" ");
  }

  // start with pane name in bold
  QString heading1 = tr("Field");
  QString heading2 = tr("Setting");
  QString s;
  int interval = spaces.length()- heading1.length();
  w->setFontWeight(QFont::Bold);
  w->setFontStyle(QFont::StyleNormal);
  // write the section name and dividing line
  s = mName.toUpper();
  w->write(s, 0, s.length());
  w->writeBorders();
  //Draw horizontal dividing line for each Pane section
  w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),w->getCharactersPerLine()+1);
  s = "\n";
  w->write(s,0,s.length());
  // if this isn't the raw CV section, write the column headings
  if (cvList->size()== 0)
  {
   w->setFontStyle(QFont::StyleItalic);
   w->setFontWeight(QFont::Bold);
   s = "   " + heading1 + spaces.mid(0,interval) + "   " +   heading2;
   w->write(s, 0, s.length());
   w->writeBorders();
   s = "\n";
   w->write(s,0,s.length());
  }
  w->setFontStyle(QFont::StyleNormal); // Font.PLAIN
  w->setFontWeight(QFont::Normal);
  // Define a vector to store the names of variables that have been printed
  // already.  If they have been printed, they will be skipped.
  // Using a vector here since we don't know how many variables will
  // be printed and it allows expansion as necessary
  QVector<QString> printedVariables =  QVector<QString>(10/*,5)*/);
  // index over variables
  for (int i=0; i<varList->size(); i++)
  {
   Q_ASSERT(spaces.length() == col1Width);
   int varNum = varList->at(i);
   VariableValue* var = _varModel->getVariable(varNum);
   QString name = var->label();
   if (name == NULL) name = var->item();
   // Check if variable has been printed.  If not store it and print
   bool alreadyPrinted = false;
   for (int j = 0; j < printedVariables.size(); j++)
   {
    if (printedVariables.at(j) == name) alreadyPrinted = true;
   }
   //If already printed, skip it.  If not, store it and print
   if (alreadyPrinted == true) continue;
   printedVariables.append( name);

   QString value = var->getTextValue();
   QString originalName = name;
   QString originalValue = value;
   name = name +" (CV" +var->getCvNum() + ")";

   //define index values for name and value mids
   int nameLeftIndex = 0;
   int nameRightIndex = name.length();
   int valueLeftIndex = 0;
   int valueRightIndex =value.length();
   QString trimmedName;
   QString trimmedValue;
   int lastValueDelimiter = -1;

   // Check the name length to see if it is wider than the column.
   // If so, split it and do the same checks for the Value
   // Then concatenate the name and value (or the split versions thereof)
   // before writing - if split, repeat until all pieces have been output
   while ((valueLeftIndex < value.length()) || (nameLeftIndex < name.length()))
   {
    // name split code
    if (name.mid(nameLeftIndex).length() > col1Width)
    {
     for (int j = 0; j < col1Width; j++)
     {
      QString delimiter = name.mid(nameLeftIndex + col1Width - j - 1, nameLeftIndex + col1Width - j);
      if (delimiter.startsWith(" ") || delimiter.startsWith(";") || delimiter.startsWith(","))
      {
       nameRightIndex = nameLeftIndex + col1Width - j;
       break;
      }
     }
     trimmedName = name.mid(nameLeftIndex,nameRightIndex);
     nameLeftIndex = nameRightIndex;
     int space = spaces.length()- trimmedName.length();
     if(space > 0)
      s = "   " + trimmedName + spaces.mid(0,space);
     else
      s = "   " + trimmedName;
    }
    else
    {
     trimmedName = name.mid(nameLeftIndex);
     int space = spaces.length() - trimmedName.length();
     if(space > 0)
      s = "   " + trimmedName + spaces.mid(0,space);
     else
      s = "   " + trimmedName;
     name = "";
     nameLeftIndex = 0;
    }

    // value split code
    if (value.mid(valueLeftIndex).length() > col2Width)
    {
     for (int j = 0; j < col2Width; j++)
     {
      //QString delimiter = value.mid(valueLeftIndex + col2Width - j - 1, valueLeftIndex + col2Width - j);
      QString delimiter = value.mid(valueLeftIndex + j);
      if (delimiter.startsWith(" ") || delimiter.startsWith(";") || delimiter.startsWith(","))
      {
       valueRightIndex = valueLeftIndex + col2Width - j;
       lastValueDelimiter = valueLeftIndex + j;
       //break;
      }
     }
     trimmedValue = value.mid(valueLeftIndex,lastValueDelimiter - valueLeftIndex + 1);
     //valueLeftIndex = valueRightIndex;
     valueLeftIndex = lastValueDelimiter +1;
     s= s + "   " + trimmedValue;
    }
    else
    {
     trimmedValue = value.mid(valueLeftIndex);
     s = s + "   " + trimmedValue;
     valueLeftIndex = 0;
     value = "";
    }
    w->write(s,0,s.length());
    w->writeBorders();
    s = "\n";
    w->write(s,0,s.length());
   }

   // Check for a Speed Table output and create a graphic display.
   // Java 1.5 has a known bug, #6328248, that prevents printing of progress
   //  bars using old style printing classes.  It results in blank bars on Windows,
   //  but hangs Macs-> The version check is a workaround.
   float v = 1.6; // TODO: //Float.valueOf(java.lang.System.getProperty("java.version").mid(0, 3)).floatValue();
   if (originalName==("Speed Table") && v < 1.5)
   {
    // set the height of the speed table graph in lines
    int speedFrameLineHeight = 11;
    s = "\n";

    // check that there is enough room on the page; if not,
    // space down the rest of the page.
    // don't use page break because we want the table borders to be written
    // to the bottom of the page
    int pageSize = w->getLinesPerPage();
    int here = w->getCurrentLineNumber();
    if (pageSize - here < speedFrameLineHeight)
    {
     for (int j = 0; j < (pageSize - here); j++)
     {
      w->writeBorders();
      w->write(s,0,s.length());
     }
    }

    // Now that there is page space, create the window to hold the graphic speed table
    /*JWindow*/QMainWindow* speedWindow = new QMainWindow();
    // Window size as wide as possible to allow for largest type size
    speedWindow->resize(512,165);
    QWidget* contentPane = new QWidget;
    QVBoxLayout* contentPaneLayout = new QVBoxLayout;
    speedWindow->setCentralWidget(contentPane);
    //speedWindow->getContentPane().setBackground(Color.white);
    //speedWindow->getContentPane().setLayout(NULL);
    // in preparation for display, extract the speed table values into an array
    //StringTokenizer valueTokens =  StringTokenizer(originalValue,",",false);
    QStringList valueTokens = originalValue.split(",");
    QVector<int> speedVals =  QVector<int>(28);
    int k = 0;
    QStringListIterator iter(valueTokens);
    while (iter.hasNext())
    {
     speedVals.replace(k, iter.next().toInt());
     k++;
    }

    // Now create a set of vertical progress bar whose length is based
    // on the speed table value (half height) and add them to the window
    for (int j = 0; j < 28; j++)
    {
     QProgressBar* printerBar = new QProgressBar(); //QProgressBar::VERTICAL,0,127);
     printerBar->setOrientation(Qt::Vertical);
     printerBar->setMinimum(0);
     printerBar->setMaximum(127);
     printerBar->setGeometry(52+j*15, 19, 10, 127);
     printerBar->setValue(speedVals[j]/2);
//       printerBar->setBackground(Color.white);
//       printerBar->setForeground(Color.darkGray);
//       printerBar->setBorder(BorderFactory.createLineBorder(Color.black));
     contentPaneLayout->addWidget(printerBar);
     // create a set of value labels at the top containing the speed table values
     JLabel* barValLabel = new JLabel(QString::number(speedVals[j]));
     barValLabel->setAlignment(Qt::AlignCenter);
     barValLabel->setBounds(50+j*15, 4, 15, 15);
     barValLabel->setFont( QFont("Monospace", 7,QFont::Normal, false));
     contentPaneLayout->addWidget(barValLabel);
     //Create a set of labels at the bottom with the CV numbers in them
     JLabel* barCvLabel = new JLabel(QString::number(67+j)); //,SwingConstants.CENTER);
     barCvLabel->setAlignment(Qt::AlignCenter);
     barCvLabel->setBounds(50+j*15, 150, 15, 15);
     barCvLabel->setFont( QFont("Monospace", 7,QFont::Normal, false));
     contentPaneLayout->addWidget(barCvLabel);
    }
    JLabel* cvLabel = new JLabel("Value");
    cvLabel->setFont( QFont("Monospace", 7,QFont::Normal, false));
    cvLabel->setBounds(25,4,26,15);
    contentPaneLayout->addWidget(cvLabel);
    JLabel* valueLabel = new JLabel("CV");
    valueLabel->setFont( QFont("Monospace", 7,QFont::Normal, false));
    valueLabel->setBounds(37,150,13,15);
    contentPaneLayout->addWidget(valueLabel);
    // pass the complete window to the printing class
    w->write(speedWindow);
    // Now need to write the borders on sides of table
    for (int j = 0; j < speedFrameLineHeight; j++)
    {
     w->writeBorders();
     w->write(s,0,s.length());
    }
   }
  }

  // index over CVs
  if (cvList->size() > 0)
  {
   //            Check how many Cvs there are to print
   int cvCount = cvList->size();
   w->setFontWeight(QFont::Bold); //set font to Bold
   w->setFontStyle(QFont::StyleNormal);
   // print a simple heading
   s = "      Value           Value           Value           Value";
   w->write(s, 0, s.length());
   w->writeBorders();
   s = "\n";
   w->write(s,0,s.length());
   s = " CV   Dec Hex    CV   Dec Hex    CV   Dec Hex    CV   Dec Hex";
   w->write(s, 0, s.length());
   w->writeBorders();
   s = "\n";
   w->write(s,0,s.length());
   w->setFontWeight(QFont::Normal); //set font back to Normal
   w->setFontStyle(QFont::StyleNormal);
   //           }
   /*create an array to hold CV/Value strings to allow reformatting and sorting
    Same size as the table drawn above (4 columns*tableHeight; heading rows
    not included). Use the count of how many CVs there are to determine the number
    of table rows required.  Add one more row if the divison into 4 columns
    isn't even.
    */
   int tableHeight = cvCount/4;
   if (cvCount%4 > 0) tableHeight++;
   //String[] cvStrings = new String[4 * tableHeight];
   QStringList cvStrings = (QStringList)(QVector<QString>(4 * tableHeight)).toList();

   //blank the array
   for (int j = 0; j < cvStrings.length(); j++)
    cvStrings[j] = "";

   // get each CV and value
   int i = 0;
   foreach (int cvNum, *cvList)
   {
    CvValue* cv = _cvModel->getCvByRow(cvNum);

    int value = cv->getValue();

    //convert and pad numbers as needed
    QString numString = QString("%1").arg(cv->number().toInt(),3);
    QString valueString = QString::number(value);
    QString valueStringHex = QString::number(value,16).toUpper();
    if (value < 16)
     valueStringHex = "0" + valueStringHex;
    for (int j = 1; j < 3; j++)
    {
    if (numString.length() < 3)
      numString = " " + numString;
    }
    for (int j = 1; j < 3; j++)
    {
     if (valueString.length() < 3)
      valueString = " " + valueString;
    }
    //Create composite string of CV and its decimal and hex values
    s =  numString + "   " + valueString + "  " + valueStringHex +
        " ";

    //populate printing array - still treated as a single column
    cvStrings.replace(i, s);
    i++;
   }
   //sort the array in CV order (just the members with values)
   QString temp;
   bool swap = false;
   do
   {
    swap = false;
    for (int i = 0; i < _cvModel->rowCount(QModelIndex()) - 1; i++)
    {
     if ((cvStrings[i + 1].mid(0, 3).trimmed()).toInt() <
                  (cvStrings[i].mid(0, 3).trimmed()).toInt())
     {
      temp = cvStrings[i + 1];
      cvStrings.replace(i + 1, cvStrings[i]);
      cvStrings.replace(i, temp);
      swap = true;
     }
    }
   }
   while (swap == true);

   //Print the array in four columns
   for (int i = 0; i < tableHeight; i++)
   {
    s = cvStrings[i] + "  " + cvStrings[i + tableHeight] + "  " + cvStrings[i + tableHeight * 2] + "  " + cvStrings[i + tableHeight * 3];
    w->write(s, 0, s.length());
    w->writeBorders();
    s = "\n";
    w->write(s,0,s.length());
   }
  }
  s = "\n";
  w->writeBorders();
  w->write(s, 0, s.length());
  w->writeBorders();
  w->write(s, 0, s.length());

  // handle special cases
 }
 catch (IOException e) { log->warn("error during printing: "+e.getMessage());
 }
#endif
}

/*private*/ QWidget* PaneProgPane::addDccAddressPanel(QDomElement  e)
{
 QWidget* l;
 QString at = /*LocaleSelector.attribute(e, "label")*/e.attribute("label");
 if (at!=NULL)
  l = new DccAddressPanel(_varModel, at);
 else
  l = new DccAddressPanel(_varModel, tr("Active DCC Address:"));
 panelList->append(l);
 // make sure this will get read/written, even if real vars not on pane
 int iVar;

 // note we want Short Address first, as it might change others
 iVar = _varModel->findVarIndex("Short Address");
 if (iVar>=0) varList->append((iVar));
 else log->debug("addDccAddressPanel did not find Short Address");

 iVar = _varModel->findVarIndex("Address Format");
 if (iVar>=0) varList->append((iVar));
 else log->debug("addDccAddressPanel did not find Address Format");

 iVar = _varModel->findVarIndex("Long Address");
 if (iVar>=0) varList->append((iVar));
 else log->debug("addDccAddressPanel did not find Long Address");

 // included here because CV1 can modify it, even if it doesn't show on pane;
 iVar = _varModel->findVarIndex("Consist Address");
 if (iVar>=0) varList->append((iVar));
 else log->debug("addDccAddressPanel did not find CV19 Consist Address");

 return l;
}

void PaneProgPane::On_readChangesButton_clicked() // SLOT[]
{
 //if (e.getStateChange() == ItemEvent.SELECTED)
 if(readChangesButton->isSelected())
 {
  readChangesButton->setText(tr("Stop Read changes on sheet"));
  if (container->isBusy() == false)
  {
   prepReadPane(true);
   prepGlassPane(readChangesButton);
   container->getBusyGlassPane()->setVisible(true);
   readPaneChanges();
  }
 }
 else
 {
  stopProgramming();
  readChangesButton->setText(tr("Read changes on sheet"));
  if (container->isBusy())
  {
   readChangesButton->setEnabled(false);
  }
 }
}

void PaneProgPane::On_readAllButton_clicked() // SLOT[]
{
 //if (e.getStateChange() == ItemEvent.SELECTED) {
 if(readAllButton->isSelected())
 {
  readAllButton->setText(tr("Stop Read full sheet"));
  if (container->isBusy() == false)
  {
   prepReadPane(false);
   prepGlassPane(readAllButton);
   container->getBusyGlassPane()->setVisible(true);
   readPaneAll();
  }
 }
 else
 {
  stopProgramming();
  readAllButton->setText(tr("Read full sheet"));
  if (container->isBusy())
  {
   readAllButton->setEnabled(false);
  }
 }
}
void PaneProgPane::On_writeChangesButton_clicked()
{
 //if (e.getStateChange() == ItemEvent.SELECTED)
 if(writeChangesButton->isSelected())
 {
  writeChangesButton->setText(tr("Stop Write changes on sheet"));
  if (container->isBusy() == false)
  {
    prepWritePane(true);
    prepGlassPane(writeChangesButton);
    if(container->getBusyGlassPane() != NULL)
     container->getBusyGlassPane()->setVisible(true);
    writePaneChanges();
  }
 }
 else
 {
  stopProgramming();
  writeChangesButton->setText(tr("Write changes on sheet"));
  if (container->isBusy())
  {
   writeChangesButton->setEnabled(false);
  }
 }
}
void PaneProgPane::On_writeAllButton_clicked()
{
 //if (e.getStateChange() == ItemEvent.SELECTED)
 log->debug(tr("writeAll clicked"));
 if(writeAllButton->isSelected())
 {
  writeAllButton->setText(tr("Stop Write full sheet"));
  if (container->isBusy() == false)
  {
    prepWritePane(false);
    prepGlassPane(writeAllButton);
    container->getBusyGlassPane()->setVisible(true);
    writePaneAll();
  }
 }
 else
 {
  stopProgramming();
  writeAllButton->setText(tr("Write full sheet"));
  if (container->isBusy())
  {
   writeAllButton->setEnabled(false);
  }
 }
}
void PaneProgPane::On_confirmChangesButtonClicked()
{
 if(confirmChangesButton->isSelected())
 {
  confirmChangesButton->setText(tr("Stop Compare changes on sheet"));
  if (container->isBusy() == false)
  {
    prepConfirmPane(true);
    prepGlassPane(confirmChangesButton);
    container->getBusyGlassPane()->setVisible(true);
    confirmPaneChanges();
  }
 }
 else
 {
  stopProgramming();
  confirmChangesButton->setText(tr("Compare changes on sheet"));
  if (container->isBusy())
  {
   confirmChangesButton->setEnabled(false);
  }
 }
}
void PaneProgPane::On_confirmAllButtonClicked()
{
 if(confirmAllButton->isSelected())
 {
  confirmAllButton->setText(tr("Stop Compare full sheet"));
  if (container->isBusy() == false)
  {
    prepConfirmPane(false);
    prepGlassPane(confirmAllButton);
    if(container->getBusyGlassPane()!= NULL)
     container->getBusyGlassPane()->setVisible(true);
    confirmPaneAll();
  }
 }
 else
 {
  stopProgramming();
  confirmAllButton->setText(tr("Compare full sheet"));
  if (container->isBusy())
  {
   confirmAllButton->setEnabled(false);
  }
 }
}
void PaneProgPane::addPropertyChangeListener(PropertyChangeListener* /*l*/)
{
// pcs->addPropertyChangeListener(l);
}
void PaneProgPane::removePropertyChangeListener(PropertyChangeListener* /*l*/)
{
// pcs->removePropertyChangeListener(l);
}

QVector<Attribute*> PaneProgPane::getAttributeList(QDomElement e)
{
 QDomNamedNodeMap l = e.attributes();
 QVector<Attribute*> attrList;
 for(int i = 0; i < l.size(); i++)
 {
  QDomNode n  = l.item(i);
  Attribute* a = new Attribute(n.nodeName(), n.nodeValue());
  attrList.append(a);
 }
 return attrList;
}
/**
 * Support for reporting bound property changes for Object properties.
 * This method can be called when a bound property has changed and it will
 * send the appropriate PropertyChangeEvent to any registered
 * PropertyChangeListeners.
 *
 * @param propertyName the property whose value has changed
 * @param oldValue the property's previous value
 * @param newValue the property's new value
 */
/*protected*/ void PaneProgPane::firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue)
{
//    synchronized (getObjectLock()) {
//        changeSupport = this->changeSupport;
//    }
    if (changeSupport == NULL ||
        (oldValue != QVariant() && newValue != QVariant() && oldValue==(newValue))) {
        return;
    }
    changeSupport->firePropertyChange(propertyName, oldValue, newValue);
}

/*private*/ /*final*/ /*static*/ Logger* PaneProgPane::log = LoggerFactory::getLogger("PaneProgPane");
