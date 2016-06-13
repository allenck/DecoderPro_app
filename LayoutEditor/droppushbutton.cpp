#include "droppushbutton.h"
#include <QDragMoveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include "namedicon.h"
#include <QFileInfo>

DropPushButton::DropPushButton(QWidget *parent) :
    QPushButton(parent)
{
 setAcceptDrops(true);
}
void DropPushButton::dragMoveEvent(QDragMoveEvent *de)
{
 QString path = de->mimeData()->text().toLatin1().data();
 QFileInfo info(path);
 if(!info.exists())
 {
  de->ignore();
  return;
 }
 // The event needs to be accepted here
 de->accept();
}
void DropPushButton::dragEnterEvent(QDragEnterEvent *event)
{
 QString path = event->mimeData()->text().toLatin1().data();
 QFileInfo info(path);
 if(!info.exists())
 {
  event->ignore();
  return;
 }
 // Set the drop action to be the proposed action.
 event->acceptProposedAction();
}
void DropPushButton::dropEvent(QDropEvent *de)
{
 // Unpack dropped data and handle it the way you want
 qDebug("Contents: %s", de->mimeData()->text().toLatin1().data());
 QString path = de->mimeData()->text().toLatin1().data();
 NamedIcon* icon = new NamedIcon(path, path);
 if(icon != NULL)
 {
  this->setIcon(QPixmap::fromImage(icon->getImage()));
  emit iconChanged(icon);
 }
}
