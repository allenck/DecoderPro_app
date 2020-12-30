#include "abstractmonpane.h"
#include "instancemanager.h"
//#include "defaultusermessagepreferences.h"
#include "jtogglebutton.h"
#include "jtextarea.h"
#include "jtextfield.h"
#include <QCheckBox>
#include <QPushButton>
#include "jmriuserpreferencesmanager.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include "fileutil.h"
#include "jlabel.h"
#include "QFont"
#include <QTextStream>
#include <QRegExpValidator>
#include "message.h"

//AbstractMonPane::AbstractMonPane(QWidget *parent) :
//    JmriPanel(parent)
//{
//}
/**
 * Abstract base class for JPanels displaying communications monitor information
 * @author	Bob Jacobsen   Copyright (C) 2001, 2003, 2010
 * @version	$Revision: 22622 $
 */
// /*public*/ abstract class AbstractMonPane extends JmriPanel  {

// template functions to fill in
//@Override

/*static*/ /*private*/ int AbstractMonPane::MAX_LINES = 500 ;

/**
 * Initialize the data source.
 * <P>
 * This is invoked at the end of the GUI initialization phase.
 * Subclass implementations should connect to their data source here.
 */
AbstractMonPane::~AbstractMonPane()
{
 dispose();
}

// the subclass also needs a dispose() method to close any specific communications; call super.dispose()
//@Override
/*public*/ void AbstractMonPane::dispose()
{
 p->setSimplePreferenceState(timeStampCheck, timeCheckBox->isChecked());
 p->setSimplePreferenceState(rawDataCheck, rawCheckBox->isChecked());
 p->setSimplePreferenceState(alwaysOnTopCheck, alwaysOnTopCheckBox->isChecked());
 p->setSimplePreferenceState(autoScrollCheck, autoScrollCheckBox->isChecked());
 p->setProperty(filterFieldCheck, filterFieldCheck, filterField->text());
 //JmriPanel::dispose();
 JmriPanel::dispose();
}
// you'll also have to add the message(Foo) members to handle info to be logged.
// these should call nextLine(String line, String raw) with their updates

//@SuppressWarnings("LeakingThisInConstructor")
/*public*/ AbstractMonPane::AbstractMonPane(QWidget *parent) : JmriPanel(parent)//JmriPanel(parent)
{
 //super();
 self = this;
 setVisible(false);
 // member declarations
 clearButton = new QPushButton();
 freezeButton = new JToggleButton();
//    jScrollPane1 = new QScrollArea();
 monTextPane = new JTextArea();
 startLogButton = new QPushButton ();
 startLogButton->setEnabled(false);
 stopLogButton = new QPushButton ();
 stopLogButton->setEnabled(false);
 rawCheckBox = new QCheckBox ();
 timeCheckBox = new QCheckBox ();
 alwaysOnTopCheckBox = new QCheckBox ();
 autoScrollCheckBox = new QCheckBox ();
 filterField = new JTextField();
 filterLabel = new JLabel("Filter Bytes:", JLabel::LEFT);
 openFileChooserButton = new QPushButton ();
 entryField = new JTextField();
 enterButton = new QPushButton ();
 //newline = /*System.getProperty("line.separator");*/ "\n";
#ifdef WIN32
 newline = "\r\n";
#else
 newline = "\n";
#endif
 log = new Logger("AbstractMonFrame");
 logStream = nullptr;
 df = QString("HH:mm:ss.zzz");
 linesBuffer =  QString();
 data = nullptr;
 logFileChooser = new QFileDialog(this, tr("Select Log File"), FileUtil::getUserFilesPath());
}

//@Override
/*public*/ void AbstractMonPane::initComponents() throw (Exception)
{
 p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");
 rawDataCheck = QString(getClassName())+".RawData";
 timeStampCheck = QString(getClassName())+".TimeStamp";
 alwaysOnTopCheck = QString(getClassName())+".alwaysOnTop";
 autoScrollCheck = QString(getClassName())+".AutoScroll";
 filterFieldCheck = QString(getClassName())+".FilterField";

 // the following code sets the frame's initial state

 clearButton->setText("Clear screen");
 clearButton->setVisible(true);
 clearButton->setToolTip("Clear monitoring history");

 freezeButton->setText("Freeze screen");
 freezeButton->setVisible(true);
 freezeButton->setToolTip("Stop display scrolling");
 enterButton->setText("Add Message");
 enterButton->setVisible(true);
 enterButton->setToolTip("Add a text message to the log");

 monTextPane->setVisible(true);
 monTextPane->setToolTip("Command and reply monitoring information appears here");
 monTextPane->setEditable(false);
 monTextPane->setReadOnly(true);
 monTextPane->setEnabled(true);

 // Add document listener to scroll to end when modified if required
 //    monTextPane->getDocument().addDocumentListener(new DocumentListener();
 //    {

//        // References to the JTextArea and QCheckBox
//        // of this instantiation
//        JTextArea* ta = monTextPane;
//        QCheckBox*  chk = autoScrollCheckBox;

//       // @Override
//        /*public*/ void insertUpdate(DocumentEvent* e) {
//            doAutoScroll(ta, chk->isChecked());
//        }

//       //@Override
//        /*public*/ void removeUpdate(DocumentEvent* e) {
//            doAutoScroll(ta, chk->isChecked());
//        }

//        //@Override
//        /*public*/ void changedUpdate(DocumentEvent e) {
//            doAutoScroll(ta, chk->isChecked());
//        }
//    });

 entryField->setToolTip("Enter text here, then click button to include it in log");
 // cap vertical size to avoid over-growth
 QSize currentPreferredSize = entryField->getPreferredSize();
 QSize currentMaximumSize = entryField->maximumSize();
 currentMaximumSize.setHeight(currentPreferredSize.height());
 entryField->setMaximumSize(currentMaximumSize);

 //setup filterField
 filterField->setToolTip("Enter byte values to hide, separated by spaces");
 filterField->setMaximumSize(currentMaximumSize);
 QRegExp rx("[0-9A-Fa-f ]{1,8}");
 filterField->setValidator(new QRegExpValidator(rx,0));
 try
 {
  filterField->setText(p->getProperty(filterFieldCheck, filterFieldCheck).toString());  //restore prev values
 }
 catch (Exception e1) {  //leave blank if previous value not retrieved
 }
 //automatically uppercase input in filterField, and only accept spaces and valid hex characters
//    ((AbstractDocument) filterField.getDocument()).setDocumentFilter(new DocumentFilter() {
//        /*public*/ void insertString(DocumentFilter.FilterBypass fb, int offset, String text,
//                AttributeSet attr) throws BadLocationException {
//            if (text.matches("[[0-9a-fA-F]{0,7}| ]")) {
//                fb.insertString(offset, text.toUpperCase(), attr);
//            }
//        }
//        /*public*/ void replace(DocumentFilter.FilterBypass fb, int offset, int length, String text,
//                AttributeSet attrs) throws BadLocationException {
//            if (text.matches("[[0-9a-fA-F]{0,7}| ]")) {
//                fb.replace(offset, length, text.toUpperCase(), attrs);
//            }
//        }
//    });

 // fix a width for current character set
 //JTextField* t = new JTextField(80);
//    int x = jScrollPane1.getPreferredSize().width+t.getPreferredSize().width;
//    int y = jScrollPane1.getPreferredSize().height+10*t.getPreferredSize().height;

//    jScrollPane1->getViewport().add(monTextPane);
//    jScrollPane1->setPreferredSize(new Dimension(x, y));
//    jScrollPane1->setVisible(true);

 startLogButton->setText("Start logging");
 startLogButton->setVisible(true);
 startLogButton->setToolTip("start logging to file");

 stopLogButton->setText("Stop logging");
 stopLogButton->setVisible(true);
 stopLogButton->setToolTip("Stop logging to file");

 rawCheckBox->setText("Show raw data");
 rawCheckBox->setVisible(true);
 rawCheckBox->setToolTip("If checked, show the raw traffic in hex");
 rawCheckBox->setChecked(p->getSimplePreferenceState(rawDataCheck));


 timeCheckBox->setText("Show timestamps");
 timeCheckBox->setVisible(true);
 timeCheckBox->setToolTip("If checked, show timestamps before each message");
 timeCheckBox->setChecked(p->getSimplePreferenceState(timeStampCheck));
 connect(timeCheckBox, SIGNAL(toggled(bool)), this, SLOT(OnTimestampCheck(bool)));

 alwaysOnTopCheckBox->setText("Window always on Top");
 alwaysOnTopCheckBox->setVisible(true);
 alwaysOnTopCheckBox->setToolTip("If checked, this window be always be displayed in front of any other window");
 alwaysOnTopCheckBox->setChecked(p->getSimplePreferenceState(alwaysOnTopCheck));
    //setAlwaysOnTop(alwaysOnTopCheckBox->isChecked());
 if(alwaysOnTopCheckBox->isChecked())
  setWindowFlags(Qt::WindowStaysOnTopHint);

 autoScrollCheckBox->setText("Auto scroll");
 autoScrollCheckBox->setVisible(true);
 autoScrollCheckBox->setToolTip("If checked, always scroll to the latest log entry");
 autoScrollCheckBox->setChecked(p->getSimplePreferenceState(autoScrollCheck));

 openFileChooserButton->setText("Choose log file");
 openFileChooserButton->setVisible(true);
 openFileChooserButton->setToolTip("Click here to select a new output log file");

//    getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
 //QWidget* centralWidget = new QWidget;
 QVBoxLayout* contentPaneLayout = new QVBoxLayout;
 setLayout(contentPaneLayout);
 // add items to GUI
 contentPaneLayout->addWidget(/*jScrollPane1*/monTextPane);

//    QWidget* paneA = new QWidget();
//    paneA.setLayout(new BoxLayout(paneA, BoxLayout.Y_AXIS));
 QVBoxLayout* paneALayout = new QVBoxLayout;

//    QWidget* pane1 = new QWidget();
//    pane1.setLayout(new BoxLayout(pane1, BoxLayout.X_AXIS));
 QHBoxLayout* pane1Layout = new QHBoxLayout;
 pane1Layout->addWidget(clearButton);
 pane1Layout->addWidget(freezeButton);
 pane1Layout->addWidget(rawCheckBox);
 pane1Layout->addWidget(timeCheckBox);
 pane1Layout->addWidget(alwaysOnTopCheckBox);
 pane1Layout->addWidget(autoScrollCheckBox);
 paneALayout->addLayout(pane1Layout);

//    QWidget* pane2 = new QWidget();
//    pane2.setLayout(new BoxLayout(pane2, BoxLayout.X_AXIS));
 QHBoxLayout* pane2Layout = new QHBoxLayout;
 pane2Layout->addWidget(filterLabel);
 pane2Layout->addWidget(filterField);
 pane2Layout->addWidget(openFileChooserButton);
 pane2Layout->addWidget(startLogButton);
 pane2Layout->addWidget(stopLogButton);
 paneALayout->addLayout(pane2Layout);

//    QWidget* pane3 = new QWidget();
//    pane3.setLayout(new BoxLayout(pane3, BoxLayout.X_AXIS));
 QHBoxLayout* pane3Layout = new QHBoxLayout;
 pane3Layout->addWidget(enterButton);
 pane3Layout->addWidget(entryField);
 paneALayout->addLayout(pane3Layout);

 contentPaneLayout->addLayout(paneALayout);

 // connect actions to buttons
//    clearButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            clearButtonActionPerformed(e);
//        }
//    });
 connect(clearButton, SIGNAL(clicked()), this, SLOT(clearButtonActionPerformed()));
//    startLogButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            startLogButtonActionPerformed(e);
//        }
//    });
 connect(startLogButton, SIGNAL(clicked()),this, SLOT(startLogButtonActionPerformed()));
//    stopLogButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            stopLogButtonActionPerformed(e);
//        }
//    });
 connect(stopLogButton, SIGNAL(clicked()), this, SLOT(stopLogButtonActionPerformed()));
//    openFileChooserButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            openFileChooserButtonActionPerformed(e);
//        }
//    });
 connect(openFileChooserButton, SIGNAL(clicked()), this, SLOT(openFileChooserButtonActionPerformed()));
//    enterButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            enterButtonActionPerformed(e);
//        }
//    });
 connect(enterButton, SIGNAL(clicked()), this, SLOT(enterButtonActionPerformed()));

//    alwaysOnTopCheckBox.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setAlwaysOnTop(alwaysOnTopCheckBox.isChecked());
//        }
//    });
 connect(alwaysOnTopCheckBox, SIGNAL(toggled(bool)), this, SLOT(OnAlwaysOnTopCheckBox(bool)));

//    autoScrollCheckBox.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            doAutoScroll(monTextPane, autoScrollCheckBox.isChecked());
//        }
//    });
 connect(autoScrollCheckBox, SIGNAL(toggled(bool)), this, SLOT(OnAutoScrollCheckBox(bool)));

 connect(rawCheckBox,SIGNAL(toggled(bool)), this,SLOT(OnRawCheckBox(bool)));

  // set file chooser to a default
//  logFileChooser->setSelectedFile(new QFile("monitorLog.txt"));

  // connect to data source
 init();
}

void AbstractMonPane::OnAutoScrollCheckBox(bool /*bChecked*/)
{
 //doAutoScroll(monTextPane, autoScrollCheckBox->isChecked());
 p->setSimplePreferenceState(autoScrollCheck, autoScrollCheckBox->isChecked());
}

void AbstractMonPane::OnAlwaysOnTopCheckBox(bool bChecked)
{
 Qt::WindowFlags flags = windowFlags();
 if (bChecked)
 {
  this->window()->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
  this->window()->show();
 }
 else
 {
  this->window()->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
  this->window()->show();
 }
 p->setSimplePreferenceState(alwaysOnTopCheck, alwaysOnTopCheckBox->isChecked());
}

/**
 * Sets the display window to fixed width font, so that
 * e.g. columns line up
 */
/*public*/ void AbstractMonPane::setFixedWidthFont()
{
 QFont f = font();
 f.setFixedPitch(true);
 monTextPane->setFont(f);
 //"Monospaced", java.awt.Font.PLAIN, monTextPane.getFont().getSize() ) );
}

/**
 * Define help menu for this window.
 * <p>
 * By default, provides a generic help page
 * that covers general features.  Specific
 * implementations can override this to
 * show their own help page if desired.
 */
//@Override
/*public*/ QString AbstractMonPane::getHelpTarget() {
    return "package.jmri.jmrix.AbstractMonFrame";
}
/**
 *  Log an Message derived message.
 *
 *  @param message message object to log.
 */
/*public*/ void AbstractMonPane::logMessage(Message* message){
 logMessage("","",message);
}

/**
 *  Log an Message derived message.
 *
 *  @param messagePrefix text to prefix the message with.
 *  @param message message object to log.
 */
/*public*/ void AbstractMonPane::logMessage(QString messagePrefix,Message* message){
 logMessage(messagePrefix,"",message);
}

/**
 *  Log an Message derived message with a prefixed label.
 *
 *  @param messagePrefix text to prefix the message with.
 *  @param rawPrefix label to add to the start of the message.
 *  @param message message object to log.
 */
/*public*/ void AbstractMonPane::logMessage(QString messagePrefix,QString rawPrefix,Message* message){
    // display the raw data if requested
    QString raw = rawPrefix; //new StringBuilder(rawPrefix);
    if (rawCheckBox->isChecked()) {
        raw.append(message->toString());
    }

    // display the decoded data
    QString text=message->toMonitorString();
    nextLine(messagePrefix + " " + text + "\n", raw);
}

/*public*/ void AbstractMonPane::nextLine(QString line, QString raw)
{
 // handle display of traffic
 // line is the traffic in 'normal form', raw is the "raw form"
 // Both should be one or more well-formed lines, e.g. end with \n
 QString sb;

 // display the timestamp if requested
 if ( timeCheckBox->isChecked() )
 {
  sb.append(QDateTime::currentDateTime().toString(df) + " " ) ;
 }

 // display the raw data if available and requested
 if ( raw != "" && rawCheckBox->isChecked() )
 {
   sb.append( '[' ).append(raw).append( "]  " );
 }

 // display decoded data
 if(line.endsWith('\n'))
 {
  line = line.mid(0, line.length()-1);
 }
 sb.append(line);
//    synchronized( self )
 {
  linesBuffer.append( sb/*.toString()*/ );
 }
#if 1
 // if requested, log to a file.
 if (logStream != nullptr)
 {
  /*synchronized (logStream)*/
  {
   QString logLine = sb/*.toString()*/;
   if (newline!=("\n"))
   {
   // have to massage the line-ends
   int i = 0;
   int lim = sb.length();
   QString out;// = new StringBuffer(sb.length()+10);  // arbitrary guess at space
   for ( i = 0; i<lim; i++)
   {
    if (sb.at(i) == '\n')
     out.append(newline);
    else
     out.append(sb.at(i));
    }
    logLine = out/*.toString()*/;
   }
   *logStream << (logLine);
  }
 }
#endif
 // if frozen, exit without adding to the Swing thread
 if (freezeButton->isSelected())
 {
   return;
 }
 //don't bother to check filter if no raw value passed
 if (raw != "")
 {
  // if first bytes are in the skip list,  exit without adding to the Swing thread
  QStringList filters = filterField->text().toUpper().split(" ");
  QString checkRaw = raw.mid(0, 2).toUpper();

  foreach (QString s, filters)
  {
   if (s==(checkRaw))
   {
    linesBuffer="" ;
    return;
   }
  }
 }
#if 0
//    Runnable r = new Runnable() {
//        //@Override
//        /*public*/ void run() {
//            synchronized( self )
//            {
//                monTextPane.append( linesBuffer.toString() );
//                int LineCount = monTextPane.getLineCount() ;
//                if( LineCount > MAX_LINES )
//                {
//                    LineCount -= MAX_LINES ;
//                    try {
//                        int offset = monTextPane.getLineStartOffset(LineCount);
//                        monTextPane.getDocument().remove(0, offset ) ;
//                    }
//                    catch (BadLocationException ex) {
//                    }
//                }
//                linesBuffer.setLength(0) ;
//            }
//        }
//    };
//    javax.swing.SwingUtilities.invokeLater(r);
    AMPRunnable* r = new AMPRunnable(this);
    r->start();

#else
 monTextPane->append( linesBuffer/*.toString()*/ );
 int LineCount = monTextPane->document()->lineCount() ;
 if( LineCount > AbstractMonPane::MAX_LINES )
 {
  LineCount -= AbstractMonPane::MAX_LINES ;
  //   try
  //   {
  //    int offset = pane->monTextPane->getLineStartOffset(LineCount);
  //    pane->monTextPane->getDocument().remove(0, offset ) ;
  //   }
  //   catch (BadLocationException ex)
  //   {
  //   }
  QTextCursor tc = monTextPane->textCursor();
  tc.movePosition(QTextCursor::Start);
  tc.setPosition(500);
  tc.removeSelectedText();
 }
 linesBuffer = "";
 if(autoScrollCheckBox->isChecked())
  monTextPane->moveCursor( QTextCursor::End);
#endif
}
#if 0
AMPRunnable::AMPRunnable(AbstractMonPane *pane)
{
 this->pane = pane;
}
void AMPRunnable::run()
{
//    synchronized( self )
 {
  pane->monTextPane->append( pane->linesBuffer/*.toString()*/ );
  int LineCount = pane->monTextPane->document()->lineCount() ;
  if( LineCount > AbstractMonPane::MAX_LINES )
  {
   LineCount -= AbstractMonPane::MAX_LINES ;
//   try
//   {
//    int offset = pane->monTextPane->getLineStartOffset(LineCount);
//    pane->monTextPane->getDocument().remove(0, offset ) ;
//   }
//   catch (BadLocationException ex)
//   {
//   }
   QTextCursor tc = pane->monTextPane->textCursor();
   tc.movePosition(QTextCursor::Start,QTextCursor::KeepAnchor);
   tc.setPosition(500);
   tc.removeSelectedText();
  }
  pane->linesBuffer = "" ;
 }
}
#endif

/*public*/ /*synchronized*/ void AbstractMonPane::clearButtonActionPerformed(JActionEvent* /*e*/) {
    // clear the monitoring history
//    synchronized( linesBuffer )
    {
        linesBuffer="";
        monTextPane->setText("");
    }
}

/*public*/ /*synchronized*/ void AbstractMonPane::startLogButtonActionPerformed(JActionEvent* /*e*/) {
    // start logging by creating the stream
#if 0
    if ( logStream==nullptr) {  // successive clicks don't restart the file
        // start logging
        try {
            logStream = new PrintStream (new FileOutputStream(logFileChooser.getSelectedFile()));
        } catch (Exception ex) {
            log->error("exception "+ex);
        }
    }
#endif
    if((data == nullptr) || (!data->open(QFile::WriteOnly | QFile::Truncate)))
     log->error(tr("File open failed ")+ data->fileName());
    stopLogButton->setEnabled(true);
}

/*public*/ /*synchronized*/ void AbstractMonPane::stopLogButtonActionPerformed(JActionEvent* /*e*/)
{
 // stop logging by removing the stream
#if 1
 if (logStream!=nullptr)
 {
  /*synchronized (logStream) */
  {
   logStream->flush();
   delete logStream;
   data->close();
  }
  logStream = nullptr;
  stopLogButton->setEnabled(false);
 }
#endif
}

/*public*/ void AbstractMonPane::openFileChooserButtonActionPerformed(JActionEvent* e)
{
 // start at current file, show dialog
#if 0 // done
    int retVal = logFileChooser.showSaveDialog(this);

    // handle selection or cancel
    if (retVal == JFileChooser.APPROVE_OPTION) {
        boolean loggingNow = (logStream != null);
        stopLogButtonActionPerformed(e);  // stop before changing file
        //File file = logFileChooser.getSelectedFile();
        // if we were currently logging, start the new file
        if (loggingNow) startLogButtonActionPerformed(e);
    }
#endif
 logFileChooser = new QFileDialog(this, tr("Select log file"),FileUtil::getUserFilesPath(), tr("Log files(*.txt *.log"));
 setCursor(Qt::WaitCursor);
 if(logFileChooser->exec() ==  QDialog::Accepted)
 {
  setCursor(Qt::ArrowCursor);
  bool loggingNow = (logStream != nullptr);
  stopLogButtonActionPerformed(e);  // stop before changing file
  data = new QFile(logFileChooser->selectedFiles().at(0));
  // if we were currently logging, start the new file
  if (loggingNow) startLogButtonActionPerformed(e);
  startLogButton->setEnabled(true);
 }
 setCursor(Qt::ArrowCursor);
}

/*public*/ void AbstractMonPane::enterButtonActionPerformed(JActionEvent* /*e*/) {
    nextLine(entryField->text(), "");
}

/*public*/ /*synchronized*/ QString AbstractMonPane::getFrameText() {
    return linesBuffer/*.toString()*/;
}
#if 0
/**
 * Method to position caret at end of JTextArea ta when
 * scroll true.
 * @param ta Reference to JTextArea
 * @param scroll True to move to end
 */
/*private*/ void AbstractMonPane::doAutoScroll(/*final*/ JTextArea* ta, /*final*/ bool scroll) {
    SwingUtilities.invokeLater(new Runnable() {
        //@Override
        /*public*/ void run() {
            int len = ta.getText().length();
            if (scroll) {
                ta.setCaretPosition(len);
            } else if (ta.getCaretPosition()==len && len>0) {
                ta.setCaretPosition(len-1);
            }
        }
    });
}
#endif

/*public*/ QString AbstractMonPane::getClassName()
{
 return "";
}

void AbstractMonPane::OnRawCheckBox(bool)
{
 p->setSimplePreferenceState(rawDataCheck, rawCheckBox->isChecked());

}

void AbstractMonPane::OnTimestampCheck(bool)
{
p->setSimplePreferenceState(timeStampCheck, timeCheckBox->isChecked());
}
