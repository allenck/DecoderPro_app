#include "editcommentdialog.h"
#include "jpanel.h"
#include "jbutton.h"

/**
 * Show a dialog that lets the user edit a multiline comment
 *
 * @author Daniel Bergqvist 2021
 */
// /*public*/ class EditCommentDialog {

    /*private*/ /*static*/ /*final*/ int EditCommentDialog::panelWidth = 500;
    /*private*/ /*static*/ /*final*/ int EditCommentDialog::panelHeight = 500;



    /*public*/ EditCommentDialog::EditCommentDialog(QObject* parent) :QObject(parent){
    }

    /*public*/ QString EditCommentDialog::showDialog(QString comment) {

        _comment = comment;

        _commentTextArea->setText(comment);

        _editCommentDialog  = new JDialog(
                (JDialog*)nullptr,
                tr("EditComment"),
                true);


        QWidget* contentPanel = _editCommentDialog->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
        p->setLayout(new QVBoxLayout());//p, BoxLayout.Y_AXIS));
        p->layout()->addWidget(_commentLabel);

//        JScrollPane commentScroller = new JScrollPane(_commentTextArea);
//        commentScroller.setPreferredSize(new Dimension(panelWidth, panelHeight));
        p->layout()->addWidget(/*commentScroller*/_commentTextArea);

        contentPanel->layout()->addWidget(p);
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));

        contentPanel->layout()->addWidget(panel3);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());

        // Cancel
        JButton* buttonCancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(buttonCancel);
        connect(buttonCancel, &JButton::clicked, [=] {
            cancelPressed(nullptr);
        });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
        buttonCancel->setToolTip("Press to return to Logix Table without any changes");      // NOI18N

        // OK
        JButton* buttonOK = new JButton(tr("OK"));    // NOI18N
        panel5->layout()->addWidget(buttonOK);
        connect(buttonOK, &JButton::clicked, [=] {
            okPressed(nullptr);
        });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
        buttonOK->setToolTip("Press to return to save changes");      // NOI18N
#if 0
        _editCommentDialog.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent e) {
                cancelPressed(null);
            }
        });
#endif
        contentPanel->layout()->addWidget(panel5);

        _editCommentDialog->setMinimumSize(QSize(panelWidth, panelHeight));

//        addLogixNGFrame.setLocationRelativeTo(component);
//        _editCommentDialog->setLocationRelativeTo(null);
        _editCommentDialog->pack();
        _editCommentDialog->setVisible(true);

        return _comment;
    }

    /*final*/ /*protected*/ void EditCommentDialog::cancelPressed(JActionEvent* e) {
        _editCommentDialog->setVisible(false);
        _editCommentDialog->dispose();
        _editCommentDialog = nullptr;
    }

    /*final*/ /*protected*/ void EditCommentDialog::okPressed(QActionEvent* e) {
        if (_commentTextArea->getText().isEmpty()) {
            _comment = "";
        } else {
            _comment = _commentTextArea->getText();
        }
        _editCommentDialog->setVisible(false);
        _editCommentDialog->dispose();
        _editCommentDialog = nullptr;
    }
