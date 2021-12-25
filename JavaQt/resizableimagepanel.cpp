#include "resizableimagepanel.h"
#include "logger.h"
#include "propertychangesupport.h"
#include <QPainter>
#include <QVBoxLayout>

ResizableImagePanel::ResizableImagePanel(QWidget *parent)
 : Component(parent)
{
 common();
}

void ResizableImagePanel::common()
{
  image = QImage();
  scaledImage = QImage();
  _resizeContainer = false;
 _respectAspectRatio = true;
  bgImg = NULL;
  toResize = false;
  setBackground(BackGroundColor);
  setVisible(true);
  log = new Logger("ResizableImagePanel");
  pcs = new PropertyChangeSupport(this);

  //setLayout(new QVBoxLayout);
}

/**
 * A class extending JPanels to have a image display in a panel, supports<ul>
 * <li>drag'n drop of image file</li>
 * <li>can resize container</li>
 * <li>can scale content to size</li>
 * <li>respect aspect ratio by default (when resizing content)</li>
 * </ul>
 * (overrides paintComponent for performances)
 *
 * @author Lionel Jeanson - Copyright 2009
 */
///*public*/ class ResizableImagePanel extends JPanel implements ComponentListener {

/*public*/ /*static*/ /*final*/QString ResizableImagePanel::IMAGE_PATH = "imagePath";

/*static*/ /*private*/ QColor ResizableImagePanel::BackGroundColor = QColor(Qt::black);
/*final*/ /*static*/ QSize ResizableImagePanel::smallDim = QSize(10, 10);

/**
 * Default constructor.
 *
 */
//    /*public*/ ResizableImagePanel() {
//        super();
//        super.setBackground(BackGroundColor);
//        setVisible(false);
//    }

/**
 * Constructor with initial image file path as parameter. Component will be
 * (preferred) sized to image sized
 *
 *
 * @param imagePath Path to image to display
 */
/*public*/ ResizableImagePanel::ResizableImagePanel(QString imagePath, QWidget *parent)
 : Component(parent)
{
    //super();
 common();
    setBackground(BackGroundColor);
    setImagePath(imagePath);
}

/**
 * Constructor for ResizableImagePanel with forced initial size
 *
 * @param imagePath Path to image to display
 * @param w         Panel width
 * @param h         Panel height
 */
/*public*/ ResizableImagePanel::ResizableImagePanel(QString imagePath, int w, int h, QWidget *parent)
 : Component(parent)
{
    //super();
 common();
    //setPreferredSize(QSize(w, h));
    resize(w, h);
    setBackground(BackGroundColor);
    setImagePath(imagePath);
    update();
}

//@Override
/*public*/ void ResizableImagePanel::setBackground(QColor bckCol) {
    //super.setBackground(bckCol);
 QString ss = QString("background-color: rgb(%1,%2,%3)").arg(bckCol.red()).arg(bckCol.green()).arg(bckCol.blue());
 setStyleSheet(ss);
    setScaledImage();
}

/**
 * Allows this ResizableImagePanel to force resize of its container
 *
 */
/*public*/ void ResizableImagePanel::setResizingContainer(bool b) {
    _resizeContainer = b;
}

/**
 * Can this DnDImagePanel resize its container?
 *
 * @return true if container can be resized
 */
/*public*/ bool ResizableImagePanel::isResizingContainer() {
    return _resizeContainer;
}

/**
 * Is this DnDImagePanel respecting aspect ratio when resizing content?
 *
 * @return true is aspect ratio is maintained
 */
/*public*/ bool ResizableImagePanel::isRespectingAspectRatio() {
    return _respectAspectRatio;
}

/**
 * Allow this ResizableImagePanel to respect aspect ratio when resizing
 * content
 *
 */
/*public*/ void ResizableImagePanel::setRespectAspectRatio(bool b) {
    _respectAspectRatio = b;
}

/**
 * Return current image file path
 *
 * @return The image path or "/" if no image is specified
 */
/*public*/ QString ResizableImagePanel::getImagePath() {
    return _imagePath;
}

/**
 * Set image file path, display will be updated if passed value is NULL,
 * blank image
 *
 */
/*public*/ void ResizableImagePanel::setImagePath(QString s) {
    QString old = _imagePath;
    if (s != NULL && s!=("")) {
        _imagePath = s;
    } else {
        _imagePath = "";
        image = QImage();
        scaledImage = QImage();
    }
    log->debug(tr("Image path is now : %1").arg(_imagePath));
    if (_imagePath != NULL) {
        //try {
            image = QImage((_imagePath));
        //} catch (IOException* ex) {
            if(image.isNull())
            {
             log->error(tr("%1 is not a valid image file, exception: ").arg(_imagePath));
            image = QImage();
            scaledImage = QImage();
        }
    }
    if (isResizingContainer()) {
        resizeContainer();
    }
    setScaledImage();
    setVisible(true);
    repaint();
    if (parent() != NULL) {
        ((QWidget*)parent())->repaint();
    }
    pcs->firePropertyChange(IMAGE_PATH, old, _imagePath);
}
#if 0
//
// componentListener methods, for auto resizing and scaling
//
@Override
/*public*/ void componentResized(ComponentEvent e) {
    if (!(isResizingContainer())) {
        if (e.getComponent().isVisible()) {
            setSize(e.getComponent().getSize());
            setPreferredSize(e.getComponent().getSize());
            setScaledImage();
            toResize = false;
        } else {
            toResize = true;
        }
    }
    repaint();
    if (getParent() != NULL) {
        getParent().repaint();
    }
}

@Override
/*public*/ void componentMoved(ComponentEvent e) {
}

@Override
/*public*/ void componentShown(ComponentEvent e) {
    if (isResizingContainer()) {
        resizeContainer();
    } else {
        if ((toResize) || (scaledImage == NULL)) {
            setSize(e.getComponent().getSize());
            setPreferredSize(e.getComponent().getSize());
            setScaledImage();
            toResize = false;
        }
    }
}

@Override
/*public*/ void componentHidden(ComponentEvent e) {
    log->debug("Component hidden");
    if (isResizingContainer()) {
        resizeContainer(smallDim);
    }
}
#endif
/*private*/ void ResizableImagePanel::resizeContainer(QSize d) {
    log->debug("Resizing container");
    QWidget* p1 = (QWidget*)parent();
    if ((p1 != NULL) && (!image.isNull())) {
//        setPreferredSize(d);
        resize(d);
//        p1->setPreferredSize(d);
        p1->resize(d);
//        if ((getTopLevelAncestor() != NULL) && (getTopLevelAncestor() instanceof Window)) {
//            ((Window) getTopLevelAncestor()).pack(); // yes, lucky hack, possibly dirty
//        }
        window()->adjustSize();
    }
}

/*private*/ void ResizableImagePanel::resizeContainer() {
    if (!scaledImage.isNull()) {
        resizeContainer(QSize(scaledImage.width(), scaledImage.height()));
    } else if (!image.isNull()) {
        resizeContainer(QSize(image.width(), image.height()));
    }
}

//override paintComponent
//@Override
/*protected*/ void ResizableImagePanel::paintEvent(QPaintEvent* /*e*/)
{
 QPainter painter;
 painter.begin(this);
 // ?? super.paintComponent(g);
 setBackgroundRole(QPalette::NoRole);
 if (!scaledImage.isNull())
 {
     //g->drawImage(scaledImage, 0, 0, this);
  painter.drawImage(0,0, scaledImage);
 }
 else
 {
  painter.drawRect(0, 0, (int) size().width(), (int) size().height());
 }
 painter.end();
}

/**
 * Get current scaled Image
 *
 * @return the image resized as specified
 */
/*public*/ QImage ResizableImagePanel::getScaledImage() {
    return scaledImage;
}

/*private*/ void ResizableImagePanel::setScaledImage()
{
 if (!image.isNull())
 {
  if(image.height() < size().height() && image.width() < size().width())
  {
   scaledImage = image;
   return;
  }
  if ((size().width() != 0) && (size().height() != 0)
          && ((size().width() != image.width()) || (size().height() != image.height()))) {
      int newW = (int) size().width();
      int newH = (int) size().height();
//      int new0x = 0;
//      int new0y = 0;
      log->debug(tr("Actually resizing image %1 from %4x%%5 to %2x%3").arg(this->getImagePath()).arg(newW).arg(newH).arg(image.width()).arg(image.height()));
#if 0
      scaledImage = new QImage(newW, newH, image.getType() == 0 ? BufferedImage.TYPE_INT_ARGB : image.getType());
      Graphics2D g = scaledImage.createGraphics();
      g.setBackground(getBackground());
      g.clearRect(0, 0, newW, newH);
      g.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
      if (_respectAspectRatio) {
          if ((getSize().getWidth() / getSize().getHeight()) > ((double) image.getWidth(NULL) / (double) image.getHeight(NULL))) { // Fill on height
              newW = image.getWidth(NULL) * newH / image.getHeight(NULL);
              new0x = (int) (getSize().getWidth() - newW) / 2;
          } else { // Fill on width
              newH = image.getHeight(NULL) * newW / image.getWidth(NULL);
              new0y = (int) (getSize().getHeight() - newH) / 2;
          }
      }
      g.drawImage(image, new0x, new0y, new0x + newW, new0y + newH, 0, 0, image.getWidth(), image.getHeight(), this);
      g.dispose();
#endif
   scaledImage = image.scaled(newW, newH, _respectAspectRatio? Qt::KeepAspectRatio:Qt::IgnoreAspectRatio); //, image.getType() == 0 ? BufferedImage.TYPE_INT_ARGB : image.getType());
  } else {
      scaledImage = image;
  }
 }
}

