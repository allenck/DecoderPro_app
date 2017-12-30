#include "tabbedpreferencesframe.h"
#include "instancemanager.h"
#include "tabbedpreferences.h"
#include <QBoxLayout>
#include <QMessageBox>

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
 return InstanceManager::tabbedPreferencesInstance()->getTitle();
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
 setWindowTitle(InstanceManager::tabbedPreferencesInstance()->getTitle());

 layout->addWidget(InstanceManager::tabbedPreferencesInstance());
 addHelpMenu("package.apps.TabbedPreferences", true);
 resize(800,800);
}

/*public*/ void TabbedPreferencesFrame::gotoPreferenceItem(QString item,QString sub){
    InstanceManager::tabbedPreferencesInstance()->gotoPreferenceItem(item, sub);
}

//@Override
/*public*/ void TabbedPreferencesFrame::windowClosing(QCloseEvent* /*e*/)
{
 if (InstanceManager::tabbedPreferencesInstance()->isDirty())
 {
  //     switch (JOptionPane.showConfirmDialog(this,
  //             Bundle.getMessage("UnsavedChangesMessage", InstanceManager.tabbedPreferencesInstance().getTitle()), // NOI18N
  //             Bundle.getMessage("UnsavedChangesTitle"), // NOI18N
  //             JOptionPane.YES_NO_CANCEL_OPTION,
  //             JOptionPane.QUESTION_MESSAGE)) {
  //         case JOptionPane.YES_OPTION:
  //             // save preferences
  //             InstanceManager.tabbedPreferencesInstance().savePressed(InstanceManager.tabbedPreferencesInstance().invokeSaveOptions());
  //             break;
  //         case JOptionPane.NO_OPTION:
  //             // do nothing
  //             break;
  //         case JOptionPane.CANCEL_OPTION:
  //         default:
  //             // abort window closing
  //             return;
  //     }
  switch(QMessageBox::question(this, tr("Unsaved Changes"), tr("There are unsaved changes to this panel. Do you wish to cloase?"), QMessageBox::Yes |QMessageBox::No | QMessageBox::Cancel))
  {
   case QMessageBox::Yes:
       // save preferences
       InstanceManager::tabbedPreferencesInstance()->savePressed(InstanceManager::tabbedPreferencesInstance()->invokeSaveOptions());
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
 this->setVisible(false);
}
