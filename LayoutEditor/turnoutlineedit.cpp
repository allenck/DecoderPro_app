#include "turnoutlineedit.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include <QDragEnterEvent>


TurnoutLineEdit::TurnoutLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
  setAcceptDrops(true);
}
void TurnoutLineEdit::dragMoveEvent(QDragMoveEvent *de)
{
 QString turnout = de->mimeData()->text().toLatin1().data();
 if(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(turnout)== NULL)
 {
  de->ignore();
  return;
 }
 de->accept();
}
void TurnoutLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
 QString name = event->mimeData()->text().toLatin1().data();
 ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
 if(mgr->getTurnout(name) == NULL) return;
 // Set the drop action to be the proposed action.
 event->acceptProposedAction();
}
void TurnoutLineEdit::dropEvent(QDropEvent *de)
{
 // Unpack dropped data and handle it the way you want
 qDebug("Contents: %s", de->mimeData()->text().toLatin1().data());
 QString name = de->mimeData()->text().toLatin1().data();
 ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
 if(mgr->getTurnout(name) != NULL)
 {
  setStyleSheet("QLineEdit { border: 1px solid darkgray; }");
  setText(name);
 }
 else
 {
  setStyleSheet("QLineEdit { border: 1px solid red; }");
 }
}
void TurnoutLineEdit::setText(const QString &s)
{
 if(s == "" || s == tr("undefined"))
 {
  QLineEdit::setText(s);
  setStyleSheet("QLineEdit { border: 1px solid red; }");
 }
 else
 {
  QLineEdit::setText(s);
  setStyleSheet("QLineEdit { border: 1px solid darkgray; }");
 }
}
