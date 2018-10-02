#include "controlpanelpropertyeditor.h"
#include <QBoxLayout>
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>
#include "flowlayout.h"

/**
 * A very specific dialog for editing the properties of a FunctionButton object.
 *
 * @author Paul Bender Copyright (C) 2005
 */
///*public*/ class ControlPanelPropertyEditor extends JDialog {

/**
 * Constructor. Create it and pack it.
 */
/*public*/ ControlPanelPropertyEditor::ControlPanelPropertyEditor(ControlPanel* panel) : JDialog(panel){
    control = panel;
    initGUI();
    pack();
}

/**
 * Create, initilize, and place the GUI objects.
 */
/*private*/ void ControlPanelPropertyEditor::initGUI()
{
 resize(400,300);
    this->setDefaultCloseOperation(JDialog::HIDE_ON_CLOSE);
    this->setTitle(tr("Edit SpeedControl Panel"));
    QWidget* mainPanel = this; //new JPanel();
    //this.setContentPane(mainPanel);
    QVBoxLayout* mainPanellayout;
    mainPanel->setLayout(mainPanellayout = new QVBoxLayout());//new BorderLayout());

    QWidget* propertyPanel = new QWidget();
    GridBagLayout* propertyPanelLayout;
    propertyPanel->setLayout(propertyPanelLayout = new GridBagLayout());
    GridBagConstraints constraints = GridBagConstraints();
    constraints.anchor = GridBagConstraints::WEST;
    constraints.fill = GridBagConstraints::HORIZONTAL;
    constraints.gridheight = 1;
    constraints.gridwidth = 1;
    constraints.ipadx = 0;
    constraints.ipady = 0;
    Insets* insets = new Insets(2, 2, 2, 2);
    constraints.insets = insets;
    constraints.weightx = 1;
    constraints.weighty = 1;
    constraints.gridx = 0;
    constraints.gridy = 0;

    QButtonGroup* modeSelectionButtons = new QButtonGroup(this);

    displaySlider = new QRadioButton(tr("Display Speed Slider"));
    displaySliderContinuous = new QRadioButton(tr("Display shunting speed slider (from -100 to 0 to 100)"));
    displaySteps = new QRadioButton(tr("Display Speed Steps"));

    modeSelectionButtons->addButton(displaySlider);
    modeSelectionButtons->addButton(displaySteps);
    modeSelectionButtons->addButton(displaySliderContinuous);

    _displaySlider = control->getDisplaySlider();

    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridy = 1;
    propertyPanelLayout->addWidget(displaySlider, constraints);

    constraints.gridy = 2;
    propertyPanelLayout->addWidget(displaySteps, constraints);

    constraints.gridy = 3;
    propertyPanelLayout->addWidget(displaySliderContinuous, constraints);

    trackBox = new QCheckBox(tr("Track slider in real time"));
    constraints.gridy = 4;
    trackBox->setChecked(control->getTrackSlider());
    propertyPanelLayout->addWidget(trackBox, constraints);

    QLabel* functionSwitchLabel = new QLabel(tr("Switch to continuous speed slider on function: "));
    functionSwitchSlider = new JTextField(4);
    functionSwitchSlider->setText(control->getSwitchSliderFunction());
    constraints.gridy = 5;
    constraints.gridx = 0;
    propertyPanelLayout->addWidget(functionSwitchLabel, constraints);
    constraints.gridx = 1;
    propertyPanelLayout->addWidget(functionSwitchSlider, constraints);

    displaySlider->setChecked(_displaySlider == ControlPanel::SLIDERDISPLAY);
    displaySteps->setChecked(_displaySlider == ControlPanel::STEPDISPLAY);
    displaySliderContinuous->setChecked(_displaySlider == ControlPanel::SLIDERDISPLAYCONTINUOUS);

//    displaySlider.addActionListener(
//            new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    displaySlider.setSelected(true);
//                    displaySteps.setSelected(false);
//                    displaySliderContinuous.setSelected(false);
//                    _displaySlider = ControlPanel.SLIDERDISPLAY;
//                }
//            });
    connect(displaySlider, SIGNAL(clicked(bool)), this, SLOT(on_displaySlider_clicked()));

//    displaySteps.addActionListener(
//            new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    displaySlider.setSelected(false);
//                    displaySteps.setSelected(true);
//                    displaySliderContinuous.setSelected(false);
//                    _displaySlider = ControlPanel.STEPDISPLAY;
//                }
//            });
    connect(displaySteps, SIGNAL(clicked(bool)), this, SLOT(on_displaySteps_clicked()));

//    displaySliderContinuous.addActionListener(
//            new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    displaySlider.setSelected(false);
//                    displaySteps.setSelected(false);
//                    displaySliderContinuous.setSelected(true);
//                    _displaySlider = ControlPanel.SLIDERDISPLAYCONTINUOUS;
//                }
//            });
    connect(displaySliderContinuous, SIGNAL(clicked(bool)), this, SLOT(on_displaySliderContinuous_clicked()));

    // disable the speed controls if the control panel says they
    // aren't possible
    displaySlider->setEnabled(control->
            isSpeedControllerAvailable(ControlPanel::SLIDERDISPLAY));
    displaySteps->setEnabled(control->
            isSpeedControllerAvailable(ControlPanel::STEPDISPLAY));
    displaySliderContinuous->setEnabled(control->
            isSpeedControllerAvailable(ControlPanel::SLIDERDISPLAYCONTINUOUS));

    QWidget* buttonPanel = new QWidget();
    FlowLayout* buttonPanelLayout;
    buttonPanel->setLayout(buttonPanelLayout = new FlowLayout());//1, 2, 4, 4));

    QPushButton* saveButton = new QPushButton(tr("OK"));
//    saveButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            saveProperties();
//        }
//    });
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveProperties()));

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            finishEdit();
//        }
//    });
    connect(cancelButton, SIGNAL(clicked()),this, SLOT(finishEdit()));

    buttonPanelLayout->addWidget(saveButton);
    buttonPanelLayout->addWidget(cancelButton);

    mainPanellayout->addWidget(propertyPanel, 0, Qt::AlignCenter); // BorderLayout.CENTER);
    mainPanellayout->addWidget(buttonPanel, 0, Qt::AlignBottom);// BorderLayout.SOUTH);

}

void ControlPanelPropertyEditor::on_displaySlider_clicked()
{
 displaySlider->setChecked(true);
 displaySteps->setChecked(false);
 displaySliderContinuous->setChecked(false);
 _displaySlider = ControlPanel::SLIDERDISPLAY;
}

void ControlPanelPropertyEditor::on_displaySteps_clicked()
{
 displaySlider->setChecked(false);
 displaySteps->setChecked(true);
 displaySliderContinuous->setChecked(false);
 _displaySlider = ControlPanel::STEPDISPLAY;
}

void ControlPanelPropertyEditor::on_displaySliderContinuous_clicked()
{
 displaySlider->setChecked(false);
 displaySteps->setChecked(false);
 displaySliderContinuous->setChecked(true);
 _displaySlider = ControlPanel::SLIDERDISPLAYCONTINUOUS;
}

/**
 * Save the user-modified properties back to the FunctionButton.
 */
/*private*/ void ControlPanelPropertyEditor::saveProperties() {
    if (isDataValid()) {
        control->setTrackSlider(trackBox->isChecked());
        control->setSwitchSliderFunction(functionSwitchSlider->text());
        control->setSpeedController(_displaySlider);
        finishEdit();
    }
}

/**
 * Finish the editing process. Hide the dialog.
 */
/*private*/ void ControlPanelPropertyEditor::finishEdit() {
    this->setVisible(false);
}

/**
 * Verify the data on the dialog. If invalid, notify user of errors. This
 * only needs to do something if we add something other than speed control
 * selection to this panel.
 */
/*private*/ bool ControlPanelPropertyEditor::isDataValid() {
    return true;
}
