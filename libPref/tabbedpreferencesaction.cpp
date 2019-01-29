#include "tabbedpreferencesaction.h"
#include "jmripanel.h"
#include "instancemanager.h"
#include "tabbedpreferences.h"
#include "windowinterface.h"

//TabbedPreferencesAction::TabbedPreferencesAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Tabbed Preferences Action for dealing with all the preferences in a single view
 * with a list option to the left hand side.
 * <P>
 * @author	Kevin Dickerson   Copyright (C) 2009
 * @version	$Revision: 28013 $
 */

// /*public*/ class TabbedPreferencesAction extends jmri.util.swing.JmriAbstractAction {

/**
 *
 */
//    private static final long serialVersionUID = 7214016766558164269L;

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param s
 * @param category
 * @param subCategory
 */
TabbedPreferencesFrame* TabbedPreferencesAction::f;

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QString category, QString subCategory, QObject* parent)
    : AbstractAction(s, parent)
{
 //super(s);
 common();
 preferencesItem = category;
 preferenceSubCat = subCategory;
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QString category, QObject* parent)
    : AbstractAction(s, parent)
{
 //super(s);
 common();
 preferencesItem = category;
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QObject* parent)
    : AbstractAction(s, parent)
{
 //super(s);
 common();
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QObject* parent)
    : AbstractAction(parent)
{ //this(Bundle.getMessage("MenuItemPreferences"));
 common();
 setText(tr("Preferences"));
}

///*public*/ TabbedPreferencesAction(String s, WindowInterface wi) {
//    super(s, wi);
//}

/*public*/TabbedPreferencesAction:: TabbedPreferencesAction(QString s, QIcon i, WindowInterface* wi)
    : AbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, WindowInterface* wi, QString category, QString subCategory)
    : AbstractAction(s,wi)
{
 //super(s, wi);
 common();
 preferencesItem = category;
 preferenceSubCat = subCategory;
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QIcon i, WindowInterface* wi, QString category)
    : AbstractAction(s, i, wi)
{
  //super(s, i, wi);
  common();
  preferencesItem = category;
}

void TabbedPreferencesAction::common()
{
 preferencesItem = "";
 preferenceSubCat = "";
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
/*static*/ bool TabbedPreferencesAction::inWait = false;

/*public*/ void TabbedPreferencesAction::actionPerformed()
{
 // create the JTable model, with changes for specific NamedBean
 // create the frame
 if(inWait)
 {
  log->info("We are already waiting for the preferences to be displayed");
  return;
 }

 if (f==NULL)
 {
  f = new TabbedPreferencesFrame();
//  {

//    /**
//     *
//     */
//  private static final long serialVersionUID = 400412053977528653L;
//  };
  TPRunnable* r = new TPRunnable(this);
//          /*public*/ void run() {
//            try {
//                setWait(true);
//                while(jmri.InstanceManager.tabbedPreferencesInstance().init()!=0x02){
//                    Thread.sleep(50);
//                }
//                SwingUtilities.updateComponentTreeUI(f);
//                showPreferences();
//            } catch (InterruptedException ex) {
//                Thread.currentThread().interrupt();
//                setWait(false);
//            }
//          }
//        };
//  QThread* thr = new QThread(r);
//  thr->start();
  connect(r, SIGNAL(waitChange(bool)), this, SLOT(setWait(bool)));
  connect(r, SIGNAL(showPreferences()), this, SLOT(showPreferences()));
  ((TabbedPreferences*)InstanceManager::getDefault("TabbedPreferences"))->init();
  r->start();
 }
 else
 {
  showPreferences();
 }
}
void TPRunnable::run()
{
 try
 {
  emit waitChange(true);
  while(((TabbedPreferences*)InstanceManager::getDefault("TabbedPreferences"))->init()!=0x02)
  {
   QThread::sleep(50);
  }
  //SwingUtilities.updateComponentTreeUI(f);
  emit showPreferences();
 }
 catch (InterruptedException ex)
 {
  //Thread.currentThread().interrupt();
  emit waitChange(false);
 }
}


/*private*/ void TabbedPreferencesAction::showPreferences()
{
 // Update the GUI Look and Feel
 // This is needed as certain controls are instantiated
 // prior to the setup of the Look and Feel
 setWait(false);
 f->gotoPreferenceItem(preferencesItem, preferenceSubCat);
 f->adjustSize();

 f->setVisible(true);
}

/*synchronized*/ /*static*/ void TabbedPreferencesAction::setWait(bool boo)
{
 inWait = boo;
}

//@Override
/*public*/ void actionPerformed(ActionEvent* /*e*/)
{
 //actionPerformed();
}

void TabbedPreferencesAction::setTitle()
{ //Note required as sub-panels will set them
}

QString TabbedPreferencesAction::helpTarget()
{
 return "package.apps.TabbedPreferences";
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* makePanel()
{
 throw  IllegalArgumentException("Should not be invoked");
}
