#include "defaultbackup.h"

//DefaultBckup::DefaultBckup(QObject *parent) :
//  BckupBase(parent)
//{
//}
namespace Operations
{
/**
 * Specific Backup class for backing up and restoring Operations working files
 * to the Default Backup Store. Derived from BackupBase.
 *
 * @author Gregory Madsen Copyright (C) 2012
 */
///*public*/ class DefaultBackup extends BackupBase {

//    static Logger log = LoggerFactory
//            .getLogger(DefaultBackup.class.getName());

    /**
     * Creates a DefaultBackup instance and initializes the root directory to
     * the given name.
     */
    /*public*/ DefaultBackup::DefaultBackup(QObject *parent) :
   BackupBase("backups", parent) {
        //super("backups"); // NOI18N
    }
}
