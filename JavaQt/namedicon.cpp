#include "namedicon.h"
#include <QDebug>
#include "qmath.h"
#include "fileutil.h"
#include "file.h"

//NamedIcon::NamedIcon(QObject *parent) :
//    QIcon(parent)
//{
//}
/**
 * Extend an ImageIcon to remember the name from which it was created
 * and provide rotation & scaling services.
 *<p>
 * We store both a "URL" for finding the file this was made from
 * (so we can load this later), plus a shorter "name" for display.
 * <p>
 * These can be persisted by storing their name and rotation
 *
 * @see jmri.jmrit.display.configurexml.PositionableLabelXml
 * @author Bob Jacobsen  Copyright 2002, 2008
 * @author  Pete Cressman Copyright: Copyright (c) 2009, 2010
 * @version $Revision: 22402 $
 */

///*public*/ class NamedIcon extends ImageIcon {

/**
 * Create a NamedIcon that is a complete copy
 * of an existing NamedIcon
 * @param pOld Object to copy
 * i.e. copy of the original icon, but NOT a complete
 * copy of pOld (no transformations done)
 */
/*public*/ NamedIcon::NamedIcon(NamedIcon* pOld, QObject *parent) : ImageIcon(pOld->getImage(),parent)
{
 init();
 //this(pOld.mURL, pOld.mName);
 mURL = pOld->mURL;
 mName = pOld->mName;
 mDefaultImage = pOld->mDefaultImage;
 mRotation = 0;
}

/**
 * Create a NamedIcon that is really a complete copy
 * of an existing NamedIcon
 * @param pOld Object to copy
 */
/*public*/ NamedIcon::NamedIcon(NamedIcon* pOld, QObject* comp,QObject *parent) : ImageIcon(pOld->getImage(), parent)
{
 init();
 //this(pOld->mURL, pOld.mName);
 mURL = pOld->mURL;
 mName = pOld->mName;
 mDefaultImage = pOld->mDefaultImage;
 setLoad(pOld->_deg, pOld->_scale, comp);
 setRotation(pOld->mRotation, comp);
}

/**
 * Create a named icon that includes an image
 * to be loaded from a URL.
 * <p>
 * The default access form is "file:", so a
 * bare pathname to an icon file will also work
 * for the URL argument
 *
 * @param pUrl URL of image file to load
 * @param pName Human-readable name for the icon
 */
/*public*/ NamedIcon::NamedIcon(QString pUrl, QString pName, QObject *parent) : ImageIcon(FileUtil::findExternalFilename(pUrl), pName, parent)
{
 init();
 if(pUrl.at(1) == 0)
  pUrl = QString(pUrl);
//    super(FileUtil.findExternalFilename(pUrl));
 QUrl u = FileUtil::findExternalFilename(pUrl);
 if (u.isEmpty())
 {
  log->warn("Could not load image from " + pUrl + " (file does not exist)");
 }

 mURL = /*FileUtil::getPortableFilename(pUrl);*/ u.path();
 mDefaultImage = getImage();
 if (mDefaultImage.isNull())
 {
  log->warn("Could not load image from " + pUrl +"("+ FileUtil::getAbsoluteFilename(pUrl)+ ") (image is NULL)");
 }
 mName = pName;
 mURL = FileUtil::getPortableFilename(pUrl);
 mRotation = 0;
}

/*public*/ NamedIcon::NamedIcon(QImage im, QObject *parent) : ImageIcon(im, parent)
{
 init();
 //super(im);
 mDefaultImage = im;
}

void NamedIcon::init()
{
 mName="";
 mURL="";
 mDefaultImage = QImage();
 _deg = 0;
 _scale = 1.0;
// _transformS = new AffineTransform();    // scaling
// _transformF = new AffineTransform();    // Fliped or Mirrored
 log = new Logger("NamedIcon");
 log->setDebugEnabled(true);
}

/**
 * Find the NamedIcon corresponding to a name. Understands the
 * <a href="http://jmri.org/help/en/html/doc/Technical/FileNames.shtml">standard portable filename prefixes</a>.
 *
 * @param pName The name string, possibly starting with file: or resource:
 * @return the desired icon with this same pName as its name.
 */
/*static*/ /*public*/ NamedIcon* NamedIcon::getIconByName(QString pName)
{
 if (pName == NULL || pName.length() == 0)
 {
  return NULL;
 }
 QUrl u = FileUtil::findExternalFilename(pName);
 if (!u.isValid())
 {
  return NULL;
 }
// else
//  return new NamedIcon(u.fileName(), pName);
 return new NamedIcon(pName, pName);
}

/**
 * Return the human-readable name of this icon
 */
/*public*/ QString NamedIcon::getName() { return mName; }

/**
* Actually it is mName that is the URL that loads the icon!
*/
/*public*/ void NamedIcon::setName(QString name) { mName = name; }

/**
 * Return the URL of this icon
 */
/*public*/ QString NamedIcon::getURL()
{
 return mURL;
}

/**
 * Set URL of original icon image
 */
/*public*/ void NamedIcon::setURL(QString url)
{
 mURL = url;
}

/**
 * Return the 0-3 number of 90-degree rotations needed to
 * properly display this icon
 */
/*public*/ int NamedIcon::getRotation() { return mRotation; }

/**
 * Set the 0-3 number of 90-degree rotations needed to properly
 * display this icon
 */
/*public*/ void NamedIcon::setRotation(int pRotation, QObject* /*comp*/)
{
 // don't transform a blinking icon, it will no longer blink!
 if (pRotation == 0)
     return;
 if (pRotation>3) pRotation = 0;
 if (pRotation<0) pRotation = 3;
 mRotation = pRotation;
//    setImage(createRotatedImage(mDefaultImage, comp, mRotation));
//    _deg = 0;
//    int w = (int)Math.ceil(_scale*getIconWidth());
//    int h = (int)Math.ceil(_scale*getIconHeight());
//    transformImage(w, h, _transformS, comp);
 switch(mRotation)
 {
 case 0:
   _deg = 0;
   break;
 case 1:
   _deg = 90;
   break;
 case 2:
   _deg = 180;
   break;
 case 3:
   _deg = 270;
   break;
 }
}

/*
/*public*/ QImage NamedIcon::getOriginalImage()
{
 return mDefaultImage;
}
#if 0 // not necesary as QraphicsItems can be rotated.

/**
 * The following was based on a text-rotating applet from
 * David Risner, available at http://www.risner.org/java/rotate_text.html
 * @param pImage Image to transform
 * @param pComponent Component containing the image, needed to obtain
 *                  a MediaTracker to process the image consistently with display
 * @param pRotation 0-3 number of 90-degree rotations needed
 * @return new Image object containing the rotated input image
 */
/*public*/ QImage* NamedIcon::createRotatedImage(QImage* pImage, /*Component pComponent,*/ int pRotation)
{
    if (log.isDebugEnabled()) log.debug("createRotatedImage: pRotation= "+pRotation+
                                   ", mRotation= "+mRotation);
    if (pRotation == 0) return pImage;

    MediaTracker mt = new MediaTracker(pComponent);
    mt.addImage(pImage, 0);
    try {
        mt.waitForAll();
    } catch (InterruptedException ie) {
        Thread.currentThread().interrupt(); // retain if needed later
    }

    int w = pImage.getWidth(NULL);
    int h = pImage.getHeight(NULL);

    int[] pixels = new int[w*h];
    PixelGrabber pg = new PixelGrabber(pImage, 0, 0, w, h, pixels, 0, w);
    try {
        pg.grabPixels();
    } catch (InterruptedException ie) {}
    int[] newPixels = new int[w*h];

    // transform the pixels
    MemoryImageSource imageSource = NULL;
    switch (pRotation) {
    case 1:  // 90 degrees
        for (int y=0; y < h; ++y) {
            for (int x=0; x < w; ++x) {
                newPixels[x*h + y] = pixels[y*w + (w-1-x)];
            }
        }
        imageSource = new MemoryImageSource(h, w,
            ColorModel.getRGBdefault(), newPixels, 0, h);
        break;
    case 2: // 180 degrees
        for (int y=0; y < h; ++y) {
            for (int x=0; x < w; ++x) {
                newPixels[x*h + y] = pixels[(w-1-x)*h + (h-1-y)];
            }
        }
        imageSource = new MemoryImageSource(w, h,
            ColorModel.getRGBdefault(), newPixels, 0, w);
        break;
    case 3: // 270 degrees
        for (int y=0; y < h; ++y) {
            for (int x=0; x < w; ++x) {
                newPixels[x*h + y] = pixels[(h-1-y)*w + x];
            }
        }
        imageSource = new MemoryImageSource(h, w,
            ColorModel.getRGBdefault(), newPixels, 0, h);
        break;
    }

    Image myImage = pComponent.createImage(imageSource);
    mt.addImage(myImage, 1);
    try {
        mt.waitForAll();
    } catch (InterruptedException ie) {}
    return myImage;
}
#endif
/*public*/ int NamedIcon::getDegrees() { return /*_deg*/ 0; } // not needed since QtScene does the rotating
/*public*/ double NamedIcon::getScale() { return _scale; }

/*public*/ void NamedIcon::setLoad(int d, double s, QObject* comp)
{
 if (d!=0 || s!=1.0)
 {
//        setImage(createRotatedImage(mDefaultImage, comp, 0));
     //mRotation = 3;
 }
 if (d!=0)
 {
  rotate(d, comp);
 }
 if (s!=1.0)
 {
  scale(s, comp);
 }
}
#if 0
/*public*/ void NamedIcon::transformImage(int w, int h, AffineTransform t, Component comp) {
    if (w<=0 || h<=0) {
        if (log.isDebugEnabled()) log.debug("transformImage bad coords "+
                                       ((jmri.jmrit.display.Positionable)comp).getNameQString());
        return;
    }
    BufferedImage bufIm = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
    Graphics2D g2d = bufIm.createGraphics();
    g2d.setRenderingHint(RenderingHints.KEY_RENDERING,
                         RenderingHints.VALUE_RENDER_QUALITY);
    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                         RenderingHints.VALUE_ANTIALIAS_ON);
    g2d.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION,
                         RenderingHints.VALUE_ALPHA_INTERPOLATION_QUALITY);
    g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                         RenderingHints.VALUE_INTERPOLATION_BICUBIC);
    g2d.drawImage(getImage(), t, comp);
    setImage(bufIm);
    g2d.dispose();
}
/*
void debugDraw(QString op, Component c) {
    jmri.jmrit.display.Positionable pos = (jmri.jmrit.display.Positionable)c;
    java.awt.Rectangle r = c.getBounds();
    log.debug(pos.getNameQString()+" "+op);
    System.out.println("\tBounds at ("+r.x+", "+r.y+") width= "+r.width+", height= "+r.height);
    System.out.println("\tLocation at ("+c.getX()+", "+c.getY()+") width= "+
                       c.getWidth()+", height= "+c.getHeight());
}
*/
#endif
/**
*  Scale as a percentage
*
*/
/*public*/ void NamedIcon::scale(int s, QObject* comp)
{
 //log.info("scale= "+s+", "+getDescription());
 if (s<1) { return; }
 scale(s/100.0, comp);
}


/*public*/ void NamedIcon::scale(double scale, QObject* comp)
{
//    setImage(mDefaultImage);
//    int w = (int)qCeil(scale*getIconWidth());
//    int h = (int)qCeil(scale*getIconHeight());
//    _transformS = AffineTransform.getScaleInstance(scale, scale);
//    transformImage(w, h, _transformS, comp);
 _scale = scale;
 if(_deg!=0)
 {
  rotate(_deg, comp);
 }
}

/**
* Rotate from anchor point (upper left corner) and shift into place
*/
/*public*/ void NamedIcon::rotate(int degree, QObject*)
{
//    setImage(mDefaultImage);
//    if (_scale!=1.0) {
//        int w = (int)Math.ceil(_scale*getIconWidth());
//        int h = (int)Math.ceil(_scale*getIconHeight());
//        transformImage(w, h, _transformS, comp);
//    }
//    mRotation=0;
//    degree = degree%360;
//    double rad = degree*Math.PI/180.0;
//    double w = getIconWidth();
//    double h = getIconHeight();
//    int width = (int)Math.ceil(Math.abs(h*Math.sin(rad)) + Math.abs(w*Math.cos(rad)));
//    int heigth = (int)Math.ceil(Math.abs(h*Math.cos(rad)) + Math.abs(w*Math.sin(rad)));
//    AffineTransform t = NULL;
//    if (0<=degree && degree<90 || -360<degree && degree<=-270){
//        t = AffineTransform.getTranslateInstance(h*Math.sin(rad), 0.0);
//    } else if (90<=degree && degree<180 || -270<degree && degree<=-180) {
//        t = AffineTransform.getTranslateInstance(h*Math.sin(rad)-w*Math.cos(rad), -h*Math.cos(rad));
//    } else if (180<=degree && degree<270 || -180<degree && degree<=-90) {
//        t = AffineTransform.getTranslateInstance(-w*Math.cos(rad), -w*Math.sin(rad)-h*Math.cos(rad));
//    } else /*if (270<=degree && degree<360)*/ {
//        t = AffineTransform.getTranslateInstance(0.0, -w*Math.sin(rad));
//    }
//    AffineTransform r = AffineTransform.getRotateInstance(rad);
//    t.concatenate(r);
//    transformImage(width, heigth, t, comp);
    _deg = degree;
}
#if 1
/**
*  If necessary, reduce this image to within 'width' x 'height' dimensions.
* limit the reduction by 'limit'
*/
/*public*/ double NamedIcon::reduceTo(int width, int height, double limit)
{
 int w = getIconWidth();
 int h = getIconHeight();
 double scale = 1.0;
 if (w > width)
 {
  scale = ((double)width)/w;
 }
 if (h > height)
 {
  scale = qMin(scale, ((double)height)/h);
 }
 if (scale < 1)
 { // make a thumbnail
  if (limit > 0.0)
  {
   scale = qMax(scale, limit);  // but not too small
  }
//        AffineTransform t = AffineTransform.getScaleInstance(scale, scale);
//        transformImage((int)Math.ceil(scale*w), (int)Math.ceil(scale*h), t, NULL);
  mDefaultImage = mDefaultImage.scaled(width,height,Qt::KeepAspectRatio);
 }
 return scale;
}
#endif

/*public*/ void NamedIcon::flip(int flip/*, Component comp*/)
{
 if(flip==NOFLIP)
 {
  setImage(mDefaultImage);
  //_transformF = new AffineTransform();
  _deg = 0;
  int w = (int)qCeil(_scale*getIconWidth());
  int h = (int)qCeil(_scale*getIconHeight());
  //transformImage(w, h, _transformF, comp);
  mDefaultImage = mDefaultImage.scaled(w,h);
  return;
 }
 int w = getIconWidth();
 int h = getIconHeight();
 if(flip==HORIZONTALFLIP)
 {
//  _transformF = AffineTransform.getScaleInstance(-1, 1);
//  _transformF.translate(-w, 0);
  mDefaultImage = mDefaultImage.mirrored(true, false);
 }
 else
 {
//   _transformF = AffineTransform.getScaleInstance(1, -1);
//   _transformF.translate(0, -h);
  mDefaultImage = mDefaultImage.mirrored(false, true);
 }
// transformImage(w, h, _transformF, NULL);

}

int NamedIcon::getIconWidth()
{
 if(!mDefaultImage.isNull())
  return mDefaultImage.width();
 return 0;
}
int NamedIcon::getIconHeight()
{
 if(!mDefaultImage.isNull())
 {
  int h = mDefaultImage.height();
  return mDefaultImage.height();
 }
 return 0;
}

QImage NamedIcon::getImage()
{
 if(this == NULL)
  return QImage();
 if(!mDefaultImage.isNull())
  return mDefaultImage;
 QImage img;

 const char* fmt;
 if(mURL.endsWith(".jpg"))
  fmt = "JPG";
 else
 if(mURL.endsWith(".gif"))
  fmt = "GIF";
 else
  if(mURL.endsWith(".png"))
   fmt = "PNG";

 if(File(mURL).exists())
 {
  img = QImage(mURL, fmt);
  filename = File(mURL).getPath();
 }
 else
 {
  filename = FileUtil::getAbsoluteFilename(mURL);
  img =  QImage(filename, fmt);
 }
 if(img.isNull())
  log->debug( "unable to load " + mURL + " ("+ filename + ")");
 return img;
}
void NamedIcon::setImage(QImage img)
{
 mDefaultImage = img;
}

