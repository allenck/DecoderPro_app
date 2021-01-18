#ifndef CONTROLPANELEDITOR_H
#define CONTROLPANELEDITOR_H
#include "editor.h"
#include "liblayouteditor_global.h"
#include "colordialog.h"

class ShapeDrawer;
class PortalIcon;
class CircuitBuilder;
class LibTables;
class ItemPalette;
class LIBLAYOUTEDITORSHARED_EXPORT ControlPanelEditor : public Editor
{
    Q_OBJECT
public:
    explicit ControlPanelEditor(QWidget *parent = 0);
    ~ControlPanelEditor();
 ControlPanelEditor(const ControlPanelEditor& other) : Editor((QWidget*)other.parent()) {}
    /*public*/ bool _debug;
    /*public*/ ControlPanelEditor(QString name, QWidget *parent = 0);
    /*public*/ void setCopyMenu(Positionable* p, QMenu* popup);
    /*public*/ static /*final*/ QString POSITIONABLE_LIST_FLAVOR;// = java.awt.datatransfer.DataFlavor.javaJVMLocalObjectMimeType + ";class=jmri.jmrit.display.controlPanelEditor.ControlPanelEditor";


//    /*public*/ static final ResourceBundle rbcp = ResourceBundle.getBundle("jmri.jmrit.display.controlPanelEditor.ControlPanelBundle");

    // DnD
    //    /*public*/ static final String POSITIONABLE_LIST_FLAVOR = java.awt.datatransfer.DataFlavor.javaJVMLocalObjectMimeType +
    //               ";class=jmri.jmrit.display.controlPanelEditor.ControlPanelEditor";
    /*public*/ void initView();
    /*public*/ void setSelectionGroup(QList<Positionable *> *group);
    /*public*/ void resetEditor();
    /*public*/ QList <Positionable*>* getClipGroup();
    /*public*/ void setTitle();
    /*public*/ void loadComplete();
    /*public*/ void setDefaultPortalIcons(QMap<QString, NamedIcon *> *map);
    /*public*/ QMap<QString, NamedIcon *> *getPortalIconMap();
    /*public*/ bool getShapeSelect();
    /*public*/ void setShapeSelect(bool set);
    /*public*/ ShapeDrawer* getShapeDrawer();
    /*public*/ CircuitBuilder* getCircuitBuilder();
    /*public*/ void mouseEntered(QGraphicsSceneMouseEvent * event);
    /*public*/ void mouseExited(QGraphicsSceneMouseEvent * event);
    /*public*/ void keyPressEvent(QKeyEvent* e);
    /*public*/ void keyReleaseEvent(QKeyEvent* e);
    /*public*/ void setNextLocation(Positionable* obj);
    /*public*/ void setColorMenu(QMenu* popup, /*JComponent*/QWidget *pos, int type);
    /*public*/ QString getClassName();


signals:
    void selectionRect(QRectF, QGraphicsSceneMouseEvent*);

public slots:
 /*public*/ void setUseGlobalFlag(bool set); // SLOT
//    void onItemTableList();
    void actionCut();
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event) override;
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event) override;
    ///*public*/ void mouseDoubleClicked(QGraphicsSceneMouseEvent* event);
    /*public*/ void setAllEditable(bool edit) override;


private:
 /*private*/ QMenu* _editorMenu;
 /*private*/ QMenu* _markerMenu;
 /*private*/ QMenu* _warrantMenu;
 /*private*/ QMenu* _circuitMenu;
 /*private*/ QMenu* _drawMenu;
 /*private*/ CircuitBuilder* _circuitBuilder = nullptr;
 /*private*/ QList<Positionable*>* _secondSelectionGroup = nullptr;
 /*private*/ ShapeDrawer* _shapeDrawer;
 /*private*/ ItemPalette* _itemPalette = nullptr;
 /*private*/ bool _disableShapeSelection;
 /*private*/ bool _disablePortalSelection;// = true;		// only select PortalIcon in CircuitBuilder
 /*private*/ QAction* useGlobalFlagBox;// = new QAction(tr("Override individual Position & Control settings "));
 /*private*/ QAction* positionableBox;// = new QAction(tr("All panel items can be repositioned"),this);
 /*private*/ QAction* controllingBox;// = new QAction(tr("Panel items control layout"));
 /*private*/ QAction* showTooltipBox;// = new QAction(tr("Show tooltips for all items"),this);
 /*private*/ QAction* hiddenBox;// = new QAction(tr("Show all hidden items"), this);
 /*private*/ QAction* disableShapeSelect;// = new JCheckBoxMenuItem(Bundle.getMessage("disableShapeSelect"));
 /*private*/ QAction* scrollBoth;// = new JRadioButtonMenuItem(Bundle.getMessage("ScrollBoth"));
 /*private*/ QAction* scrollNone;// = new JRadioButtonMenuItem(Bundle.getMessage("ScrollNone"));
 /*private*/ QAction* scrollHorizontal;// = new JRadioButtonMenuItem(Bundle.getMessage("ScrollHorizontal"));
 /*private*/ QAction* scrollVertical;// = new JRadioButtonMenuItem(Bundle.getMessage("ScrollVertical"));

      Logger* log;
 int _fitX;// = 0;
 int _fitY;// = 0;
 /*private*/ void makeFileMenu();
 /*private*/ QMap<QString, NamedIcon*>* _portalIconMap;
 /*private*/ void makePortalIconMap();
 /*private*/ bool _regular;// = true;	// true when TO_ARROW shows entry into ToBlock
 /*private*/ bool _hide;// = false;	// true when arrow should NOT show entry into ToBlock
 void dragEnterEvent(QDragEnterEvent *);
 //void dropEvent(QDropEvent *);
 void dragMoveEvent(QDragMoveEvent *);
 qint64 _clickTime;
 void abortPasteItems();
 void pasteItems();
 LibTables* libTables;
 QPointF dragPos;
 QList <Positionable*>* _clipGroup;
 bool bPopupTrigger;
 DataFlavor* _positionableDataFlavor;
 DataFlavor* _positionableListDataFlavor;
 DataFlavor* _namedIconDataFlavor;
 /*private*/ qint64 _mouseDownTime = 0;
 /*private*/ bool _manualSelection = false;
 Positionable* _lastSelection;

private slots:
 /*private*/ void zoomRestore(); // SLOT
 /*private*/ void zoomToFit();
 void dropEvent(QGraphicsSceneDragDropEvent* e);
 /*private*/ void copyToClipboard();
 /*private*/ void pasteFromClipboard();
 void selectAllAction();
 void storeImageIndexAction();
 void deleteAction();
 void sceneChanged(QList<QRectF>);

protected:
 /*protected*/ QMenuBar* _menuBar;
 /*protected*/ void init(QString name);
 /*protected*/ QMenu* _editMenu;
 /*protected*/ QMenu* _fileMenu;
 /*protected*/ QMenu* _optionMenu;
 /*protected*/ QMenu* _iconMenu;
 /*protected*/ QMenu* _zoomMenu;
 /*protected*/ void makeDrawMenu();
 /*protected*/ void makeIconMenu();
 /*protected*/ void makeZoomMenu();
 /*protected*/ void makeMarkerMenu();
 /*protected*/ void makeOptionMenu();
 /*protected*/ void makeEditMenu();
 /*protected*/ void makeWarrantMenu(bool, bool );
/*protected*/ Positionable* getCurrentSelection(QGraphicsSceneMouseEvent* event);
/*protected*/ Positionable* getCopySelection(QGraphicsSceneMouseEvent* event);
/*protected*/ void makeCircuitMenu();
/*protected*/ void disableMenus();
/*protected*/ QList<Positionable*>* getSelectionGroup();
/*protected*/ void highlight(Positionable* pos);
/*protected*/ void copyItem(Positionable* p);
/*protected*/ void makeDataFlavors();
/*protected*/ NamedIcon* getPortalIcon(QString name);
/*protected*/ void paintTargetPanel(QGraphicsScene* g);
/*protected*/ void setSecondSelectionGroup(QList<Positionable*>* list);
/*protected*/ void targetWindowClosingEvent(QCloseEvent* e);
/*protected*/ void setSelectionsScale(double s, Positionable* p);
/*protected*/ void setSelectionsRotation(int k, Positionable* p);
/*protected*/ void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);

protected slots:
 /*protected*/ void makeCircuitMenu(bool edit);

friend class CircuitBuilder;
friend class EditCircuitFrame;
friend class DuplicateActionListener;
friend class EditPortalDirection;
friend class EditPortalFrame;
friend class CPEActionListener;
friend class IconDragJLabel;
friend class EditSignalFrame;
friend class ConvertDialog;
friend class EPIconDragJLabel;
};
Q_DECLARE_METATYPE(ControlPanelEditor)

class CPEditItemActionListener : public ActionListener
{
    Q_OBJECT
    ControlPanelEditor* panelEd;
public slots:
    /*public*/ void actionPerformed(JActionEvent* e = 0);
public:
    CPEditItemActionListener* init(ControlPanelEditor* pe);
};
class DuplicateActionListener : public ActionListener
{
 Q_OBJECT
 Positionable* comp;
 ControlPanelEditor* edit;
public slots:
    /*public*/ void actionPerformed(JActionEvent* e = 0);
public:
    DuplicateActionListener* init(Positionable* pos, ControlPanelEditor* edit);
};

class CPEEditListener : public ActionListener
{
  Q_OBJECT
 ControlPanelEditor* edit;
 int type;
 QWidget* pos;
public:
 CPEEditListener(int type, QWidget* pos, ControlPanelEditor* edit)
 {
  this->type = type;
  this->pos = pos;
  this->edit = edit;
 }
public slots:
 void actionPerformed() { new ColorDialog(edit, pos, type, nullptr);}
};


#endif // CONTROLPANELEDITOR_H
