#ifndef COLORUTIL_H
#define COLORUTIL_H
#include "logger.h"
#include <QColor>

class ColorUtil
{
public:
 /*public*/ static QString colorToHexString(/*@Nullable*/ QColor color);
 /*public*/ static QString colorToString(/*@Nullable*/ QColor color);
 /*public*/ static QString colorToColorName(/*@Nullable*/ QColor color);
 /*public*/ static QColor stringToColor(QString string);
 /*public*/ static QColor setAlpha(/*@Nonnull*/ QColor color, int alpha);
 /*public*/ static QColor setAlpha(/*@Nonnull*/ QColor color, double alpha);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ColorUtil");
 /*private*/ static QString colorToName(/*@Nullable*/ QColor color);

 ColorUtil();
};

#endif // COLORUTIL_H
