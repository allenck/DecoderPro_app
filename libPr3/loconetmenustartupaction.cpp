#include "loconetmenustartupaction.h"
#include "loconetmenu.h"
#include "instancemanager.h"

LocoNetMenuStartupAction::LocoNetMenuStartupAction(QObject* parent) : AbstractAction(tr("Monitor Loconet"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

LocoNetMenuStartupAction::LocoNetMenuStartupAction(QString title, QObject* parent) : AbstractAction(title, parent)
{
 this->title = title;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void LocoNetMenuStartupAction::actionPerformed(ActionEvent *)
{

 if(LocoNetMenu::instance() != NULL)
 {
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
