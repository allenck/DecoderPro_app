#include "backupset.h"
#include "file.h"
#include <QDate>
#include "logger.h"

//BackupSet::BackupSet(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{
/**
 * Represents the set of Operations files that is considered a "Backup" of the
 * current Operations files.
 *
 * It can facilitate the display and selection of backup sets using a GUI.
 *
 * This class needs tests.......
 *
 * @author Gregory Madsen Copyright (C) 2012
 *
 */
///*public*/ class BackupSet {


    /*public*/ QString BackupSet::getSetName() {
        return _setName;
    }


    /*public*/ BackupSet::BackupSet(File* dir,QObject *parent) :
  QObject(parent) {
        _dir = dir;
        _setName = dir->getName();
        _lastModifiedDate = dir->lastModified().date();
    }

    /*public*/ void BackupSet::_delete() {
        deleteDirectoryAndFiles(_dir);
    }

    /*private*/ void BackupSet::deleteDirectoryAndFiles(File* dir) {
        // Deletes all of the files in a directory, and then the directory
        // itself.
        // This is NOT a general purpose method, as it only handles directories
        // with only files and no sub directories.
        // This probably needs to handle failures. delete() returns false if it fails.
        bool ok;
        foreach (File* f, dir->listFiles()) {
            // Delete files first
            if (f->isFile()) {
                ok = f->_delete();
                if (!ok) {
                    Logger::error("Failed to delete file: " + f->getAbsolutePath()); // NOI18N
                }
            }
        }

        ok = dir->_delete();
        if (!ok) {
            Logger::error("Failed to delete directory: " + dir->getAbsolutePath()); // NOI18N
        }
    }

    //@Override
    /*public*/ QString BackupSet::toString() {
        return tr("%1 (%2)").arg(_setName).arg(_lastModifiedDate.toString("yyyy/MM/dd")); // NOI18N
    }
}
