#include "layoutrhturnouteditor.h"

/**
 * MVC Editor component for LayoutRHTurnout objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutRHTurnoutEditor extends LayoutTurnoutEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutRHTurnoutEditor::LayoutRHTurnoutEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutEditor(layoutEditor){
        //super(layoutEditor);
    }

    // set the continuing route Turnout State
    //@Override
    /*protected*/ void LayoutRHTurnoutEditor::setContinuingRouteTurnoutState() {
        layoutTurnout->setContinuingSense(Turnout::CLOSED);
        if (editLayoutTurnoutStateComboBox->currentIndex() == editLayoutTurnoutThrownIndex) {
            layoutTurnout->setContinuingSense(Turnout::THROWN);
        }
    }
