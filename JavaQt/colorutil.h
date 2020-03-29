#ifndef COLORUTIL_H
#define COLORUTIL_H
#include "logger.h"
#include <QColor>

class ColorUtil
{
public:
 /*
      * Color lists for screen colors.
      */
     /*public final*/ static QString ColorTrack;// = "track";
     /*public final*/ static QString ColorBlack;// = "black";
     /*public final*/ static QString ColorDarkGray;// = "darkGray";
     /*public final*/ static QString ColorGray;// = "gray";
     /*public final*/ static QString ColorLightGray;// = "lightGray";
     /*public final*/ static QString ColorWhite;// = "white";
     /*public final*/ static QString ColorRed;// = "red";
     /*public final*/ static QString ColorPink;// = "pink";
     /*public final*/ static QString ColorOrange;// = "orange";
     /*public final*/ static QString ColorYellow;// = "yellow";
     /*public final*/ static QString ColorGreen;// = "green";
     /*public final*/ static QString ColorBlue;// = "blue";
     /*public final*/ static QString ColorMagenta;// = "magenta";
     /*public final*/ static QString ColorCyan;// = "cyan";
     /*public final*/ static QString ColorClear;// = "clear";
     /*public final*/ static QString ColorBrown;// = "brown";

     /*public*/ /*final*/ static QColor clear;// = setAlpha(Color.BLACK, 0);
     /*public*/ /*final*/ static QColor CLEAR;// = clear;
     /*public*/ /*final*/ static QColor BROWN;// = new Color(102, 51, 0);

 /*public*/ static QString colorToHexString(/*@Nullable*/ QColor color);
 /*public*/ static QString colorToString(/*@Nullable*/ QColor color);
 /*public*/ static QString colorToColorName(/*@Nullable*/ QColor color);
 /*public*/ static QColor stringToColor(QString string);
 /*public*/ static QColor setAlpha(/*@Nonnull*/ QColor color, int alpha);
 /*public*/ static QColor setAlpha(/*@Nonnull*/ QColor color, double alpha);
 /*public*/ static QColor contrast(/*@Nonnull*/ QColor color);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ColorUtil");
 /*private*/ static QString colorToName(/*@Nullable*/ QColor color);

 ColorUtil();
};

#endif // COLORUTIL_H
