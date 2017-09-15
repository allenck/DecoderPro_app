#ifndef AFFINETRANSFORM_H
#define AFFINETRANSFORM_H
#include <QVector>

class Logger;
class AffineTransform
{
public:
 AffineTransform();
 /*public*/ static /*final*/ int TYPE_IDENTITY;// = 0;
 /*public*/ static /*final*/ int TYPE_TRANSLATION;// = 1;
 /*public*/ static /*final*/ int TYPE_UNIFORM_SCALE;// = 2;
 /*public*/ static /*final*/ int TYPE_GENERAL_SCALE;// = 4;
 /*public*/ static /*final*/ int TYPE_MASK_SCALE;// = (TYPE_UNIFORM_SCALE |
//                                                TYPE_GENERAL_SCALE);
 /*public*/ static /*final*/ int TYPE_FLIP;// = 64;
 /*public*/ static /*final*/ int TYPE_QUADRANT_ROTATION;// = 8;
 /*public*/ static /*final*/ int TYPE_GENERAL_ROTATION;// = 16;
 /*public*/ static /*final*/ int TYPE_MASK_ROTATION;// = (TYPE_QUADRANT_ROTATION |
//                                               TYPE_GENERAL_ROTATION);
 /*public*/ static /*final*/ int TYPE_GENERAL_TRANSFORM;// = 32;
 /*private*/ AffineTransform(double m00, double m10,
                         double m01, double m11,
                         double m02, double m12,
                         int state);
 /*public*/ AffineTransform(float m00, float m10,
                        float m01, float m11,
                        float m02, float m12);
 /*public*/ AffineTransform(const AffineTransform& Tx);

 /*public*/ void transform(QVector<float>* srcPts, int srcOff,
                       QVector<float>* dstPts, int dstOff,
                       int numPts);
 /*public*/ void transform(QVector<double>* srcPts, int srcOff,
                       QVector<double>* dstPts, int dstOff,
                       int numPts);
 /*public*/ void transform(QVector<float>* srcPts, int srcOff,
                       QVector<double>* dstPts, int dstOff,
                       int numPts);
 /*public*/ AffineTransform* createInverse();
 /*public*/ void setToTranslation(double tx, double ty);
 /*public*/ void setToRotation(double theta);
 /*public*/ void setToRotation(double theta, double anchorx, double anchory);
 /*public*/ void setToRotation(double vecx, double vecy);
 /*public*/ void setToRotation(double vecx, double vecy,
                           double anchorx, double anchory);
private:
 static void arraycopy(QVector<float>* srcPts, int srcOff, QVector<float>* dstPts, int dstOff, int numPts);
 static void arraycopy(QVector<double>* srcPts, int srcOff, QVector<double>* dstPts, int dstOff, int numPts);

 /*private*/ static /*final*/ int TYPE_UNKNOWN;// = -1;
 static /*final*/ int APPLY_IDENTITY;// = 0;
 static /*final*/ int APPLY_TRANSLATE;// = 1;
 static /*final*/ int APPLY_SCALE;// = 2;
 static /*final*/ int APPLY_SHEAR;// = 4;
 /*private*/ static /*final*/ int HI_SHIFT;// = 3;
 /*private*/ static /*final*/ int HI_IDENTITY;// = APPLY_IDENTITY << HI_SHIFT;
 /*private*/ static /*final*/ int HI_TRANSLATE;// = APPLY_TRANSLATE << HI_SHIFT;
 /*private*/ static /*final*/ int HI_SCALE;// = APPLY_SCALE << HI_SHIFT;
 /*private*/ static /*final*/ int HI_SHEAR;// = APPLY_SHEAR << HI_SHIFT;
 /**
  * The X coordinate scaling element of the 3x3
  * affine transformation matrix.
  *
  * @serial
  */
 double m00;

 /**
  * The Y coordinate shearing element of the 3x3
  * affine transformation matrix.
  *
  * @serial
  */
  double m10;

 /**
  * The X coordinate shearing element of the 3x3
  * affine transformation matrix.
  *
  * @serial
  */
  double m01;

 /**
  * The Y coordinate scaling element of the 3x3
  * affine transformation matrix.
  *
  * @serial
  */
  double m11;

 /**
  * The X coordinate of the translation element of the
  * 3x3 affine transformation matrix.
  *
  * @serial
  */
  double m02;

 /**
  * The Y coordinate of the translation element of the
  * 3x3 affine transformation matrix.
  *
  * @serial
  */
  double m12;

 /**
  * This field keeps track of which components of the matrix need to
  * be applied when performing a transformation.
  * @see #APPLY_IDENTITY
  * @see #APPLY_TRANSLATE
  * @see #APPLY_SCALE
  * @see #APPLY_SHEAR
  */
 /*transient*/ int state;

 /**
  * This field caches the current transformation type of the matrix.
  * @see #TYPE_IDENTITY
  * @see #TYPE_TRANSLATION
  * @see #TYPE_UNIFORM_SCALE
  * @see #TYPE_GENERAL_SCALE
  * @see #TYPE_FLIP
  * @see #TYPE_QUADRANT_ROTATION
  * @see #TYPE_GENERAL_ROTATION
  * @see #TYPE_GENERAL_TRANSFORM
  * @see #TYPE_UNKNOWN
  * @see #getType
  */
 /*private*/ /*transient*/ int type;
  void updateState();
  /*private*/ void stateError();
  Logger* log;
  friend class CopyIterator;
};

#endif // AFFINETRANSFORM_H
