#include "swingshutdowntask.h"
#include <QMessageBox>
#include <QPushButton>

//SwingShutDownTask::SwingShutDownTask(QObject *parent) :
//    AbstractShutdownTask(parent)
//{
//}
/**
 * Provides a base for using Swing to ask if shutdown should
 * conditionally continue.
 * <p>
 * Sequence:
 * <ol>
 * <li>checkPromptNeeded determines if ready to shutdown. If so,
 * return ready.
 * <li>Issue a prompt, asking if the user wants to continue or do something else
 * <li>Recheck until something decided.
 * </ul>
 *
 * <p>
 * If no "action" name is provided, only the continue and cancel options are shown.
 *
 * @author Bob Jacobsen Copyright (C) 2008
 * @version $Revision: 22323 $
 */
///*public*/ class SwingShutDownTask extends AbstractShutDownTask {

/**
 * Constructor specifies the warning message
 * and action to take
 */
/*public*/ SwingShutDownTask::SwingShutDownTask(QString name, QString warning, QString action, QWidget* component, QObject *parent)
 : AbstractShutDownTask(name, parent)
{
    //super(name);
    this->component = component;
    this->warning = warning;
    this->action = action;
    log = new Logger("SwingShutDownTask");
}


/**
 * Take the necessary action.
 * @return true if the shutdown should continue, false
 * to abort.
 */
/*public*/ bool SwingShutDownTask::execute()
{
 while (!checkPromptNeeded())
 {
    // issue prompt
//    QObjectList* possibleValues;
//    if (action!=NULL) possibleValues = new QObjectList {tr("ButtonContinue"),
//                               tr("ButtonAbort"),
//                               action};
//    else possibleValues = new QObjectList {tr("ButtonContinue"),
//                               tr("ButtonAbort")};

//    int selectedValue = JOptionPane.showOptionDialog(component,
//                                                     warning,
//                                                     tr("ShutDownWarningTitle"),
//                                                     JOptionPane.DEFAULT_OPTION,
//                                                     JOptionPane.WARNING_MESSAGE, NULL,
//                                                     possibleValues, possibleValues[possibleValues.length-1]);
//  int selectedValue = QMessageBox::warning(0, tr("Program Quitting"), warning, QMessageBox::Cancel | QMessageBox::Close);
//    if (selectedValue == 1) {
//        // abort quit
//        return false;
//    } else if (selectedValue == 0) {
//        // quit anyway
//        return true;
//    } else if (selectedValue == 2) {
//        // take action and try again
//        return doPrompt();
//    } else if (selectedValue == -1) {
//        // dialog window closed
//        return doClose();
  QMessageBox msgBox;

  msgBox.setText(warning);
  QPushButton *abortButton = msgBox.addButton(tr("Cancel Quit"), QMessageBox::RejectRole);
  QPushButton *continueButton = msgBox.addButton(tr("Continue Quitting"),QMessageBox::AcceptRole);
  QPushButton *actionButton;
  if(action != "")
   actionButton = msgBox.addButton(action, QMessageBox::ActionRole);
  msgBox.exec();
  if(msgBox.clickedButton() == (QAbstractButton*)abortButton)
  { // abort quit
    return false;
  }
  else if (msgBox.clickedButton() == (QAbstractButton*)continueButton)
  { // quit anyway
        return true;
  }
  else if( action != "" && msgBox.clickedButton() == (QAbstractButton*)actionButton)
  {
   // take action and try again
   return doPrompt();
  }
  else
  {
   // unexpected value, log but continue
   log->error("unexpected selection: "+msgBox.clickedButton()->text());
   return true;
  }
 }
 // break out of loop when ready to continue
 return true;
}


/**
 * Provide a subclass-specific check as to whether it's
 * OK to shutdown.  If not, issue a prompt before continuing.
 * Default implementation never passes, causing message to be emitted.
 * @return true if ready to shutdown, and no prompt needed. false to present dialog
 * before shutdown proceeds
 */
/*protected*/ bool SwingShutDownTask::checkPromptNeeded() {
    return false;
}

/**
 * Provide a subclass-specific method to handle the
 * request to fix the problem. This is a dummy implementation,
 * intended to be overloaded.
 * @return true if ready to shutdown, false to end shutdown
 */
/*protected*/ bool SwingShutDownTask::doPrompt() {
    return true;
}

/**
 * Provide a subclass-specific method to handle the case
 * where the user has chosen the close window option.
 * @return true if ready to shutdown, false to end shutdown
 */
/*protected*/ bool SwingShutDownTask::doClose() {
    return true;
}
