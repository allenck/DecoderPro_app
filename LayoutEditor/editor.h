#ifndef EDITOR_H
#define EDITOR_H
#include "jmrijframe.h"
//#include <QMainWindow>
#include <QLineEdit>
#include "namedicon.h"
#include "positionable.h"
#include <QGraphicsView>
#include <QFormLayout>
#include "editscene.h"
#include "positionablelabel.h"
#include "signalmasticon.h"
#include "jdialog.h"
#include "actionlistener.h"
#include <QSpinBox>
#include "iconadder.h"
#include "spinnernumbermodel.h"
#include "flowlayout.h"

#if 0
class UrlErrorDialog : QDialog {
    QLineEdit* _urlField;
    CatalogPanel  _catalog;
    QString _badUrl;
    UrlErrorDialog(QString msg, QString url)
    {
        super(_targetFrame, Bundle.getMessage("BadIcon"), true);
        _badUrl = url;
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(new JLabel(java.text.MessageFormat.format(Bundle.getMessage("IconUrlError"), msg)));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt1")));
        panel.add(javax.swing.Box.createVerticalStrut(10));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt2")));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt3")));
        panel.add(new JLabel(Bundle.getMessage("UrlErrorPrompt4")));
        _urlField = new JTextField(url);
        _urlField.setDragEnabled(true);
        _urlField.setTransferHandler(new jmri.util.DnDQStringImportHandler());
        panel.add(_urlField);
        panel.add(makeDoneButtonPanel());
        _urlField.setToolTipText(Bundle.getMessage("TooltipFixUrl"));
        panel.setToolTipText(Bundle.getMessage("TooltipFixUrl"));
        _catalog = CatalogPanel.makeDefaultCatalog();
        _catalog.setToolTipText(Bundle.getMessage("ToolTipDragIconToText"));
        panel.add(_catalog);
        setContentPane(panel);
        setLocation(200, 100);
        pack();
        setVisible(true);
    }
    /*protected*/ JPanel makeDoneButtonPanel() {
        JPanel panel0 = new JPanel();
        panel0.setLayout(new FlowLayout());
        JButton doneButton = new JButton(Bundle.getMessage("ButtonContinue"));
        doneButton.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    _newIcon = NamedIcon.getIconByName(_urlField.getText());
                    if (_newIcon!=null) {
                        _urlMap.put(_badUrl, _urlField.getText());
                    }
                    dispose();
                }
        });
        doneButton.setToolTipText(Bundle.getMessage("TooltipContinue"));
        panel0.add(doneButton);

        JButton deleteButton = new JButton(Bundle.getMessage("ButtonDeleteIcon"));
        deleteButton.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    _delete = true;
                    dispose();
                }
        });
        panel0.add(deleteButton);
        deleteButton.setToolTipText(Bundle.getMessage("TooltipDelete"));

        JButton cancelButton = new JButton(Bundle.getMessage("ButtonIgnore"));
        cancelButton.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent a) {
                    _ignore = true;
                    dispose();
                }
        });
        panel0.add(cancelButton);
        cancelButton.setToolTipText(Bundle.getMessage("TooltipIgnore"));
        return panel0;
    }
};
static class ToolTipTimer : QTimer {
    ToolTip* tooltip;
    ToolTipTimer(int delay, ActionListener listener, ToolTip tip) {
        super(delay, listener);
        tooltip = tip;
    }
    ToolTip getTooltip() {
        return tooltip;
    }
};
/**
 *  Special internal class to allow drawing of layout to a JLayeredPane
 *  This is the 'target' pane where the layout is displayed
 */
/*public*/ class TargetPane : JLayeredPane
{
    int h = 100;
    int w = 150;
    /*public*/ TargetPane() {
        setLayout(null);
    }

    /*public*/ void setSize(int width, int height) {
//            if (_debug) log.debug("size now w="+width+", h="+height);
        this.h = height;
        this.w = width;
        super.setSize(width, height);
    }
    /*public*/ Dimension getSize() {
        return new Dimension(w,h);
    }
    /*public*/ Dimension getPreferredSize() {
        return new Dimension(w,h);
    }
    /*public*/ Dimension getMinimumSize() {
        return getPreferredSize();
    }
    /*public*/ Dimension getMaximumSize() {
        return getPreferredSize();
    }
    /*public*/ Component add(Component c, int i) {
        int hnew = Math.max(this.h, c.getLocation().y+c.getSize().height);
        int wnew = Math.max(this.w, c.getLocation().x+c.getSize().width);
        if (hnew>h || wnew>w) {
//                if (_debug) log.debug("size was "+w+","+h+" - i="+i);
            setSize(wnew,hnew);
        }
        return super.add(c, i);
    }
    /*public*/ void add(Component c, Object o) {
        super.add(c, o);
        int hnew = Math.max(h, c.getLocation().y+c.getSize().height);
        int wnew = Math.max(w, c.getLocation().x+c.getSize().width);
        if (hnew>h || wnew>w) {
//                if (_debug) log.debug("adding of "+c.getSize()+" with Object - i="+o);
            setSize(wnew,hnew);
        }
    }
#endif
#if 0

    /*public*/ void setBackgroundColor(Color col){
        setBackground(col);
        setOpaque(true);
    }

    /*public*/ void clearBackgroundColor(){
        setOpaque(false);
    }

    /*public*/ Color getBackgroundColor(){
        if (isOpaque())
            return getBackground();
        return null;
    }
};
#endif

class BlockContentsIcon;
class Class;
class CircuitBuilder;
class TrainIcon;
class JDialog;
class SpinnerNumberModel;
class MultiSensorIcon;
class LightIcon;
class ReporterIcon;
class MemoryIcon;
class MemorySpinnerIcon;
class MemoryInputIcon;
class SignalHeadIcon;
class TurnoutIcon;
class ActionListener;
class JFrameItem;
class IconAdder;
class DecoratorPanel;
class PositionableLabel;
class LocoIcon;
class RosterEntry;
class SensorIcon;
class RosterEntrySelectorPanel;
class Positionable;
class SignalMastIcon;
class LIBLAYOUTEDITORSHARED_EXPORT Editor : public JmriJFrame
{
 Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0);
    /*public*/ Editor(QString name, bool saveSize, bool savePosition, QWidget* parent=0);
    /*public*/ Editor(QString name, QWidget* parent);

    const /*public*/ static int BKG       = 1;
    const /*public*/ static int TEMP      = 2;
    const /*public*/ static int ICONS     = 3;
    const /*public*/ static int LABELS    = 4;
    const /*public*/ static int MEMORIES  = 5;
    const /*public*/ static int REPORTERS = 5;
    const /*public*/ static int SECURITY  = 6;
    const /*public*/ static int TURNOUTS  = 7;
    const /*public*/ static int LIGHTS    = 8;
    const /*public*/ static int SIGNALS   = 9;
    const /*public*/ static int SENSORS   = 10;
    const /*public*/ static int CLOCK     = 10;
    const /*public*/ static int MARKERS   = 10;
    const /*public*/ static int HANDLES   = 11;
    const /*public*/ static int NUM_LEVELS= 11;

    const /*public*/ static int SCROLL_NONE       = 0;
    const /*public*/ static int SCROLL_BOTH       = 1;
    const /*public*/ static int SCROLL_HORIZONTAL = 2;
    const /*public*/ static int SCROLL_VERTICAL   = 3;
    const /*public*/ static int OPTION_POSITION = 1;
    const /*public*/ static int OPTION_CONTROLS = 2;
    const /*public*/ static int OPTION_HIDDEN = 3;
    const /*public*/ static int OPTION_TOOLTIP= 4;
    /*final*/ /*public*/ static QColor HIGHLIGHT_COLOR;// =  QColor(204, 207, 88);

    //    const /*public*/ static int OPTION_COORDS = 5;
    /*public*/ void loadFailed();
    /*public*/ NamedIcon* loadFailed(QString msg, QString url);
    /*public*/ void disposeLoadData();
    /*public*/ bool loadOK();
    /*public*/ QList <Positionable*> getContents();
    /*public*/ void setDefaultToolTip(QString dtt);
//    /*public*/ const JComponent* getTargetPanel();
    /*public*/ JFrame* getTargetFrame();
    /*public*/ QColor getBackgroundColor();
    /*public*/ void setBackgroundColor(QColor col);
    /*public*/ void clearBackgroundColor();
    /**
     * Get/Set scale for TargetPane drawing
     */
    /*public*/ /*const*/ double getPaintScale();
//    static const int TOOLTIPSHOWDELAY = 1000; // msec
//    static const int TOOLTIPDISMISSDELAY = 4000;  // msec
    /**
    * Wait TOOLTIPSHOWDELAY then show tooltip.  Wait TOOLTIPDISMISSDELAY and disaappear
    */
//    /*public*/ void actionPerformed(ActionEvent event);
    /*public*/ void setAllEditable(bool state);
    // accessor routines for persistent information
    /*public*/ bool isEditable() ;
    /*public*/ void setUseGlobalFlag(bool set);
    /*public*/ virtual bool useGlobalFlag();
    /*public*/ bool getFlag(int whichOption, bool localFlag);
    /*public*/ void setGlobalSetsLocalFlag(bool set) ;
    /*public*/ void setAllPositionable(bool state) ;
    /*public*/ bool allPositionable();
    /*public*/ void setAllControlling(bool state) ;
    /*public*/ bool allControlling();
    /*public*/ void setShowHidden(bool state);
    /*public*/ bool showHidden();
    /*public*/ void setAllShowTooltip(bool state);
    /*public*/ bool showTooltip();
    /*public*/ void setShowCoordinates(bool state);
    /*public*/ bool showCoordinates();
    /*public*/ Q_DECL_DEPRECATED void setPanelMenu(bool state);
    /*public*/ void setPanelMenuVisible(bool state);
    /*public*/ bool isPanelMenuVisible();
    /*public*/ void setPositionableMenu(Positionable* p, QMenu* popup);
    /*public*/ bool setShowCoordinatesMenu(Positionable* p, QMenu* popup);
    /*public*/ bool setShowAlignmentMenu(Positionable* p, QMenu* popup);
    /*public*/ void setDisplayLevelMenu(Positionable* p, QMenu* popup);
    /*public*/ void setHiddenMenu(Positionable* p, QMenu* popup);
    /*public*/ void setRemoveMenu(Positionable* p, QMenu* popup);
    /*public*/ PositionableLabel* setUpBackground(QString name);
    /*public*/ void displayLevelChange(Positionable* l);
    /*public*/ TrainIcon* addTrainIcon (QString name);
    /*public*/ LocoIcon* addLocoIcon (QString name);
    /*public*/ void putLocoIcon(LocoIcon* l, QString name);
    /*public*/ virtual void putItem(Positionable* l);
    /*public*/ bool removeFromContents(Positionable* l);
    /*public*/ bool deletePanel();
    /*public*/ void dispose(bool clear);
    /*public*/ const static int VIEWPOPUPONLY = 0x00;
    /*public*/ const static int EDITPOPUPONLY = 0x01;
    /*public*/ const static int BOTHPOPUPS = 0x02;
    /*public*/ QGraphicsScene* getTargetPanel();
    //void setDirty() { bDirty = true;}
    void setDirty(bool bDirty=true) {this->bDirty = bDirty;}
    /*public*/ virtual void setTitle();
    /*public*/ void drawSelectRect(int x, int y);
    /*public*/ /*const*/ int getAnchorX();
    /*public*/ /*const*/ int getAnchorY();
    /*public*/ void setHighlightColor(QColor color);
    /*public*/ void setSelectGroupColor(QColor color);
    /*public*/ void setSelectRectColor(QColor color);
    /*public*/ void setSelectRectStroke(Qt::PenStyle stroke);
    /*public*/ void setDefaultColors();
    /*public*/ virtual void paint(QGraphicsScene* g);
    QString getName();
    void setName(QString name);
    QString getTitle();
    static const /*public*/ QStringList ICON_EDITORS;
    /*public*/ int frameLocationX;// = 0;
    /*public*/ int frameLocationY;// = 0;
    static const int DELTA;// = 20;
    /*public*/ static /*final*/ QString POSITIONABLE_FLAVOR;// = java.awt.datatransfer.DataFlavor.javaJVMLocalObjectMimeType +
//                   ";class=jmri.jmrit.display.Positionable";
    /*public*/ QRectF getSelectRect();
    /*public*/ IconAdder* getIconEditor(QString name);
    /*public*/ void setShowTooltipMenu(Positionable* p, QMenu* popup);
    /*synchronized*/ /*public*/ static QVector<Editor*> getEditors();
    //template<class T>
    /*synchronized*/ /*public*/ static /*<T extends Editor>*/ QList<Editor*> getEditors(/*@Nonnull*/ QString type);
    /*public*/ static Editor* getEditor(QString name);
    /*public*/ void setScroll(QString strState);
    /*public*/ QString getScrollable();

signals:
    
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent *);

private:
    /*private*/ bool _debug;// = false;
    /*private*/ bool _loadFailed;// = false;
    bool bDirty;

    bool showCloseInfoMessage;// = true;	//display info message when closing panel
    void commonInit();
    /*private*/ JFrame*      _targetFrame;
//    /*private*/ JScrollPane _panelScrollPane;
    // Option menu items
    /*private*/ bool _positionable;// = true;
    /*private*/ bool _controlLayout;// = true;
    /*private*/ bool _showHidden;// = true;
    /*private*/ bool _showTooltip;// = true;
    /*private*/ bool _globalSetsLocal;// = true;    // pre 2.9.6 behavior
    /*private*/ bool _useGlobalFlag;// = false;     // pre 2.9.6 behavior

//    /*private*/ ToolTip* _defaultToolTip;
    QString _defaultToolTip;
    //    /*private*/ ToolTip* _tooltip = null;
    QString _toolTip;
    NamedIcon* _newIcon;
    bool _ignore;// = false;
    bool _delete;
    QMap<QString, QString>* _urlMap;// = new QMap<QString, QString>();
    //ToolTipTimer* _tooltipTimer;
    QGraphicsView* editPanel;
    EditScene* _targetPanel;
    EditScene* editScene;
    QGraphicsItemGroup* _selectRectItemGroup;
    QString name;
    Logger* log;
    bool saveSize;
    bool savePosition;
    bool _showCoordinates;
    void closeEvent(QCloseEvent *);
    PositionableLabel* currItem;
    Positionable* saveP;
    /*private*/ int getNextBackgroundLeft();
    QFormLayout* formLayout;
    RosterEntrySelectorPanel* rosterBox;
    QPointF dLoc;
    QColor defaultTextColor;
    /*private*/ QColor _highlightColor;// =  QColor(204, 207, 88);
    /*private*/ QColor _selectGroupColor;// =  QColor(204, 207, 88);
    /*private*/ QColor _selectRectColor;// = QColor(Qt::red);
    Qt::PenStyle _selectRectStroke;// = Qt::DashLine;
    QGraphicsSceneMouseEvent* saveEvent;
    SpinnerNumberModel* _spinCols;// = new SpinnerNumberModel(3,1,100,1);
    /*private*/ CircuitBuilder* _circuitBuilder;
//    /*private*/ QList<Positionable*> _secondSelectionGroup;
    /*private*/ bool panelMenuIsVisible;// = true;
    /*private*/ static /*volatile*/ QVector<Editor*>* editors;// = new ArrayList<Editor>();

private slots:
  void On_lockItemAction_toggled(bool);
  void On_actionHidden_toggled(bool bState); // [slot]
  void On_rosterBoxSelectionChanged(QString propertyName,QObject* o,QObject* n);
  void On_textAttributesAction_triggered();
  void On_removeMenuAction_triggered();

 protected:
    /*protected*/ QVector <Positionable*>* _contents;// = new QVector<Positionable*>();
//    /*protected*/ JLayeredPane _targetPanel;
    /*protected*/ int _scrollState;// = SCROLL_NONE;
    /*protected*/ bool _editable;// = true;
    // mouse methods variables
    /*protected*/ int _lastX;
    /*protected*/ int _lastY;
//    BasicStroke DASHED_LINE = new BasicStroke(1f, BasicStroke.CAP_BUTT,
//                                    BasicStroke.JOIN_BEVEL,
//                                    10f, new float[] {10f, 10f}, 0f);

    /*protected*/ QRectF _selectRect;// = null;
    /*protected*/ QRectF _highlightcomponent;// = null;
    /*protected*/ bool _dragging;// = false;
    /*protected*/ QList <Positionable*>* _selectionGroup;// = NULL;  // items gathered inside fence

    /*protected*/ Positionable* _currentSelection;
    // Accessible to editor views
    /*protected*/ int xLoc;// = 0;     // x coord of selected Positionable
    /*protected*/ int yLoc;// = 0;     // y coord of selected Positionable
    /*protected*/ int _anchorX;     // x coord when mousePressed
    /*protected*/ int _anchorY;     // y coord when mousePressed

    //    /*private*/ bool delayedPopupTrigger = false; // Used to delay the request of a popup, on a mouse press as this may conflict with a drag event

    /*protected*/ double _paintScale;// = 1.0;   // scale for _targetPanel drawing

    /*protected*/ QColor defaultBackgroundColor;// = QColor(Qt::lightGray);
    /*protected*/ bool _pastePending;// = false;

    // map of icon editor frames (incl, icon editor) keyed by name
//    /*protected*/ QHash <QString, JFrameItem*> _iconEditorFrame = new QHash <QString, JFrameItem*>();
    /**
    * An Editor may or may not choose to use 'this' as its frame or
    * the interior class 'TargetPane' for its targetPanel
    */
    /*protected*/ void setTargetPanel(EditScene* targetPanel, JmriJFrame* frame);
    /*protected*/ void setTargetPanelSize(int w, int h);
    /*protected*/ QSizeF getTargetPanelSize();

//    /*protected*/ const JScrollPane* getPanelScrollPane();

//    ToolTipTimer* _tooltipTimer;
  /*protected*/ virtual void targetWindowClosing(bool save);
  /*abstract*/ /*protected*/ virtual void targetWindowClosingEvent(QCloseEvent* /*e*/) {}

  /*protected*/ LocoIcon* selectLoco(QString rosterEntryTitle);
  /*protected*/ LocoIcon* selectLoco(RosterEntry* entry);
  /*protected*/ PositionableLabel* addLabel(QString text);
  /*protected*/ void removeFromTarget(Positionable* l);
  /*protected*/ void moveItem(Positionable* p, int deltaX, int deltaY);
  /*protected*/ QList <Positionable*>* getSelectedItems(QGraphicsSceneMouseEvent* event);
  /*protected*/ QList <Positionable*>* getSelectedItems(QPointF pt);
  /*protected*/ void makeSelectionGroup(QGraphicsSceneMouseEvent* event);
  /*protected*/ void modifySelectionGroup(Positionable* selection, QGraphicsSceneMouseEvent* event);
  /*protected*/ bool setTextAttributes(Positionable* p, QMenu* popup);
  /*protected*/ /*const*/ void setPaintScale(double newScale);
  /*protected*/ void setToolTip(QString tt);
  /*protected*/ bool showAlignPopup(Positionable* p);
  /*protected*/ void setSelectionsAttributes(PositionablePopupUtil* util, Positionable* pos, bool isOpaque);
  /*protected*/ void setSelectionsHidden(bool enabled, Positionable* p);
  /*protected*/ void addToTarget(Positionable* l);
  /*protected*/ int getItemX(Positionable* p, int deltaX) ;
  /*protected*/ int getItemY(Positionable* p, int deltaY);
  /*protected*/ void setSelectionsRotation(int k, Positionable* p);
  /*protected*/ void addClock();
//  /*protected*/ void addRpsReporter();
  /*protected*/ void removeSelections(Positionable* p);
  /*protected*/ void setSelectionsScale(double s, Positionable* p);
  virtual void repaint();
  /*protected*/ void setAttributes(PositionablePopupUtil* newUtil, Positionable* p, bool isOpaque);
  /*protected*/ void setSelectionsDockingLocation(Positionable* p);
  /*protected*/ void dockSelections(Positionable* p);
  /*protected*/ QHash <QString, JFrameItem*>* _iconEditorFrame;// = new QHash <QString, JFrameItem*>();
  /*protected*/ Editor* changeView(QString className);
//  /*protected*/ void setSecondSelectionGroup(QList<Positionable*> list);
  /*abstract*/ /*protected*/ virtual void init(QString name);
  /*protected*/ void addRpsReporter();
  /*protected*/ void setScroll(int state);
  /*protected*/ BlockContentsIcon* putBlockContents();

  class SignalHeadActionListener : public ActionListener
  {
      Editor* editor;
  public:
      SignalHeadActionListener(Editor* editor) { this->editor = editor;}
   void actionPerformed(ActionEvent */*e*/= 0) { editor->putSignalHead();}
  };
  class SignalMastActionListener : public ActionListener
  {
      Editor* editor;
  public:
      SignalMastActionListener(Editor* editor) { this->editor = editor;}
   void actionPerformed(ActionEvent */*e*/= 0) { editor->putSignalMast();}
  };
  class MultisensorIconActionListener : public ActionListener
  {
      Editor* editor;
  public:
      MultisensorIconActionListener(Editor* editor) { this->editor = editor;}
   void actionPerformed(ActionEvent */*e*/= 0) { editor->addMultiSensor();}
  };
  class MemoryIconAdder : public IconAdder
  {
   private:
    Editor* editor;
    QPushButton* bSpin;// = new QPushButton(tr("Add Spinner"));
    QPushButton* bBox;// = new QPushButton(tr("Add InputBox"));
    QSpinBox* spinner;// = new QSpinBox(/*_spinCols*/);
  public:
    MemoryIconAdder(Editor* editor);

  protected:
    /*protected*/ void addAdditionalButtons(QWidget* p);

    /*public*/ void valueChanged(ListSelectionEvent* e = 0);
//   protected slots:
//    void spinAction() { editor->addMemorySpinner();}
  };

protected slots:
  /*protected*/ void locoMarkerFromInput();
  /*protected*/ void removeMarkers();
  void locoMarkerFromRoster();
  /*protected*/ JFrameItem* makeAddIconFrame(QString name, bool add, bool table, IconAdder* editor);
  /*protected*/ void addTextEditor();
  /*protected*/ void addRightTOEditor();
  /*protected*/ void addLeftTOEditor();
  /*protected*/ void addSlipTOEditor();
  /*protected*/ void addSensorEditor();
  /*protected*/ IconAdder* getSignalHeadEditor();
  /*protected*/ void addSignalHeadEditor();
  /*protected*/ void addSignalMastEditor();
  /*protected*/ void addMemoryEditor();
  /*protected*/ void addReporterEditor();
  /*protected*/ void addLightEditor();
  /*protected*/ void addBackgroundEditor();
  /*protected*/ JFrameItem* addMultiSensorEditor();
  /*protected*/ void addIconEditor();
  /*protected*/ SensorIcon* putSensor();
  void addTurnoutR();
  void addTurnoutL();
  /*protected*/ TurnoutIcon*  addTurnout(IconAdder* editor);
  void addSlip();
  /*protected*/ SignalHeadIcon* putSignalHead();
  /*protected*/ SignalMastIcon* putSignalMast();
  /*protected*/ MemoryIcon* putMemory();
  /*protected*/ MemorySpinnerIcon* addMemorySpinner();
  /*protected*/ MemoryInputIcon* addMemoryInputBox() ;
  /*protected*/ LightIcon* addLight() ;
  /*protected*/ ReporterIcon* addReporter();
  void putBackground();
  /*protected*/ Positionable* putIcon();
  /*public*/ MultiSensorIcon* addMultiSensor();
  virtual /*abstract*/ /*protected*/ void setNextLocation(Positionable* /*obj*/){}
  /*protected*/ bool setSelectionsPositionable(bool enabled, Positionable* p);
  virtual /*abstract*/ /*protected*/ void paintTargetPanel(QGraphicsScene* g);
  /*protected*/ void deselectSelectionGroup();


  friend class CoordinateEdit;
  friend class LayoutEditor;
  friend class LoadXml;
  friend class PanelEditor;
  friend class DisplayMemoryIcon;
  friend class SensorIcon;
  friend class TurnoutIcon;
  friend class PositionableLabel;
  friend class LightIcon;
  friend class ReporterIcon;
  friend class SignalHeadIcon;
  friend class SignalMastIcon;
  friend class AddPanelIconDialog;
  friend class MultiSensorIcon;
  friend class DockingActionListener;
  friend class DockMenuListener;
  friend class TextAttrDialog;
  friend class ControlPanelEditor;
  friend class PositionableJPanel;
  friend class LocoIcon;
  friend class PositionableIcon;
  friend class AddPanelIconActionListener;
  friend class IndicatorTurnoutIconXml;
  friend class IndicatorTrackIcon;
  friend class IndicatorTurnoutIcon;
  friend class PositionablePropertiesUtil;
  friend class PositionablePopupUtil;
  friend class PositionableShape;
  friend class LayoutEditorXml;
  friend class PositionablePolygon;
  friend class PolygonAction;

public:
  class AddRightTOActionListener : public ActionListener
  {
   Editor* parent;
public:
   AddRightTOActionListener(Editor* parent)
   {
    this->parent = parent;
   }
   void actionPerformed(ActionEvent *e = 0)
   {
    Q_UNUSED(e);
    parent->  addTurnoutR();
   }
  };
 class AddLeftTOActionListener : public ActionListener
 {
  Editor* parent;
 public:
  AddLeftTOActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  addTurnoutL();
  }
 };
 class AddSlipActionListener : public ActionListener
 {
  Editor* parent;
 public:
  AddSlipActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  addSlip();
  }
 };
 class AddReporterActionListener : public ActionListener
 {
  Editor* parent;
 public:
  AddReporterActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  addReporter();
  }
 };

 class AddLightActionListener : public ActionListener
 {
  Editor* parent;
 public:
  AddLightActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  addLight();
  }
 };
 class AddBackgoundActionListener : public ActionListener
 {
  Editor* parent;
 public:
  AddBackgoundActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  putBackground();
  }
 };
 class AddIconActionListener : public ActionListener
 {
  Editor* parent;
 public:
  AddIconActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  putIcon();
  }
 };
 class MemoryActionListener : public ActionListener
 {
  Editor* parent;
 public:
  MemoryActionListener(Editor*   parent)
  {
   this->parent = parent;
  }
  void actionPerformed(ActionEvent *e = 0)
  {
   Q_UNUSED(e);
   parent->  putMemory();
  }
 };
 friend class AddIconFrameWindowListener;
};
class TextAttributesActionListener : public QObject
{
 Q_OBJECT
 Positionable* comp;
 /*public*/ void actionPerformed();
 TextAttributesActionListener* init(Positionable* pos);

};
class TextAttrDialog : public JDialog {
    Q_OBJECT
    Positionable* _pos;
    DecoratorPanel* _decorator;
    Editor* editor;
public:
    TextAttrDialog(Positionable* p, QWidget* parent);
public slots:
    void doneButton_clicked();

protected:
    /*protected*/ QWidget* makeDoneButtonPanel();
    // map of icon editor frames (incl, icon editor) keyed by name

};
/*********************** Icon Editors utils ****************************/

/*public*/ /*static*/ class JFrameItem : public JmriJFrame
{
 Q_OBJECT
    IconAdder* _editor;
public:
    JFrameItem (QString name, IconAdder* editor, QWidget* parent = 0);
    /*public*/ IconAdder* getEditor();
    /*public*/ QString toString();
};
class SearchItemActionListener : public ActionListener
{
    Q_OBJECT
    IconAdder* ea;
public slots:
    /*public*/ void actionPerformed(ActionEvent *e = 0);
public:
    SearchItemActionListener* init(IconAdder* ed);
};

class EditItemActionListener : public ActionListener
{
 Q_OBJECT
 Editor* editor;
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = 0);
 EditItemActionListener* init(Editor* ed);
};

class AddPanelIconActionListener : public ActionListener
{
 Q_OBJECT
    Editor* parent;
public:
    AddPanelIconActionListener(Editor* parent);
    void actionPerformed(ActionEvent *e = 0);
};
class ShowToolTipActionListener : public ActionListener
{
 Q_OBJECT
 Editor* editor;
 Positionable* comp;
 bool isChecked;
public:
 ShowToolTipActionListener(Positionable* pos, bool isChecked, Editor* editor);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};

class AddIconFrameWindowListener : public WindowListener
{
 Q_OBJECT
 Editor* editor;
public:
 AddIconFrameWindowListener(Editor* editor);
 void windowClosing(QCloseEvent *e);
};

#endif // EDITOR_H
