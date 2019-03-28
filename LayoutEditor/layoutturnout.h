#ifndef LAYOUTTURNOUT_H
#define LAYOUTTURNOUT_H

#include "layouttrack.h"
//#include "layoutblock.h"
//#include "mylayouteditor.h"
#include "turnout.h"
//#include "layouteditortools.h"
//#include <QComboBox>
//#include <QLabel>
//#include <QCheckBox>
//#include <QPushButton>
//#include "editturnout.h"
//#include <QGraphicsItem>
#include "liblayouteditor_global.h"
#include "actionlistener.h"
#include <QPointF>
#include <QVector>
#include "windowlistener.h"
#include "exceptions.h"

class SignalHead;
class QGraphicsEllipseItem;
class QCloseEvent;
class JmriJFrame;
class QDialog;
class SignalMast;
class QGraphicsSceneMouseEvent;
class JTextField;
class QLineEdit;
class QGraphicsScene;
class QGraphicsItemGroup;
class QAction;
class QMenu;
class QPointF;
class QComboBox;
class QLabel;
class QCheckBox;
class QPushButton;
class QGraphicsItem;
class EditTurnout;
class QMenuItem;
class LayoutEditor;
class LayoutBlock;
class LayoutEditorTools;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutTurnout : public LayoutTrack
{
    Q_OBJECT
public:
    //explicit LayoutTurnout(QObject *parent = 0);
    // defined constants - turnout types
 enum TURNOUTTYPES
 {
    RH_TURNOUT = 1,
    LH_TURNOUT = 2,
    WYE_TURNOUT = 3,
    DOUBLE_XOVER = 4,
    RH_XOVER = 5,
    LH_XOVER = 6,
    SINGLE_SLIP = 7, //used in LayoutSlip which extends this class
    DOUBLE_SLIP = 8 //used in LayoutSlip which extends this class
     };
 Q_ENUM(TURNOUTTYPES)
    // defined constants - link types
 enum LINKTYPES
 {
   NO_LINK = 0,
   FIRST_3_WAY = 1,       // this turnout is the first turnout of a 3-way
                                                    // turnout pair (closest to the throat)
   SECOND_3_WAY = 2,      // this turnout is the second turnout of a 3-way
                                                    // turnout pair (furthest from the throat)
   THROAT_TO_THROAT = 3  // this turnout is one of two throat-to-throat
 };                                   // turnouts - no signals at throat
 Q_ENUM(LINKTYPES)
 enum POINTS
 {
  POINTA = 0x01,
  POINTA2 = 0x03,
  POINTA3 = 0x05,
  POINTB = 0x10,
  POINTB2 = 0x12,
  POINTC = 0x20,
  POINTC2 = 0x22,
  POINTD = 0x30,
  POINTD2 = 0x32
 };
 Q_ENUM(POINTS)
 // operational instance variables (not saved between sessions)
 enum STATES
 {
  UNKNOWN = Turnout::UNKNOWN,
  STATE_AC = 0x02,
  STATE_BD = 0x04,
  STATE_AD = 0x06,
  STATE_BC = 0x08
};
 Q_ENUM(STATES)
     // program default turnout size parameters
     /*public*/ static /*final*/ double turnoutBXDefault;// = 20.0;  // RH, LH, WYE
     /*public*/ static /*final*/ double turnoutCXDefault;// = 20.0;
     /*public*/ static /*final*/ double turnoutWidDefault;// = 10.0;
     /*public*/ static /*final*/ double xOverLongDefault;// = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
     /*public*/ static /*final*/ double xOverHWidDefault;// = 10.0;
     /*public*/ static /*final*/ double xOverShortDefault;// = 10.0;

//    /*public*/ QString ident;   // name of this layout turnout (hidden from user)
    /*public*/ QString turnoutName;// = "";   // should be the name (system or user) of
                                //	an existing physical turnout
    /*public*/ QString blockName;// = "";  // name for block, if there is one
    /*public*/ QString blockBName;// = "";  // Xover - name for second block, if there is one
    /*public*/ QString blockCName;// = "";  // Xover - name for third block, if there is one
    /*public*/ QString blockDName;// = "";  // Xover - name for fourth block, if there is one

    /*public*/ QString signalA1Name;// = ""; // signal 1 (continuing) (throat for RH, LH, WYE)
    /*public*/ QString signalA2Name;// = ""; // signal 2 (diverging) (throat for RH, LH, WYE)
    /*public*/ QString signalA3Name;// = ""; // signal 3 (second diverging) (3-way turnouts only)
    /*public*/ QString signalB1Name;// = ""; // continuing (RH, LH, WYE) signal 1 (double crossover)
    /*public*/ QString signalB2Name;// = ""; // LH_Xover and double crossover only
    /*public*/ QString signalC1Name;// = ""; // diverging (RH, LH, WYE) signal 1 (double crossover)
    /*public*/ QString signalC2Name;// = ""; // RH_Xover and double crossover only
    /*public*/ QString signalD1Name;// = ""; // single or double crossover only
    /*public*/ QString signalD2Name;// = ""; // LH_Xover and double crossover only

    /*public*/ QString signalAMast;// = ""; // Throat
    /*public*/ QString signalBMast;// = ""; // Continuing
    /*public*/ QString signalCMast;// = ""; // diverging
    /*public*/ QString signalDMast;// = ""; // single or double crossover only
    /*protected*/ NamedBeanHandle<Sensor*>* sensorANamed;// = NULL; // Throat
    /*protected*/ NamedBeanHandle<Sensor*>* sensorBNamed;// = NULL; // Continuing
    /*protected*/ NamedBeanHandle<Sensor*>* sensorCNamed;// = NULL; // diverging
    /*protected*/ NamedBeanHandle<Sensor*>* sensorDNamed;// = NULL; // single or double crossover only
    /*public*/ int type;// = RH_TURNOUT;
    /*public*/ LayoutTrack* connectA;// = NULL;		// throat of LH, RH, RH Xover, LH Xover, and WYE turnouts
    /*public*/ LayoutTrack* connectB;// = NULL;		// straight leg of LH and RH turnouts
    /*public*/ LayoutTrack* connectC;// = NULL;
    /*public*/ LayoutTrack* connectD;// = NULL;		// double xover, RH Xover, LH Xover only
    /*public*/ int continuingSense;// = Turnout::CLOSED;
    /*public*/ bool disabled;// = false;
    /*public*/ bool disableWhenOccupied;// = false;
    /*public*/ QPointF dispB;// = new QPoint.Double(20.0,0.0);
    /*public*/ QPointF dispC;// = new QPoint.Double(20.0,10.0);
    /*public*/ QString linkedTurnoutName;// = ""; // name of the linked Turnout (as entered in tool)
    /*public*/ int linkType;// = NO_LINK;
    /**
     * constructor method
     */
    /*public*/ LayoutTurnout(/*@Nonnull*/ QString id, int t, /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor);
    /*public*/ LayoutTurnout(/*@Nonnull*/ QString id, int t, /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int version);
    /**
     * Accessor methods
    */
    /*public*/ QString getName();
    /*public*/ bool useBlockSpeed();
    /*public*/ QString getTurnoutName();
    /*public*/ QString getSecondTurnoutName();
    /*public*/ bool isSecondTurnoutInverted();
    /*public*/ void setSecondTurnoutInverted(bool inverted);
    /*public*/ bool getHidden();
    /*public*/ void setHidden(bool hide);
    /*public*/ QString getBlockName();
    /*public*/ QString getBlockBName();
    /*public*/ QString getBlockCName();
    /*public*/ QString getBlockDName();
    /*public*/ QString getSignalA1Name();
    /*public*/ SignalHead* getSignalHead(int loc);
    /*public*/ void setSignalA1Name(QString signalName);
    /*public*/ QString getSignalA2Name();
    /*public*/ void setSignalA2Name(QString signalName) ;
    /*public*/ QString getSignalA3Name();
    /*public*/ void setSignalA3Name(QString signalName);
    /*public*/ QString getSignalB1Name();
    /*public*/ void setSignalB1Name(QString signalName);
    /*public*/ QString getSignalB2Name();
    /*public*/ void setSignalB2Name(QString signalName);
    /*public*/ QString getSignalC1Name();
    /*public*/ void setSignalC1Name(QString signalName);
    /*public*/ QString getSignalC2Name();
    /*public*/ void setSignalC2Name(QString signalName);
    /*public*/ QString getSignalD1Name();
    /*public*/ void setSignalD1Name(QString signalName);
    /*public*/ QString getSignalD2Name();
    /*public*/ void setSignalD2Name(QString signalName);
    /*public*/ void removeBeanReference(NamedBean* nb);

    /*public*/ QString getSignalAMastName();
    /*public*/ SignalMast* getSignalAMast();
    /*public*/ void setSignalAMast(QString signalMast);
    /*public*/ QString getSignalBMastName();
    /*public*/ SignalMast* getSignalBMast();
    /*public*/ void setSignalBMast(QString signalMast);
    /*public*/ QString getSignalCMastName();
    /*public*/ SignalMast *getSignalCMast();
    /*public*/ void setSignalCMast(QString signalMast);
    /*public*/ QString getSignalDMastName();
    /*public*/ SignalMast* getSignalDMast();
    /*public*/ void setSignalDMast(QString signalMast);
    /*public*/ QString getSensorAName();
    /*public*/ Sensor* getSensorA();
    /*public*/ void setSensorA(QString sensorName);
    /*public*/ QString getSensorBName();
    /*public*/ Sensor* getSensorB();
    /*public*/ void setSensorB(QString sensorName);
    /*public*/ QString getSensorCName();
    /*public*/ Sensor* getSensorC();
    /*public*/ void setSensorC(QString sensorName);
    /*public*/ QString getSensorDName();
    /*public*/ Sensor* getSensorD();
    /*public*/ void setSensorD(QString sensorName);
    /*public*/ QString getLinkedTurnoutName();
    /*public*/ void setLinkedTurnoutName(QString s);

    /*public*/ int getLinkType();
    /*public*/ void setLinkType(int type);
    /*public*/ int getTurnoutType();
    /*public*/ QObject* getConnectA();
    /*public*/ QObject* getConnectB();
    /*public*/ QObject* getConnectC();
    /*public*/ QObject* getConnectD();
    /*public*/ Turnout* getTurnout();
    /**
     * Accessor methods
    */
//    /*public*/ QString getName();
//    /*public*/ bool useBlockSpeed();
//    /*public*/ QString getTurnoutName();
//    /*public*/ QString getSecondTurnoutName();
    /*public*/ int getContinuingSense();
    /*public*/ void setTurnout(QString tName);
    /*public*/ Turnout* getSecondTurnout();
    /*public*/ void setSecondTurnout(QString tName);
    /*public*/ void setContinuingSense(int sense);
//    /*public*/ void setDisabled(bool state);
    /*public*/ bool isDisabled();
//    /*public*/ void setDisableWhenOccupied(bool state);
    /*public*/ bool isDisabledWhenOccupied();
    /*public*/ void setConnectA(LayoutTrack *o, int type);
    /*public*/ void setConnectB(LayoutTrack* o,int type);
    /*public*/ void setConnectC(LayoutTrack *o, int type);
    /*public*/ void setConnectD(LayoutTrack* o,int type);
    /*public*/ LayoutBlock* getLayoutBlock();
    /*public*/ LayoutBlock* getLayoutBlockB();
    /*public*/ LayoutBlock* getLayoutBlockC() ;
    /*public*/ LayoutBlock* getLayoutBlockD();
    /*public*/ QPointF getCoordsCenter();
    /*public*/ QPointF getCoordsA();
    /*public*/ QPointF getCoordsB();
    /*public*/ QPointF getCoordsC();
    /*public*/ QPointF getCoordsD();
    /**
     * Set Up a Layout Block(s) for this Turnout
     */
    /*public*/ void setLayoutBlock (LayoutBlock* b);
    /*public*/ void setLayoutBlockB (LayoutBlock* b);
    /*public*/ void setLayoutBlockC (LayoutBlock* b);
    /*public*/ void setLayoutBlockD (LayoutBlock* b);
    /*public*/ void setLayoutBlockByName (QString name);
    /*public*/ void setLayoutBlockBByName (QString name);
    /*public*/ void setLayoutBlockCByName (QString name);
    /*public*/ void setLayoutBlockDByName (QString name);
    /**
     * Methods to test if turnout legs are mainline track or not
     *  Returns true if connecting track segment is mainline
     *  Defaults to not mainline if connecting track segment is missing
     */
    /*public*/ bool isMainlineA() ;
    /*public*/ bool isMainlineB();
    /*public*/ bool isMainlineC();
    /*public*/ bool isMainlineD();
    /**
     * Modify coordinates methods
     */
    /*public*/ void setCoordsCenter(QPointF p) ;
    /*public*/ void setCoordsA(QPointF p);
    /*public*/ void setCoordsB(QPointF p);
    /*public*/ void setCoordsC(QPointF p);
    /*public*/ void setCoordsD(QPointF p);
    /*public*/ void scaleCoords(float xFactor, float yFactor);
    /**
     * Toggle turnout if clicked on, physical turnout exists, and
     *    not disabled
     */
    /*public*/ void toggleTurnout();

    // initialization instance variables (used when loading a LayoutEditor)
    /*public*/ QString connectAName;// = "";
    /*public*/ QString connectBName;// = "";
    /*public*/ QString connectCName;// = "";
    /*public*/ QString connectDName;// = "";
    /*public*/ QString tBlockName;// = "";
    /*public*/ QString tBlockBName;// = "";
    /*public*/ QString tBlockCName;// = "";
    /*public*/ QString tBlockDName;// = "";
    /*public*/ QString tTurnoutName;// = "";
    /*public*/ QString tSecondTurnoutName;// = "";
 /**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void setObjects(LayoutEditor* p);

/*public*/ QStringList getBlockBoundaries();
 /*public*/ QList<LayoutBlock*> getProtectedBlocks(NamedBean* bean);

 /*public*/ void reCheckBlockBoundary();
 void removeSML(SignalMast *signalMast);
 /**
  * Clean up when this object is no longer needed.  Should not
  * be called while the object is still displayed; see remove()
  */
 void dispose();
 /**
  * Removes this object from display and persistance
  */
 void remove();
 /*public*/ bool isActive();
 /*public*/ void addViewPopUpMenu(QObject* menu);
 /*public*/ void addEditPopUpMenu(QObject* menu);

 /*public*/ void setAdditionalEditPopUpMenu(QMenu* popup);
 /*public*/ void setAdditionalViewPopUpMenu(QMenu* popup);
 /*public*/ int getVersion() ;
 /*public*/ void setVersion(int v);
 virtual /*public*/ LayoutTrack* getConnection(int location) throw (JmriException);
 virtual /*public*/ void setConnection(int location, LayoutTrack *o, int type) throw (JmriException);
 /*public*/ QPointF getCoordsForConnectionType(int connectionType);
 /*public*/ QRectF getBounds();
 /*public*/ QList<int> checkForFreeConnections();
 /*public*/ bool checkForUnAssignedBlocks();
 /*public*/ void checkForNonContiguousBlocks(/*@Nonnull*/QMap<QString, QList<QSet<QString> > > blockNamesToTrackNameSetsMap);
 /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
   /*@Nonnull*/ QSet<QString> TrackNameSet);
 /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock);
 /*public*/ void setState(int state);
 /*public*/ int getState();
 /*public*/ bool isMainline();
 void invalidate(EditScene *g2);


 //make 'public' because of Jmri.h!
 /*private*/ QString secondTurnoutName /*= ""*/;   /* should be the name (system or user) of
                             an existing physical turnout. Second turnout is
                             used to allow the throwing of two different turnout
                             to control one cross-over
                             */
 /*private*/ bool secondTurnoutInverted = false;

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
 void on_setSignalsAct_triggered();
 void on_viewBlockRouting();
 void on_viewRoutingAAct();
 void on_viewRoutingBAct();
 void on_viewRoutingCAct();
 void on_viewRoutingDAct();

private:
 int version;
 void common(QString id, int t, QPointF c, double rot, double xFactor, double yFactor,
             LayoutEditor* myPanel, int v);
    /*private*/ LayoutBlock* blockB;// = NULL;  // Xover - second block, if there is one
    /*private*/ LayoutBlock* blockC;// = NULL;  // Xover - third block, if there is one
    /*private*/ LayoutBlock* blockD;// = NULL;  // Xover - fourth block, if there is one
    /*private*/ PropertyChangeListener* mTurnoutListener;// = NULL;
    /*private*/ bool hidden;// = false;
    /*private*/ bool _useBlockSpeed;// = false;

    /*private*/ double round (double x);
    // updates connectivity for blocks assigned to this turnout and connected track segments
    /*private*/ void updateBlockInfo();
    /**
     * Set default size parameters to correspond to this turnout's size
     */
//    /*private*/ void setUpDefaultSize();
    /**
     * Activate/Deactivate turnout to redraw when turnout state changes
     */
    /*private*/ void activateTurnout();
    /*private*/ void deactivateTurnout();
    /*private*/ bool disableOccupiedTurnout();
    QMenu* popup;// = NULL;
//    JCheckBoxMenuItem* disableItem = NULL;
//    JCheckBoxMenuItem* disableWhenOccupiedItem = NULL;
    LayoutEditorTools* tools;// = NULL;
    static Logger* log;
    QAction* actionRHTurnout;
    QAction* actionLHTurnout;
    QAction* actionWYETurnout;
    QAction* actionXOverTurnout;
    QAction* actionRHXOverTurnout;
    QAction* actionLHXOverTurnout;
    QAction* actionIdent;
    QAction* actionNoTurnout;
    QAction* actionNewTurnout;
    // variables for Edit Layout Turnout pane
    /*private*/ QLineEdit* turnoutNameField;// = new QLineEdit(16);
    /*private*/ QComboBox* secondTurnoutComboBox;
    /*private*/ QLabel* secondTurnoutLabel;
    /*private*/ QLineEdit* blockBNameField;// = new QLineEdit(16);
    /*private*/ QLineEdit* blockCNameField;// = new QLineEdit(16);
    /*private*/ QLineEdit* blockDNameField;// = new QLineEdit(16);
    /*private*/ QComboBox* stateBox;// = new QComboBox();
    /*private*/ QCheckBox* hiddenBox;// = new QCheckBox(rb.getQString("HideTurnout"));
    /*private*/ int turnoutClosedIndex;
    /*private*/ int turnoutThrownIndex;
    /*private*/ QPushButton* turnoutEditBlock;
    /*private*/ QPushButton* turnoutEditDone;
    /*private*/ QPushButton* turnoutEditCancel;
    /*private*/ QPushButton* turnoutEditBlockB;
    /*private*/ QPushButton* turnoutEditBlockC;
    /*private*/ QPushButton* turnoutEditBlockD;
    /*private*/ bool editOpen;// = false;
    /*private*/ QCheckBox* additionalTurnout;// = new QCheckBox(rb.getQString("SupportingTurnout"));
    bool active;// = true;
    QVector<QObject*>* editAdditionalMenu;// = new QVector<QMenuItem*>();
    QVector<QObject*>* viewAdditionalMenu;// = new QVector<QMenuItem*>();
    QGraphicsItemGroup* item = nullptr;
    QGraphicsItemGroup* circles = nullptr;
    QGraphicsItemGroup* rects = nullptr;
    QGraphicsEllipseItem* circle;
//    QGraphicsItemGroup* turnoutItemMain = nullptr;
//    QGraphicsItemGroup* turnoutItemSide = nullptr;
//    void drawTurnouts(LayoutEditor* editor, QGraphicsScene* g2);
//    void drawTurnoutRects(LayoutEditor *editor, QGraphicsScene *g2);
//    void drawTurnoutCircles(LayoutEditor *editor, QGraphicsScene *g2);
//    void repaint(LayoutEditor *editor, QGraphicsScene *g2);
    QVector<QString> boundaryBetween;
    void windowClosing(QCloseEvent*);
    void setTrackSegmentBlocks();
    void setTrackSegmentBlock(int pointType, bool isAutomatic);
    /*private*/ bool isOccupied();
    QGraphicsItemGroup* itemGroup;// = new QGraphicsItemGroup();


private slots:
 /*private*/ void setUpDefaultSize();
 void editLayoutTurnout();
 void on_removeAction_triggered();
 /*public*/ void setDisabled(bool state);
 /*public*/ void setDisableWhenOccupied(bool state);
 void on_rotateItemAction_triggered();
 void redrawPanel();
 void on_viewRoutingAct_triggered();
 void on_setSignalMastsAct_triggered();
 void on_setSensorsAct_triggered();
 //void on_secondTurnoutComboBox_textChanged(QString);
 void on_additionalTurnout_toggled(bool);
 void turnoutEditBlockPressed(ActionEvent* a = 0);
 void turnoutEditBlockBPressed(ActionEvent* a = 0);
 void turnoutEditBlockCPressed(ActionEvent* a = 0);
 void turnoutEditBlockDPressed(ActionEvent* a = 0);
 void turnoutEditDonePressed(ActionEvent* a = 0);
 void turnoutEditCancelPressed(ActionEvent* a = 0);
 void on_blockNameField_textEdited(QString);
 void on_blockBNameField_textEdited(QString);
 void on_blockCNameField_textEdited(QString);
 void on_blockDNameField_textEdited(QString);

protected:
 /*protected*/ LayoutTurnout(/*@Nonnull*/ QString id,
         /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor);
    // operational instance variables (not saved between sessions)
    //private Turnout turnout = NULL;
    /*protected*/ NamedBeanHandle<Turnout*>* namedTurnout;// = NULL;
    //Second turnout is used to either throw a second turnout in a cross over or if one turnout address is used to throw two physical ones
    /*protected*/ NamedBeanHandle<Turnout*>* secondNamedTurnout;// = NULL;
    /*protected*/ LayoutBlock* block;// = NULL;
//    /*protected*/ LayoutTurnout* instance;// = NULL;
//    /*protected*/ LayoutEditor* layoutEditor;// = NULL;
    /*protected*/ void rotateCoords(double rot);
    /*protected*/ QMenu* showPopup(QGraphicsSceneMouseEvent* e);
    /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity();

    /*protected*/ JmriJFrame* editLayoutTurnoutFrame;// = NULL;
    /*protected*/ JTextField* blockNameField;// = new QLineEdit(16);
    /*protected*/ bool needRedraw;// = false;
    /*protected*/ bool needsBlockUpdate;// = false;
    /*protected*/ NamedBeanHandle<SignalMast*>* signalAMastNamed;// = NULL; // Throat
    /*protected*/ NamedBeanHandle<SignalMast*>* signalBMastNamed;// = NULL; // Continuing
    /*protected*/ NamedBeanHandle<SignalMast*>* signalCMastNamed;// = NULL; // diverging
    /*protected*/ NamedBeanHandle<SignalMast*>* signalDMastNamed;// = NULL; // single or double crossover only
    /*protected*/ QPointF rotatePoint(QPointF p, double sineAng, double cosineAng);
    /*protected*/ int getConnectivityStateForLayoutBlocks(        LayoutBlock* currLayoutBlock,
                                                                  LayoutBlock* prevLayoutBlock,
                                                                  LayoutBlock* nextLayoutBlock,
                                                                  bool suppress);

    /*protected*/ NamedBeanHandle<SignalHead*>* signalA1HeadNamed = nullptr; // signal 1 (continuing) (throat for RH, LH, WYE)
    /*protected*/ NamedBeanHandle<SignalHead*>* signalA2HeadNamed = nullptr; // signal 2 (diverging) (throat for RH, LH, WYE)
    /*protected*/ NamedBeanHandle<SignalHead*>* signalA3HeadNamed = nullptr; // signal 3 (second diverging) (3-way turnouts only)
    /*protected*/ NamedBeanHandle<SignalHead*>* signalB1HeadNamed = nullptr; // continuing (RH, LH, WYE) signal 1 (double crossover)
    /*protected*/ NamedBeanHandle<SignalHead*>* signalB2HeadNamed = nullptr; // LH_Xover and double crossover only
    /*protected*/ NamedBeanHandle<SignalHead*>* signalC1HeadNamed = nullptr; // diverging (RH, LH, WYE) signal 1 (double crossover)
    /*protected*/ NamedBeanHandle<SignalHead*>* signalC2HeadNamed = nullptr; // RH_Xover and double crossover only
    /*protected*/ NamedBeanHandle<SignalHead*>* signalD1HeadNamed = nullptr; // single or double crossover only
    /*protected*/ NamedBeanHandle<SignalHead*>* signalD2HeadNamed = nullptr; // LH_Xover and double crossover only
    /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock);
    /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement);
    /*protected*/ void highlightUnconnected(EditScene* g2, int specificType);
    /*protected*/ void drawTurnoutControls(EditScene* g2);
    /*protected*/ void drawEditControls(EditScene* g2);
    /*protected*/ int findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected);


 friend class LayoutEditor;
 friend class EditTurnout;
 friend class LoadXml;
 friend class LayoutSlip;
 friend class SetSignalsActionListener;
 friend class LayoutTurnoutXml;
 friend class ETWindowListener;
 friend class ConnectivityUtil;
 friend class LayoutEditorAuxTools;
 friend class LayoutTrackEditors;
};

class ETWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutTurnout* parent;
 public:
 ETWindowListener(LayoutTurnout* parent);
 void windowClosing(QCloseEvent *e);
};
#endif // LAYOUTTURNOUT_H
