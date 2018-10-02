#ifndef BUFFEREDIMAGE_H
#define BUFFEREDIMAGE_H
#include <QImage>
#include <QVariant>

class BufferedImage : public QImage
{
public:
 BufferedImage();
 /**
  * Image Type Constants
  */
 enum TYPES
 {
 /**
  * Image type is not recognized so it must be a customized
  * image.  This type is only used as a return value for the getType()
  * method.
  */
  TYPE_CUSTOM = 0,

 /**
  * Represents an image with 8-bit RGB color components packed into
  * integer pixels.  The image has a {@link DirectColorModel} without
  * alpha.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_INT_RGB = 1,

 /**
  * Represents an image with 8-bit RGBA color components packed into
  * integer pixels.  The image has a <code>DirectColorModel</code>
  * with alpha. The color data in this image is considered not to be
  * premultiplied with alpha.  When this type is used as the
  * <code>imageType</code> argument to a <code>BufferedImage</code>
  * constructor, the created image is consistent with images
  * created in the JDK1.1 and earlier releases.
  */
  TYPE_INT_ARGB = 2,

 /**
  * Represents an image with 8-bit RGBA color components packed into
  * integer pixels.  The image has a <code>DirectColorModel</code>
  * with alpha.  The color data in this image is considered to be
  * premultiplied with alpha.
  */
  TYPE_INT_ARGB_PRE = 3,

 /**
  * Represents an image with 8-bit RGB color components, corresponding
  * to a Windows- or Solaris- style BGR color model, with the colors
  * Blue, Green, and Red packed into integer pixels.  There is no alpha.
  * The image has a {@link DirectColorModel}.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_INT_BGR = 4,

 /**
  * Represents an image with 8-bit RGB color components, corresponding
  * to a Windows-style BGR color model) with the colors Blue, Green,
  * and Red stored in 3 bytes.  There is no alpha.  The image has a
  * <code>ComponentColorModel</code>.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_3BYTE_BGR = 5,

 /**
  * Represents an image with 8-bit RGBA color components with the colors
  * Blue, Green, and Red stored in 3 bytes and 1 byte of alpha.  The
  * image has a <code>ComponentColorModel</code> with alpha.  The
  * color data in this image is considered not to be premultiplied with
  * alpha.  The byte data is interleaved in a single
  * byte array in the order A, B, G, R
  * from lower to higher byte addresses within each pixel.
  */
  TYPE_4BYTE_ABGR = 6,

 /**
  * Represents an image with 8-bit RGBA color components with the colors
  * Blue, Green, and Red stored in 3 bytes and 1 byte of alpha.  The
  * image has a <code>ComponentColorModel</code> with alpha. The color
  * data in this image is considered to be premultiplied with alpha.
  * The byte data is interleaved in a single byte array in the order
  * A, B, G, R from lower to higher byte addresses within each pixel.
  */
  TYPE_4BYTE_ABGR_PRE = 7,

 /**
  * Represents an image with 5-6-5 RGB color components (5-bits red,
  * 6-bits green, 5-bits blue) with no alpha.  This image has
  * a <code>DirectColorModel</code>.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_USHORT_565_RGB = 8,

 /**
  * Represents an image with 5-5-5 RGB color components (5-bits red,
  * 5-bits green, 5-bits blue) with no alpha.  This image has
  * a <code>DirectColorModel</code>.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_USHORT_555_RGB = 9,

 /**
  * Represents a unsigned byte grayscale image, non-indexed.  This
  * image has a <code>ComponentColorModel</code> with a CS_GRAY
  * {@link ColorSpace}.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_BYTE_GRAY = 10,

 /**
  * Represents an unsigned short grayscale image, non-indexed).  This
  * image has a <code>ComponentColorModel</code> with a CS_GRAY
  * <code>ColorSpace</code>.
  * When data with non-opaque alpha is stored
  * in an image of this type,
  * the color data must be adjusted to a non-premultiplied form
  * and the alpha discarded,
  * as described in the
  * {@link java.awt.AlphaComposite} documentation.
  */
  TYPE_USHORT_GRAY = 11,

 /**
  * Represents an opaque byte-packed 1, 2, or 4 bit image.  The
  * image has an {@link IndexColorModel} without alpha.  When this
  * type is used as the <code>imageType</code> argument to the
  * <code>BufferedImage</code> constructor that takes an
  * <code>imageType</code> argument but no <code>ColorModel</code>
  * argument, a 1-bit image is created with an
  * <code>IndexColorModel</code> with two colors in the default
  * sRGB <code>ColorSpace</code>: {0,&nbsp;0,&nbsp;0} and
  * {255,&nbsp;255,&nbsp;255}.
  *
  * <p> Images with 2 or 4 bits per pixel may be constructed via
  * the <code>BufferedImage</code> constructor that takes a
  * <code>ColorModel</code> argument by supplying a
  * <code>ColorModel</code> with an appropriate map size.
  *
  * <p> Images with 8 bits per pixel should use the image types
  * <code>TYPE_BYTE_INDEXED</code> or <code>TYPE_BYTE_GRAY</code>
  * depending on their <code>ColorModel</code>.

  * <p> When color data is stored in an image of this type,
  * the closest color in the colormap is determined
  * by the <code>IndexColorModel</code> and the resulting index is stored.
  * Approximation and loss of alpha or color components
  * can result, depending on the colors in the
  * <code>IndexColorModel</code> colormap.
  */
  TYPE_BYTE_BINARY = 12,

 /**
  * Represents an indexed byte image.  When this type is used as the
  * <code>imageType</code> argument to the <code>BufferedImage</code>
  * constructor that takes an <code>imageType</code> argument
  * but no <code>ColorModel</code> argument, an
  * <code>IndexColorModel</code> is created with
  * a 256-color 6/6/6 color cube palette with the rest of the colors
  * from 216-255 populated by grayscale values in the
  * default sRGB ColorSpace.
  *
  * <p> When color data is stored in an image of this type,
  * the closest color in the colormap is determined
  * by the <code>IndexColorModel</code> and the resulting index is stored.
  * Approximation and loss of alpha or color components
  * can result, depending on the colors in the
  * <code>IndexColorModel</code> colormap.
  */
  TYPE_BYTE_INDEXED = 13
 };
private:
 /*private*/ int imageType;// = TYPE_CUSTOM;
// /*private*/ ColorModel colorModel;
// /*private*/ final WritableRaster raster;
// /*private*/ OffScreenImageSource osis;
 /*private*/ QHash<QString, QVariant> properties;

 enum MASKS
 {
   DCM_RED_MASK   = 0x00ff0000,
   DCM_GREEN_MASK = 0x0000ff00,
   DCM_BLUE_MASK  = 0x000000ff,
   DCM_ALPHA_MASK = 0xff000000,
   DCM_565_RED_MASK = 0xf800,
   DCM_565_GRN_MASK = 0x07E0,
   DCM_565_BLU_MASK = 0x001F,
   DCM_555_RED_MASK = 0x7C00,
   DCM_555_GRN_MASK = 0x03E0,
   DCM_555_BLU_MASK = 0x001F,
   DCM_BGR_RED_MASK = 0x0000ff,
   DCM_BGR_GRN_MASK = 0x00ff00,
   DCM_BGR_BLU_MASK = 0xff0000

 };
};

#endif // BUFFEREDIMAGE_H
