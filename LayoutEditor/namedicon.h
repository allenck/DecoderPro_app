#ifndef NAMEDICON_H
#define NAMEDICON_H

#include <QIcon>
#include <QImage>
#include <QUrl>
#include "logger.h"
#include "imageicon.h"
#include "liblayouteditor_global.h"

class Logger;
class QObject;
class LIBLAYOUTEDITORSHARED_EXPORT NamedIcon : public ImageIcon
{
    Q_OBJECT
public:
    //explicit NamedIcon(QObject *parent = 0);
    /**
     * Create a NamedIcon that is a complete copy
     * of an existing NamedIcon
     * @param pOld Object to copy
     * i.e. copy of the original icon, but NOT a complete
     * copy of pOld (no transformations done)
     */
    /*public*/ NamedIcon(NamedIcon* pOld, QObject *parent  =0);
    /**
     * Create a NamedIcon that is really a complete copy
     * of an existing NamedIcon
     * @param pOld Object to copy
     */
    /*public*/ NamedIcon(NamedIcon* pOld, QObject* comp, QObject *parent = 0) ;
    /**
     * Create a named icon that includes an image
     * to be loaded from a URL.
     *
     * @param pUrl String-form URL of image file to load
     * @param pName Human-readable name for the icon
     */
    /*public*/ NamedIcon(QString pUrl, QString pName, QObject *parent = 0);
    /*public*/ NamedIcon(QImage im, QObject *parent = 0);
    /**
     * Find the NamedIcon corresponding to a name. Understands the
     * <a href="http://jmri.org/help/en/html/doc/Technical/FileNames.shtml">standard portable filename prefixes</a>.
     *
     * @param pName The name string, possibly starting with file: or resource:
     * @return the desired icon with this same pName as its name.
     */
    static /*public*/ NamedIcon* getIconByName(QString pName);
    /**
     * Return the human-readable name of this icon
     */
    /*public*/ QString getName() ;
    /**
    * Actually it is mName that is the URL that loads the icon!
    */
    /*public*/ void setName(QString name);
    /**
     * Return the URL of this icon
     */
    /*public*/ QString getURL();

    /**
     * Set URL of original icon image
     */
    /*public*/ void setURL(QString url);
    /**
     * Return the 0-3 number of 90-degree rotations needed to
     * properly display this icon
     */
    /*public*/ int getRotation();
    /**
     * Set the 0-3 number of 90-degree rotations needed to properly
     * display this icon
     */
    /*public*/ void setRotation(int pRotation, QObject* comp);
    /**
     * The following was based on a text-rotating applet from
     * David Risner, available at http://www.risner.org/java/rotate_text.html
     * @param pImage Image to transform
     * @param pComponent Component containing the image, needed to obtain
     *                  a MediaTracker to process the image consistently with display
     * @param pRotation 0-3 number of 90-degree rotations needed
     * @return new Image object containing the rotated input image
     */
    /*public*/ QImage* createRotatedImage(QImage* pImage, QObject*, int pRotation);
    /*public*/ int getDegrees();
    /*public*/ double getScale();
    /*public*/ void setLoad(int d, double s, QObject* comp) ;
//    /*public*/ void transformImage(int w, int h, AffineTransform t /*, Component comp*/);
    /**
    *  Scale as a percentage
    */
    /*public*/ void scale(int s, QObject* comp) ;
    /*public*/ void scale(double scale, QObject* comp);

    /**
    * Rotate from anchor point (upper left corner) and shift into place
    */
    /*public*/ void rotate(int degree, QObject*);
    /**
    *  If necessary, reduce this image to within 'width' x 'height' dimensions.
    * limit the reduction by 'limit'
    */
    /*public*/ double reduceTo(int width, int height, double limit) ;
    /*public*/ const static int NOFLIP = 0X00;
    /*public*/ const static int HORIZONTALFLIP = 0X01;
    /*public*/ const static int VERTICALFLIP = 0X02;

    /*public*/ void flip(int flip/*, Component comp*/);
    int getIconWidth();
    int getIconHeight();
    //QImage getImage();
    /*public*/ QImage getOriginalImage();
    void setImage(QImage);
    QString getFilename() {return filename;}
signals:
    
public slots:
private:
/*private*/ QString mName;//=null;
/*private*/ QString mURL;//=null;
/*private*/ QImage mDefaultImage;
/*private*/ QString filename;
void init();
/*private*/ int _deg;// = 0;
/*private*/ double _scale;// = 1.0;
///*private*/ AffineTransform _transformS;// = new AffineTransform();    // scaling
///*private*/ AffineTransform _transformF;// = new AffineTransform();    // Fliped or Mirrored
static Logger* log;
/**
 * Valid values are <UL>
 * <LI>0 - no rotation
 * <LI>1 - 90 degrees counter-clockwise
 * <LI>2 - 180 degrees counter-clockwise
 * <LI>3 - 270 degrees counter-clockwise
 * </UL>
 */
int mRotation;
};

#endif // NAMEDICON_H
