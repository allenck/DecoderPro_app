#include "functionbuttonpropertyeditor.h"
#include "functionbutton.h"
#include "jtextfield.h"
#include <QVBoxLayout>
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
#include <QLabel>
#include <QCheckBox>
#include "fileutil.h"
#include <QPushButton>
#include "editableresizableimagepanel.h"
#include <QValidator>
#include <QFont>

//FunctionButtonPropertyEditor::FunctionButtonPropertyEditor()
//{

//}
/**
 * A very specific dialog for editing the properties of a FunctionButton object.
 */
///*public*/ class FunctionButtonPropertyEditor extends JDialog {

    /*final*/ /*static*/ int FunctionButtonPropertyEditor::BUT_IMG_SIZE = 45;

/**
 * Constructor. Create it and pack it.
 */
/*public*/ FunctionButtonPropertyEditor::FunctionButtonPropertyEditor(QObject* parent)
{
 initGUI();
 adjustSize();
}

/**
 * Create, initilize, and place the GUI objects.
 */
 /*private*/ void FunctionButtonPropertyEditor::initGUI() {
    this->setDefaultCloseOperation(JDialog::HIDE_ON_CLOSE);
    this->setTitle(tr("Edit Function Button"));
    QWidget* mainPanel = this;
    QVBoxLayout* mainPanelLayout = new QVBoxLayout;

    //this->setContentPane(mainPanel);
    mainPanel->setLayout(mainPanelLayout);

    QWidget* propertyPanel = new QWidget();
    GridBagLayout* propertyPanelLayout;
    propertyPanel->setLayout(propertyPanelLayout =new GridBagLayout());
    GridBagConstraints constraints = GridBagConstraints();
    constraints.anchor = GridBagConstraints::WEST;
    constraints.fill = GridBagConstraints::HORIZONTAL;
    constraints.gridheight = 1;
    constraints.gridwidth = 1;
    constraints.ipadx = 0;
    constraints.ipady = 0;
    Insets* insets =  new Insets(2, 2, 2, 2);
    constraints.insets = insets;
    constraints.weightx = 1;
    constraints.weighty = 1;
    constraints.gridx = 0;
    constraints.gridy = 0;

    idField = new JTextField();
    idField->setColumns(1);
    idField->setValidator(new QIntValidator(0,28));
    propertyPanelLayout->addWidget(new QLabel(tr("Function Number")), constraints);

    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridx = 1;
    propertyPanelLayout->addWidget(idField, constraints);

    constraints.anchor = GridBagConstraints::WEST;
    constraints.gridx = 0;
    constraints.gridy = 1;
    textField = new JTextField();
    textField->setColumns(10);
    propertyPanelLayout->addWidget(new QLabel(tr("Text")), constraints);

    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridx = 1;
    propertyPanelLayout->addWidget(textField, constraints);

    constraints.anchor = GridBagConstraints::WEST;
    constraints.gridx = 0;
    constraints.gridy = 2;
    fontField = new JTextField();
    fontField->setColumns(10);
    fontField->setValidator(new QIntValidator(1,16));
    propertyPanelLayout->addWidget(new QLabel(tr("Font Size")), constraints);

    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridx = 1;
    propertyPanelLayout->addWidget(fontField, constraints);

    lockableCheckBox = new QCheckBox(tr("CheckBoxLockable"));
    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridx = 0;
    constraints.gridy = 3;
    propertyPanelLayout->addWidget(lockableCheckBox, constraints);

    visibleCheckBox = new QCheckBox(tr("CheckBox Visible"));
    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridx = 0;
    constraints.gridy = 4;
    propertyPanelLayout->addWidget(visibleCheckBox, constraints);

    constraints.gridy = 5;
    constraints.gridx = 0;
    propertyPanelLayout->addWidget(new QLabel(tr("Off Icon")), constraints);

    constraints.gridx = 1;
    propertyPanelLayout->addWidget(new QLabel(tr("On Icon")), constraints);

    constraints.gridy = 6;
    constraints.gridx = 0;

    _imageFilePath = new EditableResizableImagePanel("", BUT_IMG_SIZE, BUT_IMG_SIZE);
    _imageFilePath->setDropFolder(FileUtil::getUserResourcePath());
    _imageFilePath->setBackground( QColor(0, 0, 0, 0));
//    _imageFilePath.setBorder(BorderFactory.createLineBorder(java.awt.Color.blue));
    propertyPanelLayout->addWidget(_imageFilePath, constraints);

    constraints.gridx = 1;
    _imagePressedFilePath = new EditableResizableImagePanel("", BUT_IMG_SIZE, BUT_IMG_SIZE);
    _imagePressedFilePath->setDropFolder(FileUtil::getUserResourcePath());
    _imagePressedFilePath->setBackground(QColor(0, 0, 0, 0));
//    _imagePressedFilePath.setBorder(BorderFactory.createLineBorder(java.awt.Color.blue));
    propertyPanelLayout->addWidget(_imagePressedFilePath, constraints);

    QWidget* buttonPanel = new QWidget();
    QGridLayout* buttonPanelLayout = new QGridLayout();
    buttonPanel->setLayout(buttonPanelLayout); //(1, 2, 4, 4));

    QPushButton* saveButton = new QPushButton(tr("Ok"));
//    saveButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            saveProperties();
//        }
//    });
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveProperties()));

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            finishEdit();
//        }
//    });
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(finishEdit()));

    buttonPanelLayout->addWidget(saveButton);
    buttonPanelLayout->addWidget(cancelButton);

    mainPanelLayout->addWidget(propertyPanel, /*BorderLayout.CENTER*/0, Qt::AlignCenter);
    mainPanelLayout->addWidget(buttonPanel, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);

}

/**
 * Set the FunctionButton this dialog will edit. Method will initialize GUI
 * from button properties.
 *
 * @param button The FunctionButton to edit.
 */
/*public*/ void FunctionButtonPropertyEditor::setFunctionButton(FunctionButton* button) {
    this->button = button;
    textField->setText(button->getButtonLabel());
    lockableCheckBox->setChecked(button->getIsLockable());
    idField->setText(QString::number(button->getIdentity()));
    fontField->setText(QString::number(button->font().pointSize()));
    visibleCheckBox->setChecked(button->getDisplay());
     _imageFilePath->setImagePath(button->getIconPath());
    _imagePressedFilePath->setImagePath(button->getSelectedIconPath());
    textField->setFocus();
}

/**
 * Save the user-modified properties back to the FunctionButton.
 */
 /*private*/ void FunctionButtonPropertyEditor::saveProperties() {
    if (isDataValid()) {
        button->setButtonLabel(textField->text());
        button->setIsLockable(lockableCheckBox->isChecked());
        button->setIdentity(idField->text().toInt());
        QString name = button->font().family();
//        button->setFont( QFont(name,
//                button->font.().getStyle(),
//                Integer.parseInt(fontField.getText())));
        QFont f = button->font();
        f.setPointSize(fontField->text().toInt());
        button->setVisible(visibleCheckBox->isChecked());
        button->setDisplay(visibleCheckBox->isChecked());
        button->setIconPath(_imageFilePath->getImagePath());
        button->setSelectedIconPath(_imagePressedFilePath->getImagePath());
        button->setDirty(true);
        button->updateLnF();
        //finishEdit();
    }
    accepted();
    close();
}

/**
 * Finish the editing process. Hide the dialog.
 */
 /*private*/ void FunctionButtonPropertyEditor::finishEdit() {
    //this.setVisible(false);
 rejected();
 close();
}

/**
 * Verify the data on the dialog. If invalid, notify user of errors.
 */
 /*private*/ bool FunctionButtonPropertyEditor::isDataValid() {
    QString errors;// = new StringBuffer();
    int errorNumber = 0;
    /* ID >=0 && ID <= 28 */
//    try {
//        int id = Integer.parseInt(idField.getText());
//        if ((id < 0) || id > 28) {
//            throw new NumberFormatException("");
//        }
//    } catch (NumberFormatException* ex) {
//        errors.append(String.valueOf(++errorNumber));
//        errors.append(". " + tr("ErrorFunctionKeyRange") + "\n");
//    }

    /* font > 0 */
//    try {
//        int size = Integer.parseInt(fontField.getText());
//        if (size < 1) {
//            throw new NumberFormatException("");
//        }
//    } catch (NumberFormatException* ex) {
//        errors.append(String.valueOf(++errorNumber));
//        errors.append(". " + tr("ErrorFontSize"));
//    }

//    if (errorNumber > 0) {
//        JOptionPane.showMessageDialog(this, errors,
//                "Errors on page", JOptionPane.ERROR_MESSAGE);
//        return false;
//    }
    return true;
}

