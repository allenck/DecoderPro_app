#include "opsessionlog.h"
#include "jfilechooser.h"
#include "file.h"
#include "logger.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include "fileutil.h"

//OpSessionLog::OpSessionLog(QObject *parent) :
//  QObject(parent)
//{
//}
//class OpSessionLog {

/*private*/ /*static*/ OpSessionLog*  OpSessionLog::_instance = NULL;
/*static*/ QTextStream* OpSessionLog::_outBuff = nullptr;
/*static*/ QFile* OpSessionLog::qFile = nullptr;


/*private*/ OpSessionLog::OpSessionLog(QObject *parent) :
QObject(parent)
{
 _outBuff = NULL;
}

/*public*/ /*static*/ OpSessionLog* OpSessionLog::getInstance()
{
 if (_instance == NULL) {
     _instance = new OpSessionLog();
 }
 return _instance;
}

/*public*/ /*synchronized*/ bool OpSessionLog::showFileChooser(QObject* parent)
{
    JFileChooser* fileChooser = new JFileChooser(FileUtil::getUserFilesPath());
    fileChooser->setDialogTitle(tr("Log Session To File"));
    fileChooser->setFileFilter(QString("Text files (*.txt, *.TXT)"));
    int retVal = fileChooser->showDialog(/*(QWidget*)parent*/NULL, tr("Log File"));
    if (retVal != JFileChooser::APPROVE_OPTION) {
        return false;
    }

    File* file = fileChooser->getSelectedFile();
    QString fileName = file->getAbsolutePath();
    QString fileNameLC = fileName.toLower();
    if (!fileNameLC.endsWith(".txt")) {
        fileName = fileName + ".txt";
        file = new File(fileName);
    }
    // check for possible overwrite
//    if (file->exists()) {
//        if (JOptionPane.showConfirmDialog(parent,
//                tr("overWritefile", fileName), tr("QuestionTitle"),
//                JOptionPane.OK_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE) != JOptionPane.OK_OPTION) {
//            return false;
//        }
//    }
//    try {
    qFile = new QFile(file->getAbsolutePath());
    qFile->open(QIODevice::WriteOnly);
    _outBuff = new QTextStream(qFile);
        writeHeader(fileName);
//    }
//    catch (FileNotFoundException* fnfe) {
////        JOptionPane.showMessageDialog(parent, fnfe->getMessage(),
////                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
//     QMessageBox::warning(parent, tr("Warning"), fnfe->getMessage())
//        return false;
//    }
    return true;
}

void OpSessionLog::writeHeader(QString fileName)
{
    //try {
 *_outBuff << "\n";
 *_outBuff << "\t\t\t";
 *_outBuff << fileName;
 *_outBuff << "\n";
 *_outBuff << "\t\t\t";
 //SimpleDateFormat dateFormatter = new SimpleDateFormat("EEEE, MMMM d, yyyy");
 *_outBuff << QDateTime::currentDateTime().toString("EEEE, MMMM, d, yyyy");
 *_outBuff<< "\n";
 *_outBuff<< "\n";
 writeLn(tr("startLog"));
 //    } catch (IOException* ioe) {
 //        Logger::error("Op session log error " + ioe->getMessage());
 //    }
}

/*synchronized*/ /*public*/ void OpSessionLog::writeLn(QString text)
{
//    try {
        //SimpleDateFormat dateFormatter = new SimpleDateFormat("  hh:mm:ss a   ");
 if(_outBuff == NULL) return;

 *_outBuff << QDateTime::currentDateTime().toString("  hh:mm:ss a   ");
 *_outBuff << text;
 *_outBuff << "\n";
//    } catch (IOException* ioe) {
//        Logger::error("Op session log error " + ioe->getMessage());
//    }
}

/*synchronized*/ /*public*/ void OpSessionLog::close()
{
//    try {
 if(_outBuff == NULL) return;

  writeLn(tr("Close Session Log"));
  _outBuff->flush();
  qFile->close();
  _outBuff = NULL;
//    } catch (IOException* ioe) {
//        Logger::error("Op session log error " + ioe->getMessage());
//    }
}
