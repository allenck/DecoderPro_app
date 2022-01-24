#include "colorutil.h"
#include "loggerfactory.h"

ColorUtil::ColorUtil()
{

}
/*
 * Color lists for screen colors.
 */
/*public final static*/ QString ColorUtil::ColorTrack = "track";
/*public final static*/ QString ColorUtil::ColorBlack = "black";
/*public final static*/ QString ColorUtil::ColorDarkGray = "darkGray";
/*public final static*/ QString ColorUtil::ColorGray = "gray";
/*public final static*/ QString ColorUtil::ColorLightGray = "lightGray";
/*public final static*/ QString ColorUtil::ColorWhite = "white";
/*public final static*/ QString ColorUtil::ColorRed = "red";
/*public final static*/ QString ColorUtil::ColorPink = "pink";
/*public final static*/ QString ColorUtil::ColorOrange = "orange";
/*public final static*/ QString ColorUtil::ColorYellow = "yellow";
/*public final static*/ QString ColorUtil::ColorGreen = "green";
/*public final static*/ QString ColorUtil::ColorBlue = "blue";
/*public final static*/ QString ColorUtil::ColorMagenta = "magenta";
/*public final static*/ QString ColorUtil::ColorCyan = "cyan";
/*public final static*/ QString ColorUtil::ColorClear = "clear";
/*public final static*/ QString ColorUtil::ColorBrown = "brown";

/*public*/ /*final*/ /*static*/ QColor ColorUtil::clear = ColorUtil::setAlpha(QColor(Qt::black), 0);
/*public*/ /*final*/ /*static*/ QColor ColorUtil::CLEAR = ColorUtil::clear;
/*public*/ /*final*/ /*static*/ QColor ColorUtil::BROWN = QColor(102, 51, 0);

/**
 * A collection of utilities related to colors.
 *
 * @author Dave Duchamp Copyright: (c) 2004-2007
 */
///*public*/ class ColorUtil {

/**
 * Handles known colors plus special value for track
 *
 * @param color the color or null
 * @return the name of the color or "black" if a color was provided; "track"
 *         if color is null
 */
//@Nonnull
/*public*/ /*static*/ QString ColorUtil::colorToString(/*@Nullable*/ QColor color) {
    if (!color.isValid()) {
        return ColorTrack;
    }
    QString colorName = colorToName(color);
    if (colorName != "") {
        return colorName;
    }
    log->error("unknown color sent to colorToString");
    return ColorBlack;
}

/**
 * Returns known color name or hex value in form #RRGGBB
 *
 * @param color the color
 * @return the name or hex value of color; returns null if color is null
 */
//@CheckForNull
/*public*/ /*static*/ QString ColorUtil::colorToColorName(/*@Nullable*/ QColor color) {
    if (!color.isValid()) {
        return "";
    }
    QString colorName = colorToName(color);
    if (colorName != "") {
        return colorName;
    }
    //return colorToHexString(color);
    return color.name();
}

/*public*/ /*static*/ QColor ColorUtil::stringToColor(QString string)
{
 if(string.startsWith('#'))
 {
  QColor c = QColor(string);
  if(c.isValid())
   return c;
 }
    if(string == ColorBlack)
            return Qt::black;
     else if(string == ColorDarkGray)
            return Qt::darkGray;
     else if(string == ColorGray)
            return Qt::gray;
     else if(string == ColorLightGray)
            return Qt::lightGray;
     else if(string == ColorWhite)
            return Qt::white;
     else if(string == ColorRed)
            return Qt::red;
     else if(string == ColorPink)
            return QColor(255,233,236);
     else if(string == ColorOrange)
            return QColor(255,165,0);
     else if(string == ColorYellow)
            return Qt::yellow;
     else if(string == ColorGreen)
            return Qt::green;
     else if(string == ColorBlue)
            return Qt::blue;
     else if(string == ColorMagenta)
            return Qt::magenta;
     else if(string == ColorCyan)
            return Qt::cyan;
     else if(string == ColorBrown)
            return BROWN;
     else if(string == ColorTrack)
            return "";
    log->error("unknown color text '" + string + "' sent to stringToColor");
    throw new IllegalArgumentException("unknown color text '" + string + "'");
}

/**
 * Convert a color into hex value of form #RRGGBB.
 *
 * @param color the color or null
 * @return the hex string or null if color is null
 */
//@CheckForNull
/*public*/ /*static*/ QString ColorUtil::colorToHexString(/*@Nullable*/ QColor color) {
    if (!color.isValid()) {
        return "";
    }
    //return QString("#%1%2%3").arg(color.red(),2,16).arg( color.green(),2,16).arg(color.blue(),2,16).replace(' ','0');
    return color.name();
}

/**
 * Internal method to return string name of several known colors, returns
 * null if not in list.
 *
 * @param color the color
 * @return the color name or null if not known
 */
//'@CheckForNull
/*public*/ /*static*/ QString ColorUtil::colorToName(/*@Nullable*/ QColor color) {
    if (!color.isValid()) {
        return "";
    }
    foreach(QString s, QColor::colorNames())
    {
     if(QColor(s).name()== color.name())
      return s;
    }
    if (color == QColor(Qt::black)) {
        return ColorBlack;
    } else if (color== QColor(Qt::darkGray)) {
        return ColorDarkGray;
    } else if (color == QColor(Qt::gray)) {
        return ColorGray;
    } else if (color==QColor(Qt::lightGray)) {
        return ColorLightGray;
    } else if (color== QColor(Qt::white)) {
        return ColorWhite;
    } else if (color== QColor(Qt::red)) {
        return ColorRed;
    }
    else if (color == (QColor(255,233,236)))
    {
     return ColorPink;
    }
    else if (color == (QColor(255,165,0)))
    {
        return ColorOrange;
    }
    else if (color== QColor(Qt::yellow)) {
        return ColorYellow;
    } else if (color== QColor(Qt::green)) {
        return ColorGreen;
    } else if (color == QColor(Qt::blue)) {
        return ColorBlue;
    } else if (color== QColor(Qt::magenta)) {
        return ColorMagenta;
    } else if (color== QColor(Qt::cyan)) {
        return ColorCyan;
    } else if (color == (BROWN)) {
     return ColorBrown;
 }
//    else
//    return QString("rgb(%1,%2,%3,%4) '%5'").arg(colorIn.red()).arg(colorIn.green()).arg(colorIn.blue()).arg(colorIn.alpha()).arg(name);
    return "";
}

/**
 * Return the color (Black/White) that most contrasts with the specified
 * color.
 *
 * @param color the source color
 * @return the contrasting color
 */
/*public*/ /*static*/ QColor ColorUtil::contrast(/*@Nonnull*/ QColor color) {
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    int average = (red + green + blue) / 3;

    return (average >= 128) ? QColor(Qt::black) : QColor(Qt::white);
}
/**
 * set the alpha component of a color
 *
 * @param color the color
 * @param alpha the alpha component (integer 0 - 255)
 * @return the new color with the specified alpha
 */
//@CheckReturnValue
/*public*/ /*static*/ QColor ColorUtil::setAlpha(/*@Nonnull*/ QColor color, int alpha) {
    return QColor(color.red(), color.green(), color.blue(), alpha);
}

/**
 * set the alpha component of a color
 *
 * @param color the color
 * @param alpha the alpha component (double 0.0 - 1.0)
 * @return the new color with the specified alpha
 */
//@CheckReturnValue
/*public*/ /*static*/ QColor ColorUtil::setAlpha(/*@Nonnull*/ QColor color, double alpha) {
//    return  QColor(color.redF(), color.greenF(), color.blueF(),
//            (int) (255.0 * alpha));
 color.setAlphaF(alpha);
 return color;
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* ColorUtil::log = LoggerFactory::getLogger("ColorUtil");
