#include "reportcontextaction.h"
#include "windowinterface.h"
#include "jmrijframe.h"
#include <QTextBrowser>
#include <QClipboard>
#include <QApplication>
#include "reportcontext.h"
#include <QPushButton>
#include "flowlayout.h"
#include "system.h"

/**
 * Swing action to display the JMRI context for the user
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 * @author Matt Harris Copyright (C) 2008
 *
 */
 ///*public*/ class ReportContextAction extends jmri.util.swing.JmriAbstractAction {

/*public*/ ReportContextAction::ReportContextAction(QString s, WindowInterface* wi)
 : AbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ ReportContextAction::ReportContextAction(QString s, QIcon i, WindowInterface* wi)
 : AbstractAction(s, i, wi)

{
    //super(s, i, wi);
 common();
}

/*public*/ ReportContextAction::ReportContextAction(QObject* parent)
 :  AbstractAction(tr("Context"), parent)
{
    //super(tr("TitleContext"));
 common();
}

void ReportContextAction::common()
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed(ActionEvent*)));
}

/*public*/ void ReportContextAction::actionPerformed(ActionEvent* ev)
{

    frame = new JmriJFrame(tr("Context"));  // JmriJFrame to ensure fits on screen
    QVBoxLayout* frameLayout = (QVBoxLayout*)frame->getContentPane()->layout();

    ///*final*/ Clipboard clipboard = frame.getToolkit().getSystemClipboard();
    QClipboard *clipboard = QApplication::clipboard();

    pane = new QTextBrowser();
    pane->append("\n"); // add a little space at top
    //pane.setEditable(false);
    //pane->setLineWrap(true);
    //pane.setWrapStyleWord(true);
    //pane.setColumns(120);
    pane->setLineWrapMode(QTextEdit::FixedColumnWidth);
    pane->setLineWrapColumnOrWidth(800);

//    JScrollPane scroll = new JScrollPane(pane);
//    frame.add(scroll, BorderLayout.CENTER);
    frameLayout->addWidget(pane,0, Qt::AlignCenter);

    ReportContext* r = new ReportContext();
    addString(r->getReport(true));

    pane->append("\n"); // add a little space at bottom

    // Add button to allow copy to clipboard
    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout);
    QPushButton* copy = new QPushButton(tr("Copy Clip"));
//    copy.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            StringSelection text = new StringSelection(pane.getText());
//            clipboard.setContents(text, text);
//        }
//    });
    connect(copy, SIGNAL(clicked(bool)), this, SLOT(on_copyClicked()));
    p->layout()->addWidget(copy);
    QPushButton* close = new QPushButton(tr("Close"));
//    close.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            frame.setVisible(false);
//            frame.dispose();
//        }
//    });
    connect(close, SIGNAL(clicked(bool)), this, SLOT(on_closeClicked()));
    p->layout()->addWidget(close);
    //frame.add(p, BorderLayout.SOUTH);
    frameLayout->addWidget(p, 0, Qt::AlignBottom);
    frame->adjustSize();

    // start scrolled to top
//    pane.setCaretPosition(0);
//    JScrollBar b = scroll.getVerticalScrollBar();
//    b.setValue(b.getMaximum());

    // show
    frame->setVisible(true);

}

/*public*/ void ReportContextAction::on_copyClicked()
{
//    StringSelection text = new StringSelection(pane.getText());
//    clipboard.setContents(text, text);
 pane->copy();
}

/*public*/ void ReportContextAction::on_closeClicked() {
    frame->setVisible(false);
    frame->dispose();
}

void ReportContextAction::addString(QString val) {
    pane->append(val + "\n");
}

void ReportContextAction::addProperty(QString prop) {
    addString(prop + ": " + System::getProperty(prop) + "  ");
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* ReportContextAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
