#include "errorhandlingdialog.h"
#include <QBoxLayout>
#include "jlabel.h"
#include "box.h"
#include "jpanel.h"
#include "jbutton.h"
#include "conditionalng.h"
#include "logixng.h"
#include "instancemanager.h"
#include "logixng_manager.h"

/**
 *
 * @author Daniel Bergqvist 2020
 */
// /*public*/ class ErrorHandlingDialog {
    
    /*public*/  ErrorHandlingDialog::ErrorHandlingDialog(QObject *parent) : QObject(parent) {
    }
    
    /*public*/  bool ErrorHandlingDialog::showDialog(Base* item, QString errorMessage) {
        
        _item = item;
        
        _errorDialog = new JDialog(
                (JDialog*)nullptr,
                tr("An error has occurred"),
                true);
        
        QWidget* contentPanel = _errorDialog->getContentPane();
        contentPanel->setLayout(new QVBoxLayout());//contentPanel, BoxLayout.Y_AXIS));
        
        contentPanel->layout()->addWidget(new JLabel(tr(
                "Name: %1").arg(item->getShortDescription())));
        contentPanel->layout()->addWidget(Box::createVerticalStrut(10));
        contentPanel->layout()->addWidget(new JLabel(errorMessage+"     "));   // Use some spaces to get extra space right of the error message
        contentPanel->layout()->addWidget(Box::createVerticalStrut(10));
        
        contentPanel->layout()->addWidget(_disableConditionalNGCheckBox);
//        _disableConditionalNGCheckBox.setAlignmentX(Component.LEFT_ALIGNMENT);
        contentPanel->layout()->addWidget(_disableLogixNGCheckBox);
//        _disableLogixNGCheckBox.setAlignmentX(Component.LEFT_ALIGNMENT);
        contentPanel->layout()->addWidget(_stopAllLogixNGCheckBox);
//        _stopAllLogixNGCheckBox.setAlignmentX(Component.LEFT_ALIGNMENT);
        
        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));
        
        contentPanel->layout()->addWidget(panel3);
        
        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        
        // Abort
        JButton* abortButton = new JButton(tr("Abort"));  // NOI18N
        panel5->layout()->addWidget(abortButton);
        //abortButton.addActionListener((JActionEvent* e) -> {
        connect(abortButton, &JButton::clicked, [=]() {
            abortPressed(nullptr);
        });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
//        abortButton.setToolTipText("CancelLogixButtonHint");      // NOI18N
        
        // Continue
        JButton* continueButton = new JButton(tr("Continue"));    // NOI18N
        panel5->layout()->addWidget(continueButton);
        //continueButton.addActionListener((JActionEvent* e) -> {
        connect(continueButton, &JButton::clicked, [=](){
            continuePressed(nullptr);
        });
//        cancel.setToolTipText(Bundle.getMessage("CancelLogixButtonHint"));      // NOI18N
//        continueButton.setToolTipText("CancelLogixButtonHint");      // NOI18N
        
//        _errorDialog.addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
//                continuePressed(null);
//            }
//        });
        _errorDialog->addWindowListener(new EHDWindowListener(this));
/*        
        _create = new JButton(Bundle.getMessage("ButtonCreate"));  // NOI18N
        panel5.add(_create);
        _create.addActionListener((JActionEvent* e) -> {
            cancelAddPressed(null);
            
            SwingConfiguratorInterface swingConfiguratorInterface =
                    _swingConfiguratorComboBox.getItemAt(_swingConfiguratorComboBox.getSelectedIndex());
//            System.err.format("swingConfiguratorInterface: %s%n", swingConfiguratorInterface.getClass().getName());
            createAddFrame(femaleSocket, path, swingConfiguratorInterface);
        });
*/        
        contentPanel->layout()->addWidget(panel5);
        
//        addLogixNGFrame.setLocationRelativeTo(component);
        _errorDialog->setLocationRelativeTo(nullptr);
        _errorDialog->pack();
        _errorDialog->setVisible(true);
        
        return _abortExecution;
    }
    
    /*private*/ void ErrorHandlingDialog::handleCheckBoxes() {
        if (_disableConditionalNGCheckBox->isSelected()) {
            _item->getConditionalNG()->setEnabled(false);
        }
        if (_disableLogixNGCheckBox->isSelected()) {
            _item->getLogixNG()->setEnabled(false);
        }
        if (_stopAllLogixNGCheckBox->isSelected()) {
            ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->deActivateAllLogixNGs();
        }
    }
    
    /*private*/ void ErrorHandlingDialog::abortPressed(JActionEvent* e) {
        _errorDialog->setVisible(false);
        _errorDialog->dispose();
        _errorDialog = nullptr;
        _abortExecution = true;
        handleCheckBoxes();
    }
    
    /*private*/ void ErrorHandlingDialog::continuePressed(JActionEvent* e) {
        _errorDialog->setVisible(false);
        _errorDialog->dispose();
        _errorDialog = nullptr;
        handleCheckBoxes();
    }
    
