#include "filenameextensionfilter.h"
#include "file.h"
#include "exceptions.h"

FileNameExtensionFilter::FileNameExtensionFilter()
{

}
/**
 * An implementation of {@code FileFilter} that filters using a
 * specified set of extensions. The extension for a file is the
 * portion of the file name after the last ".". Files whose name does
 * not contain a "." have no file name extension. File name extension
 * comparisons are case insensitive.
 * <p>
 * The following example creates a
 * {@code FileNameExtensionFilter} that will show {@code jpg} files:
 * <pre>
 * FileFilter filter = new FileNameExtensionFilter("JPEG file", "jpg", "jpeg");
 * JFileChooser fileChooser = ...;
 * fileChooser.addChoosableFileFilter(filter);
 * </pre>
 *
 * @see FileFilter
 * @see javax.swing.JFileChooser#setFileFilter
 * @see javax.swing.JFileChooser#addChoosableFileFilter
 * @see javax.swing.JFileChooser#getFileFilter
 *
 * @since 1.6
 */
// /*public*/ /*final*/ class FileNameExtensionFilter extends FileFilter {

/**
 * Creates a {@code FileNameExtensionFilter} with the specified
 * description and file name extensions. The returned {@code
 * FileNameExtensionFilter} will accept all directories and any
 * file with a file name extension contained in {@code extensions}.
 *
 * @param description textual description for the filter, may be
 *                    {@code NULL}
 * @param extensions the accepted file name extensions
 * @throws IllegalArgumentException if extensions is {@code NULL}, empty,
 *         contains {@code NULL}, or contains an empty string
 * @see #accept
 */
/*public*/ FileNameExtensionFilter::FileNameExtensionFilter(QString description, QStringList extensions)
{
 if ( extensions.length() == 0) {
     throw new IllegalArgumentException(
             "Extensions must be non-NULL and not empty");
 }
 this->description = description;
 this->extensions = QStringList();
 this->extensions.reserve(extensions.length());
 this->lowerCaseExtensions = QStringList();//new String[extensions.length];
 this->lowerCaseExtensions.reserve(extensions.length());
 for (int i = 0; i < extensions.length(); i++) {
     if (extensions[i] == NULL || extensions[i].length() == 0) {
         throw new IllegalArgumentException(
             "Each extension must be non-NULL and not empty");
     }
     this->extensions.replace(i, extensions[i]);
     lowerCaseExtensions.replace(i, extensions[i].toLower()); //Locale.ENGLISH);
 }
}

/**
 * Tests the specified file, returning true if the file is
 * accepted, false otherwise. True is returned if the extension
 * matches one of the file name extensions of this {@code
 * FileFilter}, or the file is a directory.
 *
 * @param f the {@code File} to test
 * @return true if the file is to be accepted, false otherwise
 */
/*public*/ bool FileNameExtensionFilter::accept(File* f) {
    if (f != NULL) {
        if (f->isDirectory()) {
            return true;
        }
        // NOTE: we tested implementations using Maps, binary search
        // on a sorted list and this implementation. All implementations
        // provided roughly the same speed, most likely because of
        // overhead associated with java.io.File. Therefor we've stuck
        // with the simple lightweight approach.
        QString fileName = f->getName();
        int i = fileName.lastIndexOf('.');
        if (i > 0 && i < fileName.length() - 1) {
            QString desiredExtension = fileName.mid(i+1).
                    toLower(); //(Case(Locale.ENGLISH)));
            foreach (QString extension, lowerCaseExtensions) {
                if (desiredExtension==(extension)) {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * The description of this filter. For example: "JPG and GIF Images."
 *
 * @return the description of this filter
 */
/*public*/ QString FileNameExtensionFilter::getDescription() {
    return description;
}

/**
 * Returns the set of file name extensions files are tested against.
 *
 * @return the set of file name extensions files are tested against
 */
/*public*/ QStringList FileNameExtensionFilter::getExtensions() {
    QStringList result = QStringList();// new String[extensions.length];
    result.reserve(extensions.length());
    //System.arraycopy(extensions, 0, result, 0, extensions.length);
    for(int i = 0; i < extensions.length(); i++)
    {
     result.replace(i, extensions.at(i));
    }
    return result;
}

/**
 * Returns a string representation of the {@code FileNameExtensionFilter}.
 * This method is intended to be used for debugging purposes,
 * and the content and format of the returned string may vary
 * between implementations.
 *
 * @return a string representation of this {@code FileNameExtensionFilter}
 */
/*public*/ QString FileNameExtensionFilter::toString() {
//    return FileFilter::toString() + "[description=" + getDescription() +
//        " extensions=" + /*java.util.Arrays.asList*/(getExtensions()) + "]";
 QString filter = description + " (";
 bool bFirst = true;
 foreach (QString extension, getExtensions())
 {
  if(!bFirst)
   filter.append(",");
  bFirst = false;
  filter.append(QString("*.%1").arg(extension));
 }
  filter.append(")");
 return filter;
}
