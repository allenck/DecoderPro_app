#include "tracksegment.h"
#include "edittracksegmentdlg.h"
#include <QMenu>
#include "abstractaction.h"
#include "layoutblockroutetableaction.h"
#include "layoutturntable.h"
//TrackSegment::TrackSegment(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * TrackSegment is a segment of track on a layout linking two nodes of the
 *     layout.  A node may be a LayoutTurnout, a LevelXing or a PositionablePoint.
 * <P>
 * PositionablePoints have 1 or 2 connection points. LayoutTurnouts
 *		have 3 or 4 (crossovers) connection points, designated A, B, C, and D.
 *		LevelXing's have 4 connection points, designated A, B, C, and D.
 * <P>
 * TrackSegments carry the connectivity information between the three types of nodes. Track Segments
 *		serve as the lines in a graph which shows layout connectivity. For the connectivity graph
 *		to be valid, all connections between nodes must be via TrackSegments.
 * <P>
 * TrackSegments carry Block information, as do LayoutTurnouts and LevelXings.
 * <P>
 * TrackSegments may be drawn as dashed lines or solid lines.  In addition TrackSegments
 *		may be hidden when the panel is not in EditMode.
 *
 * @author Dave Duchamp Copyright (c) 2004-2009
 * @version $Revision: 20715 $
 */

///*public*/ class TrackSegment
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");


/*public*/
TrackSegment::TrackSegment(QString id, QObject* c1, int t1, QObject* c2, int t2, bool dash, bool main, LayoutEditor* myPanel)
{
 init(id);
 layoutEditor = myPanel;
 // validate input
 if ( (c1==NULL) || (c2==NULL) )
 {
  log.error("Invalid object in TrackSegment constructor call - "+id);
 }
 connect1 = c1;
 connect2 = c2;
 if ( (t1<LayoutEditor::POS_POINT) ||
             ( ((t1>LayoutEditor::LEVEL_XING_D) && (t1<LayoutEditor::SLIP_A))
                 || ((t1>LayoutEditor::SLIP_D) && (t1<LayoutEditor::TURNTABLE_RAY_OFFSET)) ) )
 {
  log.error("Invalid connect type 1 in TrackSegment constructor - "+id);
 }
 else
 {
  type1 = t1;
 }
 if ( (t2<LayoutEditor::POS_POINT) ||
             ( ((t2>LayoutEditor::LEVEL_XING_D) && (t2<LayoutEditor::SLIP_A))
                 || ((t2>LayoutEditor::SLIP_D) && (t2<LayoutEditor::TURNTABLE_RAY_OFFSET)) ) )
 {
  log.error("Invalid connect type 2 in TrackSegment constructor - "+id);
 }
 else
 {
  type2 = t2;
 }
 instance = this;
 ident = id;
 dashed = dash;
 mainline = main;
//    arc = false;
//    flip = false;
//    angle = 0.0D;
//    circle = false;
}
// alternate constructor for loading layout editor panels
/*public*/
TrackSegment::TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor* myPanel)
{
 init(id);
 layoutEditor = myPanel;
 tConnect1Name = c1Name;
 type1 = t1;
 tConnect2Name = c2Name;
 type2 = t2;
 instance = this;
 ident = id;
 dashed = dash;
 mainline = main;
 hidden = hide;
}
void TrackSegment::init(QString id)
{
// operational instance variables (not saved between sessions)
 setObjectName("TS_"+id);

 block = NULL;
 instance = NULL;
 layoutEditor = NULL;
 item = NULL;
 circleItem = NULL;
 trackOval = NULL;
 showConstructionLine = SHOWCON;

// persistent instances variables (saved between sessions)
 QString ident = "";
 blockName = "";
 connect1 = NULL;
 type1 = 0;
 connect2 = NULL;
 type2 = 0;
 dashed = false;
 mainline = false;
 hidden = false;
 arc = false;
 flip = false;
 angle =0.0;
 circle=false;
 changed=false;
 active = true;
 popup = NULL;
 needsRedraw = false;

}
/**
 * Accessor methods
*/
/*public*/ QString TrackSegment::getID()
{
       return ident;
}

/*public*/ QString TrackSegment::getBlockName() {
    return blockName;
}

/*public*/ int TrackSegment::getType1() {
    return type1;
}

/*public*/ int TrackSegment::getType2() {
    return type2;
}

/*public*/ QObject* TrackSegment::getConnect1() {
    return connect1;
}

/*public*/ QObject* TrackSegment::getConnect2() {
    return connect2;
}

/*protected*/ void TrackSegment::setNewConnect1(QObject* o, int type) {
    connect1 = o;
    type1 = type;

}

/*protected*/ void TrackSegment::setNewConnect2(QObject* o, int type) {
    connect2 = o;
    type2 = type;
}

/*public*/ bool TrackSegment::getDashed()
{
    return dashed;
}

/*public*/ void TrackSegment::setDashed(bool dash) {
    dashed = dash;
}

/*public*/ bool TrackSegment::getHidden() {
    return hidden;
}

/*public*/ void TrackSegment::setHidden(bool hide) {
    hidden = hide;
}

/*public*/ bool TrackSegment::getMainline() {
    return mainline;
}

/*public*/ void TrackSegment::setMainline(bool main) {
    mainline = main;
}

/*public*/ void TrackSegment::setArc(bool boo) {
    arc = boo;
    changed=true;
}
//    /*public*/ bool getCircle() {return circle;}
/*public*/ void
TrackSegment::setCircle(bool boo) {
    circle = boo;
    changed=true;
}
//    /*public*/ bool getFlip() {return flip;}
/*public*/ void
TrackSegment::setFlip(bool boo) {
    flip = boo;
    changed=true;
}
///*public*/ int getStartAngle() {return startangle;}
///*public*/ void setStartAngle(int x) {startangle = x;}
//    /*public*/ double getAngle() {return angle;}
/*public*/ void
TrackSegment::setAngle(double x)
{
// GT 8-OCT-2009 ==== Changed arcs maths : Start
//        if (angle>180) // ???
 if (x>180.0)
  x=180.0;
 else if (x < 0.0)
  x = 0.0;
// GT 8-OCT-2009 ==== Changed arcs maths : End
  angle = x;
  changed=true;
}
//This method is used to determine if we need to redraw a curved piece of track
//It saves having to recalculate the circle details each time.
//    /*public*/ bool trackNeedsRedraw() { return changed; }
//    /*public*/ void trackRedrawn() { changed = false; }
///*public*/ int getRadius() {return radius;}
///*public*/ void setRadius(int x) {radius = x;}

/*public*/ LayoutBlock*
TrackSegment::getLayoutBlock()
{
 if ( (block==NULL) && (blockName!=NULL) && (blockName!="") )
 {
  block = layoutEditor->provideLayoutBlock(blockName);
 }
 return block;
}
//    /*public*/ QString getConnect1Name() {return getConnectName(connect1,type1);}
//    /*public*/ QString getConnect2Name() {return getConnectName(connect2,type2);}

/*private*/ QString
TrackSegment::getConnectName(QObject* o,int type)
{
 if (type == LayoutEditor::POS_POINT)
 {
  return ((PositionablePoint*)o)->getID();
 }
 if ( (type == LayoutEditor::TURNOUT_A) || (type == LayoutEditor::TURNOUT_B) ||
         (type == LayoutEditor::TURNOUT_C) || (type == LayoutEditor::TURNOUT_D) )
 {
  return ((LayoutTurnout*)o)->getName();
 }
 if ( (type == LayoutEditor::LEVEL_XING_A) || (type == LayoutEditor::LEVEL_XING_B) ||
         (type == LayoutEditor::LEVEL_XING_C) || (type == LayoutEditor::LEVEL_XING_D) )
 {
  return ((LevelXing*)o)->getID();
 }
 if ( (type == LayoutEditor::SLIP_A) || (type == LayoutEditor::SLIP_B) ||
         (type == LayoutEditor::SLIP_C) || (type == LayoutEditor::SLIP_D) )
 {
  return ((LayoutSlip*)o)->getName();
 }
#if 1 //TODO

 if (type>=LayoutEditor::TURNTABLE_RAY_OFFSET) {
     return ((LayoutTurntable*)o)->getID();
 }
#endif
 return "";
}
// initialization instance variables (used when loading a LayoutEditor)
//	public String tBlockName = "";
//	public String tConnect1Name = "";
//	public String tConnect2Name = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void TrackSegment::setObjects(LayoutEditor* p)
{
 if (tBlockName.length()>0)
 {
  block = p->getLayoutBlock(tBlockName);
  if (block!=NULL)
  {
   blockName = tBlockName;
   block->incrementUse();
  }
  else
  {
   log.error("bad blockname '"+tBlockName+"' in tracksegment "+ident);
  }
 }
 connect1 = p->findObjectByTypeAndName(type1,tConnect1Name);
 connect2 = p->findObjectByTypeAndName(type2,tConnect2Name);
}

/**
 * Set Up a Layout Block for a Track Segment
 */
/*public*/ void TrackSegment::setLayoutBlock (LayoutBlock* b) {
    block = b;
    if (b!=NULL) {
        blockName = b->getID();
    }
}
/*public*/ void TrackSegment::setLayoutBlockByName (QString name) {
    blockName = name;
}
/*protected*/ void TrackSegment::updateBlockInfo()
{
 if (block!=NULL)
  block->updatePaths();
 LayoutBlock* b1 = getBlock(connect1,type1);
 if ((b1!=NULL)&&(b1!=block))
  b1->updatePaths();
 LayoutBlock* b2 = getBlock(connect2,type2);
 if ((b2!=NULL)&&(b2!=block)&&(b2!=b1))
  b2->updatePaths();
 //if(getConnect1() instanceof PositionablePoint)
 if(qobject_cast<PositionablePoint*>(getConnect1())!= NULL)
  ((PositionablePoint*)getConnect1())->reCheckBlockBoundary();
 else
  //if(getConnect1() instanceof LayoutTurnout)
 if(qobject_cast<LayoutTurnout*>(getConnect1())!= NULL)
  ((LayoutTurnout*)getConnect1())->reCheckBlockBoundary();
 else
   //if(getConnect1() instanceof LevelXing)
 if(qobject_cast<LevelXing*>(getConnect1())!= NULL)
  ((LevelXing*)getConnect1())->reCheckBlockBoundary();
  else
    //if(getConnect1() instanceof LayoutSlip)
     if(qobject_cast<LayoutSlip*>(getConnect1()) !=NULL)
  ((LayoutSlip*)getConnect1())->reCheckBlockBoundary();

    //if(getConnect2() instanceof PositionablePoint)
 if(qobject_cast<PositionablePoint*>(getConnect2())!= NULL)
  ((PositionablePoint*)getConnect2())->reCheckBlockBoundary();
 else
    //if(getConnect2() instanceof LayoutTurnout)
 if(qobject_cast<LayoutTurnout*>(getConnect2())!= NULL)
  ((LayoutTurnout*)getConnect2())->reCheckBlockBoundary();
 else
    //if(getConnect2() instanceof LevelXing)
 if(qobject_cast<LevelXing*>(getConnect2())!= NULL)
  ((LevelXing*)getConnect2())->reCheckBlockBoundary();
 else
     //if(getConnect2() instanceof LayoutSlip)
 if(qobject_cast<LayoutSlip*>(getConnect2()) !=NULL)
  ((LayoutSlip*)getConnect2())->reCheckBlockBoundary();
}

/*private*/ LayoutBlock* TrackSegment::getBlock (QObject* connect, int type)
{
 if (connect==NULL) return NULL;
 if (type==LayoutEditor::POS_POINT)
 {
  PositionablePoint* p = (PositionablePoint*)connect;
  if (p->getConnect1()!=instance)
  {
   if (p->getConnect1()!=NULL) return (p->getConnect1()->getLayoutBlock());
    else return NULL;
  }
  else
  {
   if (p->getConnect2()!=NULL) return (p->getConnect2()->getLayoutBlock());
   else return NULL;
  }
 }
 else
 {
  return (layoutEditor->getAffectedBlock(connect,type));
 }
}


/**
 * Display popup menu for information and editing
 */
/*protected*/ void TrackSegment::showPopUp(QGraphicsSceneMouseEvent* /*e*/)
{
 if (popup != NULL )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }
 if (!dashed) popup->addAction(new QAction(tr("Style")+" - "+tr("Solid"),this));
    else popup->addAction(new QAction(tr("Style")+" - "+tr("Dashed"),this));
    if (!mainline) popup->addAction(new QAction(tr("NotMainline"),this));
    else popup->addAction(new QAction(tr("Mainline"),this));
    if (blockName==("")) popup->addAction(new QAction(tr("NoBlock"),this));
    else popup->addAction(new QAction(tr("Block")+": "+getLayoutBlock()->getID(),this));
    if (hidden) popup->addAction(new QAction(tr("Hidden"),this));
    else popup->addAction(new QAction(tr("NotHidden"),this));
    popup->addSeparator();
//    popup.add(new AbstractAction(rb.getQString("Edit")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editTrackSegment();
//            }
//        });
    QAction* editAction = new QAction(tr("Edit"),this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(on_actionEdit_triggered()));
    popup->addAction(editAction);
//    popup.add(new AbstractAction(rb.getQString("Remove")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                layoutEditor.removeTrackSegment(instance);
//                remove();
//                dispose();
//            }
//        });
    QAction* removeAction = new QAction(tr("Remove"),this);
    popup->addAction(removeAction);
    connect(removeAction, SIGNAL(triggered()), this, SLOT(on_actionRemove()));

    QMenu* lineType = new QMenu(tr("Change To"));
    QActionGroup* actGrp = new QActionGroup(this);
    actGrp->setExclusive(true);
    popup->addMenu(lineType);
    QAction* lineAction = new QAction(tr("Line"),this);
    lineAction->setCheckable(true);
    lineAction->setChecked(!arc && !circle);
    lineAction->setData(0);
    lineType->addAction(lineAction);
    actGrp->addAction(lineAction);
//    lineType.add(new AbstractAction("Line") {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeType(0);
//            }
//    });
    QAction* circleAction = new QAction(tr("Circle"),this);
    circleAction->setCheckable(true);
    circleAction->setChecked(circle && arc);
    circleAction->setData(1);
    lineType->addAction(circleAction);
    actGrp->addAction(circleAction);
//    lineType.add(new AbstractAction("Circle") {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeType(1);
//        }
////    });
    QAction* ellipseAction = new QAction(tr("Ellipse"),this);
    ellipseAction->setCheckable(true);
    ellipseAction->setChecked(arc && !circle);
    ellipseAction->setData(2);
    lineType->addAction(ellipseAction);
    actGrp->addAction(ellipseAction);
//    lineType.add(new AbstractAction("Elipse") {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeType(2);
//        }
//    });
    connect(actGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_changeType(QAction*)));
    popup->addMenu(lineType);
    if (getArc())
    {
//        popup.add(new AbstractAction("Flip Angle") {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    flipAngle();
//                }
//            });
     QAction* arcAction = new QAction(tr("Flip Angle"), this);
     lineType->addAction(arcAction);
     connect(arcAction, SIGNAL(triggered()), this, SLOT(flipAngle()));
    }
#if 1 // TODO:
//    if ((blockName!=("")) && (InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled()))
    if ((blockName!=("")) && layoutEditor->layoutBlockManager->isAdvancedRoutingEnabled())
    {
     TSAbstractAction* act;
     popup->addAction(act = new TSAbstractAction(tr("View Block Routing"), this));
//     {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
//                routeTableAction.actionPerformed(e);
//            }
//        });
//      QAction* routeTableAction = new QAction(tr("ViewBlockRouting"),this);
//      popup->addAction(routeTableAction);
     connect(act, SIGNAL(triggered()), act, SLOT(actionPerformed()));
    }
#endif
    //popup.show(e.getComponent(), e.getX(), e.getY());
    popup->exec(QCursor::pos());
}
TSAbstractAction::TSAbstractAction(QString name, QObject *parent)
 : AbstractAction(name, parent) {}

/*public*/ void TSAbstractAction::actionPerformed(ActionEvent* e)
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", ((TrackSegment*)parent())->getLayoutBlock());
 routeTableAction->actionPerformed();
}

void TrackSegment::on_changeType(QAction *act)
{
 changeType(act->data().toInt());
}

void TrackSegment::on_actionRemove()
{
 layoutEditor->removeTrackSegment(instance);
 remove();
 dispose();
}

void TrackSegment::changeType(int choice)
{
 switch (choice)
 {
    case 0 :    setArc(false);
                setAngle(0.0);
                setCircle(false);
                break;
    case 1 :    setArc(true);
                setAngle(90.0);
                setCircle(true);
                break;
    case 2 :    setArc(true);
                setAngle(90.0);
                setCircle(false);
                break;
    default : break;
 }
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
 //layoutEditor->repaint();
}

void TrackSegment::flipAngle()
{
    if(getFlip()){
        setFlip(false);
    } else{
        setFlip(true);
    }
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
}
#if 0 // now implemented in edittracksegmentdlg
    // variables for Edit Track Segment pane
 // NOTE: these are now implemented in EditTrackSegmentDlg.
    /*private*/ JmriJFrame editTrackSegmentFrame = NULL;
    /*private*/ JComboBox dashedBox = new JComboBox();
    /*private*/ int dashedIndex;
    /*private*/ int solidIndex;
    /*private*/ JComboBox mainlineBox = new JComboBox();
    /*private*/ int mainlineTrackIndex;
    /*private*/ int sideTrackIndex;
    /*private*/ JTextField blockNameField = new JTextField(16);
    /*private*/ JTextField arcField = new JTextField(5);
    /*private*/ JCheckBox hiddenBox = new JCheckBox(rb.getQString("HideTrack"));
    /*private*/ JButton segmentEditBlock;
    /*private*/ JButton segmentEditDone;
    /*private*/ JButton segmentEditCancel;
    /*private*/ bool editOpen = false;

    /**
     * Edit a Track Segment
     */
    protected void editTrackSegment() {
        if (editOpen) {
            editTrackSegmentFrame.setVisible(true);
            return;
        }
        // Initialize if needed
        if (editTrackSegmentFrame == NULL) {
            editTrackSegmentFrame = new JmriJFrame( rb.getQString("EditTrackSegment"), false, true );
            editTrackSegmentFrame.addHelpMenu("package.jmri.jmrit.display.EditTrackSegment", true);
            editTrackSegmentFrame.setLocation(50,30);
            Container contentPane = editTrackSegmentFrame.getContentPane();
            contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
            // add dashed choice
            JPanel panel31 = new JPanel();
            panel31.setLayout(new FlowLayout());
            dashedBox.removeAllItems();
            dashedBox.addItem( rb.getQString("Solid") );
            solidIndex = 0;
            dashedBox.addItem( rb.getQString("Dashed") );
            dashedIndex = 1;
            dashedBox.setToolTipText(rb.getQString("DashedToolTip"));
            panel31.add (new JLabel(rb.getQString("Style")+" : "));
            panel31.add (dashedBox);
            contentPane.add(panel31);
            // add mainline choice
            JPanel panel32 = new JPanel();
            panel32.setLayout(new FlowLayout());
            mainlineBox.removeAllItems();
            mainlineBox.addItem( rb.getQString("Mainline") );
            mainlineTrackIndex = 0;
            mainlineBox.addItem( rb.getQString("NotMainline") );
            sideTrackIndex = 1;
            mainlineBox.setToolTipText(rb.getQString("MainlineToolTip"));
            panel32.add (mainlineBox);
            contentPane.add(panel32);
            // add hidden choice
            JPanel panel33 = new JPanel();
            panel33.setLayout(new FlowLayout());
            hiddenBox.setToolTipText(rb.getQString("HiddenToolTip"));
            panel33.add (hiddenBox);
            contentPane.add(panel33);
            // setup block name
            JPanel panel2 = new JPanel();
            panel2.setLayout(new FlowLayout());
            JLabel blockNameLabel = new JLabel( rb.getQString("BlockID"));
            panel2.add(blockNameLabel);
            panel2.add(blockNameField);
            blockNameField.setToolTipText( rb.getQString("EditBlockNameHint") );
            contentPane.add(panel2);
            if((getArc())&&(getCircle())){
                JPanel panel20 = new JPanel();
                panel20.setLayout(new FlowLayout());
                JLabel arcLabel = new JLabel( "Set Arc Angle");
                panel20.add(arcLabel);
                panel20.add(arcField);
                arcField.setToolTipText( "Set Arc Angle" );
                contentPane.add(panel20);
                arcField.setText(getAngle());
            }
            // set up Edit Block, Done and Cancel buttons
            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            // Edit Block
            panel5.add(segmentEditBlock = new JButton(rb.getQString("EditBlock")));
            segmentEditBlock.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    segmentEditBlockPressed(e);
                }
            });
            segmentEditBlock.setToolTipText( rb.getQString("EditBlockHint") );
            panel5.add(segmentEditDone = new JButton(rb.getQString("Done")));
            segmentEditDone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    segmentEditDonePressed(e);
                }
            });
            segmentEditDone.setToolTipText( rb.getQString("DoneHint") );
            // Cancel
            panel5.add(segmentEditCancel = new JButton(rb.getQString("Cancel")));
            segmentEditCancel.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    segmentEditCancelPressed(e);
                }
            });
            segmentEditCancel.setToolTipText( rb.getQString("CancelHint") );
            contentPane.add(panel5);
        }
        // Set up for Edit
        if (mainline)
            mainlineBox.setSelectedIndex(mainlineTrackIndex);
        else
            mainlineBox.setSelectedIndex(sideTrackIndex);
        if (dashed)
            dashedBox.setSelectedIndex(dashedIndex);
        else
            dashedBox.setSelectedIndex(solidIndex);
        hiddenBox.setSelected(hidden);
        blockNameField.setText(blockName);
        editTrackSegmentFrame.addWindowListener(new java.awt.event.WindowAdapter() {
                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                    segmentEditCancelPressed(NULL);
                }
            });
        editTrackSegmentFrame.pack();
        editTrackSegmentFrame.setVisible(true);
        editOpen = true;
    }
    void segmentEditBlockPressed(ActionEvent a) {
        // check if a block name has been entered
        if (!blockName.equals(blockNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if (block!=NULL) {
                block.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockName = blockNameField.getText().trim();
            block = layoutEditor.provideLayoutBlock(blockName);
            if (block == NULL) {
                blockName = "";
            }
            needsRedraw = true;
            layoutEditor.auxTools.setBlockConnectivityChanged();
            updateBlockInfo();
        }
        // check if a block exists to edit
        if (block==NULL) {
            JOptionPane.showMessageDialog(editTrackSegmentFrame,
                    rb.getQString("Error1"),
                    rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        block.editLayoutBlock(editTrackSegmentFrame);
        layoutEditor.setDirty();
        needsRedraw = true;
    }
    void segmentEditDonePressed(ActionEvent a) {
        // set dashed
        bool oldDashed = dashed;
        if (dashedBox.getSelectedIndex() == dashedIndex) dashed = true;
        else dashed = false;
        // set mainline
        bool oldMainline = mainline;
        if (mainlineBox.getSelectedIndex() == mainlineTrackIndex) mainline = true;
        else mainline = false;
        // set hidden
        bool oldHidden = hidden;
        hidden = hiddenBox.isSelected();
        if(getArc()){
            //setAngle(Integer.parseInt(arcField.getText()));
            //needsRedraw = true;
            try {
                double newAngle = Double.parseDouble(arcField.getText());
                setAngle(newAngle);
                needsRedraw = true;
            }
            catch (NumberFormatException e) {
                arcField.setText(getAngle());
            }
        }
        // check if anything changed
        if ( (oldDashed!=dashed) || (oldMainline!=mainline) || (oldHidden!=hidden) )
            needsRedraw = true;
        // check if Block changed
        if ( !blockName.equals(blockNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if (block!=NULL) {
                block.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockName = blockNameField.getText().trim();
            block = layoutEditor.provideLayoutBlock(blockName);
            if (block == NULL) {
                blockName = "";
            }
            needsRedraw = true;
            layoutEditor.auxTools.setBlockConnectivityChanged();
            updateBlockInfo();
        }
        editOpen = false;
        editTrackSegmentFrame.setVisible(false);
        editTrackSegmentFrame.dispose();
        editTrackSegmentFrame = NULL;
        if (needsRedraw) layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }
    void segmentEditCancelPressed(ActionEvent a) {
        editOpen = false;
        editTrackSegmentFrame.setVisible(false);
        editTrackSegmentFrame.dispose();
        editTrackSegmentFrame = NULL;
        if (needsRedraw) {
            layoutEditor.setDirty();
            layoutEditor.redrawPanel();
        }
    }
#endif
/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void TrackSegment::dispose() {
//        if (popup != NULL) popup.removeAll();
//        popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void TrackSegment::remove() {
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool TrackSegment::isActive() {
    return active;
}

/**
* The following are used only as a temporary store after a circle or arc has been calculated.
* This prevents the need to recalculate the values each time a re-draw is required.
*/

/*public*/ QPointF TrackSegment::getTmpPt1(){
    return pt1;
}
/*public*/ QPointF TrackSegment::getTmpPt2(){
    return pt2;
}

/*public*/ void TrackSegment::setTmpPt1(QPointF Pt1){
    pt1 = Pt1;
    changed= true;
}
/*public*/ void TrackSegment::setTmpPt2(QPointF Pt2){
    pt2 = Pt2;
    changed= true;
}

///*private*/ int startadj;

/*public*/ double TrackSegment::getCX(){
    return cX;
}

/*public*/ void TrackSegment::setCX(double CX){
    cX = CX;
}

/*public*/ double TrackSegment::getCY(){
    return cY;
}

/*public*/ void TrackSegment::setCY(double CY){
    cY = CY;
}

/*public*/ double TrackSegment::getCW(){
    return cW;
}

/*public*/ void TrackSegment::setCW(double CW){
    cW = CW;
}

/*public*/ double TrackSegment::getCH(){
    return cH;
}

/*public*/ void TrackSegment::setCH(double CH){
    cH = CH;
}

/*public*/ double TrackSegment::getStartadj(){
    return startadj;
}

/*public*/ void TrackSegment::setStartadj(double Startadj){
    startadj = Startadj;
}

/*public*/ double TrackSegment::getCentreX(){
    return centreX;
}

/*public*/ void TrackSegment::setCentreX(double CentreX){
    centreX = CentreX;
}

/*public*/ double TrackSegment::getCentreY(){
    return centreY;
}

/*public*/ void TrackSegment::setCentreY(double CentreY){
    centreY = CentreY;
}

/*public*/ double TrackSegment::getTmpAngle(){
    return tmpangle;
}

/*public*/ void TrackSegment::setTmpAngle(double TmpAngle){
    tmpangle = TmpAngle;
}

/*public*/ QPointF TrackSegment::getCoordsCenterCircle() { return  QPointF(getCentreX(),getCentreY()); }

/*public*/ double TrackSegment::getChordLength() { return chordLength; }
/*public*/ void TrackSegment::setChordLength(double chord) { chordLength=chord;}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TrackSegment.class.getName());

//}

void TrackSegment::on_actionEdit_triggered()
{
 EditTrackSegmentDlg* dlg = new EditTrackSegmentDlg(this, layoutEditor);
 dlg->show();
}
void TrackSegment::invalidate(QGraphicsScene *g2)
{
 if(item != NULL)
 {
  g2->removeItem(item);
 }
 if(trackOval != NULL)
 {
  g2->removeItem(trackOval);
  trackOval =NULL;
 }
 if(circleItem != NULL)
 {
  g2->removeItem(circleItem);
 circleItem = NULL;
 }

}
void TrackSegment::drawHiddenTrack(LayoutEditor* editor, QGraphicsScene *g2)
{
 QColor color;
 //if (isEditable() && getHidden())
 {
  LayoutBlock* b = getLayoutBlock();
  if (b!=NULL) color = (b->getBlockColor());
  else color =(editor->defaultTrackColor);
//   g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
//   g2.draw(new Line2D.Double(getCoords(t->getConnect1(),t.getType1()), getCoords(t->getConnect2(),t.getType2())));
//   g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(color, trackWidth));
  QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(editor->getCoords(getConnect1(),getType1()), editor->getCoords(getConnect2(),getType2())));
  lineItem->setPen(QPen(color, 1.0));
  item = lineItem;
  g2->addItem(item);
  editor->setTrackStrokeWidth(!editor->main);
 }
}
void TrackSegment::drawDashedTrack(LayoutEditor* editor, QGraphicsScene* g2, bool mainline)
{
 QColor color;
 LayoutBlock* b = getLayoutBlock();
 if (b!=NULL) color = (b->getBlockColor());
 else color = (editor->defaultTrackColor);
 editor->setTrackStrokeWidth(mainline);
 if (getArc())
 {
  CalculateTrackSegmentAngle(editor);
  //Stroke drawingStroke;
  //Stroke originalStroke = g2.getStroke();
  QPen drawingStroke;
  if (mainline)
   //drawingStroke = new BasicStroke(mainlineTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
   drawingStroke = QPen(color,editor->mainlineTrackWidth,Qt::DashLine, Qt::SquareCap,Qt::BevelJoin);
  else
//    drawingStroke = new BasicStroke(sideTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
   drawingStroke =  QPen(color,editor->sideTrackWidth,Qt::DashLine, Qt::SquareCap,Qt::BevelJoin);

  //g2.setStroke(drawingStroke);
  //g2.draw(new Arc2D.Double(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
  //g2->addEllipse(t->getCX(), t->getCY(), t->getCW(), t->getCH(),drawingStroke);
  QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
  lineItem->setStartAngle(getStartadj()*16);
  lineItem->setSpanAngle(getTmpAngle()*16);
  lineItem->setPen(drawingStroke);
  item = lineItem;
  g2->addItem(item);
  //g2.setStroke(originalStroke);
 }
 else
 {
  QPointF end1 = editor->getCoords(getConnect1(),getType1());
  QPointF end2 = editor->getCoords(getConnect2(),getType2());
  double delX = end1.x() - end2.x();
  double delY = end1.y() - end2.y();
  double cLength = qSqrt( (delX*delX) + (delY*delY) );
  // note: The preferred dimension of a dash (solid + blank space) is
  //         5 * the track width - about 60% solid and 40% blank.
  int nDashes = (int)( cLength / ((editor->trackWidth)*5.0) );
  if (nDashes < 3) nDashes = 3;
  double delXDash = -delX/( (nDashes) - 0.5 );
  double delYDash = -delY/( (nDashes) - 0.5 );
  double begX = end1.x();
  double begY = end1.y();
  QGraphicsItemGroup* group = new QGraphicsItemGroup();
  for (int k = 0; k<nDashes; k++)
  {
   //g2->addLine(QLineF( QPointF(begX,begY), QPointF((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))),QPen(color,trackWidth));
   QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF( QPointF(begX,begY), QPointF((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))));
   lineItem->setPen(QPen(color,editor->trackWidth));
   group->addToGroup(lineItem);
   begX += delXDash;
   begY += delYDash;
  }
  g2->addItem(group);
 }
}
/*
* Calculates the initial parameters for drawing a circular track segment.
*/
/*private*/ void TrackSegment::CalculateTrackSegmentAngle(LayoutEditor* editor)
{
  QPointF pt1 = editor->getCoords(getConnect1(),getType1());
  QPointF pt2 = editor->getCoords(getConnect2(),getType2());
  if (getFlip())
  {
   pt1 = editor->getCoords(getConnect2(),getType2());
   pt2 = editor->getCoords(getConnect1(),getType1());
  }
  if((getTmpPt1()!=pt1) || (getTmpPt2()!=pt2) || trackNeedsRedraw())
  {
   setTmpPt1(pt1);
   setTmpPt2(pt2);
   //setTrackStrokeWidth(g2,false);
   double pt2x;
   double pt2y;
   double pt1x;
   double pt1y;
   pt2x = pt2.x();
   pt2y = pt2.y();
   pt1x = pt1.x();
   pt1y = pt1.y();

   if (getAngle() == 0.0)
      setTmpAngle(90.0);
   else
      setTmpAngle(getAngle());
   //double toDegrees = M_PI/180.;
   // Convert angle to radians in order to speed up maths
   double halfAngle = degToRad(getTmpAngle())/2.0;
   double chord;
   double a;
   double o;
   double radius;
   // Compute arc's chord
   a = pt2x - pt1x;
   o = pt2y - pt1y;
   chord=qSqrt(((a*a)+(o*o)));
   setChordLength(chord);
   // Make sure chord is not NULL
   // In such a case (pt1 == pt2), there is no arc to draw
   if (chord > 0.0)
   {
    radius = (chord/2)/(qSin(halfAngle));
    // Circle
    double startRad = qAtan2(a, o) - halfAngle;
    setStartadj(radToDeg(startRad));
    if(getCircle())
    {
     // Circle - Compute center
     setCentreX(pt2x - qCos(startRad) * radius);
     setCentreY(pt2y + qSin(startRad) * radius);
     // Circle - Compute rectangle required by Arc2D.Double
     setCW(radius * 2.0);
     setCH(radius * 2.0);
     setCX(getCentreX()-(radius));
     setCY(getCentreY()-(radius));
    }
    else
    {
     // Elipse - Round start angle to the closest multiple of 90
     setStartadj(qRound(getStartadj() / 90.0) * 90.0);
     // Elipse - Compute rectangle required by Arc2D.Double
     setCW(qAbs(a)*2.0);
     setCH(qAbs(o)*2.0);
     // Elipse - Adjust rectangle corner, depending on quadrant
     if (o * a < 0.0)
      a = -a;
     else
      o = -o;
     setCX(qMin(pt1x, pt2x)-qMax(a, 0.0));
     setCY(qMin(pt1y, pt2y)-qMax(o, 0.0));
    }
   }
  }
}

void TrackSegment::drawSolidTrack(LayoutEditor* editor, QGraphicsScene* g2, bool /*isMainline*/)
{
 QColor color;

 LayoutBlock* b = getLayoutBlock();
 if (b!=NULL)
  color = (b->getBlockColor());
 else
  color =(editor->defaultTrackColor);
 Q_ASSERT(color.isValid());

 //setTrackStrokeWidth(g2,mainline);
 if(getArc())
 {
  CalculateTrackSegmentAngle(editor);
  //g2.draw(new Arc2D.Double(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
  QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
  lineItem->setStartAngle(getStartadj()*16);
  lineItem->setSpanAngle(getTmpAngle()*16);
  lineItem->setPen(QPen(QColor(color),editor->trackWidth));
  item = lineItem;
  g2->addItem(item);
 } else
 {
  //g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
  //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(QColor(color),trackWidth));
  QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(editor->getCoords(getConnect1(),getType1()), editor->getCoords(getConnect2(),getType2())));
  lineItem->setPen(QPen(QColor(color),editor->trackWidth));
  item = lineItem;
  g2->addItem(item);
 }
 trackRedrawn();
}
void TrackSegment::drawTrackOvals(LayoutEditor *editor, QGraphicsScene *g2)
{
 QColor color;
 color = (editor->defaultTrackColor);
 QPointF pt1 = editor->getCoords(getConnect1(),getType1());
 QPointF pt2 = editor->getCoords(getConnect2(),getType2());
 double cX = (pt1.x() + pt2.x())/2.0;
 double cY = (pt1.y() + pt2.y())/2.0;
 //g2.draw(new Ellipse2D.Double (cX-SIZE2, cY-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
 QGraphicsItemGroup* group = new QGraphicsItemGroup();
 //g2->addEllipse(cX-SIZE2, cY-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2,QPen(color,1));
 QGraphicsEllipseItem* item = new QGraphicsEllipseItem(cX-LayoutEditor::SIZE2, cY-LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2);
 item->setPen(QPen(color,1));
 group->addToGroup(item);
 if (getArc())
 {
  LayoutBlock* b = getLayoutBlock();
  if (b!=NULL) color =(b->getBlockColor());
  else color =(editor->defaultTrackColor);
  //g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
  //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(color,1));
  QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(editor->getCoords(getConnect1(),getType1()), editor->getCoords(getConnect2(),getType2())));
  item->setPen(QPen(color,1));
  group->addToGroup(item);
  if (getCircle())
  {
   //g2.draw(new Line2D.Double();
   //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()),  QPointF(t->getCentreX(),t->getCentreY())),QPen(color,trackWidth));
   QGraphicsLineItem* item1 = new QGraphicsLineItem(QLineF(editor->getCoords(getConnect1(),getType1()),  QPointF(getCentreX(),getCentreY())));
   item1->setPen(QPen(color,editor->trackWidth));
   group->addToGroup(item1);
   //g2.draw(new Line2D.Double(getCoords(t.getConnect2(),t.getType2()), new QPointF.Double(t.getCentreX(),t.getCentreY())));
   //g2->addLine(QLineF(getCoords(t->getConnect2(),t->getType2()), QPointF(t->getCentreX(),t->getCentreY())),QPen(color, trackWidth));
   QGraphicsLineItem* item2 = new QGraphicsLineItem(QLineF(editor->getCoords(getConnect2(),getType2()), QPointF(getCentreX(),getCentreY())));
   item2->setPen(QPen(color, editor->trackWidth));
   group->addToGroup(item2);
  }
  color =(editor->defaultTrackColor);
 }
 trackOval = group;
 g2->addItem(trackOval);
}
void TrackSegment::drawTrackCircleCentre(LayoutEditor */*editor*/, QGraphicsScene *g2)
{
    QPointF pt = getCoordsCenterCircle();
    reCalculateTrackSegmentAngle(pt.x(), pt.y()); // added ACK
//    g2.setColor(Color.black);
//    g2.draw(new Rectangle2D.Double (pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
      //g2->addRect(QRectF(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2),QPen(QColor(Qt::black),1));
    QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2));
    item->setPen(QPen(QColor(Qt::black),1));
    circleItem = item;
    g2->addItem(circleItem);
}
/*
* The recalculation method is used when the user changes the angle dynamically in edit mode
* by dragging the centre of the cirle
*/
/*private*/ void TrackSegment::reCalculateTrackSegmentAngle(double x, double y)
{

  double pt2x;
  double pt2y;
  double pt1x;
  double pt1y;

  pt2x = getTmpPt2().x();
  pt2y = getTmpPt2().y();
  pt1x = getTmpPt1().x();
  pt1y = getTmpPt1().y();
  if (getFlip())
  {
   pt1x = getTmpPt2().x();
   pt1y = getTmpPt2().y();
   pt2x = getTmpPt1().x();
   pt2y = getTmpPt1().y();
  }
  //Point 1 to new point length
  double a;
  double o;
  double la;
  // Compute arc's chord
  a = pt2x - x;
  o = pt2y - y;
  la=qSqrt(((a*a)+(o*o)));

  double lb;
  a = pt1x - x;
  o = pt1y - y;
  lb=qSqrt(((a*a)+(o*o)));
  //double toDegrees = M_PI/180;
  double newangle=radToDeg(qAcos((-getChordLength()*getChordLength()+la*la+lb*lb)/(2*la*lb)));
  setAngle(newangle);
  //qDebug() << tr("newangle = %1").arg(newangle);
}
double TrackSegment::radToDeg(double radians)
{
 double toDegrees = 180./M_PI;
 return radians * toDegrees;
}
double TrackSegment::degToRad(double degrees)
{
 double toRadians = M_PI/180.0;
 return degrees * toRadians;
}
/*public*/ void TrackSegment::hideConstructionLines(int hide)
{
 if (hide == HIDECONALL)
 {
     showConstructionLine = showConstructionLine + HIDECONALL;
 } else if (hide == SHOWCON) {
     if ((showConstructionLine & HIDECONALL) == HIDECONALL) {
         showConstructionLine = (showConstructionLine & (~HIDECONALL));
     } else {
         showConstructionLine = hide;
     }
 } else {
     showConstructionLine = HIDECON;
 }
 //layoutEditor.redrawPanel();
 layoutEditor->setDirty();
}

/*public*/ bool TrackSegment::hideConstructionLines() {
    if ((showConstructionLine & SHOWCON) == SHOWCON) {
        return false;
    } else {
        return true;
    }
}
