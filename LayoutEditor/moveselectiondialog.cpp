#include "moveselectiondialog.h"
#include "joptionpane.h"

/**
 * Implements the move selection dialog for the Layout Editor
 *
 * @author George Warner Copyright (c) 2019
 */
///*public*/ class MoveSelectionDialog {

    // operational instance variables
    /*private*/ LayoutEditor* layoutEditor = nullptr;

    // constructor method
    /*public*/ MoveSelectionDialog::MoveSelectionDialog(/*@Nonnull*/ LayoutEditor* thePanel) {
        layoutEditor = thePanel;
    }


    //display dialog for translation a selection
    //@InvokeOnGuiThread
    /*public*/ void MoveSelectionDialog::moveSelection() {
        if (moveSelectionOpen) {
            moveSelectionFrame->setVisible(true);
            return;
        }

        //Initialize if needed
        if (moveSelectionFrame == nullptr) {
            moveSelectionFrame = new JmriJFrameX(tr("Translate (Move) Selection"));
            moveSelectionFrame->addHelpMenu("package.jmri.jmrit.display.TranslateSelection", true);
            moveSelectionFrame->setLocation(70, 30);
            QWidget* theContentPane = moveSelectionFrame->getContentPane();
            theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

            //setup x translate
            JPanel* panel31 = new JPanel();
            panel31->setLayout(new FlowLayout());
            JLabel* xMoveLabel = new JLabel(tr("Horizontal (x) Translation:"));
            panel31->layout()->addWidget(xMoveLabel);
            xMoveLabel->setLabelFor(xMoveField);
            panel31->layout()->addWidget(xMoveField);
            xMoveField->setName("XTranslateLabel");
            xMoveField->setToolTip(tr("Enter units to move (0 = don't move; negative = move left; positive = move right)."));
            theContentPane->layout()->addWidget(panel31);

            //setup y translate
            JPanel* panel32 = new JPanel();
            panel32->setLayout(new FlowLayout());
            JLabel* yMoveLabel = new JLabel(tr("Vertical (y) Translation:"));
            panel32->layout()->addWidget(yMoveLabel);
            yMoveLabel->setLabelFor(yMoveField);
            panel32->layout()->addWidget(yMoveField);
            yMoveField->setName("YTranslateLabel");
            yMoveField->setToolTip(tr("Enter units to move (0 = don't move; negative = move up; positive = move down)."));
            theContentPane->layout()->addWidget(panel32);

            //setup information message
            JPanel* panel33 = new JPanel();
            panel33->setLayout(new FlowLayout());
            JLabel* message1Label = new JLabel(tr("Only items within selection rectangle will be moved."));
            panel33->layout()->addWidget(message1Label);
            theContentPane->layout()->addWidget(panel33);

            //set up Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            panel5->layout()->addWidget(moveSelectionDone = new QPushButton(tr("Move Selection")));
            //moveSelectionDone.addActionListener(this::moveSelectionDonePressed);
            connect(moveSelectionDone, &QPushButton::clicked, [=]{
             moveSelectionDonePressed();
            });
            moveSelectionDone->setToolTip(tr("Click here to move items within the selection rectangle."));
            panel5->layout()->addWidget(moveSelectionCancel = new QPushButton(tr("Cancel")));
            //moveSelectionCancel.addActionListener((ActionEvent event) -> moveSelectionCancelPressed());
            connect(moveSelectionCancel, &QPushButton::clicked, [=]{
             moveSelectionCancelPressed();
            });
            moveSelectionCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
            theContentPane->layout()->addWidget(panel5);

            //make this button the default button (return or enter activates)
//            JRootPane rootPane = SwingUtilities.getRootPane(moveSelectionDone);
//            rootPane.setDefaultButton(moveSelectionDone);
            moveSelectionDone->setDefault(true);
        }

        //Set up for Entry of Translation
        xMoveField->setText("0");
        yMoveField->setText("0");
//        moveSelectionFrame.addWindowListener(new WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(WindowEvent event) {
//                moveSelectionCancelPressed();
//            }
//        });
        moveSelectionFrame->addWindowListener(new MSD_windowListener(this));
        moveSelectionFrame->pack();
        moveSelectionFrame->setVisible(true);
        moveSelectionOpen = true;
    }

    /*private*/ void MoveSelectionDialog::moveSelectionDonePressed(/*@Nonnull ActionEvent event*/) {
        QString newText = "";
        float xTranslation = 0.0F;
        float yTranslation = 0.0F;

        //get x translation
        newText = xMoveField->text().trimmed();
        bool ok;
            xTranslation = newText.toFloat(&ok);
        if(!ok) {
            showEntryErrorDialog(moveSelectionFrame, NumberFormatException());
            return;
        }

        //get y translation
        newText = yMoveField->text().trimmed();

            yTranslation = newText.toFloat(&ok);
        if(!ok) {
            showEntryErrorDialog(moveSelectionFrame, NumberFormatException());
            return;
        }

        layoutEditor->translate(xTranslation, yTranslation);

        moveSelectionCancelPressed();
    }

    /*private*/ void MoveSelectionDialog::moveSelectionCancelPressed() {
        moveSelectionOpen = false;
        moveSelectionFrame->setVisible(false);
        moveSelectionFrame->dispose();
        moveSelectionFrame = nullptr;
    }

    /**
     * showEntryErrorDialog(Component parentComponent, NumberFormatException e)
     *
     * @param parentComponent determines the <code>Frame</code> in which the
     *                        dialog is displayed; if <code>null</code>, or if
     *                        the <code>parentComponent</code> has no
     *                        <code>Frame</code>, a default <code>Frame</code>
     *                        is used
     * @param e               Exception thrown to indicate that the application
     *                        has attempted to convert a string to one of the
     *                        numeric types, but that the string does not have
     *                        the appropriate format.
     */
    /*private*/ void MoveSelectionDialog::showEntryErrorDialog(QWidget* parentComponent, NumberFormatException e) {
        JOptionPane::showMessageDialog(parentComponent,
                tr("%1: %2 %3").arg(tr("Error in entry")).arg(
                        e.getMessage()).arg(tr("Please reenter or Cancel.")),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);
    }

    ///*private*/ final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(
    //        MoveSelectionDialog.class);
