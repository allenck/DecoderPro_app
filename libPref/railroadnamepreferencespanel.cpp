#include "railroadnamepreferencespanel.h"
#include "jtextfield.h"
#include <QBoxLayout>
#include "jtitledseparator.h"
#include <QPushButton>
#include "jframe.h"
#include "flowlayout.h"
#include "QLabel"
#include "webserverpreferences.h"

//RailroadNamePreferencesPanel::RailroadNamePreferencesPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
///*public*/ class RailroadNamePreferencesPanel extends QWidget* implements PreferencesPanel {

/**
 *
 */
//private static final long serialVersionUID = -2483121076473347952L;
//static Logger log = LoggerFactory.getLogger(RailroadNamePreferencesPanel.class);

/*public*/ RailroadNamePreferencesPanel::RailroadNamePreferencesPanel(QWidget *parent) : QWidget(parent)
{
 parentFrame = (JFrame*)parent;
 preferences = WebServerPreferences::getDefault();
 initGUI();
 setGUI();
}

///*public*/ RailroadNamePreferencesPanel(JFrame f) {
//    this();
//    parentFrame = f;
//}

/*
 private void initComponents() {
 GroupLayout layout = new GroupLayout(this);
 this.setLayout(layout);
 layout.setAutoCreateGaps(true);
 layout.setAutoCreateContainerGaps(true);
 SequentialGroup group = layout.createSequentialGroup();
 group.addComponent(new JTitledSeparator(tr* ("TitleWebServerPreferences")));
 group.addGroup(webServerPreferences(layout));
 layout.setVerticalGroup(group);
 }
 */
/*private*/ void RailroadNamePreferencesPanel::initGUI()
{
 QVBoxLayout* thisLayout;
 this->setLayout(thisLayout = new QVBoxLayout); //(this, BoxLayout.PAGE_AXIS));
 thisLayout->addWidget(new JTitledSeparator(tr("Railroad Name")));
 thisLayout->addWidget(rrNamePanel());
}

/*
 private Group webServerPreferences(GroupLayout layout) {
 railroadName = new JTextField(preferences.getRailRoadName());
 railroadName.setToolTipText(tr* ("ToolTipRailRoadName"));
 railroadName.setColumns(30);
 ParallelGroup group = layout.createParallelGroup(GroupLayout.Alignment.CENTER);
 group.addComponent(new JLabel(tr* ("LabelRailRoadName")), GroupLayout.Alignment.TRAILING);
 group.addComponent(this.railroadName, GroupLayout.Alignment.LEADING);
 return group;
 }
 */
/*private*/ void RailroadNamePreferencesPanel::setGUI() {
}

/**
 * Show the save and cancel buttons if displayed in its own frame.
 */
/*public*/ void RailroadNamePreferencesPanel::enableSave()
{
 saveB->setVisible(true);
 cancelB->setVisible(true);
}

/**
 * set the local prefs to match the GUI Local prefs are independent from the
 * singleton instance prefs.
 *
 * @return true if set, false if values are unacceptable.
 */
/*private*/ bool RailroadNamePreferencesPanel::setValues() {
    bool didSet = true;
    preferences->setRailroadName(railroadName->text());
    return didSet;
}

/*public*/ void RailroadNamePreferencesPanel::storeValues()
{
 if (setValues())
 {
  preferences->save();

  if (parentFrame != NULL)
  {
   parentFrame->dispose();
  }
 }
}

/**
 * Update the singleton instance of prefs, then mark (isDirty) that the
 * values have changed and needs to save to xml file.
 */
/*protected*/ void RailroadNamePreferencesPanel::applyValues()
{
 if (setValues())
 {
  preferences->setIsDirty(true);
 }
}

/*protected*/ void RailroadNamePreferencesPanel::cancelValues()
{
 if (getTopLevelAncestor() != NULL)
 {
  ((JFrame*) getTopLevelAncestor())->setVisible(false);
 }
}

/*private*/ QWidget* RailroadNamePreferencesPanel::rrNamePanel()
{
 QWidget* panel = new QWidget();
 FlowLayout* panelLayout = new FlowLayout;
 panel->setLayout(panelLayout);
 railroadName = new JTextField(preferences->getRailroadName());
 railroadName->setToolTip(tr("Used by various JMRI network services."));
 railroadName->setColumns(30);
 panelLayout->addWidget(new QLabel(tr("Railroad Name")));
 panelLayout->addWidget(railroadName);
 return panel;
}

//@Override
/*public*/ QString RailroadNamePreferencesPanel::getPreferencesItem() {
    return tr("RAILROAD");
}

//@Override
/*public*/ QString RailroadNamePreferencesPanel::getPreferencesItemText() {
    return tr("Railroad Name");
}

//@Override
/*public*/ QString RailroadNamePreferencesPanel::getTabbedPreferencesTitle() {
    return "";
}

//@Override
/*public*/ QString RailroadNamePreferencesPanel::getLabelKey() {
    return "";
}

//@Override
/*public*/ QWidget* RailroadNamePreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool RailroadNamePreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString RailroadNamePreferencesPanel::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void RailroadNamePreferencesPanel::savePreferences() {
    this->storeValues();
}

//@Override
/*public*/ bool RailroadNamePreferencesPanel::isDirty() {
    return this->preferences->isDirty();
}

//@Override
/*public*/ bool RailroadNamePreferencesPanel::isRestartRequired() {
    return false;
}
/*public*/ QWidget* RailroadNamePreferencesPanel::getTopLevelAncestor()
{
 for(QObject* p = this; p != NULL; p = p->parent())
 {
  //if(p instanceof Window || p instanceof Applet)
     if(qobject_cast<JFrame*>(p)!=NULL)
  {
   return (QWidget*)p;
  }
 }
 return NULL;
}

/*public*/ QString RailroadNamePreferencesPanel::className() {return "RailroadNamePreferencesPanel";}
