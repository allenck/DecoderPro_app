#include "abstractmonframe.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "jtogglebutton.h"
#include "jtextarea.h"
#include "jtextfield.h"
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include "fileutil.h"
#include "jfilechooser.h"
#include "loggerfactory.h"

//AbstractMonFrame::AbstractMonFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Abstract base class for Frames displaying communications monitor information
 * @author	Bob Jacobsen   Copyright (C) 2001, 2003
 * @version	$Revision: 22530 $
 */
// /*public*/ abstract class AbstractMonFrame extends JmriJFrame  {

// template functions to fill in

/**
 * Initialize the data source.
 * <P>
 * This is invoked at the end of the GUI initialization phase.
 * Subclass implementations should connect to their data source here.
 */

// the subclass also needs a dispose() method to close any specific communications; call super.dispose()
//@Override
/*public*/ void AbstractMonFrame::dispose() {
    p->setSimplePreferenceState(timeStampCheck, timeCheckBox->isChecked());
    p->setSimplePreferenceState(rawDataCheck, rawCheckBox->isChecked());
    p->setSimplePreferenceState(alwaysOnTopCheck, alwaysOnTopCheckBox->isChecked());
    p->setSimplePreferenceState(autoScrollCheck, !autoScrollCheckBox->isChecked());
    JmriJFrame::dispose();
}
// you'll also have to add the message(Foo) members to handle info to be logged.
// these should call nextLine(String line, String raw) with their updates
/*static*/ /*private*/ int AbstractMonFrame::MAX_LINES = 500 ;


/*public*/ AbstractMonFrame::AbstractMonFrame(QWidget *parent) : JmriJFrame(parent){
    //super();
    self = this;
    rawDataCheck = QString(this->metaObject()->className())+".RawData";
    timeStampCheck = QString(this->metaObject()->className())+".TimeStamp";
     alwaysOnTopCheck = QString(this->metaObject()->className())+".alwaysOnTop";
    autoScrollCheck = QString(this->metaObject()->className())+".AutoScroll";
    // member declarations
    clearButton = new QPushButton();
    freezeButton = new JToggleButton();
//    jScrollPane1 = new QScrollArea();
    monTextPane = new JTextArea();
    startLogButton = new QPushButton ();
    stopLogButton = new QPushButton ();
    rawCheckBox = new QCheckBox ();
    timeCheckBox = new QCheckBox ();
    alwaysOnTopCheckBox = new QCheckBox ();
    autoScrollCheckBox = new QCheckBox ();
    openFileChooserButton = new QPushButton ();
    entryField = new JTextField();
    enterButton = new QPushButton ();
    newline = /*System.getProperty("line.separator");*/ "\n";
    logStream = NULL;
    df = QString("HH:mm:ss.zzz");
    linesBuffer =  QString();
    logFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
}

/*public*/ void AbstractMonFrame::initComponents() throw (Exception)
{

    p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");
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

    // fix a width for current character set
//    JTextField* t = new JTextField(80);
//    int x = jScrollPane1->sizeHint().width()+t->sizeHint().width();
//    int y = jScrollPane1->sizeHint().height()+10*t->sizeHint().height();

//    //jScrollPane1->getViewport().add(monTextPane);
//    jScrollPane1->setWidget(monTextPane);
//    jScrollPane1->setWidgetResizable(true);
//    jScrollPane1->resize(QSize(x, y));
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

    alwaysOnTopCheckBox->setText("Window always on Top");
    alwaysOnTopCheckBox->setVisible(true);
    alwaysOnTopCheckBox->setToolTip("If checked, this window be always be displayed in front of any other window");
    alwaysOnTopCheckBox->setChecked(p->getSimplePreferenceState(alwaysOnTopCheck));
    setAlwaysOnTop(alwaysOnTopCheckBox->isChecked());

    autoScrollCheckBox->setText("Auto scroll");
    autoScrollCheckBox->setVisible(true);
    autoScrollCheckBox->setToolTip("If checked, always scroll to the latest log entry");
    autoScrollCheckBox->setChecked(!p->getSimplePreferenceState(autoScrollCheck));

    openFileChooserButton->setText("Choose log file");
    openFileChooserButton->setVisible(true);
    openFileChooserButton->setToolTip("Click here to select a new output log file");

    setTitle(title());

    QVBoxLayout* contentPaneLayout;
    getContentPane()->setLayout(contentPaneLayout = new QVBoxLayout());//, BoxLayout.Y_AXIS));

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
    connect(alwaysOnTopCheckBox, SIGNAL(clicked(bool)), this, SLOT(On_alwaysOnTopCheckBox(bool)));

//    autoScrollCheckBox.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            doAutoScroll(monTextPane, autoScrollCheckBox.isChecked());
//        }
//    });
    connect(autoScrollCheckBox, SIGNAL(clicked()), this, SLOT(On_autoScrollCheckBox()));

 // set file chooser to a default
 logFileChooser->setSelectedFile(new File("monitorLog.txt"));

 // connect to data source
 init();

 // add help menu to window
 setHelp();

 // prevent button areas from expanding
 pack();
 //paneALayout->setMaximumSize(paneALayout->sizeHint());
 pack();
}

void AbstractMonFrame::On_alwaysOnTopCheckBox(bool bChecked)
{
 Qt::WindowFlags flags = windowFlags();
 if (bChecked)
 {
  this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
  this->show();
 }
 else
 {
  this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
  this->show();
 }

}

void AbstractMonFrame::On_autoScrollCheckBox()
{
 doAutoScroll(monTextPane, autoScrollCheckBox->isChecked());
}

/**
 * Define help menu for this window.
 * <p>
 * By default, provides a generic help page that covers general features.
 * Specific implementations can override this to show their own help page if
 * desired.
 */
/*protected*/ void AbstractMonFrame::setHelp() {
    addHelpMenu("package.jmri.jmrix.AbstractMonFrame", true); // NOI18N
}

/*public*/ void AbstractMonFrame::nextLine(QString line, QString raw)
{
 // handle display of traffic
 // line is the traffic in 'normal form', raw is the "raw form"
 // Both should be one or more well-formed lines, e.g. end with \n
 //StringBuffer sb = new StringBuffer(120);
 QString sb;

 // display the timestamp if requested
 if ( timeCheckBox->isChecked() )
 {
  sb.append(QDateTime::currentDateTime().toString(df) + " " ) ;    }

 // display the raw data if requested
 if ( rawCheckBox->isChecked() )
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
  linesBuffer.append( sb/*.toString() */);
 }

 // if not frozen, display it in the Swing thread
 if (!freezeButton->isChecked())
 {
//        Runnable r = new Runnable() {
//            /*public*/ void run() {
//                synchronized( self )
//                {
   monTextPane->append( linesBuffer/*.toString()*/ );
   int LineCount = monTextPane->document()->lineCount();
   if( LineCount > MAX_LINES )
   {
    LineCount -= MAX_LINES ;
//                        try {
//                            int offset = monTextPane->getLineStartOffset(LineCount);
//                            monTextPane->document()->remove(0, offset ) ;
//                        }
//                        catch (BadLocationException ex) {
//                        }
    QTextCursor tc = monTextPane->textCursor();
    tc.movePosition(QTextCursor::Start);
    tc.setPosition(500);
    tc.removeSelectedText();
   }
   linesBuffer = "";
   if(autoScrollCheckBox->isChecked())
    monTextPane->moveCursor( QTextCursor::End);
//                    linesBuffer.setLength(0) ;
//                }
//            }
//        };
//        javax.swing.SwingUtilities.invokeLater(r);
 }

 // if requested, log to a file.
#if 0
 if (logStream != NULL) {
     synchronized (logStream)
     {
         QString logLine = sb.toString();
         if (!newline == ("\n"))
         {
             // have to massage the line-ends
             int i = 0;
             int lim = sb.length();
             QString out;// = new StringBuffer(sb.length()+10);  // arbitrary guess at space
             for ( i = 0; i<lim; i++) {
                 if (sb.at(i) == '\n')
                     out.append(newline);
                 else
                     out.append(sb.at(i));
             }
             logLine = out/*.toString()*/;
         }
         logStream->print(logLine);
     }
 }
#endif
}

AMFWorker::AMFWorker() {}
void AMFWorker::process()
{

}

/*public*/ /*synchronized*/ void AbstractMonFrame::clearButtonActionPerformed(JActionEvent* e) {
    // clear the monitoring history
//    synchronized( linesBuffer )
    {
//        linesBuffer.setLength(0);
//        monTextPane.setText("");
    }
}

/*public*/ /*synchronized*/ void AbstractMonFrame::startLogButtonActionPerformed(JActionEvent* e) {
    // start logging by creating the stream
    if ( logStream==NULL) {  // successive clicks don't restart the file
        // start logging
        try {
//            logStream = new PrintStream (new FileOutputStream(logFileChooser->getSelectedFile()));
        } catch (Exception ex) {
            log->error("exception "+ex.getMessage());
        }
    }
}

/*public*/ /*synchronized*/ void AbstractMonFrame::stopLogButtonActionPerformed(JActionEvent* e) {
    // stop logging by removing the stream
    if (logStream!=NULL) {
//        synchronized (logStream)
        {
//            logStream.flush();
//            logStream.close();
        }
        logStream = NULL;
    }
}

/*public*/ void AbstractMonFrame::openFileChooserButtonActionPerformed(JActionEvent*e) {
    // start at current file, show dialog
    int retVal = logFileChooser->showSaveDialog(this);

    // handle selection or cancel
    if (retVal == JFileChooser::APPROVE_OPTION) {
        bool loggingNow = (logStream != NULL);
        stopLogButtonActionPerformed(e);  // stop before changing file
        //File file = logFileChooser.getSelectedFile();
        // if we were currently logging, start the new file
        if (loggingNow) startLogButtonActionPerformed(e);
    }
}

/*public*/ void AbstractMonFrame::enterButtonActionPerformed(JActionEvent* /*e*/) {
    nextLine(entryField->text()+"\n", "");
}

/*public*/ /*synchronized*/ QString AbstractMonFrame::getFrameText()
{
    return linesBuffer/*.toString()*/;
}

/**
 * Method to position caret at end of JTextArea ta when
 * scroll true.
 * @param ta Reference to JTextArea
 * @param scroll True to move to end
 */
/*private*/ void AbstractMonFrame::doAutoScroll(/*final*/ JTextArea* ta, /*final*/ bool scroll) {
//    SwingUtilities.invokeLater(new Runnable()
//    {
//        //@Override
//        /*public*/ void run()
        {
            int len = ta->toPlainText().length();
//            if (scroll) {
//                ta->setCaretPosition(len);
//            } else if (ta.getCaretPosition()==len && len>0) {
//                ta.setCaretPosition(len-1);
//            }
        }
//    });
}

/*private*/ /*static*/ /*final*/ Logger* AbstractMonFrame::log = LoggerFactory::getLogger("AbstractMonFrame");
//}
