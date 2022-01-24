#ifndef DIRECTORYRESOURCE_H
#define DIRECTORYRESOURCE_H
#include "resource.h"
#include <QLocale>

class DirectoryResource : public Resource
{
 Q_OBJECT
public:
 /*public*/ DirectoryResource(QLocale locale, Resource* resource, QObject* parent = nullptr);
 /*public*/ QString getListHTML(QString base, bool parent) /*throw (IOException)*/;


private:
 /*private*/ /*final*/ Resource* resource;
 /*private*/ /*final*/ QLocale locale;
 /*private*/ static QString hrefEncodeURI(QString raw);

};

#endif // DIRECTORYRESOURCE_H
