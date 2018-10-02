#ifndef ITEMPANEL_H
#define ITEMPANEL_H

#include <QWidget>
#include "displayframe.h"

class QVBoxLayout;
class Editor;
class NamedIcon;
class ItemPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit ItemPanel(QWidget *parent = 0);
    /*public*/ ItemPanel(DisplayFrame* parentFrame, QString  type, QString family, Editor* editor, QWidget *parent = 0);
    virtual /*public*/ void init();
    /*public*/ QString getFamilyName();
    static /*final*/ QStringList TURNOUT;// = {"TurnoutStateClosed", "TurnoutStateThrown",
//                                         "BeanStateInconsistent", "BeanStateUnknown"};
    static /*final*/ QStringList SENSOR;// = {"SensorStateActive", "SensorStateInactive",
//                                        "BeanStateInconsistent", "BeanStateUnknown"};
    static /*final*/ QStringList _SIGNAL;// = {"SignalHeadStateRed", "SignalHeadStateYellow",
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
    /*public*/ void dispose();

signals:

public slots:
private:
    QVBoxLayout* thisLayout;
protected:
    /*protected*/ JmriJFrame*  _paletteFrame;
    /*protected*/ QString    _itemType;
    /*protected*/ QString    _family;
    /*protected*/ Editor*    _editor;
    /*protected*/ bool   _update;// = false;    // Editing existing icon, do not allow icon dragging. set in init()
    /*protected*/ bool   _initialized;// = false;    // Has init() been run
    /*protected*/ void initIconFamiliesPanel();
    /*protected*/ void addIconsToPanel(QHash<QString, NamedIcon*>* iconMap);
    /*protected*/ void setFamily(QString family);
    /*protected*/ void removeIconFamiliesPanel();
    /*protected*/ void removeIconMap(QString family);
    /*protected*/ virtual void closeDialogs() {}
    /*protected*/ void reset();
    /*protected*/ void updateFamiliesPanel();
    /*protected*/ /*final*/ bool isUpdate();
    static /*protected*/ QHash<QString, NamedIcon*>* makeNewIconMap(QString type);
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
};

#endif // ITEMPANEL_H
