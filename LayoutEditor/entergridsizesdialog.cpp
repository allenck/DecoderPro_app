#include "entergridsizesdialog.h"
#include "jlabel.h"
#include "joptionpane.h"

/**
 * Layout Editor Dialogs implements some dialogs for the Layout Editor
 *
 * @author George Warner Copyright (c) 2019
 */
///*public*/ class EnterGridSizesDialog {


    // constructor method
    /*public*/ EnterGridSizesDialog::EnterGridSizesDialog(/*@Nonnull*/ LayoutEditor* thePanel) {
        layoutEditor = thePanel;
    }


    //display dialog for entering grid sizes
    //@InvokeOnGuiThread
    /*public*/ void EnterGridSizesDialog::enterGridSizes() {
        if (enterGridSizesOpen) {
            enterGridSizesFrame->setVisible(true);
            return;
        }

        //Initialize if needed
        if (enterGridSizesFrame == nullptr) {
            enterGridSizesFrame = new JmriJFrameX(tr("Set Grid Sizes"));
            enterGridSizesFrame->addHelpMenu("package.jmri.jmrit.display.EnterGridSizes", true);
            enterGridSizesFrame->setLocation(70, 30);
            QWidget* theContentPane = enterGridSizesFrame->getContentPane();
            theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

            //setup primary grid sizes
            JPanel* panel3 = new JPanel();
            panel3->setLayout(new FlowLayout());
            JLabel* primaryGridSizeLabel = new JLabel(tr("Primary Grid Size:"));
            panel3->layout()->addWidget(primaryGridSizeLabel);
            primaryGridSizeLabel->setLabelFor(primaryGridSizeField);
            panel3->layout()->addWidget(primaryGridSizeField);
            primaryGridSizeField->setToolTip(tr("Enter width for primary grid size"));
            theContentPane->layout()->addWidget(panel3);

            //setup side track width
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            JLabel* secondaryGridSizeLabel = new JLabel(tr("Secondary Grid Size:"));
            panel2->layout()->addWidget(secondaryGridSizeLabel);
            secondaryGridSizeLabel->setLabelFor(secondaryGridSizeField);
            panel2->layout()->addWidget(secondaryGridSizeField);
            secondaryGridSizeField->setName("SecondaryGridSize");
            secondaryGridSizeField->setToolTip(tr("Enter width for secondary grid size"));
            theContentPane->layout()->addWidget(panel2);

            //set up Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            panel5->layout()->addWidget(gridSizesDone = new QPushButton(tr("Done")));
            //gridSizesDone.addActionListener(this::gridSizesDonePressed);
            connect(gridSizesDone, &QPushButton::clicked, [=]{
             gridSizesDonePressed();
            });
            gridSizesDone->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));

            //Cancel
            panel5->layout()->addWidget(gridSizesCancel = new QPushButton(tr("Cancel")));
            //gridSizesCancel.addActionListener(this::gridSizesCancelPressed);
            connect(gridSizesCancel, &QPushButton::clicked, [=]{
             gridSizesCancelPressed();
            });
            gridSizesCancel->setToolTip(tr("CancelHint").arg(tr("Cancel")));
            theContentPane->layout()->addWidget(panel5);

            //make this button the default button (return or enter activates)
//            JRootPane* rootPane = SwingUtilities.getRootPane(gridSizesDone);
//            rootPane.setDefaultButton(gridSizesDone);
            gridSizesDone->setDefault(true);
        }

        //Set up for Entry of Track Widths
        primaryGridSizeField->setText(QString::number(layoutEditor->gContext->getGridSize()));
        secondaryGridSizeField->setText(QString::number(layoutEditor->gContext->getGridSize2nd()));
        //        enterGridSizesFrame.addWindowListener(new WindowAdapter() {
        //            @Override
        //            /*public*/ void windowClosing(WindowEvent event) {
        //                gridSizesCancelPressed(null);
        //            }
        //        });
        enterGridSizesFrame->addWindowListener(new EGSD_WindowListener(this));
        enterGridSizesFrame->pack();
        enterGridSizesFrame->setVisible(true);
        gridSizesChange = false;
        enterGridSizesOpen = true;
    }

    /*private*/ void EnterGridSizesDialog::gridSizesDonePressed(/*@Nonnull ActionEvent event*/) {
        QString newGridSize = "";
        float siz = 0.0F;

        //get secondary grid size
        newGridSize = secondaryGridSizeField->text().trimmed();
        bool ok;
            siz = newGridSize.toFloat(&ok);
        if(!ok) {
            showEntryErrorDialog(enterGridSizesFrame, NumberFormatException());
            return;
        }

        if ((siz < 5.0) || (siz > 100.0)) {
            JOptionPane::showMessageDialog(enterGridSizesFrame,
                    tr("Error - Entered value \"%1\" is not in the allowed range.").arg(siz),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);

            return;
        }

        if (!MathUtil::equals(layoutEditor->gContext->getGridSize2nd(), siz)) {
            layoutEditor->gContext->setGridSize2nd((int) siz);
            gridSizesChange = true;
        }

        //get mainline track width
        newGridSize = primaryGridSizeField->text().trimmed();

            siz = newGridSize.toFloat(&ok);
        if(!ok) {
            showEntryErrorDialog(enterGridSizesFrame, NumberFormatException());
            return;
        }

        if ((siz < 5) || (siz > 100.0)) {
            JOptionPane::showMessageDialog(enterGridSizesFrame,
                    tr("Error - Entered value \"%1\" is not in the allowed range.").arg(siz),
                    tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
        } else {
            if (!MathUtil::equals(layoutEditor->gContext->getGridSize(), siz)) {
                layoutEditor->gContext->setGridSize((int) siz);
                gridSizesChange = true;
            }
            gridSizesCancelPressed();
        }
    }

    /*private*/ void EnterGridSizesDialog::gridSizesCancelPressed(/*ActionEvent event*/) {
        enterGridSizesOpen = false;
        enterGridSizesFrame->setVisible(false);
        enterGridSizesFrame->dispose();
        enterGridSizesFrame = nullptr;

        if (gridSizesChange) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
        }
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
    /*private*/ void EnterGridSizesDialog::showEntryErrorDialog(QWidget* parentComponent, NumberFormatException e) {
        JOptionPane::showMessageDialog(parentComponent,
                tr("%1: %2 %3").arg(tr("Error in entry")).arg(
                        e.getMessage()).arg(tr("Please reenter or Cancel.")),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);
    }

//    /*private*/ final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(
//            EnterGridSizesDialog.class);
