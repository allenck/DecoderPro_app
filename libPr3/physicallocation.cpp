#include "physicallocation.h"
#include <QVector>
#include <QRegExp>

PhysicalLocation* PhysicalLocation::Origin = new PhysicalLocation(0.0f, 0.0f, 0.0f);
QString PhysicalLocation::NBPropertyKey = "physical_location";

//PhysicalLocation::PhysicalLocation(QObject *parent) :
//    QObject(parent)
//{
//    f = new QVector<float>(3);  // used for extracting a single dimension
//                               // from the underlying vector.
//    _isTunnel = false;

//}
/** PhysicalLocation
 *
 * Represents a physical location on the layout in 3D space.
 *
 * Dimension units are not specified, but should be kept consistent in
 * all three dimensions for a given usage.
 *
 * Used by VSDecoder for spatially positioning sounds on the layout.
 *
 * Could also be used, for example, for velocity calculations between
 * sensors, or for keying operations locations or panel icons to a
 * physical map view of the layout.
 *
 */


//public class PhysicalLocation extends Vector3f {
    // Class methods
/** translate()
 *
 * Return a PhysicalLocation that represents the position of point "loc" relative to
 * reference point "ref".
 *
 * @param loc : PhysicalLocation to translate
 * @param ref : PhysicalLocation to use as new reference point (origin)
 * @return PhysicalLocation
 */
/*public*/ /*static*/ PhysicalLocation* PhysicalLocation::translate(PhysicalLocation* loc, PhysicalLocation* ref) {
if (loc == NULL || ref == NULL)
    return(NULL);
PhysicalLocation* rv = new PhysicalLocation();
rv->setX(loc->getX() - ref->getX());
rv->setY(loc->getY() - ref->getY());
rv->setZ(loc->getZ() - ref->getZ());
return(rv);
}

/** getBeanPhysicalLocation(NamedBean b)
 *
 * Extract the PhysicalLocation stored in NamedBean b, and return as
 * a new PhysicalLocation object.
 *
 * If the given NamedBean does not have a PhysicalLocation property
 * returns Origin.  (should probably return NULL instead, but...)
 *
 * @param b : NamedBean
 * @return PhysicalLocation
 */
/*public*/ /*static*/ PhysicalLocation* PhysicalLocation::getBeanPhysicalLocation(NamedBean* b)
{
 QString s = b->getProperty(PhysicalLocation::NBPropertyKey).toString();
 if ((s == NULL) || (s==("")))
 {
  return(PhysicalLocation::Origin);
 }
 else
 {
  return(PhysicalLocation::parse(s));
 }
}

/** setBeanPhysicalLocation(PhysicalLocation p, NamedBean b)
 *
 * Store PhysicalLocation p as a property in NamedBean b.
 *
 * @param p PhysicalLocation
 * @param b NamedBean
 */
/*public*/ /*static*/ void PhysicalLocation::setBeanPhysicalLocation(PhysicalLocation* p, NamedBean* b)
{
 b->setProperty(PhysicalLocation::NBPropertyKey,  p->toString());
}

#if 0 // TODO:
/** Get a panel component that can be used to view and/or edit a location. */
static /*public*/ PhysicalLocationPanel* PhysicalLocation::getPanel(QString title) {
return(new PhysicalLocationPanel(title));
}
#endif

/** Parse a string representation (x,y,z)
 * Returns a new PhysicalLocation object.
 *
 * @param pos : String "(X, Y, Z)"
 * @return PhysicalLocation
 */
/*static*/ /*public*/ PhysicalLocation* PhysicalLocation::parse(QString pos) {
// position is stored as a tuple string "(x,y,z)"
// Optional flags come immediately after the (x,y,z) in the form of "(flag)".
// Flags are bool. If they are present, they are true.
// Regex [-+]?[0-9]*\.?[0-9]+
//String syntax = "\\((\\s*[-+]?[0-9]*\\.?[0-9]+),(\\s*[-+]?[0-9]*\\.?[0-9]+),(\\s*[-+]?[0-9]*\\.?[0-9]+)\\)";
QString syntax = "\\((\\s*[-+]?[0-9]*\\.?[0-9]+),(\\s*[-+]?[0-9]*\\.?[0-9]+),(\\s*[-+]?[0-9]*\\.?[0-9]+)\\)(\\([tunnel]\\))*";
#if 0 // TODO:
try {
    Pattern* p = Pattern.compile(syntax);
    Matcher* m = p.matcher(pos);
    if (!m.matches()) {
    log.error("String does not match a valid position pattern. syntax= " + syntax + " string = " + pos);
    return(NULL);
    }
    // ++debug
    QString xs = m.group(1);
    QString ys = m.group(2);
    QString zs = m.group(3);
    log.debug("Loading position: x = " + xs + " y = " + ys + " z = " + zs);
    // --debug
    bool is_tunnel = false;
    // Handle optional flags
    for (int i = 4; i < m.groupCount()+1; i++) {
    if ((m.group(i) != NULL) && (m.group(i) == "(tunnel)"))
        is_tunnel = true;
    }

    return(new PhysicalLocation(Float.parseFloat(m.group(1)),
                Float.parseFloat(m.group(2)),
                Float.parseFloat(m.group(3)),
                is_tunnel));
} catch(PatternSyntaxException* e) {
    log.error("Malformed listener position syntax! " + syntax);
    return(NULL);
} catch(IllegalStateException* e) {
    log.error("Group called before match operation executed syntax=" + syntax + " string= " + pos + " " + e.toString());
    return(NULL);
} catch (IndexOutOfBoundsException* e) {
    log.error("Index out of bounds " + syntax + " string= " + pos + " " + e.toString());
    return(NULL);
}
#else
QRegExp regExp(syntax);
if(regExp.exactMatch(pos))
{
 QStringList sl = pos.split(",");
 bool is_tunnel = false;

 if(sl.count()>3 && sl[3] == "tunnel")
     is_tunnel = true;
 return new PhysicalLocation(sl[0].toFloat(), sl[1].toFloat(), sl[2].toFloat(), is_tunnel);

}
else
{
 Logger log;
 log.error("String does not match a valid position pattern. syntax= " + syntax + " string = " + pos);
 return NULL;
}
#endif
}

/** toString()
 *
 * Output a string representation (x,y,z)
 *
 * @return String  "(X, Y, Z)"
 */
/*public*/ QString PhysicalLocation::toString()
{
 QString s = "(" + QString("%1").arg(this->getX()) + ", "+ QString("%1").arg(this->getY()) + ", " + QString("%1").arg(this->getZ()) + ")";
 if (_isTunnel)
 {
    s += "(tunnel)";
 }
 return(s);
}
#if 0 // TODO:
/*public*/ Vector3d PhysicalLocation::toVector3d() {
return(new Vector3d(this));
}
#endif
// Instance methods

/** Default constructor */
/*public*/ PhysicalLocation::PhysicalLocation()
{
//super();
 f = QVector<float>(3);
_isTunnel = false;
}
#if 0
/** Constructor from Vector3f */
/*public*/ PhysicalLocation(Vector3f v) {
super(v);
_isTunnel = false;
}
#endif
/*public*/ PhysicalLocation::PhysicalLocation(QVector3D v)

{
 //super(v);
 f = QVector<float>(3);
 _location = v;
 _isTunnel = false;
}

/** Constructor from X, Y, Z (float)  + is_tunnel (bool) */
/*public*/ PhysicalLocation::PhysicalLocation(float x, float y, float z, bool is_tunnel)
{
 //super(x, y, z);
 f = QVector<float>(3);
 _location = QVector3D(x, y, z);
    f.clear();
    f.append(x);
    f.append(y);
    f.append(z);
 _isTunnel = is_tunnel;
}

/** Constructor from X, Y, Z (float) */
/*public*/ PhysicalLocation::PhysicalLocation(float x, float y, float z)
{
 f = QVector<float>(3);
_location = QVector3D(x, y, z);
_isTunnel = false;

}

/** Constructor from X, Y, Z (double) */
/*public*/ PhysicalLocation::PhysicalLocation(double x, double y, double z)
{
 //super(x, y, z);
  f = QVector<float>(3);
 _location = QVector3D(x, y, z);
   f.replace(0, x);
   f.replace(1,y);
   f.replace(2,z);
_isTunnel = false;
}

/** Constructor from X, Y, Z (double) */
/*public*/ PhysicalLocation::PhysicalLocation(double x, double y, double z, bool is_tunnel)
{
 //super(x, y, z);
 f = QVector<float>(3);
 _location = QVector3D(x, y, z);
 f.replace(0, x);
 f.replace(1,y);
 f.replace(2,z);
_isTunnel = is_tunnel;
}

/** Copy Constructor */
/*public*/ PhysicalLocation::PhysicalLocation(const PhysicalLocation& p)
{
 //super(p.getX(), p.getY(), p.getZ());
 f = QVector<float>(3);

 f.replace(0, p.getX());
 f.replace(1, p.getY());
 f.replace(2, p.getZ());
 this->setX(p.getX());
 this->setY(p.getY());
 this->setZ(p.getZ());
 this->setIsTunnel(p.isTunnel());
}

/** Get X dimension */
/*public*/ float PhysicalLocation::getX() const
{
 //this->get(f);
 return f.at(0);
}

/** Set X dimension */
/*public*/ void PhysicalLocation::setX(float x) {
//this->get(f);
f.replace(0, x);
//this->set(f);
}

/** Get Y dimension */
/*public*/ float PhysicalLocation::getY() const {
//this->get(f);
    return(f.at(1));
}

/** Set Y dimension */
/*public*/ void PhysicalLocation::setY(float y) {
//this->get(f);
f.replace(1,y);
//this->set(f);
}

/** Get Z dimension */
/*public*/ float PhysicalLocation::getZ()  const {
//this->get(f);
return(f.at(2));
}

/** Set Z dimension */
/*public*/ void PhysicalLocation::setZ(float z) {
//this->get(f);
f.replace(2,z);
//this->set(f);
}

/*public*/ bool PhysicalLocation::isTunnel() const {
return(_isTunnel);
}

/*public*/ void PhysicalLocation::setIsTunnel(bool t) {
_isTunnel = t;
}

/** equals() */
/*public*/ bool PhysicalLocation::equals(PhysicalLocation* l) {
if ((this->getX() == l->getX()) &&
    (this->getY() == l->getY()) &&
    (this->getZ() == l->getZ()) &&
    (this->isTunnel() == l->isTunnel())) {
    return (true);
} else {
    return(false);
}
}

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
/*public*/ void PhysicalLocation::translate(PhysicalLocation* ref) {
if (ref == NULL)
    return;

this->setX(this->getX() - ref->getX());
this->setY(this->getY() - ref->getY());
this->setZ(this->getZ() - ref->getZ());
}



//private static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PhysicalLocation.class.getName());

