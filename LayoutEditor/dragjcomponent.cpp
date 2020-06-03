#include "dragjcomponent.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include "dataflavor.h"
#include <QVBoxLayout>
#include "borderfactory.h"

//DragJComponent::DragJComponent(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Gives a JComponent the capability to Drag and Drop
 * <P>
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
 * @author			Pete Cressman  Copyright 2011
 *
 */
// /*public*/ abstract class DragJComponent extends JPanel implements DragGestureListener, DragSourceListener, Transferable {

 /*public*/ DragJComponent::DragJComponent(DataFlavor* flavor, QWidget *comp, QWidget *parent) : JPanel(parent){
     //super();
     QString borderName = tr("Drag to Panel");
     setLayout(new QVBoxLayout());
     setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
                                                      borderName));
     //setTitle(borderName);
     QSize dim = comp->sizeHint();
     this->layout()->addWidget(comp);
     // guestimate border is about 5 pixels thick. plus some margin
     int width = qMax(100, dim.width()+20);
     int height = qMax(65, dim.height()+20);
     resize(QSize(width, height));
     setToolTip(tr("Drag an icon from the Catalog to replace an icon in the item group"));
//     DragSource dragSource = DragSource.getDefaultDragSource();
//     dragSource.createDefaultDragGestureRecognizer(this,
//                 DnDConstants.ACTION_COPY, this);
     _dataFlavor = flavor;
 }
#if 0
 /**************** DragGestureListener ***************/
 /*public*/ void dragGestureRecognized(DragGestureEvent e) {
     if (log.isDebugEnabled()) log.debug("DragJLabel.dragGestureRecognized ");
     //Transferable t = getTransferable(this);
     e.startDrag(DragSource.DefaultCopyDrop, this, this);
 }
 /**************** DragSourceListener ************/
 /*public*/ void dragDropEnd(DragSourceDropEvent e) {
     if (log.isDebugEnabled()) log.debug("DragJLabel.dragDropEnd ");
     }
 /*public*/ void dragEnter(DragSourceDragEvent e) {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.DragSourceDragEvent ");
     }
 /*public*/ void dragExit(DragSourceEvent e) {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.dragExit ");
     }
 /*public*/ void dragOver(DragSourceDragEvent e) {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.dragOver ");
     }
 /*public*/ void dropActionChanged(DragSourceDragEvent e) {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.dropActionChanged ");
     }
#endif
 /*************** Transferable *********************/
 /*public*/ QList<DataFlavor*> DragJComponent::getTransferDataFlavors() {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.getTransferDataFlavors ");
    return  QList<DataFlavor*>() <<_dataFlavor << DataFlavor::stringFlavor ;
 }
 /*public*/ bool DragJComponent::isDataFlavorSupported(DataFlavor* flavor) {
     //if (log.isDebugEnabled()) log.debug("DragJLabel.isDataFlavorSupported ");
     return _dataFlavor == (flavor);
 }

void DragJComponent::mousePressEvent(QMouseEvent *e)
{
 QByteArray text = mimeData();
 if(text != "")
 {
  if(e->button()&Qt::LeftButton)
  {
   QDrag *dr = new QDrag(this);
   QMimeData *data = new QMimeData();
   //data->setText(_dataFlavor->toString());
   data->setData("object/x-myApplication-object", text);
   // Assign ownership of the QMimeData object to the QDrag object.
   dr->setMimeData(data);
   dr->start();
  }
 }
}
