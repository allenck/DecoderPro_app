#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <QObject>

class Positionable : /*public*/ QObject
{
    Q_OBJECT
public:
    //explicit Positionable(QObject *parent = 0);
    /**
     * Defines display objects.
     * <P>
     * These are capable of:
     * <UL>
     * <LI>Being positioned by being dragged around on the screen.
     * (See {@link #setPositionable})
     * <LI>Being hidden. (See {@link #setHidden})
     * <LI>Controlling the layout. (See {@link #setControlling})
     * </OL>
     * These are manipulated externally, for example by a
     * subclass of {@link Editor}.
     * They are generally not stored
     * directly as part of the state of the object, though they
     * could be, but as part of the state of the external control.
     *<p>
     * Instead of the usual MouseEvent handling methods, e.g mouseClicked(...),
     * Positionables have similar methods called doMouseClicked
     * invoked by the {@link Editor} subclass that contains
     * them, so the Editor can handle e.g. box selection, etc.
     *
     * @see PositionableJComponent
     * @see PositionableLabel
     * @author Bob Jacobsen Copyright (c) 2002
     * @author Pete Cressman Copyright (c) 2010
     * @version $Revision: 21256 $
     */
//    /*public*/ interface Positionable extends Cloneable  {
        /*public*/ virtual void setPositionable(bool enabled) =0;
        /*public*/ virtual bool isPositionable()=0;

        /*public*/ virtual void setEditable(bool enabled) =0;
        /*public*/ virtual bool isEditable() =0;

        /*public*/ virtual void setShowTooltip(bool set) =0;
        /*public*/ virtual bool showTooltip() =0;
        /*public*/ virtual void setTooltip(ToolTip tip) =0;
        /*public*/ virtual ToolTip getTooltip() =0;

        /*public*/ virtual void setViewCoordinates(bool enabled) =0;
        /*public*/ virtual bool getViewCoordinates() =0;

        /*public*/ virtual void setControlling(bool enabled) =0;
        /*public*/virtual  bool isControlling() =0;

        /*public*/ virtual void setHidden(bool enabled) =0;
        /*public*/ virtual bool isHidden() =0;
        /*public*/ virtual void showHidden() =0;

        /*public*/ int getDisplayLevel();
        /*public*/ void setDisplayLevel(int l);

        /*public*/ virtual Editor* getEditor();
        /*public*/ virtual void setEditor(Editor ed);
        /*public*/ void updateSize();
        /*public*/ virtual int maxWidth();
        /*public*/ virtual int maxHeight();

        /**
        * Make a deep copy of Positional object. Implementation should
        * create a new object and immediately pass the object to
        * finishClone() returning the result of finishClone().
        * i.e. implementation must be:
        * public Positionable deepClone() {
        *    Subtype t = new Subtype();
        *    return finishClone(t);
        * }
        */
        /*public*/ virtual Positionable* deepClone();
        /**
        * Finsh the deep Copy of a Positional object. Implementation should
        * make deep copies of the additional members of this sub class and
        * then pass Positionable p to super.finishClone().
        * i.e. implementation must terminate with statement
        * return super.finishClone(p);
        * See IndicatorTurnoutIcon extends TurnoutIcon extends PositionableLabel
        * for an example of how to continue deep cloning a chain of subclasses.
        */
        /*public*/virtual  Positionable* finishClone(Positionable* p);

        /** Methods to add popup menu items
        * return true if a popup item is set
        */
        /*public*/ virtual QString getNameString();
        /*public*/ virtual bool setRotateOrthogonalMenu(JPopupMenu popup);
        /*public*/ virtual bool setRotateMenu(JPopupMenu popup);
        /*public*/ virtual bool setScaleMenu(JPopupMenu popup);
        /*public*/ virtual bool setEditIconMenu(JPopupMenu popup);
        /*public*/ virtual bool setEditItemMenu(JPopupMenu popup);
        /*public*/ virtual bool setDisableControlMenu(JPopupMenu popup);
        /*public*/ virtual bool setTextEditMenu(JPopupMenu popup);

        /*public*/ virtual bool showPopUp(JPopupMenu popup);

        /*public*/ virtual void setScale(double s);
        /*public*/ virtual double getScale();
        /*public*/ void rotate(int deg);
        /*public*/ virtual int getDegrees();
        /*public*/ virtual bool getSaveOpaque();		// for rotated text
        /*public*/ virtual JComponent getTextComponent();

        /*public*/ virtual void remove();

        /**
         * Store a permanent copy of this Positionable
         * The editorXml will call this method to find out whether it
         * should store this Positionable item.
         * @return true if the Editor should store this in the configuration file
         * @return false if if the Editor should not store this object
         */
        /*public*/ virtual bool storeItem();
        /**
         * Use the 'Standard' presentation of the popup menu items.
         * The editor will call this method to find out whether it
         * should creates any popup viewing menu items.
         * @return true if Editor may add the standardpopup menu items
        */
        /*public*/ virtual bool doViemMenu();
        /*
        * Utility to handle Margins, Borders and other common popup items
        * @return null if these item do not apply
        */
        /*public*/ virtual PositionablePopupUtil getPopupUtility();
        /*public*/ virtual void setPopupUtility(PositionablePopupUtil tu);
        /*public*/ virtual NamedBean* getNamedBean();

        // Mouse-handling events.  See
        // Editor class for more information on how these are used.
        /*public*/ virtual void doMousePressed(MouseEvent event);
        /*public*/ virtual void doMouseReleased(MouseEvent event);
        /*public*/ virtual void doMouseClicked(MouseEvent event);
        /*public*/ virtual void doMouseDragged(MouseEvent event);
        /*public*/ virtual void doMouseMoved(MouseEvent event);
        /*public*/ virtual void doMouseEntered(MouseEvent event);
        /*public*/ virtual void doMouseExited(MouseEvent event);

        // The following are common for all JComponents
        /*public*/ virtual Rectangle getBounds(Rectangle r);
        /*public*/ virtual bool contains(int x, int y);
        /*public*/ virtual int getX();
        /*public*/ virtual int getY();
        /*public*/ virtual Point getLocation();
        /*public*/ virtual void setLocation(int x, int y);
        /*public*/ virtual void setLocation(Point p);
        /*public*/ virtual void setSize(int width, int height);
        /*public*/ virtual void setVisible(bool b);
        /*public*/ virtual int getWidth();
        /*public*/ virtual int getHeight();
        /*public*/ virtual Container getParent();
        /*public*/ virtual void setOpaque(bool isOpaque);
        /*public*/ virtual bool isOpaque();
        /*public*/ virtual void setBackground(Color bg);
        /*public*/ virtual QColor getBackground();
        /*public*/ virtual void setForeground(Color bg);
        /*public*/ virtual Color getForeground();
        /*public*/ virtual Font getFont();
        /*public*/ virtual void setBorder(Border border);
        /*public*/ virtual Dimension getPreferredSize();
        /*public*/ virtual void invalidate();
        /*public*/ virtual void repaint();
        /*public*/ virtual bool requestFocusInWindow();
signals:
    
/*public*/ slots:
    
};

#endif // POSITIONABLE_H
