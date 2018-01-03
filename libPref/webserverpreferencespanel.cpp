#include "webserverpreferencespanel.h"
#include "webserverpreferences.h"
#include "instancemanager.h"
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QBoxLayout>
#include "startupactionsmanager.h"
#include "performactionmodel.h"
#include "startupmodel.h"

///*public*/ class WebServerPreferencesPanel extends JPanel implements PreferencesPanel {


/*public*/ WebServerPreferencesPanel::WebServerPreferencesPanel(QWidget* parent) : PreferencesPanel(parent) {
 startupActionPosition = -1;
    preferences = (WebServerPreferences*)InstanceManager::getDefault("WebServerPreferences");
    initComponents();
}

/*private*/ void WebServerPreferencesPanel::initComponents() {
#if 0
    bindingGroup = new BindingGroup();
#endif
    port = new QSpinBox();
    portLabel = new QLabel();
    readonlyPower = new QCheckBox();
    startup = new QCheckBox();
    QVBoxLayout* thisLayout = new QVBoxLayout(this);

    //port.setModel(new SpinnerNumberModel(12080, 1, 65535, 1));
    port->setMinimum(1);
    port->setMaximum(65535);
    port->setSingleStep(1);
    port->setValue(12080);
    //port.setEditor(new JSpinner.NumberEditor(port, "#"));
    port->setToolTip(tr("Port to use for web server (default 12080)")); // NOI18N

    portLabel->setText(tr("Port")); // NOI18N
    portLabel->setToolTip(tr("Port to use for web server (default 12080)")); // NOI18N

    readonlyPower->setText(tr("Disable power control in menus")); // NOI18N
//    readonlyPower.addActionListener((ActionEvent e) -> {
//        readonlyPower.setToolTipText(tr(readonlyPower.isSelected() ? "ToolTipReadonlyPowerTrue" : "ToolTipReadonlyPowerFalse"));
//    });
    connect(readonlyPower, SIGNAL(clicked(bool)), this, SLOT(on_readonlyPower_checked(bool)));
#if 0
    Binding binding = Bindings.createAutoBinding(AutoBinding.UpdateStrategy.READ_WRITE, preferences, ELProperty.create("${port}"), port, BeanProperty.create("value"));
    bindingGroup.addBinding(binding);
#endif

    startup->setChecked(this->isStartupAction());
    startup->setText(tr("Start automatically with application")); // NOI18N
#if 1 // TODO
    //    this->startupItemListener = (ItemEvent e) ->
    //    {
    //        this->startup.removeItemListener(this->startupItemListener);
    //        StartupActionsManager manager = InstanceManager.getDefault(StartupActionsManager.class);
    //        if (this->startup.isSelected()) {
    //            PerformActionModel model = new PerformActionModel();
    //            model.setClassName(WebServerAction.class.getName());
    //            if (this->startupActionPosition == -1 || this->startupActionPosition >= manager.getActions().length) {
    //                manager.addAction(model);
    //            } else {
    //                manager.setActions(this->startupActionPosition, model);
    //            }
    //        } else {
    //            manager.getActions(PerformActionModel.class).stream().filter((model) -> (WebServerAction.class.getName().equals(model.getClassName()))).forEach((model) -> {
    //                this->startupActionPosition = Arrays.asList(manager.getActions()).indexOf(model);
    //                manager.removeAction(model);
    //            });
    //        }
    //        this->startup.addItemListener(this->startupItemListener);
    //    };
    //this->startup->addItemListener(this->startupItemListener);
    connect(startup, SIGNAL(toggled(bool)), this, SLOT(on_webSeverStartupOption(bool)));
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
                            .addComponent(startup, GroupLayout.DEFAULT_SIZE, 388, Short.MAX_VALUE)
                            .addComponent(readonlyPower, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addContainerGap())
    );
#else
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(portLabel);
    layout->addWidget(port);
    layout->addWidget(startup);
    layout->addWidget(readonlyPower);
#endif
#if 0
    layout.setVerticalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                    .addContainerGap()
                    .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                            .addComponent(port, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                            .addComponent(portLabel))
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(readonlyPower)
                    .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(startup)
                    .addContainerGap(198, Short.MAX_VALUE))
    );
#else
    thisLayout->addLayout(layout);
#endif
#if 0 // TODO:
    bindingGroup.bind();
#endif
}

void WebServerPreferencesPanel::on_webSeverStartupOption(bool bChecked)
{
 //this->startup->removeItemListener(this->startupItemListener);
 //disconnect(startup, SIGNAL(clicked(bool)), this, SLOT(on_webSeverStartupOption(bool)));
 StartupActionsManager* manager =(StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager");
 if (this->startup->isChecked())
 {
  PerformActionModel* model = new PerformActionModel();
  //model->setName("WebServerAction");
  model->setClassName("jmri.web.server.WebServerAction");
  if (this->startupActionPosition == -1 || this->startupActionPosition >= manager->getActions()->length())
  {
   manager->addAction(model);
  }
  else
  {
   manager->setActions(this->startupActionPosition, model);
  }
 }
 else
 {
//     manager.getActions("PerformActionModel").stream().filter((model) -> (WebServerAction.class.getName().equals(model.getClassName()))).forEach((model) ->
  foreach(StartupModel* model, *manager->getActions("PerformActionModel"))
  {
   this->startupActionPosition = /*Arrays.asList*/manager->getActions()->indexOf((StartupModel*)model);
   manager->removeAction(model);
  }
 }
 //this->startup.addItemListener(this->startupItemListener);
 //connect(startup, SIGNAL(toggled(bool)), this, SLOT(on_webSeverStartupOption(bool)));
}

void WebServerPreferencesPanel::on_readonlyPower_checked(bool b)
{
 readonlyPower->setToolTip(b ? tr("Power control in web pages will not function") :tr("Power control in web pages will display a dialog allowing power to be set"));
}

//@Override
/*public*/ QString WebServerPreferencesPanel::getPreferencesItem() {
    return tr("WEBSERVER");
}

//@Override
/*public*/ QString WebServerPreferencesPanel::getPreferencesItemText() {
    return tr("Web Server");
}

//@Override
/*public*/ QString WebServerPreferencesPanel::getTabbedPreferencesTitle() {
    return tr("Web Server");
}

//@Override
/*public*/ QString WebServerPreferencesPanel::getLabelKey() {
    return NULL;
}

//@Override
/*public*/ QWidget* WebServerPreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool WebServerPreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString WebServerPreferencesPanel::getPreferencesTooltip() {
    return NULL;
}

//@Override
/*public*/ void WebServerPreferencesPanel::savePreferences() {
    this->preferences->save();
}

//@Override
/*public*/ bool WebServerPreferencesPanel::isDirty() {
    return this->preferences->isDirty();
}

//@Override
/*public*/ bool WebServerPreferencesPanel::isRestartRequired() {
    return this->preferences->isRestartRequired();
}

//@Override
/*public*/ bool WebServerPreferencesPanel::isPreferencesValid() {
    return true; // no validity checking performed
}

/*private*/ bool WebServerPreferencesPanel::isStartupAction() {
    //return ((StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager"))->getActions("PerformActionModel").stream()
//            .anyMatch((model) -> (WebServerAction.class.getName().equals(model.getClassName())));
 bool ret = false;
 foreach(StartupModel* model, *((StartupActionsManager*) InstanceManager::getDefault("StartupActionsManager"))->getActions("PerformActionModel"))
 {
  if("WebServerAction" == QString(model->metaObject()->className()))
   ret = true;
 }
 return ret;
}
