#include "throttleframepropertyeditor.h"
#include <QVBoxLayout>
#include "borderlayout.h"
#include "gridbagconstraints.h"
#include "jtextfield.h"
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include "throttlewindow.h"
#include <QCheckBox>
#include "borderlayout.h"

ThrottleFramePropertyEditor::ThrottleFramePropertyEditor(QWidget *parent) :
    JDialog(parent)
{
 titleTextTypes = QStringList() << "address" << "text" << "textAddress" << "addressText" << "rosterID";
 titleTextTypeNames = QStringList() <<
tr("Address") <<
tr("Text") <<
tr("Text Address") <<
tr("Address Text") <<
tr("Roster Id");

}
#if 1
/**
 * A very specific dialog for editing the properties of a ThrottleFrame
 * object.
 * @author		Original Unknown
 * @author		Ken Cameron, copyright 2008
 * @version     $Revision: 22216 $
 */
///*public*/ class ThrottleFramePropertyEditor extends JDialog
//{


/**
 * Create, initialize, and place the GUI objects.
 */
/*private*/ void ThrottleFramePropertyEditor::initGUI()
{
 this->setDefaultCloseOperation(JDialog::HIDE_ON_CLOSE);
 this->setTitle(tr("Edit Throttle Frame"));
 //QWidget* mainPanel = new QWidget();
 //this->setContentPane(mainPanel);
 //mainPanel.setLayout(new BorderLayout());
 QVBoxLayout* mainPanelLayout = new QVBoxLayout;
 setLayout(mainPanelLayout);

 QWidget* propertyPanel = new QWidget();
 //propertyPanel.setLayout(new GridBagLayout());
 QGridLayout* propertyPanelLayout = new QGridLayout(propertyPanel);

 GridBagConstraints constraints;// =  GridBagConstraints();
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

    titleField = new JTextField();
    titleField->setColumns(24);
//    titleField.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            titleFieldChanged();
//        }
//    });
    connect(titleField, SIGNAL(textEdited(QString)), this, SLOT(titleFieldChanged()));
    propertyPanelLayout->addWidget(new QLabel(tr("Frame Title:")), constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

    constraints.anchor = GridBagConstraints::CENTER;
    constraints.gridx++;
    propertyPanelLayout->addWidget(titleField, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

    titleType = new QListWidget(/*titleTextTypeNames*/);
    titleType->addItems(titleTextTypeNames);
//    titleType-setRowCount(titleTextTypeNames.length());
    titleType->setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i = 0; i < titleTextTypes.length(); i++)
    {
     if (titleTextTypes.at(i) == ( frame->getTitleTextType()) )
     {
         titleType->setCurrentRow(i);
            break;
        }
    }
 constraints.gridy++;
    constraints.gridx = 0;
    propertyPanelLayout->addWidget(new QLabel(tr("Frame Title Components:")), constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
    constraints.gridx++;
    propertyPanelLayout->addWidget(titleType, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());

    // add a checkbox for borders off, but only if that's actually possible.
    // this code uses details of internal UI code
    //if (((javax.swing.plaf.basic.BasicInternalFrameUI)frame.getCurrentThrottleFrame().getControlPanel().getUI()).getNorthPane()!=null)
    {
        borderOff = new QCheckBox(tr("Frame Border Off")/*, false*/);
        constraints.gridy++;
        constraints.gridx = 0;
        propertyPanelLayout->addWidget(new QLabel(tr("Frame Decorations:")), constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
        constraints.gridx++;
        propertyPanelLayout->addWidget(borderOff, constraints.gridy, constraints.gridx, constraints.rowSpan(), constraints.colSpan());
    }

    QWidget* buttonPanel = new QWidget();
    QGridLayout* buttonPanelLayout = new QGridLayout(buttonPanel);
//    buttonPanel.setLayout(new GridLayout(1, 2, 4, 4));

    QPushButton* saveButton = new QPushButton(tr("OK"));
//    saveButton.addActionListener(new ActionListener()
//    {
//        /*public*/ void actionPerformed(ActionEvent e)
//        {
//            saveProperties();
//        }
//    });
 connect(saveButton, SIGNAL(clicked()), this, SLOT( saveProperties()));

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener()
//    {
//        /*public*/ void actionPerformed(ActionEvent e)
//        {
//            finishEdit();
//        }
//    });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(finishEdit()));
 buttonPanelLayout->addWidget(saveButton,0,2,1,1);
 buttonPanelLayout->addWidget(cancelButton,0,3,1,1);

 mainPanelLayout->addWidget(propertyPanel/*, BorderLayout::Center*/);
 mainPanelLayout->addWidget(buttonPanel/*, BorderLayout::South*/);
 this->setVisible(true);
}

/**
 * Set the ThrottleFrame used here. Does some initialization of the
 * Frame.
 */
/*public*/ void ThrottleFramePropertyEditor::setThrottleFrame(ThrottleWindow* f)
{
#if 1
 this->frame = f;
    initGUI();
    pack();
    titleField->setText(frame->getTitleText());
    titleField->selectAll();

//    if (((javax.swing.plaf.basic.BasicInternalFrameUI)frame.getCurrentThrottleFrame().getControlPanel().getUI()).getNorthPane()!=null)
//    {
//        QSize bSize=((javax.swing.plaf.basic.BasicInternalFrameUI) frame.getCurrentThrottleFrame().getControlPanel().getUI()).getNorthPane().getPreferredSize();
//        if (bSize.height == 0) borderOff.setSelected(true);
//        else borderOff.setSelected(false);
//    }
#endif
}

/**
 * TItle field has been changed. If it has
 * text, make sure that's displayed.
 */
/*protected*/ void ThrottleFramePropertyEditor::titleFieldChanged() {
    if (titleField->text()==("")) return;
    if (titleType->currentItem()->text()==(tr("Address")))
    {
        titleType->currentItem()->setText(tr("Text")/*, true*/);
        titleType->currentItem()->setCheckState(Qt::Checked);
    }
}

/**
 * Save the user-modified properties back to the ThrottleFrame.
 */
/*private*/ void ThrottleFramePropertyEditor::saveProperties()
{
#if 0
 if (isDataValid())
 {
  int bSize = Integer.parseInt(tr("FrameSize"));
        JInternalFrame myFrame;
        frame.setTitleText( titleField.getText() );
        frame.setTitleTextType( titleTextTypes[titleType.getSelectedIndex()] );
        frame.getCurrentThrottleFrame().setFrameTitle();

        if (((javax.swing.plaf.basic.BasicInternalFrameUI)frame.getCurrentThrottleFrame().getControlPanel().getUI()).getNorthPane()!=null) {
            if (borderOff.isSelected()) bSize = 0;
            myFrame = frame.getCurrentThrottleFrame().getControlPanel();
            ((javax.swing.plaf.basic.BasicInternalFrameUI)myFrame.getUI()).getNorthPane().setPreferredSize( new Dimension(0,bSize));
            if (myFrame.isVisible()) {
                myFrame.setVisible(false);
                myFrame.setVisible(true);
            }
            myFrame = frame.getCurrentThrottleFrame().getFunctionPanel();
            ((javax.swing.plaf.basic.BasicInternalFrameUI)myFrame.getUI()).getNorthPane().setPreferredSize( new Dimension(0,bSize));
            if (myFrame.isVisible()) {
                myFrame.setVisible(false);
                myFrame.setVisible(true);
            }
            myFrame = frame.getCurrentThrottleFrame().getAddressPanel();
            ((javax.swing.plaf.basic.BasicInternalFrameUI)myFrame.getUI()).getNorthPane().setPreferredSize( new Dimension(0,bSize));
            if (myFrame.isVisible()) {
                myFrame.setVisible(false);
                myFrame.setVisible(true);
            }
        }
        finishEdit();
    }
#endif
}

/**
 * Finish the editing process. Hide the dialog.
 */
/*private*/ void ThrottleFramePropertyEditor::finishEdit()
{
 this->setVisible(false);
}

/**
 * Verify the data on the dialog. If invalid, notify user of errors.
 */
/*private*/ bool ThrottleFramePropertyEditor::isDataValid()
{
 QString errors;// = new StringBuffer();
 int errorNumber = 0;


 if (errorNumber > 0)
 {
//        JOptionPane.showMessageDialog(this, errors,
//                tr("ErrorOnPage"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(this, tr("Error"), tr("Errors on page"));
        return false;
 }
 return true;
}
#endif
