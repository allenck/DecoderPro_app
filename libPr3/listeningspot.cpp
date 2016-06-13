#include "listeningspot.h"
#include "logger.h"
#include "physicallocation.h"

//ListeningSpot::ListeningSpot(QObject *parent) :
//  QObject(parent)
//{
//}

/**
 * class ListeningSpot
 *
 * Represents a defined spot for viewing (and therefore listening to) a layout.
 *
 */

/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2012
 * @version			$Revision: 21510 $
 */
//import java.util.regex.Matcher;
//import java.util.regex.Pattern;
//import java.util.regex.PatternSyntaxException;
//import javax.vecmath.Vector3d;
//import javax.vecmath.Vector3f;
//import jmri.util.PhysicalLocation;
//import org.jdom2.Element;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

///*public*/ class ListeningSpot {


/*private*/ /*static final*/ QVector3D ListeningSpot::_rightVector =  QVector3D(0.0, 1.0, 0.0);
/*private*/ /*static final*/ QVector3D ListeningSpot::_upVector =  QVector3D(0.0, 0.0, 1.0);

/*public*/ ListeningSpot::ListeningSpot(QObject *parent) :
QObject(parent) {
 _name = "";
    _location =  QVector3D();
    _up = _upVector;
    _lookAt = _rightVector;
}
#if 0
    /*public*/ ListeningSpot(Vector3f position) {
        _name = null;
        _location = new Vector3d(position);
        _up = _upVector;
        _lookAt = _rightVector;
    }
#endif
/*public*/ ListeningSpot::ListeningSpot(QVector3D position) {
    //this(null, position);
 _name = "";
 _location = position;
 _lookAt = _rightVector;
 _up = _upVector;
}

/*public*/ ListeningSpot::ListeningSpot(QString name, QVector3D position) {
    _name = name;
    _location = position;
    _lookAt = _rightVector;
    _up = _upVector;
}

/*public*/ ListeningSpot::ListeningSpot(QString name, QVector3D loc, QVector3D up, QVector3D at) {
    _name = name;
    _location = loc;
    _up = up;
    _lookAt = at;
}

/*public*/ ListeningSpot::ListeningSpot(QDomElement e) {
    this->setXml(e);
}

/*public*/ QString ListeningSpot::getName() {
    return (_name);
}

/*public*/ QVector3D ListeningSpot::getLocation() {
    return (_location);
}

/*public*/ PhysicalLocation* ListeningSpot::getPhysicalLocation() {
#if 1
 return new PhysicalLocation(_location.x(), _location.y(), _location.z());
#endif
}
#if 0
    /*public*/ Vector3d getUpVector() {
        return (_up);
    }

    /*public*/ Vector3d getLookAtVector() {
        return (_lookAt);
    }

    /* TRig notes
     * Trig x = map y
     * Trig y = map x
     * bearing = theta
     * azimuth = 90 - rho
     * map y = r sin (90-azimuth) cos bearing
     * map x = r sin (90-azimuth) sin bearing
     * map z = r cos (90-azimuth)
     * r = sqrt( x^2 + y^2 + z^2 )
     * bearing = theta = atan(map x / map y)
     * azimuth = 90 - rho = 90 - acos(z / p)
     */
    /*public*/ Double getBearing() {
        //bearing = theta = atan(map x / map y)
        return (Math.toDegrees(Math.atan(_location.x / _location.y)));
    }

    /*public*/ Double getAzimuth() {
        // r = sqrt( x^2 + y^2 + z^2 )
        // azimuth = 90 - rho = 90 - acos(z / p)
        Double r = Math.sqrt(Math.pow(_location.x, 2.0d) + Math.pow(_location.y, 2.0d) + Math.pow(_location.z, 2.0d));
        return (Math.toDegrees(Math.acos(_location.z / r)));
    }

    /*public*/ void setName(String n) {
        _name = n;
    }

    /*public*/ void setLocation(Vector3d loc) {
        _location = loc;
    }

    /*public*/ void setLocation(Double x, Double y, Double z) {
        _location = new Vector3d(x, y, z);
    }

    /*public*/ void setLocation(PhysicalLocation l) {
        _location = new Vector3d(l.getX(), l.getY(), l.getZ());
    }

    /*public*/ void setUpVector(Vector3d up) {
        _up = up;
    }

    /*public*/ void setLookAtVector(Vector3d at) {
        _lookAt = at;
    }

    /*public*/ void setOrientation(PhysicalLocation target) {
        Vector3d la = new Vector3d();
        // Calculate the look-at vector
        la.sub(target.toVector3d(), _location);  // la = target - location
        la.normalize();
        _lookAt = la;
        // Calculate the up vector
        _up = calcUpFromLookAt(la);
    }

    /*private*/ Vector3d calcUpFromLookAt(Vector3d la) {
        Vector3d _la = la;
        _la.normalize();
        Vector3d up = new Vector3d();
        up.cross(_la, _rightVector);
        up.cross(up, _la);
        return (up);
    }

    /*public*/ void setOrientation(double bearing, double azimuth) {
        // Convert bearing + azimuth to look-at and up vectors.
        // Bearing measured clockwise from Y axis.
        // Azimuth measured up (or down) from X/Y plane.
        // map y = r sin (90-azimuth) cos bearing
        // map x = r sin (90-azimuth) sin bearing
        // map z = r cos (90-azimuth)
        // Assumes r = 1;
        double y = Math.sin(Math.toRadians(90 - azimuth)) * Math.cos(bearing);
        double x = Math.sin(Math.toRadians(90 - azimuth)) * Math.sin(bearing);
        double z = Math.cos(Math.toRadians(90 - azimuth));
        _lookAt = new Vector3d(x, y, z);
        _up = calcUpFromLookAt(_lookAt);
    }

    /*public*/ Boolean equals(ListeningSpot other) {
        if ((this._name.equals(other.getName()))
                && (this._location == other.getLocation())
                && (this._up == other.getUpVector())
                && (this._lookAt == other.getLookAtVector())) {
            return (true);
        } else {
            return (false);
        }
    }
#endif
/*private*/ QVector3D ListeningSpot::parseVector3d(QString pos)
{
 if (pos == "")
 {
  return (QVector3D());
 }
#if 0
    // position is stored as a tuple string "(x,y,z)"
    // Regex [-+]?[0-9]*\.?[0-9]+
    QString syntax = "\\((\\s*[-+]?[0-9]*\\.?[0-9]+),(\\s*[-+]?[0-9]*\\.?[0-9]+),(\\s*[-+]?[0-9]*\\.?[0-9]+)\\)";
    try {
        Pattern p = Pattern.compile(syntax);
        Matcher m = p.matcher(pos);
        if (!m.matches()) {
            log->error("String does not match a valid position pattern. syntax= " + syntax + " string = " + pos);
            return (null);
        }
        // ++debug
        String xs = m.group(1);
        String ys = m.group(2);
        String zs = m.group(3);
        log->debug("Loading Vector3d: x = " + xs + " y = " + ys + " z = " + zs);
        // --debug
        return (new Vector3d(Double.parseDouble(m.group(1)), Double.parseDouble(m.group(2)), Double.parseDouble(m.group(3))));
    } catch (PatternSyntaxException e) {
        log->error("Malformed Vector3d syntax! " + syntax);
        return (null);
    } catch (IllegalStateException e) {
        log->error("Group called before match operation executed syntax=" + syntax + " string= " + pos + " " + e.toString());
        return (null);
    } catch (IndexOutOfBoundsException e) {
        log->error("Index out of bounds " + syntax + " string= " + pos + " " + e.toString());
        return (null);
    }
#endif
}


/*public*/ QString ListeningSpot::toString() {
 if ((_location.isNull()) || (_lookAt.isNull()) || (_up.isNull())) {
        return ("ListeningSpot (undefined)");
    } else {
#if 0
        return ("ListeningSpot Name: " + _name + " Location: " + _location.toString() + " LookAt: " + _lookAt.toString() + " Up: " + _up.toString());
#endif
    }
}

/*public*/ QDomElement ListeningSpot::getXml(QString elementName) {
    QDomElement me = doc.createElement(elementName);
    me.setAttribute("name", _name);
#if 0
    me.setAttribute("location", _location.toString());
    me.setAttribute("up", _up.toString());
    me.setAttribute("look_at", _lookAt.toString());
#endif
    return (me);
}

/*public*/ void ListeningSpot::setXml(QDomElement e) {
    if (!e.isNull()) {
        log->debug("ListeningSpot: " + e.attribute("name"));
        _name = e.attribute("name");
        _location = parseVector3d(e.attribute("location"));
        _up = parseVector3d(e.attribute("up"));
        _lookAt = parseVector3d(e.attribute("look_at"));
    }
}

