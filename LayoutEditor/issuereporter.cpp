#include "issuereporter.h"
#include "loggerfactory.h"
#include <QScrollArea>

/**
 * User interface for generating an issue report on the JMRI GitHub project.
 * To allow international support, only the UI is localized.
 * The user is requested to supply the report contents in English.
 *
 * @author Randall Wood Copyright 2020
 */
//@API(status = API.Status.INTERNAL)
// /*public*/ class IssueReporter extends JFrame implements ClipboardOwner, DocumentListener {

    /*private*/ /*static*/ /*final*/ const int IssueReporter::BUG = 0; // index in type combo box
    /*private*/ /*static*/ /*final*/ const int IssueReporter::RFE = 1; // index in type combo box

    /*private*/ /*static*/ Logger* IssueReporter::log = LoggerFactory::getLogger("IssueReporter");

    /**
     * Creates new form IssueReporterUI
     */
    /*public*/ IssueReporter::IssueReporter(QWidget *parent) : JFrame(parent) {
        initComponents();
    }

    /*private*/ void IssueReporter::initComponents() {

        titleText = new JTextField();
        bodyTA = new JTextArea();
        submitBtn = new JToggleButton();
        typeCB = new JComboBox();
        repoCB = new JComboBox();
        typeOptionsPanel = new JPanel();
        bugReportPanel = new JPanel();
        descriptionLabel = new JLabel();
        instructionsLabel = new JLabel();
        JLabel* titleLabel = new JLabel();
        QScrollArea* bodySP = new QScrollArea();
        JLabel* typeLabel = new JLabel();
        JLabel* repoLabel = new JLabel();
        profileCB = new JCheckBox();
        sysInfoCB = new JCheckBox();
        logsCB = new JCheckBox();

        setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
        setTitle(tr("Report Issue...", ""));
        resize(QSize(400, 600));

        //QFont f = titleLabel->getFont();
        //titleLabel->setFont(titleLabel.getFont().deriveFont(titleLabel.getFont().getStyle()));
        titleLabel->setText(tr("Title:"));

        bodyTA->setColumns(20);
        bodyTA->setLineWrap(true);
        bodyTA->setRows(5);
        bodyTA->setWrapStyleWord(true);
        //bodySP.setViewportView(bodyTA);
        bodySP->setWidget(bodyTA);

        submitBtn->setText(tr("Submit to GitHub"));
        submitBtn->setEnabled(false);
//        submitBtn->addActionListener(this->submitBtnActionListener);

//        descriptionLabel.setFont(descriptionLabel.getFont().deriveFont(descriptionLabel.getFont().getStyle() | java.awt.Font.BOLD));
        descriptionLabel->setText(tr("Steps to Reproduce"));

        instructionsLabel->setText(tr("<html>Share the steps needed to reliably reproduce the problem. Please include actual and expected results. We support GitHub-flavored Markdown. You will be able to edit your issue and add screenshots when you preview it on GitHub.</html>"));

//        typeLabel.setFont(typeLabel.getFont().deriveFont(typeLabel.getFont().getStyle()));
        typeLabel->setText(tr("This is a:"));

//        typeCB.setModel(new DefaultComboBoxModel<>(new String[]{tr("Bug Report"), tr("Feature Request")}));
//        typeCB->addActionListener(this->typeCBActionListener);

//        repoLabel.setFont(repoLabel.getFont().deriveFont(repoLabel.getFont().getStyle()));
        repoLabel->setText(tr("Report on:"));

//        repoCB->setModel(new GitHubRepositoryComboBoxModel());
//        repoCB->setRenderer(new GitHubRepositoryListCellRenderer());

        profileCB->setText(tr("Include my configuration"));

        sysInfoCB->setText(tr("Include my system information"));

        logsCB->setText(tr("Include my logs"));
#if 0
        titleText.getDocument()->addDocumentListener(this);

        bodyTA->getDocument().addDocumentListener(this);

        GroupLayout bugReportPanelLayout = new GroupLayout(bugReportPanel);
        bugReportPanel.setLayout(bugReportPanelLayout);
        bugReportPanelLayout.setHorizontalGroup(
                bugReportPanelLayout.createParallelGroup(Alignment.LEADING)
                        .addGroup(bugReportPanelLayout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(bugReportPanelLayout.createParallelGroup(Alignment.LEADING)
                                        .addComponent(sysInfoCB)
                                        .addComponent(logsCB)
                                        .addComponent(profileCB))
                                .addContainerGap(DEFAULT_SIZE, Short.MAX_VALUE))
        );
        bugReportPanelLayout.setVerticalGroup(
                bugReportPanelLayout.createParallelGroup(Alignment.LEADING)
                        .addGroup(bugReportPanelLayout.createSequentialGroup()
                                .addContainerGap()
                                .addComponent(sysInfoCB)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(logsCB)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(profileCB)
                                .addContainerGap(DEFAULT_SIZE, Short.MAX_VALUE))
        );

        GroupLayout typeOptionsPanelLayout = new GroupLayout(typeOptionsPanel);
        typeOptionsPanel.setLayout(typeOptionsPanelLayout);
        typeOptionsPanelLayout.setHorizontalGroup(
                typeOptionsPanelLayout.createParallelGroup(Alignment.LEADING)
                        .addComponent(bugReportPanel, Alignment.TRAILING, DEFAULT_SIZE, DEFAULT_SIZE, Short.MAX_VALUE)
        );
        typeOptionsPanelLayout.setVerticalGroup(
                typeOptionsPanelLayout.createParallelGroup(Alignment.LEADING)
                        .addComponent(bugReportPanel, PREFERRED_SIZE, DEFAULT_SIZE, PREFERRED_SIZE)
        );

        GroupLayout layout = new GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(Alignment.LEADING)
                                        .addComponent(bodySP, DEFAULT_SIZE, 376, Short.MAX_VALUE)
                                        .addComponent(instructionsLabel, DEFAULT_SIZE, DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(descriptionLabel, DEFAULT_SIZE, DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addGroup(Alignment.TRAILING, layout.createSequentialGroup()
                                                .addGap(0, 0, Short.MAX_VALUE)
                                                .addComponent(submitBtn))
                                        .addGroup(layout.createSequentialGroup()
                                                .addGroup(layout.createParallelGroup(Alignment.LEADING, false)
                                                        .addComponent(typeLabel, PREFERRED_SIZE, 70, Short.MAX_VALUE)
                                                        .addComponent(repoLabel, PREFERRED_SIZE, 70, Short.MAX_VALUE)
                                                        .addComponent(titleLabel, DEFAULT_SIZE, DEFAULT_SIZE, Short.MAX_VALUE))
                                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(layout.createParallelGroup(Alignment.LEADING)
                                                        .addComponent(typeCB, 0, DEFAULT_SIZE, Short.MAX_VALUE)
                                                        .addComponent(repoCB, 0, DEFAULT_SIZE, Short.MAX_VALUE)
                                                        .addComponent(titleText)))
                                        .addComponent(typeOptionsPanel, Alignment.TRAILING, DEFAULT_SIZE, DEFAULT_SIZE, Short.MAX_VALUE))
                                .addContainerGap())
        );

        layout.linkSize(SwingConstants.HORIZONTAL, titleLabel, typeLabel, repoLabel);

        layout.setVerticalGroup(
                layout.createParallelGroup(Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(Alignment.BASELINE)
                                        .addComponent(typeCB, PREFERRED_SIZE, DEFAULT_SIZE, PREFERRED_SIZE)
                                        .addComponent(typeLabel))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(Alignment.BASELINE)
                                        .addComponent(repoCB, PREFERRED_SIZE, DEFAULT_SIZE, PREFERRED_SIZE)
                                        .addComponent(repoLabel))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(Alignment.BASELINE)
                                        .addComponent(titleLabel)
                                        .addComponent(titleText, PREFERRED_SIZE, DEFAULT_SIZE, PREFERRED_SIZE))
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(descriptionLabel)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(instructionsLabel)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(bodySP, DEFAULT_SIZE, 109, Short.MAX_VALUE)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(typeOptionsPanel, PREFERRED_SIZE, DEFAULT_SIZE, PREFERRED_SIZE)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(submitBtn)
                                .addContainerGap())
        );
#endif
        pack();
    }

    //@Override
    /*public*/ void IssueReporter::insertUpdate(DocumentEvent* e) {
        changedUpdate(e);
    }

    //@Override
    /*public*/ void IssueReporter::removeUpdate(DocumentEvent* e) {
        changedUpdate(e);
    }

    //@Override
    /*public*/ void IssueReporter::changedUpdate(DocumentEvent* /*e*/) {
        submitBtn->setEnabled(!bodyTA->getText().isEmpty() && !titleText->text().isEmpty());
    }

    /*private*/ void IssueReporter::typeCBActionListener(JActionEvent* /*e*/) {
        switch (typeCB->getSelectedIndex()) {
            case BUG:
                descriptionLabel->setText(tr("IssueReporter.descriptionLabel.bug"));
                instructionsLabel->setText(tr("IssueReporter.instructionsLabel.bug"));
                if (typeOptionsPanel != (bugReportPanel->parent())) {
                    typeOptionsPanel->layout()->addWidget(bugReportPanel);
                    typeOptionsPanel->resize(bugReportPanel->sizeHint());
                    bugReportPanel->update();
                    bugReportPanel->repaint();
                }
                break;
            case RFE:
                descriptionLabel->setText(tr("Description"));
                instructionsLabel->setText(tr("<html>Please describe the feature you would like to see. We support GitHub-flavored Markdown. You will be able to edit your issue and add screenshots when you preview it on GitHub. Please provide a description in plain English to allow other users to assist you. Don't forget to confirm your report by clicking the [Submit new issue] button on GitHub.</html>"));
                typeOptionsPanel->layout()->removeWidget(bugReportPanel);
                break;
            default:
                log->error(tr("Unexpected selected index %1 for issue type").arg(typeCB->currentIndex()),  IllegalArgumentException());
        }
    }

    /*private*/ void IssueReporter::submitBtnActionListener(JActionEvent* e) {
#if 0
        IssueReport report = null;
        switch (typeCB.getSelectedIndex()) {
            case BUG:
                report = new BugReport(titleText.getText(), bodyTA.getText(), profileCB.isSelected(), sysInfoCB.isSelected(), logsCB.isSelected());
                break;
            case RFE:
                report = new EnhancementRequest(titleText.getText(), bodyTA.getText());
                break;
            default:
                log.error("Unexpected selected index {} for issue type", typeCB.getSelectedIndex(), new IllegalArgumentException());
        }
        if (report != null) {
            submitReport(report);
        }
#endif
    }

    // package private
    /*private*/ void IssueReporter::submitReport(IssueReport* report) {
#if 0
        try {
            URI uri = report.submit(repoCB.getItemAt(repoCB.getSelectedIndex()));
            List<File> attachments = report.getAttachments();
            if (!attachments.isEmpty()) {
                JOptionPane.showMessageDialog(this,
                        tr("IssueReporter.attachments.message"),
                        tr("IssueReporter.attachments.title"),
                        JOptionPane.INFORMATION_MESSAGE);
                Desktop.getDesktop().open(attachments.get(0).getParentFile());
            }
            if ( Desktop.getDesktop().isSupported( Desktop.Action.BROWSE) ) {
                // Open browser to URL with draft report
                Desktop.getDesktop().browse(uri);
                this.dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING)); // close report window
            } else {
                // Can't open browser, ask the user to instead
                Object[] options = {tr("IssueReporter.browser.copy"), tr("IssueReporter.browser.skip")};
                int choice = JOptionPane.showOptionDialog(this,
                    tr("IssueReporter.browser.message"), // message
                    tr("IssueReporter.browser.title"), // window title
                    JOptionPane.YES_NO_OPTION,
                    JOptionPane.INFORMATION_MESSAGE,
                    null, // icon
                    options,
                    tr("IssueReporter.browser.copy")
                );

                if (choice == 0 ) {
                    Toolkit.getDefaultToolkit()
                        .getSystemClipboard()
                        .setContents(
                            new StringSelection(uri.toString()),
                            null
                        );
                    this.dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING)); // close report window
                }
            }

        } catch (IOException | URISyntaxException ex) {
            log.error("Unable to report issue", ex);
            JOptionPane.showMessageDialog(this,
                    tr("IssueReporter.error.message", ex.getLocalizedMessage()),
                    tr("IssueReporter.error.title"),
                    JOptionPane.ERROR_MESSAGE);
        } catch (IssueReport414Exception ex) {
            BodyTransferable bt = new BodyTransferable(report.getBody());
            Toolkit.getDefaultToolkit().getSystemClipboard().setContents(bt, this);
            JOptionPane.showMessageDialog(this,
                    tr("IssueReporter.414.message"),
                    tr("IssueReporter.414.title"),
                    JOptionPane.INFORMATION_MESSAGE);
            submitReport(report);
        }
#endif
    }
#if 0
    //@Override
    /*public*/ void lostOwnership(Clipboard clipboard, Transferable contents
    ) {
        // ignore -- merely means something else was put on clipboard
    }

    private static class GitHubRepositoryComboBoxModel extends DefaultComboBoxModel<GitHubRepository> {

        /*public*/ GitHubRepositoryComboBoxModel() {
            super();
            ServiceLoader<GitHubRepository> loader = ServiceLoader.load(GitHubRepository.class);
            Set<GitHubRepository> set = new TreeSet<>();
            loader.forEach(set::add);
            loader.reload();
            set.forEach(r -> {
                addElement(r);
                if (r.getTitle().equals(Application.getApplicationName())) {
                    setSelectedItem(r);
                }
            });
        }

    }

    private static class GitHubRepositoryListCellRenderer extends DefaultListCellRenderer {

        @Override
        /*public*/ Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
            return super.getListCellRendererComponent(list,
                    (value instanceof GitHubRepository) ? ((GitHubRepository) value).getTitle() : value,
                    index,
                    isSelected,
                    cellHasFocus);
        }
    }

    /*public*/ static class FileTransferable implements Transferable {

        private final List<File> files;

        /*public*/ FileTransferable(@Nonnull List<File> files) {
            this.files = files;
        }

        @Override
        /*public*/ DataFlavor[] getTransferDataFlavors() {
            return new DataFlavor[]{DataFlavor.javaFileListFlavor};
        }

        @Override
        /*public*/ boolean isDataFlavorSupported(DataFlavor flavor) {
            return DataFlavor.javaFileListFlavor.equals(flavor);
        }

        @Override
        @Nonnull
        /*public*/ Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
            return files;
        }

    }

    /*public*/ static class BodyTransferable implements Transferable {

        private final String body;

        /*public*/ BodyTransferable(@Nonnull String body) {
            this.body = body;
        }

        @Override
        /*public*/ DataFlavor[] getTransferDataFlavors() {
            return new DataFlavor[]{DataFlavor.stringFlavor};
        }

        @Override
        /*public*/ boolean isDataFlavorSupported(DataFlavor flavor) {
            return DataFlavor.stringFlavor.equals(flavor);
        }

        //@Override
        //@Nonnull
        /*public*/ Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
            return body;
        }

    }
#endif
