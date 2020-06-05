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
/*public*/ MatteBorder::MatteBorder(int top, int left, int bottom, int right, QColor matteColor, QWidget *parent)
  : EmptyBorder(top, left, bottom, right)
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
/*public*/ MatteBorder::MatteBorder(Insets* borderInsets, QColor matteColor, QWidget* parent)
  : EmptyBorder(borderInsets, parent)  {
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
/*public*/ MatteBorder::MatteBorder(int top, int left, int bottom, int right, QIcon tileIcon, QWidget* parent)
  : EmptyBorder(top, left, bottom, right, parent)
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
/*public*/ MatteBorder::MatteBorder(Insets* borderInsets, QIcon tileIcon, QWidget *parent)
  : EmptyBorder(borderInsets, parent)  {
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

/**
 * Paints the matte border.
 */
/*public*/ void MatteBorder::paintBorder(QWidget *c, /*QPainter g, */int x, int y, int width, int height) {
  QPainter  g(c);
    Insets* insets = getBorderInsets(c, new Insets());
    QPen pen = g.pen();
    QColor oldColor = pen.color();//g.getColor();
    g.translate(x, y);
#if 0
    // If the tileIcon failed loading, paint as gray.
    if (!tileIcon.isNull()) {
        color = (tileIcon.actualSize(QSize(64,64)).width() == -1) ? Qt::gray : QColor();
    }
#endif
    if (color.isValid()) {
        g.setPen(color);
        g.fillRect(0, 0, width - insets->right, insets->top, QBrush(color));
        g.fillRect(0, insets->top, insets->left, height - insets->top, QBrush(color));
        g.fillRect(insets->left, height - insets->bottom, width - insets->left, insets->bottom, QBrush(color));
        g.fillRect(width - insets->right, 0, insets->right, height - insets->bottom, QBrush(color));

    }
#if 0
    else if (!tileIcon.isNull()) {
        int tileW = tileIcon.actualSize(QSize(64,64)).width();
        int tileH = tileIcon.actualSize(QSize(64,64)).height();
        paintEdge(c, g, 0, 0, width - insets->right, insets->top, tileW, tileH);
        paintEdge(c, g, 0, insets->top, insets->left, height - insets->top, tileW, tileH);
        paintEdge(c, g, insets->left, height - insets->bottom, width - insets->left, insets->bottom, tileW, tileH);
        paintEdge(c, g, width - insets->right, 0, insets->right, height - insets->bottom, tileW, tileH);
    }
#endif
    g.translate(-x, -y);
    g.setPen(oldColor);

}

/*private*/ void MatteBorder::paintEdge(QWidget* c, /*QPainter g,*/ int x, int y, int width, int height, int tileW, int tileH) {
#if 0
    g = g.create(x, y, width, height);
    int sY = -(y % tileH);
    for (x = -(x % tileW); x < width; x += tileW) {
        for (y = sY; y < height; y += tileH) {
            this->tileIcon.paint(c, g, x, y);
        }
    }
    g.dispose();
#endif
}

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
    }
    else
    {
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


// void MatteBorder::paintEvent(QPaintEvent *event)
// {
//  QPainter* g = (QPainter*)this;
//  QRect r = event->rect();
//  paintBorder(this, g, r.x(), r.y(), r.width(), r.height());

// }
