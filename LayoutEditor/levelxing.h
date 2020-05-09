#ifndef LEVELXING_H
#define LEVELXING_H

#include <QObject>
#include "layoutblock.h"
#include "layouteditor.h"
#include <QPointF>
//#include "signalmast.h"
#include <QMenu>
#include <QLineEdit>
#include <QPushButton>
//#include <QMenuItem>
#include <QMouseEvent>
#include "layouteditortools.h"
#include <QWidget>
#include "liblayouteditor_global.h"
#include <cmath>

class QMenuItem;
class LayoutBlock;
class LayoutEditor;
class SignalMast;
class LIBLAYOUTEDITORSHARED_EXPORT LevelXing : public LayoutTrack
{
    Q_OBJECT
public:
    //explicit LevelXing(QObject *parent = 0);
    /**
     * constructor method
     */
    /*public*/ LevelXing(QString id, QPointF c, LayoutEditor* myPanel);
 enum POINTS
 {
  POINTA = 0x01,
  POINTB = 0x10,
  POINTC = 0x20,
  POINTD = 0x30
};
    /**
     * Accessor methods
    */
    /*public*/ QString getID() {return ident;}
    /*public*/ QString getBlockNameAC() {return blockNameAC;}
    /*public*/ QString getBlockNameBD() {return blockNameBD;}
    /*public*/ QString getSignalAName() {return signalAName;}
    /*public*/ void setSignalAName(QString signalName) {signalAName = signalName;}
    /*public*/ QString getSignalBName() {return signalBName;}
    /*public*/ void setSignalBName(QString signalName) {signalBName = signalName;}
    /*public*/ QString getSignalCName() {return signalCName;}
    /*public*/ void setSignalCName(QString signalName) {signalCName = signalName;}
    /*public*/ QString getSignalDName() {return signalDName;}
    /*public*/ void setSignalDName(QString signalName) {signalDName = signalName;}
    /*public*/ void removeBeanReference(NamedBean* nb);
    /*public*/ QString getSignalAMastName();
    /*public*/ void setSignalAMastName(QString signalName) {signalAMastName = signalName;}
    /*public*/ QString getSignalBMastName() {return signalBMastName;}
    /*public*/ void setSignalBMastName(QString signalName) {signalBMastName = signalName;}
    /*public*/ QString getSignalCMastName() {return signalCMastName;}
    /*public*/ void setSignalCMastName(QString signalName) {signalCMastName = signalName;}
    /*public*/ QString getSignalDMastName() {return signalDMastName;}
    /*public*/ void setSignalDMastName(QString signalName) {signalDMastName = signalName;}
    /*public*/ QString getSensorAName();
    /*public*/ void setSensorAName(QString sensorName);
    /*public*/ QString getSensorBName();
    /*public*/ void setSensorBName(QString sensorName);
    /*public*/ QString getSensorCName();
    /*public*/ void setSensorCName(QString sensorName);
    /*public*/ QString getSensorDName();
    /*public*/ void setSensorDName(QString sensorName);
    /*public*/ QObject* getConnectA() {return connectA;}
    /*public*/ QObject* getConnectB() {return connectB;}
    /*public*/ QObject* getConnectC() {return connectC;}
    /*public*/ QObject* getConnectD() {return connectD;}
    /*public*/ void setConnectA(LayoutTrack* o,int type);
    /*public*/ void setConnectB(LayoutTrack *o, int type);
    /*public*/ void setConnectC(LayoutTrack* o,int type);
    /*public*/ void setConnectD(LayoutTrack *o, int type);
    /*public*/ LayoutBlock* getLayoutBlockAC();
    /*public*/ LayoutBlock* getLayoutBlockBD();
    /*public*/ QPointF getCoordsCenter();
    /*public*/ QPointF getCoordsA();
    /*public*/ QPointF getCoordsB();
    /*public*/ QPointF getCoordsC();
    /*public*/ QPointF getCoordsD();
    /**
     * Add Layout Blocks
     */
    /*public*/ void setLayoutBlockAC (LayoutBlock* newLayoutBlock) ;
    /*public*/ void setLayoutBlockBD (LayoutBlock* newLayoutBlock);
    /*public*/ void reCheckBlockBoundary()const override;
//    void removeSML(QString signalMast);
    /**
     * Methods to test if mainline track or not
     *  Returns true if either connecting track segment is mainline
     *  Defaults to not mainline if connecting track segments are missing
     */
    /*public*/ bool isMainlineAC();
    /*public*/ bool isMainlineBD();
    /**
     * Modify coordinates methods
     */
    /*public*/ void setCoordsCenter(QPointF p)override;
    /*public*/ void setCoordsA(QPointF p);
    /*public*/ void setCoordsB(QPointF p);
    /*public*/ void setCoordsC(QPointF p);
    /*public*/ void setCoordsD(QPointF p);
    /*public*/ void scaleCoords(double xFactor, double yFactor)override;
    double round (double x);

    /**
     * Initialization method
     *   The above variables are initialized by PositionablePointXml, then the following
     *        method is called after the entire LayoutEditor is loaded to set the specific
     *        TrackSegment objects.
     */
    /*public*/ void setObjects(LayoutEditor* p)override;
    // initialization instance variables (used when loading a LayoutEditor)
    /*public*/ QString connectAName;// = "";
    /*public*/ QString connectBName;// = "";
    /*public*/ QString connectCName;// = "";
    /*public*/ QString connectDName;// = "";
    /*public*/ QString tBlockNameAC;// = "";
    /*public*/ QString tBlockNameBD;// = "";
    QMenu* popup;// = NULL;
    LayoutEditorTools* tools;// = NULL;
    /*public*/ QVector<QString>* getBlockBoundaries();
//    /*public*/ void removeSignalMastLogic(SignalMast* sm);
    void invalidate(QGraphicsScene* g2);
//    void drawXings(LayoutEditor* editor, QGraphicsScene* g2);
    void drawXingRects(LayoutEditor* editor, QGraphicsScene* g2);
    /*public*/ void addSignalMastLogic(SignalMast* sm);
    /*public*/ void removeSignalMastLogic(SignalMast* sm);
    /*public*/ void addEditPopUpMenu(QMenu* menu);
    /*public*/ void addViewPopUpMenu(QMenu* menu);
    /*public*/ SignalMast* getSignalAMast();
    /*public*/ SignalHead* getSignalHead(int loc);
    /*public*/ void setSignalAMast(QString signalMast) ;
    /*public*/ SignalMast* getSignalBMast();
    /*public*/ void setSignalBMast(QString signalMast) ;
    /*public*/ SignalMast* getSignalCMast();
    /*public*/ void setSignalCMast(QString signalMast);
    /*public*/ SignalMast* getSignalDMast();
    /*public*/ void setSignalDMast(QString signalMast);
    /*public*/ LayoutTrack* getConnection(int location) throw (JmriException)override;
    /*public*/ void setConnection(int location, LayoutTrack *o, int type) throw (JmriException);
    /*public*/ QPointF getCoordsForConnectionType(int connectionType)override;
    /*public*/ QRectF getBounds()override;
    /*public*/ Sensor* getSensorA();
    /*public*/ Sensor* getSensorB();
    /*public*/ Sensor* getSensorC();
    /*public*/ Sensor* getSensorD();
    /*public*/ void addViewPopUpMenu(QMenuItem menu);
    /*public*/ void setAdditionalEditPopUpMenu(QMenu* popup);
    /*public*/ void setAdditionalViewPopUpMenu(QMenu* popup);
    /*public*/ void translateCoords(double xFactor, double yFactor)override;
    /*public*/ QList<int> checkForFreeConnections() override;
    /*public*/ bool checkForUnAssignedBlocks() override;
    /*public*/ void checkForNonContiguousBlocks(/*@Nonnull*/ QMap<QString, QList<QSet<QString> *> *> *blockNamesToTrackNameSetsMap) override;
    /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
            /*@Nonnull*/ QSet<QString>* TrackNameSet);
    /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock);

signals:
    
public slots:
    void On_viewBlockRoutingAC();
    void On_viewBlockRoutingBD();
    void on_set_signals();
    void on_setSignalMasts();
    void on_setSensors();
private:
    // defined constants

    // operational instance variables (not saved between sessions)
    /*private*/ LayoutBlock* blockAC;// = NULL;
    /*private*/ LayoutBlock* blockBD;// = NULL;
    /*private*/ LevelXing* instance;// = NULL;
    /*private*/ LayoutEditor* layoutEditor;// = NULL;

    // persistent instances variables (saved between sessions)
//    /*private*/ QString ident;// = "";
    /*private*/ QString blockNameAC;// = "";
    /*private*/ QString blockNameBD; //"";
    /*private*/ QString signalAName; //"";  // signal at A track junction
    /*private*/ QString signalBName; //"";  // signal at B track junction
    /*private*/ QString signalCName; //"";  // signal at C track junction
    /*private*/ QString signalDName; //"";  // signal at D track junction

    /*private*/ QString signalAMastName; //"";  // signal at A track junction
    /*private*/ QString signalBMastName; //"";  // signal at B track junction
    /*private*/ QString signalCMastName; //"";  // signal at C track junction
    /*private*/ QString signalDMastName; //"";  // signal at D track junction

    /*/*private*/ QString sensorAName; //"";  // sensor at A track junction
    /*private*/ QString sensorBName; //"";  // sensor at B track junction
    /*private*/ QString sensorCName; //"";  // sensor at C track junction
    /*private*/ QString sensorDName; //"";  // sensor at D track junction    */

    /*private*/ NamedBeanHandle<Sensor*>* sensorANamed; //NULL; // sensor at A track junction
    /*private*/ NamedBeanHandle<Sensor*>* sensorBNamed; //NULL; // sensor at B track junction
    /*private*/ NamedBeanHandle<Sensor*>* sensorCNamed; //NULL; // sensor at C track junction
    /*private*/ NamedBeanHandle<Sensor*>* sensorDNamed; //NULL; // sensor at D track junction

    /*private*/ LayoutTrack* connectA; //NULL;
    /*private*/ LayoutTrack* connectB; //NULL;
    /*private*/ LayoutTrack* connectC; //NULL;
    /*private*/ LayoutTrack* connectD; //NULL;
    /*private*/ QPointF center; //new QPointF(50.0,50.0);
    /*private*/ QPointF dispA; //new QPointF(-20.0,0.0);
    /*private*/ QPointF dispB; //new QPointF(-14.0,14.0);
    // variables for Edit Level Crossing pane
    QWidget* editLevelXingFrame;// = NULL;
    QLineEdit* block1Name;// = new QTextEdit(16);
    QLineEdit* block2Name;// = new QTextEdit(16);
    QPushButton* xingEditDone;
    QPushButton* xingEditCancel;
    QPushButton* xingEdit1Block;
    QPushButton* xingEdit2Block;
    bool editOpen;// = false;
    bool needsRedraw;// = false;
    bool needsBlockUpdate;// = false;
    /**
     * Clean up when this object is no longer needed.  Should not
     * be called while the object is still displayed; see remove()
     */
    void dispose();
    /**
     * Removes this object from display and persistance
     */
    void remove();
    bool active;// = true;
    /**
     * "active" means that the object is still displayed, and should be stored.
     */
    /*public*/ bool isActive();
    QVector<SignalMast*>* sml;// = new QVector<SignalMast*>();
    QVector<QMenu*>* editAdditionalMenu;// = new QVector<QMenuItem*>(0);
    QVector<QMenu*>* viewAdditionalMenu;// = new QVector<QMenuItem*>(0);
 QGraphicsItemGroup* item;
 QGraphicsItemGroup* rects;
 Logger log;
 /*private*/ void updateBlockInfo();
 void removeSML(SignalMast* signalMast);
 /*final*/ QVector<QString>* boundaryBetween;
 QGraphicsItemGroup* itemGroup =nullptr;

private slots:
void on_xingEdit1Block_clicked();
void on_xingEdit2Block_clicked();
void on_xingEditDone_clicked();
void on_xingEditCancel_clicked();
/**
 * Edit a Level Crossing
 */
/*protected*/ void editLevelXing(/*LevelXing* o*/);
void on_removeAction_triggered();
///*private*/ void drawXingAC(LayoutEditor* editor);
///*private*/ void drawXingBD(LayoutEditor* editor);

protected:
/**
 * Display popup menu for information and editing
 */
 /*protected*/ QMenu* showPopup(QGraphicsSceneMouseEvent* e)override;

 /*private*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockAC = nullptr;
 /*private*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockBD = nullptr;

 /*protected*/ NamedBeanHandle<SignalHead*>* signalAHeadNamed;// = NULL; // signal at A track junction
 /*protected*/ NamedBeanHandle<SignalHead*>* signalBHeadNamed;// = NULL; // signal at B track junction
 /*protected*/ NamedBeanHandle<SignalHead*>* signalCHeadNamed;// = NULL; // signal at C track junction
 /*protected*/ NamedBeanHandle<SignalHead*>* signalDHeadNamed;// = NULL; // signal at D track junction

 /*protected*/ NamedBeanHandle<SignalMast*>* signalAMastNamed;// = NULL; // signal at A track junction
 /*protected*/ NamedBeanHandle<SignalMast*>* signalBMastNamed;// = NULL; // signal at B track junction
 /*protected*/ NamedBeanHandle<SignalMast*>* signalCMastNamed;// = NULL; // signal at C track junction
 /*protected*/ NamedBeanHandle<SignalMast*>* signalDMastNamed;// = NULL; // signal at D track junction
/*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock, ITEMTYPE itemType)override;
/*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement, ITEMTYPE itemType)override;
/*protected*/ void highlightUnconnected(EditScene* g2, int specificType)override;
/*protected*/ void drawEditControls(EditScene* g2)override;
/*protected*/ void drawTurnoutControls(EditScene* g2)override;
/*protected*/ int findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected)override;
/*protected*/ QList<LayoutConnectivity*>* getLayoutConnectivity() override;

friend class LayoutEditor;
friend class LoadXml;
friend class EditLevelXingDlg;
friend class LayoutTrackEditors;
};

#endif // LEVELXING_H
