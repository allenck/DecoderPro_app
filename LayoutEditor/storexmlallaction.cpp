#include "storexmlallaction.h"
#include "file.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "configuremanager.h"

//StoreXmlAllAction::StoreXmlAllAction(QObject *parent) :
//  StoreXmlConfigAction(parent)
//{
//}
/**
 * Store the entire JMRI status in an XML file.
 * <P>
 * See {@link jmri.ConfigureManager} for information on the various types of
 * information stored in configuration files.
 *
 * @author	Bob Jacobsen Copyright (C) 2002
 * @version	$Revision: 29359 $
 * @see jmri.jmrit.XmlFile
 */
// /*public*/ class StoreXmlAllAction extends StoreXmlConfigAction {

/**
 *
 */
//private static final long serialVersionUID = 2662912096519480927L;
//static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle");

/*public*/ StoreXmlAllAction::StoreXmlAllAction(QObject *parent) :
  StoreXmlConfigAction(tr("Store all ..."),parent)
{
 //this("Store all ...");
 log = new Logger("StoreXmlAllAction");
}

/*public*/ StoreXmlAllAction::StoreXmlAllAction(QString s, QObject *parent) :
  StoreXmlConfigAction(s, parent)
{
 //super(s);
 log = new Logger("StoreXmlAllAction");
}

/*public*/ void StoreXmlAllAction::actionPerformed(JActionEvent * /*e*/)
{
 File* file = StoreXmlConfigAction::getFileName(this->getAllFileChooser());
 if (file == NULL)
 {
  return;
 }

 // and finally store
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cm == NULL) {
     log->error("Failed to get default configure manager");
 }
 else
 {
  bool results =cm->storeAll(file);
  log->debug(results ? "store was successful" : "store failed");
  if (!results)
  {
//     JOptionPane.showMessageDialog(NULL,
//             rb.getString("PanelStoreHasErrors") + "\n"
//             + rb.getString("PanelStoreIncomplete") + "\n"
//             + rb.getString("ConsoleWindowHasInfo"),
//             rb.getString("PanelStoreError"), JOptionPane.ERROR_MESSAGE);
  QMessageBox::information(NULL,   tr("Errors experienced during store."),
             tr("The storing of your information is incomplete and may result in missing items")+"\n"
             +tr("The console window contains error details."));
  }
 }
}
