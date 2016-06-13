#include "lnhexfileport.h"
#include "hexfileframe.h"
#include "sleeperthread.h"

//LnHexFilePort::LnHexFilePort(QObject *parent) :
//    LnPortController(parent)
//{
//}
/**
 * LnHexFilePort implements a LnPortController via a
 * ASCII-hex input file. See below for the file format
 * There are user-level controls for
 *      send next message
 *	how long to wait between messages
 *
 * An object of this class should run in a thread
 * of its own so that it can fill the output pipe as
 * needed.
 *
 *	The input file is expected to have one message per line. Each line
 *	can contain as many bytes as needed, each represented by two Hex characters
 *	and separated by a space. Variable whitespace is not (yet) supported
 *
 * @author			Bob Jacobsen    Copyright (C) 2001
 * @version			$Revision: 28493 $
 */
// /*public*/ class LnHexFilePort extends LnPortController implements Runnable, jmri.jmrix.SerialPortAdapter {


/*public*/ LnHexFilePort::LnHexFilePort(QObject *parent)
    : LnPortController(new LocoNetSystemConnectionMemo(), parent)
{
 sFile = NULL;
 log = new Logger("LnHexFilePort");
 // private data
 _running = false;

 // streams to share with user class
 pout = NULL; // this is provided to classes who want to write to us
 pin = NULL;  // this is provided to class who want data from us

 // internal ends of the pipes
 outpipe = NULL;  // feed pin
 //private DataInputStream inpipe = NULL; // feed pout
 delay=100;  				// units are milliseconds; default is quiet a busy LocoNet


 //super(new LocoNetSystemConnectionMemo());
 try
 {
  //PipedInputStream* tempPipe = new PipedInputStream();
  /*BufferedReader*/  QByteArray* tempPipe = new QByteArray(500, 0);
  pin = new /*DataInputStream(tempPipe);*/ QDataStream(tempPipe, QIODevice::ReadOnly);
  outpipe = /*new DataOutputStream(new PipedOutputStream(tempPipe));*/ new QDataStream(tempPipe, QIODevice::WriteOnly);
  pout = outpipe;
 }
 catch (IOException e)
 {
  log->error("init (pipe): Exception: "/*+e.toString()*/);
 }
 options.insert("SensorDefaultState", new Option(tr("Default State Of Sensors") + ":", QStringList() <<  tr("Unknown") <<  tr("Inactive")<< tr("Active"), true));
}

/* load(File) fills the contents from a file */
/*public*/ void LnHexFilePort::load(QFile* file)
{
 if (log->isDebugEnabled()) log->debug("file: "+file->fileName());

 // create the pipe stream for output, also store as the input stream if somebody wants to send
 // (This will emulate the LocoNet echo)
 try
 {
  //sFile = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
  sFile = new QTextStream(file);
 }
 catch (Exception e)
 {
  log->error("load (pipe): Exception: "+e.getMessage());
 }
}

/*public*/ void LnHexFilePort::_connect() throw (Exception)
{
 HexFileFrame* f = new HexFileFrame();

 f->setAdapter(this);
 try
 {
  f->initComponents();
 }
 catch (Exception ex)
 {
        //log->error("starting HexFileFrame exception: "+ex.toString());
 }
 f->configure();
}

/*public*/ void LnHexFilePort::run()
{ // invoked in a new thread
 if (log->isInfoEnabled())
  log->info("LocoNet Simulator Started");
 QThread* currentThread = QThread::currentThread();
 connect(currentThread, SIGNAL(terminated()), this, SLOT(on_interrupted()));
 while (true)
 {
  while (sFile == NULL)
  {
   // Wait for a file to be available. We have nothing else to do, so we can sleep
   // until we are interrupted
//   try
//   {
    //Thread.sleep(10000);
    SleeperThread::msleep(10000);
//   }
  }
 }

//
 log->info("LnHexFilePort.run: changing input file...");

 // process the input file into the output side of pipe
 _running = true;
 try
 {
   // Take ownership of the current file, it will automatically go out of scope
   // when we leave this scope block.  Set sFile to NULL so we can detect a new file
   // being set in load() while we are running the current file.
   /*BufferedReader*/QTextStream* currFile = sFile;
   sFile = NULL;

   QString s;
   while ( (s = currFile->readLine()) != NULL)
   {
    // this loop reads one line per turn
    // ErrLog.msg(ErrLog.debugging,"LnHexFilePort","run","string=<"+s+">");
    int len = s.length();
    bool bOk;
    for (int i=0; i<len; i+=3)
    {
     // parse as hex into integer, then convert to byte
     int ival = s.mid(i,i+2).toInt(&bOk,16);
     // send each byte to the output pipe (input to consumer)
     char bval = (char) ival;
     outpipe->writeBytes(&bval, 1);
    }

    // flush the pipe so other threads can see the message
    //outpipe->flush();

    // finished that line, wait
    // Thread.sleep(delay);
    SleeperThread::msleep(delay);
   }

   // here we're done processing the file
   log->info("LnHexFDilePort.run: normal finish to file");

  }
  catch (InterruptedException e)
  {
   if (sFile != NULL)
  {
   log->info("LnHexFilePort.run: user selected new file");
   // swallow the exception since we have handled its intent
  }
  else
  {
   log->error("LnHexFilePort.run: unexpected InterruptedException, exiting");
   //Thread.currentThread().interrupt();
   QThread::currentThread()->quit();
   return;
  }
 }
 catch (Exception e)
 {
  log->error("run: Exception: "+e.getMessage());
 }
 _running = false;
}
//}
//catch (InterruptedException e)
void LnHexFilePort::On_interrupted()
{
log->info("LnHexFilePort.run: woken from sleep");
if (sFile == NULL)
{
log->error("LnHexFilePort.run: unexpected InterruptedException, exiting");
//Thread.currentThread().interrupt();
QThread::currentThread()->quit();
return;
}
}

/**
 * Provide a new message delay value, but
 * don't allow it to go below 2 msec.
 */
/*public*/ void LnHexFilePort::setDelay(int newDelay) {
    delay = qMax(2,newDelay);
}

// base class methods
/*public*/ QDataStream* LnHexFilePort::getInputStream()
{
 if (pin == NULL)
  log->error("getInputStream: called before load(), stream not available");
 return pin;
}

/*public*/ QDataStream* LnHexFilePort::getOutputStream()
{
    if (pout == NULL) log->error("getOutputStream: called before load(), stream not available");
    return pout;
}

/*public*/ bool LnHexFilePort::status() {return (pout!=NULL)&(pin!=NULL);}

// to tell if we're currently putting out data
/*public*/ bool LnHexFilePort::running() { return _running; }


/*public*/ bool LnHexFilePort::okToSend() { return true; }
// define operation

/*public*/ QVector<QString> LnHexFilePort::getPortNames() {
    log->error("getPortNames should not have been invoked");
    //new Exception().printStackTrace();
    return QVector<QString>();
}
/*public*/ QString LnHexFilePort::openPort(QString /*portName*/, QString /*appName*/) {
    log->error("openPort should not have been invoked");
    //new Exception().printStackTrace();
    return "openPort should not have been invoked";
}
/*public*/ void LnHexFilePort::configure() {
    log->error("configure should not have been invoked");
    //new Exception().printStackTrace();
}
/*public*/ QStringList LnHexFilePort::validBaudRates() {
    log->error("validBaudRates should not have been invoked");
    //new Exception().printStackTrace();
    return QStringList();
}

/**
 * Get an array of valid values for "option 3"; used to display valid options.
 * May not be NULL, but may have zero entries
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
/*public*/ QStringList LnHexFilePort::validOption3() { return  QStringList() <<  "Normal"<< "Spread"<< "One Only"<< "Both"; }

/**
 * Get a String that says what Option 3 represents
 * May be an empty string, but will not be NULL
 */
/*public*/ QString LnHexFilePort::option3Name() { return "Turnout command handling: "; }

/**
 * Set the third port option.  Only to be used after construction, but
 * before the openPort call
 */
/*public*/ void LnHexFilePort::configureOption3(QString value) {
    LnPortController::configureOption3(value);
    log->debug("configureOption3: "+value);
    setTurnoutHandling(value);
}
