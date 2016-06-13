#include "levelxing.h"
#include "instancemanager.h"

LevelXing::LevelXing(QObject *parent) :
    QObject(parent)
{
}
/**
 * A LevelXing is two track segment on a layout that cross at an angle.
 * <P>
 * A LevelXing has four connection points, designated A, B, C, and D.
 *		At the crossing, A-C and B-D are straight segments.  A train proceeds
 *		through the crossing on either of these segments.
 * <P>
 * Each straight segment carries Block information.  A-C and B-D may be in the
 *		same or different Layout Blocks.
 * <P>
 * For drawing purposes, each LevelXing carries a center point and displacements
 *		for A and B.  The displacements for C = - the displacement for A, and the
 *		displacement for D = - the displacement for B.  The center point and these
 *      displacements may be adjusted by the user when in edit mode.
 * <P>
 * When LevelXings are first created, there are no connections.  Block information
 *		and connections are added when available.
 * <P>
 * Signal Head names are saved here to keep track of where signals are. LevelXing
 *		only serves as a storage place for signal head names. The names are placed here
 *		by Set Signals at Level Crossing in Tools menu.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 20802 $
 */

///*public*/ class LevelXing
//{

    // Defined text resource
    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");


/**
 * constructor method
 */
/*public*/ LevelXing::LevelXing(QString id, QPointF* c, LayoutEditor* myPanel)
{
 blockAC = NULL;
 blockBD = NULL;
 instance = NULL;
 layoutEditor = NULL;

 // persistent instances variables (saved between sessions)
 ident = "";
 blockNameAC = "";
 blockNameBD = "";
 signalAName = "";  // signal at A track junction
 signalBName = "";  // signal at B track junction
 signalCName = "";  // signal at C track junction
 signalDName = "";  // signal at D track junction

 signalAMastName = "";  // signal at A track junction
 signalBMastName = "";  // signal at B track junction
 signalCMastName = "";  // signal at C track junction
 signalDMastName = "";  // signal at D track junction

 sensorAName = "";  // sensor at A track junction
 sensorBName = "";  // sensor at B track junction
 sensorCName = "";  // sensor at C track junction
 sensorDName = "";  // sensor at D track junction    */

 sensorANamed = NULL; // sensor at A track junction
 sensorBNamed = NULL; // sensor at B track junction
 sensorCNamed = NULL; // sensor at C track junction
 sensorDNamed = NULL; // sensor at D track junction

 connectA = NULL;
 connectB = NULL;
 connectC = NULL;
 connectD = NULL;
 center = new QPointF(50.0,50.0);
 dispA = new QPointF(-20.0,0.0);
 dispB = new QPointF(-14.0,14.0);
 connectAName = "";
 connectBName = "";
 connectCName = "";
 connectDName = "";
 tBlockNameAC = "";
 tBlockNameBD = "";
 active = true;
 sml = new QVector<SignalMast*>();
 editAdditionalMenu = new QVector<QMenuItem*>(0);
 viewAdditionalMenu = new QVector<QMenuItem*>(0);

 editOpen = false;
 needsRedraw = false;
 needsBlockUpdate = false;
 popup = NULL;
 block1Name = new QTextEdit(16);
 block2Name = new QTextEdit(16);
 tools = NULL;
 editLevelXingFrame = NULL;

    instance = this;
    layoutEditor = myPanel;
    ident = id;
    center = c;
}


/*public*/ QString LevelXing::getSensorAName() {
    if(sensorANamed!=NULL)
        return sensorANamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorAName(QString sensorName)
{
 if(sensorName==NULL || sensorName==(""))
 {
  sensorANamed=NULL;
  return;
 }

 Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
 if (sensor != NULL)
 {
     sensorANamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
 }
 else
 {
  sensorANamed=NULL;
 }
}

/*public*/ QString LevelXing::getSensorBName() {
    if(sensorBNamed!=NULL)
        return sensorBNamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorBName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorBNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorBNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorBNamed=NULL;
    }
}

/*public*/ QString LevelXing::getSensorCName() {
    if(sensorCNamed!=NULL)
        return sensorCNamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorCName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorCNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorCNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorCNamed=NULL;
    }
}

/*public*/ QString LevelXing::getSensorDName() {
    if(sensorDNamed!=NULL)
        return sensorDNamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorDName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorDNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorDNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorDNamed=NULL;
    }
}

/*public*/ void LevelXing::setConnectA(QObject* o,int type) {
    connectA = o;
    if ( (connectA!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of A connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectB(QObject* o,int type) {
    connectB = o;
    if ( (connectB!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of B connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectC(QObject* o,int type) {
    connectC = o;
    if ( (connectC!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of C connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectD(QObject* o,int type) {
    connectD = o;
    if ( (connectD!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of D connection to levelXing - "+type);
    }
}
/*public*/ LayoutBlock* LevelXing::getLayoutBlockAC() {
    if ( (blockAC==NULL) && (blockNameAC.length()>0) ) {
        blockAC = layoutEditor->provideLayoutBlock(blockNameAC);
        if ( (blockAC!=NULL) && (blockAC==blockBD) )
                blockAC->decrementUse();
    }
    return blockAC;
}
/*public*/ LayoutBlock* LevelXing::getLayoutBlockBD() {
    if ( (blockBD==NULL) && (blockNameBD.length()>0) ) {
        blockBD = layoutEditor->provideLayoutBlock(blockNameBD);
        if ( (blockBD!=NULL) && (blockAC==blockBD) )
                blockBD->decrementUse();
    }
    return blockBD;
}
/*public*/ QPointF*  LevelXing::getCoordsA() {
    double x = center->x() + dispA->x();
    double y = center->y() + dispA->y();
    return new QPointF(x,y);
}
/*public*/ QPointF* LevelXing::getCoordsB() {
    double x = center->x() + dispB->x();
    double y = center->y() + dispB->y();
    return new QPointF(x,y);
}
/*public*/ QPointF* LevelXing::getCoordsC() {
    double x = center->x() - dispA->x();
    double y = center->y() - dispA->y();
    return new QPointF(x,y);
}
/*public*/ QPointF* LevelXing::getCoordsD() {
    double x = center->x() - dispB->x();
    double y = center->y() - dispB->y();
    return new QPointF(x,y);
}

/**
 * Add Layout Blocks
 */
/*public*/ void LevelXing::setLayoutBlockAC (LayoutBlock* b) {
    blockAC = b;
    if (b!=NULL) {
        blockNameAC = b->getID();
    }
}
/*public*/ void LevelXing::setLayoutBlockBD (LayoutBlock* b) {
    blockBD = b;
    if (b!=NULL) {
        blockNameBD = b->getID();
    }
}
/*private*/ void LevelXing::updateBlockInfo() {
    LayoutBlock* b1 = NULL;
    LayoutBlock* b2 = NULL;
    if (blockAC!=NULL) blockAC->updatePaths();
    if (connectA!=NULL) {
        b1 = ((TrackSegment*)connectA)->getLayoutBlock();
        if ((b1!=NULL)&&(b1!=blockAC)) b1->updatePaths();
    }
    if (connectC!=NULL) {
        b2 = ((TrackSegment*)connectC)->getLayoutBlock();
        if ((b2!=NULL)&&(b2!=blockAC)&&(b2!=b1)) b2->updatePaths();
    }
    if (blockBD!=NULL) blockBD->updatePaths();
    if (connectB!=NULL) {
        b1 = ((TrackSegment)connectB).getLayoutBlock();
        if ((b1!=NULL)&&(b1!=blockBD)) b1->updatePaths();
    }
    if (connectD!=NULL) {
        b2 = ((TrackSegment)connectD).getLayoutBlock();
        if ((b2!=NULL)&&(b2!=blockBD)&&(b2!=b1)) b2->updatePaths();
    }
    reCheckBlockBoundary();
}

/*public*/ void LevelXing::reCheckBlockBoundary(){
    if(connectA==NULL && connectB==NULL && connectC==NULL && connectD==NULL){
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
        if(getSignalAMastName()!=(""))
            removeSML(getSignalAMastName());
        if(getSignalBMastName()!=(""))
            removeSML(getSignalBMastName());
        if(getSignalCMastName()!=(""))
            removeSML(getSignalCMastName());
        if(getSignalDMastName()!=(""))
            removeSML(getSignalDMastName());
        setSignalAMastName("");
        setSignalBMastName("");
        setSignalCMastName("");
        setSignalDMastName("");
        setSensorAName("");
        setSensorBName("");
        setSensorCName("");
        setSensorDName("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any logics generated
    }  else if(connectA==NULL || connectB==NULL || connectC==NULL || connectD==NULL){
        //could still be in the process of rebuilding the point details
        return;
    }

    TrackSegment* trkA;
    TrackSegment* trkB;
    TrackSegment* trkC;
    TrackSegment* trkD;

    //if(connectA instanceof TrackSegment*)
    {
        trkA = (TrackSegment*)connectA;
        if(trkA->getLayoutBlock()==blockAC){
            setSignalAMastName("");
            setSensorAName("");
            if(getSignalAMastName()!=(""))
                removeSML(getSignalAMastName());
        }
    }
//    if(connectC instanceof TrackSegment*)
    {
        trkC = (TrackSegment*)connectC;
        if(trkC->getLayoutBlock()==blockAC){
            setSignalCMastName("");
            setSensorCName("");
            if(getSignalCMastName()!=(""))
                removeSML(getSignalCMastName());
        }
    }
//    if(connectB instanceof TrackSegment)
    {
        trkB = (TrackSegment*)connectB;
        if(trkB->getLayoutBlock()==blockBD){
            setSignalBMastName("");
            setSensorBName("");
            if(getSignalBMastName()!=(""))
                removeSML(getSignalBMastName());
        }
    }

//    if(connectD instanceof TrackSegment)
    {
        trkD = (TrackSegment*)connectC;
        if(trkD->getLayoutBlock()==blockBD){
            setSignalDMastName("");
            setSensorDName("");
            if(getSignalDMastName()!=(""))
                removeSML(getSignalDMastName());
        }
    }
}

void LevelXing::removeSML(QString signalMast){
    if(signalMast==NULL || signalMast!=(""))
        return;
    SignalMast* mast = InstanceManager::signalMastManagerInstance().getSignalMast(signalMast);
    if(InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled() && InstanceManager::signalMastLogicManagerInstance().isSignalMastUsed(mast)){
        SignallingGuiTools.removeSignalMastLogic(NULL, mast);
    }
}

/**
 * Methods to test if mainline track or not
 *  Returns true if either connecting track segment is mainline
 *  Defaults to not mainline if connecting track segments are missing
 */
/*public*/ bool LevelXing::isMainlineAC() {
    if ( ((connectA != NULL) && (((TrackSegment*)connectA)->getMainline())) ||
        ((connectB != NULL) && (((TrackSegment*)connectB)->getMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}
/*public*/ bool LevelXing::isMainlineBD() {
    if ( ((connectB != NULL) && (((TrackSegment)connectB).getMainline())) ||
        ((connectD != NULL) && (((TrackSegment)connectD).getMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Modify coordinates methods
 */
/*public*/ void setCoordsCenter(QPointF* p) {
    center = p;
}
/*public*/ void LevelXing::setCoordsA(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispA = new QPointF(-x,-y);
}
/*public*/ void LevelXing::setCoordsB(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispB = new QPointF(-x,-y);
}
/*public*/ void LevelXing::setCoordsC(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispA = new QPointF(x,y);
}
/*public*/ void LevelXing::setCoordsD(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispB = new QPointF(x,y);
}
/*public*/ void LevelXing::scaleCoords(float xFactor, float yFactor) {
    QPointF* pt = new QPointF(round(center->x()*xFactor),
                                    round(center->y()*yFactor));
    center = pt;
    pt = new QPointF(round(dispA->x()*xFactor),
                                    round(dispA->y()*yFactor));
    dispA = pt;
    pt = new QPointF(round(dispB->x()*xFactor),
                                    round(dispB->y()*yFactor));
    dispB = pt;
}
double round (double x) {
    int i = (int)(x+0.5);
    return i;
}

// initialization instance variables (used when loading a LayoutEditor)
///*public*/ QString connectAName = "";
///*public*/ QString connectBName = "";
///*public*/ QString connectCName = "";
///*public*/ QString connectDName = "";
///*public*/ QString tBlockNameAC = "";
///*public*/ QString tBlockNameBD = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void LevelXing::setObjects(LayoutEditor* p) {
    connectA = p->findTrackSegmentByName(connectAName);
    connectB = p->findTrackSegmentByName(connectBName);
    connectC = p->findTrackSegmentByName(connectCName);
    connectD = p->findTrackSegmentByName(connectDName);
    if (tBlockNameAC.length()>0) {
        blockAC = p->getLayoutBlock(tBlockNameAC);
        if (blockAC!=NULL) {
            blockNameAC = tBlockNameAC;
            if (blockAC!=blockBD)
                blockAC->incrementUse();
        }
        else {
            log.error("bad blocknameac '"+tBlockNameAC+"' in levelxing "+ident);
        }
    }
    if (tBlockNameBD.length()>0) {
        blockBD = p->getLayoutBlock(tBlockNameBD);
        if (blockBD!=NULL) {
            blockNameBD = tBlockNameBD;
            if (blockAC!=blockBD)
                blockBD.incrementUse();
        }
        else {
            log.error("bad blocknamebd '"+tBlockNameBD+"' in levelxing "+ident);
        }
    }
}


/**
 * Display popup menu for information and editing
 */
/*protected*/ void LevelXing::showPopUp(QMouseEvent* e, bool isEditable) {
    if (popup != NULL ) {
        popup->clear();
    }
    else {
        popup = new QMenu();
    }
    if(isEditable){
        popup.add(rb.getQString("LevelCrossing"));
        ->bool blockACAssigned = false;
        ->bool blockBDAssigned = false;
        if ( (blockNameAC==NULL) || (blockNameAC==("")) ) popup.add(rb.getQString("NoBlock1"));
        else {
            popup.add(rb.getQString("Block1ID")+": "+getLayoutBlockAC().getID());
            blockACAssigned = true;
        }
        if ( (blockNameBD==NULL) || (blockNameBD==("")) ) popup.add(rb.getQString("NoBlock2"));
        else {
            popup.add(rb.getQString("Block2ID")+": "+getLayoutBlockBD().getID());
            blockBDAssigned = true;
        }
        popup.add(new JSeparator(JSeparator.HORIZONTAL));
        popup.add(new AbstractAction(rb.getQString("Edit")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    editLevelXing(instance);
                }
            });
        popup.add(new AbstractAction(rb.getQString("Remove")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (layoutEditor.removeLevelXing(instance)) {
                        // Returned true if user did not cancel
                        remove();
                        dispose();
                    }
                }
            });
        if (blockACAssigned && blockBDAssigned) {
            popup.add(new AbstractAction(rb.getQString("SetSignals")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(layoutEditor);
                    }
                    // bring up signals at level crossing tool dialog
                    tools.setSignalsAtLevelXingFromMenu(instance,
                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
            });
        }

        final QStringList boundaryBetween = getBlockBoundaries();
        ->bool blockBoundaries = false;
        if (jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled()){
            if(blockACAssigned && !blockBDAssigned){
                popup.add(new AbstractAction(rb.getQString("ViewBlockRouting")) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockAC());
                        routeTableAction.actionPerformed(e);
                    }
                });
            } else if(!blockACAssigned && blockBDAssigned){
                popup.add(new AbstractAction(rb.getQString("ViewBlockRouting")) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockBD());
                        routeTableAction.actionPerformed(e);
                    }
                });
            } else if(blockACAssigned && blockBDAssigned){
                JMenu viewRouting = new JMenu(rb.getQString("ViewBlockRouting"));
                viewRouting.add(new AbstractAction( blockNameAC) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction( blockNameAC, getLayoutBlockAC());
                        routeTableAction.actionPerformed(e);
                    }
                });

                viewRouting.add(new AbstractAction(blockNameBD) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockNameBD, getLayoutBlockBD());
                        routeTableAction.actionPerformed(e);
                    }
                });

                popup.add(viewRouting);
            }
        }

        for (int i = 0; i<4; i++){
            if(boundaryBetween[i]!=NULL)
                blockBoundaries=true;
        }
        if (blockBoundaries){
             popup.add(new AbstractAction(rb.getQString("SetSignalMasts")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(layoutEditor);
                    }

                    tools.setSignalMastsAtLevelXingFromMenu(instance, boundaryBetween, layoutEditor.signalFrame);
                }
            });
             popup.add(new AbstractAction(rb.getQString("SetSensors")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(layoutEditor);
                    }

                    tools.setSensorsAtLevelXingFromMenu(instance, boundaryBetween, layoutEditor.sensorIconEditor, layoutEditor.sensorFrame);
                }
            });
        }

        layoutEditor.setShowAlignmentMenu(popup);
        popup.show(e.getComponent(), e->x(), e->y());
    } else if(!viewAdditionalMenu.isEmpty()){
        setAdditionalViewPopUpMenu(popup);
        popup.show(e.getComponent(), e->x(), e->y());
    }
}

/*public*/ QStringList LevelXing::getBlockBoundaries(){
    final QStringList boundaryBetween = new QString[4];

    if ( (blockNameAC!=NULL) && (!blockNameAC==("")) && (blockAC!=NULL) ){
        if ((connectA instanceof TrackSegment) && (((TrackSegment)connectA).getLayoutBlock()!=blockAC)){
            try {
                boundaryBetween[0]=(((TrackSegment)connectA).getLayoutBlock().getDisplayName()+ " - " + blockAC.getDisplayName());
            } catch (java.lang.NullPointerException e){
                //Can be considered normal if tracksegement hasn't yet been allocated a block
                log.debug("TrackSegement at connection A doesn't contain a layout block");
            }
        }
        if ((connectC instanceof TrackSegment) && (((TrackSegment)connectC).getLayoutBlock()!=blockAC)){
            try {
                boundaryBetween[2]=(((TrackSegment)connectC).getLayoutBlock().getDisplayName()+ " - " + blockAC.getDisplayName());
            } catch (java.lang.NullPointerException e){
                //Can be considered normal if tracksegement hasn't yet been allocated a block
                log.debug("TrackSegement at connection C doesn't contain a layout block");
            }
        }
    }
    if ( (blockNameBD!=NULL) && (!blockNameBD==("")) && (blockBD!=NULL) ){
        if ((connectB instanceof TrackSegment) && (((TrackSegment)connectB).getLayoutBlock()!=blockBD)){
            try {
                boundaryBetween[1]=(((TrackSegment)connectB).getLayoutBlock().getDisplayName()+ " - " + blockBD.getDisplayName());
            } catch (java.lang.NullPointerException e){
                //Can be considered normal if tracksegement hasn't yet been allocated a block
                log.debug("TrackSegement at connection B doesn't contain a layout block");
            }
        }
        if ((connectD instanceof TrackSegment) && (((TrackSegment)connectD).getLayoutBlock()!=blockBD)){
            try {
                boundaryBetween[3]=(((TrackSegment)connectD).getLayoutBlock().getDisplayName()+ " - " + blockBD.getDisplayName());
            } catch (java.lang.NullPointerException e){
                //Can be considered normal if tracksegement hasn't yet been allocated a block
                log.debug("TrackSegement at connection D doesn't contain a layout block");
            }
        }
    }
    return boundaryBetween;
}


/**
 * Edit a Level Crossing
 */
/*protected*/ void LevelXing::editLevelXing(LevelXing o) {
    if (editOpen) {
        editLevelXingFrame.setVisible(true);
        return;
    }
    // Initialize if needed
    if (editLevelXingFrame == NULL) {
        editLevelXingFrame = new JmriJFrame( rb.getQString("EditXing"), false, true );
        editLevelXingFrame.addHelpMenu("package.jmri.jmrit.display.EditLevelXing", true);
        editLevelXingFrame.setLocation(50,30);
        Container contentPane = editLevelXingFrame.getContentPane();
        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
        // setup block 1 name
        JPanel panel1 = new JPanel();
        panel1.setLayout(new FlowLayout());
        JLabel block1NameLabel = new JLabel( rb.getQString("Block1ID") );
        panel1.add(block1NameLabel);
        panel1.add(block1Name);
        block1Name.setToolTipText( rb.getQString("EditBlockNameHint") );
        contentPane.add(panel1);
        // setup block 2 name
        JPanel panel2 = new JPanel();
        panel2.setLayout(new FlowLayout());
        JLabel block2NameLabel = new JLabel( rb.getQString("Block2ID"));
        panel2.add(block2NameLabel);
        panel2.add(block2Name);
        block2Name.setToolTipText( rb.getQString("EditBlockNameHint") );
        contentPane.add(panel2);
        // set up Edit 1 Block and Edit 2 Block buttons
        JPanel panel4 = new JPanel();
        panel4.setLayout(new FlowLayout());
        // Edit 1 Block
        panel4.add(xingEdit1Block = new JButton(rb.getQString("EditBlock1")));
        xingEdit1Block.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                on_xingEdit1Block_clicked(e);
            }
        });
        xingEdit1Block.setToolTipText( rb.getQString("EditBlockHint") );
        // Edit 2 Block
        panel4.add(xingEdit2Block = new JButton(rb.getQString("EditBlock2")));
        xingEdit2Block.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                on_xingEdit2Block_clicked(e);
            }
        });
        xingEdit2Block.setToolTipText( rb.getQString("EditBlockHint") );
        contentPane.add(panel4);
        // set up Done and Cancel buttons
        JPanel panel5 = new JPanel();
        panel5.setLayout(new FlowLayout());
        panel5.add(xingEditDone = new JButton(rb.getQString("Done")));
        xingEditDone.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                on_xingEditDone_clicked(e);
            }
        });
        xingEditDone.setToolTipText( rb.getQString("DoneHint") );
        // Cancel
        panel5.add(xingEditCancel = new JButton(rb.getQString("Cancel")));
        xingEditCancel.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                on_xingEditCancel_clicked(e);
            }
        });
        xingEditCancel.setToolTipText( rb.getQString("CancelHint") );
        contentPane.add(panel5);
    }
    // Set up for Edit
    block1Name.setText(blockNameAC);
    block2Name.setText(blockNameBD);
    editLevelXingFrame.addWindowListener(new java.awt.event.WindowAdapter() {
            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                on_xingEditCancel_clicked(NULL);
            }
        });
    editLevelXingFrame.pack();
    editLevelXingFrame.setVisible(true);
    editOpen = true;
    needsBlockUpdate = false;
}
void LevelXing::on_xingEdit1Block_clicked()
{
    // check if a block name has been entered
    if (!blockNameAC==(block1Name->getText().trim()) ) {
        // block 1 has changed, if old block exists, decrement use
        if ( (blockAC!=NULL) && (blockAC!=blockBD) ) {
            blockAC.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameAC = block1Name.getText().trim();
        if ( (blockNameAC!=NULL) && (blockNameAC.length()>0)) {
            blockAC = layoutEditor.provideLayoutBlock(blockNameAC);
            if (blockAC!=NULL) {
                // decrement use if block was previously counted
                if ( (blockAC!=NULL) && (blockAC==blockBD) ) blockAC.decrementUse();
            }
            else {
                blockNameAC = "";
                block1Name.setText("");
            }
        }
        else {
            blockAC = NULL;
            blockNameAC = "";
        }
        needsRedraw = true;
        layoutEditor.auxTools.setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockAC==NULL) {
        JOptionPane.showMessageDialog(editLevelXingFrame,
                rb.getQString("Error1"),
                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockAC.editLayoutBlock(editLevelXingFrame);
    needsRedraw = true;
}
void LevelXing::on_xingEdit2Block_clicked()
{
    // check if a block name has been entered
    if (!blockNameBD==(block2Name->getText().trim()) ) {
        // block has changed, if old block exists, decrement use
        if ( (blockBD!=NULL) && (blockBD!=blockAC) ) {
            blockBD.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameBD = block2Name.getText().trim();
        if ( (blockNameBD!=NULL) && (blockNameBD.length()>0)) {
            blockBD = layoutEditor.provideLayoutBlock(blockNameBD);
            if (blockBD!=NULL) {
                // decrement use if block was previously counted
                if ( (blockBD!=NULL) && (blockAC==blockBD) ) blockBD.decrementUse();
            }
            else {
                blockNameBD = "";
                block2Name.setText("");
            }
        }
        else {
            blockBD = NULL;
            blockNameBD = "";
        }
        needsRedraw = true;
        layoutEditor.auxTools.setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockBD==NULL) {
        JOptionPane.showMessageDialog(editLevelXingFrame,
                rb.getQString("Error1"),
                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockBD.editLayoutBlock(editLevelXingFrame);
    needsRedraw = true;
}
void LevelXing::on_xingEditDone_clicked() {
    // check if Blocks changed
    if ( !blockNameAC==(block1Name->getText().trim()) ) {
        // block 1 has changed, if old block exists, decrement use
        if ( (blockAC!=NULL) && (blockAC!=blockBD) ) {
            blockAC.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameAC = block1Name.getText().trim();
        if ( (blockNameAC!=NULL) && (blockNameAC.length()>0)) {
            blockAC = layoutEditor.provideLayoutBlock(blockNameAC);
            if (blockAC!=NULL) {
                // decrement use if block was previously counted
                if ( (blockAC!=NULL) && (blockAC==blockBD) ) blockAC.decrementUse();
            }
            else {
                blockNameAC = "";
                block1Name.setText("");
            }
        }
        else {
            blockAC = NULL;
            blockNameAC = "";
        }
        needsRedraw = true;
        layoutEditor.auxTools.setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    if ( !blockNameBD==(block2Name.getText().trim()) ) {
        // block 2 has changed, if old block exists, decrement use
        if ( (blockBD!=NULL) && (blockBD!=blockAC) ) {
            blockBD.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameBD = block2Name.getText().trim();
        if ( (blockNameBD!=NULL) && (blockNameBD.length()>0)) {
            blockBD = layoutEditor.provideLayoutBlock(blockNameBD);
            if (blockBD!=NULL) {
                // decrement use if block was previously counted
                if ( (blockBD!=NULL) && (blockAC==blockBD) ) blockBD.decrementUse();
            }
            else {
                blockNameBD = "";
                block2Name.setText("");
            }
        }
        else {
            blockBD = NULL;
            blockNameBD = "";
        }
        needsRedraw = true;
        layoutEditor.auxTools.setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    editOpen = false;
    editLevelXingFrame.setVisible(false);
    editLevelXingFrame.dispose();
    editLevelXingFrame = NULL;
    if (needsBlockUpdate) updateBlockInfo();
    if (needsRedraw) {
        layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }
}
void LevelXing::on_xingEditCancel_clicked()
{
    editOpen = false;
    editLevelXingFrame.setVisible(false);
    editLevelXingFrame.dispose();
    editLevelXingFrame = NULL;
    if (needsBlockUpdate) updateBlockInfo();
    if (needsRedraw) {
        layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }
}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void LevelXing::dispose() {
    if (popup != NULL) popup.removeAll();
    popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void LevelXing::remove() {
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool LevelXing::isActive() {
    return active;
}


/*public*/ void LevelXing::addSignalMastLogic(SignalMast* sm){
    if (sml.contains(sm))
        return;
    if(sml.isEmpty()){
        sml.add(sm);
        return;
    }
    SignalMastLogic sl = jmri.InstanceManager.signalMastLogicManagerInstance().getSignalMastLogic(sm);
    for(int i = 0; i<sml.size(); i++){
        SignalMastLogic s = jmri.InstanceManager.signalMastLogicManagerInstance().getSignalMastLogic(sml.get(i));
        if (s!=NULL){
            s.setConflictingLogic(sm, this);
        }
        sl.setConflictingLogic(sml.get(i), this);
    }
    sml.add(sm);
}

/*public*/ void LevelXing::removeSignalMastLogic(SignalMast* sm){
    if(!sml.contains(sm))
        return;
    sml.remove(sm);
    if(sml.isEmpty()){
        return;
    }
    for(int i = 0; i<sml.size(); i++){
        SignalMastLogic s = jmri.InstanceManager.signalMastLogicManagerInstance().getSignalMastLogic(sm);
        if (s!=NULL)
            s.removeConflictingLogic(sm, this);
    }
}


/*public*/ void LevelXing::addEditPopUpMenu(JMenuItem menu){
    if(!editAdditionalMenu.contains(menu)){
        editAdditionalMenu.add(menu);
    }
}

/*public*/ void LevelXing::addViewPopUpMenu(JMenuItem menu){
    if(!viewAdditionalMenu.contains(menu)){
        viewAdditionalMenu.add(menu);
    }
}

/*public*/ void LevelXing::setAdditionalEditPopUpMenu(JPopupMenu popup){
    if(editAdditionalMenu.isEmpty())
        return;
    popup.addSeparator();
    for(JMenuItem mi:editAdditionalMenu){
        popup.add(mi);
    }
}

/*public*/ void LevelXing::setAdditionalViewPopUpMenu(JPopupMenu popup){
    if(viewAdditionalMenu.isEmpty())
        return;
    popup.addSeparator();
    for(JMenuItem mi:viewAdditionalMenu){
        popup.add(mi);
    }
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LevelXing.class.getName());

