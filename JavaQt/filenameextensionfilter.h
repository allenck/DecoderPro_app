#ifndef FILENAMEEXTENSIONFILTER_H
#define FILENAMEEXTENSIONFILTER_H
#include "filefilter.h"

class FileNameExtensionFilter : public FileFilter
{
public:
 FileNameExtensionFilter();
 /*public*/ FileNameExtensionFilter(QString description, QStringList extensions);
 /*public*/ bool accept(File* f);
 /*public*/ QString getDescription();
 /*public*/ QStringList getExtensions();
 /*public*/ QString toString();

private:
 // Description of this filter.
 /*private*/ /*final*/ QString description;
 // Known extensions.
 /*private*/ /*final*/ QStringList extensions;
 // Cached ext
 /*private*/ /*final*/ QStringList lowerCaseExtensions;

};

#endif // FILENAMEEXTENSIONFILTER_H
