#include "loaderengine.h"
#include "loconetsystemconnectionmemo.h"
#include "sleeperthread.h"
#include "spjfile.h"
#include "loconetmessage.h"
#include "logger.h"

//LoaderEngine::LoaderEngine(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Controls the actual LocoNet transfers to download sounds into a Digitrax SFX
 * decoder.
 *
 * @author	Bob Jacobsen Copyright (C) 2006
 * @version	$Revision: 28771 $
 */
///*public*/ class LoaderEngine {

//static java.util.ResourceBundle res = java.util.ResourceBundle.getBundle("jmri.jmrix.loconet.soundloader.Loader");

/*static*/ /*final*/ int LoaderEngine::CMD_START = 0x04;
/*static*/ /*final*/ int LoaderEngine::CMD_ADD = 0x08;

/*static*/ /*final*/ int LoaderEngine::TYPE_SDF = 0x01;
/*static*/ /*final*/ int LoaderEngine::TYPE_WAV = 0x00;

/*static*/ /*final*/ int LoaderEngine::SENDPAGESIZE = 256;
/*static*/ /*final*/ int LoaderEngine::SENDDATASIZE = 128;


/*public*/ LoaderEngine::LoaderEngine(LocoNetSystemConnectionMemo* memo, QObject *parent) :
  QObject(parent)
{
 controller = NULL;
 this->memo = memo;
 log = new Logger("LoaderEngine");
}
void LoaderEngine::setFile(SpjFile *file)
{
 spjFile = file;
}
void LoaderEngine::process()
{
 runDownload();
}

/**
 * Send the complete sequence to download to a decoder.
 *
 * Intended to be run in a separate thread. Uses "notify" method for status
 * updates; overload that to redirect the messages
 */
/*public*/ void LoaderEngine::runDownload(/*SpjFile* file*/)
{
 // this->spjFile = file;

 initController();

    // use a try-catch to handle aborts from below
//    try {
        // erase flash
 emit notify(tr("Starting download; erase flash"));
 controller->sendLocoNetMessage(getEraseMessage());
 //protectedWait(1000);
 SleeperThread::msleep(1000);
 emit notify(tr("Waiting for flash memory to erase (this will take up to 30 seconds)"));
 //protectedWait(20000);
 SleeperThread::msleep(20000);

 // start
 emit notify(tr("Sending initialization message"));
 controller->sendLocoNetMessage(getInitMessage());
 //protectedWait(250);
 SleeperThread::msleep(250);

 // send SDF info
 sendSDF();

 // send all WAV subfiles
 sendAllWAV();

 // end
 controller->sendLocoNetMessage(getExitMessage());
 notify(tr("Done"));
//    } catch (DelayException e) {
//        notify(tr("Download aborted; PR2 not ready"));
//    }

}

void LoaderEngine::sendSDF() /*throws DelayException*/
{
 notify(tr("Send SDF data"));

 // get control info, data
 Header* header = spjFile->findSdfHeader();
 int handle = header->getHandle();
 QString name = header->getName();
 QVector<char>* contents = header->getByteArray();

 // transfer
 LocoNetMessage* m;

 m = initTransfer(TYPE_SDF, handle, name, contents);
 controller->sendLocoNetMessage(m);
 throttleOutbound(m);

 while ((m = nextTransfer()) != NULL)
 {
  controller->sendLocoNetMessage(m);
  throttleOutbound(m);
 }
}

void LoaderEngine::sendAllWAV() /*throws DelayException*/
{
 emit notify(tr("Send WAV data"));
 for (int i = 1; i < spjFile->numHeaders(); i++)
 {
  // see if WAV
  if (spjFile->getHeader(i)->isWAV()) {
      sendOneWav(i);
  }
 }
}

/*public*/ void LoaderEngine::sendOneWav(int index) /*throws DelayException*/
{
 emit notify(tr("Send WAV data block %1").arg(index));
 // get control info, data
 Header* header = spjFile->getHeader(index);
 int handle = header->getHandle();
 QString name = header->getName();
 QVector<char>* buffer = header->getByteArray();

 // that byte array is the "record", not "data";
 // recopy in offset
 int offset = header->getDataStart() - header->getRecordStart();
 int len = header->getDataLength();
 QVector<char>* contents = new QVector<char>(len,0);
 for (int i = 0; i < len; i++)
 {
  //contents[i] = buffer[i + offset];
  contents->replace(i, buffer->at(i+offset));
 }

 // transfer
 LocoNetMessage* m;

 m = initTransfer(TYPE_WAV, handle, name, contents);
 controller->sendLocoNetMessage(m);
 throttleOutbound(m);

 while ((m = nextTransfer()) != NULL) {
     controller->sendLocoNetMessage(m);
     throttleOutbound(m);
 }
}

/**
 * Nofify of status of download.
 *
 * This implementation doesn't do much, but this is provided as a separate
 * method to allow easy overloading
 */
///*public*/ void notify(String message) {
//    log->debug(message);
//}

/**
 * Delay to prevent too much data being sent down.
 *
 * Works with the controller to ensure that too much data doesn't back up.
 */
void LoaderEngine::throttleOutbound(LocoNetMessage* m) /*throws DelayException*/
{
    //protectedWait(50);  // minimum wait to clear
 SleeperThread::msleep(50);

 // wait up to 1 sec in 10mSec chunks for isXmtBusy to clear
 for (int i = 1; i < 1000; i++)
 {
  if (!controller->isXmtBusy())
  {
      return; // done, so return
  }            // wait a while, and then try again
  //protectedWait(10);
  SleeperThread::msleep(10);
 }
//    throw new DelayException("Ran out of time after sending " + m->toString());
 log->error("Ran out of time after sending " + m->toString());
}

//static class DelayException extends Exception {

//    /**
//     *
//     */
//    /*private*/ static /*final*/ long serialVersionUID = 5382070125978390478L;

//    DelayException(String s) {
//        super(s);
//    }
//};

/**
 * Provide a simple object wait. This handles interrupts, synchonization,
 * etc
 */
///*public*/ void protectedWait(int millis) {
//    synchronized (this) {
//        try {
//            wait(millis);
//        } catch (InterruptedException e) {
//            Thread.currentThread().interrupt(); // retain if needed later
//        }
//    }
//}

/**
 * Start a sequence to download a specific type of data.
 *
 * This returns the message to start the process. You then loop calling
 * nextWavTransfer() until it says it's complete.
 *
 * @param type Either TYPE_SDF or TYPE_WAV for the data type
 */
LocoNetMessage* LoaderEngine::initTransfer(int type, int handle, QString name, QVector<char>* contents)
{
 transferType = type;
 transferStart = true;
 transferHandle = handle;
 transferName = name;
 transferContents = contents;

 return getStartDataMessage(transferType, handle, contents->size());
}


/**
 * Get the next message for an ongoing WAV download.
 *
 * You loop calling nextWavTransfer() until it says it's complete by
 * returning NULL.
 */
/*public*/ LocoNetMessage* LoaderEngine::nextTransfer()
{
 if (transferStart)
 {

  transferStart = false;
  transferIndex = 0;

  // first transfer, send DataHeader info
  QVector<char>* header = new QVector<char>(40,0);
  header->replace(0, /*(byte)*/ transferHandle);
  header->replace(1, /*(byte)*/ (transferContents->size() & 0xFF));
  header->replace(2, /*(byte)*/ ((transferContents->size() / 256) & 0xFF));
  header->replace(3, /*(byte)*/ ((transferContents->size() / 256 / 256) & 0xFF));
  header->replace(4, 0); // hdroffset
  header->replace(5, 0); // wavemode1
  header->replace(6, 0); // wavemode2
  header->replace(7, 0); // spare1

  for (int i = 8; i < 40; i++) {
      header->replace(i, 0);
  }
  if (transferName.length() > 32) {
      log->error("name " + transferName + " is too long, truncated");
  }
  for (int i = 0; i < qMin(32, transferName.length()); i++) {
      header->replace(i + 8, /*(byte)*/ transferName.toLocal8Bit().at(i));
  }

  return getSendDataMessage(transferType, transferHandle, header);

 }
 else
 {
  // subsequent transfers, send what data you can.
  // calculate remaining bytes
int remaining = transferContents->size() - transferIndex;
  if (remaining < 0) {
   log->error("Did not expect to find length " + QString::number(transferContents->size()) + " and index " + QString::number(transferIndex));
  }
  if (remaining <= 0) {
      return NULL; // transfer complete
  }
  // set up a buffer for this transfer
  int sendSize = remaining;
  if (remaining > SENDDATASIZE) {
      sendSize = SENDDATASIZE;
  }
  QVector<char>* buffer = new QVector<char>(sendSize,0);
  for (int i = 0; i < sendSize; i++) {
      //buffer[i] = transferContents[transferIndex + i];
   buffer->replace(i, transferContents->at(transferIndex+i));
  }

  // update for next time
  transferIndex = transferIndex + sendSize;

  // and return the message
  return getSendDataMessage(transferType, transferHandle, buffer);

 }
}

/**
 * Get a message to start the download of data
 *
 * @param handle Handle number for the following data
 * @param length Total length of the WAV data to load
 */
LocoNetMessage* LoaderEngine::getStartDataMessage(int type, int handle, int length) {
    int pagecount = length / SENDPAGESIZE;
    int remainder = length - pagecount * SENDPAGESIZE;
    if (remainder != 0) {
        pagecount++;
    }

    if (log->isDebugEnabled()) {
        log->debug("getStartDataMessage: " + QString::number(type) + "," + QString::number(handle) + "," + QString::number(length) + ";"
                + QString::number(pagecount) + "," + QString::number(remainder));
    }
    QVector<char> contents = QVector<char>() << 0xD3 << (type | CMD_START) << handle << (pagecount & 0x7F) <<
       (pagecount / 128) << 0;
    LocoNetMessage* m = new LocoNetMessage(contents);
    m->setParity();
    return m;
}

/**
 * Get a message to tell the PR2 to store length bytes of data (following)
 *
 * @param handle   Handle number for the following data
 * @param contents Data to download
 */
LocoNetMessage* LoaderEngine::getSendDataMessage(int type, int handle, QVector<char>* contents)
{

 int length = contents->size();

 LocoNetMessage* m = new LocoNetMessage(length + 7);
 m->setElement(0, 0xD3);
 m->setElement(1, type | CMD_ADD);
 m->setElement(2, handle);
 m->setElement(3, length & 0x7F);
 m->setElement(4, (length / 128));
 m->setElement(5, 0x00);  // 1st checksum

 for (int i = 0; i < length; i++)
 {
  m->setElement(6 + i, contents->at(i));
 }

 m->setParity();
 return m;
}

/**
 * Get a message to erase the non-volatile sound memory
 */
LocoNetMessage* LoaderEngine::getEraseMessage()
{
 QVector<char> contents =  QVector<char>() <<0xD3<< 0x02<< 0x01<< 0x7F<< 0x00<< 0x50;
 LocoNetMessage* m = new LocoNetMessage(contents);
 m->setParity();
 return m;
}

/**
 * Get a message to initialize the load sequence
 */
LocoNetMessage* LoaderEngine::getInitMessage()
{
 QVector<char> contents = QVector<char>() << 0xD3<< 0x01<< 0x00 << 0x00 << 0x00 << 0x2D;
 LocoNetMessage* m = new LocoNetMessage(contents);
 m->setParity();
 return m;
}

/**
 * Get a message to exit the download process
 */
LocoNetMessage* LoaderEngine::getExitMessage()
{
 QVector<char> contents = QVector<char>() <<0xD3<< 0x00<< 0x00<< 0x00<< 0x00<< 0x2C;
 LocoNetMessage* m = new LocoNetMessage(contents);
 m->setParity();
 return m;
}


void LoaderEngine::initController()
{
 if (controller == NULL)
 {
  controller = memo->getLnTrafficController();
 }
}


/*public*/ void LoaderEngine::dispose()
{
}
