#include "imagepanel.h"
#include "loggerfactory.h"

ImagePanel::ImagePanel(QWidget *parent) : QFrame(parent)
{
 back = NULL;
 clip = NULL;
 setObjectName("ImagePanel");
}
/**
 * Common utility to draw a BufferedImage as background behind a JPanel.
 * Used in jmri.jmrit.catalog, jmri.jmrit.display.palette (via LayoutEditor 'Add Items' menu).
 *
 * @author Egbert Broerse copyright (c) 2017
 */
// /*public*/ class ImagePanel extends JPanel {

/**
 * Set background images for ImagePanel.
 * @see jmri.jmrit.catalog.PreviewDialog#setupPanel()
 * @see jmri.jmrit.catalog.CatalogPanel#makeButtonPanel()
 *
 * @param img Image to load as background
 */
/*public*/ void ImagePanel::setImage(QImage* img) {
    back = (BufferedImage*) img;
//    repaint();
    QPixmap bkgnd = QPixmap::fromImage(*back);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    update();
    log->debug("DrawPanel ready");
}
#if 0
//@Override
/*protected*/ void paintComponent(Graphics g) {
    super.paintComponent(g);
    if (back != null) {
        int imgWidth;
        int imgHeight;
        imgWidth = back.getWidth(this);
        imgHeight = back.getHeight(this);
        double frameRatio = (double) getWidth() / (double) getHeight();
        double imgRatio = imgWidth / imgHeight;
        log.debug("ratios: fr {} - img {}", frameRatio, imgRatio);

        // maintain squares on non square panels, enlarge to fill full frame
        if (frameRatio < imgRatio) { // image more oblong than frame
            imgWidth = (int) (imgHeight * frameRatio); // clip width
            // keep full imgHeight
        } else { // image taller than frame
            // keep full imgWidth
            imgHeight = (int) (imgWidth / frameRatio); // clip height
        }
        // clip part op back image
        clip = new BufferedImage(imgWidth, imgHeight, BufferedImage.TYPE_INT_RGB);
        clip = back.getSubimage(0, 0, Math.min(imgWidth, back.getWidth(this)),
                Math.min(imgHeight, back.getWidth(this))); // catch clip size error on change to different pane

        g.drawImage(clip, 0, 0, getWidth(), getHeight(), this);
    }
}
#endif
//private void update() {
//    repaint();
//}

/*private*/ /*static*/ /*final*/ Logger* ImagePanel::log = LoggerFactory::getLogger("ImagePanel");
