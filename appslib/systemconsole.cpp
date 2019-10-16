#include "systemconsole.h"
#include "jmrijframe.h"
#include <QButtonGroup>
#include <QMenu>
#include <QCheckBox>
#include "jframe.h"
#include "instancemanager.h"
#include <QTextStream>
#include <stdio.h>
#include "logger.h"
#include <QClipboard>
#include <QApplication>
#include "flowlayout.h"
#include <QPushButton>
#include "userpreferencesmanager.h"
#include "borderlayout.h"
#include <QScrollArea>
#include <QRadioButton>
#include <QSignalMapper>
#include <QActionGroup>
#include "consoleinterface.h"
#include <QScrollBar>

//SystemConsole::SystemConsole(QObject *parent) :
//  JTextArea(parent)
//{
//}
/**
 * Class to direct standard output and standard error to a JTextArea. This
 * allows for easier clipboard operations etc.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris copyright (c) 2010, 2011, 2012
 * @version $Revision: 29218 $
 */
///*public*/  /*final*/ class SystemConsole extends JTextArea {

/**
 *
 */
///*private*/ static /*final*/ long serialVersionUID = 1807853160696208390L;

//static /*final*/ ResourceBundle rbc = ResourceBundle.getBundle("apps.AppsConfigBundle"); // NOI18N

/*private*/ /*static*/ /*final*/ int SystemConsole::STD_ERR = 1;
/*private*/ /*static*/ /*final*/ int SystemConsole::STD_OUT = 2;
/*private*/ /*static*/ SystemConsole* SystemConsole::instance = NULL;



/**
 * Initialise the system console ensuring both System.out and System.err
 * streams are re-directed to the consoles JTextArea
 */
/*public*/  /*static*/ void SystemConsole::create()
{
 if (instance == NULL) {
     instance = new SystemConsole();
 }
}

/*private*/ SystemConsole::SystemConsole(QObject *parent) :
  QObject(parent)
{
 log = new Logger("SystemConsole");
 frame = NULL;
 popup = new QMenu();
 copySelection = NULL;
 wrapMenu = NULL;
 wrapGroup = NULL;
 schemeMenu = NULL;
 scheme = 0; // Green on Black
 fontSize = 14;
 fontStyle = PLAIN;
 fontFamily = "Monospace";  //NOI18N
 wrapStyle = WRAP_STYLE_WORD;
 alwaysScrollCheck = QString("apps.SystemConsole.alwaysScroll"); //NO
 alwaysOnTopCheck = QString("apps.SystemConsole.alwaysOnTop");   //NOI18N
 schemes = NULL;
 autoScroll = new QCheckBox(tr("Auto-scroll"));

 // Record current System.out and System.err
 // so that we can still send to them
 originalOut = /*System.out*/ new QTextStream(stdout);
 originalErr = /*System.err*/ new QTextStream(stderr);

 // Create the console text area
 console = new JTextArea();

 // Setup the console text area
 console->setRows(20);
 console->setColumns(120);
 console->setMinimumSize(100,20);
 QFont f = QFont(fontFamily, fontSize, (fontStyle& BOLD?QFont::Bold:QFont::Normal),fontStyle*ITALIC?QFont::StyleItalic:QFont::StyleNormal);

// console->setEditable(false);
 console->setVisible(false);
// console->setReadOnly(true);
 f.setFixedPitch(true);
 log->debug("font = " + f.toString());
 console->setFont(f);
 console->setContextMenuPolicy(Qt::CustomContextMenu);

 console->append("Console started");
 QSizePolicy sizePolicy = console->sizePolicy();
 sizePolicy.setHorizontalStretch(1);
 sizePolicy.setVerticalStretch(1);
// sizePolicy.setHeightForWidth(console->sizePolicy().hasWidthForHeight());
 console->setSizePolicy(sizePolicy);
 connect(console, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(On_contextMenu(QPoint)));

 setScheme(scheme);
 setWrapStyle(wrapStyle);

 this->outputStream = new QTextStream(stdout);
 this->errorStream = new QTextStream(stderr);

 // Then redirect to it
 redirectSystemStreams();

 connect(ConsoleInterface::instance(), SIGNAL(message(QString,LoggingEvent*)), this, SLOT(On_appendText(QString)));
}

void SystemConsole::On_appendText(QString text)
{
 console->append(text);
 if(autoScroll->isChecked())
 {
  QScrollBar* sb = console->verticalScrollBar();
  if(sb != NULL)
   sb->setValue(sb->maximum());
 }
}

/**
 * Get current SystemConsole instance.
 * If one doesn't yet exist, create it.
 * @return current SystemConsole instance
 */
/*public*/  /*static*/ SystemConsole* SystemConsole::getInstance()
{
 if (instance == NULL)
 {
  SystemConsole::create();
 }
 return instance;
}


/**
 * Return the JFrame containing the console
 *
 * @return console JFrame
 */
/*public*/  /*static*/ JmriJFrame* SystemConsole::getConsole() {
    return SystemConsole::getInstance()->getFrame();
}

/*public*/  JmriJFrame* SystemConsole::getFrame()
{
 // Check if we've created the frame and do so if not
 if (frame == NULL)
 {
  log->debug("Creating frame for console");
  // To avoid possible locks, frame layout should be
  // performed on the Swing thread
//        if (SwingUtilities.isEventDispatchThread()) {
  createFrame();
//        } else {
//            try {
//                // Use invokeAndWait method as we don't want to
//                // return until the frame layout is completed
//                SwingUtilities.invokeAndWait(this::createFrame);
//            } catch (InterruptedException | InvocationTargetException ex) {
//                log->error("Exception creating system console frame: " + ex);
//            }
//        }
  log->debug("Frame created");
 }

 return frame;
}

/**
 * Layout the console frame
 */
/*private*/ void SystemConsole::createFrame()
{
 // Use a JmriJFrame to ensure that we fit on the screen
 frame = new JmriJFrame(tr("JMRI System console"));
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 frame->setCentralWidget(centralWidget);
 frame->setMinimumSize(450,300);
 frame->resize(450,300);
 //BorderLayout* frameLayout = new BorderLayout(0,5);
 QVBoxLayout* frameLayout = new QVBoxLayout;
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");

 // Grab a reference to the system clipboard
 /*final*/ QClipboard* clipboard = /*frame.getToolkit().getSystemClipboard();*/ QApplication::clipboard();
Q_UNUSED(clipboard);
 // Setup the scroll pane
 //QScrollArea* scroll = new QScrollArea(console);
 //frameLayout->addWidget(console, BorderLayout::Center);
 frameLayout->addWidget(console, 0, Qt::AlignVCenter);
 //console->resize(400, 100);
 console->setVisible(true);
 console->setReadOnly(true);

 // Add button to allow copy to clipboard
 QWidget* p = new QWidget();
 FlowLayout* pLayout = new FlowLayout;
 p->setLayout(pLayout);
 QPushButton* copy = new QPushButton(tr("Copy to clipboard"));
//    copy.addActionListener((ActionEvent event) -> {
//        StringSelection text = new StringSelection(console->getText());
//        clipboard.setContents(text, text);
//    });
 pLayout->addWidget(copy);
 connect(copy, SIGNAL(clicked()), this, SLOT(On_copy_clicked()));

 // Add button to allow console window to be closed
 QPushButton* close = new QPushButton(tr("Close"));
//    close.addActionListener((ActionEvent event) -> {
//        frame.setVisible(false);
//        frame.dispose();
//    });
 connect(close, SIGNAL(clicked()), this, SLOT(On_close_clicked()));
 pLayout->addWidget(close);

//    QPushButton stackTrace = new QPushButton(tr("ButtonStackTrace"));
//    stackTrace.addActionListener((ActionEvent event) -> {
//        performStackTrace();
//    });
//    p.add(stackTrace);

 // Add checkbox to enable/disable auto-scrolling
 // Use the inverted SimplePreferenceState to default as enabled
 pLayout->addWidget(autoScroll);
 autoScroll->setChecked(!pref->getSimplePreferenceState(alwaysScrollCheck));
//    autoScroll.addActionListener((ActionEvent event) -> {
//        doAutoScroll(console, autoScroll.isSelected());
//        pref.setSimplePreferenceState(alwaysScrollCheck, !autoScroll.isSelected());
//    });
 connect(autoScroll, SIGNAL(toggled(bool)), this, SLOT(On_autoScroll_toggled(bool)));

 // Add checkbox to enable/disable always on top
 pLayout->addWidget(alwaysOnTop = new QCheckBox(tr("Always on top")));
alwaysOnTop->setChecked(pref->getSimplePreferenceState(alwaysOnTopCheck));
On_alwaysOnTop_toggled(alwaysOnTop->isChecked());
 alwaysOnTop->setVisible(true);
 alwaysOnTop->setToolTip(tr("If checked, this window be always be displayed in front of any other window"));
// alwaysOnTop.addActionListener((ActionEvent event) -> {
//     frame.setAlwaysOnTop(alwaysOnTop.isSelected());
//     pref.setSimplePreferenceState(alwaysOnTopCheck, alwaysOnTop.isSelected());
// });
 connect(alwaysOnTop, SIGNAL(toggled(bool)), this, SLOT(On_alwaysOnTop_toggled(bool)));
 ((JFrame*)frame)->setAlwaysOnTop(alwaysOnTop->isChecked());

 // Define the pop-up menu
 copySelection = new QAction(tr("Copy"), frame);
// copySelection.addActionListener((ActionEvent event) -> {
//     StringSelection text = new StringSelection(console->getSelectedText());
//     clipboard.setContents(text, text);
// });
 connect(copySelection, SIGNAL(triggered()), console, SLOT(copy()));
 popup->addAction(copySelection);

 QAction* menuItem = new QAction(tr("Copy to clipboard"), this);
// menuItem.addActionListener((ActionEvent event) -> {
//     StringSelection text = new StringSelection(console->getText());
//     clipboard.setContents(text, text);
// });
 connect(menuItem, SIGNAL(triggered()), console, SLOT(copy()));
 popup->addAction(menuItem);

 popup->addSeparator();

#if 0
 // Define the colour scheme sub-menu
 schemeMenu = new QMenu(tr("Color scheme"));
 schemeGroup = new QButtonGroup();
 foreach (/*final*/ Scheme* s,  schemes)
 {
     rbMenuItem = new JRadioButtonMenuItem(s.description);
     rbMenuItem.addActionListener((ActionEvent event) -> {
         setScheme(schemes.indexOf(s));
     });
     rbMenuItem.setSelected(getScheme() == schemes.indexOf(s));
     schemeMenu.add(rbMenuItem);
     schemeGroup.add(rbMenuItem);
 }
 popup.add(schemeMenu);

 // Define the wrap style sub-menu
 wrapMenu = new JMenu(tr("ConsoleWrapStyleMenu"));
 wrapGroup = new ButtonGroup();
 rbMenuItem = new JRadioButtonMenuItem(tr("ConsoleWrapStyleNone"));
 rbMenuItem.addActionListener((ActionEvent event) -> {
     setWrapStyle(WRAP_STYLE_NONE);
 });
 rbMenuItem.setSelected(getWrapStyle() == WRAP_STYLE_NONE);
 wrapMenu.add(rbMenuItem);
 wrapGroup.add(rbMenuItem);

 rbMenuItem = new JRadioButtonMenuItem(tr("ConsoleWrapStyleLine"));
 rbMenuItem.addActionListener((ActionEvent event) -> {
     setWrapStyle(WRAP_STYLE_LINE);
 });
 rbMenuItem.setSelected(getWrapStyle() == WRAP_STYLE_LINE);
 wrapMenu.add(rbMenuItem);
 wrapGroup.add(rbMenuItem);

 rbMenuItem = new JRadioButtonMenuItem(tr("ConsoleWrapStyleWord"));
 rbMenuItem.addActionListener((ActionEvent event) -> {
     setWrapStyle(WRAP_STYLE_WORD);
 });
 rbMenuItem.setSelected(getWrapStyle() == WRAP_STYLE_WORD);
 wrapMenu.add(rbMenuItem);
 wrapGroup.add(rbMenuItem);

 popup.add(wrapMenu);

 // Bind pop-up to objects
 MouseListener popupListener = new PopupListener();
 console->addMouseListener(popupListener);
 frame.addMouseListener(popupListener);

 // Add document listener to scroll to end when modified if required
 console->getDocument().addDocumentListener(new DocumentListener() {

     // References to the JTextArea and JCheckBox
     // of this instantiation
     JTextArea ta = console;
     JCheckBox chk = autoScroll;

     //@Override
     /*public*/  void insertUpdate(DocumentEvent e) {
         doAutoScroll(ta, chk.isSelected());
     }

     //@Override
     /*public*/  void removeUpdate(DocumentEvent e) {
         doAutoScroll(ta, chk.isSelected());
     }

     //@Override
     /*public*/  void changedUpdate(DocumentEvent e) {
         doAutoScroll(ta, chk.isSelected());
     }
 });
#endif

 // Add the button panel to the frame & then arrange everything
 //frameLayout->addWidget(p, BorderLayout::South);
 frameLayout->addWidget(p, 0, Qt::AlignBottom);
 centralWidgetLayout->addLayout(frameLayout);
 frame->adjustSize();
 //frame->pack();
 frame->setVisible(true);
}
void SystemConsole::On_copy_clicked()
{
 //        StringSelection text = new StringSelection(console->getText());
 console->copy();
 //        clipboard.setContents(text, text);
}
void SystemConsole::On_close_clicked()
{
 frame->setVisible(false);
 //frame->dispose();
}
void SystemConsole::On_alwaysOnTop_toggled(bool b)
{
 ((JFrame*)frame)->setAlwaysOnTop(b);
 pref->setSimplePreferenceState(alwaysOnTopCheck, b);

}
void SystemConsole::On_autoScroll_toggled(bool b)
{
 // ??
 pref->setSimplePreferenceState(alwaysScrollCheck, b);
}
void SystemConsole::On_contextMenu(QPoint /*pt*/)
{
 popup->clear();
 QAction* rbMenuItem;

 schemeMenu = new QMenu(tr("Color scheme"));
 schemeGroup = new QActionGroup(this);
 QSignalMapper* mapper = new QSignalMapper();
 int i = 0;
 foreach (/*final*/ Scheme* s,  *schemes)
 {
  rbMenuItem = new QAction(s->description, console);
  rbMenuItem->setCheckable(true);

//  rbMenuItem.addActionListener((ActionEvent event) -> {
//      setScheme(schemes.indexOf(s));
//  });
  mapper->setMapping(rbMenuItem, i++);
  connect(rbMenuItem, SIGNAL(toggled(bool)), mapper, SLOT(map()));
  rbMenuItem->setChecked(getScheme() == schemes->indexOf(s));
  schemeMenu->addAction(rbMenuItem);
  schemeGroup->addAction(rbMenuItem);
 }
 connect(mapper, SIGNAL(mapped(int)), this, SLOT(setScheme(int)));
 popup->addMenu(schemeMenu);

 // Define the wrap style sub-menu
 wrapMenu = new QMenu(tr("Wrap style"));
 wrapGroup = new QActionGroup(this);
 rbMenuItem = new QAction(tr("No text wrapping"), console);
// rbMenuItem.addActionListener((ActionEvent event) -> {
//     setWrapStyle(WRAP_STYLE_NONE);
// });
 connect(rbMenuItem, SIGNAL(toggled(bool)), this, SLOT(On_setWrapStyleNone()));
 rbMenuItem->setCheckable(true);
 rbMenuItem->setChecked(getWrapStyle() == WRAP_STYLE_NONE);
 wrapMenu->addAction(rbMenuItem);
 wrapGroup->addAction(rbMenuItem);

 rbMenuItem = new QAction(tr("Wrap text at end of line"), console);
// rbMenuItem.addActionListener((ActionEvent event) -> {
//     setWrapStyle(WRAP_STYLE_LINE);
// });
 connect(rbMenuItem, SIGNAL(triggered(bool)), this, SLOT(On_wrapLine()));
 rbMenuItem->setCheckable(true);
 rbMenuItem->setChecked(getWrapStyle() == WRAP_STYLE_LINE);
 wrapMenu->addAction(rbMenuItem);
 wrapGroup->addAction(rbMenuItem);

 rbMenuItem = new QAction(tr("ConsoleWrapStyleWord"), console);
// rbMenuItem.addActionListener((ActionEvent event) -> {
//     setWrapStyle(WRAP_STYLE_WORD);
// });
 connect(rbMenuItem, SIGNAL(triggered()), this, SLOT(On_wrapWord()));
 rbMenuItem->setCheckable(true);
 rbMenuItem->setChecked(getWrapStyle() == WRAP_STYLE_WORD);
 wrapMenu->addAction(rbMenuItem);
 wrapGroup->addAction(rbMenuItem);

 popup->addMenu(wrapMenu);
 QAction* copy = new QAction(tr("Copy"), this);
 popup->addSeparator();
 connect(copy, SIGNAL(triggered()), this, SLOT(On_copy_clicked()));

// // Bind pop-up to objects
// MouseListener popupListener = new PopupListener();
// console->addMouseListener(popupListener);
// frame.addMouseListener(popupListener);
 popup->exec(QCursor::pos());
}

/**
 * Add text to the console
 *
 * @param text  the text to add
 * @param which the stream that this text is for
 */
/*private*/ void SystemConsole::updateTextArea(/*final*/ QString text, /*final*/ int which)
{
 // Append message to the original System.out / System.err streams
 if (which == STD_OUT)
 {
  //originalOut.append(text);
  *originalOut << text;
 } else if (which == STD_ERR)
 {
 // originalErr.append(text);
  *originalErr << text;
 }

 // Now append to the JTextArea
 // As append method is thread safe, we don't need to run this on
 // the Swing dispatch thread
 console->append(text);
}
void SystemConsole::On_wrapLine()
{
 setWrapStyle(WRAP_STYLE_LINE);
}
void SystemConsole::On_wrapWord()
{
 setWrapStyle(WRAP_STYLE_WORD);
}
void SystemConsole::On_setWrapStyleNone()
{
 setWrapStyle(WRAP_STYLE_NONE);
}

/**
 * Method to position caret at end of JTextArea ta when scroll true.
 *
 * @param ta     Reference to JTextArea
 * @param scroll True to move to end
 */
/*private*/ void SystemConsole::doAutoScroll(/*final*/ JTextArea* /*ta*/, /*final*/ bool /*scroll*/)
{
//    SwingUtilities.invokeLater(() -> {
//        int len = ta.getText().length();
//        if (scroll) {
//            ta.setCaretPosition(len);
//        } else if (ta.getCaretPosition() == len && len > 0) {
//            ta.setCaretPosition(len - 1);
//        }
//    });
}

/**
 * Creates a new OutputStream for the specified stream
 *
 * @param which the stream, either STD_OUT or STD_ERR
 * @return the new OutputStream
 */
/*private*/ QDataStream* SystemConsole::outStream(/*final*/ int /*which*/)
{
#if 0
    return new QDataStream();
    {
        //@Override
        /*public*/  void write(int b) throws IOException {
            updateTextArea(String.valueOf((char) b), which);
        }

        //@Override
        //@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "DM_DEFAULT_ENCODING",
                justification = "Can only be called from the same instance so default encoding OK")
        /*public*/  void write(byte[] b, int off, int len) throws IOException {
            updateTextArea(new String(b, off, len), which);
        }

        //@Override
        /*public*/  void write(byte[] b) throws IOException {
            write(b, 0, b.length);
        }
    };
#endif
    return NULL;
}

/**
 * Method to redirect the system streams to the console
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "DM_DEFAULT_ENCODING",
//        justification = "Can only be called from the same instance so default encoding OK")
/*private*/ void SystemConsole::redirectSystemStreams() {
#if 0
    System.setOut(this.getOutputStream());
    System.setErr(this.getErrorStream());
#endif
}

/**
 * Set the console wrapping style to one of the following:
 *
 * @param style one of the defined style attributes - one of
 * <ul>
 * <li>{@link #WRAP_STYLE_NONE} No wrapping
 * <li>{@link #WRAP_STYLE_LINE} Wrap at end of line
 * <li>{@link #WRAP_STYLE_WORD} Wrap by word boundaries
 * </ul>
 */
/*public*/  void SystemConsole::setWrapStyle(int style) {
    wrapStyle = style;
    console->setLineWrapMode(style == WRAP_STYLE_NONE? QTextEdit::NoWrap: QTextEdit::WidgetWidth);
    console->setWordWrapMode(style == WRAP_STYLE_WORD?QTextOption::WrapAtWordBoundaryOrAnywhere:QTextOption::NoWrap);
#if 0
    if (wrapGroup != NULL) {
        wrapGroup.setSelected(wrapMenu.getItem(style).getModel(), true);
    }
#endif
}

/**
 * Retrieve the current console wrapping style
 *
 * @return current wrapping style - one of
 * <ul>
 * <li>{@link #WRAP_STYLE_NONE} No wrapping
 * <li>{@link #WRAP_STYLE_LINE} Wrap at end of line
 * <li>{@link #WRAP_STYLE_WORD} Wrap by word boundaries (default)
 * </ul>
 */
/*public*/  int SystemConsole::getWrapStyle() {
    return wrapStyle;
}

/**
 * Set the console font size
 *
 * @param size point size of font between 6 and 24 point
 */
/*public*/  void SystemConsole::setFontSize(int size)
{
 updateFont(fontFamily, fontStyle, (fontSize = size < 6 ? 6 : size > 24 ? 24 : size));
}

/**
 * Retrieve the current console font size (default 12 point)
 *
 * @return selected font size in points
 */
/*public*/  int SystemConsole::getFontSize() {
    return fontSize;
}

/**
 * Set the console font style
 *
 * @param style one of
 *              {@link Font#BOLD}, {@link Font#ITALIC}, {@link Font#PLAIN}
 *              (default)
 */
/*public*/  void SystemConsole::setFontStyle(int style)
{
 if (style == BOLD || style == ITALIC || style == PLAIN || style == (BOLD | ITALIC))
 {
  fontStyle = style;
 }
 else
 {
  fontStyle = PLAIN;
 }
 updateFont(fontFamily, fontStyle, fontSize);
}

/*public*/  void SystemConsole::setFontFamily(QString family)
{
 updateFont((fontFamily = family), fontStyle, fontSize);
}

/*public*/  QString SystemConsole::getFontFamily() {
    return fontFamily;
}

/**
 * Retrieve the current console font style
 *
 * @return selected font style - one of
 *         {@link Font#BOLD}, {@link Font#ITALIC}, {@link Font#PLAIN}
 *         (default)
 */
/*public*/  int SystemConsole::getFontStyle() {
    return fontStyle;
}

/**
 * Update the system console font with the specified parameters
 *
 * @param style font style
 * @param size  font size
 */
/*private*/ void SystemConsole::updateFont(QString family, int style, int size)
{
 console->setFont( QFont(family, size, style&BOLD?QFont::Bold:QFont::Normal, style& ITALIC?QFont::StyleItalic:QFont::StyleNormal));
 QFont f = console->font();
 log->debug(QString("font family = %1, size = %2, weight = %3, style = %4").arg(f.family()).arg(f.pointSize()).arg(f.weight()).arg(f.style()));
}

/**
 * Method to define console colour schemes
 */
/*private*/ void SystemConsole::defineSchemes() {
    schemes = new QList<Scheme*>();
    schemes->append(new SystemConsole::Scheme(tr("Green on Black"), Qt::green, Qt::black));
    schemes->append(new SystemConsole::Scheme(tr("Orange on Black"), QColor(255,165,0), Qt::black));
    schemes->append(new SystemConsole::Scheme(tr("White On Black"), Qt::white, Qt::black));
    schemes->append(new SystemConsole::Scheme(tr("Black On White"), Qt::black, Qt::white));
    schemes->append(new SystemConsole::Scheme(tr("White On Blue"), Qt::white, Qt::blue));
    schemes->append(new SystemConsole::Scheme(tr("Black On LightGray"), Qt::black, QColor(211,211,211)));
    schemes->append(new SystemConsole::Scheme(tr("Black On Gray"), Qt::black, Qt::gray));
    schemes->append(new SystemConsole::Scheme(tr("White On Gray"), Qt::white, Qt::gray));
    schemes->append(new SystemConsole::Scheme(tr("White On DarkGray"), Qt::white, QColor(112,128,144)));
    schemes->append(new SystemConsole::Scheme(tr("Green On DarkGray"), Qt::green, QColor(112,128,144)));
    schemes->append(new SystemConsole::Scheme(tr("Orange On DarkGray"), QColor(255,165,0), QColor(112,128,144)));
}

///*private*/ Map<Thread, StackTraceElement[]> traces;

///*private*/ void performStackTrace() {
//    System.out.println("----------- Begin Stack Trace -----------"); //NO18N
//    System.out.println("-----------------------------------------"); //NO18N
//    traces = new HashMap<>(Thread.getAllStackTraces());
//    for (Thread thread : traces.keySet()) {
//        System.out.println("[" + thread.getId() + "] " + thread.getName());
//        for (StackTraceElement el : thread.getStackTrace()) {
//            System.out.println("  " + el);
//        }
//        System.out.println("-----------------------------------------"); //NO18N
//    }
//    System.out.println("-----------  End Stack Trace  -----------"); //NO18N
//}

/**
 * Set the console colour scheme
 *
 * @param which the scheme to use
 */
/*public*/  void SystemConsole::setScheme(int which)
{
 scheme = which;

 if (schemes == NULL)
 {
  defineSchemes();
 }

 SystemConsole::Scheme* s;

 try {
     s = schemes->at(which);
 } catch (IndexOutOfBoundsException ex) {
     s = schemes->at(0);
     scheme = 0;
 }

//    console->setForeground(s.foreground);
//    console->setBackground(s.background);
 console->setStyleSheet(QString("QTextEdit {color: rgb(%1, %2, %3); background-color: rgb(%4, %5, %6); background-attachment: scroll;}").arg(s->foreground.red()).arg(s->foreground.green()).arg(s->foreground.blue()).arg(s->background.red()).arg(s->background.green()).arg(s->background.blue()));

 if (schemeGroup != NULL)
 {
//     schemeGroup->setSelected(schemeMenu.getItem(scheme).getModel(), true);
 }
}

/*public*/  QTextStream* SystemConsole::getOutputStream() {
    return this->outputStream;
}

/*public*/  QTextStream* SystemConsole::getErrorStream() {
    return this->errorStream;
}

/**
 * Retrieve the current console colour scheme
 *
 * @return selected colour scheme
 */
/*public*/  int SystemConsole::getScheme() {
    return scheme;
}

/*public*/  QList<SystemConsole::Scheme*>* SystemConsole::getSchemes()
{
 //return this.schemes.toArray(new Scheme[this.schemes.size()]);
 return schemes;
}

/**
 * Class holding details of each scheme
 */
///*public*/  static /*final*/ class Scheme {

//    /*public*/  Color foreground;
//    /*public*/  Color background;
//    /*public*/  String description;

    SystemConsole::Scheme::Scheme(QString description, QColor foreground, QColor background)
    {
     this->foreground = foreground;
     this->background = background;
     this->description = description;
    }
//}

///**
// * Class to deal with handling popup menu
// */
///*public*/  /*final*/ class PopupListener : QMouseAdapter {

// //@Override
// /*public*/  void mousePressed(MouseEvent e) {
//     maybeShowPopup(e);
// }

// //@Override
// /*public*/  void mouseReleased(MouseEvent e) {
//     maybeShowPopup(e);
// }

///*private*/ void SystemConsole::maybeShowPopup(QMouseEvent* e)
//{
//#if 0
// if (e.isPopupTrigger())
// {
//  copySelection.setEnabled(console->getSelectionStart() != console->getSelectionEnd());
//  popup.show(e.getComponent(), e.getX(), e.getY());
// }
//#endif
//}
