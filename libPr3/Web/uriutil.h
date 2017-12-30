#ifndef URIUTIL_H
#define URIUTIL_H
#include <QtCore>

class URIUtil
{
public:
 /*public*/ static /*final*/ QString SLASH;//="/";
 /*public*/ static /*final*/ QString HTTP;//="http";
 /*public*/ static /*final*/ QString HTTP_COLON;//="http:";
 /*public*/ static /*final*/ QString HTTPS;//="https";
 /*public*/ static /*final*/ QString HTTPS_COLON;//="https:";
 // Use UTF-8 as per http://www.w3.org/TR/html40/appendix/notes.html#non-ascii-chars
 ///*public*/ static /*final*/ Charset __CHARSET;
 ///
 /*public*/ static QString decodePath(QString path);
 /*public*/ static QString addPaths(QString p1, QString p2);
 /*public*/ static QString encodePath(QString path);
 /*public*/ static QString encodePath(QString buf, QString path);
 /*public*/ static QString parentPath(QString p);
 /*public*/ static QString canonicalPath(QString path);

private:
 URIUtil();


};

#endif // URIUTIL_H
