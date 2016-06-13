#include "xmlfilenamefilter.h"

XmlFilenameFilter::XmlFilenameFilter(QObject *parent) :
    QObject(parent)
{
}
/**
 *
 * @author rhwood
 */
// /*public*/ class XmlFilenameFilter implements FilenameFilter {

    //@Override
/*public*/ bool XmlFilenameFilter::accept(QFile* dir, QString name)
{
 return name.endsWith(".xml"); // NOI18N
}

