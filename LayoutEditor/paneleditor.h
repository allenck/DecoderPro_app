#ifndef PANELEDITOR_H
#define PANELEDITOR_H

#include <QMainWindow>
#include "logger.h"
#include "editor.h"
#include "actionlistener.h"

namespace Ui {
class PanelEditor;
}

class JTextField;
//class AddPanelIconDialog;
//class AddPanelEditorDialog;
class InputDialog;
class PanelEditor : public Editor
{
    Q_OBJECT

public:
    explicit PanelEditor(QWidget *parent = nullptr);
    /*public*/ PanelEditor(QString name, QWidget *parent=nullptr);

    ~PanelEditor();
 PanelEditor(const PanelEditor&) :Editor() {}
    /*public*/ bool _debug;
 /*public*/ void initView();

public slots:
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
    /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event);
    void sceneDropEvent(QGraphicsSceneDragDropEvent*);
    /*public*/ void setBackgroundMenu(QMenu* popup);
    void on_backgroundColorSelection(QAction* act);
    void on_actionAdd_loco_triggered();
    void on_actionAdd_Loco_from_roster_triggered();
    void on_actionRemove_markers_triggered();
    void on_addClock_triggered();
//    void on_addLcdClock_triggered();
//    void on_addNixieClockAct_triggered();
    void on_addSensor_triggered();
    void on_addSignalHead_triggered();
    void on_addSignalMast_triggered();
//    void on_actionOpenEditor_triggered();
    /*public*/ void putItem(Positionable* l);
    void on_addRHTurnout_triggered();
    void on_addLHTurnout_triggered();
    void on_addSlipTurnout_triggered();
    void setLocation(int x, int y);
    void on_addLight_triggered();
    void on_addRPSReporter_triggered();
    void on_addMemory_triggered();
    void on_addReporter_triggered();
    void on_addIcon_triggered();
    void on_addTextLabel_triggered();
    void on_actionDelete_this_panel_triggered();
    //void on_menuWindow_aboutToShow();
    void on_addMultiSensor_triggered();
    void on_addBackground_triggered();
    void on_actionOpenEditor_triggered();
private:
    Ui::PanelEditor *ui;
 Logger* log;
 int panelWidth, panelHeight;
 bool delayedPopupTrigger;
 /*private*/ void amendSelectionGroup(Positionable* p);
 void drawLabelImages(EditScene* g2);
// AddPanelEditorDialog* dlg;
// AddPanelIconDialog* addSensorDlg;
// AddPanelIconDialog* addRHTurnoutDlg;
// AddPanelIconDialog* addLHTurnoutDlg;
// AddPanelIconDialog* addSlipTODlg;
// AddPanelIconDialog* addLightDlg;
// AddPanelIconDialog* addRPSReporterDlg;
// AddPanelIconDialog* addReporterDlg;
// AddPanelIconDialog* addMemoryDlg;
// AddPanelIconDialog* addIconDlg;
// AddPanelIconDialog* addSignalHeadDlg;
// AddPanelIconDialog* addSignalMastDlg;
// AddPanelIconDialog* addMultiSensorDlg;
// AddPanelIconDialog* addBackgroundDlg;

 InputDialog* addTextLabelDlg;
 void closeEvent(QCloseEvent *);
 JTextField* nextX;// = new JTextField(tr("Default X"),4);
 JTextField* nextY;// = new JTextField(tr("Default Y"),4);
private slots:
 void on_storeIndexItem_triggered();
 void on_CPEView_triggered();

protected:
 /*protected*/ void init(QString name);
 /*protected*/ virtual void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);
 /*protected*/ void showMultiSelectPopUp(/*final*/ QGraphicsSceneMouseEvent* event, Positionable* p);
 /*protected*/ QVector <Positionable*>* _multiItemCopyGroup;// = NULL;  // items gathered inside fence
 /*protected*/ void backgroundPopUp(QGraphicsSceneMouseEvent* event);
 /*protected*/ bool pasteItemFlag;// = false;
 /*protected*/ void makeColorMenu(QMenu* colorMenu);
 /*protected*/ void addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup,
                        /*final*/ QString name, QColor color);
// /*protected*/ void PanelEditor::setColorButton(QColor color, QColor buttonColor, JRadioButtonMenuItem r);
 /*protected*/ void showAddItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event, QMenu* popup);
 /*protected*/ void pasteItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event);
 /*protected*/ void pasteItem();
// /*protected*/ void setNextLocation(Positionable* obj);
 /*protected*/ bool addItemViaMouseClick;// = false;
 /*protected*/ void copyItem(Positionable* p);
 void repaint();
 /*protected*/ void setNextLocation(Positionable* obj);

 friend class PositionableLabel;
};
Q_DECLARE_METATYPE(PanelEditor)
#endif // PANELEDITOR_H
