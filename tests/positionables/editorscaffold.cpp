#include "editorscaffold.h"
#include "editscene.h"
#include <QMenuBar>

/**
 * This class provides a concrete implementation of the Abstract Editor
 * class to be used in testing.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002, 2003, 2007
 * @author Dennis Miller 2004
 * @author Howard G. Penny Copyright: Copyright (c) 2005
 * @author Matthew Harris Copyright: Copyright (c) 2009
 * @author Pete Cressman Copyright: Copyright (c) 2009, 2010, 2011
 * @author Paul Bender Copyright (c) 2016
 *
 */
///*public*/ class EditorScaffold extends Editor {

/*public*/ EditorScaffold::EditorScaffold(QWidget *parent) : Editor("foo", true, true,parent) {
    //this("foo");
 setTargetPanel(new EditScene(),this);
 this->setMenuBar(new QMenuBar());
}

/*public*/ EditorScaffold::EditorScaffold(QString name, bool saveSize, bool savePosition, QWidget *parent)
: Editor(name, saveSize, savePosition, parent) {
    //super(name, saveSize, savePosition);
    setTargetPanel(new EditScene(),this);
    this->setMenuBar(new QMenuBar());
}

/*public*/ EditorScaffold::EditorScaffold(QString name, QWidget *parent) : Editor(name, true, true, parent)
{
 //this(name, true, true);
 setTargetPanel(new EditScene(),this);
 this->setMenuBar(new QMenuBar());
}

/*
 * ********************* Abstract Methods ***********************
 */
//@Override
/*public*/ void EditorScaffold::mousePressed(QGraphicsSceneMouseEvent* event){
}

//@Override
/*public*/ void EditorScaffold::mouseReleased(QGraphicsSceneMouseEvent* event){
}

//@Override
/*public*/ void EditorScaffold::mouseClicked(QGraphicsSceneMouseEvent* event){
}

//@Override
/*public*/ void EditorScaffold::mouseDragged(QGraphicsSceneMouseEvent* event){
}

//@Override
/*public*/ void EditorScaffold::mouseMoved(QGraphicsSceneMouseEvent* event){
}

//@Override
/*public*/ void EditorScaffold::mouseEntered(QGraphicsSceneMouseEvent* event){
}

//@Override
/*public*/ void EditorScaffold::mouseExited(QGraphicsSceneMouseEvent* event){
}

/*
 * set up target panel, frame etc.
 */
//@Override
/*protected*/ void EditorScaffold::init(QString name){
}

/*
 * Closing of Target frame window.
 */
//@Override
/*protected*/ void EditorScaffold::targetWindowClosingEvent(QCloseEvent* e){
}

/**
 * Called from TargetPanel's paint method for additional drawing by editor
 * view
 *
 */
//@Override
/*protected*/ void EditorScaffold::paintTargetPanel(QGraphicsScene* g){
}

/**
 * Set an object's location when it is created.
 *
 */
//@Override
/*protected*/ void EditorScaffold::setNextLocation(Positionable* obj){
}

/**
 * Editor Views should make calls to this class (Editor) to set popup menu
 * items. See 'Popup Item Methods' above for the calls.
 *
 */
//@Override
/*protected*/ void EditorScaffold::showPopUp(Positionable* p, QGraphicsSceneMouseEvent *event){
}

/**
 * After construction, initialize all the widgets to their saved config
 * settings.
 */
//@Override
/*public*/ void EditorScaffold::initView(){
}

/**
 * set up item(s) to be copied by paste
 *
 */
//@Override
/*protected*/ void EditorScaffold::copyItem(Positionable* p){
}
