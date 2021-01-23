#include "connectionspreferencespanel.h"
#include "fileutil.h"
#include "imageicon.h"
#include "instancemanager.h"
#include "jmrixconfigpane.h"
#include <QBoxLayout>
#include "jbutton.h"
#include "flowlayout.h"
#include <QCheckBox>
#include <QLabel>
#include "connectionstatus.h"
#include "tabbedpreferences.h"
#include <QMessageBox>
#include "exceptions.h"
#include <QTabBar>
#include <QToolButton>
#include "configuremanager.h"
#include "loggerfactory.h"
#include "jtabbedpane.h"
#include "connectionconfigmanager.h"
#include "indexedpropertychangeevent.h"
#include "vptr.h"

/**
 *
 * @author Randall Wood <randall.h.wood@alexandriasoftware.com>
 */
// /*public*/ class ConnectionsPreferencesPanel extends JTabbedPane implements PreferencesPanel {

//    /*private*/ static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle"); // NOI18N
/*private*/ /*static*/ /*final*/ Logger* ConnectionsPreferencesPanel::log = LoggerFactory::getLogger("ConnectionsPreferencesPanel");


///*public*/ ConnectionsPreferencesPanel::ConnectionsPreferencesPanel(TabbedPreferences* preferences, QWidget* parent)
// : ManagingPreferencesPanel(parent)
//{
// //super();
// common(preferences);
//}

void ConnectionsPreferencesPanel::common(/*TabbedPreferences* preferences*/)
{
 setObjectName("ConnectionsPreferencesPanel");
 resize(400,400);
 //setContentsMargins(0,0,0,0);
 //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 // tabWidget->setMinimumSize(400,400);
 setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
 
 //this->preferences = preferences;
 deleteIconRollOver =  QIcon(":/resources/icons/misc/gui3/Delete16x16.png");
 deleteIcon =  QIcon(":/resources/icons/misc/gui3/Delete-bw16x16.png");
 ImageIcon* deleteImageIcon = new ImageIcon(QImage(":/resources/icons/misc/gui3/Delete-bw16x16.png"));
 deleteButtonSize =  QSize(
            deleteImageIcon->getIconWidth() + 2,
            deleteImageIcon->getIconHeight() + 2);
 addIcon =  QIcon(":/resources/icons/misc/gui3/Add16x16.png");
 ConnectionConfigManager* ccm = (ConnectionConfigManager*)InstanceManager::getDefault("ConnectionConfigManager");
 QVector<ConnectionConfig*> connections = ccm->getConnections();
 if (connections.length() != 0) {
     for (int i = 0; i < connections.length(); i++) {
         addConnection(i, JmrixConfigPane::createPanel(i));
     }
 } else {
     addConnection(0, JmrixConfigPane::createNewPanel());
 }
 ccm->addPropertyChangeListener(ConnectionConfigManager::CONNECTIONS, (PropertyChangeListener*)this); //(PropertyChangeEvent evt) -> {
//     int i = ((IndexedPropertyChangeEvent) evt).getIndex();
//     if (evt.getNewValue() == null
//             && i < configPanes.size()
//             && evt.getOldValue().equals(configPanes.get(i).getCurrentObject())) {
//         removeTab(null, i);
//     } else if (evt.getOldValue() == null) {
//         for (JmrixConfigPane pane : this.configPanes) {
//             if (pane.getCurrentObject() == null ) {
//                 log.error("did not expect pane.getCurrentObject()==null here for {} {} {}", i, evt.getNewValue(), configPanes);
//             } else if (pane.getCurrentObject().equals(evt.getNewValue())) {
//                 return; // don't add the connection again
//             }
//         }
//         addConnection(i, JmrixConfigPane.createPanel(i));
//     }
// });
 //this->addChangeListener(addTabListener);
 connect(this, SIGNAL(tabBarClicked(int)), this, SLOT(On_currentChanged(int)));
 newConnectionTab();
 this->setCurrentIndex(0);
}

void ConnectionsPreferencesPanel::propertyChange(PropertyChangeEvent* evt)
{
 int i = ((IndexedPropertyChangeEvent*) evt)->getIndex();
 QObject* pNewValue = VPtr<QObject>::asPtr(evt->getNewValue());
 QObject* pOldValue = VPtr<QObject>::asPtr(evt->getOldValue());

 log->debug(tr("PrefPanel ChangeListener of tab index i = %1 of %2 list").arg(i+1).arg(configPanes.size()));
 //if (evt.getNewValue() == null
 //        && i < configPanes.size()
 //        && evt.getOldValue().equals(configPanes.get(i).getCurrentObject())) {
 //    //removeTab(null, i); // called same method removeTab again, conn tab was already removed by the user click
 //} else
 if ((pOldValue == nullptr) && (pNewValue != nullptr)) {
     for (JmrixConfigPane* pane : this->configPanes) {
         if (pane->getCurrentObject() == nullptr ) {
             log->error(tr("did not expect pane.getCurrentObject()==null here for %1 %2 %3").arg(i).arg(pNewValue->objectName()).arg(configPanes.count()));
         } else if (pane->getCurrentObject() == (pNewValue)) {
             return; // don't add the connection again
         }
     }
     addConnection(i, JmrixConfigPane::createPanel(i));
 }
}

/*public*/ ConnectionsPreferencesPanel::ConnectionsPreferencesPanel(QWidget *parent)
    : ManagingPreferencesPanel(parent)
{
 common(/*(TabbedPreferences*)InstanceManager::getDefault("TabbedPreferences")*/);
}

///*transient*/ ChangeListener* addTabListener = (ChangeEvent evt) {

void ConnectionsPreferencesPanel::On_currentChanged(int sel)
{
 // This method is called whenever the selected tab changes
 JTabbedPane* pane = (JTabbedPane*)this->widget(sel);////(JTabbedPane) evt.getSource();
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
   QString _tabText = tabText(sel);
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
 //this->preferences = other.preferences;
}

/*private*/ void ConnectionsPreferencesPanel::activeTab()
{
 for (int i = 0; i < count() - 1; i++)
 {
  //QWidget* panel = (QWidget) this->getTabComponentAt(i);
  QWidget* panel = widget(i);
  //panel.invalidate();
  //Component[] comp = panel.getComponents();
  QObjectList comp = panel->children();
  foreach (QObject* o, comp)
  {
   //if (c instanceof JButton)
   if(qobject_cast<QPushButton*>(o) != NULL)
   {
    QPushButton* c = (QPushButton*)o;
    if (i == currentIndex())
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
 tabCloseButton->setStyleSheet(ss = QString("QToolButton { border-image: url(%1) 2; } QToolButton:hover { border-image: url(%2) 2; }").arg(FileUtil::getExternalFilename(":/resources/icons/misc/gui3/Delete-bw16x16.png")).arg(FileUtil::getExternalFilename(":/resources/icons/misc/gui3/Delete16x16.png")));
 tabCloseButton->resize(deleteButtonSize);
 //tabCloseButton.setBorderPainted(false);
 //tabCloseButton->setRolloverIcon(deleteIconRollOver);
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
 this->addTab(title, p);
 //int iTab = this->insertTab(tabPosition, p, title);
 setTabButton(count()-1, tabCloseButton);
    //this->setTabComponentAt(tabPosition, tabTitle);
 //tabWidget->insertTab(tabPosition,tabTitle, title);

//    tabCloseButton.addActionListener((ActionEvent e) -> {
//        removeTab(e, this->indexOfTabComponent(tabTitle));
//    });
 CloseButtonListener* cbl = new CloseButtonListener(tabPosition, this);
 connect(tabCloseButton, SIGNAL(clicked()), cbl, SLOT(actionPerformed()));

 setTabToolTip(tabPosition, title);


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

void DisableCheckboxListener::actionPerformed(JActionEvent *)
{
 configPane->setDisabled(checkBox->isChecked());
}

CloseButtonListener::CloseButtonListener(int index, ConnectionsPreferencesPanel* parent)
{
 this->index = index;
    this->parent = parent;
}

void CloseButtonListener::actionPerformed(JActionEvent *)
{
 parent->removeTab(index);
}

void ConnectionsPreferencesPanel::addConnectionTab()
{
 //this->removeTabAt(this->indexOfTab(addIcon));
 this->removeTabAt(this->indexOfTab(""));
 addConnection(configPanes.size(), JmrixConfigPane::createNewPanel());
 newConnectionTab();
}

/*private*/ void ConnectionsPreferencesPanel::newConnectionTab()
{
 this->addTab("", addIcon, new QWidget(), tr("Add New Connection"));
 this->setSelectedIndex(this->count() - 2);
 log->debug(tr("Tab count = %1").arg(count()));
}

/*private*/ void ConnectionsPreferencesPanel::removeTab(/*ActionEvent* e, */int x)
{
 int i;

 i = x;

 if (i != -1 )
 {
//        int n = JOptionPane::showConfirmDialog(NULL, MessageFormat.format(
//                tr("MessageDoDelete"),
//                new Object[]{this->getTitleAt(i)}),
//                tr("MessageDeleteConnection"),
//                JOptionPane.YES_NO_OPTION);
//        if (n != JOptionPane.YES_OPTION) {
  bDeleteFlag = true;
  if(tabText(x) != "")
  {
   if(QMessageBox::question(NULL, tr("Delete Connection"), tr("Do you really want to delete connection %1?").arg(tabText(i)),QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
   {
    bDeleteFlag = false;
    return;
   }
  }
  JmrixConfigPane* configPane = this->configPanes.at(i);

  //this->removeChangeListener(addTabListener);
  //this->remove(i); // was x
  removeTabAt(i);
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
  if (count() == 1)
  {
   addConnectionTab();
  }
  if (x != 0)
  {
    setCurrentIndex(x - 1);
  }
  else
  {
   setCurrentIndex(0);
  }
  //this->addChangeListener(addTabListener);
  connect(this, SIGNAL(currentChanged(int)), this, SLOT(On_currentChanged(int)));
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
 for(int i=0; i < this->count(); i++)
 {
  if(this->tabText(i) == text) return i;
 }
 return -1;
}

//MyTabWidget::MyTabWidget(QWidget *parent) : QTabWidget(parent) {}

//void MyTabWidget::setTabButton(int iTab, QToolButton * button)
//{
// tabBar()->setTabButton(iTab, QTabBar::RightSide, button);
//}
//@Override
/*public*/ bool ConnectionsPreferencesPanel::isPreferencesValid()
{
//    return this.configPanes.stream().allMatch((panel) -> (panel.isPreferencesValid()));
 bool bValid = true;
 foreach(JmrixConfigPane* panel, this->configPanes)
 {
  if(!panel->isPreferencesValid())
  {
   bValid = false;
   break;
  }
 }
 return bValid;
}

/*public*/ QString ConnectionsPreferencesPanel::className() {return "ConnectionsPreferencesPanel";}

//@Override
/*public*/ QList<PreferencesPanel*>* ConnectionsPreferencesPanel::getPreferencesPanels() {
    return (QList<PreferencesPanel*>*)new QList<JmrixConfigPane*>(this->configPanes);
}
