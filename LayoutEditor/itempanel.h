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
class ItemPanel : public QWidget
{
    Q_OBJECT
public:
    //explicit ItemPanel(QWidget *parent = 0);
    /*public*/ ItemPanel(DisplayFrame* parentFrame, QString  type, Editor* editor, QWidget *parent = 0);
    virtual /*public*/ void init();
 /*abstract*/ virtual /*public*/ void init(ActionListener* doneAction);
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
    virtual /*public*/ bool oktoUpdate();
    QVBoxLayout* thisLayout;
    /*public*/ QSize shellDimension(ItemPanel* panel);

signals:

public slots:
    void on_bgColorBox();

private:
    static Logger* log;
    static /*private*/ QStringList getNames(QString type);

protected:
    /*protected*/ DisplayFrame*  _paletteFrame;
    /*protected*/ QString    _itemType;
    /*protected*/ Editor*    _editor;
    /*protected*/ bool   _initialized = false;    // Has init() been run
    /*protected*/ bool   _update = false;    // Editing existing icon, do not allow icon dragging. set in init()
    /*protected*/ bool _suppressDragging;
    /*protected*/ JTextField* _linkName= new JTextField(30);
    static QColor _grayColor;// = QColor(235, 235, 235);
    static QColor _darkGrayColor;// = QColor(150, 150, 150);
    static /*protected*/ QVector<QColor> colorChoice;// = new Color[]{Color.white, _grayColor, _darkGrayColor}; // panel bg color picked up directly
    /**
     * Array of BufferedImage backgrounds loaded as background image in Preview (not shared across tabs)
     */
    /*protected*/ QVector<BufferedImage*>* _backgrounds = nullptr;
    /**
     * JComboBox to choose the above backgrounds
     */
    /*protected*/ QComboBox* _bgColorBox = nullptr;

    /*protected*/ virtual void closeDialogs();
    /*protected*/ void reset();
    /*protected*/ /*final*/ bool isUpdate();
    static /*protected*/ QMap<QString, NamedIcon*>* makeNewIconMap(QString type);
    virtual /*protected*/ void setEditor(Editor* ed);
    /*abstract*/ /*protected*/ virtual void setPreviewBg(int index);
    /*abstract*/ /*protected*/ virtual void updateBackground0(BufferedImage* im);
    /*protected*/ void initLinkPanel();
    /*protected*/ virtual QWidget* makeBgButtonPanel(ImagePanel* preview1, ImagePanel* preview2);
    ImagePanel* preview1 = nullptr;
    ImagePanel* preview2 = nullptr;
    /*protected*/ void updateBackgrounds(Editor* ed);
    static /*protected*/ QVector<BufferedImage*>* makeBackgrounds(QVector<BufferedImage*> *backgrounds, QColor panelBackground);
    /*protected*/ JPanel *makePreviewPanel(ImagePanel* panel1, ImagePanel* panel2);
    static /*protected*/ void checkIconMap(QString type, QMap<QString, NamedIcon*>* map);
    /*protected*/ DisplayFrame* getParentFrame();
    /*protected*/ void reSizeDisplay(bool isPalette, QSize oldDim, QSize totalDim);

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
};

#endif // ITEMPANEL_H
