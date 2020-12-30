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
#include <QScrollArea>
#include <QLabel>
#include "jtextarea.h"

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
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 zeroConf = new QZeroConf();
}

/*public*/ void ReportContextAction::actionPerformed(JActionEvent * )
{

    frame = new JmriJFrameX(tr("Context"));  // JmriJFrame to ensure fits on screen
    QVBoxLayout* frameLayout = (QVBoxLayout*)frame->getContentPane()->layout();
    ///*final*/ Clipboard clipboard = frame.getToolkit().getSystemClipboard();

    pane = new JTextArea();
    frame->setMaximumSize(400,300);
    //pane->("\n"); // add a little space at top
    addString("\n"); // add a little space at top
    //pane->setReadOnly(true);
    //pane->setWordWrap(true);
    pane->setTextInteractionFlags(Qt::TextSelectableByMouse);
    pane->setEditable(true);
    pane->setLineWrap(true);
    pane->setWrapStyleWord(true);
    pane->setColumns(120);

    //QFont font = pane->document()->defaultFont();    //# or another font if you change it
    QFont font = pane->font();
    QFontMetrics fontMetrics = QFontMetrics(font);      //# a QFontMetrics based on our font
    QSize textSize = fontMetrics.size(0, "M");

    int textWidth = textSize.width() + 30;       //# constant may need to be tweaked
    int textHeight = textSize.height() + 30;    // # constant may need to be tweaked

    //pane->setMinimumSize(textWidth, textHeight);
//    pane->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
//    pane->sizePolicy().setHorizontalStretch(1);
//    pane->sizePolicy().setVerticalStretch(1);
//    pane->setLineWrapMode(QTextEdit::FixedColumnWidth);
//    pane->setLineWrapColumnOrWidth(800);
//    pane->setMaximumSize(16777215,16777215);

//    QScrollArea* scroll = new QScrollArea(/*pane*/);
//    frameLayout->addWidget(scroll, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
//    frameLayout->addWidget(scroll,0, Qt::AlignCenter);
//    scroll->setWidget(pane);
//    scroll->setWidgetResizable(true);
    frameLayout->addWidget(pane);

    ReportContext* r = new ReportContext();
    addString(r->getReport(true));

    //pane->append("\n"); // add a little space at bottom
    addString("\n"); // add a little space at top

    QWidget* p = new QWidget();
    p->setLayout(new FlowLayout);
#if 0
    // Add button to allow copy to clipboard
    QPushButton* copy = new QPushButton(tr("Copy Clip"));
//    copy.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent event) {
//            StringSelection text = new StringSelection(pane.getText());
//            clipboard.setContents(text, text);
//        }
//    });
    connect(copy, SIGNAL(clicked(bool)), this, SLOT(on_copyClicked()));
    p->layout()->addWidget(copy);
#endif
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
    QMetaObject::connectSlotsByName(frame);

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
 //pane->copy();
 QClipboard* clipboard = QApplication::clipboard();
 QString selected = pane->textCursor().selectedText();
 clipboard->setText(selected);

}

/*public*/ void ReportContextAction::on_closeClicked() {
    frame->setVisible(false);
    frame->dispose();
}

void ReportContextAction::addString(QString val) {
    //pane->append(val + "\n");
 pane->append(val+ "\n");
}

void ReportContextAction::addProperty(QString prop) {
    addString(prop + ": " + System::getProperty(prop) + "  ");
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* ReportContextAction::makePanel() {
    throw  IllegalArgumentException("Should not be invoked");
}
