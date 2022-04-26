#include "filehistory.h"
#include <qdatetime.h>

FileHistory::FileHistory(QObject *parent) :
  QObject(parent)
{
 list =  QList<OperationMemo*>();
 //setProperty("InstanceManagerAutoDefault", "yes");
 setObjectName("FileHistory");
}
/**
 * Memo class to remember a file revision history.
 * <p>
 * These can be nested: A revision can come with a history.
 *
 * @author Bob Jacobsen Copyright (c) 2010
 * @version $Revision: 28746 $
 */
// /*public*/ class FileHistory {


/**
 * Used to add a revision form complete information created elsewhere
 */
/*public*/ void FileHistory::addOperation(
        QString type,
        QString date,
        QString filename,
        FileHistory* history
)
{
 OperationMemo* r = new OperationMemo();
 r->type = type;
 r->date = date;
 r->filename = filename;
 r->history = history;

 foreach (OperationMemo* m, list)
 {
  if(m->date == date)
   return; // already in history
 }
 list.append(r);
}

/*public*/ void FileHistory::addOperation(OperationMemo* r)
{
 list.append(r);
}

/*public*/ void FileHistory::addOperation(
        QString type,
        QString filename,
        FileHistory* history
)
{
 OperationMemo* r = new OperationMemo();
 r->type = type;
 r->date = QDateTime::currentDateTime().toString();
 r->filename = filename;
 r->history = history;

 list.append(r);
}

/**
 * @param keep Number of levels to keep
 */
/*public*/ void FileHistory::purge(int keep)
{
 for (int i = 0; i < list.size(); i++)
 {
  OperationMemo* r = list.at(i);
  if (keep <= 1)
  {
   r->history = NULL;
  }
  if (r->history != NULL)
  {
   r->history->purge(keep - 1);
  }
 }
}

/*public*/ QString FileHistory::toString(QString prefix)
{
 QString retval = "";
 for (int i = 0; i < list.size(); i++) {
     OperationMemo* r = list.at(i);
     retval += prefix + r->date + ": " + r->type + " " + r->filename + "\n";
     if (r->history != NULL) {
         retval += r->history->toString(prefix + "    ");
     }
 }
 return retval;
}

/*public*/ QString FileHistory::toString() {
    return toString("");
}

/*public*/ QList<FileHistory::OperationMemo*> FileHistory::getList() {
    return list;
}

///**
// * Memo class for each revision itself
// */
///*public*/ class OperationMemo {

//    /*public*/ String type;  // load, store
//    /*public*/ String date;
//    /*public*/ String filename;
//    /*public*/ FileHistory history;  // only with load
//}
