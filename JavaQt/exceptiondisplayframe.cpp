#include "exceptiondisplayframe.h"
#include "borderfactory.h"

/**
 * Dialog to display the details of an Exception. The Exception and additional
 * details about what was happening when the exception occurred are passed in
 * using an ExceptionContext object.
 * <p>
 * This is a preliminary version that is incomplete, but works. Copy to the
 * clipboard needs to be added.
 *
 * @author Gregory Madsen Copyright (C) 2012
 *
 */
// /*public*/  class ExceptionDisplayFrame extends JDialog {


    // This needs MAJOR clean-up to better organize the controls and their
    // hierarchy.


    /**
     * Create the frame.
     *
     * @param context the ExceptionContext
     * @param owner   the associated window, or none if null
     *
     */
    /*public*/  ExceptionDisplayFrame::ExceptionDisplayFrame(ExceptionContext* context, /*@CheckForNull*/ QWidget* owner)
     : JDialog(owner, context->getTitle(), ModalityType::DOCUMENT_MODAL)
    {
        //super(owner, context.getTitle(), ModalityType.DOCUMENT_MODAL);
        //Objects.requireNonNull(context, "ExceptinContext argument passed to ErrorDisplayFrame constructor cannot be null."); // NOI18N
        if(!context)
         throw new NullPointerException("ExceptinContext argument passed to ErrorDisplayFrame constructor cannot be null.");
        this->context = context;

        initComponents();
    }

    /**
     * Constructor that takes just an Exception and defaults everything else.
     *
     * @param ex    the Exception
     * @param owner the associated window, or none if null
     *
     */
    /*public*/  ExceptionDisplayFrame::ExceptionDisplayFrame(Exception* ex, /*@CheckForNull*/ QWidget* owner) {
//        this(new ExceptionContext(ex,
//             Bundle.getMessage("ExceptionDisplayDefaultOperation"),
//             Bundle.getMessage("ExceptionDisplayDefaultHint")), owner);
     this->context = new ExceptionContext(ex, tr("Operation unavailable"), tr("Hint unavailable"), owner);
    }

    /*private*/  void ExceptionDisplayFrame::initComponents() {
        contentPane = new JPanel();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
        contentPane->setBorder(new EmptyBorder(5, 5, 5, 5));

        setContentPane(contentPane);

        lblNewLabel_1 = new JLabel(tr("This is a prototype dialog for displaying details about exceptions that are thrown during program execution. It still needs a lot of work!"));
        lblNewLabel_1->setAlignmentX(/*Component.CENTER_ALIGNMENT*/Qt::AlignHCenter);

        contentPane->layout()->addWidget(lblNewLabel_1);

        summaryPanel = new JPanel();
        contentPane->layout()->addWidget(summaryPanel);

        lblNewLabel_3 = new JLabel(tr("Summary:"));
        summaryPanel->layout()->addWidget(lblNewLabel_3);

        summaryTextArea2 = new JTextArea();
        summaryPanel->layout()->addWidget(summaryTextArea2);

        showDetailsButton = new JButton(tr("Show details"));
//        showDetailsButton.setAlignmentX(Component.CENTER_ALIGNMENT);
//        showDetailsButton.addActionListener((ActionEvent arg0) -> {
        connect(showDetailsButton, &JButton::clicked, [=]{
            detailsPanel->setVisible(true);
            pack();
        });
        contentPane->layout()->addWidget(showDetailsButton);

        detailsPanel = new JPanel();
        detailsPanel->setLayout(new QVBoxLayout());//detailsPanel, BoxLayout.Y_AXIS));
        detailsPanel->setVisible(false);
        contentPane->layout()->addWidget(detailsPanel);
#if 0
        stackTraceTextArea = new JTextArea();
        stackTraceTextArea
                .setToolTipText(Bundle.getMessage("ExceptionDisplayStackTraceToolTip"));

        stackTraceLabel = new JLabel(Bundle.getMessage("ExceptionDisplayStackTraceLabel"));
        stackTraceLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        stackTraceLabel.setHorizontalAlignment(SwingConstants.LEFT);
        detailsPanel->layout()->addWidget(stackTraceLabel);
        detailsPanel->layout()->addWidget(stackTraceTextArea);
#endif
        panel = new JPanel();
        detailsPanel->layout()->addWidget(panel);

        lblNewLabel = new JLabel(tr("Operation:"));
        panel->layout()->addWidget(lblNewLabel);

        operationTextArea = new JTextArea();
        panel->layout()->addWidget(operationTextArea);

        panel_4 = new JPanel();
        detailsPanel->layout()->addWidget(panel_4);

        lblNewLabel_4 = new JLabel(tr("Message:"));
        panel_4->layout()->addWidget(lblNewLabel_4);

        messageTextArea = new JTextArea();
        panel_4->layout()->addWidget(messageTextArea);

        panel_2 = new JPanel();
        detailsPanel->layout()->addWidget(panel_2);

        lblNewLabel_2 = new JLabel(tr("Hint:"));
        panel_2->layout()->addWidget(lblNewLabel_2);

        hintTextArea = new JTextArea();
        panel_2->layout()->addWidget(hintTextArea);

        panel_5 = new JPanel();
        detailsPanel->layout()->addWidget(panel_5);

        lblNewLabel_5 = new JLabel(tr("Exception Type:"));
        panel_5->layout()->addWidget(lblNewLabel_5);

        typeTextArea = new JTextArea();
        panel_5->layout()->addWidget(typeTextArea);

        panel_6 = new JPanel();
        detailsPanel->layout()->addWidget(panel_6);

        lblNewLabel_6 = new JLabel(tr("Exception toString():"));
        panel_6->layout()->addWidget(lblNewLabel_6);

        toStringTextArea = new JTextArea();
        panel_6->layout()->addWidget(toStringTextArea);

        panel_7 = new JPanel();
        detailsPanel->layout()->addWidget(panel_7);

        lblNewLabel_7 = new JLabel(tr("Cause (Inner Ex):"));
        panel_7->layout()->addWidget(lblNewLabel_7);

        causeTextArea = new JTextArea();
        panel_7->layout()->addWidget(causeTextArea);

        buttonPanel = new JPanel();
//        buttonPanel->setAlignmentX(/*Component.LEFT_ALIGNMENT*/Qt::AlignLeft);
        contentPane->layout()->addWidget(buttonPanel);
        buttonPanel->setLayout(new FlowLayout());//FlowLayout.RIGHT, 5, 5));

        copyButton = new JButton(tr("Copy to Clipboard"));
        copyButton->setEnabled(false);
        buttonPanel->layout()->addWidget(copyButton);

        closeButton = new JButton(tr("Close"));
//        closeButton.addActionListener((ActionEvent arg0) -> {
        connect(closeButton, &JButton::clicked, [=]{
            dispose();
        });
        buttonPanel->layout()->addWidget(closeButton);
#if 0
        // Now fill in the controls...
        stackTraceTextArea->setText(context->getStackTraceAsString(10));
#endif
        // New controls
        operationTextArea->setText(context->getOperation());
        messageTextArea->setText(context->getException()->getMessage());
        hintTextArea->setText(context->getHint());
        summaryTextArea2->setText(context->getSummary());
        typeTextArea->setText(context->getException()/*.getClass().getName()*/->name);

        toStringTextArea->setText(context->getException()->toString());

        Throwable* cause = context->getException()->getCause();

        if (cause != nullptr) {
            causeTextArea->setText(cause->toString());
        } else {
            causeTextArea->setText("null"); // NOI18N
        }

        pack();

        setModal(true);
        setLocationRelativeTo(/*getOwner()*/(QWidget*)parent());
    }
