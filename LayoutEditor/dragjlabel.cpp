#include "dragjlabel.h"
#include "namedicon.h"
#include "dataflavor.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QMimeData>
#include "rosterentry.h" // for Vptr

//DragJLabel::DragJLabel(QWidget *parent) :
//    JLabel(parent)
//{
//}
/**
 * Gives a JLabel the capability to Drag and Drop
 * <P>
 *
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
// /*public*/ class DragJLabel extends JLabel implements DragGestureListener, DragSourceListener, Transferable {

/*public*/ DragJLabel::DragJLabel(DataFlavor* flavor, QWidget *parent) : QLabel(parent)
{
     //super();
//     DragSource dragSource = DragSource.getDefaultDragSource();
//     dragSource.createDefaultDragGestureRecognizer(this,
//                 DnDConstants.ACTION_COPY, this);
 log = new Logger("DragJLabel");
 _dataFlavor = flavor;
 icon = NULL;
}
DragJLabel::~DragJLabel()
{
 delete log;
}
 /**************** DragGestureListener ***************/
// /*public*/ void dragGestureRecognized(DragGestureEvent e) {
//     if (log.isDebugEnabled()) log.debug("DragJLabel.dragGestureRecognized ");
//     //Transferable t = getTransferable(this);
//     e.startDrag(DragSource.DefaultCopyDrop, this, this);
// }
 /**************** DragSourceListener ************/
// /*public*/ void dragDropEnd(DragSourceDropEvent e) {
//     if (log.isDebugEnabled()) log.debug("DragJLabel.dragDropEnd ");
//     }
// /*public*/ void dragEnter(DragSourceDragEvent e) {
//void DragJLabel::dragEnterEvent(QDragEnterEvent * event)
//{
// event->acceptProposedAction();
//}
//void DragJLabel::dragMoveEvent(QDragMoveEvent *de)
//{
// // The event needs to be accepted here
// de->accept();
//}
void DragJLabel::mousePressEvent(QMouseEvent *e)
{
 if(e->button()&Qt::LeftButton)
 {
  QDrag *dr = new QDrag(this);
  QMimeData *data = new QMimeData;
  QString s_mimeData = mimeData();
  if(!s_mimeData.isEmpty())
   data->setText(s_mimeData);
  else
   data->setText(_dataFlavor->toString());
  //data->setText(mimeData());
  // Assign ownership of the QMimeData object to the QDrag object.
  dr->setMimeData(data);
  dr->start();
 }
 if(e->button() & Qt::RightButton)
 {
  emit showPopUp(getIcon());
 }
}

//     //if (log.isDebugEnabled()) log.debug("DragJLabel.DragSourceDragEvent ");
//     }
// /*public*/ void dragExit(DragSourceEvent e) {
//     //if (log.isDebugEnabled()) log.debug("DragJLabel.dragExit ");
//     }
// /*public*/ void dragOver(DragSourceDragEvent e) {
//     //if (log.isDebugEnabled()) log.debug("DragJLabel.dragOver ");
//     }
// /*public*/ void dropActionChanged(DragSourceDragEvent e) {
//     //if (log.isDebugEnabled()) log.debug("DragJLabel.dropActionChanged ");
//     }
 /*************** Transferable *********************/
 /*public*/ QList<DataFlavor*> DragJLabel::getTransferDataFlavors() {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.getTransferDataFlavors ");
   QList<DataFlavor*>list =  QList<DataFlavor*>() << _dataFlavor << DataFlavor::stringFlavor ;
   return list;
 }
 /*public*/ bool DragJLabel::isDataFlavorSupported(DataFlavor* flavor) {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.isDataFlavorSupported ");
     if (DataFlavor::stringFlavor==(flavor)) {
         return true;
     }
     return _dataFlavor==(flavor);
 }

/*public*/ QVariant DragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
     if (log->isDebugEnabled()) log->debug("DragJLabel.getTransferData ");
     if (_dataFlavor==(flavor)) {
         return VPtr<NamedIcon>::asQVariant(getIcon());
     }
     if (DataFlavor::stringFlavor==(flavor)) {
         NamedIcon* icon = (NamedIcon*)getIcon();
         return icon->getURL();
     }
     return QVariant();
 }

QString DragJLabel::mimeData()
{ return _dataFlavor->toString();}

void DragJLabel::setIcon(NamedIcon *icon)
{
 this->icon = icon;
 QPixmap pixmap = QPixmap::fromImage(icon->getImage());
 setPixmap(pixmap);
}

NamedIcon* DragJLabel::getIcon() { return icon;}

void DragJLabel::setName(QString name)
{
 this->name = name;
}
