#include "sdfeditorpane.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QTreeView>
#include "defaultmutabletreenode.h"
#include "sdfmacroeditor.h"
#include "jseparator.h"
#include "sdfbuffer.h"
#include "sdfmacro.h"
#include "flowlayout.h"
#include "treepath.h"
#include "monitoringlabel.h"
#include "jeditorpane.h"
#include "rosterentry.h"
#include "defaultmutabletreemodel.h"


//SdfEditorPane::SdfEditorPane(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * Pane for editing Digitrax SDF files.
 * <P>
 * The GUI consists of a tree of instructions on the left, and on the right an
 * edit panel. The edit panel has a small detailed view of the instruction over
 * a larger detailed view.
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008
 * @version	$Revision: 28746 $
 */
// /*public*/ class EditorPane extends javax.swing.JPanel implements TreeSelectionListener {

/**
 *
 */
//private static final long serialVersionUID = 1271269633621702533L;
// GUI member declarations
/*static ResourceBundle res = ResourceBundle.getBundle("jmri.jmrix.loconet.sdfeditor.Editor");
static ResourceBundle exp = ResourceBundle.getBundle("jmri.jmrix.loconet.sdfeditor.Explanations");

/*public*/ SdfEditorPane::SdfEditorPane(QWidget *parent) :
  QWidget(parent)
{
 lastEditor = NULL;
 instruction = new MonitoringLabel();
 instruction->setReadOnly(true);
 explanation = new JEditorPane();
 explanation->setReadOnly(true);

 detailed = new QWidget(); // panel that contains the specific
 detailed->setLayout(new QHBoxLayout);

 // start to configure GUI
 QHBoxLayout* thisLayout;
 setLayout(thisLayout = new QHBoxLayout); //(this, BoxLayout.X_AXIS));

 // install left and right parts in split pane
 //split = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, newTree(), newEditPane());

 split = new QSplitter(Qt::Horizontal);
 split->addWidget(newTree());
 split->addWidget(newEditPane());

 thisLayout->addWidget(split);

 exp = QMap<QString, QString>();
 exp.insert("BRANCH_TO", tr("Instead of continuing to the next instruction, branch and continue at the indicated location."));
 exp.insert("CHANNEL_START", tr("Indicates the start of instructions for a specific sound processing channel. The channel numbers correspond to specific parts of the decoder hardware, and cannot be modified."));
 exp.insert("DELAY_SOUND", tr("Delay sound output until an event or for a specific time."));
 exp.insert("END_SOUND", tr("End of the definition of a sound sequence."));
 exp.insert("GENERATE_TRIGGER", tr("Create a trigger event."));
 exp.insert("INITIATE_SOUND", tr("<html><BODY>Start the definition of a specific sound within a channel. <p>The first argument set the trigger condition under which this sequence starts.<p>The second contains up to four modifiers that effect the interpretation of the trigger condition.</BODY></html>"));
 exp.insert("LOAD_MODIFIER", tr("Configure modifiers that control aspects of sound generation."));
 exp.insert("MASK_COMPARE", tr("Check status information to decide whether to skip the next thisLayout->addWidget."));
 exp.insert("PLAY", tr("<html><body>Start streaming a sound file fragment. <p>The first argument is the handle number of the fragment to play.  This is matched to a particular sound fragment (WAV file) in the sound project file. <p>The second argument controls how long the fragment will loop for.</p><p>The third argument allows you to invert the loop condition, and/or make the condition global. </body></html>"));
 exp.insert("SDL_START", tr("Document the version of the SDF format used. Currently only version 1 is defined, so there is nothing to edit on this instruction."));
 exp.insert("SKEME_START", tr("Start the definition of a particular sound scheme. The scheme numbers start with 0 and count up. Scheme 31 marks the end of the sound definition file."));
 exp.insert("SKIP_ON_TRIGGER", tr("If a specific trigger condition is true, skip the next instruction."));
}


QWidget* SdfEditorPane::newTree() {
 topNode = new DefaultMutableTreeNode("file");
 tree = new QTreeView(/*topNode*/);
// tree->getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
 tree->setSelectionMode(QAbstractItemView::SingleSelection);
 model = new DefaultMutableTreeModel();
 tree->setModel(model);


 // Listen for when the selection changes.
 //tree->addTreeSelectionListener(this);
 connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged(QModelIndex)));

 // install in scroll area
// JScrollPane treeView = new JScrollPane(tree);
// treeView.setMinimumSize(new QSize(250, 600));
// treeView.setPreferredSize(new QSize(250, 600));
// return treeView;
 return tree;
}


/**
 * Handle tree selection
 */
/*public*/ void SdfEditorPane::valueChanged(/*TreeSelectionEvent* e*/QModelIndex index)
{
 //DefaultMutableTreeNode* node = (DefaultMutableTreeNode*) tree->getLastSelectedPathComponent();
 DefaultMutableTreeModelItem* node = ((DefaultMutableTreeModelItem*)tree->currentIndex().internalPointer());

 if (node == NULL)
 {
  return;
 }

 // get an editor
 //SdfMacroEditor* nodeInfo = (SdfMacroEditor*) node->getUserObject();
 SdfMacroEditor* nodeInfo = node->macroEditor;

 // use that editor to show the instruction
 instruction->setText(nodeInfo->oneInstructionString());

 // show the explanation text
 explanation->setHtml(exp.value(nodeInfo->getMacro()->name()));

 // make the correct editor visible
 if (lastEditor != NULL)
 {
  lastEditor->setVisible(false);
 }
 lastEditor = nodeInfo;
 nodeInfo->update();
 nodeInfo->setVisible(true);
}

/*public*/ void SdfEditorPane::updateSummary()
{
 if (lastEditor != NULL)
 {
  instruction->setText(lastEditor->oneInstructionString());
 }
}

QWidget* SdfEditorPane::newEditPane()
{
 QWidget* p = new QWidget();
 p->setMinimumSize( QSize(600, 400));
// p->resize(QSize(600, 400));
// p->setMaximumSize( QSize(600, 400));

 // layout is two vertical parts
 QVBoxLayout* pLayout;
 p->setLayout(pLayout = new QVBoxLayout); //(p, BoxLayout.Y_AXIS));

 // upper part of right window
 pLayout->addWidget(newInstructionPane());

 pLayout->addWidget(new JSeparator());

 pLayout->addWidget(explanation);
 //explanation->setEnabled(false);
//    explanation->setContentType("text/html");
 explanation->setMinimumSize( QSize(600, 80));
// explanation->resize( QSize(600, 200));
// explanation->setMaximumSize( QSize(600, 200));
//    explanation->setBackground(new QLabel().getBackground());

 pLayout->addWidget(new JSeparator());

 // lower part of right window
 pLayout->addWidget(newDetailPane()); // add detailPane

 return p;
}


QWidget* SdfEditorPane::newInstructionPane()
{
//    instruction->setLineWrap(true);
//    instruction->setWrapStyleWord(true);
 instruction->setText("Select an instruction in the tree to the left");
 instruction->setReadOnly(true);
 instruction->setMinimumSize( QSize(600, 80));
 instruction->setEnabled(true);
// instruction->resize( QSize(600, 80));
// instruction->setMaximumSize( QSize(600, 80));
//    instruction->setBackground(new JLabel().getBackground());
 return instruction;
}


QWidget* SdfEditorPane::newDetailPane()
{
 if(detailed->layout() == NULL)
  detailed->setLayout(new QHBoxLayout());
 return detailed;
}

/**
 * Add the instructions to the tree
 */
void SdfEditorPane::addSdf(SdfBuffer* buff)
{
 //DefaultMutableTreeNode newNode = NULL;

 // make the top elements at the top
 QList<SdfMacro*>* ops = buff->getMacroList();
 for (int i = 0; i < ops->size(); i++)
 {
  nestNodes(topNode, ops->at(i));
 }

 // don't show the top (single) node,
 // do show all the ones right under that.
// TODO:
//    tree->expandPath(new TreePath(topNode));
//    tree->setRootVisible(false);

}

void SdfEditorPane::nestNodes(DefaultMutableTreeNode* parent, SdfMacro* macro)
{
 // put in the new topmost node
 SdfMacroEditor* macroEditor = SdfMacroEditor::attachEditor(macro);
 //detailed.add(e);
 ((QHBoxLayout*)detailed->layout())->addWidget(macroEditor);

 macroEditor->setVisible(false);
 DefaultMutableTreeNode* newNode
         = new DefaultMutableTreeNode(macroEditor);
 macroEditor->setNotify(newNode, this);
 parent->add(newNode);

 DefaultMutableTreeModelItem* parentItem =  model->createNewNode(macro->name(), macroEditor);

 // recurse for kids
 QList<SdfMacro*>* children = macro->getChildren();
 if (children == NULL) {
     return;
 }
 for (int i = 0; i < children->size(); i++)
 {
  nestNodes(newNode, children->at(i));
  QList<QVariant> data;
  SdfMacroEditor* macroEditor = SdfMacroEditor::attachEditor(children->at(i));
  ((QHBoxLayout*)detailed->layout())->addWidget(macroEditor);
  macroEditor->setHidden(true);
  data << QVariant(children->at(i)->name()) << "";
  DefaultMutableTreeModelItem* item = new DefaultMutableTreeModelItem(data, macroEditor, parentItem);
  parentItem->appendChild(item);
 }
}

/**
 * Get rid of held resources
 */
void SdfEditorPane::dispose() {
}
