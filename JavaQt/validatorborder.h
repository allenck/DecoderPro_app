#ifndef VALIDATORBORDER_H
#define VALIDATORBORDER_H

#include "compoundborder.h"
#include "validation.h"
#include "jcomponent.h"

class ValidatorBorder : public CompoundBorder
{
 public:
  ValidatorBorder(Validation* vldtn, Border* border);

 private:
  /*private*/ /*final*/ Validation* validation = nullptr;
  /*private*/ QFont font;
  /*private*/ QFontMetrics getFontMetrics(QWidget* cmpnt);
 friend class VBAbstractBorder;
};

class VBAbstractBorder : public AbstractBorder
{
  ValidatorBorder* border;
 public:
  VBAbstractBorder(ValidatorBorder* border) {this->border = border;}
  /**
   * {@inheritDoc}
   */
  //@Override
  /*public*/ void paintBorder(QWidget* c, /*@Nonnull Graphics g,*/ int x, int y, int width, int /*height*/)
  {
   QPainter g(c);
   Insets* insets = border->outsideBorder->getBorderInsets(c);
   QFontMetrics metrics = border->getFontMetrics(c);
   int by = (c->height() / 2) + (metrics.ascent() / 2) - insets->top;
   int bw = qMax(2, insets->right); // border width
   int iw = metrics.size(Qt::TextSingleLine, border->validation->getIcon()).width(); // icon width
   int bx = x + width - (qRound((iw * 1.5f) + (bw * 1.5f))) + 2;
   g.translate(bx, by);
   //g.setColor(validation.getColor());
   g.setPen(border->validation->getColor());
   g.setFont(border->font);
   //if (g instanceof Graphics2D)
//   {
//       //Graphics2D g2d = (Graphics2D) g;
//       g2d.setRenderingHint(
//               RenderingHints.KEY_TEXT_ANTIALIASING,
//               RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
//       g2d.setRenderingHint(
//               RenderingHints.KEY_FRACTIONALMETRICS,
//               RenderingHints.VALUE_FRACTIONALMETRICS_ON);
//   }
   g.drawText( QPoint(x + (iw / 2), y), border->validation->getIcon());
  }

  /**
   * {@inheritDoc}
   */
  //@Override
  /*public*/ bool isBorderOpaque() {
      return false;
  }

  /**
   * {@inheritDoc}
   */
  //@Override
  /*public*/ Insets* getBorderInsets(QWidget* c, Insets* insets) {
      QFontMetrics metrics = border->getFontMetrics(c);
      int iw = metrics.size(Qt::TextSingleLine, border->validation->getIcon()).width(); // icon width
      insets->right = qRound(iw * 1.5f);
      return insets;
  }
};


#endif // VALIDATORBORDER_H
