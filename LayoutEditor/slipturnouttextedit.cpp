#include "slipturnouttextedit.h"
#include "slipturnouticon.h"
#include <QLabel>
#include <QPushButton>
#include "jtextfield.h"
#include <QGridLayout>
#include "gridbagconstraints.h"

//SlipTurnoutTextEdit::SlipTurnoutTextEdit(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Displays and allows user to modify the text display used in a turnout slip
 *
 * This is a modification of CoordinateEdit.java by Dan Boudreau for use with LayoutEditor
 *
 * @author Dan Boudreau Copyright (C) 2007
 * @author Kevin Dickerson (SlipTurnoutTextEditor version);
 * @version $Revision: 22320 $
 */

//  /*public*/ class SlipTurnoutTextEdit extends JmriJFrame
//{

/*static*/ /*final*/ QString SlipTurnoutTextEdit::INIT = "";
/*public*/ SlipTurnoutTextEdit::SlipTurnoutTextEdit(QWidget *parent)  : JmriJFrame(parent)
{
    //super();
oldLWUE = INIT;
oldUWLE = INIT;
oldLWLE = INIT;
oldUWUE = INIT;

// member declarations
lableName = new QLabel();
nameText = new QLabel();
textLWUE = new QLabel();
textUWLE = new QLabel();
textLWLE = new QLabel();
textUWUE = new QLabel();

// buttons
okButton = new QPushButton();
cancelButton = new QPushButton();

// text field
UWLETextField = new JTextField(15);
LWUETextField = new JTextField(15);
LWLETextField = new JTextField(15);
UWUETextField = new JTextField(15);

// for padding out panel
space1 = new QLabel();
space2 = new QLabel();

}

// /*public*/ void windowClosed(java.awt.event.WindowEvent e)
/*public*/ void SlipTurnoutTextEdit::closeEvent(QCloseEvent* e)
{
 //super.windowClosed(e);
 //JFrame::closeEvent(e);
}

/*public*/ void SlipTurnoutTextEdit::initComponents(SlipTurnoutIcon* l, QString name) //throw (Exception)
{
 pl = l;

 // the following code sets the frame's initial state
 lableName->setText(tr("Name")+": ");
 lableName->setVisible(true);

 nameText->setText(name);
 nameText->setVisible(true);

 textLWUE->setText(tr("Upper West To Lower East") + " = " + pl->getUWLEText());
 textLWUE->setVisible(true);
 textUWLE->setText(tr("Lower West To Upper East") + " = " + pl->getLWUEText());
 textUWLE->setVisible(true);
 textLWLE->setText(tr("Lower West To Lower East") + " = " + pl->getLWLEText());
 textUWUE->setText(tr("Upper West To Upper East") + " = " + pl->getUWUEText());

 UWLETextField->setText(pl->getUWLEText());
 UWLETextField->setToolTip(tr("Enter the text for the Slip route Upper West to Lower East"));
 UWLETextField->setMaximumSize( QSize( UWLETextField->maximumSize().width(), UWLETextField->getPreferredSize().height()));

 LWUETextField->setText(pl->getLWUEText());
 LWUETextField->setToolTip(tr("Enter the text for the Slip route Lower West to Upper East"));
 LWUETextField->setMaximumSize( QSize(LWUETextField->maximumSize().width(), LWUETextField->getPreferredSize().height()));

 LWLETextField->setText(pl->getLWLEText());
 LWLETextField->setToolTip(tr("Enter the text for the Slip route Lower West to Lower East"));
 LWLETextField->setMaximumSize( QSize( LWLETextField->maximumSize().width(), LWLETextField ->getPreferredSize().height()));

 UWUETextField->setText(pl->getUWUEText());
 UWUETextField->setToolTip(tr("Enter the text for the Slip route Upper West to Upper East"));
 UWUETextField->setMaximumSize( QSize( UWUETextField->maximumSize().width(), UWUETextField->getPreferredSize().height()));

 if (l->getTurnoutType()==SlipTurnoutIcon::DOUBLESLIP)
 {
  textLWLE->setVisible(true);
  textUWUE->setVisible(true);
 }
 else if (l->getTurnoutType()==SlipTurnoutIcon::THREEWAY)
 {
  textLWLE->setVisible(true);
  LWLETextField->setVisible(true);
  textUWUE->setVisible(false);
  UWUETextField->setVisible(false);
  textLWUE->setText(tr("Upper") + " = " + pl->getLWUEText());
  textUWLE->setText(tr("Middle") + " = " + pl->getUWLEText());
  textLWLE->setText(tr("Lower") + " = " + pl->getLWLEText());
  LWLETextField->setToolTip(tr("Enter the text for the 3-Way lower exit"));
  UWLETextField->setToolTip(tr("Enter the text for the 3-Way middle exit"));
  LWUETextField->setToolTip(tr("Enter the text for the 3-Way upper exit"));
 }
 else if(l->getTurnoutType()==SlipTurnoutIcon::SINGLESLIP)
 {
  if(l->getSingleSlipRoute())
  { // upper west to upper east
   textUWUE->setVisible(true);
   UWUETextField->setVisible(true);
   textLWLE->setVisible(false);
   LWLETextField->setVisible(false);
  }
  else
  { // lower west to lower east
   textUWUE->setVisible(false);
   UWUETextField->setVisible(false);
   textLWLE->setVisible(true);
   LWLETextField->setVisible(true);
  }
 }
 else
 { // SCISSORS
  textUWUE->setVisible(true);
  UWUETextField->setVisible(true);
  textLWLE->setVisible(true);
  LWLETextField->setVisible(true);
 }

 okButton->setText(tr("Set"));
 okButton->setVisible(true);
 okButton->setToolTip(tr("Press to change the text"));

 cancelButton->setText(tr("Cancel"));
 cancelButton->setVisible(true);
 cancelButton->setToolTip(tr("Press to cancel changes"));

 setTitle(tr("SetTurnoutText"));
 QGridLayout* g;
 QLayout* layout = getContentPane()->layout();
 delete layout;
    getContentPane()->setLayout(g = new QGridLayout());

    resize(400, 220);
    setMinimumHeight(220);

    addItem(lableName, 0, 0);
    addItem(nameText, 1, 0);
    addItem(textLWUE, 0, 1);
    addItem(LWUETextField, 1, 1);

    addItem(textUWLE, 0, 2);
    addItem(UWLETextField, 1, 2);
    addItem(textLWLE, 0, 3);
    addItem(LWLETextField, 1, 3);
    addItem(textUWUE, 0, 4);
    addItem(UWUETextField, 1, 4);
    addItem(cancelButton, 0, 5);
    addItem(okButton, 1, 5);

    // setup buttons
    //addButtonAction(okButton);
    connect(okButton, SIGNAL(clicked()), this, SLOT(on_okButton()));
    //addButtonAction(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton()));
    pack();

}

/*private*/ void SlipTurnoutTextEdit::addItem(QWidget* c, int x, int y) {
    GridBagConstraints gc;// = GridBagConstraints();
    gc.gridx = x;
    gc.gridy = y;
    gc.weightx = 100.0;
    gc.weighty = 100.0;
    ((QGridLayout*)getContentPane()->layout())->addWidget(c, gc.gridy, gc.gridx, gc.rowSpan(), gc.colSpan());
}


/*public*/ void SlipTurnoutTextEdit::on_okButton()
{
 // save current values in case user cancels
 if (oldLWUE == INIT)
 {
    oldLWUE = pl->getLWUEText();
    oldUWLE = pl->getUWLEText();
    oldLWLE = pl->getLWLEText();
    oldUWUE = pl->getUWUEText();
 }
 pl->setUWLEText(UWLETextField->text());
 pl->setLWUEText(LWUETextField->text());
 pl->setLWLEText(LWLETextField->text());
 pl->setUWUEText(UWUETextField->text());
 textLWUE->setText(tr("Lower West ToUpper East") + " = " + pl->getLWUEText());
 textUWLE->setText(tr("Upper West To Lower East") + " = " + pl->getUWLEText());
 textLWLE->setText(tr("Lower West To Lower East") + " = " + pl->getLWLEText());
 textUWUE->setText(tr("Upper West To Upper East") + " = " + pl->getUWUEText());
 if (pl->getTurnoutType()==SlipTurnoutIcon::THREEWAY)
 {
    textLWUE->setText(tr("Upper") + " = " + pl->getLWUEText());
    textUWLE->setText(tr("Middle") + " = " + pl->getUWLEText());
    textLWLE->setText(tr("Lower") + " = " + pl->getLWLEText());
    /*textLWUE->setText(tr("Upper") + " = " + pl->getLWLEText());
    textUWLE->setText(tr("Middle") + " = " + pl->getLWUEText());
    textLWLE->setText(tr("Lower") + " = " + pl->getLWLEText());*/
 }
}
void SlipTurnoutTextEdit::on_cancelButton()
{
 if (oldLWUE != INIT)
 {
  pl->setUWLEText(oldUWLE);
  pl->setLWUEText(oldLWUE);
  pl->setLWLEText(oldLWLE);
  pl->setUWUEText(oldUWUE);
 }
 dispose();
}

