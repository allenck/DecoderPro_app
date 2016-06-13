#include "tabbedpreferencesframe.h"
#include "instancemanager.h"
#include "tabbedpreferences.h"
#include <QBoxLayout>

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

 layout->addWidget(InstanceManager::tabbedPreferencesInstance());
 addHelpMenu("package.apps.TabbedPreferences", true);
 resize(800,800);
}

/*public*/ void TabbedPreferencesFrame::gotoPreferenceItem(QString item,QString sub){
    InstanceManager::tabbedPreferencesInstance()->gotoPreferenceItem(item, sub);
}
