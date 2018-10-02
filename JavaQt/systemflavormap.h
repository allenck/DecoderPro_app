#ifndef SYSTEMFLAVORMAP_H
#define SYSTEMFLAVORMAP_H
#include "flavormap.h"

class SystemFlavorMap : public FlavorMap
{
public:
 /*public*/ static FlavorMap* getDefaultFlavorMap();

private:
 /*private*/ SystemFlavorMap();
 /*private*/ static QString JavaMIME;// = "JAVA_DATAFLAVOR:";

 /*private*/ static /*final*/ QObject* FLAVOR_MAP_KEY;// = new Object();

 /**
  * Copied from java.util.Properties.
  */
 /*private*/ static /*final*/ QString keyValueSeparators;// = "=: \t\r\n\f";
 /*private*/ static /*final*/ QString strictKeyValueSeparators;// = "=:";
 /*private*/ static /*final*/ QString whiteSpaceChars;// = " \t\r\n\f";

 /**
  * The list of valid, decoded text flavor representation classes, in order
  * from best to worst.
  */
 /*private*/ static /*final*/ QStringList UNICODE_TEXT_CLASSES;// = {
//     "java.io.Reader", "java.lang.String", "java.nio.CharBuffer", "\"[C\""
// };

 /**
  * The list of valid, encoded text flavor representation classes, in order
  * from best to worst.
  */
 /*private*/ static /*final*/ QStringList ENCODED_TEXT_CLASSES;// = {
//     "java.io.InputStream", "java.nio.ByteBuffer", "\"[B\""
// };

 /**
  * A String representing text/plain MIME type.
  */
 /*private*/ static /*final*/ QString TEXT_PLAIN_BASE_TYPE;// = "text/plain";

 /**
  * A String representing text/html MIME type.
  */
 /*private*/ static /*final*/ QString HTML_TEXT_BASE_TYPE;// = "text/html";
  /**
   * Maps native Strings to Lists of DataFlavors (or base type Strings for
   * text DataFlavors).
   * Do not use the field directly, use getNativeToFlavor() instead.
   */
  /*private*/ /*final*/ QMap<QString, QList<DataFlavor*> > nativeToFlavor;// = QMap<QString, QList<DataFlavor*> >();

};

#endif // SYSTEMFLAVORMAP_H
