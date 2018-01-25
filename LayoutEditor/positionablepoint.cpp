#include "positionablepoint.h"
#include "tracksegment.h"
#include "instancemanager.h"
#include "panelmenu.h"
#include "signalheadmanager.h"
#include "blockbosslogic.h"

//PositionablePoint::PositionablePoint(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * PositionablePoint is a Point defining a node in the Track that can be dragged around the
 * inside of the enclosing LayoutEditor panel using a right-drag (drag with meta key).
 * <P>
 * Two types of Positionable Point are supported:
 *		Anchor - point on track - two track connections
 *		End Bumper - end of track point - one track connection
 * <P>
 * Note that a PositionablePoint exists for specifying connectivity and drawing position
 * only.  The Track Segments connected to a PositionablePoint may belong to the same block
 * or to different blocks.  Since each Track Segment may only belong to one block, a
 * PositionablePoint may function as a Block Boundary.
 * <P>
 * Signal names are saved here at a Block Boundary anchor point by the tool Set Signals at
 * Block Boundary. PositionablePoint does nothing with these signal head names; it only
 * serves as a place to store them.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 20243 $
 */

///*public*/ class PositionablePoint
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

    // operational instance variables (not saved between sessions)

/*public*/ PositionablePoint::PositionablePoint(QString id, int t, QPointF p, LayoutEditor* myPanel,QObject *parent) : QObject(parent)
{
 setObjectName(id);
 instance = NULL;
 layoutEditor = NULL;
 // initialization instance variables (used when loading a LayoutEditor)
 trackSegment1Name = "";
 trackSegment2Name = "";

 // persistent instances variables (saved between sessions)
 ident = "";
 type = 0;
 connect1 = NULL;
 connect2 = NULL;
 coords = QPointF(10.0,10.0);
 eastBoundSignalName = ""; // signal head for east (south) bound trains
 westBoundSignalName = ""; // signal head for west (north) bound trains
 /* We use a namedbeanhandle for the the sensors, even though we only store the name here,
        this is so that we can keep up with moves and changes of userNames */
 eastBoundSensorNamed = NULL;
 westBoundSensorNamed = NULL;
 eastBoundSignalMastNamed = NULL;
 westBoundSignalMastNamed = NULL;

 eastBoundSignalMastName = "";
 westBoundSignalMastName = "";
 instance = this;
 layoutEditor = myPanel;
 if ( (t==ANCHOR) || (t==END_BUMPER) || (t == EDGE_CONNECTOR))
 {
  type = t;
 }
 else
 {
  log.error("Illegal type of PositionablePoint - "+t);
  type = ANCHOR;
 }
 ident = id;
 coords = p;
 popup = NULL;
 active = true;
 tools = NULL;
 // cursor location reference for this move (relative to object)
 xClick = 0;
 yClick = 0;
 item = NULL;
 editLink = NULL;

}

/**
 * Accessor methods
*/
/*public*/ QString PositionablePoint::getID() {return ident;}
/*public*/ int PositionablePoint::getType() {return type;}

/*public*/ TrackSegment* PositionablePoint::getConnect1() {return connect1;}
/*public*/ TrackSegment* PositionablePoint::getConnect2()
{
 if (type == EDGE_CONNECTOR && getLinkedPoint() != NULL) {
     return getLinkedPoint()->getConnect1();
 }
 return connect2;
}
/*public*/ QPointF PositionablePoint::getCoords() {return coords;}
/*public*/ void PositionablePoint::setCoords(QPointF p) {coords = p;}

/*public*/ QString PositionablePoint::getLinkEditorName() {
    if (getLinkedEditor() != NULL) {
        return getLinkedEditor()->getLayoutName();
    }
    return "";
}

/*public*/ PositionablePoint* PositionablePoint::getLinkedPoint() {
    return linkedPoint;
}

/*public*/ QString PositionablePoint::getLinkedPointId() {
    if (linkedPoint != NULL) {
        return linkedPoint->getID();
    }
    return "";
}

/*public*/ void PositionablePoint::setLinkedPoint(PositionablePoint* p) {
    if (p == linkedPoint) {
        return;
    }
    if (linkedPoint != NULL && linkedPoint != p) {
        PositionablePoint* oldLinkedPoint = linkedPoint;
        linkedPoint = NULL;
        if (oldLinkedPoint->getLinkedPoint() != NULL) {
            oldLinkedPoint->setLinkedPoint(NULL);
        }
        if (oldLinkedPoint->getConnect1() != NULL) {
            TrackSegment* ts = oldLinkedPoint->getConnect1();
            oldLinkedPoint->getLayoutEditor()->auxTools->setBlockConnectivityChanged();
            ts->updateBlockInfo();
            oldLinkedPoint->getLayoutEditor()->repaint();
        }
        if (getConnect1() != NULL) {
            layoutEditor->auxTools->setBlockConnectivityChanged();
            getConnect1()->updateBlockInfo();
            layoutEditor->repaint();
        }
    }
    linkedPoint = p;
    if (p != NULL) {
        p->setLinkedPoint(this);
        if (getConnect1() != NULL) {
            layoutEditor->auxTools->setBlockConnectivityChanged();
            getConnect1()->updateBlockInfo();
            layoutEditor->repaint();
        }
    }
}

/*public*/ LayoutEditor* PositionablePoint::getLinkedEditor() {
    if (getLinkedPoint() != NULL) {
        return getLinkedPoint()->getLayoutEditor();
    }
    return NULL;
}

/*protected*/ LayoutEditor* PositionablePoint::getLayoutEditor() {
    return layoutEditor;
}
/*public*/ QString PositionablePoint::getEastBoundSignal() {return eastBoundSignalName;}
/*public*/ void PositionablePoint::setEastBoundSignal(QString signalName) {eastBoundSignalName = signalName;}
/*public*/ QString PositionablePoint::getWestBoundSignal() {return westBoundSignalName;}
/*public*/ void PositionablePoint::setWestBoundSignal(QString signalName) {westBoundSignalName = signalName;}

/*public*/ QString PositionablePoint::getEastBoundSensorName() {
    if (eastBoundSensorNamed != NULL) {
        return eastBoundSensorNamed->getName();
    }
    return "";
}
/*public*/ QString PositionablePoint::getEastBoundSensor() {
    if(eastBoundSensorNamed!=NULL)
        return eastBoundSensorNamed->getName();
    return "";
}
/*public*/ void PositionablePoint::setEastBoundSensor(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        eastBoundSensorNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        eastBoundSensorNamed =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        eastBoundSensorNamed=NULL;
    }
}

/*public*/ QString PositionablePoint::getWestBoundSensorName() {
        if (westBoundSensorNamed != NULL) {
            return westBoundSensorNamed->getName();
        }
        return "";
    }/*public*/ QString PositionablePoint::getWestBoundSensor() {
    if(westBoundSensorNamed!=NULL)
        return westBoundSensorNamed->getName();
    return "";
}
/*public*/ void PositionablePoint::setWestBoundSensor(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        westBoundSensorNamed=NULL;
        return;
    }
    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        westBoundSensorNamed =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        westBoundSensorNamed=NULL;
    }
}
/*public*/ QString PositionablePoint::getEastBoundSignalMastName() {
        if (getEastBoundSignalMastNamed() != NULL) {
            return getEastBoundSignalMastNamed()->getName();
        }
        return "";
    }
/*public*/ QString PositionablePoint::getEastBoundSignalMast() {return eastBoundSignalMastName;}

/*private*/ NamedBeanHandle<SignalMast*>* PositionablePoint::getEastBoundSignalMastNamed()
{
 if (getType() == EDGE_CONNECTOR)
 {
     int dir = getConnect1Dir();
     if (dir == Path::SOUTH || dir == Path::EAST || dir == Path::SOUTH + Path::EAST) {
         return eastBoundSignalMastNamed;
     } else if (getLinkedPoint() != NULL) {
         int linkDir = getLinkedPoint()->getConnect1Dir();
         if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH + Path::EAST) {
             return getLinkedPoint()->getEastBoundSignalMastNamed();
         }
     }
 }
 return eastBoundSignalMastNamed;
}
/*private*/ NamedBeanHandle<SignalMast*>* PositionablePoint::getWestBoundSignalMastNamed()
{
 if (getType() == EDGE_CONNECTOR)
 {
  int dir = getConnect1Dir();
  if (dir == Path::SOUTH || dir == Path::EAST || dir == Path::SOUTH + Path::EAST)
  {
   return westBoundSignalMastNamed;
  }
  else if (getLinkedPoint() != NULL)
  {
   int linkDir = getLinkedPoint()->getConnect1Dir();
   if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH + Path::EAST) {
       return getLinkedPoint()->getWestBoundSignalMastNamed();
   }
  }
 }
 return westBoundSignalMastNamed;
}
/*public*/ void PositionablePoint::setEastBoundSignalMast(QString signalMastName) {eastBoundSignalMastName = signalMastName;}
/*public*/ QString PositionablePoint::getWestBoundSignalMastName() {
        if (getWestBoundSignalMastNamed() != NULL) {
            return getWestBoundSignalMastNamed()->getName();
        }
        return "";
    }
/*public*/ QString PositionablePoint::getWestBoundSignalMast() {return westBoundSignalMastName;}
/*public*/ void PositionablePoint::setWestBoundSignalMast(QString signalMastName) {westBoundSignalMastName = signalMastName;}

// initialization instance variables (used when loading a LayoutEditor)
//	public String trackSegment1Name = "";
//	public String trackSegment2Name = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void PositionablePoint::setObjects(LayoutEditor* p) {
    connect1 = p->findTrackSegmentByName(trackSegment1Name);
    connect2 = p->findTrackSegmentByName(trackSegment2Name);
}

/**
 * Setup and remove connections to track
 */
/*public*/ bool PositionablePoint::setTrackConnection (TrackSegment* track) {
    if (track==NULL) {
        return false;
    }
    if ( (connect1!=track) && (connect2!=track) ) {
        // not connected to this track
        if (connect1==NULL) {
            connect1 = track;
        }
        else if ( (type!=END_BUMPER) && (connect2==NULL) ) {
            connect2 = track;
            if(connect1->getLayoutBlock()==connect2->getLayoutBlock()){
                setWestBoundSignalMast("");
                setEastBoundSignalMast("");
                setWestBoundSensor("");
                setEastBoundSensor("");
            }
        }
        else {
            log.error ("Attempt to assign more than allowed number of connections");
            return false;
        }
    }
    return true;
}

/*public*/ void PositionablePoint::removeTrackConnection (TrackSegment* track)
{
    if (track==connect1)
    {
        connect1 = NULL;
        reCheckBlockBoundary();
    }
    else if (track==connect2) {
        connect2 = NULL;
        reCheckBlockBoundary();
    }
    else {
        log.error ("Attempt to remove non-existant track connection");
    }
}

/*public*/ void PositionablePoint::reCheckBlockBoundary(){
    if(type==END_BUMPER)
        return;
    if(connect1==NULL && connect2==NULL){
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
//        if(!getWestBoundSignalMast().equals(""))
//            removeSML(getWestBoundSignalMast());
//        if(!getEastBoundSignalMast().equals(""))
//            removeSML(getEastBoundSignalMast());
        setWestBoundSignalMast("");
        setEastBoundSignalMast("");
        setWestBoundSensor("");
        setEastBoundSensor("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any SignalMast logics generated
    }  else if(connect1==NULL || connect2==NULL){
        //could still be in the process of rebuilding the point details
        return;
    } else if (connect1->getLayoutBlock()==connect2->getLayoutBlock()){
        //We are no longer a block bounardy
//        if(!getWestBoundSignalMast().equals(""))
//            removeSML(getWestBoundSignalMast());
//        if(!getEastBoundSignalMast().equals(""))
//            removeSML(getEastBoundSignalMast());
        setWestBoundSignalMast("");
        setEastBoundSignalMast("");
        setWestBoundSensor("");
        setEastBoundSensor("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any SignalMast logics generated
    }
}
#if 0 // TODO:

void removeSML(QString signalMast){
    if(signalMast==NULL || signalMast.equals(""))
        return;
    jmri.SignalMast mast = jmri.InstanceManager.signalMastManagerInstance().getSignalMast(signalMast);
    if(jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() && InstanceManager.signalMastLogicManagerInstance().isSignalMastUsed(mast)){
        if(SignallingGuiTools.removeSignalMastLogic(NULL, mast)){
            if (tools == NULL) {
                tools = new LayoutEditorTools(layoutEditor);
            }
            tools.removeSignalMastFromPanel(signalMast);
        }
    }
}
#endif
/*protected*/ int PositionablePoint::maxWidth(){
    return 5;
}
/*protected*/ int PositionablePoint::maxHeight(){
    return 5;
}

/*public*/ void PositionablePoint::mousePressed(QGraphicsSceneMouseEvent* e) {
    // remember where we are
    xClick = e->scenePos().x();
    yClick = e->scenePos().y();
    // if (debug) log.debug("Pressed: "+where(e));
//    if (e.isPopupTrigger()) {
//        showPopUp(e);
//    }
}

/*public*/ void PositionablePoint::mouseReleased(QGraphicsSceneMouseEvent* e)
{
 // if (debug) log.debug("Release: "+where(e));
 //if (e.isPopupTrigger())
 if(e->buttons()& Qt::RightButton != 0)
 {
  showPopUp(e);
 }
}

/*public*/ void PositionablePoint::mouseClicked(QGraphicsSceneMouseEvent* e) {
    if(e->buttons()& Qt::RightButton != 0)
    {
     showPopUp(e);
    }
}


/**
 * For editing: only provides remove
 */
/*protected*/ void PositionablePoint::showPopUp(QGraphicsSceneMouseEvent* /*e*/)
{
 if (popup != NULL )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }
 bool blockBoundary = false;
 bool endBumper = false;
 switch (getType())
 {
 case ANCHOR:
 {
  popup->addAction(new QAction(tr("Anchor"),this));
  LayoutBlock* block1 = NULL;
  LayoutBlock* block2 = NULL;
  if (connect1!=NULL) block1 = connect1->getLayoutBlock();
  if (connect2!=NULL) block2 = connect2->getLayoutBlock();
  if ( (block1!=NULL) && (block1==block2) )
  {
   popup->addAction(new QAction(tr("Block")+": "+block1->getID(),this));
  }
  else if ( (block1!=NULL) && (block2!=NULL) && (block1!=block2) )
  {
   popup->addAction(new QAction(tr("BlockDivider"),this));
   popup->addAction(new QAction(" "+tr("Block1ID")+": "+block1->getID(),this));
   popup->addAction(new QAction(" "+tr("Block2ID")+": "+block2->getID(),this));
   blockBoundary = true;
  }
  break;
 }
 case END_BUMPER:
 {
  popup->addAction(new QAction(tr("End Bumper"),this));
  LayoutBlock* blockEnd = NULL;
  if (connect1!=NULL) blockEnd = connect1->getLayoutBlock();
  if (blockEnd!=NULL)
  {
   popup->addAction(new QAction(tr("BlockID")+": "+blockEnd->getID(),this));
  }
  endBumper = true;
  break;
 }
 default : break;
 }
 popup->addSeparator();

 // popup.add(new AbstractAction(tr("Remove"))
// {
//  /*public*/ void actionPerformed(ActionEvent e)
//  {
//   if (layoutEditor.removePositionablePoint(instance))
//   {
//    // user is serious about removing this point from the panel
//    remove();
//    dispose();
//   }
//  }
//  });
 QAction* actRemove = new QAction(tr("Remove"),this);
 popup->addAction(actRemove);
 connect(actRemove, SIGNAL(triggered()), this, SLOT(on_actRemove_triggered()));
#if 1 // TODO:
  if (blockBoundary)
  {
   QAction * act;
   if (getType() == EDGE_CONNECTOR)
   {
    popup->addAction(act = new AbstractAction(tr("Edit Link"),this));
//    {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            setLink();
//        }
//    });
    connect(act, SIGNAL(triggered()), this, SLOT(setLink()));
    }
    popup->addAction(act =new QAction(tr("Set Signals"), this));
//   {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                if (tools == NULL) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                // bring up signals at level crossing tool dialog
//                tools.setSignalsAtBlockBoundaryFromMenu(instance,
//                    layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//            });
   connect(act, SIGNAL(triggered()), this, SLOT(On_setSignals()));
   popup->addAction(act = new QAction(tr("Set Sensors"), this));
//   {
//       /*public*/ void actionPerformed(ActionEvent event) {
//           if (tools == NULL) {
//               tools = new LayoutEditorTools(layoutEditor);
//           }
//           // bring up signals at block boundary tool dialog
//           tools.setSensorsAtBlockBoundaryFromMenu(instance,
//               layoutEditor.sensorIconEditor,layoutEditor.sensorFrame);
//       }
//   });
     connect(act, SIGNAL(triggered()), this, SLOT(On_setSensors()));
   popup->addAction(act = new QAction(tr("Set Signal Masts"), this));
//   {
//       /*public*/ void actionPerformed(ActionEvent event) {
//           if (tools == NULL) {
//               tools = new LayoutEditorTools(layoutEditor);
//           }
//           // bring up signals at block boundary tool dialog
//           tools.setSignalMastsAtBlockBoundaryFromMenu(instance);
//       }
//   });
  }
  if (endBumper)
  {
   QAction* act;
        popup->addAction(act = new QAction(tr("Set Sensors"), this));
//        {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                if (tools == NULL) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                // bring up signals at block boundary tool dialog
//                tools.setSensorsAtBlockBoundaryFromMenu(instance,
//                    layoutEditor.sensorIconEditor,layoutEditor.sensorFrame);
//            }
//        });
          connect(act, SIGNAL(triggered()), this, SLOT(On_setSensors()));
        popup->addAction(act = new QAction(tr("Set Signal Masts"),this));
//        {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                if (tools == NULL) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                // bring up signals at block boundary tool dialog
//                tools.setSignalMastsAtBlockBoundaryFromMenu(instance);
//            }
//        });
        connect(act, SIGNAL(triggered()), this, SLOT(On_setSignalMasts()));
  }
#endif
  layoutEditor->setShowAlignmentMenu(popup);
  //popup.show(e.getComponent(), e.getX(), e.getY());
  //popup->exec(layoutEditor->panel()->mapFromScene(QPoint(e->scenePos().x(), e->scenePos().y())));
  popup->exec(QCursor::pos());
}

QString PositionablePoint::where(QGraphicsSceneMouseEvent* e) {
    return QString("%1").arg(+e->scenePos().x())+","+QString("%1").arg(e->scenePos().y());
}
void PositionablePoint::On_setSignals()
{
 if (tools == NULL)
 {
     tools = new LayoutEditorTools(layoutEditor);
 }
 // bring up signals at level crossing tool dialog
 tools->setSignalsAtBlockBoundaryFromMenu(instance,
     layoutEditor->signalIconEditor,layoutEditor->signalFrame);
}

void PositionablePoint::On_setSensors()
{
 if (tools == NULL) {
     tools = new LayoutEditorTools(layoutEditor);
 }
 // bring up signals at block boundary tool dialog
 tools->setSensorsAtBlockBoundaryFromMenu(instance,
     layoutEditor->sensorIconEditor,layoutEditor->sensorFrame);

}
void PositionablePoint::On_setSignalMasts()
{
 if (tools == NULL) {
     tools = new LayoutEditorTools(layoutEditor);
 }
 // bring up signals at block boundary tool dialog
 tools->setSignalMastsAtBlockBoundaryFromMenu(instance);

}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void PositionablePoint::dispose()
{
 if (popup != NULL) popup->clear();
 popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void PositionablePoint::remove()
{
 // remove from persistance by flagging inactive
 active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool PositionablePoint::isActive()
{
 return active;
}

void PositionablePoint::setLink()
{
 if (getConnect1() == NULL || getConnect1()->getLayoutBlock() == NULL) {
     log.error("Can not set link until we have a connecting track with a block assigned");
     return;
 }
 editLink = new JDialog();
 editLink->setTitle("EDIT LINK from " + getConnect1()->getLayoutBlock()->getDisplayName());
 QVBoxLayout* editLinkLayout = new QVBoxLayout(editLink);

 QWidget* container = new QWidget();
 //container.setLayout(new BorderLayout());
 QVBoxLayout* containerLayout = new QVBoxLayout(container);

 QPushButton* done = new QPushButton(tr("Done"));
// done.addActionListener(
//         (ActionEvent a) -> {
//     updateLink();
// });
 connect(done, SIGNAL(clicked(bool)), this, SLOT(updateLink()));
#if 0
 // make this button the default button (return or enter activates)
 // Note: We have to invoke this later because we don't currently have a root pane
 SwingUtilities.invokeLater(() -> {
     JRootPane rootPane = SwingUtilities.getRootPane(done);
     rootPane.setDefaultButton(done);
 });
#endif
 containerLayout->addWidget(getLinkPanel(),0, Qt::AlignTop);//, BorderLayout.NORTH);
 containerLayout->addWidget(done, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
 //container.revalidate();
 container->update();

 editLinkLayout->addWidget(container);

 editLink->adjustSize();
 //editLink.setModal(false);
 editLink->setVisible(true);
}

/*public*/ QWidget* PositionablePoint::getLinkPanel() {
    editorCombo = new QComboBox/*<JCBHandle<LayoutEditor>>*/();
    QList<LayoutEditor*>* panels = PanelMenu::instance()->getLayoutEditorPanelList();
    editorCombo->addItem("None", QVariant());
    if (panels->contains(layoutEditor)) {
        panels->removeOne(layoutEditor);
    }
    for (LayoutEditor* p : *panels) {
        //JCBHandle<LayoutEditor> h = new JCBHandle<LayoutEditor>(p);
        //editorCombo.addItem(h);
     editorCombo->addItem(p->getName(), VPtr<LayoutEditor>::asQVariant(p));
        if (p == getLinkedEditor()) {
            editorCombo->setCurrentText(p->getName());
        }
    }

//    ActionListener selectPanelListener = (ActionEvent a) -> {
//        updatePointBox();
//    };

//    editorCombo.addActionListener(selectPanelListener);
    connect(editorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePointBox()));
    QWidget* selectorPanel = new QWidget();
    QHBoxLayout* selectorPanelLayout = new QHBoxLayout(selectorPanel);
    selectorPanelLayout->addWidget(new QLabel("Select Panel"));
    selectorPanelLayout->addWidget(editorCombo);
    linkPointsBox = new QComboBox();
    updatePointBox();
    selectorPanelLayout->addWidget(new QLabel("Connecting Block"));
    selectorPanelLayout->addWidget(linkPointsBox);
    return selectorPanel;
}

void PositionablePoint::updatePointBox() {
    linkPointsBox->clear();
    pointList = new QList<PositionablePoint*>();
    if (editorCombo->currentIndex() == 0) {
        linkPointsBox->setEnabled(false);
        return;
    }
    int ourDir = getConnect1Dir();
    linkPointsBox->setEnabled(true);
    //for (PositionablePoint* p : VPtr<LayoutEditor*>::asPtr(editorCombo->currentData().item().pointList)
    for(int i = 1; i< editorCombo->count(); i++)
    {
     QVector<PositionablePoint*>* pointList = VPtr<LayoutEditor>::asPtr(editorCombo->itemData(i))->pointList;
     for(int j=0;  j< pointList->count(); j++)
     {
      PositionablePoint* p = pointList->at(j);
        if (p->getType() == EDGE_CONNECTOR) {
            if (p->getLinkedPoint() == this) {
                pointList->append(p);
                linkPointsBox->addItem(p->getConnect2()->getLayoutBlock()->getDisplayName());
                linkPointsBox->setCurrentText(p->getConnect2()->getLayoutBlock()->getDisplayName());
            } else if (p->getLinkedPoint() == NULL) {
                if (p->getConnect1() != NULL && p->getConnect1()->getLayoutBlock() != NULL) {
                    if (p->getConnect1()->getLayoutBlock() != getConnect1()->getLayoutBlock() && ourDir != p->getConnect1Dir()) {
                        pointList->append(p);
                        linkPointsBox->addItem(p->getConnect1()->getLayoutBlock()->getDisplayName());
                    }
                }
            }
        }
     }
    }
    editLink->adjustSize();
}

/*public*/ void PositionablePoint::updateLink() {
    if (editorCombo->currentIndex() == 0 || linkPointsBox->currentIndex() == -1) {
        if (getLinkedPoint() != NULL && getConnect2() != NULL) {
            QString removeremote = NULL;
            QString removelocal = NULL;
            if (getConnect1Dir() == Path::EAST || getConnect1Dir() == Path::SOUTH) {
                removeremote = getLinkedPoint()->getEastBoundSignal();
                removelocal = getWestBoundSignal();
                getLinkedPoint()->setEastBoundSignal("");
            } else {
                removeremote = getLinkedPoint()->getWestBoundSignal();
                removelocal = getEastBoundSignal();
                getLinkedPoint()->setWestBoundSignal("");
            }
            // removelocal and removeremote have been set here.
            if (removeremote != ("")) {
                SignalHead* sh = ((SignalHeadManager*) InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(removeremote);
                getLinkedEditor()->removeSignalHead(sh);
                BlockBossLogic::getStoppedObject(removeremote);
            }
            if (removelocal != ("")) {
                SignalHead* sh = ((SignalHeadManager*)  InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(removelocal);
                layoutEditor->removeSignalHead(sh);
                BlockBossLogic::getStoppedObject(removelocal);
            }
        }
        setLinkedPoint(NULL);
    } else {
        setLinkedPoint(pointList->at(linkPointsBox->currentIndex()));
    }
    editLink->setVisible(false);
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionablePoint.class.getName());

//}
void PositionablePoint::on_actRemove_triggered()
{
 if(layoutEditor->removePositionablePoint(this))
 {
  remove();
  dispose();
 }
}
void PositionablePoint::invalidate(QGraphicsScene* g2)
{
 if(item != NULL)
 {
  Q_ASSERT(item->scene()!=0);
  g2->removeItem(item);
  item = NULL;
 }
}

void PositionablePoint::draw(QGraphicsScene* g2)
{
    QColor color;
    QGraphicsRectItem* rectItem;
    switch (getType())
    {
     case PositionablePoint::ANCHOR:
      // nothing to draw unless in edit mode
      //if (isEditable())
      {
       // in edit mode, draw locater rectangle
       QPointF pt = getCoords();
       if ((getConnect1()==NULL) || (getConnect2()==NULL))
       {
        //g2.setColor(Color.red);
        color = QColor(Qt::red);
       }
       else
       {
        //g2.setColor(Color.green);
        color = QColor(Qt::green);
       }
 //      rectItem =  new QGraphicsRectItem(QRect(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2),0,g2);
 //      rectItem->setPen( QPen( color, 1, Qt::SolidLine ) );
       //QGraphicsRectItem* item = g2->addRect(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2,QPen( color, 1, Qt::SolidLine ));
       rectItem = new QGraphicsRectItem(QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2));
       rectItem->setPen(QPen( color, 1, Qt::SolidLine ));
       item = rectItem;
       item->setFlags(QGraphicsItem::ItemIsMovable);
      }
      break;
     case PositionablePoint::END_BUMPER:
      // nothing to draw unless in edit mode
     //if (isEditable())
     {
      // in edit mode, draw locater rectangle
      QPointF pt = getCoords();
      if (getConnect1()==NULL)
       {
        //g2.setColor(Color.red);
        color = QColor(Qt::red);
       }
       else
       {
        //g2.setColor(Color.green);
        color = QColor(Qt::green);
       }
       rectItem = new QGraphicsRectItem(QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
       rectItem->setPen( QPen( color, 1, Qt::SolidLine ) );
       item = rectItem;
       item->setFlags(QGraphicsItem::ItemIsMovable);
      }
      break;
     default:
     log.error("Illegal type of Positionable Point");
    }
    g2->addItem(item);
}
/*protected*/ int PositionablePoint::getConnect1Dir() {
 QPointF p1;
 if (getConnect1() == NULL) {
     return Path::NONE;
 }
 if (getConnect1()->getConnect1() == this) {
     p1 = layoutEditor->getCoords(getConnect1()->getConnect2(), getConnect1()->getType2());
 } else {
     p1 = layoutEditor->getCoords(getConnect1()->getConnect1(), getConnect1()->getType1());
 }

 double dh = getCoords().x() - p1.x();
 double dv = getCoords().y() - p1.y();
 int dir = Path::NORTH;
 double tanA;
 if (dv != 0.0) {
     tanA = qAbs(dh) / qAbs(dv);
 } else {
     tanA = 10.0;
 }
 if (tanA < 0.38268) {
     // track is mostly vertical
     if (dv < 0.0) {
         dir = Path::NORTH;
     } else {
         dir = Path::SOUTH;
     }
 } else if (tanA > 2.4142) {
     // track is mostly horizontal
     if (dh > 0.0) {
         dir = Path::EAST;
     } else {
         dir = Path::WEST;
     }
 } else {
     // track is between horizontal and vertical
     if ((dv > 0.0) && (dh > 0.0)) {
         dir = Path::SOUTH + Path::EAST;
     } else if ((dv > 0.0) && (dh < 0.0)) {
         dir = Path::SOUTH + Path::WEST;
     } else if ((dv < 0.0) && (dh < 0.0)) {
         dir = Path::NORTH + Path::WEST;
     } else {
         dir = Path::NORTH + Path::EAST;
     }
 }
 return dir;
}
