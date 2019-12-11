#include "positionabletestbase.h"
#include "jframe.h"
#include "editorscaffold.h"
#include "jpanel.h"
#include "editorframeoperator.h"

PositionableTestBase::PositionableTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Base class for tests for Positionable objects.
 *
 * @author Paul Bender Copyright (C) 2017
 */
// abstract /*public*/ class PositionableTestBase {


/**
 * Must call first in overriding method if overridden.
 */
//@Before
//@OverridingMethodsMustInvokeSuper
/*public*/ void PositionableTestBase::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::resetProfileManager();
}

/**
 * Must call last in overriding method if overridden.
 */
//@After
//@OverridingMethodsMustInvokeSuper
/*public*/ void PositionableTestBase::tearDown()
{
#if 0
 // now close panel window, if it exists
 if (editor != nullptr)
 {
  JFrame* target = editor->getTargetFrame();
  if (target != nullptr)
  {
   QVector<WindowListener*> listeners = target->getWindowListeners();
   for (WindowListener* listener : listeners) {
       target->removeWindowListener(listener);
   }
   if (editor !=(target)) {
       JUnitUtil::dispose(target);
   }
  }
  JUnitUtil::dispose(editor);
 }
#endif
 JUnitUtil::resetWindows(false, false);  // don't log here.  should be from this class.
 editor = nullptr;
 p = nullptr;
 JUnitUtil::tearDown();
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetPositionable() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Defalt Positionable", p->isPositionable(), __FILE__,  __LINE__);
    p->setPositionable(false);
    Assert::assertFalse("Positionable after set false", p->isPositionable(), __FILE__,  __LINE__);
    p->setPositionable(true);
    Assert::assertTrue("Positionable after set true", p->isPositionable(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetEditable() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Defalt Editable", p->isEditable(), __FILE__,  __LINE__);
    p->setEditable(false);
    Assert::assertFalse("Editable after set false", p->isEditable(), __FILE__,  __LINE__);
    p->setEditable(true);
    Assert::assertTrue("Editable after set true", p->isEditable(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetShowToolTip() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Defalt ShowToolTip", p->showToolTip(), __FILE__,  __LINE__);
    p->setShowToolTip(false);
    Assert::assertFalse("showToolTip after set false", p->showToolTip(), __FILE__,  __LINE__);
    p->setShowToolTip(true);
    Assert::assertTrue("showToolTip after set true", p->showToolTip(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetToolTip() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertNull("default tool tip", p->getToolTip(), __FILE__,  __LINE__);
    p->setToolTip(/*new ToolTip("hello",0,0)*/"hello");
    Assert::assertNotNull("tool tip after set", p->getToolTip(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetViewCoordinates() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Default View Coordinates", p->getViewCoordinates(), __FILE__,  __LINE__);
    p->setViewCoordinates(false);
    Assert::assertFalse("View Coordinates after set false", p->getViewCoordinates(), __FILE__,  __LINE__);
    p->setViewCoordinates(true);
    Assert::assertTrue("View Coordinates after set true", p->getViewCoordinates(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetControlling() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Defalt ShowToolTip", p->isControlling(), __FILE__,  __LINE__);
    p->setControlling(false);
    Assert::assertFalse("Controlling after set false", p->isControlling(), __FILE__,  __LINE__);
    p->setControlling(true);
    Assert::assertTrue("Controlling after set true", p->isControlling(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetHidden() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertFalse("Defalt Hidden", p->isHidden(), __FILE__,  __LINE__);
    p->setHidden(true);
    Assert::assertTrue("Hidden after set true", p->isHidden(), __FILE__,  __LINE__);
    p->setHidden(false);
    Assert::assertFalse("Hidden after set false", p->isHidden(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetDisplayLevel(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    p->setDisplayLevel(2);
    Assert::assertEquals("Display Level",2,p->getDisplayLevel(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetEditor(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Editor* es = new EditorScaffold();
    p->setEditor(es);
    Assert::assertEquals("Editor",es,p->getEditor(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testClone() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    p->deepClone();

    // this next line is consistently failing (on all object types).
    // It should pass.
    //Assert::assertFalse("clone object (not content) equality", p->equals(p));

    Assert::assertTrue("class type equality", p->getClass() == (p->getClass()), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testMaxWidth() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Max Width",0<=p->maxWidth(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testMaxHeight() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Max Height",0<=p->maxHeight(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetScale(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertEquals("Default Scale",1.0,p->getScale(),0.0, __FILE__,  __LINE__);
    p->setScale(5.0);
    Assert::assertEquals("Scale",5.0 ,p->getScale(),0.0, __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetAndSetRotationDegrees(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    p->rotate(50);
    Assert::assertEquals("Degrees",50,p->getDegrees(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetTextComponent(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertNotNull("text component",p->getTextComponent(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testStoreItem(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Store Item",p->storeItem(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testDoViemMenu(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertTrue("Do Viem Menu",p->doViemMenu(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testGetNameString(){
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Assert::assertNotNull("Name String",p->getNameString(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void PositionableTestBase::testShow() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());

    JFrame* jf = new JmriJFrame("Positionable Target Panel");
    JPanel* panel = new JPanel();
    jf->getContentPane(true)->layout()->addWidget(panel);
    jf->pack();
    jf->setVisible(true);

    editor->putItem(p);
    p->setDisplayLevel(Editor::LABELS);

    Assert::assertEquals("Display Level ", p->getDisplayLevel(), Editor::LABELS, __FILE__,  __LINE__);

    editor->setLocation(150, 150);

    editor->setTitle();

    editor->pack();
    editor->setVisible(true);

    // close the frame.
#if 0
    EditorFrameOperator* jfo = new EditorFrameOperator(jf);
    jfo->requestClose();
    jfo->waitClosed();
#endif
}
