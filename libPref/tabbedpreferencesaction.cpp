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

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QString category, QString subCategory, QObject* parent)
    : JmriAbstractAction(s, parent)
{
 //super(s);
 common();
 preferencesItem = category;
 preferenceSubCat = subCategory;
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QString category, QObject* parent)
    : JmriAbstractAction(s, parent)
{
 //super(s);
 common();
 preferencesItem = category;
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QObject* parent)
    : JmriAbstractAction(s, parent)
{
 //super(s);
 common();
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QObject* parent)
    : JmriAbstractAction(parent)
{ //this(Bundle.getMessage("MenuItemPreferences"));
 common();
 setText(tr("Preferences"));
}

///*public*/ TabbedPreferencesAction(String s, WindowInterface wi) {
//    super(s, wi);
//}

/*public*/TabbedPreferencesAction:: TabbedPreferencesAction(QString s, QIcon i, WindowInterface* wi)
    : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, WindowInterface* wi, QString category, QString subCategory)
    : JmriAbstractAction(s,wi)
{
 //super(s, wi);
 common();
 preferencesItem = category;
 preferenceSubCat = subCategory;
}

/*public*/ TabbedPreferencesAction::TabbedPreferencesAction(QString s, QIcon i, WindowInterface* wi, QString category)
    : JmriAbstractAction(s, i, wi)
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

/*public*/ void TabbedPreferencesAction::actionPerformed()
{
    TabbedPreferencesFrame* f = (TabbedPreferencesFrame*)InstanceManager::getOptionalDefault("TabbedPreferencesFrame");// .orElseGet(() -> {
    if(f == nullptr)
        InstanceManager::setDefault("TabbedPreferencesFrame", f = new TabbedPreferencesFrame());
//    }//);

    showPreferences(f);
}

/*private*/ void TabbedPreferencesAction::showPreferences(TabbedPreferencesFrame* f)
{
    // Update the GUI Look and Feel
    // This is needed as certain controls are instantiated
    // prior to the setup of the Look and Feel

    // might not be a preferences item set yet
    if (preferencesItem != nullptr)
        f->gotoPreferenceItem(preferencesItem, preferenceSubCat);

    f->pack();

    f->setVisible(true);
}

//@Override
/*public*/ void TabbedPreferencesAction::actionPerformed(ActionEvent* /*e*/)
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
/*public*/ JmriPanel* TabbedPreferencesAction::makePanel()
{
 throw  IllegalArgumentException("Should not be invoked");
}
