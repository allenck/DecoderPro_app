#include "managerdefaultsconfigpane.h"
#include <QBoxLayout>
#include <QButtonGroup>
#include <QBoxLayout>
#include "managerdefaultselector.h"
#include "systemconnectionmemo.h"
#include <QLabel>
#include <QGridLayout>
#include <QRadioButton>
#include "instancemanager.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"

//ManagerDefaultsPane::ManagerDefaultsPane(QWidget *parent) :
//    PreferencesPanel(parent)
//{
//}

/**
 * Provide GUI to configure InstanceManager defaults.
 * <P>
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @version	$Revision: 28430 $
 * @since 2.9.5
 */
// /*public*/ class ManagerDefaultsConfigPane extends JmriPanel implements PreferencesPanel {

/**
 *
 */
//private static final long serialVersionUID = 4382220076212974325L;
//private static final ResourceBundle rb = ResourceBundle.getBundle("apps.AppsConfigBundle");

/*public*/ ManagerDefaultsConfigPane::ManagerDefaultsConfigPane(QWidget *parent)
    : JmriPanel(parent)
{
 setObjectName("ManagerDefaultsConfigFile");
 dirty = false;
 setLayout(thisLayout = new QVBoxLayout);//(this, BoxLayout.Y_AXIS));

 matrix = new QWidget();
 matrix->setObjectName("matrix");
 matrixLayout = new QGridLayout(matrix);
 thisLayout->addWidget(matrix);
//  manager.addPropertyChangeListener((PropertyChangeEvent e) -> {
//        if (e.getPropertyName().equals("Updated")) {
//            update();
//        }
//    });
 ManagerDefaultSelector* mgr =(ManagerDefaultSelector*) InstanceManager::getDefault("ManagerDefaultSelector");
 connect(mgr->propertyChangeSupport, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 update();
}

ManagerDefaultsConfigPane::~ManagerDefaultsConfigPane() {}

ManagerDefaultsConfigPane::ManagerDefaultsConfigPane(const ManagerDefaultsConfigPane&) : PreferencesPanel() {}

void ManagerDefaultsConfigPane::propertyChange(PropertyChangeEvent * e)
{
 if (e->getPropertyName()==("Updated"))
 {
  update();
 }
}

/**
 * Invoke when first displayed to load and present options
 */
/*public*/ void ManagerDefaultsConfigPane::update()
{
 //matrix.removeAll();
 if(matrixLayout != NULL)
 {
  QObjectList ol = matrixLayout->children();
  foreach(QObject* o, ol)
  {
   if(qobject_cast<QWidget*>(o) != NULL)
   {
    matrix->layout()->removeWidget((QWidget*)o);
    o->deleteLater();
   }
  }
//  matrixLayout->deleteLater();
//  matrixLayout = NULL;
 }

 // this doesn't find non-migrated systems, how do we handle that eventually?
 QObjectList* connList = InstanceManager::getList("SystemConnectionMemo");
 if (!connList->isEmpty())
 {
  reloadConnections(*connList);
 }
 else
 {
  matrixLayout->addWidget(new QLabel("No new-form system connections configured"));
 }
}

void ManagerDefaultsConfigPane::reloadConnections(QObjectList connList)
{
 log->debug(" reloadConnections");
 ManagerDefaultSelector* manager = (ManagerDefaultSelector*) InstanceManager::getDefault("ManagerDefaultSelector");
 int row = 0;
 int col = 0;
 if(matrixLayout == NULL)
  matrix->setLayout(matrixLayout = new QGridLayout); //(connList.size() + 1, ManagerDefaultSelector.instance.knownManagers.length + 1));
 matrixLayout->addWidget(new QLabel(""), row, col++);


 foreach (ManagerDefaultSelector::Item item, manager->knownManagers)
 {
  matrixLayout->addWidget(new QLabel(item.typeName), row, col++);
 }
 row++;
 col = 1;
 groups = QVector<QButtonGroup*>(manager->knownManagers.length());
 for (int i = 0; i <  manager->knownManagers.length(); i++)
 {
  groups.replace(i, new QButtonGroup());
 }
 for (int x = 0; x < connList.size(); x++)
 {
  SystemConnectionMemo* memo = (SystemConnectionMemo*)connList.at(x);
//  // ACK hack to hanle corrupt programmerManager pointer
//  if(qobject_cast<LocoNetSystemConnectionMemo*>(memo))
//  {
//   qobject_cast<LocoNetSystemConnectionMemo*>(memo)->resetProgrammer();
//  }
  QString name = memo->getUserName();
  matrixLayout->addWidget(new QLabel(name));
  int i = 0;
  foreach (ManagerDefaultSelector::Item item, manager->knownManagers)
  {
   if (memo->provides(item.managerClass))
   {
    QRadioButton* r = new SelectionButton(name, item.managerClass, this);
    matrixLayout->addWidget(r, row, col++);
    groups[i]->addButton(r);
    if (x == connList.size() - 1 && manager->getDefault(item.managerClass) == NULL) {
     r->setChecked(true);
    }
   }
   else
   {
    // leave a blank
    QRadioButton* r = new QRadioButton();
    r->setEnabled(false);
    matrixLayout->addWidget(r, row, col++);
   }
   i++; //we need to increment 'i' as we are going onto the next group even if we added a blank button
  }
  row++;
  col = 1;
 }
 //revalidate();
 //update();
}



//@Override
/*public*/ QString ManagerDefaultsConfigPane::getPreferencesItem() {
    return "DEFAULTS"; // NOI18N
}

//@Override
/*public*/ QString ManagerDefaultsConfigPane::getPreferencesItemText() {
    return tr("Defaults"); // NOI18N
}

//@Override
/*public*/ QString ManagerDefaultsConfigPane::getTabbedPreferencesTitle() {
    return tr("TabbedLayoutDefaults"); // NOI18N
}

//@Override
/*public*/ QString ManagerDefaultsConfigPane::getLabelKey() {
    return tr("Set connection defaults here; may have to save and restart to see all choices"); // NOI18N
}

//@Override
/*public*/ QWidget* ManagerDefaultsConfigPane::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool ManagerDefaultsConfigPane::isPersistant() {
    return true;
}

//@Override
/*public*/ QString ManagerDefaultsConfigPane::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void ManagerDefaultsConfigPane::savePreferences() {
    // do nothing - the persistant manager will take care of this
}

//@Override
/*public*/ bool ManagerDefaultsConfigPane::isDirty() {
    return this->dirty;
}

//@Override
/*public*/ bool ManagerDefaultsConfigPane::isRestartRequired() {
    return this->isDirty();
}

/**
 * Captive class to track changes
 */
//static class SelectionButton extends JRadioButton {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -2572336492673634333L;

    SelectionButton::SelectionButton(QString name, QString managerClass, ManagerDefaultsConfigPane* pane)
    {
     //super();
     this->managerClass = managerClass;
     this->name = name;
     this->pane = pane;
ManagerDefaultSelector* manager = (ManagerDefaultSelector*) InstanceManager::getDefault("ManagerDefaultSelector");
     if (name == ( manager->getDefault(managerClass)))
     {
      QRadioButton::setChecked(true);
     }

//        addActionListener((ActionEvent e) -> {
//            if (isSelected()) {
//                ManagerDefaultSelector.instance.setDefault(SelectionButton.this.managerClass, SelectionButton.this.name);
//                pane.dirty = true;
//            }
//        });
     connect(this, SIGNAL(toggled(bool)), this, SLOT(On_toggled(bool)));
    }

    //@Override
    /*public*/ void SelectionButton::setSelected(bool t) {
        QRadioButton::setChecked(t);
        ManagerDefaultSelector* manager = (ManagerDefaultSelector*) InstanceManager::getDefault("ManagerDefaultSelector");
        if (t) {
             manager->setDefault(this->managerClass, this->name);
        }
    }
    void SelectionButton::On_toggled(bool t)
    {
     if (t)
     {
      ManagerDefaultSelector* manager = (ManagerDefaultSelector*) InstanceManager::getDefault("ManagerDefaultSelector");
       manager->setDefault(this->managerClass, this->name);
      pane->dirty = true;
     }
    }
//};

/*public*/ QString ManagerDefaultsConfigPane::className() {return "apps.ManagerDefaultsConfigPane";}

/*private*/ /*final*/ /*static*/ Logger* ManagerDefaultsConfigPane::log = LoggerFactory::getLogger("ManagerDefaultsConfigPane");

