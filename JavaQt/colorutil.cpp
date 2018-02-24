#include "colorutil.h"
#include "loggerfactory.h"

ColorUtil::ColorUtil()
{

}
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
        return "track";
    }
    QString colorName = colorToName(color);
    if (colorName != "") {
        return colorName;
    }
    log->error("unknown color sent to colorToString");
    return "black";
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
    return colorToHexString(color);
}

/*public*/ /*static*/ QColor ColorUtil::stringToColor(QString string) {
    if(string == "black")
            return Qt::black;
     else if(string == "darkGray")
            return Qt::darkGray;
     else if(string == "gray")
            return Qt::gray;
     else if(string == "lightGray")
            return Qt::lightGray;
     else if(string == "white")
            return Qt::white;
     else if(string == "red")
            return Qt::red;
     else if(string == "pink")
            return QColor(255,233,236);
     else if(string == "orange")
            return QColor(255,170,0);
     else if(string == "yellow")
            return Qt::yellow;
     else if(string == "green")
            return Qt::green;
     else if(string == "blue")
            return Qt::blue;
     else if(string == "magenta")
            return Qt::magenta;
     else if(string == "cyan")
            return Qt::cyan;
     else if(string == "track")
            return "";
    log->error("unknown color text '" + string + "' sent to stringToColor");
    return Qt::black;
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
    return QString("#%1X%2X%3X").arg(color.red()).arg( color.green()).arg(color.blue());
}

/**
 * Internal method to return string name of several known colors, returns
 * null if not in list.
 *
 * @param color the color
 * @return the color name or null if not known
 */
//'@CheckForNull
/*private*/ /*static*/ QString ColorUtil::colorToName(/*@Nullable*/ QColor color) {
    if (!color.isValid()) {
        return "";
    }
    if (color == Qt::black) {
        return "black";
    } else if (color== Qt::darkGray) {
        return "darkGray";
    } else if (color == Qt::gray) {
        return "gray";
    } else if (color==Qt::lightGray) {
        return "lightGray";
    } else if (color== Qt::white) {
        return "white";
    } else if (color== Qt::red) {
        return "red";
    }
    else if (color == (QColor(255,233,236)))
    {
     return "pink";
    }
    else if (color == (QColor(255,170,0)))
    {
        return "orange";
    }
    else if (color== Qt::yellow) {
        return "yellow";
    } else if (color== Qt::green) {
        return "green";
    } else if (color == Qt::blue) {
        return "blue";
    } else if (color== Qt::magenta) {
        return "magenta";
    } else if (color== Qt::cyan) {
        return "cyan";
    }
    return "";
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
    return  QColor(color.redF(), color.greenF(), color.blueF(),
            (int) (255.0 * alpha));
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* ColorUtil::log = LoggerFactory::getLogger("ColorUtil");
