#include "resizableimagepanel.h"
#include "loggerfactory.h"
#include <QResizeEvent>
#include "exceptions.h"

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

    /*public*/ /*static*/ /*final*/ QString ResizableImagePanel::IMAGE_PATH = "imagePath";

    /*static*/ /*private*/ QColor ResizableImagePanel::backgroundColor = QColor(Qt::black);
    /*final*/ /*static*/ QSize ResizableImagePanel::SMALL_DIM = QSize(10, 10);

    /**
     * Default constructor.
     */
    /*public*/ ResizableImagePanel::ResizableImagePanel(QWidget* parent) : QWidget(parent){
        //super();
     common();
// TODO:        super.setBackground(backgroundColor);
     QPalette pal = palette();
     pal.setColor(QPalette::Background, Qt::black);
     setPalette(pal);
        setVisible(false);
    }

    void ResizableImagePanel::common()
    {
     bgImg = NULL;
     image = NULL;
     scaledImage = NULL;
     _resizeContainer = false;
     _respectAspectRatio = true;
     toResize = false;

    }

    /**
     * Constructor with initial image file path as parameter. Component will be
     * (preferred) sized to image sized
     *
     *
     * @param imagePath Path to image to display
     */
    /*public*/ ResizableImagePanel::ResizableImagePanel(QString imagePath, QWidget* parent) : QWidget(parent) {
        //super();
        common();
        //super.setBackground(backgroundColor);
        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::black);
        setPalette(pal);
        setImagePath(imagePath);
    }

    /**
     * Constructor for ResizableImagePanel with forced initial size
     *
     * @param imagePath Path to image to display
     * @param w         Panel width
     * @param h         Panel height
     */
    /*public*/ ResizableImagePanel::ResizableImagePanel(QString imagePath, int w, int h, QWidget* parent) : QWidget(parent) {
        //super();
     common();
        resize(QSize(w, h));
//        setSize(w, h);
        //super.setBackground(backgroundColor);
        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::black);
        setPalette(pal);
        setImagePath(imagePath);
    }

    //@Override
    /*public*/ void ResizableImagePanel::setBackground(QColor bckCol) {
        //super.setBackground(bckCol);
     QPalette pal = palette();
     pal.setColor(QPalette::Background, bckCol);
     setPalette(pal);
//        setScaledImage();
    }

    /**
     * Allows this ResizableImagePanel to force resize of its container
     *
     * @param b true if this instance can resize its container; false otherwise
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
     * content.
     *
     * @param b true if aspect ratio should be respected; false otherwise
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
     * @param s path to image file
     */
    /*public*/ void ResizableImagePanel::setImagePath(QString s) {
        QString old = _imagePath;
        if (s != NULL && s != ("")) {
            _imagePath = s;
        } else {
            _imagePath = "";
            image = NULL;
            scaledImage = NULL;
        }
        log->debug(tr("Image path is now : %1").arg(_imagePath));
        if (_imagePath != NULL) {
            try {
                image = new QImage(_imagePath);//ImageIO.read(new File(_imagePath));
            } catch (IOException ex) {
                log->error(tr("%1 is not a valid image file, exception: ").arg(_imagePath) +  ex.getMessage());
                image = NULL;
                scaledImage = NULL;
            }
        }
        if (isResizingContainer()) {
            resizeContainer();
        }
//        setScaledImage();
        setVisible(true);
        repaint();
        if (parent() != NULL) {
//            parent()->repaint();
        }
//        this->firePropertyChange(IMAGE_PATH, old, _imagePath);
    }

    //
    // componentListener methods, for auto resizing and scaling
    //
    //@Override
    /*public*/ void ResizableImagePanel::componentResized(QResizeEvent* e) {
        if (!(isResizingContainer())) {
#if 0
            if (e->getComponent().isVisible()) {
                setSize(e.getComponent().getSize());
                setPreferredSize(e.getComponent().getSize());
                setScaledImage();
                toResize = false;
            } else {
                toResize = true;
            }
#endif
        }
        repaint();
        if (parent() != NULL) {
 //           parent()->repaint();
        }
    }

    //@Override
    /*public*/ void ResizableImagePanel::componentMoved(QMoveEvent* e) {
    }

    //@Override
    /*public*/ void ResizableImagePanel::componentShown(QShowEvent* e) {
        if (isResizingContainer()) {
            resizeContainer();
        } else {
            if ((toResize) || (scaledImage == NULL)) {
#if 0
                setSize(e.getComponent().getSize());
                setPreferredSize(e.getComponent().getSize());
                setScaledImage();
                toResize = false;
#endif
            }
        }
    }

    //@Override
    /*public*/ void ResizableImagePanel::componentHidden(QHideEvent* e) {
        log->debug("Component hidden");
        if (isResizingContainer()) {
            resizeContainer(SMALL_DIM);
        }
    }

    /*private*/ void ResizableImagePanel::resizeContainer(QSize d) {
        log->debug("Resizing container");
        QWidget* p1 = (QWidget*)parent();
        if ((p1 != NULL) && (image != NULL)) {
            resize(d);
//            setSize(d);
            p1->resize(d);
//            p1.setSize(d);
            QWidget* c = window();//getTopLevelAncestor();
#if 0
            if (c != NULL && c instanceof Window) {
                ((Window) c).pack();
            }
#endif
        }
    }

    /*private*/ void ResizableImagePanel::resizeContainer() {
        if (scaledImage != NULL) {
            resizeContainer(QSize(scaledImage->width(), scaledImage->height()));
        } else if (image != NULL) {
            resizeContainer(QSize(image->width(), image->height()));
        }
    }
#if 0
    //override paintComponent
    //@Override
    /*public*/ void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (scaledImage != NULL) {
            g.drawImage(scaledImage, 0, 0, this);
        } else {
            g.clearRect(0, 0, (int) getSize().getWidth(), (int) getSize().getHeight());
        }
    }

    /**
     * Get current scaled Image
     *
     * @return the image resized as specified
     */
    /*public*/ BufferedImage getScaledImage() {
        return scaledImage;
    }

    /*private*/ void setScaledImage() {
        if (image != NULL) {
            if ((getSize().getWidth() != 0) && (getSize().getHeight() != 0)
                    && ((getSize().getWidth() != image.getWidth(NULL)) || (getSize().getHeight() != image.getHeight(NULL)))) {
                int newW = (int) getSize().getWidth();
                int newH = (int) getSize().getHeight();
                int new0x = 0;
                int new0y = 0;
                log->debug("Actually resizing image {} to {}x{}", this.getImagePath(), newW, newH);
                scaledImage = new BufferedImage(newW, newH, image.getType() == 0 ? BufferedImage.TYPE_INT_ARGB : image.getType());
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
            } else {
                scaledImage = image;
            }
        }
    }
#endif
    /*private*/ /*final*/ /*static*/ Logger* ResizableImagePanel::log = LoggerFactory::getLogger("ResizableImagePanel");
