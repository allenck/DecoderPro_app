#include "drawsquares.h"
#include "loggerfactory.h"
#include <QColor>
#include "bufferedimage.h"

DrawSquares::DrawSquares(QObject *parent) : QObject(parent)
{

}
/**
 * Common utility to draw colored rectangular Image.
 *
 * @author Egbert Broerse copyright (c) 2017
 */
//public class DrawSquares {

/**
 * Produce a grid of contrasting squares. Ideally the width and height match
 * the parent frame size.
 *
 * @param width  image width in pixels
 * @param height image height in pixels
 * @param dim    length of sides of squares in pixels
 * @param color1 background color
 * @param color2 contrasting fill color
 * @return the image with a grid of squares
 * @see jmri.jmrit.catalog.PreviewDialog#setupPanel()
 */
/*public*/ /*static*/ BufferedImage* DrawSquares::getImage(int width, int height, int dim, QColor color1, QColor color2) {
    QColor sqColor = QColor(235, 235, 235); // light gray
    QColor bgColor = QColor(Qt::white);
    BufferedImage* result;
    int w = 500;
    int h = 500;
    if (width > 0) {
        w = width;
    }
    if (height > 0) {
        h = height;
    }
    if (color1.isValid()) {
        bgColor = color1;
    }
    if (color2.isValid()) {
        sqColor = color2;
    }
    // paint alternate squares
    result = new BufferedImage(w, h, QImage::Format_Mono);//(w, h, BufferedImage::TYPE_INT_RGB);
//    Graphics2D g2d = result->createGraphics();
//    g2d.setColor(bgColor);
//    g2d.fillRect(0, 0, w, h); // plain rect background
//    if (sqColor != bgColor) {
//        g2d.setColor(sqColor);
//        for (int j = 0; j <= (w / dim); j++) {
//            for (int k = 0; k <= (h / dim); k++) {
//                if ((j + k) % 2 == 0) { // skip every other square
//                    g2d.fillRect(j * dim, k * dim, dim, dim); // gray squares
//                }
//            }
//        }
//    }
//    g2d.dispose();
    result->setColorCount(2);
    result->setColor(0, qRgba(bgColor.red(), bgColor.green(), bgColor.blue(), 255));
    result->setColor(1, qRgba(sqColor.red(), sqColor.green(), sqColor.blue(), 255));
    result->fill(0);
    if (sqColor != bgColor)
    {
     for (int j = 0; j <= (w / dim); j++)
     {
      for (int k = 0; k <= (h / dim); k++)
      {
       if ((j + k) % 2 == 0)
       { // skip every othexr square
        //g2d.fillRect(j * dim, k * dim, dim, dim); // gray squares
        for(short x = j*dim; x<j*dim+dim; x++)
        {
         for(short y = k*dim; y < k*dim+dim; y++)
          if(x < w && y < h)
          result->setPixel(x, y,1);
        }
       }
      }
     }
    }
    log->debug("DrawSquares ready");
    return result;
}

/*private*/ /*static*/ /*final*/ Logger* DrawSquares::log = LoggerFactory::getLogger("DrawSquares");
