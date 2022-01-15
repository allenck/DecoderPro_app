#include "lightcontrolpane.h"
#include "lightcontroltablemodel.h"
#include "jtable.h"

/**
 * Pane to add / edit Light Controls for a new or given Light.
 * <p>
 * Light Control Table with new control / edit individual Control buttons.
 * Uses separate JFrame to Edit a Single Control.
 * <p>
 * Defaults to No Light Controls for a New Light.
 * <p>
 * Code originally within LightTableAction.
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class LightControlPane extends JPanel {


/**
 * Create a Panel for Light Controls.
 * No Controls as default.
 */
/*public*/ LightControlPane::LightControlPane() : JPanel(){
    //super();
    init();
}

/**
 * Create a Panel for Light Controls.
 * @param l Light to display Light Controls for.
 */
/*public*/ LightControlPane::LightControlPane(Light* l) : JPanel(){
    //super();
    init();
    setToLight(l);
}

/*private*/ void LightControlPane::init(){

    setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
    lightControlTableModel = new LightControlTableModel(this);
    JTable* lightControlTable = new JTable(lightControlTableModel);

    lightControlTableModel->configureJTable(lightControlTable);
//    lightControlTable.setPreferredScrollableViewportSize(new java.awt.Dimension(600, 100));
    //JScrollPane lightControlTableScrollPane = new JScrollPane(lightControlTable);
    this->layout()->addWidget(/*lightControlTableScrollPane*/lightControlTable);

    addControl = new JButton(tr("Add Controller"));
    //addControl.addActionListener(this::addControlPressed);
    connect(addControl, &JButton::clicked, [=]{addControlPressed();});
    addControl->setToolTip(tr("Click to add a Light Controller to this Light"));

    JPanel* panel35 = new JPanel();
    panel35->setLayout(new FlowLayout());
    panel35->layout()->addWidget(addControl);
    this->layout()->addWidget(panel35);
}

/**
 * Respond to pressing the Add Control button.
 *
 * @param e the event containing the press action
 */
/*protected*/ void LightControlPane::addControlPressed(/*ActionEvent e*/) {
    // Use separate Runnable so window is created on top
//    javax.swing.SwingUtilities.invokeLater(() -> {
            addEditControlWindow(nullptr);
//    });
}

/**
 * Respond to pressing the Update Control button in the New / Edit Control Frame.
 *
 * @param oldControl the LightControl to remove
 * @param newControl the LightControl to add
 */
/*protected*/ void LightControlPane::updateControlPressed(LightControl* oldControl, LightControl* newControl) {
    lightControlTableModel->removeControl(oldControl);
    lightControlTableModel->addControl(newControl);
}

/**
 * Set Controls from the Control Table to the Light.
 * Removes any existing Light Controls on the Light.
 * @param g Light to set Controls to.
 */
/*public*/ void LightControlPane::setLightFromControlTable(Light* g) {
    g->deactivateLight();
    g->clearLightControls(); // clear list on Light
//    getControlList().stream().map(control -> {
//        control.setParentLight(g);
//        return control;
//    }).forEachOrdered(control -> {
//        g.addLightControl(control);
//    });
    for(LightControl* control : getControlList())
    {
     control->setParentLight((AbstractLight*)g->self());
     // ??
    }
    g->activateLight();
}

/**
 * Respond to Edit button on row in the Light Control Table.
 *
 * @param lc the Light Control to edit.
 */
/*protected*/ void LightControlPane::editControlAction(/*@Nonnull*/ LightControl* lc) {
    addEditControlWindow(lc);
}

/**
 * Add a Single Light Control to the Table.
 * @param lc the Light Control to add.
 */
/*protected*/ void LightControlPane::addControlToTable(LightControl* lc) {
    lightControlTableModel->addControl(lc);
}

/**
 * Get Light Control List currently displayed in the Table.
 * Returned by the TableModel as unmodifiable.
 * @return List of Light Controls.
 */
/*public*/ QList<LightControl*> LightControlPane::getControlList(){
    return lightControlTableModel->getControlList();
}

/**
 * Set the Table to the Light Controls of a single Light.
 * @param l the Light to set display for.
 */
/*public*/ /*final*/ void LightControlPane::setToLight(Light* l){
    lightControlTableModel->setTableToLight(l);
}


/**
 * UI Function to get Last Selected Light Control Index within
 * AddEditSingleLightControl.java
 * @return Light Control Index.
 */
/*protected*/ int LightControlPane::getLastSelectedControlIndex(){
    return defaultControlIndex;
}

/*protected*/ void LightControlPane::setLastSelectedControlIndex(int newIndex){
    defaultControlIndex = newIndex;
}


/**
 * Create the Add/Edit Light Control pane.
 */
/*private*/ void LightControlPane::addEditControlWindow(LightControl* lc) {
    closeEditControlWindow();
    addEditCtrlFrame = new AddEditSingleLightControlFrame(this, lc);
}

/*protected*/ void LightControlPane::closeEditControlWindow(){
    if (!(addEditCtrlFrame == nullptr)) {
        addEditCtrlFrame->dispose();
        addEditCtrlFrame = nullptr;
    }
    addEditCtrlFrame = nullptr;
}

/*public*/ void LightControlPane::dispose(){
    closeEditControlWindow();
}
