#ifndef CIRCUITBUILDER_H
#define CIRCUITBUILDER_H

#include <QObject>
#include <QMenu>
#include "logger.h"
#include "actionlistener.h"
#include "jmrijframe.h"

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
    /*public*/ QList<PortalIcon*>* getPortalIcons();
 /*public*/ bool doMouseReleased(Positionable* selection, bool dragging);
 /*public*/ bool doMouseDragged(Positionable* selection, QGraphicsSceneMouseEvent* event);
 /*public*/ bool dragPortal();
 /*public*/ bool doMouseReleased(Positionable* selection, QGraphicsSceneMouseEvent* event);

signals:

public slots:
    void cancelButton_clicked();
    void doneButton_clicked();
    void showDoneButton_clicked();
private:
    static const int STRUT_SIZE = 10;
    void common();
    /*private*/ QMenu* _circuitMenu;
    /*private*/ QMenu* _todoMenu;

    // map track icon to OBlock to which it belongs
    /*private*/ QHash<Positionable*, OBlock*>* _iconMap;// = new QHash<Positionable*, OBlock*>();

    // map OBlock to List of icons that represent it
    /*private*/ QHash<OBlock*, QList<Positionable*>*>* _circuitMap;

    // list of track icons not belonging to an OBlock
    /*private*/ QList<Positionable*> _darkTrack;

    // list of OBlocks with no icons
    /*private*/ QList<OBlock*>* _bareBlock;

    // list of icons needing converting
    /*private*/ QList<Positionable*> _unconvertedTrack;

    // list of OBlocks whose icons need converting
    /*private*/ QList<OBlock*>* _convertBlock;

    // map of Portals without PortalIcons or misplaced icons
    /*private*/ QMap<QString, Portal*> _badPortalIcon;// = new HashMap<String, Portal>();

    // map of PortalIcons by portal name
    /*private*/ QHash<QString, PortalIcon*> _portalIconMap;

    // map of Portals by portal name
    /*private*/ QHash<QString, Portal*> _portalMap;

    // OBlock list to open edit frames
    /*private*/ PickListModel* _oblockModel;
    /*private*/ bool hasOBlocks;// = false;

//    // "Editing Frames" - Called from menu in Main Frame
   /*private*/ EditCircuitFrame* _editCircuitFrame;
    /*private*/ EditPortalFrame*  _editPortalFrame;
    /*private*/ EditCircuitPaths* _editPathsFrame;

    // list of icons making a circuit - used by editing frames to indicate block(s) being worked on
    /*private*/ QList<Positionable*>* _circuitIcons;      // Dark Blue

    /*private*/ JTextField* _sysNameBox;// = new JTextField();
    /*private*/ JTextField* _userNameBox;// = new JTextField();
    /*private*/ OBlock*  _currentBlock;
    /*private*/ JDialog* _dialog;
    Logger* log;
    /*private*/ void addIcon(OBlock* block, Positionable* pos);
    /*private*/ void makeToDoMenu();
    /*private*/ void checkCircuits();
    /*private*/ bool isUnconvertedTrack(Positionable* pos);
    IndicatorItemPanel* _trackPanel;
    IndicatorTOItemPanel* _trackTOPanel;
    PositionableLabel* _oldIcon;
    JmriJFrame* _convertFrame;     // must be modal dialog to halt convetIcons loop
    QDialog* _convertDialog;     // must be modal dialog to halt convetIcons loop
    /*private*/ bool editingOK();
    /*private*/ QList<Positionable*>* makeSelectionGroup(OBlock* block, bool showPort);
    /*private*/ void editCircuitDialog(QString title);
    /*private*/ QWidget* makeDoneButtonPanel(bool add);
    /*private*/ void addCircuitDialog();
    /*private*/ QWidget* makeSystemNamePanel();
    /*private*/ bool doAddAction();
    /*private*/ bool doOpenAction();
    /*private*/ void closeCircuitBuilder();
    /*private*/ void removePortalIcons();
    /*private*/ void convertIcon(Positionable* pos);
    /*private*/ void makePalettteFrame(QString title);
    /*private*/ void convertTO();
    /*private*/ void setIconGroup(OBlock* block, QList<Positionable*>* selections);
    /*private*/ void finishConvert(Positionable* pos);

    /*private*/ void convertSeg();
    /*private*/ void setPortalsPositionable(OBlock* block, bool set);
    EditPortalDirection* _editDirectionFrame;
    QList<Positionable*>* _saveSelectionGroup;
    /*private*/ void handleSelection(Positionable* selection, QGraphicsSceneMouseEvent* event);
    /*private*/ bool okPath(Positionable* pos, OBlock* block);
    /*private*/ bool okToAdd(Positionable* pos, OBlock* editBlock);
    /*private*/ Positionable* getSelection(QList<Positionable*>* tracks);


private slots:
    /*private*/ void errorCheck();
    /*private*/ void editCircuitError(QString sysName);
    /*private*/ void portalCircuitError(QString sysName);
    /*private*/ void makeCircuitMenu();
    void editCircuitItem_triggered();
    void editPortalItem_triggered();
    void editCircuitPaths_triggered();

protected:
    /*protected*/ QList <PortalIcon*>* _portalIcons;// = new QList<PortalIcon>();
    /*protected*/ ControlPanelEditor* _editor;
    /*protected*/ QMenu* makeMenu();
    /*protected*/ void addPortalIcon(PortalIcon* icon);
    /*protected*/ QList<Positionable*>* getCircuitIcons(OBlock* block);
    /*protected*/ bool doMouseClicked(QList<Positionable*>* selections, QGraphicsSceneMouseEvent* event);
    /*protected*/ bool saveSelectionGroup(QList<Positionable*>* selectionGroup);
    /*protected*/ void doMousePressed(QGraphicsSceneMouseEvent* event, Positionable* selection);
    /*protected*/ OBlock* getBlock(Positionable* pos);

     protected slots:
    /*protected*/ void editCircuit(QString title);
    /*protected*/ static QWidget* makeTextBoxPanel(bool vertical, JTextField* textField, QString label,
                                             bool editable, QString tooltip);
    /*protected*/ static QWidget* makeBoxPanel(bool vertical, JTextField* textField, QString label,QString tooltip);
    /*protected*/ static void doSize(QWidget* comp, int max, int min);
    /*protected*/ void editPortals(QString title);
    /*protected*/ void editCircuitPaths(QString title);
    /*protected*/ void checkCircuitFrame(OBlock* block);
    /*protected*/ void closeCircuitFrame();
    /*protected*/ void closePortalDirection(OBlock* block) ;
    /*private*/ bool iconsConverted(OBlock* block);
    /*private*/ void queryConvertIcons(OBlock* block);
    /*protected*/ void convertIcons(QList<Positionable*>* iconList);
    /*protected*/ void closePathFrame(OBlock* block);
    /*protected*/ void closePortalFrame(OBlock* block);
    /*protected*/ QList<Positionable*>* getCircuitGroup();
    /*protected*/ void editPortalDirection(QString title);
    /*protected*/ QHash<QString, PortalIcon*> getPortalIconMap() ;
    /*protected*/ Portal* getPortalByName(QString name);
    /*protected*/ void changePortalName(QString oldName, QString newName);
    /*protected*/ void removePortal(QString name);
    /*protected*/ bool isTrack(Positionable* pos);

protected slots:
    /*protected*/ void newCircuit();
    void OnIconNeeds1();
    void OnIconNeeds2();


 friend class ControlPanelEditor;
 friend class EditCircuitFrame;
 friend class TOPActionListener;
 friend class EditCircuitActionListener;
 friend class PortalCircuitActionListener;
 friend class EditCircuitPaths;
 friend class EditPortalFrame;
 friend class EditPortalDirection;
 friend class PortalIcon;

};
class TOPActionListener : public ActionListener
{
 Q_OBJECT

 CircuitBuilder* parent;
 bool bIsTO;
public:
 TOPActionListener(bool bIsTO, CircuitBuilder* parent);
public slots:
 void actionPerformed(ActionEvent *e = 0);
};
/*static*/ class convertFrame : public JmriJFrame {
    Q_OBJECT
    QDialog* _dialog;
    CircuitBuilder* parent;
public:
    convertFrame (QDialog* dialog, CircuitBuilder* parent) ;
    /*public*/ void pack();
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
 void actionPerformed(ActionEvent */*e*/ = 0)
 {
  QString sysName = command;
  parent-> editCircuitError(sysName);
 }
};
class PortalCircuitActionListener : public ActionListener
{
    Q_OBJECT
    CircuitBuilder* parent;
    QString command;
   public:
    PortalCircuitActionListener(QString command, CircuitBuilder* parent)
    {
     this->parent = parent;
    this->command = command;
    }
   public slots:
    void actionPerformed(ActionEvent */*e*/ = 0)
    {
     QString sysName = command;
     parent-> portalCircuitError(sysName);
    }

};

#endif // CIRCUITBUILDER_H
