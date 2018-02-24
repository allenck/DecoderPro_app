#include "titledborder.h"
#include "insets.h"
#include "exceptions.h"

/**
 * A class which implements an arbitrary border
 * with the addition of a String title in a
 * specified position and justification.
 * <p>
 * If the border, font, or color property values are not
 * specified in the constructor or by invoking the appropriate
 * set methods, the property values will be defined by the current
 * look and feel, using the following property names in the
 * Defaults Table:
 * <ul>
 * <li>&quot;TitledBorder.border&quot;
 * <li>&quot;TitledBorder.font&quot;
 * <li>&quot;TitledBorder.titleColor&quot;
 * </ul>
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author David Kloba
 * @author Amy Fowler
 */
//@SuppressWarnings("serial")
///*public*/ class TitledBorder extends AbstractBorder
//{





// Space between the border and the component's edge
/*static*/ /*protected*/ /*final*/ int TitledBorder::EDGE_SPACING = 2;

// Space between the border and text
/*static*/ /*protected*/ /*final*/ int TitledBorder::TEXT_SPACING = 2;

// Horizontal inset of text that is left or right justified
/*static*/ /*protected*/ /*final*/ int TitledBorder::TEXT_INSET_H = 5;

/**
 * Creates a TitledBorder instance.
 *
 * @param title  the title the border should display
 */
/*public*/ TitledBorder::TitledBorder(QString title, QObject* parent) {
    common(NULL, title, LEADING, DEFAULT_POSITION, QFont(), QColor());
}

/**
 * Creates a TitledBorder instance with the specified border
 * and an empty title.
 *
 * @param border  the border
 */
/*public*/ TitledBorder::TitledBorder(Border* border, QObject* parent)
 : AbstractBorder(parent)
{
    common(border, "", LEADING, DEFAULT_POSITION, QFont(), QColor());
}

/**
 * Creates a TitledBorder instance with the specified border
 * and title.
 *
 * @param border  the border
 * @param title  the title the border should display
 */
/*public*/ TitledBorder::TitledBorder(Border* border, QString title, QObject* parent)
 : AbstractBorder(parent)
{
    common(border, title, LEADING, DEFAULT_POSITION, QFont(), QColor());
}

/**
 * Creates a TitledBorder instance with the specified border,
 * title, title-justification, and title-position.
 *
 * @param border  the border
 * @param title  the title the border should display
 * @param titleJustification the justification for the title
 * @param titlePosition the position for the title
 */
/*public*/ TitledBorder::TitledBorder(Border* border,
                    QString title,
                    int titleJustification,
                    int titlePosition, QObject* parent)
 : AbstractBorder(parent)
{
    common(border, title, titleJustification,
         titlePosition, QFont(), QColor());
}

/**
 * Creates a TitledBorder instance with the specified border,
 * title, title-justification, title-position, and title-font.
 *
 * @param border  the border
 * @param title  the title the border should display
 * @param titleJustification the justification for the title
 * @param titlePosition the position for the title
 * @param titleFont the font for rendering the title
 */
/*public*/ TitledBorder::TitledBorder(Border* border,
                    QString title,
                    int titleJustification,
                    int titlePosition,
                    QFont titleFont, QObject* parent)
{
    common(border, title, titleJustification,
         titlePosition, titleFont, QColor());
}

/**
 * Creates a TitledBorder instance with the specified border,
 * title, title-justification, title-position, title-font, and
 * title-color.
 *
 * @param border  the border
 * @param title  the title the border should display
 * @param titleJustification the justification for the title
 * @param titlePosition the position for the title
 * @param titleFont the font of the title
 * @param titleColor the color of the title
 */
//@ConstructorProperties({"border", "title", "titleJustification", "titlePosition", "titleFont", "titleColor"})
/*public*/ TitledBorder::TitledBorder(Border* border,
                    QString title,
                    int titleJustification,
                    int titlePosition,
                    QFont titleFont,
                    QColor titleColor, QObject* parent) : AbstractBorder(parent)
{
 common(border, title, titleJustification, titlePosition, titleFont, titleColor);
}

void TitledBorder::common(Border *border, QString title, int titleJustification, int titlePosition, QFont titleFont, QColor titleColor)
{
    this->title = title;
    this->border = border;
    this->titleFont = titleFont;
    this->titleColor = titleColor;

    setTitleJustification(titleJustification);
    setTitlePosition(titlePosition);

    this->label = new QLabel();
//    this->label->setOpaque(false);
//    this->label.putClientProperty(BasicHTML.propertyKey, NULL);
}
#if 0
/**
 * Paints the border for the specified component with the
 * specified position and size.
 * @param c the component for which this border is being painted
 * @param g the paint graphics
 * @param x the x position of the painted border
 * @param y the y position of the painted border
 * @param width the width of the painted border
 * @param height the height of the painted border
 */
/*public*/ void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
    Border border = getBorder();
    String title = getTitle();
    if ((title != NULL) && !title.isEmpty()) {
        int edge = (border instanceof TitledBorder) ? 0 : EDGE_SPACING;
        JLabel label = getLabel(c);
        Dimension size = label.getPreferredSize();
        Insets insets = getBorderInsets(border, c, new Insets(0, 0, 0, 0));

        int borderX = x + edge;
        int borderY = y + edge;
        int borderW = width - edge - edge;
        int borderH = height - edge - edge;

        int labelY = y;
        int labelH = size.height;
        int position = getPosition();
        switch (position) {
            case ABOVE_TOP:
                insets.left = 0;
                insets.right = 0;
                borderY += labelH - edge;
                borderH -= labelH - edge;
                break;
            case TOP:
                insets.top = edge + insets.top/2 - labelH/2;
                if (insets.top < edge) {
                    borderY -= insets.top;
                    borderH += insets.top;
                }
                else {
                    labelY += insets.top;
                }
                break;
            case BELOW_TOP:
                labelY += insets.top + edge;
                break;
            case ABOVE_BOTTOM:
                labelY += height - labelH - insets.bottom - edge;
                break;
            case BOTTOM:
                labelY += height - labelH;
                insets.bottom = edge + (insets.bottom - labelH) / 2;
                if (insets.bottom < edge) {
                    borderH += insets.bottom;
                }
                else {
                    labelY -= insets.bottom;
                }
                break;
            case BELOW_BOTTOM:
                insets.left = 0;
                insets.right = 0;
                labelY += height - labelH;
                borderH -= labelH - edge;
                break;
        }
        insets.left += edge + TEXT_INSET_H;
        insets.right += edge + TEXT_INSET_H;

        int labelX = x;
        int labelW = width - insets.left - insets.right;
        if (labelW > size.width) {
            labelW = size.width;
        }
        switch (getJustification(c)) {
            case LEFT:
                labelX += insets.left;
                break;
            case RIGHT:
                labelX += width - insets.right - labelW;
                break;
            case CENTER:
                labelX += (width - labelW) / 2;
                break;
        }

        if (border != NULL) {
            if ((position != TOP) && (position != BOTTOM)) {
                border.paintBorder(c, g, borderX, borderY, borderW, borderH);
            }
            else {
                Graphics g2 = g.create();
                if (g2 instanceof Graphics2D) {
                    Graphics2D g2d = (Graphics2D) g2;
                    Path2D path = new Path2D.Float();
                    path.append(new Rectangle(borderX, borderY, borderW, labelY - borderY), false);
                    path.append(new Rectangle(borderX, labelY, labelX - borderX - TEXT_SPACING, labelH), false);
                    path.append(new Rectangle(labelX + labelW + TEXT_SPACING, labelY, borderX - labelX + borderW - labelW - TEXT_SPACING, labelH), false);
                    path.append(new Rectangle(borderX, labelY + labelH, borderW, borderY - labelY + borderH - labelH), false);
                    g2d.clip(path);
                }
                border.paintBorder(c, g2, borderX, borderY, borderW, borderH);
                g2.dispose();
            }
        }
        g.translate(labelX, labelY);
        label.setSize(labelW, labelH);
        label.paint(g);
        g.translate(-labelX, -labelY);
    }
    else if (border != NULL) {
        border.paintBorder(c, g, x, y, width, height);
    }
}

/**
 * Reinitialize the insets parameter with this Border's current Insets.
 * @param c the component for which this border insets value applies
 * @param insets the object to be reinitialized
 */
/*public*/ Insets getBorderInsets(Component c, Insets insets) {
    Border border = getBorder();
    insets = getBorderInsets(border, c, insets);

    String title = getTitle();
    if ((title != NULL) && !title.isEmpty()) {
        int edge = (border instanceof TitledBorder) ? 0 : EDGE_SPACING;
        JLabel label = getLabel(c);
        Dimension size = label.getPreferredSize();

        switch (getPosition()) {
            case ABOVE_TOP:
                insets.top += size.height - edge;
                break;
            case TOP: {
                if (insets.top < size.height) {
                    insets.top = size.height - edge;
                }
                break;
            }
            case BELOW_TOP:
                insets.top += size.height;
                break;
            case ABOVE_BOTTOM:
                insets.bottom += size.height;
                break;
            case BOTTOM: {
                if (insets.bottom < size.height) {
                    insets.bottom = size.height - edge;
                }
                break;
            }
            case BELOW_BOTTOM:
                insets.bottom += size.height - edge;
                break;
        }
        insets.top += edge + TEXT_SPACING;
        insets.left += edge + TEXT_SPACING;
        insets.right += edge + TEXT_SPACING;
        insets.bottom += edge + TEXT_SPACING;
    }
    return insets;
}

/**
 * Returns whether or not the border is opaque.
 */
/*public*/ boolean isBorderOpaque() {
    return false;
}

/**
 * Returns the title of the titled border.
 *
 * @return the title of the titled border
 */
/*public*/ String getTitle() {
    return title;
}

/**
 * Returns the border of the titled border.
 *
 * @return the border of the titled border
 */
/*public*/ Border getBorder() {
    return border != NULL
            ? border
            : UIManager.getBorder("TitledBorder.border");
}

/**
 * Returns the title-position of the titled border.
 *
 * @return the title-position of the titled border
 */
/*public*/ int getTitlePosition() {
    return titlePosition;
}

/**
 * Returns the title-justification of the titled border.
 *
 * @return the title-justification of the titled border
 */
/*public*/ int getTitleJustification() {
    return titleJustification;
}

/**
 * Returns the title-font of the titled border.
 *
 * @return the title-font of the titled border
 */
/*public*/ Font getTitleFont() {
    return titleFont == NULL ? UIManager.getFont("TitledBorder.font") : titleFont;
}

/**
 * Returns the title-color of the titled border.
 *
 * @return the title-color of the titled border
 */
/*public*/ Color getTitleColor() {
    return titleColor == NULL ? UIManager.getColor("TitledBorder.titleColor") : titleColor;
}


// REMIND(aim): remove all or some of these set methods?

/**
 * Sets the title of the titled border.
 * @param title  the title for the border
 */
/*public*/ void setTitle(String title) {
    this->title = title;
}

/**
 * Sets the border of the titled border.
 * @param border the border
 */
/*public*/ void setBorder(Border border) {
    this->border = border;
}
#endif
/**
 * Sets the title-position of the titled border.
 * @param titlePosition the position for the border
 */
/*public*/ void TitledBorder::setTitlePosition(int titlePosition) {
    switch (titlePosition) {
        case ABOVE_TOP:
        case TOP:
        case BELOW_TOP:
        case ABOVE_BOTTOM:
        case BOTTOM:
        case BELOW_BOTTOM:
        case DEFAULT_POSITION:
            this->titlePosition = titlePosition;
            break;
        default:
            throw IllegalArgumentException(QString::number(titlePosition) +
                    " is not a valid title position.");
    }
}

/**
 * Sets the title-justification of the titled border.
 * @param titleJustification the justification for the border
 */
/*public*/ void TitledBorder::setTitleJustification(int titleJustification) {
    switch (titleJustification) {
        case DEFAULT_JUSTIFICATION:
        case LEFT:
        case CENTER:
        case RIGHT:
        case LEADING:
        case TRAILING:
            this->titleJustification = titleJustification;
            break;
        default:
            throw IllegalArgumentException(QString::number(titleJustification) +
                    " is not a valid title justification.");
    }
}
#if 0
/**
 * Sets the title-font of the titled border.
 * @param titleFont the font for the border title
 */
/*public*/ void setTitleFont(Font titleFont) {
    this->titleFont = titleFont;
}

/**
 * Sets the title-color of the titled border.
 * @param titleColor the color for the border title
 */
/*public*/ void setTitleColor(Color titleColor) {
    this->titleColor = titleColor;
}

/**
 * Returns the minimum dimensions this border requires
 * in order to fully display the border and title.
 * @param c the component where this border will be drawn
 * @return the {@code Dimension} object
 */
/*public*/ Dimension getMinimumSize(Component c) {
    Insets insets = getBorderInsets(c);
    Dimension minSize = new Dimension(insets.right+insets.left,
                                      insets.top+insets.bottom);
    String title = getTitle();
    if ((title != NULL) && !title.isEmpty()) {
        JLabel label = getLabel(c);
        Dimension size = label.getPreferredSize();

        int position = getPosition();
        if ((position != ABOVE_TOP) && (position != BELOW_BOTTOM)) {
            minSize.width += size.width;
        }
        else if (minSize.width < size.width) {
            minSize.width += size.width;
        }
    }
    return minSize;
}

/**
 * Returns the baseline.
 *
 * @throws NullPointerException {@inheritDoc}
 * @throws IllegalArgumentException {@inheritDoc}
 * @see javax.swing.JComponent#getBaseline(int, int)
 * @since 1.6
 */
/*public*/ int getBaseline(Component c, int width, int height) {
    if (c == NULL) {
        throw new NullPointerException("Must supply non-NULL component");
    }
    if (width < 0) {
        throw new IllegalArgumentException("Width must be >= 0");
    }
    if (height < 0) {
        throw new IllegalArgumentException("Height must be >= 0");
    }
    Border border = getBorder();
    String title = getTitle();
    if ((title != NULL) && !title.isEmpty()) {
        int edge = (border instanceof TitledBorder) ? 0 : EDGE_SPACING;
        JLabel label = getLabel(c);
        Dimension size = label.getPreferredSize();
        Insets insets = getBorderInsets(border, c, new Insets(0, 0, 0, 0));

        int baseline = label.getBaseline(size.width, size.height);
        switch (getPosition()) {
            case ABOVE_TOP:
                return baseline;
            case TOP:
                insets.top = edge + (insets.top - size.height) / 2;
                return (insets.top < edge)
                        ? baseline
                        : baseline + insets.top;
            case BELOW_TOP:
                return baseline + insets.top + edge;
            case ABOVE_BOTTOM:
                return baseline + height - size.height - insets.bottom - edge;
            case BOTTOM:
                insets.bottom = edge + (insets.bottom - size.height) / 2;
                return (insets.bottom < edge)
                        ? baseline + height - size.height
                        : baseline + height - size.height + insets.bottom;
            case BELOW_BOTTOM:
                return baseline + height - size.height;
        }
    }
    return -1;
}

/**
 * Returns an enum indicating how the baseline of the border
 * changes as the size changes.
 *
 * @throws NullPointerException {@inheritDoc}
 * @see javax.swing.JComponent#getBaseline(int, int)
 * @since 1.6
 */
/*public*/ Component.BaselineResizeBehavior getBaselineResizeBehavior(
        Component c) {
    super.getBaselineResizeBehavior(c);
    switch (getPosition()) {
        case TitledBorder.ABOVE_TOP:
        case TitledBorder.TOP:
        case TitledBorder.BELOW_TOP:
            return Component.BaselineResizeBehavior.CONSTANT_ASCENT;
        case TitledBorder.ABOVE_BOTTOM:
        case TitledBorder.BOTTOM:
        case TitledBorder.BELOW_BOTTOM:
            return JComponent.BaselineResizeBehavior.CONSTANT_DESCENT;
    }
    return Component.BaselineResizeBehavior.OTHER;
}

/*private*/ int getPosition() {
    int position = getTitlePosition();
    if (position != DEFAULT_POSITION) {
        return position;
    }
    Object value = UIManager.get("TitledBorder.position");
    if (value instanceof Integer) {
        int i = (Integer) value;
        if ((0 < i) && (i <= 6)) {
            return i;
        }
    }
    else if (value instanceof String) {
        String s = (String) value;
        if (s.equalsIgnoreCase("ABOVE_TOP")) {
            return ABOVE_TOP;
        }
        if (s.equalsIgnoreCase("TOP")) {
            return TOP;
        }
        if (s.equalsIgnoreCase("BELOW_TOP")) {
            return BELOW_TOP;
        }
        if (s.equalsIgnoreCase("ABOVE_BOTTOM")) {
            return ABOVE_BOTTOM;
        }
        if (s.equalsIgnoreCase("BOTTOM")) {
            return BOTTOM;
        }
        if (s.equalsIgnoreCase("BELOW_BOTTOM")) {
            return BELOW_BOTTOM;
        }
    }
    return TOP;
}

/*private*/ int getJustification(Component c) {
    int justification = getTitleJustification();
    if ((justification == LEADING) || (justification == DEFAULT_JUSTIFICATION)) {
        return c.getComponentOrientation().isLeftToRight() ? LEFT : RIGHT;
    }
    if (justification == TRAILING) {
        return c.getComponentOrientation().isLeftToRight() ? RIGHT : LEFT;
    }
    return justification;
}

/*protected*/ Font getFont(Component c) {
    Font font = getTitleFont();
    if (font != NULL) {
        return font;
    }
    if (c != NULL) {
        font = c.getFont();
        if (font != NULL) {
            return font;
        }
    }
    return new Font(Font.DIALOG, Font.PLAIN, 12);
}

/*private*/ Color getColor(Component c) {
    Color color = getTitleColor();
    if (color != NULL) {
        return color;
    }
    return (c != NULL)
            ? c.getForeground()
            : NULL;
}

/*private*/ JLabel getLabel(Component c) {
    this->label.setText(getTitle());
    this->label.setFont(getFont(c));
    this->label.setForeground(getColor(c));
    this->label.setComponentOrientation(c.getComponentOrientation());
    this->label.setEnabled(c.isEnabled());
    return this->label;
}

/*private*/ static Insets getBorderInsets(Border border, Component c, Insets insets) {
    if (border == NULL) {
        insets.set(0, 0, 0, 0);
    }
    else if (border instanceof AbstractBorder) {
        AbstractBorder ab = (AbstractBorder) border;
        insets = ab.getBorderInsets(c, insets);
    }
    else {
        Insets i = border.getBorderInsets(c);
        insets.set(i.top, i.left, i.bottom, i.right);
    }
    return insets;
}
#endif
