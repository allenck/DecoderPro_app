#include "matteborder.h"

//MatteBorder::MatteBorder()
//{

//}
#if 0
/**
 * A class which provides a matte-like border of either a solid color
 * or a tiled icon.
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
 * @author Amy Fowler
 */
@SuppressWarnings("serial")
public class MatteBorder extends EmptyBorder
{
#endif
/**
 * Creates a matte border with the specified insets and color.
 * @param top the top inset of the border
 * @param left the left inset of the border
 * @param bottom the bottom inset of the border
 * @param right the right inset of the border
 * @param matteColor the color rendered for the border
 */
/*public*/ MatteBorder::MatteBorder(int top, int left, int bottom, int right, QColor matteColor, QObject* parent) : EmptyBorder(top, left, bottom, right)
 {
    //super(top, left, bottom, right);
    this->color = matteColor;
}

/**
 * Creates a matte border with the specified insets and color.
 * @param borderInsets the insets of the border
 * @param matteColor the color rendered for the border
 * @since 1.3
 */
/*public*/ MatteBorder::MatteBorder(Insets* borderInsets, QColor matteColor, QObject* parent) : EmptyBorder(borderInsets, parent)  {
    //super(borderInsets);
    this->color = matteColor;
}

/**
 * Creates a matte border with the specified insets and tile icon.
 * @param top the top inset of the border
 * @param left the left inset of the border
 * @param bottom the bottom inset of the border
 * @param right the right inset of the border
 * @param tileIcon the icon to be used for tiling the border
 */
/*public*/ MatteBorder::MatteBorder(int top, int left, int bottom, int right, QIcon tileIcon, QObject* parent)   : EmptyBorder(top, left, bottom, right, parent)
 {
   // super(top, left, bottom, right);
    this->tileIcon = tileIcon;
}

/**
 * Creates a matte border with the specified insets and tile icon.
 * @param borderInsets the insets of the border
 * @param tileIcon the icon to be used for tiling the border
 * @since 1.3
 */
/*public*/ MatteBorder::MatteBorder(Insets* borderInsets, QIcon tileIcon, QObject* parent) : EmptyBorder(borderInsets, parent)  {
   //super(borderInsets);
    this->tileIcon = tileIcon;
}

/**
 * Creates a matte border with the specified tile icon.  The
 * insets will be calculated dynamically based on the size of
 * the tile icon, where the top and bottom will be equal to the
 * tile icon's height, and the left and right will be equal to
 * the tile icon's width.
 * @param tileIcon the icon to be used for tiling the border
 */
/*public*/ MatteBorder::MatteBorder(QIcon tileIcon, QObject* parent) : EmptyBorder(-1,-1,-1,-1)   {
    //this(-1,-1,-1,-1, tileIcon);
  this->top = -1;
  this->bottom = -1;
  this->left = -1;
  this->right = -1;
  this->tileIcon = tileIcon;
}
#if 0
/**
 * Paints the matte border.
 */
public void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
    Insets insets = getBorderInsets(c);
    Color oldColor = g.getColor();
    g.translate(x, y);

    // If the tileIcon failed loading, paint as gray.
    if (tileIcon != NULL) {
        color = (tileIcon.getIconWidth() == -1) ? Color.gray : NULL;
    }

    if (color != NULL) {
        g.setColor(color);
        g.fillRect(0, 0, width - insets->right, insets->top);
        g.fillRect(0, insets->top, insets->left, height - insets->top);
        g.fillRect(insets->left, height - insets->bottom, width - insets->left, insets->bottom);
        g.fillRect(width - insets->right, 0, insets->right, height - insets->bottom);

    } else if (tileIcon != NULL) {
        int tileW = tileIcon.getIconWidth();
        int tileH = tileIcon.getIconHeight();
        paintEdge(c, g, 0, 0, width - insets->right, insets->top, tileW, tileH);
        paintEdge(c, g, 0, insets->top, insets->left, height - insets->top, tileW, tileH);
        paintEdge(c, g, insets->left, height - insets->bottom, width - insets->left, insets->bottom, tileW, tileH);
        paintEdge(c, g, width - insets->right, 0, insets->right, height - insets->bottom, tileW, tileH);
    }
    g.translate(-x, -y);
    g.setColor(oldColor);

}

private void paintEdge(Component c, Graphics g, int x, int y, int width, int height, int tileW, int tileH) {
    g = g.create(x, y, width, height);
    int sY = -(y % tileH);
    for (x = -(x % tileW); x < width; x += tileW) {
        for (y = sY; y < height; y += tileH) {
            this.tileIcon.paintIcon(c, g, x, y);
        }
    }
    g.dispose();
}
#endif
/**
 * Reinitialize the insets parameter with this Border's current Insets.
 * @param c the component for which this border insets value applies
 * @param insets the object to be reinitialized
 * @since 1.3
 */
/*public*/ Insets* MatteBorder::getBorderInsets(QWidget* c, Insets* insets) {
    return computeInsets(insets);
}

/**
 * Returns the insets of the border.
 * @since 1.3
 */
/*public*/ Insets* MatteBorder::getBorderInsets() {
    return computeInsets(new Insets(0,0,0,0));
}

/* should be protected once api changes area allowed */
/*private*/ Insets* MatteBorder::computeInsets(Insets* insets) {
    if (!tileIcon.isNull()  && top == -1 && bottom == -1 &&
        left == -1 && right == -1) {
        int w = tileIcon.actualSize(QSize(64,64)).width();
        int h = tileIcon.actualSize(QSize(64,64)).height();
        insets->top = h;
        insets->right = w;
        insets->bottom = h;
        insets->left = w;
    } else {
        insets->left = left;
        insets->top = top;
        insets->right = right;
        insets->bottom = bottom;
    }
    return insets;
}

/**
 * Returns the color used for tiling the border or NULL
 * if a tile icon is being used.
 * @since 1.3
 */
/*public*/ QColor MatteBorder::getMatteColor() {
    return color;
}

/**
 * Returns the icon used for tiling the border or NULL
 * if a solid color is being used.
 * @since 1.3
 */
/*public*/ QIcon MatteBorder::getTileIcon() {
    return tileIcon;
}

/**
 * Returns whether or not the border is opaque.
 */
/*public*/ bool MatteBorder::isBorderOpaque() {
    // If a tileIcon is set, then it may contain transparent bits
    return !color.isValid();
}

