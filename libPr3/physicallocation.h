#ifndef PHYSICALLOCATION_H
#define PHYSICALLOCATION_H

#include <QObject>
#include "namedbean.h"
#include "exceptions.h"
#include "logger.h"
#include <QVector3D>
#include <QVector>

class LIBPR3SHARED_EXPORT PhysicalLocation : public QObject
{
 Q_OBJECT
public:
    /** Default constructor */
    /*public*/ PhysicalLocation();
    /** Constructor from X, Y, Z (float)  + is_tunnel (bool) */
    /*public*/ PhysicalLocation(float x, float y, float z, bool is_tunnel);
    /** Constructor from X, Y, Z (float) */
    /*public*/ PhysicalLocation(float x, float y, float z) ;
    /** Constructor from X, Y, Z (double) */
    /*public*/ PhysicalLocation(double x, double y, double z);
    /** Constructor from X, Y, Z (double) */
    /*public*/ PhysicalLocation(double x, double y, double z, bool is_tunnel) ;
    /** Copy Constructor */
    /*public*/ PhysicalLocation(const PhysicalLocation& p) ;
    /*public*/ PhysicalLocation(QVector3D v);


    /** Origin : constant representation of (0, 0, 0) */
    /*public*/ static /*final*/ PhysicalLocation* Origin;// = new PhysicalLocation(0.0f, 0.0f, 0.0f);

    /** NBPropertyKey : Key name used when storing a PhysicalLocation as a NamedBean Property */
    /*public*/ static /*final*/ QString NBPropertyKey;// = "physical_location";
    /** translate()
     *
     * Return a PhysicalLocation that represents the position of point "loc" relative to
     * reference point "ref".
     *
     * @param loc : PhysicalLocation to translate
     * @param ref : PhysicalLocation to use as new reference point (origin)
     * @return PhysicalLocation
     */
    /*public*/ static PhysicalLocation* translate(PhysicalLocation* loc, PhysicalLocation* ref);
    /** getBeanPhysicalLocation(NamedBean b)
     *
     * Extract the PhysicalLocation stored in NamedBean b, and return as
     * a new PhysicalLocation object.
     *
     * If the given NamedBean does not have a PhysicalLocation property
     * returns Origin.  (should probably return null instead, but...)
     *
     * @param b : NamedBean
     * @return PhysicalLocation
     */
    /*public*/ static PhysicalLocation* getBeanPhysicalLocation(NamedBean* b);
    /** setBeanPhysicalLocation(PhysicalLocation p, NamedBean b)
     *
     * Store PhysicalLocation p as a property in NamedBean b.
     *
     * @param p PhysicalLocation
     * @param b NamedBean
     */
    /*public*/ static void setBeanPhysicalLocation(PhysicalLocation* p, NamedBean* b);
#if 0 // TODO:
/** Get a panel component that can be used to view and/or edit a location. */
    static /*public*/ PhysicalLocationPanel* getPanel(QString title) ;

#endif
/** Parse a string representation (x,y,z)
 * Returns a new PhysicalLocation object.
 *
 * @param pos : String "(X, Y, Z)"
 * @return PhysicalLocation
 */
static /*public*/ PhysicalLocation* parse(QString pos);
/** toString()
 *
 * Output a string representation (x,y,z)
 *
 * @return String  "(X, Y, Z)"
 */
/*public*/ QString toString();
/** Get X dimension */
/*public*/ float getX() const;
/** Set X dimension */
/*public*/ void setX(float x);
/** Get Y dimension */
/*public*/ float getY() const;
/** Set Y dimension */
/*public*/ void setY(float y);
/** Get Z dimension */
/*public*/ float getZ() const;
/** Set Z dimension */
/*public*/ void setZ(float z);
/*public*/ bool isTunnel() const ;
/*public*/ void setIsTunnel(bool t);
/** equals() */
/*public*/ bool equals(PhysicalLocation* l);
/** translate()
 *
 * Translate this PhysicalLocation's coordinates to be relative to point "ref".
 * NOTE: This is a "permanent" internal translation, and permanently changes
 * this PhysicalLocation's value.
 *
 * If you want a new PhysicalLocation that represents the relative position,
 * call the class method translate(loc, ref)
 *
 *  @param ref new reference (origin) point
 */
/*public*/ void translate(PhysicalLocation* ref);

signals:
    
public slots:
private:
 Logger log;
  QVector<float>  f;// = new QVector<float>(3);  // used for extracting a single dimension
                               // from the underlying vector.
  QVector3D _location;
 /*private*/ bool _isTunnel;
};

#endif // PHYSICALLOCATION_H
