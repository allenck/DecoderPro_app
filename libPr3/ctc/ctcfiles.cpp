#include "ctcfiles.h"
#include "file.h"
#include "loggerfactory.h"
#include "fileutil.h"

/**
 * CTC File utility

 * @author Dave Sand Copyright (C) 2019
 */

///*public*/ class CTCFiles {

    /**
     * Verify that the standard file path is valid.
     * Create the ctc directory if needed.
     * @param fileName The name of the file
     * @return the requested file object or null if the path is not valid.
     */
    /*public*/ /*static*/ File* CTCFiles::getFile(QString fileName) {
        // Verify that preference:ctc exists
        File* chkdir = new File(getFileLocation());
        if (!chkdir->exists()) {
            if (!chkdir->mkdir()) {
                log->error("Create preference:ctc failed");  // NOI18N
                return nullptr;
            }
        }
        return new File(getFullName(fileName));
    }

    /*public*/ /*static*/ QString CTCFiles::getFileLocation() {
        return (new File(FileUtil::getUserFilesPath(), "ctc"))->getAbsolutePath();  // NOI18N
    }

    /**
     * Create the full file name with path
     * @param fileName The name of the file.
     * @return the full path and name.
     */
    /*public*/ /*static*/ QString CTCFiles::getFullName(QString fileName) {
        return (new File(getFileLocation(), fileName))->getAbsolutePath();
    }

    /*public*/ /*static*/ bool CTCFiles::fileExists(QString fileName) {
        File* file = getFile(fileName);
        return (file == nullptr ? false : file->exists());
    }

    /*public*/ /*static*/ bool CTCFiles::copyFile(QString sourceFileName, QString destFileName, bool replace) {
        File* sourceFile = getFile(sourceFileName);
        File* destFile = getFile(destFileName);
        if (destFile->exists() && !replace) {
            log->error(tr("Copy file %1 failed: new file %2 already exists").arg(sourceFileName).arg(destFileName));
            return false;
        }
        try {
//            if (Files.copy(sourceFile.toPath(), destFile.toPath(), StandardCopyOption.REPLACE_EXISTING) == null) return false;
         return(QFile::copy(sourceFile->getPath(), destFile->getPath()));
        } catch(IOException ex) {
            log->error(tr("Copy file %1 to %2 failed, exception: ").arg(sourceFileName).arg(destFileName)/*, ex.getMessage()*/);
            return false;
        }
        return true;
    }

    /*public*/ /*static*/ bool CTCFiles::renameFile(QString oldFileName, QString newFileName, bool replace) {
        File* oldFile = getFile(oldFileName);
        File* newFile = getFile(newFileName);
        if (newFile->exists() && !replace) {
            log->error(tr("Rename file %1 failed: new file %2 already exists").arg(oldFileName).arg(newFileName));
            return false;
        }
        try {
//            if (Files.move(oldFile.toPath(), oldFile.toPath().resolveSibling(newFileName), StandardCopyOption.REPLACE_EXISTING) == null) return false;
         return(QFile::rename(oldFile->getPath(), newFile->getPath()));
        } catch(IOException ex) {
            log->error(tr("Rename file %1 to %2 failed, exception: ").arg(oldFileName).arg(newFileName/*, ex*/));
            return false;
        }
        return true;
    }

    /*public*/ /*static*/ bool CTCFiles::deleteFile(QString fileName) {
        File* file = getFile(fileName);
        if (!file->exists()) {
            return true;
        }
        //try {
            //Files.delete(file.toPath());
         if(!QFile::remove(file->getPath()))
        {
            log->error(tr("Delete file %1 failed, exception: ").arg(fileName/*, ex*/));
            return false;
        }
        return true;
    }

    /*public*/ /*static*/ QString CTCFiles::addExtensionIfMissing(QString path, QString missingExtension) {
        QString filenameOnly = getFilenameOnly(path);
        if (filenameOnly.indexOf('.') >= 0) return path;
        return path + missingExtension;
    }

    /*public*/ /*static*/ QString CTCFiles::changeExtensionTo(QString path, QString newExtension) {
        return addExtensionIfMissing(removeFileExtension(path), newExtension);
    }

    /*public*/ /*static*/ QString CTCFiles::removeFileExtension(QString filename) {
        /*final*/ int lastIndexOf = filename.lastIndexOf('.');
        return lastIndexOf >= 1 ? filename.mid(0, lastIndexOf) : filename;
    }

    /*public*/ /*static*/ QString CTCFiles::getFilenameOnly(QString path) {
        // Paths.get(path) can return null per the Paths documentation
//        Path file = Paths.get(path);
//        if (file != null){
//            Object fileName = file.getFileName();
//            if (fileName!=null) {
//                return fileName.toString();
//            }
//        }
//        return "";
     QFileInfo info(path);
     return info.fileName();
    }


    /*private*/ /*static*/ /*final*/ Logger* CTCFiles::log = LoggerFactory::getLogger("CTCFiles");
