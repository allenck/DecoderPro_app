#include "abstractactionmodelfactory.h"
#include "loggerfactory.h"
#include "startupmodel.h"
#include "joptionpane.h"
#include "connectionnamefromsystemname.h"
#include "abstractactionmodel.h"
#include "startupactionsmanager.h"
#include "optional.h"
#include "instancemanager.h"
#include "startupactionmodelutil.h"
#include <QBoxLayout>
#include "systemconnectionaction.h"
#include "vptr.h"
#include <QAction>

AbstractActionModelFactory::AbstractActionModelFactory()
{

}
/**
 * Provide an abstract StartupModelFactory with common methods for factories
 * that manipulate models that extend {@link apps.AbstractActionModel}.
 *
 * @author Randall Wood
 */
//abstract /*public*/ class AbstractActionModelFactory implements StartupModelFactory {

/*private*/ /*final*/ /*static*/ Logger* AbstractActionModelFactory::log = LoggerFactory::getLogger("AbstractActionModelFactory");

//@Override
/*public*/ QString AbstractActionModelFactory::getDescription() {
    //return this->getModelClass()->getCanonicalName(); //???
 return this->getModelClass();
}

//@Override
/*public*/ QString AbstractActionModelFactory::getActionText() {
    return tr("%1...").arg(this->getDescription());
}

/**
 * Get the message text for the dialog created in
 * {@link #editModel(apps.startup.StartupModel, java.awt.Component)}.
 *
 * @return the message text
 */
/*public*/ /*abstract*/ QString AbstractActionModelFactory::getEditModelMessage() {return "";}

//@Override
/*public*/ void AbstractActionModelFactory::editModel(StartupModel* model, QWidget* parent)
{
 //if (this->getModelClass()->isInstance(model))
 if(Class::forName(this->getModelClass())->isInstance(model))
 {
  actions = new JList(StartupActionModelUtil::getDefault()->getNames());
  connections = new QComboBox();
  QWidget* message = this->getDialogMessage(actions, connections);
  actions->setSelectedValue(model->getName(), true);
  QString userName = ConnectionNameFromSystemName::getConnectionName(((AbstractActionModel*) model)->getSystemPrefix());
  if (userName == NULL)
  {
   userName = ""; // make not NULL to simplify following conditionals
  }
  if (!userName.isEmpty())
  {
   connections->setCurrentIndex(connections->findText(userName));
  }
  int result = JOptionPane::showOptionDialog(parent,
          VPtr<QWidget>::asQVariant(message),
          this->getDescription(),
          JOptionPane::OK_CANCEL_OPTION,
          JOptionPane::PLAIN_MESSAGE,
          QIcon(),
          QList<QVariant>(),
          QVariant());
  if (result == JOptionPane::OK_OPTION)
  {
      QString name = actions->getSelectedValue().toString();
      model->setTitle(name);
      Optional<StartupActionsManager*>* manager = (Optional<StartupActionsManager*>*)InstanceManager::getOptionalDefault("StartupActionsManager");
   if (name != (model->getName()))
   {
    model->setName(name);
#if 0
    //manager->ifPresent(sam ->
    if(manager->ifPresent(sam))
    {
        sam->setRestartRequired();
    }//);
#endif
   }
   if (((userName.isEmpty() && connections->currentText() != NULL))
           || userName!=(connections->currentText())) {
       ((AbstractActionModel*) model)->setSystemPrefix(ConnectionNameFromSystemName::getPrefixFromName((QString) connections->currentText()));
#if 0
       //manager->ifPresent(sam ->
       if(manager->ifPresent(sam))
       {
           sam->setRestartRequired();
       }//);
#endif
   }
  }
 }
}

//@Override
/*public*/ void AbstractActionModelFactory::initialize() {
    // nothing to do
}

/*private*/ QWidget* AbstractActionModelFactory::AbstractActionModelFactory::getDialogMessage(JList* actions, QComboBox* connections) {
    connectionsLabel = new QLabel(tr("<html>Set the connection for this action.</html>"/*, JLabel.LEADING*/)); // NOI18N
//    actions.getSelectionModel().addListSelectionListener((ListSelectionEvent e) ->
//    {
//        if (!e.getValueIsAdjusting()) {
//            connections.removeAllItems();
//            connections.setEnabled(false);
//            connectionsLabel.setEnabled(false);
//            QString name = actions.getSelectedValue();
//            if (name != NULL) {
//                QString className = StartupActionModelUtil.getDefault().getClassName(name);
//                if (className != NULL && StartupActionModelUtil.getDefault().isSystemConnectionAction(className)) {
//                    try {
//                        Action action = (Action) Class.forName(className).newInstance();
//                        if (SystemConnectionAction.class.isAssignableFrom(action.getClass())) {
//                            ((SystemConnectionAction) action).getSystemConnectionMemoClasses().stream().forEach((clazz) -> {
//                                InstanceManager.getList(SystemConnectionMemo.class).stream().forEach((memo) -> {
//                                    if (clazz.isAssignableFrom(memo.getClass())) {
//                                        connections.addItem(memo.getUserName());
//                                        connections.setEnabled(true);
//                                        connectionsLabel.setEnabled(true);
//                                    }
//                                });
//                            });
//                        }
//                    } catch (ClassNotFoundException | InstantiationException | IllegalAccessException ex) {
//                        log->error("Unable to create Action", ex);
//                    }
//                }
//            }
//        }
//    });
    connect(actions, SIGNAL(clicked(QModelIndex)), this, SLOT(on_selected(/*ListSelectionEvent**/QModelIndex)));
    connections->setEnabled(false);
    connectionsLabel->setEnabled(false);
    QWidget* panel = new QWidget();
    QVBoxLayout* panelLayout;
    panel->setLayout(panelLayout = new QVBoxLayout()); //(panel, BoxLayout.PAGE_AXIS));
    panelLayout->addWidget(new QLabel(this->getEditModelMessage()/*, JLabel.LEADING)*/));
    panelLayout->addWidget(/*new JScrollPane(*/actions);
    panelLayout->addWidget(connectionsLabel);
    panelLayout->addWidget(connections);
    return panel;
}

void AbstractActionModelFactory::on_selected(/*ListSelectionEvent* e*/QModelIndex index)
{
// if (!e->getValueIsAdjusting())
 {
  connections->clear();
  connections->setEnabled(false);
  connectionsLabel->setEnabled(false);
  QString name = actions->model()->data(index).toString(); //actions->getSelectedValue().toString();
  if (name != NULL)
  {
   QString className = StartupActionModelUtil::getDefault()->getClassName(name);
   if (className != NULL && StartupActionModelUtil::getDefault()->isSystemConnectionAction(className))
   {
    try
    {
     QAction* action = (QAction*) Class::forName(className)->newInstance();
     if (Class::forName("SystemConnectionAction")->isAssignableFrom(action->metaObject()->className()))
     {
//                     ((SystemConnectionAction*) action).getSystemConnectionMemoClasses().stream().forEach((clazz) ->
      foreach(Class* clazz, ((SystemConnectionAction*) action)->getSystemConnectionMemoClasses())
      {
//                         InstanceManager::getList(SystemConnectionMemo.class).stream().forEach((memo) ->
       foreach(QObject* memo, InstanceManager::getList("SystemConnectionMemo"))
       {
        if (clazz->isAssignableFrom(memo->metaObject()->className()))
        {
         connections->addItem(((SystemConnectionMemo*)memo)->getUserName());
         connections->setEnabled(true);
         connectionsLabel->setEnabled(true);
        }
       }//);
      }//);
     }
    }
    catch (ClassNotFoundException  ex)
    {
     log->error("Unable to create Action", ex);
    }
    catch ( InstantiationException  ex)
    {
     log->error("Unable to create Action", ex);
    }
    catch ( IllegalAccessException ex)
    {
     log->error("Unable to create Action", ex);
    }
   }
  }
 }
}//);
