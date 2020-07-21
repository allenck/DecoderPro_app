#include "positionablepointeditor.h"
#include "loggerfactory.h"

/**
 * MVC Editor component for PositionablePoint objects.
 *
 * Note there might not be anything for this class to do;
 * LayoutTrackEditors has a comment saying that PositionablePoint
 * doesn't have an editor.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class PositionablePointEditor extends LayoutTrackEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ PositionablePointEditor::PositionablePointEditor(/*@Nonnull*/ LayoutEditor* layoutEditor)
     : LayoutTrackEditor(layoutEditor){
        //super(layoutEditor);
    }

    /**
     * Edit a PositionablePoint
     */
    //@Override
    /*public*/ void PositionablePointEditor::editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack) {
        log->error("no editor installed for PositionablePoint",  Exception("traceback"));
    }


    /*private*/ /*final*/ /*static*/ Logger* PositionablePointEditor::log = LoggerFactory::getLogger("PositionablePointEditor");
