#ifndef LAYOUTEDITORTOOLS_H
#define LAYOUTEDITORTOOLS_H

#include <QObject>
#include "layouteditor.h"
#include "multiiconeditor.h"
#include "signalhead.h"
#include "layoutturnout.h"

class LayoutEditor;
class LayoutEditorTools : public QObject
{
    Q_OBJECT
public:
 //explicit LayoutEditorTools(QObject *parent = 0);
 // constructor method
 /*public*/ LayoutEditorTools(LayoutEditor* thePanel, QObject *parent = 0);
// display dialog for Set Signals at Turnout tool
///*public*/ void setSignalsAtTurnoutFromMenu( LayoutTurnout* to,
//                MultiIconEditor* theEditor, JFrame theFrame ) ;
///*public*/ void setSignalsAtTurnout( MultiIconEditor* theEditor, JFrame* theFrame );

signals:
    
public slots:
private:
    // constants
    /*private*/ int NONE; //0;  // Signal at Turnout Positions
    /*private*/ int A1; //1;
    /*private*/ int A2; //2;
    /*private*/ int A3; //3;
    /*private*/ int B1; //4;
    /*private*/ int B2; //5;
    /*private*/ int C1; //6;
    /*private*/ int C2; //7;
    /*private*/ int D1; //8;
    /*private*/ int D2; //9;

    // operational instance variables shared between tools
    /*private*/ LayoutEditor* layoutEditor; //null;
    /*private*/ MultiIconEditor* signalIconEditor; //null;
//    /*private*/ JFrame* signalFrame; //null;
    /*private*/ bool needRedraw; //false;
//    /*private*/ BlockBossLogic* logic; //null;
    /*private*/ SignalHead* auxSignal; //null;
    // operational variables for Set Signals at Turnout tool
#if 0 //TODO:
    /*private*/ JmriJFrame setSignalsFrame = NULL;
    /*private*/ boolean setSignalsOpen = false;
    /*private*/ JTextField turnoutNameField = new JTextField(16);
    /*private*/ JTextField throatContinuingField = new JTextField(16);
    /*private*/ JTextField throatDivergingField = new JTextField(16);
    /*private*/ JTextField continuingField = new JTextField(16);
    /*private*/ JTextField divergingField = new JTextField(16);
    /*private*/ JCheckBox setThroatContinuing = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ JCheckBox setupLogicThroatContinuing = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ JCheckBox setThroatDiverging = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ JCheckBox setupLogicThroatDiverging = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ JCheckBox setContinuing = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ JCheckBox setupLogicContinuing = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ JCheckBox setDiverging = new JCheckBox(rb.getString("PlaceHead"));
    /*private*/ JCheckBox setupLogicDiverging = new JCheckBox(rb.getString("SetLogic"));
    /*private*/ JButton getSavedSignalHeads = NULL;
    /*private*/ JButton changeSignalIcon = NULL;
    /*private*/ JButton setSignalsDone = NULL;
    /*private*/ JButton setSignalsCancel = NULL;
    /*private*/ LayoutTurnout layoutTurnout = NULL;
    /*private*/ boolean layoutTurnoutHorizontal = false;
    /*private*/ boolean layoutTurnoutVertical = false;
    /*private*/ boolean layoutTurnoutThroatLeft = false;
    /*private*/ boolean layoutTurnoutThroatUp = false;
    /*private*/ boolean layoutTurnoutBUp = false;
    /*private*/ boolean layoutTurnoutBLeft = false;
    /*private*/ boolean turnoutFromMenu = false;
    /*private*/ Turnout turnout = NULL;
    /*private*/ SignalHead throatContinuingHead = NULL;
    /*private*/ SignalHead throatDivergingHead = NULL;
    /*private*/ SignalHead continuingHead = NULL;
    /*private*/ SignalHead divergingHead = NULL;
#endif
};

#endif // LAYOUTEDITORTOOLS_H
