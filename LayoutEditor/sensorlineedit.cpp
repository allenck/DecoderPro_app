#include "sensorlineedit.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include <QDragEnterEvent>
SensorLineEdit::SensorLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
 setAcceptDrops(true);
}
void SensorLineEdit::dragMoveEvent(QDragMoveEvent *de)
{
 QString sensor = de->mimeData()->text().toLatin1().data();
 if(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sensor)== NULL)
 {
  de->ignore();
  return;
 }
 de->accept();
}
void SensorLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
 QString name = event->mimeData()->text().toLatin1().data();
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 if(mgr->getSensor(name) == NULL) return;
 // Set the drop action to be the proposed action.
 event->acceptProposedAction();
}
void SensorLineEdit::dropEvent(QDropEvent *de)
{
 // Unpack dropped data and handle it the way you want
 qDebug("Contents: %s", de->mimeData()->text().toLatin1().data());
 QString name = de->mimeData()->text().toLatin1().data();
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 setText(name);
 if(mgr->getSensor(name) != NULL)
 {
  setStyleSheet("QLineEdit { border: 1px solid darkgray; }");
 }
 else
 {
  setStyleSheet("QLineEdit { border: 1px solid red; }");
 }
 emit sensorChanged(name);
}
void SensorLineEdit::setText(const QString &s)
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
