#include "enterreporterdialog.h"
#include "layouteditor.h"
#include "jbutton.h"
#include "jtextfield.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "jpanel.h"
#include "jrootpane.h"

/**
 * Layout Editor Dialogs implements some dialogs for the Layout Editor
 *
 * @author George Warner Copyright (c) 2019
 */
// /*public*/ class EnterReporterDialog {


// constructor method
/*public*/ EnterReporterDialog::EnterReporterDialog(/*@Nonnull*/ LayoutEditor* thePanel, QObject *parent)
 : QObject(parent)
{
 enterReporterFrame = nullptr;
 reporterOpen = false;
 xPositionField = new JTextField(6);
 yPositionField = new JTextField(6);
 reporterNameField = new JTextField(6);

 layoutEditor = thePanel;
}

class MyWindowListener : public WindowListener
{
 EnterReporterDialog* dlg;
public:
 MyWindowListener(EnterReporterDialog* dlg) {this->dlg = dlg;}
 void windowClosing(QCloseEvent*)
 {
  dlg->reporterCancelPressed();
 }
};

//display dialog for entering Reporters
//@InvokeOnGuiThread
/*public*/ void EnterReporterDialog::enterReporter(int defaultX, int defaultY) {
    if (reporterOpen) {
        enterReporterFrame->setVisible(true);
        return;
    }

    //Initialize if needed
    if (enterReporterFrame == nullptr) {
        enterReporterFrame = new JmriJFrameX(tr("Add Reporter Label"));

//enterReporterFrame.addHelpMenu("package.jmri.jmrit.display.AddReporterLabel", true);
        enterReporterFrame->setLocation(70, 30);
        QWidget* theContentPane = enterReporterFrame->getContentPane();
        theContentPane->setLayout(new QVBoxLayout());//theContentPane, BoxLayout.PAGE_AXIS));

        //setup reporter entry
        JPanel* panel2 = new JPanel();
        panel2->setLayout(new FlowLayout());
        JLabel* reporterLabel = new JLabel(tr("Reporter Name:"));
        panel2->layout()->addWidget(reporterLabel);
        reporterLabel->setLabelFor(reporterNameField);
        panel2->layout()->addWidget(reporterNameField);
        reporterNameField->setToolTip(tr("Enter name of Reporter (system name or user name)."));
        theContentPane->layout()->addWidget(panel2);

        //setup coordinates entry
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new FlowLayout());

        JLabel* xCoordLabel = new JLabel(tr("Location: x"));
        panel3->layout()->addWidget(xCoordLabel);
        xCoordLabel->setLabelFor(xPositionField);
        panel3->layout()->addWidget(xPositionField);
        xPositionField->setToolTip(tr("Enter horizontal coordinate of upper left corner."));

        JLabel* yCoordLabel = new JLabel(tr(", y"));
        panel3->layout()->addWidget(yCoordLabel);
        yCoordLabel->setLabelFor(yPositionField);
        panel3->layout()->addWidget(yPositionField);
        yPositionField->setToolTip(tr("Enter vertical coordinate of upper left corner."));

        theContentPane->layout()->addWidget(panel3);

        //set up Add and Cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        panel5->layout()->addWidget(reporterDone = new JButton(tr("Add New Label")));
//        reporterDone.addActionListener((ActionEvent event) -> {
//            reporterDonePressed(event);
//        });
        connect(reporterDone, SIGNAL(clicked(bool)), this, SLOT(reporterDonePressed()));
        reporterDone->setToolTip(tr("Select to add new Reporter Icon as specified above."));

        //Cancel
        panel5->layout()->addWidget(reporterCancel = new JButton(tr("Cancel")));
//        reporterCancel.addActionListener((ActionEvent event) -> {
//            reporterCancelPressed();
//        });
        connect(reporterCancel, SIGNAL(clicked(bool)), this, SLOT(reporterCancelPressed()));
        reporterCancel->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));
        theContentPane->layout()->addWidget(panel5);

        //make this button the default button (return or enter activates)
//        JRootPane* rootPane = SwingUtilities.getRootPane(reporterDone);
//        rootPane->setDefaultButton(reporterDone);
        reporterDone->setDefault(true);
    }

    //Set up for Entry of Reporter Icon
    xPositionField->setText(QString::number(defaultX));
    yPositionField->setText(QString::number(defaultY));
//    enterReporterFrame.addWindowListener(new WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(WindowEvent event) {
//            reporterCancelPressed();
//        }
//    });
    enterReporterFrame->addWindowListener(new MyWindowListener(this));
    enterReporterFrame->pack();
    enterReporterFrame->setVisible(true);
    reporterOpen = true;
}

/*private*/ void EnterReporterDialog::reporterDonePressed(/*@Nonnull*/ /*ActionEvent event*/) {
    //get x coordinate
    QString newX = "";
    int xx = 0;

    newX = xPositionField->text().trimmed();
    bool ok;
        xx = newX.toInt(&ok);
    if(!ok) {
        showEntryErrorDialog(enterReporterFrame, NumberFormatException("invalid number"));
        return;
    }

    if ((xx <= 0) || (xx > layoutEditor->getLayoutWidth())) {
        log->error("invalid x: " + QString::number(xx) + ", LayoutWidth: " + QString::number(layoutEditor->getLayoutWidth()));
        JOptionPane::showMessageDialog(enterReporterFrame,
                tr("Error - Entered value \"%1\" is not in the allowed range.").arg(
                        tr(" %%1 ").arg(xx)),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    // get y coordinate
    QString newY = "";
    int yy = 0;
    newY = yPositionField->text().trimmed();

        yy = newY.toInt(&ok);
    if(!ok) {
        showEntryErrorDialog(enterReporterFrame, NumberFormatException("invalid number"));
        return;
    }

    if ((yy <= 0) || (yy > layoutEditor->getLayoutHeight())) {
        log->error("invalid y: " + QString::number(yy) + ", LayoutWidth: " + QString::number(layoutEditor->getLayoutHeight()));
        JOptionPane::showMessageDialog(enterReporterFrame,
                tr("Error - Entered value \"%1\" is not in the allowed range.").arg(
                        tr(" %%1 ").arg(xx)),
                tr("Error"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    // get reporter name
    Reporter* reporter = nullptr;
    QString rName = reporterNameField->text();

    if (InstanceManager::getNullableDefault("ReporterManager") != nullptr) {
        try {
            reporter =
              ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->provideReporter(rName);
        } catch (IllegalArgumentException e) {
            JOptionPane::showMessageDialog(enterReporterFrame,
                    tr("Error - Could not provide Reporter \"%1\". Cannot add Reporter Icon.").arg(rName), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
    } else {
        JOptionPane::showMessageDialog(enterReporterFrame,
                tr("Error - Reporter manager not available. Cannot add Reporter Icon."), tr("Error"),
                JOptionPane::ERROR_MESSAGE);

        return;
    }

    //add the reporter icon
    layoutEditor->addReporter(reporter, xx, yy);

    reporterCancelPressed();
}

/*private*/ void EnterReporterDialog::reporterCancelPressed() {
    reporterOpen = false;
    enterReporterFrame->setVisible(false);
    enterReporterFrame->dispose();
    enterReporterFrame = nullptr;
    layoutEditor->redrawPanel();
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
/*private*/ void EnterReporterDialog::showEntryErrorDialog(QWidget *parentComponent, NumberFormatException e) {
    JOptionPane::showMessageDialog(parentComponent,
            tr("%1: %2 %3").arg(tr("Error in entry").arg(
                    e.toString()).arg(tr("Please reenter or Cancel."))),
            tr("Error"),
            JOptionPane::ERROR_MESSAGE);
}

/*private*/ /*final*/ /*static*/ Logger* EnterReporterDialog::log = LoggerFactory::getLogger("EnterReporterDialog");
