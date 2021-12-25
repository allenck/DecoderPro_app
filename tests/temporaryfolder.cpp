#include "temporaryfolder.h"
#include <QTemporaryDir>
#include <QTemporaryFile>

//TemporaryFolder::TemporaryFolder(QObject *parent) : QObject(parent)
//{

//}
// /*public*/ class TemporaryFolder extends ExternalResource {


    /*public*/ TemporaryFolder::TemporaryFolder(QObject *parent) : QObject(parent) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aconst_null
         * 2: invokespecial org/junit/rules/TemporaryFolder."<init>":(Ljava/io/File;)V
         * 5: return
         *  */
        // </editor-fold>
    }

    /*public*/ TemporaryFolder::TemporaryFolder(File *parentFolder, QObject *parent) : QObject(parent) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial org/junit/rules/ExternalResource."<init>":()V
         * 4: aload_0
         * 5: aload_1
         * 6: putfield      org/junit/rules/TemporaryFolder.parentFolder:Ljava/io/File;
         * 9: return
         *  */
        // </editor-fold>
    }
#if 0
    /*protected*/ void before() throws Throwable {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/junit/rules/TemporaryFolder.create:()V
         * 4: return
         *  */
        // </editor-fold>
    }

    /*protected*/ void after() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/junit/rules/TemporaryFolder.delete:()V
         * 4: return
         *  */
        // </editor-fold>
    }

    /*public*/ void create() throws IOException {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_0
         * 2: aload_0
         * 3: getfield      org/junit/rules/TemporaryFolder.parentFolder:Ljava/io/File;
         * 6: invokespecial org/junit/rules/TemporaryFolder.createTemporaryFolderIn:(Ljava/io/File;)Ljava/io/File;
         * 9: putfield      org/junit/rules/TemporaryFolder.folder:Ljava/io/File;
         * 12: return
         *  */
        // </editor-fold>
    }

    /*public*/ File newFile(String fileName) throws IOException {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           java/io/File
         * 3: dup
         * 4: aload_0
         * 5: invokevirtual org/junit/rules/TemporaryFolder.getRoot:()Ljava/io/File;
         * 8: aload_1
         * 9: invokespecial java/io/File."<init>":(Ljava/io/File;Ljava/lang/String;)V
         * 12: astore_2
         * 13: aload_2
         * 14: invokevirtual java/io/File.createNewFile:()Z
         * 17: ifne          52
         * 20: new           java/io/IOException
         * 23: dup
         * 24: new           java/lang/StringBuilder
         * 27: dup
         * 28: invokespecial java/lang/StringBuilder."<init>":()V
         * 31: ldc           a file with the name '
         * 33: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 36: aload_1
         * 37: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 40: ldc           ' already exists in the test folder
         * 42: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 45: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 48: invokespecial java/io/IOException."<init>":(Ljava/lang/String;)V
         * 51: athrow
         * 52: aload_2
         * 53: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ File newFile() throws IOException {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc           junit
         * 2: aconst_null
         * 3: aload_0
         * 4: invokevirtual org/junit/rules/TemporaryFolder.getRoot:()Ljava/io/File;
         * 7: invokestatic  java/io/File.createTempFile:(Ljava/lang/String;Ljava/lang/String;Ljava/io/File;)Ljava/io/File;
         * 10: areturn
         *  */
        // </editor-fold>
    }
#endif
    /*public*/ File* TemporaryFolder::newFolder(QString folder) /*throw (IOException)*/ {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: iconst_1
         * 2: anewarray     java/lang/String
         * 5: dup
         * 6: iconst_0
         * 7: aload_1
         * 8: aastore
         * 9: invokevirtual org/junit/rules/TemporaryFolder.newFolder:([Ljava/lang/String;)Ljava/io/File;
         * 12: areturn
         *  */
        // </editor-fold>
    QTemporaryDir* dir = new QTemporaryDir(QDir::tempPath() + QDir::separator() + folder);
    dir->setAutoRemove(true);
     File* f = new File(dir->path());
     return f;
    }
#if 0
    /*public*/ File newFolder(String[] folderNames) throws IOException {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokevirtual org/junit/rules/TemporaryFolder.getRoot:()Ljava/io/File;
         * 4: astore_2
         * 5: iconst_0
         * 6: istore_3
         * 7: iload_3
         * 8: aload_1
         * 9: arraylength
         * 10: if_icmpge     90
         * 13: aload_1
         * 14: iload_3
         * 15: aaload
         * 16: astore        4
         * 18: aload_0
         * 19: aload         4
         * 21: invokespecial org/junit/rules/TemporaryFolder.validateFolderName:(Ljava/lang/String;)V
         * 24: new           java/io/File
         * 27: dup
         * 28: aload_2
         * 29: aload         4
         * 31: invokespecial java/io/File."<init>":(Ljava/io/File;Ljava/lang/String;)V
         * 34: astore_2
         * 35: aload_2
         * 36: invokevirtual java/io/File.mkdir:()Z
         * 39: ifne          84
         * 42: aload_0
         * 43: iload_3
         * 44: aload_1
         * 45: invokespecial org/junit/rules/TemporaryFolder.isLastElementInArray:(I[Ljava/lang/String;)Z
         * 48: ifeq          84
         * 51: new           java/io/IOException
         * 54: dup
         * 55: new           java/lang/StringBuilder
         * 58: dup
         * 59: invokespecial java/lang/StringBuilder."<init>":()V
         * 62: ldc           a folder with the name '
         * 64: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 67: aload         4
         * 69: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 72: ldc           ' already exists
         * 74: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 77: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 80: invokespecial java/io/IOException."<init>":(Ljava/lang/String;)V
         * 83: athrow
         * 84: iinc          3, 1
         * 87: goto          7
         * 90: aload_2
         * 91: areturn
         *  */
        // </editor-fold>
    }

    /*private*/ void validateFolderName(QString folderName) throws IOException {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           java/io/File
         * 3: dup
         * 4: aload_1
         * 5: invokespecial java/io/File."<init>":(Ljava/lang/String;)V
         * 8: astore_2
         * 9: aload_2
         * 10: invokevirtual java/io/File.getParent:()Ljava/lang/String;
         * 13: ifnull        28
         * 16: ldc           Folder name cannot consist of multiple path components separated by a file separator. Please use newFolder('MyParentFolder','MyFolder') to create hierarchies of folders
         * 18: astore_3
         * 19: new           java/io/IOException
         * 22: dup
         * 23: aload_3
         * 24: invokespecial java/io/IOException."<init>":(Ljava/lang/String;)V
         * 27: athrow
         * 28: return
         *  */
        // </editor-fold>
    }

    /*private*/ boolean isLastElementInArray(int index, String[] array) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: iload_1
         * 1: aload_2
         * 2: arraylength
         * 3: iconst_1
         * 4: isub
         * 5: if_icmpne     12
         * 8: iconst_1
         * 9: goto          13
         * 12: iconst_0
         * 13: ireturn
         *  */
        // </editor-fold>
    }
#endif
    /*public*/ File* TemporaryFolder::newFolder() /*throw (IOException)*/ {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_0
         * 2: invokevirtual org/junit/rules/TemporaryFolder.getRoot:()Ljava/io/File;
         * 5: invokespecial org/junit/rules/TemporaryFolder.createTemporaryFolderIn:(Ljava/io/File;)Ljava/io/File;
         * 8: areturn
         *  */
        // </editor-fold>
        QTemporaryDir dir;
        return new File(dir.path());
    }
#if 0
    /*private*/ File createTemporaryFolderIn(File parentFolder) throws IOException {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: ldc           junit
         * 2: ldc
         * 4: aload_1
         * 5: invokestatic  java/io/File.createTempFile:(Ljava/lang/String;Ljava/lang/String;Ljava/io/File;)Ljava/io/File;
         * 8: astore_2
         * 9: aload_2
         * 10: invokevirtual java/io/File.delete:()Z
         * 13: pop
         * 14: aload_2
         * 15: invokevirtual java/io/File.mkdir:()Z
         * 18: pop
         * 19: aload_2
         * 20: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ File getRoot() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/junit/rules/TemporaryFolder.folder:Ljava/io/File;
         * 4: ifnonnull     17
         * 7: new           java/lang/IllegalStateException
         * 10: dup
         * 11: ldc           the temporary folder has not yet been created
         * 13: invokespecial java/lang/IllegalStateException."<init>":(Ljava/lang/String;)V
         * 16: athrow
         * 17: aload_0
         * 18: getfield      org/junit/rules/TemporaryFolder.folder:Ljava/io/File;
         * 21: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ void delete() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/junit/rules/TemporaryFolder.folder:Ljava/io/File;
         * 4: ifnull        15
         * 7: aload_0
         * 8: aload_0
         * 9: getfield      org/junit/rules/TemporaryFolder.folder:Ljava/io/File;
         * 12: invokespecial org/junit/rules/TemporaryFolder.recursiveDelete:(Ljava/io/File;)V
         * 15: return
         *  */
        // </editor-fold>
    }

    /*private*/ void recursiveDelete(File file) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: invokevirtual java/io/File.listFiles:()[Ljava/io/File;
         * 4: astore_2
         * 5: aload_2
         * 6: ifnull        43
         * 9: aload_2
         * 10: astore_3
         * 11: aload_3
         * 12: arraylength
         * 13: istore        4
         * 15: iconst_0
         * 16: istore        5
         * 18: iload         5
         * 20: iload         4
         * 22: if_icmpge     43
         * 25: aload_3
         * 26: iload         5
         * 28: aaload
         * 29: astore        6
         * 31: aload_0
         * 32: aload         6
         * 34: invokespecial org/junit/rules/TemporaryFolder.recursiveDelete:(Ljava/io/File;)V
         * 37: iinc          5, 1
         * 40: goto          18
         * 43: aload_1
         * 44: invokevirtual java/io/File.delete:()Z
         * 47: pop
         * 48: return
         *  */
        // </editor-fold>
    }
#endif
