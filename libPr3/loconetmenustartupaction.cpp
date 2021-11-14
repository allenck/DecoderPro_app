#include "loconetmenustartupaction.h"
#include "loconetmenu.h"
#include "instancemanager.h"
#include "componentfactory.h"

LocoNetMenuStartupAction::LocoNetMenuStartupAction(QObject* parent) : AbstractAction(tr("Monitor Loconet"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

LocoNetMenuStartupAction::LocoNetMenuStartupAction(QString title, QObject* parent) : AbstractAction(title, parent)
{
 this->title = title;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void LocoNetMenuStartupAction::actionPerformed(JActionEvent *)
{
 ComponentFactory* factory = (ComponentFactory*)InstanceManager::getDefault("ComponentFactory*");
 LocoNetMenu* menu = nullptr;

 if(LocoNetMenu::instance() != nullptr)
 //if(factory != nullptr)
 {
  //menu = factory->a()
  foreach(QAction* act, LocoNetMenu::instance()->actions())
  {
   if(act->text() == this->title)
   {
    act->trigger();
    return;
   }
  }
 }
 else
 {
  QTimer::singleShot(1000, this, SLOT(actionPerformed()));
 }
}

void LocoNetMenuStartupAction::setTitle(QString title) { this->title = title;}
