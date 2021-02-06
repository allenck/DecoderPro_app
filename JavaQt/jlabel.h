#ifndef JLABEL_H
#define JLABEL_H

#include <QObject>
#include <QIcon>
#include <QMutex>
#include <QLabel>
#include "jcomponent.h"
#include "border.h"
#include "propertychangesupport.h"

class Logger;
class ImageIcon;
class JLabel : public QLabel, public JComponent
{
   Q_OBJECT
   Q_INTERFACES(JComponent)
public:
   //explicit JLabel(QWidget *parent = 0);
   /*public*/ static const int CENTER  = 0;
   /*public*/ static /*final*/ float LEFT_ALIGNMENT;// = 0.0f;
   /* Identifies the leading edge of text for use with left-to-right
    * and right-to-left languages. Used by buttons and labels.
    */
   /*public*/ static const int LEADING  = 10;
   /**
    * Identifies the trailing edge of text for use with left-to-right
    * and right-to-left languages. Used by buttons and labels.
    */
   /*public*/ static const int TRAILING = 11;
    /*public*/ static const int TOP     = 1;
    /**
     * Box-orientation constant used to specify the left side of a box.
     */
    /*public*/ static const int LEFT    = 2;
    /**
     * Box-orientation constant used to specify the bottom of a box.
     */
    /*public*/ static const int BOTTOM  = 3;
    /**
     * Box-orientation constant used to specify the right side of a box.
     */
    /*public*/ static const int RIGHT   = 4;

/**
 * Creates a <code>JLabel</code> instance with the specified
 * text, image, and horizontal alignment.
 * The label is centered vertically in its display area.
 * The text is on the trailing edge of the image.
 *
 * @param text  The text to be displayed by the label.
 * @param icon  The image to be displayed by the label.
 * @param horizontalAlignment  One of the following constants
 *           defined in <code>SwingConstants</code>:
 *           <code>LEFT</code>,
 *           <code>CENTER</code>,
 *           <code>RIGHT</code>,
 *           <code>LEADING</code> or
 *           <code>TRAILING</code>.
 */
/*public*/ JLabel(QString text, ImageIcon *icon, int horizontalAlignment, QWidget *parent = 0);
    /**
     * Creates a <code>JLabel</code> instance with the specified
     * text and horizontal alignment.
     * The label is centered vertically in its display area.
     *
     * @param text  The text to be displayed by the label.
     * @param horizontalAlignment  One of the following constants
     *           defined in <code>SwingConstants</code>:
     *           <code>LEFT</code>,
     *           <code>CENTER</code>,
     *           <code>RIGHT</code>,
     *           <code>LEADING</code> or
     *           <code>TRAILING</code>.
     */
    /*public*/ JLabel(QString text, int horizontalAlignment,QWidget *parent = 0);

/**
 * Creates a <code>JLabel</code> instance with the specified text.
 * The label is aligned against the leading edge of its display area,
 * and centered vertically.
 *
 * @param text  The text to be displayed by the label.
 */
/*public*/ JLabel(QString text,QWidget *parent = 0);
/**
 * Creates a <code>JLabel</code> instance with the specified
 * image and horizontal alignment.
 * The label is centered vertically in its display area.
 *
 * @param image  The image to be displayed by the label.
 * @param horizontalAlignment  One of the following constants
 *           defined in <code>SwingConstants</code>:
 *           <code>LEFT</code>,
 *           <code>CENTER</code>,
 *           <code>RIGHT</code>,
 *           <code>LEADING</code> or
 *           <code>TRAILING</code>.
 */
///*public*/ JLabel(QIcon* image, int horizontalAlignment,QWidget *parent = 0);
/**
 * Creates a <code>JLabel</code> instance with
 * no image and with an empty string for the title.
 * The label is centered vertically
 * in its display area.
 * The label's contents, once set, will be displayed on the leading edge
 * of the label's display area.
 */
/*public*/ JLabel(ImageIcon* image, QWidget *parent = 0);
/*public*/ JLabel(QWidget *parent = 0);
    /**
     * Creates a <code>JLabel</code> instance with the specified image.
     * The label is centered vertically and horizontally
     * in its display area.
     *
     * @param image  The image to be displayed by the label.
     */
//    /*public*/ JLabel(QIcon* image,QWidget *parent = 0);
/**
 * Returns the text string that the label displays.
 *
 * @return a QString
 * @see #setText
 */
/*public*/ QString getText();
/*public*/ void setText(QString text);
/**
 * Returns the graphic image (glyph, icon) that the label displays.
 *
 * @return an Icon
 * @see #setIcon
 */
/*public*/ ImageIcon* getIcon();
    /**
     * Defines the icon this component will display.  If
     * the value of icon is NULL, nothing is displayed.
     * <p>
     * The default value of this property is NULL.
     * <p>
     * This is a JavaBeans bound property.
     *
     * @see #setVerticalTextPosition
     * @see #setHorizontalTextPosition
     * @see #getIcon
     * @beaninfo
     *    preferred: true
     *        bound: true
     *    attribute: visualUpdate true
     *  description: The icon this component will display.
     */
    /*public*/ virtual void setIcon(ImageIcon *icon) ;
    /**
     * Returns the icon used by the label when it's disabled.
     * If no disabled icon has been set this will forward the call to
     * the look and feel to construct an appropriate disabled Icon.
     * <p>
     * Some look and feels might not render the disabled Icon, in which
     * case they will ignore this.
     *
     * @return the <code>disabledIcon</code> property
     * @see #setDisabledIcon
     * @see javax.swing.LookAndFeel#getDisabledIcon
     * @see ImageIcon
     */
    //@Transient
    /*public*/ ImageIcon* getDisabledIcon() ;
    /**
     * Set the icon to be displayed if this JLabel is "disabled"
     * (JLabel.setEnabled(false)).
     * <p>
     * The default value of this property is NULL.
     *
     * @param disabledIcon the Icon to display when the component is disabled
     * @see #getDisabledIcon
     * @see #setEnabled
     * @beaninfo
     *        bound: true
     *    attribute: visualUpdate true
     *  description: The icon to display if the label is disabled.
     */
    /*public*/ void setDisabledIcon(ImageIcon* disabledIcon);
    /**
     * Specify a keycode that indicates a mnemonic key.
     * This property is used when the label is part of a larger component.
     * If the labelFor property of the label is not NULL, the label will
     * call the requestFocus method of the component specified by the
     * labelFor property when the mnemonic is activated.
     *
     * @see #getLabelFor
     * @see #setLabelFor
     * @beaninfo
     *        bound: true
     *    attribute: visualUpdate true
     *  description: The mnemonic keycode.
     */
    /*public*/ void setDisplayedMnemonic(int key);
    /**
     * Specifies the displayedMnemonic as a char value.
     *
     * @param aChar  a char specifying the mnemonic to display
     * @see #setDisplayedMnemonic(int)
     */
    /*public*/ void setDisplayedMnemonic(char aChar);
    /**
     * Return the keycode that indicates a mnemonic key.
     * This property is used when the label is part of a larger component.
     * If the labelFor property of the label is not NULL, the label will
     * call the requestFocus method of the component specified by the
     * labelFor property when the mnemonic is activated.
     *
     * @return int value for the mnemonic key
     *
     * @see #getLabelFor
     * @see #setLabelFor
     */
    /*public*/ int getDisplayedMnemonic();
// /*public*/ QWidget* getLabelFor() {return labelFor;}
/*public*/ void setHorizontalAlignment(int alignment);

/*public*/ void setAlignmentX(float alignmentX);

    /**
     * Returns the alignment of the label's contents along the Y axis.
     *
     * @return   The value of the verticalAlignment property, one of the
     *           following constants defined in <code>SwingConstants</code>:
     *           <code>TOP</code>,
     *           <code>CENTER</code>, or
     *           <code>BOTTOM</code>.
     *
     * @see SwingConstants
     * @see #setVerticalAlignment
     */
    /*public*/ int getVerticalAlignment() ;
    /**
     * Sets the alignment of the label's contents along the Y axis.
     * <p>
     * The default value of this property is CENTER.
     *
     * @param alignment One of the following constants
     *           defined in <code>SwingConstants</code>:
     *           <code>TOP</code>,
     *           <code>CENTER</code> (the default), or
     *           <code>BOTTOM</code>.
     *
     * @see SwingConstants
     * @see #getVerticalAlignment
     * @beaninfo
     *        bound: true
     *         enum: TOP    SwingConstants.TOP
     *               CENTER SwingConstants.CENTER
     *               BOTTOM SwingConstants.BOTTOM
     *    attribute: visualUpdate true
     *  description: The alignment of the label's contents along the Y axis.
     */
    /*public*/ void setVerticalAlignment(int alignment) ;
    /**
     * Returns the alignment of the label's contents along the X axis.
     *
     * @return   The value of the horizontalAlignment property, one of the
     *           following constants defined in <code>SwingConstants</code>:
     *           <code>LEFT</code>,
     *           <code>CENTER</code>,
     *           <code>RIGHT</code>,
     *           <code>LEADING</code> or
     *           <code>TRAILING</code>.
     *
     * @see #setHorizontalAlignment
     * @see SwingConstants
     */
    /*public*/ int getHorizontalAlignment() ;
    void setLocation(double x, double y);
    void setLocation(int x, int y);
    virtual QPointF getLocation();

    void setSize(double x, double y);
//    int getX();
//    int getY();
    /**
     * Returns the horizontal position of the label's text,
     * relative to its image.
     *
     * @return   One of the following constants
     *           defined in <code>SwingConstants</code>:
     *           <code>LEFT</code>,
     *           <code>CENTER</code>,
     *           <code>RIGHT</code>,
     *           <code>LEADING</code> or
     *           <code>TRAILING</code>.
     *
     * @see SwingConstants
     */
    /*public*/ int getHorizontalTextPosition();
    /**
     * Sets the horizontal position of the label's text,
     * relative to its image.
     *
     * @param textPosition  One of the following constants
     *           defined in <code>SwingConstants</code>:
     *           <code>LEFT</code>,
     *           <code>CENTER</code>,
     *           <code>RIGHT</code>,
     *           <code>LEADING</code>, or
     *           <code>TRAILING</code> (the default).
     * @exception IllegalArgumentException
     *
     * @see SwingConstants
     * @beaninfo
     *       expert: true
     *        bound: true
     *         enum: LEFT     SwingConstants.LEFT
     *               CENTER   SwingConstants.CENTER
     *               RIGHT    SwingConstants.RIGHT
     *               LEADING  SwingConstants.LEADING
     *               TRAILING SwingConstants.TRAILING
     *    attribute: visualUpdate true
     *  description: The horizontal position of the label's text,
     *               relative to its image.
     */
    /*public*/ void setHorizontalTextPosition(int textPosition);
    virtual void setName(QString name);
    QString getName();
    /*public*/ void setBounds(int x, int y, int w, int h);
    /*public*/ QObject* jself() {return (QObject*)this;}
    /*public*/ bool isOpaque();
    /*public*/ QColor getBackground();
    /*public*/ void setBackground(QColor);
    QColor getForeground();
    /*public*/ void setForeground(QColor);

    /*public*/ QFont getFont();
    /*public*/ void setOpaque(bool);
    /*public*/ void setFont(QFont);
//    /*public*/ void setLabelFor(QWidget* labelFor) {this->labelFor = labelFor;}
    /*public*/ QFontMetrics getFontMetrics();
    /*public*/ void setBorder(Border* border) override {this->_border = border;}
    /*public*/ Border* getBorder() {return _border;}
    /*public*/ int getBaseline(int w, int h);

    PropertyChangeSupport* pcs = new PropertyChangeSupport(this);
    /*public*/ void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
    /*public*/ QWidget* getLabelFor();
    /*public*/ void setLabelFor(QWidget* c);
    /*public*/ void setEnabled(bool b) override {QLabel::setEnabled(b);}
    ///*public*/ void addComponentListener()
signals:
    
public slots:
private:
 void init();
 float alignmentX;
 bool isAlignmentXSet;
 /*private*/ int mnemonic;// = '\0';
 /*private*/ int mnemonicIndex;// = -1;

 /*private*/ QString _text;// = "";         // "" rather than null,  for BeanBox
/*private*/ ImageIcon* defaultIcon;// = NULL;
/*private*/ ImageIcon* disabledIcon;// = null;
/*private*/ bool disabledIconSet;// = false;

/*private*/ int verticalAlignment;// = CENTER;
/*private*/ int horizontalAlignment;// = LEADING;
/*private*/ int verticalTextPosition;// = CENTER;
/*private*/ int horizontalTextPosition;// = TRAILING;
/*private*/ int iconTextGap;// = 4;
/*private*/ static /*final*/ QString uiClassID;// = "LabelUI";
 QString name;
 QMutex* mutex;
 bool nameExplicitlySet;
static /*final*/ QString LABELED_BY_PROPERTY;// = "labeledBy";
static Logger* log;
 double _x, _y;
 double _w, _h;
 bool _opaque = false;
 QColor bc;
 Border* _border = nullptr;
 QWidget* labelFor = nullptr;

protected:
/*protected*/ int checkHorizontalKey(int key, QString message);
/**
 * Verify that key is a legal value for the
 * verticalAlignment or verticalTextPosition properties.
 *
 * @param key the property value to check
 * @param message the IllegalArgumentException detail message
 * @exception IllegalArgumentException if key isn't TOP, CENTER, or BOTTOM.
 * @see #setVerticalAlignment
 * @see #setVerticalTextPosition
 */
/*protected*/ int checkVerticalKey(int key, QString message);

friend class PositionableIcon;
friend class PositionableJPanel;

};

#endif // JLABEL_H
