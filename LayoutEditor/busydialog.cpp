#include "busydialog.h"
#include <QBoxLayout>
#include <QProgressBar>

//BusyDialog::BusyDialog(QWidget *parent) :
//  JDialog(parent)
//{
//}
// class BusyDialog
//
// Creates a simple "indeterminate" busy spinner dialog...
//class BusyDialog extends JDialog {

    /**
     *
     */
    //private static final long serialVersionUID = -8208365926206646918L;

    /*public*/ BusyDialog::BusyDialog(JFrame* frame, QString title, bool modal,QWidget *parent) :
  JDialog((QWidget*)frame, title, modal) {
        //super(frame, title, modal);
        this->frame = frame;
        initComponents();
    }

    /*public*/ void BusyDialog::initComponents() {

// TODO:        setLocationRelativeTo(frame);
        resize(QSize(200, 100));
        setMinimumSize(QSize(200, 100));
        //setLayout(new BorderLayout(10, 10));
        QVBoxLayout* thisLayout = new QVBoxLayout(this);

        pbar = new QProgressBar();
        //pbar->setIndeterminate(true);
        //pbar->setBorder(BorderFactory.createEmptyBorder(10, 20, 10, 20));
        //pbar.setBorderPainted(true);
        thisLayout->addWidget(pbar, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
    }

    //@SuppressWarnings("deprecation")
    /*public*/ void BusyDialog::start() {
        this->pack();
        this->setVisible(true);
        //this->getContentPane().paintAll(pbar.getGraphics());
        this->show();
    }

    /*public*/ void BusyDialog::finish() {
        this->close();

    }
