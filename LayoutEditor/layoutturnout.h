#ifndef LAYOUTTURNOUT_H
#define LAYOUTTURNOUT_H

#include <QObject>
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
class LIBLAYOUTEDITORSHARED_EXPORT LayoutTurnout : public QObject
{
    Q_OBJECT
public:
    //explicit LayoutTurnout(QObject *parent = 0);
    // defined constants - turnout types
    /*public*/ static /*final*/const  int RH_TURNOUT = 1;
    /*public*/ static /*final*/const  int LH_TURNOUT = 2;
    /*public*/ static /*final*/const  int WYE_TURNOUT = 3;
    /*public*/ static /*final*/const  int DOUBLE_XOVER = 4;
    /*public*/ static /*final*/const  int RH_XOVER = 5;
    /*public*/ static /*final*/const  int LH_XOVER = 6;
    /*public*/ static /*final*/const  int SINGLE_SLIP = 7; //used in LayoutSlip which extends this class
    /*public*/ static /*final*/const  int DOUBLE_SLIP = 8; //used in LayoutSlip which extends this class
    // defined constants - link types
    /*public*/ static /*final*/const  int NO_LINK = 0;
    /*public*/ static /*final*/const  int FIRST_3_WAY = 1;       // this turnout is the first turnout of a 3-way
                                                    // turnout pair (closest to the throat)
    /*public*/ static /*final*/const  int SECOND_3_WAY = 2;      // this turnout is the second turnout of a 3-way
                                                    // turnout pair (furthest from the throat)
    /*public*/ static /*final*/const  int THROAT_TO_THROAT = 3;  // this turnout is one of two throat-to-throat
                                                    // turnouts - no signals at throat
    // persistent instances variables (saved between sessions)
    /*public*/ QString ident;   // name of this layout turnout (hidden from user)
    /*public*/ QString turnoutName;// = "";   // should be the name (system or user) of
                                //	an existing physical turnout
    /*public*/ QString secondTurnoutName /*= ""*/;   /* should be the name (system or user) of
                                an existing physical turnout. Second turnout is
                                used to allow the throwing of two different turnout
                                to control one cross-over
                                */
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
    /*public*/ QObject* connectA;// = NULL;		// throat of LH, RH, RH Xover, LH Xover, and WYE turnouts
    /*public*/ QObject* connectB;// = NULL;		// straight leg of LH and RH turnouts
    /*public*/ QObject* connectC;// = NULL;
    /*public*/ QObject* connectD;// = NULL;		// double xover, RH Xover, LH Xover only
    /*public*/ int continuingSense;// = Turnout::CLOSED;
    /*public*/ bool disabled;// = false;
    /*public*/ bool disableWhenOccupied;// = false;
    /*public*/ QPointF center;// = new QPoint.Double(50.0,50.0);
    /*public*/ QPointF dispB;// = new QPoint.Double(20.0,0.0);
    /*public*/ QPointF dispC;// = new QPoint.Double(20.0,10.0);
    /*public*/ QString linkedTurnoutName;// = ""; // name of the linked Turnout (as entered in tool)
    /*public*/ int linkType;// = NO_LINK;
    /**
     * constructor method
     */
    /*public*/ LayoutTurnout(QString id, int t, QPointF c, double rot, double xFactor, double yFactor, LayoutEditor* myPanel, int version = 1);
    /**
     * Accessor methods
    */
    /*public*/ QString getName();
    /*public*/ bool useBlockSpeed();
    /*public*/ QString getTurnoutName();
    /*public*/ QString getSecondTurnoutName();
    /*public*/ bool getHidden();
    /*public*/ void setHidden(bool hide);
    /*public*/ QString getBlockName();
    /*public*/ QString getBlockBName();
    /*public*/ QString getBlockCName();
    /*public*/ QString getBlockDName();
    /*public*/ QString getSignalA1Name();
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

    /*public*/ QString getSignalAMastName();
    /*public*/ QString getSignalAMast();
    /*public*/ void setSignalAMast(QString signalMast);
    /*public*/ QString getSignalBMastName();
    /*public*/ QString getSignalBMast();
    /*public*/ void setSignalBMast(QString signalMast);
    /*public*/ QString getSignalCMastName();
    /*public*/ QString getSignalCMast();
    /*public*/ void setSignalCMast(QString signalMast);
    /*public*/ QString getSignalDMastName();
    /*public*/ QString getSignalDMast();
    /*public*/ void setSignalDMast(QString signalMast);
    /*public*/ QString getSensorAName();
    /*public*/ QString getSensorA();
    /*public*/ void setSensorA(QString sensorName);
    /*public*/ QString getSensorBName();
    /*public*/ QString getSensorB();
    /*public*/ void setSensorB(QString sensorName);
    /*public*/ QString getSensorCName();
    /*public*/ QString getSensorC();
    /*public*/ void setSensorC(QString sensorName);
    /*public*/ QString getSensorDName();
    /*public*/ QString getSensorD();
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
    /*public*/ void setConnectA(QObject* o,int type);
    /*public*/ void setConnectB(QObject* o,int type);
    /*public*/ void setConnectC(QObject* o,int type);
    /*public*/ void setConnectD(QObject* o,int type);
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

 /*public*/ void reCheckBlockBoundary();
 void removeSML(QString signalMast);
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
 void drawTurnoutRects(LayoutEditor *editor, QGraphicsScene *g2);
 /*public*/ int getVersion() ;
 /*public*/ void setVersion(int v);

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
Logger* log;
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
QGraphicsItemGroup* item;
QGraphicsItem* rects;
void invalidate(QGraphicsScene* g2);
void drawTurnouts(LayoutEditor* editor, QGraphicsScene* g2);
void drawTurnoutCircles(LayoutEditor *editor, QGraphicsScene *g2);
void repaint(LayoutEditor *editor, QGraphicsScene *g2);
QVector<QString> boundaryBetween;
void windowClosing(QCloseEvent*);


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
    // operational instance variables (not saved between sessions)
    //private Turnout turnout = NULL;
    /*protected*/ NamedBeanHandle<Turnout*>* namedTurnout;// = NULL;
    //Second turnout is used to either throw a second turnout in a cross over or if one turnout address is used to throw two physical ones
    /*protected*/ NamedBeanHandle<Turnout*>* secondNamedTurnout;// = NULL;
    /*protected*/ LayoutBlock* block;// = NULL;
    /*protected*/ LayoutTurnout* instance;// = NULL;
    /*protected*/ LayoutEditor* layoutEditor;// = NULL;
    /*protected*/ LayoutTurnout() {}
    /*protected*/ void rotateCoords(double rot);
/*protected*/ void showPopUp(QGraphicsSceneMouseEvent* e, bool editable);
 friend class LayoutEditor;
 friend class EditTurnout;
/*protected*/ JmriJFrame* editLayoutTurnoutFrame;// = NULL;
/*protected*/ JTextField* blockNameField;// = new QLineEdit(16);
/*protected*/ bool needRedraw;// = false;
/*protected*/ bool needsBlockUpdate;// = false;
 /*protected*/ NamedBeanHandle<SignalMast*>* signalAMastNamed;// = null; // Throat
 /*protected*/ NamedBeanHandle<SignalMast*>* signalBMastNamed;// = null; // Continuing
 /*protected*/ NamedBeanHandle<SignalMast*>* signalCMastNamed;// = null; // diverging
 /*protected*/ NamedBeanHandle<SignalMast*>* signalDMastNamed;// = null; // single or double crossover only
 /*protected*/ QPointF rotatePoint(QPointF p, double sineAng, double cosineAng);

/**
 * Edit a Layout Turnout
 */
///*protected*/ void editLayoutTurnout();
friend class LoadXml;
friend class LayoutSlip;
friend class SetSignalsActionListener;
friend class LayoutTurnoutXml;
friend class ETWindowListener;

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
