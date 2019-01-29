#include "lntcppreferencespanel.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "performactionmodel.h"
#include <QVBoxLayout>
#include "flowlayout.h"

/**
 * Provide access to the LocoNet over TCP server settings.
 *
 * @author Randall Wood (C) 2017
 */
//@ServiceProvider(service = PreferencesPanel.class)
// /*public*/ class LnTcpPreferencesPanel extends JPanel implements PreferencesPanel {


/*public*/ LnTcpPreferencesPanel::LnTcpPreferencesPanel(QWidget* parent) : QWidget(parent)
{
 startupActionPosition = -1;
 preferences = (LnTcpPreferences*)InstanceManager::getOptionalDefault("LnTcpPreferences");
 if(preferences == NULL)
 {
  preferences =  (LnTcpPreferences*)InstanceManager::setDefault("LnTcpPreferences", new LnTcpPreferences());
 }
 initComponents();
}

/*private*/ void LnTcpPreferencesPanel::initComponents() {
//    bindingGroup = new BindingGroup();
    port = new QSpinBox();
    portLabel = new QLabel();
    startup = new QCheckBox();

    //port.setModel(new SpinnerNumberModel(1234, 1, 65535, 1));
    port->setRange(1, 65535);
    port->setSingleStep(1);
    port->setValue(1234);
    //port.setEditor(new JSpinner.NumberEditor(port, "#"));
    port->setToolTip(tr("Port to use for LocoNet over TCP server (default 1234)")); // NOI18N

//    Binding binding = Bindings.createAutoBinding(AutoBinding.UpdateStrategy.READ_WRITE, preferences, ELProperty.create("${port}"), port, BeanProperty.create("value"));
//    bindingGroup.addBinding(binding);

    portLabel->setText(tr("Port")); // NOI18N
    portLabel->setToolTip(tr("Port to use for LocoNet over TCP server (default 1234)")); // NOI18N

    startup->setChecked(this->isStartupAction());
    startup->setText(tr("Start automatically with application")); // NOI18N
#if 0
    this->startupItemListener = (ItemEvent e) ->
    {
        this->startup->removeItemListener(this->startupItemListener);
        StartupActionsManager* manager = (StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager");
        if (this->startup->isChecked()) {
            PerformActionModel* model = new PerformActionModel();
            model->setClassName("LnTcpServerAction");
            if (this->startupActionPosition == -1 || this->startupActionPosition >= manager->getActions()->length()) {
                manager->addAction(model);
            } else {
                manager->setActions(this->startupActionPosition, model);
            }
        } else {
            manager->getActions("PerformActionModel").stream().filter((model) -> ("LnTcpServerAction" ==(model.getClassName()))).forEach((model) -> {
                this->startupActionPosition = Arrays.asList(manager->getActions()).indexOf(model);
                manager->removeAction(model);
            });
        }
        this->startup.addItemListener(this->startupItemListener);
    };

    this->startup->addItemListener(this->startupItemListener);
#else
  connect(startup, SIGNAL(clicked(bool)), this, SLOT(on_startup_clicked()));
#endif

#if 0
    GroupLayout layout = new GroupLayout(this);
    this->setLayout(layout);
    layout.setHorizontalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                    .addComponent(port, GroupLayout.PREFERRED_SIZE, 75, GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(portLabel, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addComponent(startup, GroupLayout.DEFAULT_SIZE, 388, Short.MAX_VALUE))
                    .addContainerGap())
    );
    layout.setVerticalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                            .addComponent(port, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                            .addComponent(portLabel))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(startup)
                    .addContainerGap(198, Short.MAX_VALUE))
    );
#else
    QVBoxLayout* thisLayout = new QVBoxLayout(this);
    QWidget* panel = new QWidget();
    FlowLayout* panelLayout = new FlowLayout(panel);
    panelLayout->addWidget(portLabel);
    panelLayout->addWidget(port);
    thisLayout->addWidget(panel);
    thisLayout->addWidget(startup);
#endif

    //bindingGroup.bind();
}

void LnTcpPreferencesPanel::on_startup_clicked()
{
 StartupActionsManager* manager = (StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager");
 if (this->startup->isChecked())
 {
  PerformActionModel* model = new PerformActionModel();
  model->setClassName("LnTcpServerAction");
  if (this->startupActionPosition == -1 || this->startupActionPosition >= manager->getActions()->length()) {
      manager->addAction(model);
  } else {
      manager->setActions(this->startupActionPosition, model);
  }
 }
 else
 {
//   manager->getActions("PerformActionModel").stream().filter((model) -> ("LnTcpServerAction" ==(model.getClassName()))).forEach((model) -> {
//         this->startupActionPosition = Arrays.asList(manager->getActions()).indexOf(model);
//         manager->removeAction(model);
//     }
  foreach(StartupModel* model, *manager->getActions("PerformActionModel"))
  {
    this->startupActionPosition= manager->getActions()->indexOf(model);
    manager->removeAction(model);
  }
 }
}

/*private*/ bool LnTcpPreferencesPanel::isStartupAction() {
//    return ((StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager"))->getActions("PerformActionModel").stream()
//            .anyMatch((model) -> (LnTcpServerAction.class.getName().equals(model.getClassName())));
 foreach(StartupModel* model, *((StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager"))->getActions("PerformActionModel"))
 {
  if(model->getName() == "LnTcpServerAction")
   return true;
 }
 return false;
}

//@Override
/*public*/ QString LnTcpPreferencesPanel::getPreferencesItem() {
    return tr("LOCONETSERVER");
}

//@Override
/*public*/ QString LnTcpPreferencesPanel::getPreferencesItemText() {
    return tr("LocoNet over TCP Server");
}

//@Override
/*public*/ QString LnTcpPreferencesPanel::getTabbedPreferencesTitle() {
    return tr("LocoNet over TCP Server");
}

//@Override
/*public*/ QString LnTcpPreferencesPanel::getLabelKey() {
    return NULL;
}

//@Override
/*public*/ QWidget* LnTcpPreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool LnTcpPreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString LnTcpPreferencesPanel::getPreferencesTooltip() {
    return NULL;
}

//@Override
/*public*/ void LnTcpPreferencesPanel::savePreferences() {
    this->preferences->savePreferences();
}

//@Override
/*public*/ bool LnTcpPreferencesPanel::isDirty() {
    return this->preferences->isDirty();
}

//@Override
/*public*/ bool LnTcpPreferencesPanel::isRestartRequired() {
    return this->preferences->isRestartRequired();
}

//@Override
/*public*/ bool LnTcpPreferencesPanel::isPreferencesValid() {
    return this->preferences->isPreferencesValid();
}

/*public*/ QString LnTcpPreferencesPanel::className() {return "LnTcpPreferencesPanel";}
