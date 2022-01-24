#include "filesystemview.h"

FileSystemView::FileSystemView(QObject *parent) : QObject(parent)
{

}

/*public*/ bool FileSystemView::isParent(File* file, File* file1)
{
 return file1->getParent() == file->absoluteFilePath();
}
