#include "jythonwindow.h"
#include "jtextarea.h"
#include <QCheckBox>
#include "userpreferencesmanager.h"
#include <QPushButton>
#include "instancemanager.h"
#include "jframe.h"
#include <QBoxLayout>
#include <QScrollArea>
#include "flowlayout.h"
#include "jmrijframe.h"
#include "PythonQt.h"


//JythonWindow::JythonWindow(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * This Action creates a JmriJFrame displaying the thread output log from the
 * {@link RunJythonScript} class.
 *
 * @author	Bob Jacobsen Copyright (C) 2004
 * @author Matthew Harris Copyright (C) 2010
 * @version $Revision: 28771 $
 */
// /*public*/ class JythonWindow extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 2991411495753279905L;
JythonWindow* JythonWindow::_instance = NULL;

/**
 * Constructor just initializes parent class.
 *
 * @param name Action name
 */
/*public*/ JythonWindow::JythonWindow(QString name, QObject *parent) :
  AbstractAction(name, parent)
{
 //super(name);
 common();
}

/*public*/ JythonWindow::JythonWindow(QObject *parent) :
  AbstractAction(tr("Script Output Window"),parent)
{
 //super("Script Output Window");
 common();
}
void JythonWindow::common()
{
 alwaysOnTopCheck = QString(this->metaObject()->className()) + ".alwaysOnTop";
 alwaysScrollCheck = QString(this->metaObject()->className()) + ".alwaysScroll";
 alwaysOnTopCheckBox = new QCheckBox();
 //alwaysOnTopCheckBox->setChecked(true);
 area = new JTextArea(12,50);

 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

 connect(PythonQt::self(), SIGNAL(pythonStdErr(QString)), this, SLOT(On_stdErr(QString)));
 connect(PythonQt::self(), SIGNAL(pythonStdOut(QString)), this, SLOT(On_stdOut(QString)));

 _instance = this;
 f = NULL;
}
/**
 * Invoking this action via an event triggers display of a file dialog. If a
 * file is selected, it's then invoked as a script.
 *
 * @param e
 */
/*public*/ void JythonWindow::actionPerformed(JActionEvent * /*e*/)
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 //PythonInterp.getPythonInterpreter();

//    java.util.ResourceBundle rb = java.util.ResourceBundle.getBundle("jmri.jmrit.jython.JythonBundle");

 f = new JmriJFrameX(tr("Script Output"));
 f->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
 QWidget* centralWidget = new QWidget;
 QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
 f->setCentralWidget(centralWidget);
// f.getContentPane().add(
//         new JScrollPane(
//                 area = new javax.swing.JTextArea(jmri.util.PythonInterp.getOutputArea().getDocument(), null, 12, 50),
//                 ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
//                 ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED
//         ), BorderLayout.CENTER);
 //area = new JTextArea(12,50);
 area->setTabStopWidth(4);
 QScrollArea* js;
 centralWidgetLayout->addWidget(js = new QScrollArea);
 js->setWidget(area);
 js->setWidgetResizable(true);

 // Add checkbox to enable/disable auto-scrolling
 QWidget* p = new QWidget();
 FlowLayout* pLayout = new FlowLayout(p);
 pLayout->addWidget(clearButton = new QPushButton(tr("Clear")));
 pLayout->addWidget(autoScroll = new QCheckBox(tr("Auto Scroll")/*, true*/));
 //autoScroll->setChecked(true);
 autoScroll->setChecked(pref->getSimplePreferenceState(alwaysScrollCheck));
 alwaysOnTopCheckBox->setText("Window always on Top");
 alwaysOnTopCheckBox->setVisible(true);
 alwaysOnTopCheckBox->setToolTip(tr("If checked, this window be always be displayed in front of any other window"));
 alwaysOnTopCheckBox->setChecked(pref->getSimplePreferenceState(alwaysOnTopCheck));
 pLayout->addWidget(alwaysOnTopCheckBox);
 f->pack();
 if(pref->getSaveWindowLocation(QString(this->metaObject()->className())))
 {
  f->move(pref->getWindowLocation(QString(this->metaObject()->className())));
 }
 if(pref->getSaveWindowSize(QString(this->metaObject()->className())))
 {
  f->resize(pref->getWindowSize(QString(this->metaObject()->className())));
 }
 else
  f->resize(500, 400);

 f->setAlwaysOnTop(false);
 f->setAlwaysOnTop(alwaysOnTopCheckBox->isChecked());
 f->addWindowListener(new JWWindowListener(this));

// autoScroll.addItemListener(new ItemListener() {

//     // Reference to the JTextArea of this instantiation
//     JTextArea ta = area;

//     /*public*/ void itemStateChanged(ItemEvent e) {
//         if (e.getStateChange() == ItemEvent.SELECTED) {
//             doAutoScroll(ta, true);
//             pref.setSimplePreferenceState(alwaysScrollCheck, autoScroll.isSelected());
//         }
//     }
// });
 connect(autoScroll, SIGNAL(toggled(bool)), this, SLOT(on_autoScroll_toggled(bool)));

// alwaysOnTopCheckBox.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         f.setAlwaysOnTop(alwaysOnTopCheckBox.isSelected());
//         pref.setSimplePreferenceState(alwaysOnTopCheck, alwaysOnTopCheckBox.isSelected());
//     }
// });
 connect(alwaysOnTopCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_alwaysOnTopCheckBox_toggled(bool)));

// clearButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         area.setText("");
//     }
// });
 connect(clearButton, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));
 //f.getContentPane().add(p, BorderLayout.PAGE_END);
 centralWidgetLayout->addWidget(p);

 // set a monospaced font
 int size = area->font().pointSize();
 area->setFont(QFont("Monospaced", size, QFont::Normal));
 defaultTextBackground = area->textBackgroundColor();
 defaultTextColor = area->textColor();

#if 0 // TODO:
 // Add document listener to scroll to end when modified
 area.getDocument().addDocumentListener(new DocumentListener() {

     // References to the JTextArea and JCheckBox
     // of this instantiation
     JTextArea ta = area;
     JCheckBox chk = autoScroll;

     /*public*/ void insertUpdate(DocumentEvent e) {
         doAutoScroll(ta, chk.isSelected());
     }

     /*public*/ void removeUpdate(DocumentEvent e) {
         doAutoScroll(ta, chk.isSelected());
     }

     /*public*/ void changedUpdate(DocumentEvent e) {
         doAutoScroll(ta, chk.isSelected());
     }
 });
#endif
 // Scroll to end of document
 doAutoScroll(area, true);
 f->showNormal();
 f->activateWindow();
 f->raise();

 f->setVisible(true);
}

void JythonWindow::on_autoScroll_toggled(bool b)
{
 JTextArea* ta = area;

 doAutoScroll(ta, b);
 pref->setSimplePreferenceState(alwaysScrollCheck, b);

}

void JythonWindow::on_alwaysOnTopCheckBox_toggled(bool b)
{
 //f->setAlwaysOnTop(b);
 QSize size = f->size();
 QPoint pos = f->pos();
 disconnect(alwaysOnTopCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_alwaysOnTopCheckBox_toggled(bool)));
 disconnect(clearButton, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));
 disconnect(autoScroll, SIGNAL(toggled(bool)), this, SLOT(on_autoScroll_toggled(bool)));
 f->close();
 f->deleteLater();

 pref->setSimplePreferenceState(alwaysOnTopCheck, b);

 actionPerformed();
 f->setLocation(pos);
 f->resize(size);
}

/**
 * Method to position caret at end of JTextArea ta when scroll true.
 *
 * @param ta     Reference to JTextArea
 * @param scroll True to move to end
 */
/*private*/ void JythonWindow::doAutoScroll(JTextArea* ta, bool scroll)
{
 if (scroll)
 {
  //ta.setCaretPosition(ta.getText().length());
  QTextCursor cursor(ta->document());
  cursor.setPosition(ta->toPlainText().length());
  ta->setTextCursor(cursor);
 }
}
void JythonWindow::on_clearButton_clicked()
{
 area->setText("");
}

/*public*/ JFrame* JythonWindow::getFrame() {
    return f;
}
void JythonWindow::On_stdErr(QString err)
{
 if(f == NULL)
  actionPerformed();
// setTextColors(QColor(Qt::white), QColor(Qt::red));
// area->append(err);
 _err += err;
 int idx;
 while ((idx = _err.indexOf('\n'))!=-1)
 {
//    consoleMessage(_stdErr.left(idx));
//    std::cerr << _stdErr.left(idx).toLatin1().data() << std::endl;
     setTextColors(QColor(Qt::white), QColor(Qt::red));
  area->append( _err.left(idx) );
   _err = _err.mid(idx+1);
 }
}

void JythonWindow::On_stdOut(QString out)
{
// setTextColors(QColor(Qt::white), QColor(Qt::black));
// area->append(out);
    _err += out;
    int idx;
    while ((idx = _err.indexOf('\n'))!=-1)
    {
   //    consoleMessage(_stdErr.left(idx));
   //    std::cerr << _stdErr.left(idx).toLatin1().data() << std::endl;
     setTextColors(QColor(Qt::white), QColor(Qt::black));
     area->append( _err.left(idx) );
      _err = _err.mid(idx+1);
    }
}

JythonWindow* JythonWindow::instance()
{
 if(_instance->f == NULL)
  _instance->actionPerformed();
 return _instance;
}
void JythonWindow::appendText(QString text)
{
 area->append(text);
}

JWWindowListener::JWWindowListener(JythonWindow *parent)
{
 this->parent = parent;
}

void JythonWindow::setDefaultTextcolor()
{
 area->setTextBackgroundColor(defaultTextBackground);
 area->setTextColor(defaultTextColor);
}

void JythonWindow::setTextColors(QColor background, QColor textColor)
{
 if(area == nullptr)
  actionPerformed();
 area->setTextBackgroundColor(background);
 area->setTextColor(textColor);
}


void JWWindowListener::windowClosing(QCloseEvent *)
{
 //pref->setSaveWindowLocation(QString(this->metaObject()->className()),true);
 parent->pref->setWindowLocation(QString(parent->metaObject()->className()), parent->f->pos());
 //pref->setSaveWindowSize(QString(this->metaObject()->className()),true);
 parent->pref->setWindowSize(QString(parent->metaObject()->className()),parent->f->size());
 //parent->f = NULL;
 parent->f->setHidden(true);
}
