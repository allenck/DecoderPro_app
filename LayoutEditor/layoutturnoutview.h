#ifndef LAYOUTTURNOUTVIEW_H
#define LAYOUTTURNOUTVIEW_H
#include "layouttrackview.h"
#include <QPointF>
#include "turnout.h"
#include "namedbeanhandle.h"
#include "layoutturnout.h"

class LayoutTurnoutView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ LayoutTurnoutView(/*@Nonnull*/ LayoutTurnout* turnout,
          /*@Nonnull*/ QPointF c, double rot,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutTurnoutView(/*@Nonnull*/ LayoutTurnout* turnout,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  // operational instance variables (not saved between sessions)
  /*public*/ static /*final*/ const int UNKNOWN = Turnout::UNKNOWN;
  /*public*/ static /*final*/ const int INCONSISTENT = Turnout::INCONSISTENT;
  /*public*/ static /*final*/ const int STATE_AC = 0x02;
  /*public*/ static /*final*/ const int STATE_BD = 0x04;
  /*public*/ static /*final*/ const int STATE_AD = 0x06;
  /*public*/ static /*final*/ const int STATE_BC = 0x08;

  // program default turnout size parameters
  /*public*/ static /*final*/ constexpr double turnoutBXDefault = 20.0;  // RH, LH, WYE
  /*public*/ static /*final*/ constexpr double turnoutCXDefault = 20.0;
  /*public*/ static /*final*/ constexpr double turnoutWidDefault = 10.0;
  /*public*/ static /*final*/ constexpr double xOverLongDefault = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
  /*public*/ static /*final*/ constexpr double xOverHWidDefault = 10.0;
  /*public*/ static /*final*/ constexpr double xOverShortDefault = 10.0;

  /*public*/ QPointF dispB;// = QPointF(20.0, 0.0);
  /*public*/ QPointF dispA;// = QPointF(20.0, 10.0);
  /*public*/ QPointF pointA;// = QPointF(0, 0);
  /*public*/ QPointF pointB;// = QPointF(40, 0);
  /*public*/ QPointF pointC;// = QPointF(60, 20);
  /*public*/ QPointF pointD;// = QPointF(20, 20);
  /*public*/ static bool isTurnoutTypeTurnout(LayoutTurnout::TurnoutType);
  /*public*/ bool isTurnoutTypeTurnout();
  /*public*/ static bool isTurnoutTypeXover(LayoutTurnout::TurnoutType type);
  /*public*/ bool isTurnoutTypeXover();
  /*public*/ static bool isTurnoutTypeSlip(LayoutTurnout::TurnoutType type);
  /*public*/ bool isTurnoutTypeSlip();
  /*public*/ static bool hasEnteringSingleTrack(LayoutTurnout::TurnoutType type);
  /*public*/ bool hasEnteringSingleTrack();
  /*public*/ static bool hasEnteringDoubleTrack(LayoutTurnout::TurnoutType type);

  /*public*/ void checkForNonContiguousBlocks(/*@Nonnull*/ QMap<QString, QList<QSet<QString> *> *> blockNamesToTrackNameSetsMap);
  /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
                  /*@Nonnull*/ QSet<QString>* trackNameSet)override;
  /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock)override;
  /*public*/ bool isMainlineA();
  /*public*/ bool isMainlineB();
  /*public*/ bool isMainlineC() ;
  /*public*/ bool isMainlineD();
  /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles, bool requireUnconnected) override;
  /*public*/ void setCoordsCenter(/*@Nonnull*/ QPointF p)override;
  void reCalculateCenter();
  virtual /*public*/ void setCoordsA(QPointF p);
  virtual /*public*/ void setCoordsB(QPointF p);
  virtual /*public*/ void setCoordsC(QPointF p);
  virtual /*public*/ void setCoordsD(QPointF p);
  /*public*/ void scaleCoords(double xFactor, double yFactor) override;
  /*public*/ void translateCoords(double xFactor, double yFactor) override;
  /*public*/ void rotateCoords(double angleDEG) override;
  /*public*/ double getRotationDEG();
  /*public*/ void toggleTurnout();
  /*public*/ void setState(int state);
  /*public*/ int getState();
  // initialization instance variables (used when loading a LayoutEditor)
  /*public*/ QString connectAName = "";
  /*public*/ QString connectBName = "";
  /*public*/ QString connectCName = "";
  /*public*/ QString connectDName = "";

  /*public*/ QString tBlockAName = "";
  /*public*/ QString tBlockBName = "";
  /*public*/ QString tBlockCName = "";
  /*public*/ QString tBlockDName = "";

  /*@Nonnull*/
  /*protected*/ QMenu* showPopup(/*@CheckForNull*/ QGraphicsSceneMouseEvent* mouseEvent) override;
  virtual /*public*/ QList<QString> getBlockBoundaries();
  /*public*/ QList<LayoutBlock*> getProtectedBlocks(NamedBean* bean);
  virtual /*public*/ void dispose();
  virtual /*public*/ void remove();
  /*public*/ bool isActive();
  /*public*/ void addEditPopUpMenu(QAction* menu);
  /*public*/ void addViewPopUpMenu(QAction* menu);
  /*public*/ void setAdditionalEditPopUpMenu(QMenu* popup);
  /*public*/ void setAdditionalViewPopUpMenu(QMenu* popup);
  /*public*/ void reCheckBlockBoundary() override;
  /*public*/ /*@Nonnull*/
  QList<HitPointType::TYPES> checkForFreeConnections()override;
  /*public*/ bool checkForUnAssignedBlocks() override;
  /*public*/ bool hasEnteringDoubleTrack();
  /*public*/ QString linkedTurnoutName = ""; // name of the linked Turnout (as entered in tool)
  /*public*/ LayoutTurnout::LinkType linkType = LayoutTurnout::LinkType::NO_LINK;
  /*public*/ /*final*/ LayoutTurnout* getLayoutTurnout();
  /*public*/ QString toString();
  /*public*/ int getVersion();
  /*public*/ void setVersion(int v) ;
  /*public*/ bool useBlockSpeed();
  /*public*/ QString getTurnoutName();
  /*public*/ QString getSecondTurnoutName();
  /*public*/ QString getBlockName();
  /*public*/ QString getBlockBName();
  /*public*/ QString getBlockCName();
  /*public*/ QString getBlockDName();
  /*public*/ SignalHead* getSignalHead(LayoutTurnout::Geometry loc);
  /*public*/ SignalHead* getSignalA1();
  /*public*/ QString getSignalA1Name();
  /*public*/ void setSignalA1Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalA2();
  /*public*/ QString getSignalA2Name();
  /*public*/ void setSignalA2Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalA3();
  /*public*/ QString getSignalA3Name();
  /*public*/ void setSignalA3Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalB1();
  /*public*/ QString getSignalB1Name();
  /*public*/ void setSignalB1Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalB2();
  /*public*/ QString getSignalB2Name();
  /*public*/ void setSignalB2Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalC1();
  /*public*/ QString getSignalC1Name();
  /*public*/ void setSignalC1Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalC2();
  /*public*/ QString getSignalC2Name();
  /*public*/ void setSignalC2Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalD1();
  /*public*/ QString getSignalD1Name();
  /*public*/ void setSignalD1Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ SignalHead* getSignalD2();
  /*public*/ QString getSignalD2Name();
  /*public*/ void setSignalD2Name(/*@CheckForNull*/ QString signalHead);
  /*public*/ void removeBeanReference(/*@CheckForNull*/ NamedBean* nb);
  /*public*/ bool canRemove() override;
  /*public*/ QList<QString> getBeanReferences(QString pointName);
  /*public*/ QString getSignalAMastName();
  /*public*/ SignalMast* getSignalAMast();
  /*public*/ void setSignalAMast(/*@CheckForNull*/ QString signalMast);
  /*public*/ QString getSignalBMastName();
  /*public*/ SignalMast* getSignalBMast();
  /*public*/ void setSignalBMast(/*@CheckForNull*/ QString signalMast);
  /*public*/ QString getSignalCMastName();
  /*public*/ SignalMast* getSignalCMast();
  /*public*/ void setSignalCMast(/*@CheckForNull*/ QString signalMast);
  /*public*/ QString getSignalDMastName();
  /*public*/ SignalMast* getSignalDMast();
  /*public*/ void setSignalDMast(/*@CheckForNull*/ QString signalMast);
  /*public*/ QString getSensorAName();
  /*public*/ Sensor* getSensorA();
  /*public*/ void setSensorA(/*@CheckForNull*/  QString sensorName);
  /*public*/ QString getSensorBName();
  /*public*/ Sensor* getSensorB();
  /*public*/ void setSensorB(/*@CheckForNull*/  QString sensorName);
  /*public*/ QString getSensorCName();
  /*public*/ Sensor* getSensorC();
  /*public*/ void setSensorC(/*@CheckForNull*/  QString sensorName) ;
  /*public*/ QString getSensorDName();
  /*public*/ Sensor* getSensorD();
  /*public*/ void setSensorD(/*@CheckForNull*/  QString sensorName) ;
  /*public*/ QString getLinkedTurnoutName();
  /*public*/ void setLinkedTurnoutName(/*@Nonnull*/ QString s);
  /*public*/ LayoutTurnout::LinkType getLinkType();
  /*public*/ void setLinkType(LayoutTurnout::LinkType ltype);
  /*public*/ LayoutTurnout::TurnoutType getTurnoutType();
  /*public*/ LayoutTrack* getConnectA();
  /*public*/ LayoutTrack* getConnectB();
  /*public*/ LayoutTrack* getConnectC();
  /*public*/ LayoutTrack* getConnectD();
  /*public*/ Turnout* getTurnout();
  /*public*/ int getContinuingSense();
  /*public*/ bool isInContinuingSenseState();
  /*public*/ void setTurnout(/*@Nonnull*/ QString tName);
  /*public*/ Turnout* getSecondTurnout();
  /*public*/ void setSecondTurnout(/*@Nonnull*/ QString tName);
  /*public*/ void setSecondTurnoutInverted(bool inverted);
  /*public*/ void setContinuingSense(int sense);
  /*public*/ void setDisabled(bool state);
  /*public*/ bool isDisabled();
  /*public*/ void setDisableWhenOccupied(bool state);
  /*public*/ bool isDisabledWhenOccupied();
  /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) throw (JmriException) override;
  /*public*/ void setConnection(HitPointType::TYPES connectionType, /*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) throw (JmriException) override;
  /*public*/ void setConnectA(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ void setConnectB(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ void setConnectC(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ void setConnectD(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ LayoutBlock* getLayoutBlock() ;
  /*public*/ LayoutBlock* getLayoutBlockB();
  /*public*/ LayoutBlock* getLayoutBlockC();
  /*public*/ LayoutBlock* getLayoutBlockD();
  virtual /*public*/ QPointF getCoordsA();
  virtual /*public*/ QPointF getCoordsB();
  virtual /*public*/ QPointF getCoordsC();
  virtual /*public*/ QPointF getCoordsD();
  /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType)override;
  /*public*/ QRectF getBounds() override;
  // updates connectivity for blocks assigned to this turnout and connected track segments
  virtual /*public*/ void updateBlockInfo();
  /*public*/ void setLayoutBlock(LayoutBlock* newLayoutBlock);
  /*public*/ void setLayoutBlockB(LayoutBlock* newLayoutBlock);
  /*public*/ void setLayoutBlockC(LayoutBlock* newLayoutBlock);
  /*public*/ void setLayoutBlockD(LayoutBlock* newLayoutBlock);
  /*public*/ void setLayoutBlockByName(/*@Nonnull*/ QString name);
  /*public*/ void setLayoutBlockBByName(/*@Nonnull*/ QString name);
  /*public*/ void setLayoutBlockCByName(/*@Nonnull*/ QString name);
  /*public*/ void setLayoutBlockDByName(/*@Nonnull*/ QString name);
  /*public*/ int continuingSense = Turnout::CLOSED;
  /*public*/ bool disabled = false;
  /*public*/ bool disableWhenOccupied = false;

 private:
  static Logger* log;
  void common(/*@Nonnull*/ LayoutTurnout* turnout,
          /*@Nonnull*/ QPointF c, double rot,
          double xFactor, double yFactor,
          /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*private*/ int version = 1;
  /*private*/ /*final*/ bool _useBlockSpeed = false;
  /*final*/ /*private*/ LayoutTurnout* turnout;
  void setTrackSegmentBlocks();
  void setTrackSegmentBlock(HitPointType::TYPES pointType, bool isAutomatic);
  QList<QAction*> editAdditionalMenu = QList<QAction*>();
  QList<QAction*> viewAdditionalMenu = QList<QAction*>();
  /*private*/ QMenu* popup = nullptr;
  /*private*/ bool isOccupied();
  QGraphicsItemGroup* itemGroup = nullptr;
  QGraphicsItemGroup* item = nullptr;
  QGraphicsItemGroup* circles = nullptr;
  QGraphicsItemGroup* rects = nullptr;
  QGraphicsEllipseItem* circle;

 protected:
  // operational instance variables (not saved between sessions)
  /*protected*/ NamedBeanHandle<Turnout*>* namedTurnout = nullptr;
  // Second turnout is used to either throw a second turnout in a cross over or if one turnout address is used to throw two physical ones
  /*protected*/ NamedBeanHandle<Turnout*>* secondNamedTurnout= nullptr;

  // default is package /*protected*/
  /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockA= nullptr;
  /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockB= nullptr;  // Xover - second block, if there is one
  /*protected*/ NamedBeanHandle<LayoutBlock*>* namedLayoutBlockC= nullptr;  // Xover - third block, if there is one
  /*protected*/ NamedBeanHandle<LayoutBlock>* namedLayoutBlockD= nullptr;  // Xover - forth block, if there is one

  /*protected*/ NamedBeanHandle<SignalHead*>* signalA1HeadNamed= nullptr; // signal 1 (continuing) (throat for RH, LH, WYE)
  /*protected*/ NamedBeanHandle<SignalHead*>* signalA2HeadNamed= nullptr; // signal 2 (diverging) (throat for RH, LH, WYE)
  /*protected*/ NamedBeanHandle<SignalHead*>* signalA3HeadNamed= nullptr; // signal 3 (second diverging) (3-way turnouts only)
  /*protected*/ NamedBeanHandle<SignalHead*>* signalB1HeadNamed= nullptr; // continuing (RH, LH, WYE) signal 1 (double crossover)
  /*protected*/ NamedBeanHandle<SignalHead*>* signalB2HeadNamed= nullptr; // LH_Xover and double crossover only
  /*protected*/ NamedBeanHandle<SignalHead*>* signalC1HeadNamed= nullptr; // diverging (RH, LH, WYE) signal 1 (double crossover)
  /*protected*/ NamedBeanHandle<SignalHead*>* signalC2HeadNamed= nullptr; // RH_Xover and double crossover only
  /*protected*/ NamedBeanHandle<SignalHead*>* signalD1HeadNamed= nullptr; // single or double crossover only
  /*protected*/ NamedBeanHandle<SignalHead*>* signalD2HeadNamed= nullptr; // LH_Xover and double crossover only

  // temporary reference to the Editor that will eventually be part of View
  /*protected*/ LayoutTurnoutEditor* editor;
  /*protected*/ void setUpDefaultSize();
  /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;
  virtual /*protected*/ int getConnectivityStateForLayoutBlocks(
          LayoutBlock* currLayoutBlock,
          LayoutBlock* prevLayoutBlock,
          LayoutBlock* nextLayoutBlock,
          bool suppress);
  /*protected*/ void drawDecorations(EditScene* g2) override;
  /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock) override;
  /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement) override;
  /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) override;
  /*protected*/ void drawTurnoutControls(EditScene* g2) override;
  /*protected*/ void drawEditControls(EditScene* g2) override;
  /*protected*/ void removeSML(SignalMast* signalMast);

 friend class LayoutEditor;
 friend class LayoutSlipView;
 friend class LayoutEditorComponent;
};

/*private*/ /*static*/ class AbstractActionImpl : public AbstractAction {
Q_OBJECT
    /*private*/ /*final*/ QString blockName;
    /*private*/ /*final*/ LayoutBlock* layoutBlock;
public:
    /*public*/ AbstractActionImpl(QString name, QString blockName, LayoutBlock* layoutBlock, QObject* parent) : AbstractAction(name, parent) {
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

#endif // LAYOUTTURNOUTVIEW_H
