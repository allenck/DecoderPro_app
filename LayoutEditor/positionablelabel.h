#ifndef POSITIONALLABEL_H
#define POSITIONALLABEL_H

#include "jlabel.h"
#include <QFont>
#include <QGraphicsTextItem>
#include "logger.h"
#include "liblayouteditor_global.h"
#include "mygraphicsproxywidget.h"
#include "actionlistener.h"
#include "picklistmodel.h"
#include "windowlistener.h"
#include "positionable.h"

class JComponent;
class ItemPanel;
class PropertyChangeEvent;
class JFrameItem;
class IconAdder;
class NamedBean;
class NamedIcon;
class Positionable;
class PositionableLabel;
class Editor;
class PositionablePopupUtil;
class CoordinateEdit;
class AddPanelIconDialog;
class DisplayFrame;

class LIBLAYOUTEDITORSHARED_EXPORT PositionableLabel : public JLabel, public Positionable
{
 Q_OBJECT
 Q_INTERFACES(Positionable)
public:
    explicit PositionableLabel(QWidget *parent = 0);
    /*public*/ PositionableLabel(QString s, Editor* editor, Positionable *parent=0);
    /*public*/ PositionableLabel(NamedIcon* s, Editor* editor, Positionable *parent=0) ;
    /*public*/ /*final*/ bool isIcon();
    /*public*/ /*final*/ bool isText();
    /*public*/ /*final*/ bool isControl();
    /*public*/ Editor* getEditor() override;
    /*public*/ void setEditor(Editor* ed) override;
    /***************** Positionable methods **********************/

    /*public*/ void setPositionable(bool enabled) override;
    /*public*/ /*final*/ virtual bool isPositionable() override;
    /*public*/ void setEditable(bool enabled)  override;
    /*public*/ bool isEditable() override;

    /*public*/ void setViewCoordinates(bool enabled) override;
    /*public*/ bool getViewCoordinates() override;

    /*public*/ void setControlling(bool enabled) override;
    /*public*/ bool isControlling() override;

    /*public*/ void setHidden(bool hide) override;
    /*public*/ bool isHidden() override;
    /*public*/ void showHidden() override;
    /**
    * Delayed setDisplayLevel for DnD
    */
    /*public*/ void setLevel(int l) override;
    /*public*/ void setDisplayLevel(int l) override;
    /*public*/ int getDisplayLevel() override;
    /*public*/ void setShowToolTip(bool set) override;
    /*public*/ bool showToolTip();
    /*public*/ void setToolTip(QString tip) override;
    ///*public*/ ToolTip getTooltip();
    //QString getTooltip();
    /*public*/ QString getNameString() override;
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(Positionable* p) override;
    /*public*/ JComponent *getTextComponent() override;
    /**
     * When text is rotated or in an icon mode, the return of getText() may be
     * null or some other value
     * @return original defining text set by user
     */
    /*public*/ QString getUnRotatedText();
    //    /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ void updateSize()  override;
    /*public*/ int maxWidth() override;
    /*public*/ int maxHeight() override;
    /*public*/ int maxWidthTrue();
    /*public*/ int maxHeightTrue();
    /*public*/ bool isBackground();
    /*public*/ bool isRotated() ;
    /*public*/ void updateIcon(NamedIcon* s);
     virtual QFont getFont();
     void setFont(const QFont & font);
     /*public*/ QSize getSize() ;
     /*public*/ int getWidth()  override;
     int getHeight() override;
     void setIcon(NamedIcon* s);
     virtual bool updateScene() override;
     NamedIcon* getIcon();

     void setForeground(QColor c) override;
     QSize getPreferredSize();
     void setSize(int x, int y);
     /*public*/ bool storeItem() override;
     /*public*/ bool doViemMenu() override;
     /*public*/ void setPopupUtility(PositionablePopupUtil* tu) override;
     /*public*/ virtual NamedBean* getNamedBean() override;
     /*public*/ PositionablePopupUtil* getPopupUtility() override;
     /*public*/ void rotate(int deg) override;
     /*public*/ void setDegrees(int deg) ;
     /*public*/ virtual int getDegrees()  override;
     /**
      * Clean up when this object is no longer needed.  Should not
      * be called while the object is still displayed; see remove()
      */
     virtual /*public*/ void dispose();
     /**
      * Removes this object from display and persistance
      */
     /*public*/ void remove() override;
     /*protected*/ void setSuperText(QString text);
     //@Override
     /*public*/ void setText(QString text);
     /*public*/ bool isActive();
     bool isVisible() override;
     void setVisible(bool b) override;
     /*public*/ virtual void setOpaque(bool isOpaque) override;
     /*public*/ virtual void setScale(double s)  override;
     /*public*/ double getScale() override;
     /*public*/ void saveOpaque(bool set);
     /*public*/ bool getSaveOpaque() override;
     /*public*/ bool isOpaque() override;
     /**
     *  Call to a Positionable that has unique requirements
     * - e.g. RpsPositionIcon, SecurityElementIcon
     */
     /*public*/ virtual bool showPopUp(QMenu* popup)  override;
     /**
     * Rotate othogonally
     * return true if popup is set
     */
     /*public*/ virtual bool setRotateOrthogonalMenu(QMenu* popup) override;
     /*public*/ virtual bool setEditItemMenu(QMenu* popup) override;
     /*public*/ virtual bool setEditIconMenu(QMenu* popup) override;
     /*public*/ QColor getForeground() override;
     /*public*/ void setBackgroundColor(QColor color);
     /*public*/ QColor getBackground() override;

     /*public*/ virtual void doMousePressed(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual void doMouseReleased(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual void doMouseClicked(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual void doMouseDragged(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual void doMouseMoved(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual void doMouseEntered(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual void doMouseExited(QGraphicsSceneMouseEvent* event) override;
     /*public*/ virtual bool setRotateMenu(QMenu* popup) override;
     /*public*/ virtual bool setScaleMenu(QMenu* popup) override;
     /*public*/ virtual bool setTextEditMenu(QMenu* popup) override;
     /*public*/ QString getToolTip() override;
     /*public*/ virtual bool setDisableControlMenu(QMenu* popup) override;
     /*public*/ QRectF getBounds(QRectF = QRectF()) override;
     /*public*/ virtual void setBackground(QColor bg) override;
     MyGraphicsProxyWidget* widget;
     /* public*/ void setStyleSheet();
     /*public*/ void finishItemUpdate(DisplayFrame* paletteFrame, ItemPanel* itemPanel);
     QPointF getLocation();
     void setLocation(int x, int y);
     void setLocation(QPointF);
     int getX();
     int getY();
     QObject* self() {return (QObject*)this;}
     /*public*/ virtual QString getClassName();
     /*public*/ void mousePressEvent(QMouseEvent *ev) override;

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
 void initAfter();

private:
/*private*/ int _degrees;
//QFont _font;
void common(Positionable* parent);
/*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("PositionableLabel");/*private*/ bool needsRotate;
QColor _foreground;
QColor _background;
QSize _preferredSize, _size;
bool active;// = true;
/*private*/ NamedIcon* makeTextIcon(QString text);
bool IS_OPAQUE;
bool OPAQUE_SET;
/*private*/ bool _saveOpaque;
PositionablePopupUtil* _popupUtil = nullptr;
/************ Methods for Item Popups in Panel editor *************************/
JFrameItem* _iconEditorFrame;
//AddPanelIconDialog* _iconEditor;
IconAdder* _iconEditor;
//QGraphicsItem* item;
QString _tooltip;
Positionable* parent;
bool _bVisible;
DisplayFrame* _paletteFrame;
QFont _font;
int currRotation;
bool needsRotate;
int _x;
int _y;

friend class LinkingLabel;
friend class DragDecoratorLabel;
friend class ConvertDialog;

class AddIconActionListener : public ActionListener
{
 PositionableLabel* parent;
public:
 AddIconActionListener(PositionableLabel* parent)
 {
  this->parent = parent;
 }
 void actionPerformed(JActionEvent */*e*/ = 0)
 {
  parent->editIcon();
 }
};

private slots:
/*protected*/ virtual void rotateOrthogonal();
void on_disableControlMenu_toggled(bool bState); // [slot]
/*protected*/ virtual void edit();

protected:
/*protected*/ Editor* _editor = nullptr;

/*private*/ bool debug; //false;
/*protected*/ bool _icon; //false;
/*protected*/ bool _text; //false;
 friend class CoordinateEdit;
/*protected*/ bool _control; //false;
/*protected*/ NamedIcon* _namedIcon;
///*protected*/ ToolTip* _tooltip;
/*protected*/ bool _showTooltip;// =true;
/*protected*/ bool _editable; //true;
/*protected*/ bool _positionable; //true;
/*protected*/ bool _viewCoordinates; //true;
/*protected*/ bool _controlling; //true;
/*protected*/ bool _hidden; //false;
/*protected*/ int _displayLevel;

/*protected*/ QString _unRotatedText;
/*protected*/ bool _rotateText; //false;
/*protected*/ NamedIcon* cloneIcon(NamedIcon* icon, PositionableLabel* pos);
/**
 * Create an image of icon with text overlaid
 */
/*protected*/ NamedIcon* makeTextOverlaidIcon(QString text, NamedIcon* ic);
/*protected*/ void makeIconEditorFrame(QObject* pos, QString name, bool table, /*AddPanelIconDialog*/IconAdder* editor);
/*protected*/ void editIcon();
/*protected*/ DisplayFrame* makePaletteFrame(QString title);

 friend class LayoutEditor;
 friend class Editor;
 friend class LocoIcon;
 friend class PositionablePopupUtil;
 friend class MemoryIcon;
 friend class DisplayMemoryIcon;
 friend class LightIcon;
 friend class AnalogClock2Display;
 friend class PanelEditor;
 friend class PositionableLabelXml;
 friend class SignalHeadIcon;
 friend class MultiSensorIcon;
 friend class IndicatorTrackIcon;
 friend class PositionableJPanel;
 friend class SensorIcon;
 friend class SignalMastIcon;
 friend class TurnoutIcon;
 friend class SlipTurnoutIcon;
 friend class ReporterIcon;
 friend class IndicatorTurnoutIcon;
 friend class DPDragDecoratorLabel;
 friend class PositionablePropertiesUtil;
 friend class IEFWindowListener;
 friend class BlockContentsIcon;
 friend class ConvertFrame;
};
class IEFWindowListener : public WindowListener
{
 Q_OBJECT
 PositionableLabel* l;
public:
 IEFWindowListener(PositionableLabel* l);
 void windowClosing(QCloseEvent *e) override;
};

#endif // POSITIONALLABEL_H
