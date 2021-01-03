#ifndef LAYOUTTURNOUT_H
#define LAYOUTTURNOUT_H

#include "layouttrack.h"
#include "turnout.h"
#include "liblayouteditor_global.h"
#include "actionlistener.h"
#include <QPointF>
#include <QVector>
#include "windowlistener.h"
#include "exceptions.h"
#include "abstractaction.h"
#include "layoutblockroutetableaction.h"

class LayoutTurnoutEditor;
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
 enum TurnoutType
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
 Q_ENUM(TurnoutType)
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
  POINTA1 = 0x01,
  POINTA2 = 0x03,
  POINTA3 = 0x05,
  POINTB1 = 0x10,
  POINTB2 = 0x12,
  POINTC1 = 0x20,
  POINTC2 = 0x22,
  POINTD1 = 0x30,
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
    /*protected*/ mutable NamedBeanHandle<Sensor*>* sensorANamed = NULL; // Throat
    /*protected*/ mutable NamedBeanHandle<Sensor*>* sensorBNamed = NULL; // Continuing
    /*protected*/ mutable NamedBeanHandle<Sensor*>* sensorCNamed = NULL; // diverging
    /*protected*/ mutable NamedBeanHandle<Sensor*>* sensorDNamed = NULL; // single or double crossover only
    /*public*/ LayoutTurnout::TurnoutType type;// = RH_TURNOUT;
    /*public*/ LayoutTrack* connectA = NULL;		// throat of LH, RH, RH Xover, LH Xover, and WYE turnouts
    /*public*/ LayoutTrack* connectB = NULL;		// straight leg of LH and RH turnouts
    /*public*/ LayoutTrack* connectC = NULL;
    /*public*/ LayoutTrack* connectD = NULL;		// double xover, RH Xover, LH Xover only
    /*public*/ int continuingSense = Turnout::CLOSED;
    /*public*/ bool disabled = false;
    /*public*/ bool disableWhenOccupied = false;
    /*public*/ QPointF dispB;// = new QPoint.Double(20.0,0.0);
    /*public*/ QPointF dispA;// = new QPoint.Double(20.0,10.0);
    /*public*/ QPointF pointA;// = new Point2D.Double(0, 0);
    /*public*/ QPointF pointB;// = new Point2D.Double(40, 0);
    /*public*/ QPointF pointC;// = new Point2D.Double(60, 20);
    /*public*/ QPointF pointD;// = new Point2D.Double(20, 20);
    /*public*/ QString linkedTurnoutName;// = ""; // name of the linked Turnout (as entered in tool)
    /*public*/ int linkType;// = NO_LINK;
    /**
     * constructor method
     */

    /*public*/ LayoutTurnout(/*@Nonnull*/ QString id, LayoutTurnout::TurnoutType t, /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor);
    /*public*/ LayoutTurnout(/*@Nonnull*/ QString id, LayoutTurnout::TurnoutType t, /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int version);
    /*public*/ QString toString() override;

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
    /*public*/ SignalHead* getSignalA1();
    /*public*/ QString getSignalA1Name();
    /*public*/ SignalHead* getSignalHead(int loc);
    /*public*/ void setSignalA1Name(QString signalHead);
    /*public*/ SignalHead* getSignalA2();
    /*public*/ QString getSignalA2Name();
    /*public*/ void setSignalA2Name(QString signalHead) ;
    /*public*/ SignalHead* getSignalA3();
    /*public*/ QString getSignalA3Name();
    /*public*/ void setSignalA3Name(QString signalHead);
    /*public*/ SignalHead* getSignalB1();
    /*public*/ QString getSignalB1Name();
    /*public*/ void setSignalB1Name(QString signalHead);
    /*public*/ SignalHead* getSignalB2();
    /*public*/ QString getSignalB2Name();
    /*public*/ void setSignalB2Name(QString signalHead);
    /*public*/ SignalHead* getSignalC1();
    /*public*/ QString getSignalC1Name();
    /*public*/ void setSignalC1Name(QString signalHead);
    /*public*/ SignalHead* getSignalC2();
    /*public*/ QString getSignalC2Name();
    /*public*/ void setSignalC2Name(QString signalHead);
    /*public*/ SignalHead* getSignalD1();
    /*public*/ QString getSignalD1Name();
    /*public*/ void setSignalD1Name(QString signalHead);
    /*public*/ SignalHead* getSignalD2();
    /*public*/ QString getSignalD2Name();
    /*public*/ void setSignalD2Name(QString signalHead);
    /*public*/ void removeBeanReference(NamedBean* nb);
    /*public*/ bool canRemove() override;
    /*public*/ QList<QString> getBeanReferences(QString pointName);
    /*public*/ QString getSignalAMastName();
    /*public*/ SignalMast* getSignalAMast() const;
    /*public*/ void setSignalAMast(QString signalMast);
    /*public*/ QString getSignalBMastName();
    /*public*/ SignalMast* getSignalBMast() const;
    /*public*/ void setSignalBMast(QString signalMast);
    /*public*/ QString getSignalCMastName();
    /*public*/ SignalMast *getSignalCMast() const;
    /*public*/ void setSignalCMast(QString signalMast);
    /*public*/ QString getSignalDMastName();
    /*public*/ SignalMast* getSignalDMast() const;
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
    /*public*/ TurnoutType getTurnoutType() const;
    /*public*/ static bool isTurnoutTypeTurnout(TurnoutType type) ;
    /*public*/ bool isTurnoutTypeTurnout() const;
    /*public*/ static bool isTurnoutTypeXover(TurnoutType type);
    /*public*/ bool isTurnoutTypeXover() const;
    /*public*/ static bool isTurnoutTypeSlip(TurnoutType type);
    /*public*/ bool isTurnoutTypeSlip();
    /*public*/ static bool hasEnteringSingleTrack(TurnoutType type);
    /*public*/ bool hasEnteringSingleTrack();
    /*public*/ static bool hasEnteringDoubleTrack(TurnoutType type);
    /*public*/ bool hasEnteringDoubleTrack();
    /*public*/ QObject* getConnectA();
    /*public*/ QObject* getConnectB();
    /*public*/ QObject* getConnectC();
    /*public*/ QObject* getConnectD();
    /*public*/ Turnout* getTurnout();
    /**
     * Accessor methods
    */
    /*public*/ int getContinuingSense();
    /*public*/ bool isInContinuingSenseState();
    /*public*/ void setTurnout(QString tName);
    /*public*/ Turnout* getSecondTurnout();
    /*public*/ void setSecondTurnout(QString tName);
    /*public*/ void setContinuingSense(int sense);
    /*public*/ bool isDisabled();
   /*public*/ bool isDisabledWhenOccupied();
    /*public*/ void setConnectA(LayoutTrack *o, int type);
    /*public*/ void setConnectB(LayoutTrack* o,int type);
    /*public*/ void setConnectC(LayoutTrack *o, int type);
    /*public*/ void setConnectD(LayoutTrack* o,int type);
    /*public*/ LayoutBlock* getLayoutBlock() const;
    /*public*/ LayoutBlock* getLayoutBlockB() const;
    /*public*/ LayoutBlock* getLayoutBlockC() const ;
    /*public*/ LayoutBlock* getLayoutBlockD() const;
//    /*public*/ QPointF getCoordsCenter();
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
    /*public*/ void setCoordsCenter(QPointF p) override ;
    /*public*/ void setCoordsA(QPointF p);
    /*public*/ void setCoordsB(QPointF p);
    /*public*/ void setCoordsC(QPointF p);
    /*public*/ void setCoordsD(QPointF p);
    /*public*/ void scaleCoords(double xFactor, double yFactor) override;
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
    /*public*/ QString tBlockAName;// = "";
    /*public*/ QString tBlockBName;// = "";
    /*public*/ QString tBlockCName;// = "";
    /*public*/ QString tBlockDName;// = "";
 /**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void setObjects(LayoutEditor* p);

/*public*/ QStringList getBlockBoundaries();
 /*public*/ QList<LayoutBlock*> getProtectedBlocks(NamedBean* bean);

 /*public*/ void reCheckBlockBoundary()const override;
 void removeSML(SignalMast *signalMast) const;
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
 /*public*/ LayoutTrack* getConnection(int location) throw (JmriException) override;
 /*public*/ void setConnection(int location, LayoutTrack *o, int type) throw (JmriException) override;
 /*public*/ QPointF getCoordsForConnectionType(int connectionType) override;
 /*public*/ QRectF getBounds() override;
 /*public*/ QList<int> checkForFreeConnections() override;
 /*public*/ bool checkForUnAssignedBlocks() override;
 /*public*/ void checkForNonContiguousBlocks(/*@Nonnull*/QMap<QString, QList<QSet<QString>*>*>* blockNamesToTrackNameSetsMap) override;
 /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
   /*@Nonnull*/ QSet<QString>* TrackNameSet) override;
 /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock) override;
 /*public*/ void setState(int state);
 /*public*/ int getState();
 /*public*/ bool isMainline() override;
 void invalidate(EditScene *g2) override;


 //make 'public' because of Jmri.h!
 /*private*/ QString secondTurnoutName /*= ""*/;   /* should be the name (system or user) of
                             an existing physical turnout. Second turnout is
                             used to allow the throwing of two different turnout
                             to control one cross-over
                             */
 /*private*/ bool secondTurnoutInverted = false;
 QGraphicsItemGroup* itemGroup = nullptr;

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:

private:
 int version;
 void common(QString id, LayoutTurnout::TurnoutType t, QPointF c, double rot, double xFactor, double yFactor,
             LayoutEditor* myPanel, int v);
    /*private*/ LayoutBlock* blockB = NULL;  // Xover - second block, if there is one
    /*private*/ LayoutBlock* blockC = NULL;  // Xover - third block, if there is one
    /*private*/ LayoutBlock* blockD = NULL;  // Xover - fourth block, if there is one
    /*private*/ PropertyChangeListener* mTurnoutListener;// = NULL;
    /*private*/ bool hidden = false;
    /*private*/ bool _useBlockSpeed = false;

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
    LayoutEditorTools* tools;// = NULL;
    static Logger* log;
    QAction* actionRHTurnout = nullptr;
    QAction* actionLHTurnout = nullptr;
    QAction* actionWYETurnout = nullptr;
    QAction* actionXOverTurnout = nullptr;
    QAction* actionRHXOverTurnout = nullptr;
    QAction* actionLHXOverTurnout = nullptr;
    // variables for Edit Layout Turnout pane
    /*private*/ QLineEdit* turnoutNameField;// = new QLineEdit(16);
    /*private*/ QComboBox* secondTurnoutComboBox = nullptr;
    /*private*/ QLabel* secondTurnoutLabel  = nullptr;
    /*private*/ QLineEdit* blockBNameField;// = new QLineEdit(16);
    /*private*/ QLineEdit* blockCNameField;// = new QLineEdit(16);
    /*private*/ QLineEdit* blockDNameField;// = new QLineEdit(16);
    /*private*/ QComboBox* stateBox;// = new QComboBox();
    /*private*/ QCheckBox* hiddenBox;// = new QCheckBox(rb.getQString("HideTurnout"));
    /*private*/ int turnoutClosedIndex;
    /*private*/ int turnoutThrownIndex;
    /*private*/ QPushButton* turnoutEditBlock = nullptr;
    /*private*/ QPushButton* turnoutEditDone = nullptr;
    /*private*/ QPushButton* turnoutEditCancel = nullptr;
    /*private*/ QPushButton* turnoutEditBlockB = nullptr;
    /*private*/ QPushButton* turnoutEditBlockC = nullptr;
    /*private*/ QPushButton* turnoutEditBlockD = nullptr;
    /*private*/ bool editOpen;// = false;
    /*private*/ QCheckBox* additionalTurnout;// = new QCheckBox(rb.getQString("SupportingTurnout"));
    bool active;// = true;
    QVector<QObject*>* editAdditionalMenu;// = new QVector<QMenuItem*>();
    QVector<QObject*>* viewAdditionalMenu;// = new QVector<QMenuItem*>();
    QGraphicsItemGroup* item = nullptr;
    QGraphicsItemGroup* circles = nullptr;
    QGraphicsItemGroup* rects = nullptr;
    QGraphicsEllipseItem* circle;
    QVector<QString> boundaryBetween;
    void windowClosing(QCloseEvent*);
    void setTrackSegmentBlocks();
    void setTrackSegmentBlock(int pointType, bool isAutomatic);
    /*private*/ bool isOccupied();
    /*private*/ void reCalculateCenter();


private slots:
 /*private*/ void setUpDefaultSize();
 void editLayoutTurnout();
 void on_removeAction_triggered();
 /*public*/ void setDisabled(bool state);
 /*public*/ void setDisableWhenOccupied(bool state);
 void on_rotateItemAction_triggered();
 void redrawPanel();
 //void on_viewRoutingAct_triggered();
 void on_additionalTurnout_toggled(bool);
 void turnoutEditBlockPressed(JActionEvent* a = 0);
 void turnoutEditBlockBPressed(JActionEvent* a = 0);
 void turnoutEditBlockCPressed(JActionEvent* a = 0);
 void turnoutEditBlockDPressed(JActionEvent* a = 0);
 void turnoutEditDonePressed(JActionEvent* a = 0);
 void turnoutEditCancelPressed(JActionEvent* a = 0);
 void on_blockNameField_textEdited(QString);
 void on_blockBNameField_textEdited(QString);
 void on_blockCNameField_textEdited(QString);
 void on_blockDNameField_textEdited(QString);

protected:
 // temporary reference to the Editor that will eventually be part of View - should be moved to ctors and final
  /*protected*/ LayoutTurnoutEditor* editor;

 /*protected*/ LayoutTurnout(/*@Nonnull*/ QString id,
     /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor);
 /*protected*/ LayoutTurnout(/*@Nonnull*/ QString id,
         /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor, LayoutTurnout::TurnoutType t);

 // operational instance variables (not saved between sessions)
 //private Turnout turnout = NULL;
 /*protected*/ NamedBeanHandle<Turnout*>* namedTurnout;// = NULL;
 //Second turnout is used to either throw a second turnout in a cross over or if one turnout address is used to throw two physical ones
 /*protected*/ NamedBeanHandle<Turnout*>* secondNamedTurnout;// = NULL;
 /*protected*/ LayoutBlock* block;// = NULL;
 /*protected*/ void rotateCoords(double angleDEG);
 /*protected*/ QMenu* showPopup(QGraphicsSceneMouseEvent* e) override;
 /*protected*/ QList<LayoutConnectivity*>* getLayoutConnectivity() override;

 /*protected*/ JmriJFrame* editLayoutTurnoutFrame;// = NULL;
 /*protected*/ JTextField* blockNameField;// = new QLineEdit(16);
 /*protected*/ bool needRedraw;// = false;
 /*protected*/ bool needsBlockUpdate;// = false;
 /*protected*/ mutable NamedBeanHandle<SignalMast*>* signalAMastNamed;// = NULL; // Throat
 /*protected*/ mutable NamedBeanHandle<SignalMast*>* signalBMastNamed;// = NULL; // Continuing
 /*protected*/ mutable NamedBeanHandle<SignalMast*>* signalCMastNamed;// = NULL; // diverging
 /*protected*/ mutable NamedBeanHandle<SignalMast*>* signalDMastNamed;// = NULL; // single or double crossover only
 /*protected*/ QPointF rotatePoint(QPointF p, double sineAng, double cosineAng);
 /*protected*/ int getConnectivityStateForLayoutBlocks(        LayoutBlock* currLayoutBlock,
                                                               LayoutBlock* prevLayoutBlock,
                                                               LayoutBlock* nextLayoutBlock,
                                                               bool suppress);
 // default is package protected
 /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockA = nullptr;
 /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockB = nullptr;  // Xover - second block, if there is one
 /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockC = nullptr;  // Xover - third block, if there is one
 /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockD = nullptr;  // Xover - forth block, if there is one

 /*protected*/ NamedBeanHandle<SignalHead*>* signalA1HeadNamed = nullptr; // signal 1 (continuing) (throat for RH, LH, WYE)
 /*protected*/ NamedBeanHandle<SignalHead*>* signalA2HeadNamed = nullptr; // signal 2 (diverging) (throat for RH, LH, WYE)
 /*protected*/ NamedBeanHandle<SignalHead*>* signalA3HeadNamed = nullptr; // signal 3 (second diverging) (3-way turnouts only)
 /*protected*/ NamedBeanHandle<SignalHead*>* signalB1HeadNamed = nullptr; // continuing (RH, LH, WYE) signal 1 (double crossover)
 /*protected*/ NamedBeanHandle<SignalHead*>* signalB2HeadNamed = nullptr; // LH_Xover and double crossover only
 /*protected*/ NamedBeanHandle<SignalHead*>* signalC1HeadNamed = nullptr; // diverging (RH, LH, WYE) signal 1 (double crossover)
 /*protected*/ NamedBeanHandle<SignalHead*>* signalC2HeadNamed = nullptr; // RH_Xover and double crossover only
 /*protected*/ NamedBeanHandle<SignalHead*>* signalD1HeadNamed = nullptr; // single or double crossover only
 /*protected*/ NamedBeanHandle<SignalHead*>* signalD2HeadNamed = nullptr; // LH_Xover and double crossover only
 /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock) override;
 /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement) override;
 /*protected*/ void highlightUnconnected(EditScene* g2, int specificType) override;
 /*protected*/ void drawTurnoutControls(EditScene* g2) override;
 /*protected*/ void drawEditControls(EditScene* g2) override;
 /*protected*/ int findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) override;


 friend class LayoutEditor;
 friend class EditTurnout;
 friend class LoadXml;
 friend class LayoutSlip;
 friend class SetSignalsActionListener;
 friend class LayoutTurnoutXml;
 friend class ETWindowListener;
 friend class ConnectivityUtil;
 friend class LayoutEditorAuxTools;
 //friend class LayoutTrackEditors;
 friend class MTurnoutListener;
 friend class LayoutTurnoutEditor;
 friend class LayoutTurnoutView;
 friend class LayoutEditorComponent;
};

class ETWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutTurnout* parent;
 public:
 ETWindowListener(LayoutTurnout* parent);
 void windowClosing(QCloseEvent *e);
};

class MTurnoutListener : public PropertyChangeListener
{
 Q_OBJECT
 LayoutTurnout* layoutTurnout;
public:
 MTurnoutListener(LayoutTurnout* layoutTurnout) {this->layoutTurnout = layoutTurnout;}
public slots:
 void propertyChange(PropertyChangeEvent* e) override;
};

/*private*/ /*static*/ class AbstractActionImpl : public AbstractAction
{
 Q_OBJECT
    /*private*/ /*final*/ QString blockName;
    /*private*/ /*final*/ LayoutBlock* layoutBlock;
public:
    /*public*/ AbstractActionImpl(QString name, QString blockName, LayoutBlock* layoutBlock, QObject* parent)
  : AbstractAction(name, parent)
    {
        //super(name);
        this->blockName = blockName;
        this->layoutBlock = layoutBlock;
    }
public slots:
    //@Override
    /*public*/ void actionPerformed(/*ActionEvent e*/) {
        AbstractAction* routeTableAction = new LayoutBlockRouteTableAction(blockName, layoutBlock);
        routeTableAction->actionPerformed(/*e*/);
    }
};
#endif // LAYOUTTURNOUT_H
