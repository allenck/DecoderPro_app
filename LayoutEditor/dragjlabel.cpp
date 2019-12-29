#include "dragjlabel.h"
#include "namedicon.h"
#include "dataflavor.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QMimeData>
#include "rosterentry.h" // for Vptr
#include <QVBoxLayout>
#include "positionablelabelxml.h"

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
/*public*/ DragJLabel::DragJLabel(DataFlavor* flavor, QWidget *parent) : QGroupBox(parent)
{
     //super();
//     DragSource dragSource = DragSource.getDefaultDragSource();
//     dragSource.createDefaultDragGestureRecognizer(this,
//                 DnDConstants.ACTION_COPY, this);
 common();
 _dataFlavor = flavor;
 icon = NULL;
}

/*public*/ DragJLabel::DragJLabel(DataFlavor* flavor, NamedIcon *icon, QWidget *parent) : QGroupBox(parent)
{
     //super();
//     DragSource dragSource = DragSource.getDefaultDragSource();
//     dragSource.createDefaultDragGestureRecognizer(this,
//                 DnDConstants.ACTION_COPY, this);
 common();
 _dataFlavor = flavor;
 this->icon = icon;
 setPixmap(QPixmap::fromImage(icon->getImage()));
}

DragJLabel::~DragJLabel()
{
 delete log;
}

void DragJLabel::common()
{
 log = new Logger("DragJLabel");
 setAttribute(Qt::WA_DeleteOnClose);
 setLayout(new QVBoxLayout());
 this->layout()->addWidget(internalLabel = new QLabel);
}

/*public*/ void DragJLabel::setPixmap(QPixmap pixmap)
{
 internalLabel->setPixmap(pixmap);
}

/**
 * Source can override to prohibit dragging if data is incomplete
 * when dragGestureRecognized() is called.
 *
 * @return Source's choice to allow drag
 */
/*protected*/ bool DragJLabel::okToDrag() {
    return true;
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
  dr = new QDrag(this);
  QMimeData *data = new QMimeData;
  QByteArray s_mimeData = mimeData();
  log->debug(tr("xmldata: %1").arg(s_mimeData.data()));
  data->setData("object/x-myApplication-object", s_mimeData);
  // Assign ownership of the QMimeData object to the QDrag object.
  dr->setMimeData(data);
  dr->exec();
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

//QByteArray DragJLabel::mimeData()
//{ return QByteArray();}
/*public*/ QByteArray DragJLabel::mimeData()
{
 QByteArray xmldata;
 PositionableLabelXml* xml = new PositionableLabelXml();
 PositionableLabel* label = new PositionableLabel(getIcon(),nullptr);
 QDomElement e = xml->store((QObject*)label);
 xml->doc.appendChild(e);
 xmldata.append(xml->doc.toString());
 log->info(tr("xml data: %1").arg(xml->doc.toString()));
 return xmldata;
}

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
 setTitle(name);
}

/**
 * Source can override to prohibit dragging if data is incomplete
 * when dragGestureRecognized() is called.
 *
 * @return Source's choice to allow drag
 */
/*protected*/ bool okToDrag() {
    return true;
}

/*public*/ void DragJLabel::setMargin(int i)
{
 internalLabel->setMargin(i);
}


/*public*/ void DragJLabel::setText(QString txt)
{
 internalLabel->setText(txt);
}
