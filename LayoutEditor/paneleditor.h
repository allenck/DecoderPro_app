#ifndef PANELEDITOR_H
#define PANELEDITOR_H

#include <QMainWindow>
#include "logger.h"
#include "editor.h"
#include "actionlistener.h"
#include "abstractaction.h"
#include "keylistener.h"
#include "jtextfield.h"
#include "jcheckbox.h"
#include "windowlistener.h"
#include "liblayouteditor_global.h"

//namespace Ui {
//class PanelEditor;
//}

class QComboBox;
class JTextField;
//class AddPanelIconDialog;
//class AddPanelEditorDialog;
class InputDialog;
class LIBLAYOUTEDITORSHARED_EXPORT PanelEditor : public Editor
{
    Q_OBJECT

public:
    explicit PanelEditor(QWidget *parent = nullptr);
    /*public*/ PanelEditor(QString name, QWidget *parent=nullptr);

    ~PanelEditor();
 PanelEditor(const PanelEditor&) :Editor() {}
 ///*public*/ bool _debug;
 /*public*/ void initView()override;
 /*public*/ void setRemoveMenu(Positionable* p, QMenu* popup) override;
 /*public*/ QString getClassName() override;
 /*public*/ JmriJFrame* makeFrame(QString name);

public slots:
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event) override;
    void sceneDropEvent(QGraphicsSceneDragDropEvent*);
    /*public*/ void setBackgroundMenu(QMenu* popup);
    void on_backgroundColorSelection(QAction* act);
    void on_actionAdd_loco_triggered();
    void on_actionAdd_Loco_from_roster_triggered();
    void on_actionRemove_markers_triggered();
    void on_addClock_triggered();
    void on_addLcdClock_triggered();
    void on_addNixieClockAct_triggered();
    void on_addSensor_triggered();
    void on_addSignalHead_triggered();
    void on_addSignalMast_triggered();
//    void on_actionOpenEditor_triggered();
    /*public*/ void putItem(Positionable* l)override;
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
    /*public*/ void itemStateChanged(int index);
    /*public*/ void windowClosing(QCloseEvent* e) override;

private:
    //Ui::PanelEditor *ui;
 static Logger* log;
 //int panelWidth, panelHeight;
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
 void closeEvent(QCloseEvent *)override;
 JTextField* nextX = new JTextField(tr("0"),4);
 JTextField* nextY = new JTextField(tr("0"),4);
 /*private*/ void removeMultiItems();
 /*private*/ void setMultiItemsPositionableMenu(QMenu* popup);
 QCheckBox* editableBox = new QCheckBox(tr("Panel items popup menus active"));
 QCheckBox* positionableBox = new QCheckBox(tr("All panel items can be repositioned"));
 QCheckBox* controllingBox = new QCheckBox(tr("Panel items control layout"));
 //QCheckBox* showCoordinatesBox = new QCheckBox(tr("Show item coordinates in popup menu"));
 QCheckBox* showTooltipBox = new QCheckBox(tr("Show Tooltips for all items"));
 QCheckBox* hiddenBox = new QCheckBox(tr("Show all hidden Items"));
 QCheckBox* menuBox = new QCheckBox(tr("Panel has menu"));
 QLabel* scrollableLabel = new QLabel(tr("Panel scrollbars"));
 JComboBox* scrollableComboBox = new JComboBox();

 QPushButton* labelAdd = new QPushButton(tr("Add text:"));
 JTextField* nextLabel = new JTextField(10);

 QComboBox* _addIconBox;
 /*private*/ void hiddenCheckBoxListener();

private slots:

protected:
 /*protected*/ void init(QString name);
 /*protected*/ void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event)override;
 /*protected*/ void showMultiSelectPopUp(/*final*/ QGraphicsSceneMouseEvent* event, Positionable* p);
 /*protected*/ QList <Positionable*>* _multiItemCopyGroup= nullptr;  // items gathered inside fence
 /*protected*/ void backgroundPopUp(QGraphicsSceneMouseEvent* event);
 /*protected*/ bool pasteItemFlag = false;
 /*protected*/ void makeColorMenu(QMenu* colorMenu);
 /*protected*/ void addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup,
                        /*final*/ QString name, QColor color);
// /*protected*/ void PanelEditor::setColorButton(QColor color, QColor buttonColor, JRadioButtonMenuItem r);
 /*protected*/ void showAddItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event, QMenu* popup);
 /*protected*/ void pasteItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event);
 /*protected*/ void pasteItem(QGraphicsSceneMouseEvent* e);
// /*protected*/ void setNextLocation(Positionable* obj);
 /*protected*/ bool addItemViaMouseClick = false;
 /*protected*/ void copyItem(Positionable* p);
 void repaint()override;
 /*protected*/ void setNextLocation(Positionable* obj)override;
 /*protected*/ void paintTargetPanel(QGraphicsScene* g) override;
 /*protected*/ void targetWindowClosingEvent(QCloseEvent* /*e*/)override;

 friend class PositionableLabel;
 friend class RemoveMenuAction;
 friend class LockItemListener;
 friend class PanelEditorXml;
 friend class LayoutEditorXml;
 friend class PEKeyListener;
};
Q_DECLARE_METATYPE(PanelEditor)


class LockItemListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 Positionable* comp;
 QAction* checkBox;
 PanelEditor* editor;
public slots:
 /*public*/ void actionPerformed(JActionEvent* =0)override;
public:
 LockItemListener(PanelEditor* editor);
 ActionListener* init(Positionable* pos, QAction* cb);
 QObject* self() override {return (QObject*)this;}
};

//class RenameActionListener : public QObject, public ActionListener
//{
// Q_OBJECT
//    Q_INTERFACES(ActionListener)
// PanelEditor* editor;

//public slots:
// //@Override
// /*public*/ void actionPerformed(/*ActionEvent e*/);

// ActionListener* init(PanelEditor* e);
//};

class PEKeyListener : public KeyAdapter
{
  Q_OBJECT
  PanelEditor* editor;
 public:
  PEKeyListener(PanelEditor* editor) {this->editor = editor;}
 public slots:
  /*public*/ void keyReleased(QKeyEvent* /*a*/) override {
      if (editor->nextLabel->text() == ("")) {
          editor->labelAdd->setEnabled(false);
          editor->labelAdd->setToolTip(tr("This button will be active after you type text into the text box"));
      } else {
          editor->labelAdd->setEnabled(true);
          editor->labelAdd->setToolTip("");
      }
  }
  QObject* self() {return (QObject*)this;}
};

class PEWindowAdapter : public WindowListener
{
  Q_OBJECT
  PanelEditor* pe;
  QHash<QString, JFrameItem*> iconAdderFrames;

 public:
  PEWindowAdapter(QHash<QString, JFrameItem*> iconAdderFrames, PanelEditor* pe) {this->iconAdderFrames = iconAdderFrames; this->pe = pe;}
  void windowClosing(QCloseEvent*)
  {
   for (JFrameItem* frame : iconAdderFrames.values())
       frame->dispose();
  }
};

#endif // PANELEDITOR_H
