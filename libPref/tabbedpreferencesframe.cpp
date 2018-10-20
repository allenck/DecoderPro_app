#include "tabbedpreferencesframe.h"
#include "instancemanager.h"
#include "tabbedpreferences.h"
#include <QBoxLayout>
#include <QMessageBox>
#include "preferencespanel.h"
#include "shutdownmanager.h"

//TabbedPreferencesFrame::TabbedPreferencesFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Provide access to the various tables via a
 * listed pane.
 * <P>
 * @author	Kevin Dickerson   Copyright 2010
 * @version $Revision: 28013 $
 */
// /*public*/ class TabbedPreferencesFrame extends jmri.util.JmriJFrame {

/**
 *
 */
// private static final long serialVersionUID = 4861869203791661041L;

/*public*/ QString TabbedPreferencesFrame::getTitle()
{
 return ((TabbedPreferences*)InstanceManager::getDefault("TabbedPreferences"))->getTitle();
}

/*public*/ bool TabbedPreferencesFrame::isMultipleInstances() { return true; }

/*static*/ bool TabbedPreferencesFrame::init = false;
/*static*/ int TabbedPreferencesFrame::lastdivider;

/*public*/ TabbedPreferencesFrame::TabbedPreferencesFrame(QWidget *parent)
    : JmriJFrame(parent)
{
 QWidget* centralWidget = new QWidget;
 setCentralWidget(centralWidget);
 QVBoxLayout* layout = new QVBoxLayout;
 centralWidget->setLayout(layout);
 setWindowTitle(getTabbedPreferences()->getTitle());

 layout->addWidget(getTabbedPreferences());
 addHelpMenu("package.apps.TabbedPreferences", true);
 resize(800,800);
}

/*public*/ void TabbedPreferencesFrame::gotoPreferenceItem(QString item,QString sub){
    getTabbedPreferences()->gotoPreferenceItem(item, sub);
}

//@Override
/*public*/ void TabbedPreferencesFrame::windowClosing(QCloseEvent* /*e*/)
{
 ShutDownManager* sdm = (ShutDownManager*)InstanceManager::getNullableDefault("ShutDownManager");
 if (!getTabbedPreferences()->isPreferencesValid() && (sdm == NULL || !sdm->isShuttingDown()))
 {
  for (PreferencesPanel* panel : getTabbedPreferences()->getPreferencesPanels()->values())
  {
   if (!panel->isPreferencesValid())
   {
    switch(QMessageBox::question(this, tr("Unsaved Changes"), tr("There are unsaved changes to this panel. Do you wish to cloase?"), QMessageBox::Yes |QMessageBox::No | QMessageBox::Cancel))
    {
     case QMessageBox::Yes:
      // save preferences
      getTabbedPreferences()->savePressed(getTabbedPreferences()->invokeSaveOptions());
      break;
     case QMessageBox::No:
      // do nothing
      break;
     case QMessageBox::Cancel:
     default:
      // abort window closing
      return;
    }
   }
  }
 }
 this->setVisible(false);
}
/**
 * Ensure a TabbedPreferences instance is always available.
 *
 * @return the default TabbedPreferences instance, creating it if needed
 */
/*private*/ TabbedPreferences* TabbedPreferencesFrame::getTabbedPreferences()
{
// return InstanceManager.getOptionalDefault(TabbedPreferences.class).orElseGet(() -> {
//     return InstanceManager.setDefault(TabbedPreferences.class, new TabbedPreferences());
// });
 TabbedPreferences* tpc = (TabbedPreferences*)InstanceManager::getOptionalDefault("TabbedPreferences");
 if(tpc == NULL)
 {
  tpc = (TabbedPreferences*)InstanceManager::setDefault("TabbedPreferences", (QObject*)new TabbedPreferences());
 }
 return tpc;
}
