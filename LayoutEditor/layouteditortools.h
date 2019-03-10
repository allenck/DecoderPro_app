#ifndef LAYOUTEDITORTOOLS_H
#define LAYOUTEDITORTOOLS_H

#include <QObject>
#include "layouteditor.h"
//#include "multiiconeditor.h"
#include "signalhead.h"
#include "layoutturnout.h"
#include "actionevent.h"
#include <QRadioButton>
#include "liblayouteditor_global.h"
#include "jmribeancombobox.h"

class LevelXing;
class LayoutSlip;
class QGroupBox;
class LayoutEditor;
class PositionablePoint;
class TrackSegment;
class MultiIconEditor;
class JmriJFrame;
class JTextField;
class SignalMast;
class NamedIcon;
class BlockBossLogic;
class BeanDetails;
class JmriBeanComboBox;
class PositionableIcon;
class SignallingGuiTools;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditorTools : public QObject
{
    Q_OBJECT
public:
 //explicit LayoutEditorTools(QObject *parent = 0);
 // constructor method
 /*public*/ LayoutEditorTools(LayoutEditor* thePanel, QObject *parent = 0);
// display dialog for Set Signals at Turnout* tool
/*public*/ void setSignalsAtTurnoutFromMenu( LayoutTurnout* to,
                MultiIconEditor* theEditor, JFrame* theFrame ) ;
/*public*/ void setSignalsAtTurnout( MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ bool reachedEndBumper();
    /*public*/ static bool isAtWestEndOfAnchor(TrackSegment* t, PositionablePoint* p);
    /*public*/ void setSignalsAtBlockBoundaryFromMenu( PositionablePoint* p, MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void setSignalsAtBlockBoundary( MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void removeSignalHeadFromPanel(QString signalName);
    /*public*/ void removeAssignment(SignalMast* mast);
    /*public*/ void removeAssignment(SignalHead* head);
    /*public*/ SignalHead* getSignalHeadFromEntry(JTextField* signalName,bool requireEntry, JFrame* frame);
    /*public*/ bool isHeadOnPanel(SignalHead* head);
    /*public*/ SignalHead* getHeadFromName(QString str);
    /*public*/ void setSignalHeadOnPanel(int rotation, QString headName,int xLoc, int yLoc);
    /*public*/ SignalHead* getNextSignalFromObject(TrackSegment* track, QObject* object,
QString headName, JmriJFrame* frame);
    /*public*/ void finalizeBlockBossLogic();
    /*public*/ bool initializeBlockBossLogic(QString signalHeadName);
    /*public*/ bool isHeadAssignedAnywhere(SignalHead* head);
    /*public*/ void setSignalMastsAtTurnoutFromMenu(LayoutTurnout* to, QStringList blocks);
    /*public*/ void setSensorsAtTurnoutFromMenu(LayoutTurnout* to, QStringList blocks, MultiIconEditor* theEditor, JFrame* frame);
    /*public*/ void setSignalsAtXoverTurnoutFromMenu( LayoutTurnout* to, MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void setSensorsAtTurnouts(JFrame* frame);
    /*public*/ void setSignalsAtXoverTurnout( MultiIconEditor* theEditor, JFrame* theFrame );
    ///*public*/ bool removeAssignment(Sensor* sensor);
    /*public*/ void setSignalMastsAtTurnouts();
    /*public*/ bool isSensorAssignedAnywhere(Sensor* sensor);
    /*public*/ bool removeSensorAssignment(Sensor* sensor);
    /*public*/ bool removeSensorFromPanel(Sensor *sensor);
    /*public*/ Sensor* getSensorFromEntry(QString sensorName, bool requireEntry,
                                          JmriJFrame* frame);
    /*public*/ Sensor* getSensorFromName(QString str);
    /*public*/ SensorIcon* getSensorIcon(QString sensorName);
    /*public*/ bool isSensorOnPanel(Sensor* sensor);
    /*public*/ bool isSignalMastOnPanel(SignalMast* signalMast);
    /*public*/ SignalMast* getSignalMastFromEntry(QString signalMastName,bool requireEntry,
                    JmriJFrame* frame);
    /*public*/ SignalMast* getSignalMastFromName(QString str) ;
    /*public*/ bool isSignalMastAssignedAnywhere(SignalMast* signalMast);
    /*public*/ void removeSignalMastAssignment(SignalMast* signalMast);
    /*public*/ void removeSignalMastFromPanel(QString signalMastName) ;
    /*public*/ void updateBoundaryBasedSignalMastLogic(SignalMast* oldBlock1SignalMast, SignalMast* oldBlock2SignalMast,
                                                        SignalMast* block1BoundSignalMast,SignalMast* block2BoundSignalMast);
    /*public*/ void setIconOnPanel(PositionableIcon* l, int rotation,
                    QPoint p) ;
    /*public*/ void setIconOnPanel(PositionableIcon* l, int rotation,
                    int xLoc, int yLoc);
    void windowClosing(QCloseEvent* e);
    /*public*/ void setThroatToThroatFromMenu( LayoutTurnout* to, QString linkedTurnoutName, MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void setSignalsAtTToTTurnouts( MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ LayoutTurnout* getLayoutTurnoutFromTurnout(Turnout* turnout, bool requireDoubleXover, QString str, JFrame* theFrame);
    /*public*/ void setSensorsAtBlockBoundaryFromMenu( PositionablePoint* p, MultiIconEditor* theEditor, JFrame* theFrame);
    /*public*/ void setSensorsAtBlockBoundary( MultiIconEditor* theEditor, JFrame* theFrame);
    /*public*/ void setSignalMastsAtBlockBoundaryFromMenu(PositionablePoint* p);
    /*public*/ void setSignalMastsAtBlockBoundary();
    /*public*/ void setSensorsAtSlipFromMenu (LayoutSlip* slip, QVector<QString> blocks, MultiIconEditor* theEditor,
            JFrame* theFrame );
    /*public*/ void setSensorsAtSlip(MultiIconEditor* theEditor, JFrame* theFrame);
    /*public*/ void setSlipFromMenu( LayoutSlip* ls,
            MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void setSignalsAtSlip( MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ SignalHeadIcon* getSignalHeadIcon(QString signalName);
    /*public*/ void setSignalsAtLevelXingFromMenu (LevelXing* xing, MultiIconEditor* theEditor,JFrame* theFrame );
    /*public*/ void setSignalsAtLevelXing( MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void setSignalMastsAtSlipFromMenu (LayoutSlip* slip, QVector<QString> blocks, JFrame* theFrame );
    /*public*/ void setSignalMastsAtLayoutSlip(JFrame* theFrame);
    /*public*/ void setSignalMastsAtLevelXingFromMenu (LevelXing* xing, QVector<QString>* blocks, JFrame* theFrame );
    /*public*/ void setSignalMastsAtLevelXing(JFrame* theFrame);
    /*public*/ void setSensorsAtLevelXingFromMenu (LevelXing* xing, QVector<QString>* blocks, MultiIconEditor* theEditor,JFrame* theFrame);
    /*public*/ void setSensorsAtLevelXing(MultiIconEditor* theEditor, JFrame* theFrame);
    /*public*/ void set3WayFromMenu(QString aName, QString bName,
                    MultiIconEditor* theEditor, JFrame* theFrame );
    /*public*/ void setSignalsAt3WayTurnout( MultiIconEditor* theEditor, JFrame* theFrame );


signals:
    
public slots:
    void block1NameField_textChanged(QString);
    void block2NameField_textChanged(QString);
    void eastBoundField_textChanged(QString);
    void westBoundField_textChanged(QString);
    /*private*/ void getSavedAnchorSignals (ActionEvent* /*a*/ = 0);
    void turnoutNameField_textChanged(QString);
    void throatContinuingField_textChanged(QString);
    void throatDivergingField_textChanged(QString);
    void continuingField_textChanged(QString);
    void divergingField_textChanged(QString);
    void on_changeTToTSignalIcon_triggered();
    void On_changeSensorAtBoundaryIcon_clicked();
    void on_slipNameComboCurrentIndexChanged(QString);

private:
    // constants
    /*private*/ int NONE; //0;  // Signal at Turnout* Positions
    /*private*/ int A1; //1;
    /*private*/ int A2; //2;
    /*private*/ int A3; //3;
    /*private*/ int B1; //4;
    /*private*/ int B2; //5;
    /*private*/ int C1; //6;
    /*private*/ int C2; //7;
    /*private*/ int D1; //8;
    /*private*/ int D2; //9;

    /*private*/ MultiIconEditor* sensorIconEditor;// = NULL;


    // operational instance variables shared between tools
    /*private*/ LayoutEditor* layoutEditor; //NULL;
    /*private*/ MultiIconEditor* signalIconEditor; //NULL;
    /*private*/ JFrame* signalFrame; //NULL;
    /*private*/ bool needRedraw; //false;
    /*private*/ BlockBossLogic* logic; //NULL;
    /*private*/ SignalHead* auxSignal; //NULL;

    // operational variables for Set Signals at Turnout* tool
    /*private*/ JmriJFrame* setSignalsAtTurnoutFrame = nullptr;
    /*private*/ bool setSignalsAtTurnoutOpenFlag = false;
    /*private*/ bool setSignalsAtTurnoutFromMenuFlag = false;
    /*private*/ /*final*/ JmriBeanComboBox* turnoutComboBox;// = new JmriBeanComboBox(
//            InstanceManager::turnoutManagerInstance(),
//            nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ JmriBeanComboBox* signalMastsTurnoutComboBox;// = new JmriBeanComboBox(
//                InstanceManager.turnoutManagerInstance(), null,
//                JmriBeanComboBox.DisplayOptions.DISPLAYNAME);
    /*private*/ double placeSignalDirectionDEG = 0.0;
    /*private*/ JmriJFrame* setSignalsFrame;// = NULL;
    /*private*/ bool setSignalsOpen;// = false;
    /*private*/ JTextField* turnoutNameField ;//= new JTextField(16);
    /*private*/ JTextField* throatContinuingField;// = new JTextField(16);
    /*private*/ JTextField* throatDivergingField;// = new JTextField(16);
    /*private*/ JTextField* continuingField;// = new JTextField(16);
    /*private*/ JTextField* divergingField;// = new JTextField(16);
    /*private*/ QCheckBox* setThroatContinuing;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicThroatContinuing;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setThroatDiverging;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicThroatDiverging;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setContinuing;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicContinuing;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setDiverging;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicDiverging;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QPushButton* getSavedSignalHeads;// = NULL;
    /*private*/ QPushButton* changeSignalIcon;// = NULL;
    /*private*/ QPushButton* setSignalsDone;// = NULL;
    /*private*/ QPushButton* setSignalsCancel;// = NULL;
    /*private*/ LayoutTurnout* layoutTurnout;// = NULL;
    /*private*/ bool layoutTurnoutHorizontal;// = false;
    /*private*/ bool layoutTurnoutVertical;// = false;
    /*private*/ bool layoutTurnoutThroatLeft;// = false;
    /*private*/ bool layoutTurnoutThroatUp;// = false;
    /*private*/ bool layoutTurnoutBUp;// = false;
    /*private*/ bool layoutTurnoutBLeft;// = false;
    /*private*/ bool turnoutFromMenu;// = false;
    /*private*/ Turnout* turnout;// = NULL;
    /*private*/ SignalHead* throatContinuingHead;// = NULL;
    /*private*/ SignalHead* throatDivergingHead;// = NULL;
    /*private*/ SignalHead* continuingHead;// = NULL;
    /*private*/ SignalHead* divergingHead;// = NULL;

    // operational variables for Set Signals at Block Boundary tool
    /*private*/ JmriJFrame* setSignalsAtBoundaryFrame;// = NULL;
    /*private*/ bool setSignalsAtBoundaryOpen;// = false;
    /*private*/ JTextField* block1NameField;// = new JTextField(16);
    /*private*/ JTextField* block2NameField;// = new JTextField(16);
    /*private*/ JTextField* eastBoundField;// = new JTextField(16);
    /*private*/ JTextField* westBoundField;// = new JTextField(16);
    /*private*/ QCheckBox* setEastBound;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicEastBound;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setWestBound;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicWestBound;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QPushButton* getAnchorSavedSignalHeads;// = NULL;
    /*private*/ QPushButton* changeSignalAtBoundaryIcon;// = NULL;
    /*private*/ QPushButton* setSignalsAtBoundaryDone;// = NULL;
    /*private*/ QPushButton* setSignalsAtBoundaryCancel;// = NULL;
    /*private*/ LayoutBlock* block1;// = NULL;
    /*private*/ LayoutBlock* block2;// = NULL;
    /*private*/ TrackSegment* eastTrack;// = NULL;
    /*private*/ TrackSegment* westTrack;// = NULL;
    /*private*/ bool trackHorizontal;// = false;
    /*private*/ bool trackVertical;// = false;
    /*private*/ bool boundaryFromMenu;// = false;
    /*private*/ PositionablePoint* boundary;// = NULL;
    /*private*/ SignalHead* eastBoundHead;// = NULL;
    /*private*/ SignalHead* westBoundHead;// = NULL;
    /*private*/ NamedIcon* testIcon;// = NULL;

    // operational variables for Set Signals at Double Crossover Turnout* tool
    /*private*/ JmriJFrame* setSignalsAtXoverFrame;// = NULL;
    /*private*/ bool setSignalsAtXoverOpen;// = false;
    ///*private*/ JTextField* xoverTurnoutNameField = new JTextField(16);
    /*private*/ JTextField* a1Field;// = new JTextField(16);
    /*private*/ JTextField* a2Field;// = new JTextField(16);
    /*private*/ JTextField* b1Field;// = new JTextField(16);
    /*private*/ JTextField* b2Field;// = new JTextField(16);
    /*private*/ JTextField* c1Field;// = new JTextField(16);
    /*private*/ JTextField* c2Field;// = new JTextField(16);
    /*private*/ JTextField* d1Field;// = new JTextField(16);
    /*private*/ JTextField* d2Field;// = new JTextField(16);
    /*private*/ QCheckBox* setA1Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupA1Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setA2Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupA2Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setB1Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupB1Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setB2Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupB2Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setC1Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupC1Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setC2Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupC2Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setD1Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupD1Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setD2Head;// = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupD2Logic;// = new QCheckBox(tr("Set up Logic"));
    /*private*/ QPushButton* getSavedXoverSignalHeads;// = NULL;
    /*private*/ QPushButton* changeXoverSignalIcon;// = NULL;
    /*private*/ QPushButton* setXoverSignalsDone;// = NULL;
    /*private*/ QPushButton* setXoverSignalsCancel;// = NULL;
    /*private*/ bool xoverFromMenu;// = false;
    /*private*/ SignalHead* a1Head;// = NULL;
    /*private*/ SignalHead* a2Head;// = NULL;
    /*private*/ SignalHead* b1Head;// = NULL;
    /*private*/ SignalHead* b2Head;// = NULL;
    /*private*/ SignalHead* c1Head;// = NULL;
    /*private*/ SignalHead* c2Head;// = NULL;
    /*private*/ SignalHead* d1Head;// = NULL;
    /*private*/ SignalHead* d2Head;// = NULL;
    /*private*/ int xoverType;// = LayoutTurnout.DOUBLE_XOVER;  // changes to RH_XOVER or LH_XOVER as required
    /*private*/ QString xoverTurnoutName;// = "";
    /*private*/ QLabel* xoverTurnoutNameLabel;// = new QLabel("");

    bool setSignalMastsOpen;// =false;
    bool turnoutMastFromMenu;// = false;
    /*private*/ JmriJFrame* signalMastsJmriFrame;// = NULL;

    /*private*/ JTextField* turnoutMastNameField;// = new JTextField(16);
    /*private*/ QPushButton* setSignalMastsDone;
    /*private*/ QPushButton* getSavedSignalMasts;
    /*private*/ QPushButton* setSignalMastsCancel;

    BeanDetails* turnoutSignalMastA;
    BeanDetails* turnoutSignalMastB;
    BeanDetails* turnoutSignalMastC;
    BeanDetails* turnoutSignalMastD;

    QWidget* signalMastTurnoutPanel;// = new QWidget();
    /*private*/ QVector<QString> turnoutBlocks;// = new QVector<QString>(4);
    QList<NamedBean*> usedMasts;// = new QList<NamedBean*>();

    bool setSensorsOpen;// =false;
    bool turnoutSensorFromMenu;// = false;
    /*private*/ JmriJFrame* setSensorsFrame;// = NULL;
    /*private*/ JFrame* turnoutSensorFrame;// = NULL;
    QLabel* turnoutSensorNameLabel;

    /*private*/ JmriBeanComboBox* sensorsTurnoutComboBox;// = new JmriBeanComboBox(
//    InstanceManager.turnoutManagerInstance(),
//    null, JmriBeanComboBox.DisplayOptions.DISPLAYNAME);

    /*private*/ QPushButton* setSensorsDone;
    /*private*/ QPushButton* getSavedSensors;
    /*private*/ QPushButton* setSensorsCancel;
    /*private*/ QPushButton* changeSensorIcon;// = NULL;

    /*private*/ QVector<QString> turnoutSenBlocks;// = QVector<QString>(4);

    BeanDetails* turnoutSensorA;
    BeanDetails* turnoutSensorB;
    BeanDetails* turnoutSensorC;
    BeanDetails* turnoutSensorD;

    QWidget*sensorTurnoutPanel;// = new QWidget();

    //This section deals with assigning a sensor to a specific boundary point

    BeanDetails* westBoundSensor;
    BeanDetails* eastBoundSensor;

    /*private*/ QPushButton* getAnchorSavedSensors;// = NULL;
    /*private*/ QPushButton* changeSensorAtBoundaryIcon;// = NULL;
    /*private*/ QPushButton* setSensorsAtBoundaryDone;// = NULL;
    void setBoundarySensor(Sensor* newSensor, Sensor* currSensor, BeanDetails* beanDetail, QString direction);
    /*private*/ QPushButton* setSensorsAtBoundaryCancel;// = NULL;
    /*private*/ bool setSensorsAtBoundaryOpen;// = false;
    /*private*/ JmriJFrame* setSensorsAtBoundaryFrame;// = NULL;
    /*private*/ bool setSensorsAtBlockBoundaryOpenFlag = false;
    /*private*/ bool setSensorsAtBlockBoundaryFromMenuFlag = false;

    /*private*/ JFrame* sensorFrame;// = NULL;

    /*private*/ QPushButton* getAnchorSavedSignalMasts;// = NULL;
    /*private*/ QPushButton* setSignalMastsAtBoundaryDone;// = NULL;
    /*private*/ QPushButton* setSignalMastsAtBoundaryCancel;// = NULL;
    /*private*/ bool setSignalMastsAtBoundaryOpen;// = false;
    /*private*/ JmriJFrame* setSignalMastsAtBoundaryFrame;// = NULL;

    BeanDetails* eastSignalMast;
    BeanDetails* westSignalMast;

    double adjust;// = (5.0/90.0);
    int awayright;// = 5;
    /*final*/ int offSetFromPoint;// = 5;

    // operational variables for Set Sensors at Level Crossing tool
    /*private*/ JmriJFrame* sensorsAtSlipFrame;// = NULL;
    /*private*/ bool setSensorsAtSlipOpen;// = false;

    QPushButton* getSavedSlipSensors;// = NULL;
    QPushButton* setSlipSensorsDone;// = NULL;
    QPushButton* setSlipSensorsCancel;// = NULL;
    QPushButton* changeSensorSlipIcon;// = NULL;
    JFrame* sensorSlipFrame;// = NULL;

    /*private*/ bool slipSensorFromMenu;// = false;
    /*private*/ QVector<QString>* slipSensorBlocks;// = new String[4];

    BeanDetails* slipSensorA;
    BeanDetails* slipSensorB;
    BeanDetails* slipSensorC;
    BeanDetails* slipSensorD;

    QWidget*sensorSlipPanel;// = new QWidget();

    // operational variables for Set SignalMast at Level Crossing tool
    /*private*/ JmriJFrame* signalMastsAtXingFrame;// = null;
    /*private*/ bool setSignalMastsAtXingOpen;// = false;
    /*private*/ JTextField* blockANameMastField;// = new JTextField(16);
    /*private*/ JTextField* blockCNameMastField;// = new JTextField(16);

    /*private*/ QPushButton* getSavedXingSignalMasts;// = null;
    /*private*/ QPushButton*  setXingSignalMastsDone;// = null;
    /*private*/ QPushButton*  setXingSignalMastsCancel;// = null;

    /*private*/ bool xingMastFromMenu;// = false;
    /*private*/ QVector<QString>* xingBlocks;// = new String[4];

    BeanDetails* xingSignalMastA;
    BeanDetails* xingSignalMastB;
    BeanDetails* xingSignalMastC;
    BeanDetails* xingSignalMastD;

    QWidget* signalMastLevelXingPanel;// = new JPanel();

    //Border blackline = BorderFactory.createLineBorder(Color.black);
    // operational variables for Set Signals at Double Crossover Turnout tool
    /*private*/ JmriJFrame* setSignalsAtXoverTurnoutFrame = nullptr;
    /*private*/ JmriJFrame* setSensorsAtBlockBoundaryFrame = nullptr;
    /*private*/ bool setSignalsAtXoverTurnoutOpenFlag = false;
    /*private*/ bool setSignalsAtXoverTurnoutFromMenuFlag = false;

    static Logger* log;
    /*private*/ bool hitEndBumper;// = false;
     /*private*/ bool getBlockInformation();
    /*private*/ LayoutBlock* getBlockFromEntry(JTextField* blockNameField);
    /*private*/ void placeEastBound();
    /*private*/ void placeWestBound();
    /*private*/ void setLogicEastBound();
    /*private*/ void setLogicWestBound();
    /*private*/ int isHeadAssignedHere(SignalHead* head, LayoutTurnout* lTurnout);
    /*private*/ void warnOfSkippedTurnout(JmriJFrame* frame, QString turnoutName, QString headName);
    /*private*/ TrackSegment* getContinuingTrack(LayoutTurnout* to, int type);
    /*private*/ bool getTurnoutInformation(bool isCrossover);
    /*private*/ bool getTurnoutSignalHeadInformation();
    /*private*/ void placeThroatContinuing();
    /*private*/ void placeThroatDiverging();
    /*private*/ void placeContinuing(QString signalHeadName);
    /*private*/ void placeDiverging(QString signalHeadName);
    /*private*/ void setLogicThroatContinuing();
    /*private*/ void setLogicThroatDiverging();
    /*private*/ void setLogicContinuing();
    /*private*/ void setLogicDiverging();
    /*private*/ int isSensorAssignedHere(Sensor* sensor, LayoutTurnout* lTurnout);
    SensorIcon* turnoutSensorBlockIcon;
    void createListUsedSignalMasts();
    void refreshSignalMastAtTurnoutComboBox();
    /*private*/ int isMastAssignedHere(SignalMast* mast, LayoutTurnout* lTurnout);
    /*private*/ bool getTurnoutSensorInformation();
    bool sensorAssignedElseWhere(Sensor* sensor);
    /*private*/ bool getSimpleBlockInformation();
    /*private*/ void placeEastBoundIcon(PositionableIcon* icon, bool right, double fromPoint);
    /*private*/ void placeWestBoundIcon(PositionableIcon* icon, bool right, double fromPoint);
    /*private*/ void placingBlock(PositionableIcon* icon, bool right, double fromPoint);
    /*private*/ void placingBlockB(PositionableIcon* icon, bool right, double fromPoint);
    /*private*/ void placingBlockC(PositionableIcon* icon, bool right, double fromPoint);
    /*private*/ void placingBlockD(PositionableIcon* icon, bool right, double fromPoint);
    /*private*/ bool getTurnoutMastInformation();
    void setIconOnPanel(TrackSegment* t, PositionableIcon* l, bool eastbound, QPoint p, QPoint pt2, bool side, double fromPoint);
    QPoint southToNorth(QPoint p, PositionableIcon* l, bool right, double fromPoint);
    QPoint northToSouth(QPoint p, PositionableIcon* l, bool right, double fromPoint);
    QPoint westToEast(QPoint p, PositionableIcon* l, bool right, double fromPoint);
    QPoint eastToWest(QPoint p, PositionableIcon* l, bool right, double fromPoint);
    QPoint northEastToSouthWest(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angle, bool right, double fromPoint);
    QPoint southWestToNorthEast(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angle, bool right, double fromPoint);
    QPoint northWestToSouthEast(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angledeg, bool right, double fromPoint);
    QPoint southEastToNorthWest(QPoint p, PositionableIcon* l, int oldWidth, int oldHeight, double angleDeg, bool right, double fromPoint);
    void refreshSignalMastAtBoundaryComboBox();
    /*private*/ bool getXoverSignalHeadInformation();
    /*private*/ void placeA1();
    /*private*/ void placeA2() ;
    /*private*/ void placeB1();
    /*private*/ void placeB2();
    /*private*/ void placeC1();
    /*private*/ void placeC2() ;
    /*private*/ void placeD1() ;
    /*private*/ void placeD2();
    /*private*/ void setLogicXover(SignalHead* head,TrackSegment* track,SignalHead* secondHead,TrackSegment* track2,
                bool setup1, bool setup2);
    /*private*/ void setLogicXoverContinuing(SignalHead* head,TrackSegment* track);
    // operational variables for Set Signals at Double Crossover Turnout* tool
    /*private*/ JmriJFrame* setSignalsAtTToTFrame;// = NULL;
    /*private*/ bool setSignalsAtTToTOpen;// = false;
    /*private*/ JTextField* turnout1NameField;// = new JTextField(16);
    /*private*/ JTextField* turnout2NameField;// = new JTextField(16);
    ///*private*/ JTextField* ttNameField = new JTextField(16);
    /*private*/ JTextField* a1TToTField;// = new JTextField(16);
    /*private*/ JTextField* a2TToTField;// = new JTextField(16);
    /*private*/ JTextField* b1TToTField;// = new JTextField(16);
    /*private*/ JTextField* b2TToTField;// = new JTextField(16);
    /*private*/ JTextField* c1TToTField;// = new JTextField(16);
    /*private*/ JTextField* c2TToTField;// = new JTextField(16);
    /*private*/ JTextField* d1TToTField;// = new JTextField(16);
    /*private*/ JTextField* d2TToTField;// = new JTextField(16);
    /*private*/ QCheckBox*  setA1TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupA1TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setA2TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupA2TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setB1TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupB1TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setB2TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupB2TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setC1TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupC1TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setC2TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupC2TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setD1TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupD1TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QCheckBox*  setD2TToTHead;// = new JCheckBox(tr("PlaceHead"));
    /*private*/ QCheckBox*  setupD2TToTLogic;// = new JCheckBox(tr("SetLogic"));
    /*private*/ QPushButton* getSavedTToTSignalHeads;// = NULL;
    /*private*/ QPushButton* changeTToTSignalIcon;// = NULL;
    /*private*/ QPushButton* setTToTSignalsDone;// = NULL;
    /*private*/ QPushButton* setTToTSignalsCancel;// = NULL;
    /*private*/ LayoutTurnout* layoutTurnout1;// = NULL;
    /*private*/ LayoutTurnout* layoutTurnout2;// = NULL;
    /*private*/ Turnout* turnout1;// = NULL;
    /*private*/ Turnout* turnout2;// = NULL;
    /*private*/ TrackSegment* connectorTrack;// = NULL;
    SignalHead* a1TToTHead;// = NULL;
    SignalHead* a2TToTHead;// = NULL;
    SignalHead* b1TToTHead;// = NULL;
    SignalHead* b2TToTHead;// = NULL;
    SignalHead* c1TToTHead;// = NULL;
    SignalHead* c2TToTHead;// = NULL;
    SignalHead* d1TToTHead;// = NULL;
    SignalHead* d2TToTHead;// = NULL;
    /*private*/ bool	layoutTurnout1Horizontal;// = false;
    /*private*/ bool	layoutTurnout1Vertical;// = false;
    /*private*/ bool	layoutTurnout2Horizontal;// = false;
    /*private*/ bool	layoutTurnout2Vertical;// = false;
    /*private*/ bool	layoutTurnout1ThroatLeft;// = false;
    /*private*/ bool	layoutTurnout1ThroatUp;// = false;
    /*private*/ bool	layoutTurnout2ThroatLeft;// = false;
    /*private*/ bool	layoutTurnout2ThroatUp;// = false;
    /*private*/ bool	layoutTurnout1BUp;// = false;
    /*private*/ bool	layoutTurnout1BLeft;// = false;
    /*private*/ bool	layoutTurnout2BUp;// = false;
    /*private*/ bool	layoutTurnout2BLeft;// = false;
    /*private*/ bool getTToTTurnoutInformation();
    /*private*/ bool getTToTSignalHeadInformation();
    /*private*/ void placeA1TToT(QString headName);
    /*private*/ void placeA2TToT(QString headName);
    /*private*/ void placeB1TToT(QString headName);
    /*private*/ void placeB2TToT(QString headName);
    /*private*/ void placeC1TToT(QString headName);
    /*private*/ void placeC2TToT(QString headName);
    /*private*/ void placeD1TToT(QString headName);
    /*private*/ void placeD2TToT(QString headName);
    /*private*/ void setLogicTToT(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2,
                    bool setup1, bool setup2, bool continuing,
                        LayoutTurnout* farTurnout, LayoutTurnout* nearTurnout);
    /*private*/ QString setupNearLogix(LayoutTurnout* nearTurnout, bool continuing,
                                       SignalHead* head);
    /*private*/ void addNearSensorToLogic(QString name);
    void commonTField(QString txt, JTextField* f);

    // operational variables for Set Signals at Double Crossover Turnout tool
    /*private*/ JmriJFrame* setSignalsAtSlipFrame;// = null;
    /*private*/ bool setSignalsAtSlipOpen;// = false;
    /*private*/ QComboBox* slipNameCombo;// = new JComboBox<String>();
    /*private*/ JTextField* a1SlipField;// = new JTextField(16);
    /*private*/ JTextField* a2SlipField;// = new JTextField(16);
    /*private*/ JTextField* b1SlipField;// = new JTextField(16);
    /*private*/ JTextField* b2SlipField;// = new JTextField(16);
    /*private*/ JTextField* c1SlipField;// = new JTextField(16);
    /*private*/ JTextField* c2SlipField;// = new JTextField(16);
    /*private*/ JTextField* d1SlipField;// = new JTextField(16);
    /*private*/ JTextField* d2SlipField;// = new JTextField(16);
    /*private*/ QCheckBox* setA1SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupA1SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setA2SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupA2SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setB1SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupB1SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setB2SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupB2SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setC1SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupC1SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setC2SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupC2SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setD1SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupD1SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setD2SlipHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupD2SlipLogic;// = new JCheckBox(rb.getString("SetLogic"));

    /*private*/ QPushButton* setSlipSignalsDone;// = null;
    /*private*/ QPushButton* setSlipSignalsCancel;// = null;
    /*private*/ LayoutSlip* layoutSlip;// = null;

    /*private*/ SignalHead* a1SlipHead;// = null;
    /*private*/ SignalHead* a2SlipHead;// = null;
    /*private*/ SignalHead* b1SlipHead;// = null;
    /*private*/ SignalHead* b2SlipHead;// = null;
    /*private*/ SignalHead* c1SlipHead;// = null;
    /*private*/ SignalHead* c2SlipHead;// = null;
    /*private*/ SignalHead* d1SlipHead;// = null;
    /*private*/ SignalHead* d2SlipHead;// = null;

    /*private*/ QWidget* dblSlipC2SigPanel;
    /*private*/ QWidget* dblSlipB2SigPanel;
    /*private*/ bool slipSignalFromMenu;// = false;

    // operational variables for Set Signals at Level Crossing tool
    /*private*/ JmriJFrame* setSignalsAtXingFrame;// = null;
/*private*/ bool setSignalsAtXingOpen;// = false;
    /*private*/ JTextField* blockANameField;// = new JTextField(16);
    /*private*/ JTextField* blockCNameField;// = new JTextField(16);
    /*private*/ JTextField* aField;// = new JTextField(16);
    /*private*/ JTextField* bField;// = new JTextField(16);
    /*private*/ JTextField* cField;// = new JTextField(16);
    /*private*/ JTextField* dField;// = new JTextField(16);
    /*private*/ QCheckBox* setAHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupALogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setBHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupBLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setCHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupCLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QCheckBox* setDHead;// = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ QCheckBox* setupDLogic;// = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ QPushButton* getSavedXingSignalHeads;// = null;
    /*private*/ QPushButton* changeXingSignalIcon;// = null;
    /*private*/ QPushButton* setXingSignalsDone;// = null;
    /*private*/ QPushButton* setXingSignalsCancel;// = null;
    /*private*/ bool levelXingACHorizontal;// = false;
    /*private*/ bool levelXingACVertical;// = false;
    /*private*/ bool levelXingALeft;// = false;
    /*private*/ bool levelXingAUp;// = false;
    /*private*/ bool levelXingBUp;// = false;
    /*private*/ bool levelXingBLeft;// = false;
    /*private*/ bool xingFromMenu;// = false;
    /*private*/ LevelXing* levelXing;// = null;
    /*private*/ SignalHead* aHead;// = null;
    /*private*/ SignalHead* bHead;// = null;
    /*private*/ SignalHead* cHead;//= null;
    /*private*/ SignalHead* dHead;// = null;

    // operational variables for Set Sensors at Level Crossing tool
    /*private*/ JmriJFrame* sensorsAtXingFrame;// = NULL;
    /*private*/ bool setSensorsAtXingOpen;// = false;
    JTextField* blockANameSensorField;// = new JTextField(16);
    JTextField* blockCNameSensorField;// = new JTextField(16);

    QPushButton* getSavedXingSensors;// = NULL;
    QPushButton* setXingSensorsDone;// = NULL;
    QPushButton* setXingSensorsCancel;// = NULL;
    QPushButton* changeSensorXingIcon;// = NULL;
    JFrame* sensorXingFrame;// = NULL;

    /*private*/ bool xingSensorFromMenu;// = false;
    /*private*/ QVector<QString>* xingSensorBlocks;// = new String[4];

    BeanDetails* xingSensorA;
    BeanDetails* xingSensorB;
    BeanDetails* xingSensorC;
    BeanDetails* xingSensorD;

    QWidget*sensorXingPanel;// = new QWidget();
    /*private*/ bool getSlipSensorInformation();

    /*private*/ bool getSlipSignalHeadInformation();
    /*private*/ void placeA1Slip(QString headName);
    /*private*/ void placeA2Slip(QString headName);
    /*private*/ void placeB1Slip(QString headName);
    /*private*/ void placeB2Slip(QString headName);
    /*private*/ void placeC1Slip(QString headName);
    /*private*/ void placeC2Slip(QString headName) ;
    /*private*/ void placeD1Slip(QString headName);
    /*private*/ void placeD2Slip(QString headName);

    /*private*/ void setLogicSlip(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2, bool setup1, bool setup2,  LayoutSlip* slip, Turnout* nearTurnout, Turnout* farTurnout,int continueState, int divergeState, int number);
    /*private*/ bool getSlipTurnoutInformation();
    /*private*/ QString setupNearLogixSlip(Turnout* turn, int nearState, SignalHead* head, Turnout* farTurn, int farState, LayoutSlip* slip, int number);
    /*private*/ void addNearSensorToSlipLogic(QString name);

    // operational variables for Set SignalMast at Slip tool
 /*private*/ JmriJFrame* signalMastsAtSlipFrame;// = NULL;
 /*private*/ bool setSignalMastsAtSlipOpen;// = false;

  QPushButton* getSavedSlipSignalMasts;// = NULL;
  QPushButton* setSlipSignalMastsDone;// = NULL;
  QPushButton* setSlipSignalMastsCancel;// = NULL;

  /*private*/ bool slipMastFromMenu;// = false;
  /*private*/ QVector<QString>* slipBlocks;// = new String[4];

  BeanDetails* slipSignalMastA;
  BeanDetails* slipSignalMastB;
  BeanDetails* slipSignalMastC;
  BeanDetails* slipSignalMastD;


  QWidget*signalMastLayoutSlipPanel;// = new QWidget();
  /*private*/ bool getLevelCrossingInformation();
  /*private*/ bool getXingSignalHeadInformation();
  /*private*/ void placeXingA();
  /*private*/ void placeXingB();
  /*private*/ void placeXingC();
  /*private*/ void placeXingD();
  /*private*/ void setLogicXing(SignalHead* head, TrackSegment* track, LayoutBlock*crossBlock,TrackSegment* crossTrack1, TrackSegment* crossTrack2, QString headName);
  void refreshSignalMastAtSlipComboBox();
  /*private*/ bool getSlipMastInformation();
  QGridLayout* signalMastLayoutSlipPanelLayout;
  void refreshSignalMastAtXingComboBox();
  /*private*/ bool getLevelCrossingMastInformation();
  /*private*/ void placeXingAIcon(PositionableIcon* icon, bool right, double fromPoint);
  /*private*/ void placeXingBIcon(PositionableIcon* icon, bool right, double fromPoint);
  /*private*/ void placeXingCIcon(PositionableIcon* icon, bool right, double fromPoint);
  /*private*/ void placeXingDIcon(PositionableIcon* icon, bool right, double fromPoint);
  QGridLayout* signalMastLevelXingPanelLayout;
  /*private*/ bool getLevelCrossingSensorInformation();
  QGridLayout* sensorXingPanelLayout;
  QGridLayout* sensorSlipPanelLayout;
  QGridLayout* signalMastTurnoutPanelLayout;

  // operational variables for Set Signals at 3-Way Turnout tool
  /*private*/ JmriJFrame* setSignalsAt3WayFrame;// =NULL;
  /*private*/ bool setSignalsAt3WayOpen;// =false;
  JTextField* turnoutANameField;// =new JTextField(16);
  JTextField* turnoutBNameField;// =new JTextField(16);
  JTextField* a13WayField;// =new JTextField(16);
  JTextField* a23WayField;// =new JTextField(16);
  JTextField* a33WayField;// =new JTextField(16);
  JTextField* b3WayField;// =new JTextField(16);
  JTextField* c3WayField;// =new JTextField(16);
  JTextField* d3WayField;// =new JTextField(16);
  QCheckBox* setA13WayHead;// =new QCheckBox(tr("Add Signal Head Icon to Panel"));
  QCheckBox* setupA13WayLogic;// =new QCheckBox(tr("Set up Logic"));
  QCheckBox* setA23WayHead;// =new QCheckBox(tr("Add Signal Head Icon to Panel"));
  QCheckBox* setupA23WayLogic;// =new QCheckBox(tr("Set up Logic"));
  QCheckBox* setA33WayHead;// =new QCheckBox(tr("Add Signal Head Icon to Panel"));
  QCheckBox* setupA33WayLogic;// =new QCheckBox(tr("Set up Logic"));
  QCheckBox* setB3WayHead;// =new QCheckBox(tr("Add Signal Head Icon to Panel"));
  QCheckBox* setupB3WayLogic;// =new QCheckBox(tr("Set up Logic"));
  QCheckBox* setC3WayHead;// =new QCheckBox(tr("Add Signal Head Icon to Panel"));
  QCheckBox* setupC3WayLogic;// =new QCheckBox(tr("Set up Logic"));
  QCheckBox* setD3WayHead;// =new QCheckBox(tr("Add Signal Head Icon to Panel"));
  QCheckBox* setupD3WayLogic;// =new QCheckBox(tr("Set up Logic"));
  QPushButton* getSaved3WaySignalHeads;// =NULL;
  QPushButton* change3WaySignalIcon;// =NULL;
  QPushButton* set3WaySignalsDone;// =NULL;
  QPushButton* set3WaySignalsCancel;// =NULL;
  /*private*/ LayoutTurnout* layoutTurnoutA;// =NULL;
  /*private*/ LayoutTurnout* layoutTurnoutB;// =NULL;
  /*private*/ Turnout* turnoutA;// =NULL;
  /*private*/ Turnout* turnoutB;// =NULL;
  ///*private*/ TrackSegment* conTrack = NULL;
  SignalHead* a13WayHead;// =NULL;   // saved in A1 of Turnout A - Throat - continuing
  SignalHead* a23WayHead;// =NULL;   // saved in A2 of Turnout A - Throat - diverging A (optional)
  SignalHead* a33WayHead;// =NULL;   // saved in A3 of Turnout A - Throat - diverging B (optional)
  SignalHead* b3WayHead;// =NULL;    // saved in C1 of Turnout A - at diverging A
  SignalHead* c3WayHead;// =NULL;    // saved in B1 of Turnout B - at continuing
  SignalHead* d3WayHead;// =NULL;    // saved in C1 of Turnout B - at diverging B
  bool layoutTurnoutAHorizontal;// =false;
  bool layoutTurnoutAVertical;// =false;
  bool layoutTurnoutBHorizontal;// =false;
  bool layoutTurnoutBVertical;// =false;
  bool layoutTurnoutAThroatLeft;// =false;
  bool layoutTurnoutAThroatUp;// =false;
  bool layoutTurnoutBThroatLeft;// =false;
  bool layoutTurnoutBThroatUp;// =false;
  bool layoutTurnoutABUp;// =false;
  bool layoutTurnoutABLeft;// =false;
  bool layoutTurnoutBBUp;// =false;
  bool layoutTurnoutBBLeft;// =false;
  /*private*/ bool get3WayTurnoutInformation();
  /*private*/ bool get3WaySignalHeadInformation();
  /*private*/ void place3WayThroatContinuing();
  /*private*/ void place3WayThroatDivergingA();
  /*private*/ void place3WayThroatDivergingB();
  /*private*/ void place3WayDivergingA();
  /*private*/ void place3WayContinuing();
  /*private*/ void place3WayDivergingB();
  /*private*/ void set3WayLogicThroatContinuing();
  /*private*/ void set3WayLogicThroatDivergingA() ;
  /*private*/ void set3WayLogicThroatDivergingB() ;
  /*private*/ void set3WayLogicDivergingA();
  /*private*/ void set3WayLogicContinuing();
  /*private*/ void set3WayLogicDivergingB();

 private slots:
    void changeSignalAtBoundaryIcon_clicked();
    /*private*/ void setSignalsAtBoundaryDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setSignalsAtBoundaryCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void turnoutSignalsGetSaved (ActionEvent* /*a*/ = 0);
    void on_changeSignalIcon_clicked();
    void setSignalsDonePressed(ActionEvent* /*a*/ = 0);
    /*private*/ void setSignalsCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setXoverSignalsCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void xoverTurnoutSignalsGetSaved (ActionEvent* /*a*/ = 0);
    void on_changeXoverSignalIcon_clicked();
    /*private*/ void setXoverSignalsDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void turnoutSensorsGetSaved (ActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void turnoutSignalMastsGetSaved (ActionEvent* /*a*/ = 0); // SLOT
    /*private*/ void getSavedAnchorSensors (ActionEvent* /*a*/ = 0);
    /*private*/ void setXingSensorsCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsAtBoundaryCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsAtBoundaryDonePressed (ActionEvent* a  = 0);
    /*private*/ void setSignalMastsCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setSignalMastsDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void getSavedAnchorSignalMasts (ActionEvent* /*a*/ = 0);
    /*private*/ void setSignalMastsAtBoundaryCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setSignalMastsAtBoundaryDonePressed (ActionEvent* /*a*/ = 0) ;
    /*private*/ void setXingSignalsCancelPressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setXingSignalsDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setXingSensorsDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void setTToTSignalsDonePressed (ActionEvent* /*a*/ = 0);
    /*private*/ void tToTTurnoutSignalsGetSaved (ActionEvent* /*a*/ = 0);
    /*private*/ void setTToTSignalsCancelPressed (ActionEvent* /*a*/ = 0);
    void on_a1TToTField_textEdited(QString);
    void on_a2TToTField_textEdited(QString);
    void on_b1TToTField_textEdited(QString);
    void on_b2TToTField_textEdited(QString);
    void on_c1TToTField_textEdited(QString);
    void on_c2TToTField_textEdited(QString);
    void on_d1TToTField_textEdited(QString);
    void on_d2TToTField_textEdited(QString);
    /*private*/ void slipSensorsGetSaved (ActionEvent* a = 0);
    /*private*/ void setSlipSensorsCancelPressed (ActionEvent* a = 0);
    /*private*/ void setSlipSensorsDonePressed (ActionEvent* a = 0);
    void on_changeSensorSlipIcon();
    /*private*/ void setSlipSignalsDonePressed (ActionEvent* a = 0);
    /*private*/ void getSlipTurnoutSignalsGetSaved (ActionEvent* a = 0);
    /*private*/ void setSlipSignalsCancelPressed (ActionEvent* a = 0);
    /*private*/ void xingSignalsGetSaved (ActionEvent* a = 0);
    /*private*/ void setSlipSignalMastsCancelPressed (ActionEvent* a = 0);
    /*private*/ void slipSignalMastsGetSaved (ActionEvent* a = 0);
    /*private*/ void setSlipSignalMastsDonePressed (ActionEvent* a = 0);
    /*private*/ void xingSignalMastsGetSaved (ActionEvent* a = 0);
    /*private*/ void setXingSignalMastsCancelPressed (ActionEvent*  = 0);
    /*private*/ void setXingSignalMastsDonePressed (ActionEvent* a = 0);
    /*private*/ void xingSensorsGetSaved (ActionEvent* a = 0);
    void on_changeSensorXingIcon();
    /*private*/ void getSaved3WaySignals (ActionEvent* a = 0);
    /*private*/ void set3WaySignalsCancelPressed (ActionEvent* a = 0);
    void On_change3WaySignalIconClicked();
    /*private*/ void set3WaySignalsDonePressed (ActionEvent* a = 0);

    friend class SSWindowListener;
    friend class SXWindowListener;
    friend class SMSWindowListener;
    friend class XSMSWindowListener;
    friend class XSSSWindowListener;
    friend class SASWindowListener;
    friend class SSFWindowListener;
    friend class S3WWindowListener;
};
/*static*/ class BeanDetails : public QObject
{
    QString beanString;
    QLabel* textLabel;

    QString boundaryLabelText;// = tr("BoundaryOf");
    QLabel* boundary;// = new QLabel(boundaryLabelText);

    Manager* manager;

    QGroupBox* detailsPanel;// = new QWidget();
    QRadioButton* addBeanCheck;// = new QRadioButton(tr("Do Not Place On Panel"));
    QRadioButton* left;// = new QRadioButton(tr("Left Hand Side"));
    QRadioButton* right;// = new QRadioButton(tr("Right Hand Side"));
    QButtonGroup* buttonGroup;// = new QButtonGroup();
    JmriBeanComboBox* beanCombo;

    QLabel* boundaryBlocks;// = new QLabel();
public:
    BeanDetails(QString beanType, Manager* manager);
    void setTextField(QString value);
    QString getText();
    NamedBean* getBean();
    QWidget*getDetailsPanel();
    bool addToPanel();
    bool isRightSelected();
    void setBoundaryTitle(QString text);
    void setBoundaryLabelText(QString text);
    void setBoundaryLabel(QString label);
    JmriBeanComboBox* getCombo();
    QWidget* positionLeftRight();
    QWidget* addIconPanel();

    //Border blackline = BorderFactory.createLineBorder(Color.black);
};
class SSWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 SSWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setSlipSignalsCancelPressed();
 }
};
class SXWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 SXWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setXingSignalsCancelPressed();
 }
};
class SMSWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 SMSWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setSlipSignalMastsCancelPressed();
 }
};
class XSMSWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 XSMSWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setXingSignalMastsCancelPressed();
 }
};

class XSSSWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 XSSSWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setXingSensorsCancelPressed();
 }
};
class SASWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 SASWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setSlipSensorsCancelPressed();
 }
};
class SSFWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 SSFWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setSignalsCancelPressed();
 }
};
class S3WWindowListener: public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 S3WWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->set3WaySignalsCancelPressed();
 }
};

#endif // LAYOUTEDITORTOOLS_H
