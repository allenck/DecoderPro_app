#ifndef PANELEDITOR_H
#define PANELEDITOR_H

#include <QMainWindow>
#include "logger.h"
#include "editor.h"
#include "actionlistener.h"
#include "abstractaction.h"

namespace Ui {
class PanelEditor;
}

class QComboBox;
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
 /*public*/ void setRemoveMenu(Positionable* p, QMenu* popup);

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
    void onLabelAdd();
    void onEditableBox();
    void onControllingBox();
    void onShowToolTipBox();
    void onScrollableComboBox();
    /*public*/ void itemStateChanged(int index);
    /*public*/ void windowClosing(QCloseEvent* e);

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
 /*private*/ void removeMultiItems();
 /*private*/ void setMultiItemsPositionableMenu(QMenu* popup);
 QCheckBox* editableBox;// = new JCheckBox(Bundle.getMessage("CheckBoxEditable"));
 QCheckBox* positionableBox;// = new JCheckBox(Bundle.getMessage("CheckBoxPositionable"));
 QCheckBox* controllingBox;// = new JCheckBox(Bundle.getMessage("CheckBoxControlling"));
 //QCheckBox* showCoordinatesBox = new JCheckBox(Bundle.getMessage("CheckBoxShowCoordinates"));
 QCheckBox* showTooltipBox;// = new JCheckBox(Bundle.getMessage("CheckBoxShowTooltips"));
 QCheckBox* hiddenBox;// = new JCheckBox(Bundle.getMessage("CheckBoxHidden"));
 QCheckBox* menuBox;// = new JCheckBox(Bundle.getMessage("CheckBoxMenuBar"));
 QLabel* scrollableLabel;// = new JLabel(Bundle.getMessage("ComboBoxScrollable"));
 QComboBox* scrollableComboBox;// = new JComboBox();

 QPushButton* labelAdd;// = new JButton(Bundle.getMessage("ButtonAddText"));
 JTextField* nextLabel;// = new JTextField(10);

 QComboBox* _addIconBox;
 /*private*/ void hiddenCheckBoxListener();

private slots:
 void on_storeIndexItem_triggered();
 void on_CPEView_triggered();

protected:
 /*protected*/ void init(QString name);
 /*protected*/ virtual void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);
 /*protected*/ void showMultiSelectPopUp(/*final*/ QGraphicsSceneMouseEvent* event, Positionable* p);
 /*protected*/ QList <Positionable*>* _multiItemCopyGroup;// = NULL;  // items gathered inside fence
 /*protected*/ void backgroundPopUp(QGraphicsSceneMouseEvent* event);
 /*protected*/ bool pasteItemFlag;// = false;
 /*protected*/ void makeColorMenu(QMenu* colorMenu);
 /*protected*/ void addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup,
                        /*final*/ QString name, QColor color);
// /*protected*/ void PanelEditor::setColorButton(QColor color, QColor buttonColor, JRadioButtonMenuItem r);
 /*protected*/ void showAddItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event, QMenu* popup);
 /*protected*/ void pasteItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event);
 /*protected*/ void pasteItem(QGraphicsSceneMouseEvent* e);
// /*protected*/ void setNextLocation(Positionable* obj);
 /*protected*/ bool addItemViaMouseClick;// = false;
 /*protected*/ void copyItem(Positionable* p);
 void repaint();
 /*protected*/ void setNextLocation(Positionable* obj);

 friend class PositionableLabel;
 friend class RemoveMenuAction;
 friend class LockItemListener;
 friend class PanelEditorXml;
};
Q_DECLARE_METATYPE(PanelEditor)

class RemoveMenuAction : public AbstractAction
{
 Q_OBJECT
 Positionable* comp;
 PanelEditor *parent;
public slots:
 /*public*/ void actionPerformed();
public:
 RemoveMenuAction(QString title, PanelEditor *parent);
 AbstractAction* init(Positionable* pos);
};

class LockItemListener : public ActionListener
{
 Q_OBJECT
 Positionable* comp;
 QAction* checkBox;
 PanelEditor* editor;
public slots:
 /*public*/ void actionPerformed();
public:
 LockItemListener(PanelEditor* editor);
 ActionListener* init(Positionable* pos, QAction* cb);
};

class RenameActionListener : public ActionListener
{
 Q_OBJECT
 PanelEditor* editor;

public slots:
 //@Override
 /*public*/ void actionPerformed(/*ActionEvent e*/);

 ActionListener* init(PanelEditor* e);
};
#endif // PANELEDITOR_H
