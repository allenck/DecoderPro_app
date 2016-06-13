#include "tracksegment.h"

TrackSegment::TrackSegment(QObject *parent) :
    QObject(parent)
{
}
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
    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");


/*public*/
TrackSegment::TrackSegment(QString id, QObject* c1, int t1, QObject* c2, int t2, bool dash, bool main, LayoutEditor myPanel)
{
    init();
    layoutEditor = myPanel;
    // validate input
    if ( (c1==NULL) || (c2==NULL) ) {
        log.error("Invalid object in TrackSegment constructor call - "+id);
    }
    connect1 = c1;
    connect2 = c2;
    if ( (t1<LayoutEditor.POS_POINT) ||
                ( ((t1>LayoutEditor.LEVEL_XING_D) && (t1<LayoutEditor.SLIP_A))
                    || ((t1>LayoutEditor.SLIP_D) && (t1<LayoutEditor.TURNTABLE_RAY_OFFSET)) ) ) {
        log.error("Invalid connect type 1 in TrackSegment constructor - "+id);
    }
    else {
        type1 = t1;
    }
    if ( (t2<LayoutEditor.POS_POINT) ||
                ( ((t2>LayoutEditor.LEVEL_XING_D) && (t2<LayoutEditor.SLIP_A))
                    || ((t2>LayoutEditor.SLIP_D) && (t2<LayoutEditor.TURNTABLE_RAY_OFFSET)) ) ) {
        log.error("Invalid connect type 2 in TrackSegment constructor - "+id);
    }
    else {
        type2 = t2;
    }
    instance = this;
    ident = id;
    dashed = dash;
    mainline = main;
    arc = false;
    flip = false;
    angle = 0.0D;
    circle = false;
}
// alternate constructor for loading layout editor panels
/*public*/
TrackSegment::TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor myPanel)
{
    init();
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
void TrackSegment::init()
{
// operational instance variables (not saved between sessions)
 block = NULL;
 instance = NULL;
 layoutEditor = NULL;

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
 angle =0.0D;
 circle=false;
 changed=false;
}
    /**
     * Accessor methods
    */
    /*public*/ void
    TrackSegment::setArc(bool boo) {
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
    TrackSegment::setAngle(double x) {
// GT 8-OCT-2009 ==== Changed arcs maths : Start
//        if (angle>180) // ???
        if (x>180.0D)
            x=180.0D;
        else if (x < 0.0D)
            x = 0.0D;
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
    TrackSegment::getLayoutBlock() {
        if ( (block==NULL) && (blockName!=NULL) && (blockName!="") ) {
            block = layoutEditor.provideLayoutBlock(blockName);
        }
        return block;
    }
//    /*public*/ QString getConnect1Name() {return getConnectName(connect1,type1);}
//    /*public*/ QString getConnect2Name() {return getConnectName(connect2,type2);}

    /*private*/ QString
    TrackSegment::getConnectName(QObject* o,int type) {
        if (type == LayoutEditor.POS_POINT) {
            return ((PositionablePoint)o).getID();
        }
        if ( (type == LayoutEditor.TURNOUT_A) || (type == LayoutEditor.TURNOUT_B) ||
                (type == LayoutEditor.TURNOUT_C) || (type == LayoutEditor.TURNOUT_D) ) {
            return ((LayoutTurnout)o).getName();
        }
        if ( (type == LayoutEditor.LEVEL_XING_A) || (type == LayoutEditor.LEVEL_XING_B) ||
                (type == LayoutEditor.LEVEL_XING_C) || (type == LayoutEditor.LEVEL_XING_D) ) {
            return ((LevelXing)o).getID();
        }
        if ( (type == LayoutEditor.SLIP_A) || (type == LayoutEditor.SLIP_B) ||
                (type == LayoutEditor.SLIP_C) || (type == LayoutEditor.SLIP_D) ) {
            return ((LayoutSlip)o).getName();
        }
        if (type>=LayoutEditor.TURNTABLE_RAY_OFFSET) {
            return ((LayoutTurntable)o).getID();
        }
        return "";
    }

    // initialization instance variables (used when loading a LayoutEditor)
    /*public*/ QString tBlockName = "";
    /*public*/ QString tConnect1Name = "";
    /*public*/ QString tConnect2Name = "";
    /**
     * Initialization method
     *   The above variables are initialized by PositionablePointXml, then the following
     *        method is called after the entire LayoutEditor is loaded to set the specific
     *        TrackSegment objects.
     */
    /*public*/ void setQObject*s(LayoutEditor p) {
        if (tBlockName.length()>0) {
            block = p.getLayoutBlock(tBlockName);
            if (block!=NULL) {
                blockName = tBlockName;
                block.incrementUse();
            }
            else {
                log.error("bad blockname '"+tBlockName+"' in tracksegment "+ident);
            }
        }
        connect1 = p.findQObject*ByTypeAndName(type1,tConnect1Name);
        connect2 = p.findQObject*ByTypeAndName(type2,tConnect2Name);
    }

    /**
     * Set Up a Layout Block for a Track Segment
     */
    /*public*/ void setLayoutBlock (LayoutBlock b) {
        block = b;
        if (b!=NULL) {
            blockName = b.getID();
        }
    }
    /*public*/ void setLayoutBlockByName (QString name) {
        blockName = name;
    }
    protected void updateBlockInfo() {
        if (block!=NULL) block.updatePaths();
        LayoutBlock b1 = getBlock(connect1,type1);
        if ((b1!=NULL)&&(b1!=block)) b1.updatePaths();
        LayoutBlock b2 = getBlock(connect2,type2);
        if ((b2!=NULL)&&(b2!=block)&&(b2!=b1)) b2.updatePaths();
        if(getConnect1() instanceof PositionablePoint)
            ((PositionablePoint)getConnect1()).reCheckBlockBoundary();
        else if(getConnect1() instanceof LayoutTurnout)
            ((LayoutTurnout)getConnect1()).reCheckBlockBoundary();
        else if(getConnect1() instanceof LevelXing)
            ((LevelXing)getConnect1()).reCheckBlockBoundary();
        else if(getConnect1() instanceof LayoutSlip)
            ((LayoutSlip)getConnect1()).reCheckBlockBoundary();

        if(getConnect2() instanceof PositionablePoint)
            ((PositionablePoint)getConnect2()).reCheckBlockBoundary();
        else if(getConnect2() instanceof LayoutTurnout)
            ((LayoutTurnout)getConnect2()).reCheckBlockBoundary();
        else if(getConnect2() instanceof LevelXing)
            ((LevelXing)getConnect2()).reCheckBlockBoundary();
        else if(getConnect2() instanceof LayoutSlip)
            ((LayoutSlip)getConnect2()).reCheckBlockBoundary();
    }
    /*private*/ LayoutBlock getBlock (QObject* connect, int type) {
        if (connect==NULL) return NULL;
        if (type==LayoutEditor.POS_POINT) {
            PositionablePoint p = (PositionablePoint)connect;
            if (p.getConnect1()!=instance) {
                if (p.getConnect1()!=NULL) return (p.getConnect1().getLayoutBlock());
                else return NULL;
            }
            else {
                if (p.getConnect2()!=NULL) return (p.getConnect2().getLayoutBlock());
                else return NULL;
            }
        }
        else {
            return (layoutEditor.getAffectedBlock(connect,type));
        }
    }


    JPopupMenu popup = NULL;

    /**
     * Display popup menu for information and editing
     */
    protected void showPopUp(MouseEvent e) {
        if (popup != NULL ) {
            popup.removeAll();
        }
        else {
            popup = new JPopupMenu();
        }
        if (!dashed) popup.add(rb.getQString("Style")+" - "+rb.getQString("Solid"));
        else popup.add(rb.getQString("Style")+" - "+rb.getQString("Dashed"));
        if (!mainline) popup.add(rb.getQString("NotMainline"));
        else popup.add(rb.getQString("Mainline"));
        if (blockName.equals("")) popup.add(rb.getQString("NoBlock"));
        else popup.add(rb.getQString("Block")+": "+getLayoutBlock().getID());
        if (hidden) popup.add(rb.getQString("Hidden"));
        else popup.add(rb.getQString("NotHidden"));
        popup.add(new JSeparator(JSeparator.HORIZONTAL));
        popup.add(new AbstractAction(rb.getQString("Edit")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    editTrackSegment();
                }
            });
        popup.add(new AbstractAction(rb.getQString("Remove")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    layoutEditor.removeTrackSegment(instance);
                    remove();
                    dispose();
                }
            });
        JMenu lineType = new JMenu("Change To");
        lineType.add(new AbstractAction("Line") {
            /*public*/ void actionPerformed(ActionEvent e) {
                changeType(0);
                }
        });
        lineType.add(new AbstractAction("Circle") {
            /*public*/ void actionPerformed(ActionEvent e) {
                changeType(1);
            }
        });
        lineType.add(new AbstractAction("Elipse") {
            /*public*/ void actionPerformed(ActionEvent e) {
                changeType(2);
            }
        });
        popup.add(lineType);
        if (getArc()){
            popup.add(new AbstractAction("Flip Angle") {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        flipAngle();
                    }
                });
        }
        if ((!blockName.equals("")) && (jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled())){
            popup.add(new AbstractAction(rb.getQString("ViewBlockRouting")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
                    routeTableAction.actionPerformed(e);
                }
            });
        }
        popup.show(e.getComponent(), e.getX(), e.getY());
    }

    void changeType(int choice){
        switch (choice){
            case 0 :    setArc(false);
                        setAngle(0.0D);
                        setCircle(false);
                        break;
            case 1 :    setArc(true);
                        setAngle(90.0D);
                        setCircle(true);
                        break;
            case 2 :    setArc(true);
                        setAngle(90.0D);
                        setCircle(false);
                        break;
            default : break;
        }
        layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }

    void flipAngle(){
        if(getFlip()){
            setFlip(false);
        } else{
            setFlip(true);
        }
        layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }

    // variables for Edit Track Segment pane
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
    /*private*/ bool needsRedraw = false;

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
                arcField.setText(""+getAngle());
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
                arcField.setText(""+getAngle());
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

    /**
     * Clean up when this object is no longer needed.  Should not
     * be called while the object is still displayed; see remove()
     */
    void dispose() {
        if (popup != NULL) popup.removeAll();
        popup = NULL;
    }

    /**
     * Removes this object from display and persistance
     */
    void remove() {
        // remove from persistance by flagging inactive
        active = false;
    }

    bool active = true;
    /**
     * "active" means that the object is still displayed, and should be stored.
     */
    /*public*/ bool isActive() {
        return active;
    }

    /**
    * The following are used only as a temporary store after a circle or arc has been calculated.
    * This prevents the need to recalculate the values each time a re-draw is required.
    */

    /*private*/ Point2D pt1;
    /*private*/ Point2D pt2;

    /*public*/ Point2D getTmpPt1(){
        return pt1;
    }
    /*public*/ Point2D getTmpPt2(){
        return pt2;
    }

    /*public*/ void setTmpPt1(Point2D Pt1){
        pt1 = Pt1;
        changed= true;
    }
    /*public*/ void setTmpPt2(Point2D Pt2){
        pt2 = Pt2;
        changed= true;
    }

    ///*private*/ int startadj;

    /*private*/ double cX;
    /*public*/ double getCX(){
        return cX;
    }

    /*public*/ void setCX(double CX){
        cX = CX;
    }

    /*private*/ double cY;
    /*public*/ double getCY(){
        return cY;
    }

    /*public*/ void setCY(double CY){
        cY = CY;
    }

    /*private*/ double cW;
    /*public*/ double getCW(){
        return cW;
    }

    /*public*/ void setCW(double CW){
        cW = CW;
    }

    /*private*/ double cH;
    /*public*/ double getCH(){
        return cH;
    }

    /*public*/ void setCH(double CH){
        cH = CH;
    }

    /*private*/ double startadj;
    /*public*/ double getStartadj(){
        return startadj;
    }

    /*public*/ void setStartadj(double Startadj){
        startadj = Startadj;
    }

    /*private*/ double centreX;
    /*public*/ double getCentreX(){
        return centreX;
    }

    /*public*/ void setCentreX(double CentreX){
        centreX = CentreX;
    }

    /*private*/ double centreY;
    /*public*/ double getCentreY(){
        return centreY;
    }

    /*public*/ void setCentreY(double CentreY){
        centreY = CentreY;
    }

    /*private*/ double tmpangle;
    /*public*/ double getTmpAngle(){
        return tmpangle;
    }

    /*public*/ void setTmpAngle(double TmpAngle){
        tmpangle = TmpAngle;
    }

    /*public*/ Point2D getCoordsCenterCircle() { return new Point2D.Double(getCentreX(),getCentreY()); }

    /*private*/ double chordLength;
    /*public*/ double getChordLength() { return chordLength; }
    /*public*/ void setChordLength(double chord) { chordLength=chord;}

    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TrackSegment.class.getName());

}
