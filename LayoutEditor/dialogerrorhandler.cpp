#include "dialogerrorhandler.h"
#include "errormemo.h"
#include "instancemanager.h"
#include "jmriuserpreferencesmanager.h"

DialogErrorHandler::DialogErrorHandler(QObject *parent) :
    ErrorHandler(parent)
{
}
/**
 * Swing dialog for reporting errors while loading. Shows each one, could save
 * until end if needed.
 *
 * @author Bob Jacobsen Copyright (c) 2010
 * @version $Revision: 24834 $
 */
///*public*/ class DialogErrorHandler extends jmri.configurexml.ErrorHandler {

/**
 * Handle error by formatting and putting up a dialog box
 */
/*public*/ void DialogErrorHandler::handle(ErrorMemo* e)
{
 // first, send to log
 ErrorHandler::handle(e);

 try
 {
  // then do dialog
  QString m = "<html>" + e->description;
  if (e->systemName != "")
  {
   m += " System name \"" + e->systemName + "\"";
  }
  if (e->userName != "" && e->userName!=(""))
  {
   m += "<br> User name \"" + e->userName + "\"";
  }
  if (e->operation != "")
  {
    m += "<br> while " + e->operation;
  }
  if (e->adapter != NULL)
  {
   m += "<br> in adaptor of type " + QString(e->adapter->metaObject()->className());
  }
  //if (e->exception != NULL)
  {
    m += "<br> Exception: " + e->exception->getMessage();
  }
  m += "</html>";

  ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
            showErrorMessage("Error during " + e->title, m, e->description, "", true, false);
} catch (HeadlessException ex)
 {
  // silently do nothig - we can't display a dialog and have already
  // logged the error
 }
}

/**
 * Do nothing at end, already displayed
 */
/*public*/ void DialogErrorHandler::done() {
}
