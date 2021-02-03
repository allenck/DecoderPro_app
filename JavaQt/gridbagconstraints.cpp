#include "gridbagconstraints.h"

//GridBagConstraints::GridBagConstraints()
//{
//}
/**
 * The <code>GridBagConstraints</code> class specifies constraints
 * for components that are laid out using the
 * <code>GridBagLayout</code> class.
 *
 * @author Doug Stein
 * @author Bill Spitzak (orignial NeWS & OLIT implementation)
 * @see java.awt.GridBagLayout
 * @since JDK1.0
 */
// /*public*/ class GridBagConstraints implements Cloneable, java.io.Serializable {




/**
 * Creates a <code>GridBagConstraint</code> object with
 * all of its fields set to their default value.
 */
/*public*/ GridBagConstraints::GridBagConstraints (/*QObject* parent*/) //: QObject(parent)
{
    gridx = _RELATIVE;
    gridy = _RELATIVE;
    gridwidth = 1;
    gridheight = 1;

    weightx = 0;
    weighty = 0;
    anchor = 0;
    fill = NONE;

    insets = new Insets(0, 0, 0, 0);
    ipadx = 0;
    ipady = 0;
    gridx = gridy =0;
}

/**
 * Creates a <code>GridBagConstraints</code> object with
 * all of its fields set to the passed-in arguments.
 *
 * Note: Because the use of this constructor hinders readability
 * of source code, this constructor should only be used by
 * automatic source code generation tools.
 *
 * @param gridx     The initial gridx value.
 * @param gridy     The initial gridy value.
 * @param gridwidth The initial gridwidth value.
 * @param gridheight        The initial gridheight value.
 * @param weightx   The initial weightx value.
 * @param weighty   The initial weighty value.
 * @param anchor    The initial anchor value.
 * @param fill      The initial fill value.
 * @param insets    The initial insets value.
 * @param ipadx     The initial ipadx value.
 * @param ipady     The initial ipady value.
 *
 * @see java.awt.GridBagConstraints#gridx
 * @see java.awt.GridBagConstraints#gridy
 * @see java.awt.GridBagConstraints#gridwidth
 * @see java.awt.GridBagConstraints#gridheight
 * @see java.awt.GridBagConstraints#weightx
 * @see java.awt.GridBagConstraints#weighty
 * @see java.awt.GridBagConstraints#anchor
 * @see java.awt.GridBagConstraints#fill
 * @see java.awt.GridBagConstraints#insets
 * @see java.awt.GridBagConstraints#ipadx
 * @see java.awt.GridBagConstraints#ipady
 *
 * @since 1.2
 */
/*public*/ GridBagConstraints::GridBagConstraints(int gridx, int gridy,
                          int gridwidth, int gridheight,
                          double weightx, double weighty,
                          int anchor, int fill,
                          Insets* insets, int ipadx, int ipady) {
    this->gridx = gridx;
    this->gridy = gridy;
    this->gridwidth = gridwidth;
    this->gridheight = gridheight;
    this->fill = fill;
    this->ipadx = ipadx;
    this->ipady = ipady;
    this->insets = insets;
    this->anchor  = anchor;
    this->weightx = weightx;
    this->weighty = weighty;
}

/**
 * Creates a copy of this grid bag constraint.
 * @return     a copy of this grid bag constraint
 */
/*public*/ QObject* GridBagConstraints::clone () {
#if 0 // TODO:
    try {
        GridBagConstraints c = (GridBagConstraints)super.clone();
        c.insets = (Insets)insets.clone();
        return c;
    } catch (CloneNotSupportedException e) {
        // this shouldn't happen, since we are Cloneable
        throw new InternalError();
    }
#endif
 return NULL;
}

bool GridBagConstraints::isVerticallyResizable() {
    return (fill == BOTH || fill == VERTICAL);
}
int GridBagConstraints::rowSpan()
{
    if((fill == BOTH || fill == VERTICAL) && gridheight == REMAINDER)
     return -1;
    if(gridheight <=0) return 1;
    return gridheight;
}
int GridBagConstraints::colSpan()
{
    if((fill == BOTH || fill == HORIZONTAL) && gridwidth == REMAINDER)
     return -1;
    if(gridwidth <=0) return 1;
    return gridwidth;
}

Qt::Alignment GridBagConstraints::align()
{
 switch (anchor)
 {
  case NORTH:
   return Qt::AlignTop;
  case EAST:
   return Qt::AlignRight;
 case SOUTH:
  return Qt::AlignBottom;
 case WEST:
  return Qt::AlignLeft;
 case NORTHWEST:
  return Qt::AlignLeft | Qt::AlignTop;
 case NORTHEAST:
  return Qt::AlignRight | Qt::AlignTop;
 case SOUTHWEST:
  return Qt::AlignLeft | Qt::AlignBottom;
 case SOUTHEAST:
  return Qt::AlignRight | Qt::AlignBottom;
 case CENTER:
  return Qt::AlignCenter;
 default:
  return Qt::Alignment();
 }
}
