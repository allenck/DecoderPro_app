#include "profilefilefilter.h"
#include "file.h"

ProfileFileFilter::ProfileFileFilter(QObject *parent) :
    FileFilter(parent)
{
}
/**
 * FileFilter for use in a JFileChooser.
 *
 * @author Randall Wood Copyright (C) 2013, 2014
 */
// /*public*/ class ProfileFileFilter extends FileFilter {

//@Override
/*public*/ bool ProfileFileFilter::accept(File* f) {
    return (f->isDirectory());
}

//@Override
/*public*/ QString ProfileFileFilter::getDescription() {
    return tr("fileFilterDescription");
}
