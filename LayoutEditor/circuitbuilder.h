#ifndef CIRCUITBUILDER_H
#define CIRCUITBUILDER_H

#include <QObject>
#include <QMenu>
#include "logger.h"
#include "actionlistener.h"
#include "displayframe.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "listselectionevent.h"
#include "jmrijframe.h"
#include "jtable.h"
#include "jtextfield.h"

class NamedBean;
class PositionableIcon;
class EditFrame;
class convertFrame;
class QGraphicsSceneMouseEvent;
class EditPortalDirection;
class JDialog;
class EditCircuitPaths;
class EditPortalFrame;
class EditCircuitFrame;
class PositionableLabel;
class IndicatorTOItemPanel;
class IndicatorItemPanel;
class Portal;
class ControlPanelEditor;
class JTextField;
class PickListModel;
class Positionable;
class OBlock;
class PortalIcon;
class CircuitBuilder : public QObject
{
    Q_OBJECT
public:
    explicit CircuitBuilder(QObject *parent = 0);
    /*public*/ CircuitBuilder(ControlPanelEditor* ed, QObject *parent=0);
    ~CircuitBuilder();
    /*public*/ /*final*/ static QColor _editGroupColor;// = new Color(150, 150, 255);
    /*public*/ /*final*/ static QColor _pathColor;// = Color.green;
    /*public*/ /*final*/ static QColor _highlightColor;// = new Color(255, 100, 200);
 /*public*/ bool doMouseReleased(Positionable* selection, bool dragging);
 /*public*/ bool doMouseDragged(Positionable* selection, QGraphicsSceneMouseEvent* event);
 /*public*/ bool dragPortal();
 /*public*/ bool doMouseReleased(Positionable* selection, QGraphicsSceneMouseEvent* event);
 /*public*/ QString getClassName();

signals:

public slots:

private:
    static const int STRUT_SIZE = 10;
    void common();
    /*private*/ QMenu* _circuitMenu;
    /*private*/ QMenu* _todoMenu;

    // map track icon to OBlock to which it belongs
    /*private*/ QHash<Positionable*, OBlock*>* _iconMap = new QHash<Positionable*, OBlock*>();

    // map OBlock to List of icons that represent it
    /*private*/ QHash<OBlock*, QList<Positionable*>*>* _circuitMap = new QHash<OBlock*, QList<Positionable*>*>();

    // list of track icons not belonging to an OBlock
    /*private*/ QList<Positionable*> _darkTrack = QList<Positionable*>();

    // list of OBlocks with no icons
    /*private*/ QList<OBlock*>* _bareBlock= new QList<OBlock*>();

    // list of icons needing converting
    /*private*/ QList<Positionable*> _unconvertedTrack;

    // list of OBlocks whose icons need converting
    /*private*/ QList<OBlock*>* _convertBlock = new QList<OBlock*>();

    // list of Portals with no PortalIcon
    /*private*/ /*final*/ QList<Portal*> _noPortalIcon = QList<Portal*>();

    // list of OBlocks with no Portal
    /*private*/ /*final*/ QList<OBlock*> _noPortals = QList<OBlock*>();

    // list of OBlocks with no Path
    /*private*/ /*final*/ QList<OBlock*> _noPaths = QList<OBlock*>();

    // list of misplaced PortalIcons
    /*private*/ /*final*/ QList<PortalIcon*> _misplacedPortalIcon = QList<PortalIcon*>();

    // map of PortalIcons by portal. A Portal may have 2 icons to connect non-adjacent blocks
    /*private*/ /*final*/ QMap<Portal*, QList<PortalIcon*>*> _portalIconMap = QMap<Portal*, QList<PortalIcon*>*>();

    // map of SignalMastIcon or SignalHeadicon by Mast name
    /*private*/ /*final*/ QHash<NamedBean*, QList<PositionableIcon*>* > _signalIconMap = QHash<NamedBean*, QList<PositionableIcon*>* >();

    // list of SignalMastIcon and SignalHeadicon not protecting a block
    /*private*/ /*final*/ QList<PositionableIcon*> _unattachedMastIcon = QList<PositionableIcon*> ();

    // map SignalMasts and SignalHeads to the Portal where it is configured
    /*private*/ QHash<NamedBean*, Portal*> _signalMap = QHash<NamedBean*, Portal*>();

    /*private*/ bool _hasIndicatorTrackIcons;
    /*private*/ bool _hasPortalIcons;
    /*private*/ bool _hasMastIcons;

    // OBlock list to open edit frames
    /*private*/ PickListModel* _oblockModel= nullptr;
    /*private*/ JTable* _blockTable = nullptr;
    JmriJFrame* _cbFrame = nullptr;

//    /*private*/ bool hasOBlocks;// = false;

//    // "Editing Frames" - Called from menu in Main Frame
    /*private*/ EditCircuitFrame* _editCircuitFrame = nullptr;
    /*private*/ EditPortalFrame*  _editPortalFrame = nullptr;
    /*private*/ EditCircuitPaths* _editPathsFrame = nullptr;

    // list of icons making a circuit - used by editing frames to indicate block(s) being worked on
    /*private*/ QList<Positionable*>* _circuitIcons = nullptr;      // Dark Blue

    /*private*/ JTextField* _sysNameBox = new JTextField();
    /*private*/ JTextField* _userNameBox = new JTextField();

    // "Editing Frames" - Called from menu in Main Frame
    /*private*/ EditFrame* _editFrame = nullptr;

    /*private*/ OBlock*  _currentBlock = nullptr;
    /*private*/ JDialog* _dialog = nullptr;
    static Logger* log;
    /*private*/ void addIcon(OBlock* block, Positionable* pos);
    /*private*/ void makeToDoMenu();
    /*private*/ void checkCircuits();
    /*private*/ bool isUnconvertedTrack(Positionable* pos);
    IndicatorItemPanel* _trackPanel = nullptr;
    IndicatorTOItemPanel* _trackTOPanel = nullptr;
    PositionableLabel* _oldIcon = nullptr;
    convertFrame* _convertFrame = nullptr;     // must be modal dialog to halt convetIcons loop
    JDialog* _convertDialog = nullptr;     // must be modal dialog to halt convetIcons loop
    /*private*/ bool editingOK();
    /*private*/ QList<Positionable *> *makeSelectionGroup(OBlock* block, bool showPortal);
    /*private*/ void editCircuitDialog(QString title);
    /*private*/ JPanel *makeDoneButtonPanel();
    /*private*/ bool doOpenAction();
    /*private*/ void closeCircuitBuilder(OBlock *block);
    /*private*/ void setIconGroup(OBlock* block);
    /*private*/ void selectPrompt();
    /*private*/ void setPortalsPositionable(OBlock* block, bool set);
    EditPortalDirection* _editDirectionFrame;
    QList<Positionable*>* _saveSelectionGroup;
    /*private*/ void handleSelection(Positionable* selection, QGraphicsSceneMouseEvent* event);
    /*private*/ bool okToAdd(Positionable* pos, OBlock* editBlock);
    /*private*/ Positionable* getSelection(QList<Positionable*>* tracks);
    enum TYPES
    {
    NONE = 0,
    OBLOCK = 1,
    PORTAL = 2,
    OPATH = 3,
    ARROW = 4,
    _SIGNAL = 5
    };
    /*private*/ void makeNoOBlockMenu();
    /*private*/ void makeCircuitMenu();
    /*private*/ void setUpEditCircuit();

private slots:
    /*private*/ void editCircuitError(QString sysName);

protected:
    /*protected*/ QList <PortalIcon*>* _portalIcons;// = new QList<PortalIcon>();
    /*protected*/ ControlPanelEditor* _editor;
    /*protected*/ QMenu* makeMenu();
    /*protected*/ QList<Positionable*>* getCircuitIcons(OBlock* block);
    /*protected*/ QList<PortalIcon *>* getPortalIconMap(/*@Nonnull*/ Portal* portal);
    /*protected*/ bool doMouseClicked(QList<Positionable*>* selections, QGraphicsSceneMouseEvent* event);
    /*protected*/ bool saveSelectionGroup(QList<Positionable*>* selectionGroup);
    /*protected*/ void doMousePressed(QGraphicsSceneMouseEvent* event, Positionable* selection);
//    /*protected*/ void convertIcons(QList<Positionable*>* iconList);

     protected slots:
    /*protected*/ void editCircuit(QString title, bool fromMenu);
    /*protected*/ static JPanel *makeTextBoxPanel(bool vertical, JTextField* textField, QString label,
                                             bool editable, QString tooltip);
    ///*protected*/ static JPanel* makeBoxPanel(bool vertical, JTextField* textField, QString label);
    /*protected*/ static void doSize(QWidget* comp, int max, int min);
    /*protected*/ void editPortals(QString title, bool fromMenu);
    /*protected*/ void editCircuitPaths(QString title, bool fromMenu);
//    /*protected*/ void closePortalDirection(OBlock* block) ;
//    /*protected*/ QHash<QString, PortalIcon*> getPortalIconMap() ;
    /*protected*/ bool isTrack(Positionable* pos);

    /*protected*/ QString checkForPortals(/*@Nonnull*/ OBlock* block, QString key);
    /*protected*/ QString checkForPortalIcons(/*@Nonnull*/ OBlock* block, QString key);
    /*protected*/ QString checkForTrackIcons(/*@Nonnull*/ OBlock* block, QString key);
    /*protected*/ void openCBWindow();
    /*protected*/ void closeCBWindow();
    /*protected*/ static JPanel* makeBoxPanel(bool vertical, JTextField *textField, QString label,
            QString tooltip);
    /*protected*/ void editSignalFrame(QString title, bool fromMenu);
    /*protected*/ EditFrame* getEditFrame();
    /*protected*/ void editPortalError(OBlock* block, Portal* portal, PortalIcon* icon);
    /*protected*/ void setCurrentBlock(OBlock* b);
    /*protected*/ void hidePortalIcons();
    /*protected*/ QList<PositionableIcon *> *getSignalIconMap(/*@Nonnull*/ NamedBean* mast);
    /*protected*/ Portal* getSignalPortal(/*@Nonnull*/ NamedBean* mast);
    /*protected*/ void putSignalPortal(/*@Nonnull*/ NamedBean* mast, Portal* portal);
    /*protected*/ void removeBlock(OBlock* block);
    /*protected*/ void deletePortalIcon(PortalIcon* icon);
    /*protected*/ bool queryConvertTrackIcons(/*@Nonnull*/ OBlock* block, QString key);
    /*protected*/ void editPortalDirection(QString title, bool fromMenu);

protected slots:
    /*protected*/ void newCircuit();
    /*protected*/ bool iconIntersectsBlock(Positionable* icon, OBlock* block);
    /*protected*/ void editPortalError(QString name);


 friend class ControlPanelEditor;
 friend class EditCircuitFrame;
 friend class TOPActionListener;
 friend class EditCircuitActionListener;
 friend class PortalCircuitActionListener;
 friend class EditCircuitPaths;
 friend class EditPortalFrame;
 friend class EditPortalDirection;
 friend class PortalIcon;
 friend class ConvertFrame;
 friend class CBFrame;
 friend class IconDragJLabel;
 friend class EditFrame;
 friend class EditSignalFrame;
 friend class LengthPanel;
 friend class ConvertDialog;
 friend class EPIconDragJLabel;
 friend class CircuitBuilderTest;
};


class EditCircuitActionListener : public ActionListener
{
 Q_OBJECT
 CircuitBuilder* parent;
 QString command;
public:
 EditCircuitActionListener(QString command, CircuitBuilder* parent)
 {
  this->parent = parent;
 this->command = command;
 }
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0)
 {
  QString sysName = command;
  parent-> editCircuitError(sysName);
 }
};


class CBFrame : public JmriJFrame //, public ListSelectionListener
{
 Q_OBJECT
 QButtonGroup* _buttonGroup = new QButtonGroup();
 int _which = 0;
 QRadioButton* _newCircuitButton = makeButton("newCircuitItem", CircuitBuilder::NONE);
 CircuitBuilder *cb;
public:
 CBFrame(QString title, CircuitBuilder *cb);
 /*public*/ void dispose()override;
 QString getClassName() {cb->getClassName();}
public slots:
 /*public*/ void valueChanged(ListSelectionEvent* e);
private:
 /*private*/ void setCurrentBlock();
 QRadioButton* makeButton(QString title, int which);
};

#if 0
/*static*/ class convertFrame : public JmriJFrame {
Q_OBJECT
    /**
     *
     */
    ///*private*/ static /*final*/ long serialVersionUID = -6547026117570145767L;
    JDialog* _dialog;
public:
    convertFrame(JDialog* dialog) ;

    /*public*/ void pack();
    QString getClassName() {return "convertFrame";}
};
#endif
#endif // CIRCUITBUILDER_H
