#include "scaletrackdiagramdialog.h"
#include "layouteditor.h"
#include "loggerfactory.h"
#include "joptionpane.h"

/**
 * Layout Editor Dialogs implements some dialogs for the Layout Editor
 *
 * @author George Warner Copyright (c) 2019
 */
///*public*/ class ScaleTrackDiagramDialog {


// constructor method
/*public*/ ScaleTrackDiagramDialog::ScaleTrackDiagramDialog(/*@Nonnull*/ LayoutEditor* thePanel) {
    layoutEditor = thePanel;
}
class MyWindowListener : public WindowListener
{
 ScaleTrackDiagramDialog* stdd;
public:
 MyWindowListener(ScaleTrackDiagramDialog* stdd) {this->stdd = stdd;}
 void windowClosing(QCloseEvent *)
 {
  stdd->scaleTrackDiagramCancelPressed();
 }
};
/*===============================*\
|*  Dialog box to enter scale /  *|
|*  translate track diagram info *|
\*===============================*/

//display dialog for scaling the track diagram
//@InvokeOnGuiThread
/*public*/ void ScaleTrackDiagramDialog::scaleTrackDiagram() {
    if (scaleTrackDiagramOpen) {
        scaleTrackDiagramFrame->setVisible(true);
        return;
    }

    // Initialize if needed
    if (scaleTrackDiagramFrame == nullptr) {
        scaleTrackDiagramFrame = new JmriJFrameX(tr("Scale/Translate Track Diagram"));
        scaleTrackDiagramFrame->addHelpMenu("package.jmri.jmrit.display.ScaleTrackDiagram", true);
        scaleTrackDiagramFrame->setLocation(70, 30);
        QWidget* theContentPane = scaleTrackDiagramFrame->getContentPane();
        QVBoxLayout* theContentPaneLayout;
        theContentPane->setLayout(theContentPaneLayout = new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

        // setup x translate
        JPanel* panel31 = new JPanel();
        panel31->setLayout(new FlowLayout());
        JLabel* xTranslateLabel = new JLabel(tr("Horizontal (x) Translation:"));
        panel31->layout()->addWidget(xTranslateLabel);
        xTranslateLabel->setLabelFor(xTranslateField);
        panel31->layout()->addWidget(xTranslateField);
        xTranslateField->setToolTip(tr("Enter units to move (0 = don't move; negative = move left; positive = move right)."));
        theContentPaneLayout->addWidget(panel31);

        //setup y translate
        JPanel* panel32 = new JPanel();
        panel32->setLayout(new FlowLayout());
        JLabel* yTranslateLabel = new JLabel(tr("Vertical (y) Translation:"));
        panel32->layout()->addWidget(yTranslateLabel);
        yTranslateLabel->setLabelFor(yTranslateField);
        panel32->layout()->addWidget(yTranslateField);
        yTranslateField->setToolTip(tr("Enter units to move (0 = don't move; negative = move up; positive = move down)."));
        theContentPaneLayout->addWidget(panel32);

        //setup information message 1
        JPanel* panel33 = new JPanel();
        panel33->setLayout(new FlowLayout());
        JLabel* message1Label = new JLabel(tr("Note: Translation occurs before scaling."));
        panel33->layout()->addWidget(message1Label);
        theContentPaneLayout->addWidget(panel33);

        //setup x factor
        JPanel* panel21 = new JPanel();
        panel21->setLayout(new FlowLayout());
        JLabel* xFactorLabel = new JLabel(tr("Horizontal (x) Scale Factor:"));
        panel21->layout()->addWidget(xFactorLabel);
        xFactorLabel->setLabelFor(xFactorField);
        panel21->layout()->addWidget(xFactorField);
        xFactorField->setToolTip(tr("Enter factor for expanding (greater than 1.0) or contracting (less than 1.0)."));
        theContentPaneLayout->addWidget(panel21);

        //setup y factor
        JPanel* panel22 = new JPanel();
        panel22->setLayout(new FlowLayout());
        JLabel* yFactorLabel = new JLabel(tr("YFactorLabel"));
        panel22->layout()->addWidget(yFactorLabel);
        yFactorLabel->setLabelFor(yFactorField);
        panel22->layout()->addWidget(yFactorField);
        yFactorField->setToolTip(tr("Enter factor for expanding (greater than 1.0) or contracting (less than 1.0)."));
        theContentPaneLayout->addWidget(panel22);

        //setup information message 2
        JPanel* panel23 = new JPanel();
        panel23->setLayout(new FlowLayout());
        JLabel* message2Label = new JLabel(tr("Warning: Scaling and translation cannot be undone."));
        panel23->layout()->addWidget(message2Label);
        theContentPaneLayout->addWidget(panel23);

        //set up Done and Cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        panel5->layout()->addWidget(scaleTrackDiagramDone = new QPushButton(tr("Scale/Translate")));
        //scaleTrackDiagramDone.addActionListener((ActionEvent event) -> {
        connect(scaleTrackDiagramDone, &QPushButton::clicked, [=]{
            scaleTrackDiagramDonePressed(/*event*/);
        });
        scaleTrackDiagramDone->setToolTip(tr("Click here to translate and/or scale the track diagram."));

        panel5->layout()->addWidget(scaleTrackDiagramCancel = new QPushButton(tr("Cancel")));
        //scaleTrackDiagramCancel.addActionListener((ActionEvent event) -> {
        connect(scaleTrackDiagramCancel, &QPushButton::clicked, [=]{
            scaleTrackDiagramCancelPressed(/*event*/);
        });
        scaleTrackDiagramCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPaneLayout->addWidget(panel5);
#if 0
        //make this button the default button (return or enter activates)
        JRootPane rootPane = SwingUtilities.getRootPane(scaleTrackDiagramDone);
        rootPane.setDefaultButton(scaleTrackDiagramDone);
#else
        scaleTrackDiagramDone->setDefault(true);
#endif
    }

    // Set up for Entry of Scale and Translation
    xFactorField->setText("1.0");
    yFactorField->setText("1.0");
    xTranslateField->setText("0");
    yTranslateField->setText("0");
#if 0
    scaleTrackDiagramFrame.addWindowListener(new WindowAdapter() {
        @Override
        /*public*/ void windowClosing(WindowEvent event) {
            scaleTrackDiagramCancelPressed(null);
        }
    });
#else
    scaleTrackDiagramFrame->addWindowListener(new MyWindowListener(this));
#endif
    scaleTrackDiagramFrame->pack();
    scaleTrackDiagramFrame->setVisible(true);
    scaleTrackDiagramOpen = true;
}

/*private*/ void ScaleTrackDiagramDialog::scaleTrackDiagramDonePressed(/*@Nonnull ActionEvent event*/) {
    bool changeFlag = false;
    bool translateError = false;
    float xTranslation, yTranslation, xFactor, yFactor;

    // get x translation
    QString newText = xTranslateField->text().trimmed();
    bool bok;
        xTranslation = newText.toFloat(&bok);
    if(!bok) {
     NumberFormatException e("x not valid floating point");
        showEntryErrorDialog(scaleTrackDiagramFrame, &e);
        return;
    }

    // get y translation
    newText = yTranslateField->text().trimmed();

        yTranslation = newText.toFloat(&bok);
    if(!bok) {
     NumberFormatException e("y not valid floating point");
        showEntryErrorDialog(scaleTrackDiagramFrame, &e);
        return;
    }

    // get x factor
    newText = xFactorField->text().trimmed();

        xFactor = newText.toFloat(&bok);
     if(!bok) {
         NumberFormatException e("x factor not valid floating point");
        showEntryErrorDialog(scaleTrackDiagramFrame, &e);
        return;
    }

    // get y factor
    newText = yFactorField->text().trimmed();

        yFactor =newText.toFloat(&bok);
        if(!bok) {
         NumberFormatException e("y factor not valid floating point");
        showEntryErrorDialog(scaleTrackDiagramFrame, &e);
        return;
    }

    // here when all numbers read in successfully - check for translation
    if ((xTranslation != 0.0F) || (yTranslation != 0.0F)) {
        //apply translation
        if (layoutEditor->translateTrack(xTranslation, yTranslation)) {
            changeFlag = true;
        } else {
            log->error("Error translating track diagram");
            translateError = true;
        }
    }

    if (!translateError && ((xFactor != 1.0) || (yFactor != 1.0))) {
        //apply scale change
        if (layoutEditor->scaleTrack(xFactor, yFactor)) {
            changeFlag = true;
        } else {
            log->error("Error scaling track diagram");
        }
    }
    layoutEditor->clearSelectionGroups();

    scaleTrackDiagramCancelPressed();

    if (changeFlag) {
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*private*/ void ScaleTrackDiagramDialog::scaleTrackDiagramCancelPressed(/*ActionEvent event*/) {
    scaleTrackDiagramOpen = false;
    scaleTrackDiagramFrame->setVisible(false);
    scaleTrackDiagramFrame->dispose();
    scaleTrackDiagramFrame = nullptr;
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
/*private*/ void ScaleTrackDiagramDialog::showEntryErrorDialog(QWidget* parentComponent, NumberFormatException* e) {
    JOptionPane::showMessageDialog(parentComponent,
            QString("%1: %2 %3").arg(tr("Error in entry")).arg(
                    e->getMessage()).arg(tr("Please reenter or Cancel.")),
            tr("ErrorTitle"),
            JOptionPane::ERROR_MESSAGE);
}

/*private*/ /*final*/ /*static*/ Logger* ScaleTrackDiagramDialog::log = LoggerFactory::getLogger("ScaleTrackDiagramDialog");

