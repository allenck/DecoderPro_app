#include "dropjlabel.h"
#include "imageindexeditor.h"
#include "exceptions.h"
#include "dataflavor.h"
#include "droptarget.h"
#include "dndconstants.h"
#include "droptargetdropevent.h"
#include "transferable.h"
#include "namedicon.h"
#include "rosterentry.h" // (for VPtr)
#include "fileutil.h"

DropJLabel::DropJLabel(QWidget *parent) :
    QLabel(parent)
{
 init(NULL);
}
/**
* This file is part of JMRI
* @author Pete Cressman  Copyright (c) 2011
*/


// /*public*/ class DropJLabel extends JLabel implements DropTargetListener {


DropJLabel::DropJLabel (NamedIcon* icon,QWidget *parent) : QLabel(/*icon,*/ parent)
{
    //super(icon);
    init(icon);
}
void DropJLabel::init(NamedIcon* icon)
{
 log = new Logger("DropJLabel");
 log->setDebugEnabled(true);
 if(icon !=NULL)
  setIcon(icon);
 bRightClick = false;
 try
 {
  _dataFlavor = new DataFlavor(ImageIndexEditor::IconDataFlavorMime);
 }
 catch (ClassNotFoundException cnfe)
 {
//        cnfe.printStackTrace();
 }
  //new DropTarget((Component*)this, DnDConstants::ACTION_COPY_OR_MOVE, (DropTargetListener*)this);
    //if (log.isDebugEnabled()) log.debug("DropJLabel ctor");
 setAcceptDrops(true);
 _iconMap = NULL;
 _update = false;

}
DropJLabel::DropJLabel (NamedIcon* icon,  QMap<QString, NamedIcon *> *iconMap, bool update, QWidget *parent) : QLabel(/*icon,*/ parent)
{
 log = new Logger("DropJLabel");
 log->setDebugEnabled(true);
 _dataFlavor = new DataFlavor(ImageIndexEditor::IconDataFlavorMime);
 setIcon(icon);

 _iconMap = iconMap;
 _update = update;
 setAcceptDrops(true);
}

///*public*/ void dragExit(DropTargetEvent dte) {
//    //if (log.isDebugEnabled()) log.debug("DropJLabel.dragExit ");
//}
///*public*/ void dragEnter(DropTargetDragEvent dtde) {
//    //if (log.isDebugEnabled()) log.debug("DropJLabel.dragEnter ");
//}
/*public*/ void DropJLabel::dragEnterEvent(QDragEnterEvent *event)
{
 if (log->isDebugEnabled()) log->debug("DropJLabel.dragEnter ");  
 event->acceptProposedAction();
}

///*public*/ void dragOver(DropTargetDragEvent dtde) {
//    //if (log.isDebugEnabled()) log.debug("DropJLabel.dragOver ");
//}
/*public*/ void DropJLabel::dragMoveEvent(QDragMoveEvent *de)
{
 if (log->isDebugEnabled()) log->debug("DropJLabel.dragOver ");  
 if(!de->mimeData()->text().isEmpty())
  de->accept();
}

///*public*/ void dropActionChanged(DropTargetDragEvent dtde) {
//    //if (log.isDebugEnabled()) log.debug("DropdJLabel.dropActionChanged ");
//}
/*public*/ void DropJLabel::dropEvent(QDropEvent *de)
{
// DropTargetDropEvent* dtde = new DropTargetDropEvent((DropTargetContext*)this, de->pos(),DnDConstants::ACTION_COPY, 0);
// drop(dtde);
 QString text = de->mimeData()->text();
 if(text.startsWith("file://"))
 {
  text.remove("\r\n");
  NamedIcon* icon = new NamedIcon(text.mid(7),text.mid(7));
  if(icon != NULL)
  {
   setIcon(icon);
   emit fileNameChanged(text.mid(7));
  }
 }
 QStringList sl = text.split(";");
 QString path;
 foreach (QString s, sl)
 {
  if(s.startsWith("path"))
  {
   path = s.mid(5);
   path.replace("]", "");
   break;
  }
 }
 // Unpack dropped data and handle it the way you want
 qDebug("Contents: %s", de->mimeData()->text().toLatin1().data());
 if(!path.isEmpty())
 {
  _icon->setURL(path);
  NamedIcon* newIcon = new NamedIcon(path, path);
  QImage img = QImage(path);
  _icon->setImage(img);
  setPixmap(QPixmap::fromImage(img));
  QString name = getName();
  if(_iconMap->value(name))
  {
   _iconMap->remove(name);
   _iconMap->insert(name, newIcon);
  }
 }
}

/*public*/ void DropJLabel::drop(DropTargetDropEvent* e) 
{
 try
 {
  Transferable* tr = e->getTransferable();
  if(e->isDataFlavorSupported(_dataFlavor))
  {
   NamedIcon* newIcon = new NamedIcon((NamedIcon*) VPtr<NamedIcon>::asPtr(tr->getTransferData(_dataFlavor)));
   accept(e, newIcon);
  }
  else if(e->isDataFlavorSupported(DataFlavor::stringFlavor))
  {
   QString text = tr->getTransferData(DataFlavor::stringFlavor).toString();
   if (log->isDebugEnabled()) log->debug("drop for stringFlavor "+text);
   NamedIcon* newIcon = new NamedIcon(text, text);
   accept(e, newIcon);

  }
  else
  {
   if (log->isDebugEnabled()) log->debug("DropJLabel.drop REJECTED!");
   e->rejectDrop();
  }
 }
 catch(IOException ioe)
 {
  if (log->isDebugEnabled()) log->debug("DropPanel.drop REJECTED!");
  e->rejectDrop();
 }
 catch(UnsupportedFlavorException ufe)
 {
  if (log->isDebugEnabled()) log->debug("DropJLabel.drop REJECTED!");
  e->rejectDrop();
 }
}
/*private*/ void DropJLabel::accept(DropTargetDropEvent* e, NamedIcon* newIcon)
{
 e->acceptDrop(DnDConstants::ACTION_COPY_OR_MOVE);
 DropTarget* target = (DropTarget*)/*e->getSource();*/e->de->source();
 DropJLabel* label = (DropJLabel*)target->getComponent();
 if (log->isDebugEnabled()) log->debug("accept drop for "+label->getName()+ ", "+newIcon->getURL());
 if (newIcon==NULL || newIcon->getIconWidth()<1 || newIcon->getIconHeight()<1)
 {
  label->setText(tr("invisibleIcon"));
  //label->setForeground(QColor(Qt::lightGray));
 }
 else
 {
  newIcon->reduceTo(100, 100, 0.2);
  label->setText(NULL);
 }
 label->setIcon(newIcon);
//        _catalog.setBackground(label);
    // TODO: what about old _icomMap?
 _iconMap->insert(label->getName(), newIcon);
 if (!_update)
 {		// only prompt for save from palette
  ImageIndexEditor::indexChanged(true);
 }
 e->dropComplete(true);
 if (log->isDebugEnabled()) log->debug("DropJLabel.drop COMPLETED for "+label->getName()+ ", "+(newIcon!=NULL ? newIcon->getURL()/*.toString()*/:" newIcon==NULL "));
}
void DropJLabel::mouseMoveEvent(QMouseEvent */*ev*/)
{
 qDebug() << tr("mouse over, accept drops = ")+ (acceptDrops()?"true":"false");

}
void DropJLabel::setName(QString name) { this->name = name;}
QString DropJLabel::getName() { return name;}

void DropJLabel::setIcon(NamedIcon *icon)
{
 this->_icon = icon;
 QPixmap pixmap = QPixmap::fromImage(icon->getImage());
 setPixmap(pixmap.scaledToHeight(size().height()));
}
NamedIcon* DropJLabel::icon() {return _icon;}

void DropJLabel::setIconFn(QString fileName, QSize sz)
{
 if(fileName == "") return;
// NamedIcon* icon = new NamedIcon(fileName,fileName);
// icon->reduceTo(sz.width(), sz.height(), 24);
// if(icon != NULL)
//   setPixmap(QPixmap::fromImage( icon->getOriginalImage()));


 QImage img = QImage(fileName);
 if(!img.isNull())
 {
  if(img.width() > 24)
  {
   QImage img1 = img.scaledToWidth(24);
   setPixmap(QPixmap::fromImage(img1));
   return;
  }
  setPixmap(QPixmap::fromImage(img));
 }
}
void DropJLabel::mousePressEvent(QMouseEvent *ev)
{
 if(ev->button() == Qt::RightButton)
 {
  bRightClick = true;
 }
}
void DropJLabel::mouseReleaseEvent(QMouseEvent *ev)
{
 if(bRightClick)
  emit rightClick(this);
 bRightClick = false;
}
