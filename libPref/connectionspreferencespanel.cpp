#include "connectionspreferencespanel.h"
#include "fileutil.h"
#include "imageicon.h"
#include "instancemanager.h"
#include "jmrixconfigpane.h"
#include <QBoxLayout>
#include <QPushButton>
#include "flowlayout.h"
#include <QCheckBox>
#include <QLabel>
#include "connectionstatus.h"
#include "tabbedpreferences.h"
#include <QMessageBox>
#include "exceptions.h"
#include <QTabBar>
#include <QToolButton>

//ConnectionPreferencesPanel::ConnectionPreferencesPanel(QWidget *parent) :
//    QTabWidget(parent)
//{
//}
/**
 *
 * @author Randall Wood <randall.h.wood@alexandriasoftware.com>
 */
// /*public*/ class ConnectionsPreferencesPanel extends JTabbedPane implements PreferencesPanel {

//    /*private*/ static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle"); // NOI18N
//    /*private*/ static final Logger log = LoggerFactory.getLogger(ConnectionsPreferencesPanel.class);


/*public*/ ConnectionsPreferencesPanel::ConnectionsPreferencesPanel(TabbedPreferences* preferences, QWidget* parent)
 : ManagingPreferencesPanel(parent)
{
 //super();
 common(preferences);
}
void ConnectionsPreferencesPanel::common(TabbedPreferences* preferences)
{
 setObjectName("ConnectionsPreferencesPanel");
 setMinimumSize(400,400);
 setContentsMargins(0,0,0,0);
 setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 QVBoxLayout* thisLayout = new QVBoxLayout;
 setLayout(thisLayout);
 //QWidget* panel = new QWidget;
 //QHBoxLayout* panelLayout = new QHBoxLayout;
 //panel->setLayout(panelLayout);
 tabWidget = new MyTabWidget();
 tabWidget->setMinimumSize(400,400);
 tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 //panelLayout->addWidget(tabWidget);
 //thisLayout->addWidget(panel);
 thisLayout->addWidget(tabWidget);
 log = new Logger("ConnectionPreferencesPanel");
 restartRequired = false;
  bDeleteFlag= false;

 configPanes = QList<JmrixConfigPane*>();

 this->preferences = preferences;
 deleteIconRollOver =  QIcon(":/resources/icons/misc/gui3/Delete16x16.png");
 deleteIcon =  QIcon(":/resources/icons/misc/gui3/Delete-bw16x16.png");
 ImageIcon* deleteImageIcon = new ImageIcon(QImage(":/resources/icons/misc/gui3/Delete-bw16x16.png"));
 deleteButtonSize =  QSize(
            deleteImageIcon->getIconWidth() + 2,
            deleteImageIcon->getIconHeight() + 2);
 addIcon =  QIcon(":/resources/icons/misc/gui3/Add16x16.png");
 if (this->preferences != NULL)
 {
  QObjectList connList = InstanceManager::configureManagerInstance()
                ->getInstanceList("ConnectionConfig");
  if (!connList .isEmpty())
  {
   for (int x = 0; x < connList.size(); x++)
   {
    JmrixConfigPane* configPane = JmrixConfigPane::instance(x);
    addConnection(x, configPane);
   }
   newConnectionTab(); // added ACK
  }
  else
  {
   addConnection(0, JmrixConfigPane::createNewPanel());

   //this->addChangeListener(addTabListener);
   connect(tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(On_currentChanged(int)));
   newConnectionTab();
   tabWidget->setCurrentIndex(0);
  }
  connect(tabWidget, SIGNAL(tabBarClicked(int)), this, SLOT(On_currentChanged(int)));

 }
}

/*public*/ ConnectionsPreferencesPanel::ConnectionsPreferencesPanel(QWidget *parent)
    : ManagingPreferencesPanel(parent)
{
 common((TabbedPreferences*)InstanceManager::getDefault("TabbedPreferences"));
}

///*transient*/ ChangeListener* addTabListener = (ChangeEvent evt) {

void ConnectionsPreferencesPanel::On_currentChanged(int sel)
{
    // This method is called whenever the selected tab changes
//    JTabbedPane pane = (JTabbedPane) evt.getSource();
//    int sel = pane.getSelectedIndex();
 if (sel == -1)
 {
  addConnectionTab();
  return;
 }
 else
 {
   //QIcon icon = /*pane.getIconAt(sel);*/ tabIcon(sel);
   //if (icon == addIcon)
   QString _tabText = tabWidget->tabText(sel);
   if(_tabText == "" && !bDeleteFlag)
   {
    addConnectionTab();
    return;
   }
  }
 activeTab();
 bDeleteFlag = false;
}

/*public*/ ConnectionsPreferencesPanel::ConnectionsPreferencesPanel(const ConnectionsPreferencesPanel & other)
{
 this->preferences = other.preferences;
}

/*private*/ void ConnectionsPreferencesPanel::activeTab()
{
 for (int i = 0; i < tabWidget->count() - 1; i++)
 {
  //QWidget* panel = (QWidget) this->getTabComponentAt(i);
  QWidget* panel = tabWidget->widget(i);
  //panel.invalidate();
  //Component[] comp = panel.getComponents();
  QObjectList comp = panel->children();
  foreach (QObject* o, comp)
  {
   //if (c instanceof JButton)
   if(qobject_cast<QPushButton*>(o) != NULL)
   {
    QPushButton* c = (QPushButton*)o;
    if (i == tabWidget->currentIndex())
    {
     c->setVisible(true);
    }
    else
    {
     c->setVisible(false);
    }
   }
  }
 }
}

/*private*/ void ConnectionsPreferencesPanel::addConnection(int tabPosition, /*final*/ JmrixConfigPane* configPane)
{
 QWidget* p = new QWidget();
 QVBoxLayout* pLayout;
 p->setLayout(pLayout = new QVBoxLayout); //BorderLayout());
 pLayout->addWidget(configPane, 0, Qt::AlignCenter);

 QToolButton* tabCloseButton = new QToolButton();
 tabCloseButton->setIcon(deleteIcon);
 QString ss;
 tabCloseButton->setStyleSheet(ss = QString("QToolButton { border-image: url(%1) 2; } QToolButton:hover { border-image: url(%2) 2; }").arg(FileUtil::getExternalFilename("program:resources/icons/misc/gui3/Delete-bw16x16.png")).arg(FileUtil::getExternalFilename("program:resources/icons/misc/gui3/Delete16x16.png")));
 tabCloseButton->resize(deleteButtonSize);
 //tabCloseButton.setBorderPainted(false);
    //tabCloseButton.setRolloverIcon(deleteIconRollOver);
 tabCloseButton->setVisible(false);

 //QWidget* c = new QWidget();
 FlowLayout* cLayout = new FlowLayout;
 cLayout->setAlignment(Qt::AlignBottom);
 //c->setLayout(cLayout = new FlowLayout); //(FlowLayout.LEFT, 0, 0));
 /*final*/ QCheckBox* disable = new QCheckBox("Disable Connection");
 disable->setChecked(configPane->getDisabled());
   /* disable.addActionListener((ActionEvent e) -> {
        configPane.setDisabled(disable.isSelected());
    })*/;
 DisableCheckboxListener* dcl = new DisableCheckboxListener(configPane, disable);
 connect(disable, SIGNAL(toggled(bool)), dcl, SLOT(actionPerformed()));
 cLayout->addWidget(disable);
 pLayout->addLayout(cLayout, 0);// /*BorderLayout.SOUTH*/ Qt::AlignBottom);
 QString title;

 if (configPane->getConnectionName() != NULL)
 {
  title = configPane->getConnectionName();
 }
 else if ((configPane->getCurrentProtocolName() != NULL)
            && (configPane->getCurrentProtocolName()!=(
                    JmrixConfigPane::NONE)))
 {
  title = configPane->getCurrentProtocolName();
 }
 else
 {
  title = tr("Connection") + QString::number(tabPosition + 1);
  if (this->indexOfTab(title) != -1)
  {
   for (int x = 2; x < 12; x++)
   {
    title = tr("Connection")+ QString::number(tabPosition + 2);
    if (this->indexOfTab(title) != -1)
    {
     break;
    }
   }
  }
 }

 /*final*/ QWidget* tabTitle = new QWidget;//(new BorderLayout(5, 0));
 QVBoxLayout* tabTitleLayout = new QVBoxLayout;
 tabTitle->setLayout(tabTitleLayout);
 //tabTitle->setOpaque(false);
// p->setName(title);
 p->adjustSize();

 if (configPane->getDisabled())
 {
  title = "(" + title + ")";
 }

 QLabel* tabLabel = new QLabel(title);//, JLabel.LEFT);
 tabLabel->setAlignment(Qt::AlignLeft);
 tabTitleLayout->addWidget(tabLabel, 0, /*BorderLayout.WEST*/Qt::AlignLeft);
 tabTitleLayout->addWidget(tabCloseButton, 0, /*BorderLayout.EAST*/ Qt::AlignRight);

 this->configPanes.append(configPane);
 //int iTab = tabWidget->addTab(p, title);
 int iTab = tabWidget->insertTab(tabPosition, p, title);
 tabWidget->setTabButton(iTab, tabCloseButton);
    //this->setTabComponentAt(tabPosition, tabTitle);
 //tabWidget->insertTab(tabPosition,tabTitle, title);

//    tabCloseButton.addActionListener((ActionEvent e) -> {
//        removeTab(e, this->indexOfTabComponent(tabTitle));
//    });
 CloseButtonListener* cbl = new CloseButtonListener(tabPosition, this);
 connect(tabCloseButton, SIGNAL(clicked()), cbl, SLOT(actionPerformed()));

 tabWidget->setTabToolTip(tabPosition, title);


 if (ConnectionStatus::instance()->isConnectionOk(
            configPane->getCurrentProtocolInfo()))
 {
  //tabLabel.setForeground(Color.black);
     tabLabel->setStyleSheet("QLabel { color: black;} ");
 }
 else
 {
  //tabLabel.setForeground(Color.red);
  tabLabel->setStyleSheet("QLabel { color: red;} ");

 }
 if (configPane->getDisabled())
 {
  //tabLabel.setForeground(Color.ORANGE);
  tabLabel->setStyleSheet("QLabel { color: yellow; } ");
 }

 //preferences->getItems().append((PreferencesPanel*)configPane);
}

DisableCheckboxListener::DisableCheckboxListener(JmrixConfigPane *configPane, QCheckBox* checkBox)
{
 this->configPane = configPane;
 this->checkBox = checkBox;
}

void DisableCheckboxListener::actionPerformed(ActionEvent *)
{
 configPane->setDisabled(checkBox->isChecked());
}

CloseButtonListener::CloseButtonListener(int index, ConnectionsPreferencesPanel* parent)
{
 this->index = index;
    this->parent = parent;
}

void CloseButtonListener::actionPerformed(ActionEvent *)
{
 parent->removeTab(index);
}

void ConnectionsPreferencesPanel::addConnectionTab()
{
 int curTab = this->indexOfTab("");

 //this->removeTab(this->indexOfTab(""));
 tabWidget->removeTab(curTab);
 addConnection(configPanes.size(), JmrixConfigPane::createNewPanel());
 newConnectionTab();

}

/*private*/ void ConnectionsPreferencesPanel::newConnectionTab()
{
 int itab = tabWidget->addTab(new QWidget,  addIcon, "");
 tabWidget->setTabToolTip(itab, tr("Add New Connection"));
 tabWidget->setCurrentIndex(tabWidget->count() - 2);
 log->debug(tr("Tab count = %1").arg(tabWidget->count()));
}

/*private*/ void ConnectionsPreferencesPanel::removeTab(/*ActionEvent* e, */int x)
{
 int i;

 i = x;

 if (i != -1 )
 {
//        int n = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(
//                tr("MessageDoDelete"),
//                new Object[]{this->getTitleAt(i)}),
//                tr("MessageDeleteConnection"),
//                JOptionPane.YES_NO_OPTION);
//        if (n != JOptionPane.YES_OPTION) {
  bDeleteFlag = true;
  if(tabWidget->tabText(x) != "")
  {
   if(QMessageBox::question(NULL, tr("Delete Connection"), tr("Do you really want to delete connection %1?").arg(tabWidget->tabText(i)),QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
   {
    bDeleteFlag = false;
    return;
   }
  }
  JmrixConfigPane* configPane = this->configPanes.at(i);

  //this->removeChangeListener(addTabListener);
  //this->remove(i); // was x
  tabWidget->removeTab(i);
 //preferences->getItems().removeOne((PreferencesPanel*)configPane);
  try
  {
   JmrixConfigPane::dispose(configPane);
  }
  catch (NullPointerException ex)
  {
   log->error("Caught NULL Pointer Exception while removing connection tab");
  }
  this->configPanes.removeAt(i);
  if (tabWidget->count() == 1)
  {
   addConnectionTab();
  }
  if (x != 0)
  {
    tabWidget->setCurrentIndex(x - 1);
  }
  else
  {
   tabWidget->setCurrentIndex(0);
  }
  //this->addChangeListener(addTabListener);
  connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(On_currentChanged(int)));
 }
 activeTab();
}

//@Override
/*public*/ QString ConnectionsPreferencesPanel::getPreferencesItem() {
    return "CONNECTIONS"; // NOI18N
}

//@Override
/*public*/ QString ConnectionsPreferencesPanel::getPreferencesItemText() {
    return tr("Connections"); // NOI18N
}

//@Override
/*public*/ QString ConnectionsPreferencesPanel::getTabbedPreferencesTitle() {
    return NULL;
}

//@Override
/*public*/ QString ConnectionsPreferencesPanel::getLabelKey() {
    return NULL;
}

//@Override
/*public*/ QWidget* ConnectionsPreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool ConnectionsPreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString ConnectionsPreferencesPanel::getPreferencesTooltip() {
    return NULL;
}

//@Override
/*public*/ void ConnectionsPreferencesPanel::savePreferences() {
    // do nothing - this is a container for other preferences that maintain
    // their own state
}

//@Override
/*public*/ bool ConnectionsPreferencesPanel::isDirty() {
    //return this->configPanes.stream().anyMatch((panel) -> (panel.isDirty()));
 bool dirty = false;
 foreach (JmrixConfigPane* pane, configPanes)
 {
  if(pane->isDirty())
   dirty = true;
 }
 return dirty;
}

//@Override
/*public*/ bool ConnectionsPreferencesPanel::isRestartRequired() {
 bool brs = false;
 foreach (JmrixConfigPane* pane, configPanes)
 {
  if(pane->isRestartRequired())
   brs = true;
 }
    return this->restartRequired | brs;//            || this->configPanes.stream().anyMatch((panel) -> (panel.isRestartRequired()));

}

int ConnectionsPreferencesPanel::indexOfTab(QString text)
{
 for(int i=0; i < tabWidget->count(); i++)
 {
  if(tabWidget->tabText(i) == text) return i;
 }
 return -1;
}
MyTabWidget::MyTabWidget(QWidget *parent) : QTabWidget(parent) {}

void MyTabWidget::setTabButton(int iTab, QToolButton * button)
{
 tabBar()->setTabButton(iTab, QTabBar::RightSide, button);
}
//@Override
/*public*/ bool ConnectionsPreferencesPanel::isPreferencesValid()
{
//    return this.configPanes.stream().allMatch((panel) -> (panel.isPreferencesValid()));
 return true;  // TODO: figure out what allMactch means.
}

//@Override
/*public*/ QList<PreferencesPanel*>* ConnectionsPreferencesPanel::getPreferencesPanels() {
    return (QList<PreferencesPanel*>*)new QList<JmrixConfigPane*>(this->configPanes);
}
