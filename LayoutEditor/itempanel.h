#ifndef ITEMPANEL_H
#define ITEMPANEL_H

#include <QWidget>
#include "displayframe.h"
#include "imagepanel.h"
#include "jtextfield.h"

class QGroupBox;
class ActionListener;
class JPanel;
class JTextField;
class BufferedImage;
class QComboBox;
class QVBoxLayout;
class Editor;
class NamedIcon;
class ItemPanel : public JPanel
{
    Q_OBJECT
public:
    //explicit ItemPanel(QWidget *parent = 0);
    /*public*/ ItemPanel(JmriJFrame* parentFrame, QString  type, Editor* editor, QWidget *parent = 0);
    virtual /*public*/ void init();
 /*abstract*/ virtual /*public*/ void init(ActionListener* doneAction) {}
    static /*final*/ QStringList TURNOUT;// = {"TurnoutStateClosed", "TurnoutStateThrown",
//                                         "BeanStateInconsistent", "BeanStateUnknown"};
    static /*final*/ QStringList SENSOR;// = {"SensorStateActive", "SensorStateInactive",
//                                        "BeanStateInconsistent", "BeanStateUnknown"};
    static /*final*/ QStringList SIGNALHEAD;// = {"SignalHeadStateRed", "SignalHeadStateYellow",
//                                        "SignalHeadStateGreen", "SignalHeadStateDark",
//                                        "SignalHeadStateHeld", "SignalHeadStateLunar",
//                                        "SignalHeadStateFlashingRed", "SignalHeadStateFlashingYellow",
//                                        "SignalHeadStateFlashingGreen", "SignalHeadStateFlashingLunar"};
    static /*final*/ QStringList LIGHT;// = {"LightStateOff", "LightStateOn",
//                                       "BeanStateInconsistent", "BeanStateUnknown"};
    static /*final*/ QStringList MULTISENSOR;// = {"SensorStateInactive", "BeanStateInconsistent",
//                                             "BeanStateUnknown", "first", "second", "third"};

    static /*final*/ QStringList RPSREPORTER;// = {"active", "error"};
    static /*final*/ QStringList ICON;// = {"Icon"};
    static /*final*/ QStringList BACKGROUND;// = {"Background"};
    static /*final*/ QStringList INDICATOR_TRACK;// = {"ClearTrack", "OccupiedTrack", "AllocatedTrack",
//                                                "PositionTrack", "DontUseTrack", "ErrorTrack";
    static /*final*/ QStringList PORTAL;// = {PortalIcon.HIDDEN, PortalIcon.VISIBLE, PortalIcon.PATH,
//                PortalIcon.TO_ARROW, PortalIcon.FROM_ARROW};
    static QString redX;// = "resources/icons/misc/X-red.gif";
    QVBoxLayout* thisLayout;

signals:

public slots:
//    void on_bgColorBox();

private:
    static Logger* log;
    static /*private*/ QStringList getNames(QString type);

protected:
    /*protected*/ JmriJFrame* _paletteFrame = nullptr;
    /*protected*/ QString    _itemType;
    /*protected*/ Editor*    _editor = nullptr;
    /*protected*/ bool   _initialized = false;    // Has init() been run
    /*protected*/ bool   _update = false;    // Editing existing icon, do not allow icon dragging. set in init()
    /*protected*/ bool _suppressDragging = false;
    /*protected*/ JTextField* _linkName= new JTextField(30);
    /*protected*/ void initLinkPanel();
    /*protected*/ virtual void closeDialogs();
    /*protected*/ void reset();
    /*protected*/ /*final*/ bool isUpdate();
    static /*protected*/ QMap<QString, NamedIcon*>* makeNewIconMap(QString type);
    static /*protected*/ void checkIconMap(QString type, QMap<QString, NamedIcon*>* map);

friend class TIconDragJLabel;
friend class ItemDialog;
friend class IconDialog;
friend class FamilyItemPanel;
friend class TableItemPanel;
friend class IndicatorTOItemPanel;
friend class IndicatorItemPanel;
friend class IconItemPanel;
friend class IconDragJLabel;
friend class ItemPalette;
friend class MultiSensorIconDialog;
friend class PositionableLabel;
friend class DecoratorPanel;
friend class IndicatorTOIconDialog;
friend class BackgroundItemTable;
friend class BGIPColorDialog;
};

#endif // ITEMPANEL_H
