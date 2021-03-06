#include "path.h"
#include <QtMath>
#include "mathutil.h"

Path::Path(QObject *parent) :
    QObject(parent)
{
 _beans = new QVector<BeanSetting*>();
}
/**
 * Represents a particular set of
 * NamedBean (usually turnout) settings to put a path through
 * trackwork to a Block.
 * <P>
 * Directions are defined for traffic along this path "to" the block, and
 * "from" the block.
 * Being more specific:
 *<UL>
 *<LI>The "to" direction is the direction that a train is going
 * when it traverses this path "to" the final block.
 *<LI>The "from" direction is the direction that a train is going
 * when it traverses this path "from" the final block.
 *</UL>
 * Although useful constants are defined, you don't
 * have to restrict to those, and there's no assumption that they have
 * to be opposites; NORTH for "to" does not imply SOUTH for "from".
 * This allows you to e.g. handle a piece of curved track where you
 * can be going LEFT at one point and UP at another. The constants
 * are defined as bits, so you can use more than one at a time, for
 * example a direction can simultanously be EAST and RIGHT if desired.
 * What that means needs to be defined by whatever object is using this Path.
 * <P>
 * This implementation handles paths with a list of bean settings. This has
 * been extended from the initial implementation.
 *
 * @author	Bob Jacobsen  Copyright (C) 2006, 2008
 * @version	$Revision: 17977 $
 */
//public class Path  {

    /**
     * Create an object with default directions of NONE, and
     * no setting element.
     */
//    public Path() {
//    }

/**
 * Convenience constructor to set the destination/source block
 * and directions in one call.
 */
/*public*/ Path::Path(Block* dest, int toBlockDirection, int fromBlockDirection, QObject *parent) : QObject(parent)
{
 //this();
 common();
 _toBlockDirection = toBlockDirection;
 _fromBlockDirection = fromBlockDirection;
 setBlock(dest);
}

/**
 * Convenience constructor to set the destination/source block,
 * directions and a single setting element in one call.
 */
/*public*/ Path::Path(Block* dest, int toBlockDirection, int fromBlockDirection, BeanSetting* setting, QObject *parent) : QObject(parent)
{
 common();
 //this(dest, toBlockDirection, fromBlockDirection);
 _toBlockDirection = toBlockDirection;
 _fromBlockDirection = fromBlockDirection;
 this->_block = dest;
 addSetting(setting);
}
void Path::common()
{
 _beans = new QVector<BeanSetting*>();
 _length = 0.0f;  // always stored in millimeters
}

/*public*/ void Path::addSetting(BeanSetting* t) {
    _beans->append(t);
}

/*public*/ QList<BeanSetting*> Path::getSettings() {
    return _beans->toList();
}

/*public*/ void Path::removeSetting(BeanSetting* t) {
    _beans->remove(_beans->indexOf(t));
}

/*public*/ void Path::clearSettings() {
    for (int i = _beans->size();i>0;i--) {
        _beans->remove(i-1);
    }
}

/*public*/ void Path::setBlock(Block* b) {
    _block = b;
}

/*public*/ Block* Path::getBlock() {
    return _block;
}

/*public*/ int Path::getToBlockDirection() { return _toBlockDirection; }
/*public*/ void Path::setToBlockDirection(int d) { _toBlockDirection = d; }

/*public*/ int Path::getFromBlockDirection() { return _fromBlockDirection; }
/*public*/ void Path::setFromBlockDirection(int d) { _fromBlockDirection = d; }

/**
 * Check that the Path can be traversed.
 * This means that any path elements are set to the
 * proper state, e.g. that the Turnouts on this path
 * are set to the proper CLOSED or OPEN status.
 * @return true if the path can be traversed; always true
 * if no path elements (BeanSettings) are defined.
 */
/*public*/ bool Path::checkPathSet() {
    // empty conditions are always set
    if (_beans->size()==0) return true;
    // check the status of all BeanSettings
    for (int i = 0;i<_beans->size();i++) {
        if (!(_beans->at(i))->check())
            return false;
    }
    return true;
}

/**
 * Direction not known or not specified. May also
 * represent "stopped", in the sense of not moving in any direction.
 */
/*public*/ const static /*final*/ int NONE  =0x00000;
/**
 * Northward
 */
/*public*/ const static /*final*/ int NORTH =0x00010;
/**
 * Southward
 */
/*public*/ const static /*final*/ int SOUTH =0x00020;
/**
 * Eastward
 */
/*public*/ const static /*final*/ int EAST  =0x00040;
/**
 * Westward
 */
/*public*/ const static /*final*/ int WEST  =0x00080;
/**
 * Clockwise
 */
/*public*/ const static /*final*/ int CW    =0x00100;
/**
 * Counter-clockwise
 */
/*public*/ const static /*final*/ int CCW   =0x00200;
/**
 * Leftward, e.g. on a schematic diagram or CTC panel
 */
/*public*/ const static /*final*/ int LEFT  =0x00400;
/**
 * Rightward, e.g. on a schematic diagram or CTC panel
 */
/*public*/ const static /*final*/ int RIGHT =0x00800;
/**
 * Upward, e.g. on a schematic diagram or CTC panel
 */
/*public*/ const static /*final*/ int UP    =0x01000;
/**
 * Downward, e.g. on a schematic diagram or CTC panel
 */
/*public*/ const static /*final*/ int DOWN  =0x02000;

/**
 * Decode the direction constants into a human-readable
 * form.
 * This should eventually be internationalized.
 */
/*static*/ /*public*/ QString Path::decodeDirection(int d)
{
    if ( d==NONE ) return "None";

    //StringBbuffer* b = new StringBbuffer();
    QString b;
    if ( (d&NORTH)!=0)  appendOne(b,"North");
    if ( (d&SOUTH)!=0)  appendOne(b,"South");
    if ( (d&EAST)!=0)   appendOne(b,"East");
    if ( (d&WEST)!=0)   appendOne(b,"West");
    if ( (d&CW)!=0)     appendOne(b,"CW");
    if ( (d&CCW)!=0)    appendOne(b,"CCW");
    if ( (d&LEFT)!=0)   appendOne(b,"Left");
    if ( (d&RIGHT)!=0)  appendOne(b,"Right");
    if ( (d&UP)!=0)     appendOne(b,"Up");
    if ( (d&DOWN)!=0)   appendOne(b,"Down");
    /*final*/ int mask = NORTH|SOUTH|EAST|WEST|CW|CCW|LEFT|RIGHT|UP|DOWN;
    if ( (d & ~mask ) != 0)
        appendOne(b, "Unknown: 0x"+QString("%1").arg(d&~mask,0,16));
    return b/*.toString()*/;
}
/*public*/ void Path::setLength(float l)
{
 _length = l;
}  // l must be in millimeters

/**
 * Get actual stored length.
 *
 * @return length in millimeters or 0
 */
/*public*/ float Path::getLength() {
    return _length;
}

/*public*/ float Path::getLengthMm() {
    if (_length <= 0.0f) {
        return _block->getLengthMm();
    }
    return _length;
} // return length in millimeters

/*public*/ float Path::getLengthCm() {
    if (_length <= 0.0f) {
        return _block->getLengthCm();
    }
    return (_length / 10.0f);
}  // return length in centimeters

/*public*/ float Path::getLengthIn() {
    if (_length <= 0.0f) {
        return _block->getLengthIn();
    }
    return (_length / 25.4f);
}  // return length in inches
/*static*/ /*private*/ void Path::appendOne(QString b, QString t) {
    if (b.length()!=0) b.append(", ");
    b.append(t);
}
//@Override
//@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "FE_FLOATING_POINT_EQUALITY", justification = "equals operator should actually check for equality")
/*public*/ bool Path::equals(QObject* obj) {
    if (obj == this) {
        return true;
    }
    if (obj == nullptr) {
        return false;
    }

    if (!(metaObject()->className() == obj->metaObject()->className())) {
        return false;
    } else {
        Path* p = (Path*) obj;

        if (!(p->_length) == (this->_length)) {
            return false;
        }

        if (p->_toBlockDirection != this->_toBlockDirection) {
            return false;
        }
        if (p->_fromBlockDirection != this->_fromBlockDirection) {
            return false;
        }

        if (p->_block == nullptr && this->_block != nullptr) {
            return false;
        }
        if (p->_block != nullptr && this->_block == nullptr) {
            return false;
        }
        if (p->_block != nullptr && this->_block != nullptr && !p->_block->equals(this->_block)) {
            return false;
        }

        if (p->_beans->size() != this->_beans->size()) {
            return false;
        }
        for (int i = 0; i < p->_beans->size(); i++) {
            if (!(p->_beans->at(i) == (this->_beans->at(i))))
            {
                return false;
            }
        }
    }
    //return this->hashCode() == obj.hashCode();
    return true;
}

//@Override
/*public*/ QString Path::toString() {
    QString result;// = new StringBuilder();
    QString separator = ""; // no separator on first item // NOI18N
    for (BeanSetting* beanSetting : this->getSettings()) {
        result.append(separator).append(tr("%1 with state {%2").arg(beanSetting->getBean()->getDisplayName()).arg(beanSetting->getBean()->describeState(beanSetting->getSetting()))); // NOI18N
        separator = ", "; // NOI18N
    }
    return tr("Path: \"%1\" (%2): %3").arg(getBlock()->getDisplayName()).arg(decodeDirection(getToBlockDirection())).arg(result); // NOI18N
}

//// Can't include _toBlockDirection, _fromBlockDirection, or block information as they can change
////@Override
///*public*/ int hashCode() {
//    int hash = 7;
//    hash = 89 * hash + Objects.hashCode(this._beans);
//    hash = 89 * hash + Objects.hashCode(this._block);
//    hash = 89 * hash + this._toBlockDirection;
//    hash = 89 * hash + this._fromBlockDirection;
//    hash = 89 * hash + Float.floatToIntBits(this._length);
//    return hash;
//}


/**
 * compute octagonal direction of vector from p1 to p2
 * <p>
 * Note: the octagonal (8) directions are: North, North-East, East,
 * South-East, South, South-West, West and North-West
 *
 * @param p1 the first point
 * @param p2 the second point
 * @return the octagonal direction from p1 to p2
 */
/*public*/ /*static*/ int Path::computeDirection(QPointF p1, QPointF p2) {

    double angleDEG;// = MathUtil.computeAngleDEG(p2, p1);
    qRadiansToDegrees(atan2(p1.y() - p2.y(), p1.x() - p2.x()));
    angleDEG = MathUtil::wrap360(angleDEG);  // don't want to deal with negative numbers here...
     while (angleDEG < 0 )
     {
      angleDEG -= 360.0;
     }

    // convert the angleDEG into an octant index (ccw from south)
    // note: because we use round here, the octants are offset by half (+/-22.5 deg)
    // so SOUTH isn't from 0-45 deg; it's from -22.5 deg to +22.5 deg; etc. for other octants.
    // (and this is what we want!)
    int octant = (int) qRound(angleDEG / 45.0);

    // use the octant index to lookup its direction
    QVector<int> dirs = QVector<int>() << SOUTH << SOUTH_EAST << EAST << NORTH_EAST <<
        NORTH << NORTH_WEST << WEST<< SOUTH_WEST << SOUTH;
    return dirs.at(octant);
}   // computeOctagonalDirection

/**
 * return the reverse octagonal direction
 *
 * @param inDir the direction
 * @return the reverse direction or {@value #NONE} if inDir is not a
 *         direction
 */
/*public*/ /*static*/ int Path::reverseDirection(int inDir) {
    switch (inDir) {
        case NORTH:
            return SOUTH;
        case NORTH_EAST:
            return SOUTH_WEST;
        case EAST:
            return WEST;
        case SOUTH_EAST:
            return NORTH_WEST;
        case SOUTH:
            return NORTH;
        case SOUTH_WEST:
            return NORTH_EAST;
        case WEST:
            return EAST;
        case NORTH_WEST:
            return SOUTH_EAST;
        default:
            return NONE;
    }
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(Path.class.getName());
//}
