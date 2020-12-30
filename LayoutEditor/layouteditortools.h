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
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "namedbeancombobox.h"
#include <QCheckBox>
#include "borderfactory.h"
#include <QGroupBox>


class BeanDetails;
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
class NamedBeanComboBox;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutEditorTools : public QObject
{
    Q_OBJECT
public:
 //explicit LayoutEditorTools(QObject *parent = 0);
 // constructor method
 /*public*/ LayoutEditorTools(LayoutEditor* thePanel, QObject *parent = 0);
 /*public*/ void setSignalsAtThroatToThroatTurnoutsFromMenu(
            /*@Nonnull*/ LayoutTurnout* to, /*@Nonnull*/ QString linkedTurnoutName,
            /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame);
 /*public*/ void setSignalsAtThroatToThroatTurnouts(
         /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame);

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
    /*public*/ SignalHead* getSignalHeadFromEntry(
         /*@Nonnull*/ NamedBeanComboBox/*<SignalHead>*/* signalNameComboBox,
         bool requireEntry,
         /*@Nonnull*/ JmriJFrame* frame);
    /*public*/ SignalHead* getSignalHeadFromEntry(JTextField* signalName,bool requireEntry, JFrame* frame);
    /*public*/ SignalHead *getSignalHeadFromEntry(/*@CheckForNull*/ QString signalName,
         bool requireEntry, /*@Nonnull*/ JmriJFrame* frame);
    /*public*/ bool isHeadOnPanel(SignalHead* head);
    /*public*/ SignalHead* getHeadFromName(QString str);
    /*public*/ void setSignalHeadOnPanel(double directionDEG,
         /*@Nonnull*/ QString signalHeadName,
         /*@Nonnull*/ QPointF where);
    /*public*/ void setSignalHeadOnPanel(double directionDEG, /*@Nonnull */QString signalHeadName, int xLoc, int yLoc);
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
    /*public*/ void setSignalsAtSlipFromMenu(/*@Nonnull*/ LayoutSlip* ls,
                /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame);
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
    /*public*/ void setSignalsAt3WayTurnoutFromMenu(
                /*@Nonnull*/ QString aName, /*@Nonnull*/ QString bName,
                /*@Nonnull*/ MultiIconEditor* theEditor, /*@Nonnull*/ JFrame* theFrame);
    /*public*/ void setSignalsAt3WayTurnout(/*@Nonnull */MultiIconEditor* theEditor,
            /*@Nonnull*/ JFrame* theFrame);


signals:
    
public slots:
    /*private*/ void getSavedAnchorSignals (JActionEvent* /*a*/ = 0);

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
    JPanel* sensorBlockPanel = new JPanel(new FlowLayout());


    //operational variables for Set Signals at Double Crossover Turnout tool
        /*private*/ JmriJFrame* setSignalsAtThroatToThroatTurnoutsFrame = nullptr;
        /*private*/ bool setSignalsAtThroatToThroatTurnoutsOpenFlag = false;
        /*private*/ bool setSignalsAtThroatToThroatTurnoutsFromMenuFlag = false;

        /*private*/ JLabel* ttotTurnoutName1Label = nullptr;
        /*private*/ JLabel* ttotTurnoutName2Label = nullptr;

        /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* turnout1ComboBox = new NamedBeanComboBox(
       InstanceManager::turnoutManagerInstance(),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* turnout2ComboBox = new NamedBeanComboBox(
       InstanceManager::turnoutManagerInstance(),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a1TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a2TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b1TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b2TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c1TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c2TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d1TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
        /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d2TToTSignalHeadComboBox = new NamedBeanComboBox(
       (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ QCheckBox* setA1TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setA2TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setB1TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setB2TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setC1TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setC2TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setD1TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setD2TToTHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));

    /*private*/ /*final*/ QCheckBox* setupA1TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupA2TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupB1TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupB2TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupC1TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupC2TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupD1TToTLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupD2TToTLogic = new QCheckBox(tr("Set up SSL"));

    /*private*/ QPushButton* getSavedTToTSignalHeads = nullptr;
    /*private*/ QPushButton* changeTToTSignalIcon = nullptr;
    /*private*/ QPushButton* setTToTSignalsDone = nullptr;
    /*private*/ QPushButton* setTToTSignalsCancel = nullptr;

    /*private*/ LayoutTurnout* layoutTurnout1 = nullptr;
    /*private*/ LayoutTurnout* layoutTurnout2 = nullptr;

    /*private*/ Turnout* turnout1 = nullptr;
    /*private*/ Turnout* turnout2 = nullptr;

    /*private*/ TrackSegment* connectorTrack = nullptr;

    /*private*/ QString ttotTurnoutName1 = "";
    /*private*/ QString ttotTurnoutName2 = "";


    // operational instance variables shared between tools
    /*private*/ LayoutEditor* layoutEditor = nullptr;
    /*private*/ MultiIconEditor* signalIconEditor = nullptr;
    /*private*/ JFrame* signalFrame = nullptr;
    /*private*/ bool needRedraw = false;
    /*private*/ BlockBossLogic* logic = nullptr;
    /*private*/ SignalHead* auxSignal = nullptr;

    // operational variables for Set Signals at Turnout* tool
    /*private*/ JmriJFrame* setSignalsAtTurnoutFrame = nullptr;
    /*private*/ bool setSignalsAtTurnoutOpenFlag = false;
    /*private*/ bool setSignalsAtTurnoutFromMenuFlag = false;

    /*private*/ QLabel* xoverTurnoutNameLabel = new QLabel("");

    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* turnoutComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* throatContinuingSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* throatDivergingSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* continuingSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* divergingSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ QCheckBox* setPlaceAllHeads = new QCheckBox(tr("Place All Signal Head Icons"));
    /*private*/ /*final*/ QCheckBox* setupAllLogic = new QCheckBox(tr("Set up all SSL's"));

    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* signalMastsTurnoutComboBox = new NamedBeanComboBox(
               InstanceManager::turnoutManagerInstance(), nullptr,
               NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ double placeSignalDirectionDEG = 0.0;
    /*private*/ JmriJFrame* setSignalsFrame = nullptr;
    /*private*/ bool setSignalsOpen = false;
//    /*private*/ JTextField* turnoutNameField ;//= new JTextField(16);
//    /*private*/ JTextField* throatContinuingField;// = new JTextField(16);
//    /*private*/ JTextField* throatDivergingField;// = new JTextField(16);
//    /*private*/ JTextField* continuingField;// = new JTextField(16);
//    /*private*/ JTextField* divergingField;// = new JTextField(16);
    /*private*/ QCheckBox* setThroatContinuing = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicThroatContinuing = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setThroatDiverging = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicThroatDiverging = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setContinuing = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicContinuing = new QCheckBox(tr("Set up Logic"));
    /*private*/ QCheckBox* setDiverging = new QCheckBox(tr("Add Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupLogicDiverging = new QCheckBox(tr("Set up Logic"));
    /*private*/ QPushButton* getSavedSignalHeads = nullptr;
    /*private*/ QPushButton* changeSignalIcon = nullptr;
    /*private*/ QPushButton* setSignalsDone = nullptr;
    /*private*/ QPushButton* setSignalsCancel = nullptr;
    /*private*/ LayoutTurnout* layoutTurnout = nullptr;
    /*private*/ bool layoutTurnoutHorizontal = false;
    /*private*/ bool layoutTurnoutVertical = false;
    /*private*/ bool layoutTurnoutThroatLeft = false;
    /*private*/ bool layoutTurnoutThroatUp = false;
    /*private*/ bool layoutTurnoutBUp = false;
    /*private*/ bool layoutTurnoutBLeft = false;
    /*private*/ bool turnoutFromMenu = false;
    /*private*/ Turnout* turnout = nullptr;
    /*private*/ SignalHead* throatContinuingHead = nullptr;
    /*private*/ SignalHead* throatDivergingHead = nullptr;
    /*private*/ SignalHead* continuingHead = nullptr;
    /*private*/ SignalHead* divergingHead = nullptr;

    //operational variables for Set Signals at Block Boundary tool
    /*private*/ JmriJFrame* setSignalsAtBlockBoundaryFrame = nullptr;
    /*private*/ bool setSignalsAtBlockBoundaryOpenFlag = false;
    /*private*/ bool setSignalsAtBlockBoundaryFromMenuFlag = false;

    /*private*/ JLabel* block1NameLabel = nullptr;
    /*private*/ JLabel* block2NameLabel = nullptr;

    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* block1IDComboBox = new NamedBeanComboBox(
            (BlockManager*)InstanceManager::getDefault("BlockManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* block2IDComboBox = new NamedBeanComboBox(
            (BlockManager*)InstanceManager::getDefault("BlockManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* eastBoundSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* westBoundSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ QCheckBox* setEastBound = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupLogicEastBound = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setWestBound = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupLogicWestBound = new QCheckBox(tr("Set up SSL"));

    /*private*/ QPushButton* getAnchorSavedSignalHeads = nullptr;
    /*private*/ QPushButton* changeSignalAtBoundaryIcon = nullptr;
    /*private*/ QPushButton* setSignalsAtBlockBoundaryDone = nullptr;
    /*private*/ QPushButton* setSignalsAtBlockBoundaryCancel = nullptr;

    /*private*/ LayoutBlock* block1 = nullptr;
    /*private*/ LayoutBlock* block2 = nullptr;

    /*private*/ TrackSegment* eastTrack = nullptr;
    /*private*/ TrackSegment* westTrack = nullptr;

    /*private*/ PositionablePoint* boundary = nullptr;
    /*private*/ SignalHead* eastBoundHead = nullptr;
    /*private*/ SignalHead* westBoundHead = nullptr;

    /*private*/ bool showWest = true;
    /*private*/ bool showEast = true;

    /*private*/ NamedIcon* testIcon = nullptr;

    // operational variables for Set Signals at Double Crossover Turnout* tool
    /*private*/ JmriJFrame* setSignalsAtXoverTurnoutFrame = nullptr;
    /*private*/ bool setSignalsAtXoverTurnoutOpenFlag = false;
    /*private*/ bool setSignalsAtXoverTurnoutFromMenuFlag = false;

    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a1SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a2SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b1SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b2SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c1SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c2SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d1SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d2SignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ QCheckBox* setA1Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setA2Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setB1Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setB2Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setC1Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setC2Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setD1Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setD2Head = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));

    /*private*/ /*final*/ QCheckBox* setupA1Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupA2Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupB1Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupB2Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupC1Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupC2Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupD1Logic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setupD2Logic = new QCheckBox(tr("Set up SSL"));

    /*private*/ QPushButton* getSavedXoverSignalHeads = nullptr;
    /*private*/ QPushButton* changeXoverSignalIcon = nullptr;
    /*private*/ QPushButton* setXoverSignalsDone = nullptr;
    /*private*/ QPushButton* setXoverSignalsCancel = nullptr;

    /*private*/ SignalHead* a1Head = nullptr;
    /*private*/ SignalHead* a2Head = nullptr;
    /*private*/ SignalHead* b1Head = nullptr;
    /*private*/ SignalHead* b2Head = nullptr;
    /*private*/ SignalHead* c1Head = nullptr;
    /*private*/ SignalHead* c2Head = nullptr;
    /*private*/ SignalHead* d1Head = nullptr;
    /*private*/ SignalHead* d2Head = nullptr;

    /*private*/ int xoverType = LayoutTurnout::DOUBLE_XOVER;	 //changes to RH_XOVER or LH_XOVER as required
    /*private*/ int xoverCurr = LayoutTurnout::UNKNOWN;          //Controls creating the frame
    /*private*/ QString xoverTurnoutName = "";

    /*private*/ JmriJFrame* setSignalMastsAtTurnoutFrame = nullptr;
    /*private*/ bool setSignalMastsAtTurnoutOpenFlag = false;
    /*private*/ bool setSignalMastsAtTurnoutFromMenuFlag = false;

    /*private*/ QPushButton* setSignalMastsDone;
    /*private*/ QPushButton* getSavedSignalMasts;
    /*private*/ QPushButton* setSignalMastsCancel;
    /*private*/ JLabel* turnoutMastNameLabel = nullptr;

    BeanDetails* turnoutSignalMastA;
    BeanDetails* turnoutSignalMastB;
    BeanDetails* turnoutSignalMastC;
    BeanDetails* turnoutSignalMastD;

    QWidget* signalMastTurnoutPanel = new QWidget();
    /*private*/ QVector<QString> turnoutBlocks =  QVector<QString>(4);
    QList<NamedBean*> usedMasts = QList<NamedBean*>();

    /*private*/ JmriJFrame* setSensorsAtTurnoutFrame = nullptr;
    /*private*/ bool setSensorsAtTurnoutOpenFlag = false;
    /*private*/ bool setSensorsAtTurnoutFromMenuFlag = false;

    /*private*/ JFrame* turnoutSensorFrame = nullptr;
    /*private*/ JLabel* turnoutSensorNameLabel = nullptr;

    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* sensorsTurnoutComboBox
            = new NamedBeanComboBox(
                    InstanceManager::turnoutManagerInstance(),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ QPushButton* setSensorsDone;
    /*private*/ QPushButton* getSavedSensors;
    /*private*/ QPushButton* setSensorsCancel;
    /*private*/ QPushButton* changeSensorIcon = nullptr;

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
    /*private*/ QPushButton* setSensorsAtBlockBoundaryDone;// = NULL;
    void setBoundarySensor(Sensor* newSensor, Sensor* currSensor, BeanDetails* beanDetail, QString direction);
    /*private*/ QPushButton* setSensorsAtBlockBoundaryCancel;// = NULL;
    /*private*/ bool setSensorsAtBoundaryOpen;// = false;
    /*private*/ JmriJFrame* setSensorsAtBlockBoundaryFrame;// = NULL;
    /*private*/ bool setSensorsAtBlockBoundaryOpenFlag = false;
    /*private*/ bool setSensorsAtBlockBoundaryFromMenuFlag = false;

    /*private*/ JFrame* sensorFrame;// = NULL;

    /*private*/ bool setSignalMastsAtBoundaryOpen;// = false;
    /*private*/ JmriJFrame* setSignalMastsAtBoundaryFrame;// = NULL;

    double adjust;// = (5.0/90.0);
    int awayright;// = 5;
    /*final*/ int offSetFromPoint;// = 5;

    //operational variables for Set Sensors at Slip tool
    /*private*/ JmriJFrame* setSensorsAtSlipFrame = nullptr;
    /*private*/ bool setSensorsAtSlipOpenFlag = false;
    /*private*/ bool setSensorsAtSlipFromMenuFlag = false;

    QPushButton* getSavedSlipSensors;// = NULL;
    QPushButton* setSlipSensorsDone;// = NULL;
    QPushButton* setSlipSensorsCancel;// = NULL;
    QPushButton* changeSensorSlipIcon;// = NULL;
    JFrame* sensorSlipFrame;// = NULL;

    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSensorsBlockAComboBox
            = new NamedBeanComboBox(
                    (BlockManager*)InstanceManager::getDefault("BlockManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
   /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSensorsBlockBComboBox
            = new NamedBeanComboBox(
                    (BlockManager*)InstanceManager::getDefault("BlockManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
   /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSensorsBlockCComboBox
            = new NamedBeanComboBox(
                    (BlockManager*)InstanceManager::getDefault("BlockManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
   /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSensorsBlockDComboBox
            = new NamedBeanComboBox(
                    (BlockManager*)InstanceManager::getDefault("BlockManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ QVector<QString>* slipSensorBlocks;// = new String[4];

    BeanDetails* slipSensorA;
    BeanDetails* slipSensorB;
    BeanDetails* slipSensorC;
    BeanDetails* slipSensorD;

    QWidget*sensorSlipPanel;// = new QWidget();

    // operational variables for Set SignalMast at Level Crossing tool
    /*private*/ JmriJFrame* setSignalMastsAtLevelXingFrame = nullptr;
    /*private*/ bool setSignalMastsAtLevelXingOpenFlag = false;
    /*private*/ bool setSignalMastsAtLevelXingFromMenuFlag = false;

    /*private*/ JLabel* xingSignalBlockACNameLabel = nullptr;
    /*private*/ JLabel* xingSignalBlockBDNameLabel = nullptr;

    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* xingBlockACComboBox = new NamedBeanComboBox(
            (BlockManager*)InstanceManager::getDefault("BlockManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* xingBlockBDComboBox = new NamedBeanComboBox(
            (BlockManager*)InstanceManager::getDefault("BlockManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

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

    static Logger* log;
    /*private*/ bool hitEndBumper = false;
     /*private*/ bool getBlockInformation();
    /*private*/ LayoutBlock* getBlockFromEntry(/*@Nonnull*/ NamedBeanComboBox/*<Block>*/* blockNameComboBox);
    /*private*/ LayoutBlock* getBlockFromEntry(QString blockName);
    /*private*/ void placeEastBound();
    /*private*/ void placeWestBound();
    /*private*/ void setLogicEastBound();
    /*private*/ void SetLogicSSLWestBound();
    /*private*/ int isHeadAssignedHere(SignalHead* head, LayoutTurnout* lTurnout);
    /*private*/ void warnOfSkippedTurnout(JmriJFrame* frame, QString turnoutName, QString headName);
    /*private*/ TrackSegment* getContinuingTrack(LayoutTurnout* to, int type);
    /*private*/ bool getTurnoutInformation(bool isCrossover);
    /*private*/ bool getTurnoutSignalHeadInformation();
    /*private*/ void placeThroatContinuing();
    /*private*/ void placeThroatDiverging();
    /*private*/ void placeContinuing(QString signalHeadName);
    /*private*/ void placeDiverging(QString signalHeadName);
    /*private*/ void SetLogicSSLThroatContinuing();
    /*private*/ void SetLogicSSLThroatDiverging();
    /*private*/ void SetLogicSSLContinuing();
    /*private*/ void SetLogicSSLDiverging();
    /*private*/ int isSensorAssignedHere(Sensor* sensor, LayoutTurnout* lTurnout);
    SensorIcon* turnoutSensorBlockIcon;
    /*private*/ int whereIsSensorAssigned(Sensor* sensor, LayoutTurnout* lTurnout) ;
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
    /*private*/ void SetLogicSSLXover(SignalHead* head,TrackSegment* track,SignalHead* secondHead,TrackSegment* track2,
                bool setup1, bool setup2);
    /*private*/ void SetLogicSSLXoverContinuing(SignalHead* head,TrackSegment* track);
    // operational variables for Set Signals at Double Crossover Turnout* tool
    /*private*/ JmriJFrame* setSignalsAtTToTFrame;// = NULL;
    /*private*/ bool setSignalsAtTToTOpen;// = false;
//    /*private*/ JTextField* turnout1NameField;// = new JTextField(16);
//    /*private*/ JTextField* turnout2NameField;// = new JTextField(16);
    ///*private*/ JTextField* ttNameField = new JTextField(16);
//    /*private*/ JTextField* a1TToTField;// = new JTextField(16);
//    /*private*/ JTextField* a2TToTField;// = new JTextField(16);
//    /*private*/ JTextField* b1TToTField;// = new JTextField(16);
//    /*private*/ JTextField* b2TToTField;// = new JTextField(16);
//    /*private*/ JTextField* c1TToTField;// = new JTextField(16);
//    /*private*/ JTextField* c2TToTField;// = new JTextField(16);
//    /*private*/ JTextField* d1TToTField;// = new JTextField(16);
//    /*private*/ JTextField* d2TToTField;// = new JTextField(16);

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
    /*private*/ void SetLogicSSLTToT(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2,
                    bool setup1, bool setup2, bool continuing,
                        LayoutTurnout* farTurnout, LayoutTurnout* nearTurnout);
    /*private*/ QString setupNearLogix(LayoutTurnout* nearTurnout, bool continuing,
                                       SignalHead* head);
    /*private*/ void addNearSensorToLogic(QString name);

    //operational variables for Set Signals at slip tool
    /*private*/ JmriJFrame* setSignalsAtSlipFrame = nullptr;
    /*private*/ bool setSignalsAtSlipOpenFlag;// = false;
    /*private*/ bool setSignalsAtSlipFromMenuFlag = false;

    /*private*/ /*final*/ QComboBox* slipNameComboBox = new QComboBox();

    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a1SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a2SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b1SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b2SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c1SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c2SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d1SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d2SlipSignalHeadComboBox
            = new NamedBeanComboBox(
                    (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ QCheckBox* setA1SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupA1SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setA2SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupA2SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setB1SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupB1SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setB2SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupB2SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setC1SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupC1SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setC2SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupC2SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setD1SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupD1SlipLogic = new QCheckBox(tr("Set up SSL"));
    /*private*/ /*final*/ QCheckBox* setD2SlipHead = new QCheckBox(tr("Add the above Signal Head Icon to Panel"));
    /*private*/ /*final*/ QCheckBox* setupD2SlipLogic = new QCheckBox(tr("Set up SSL"));

    /*private*/ QPushButton* setSlipSignalsDone = nullptr;
    /*private*/ QPushButton* setSlipSignalsCancel = nullptr;
    /*private*/ LayoutSlip* layoutSlip = nullptr;

    /*private*/ SignalHead* a1SlipHead = nullptr;
    /*private*/ SignalHead* a2SlipHead = nullptr;
    /*private*/ SignalHead* b1SlipHead = nullptr;
    /*private*/ SignalHead* b2SlipHead = nullptr;
    /*private*/ SignalHead* c1SlipHead = nullptr;
    /*private*/ SignalHead* c2SlipHead = nullptr;
    /*private*/ SignalHead* d1SlipHead = nullptr;
    /*private*/ SignalHead* d2SlipHead = nullptr;

    /*private*/ JPanel* dblSlipC2SigPanel;
    /*private*/ JPanel* dblSlipB2SigPanel;

    /*private*/ void setLogicThroatContinuing();
    /*private*/ void setLogicThroatDiverging();
    /*private*/ void setLogicContinuing();
    /*private*/ void setLogicDiverging();
    /*private*/ void setLogicWestBound();
    /*private*/ void setLogicXover(SignalHead* head,TrackSegment* track,SignalHead* secondHead,TrackSegment* track2,
                bool setup1, bool setup2);
    /*private*/ void setLogicXing(SignalHead* head, TrackSegment* track, LayoutBlock*crossBlock,
                TrackSegment* crossTrack1, TrackSegment* crossTrack2, QString headName);
    /*private*/ void setLogicXoverContinuing(SignalHead* head,TrackSegment* track);
    /*private*/ void setLogicTToT(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2,
                    bool setup1, bool setup2, bool continuing,
                        LayoutTurnout* farTurnout, LayoutTurnout* nearTurnout);
    /*private*/ void setLogicSlip(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2,
                                  bool setup1, bool setup2,  LayoutSlip* slip, Turnout* nearTurnout, Turnout* farTurnout,
                                  int continueState, int divergeState, int number);

    // operational variables for Set Signals at Level Crossing tool
    /*private*/ JmriJFrame* setSignalsAtLevelXingFrame = nullptr;
    /*private*/ bool setSignalsAtLevelXingOpenFlag = false;
    /*private*/ bool setSignalsAtLevelXingFromMenuFlag = false;

    /*private*/ JLabel* blockACNameLabel = nullptr;
    /*private*/ JLabel* blockBDNameLabel = nullptr;

    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* blockACComboBox = new NamedBeanComboBox(
            (BlockManager*)InstanceManager::getDefault("BlockManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* blockBDComboBox = new NamedBeanComboBox(
            (BlockManager*)InstanceManager::getDefault("BlockManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* aSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* bSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* cSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* dSignalHeadComboBox = new NamedBeanComboBox(
            (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
            nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ QCheckBox* setAHead;// = new JCheckBox(rb.getString("Add the above Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupALogic;// = new JCheckBox(rb.getString("Set up SSL"));
    /*private*/ QCheckBox* setBHead;// = new JCheckBox(rb.getString("Add the above Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupBLogic;// = new JCheckBox(rb.getString("Set up SSL"));
    /*private*/ QCheckBox* setCHead;// = new JCheckBox(rb.getString("Add the above Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupCLogic;// = new JCheckBox(rb.getString("Set up SSL"));
    /*private*/ QCheckBox* setDHead;// = new JCheckBox(rb.getString("Add the above Signal Head Icon to Panel"));
    /*private*/ QCheckBox* setupDLogic;// = new JCheckBox(rb.getString("Set up SSL"));
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
    /*private*/ JmriJFrame* setSensorsAtLevelXingFrame = nullptr;
    /*private*/ bool setSensorsAtLevelXingOpenFlag = false;
    /*private*/ bool setSensorsAtLevelXingFromMenuFlag = false;

    /*private*/ JLabel* xingSensorsBlockACNameLabel = nullptr;
    /*private*/ JLabel* xingSensorsBlockBDNameLabel = nullptr;

    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* xingSensorsBlockACComboBox
            = new NamedBeanComboBox(
                    (BlockManager*)InstanceManager::getDefault("BlockManager"),
                    nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
    /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* xingSensorsBlockBDComboBox
            = new NamedBeanComboBox(
       (BlockManager*)InstanceManager::getDefault("BlockManager"),
       nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

    /*private*/ QPushButton* getSavedXingSensors = nullptr;
    /*private*/ QPushButton* setXingSensorsDone = nullptr;
    /*private*/ QPushButton* setXingSensorsCancel = nullptr;
    /*private*/ QPushButton* changeSensorXingIcon = nullptr;
    JFrame* sensorXingFrame = nullptr;

    /*private*/ QVector<QString>* xingSensorBlocks = new QVector<QString>(4);

    BeanDetails/*<Sensor>*/* xingSensorA;
    BeanDetails/*<Sensor>*/* xingSensorB;
    BeanDetails/*<Sensor>*/* xingSensorC;
    BeanDetails/*<Sensor>*/* xingSensorD;

    JPanel* sensorXingPanel = new JPanel(new FlowLayout());

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

    /*private*/ void SetLogicSSLSlip(SignalHead* head,TrackSegment* track1,SignalHead* secondHead,TrackSegment* track2, bool setup1, bool setup2,  LayoutSlip* slip, Turnout* nearTurnout, Turnout* farTurnout,int continueState, int divergeState, int number);
    /*private*/ bool getSlipTurnoutInformation();
    /*private*/ QString setupNearLogixSlip(Turnout* turn, int nearState, SignalHead* head, Turnout* farTurn, int farState, LayoutSlip* slip, int number);
    /*private*/ void addNearSensorToSlipLogic(QString name);

    // operational variables for Set SignalMast at Slip tool
    /*private*/ JmriJFrame* setSignalMastsAtLayoutSlipFrame = nullptr;
    /*private*/ bool setSignalMastsAtLayoutSlipOpenFlag = false;
    /*private*/ bool setSignalMastsAtLayoutSlipFromMenuFlag = false;

    QPushButton* getSavedSlipSignalMasts;// = NULL;
    QPushButton* setSlipSignalMastsDone;// = NULL;
    QPushButton* setSlipSignalMastsCancel;// = NULL;

  /*private*/ QVector<QString>* slipBlocks;// = new String[4];

  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSignalBlockAComboBox
          = new NamedBeanComboBox(
                  (BlockManager*)InstanceManager::getDefault("BlockManager"),
                  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSignalBlockBComboBox
          = new NamedBeanComboBox(
                   (BlockManager*)InstanceManager::getDefault("BlockManager"),
                  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSignalBlockCComboBox
          = new NamedBeanComboBox(
                   (BlockManager*)InstanceManager::getDefault("BlockManager"),
                  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* slipSignalBlockDComboBox
          = new NamedBeanComboBox(
                  (BlockManager*)InstanceManager::getDefault("BlockManager"),
                  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

  /*private*/ JLabel* slipSignalBlockANameLabel = nullptr;
  /*private*/ JLabel* slipSignalBlockBNameLabel = nullptr;
  /*private*/ JLabel* slipSignalBlockCNameLabel = nullptr;
  /*private*/ JLabel* slipSignalBlockDNameLabel = nullptr;

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
  /*private*/ void SetLogicSSLXing(SignalHead* head, TrackSegment* track, LayoutBlock*crossBlock,TrackSegment* crossTrack1, TrackSegment* crossTrack2, QString headName);
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
  /*private*/ JmriJFrame* setSignalsAt3WayTurnoutFrame =nullptr;
  /*private*/ bool setSignalsAt3WayTurnoutOpenFlag = false;
  /*private*/ bool setSignalsAt3WayTurnoutFromMenuFlag = false;

  /*private*/ QLabel* turnoutANameLabel = nullptr;
  /*private*/ QLabel* turnoutBNameLabel = nullptr;

  /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* turnoutAComboBox = new NamedBeanComboBox(
          InstanceManager::turnoutManagerInstance(),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* turnoutBComboBox = new NamedBeanComboBox(
          InstanceManager::turnoutManagerInstance(),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a1_3WaySignalHeadComboBox = new NamedBeanComboBox(
          (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a2_3WaySignalHeadComboBox = new NamedBeanComboBox(
          (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* a3_3WaySignalHeadComboBox = new NamedBeanComboBox(
          (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* b_3WaySignalHeadComboBox = new NamedBeanComboBox(
          (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* c_3WaySignalHeadComboBox = new NamedBeanComboBox(
          (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<SignalHead>*/* d_3WaySignalHeadComboBox = new NamedBeanComboBox(
          (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"),
          nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

  /*private*/ bool setSignalsAt3WayOpen;// =false;
//  JTextField* turnoutANameField;// =new JTextField(16);
//  JTextField* turnoutBNameField;// =new JTextField(16);
//  JTextField* a13WayField;// =new JTextField(16);
//  JTextField* a23WayField;// =new JTextField(16);
//  JTextField* a33WayField;// =new JTextField(16);
//  JTextField* b3WayField;// =new JTextField(16);
//  JTextField* c3WayField;// =new JTextField(16);
//  JTextField* d3WayField;// =new JTextField(16);
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

    /*private*/ void oneFrameToRuleThemAll(/*@Nonnull*/ JmriJFrame* goodFrame);
    /*private*/ JmriJFrame* closeIfNotFrame(/*@Nonnull */JmriJFrame* goodFrame, /*@CheckForNull*/ JmriJFrame* badFrame);
  //convenience strings
  /*private*/ /*final*/ QString eastString = tr("East");
  /*private*/ /*final*/ QString westString = tr("West");
  /*private*/ /*final*/ QString continuingString = tr("Continuing");
  /*private*/ /*final*/ QString divergingString = tr("Diverging");
  /*private*/ /*final*/ QString throatString = tr("Throat");
  /*private*/ /*final*/ QString throatContinuingString = tr("Throat Continuing");
  /*private*/ /*final*/ QString throatDivergingString = tr("Throat Diverging");

  /*private*/ /*final*/ QString divergingAString = tr("Diverging %1").arg("A");
  /*private*/ /*final*/ QString divergingBString = tr("Diverging %1").arg("B");
  /*private*/ void addInfoToMenu(/*@CheckForNull*/ QString title,
          /*@CheckForNull*/ QString info, /*@Nonnull*/ QMenu* menu) ;
  /*private*/ void addInfoToMenu(/*@CheckForNull*/ QString info, /*@Nonnull*/ QMenu* menu);

  /*===============================*\
  |* setSignalMastsAtBlockBoundary *|
  \*===============================*/
  /*private*/ JmriJFrame* setSignalMastsAtBlockBoundaryFrame = nullptr;
  /*private*/ bool setSignalMastsAtBlockBoundaryOpenFlag = false;
  /*private*/ bool setSignalMastsAtBlockBoundaryFromMenuFlag = false;

  /*private*/ QPushButton* getAnchorSavedSignalMasts = nullptr;
  /*private*/ QPushButton* setSignalMastsAtBlockBoundaryDone = nullptr;
  /*private*/ QPushButton* setSignalMastsAtBlockBoundaryCancel = nullptr;

  BeanDetails/*<SignalMast*>*/* eastSignalMast;
  BeanDetails/*<SignalMast*>*/* westSignalMast;

  JPanel* signalMastBlockPanel = new JPanel(new FlowLayout());

 private slots:
    /*private*/ void setSignalsAtBlockBoundaryDonePressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setSignalsAtBlockBoundaryCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void turnoutSignalsGetSaved (JActionEvent* /*a*/ = 0);
    void setSignalsDonePressed(JActionEvent* /*a*/ = 0);
    /*private*/ void setSignalsCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setXoverSignalsCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void xoverTurnoutSignalsGetSaved (JActionEvent* /*a*/ = 0);
    /*private*/ void setXoverSignalsDonePressed (JActionEvent* /*a*/ = 0);
    /*private*/ void turnoutSensorsGetSaved (JActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsDonePressed (JActionEvent* /*a*/ = 0);
    /*private*/ void turnoutSignalMastsGetSaved (JActionEvent* /*a*/ = 0); // SLOT
    /*private*/ void getSavedAnchorSensors (JActionEvent* /*a*/ = 0);
    /*private*/ void setXingSensorsCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsAtBlockBoundaryCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsAtBlockBoundaryDonePressed (JActionEvent* a  = 0);
    /*private*/ void setSignalMastsCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setSignalMastsDonePressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setSensorsCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void getSavedAnchorSignalMasts (JActionEvent* /*a*/ = 0);
    /*private*/ void setSignalMastsAtBlockBoundaryCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setSignalMastsAtBlockBoundaryDonePressed (JActionEvent* /*a*/ = 0) ;
    /*private*/ void setXingSignalsCancelPressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setXingSignalsDonePressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setXingSensorsDonePressed (JActionEvent* /*a*/ = 0);
    /*private*/ void setTToTSignalsDonePressed (JActionEvent* /*a*/ = 0);
    ///*private*/ void tToTTurnoutSignalsGetSaved (ActionEvent* /*a*/ = 0);
    /*private*/ void setTToTSignalsCancelPressed ();
    /*private*/ void slipSensorsGetSaved (JActionEvent* a = 0);
    /*private*/ void setSlipSensorsCancelPressed (JActionEvent* a = 0);
    /*private*/ void setSlipSensorsDonePressed (JActionEvent* a = 0);
    /*private*/ void setSlipSignalsDonePressed (JActionEvent* a = 0);
    /*private*/ void getSlipTurnoutSignalsGetSaved (JActionEvent* a = 0);
    /*private*/ void setSlipSignalsCancelPressed (JActionEvent* a = 0);
    /*private*/ void xingSignalsGetSaved (JActionEvent* a = 0);
    /*private*/ void setSlipSignalMastsCancelPressed (JActionEvent* a = 0);
    /*private*/ void slipSignalMastsGetSaved (JActionEvent* a = 0);
    /*private*/ void setSlipSignalMastsDonePressed (JActionEvent* a = 0);
    /*private*/ void xingSignalMastsGetSaved (JActionEvent* a = 0);
    /*private*/ void setXingSignalMastsCancelPressed (JActionEvent*  = 0);
    /*private*/ void setXingSignalMastsDonePressed (JActionEvent* a = 0);
    /*private*/ void xingSensorsGetSaved (JActionEvent* a = 0);
    /*private*/ void getSaved3WaySignals (JActionEvent* a = 0);
    /*private*/ void set3WaySignalsCancelPressed (JActionEvent* a = 0);
    /*private*/ void set3WaySignalsDonePressed (JActionEvent* a = 0);

    /*private*/ void setSignalsAtTToTTurnoutsGetSaved(/*ActionEvent* a*/);
protected:
    /*protected*/ bool addLayoutTurnoutSignalHeadInfoToMenu(
                /*@Nonnull*/ QString inTurnoutNameA, /*@Nonnull*/ QString inTurnoutNameB,
                /*@Nonnull*/ QMenu* inMenu);
    /*protected*/ bool addBlockBoundarySignalHeadInfoToMenu(/*@Nonnull*/ PositionablePoint* inPositionablePoint,
                /*@Nonnull*/ QMenu *inMenu);
    /*protected*/ bool addLevelXingSignalHeadInfoToMenu(
            /*@Nonnull*/ LevelXing* inLevelXing,
            /*@Nonnull*/ QMenu* inMenu);
    /*protected*/ bool addLayoutSlipSignalHeadInfoToMenu(
            /*@Nonnull*/ LayoutTurnout* inLayoutTurnout,
            /*@Nonnull*/ QMenu* inMenu);

    friend class SSWindowListener;
    friend class SXWindowListener;
    friend class SMSWindowListener;
    friend class XSMSWindowListener;
    friend class XSSSWindowListener;
    friend class SASWindowListener;
    friend class SSFWindowListener;
    friend class S3WWindowListener;
    friend class LayoutTurnout;
    friend class LevelXing;
    friend class LayoutSlip;
    friend class SBBWindowListener;
    friend class PositionablePoint;
    friend class LayoutEditorToolBarPanel;
};

/*static*/ class BeanDetails : public QObject
{
 Q_OBJECT
 /*private*/ QString bundleName;
    QString beanString;
    QLabel* textLabel;

    QString boundaryLabelText = tr("Boundary Of");
    /*private*/ /*final*/ JLabel* boundaryLabel = new JLabel(boundaryLabelText);

    Manager* manager;

    QGroupBox* detailsPanel;// = new QWidget();
    QRadioButton* addBeanCheck;// = new QRadioButton(tr("Do Not Place On Panel"));
    QRadioButton* left;// = new QRadioButton(tr("Left Hand Side"));
    QRadioButton* right;// = new QRadioButton(tr("Right Hand Side"));
    QButtonGroup* buttonGroup;// = new QButtonGroup();
    /*private*/ NamedBeanComboBox/*<B>*/* beanCombo;

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
    NamedBeanComboBox *getCombo();
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

class SBBWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutEditorTools* parent;
public:
 SBBWindowListener(LayoutEditorTools* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->setSignalsAtBlockBoundaryCancelPressed();
 }
};
#if 0
/*static*/ class BeanDetails : public NamedBean
{
 Q_OBJECT
        /*private*/ QString bundleName;
        /*private*/ QString beanString;
        /*private*/ JLabel* textLabel;

        /*private*/ /*final*/ QString boundaryLabelText = tr("Boundary Of");
        /*private*/ /*final*/ JLabel* boundaryLabel = new JLabel(boundaryLabelText);

        /*private*/ Manager/*<B>*/* manager;

        /*private*/ /*final*/ JPanel* detailsPanel = new JPanel(new FlowLayout());
        /*private*/ /*final*/ QRadioButton* addBeanCheck = new QRadioButton(tr("Do Not Place On Panel"));
        /*private*/ /*final*/ QRadioButton* left = new QRadioButton(tr("Left Hand Side"));
        /*private*/ /*final*/ QRadioButton* right = new QRadioButton(tr("Right Hand Side"));
        /*private*/ /*final*/ QButtonGroup* buttonGroup = new QButtonGroup();
        /*private*/ NamedBeanComboBox/*<B>*/* beanCombo;

        /*private*/ /*final*/ JLabel* boundaryBlocks = new JLabel();

        /*private*/ /*final*/ Border* blackline = BorderFactory::createLineBorder(Qt::black);
        Logger* log = LoggerFactory::getLogger("BeanDetails");
public:
        BeanDetails(/*@Nonnull*/ String beanType, /*@Nonnull*/ Manager* manager) {
            beanCombo = new NamedBeanComboBox(manager);
            beanCombo->setAllowNull(true);
//            JComboBoxUtil.setupComboBoxMaxRows(beanCombo);
            //I18N translate from type (Sensor) to BeanNameSensor
            //to use NamedBeanBundle property
            if ("Sensor" == (beanType)) {
                bundleName = tr("Sensor");
            } else if ("SignalMast"==(beanType)) {
                bundleName = tr("SignalMast");
            } else {
                log->error(tr("Unexpected value for BeanDetails: '%1'").arg(beanType));
                bundleName = beanType;
            }
            beanString = /*Bundle.getMessage*/(bundleName);
            textLabel = new JLabel(beanString);
            this->manager = manager;
            //this.beanType = beanType;

            buttonGroup->addButton(addBeanCheck);
            buttonGroup->addButton(left);
            buttonGroup->addButton(right);
            addBeanCheck->setChecked(true);

            boundaryBlocks->setAlignment(/*Component.CENTER_ALIGNMENT*/Qt::AlignHCenter);
            boundaryBlocks->setOpaque(false);
            detailsPanel->setLayout(new BorderLayout());
            //detailsPanel.setBorder(BorderFactory.createTitledBorder(blackline, Bundle.getMessage("Block Boundary")));
            detailsPanel->setTitle(tr(""));
            boundaryLabel->setAlignment(/*Component.CENTER_ALIGNMENT*/Qt::AlignHCenter);

            JPanel* boundaryDetails = new JPanel(new FlowLayout());
            boundaryDetails.setOpaque(false);
            boundaryDetails.setLayout(new BoxLayout(boundaryDetails, BoxLayout.Y_AXIS));
            boundaryDetails->layout()->addWidget((boundaryLabel);
            boundaryDetails->layout()->addWidget((boundaryBlocks);

            detailsPanel->layout()->addWidget(boundaryDetails, BorderLayout::PAGE_START);
            detailsPanel->layout()->addWidget(addIconPanel(), BorderLayout.CENTER);
            detailsPanel->layout()->addWidget(positionLeftRight(), BorderLayout.PAGE_END);
        }
protected:
        /*protected*/ void setTextField(QString value) {
            beanCombo->setSelectedItem(manager->getNamedBean(value));
        }

        /*protected*/ QString getText() {
            return beanCombo->getSelectedItemDisplayName();
        }

        /*protected*/ NamedBean* getBean() {
            return beanCombo->getSelectedItem();
        }

        /*protected*/ JPanel* getDetailsPanel() {
            return detailsPanel;
        }

        /*protected*/ bool addToPanel() {
            return !addBeanCheck->isChecked();
        }

        /*protected*/ bool isRightSelected() {
            return right->isChecked();
        }

        /*protected*/ void setBoundaryTitle(QString text) {
            //detailsPanel.setBorder(BorderFactory.createTitledBorder(blackline, text));
         detailsPanel->setTitle(text);
        }

        /*protected*/ void setBoundaryLabelText(QString text) {
            boundaryLabel->setText(text);
        }

        /*protected*/ void setBoundaryLabel(QString label) {
            boundaryBlocks->setText(label);
        }

        /*protected*/ NamedBeanComboBox* getCombo() {
            return beanCombo;
        }

        /*protected*/ JPanel* positionLeftRight() {
            JPanel placementPanel = new JPanel();
            placementPanel.setBorder(BorderFactory.createTitledBorder(
                    blackline,
                    Bundle.getMessage("PlaceItem", new Object[]{beanString})));

            placementPanel.setLayout(new BoxLayout(placementPanel, BoxLayout.Y_AXIS));
            placementPanel.setOpaque(false);
            placementPanel->layout()->addWidget((addBeanCheck);
            placementPanel->layout()->addWidget((left);
            placementPanel->layout()->addWidget((right);
            addBeanCheck.setOpaque(false);
            left.setOpaque(false);
            right.setOpaque(false);

            addBeanCheck.setToolTipText(Bundle.getMessage("PlaceItemToolTip",
                    new Object[]{beanString}));

            right.setToolTipText(Bundle.getMessage("PlaceRightToolTip",
                    new Object[]{beanString}));

            left.setToolTipText(Bundle.getMessage("PlaceLeftToolTip",
                    new Object[]{beanString}));
            return placementPanel;
        }

        /*protected*/ JPanel* addIconPanel() {
            JPanel* addBeanPanel = new JPanel(new FlowLayout());
            addBeanPanel->setOpaque(false);
            addBeanPanel->layout()->addWidget((textLabel);
            textLabel.setOpaque(false);
            addBeanPanel->layout()->addWidget((beanCombo);
            return addBeanPanel;
        }
    };
#endif
#endif // LAYOUTEDITORTOOLS_H
