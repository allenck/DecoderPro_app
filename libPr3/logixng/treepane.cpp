#include "treepane.h"
#include "logixng/defaultlogixngpreferences.h"
#include "vptr.h"
#include <QList>
#include "runtimeexception.h"
#include "abstractfemalesocket.h"
#include "threadingutil.h"
#include "jlabel.h"
#include "box.h"
#include "fileutil.h"
#include "symboltable.h"
#include "femalesocket.h"
#include "abstractfemalesocket.h"
#include "instancemanager.h"
#include "emptyborder.h"
#include "defaultfemaledigitalactionsocket.h"

/**
 * Show the action/expression tree.
 * <P>
 * Base class for ConditionalNG editors
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class TreePane extends JPanel implements PropertyChangeListener {

  /*private*/ /*static*/ /*final*/ QMap<QString, QColor> TreePane::FEMALE_SOCKET_COLORS =  QMap<QString, QColor>();
  /*private*/ /*static*/ ImageIcon* FemaleSocketTreeRenderer::_lockIcon = nullptr;


    /**
     * Construct a ConditionalEditor.
     *
     * @param femaleRootSocket the root of the tree
     */
    /*public*/  TreePane::TreePane(AbstractFemaleSocket* femaleRootSocket, QWidget* parent)
     : JPanel(parent) {
        _femaleRootSocket = femaleRootSocket;
        // Note!! This must be made dynamic, so that new socket types are recognized automaticly and added to the list
        // and the list must be saved between runs.
        FEMALE_SOCKET_COLORS.insert("jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket", Qt::red);
        FEMALE_SOCKET_COLORS.insert("jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket", Qt::blue);

//        _femaleRootSocket->forEntireTree([=] (Base* b)  {
//            b->addPropertyChangeListener(this);
//        });
#if 1
        RunnableWithBase* rb= new TreePane_RunnableWithBase(this);
        QString name = _femaleRootSocket->getName();
        _femaleRootSocket->forEntireTree(rb);
#endif

    }

    /*public*/  void TreePane::initComponents() {
#if 0 // TODO::
        initComponents((FemaleSocket* femaleSocket, JPanel* panel) -> panel);
#else
 initComponents(new TreePane_FemaleSocketDecorator(_femaleRootSocket, this));
#endif
    }

    /*public*/  void TreePane::initComponents(FemaleSocketDecorator* decorator) {

        femaleSocketTreeModel = new FemaleSocketTreeModel(_femaleRootSocket);

        // Create a JTree and tell it to display our model
        _tree = new JTree();
//        _tree->setRowHeight(0);
//        ToolTipManager.sharedInstance().registerComponent(_tree);
        _tree->setModel(femaleSocketTreeModel);
//        _tree->setCellRenderer(new FemaleSocketTreeRenderer(decorator));

        _tree->setRootVisible(_rootVisible);
        _tree->setShowsRootHandles(true);
        _tree->setHeaderHidden(true);
        _tree->setRootIsDecorated(true);


        // Expand the entire tree
        for (int i = 0; i < _tree->getRowCount(); i++) {
            TreePath* tp =_tree->getPathForRow(i);
            QObject* obj =_tree->getPathForRow(i)->getLastPathComponent();
            TP_FemaleSocketTreeNode* node = (TP_FemaleSocketTreeNode*)obj;
            //FemaleSocket* femaleSocket = (FemaleSocket*) _tree->getPathForRow(i)->getLastPathComponent();
            FemaleSocket* femaleSocket = node->getFemaleSocket();
            //QVariant v = node->getUserObject();
            QObject* exObj = node->getExtra();
            if(node->getExtra())
                femaleSocket = (DefaultFemaleDigitalActionSocket*)node->getExtra();
            else
            {
                TP_FemaleSocketTreeNode* tnode = (TP_FemaleSocketTreeNode*)obj;
                femaleSocket = tnode->getFemaleSocket();
            }
            if (femaleSocket->isConnected() && femaleSocket->getConnectedSocket()->isEnabled()) {
                _tree->expandRow(i);
            }
        }

        // The JTree can get big, so allow it to scroll
//        JScrollPane scrollpane = new JScrollPane(_tree);

        // create panel
        setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));

        // Display it all in a window and make the window appear
        this->layout()->addWidget(/*scrollpane*/_tree/*, "Center"*/);
    }

    /*public*/  bool TreePane::getRootVisible() {
        return _rootVisible;
    }

    /*public*/  void TreePane::setRootVisible(bool rootVisible) {
        _rootVisible = rootVisible;
    }

    /**
     * Get the path for the item base.
     *
     * @param base the item to look for
     * @param list a list of the female sockets that makes up the path
     */
    /*protected*/ void TreePane::getPath(Base* base, QList<FemaleSocket*>* list) {
        for (Base* b = base; b != nullptr; b = b->getParent()) {
            if (qobject_cast<AbstractFemaleSocket*>(b->bself())) list->insert(0, (AbstractFemaleSocket*)b->bself());
        }
    }

    //@SuppressWarnings("unchecked")
    //@Override
    /*public*/  void TreePane::propertyChange(PropertyChangeEvent* evt) {

        if (Base::PROPERTY_CHILD_COUNT == (evt->getPropertyName())) {

            // Remove myself as listener from sockets that has been removed
            if (evt->getOldValue() != QVariant()) {
                if ( VPtr<QList<FemaleSocket*> >::asPtr(evt->getOldValue()) == nullptr ) throw new RuntimeException("Old value is not a list");
                foreach (FemaleSocket* socket, *VPtr<QList<FemaleSocket*> >::asPtr(evt->getOldValue())) {
                    socket->removePropertyChangeListener(this);
                }
            }

            // Add myself as listener to sockets that has been added
            if (evt->getNewValue() != QVariant()) {
                if (! VPtr<QList<FemaleSocket*> >::asPtr(evt->getNewValue())) throw new RuntimeException("New value is not a list");
                foreach (FemaleSocket* socket, *VPtr<QList<FemaleSocket*> >::asPtr(evt->getNewValue())) {
                    ((AbstractFemaleSocket*)socket->bself())->addPropertyChangeListener(this);
                }
            }

//            tree.addTreeWillExpandListener(tel);
//            tree.addTreeExpansionListener(tel);
//            tree.expandPath(path);
//            tree.expandRow(row);
//            tree.getPathForRow(row)
//            tree.isCollapsed(row)
//            tree.isCollapsed(path)
//            tree.isExpanded(path)
//            tree.isExpanded(row)
//            tree.isVisible(path)
//            tree.makeVisible(path);

            // Update the tree
            Base* b = (Base*)evt->getSource();

            QList<FemaleSocket*>* list = new QList<FemaleSocket*>();
            getPath(b, list);

//            ThreadingUtil::runOnGUIEventually([]()  {
//                FemaleSocket* femaleSocket = list->at(list->size()-1);
//                updateTree(femaleSocket, list->toVector());
//            });
            ThreadingUtil::runOnGUIEventually(new ThreadAction1(list, this));
        }


        if (Base::PROPERTY_CHILD_REORDER == (evt->getPropertyName())) {

            if (! VPtr<QList<FemaleSocket*> >::asPtr(evt->getNewValue())) throw new RuntimeException("New value is not a list");
            for (FemaleSocket* socket :  *VPtr<QList<FemaleSocket*> >::asPtr(evt->getNewValue())) {
                // Update the tree
                QList<FemaleSocket*>* list = new QList<FemaleSocket*>();
                getPath(socket, list);
//                ThreadingUtil::runOnGUIEventually([=]() {
//                    updateTree(socket, listtoArray());
//                });
                ThreadingUtil::runOnGUIEventually(new ThreadAction2(socket, list, this));
            }
        }


        if (Base::PROPERTY_SOCKET_CONNECTED == (evt->getPropertyName())
                || Base::PROPERTY_SOCKET_DISCONNECTED == (evt->getPropertyName())) {

            FemaleSocket* femaleSocket = ((FemaleSocket*)evt->getSource());
            QList<FemaleSocket*>* list = new QList<FemaleSocket*>();
            getPath(femaleSocket, list);
//            ThreadingUtil::runOnGUIEventually(() -> {
//                updateTree(femaleSocket, list.toArray());
//            });
            ThreadingUtil::runOnGUIEventually(new ThreadAction2(femaleSocket, list, this));
        }
    }

    /*protected*/ void TreePane::updateTree(FemaleSocket* currentFemaleSocket, QVector<QObject*>* currentPath) {
        for (TreeModelListener* l : femaleSocketTreeModel->listeners) {
            TreeModelEvent* tme = new TreeModelEvent(
                    (QObject*)currentFemaleSocket,
                    currentPath
            );
            l->treeNodesChanged(tme);
        }
//        _tree->updateUI(); // ??
    }

    /*public*/  void TreePane::updateTree(Base* item) {
            QList<FemaleSocket*>* list = new QList<FemaleSocket*>();
            getPath(item, list);

            FemaleSocket* femaleSocket = list->at(list->size()-1);
            QVector<QObject*>* oList = new QVector<QObject*>();
            foreach(FemaleSocket* femaleSocket, *list)
             oList->append((QObject*)femaleSocket);
            updateTree(femaleSocket, oList);
    }

    /*public*/  void TreePane::dispose() {
//        _femaleRootSocket.forEntireTree((Base* b) -> {
//            b->addPropertyChangeListener(TreePane.this);
//        });
          _femaleRootSocket->forEntireTree(new TreePane_RunnableWithBase(this));
    }


    /**
     * The methods in this class allow the JTree component to traverse the
     * female sockets of the ConditionalNG tree.
     */
//    /*public*/  static class FemaleSocketTreeModel implements TreeModel {

//        private final FemaleSocket _root;
//        protected final List<TreeModelListener> listeners = new ArrayList<>();


        /*public*/  FemaleSocketTreeModel::FemaleSocketTreeModel(AbstractFemaleSocket* root, QObject* parent)
//          : DefaultTreeModel(new TreePane_FemaleSocketTreeNode(root), parent) {
           : DefaultTreeModel(nullptr){
          setObjectName("FemaleSocketTreeModel");
          DefaultMutableTreeNode* defaultNode = (DefaultMutableTreeNode*)DefaultTreeModel::getRoot();
          defaultNode->add(new TP_FemaleSocketTreeNode(root));
          this->_root = root;
          //nodeStructureChanged((MutableTreeNode*)root);
        }

        //@Override
        /*public*/  QObject* FemaleSocketTreeModel::getRoot() {
            return (QObject*)_root;
        }

        //@Override
        /*public*/  bool FemaleSocketTreeModel::isLeaf(QObject* node) {
            FemaleSocket* socket = (AbstractFemaleSocket*) node;
            if (!socket->isConnected()) {
                return true;
            }
            return socket->getConnectedSocket()->getChildCount() == 0;
        }

        //@Override
        /*public*/  int FemaleSocketTreeModel::getChildCount(QObject* parent) const{
            AbstractFemaleSocket* socket = (AbstractFemaleSocket*) parent;
            if (!socket->isConnected()) {
                return 0;
            }
            return socket->getConnectedSocket()->getChildCount();
        }

        //@Override
        /*public*/  QObject* FemaleSocketTreeModel::getChild(QObject* parent, int index) {
            AbstractFemaleSocket* socket = (AbstractFemaleSocket*) parent;
            if (!socket->isConnected()) {
                return nullptr;
            }
            return (QObject*)socket->getConnectedSocket()->getChild(index);
        }

        //@Override
        /*public*/  int FemaleSocketTreeModel::getIndexOfChild(QObject* parent, QObject* child) {
            FemaleSocket* socket = (AbstractFemaleSocket*) parent;
            if (!socket->isConnected()) {
                return -1;
            }

            MaleSocket* connectedSocket = socket->getConnectedSocket();
            for (int i = 0; i < connectedSocket->getChildCount(); i++) {
                if ((AbstractFemaleSocket*)child == connectedSocket->getChild(i)) {
                    return i;
                }
            }
            return -1;
        }

        // This method is invoked by the JTree only for editable trees.
        // This TreeModel does not allow editing, so we do not implement
        // this method.  The JTree editable property is false by default.
        //@Override
        /*public*/  void FemaleSocketTreeModel::valueForPathChanged(TreePath* path, QVariant newvalue) {
        }

        //@Override
        /*public*/  void FemaleSocketTreeModel::addTreeModelListener(TreeModelListener* l) {
            listeners.append(l);
        }

        //@Override
        /*public*/  void FemaleSocketTreeModel::removeTreeModelListener(TreeModelListener* l) {
            listeners.removeOne(l);
        }


//    private static final class FemaleSocketTreeRenderer implements TreeCellRenderer {

//        private final FemaleSocketDecorator _decorator;
//        private static ImageIcon _lockIcon;


        /*public*/  FemaleSocketTreeRenderer::FemaleSocketTreeRenderer(FemaleSocketDecorator* decorator) {
            this->_decorator = decorator;
        }

        //@Override
        /*public*/  QWidget* FemaleSocketTreeRenderer::getTreeCellRendererComponent(JTree* tree, QVariant value,
                                                                                    bool selected, bool expanded,
                                                                                    bool leaf, int row, bool hasFocus
                                                                                    ) {

            //UIDefaults uiDefaults = javax.swing.UIManager.getDefaults();

            FemaleSocket* socket = VPtr<FemaleSocket>::asPtr(value);

            JPanel* mainPanel = new JPanel();

            mainPanel->setLayout(new QVBoxLayout());//mainPanel, BoxLayout.Y_AXIS));
            mainPanel->setOpaque(false);
            if (selected && ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getTreeEditorHighlightRow()) {
                mainPanel->setOpaque(true);
//                mainPanel->setBackground(uiDefaults->getColor("Tree.selectionBackground"));
            }

            JPanel* commentPanel = new JPanel(new FlowLayout());//FlowLayout.LEFT, 0, 0));
            mainPanel->layout()->addWidget(commentPanel);

            QHBoxLayout* panelLayout;
            JPanel* panel = new JPanel();
//            panel.setAlignmentX(LEFT_ALIGNMENT);
            mainPanel->layout()->addWidget(panel);
            panel->setLayout(panelLayout=new QHBoxLayout());//panel, BoxLayout.X_AXIS));
            panel->setOpaque(false);

            JLabel* socketLabel = new JLabel(socket->getShortDescription());
            QFont font = socketLabel->getFont();
            //socketLabel.setFont(font.deriveFont((float)(font.getSize2D()*1.7)));
            font.setPixelSize(font.pixelSize()*1.7);
            socketLabel->setFont(font);
            socketLabel->setForeground(TreePane::FEMALE_SOCKET_COLORS.value(socket->bself()->metaObject()->className()));
//            socketLabel.setForeground(Color.red);
            panelLayout->addWidget(socketLabel,0, Qt::AlignLeft);

            panelLayout->addWidget( Box::createRigidArea(QSize(5,0)), 0, Qt::AlignLeft);

            JLabel* socketNameLabel = new JLabel(socket->getName());
            socketNameLabel->setForeground(TreePane::FEMALE_SOCKET_COLORS.value(socket->bself()->metaObject()->className()));
//            socketNameLabel.setForeground(Color.red);
            panelLayout->addWidget(socketNameLabel, 0, Qt::AlignLeft);

            panelLayout->addWidget( Box::createRigidArea(QSize(5,0)),0, Qt::AlignLeft);

            JLabel* connectedItemLabel = new JLabel();
            if (socket->isConnected()) {

                if (((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getTreeEditorHighlightRow()) {
//                    connectedItemLabel.setFont(uiDefaults.getFont("Tree.font"));
                    if (selected) {
//                        connectedItemLabel->setForeground(uiDefaults.getColor("Tree.selectionForeground"));
                    }
                }

                MaleSocket* connectedSocket = socket->getConnectedSocket();

                if (connectedSocket->isSystem()) {
                    JLabel* systemLabel = new JLabel(" "+tr("System")+" "/*, JLabel.CENTER*/);
                    systemLabel->setAlignmentX(Qt::AlignLeft);
                    systemLabel->setForeground(Qt::yellow);
                    systemLabel->setBackground(Qt::red);
                    systemLabel->setOpaque(true);
                    panelLayout->addWidget(systemLabel, 0, Qt::AlignLeft);
                    panelLayout->addWidget(Box::createRigidArea(QSize(5,0)),0, Qt::AlignLeft);
                }

                if (connectedSocket->isLocked()) {
                    if (_lockIcon == nullptr) {
                        _lockIcon = new ImageIcon(FileUtil::findURL("program:resources/icons/logixng/lock.png", FileUtil::Location::INSTALLED));
                    }
                    JLabel* icLabel = new JLabel(_lockIcon/*, JLabel.CENTER*/);
                    icLabel->setAlignmentX(Qt::AlignCenter);
                    panelLayout->addWidget(icLabel);
                }

                QString comment = connectedSocket->getComment();
                if (comment != "") {
                    JLabel* commentLabel = new JLabel();
                    commentLabel->setText("<html><pre>"+comment+"</pre></html>");
                    commentLabel->setForeground(Qt::gray);
                    QFont font2 = commentLabel->getFont();
                    font2.setItalic(true);
                    commentLabel->setFont(font2/*.deriveFont(Font.ITALIC*/);
//                    commentPanel-setOpaque(false);
                    commentPanel->layout()->addWidget(commentLabel);
//                    commentPanel.setAlignmentX(LEFT_ALIGNMENT);
                    commentPanel->setBorder(new EmptyBorder(10, 0, 0, 0));
                }

                QString label = connectedSocket->getLongDescription();
                if (connectedSocket->getUserName() != "") {
                    label += " ::: " + connectedSocket->getUserName();
                }
                if (!connectedSocket->isEnabled()) {
                    label = "<html><strike>" + label + "</strike></html>";
                }
                connectedItemLabel->setText(label);

                mainPanel->setToolTip(connectedSocket->getShortDescription());

                for (SymbolTable::VariableData* variableData : connectedSocket->getLocalVariables()) {
                    JLabel* variableLabel = new JLabel(tr(
                            "Local variable \"%1\", init to %2 \"%3\"").arg(
                            variableData->_name,
                            SymbolTable::InitialValueType::toString(variableData->_initalValueType),
                            variableData->_initialValueData));
                    variableLabel->setAlignmentX(Qt::AlignLeft);
                    if (((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getTreeEditorHighlightRow()) {
//                        variableLabel.setFont(uiDefaults.getFont("Tree.font"));
//                        if (selected) {
//                            variableLabel.setForeground(uiDefaults.getColor("Tree.selectionForeground"));
//                        }
                    }
                    mainPanel->layout()->addWidget(variableLabel);
                }
            }

            panelLayout->addWidget(connectedItemLabel,0, Qt::AlignLeft);

            return _decorator->decorate(socket, mainPanel);
        }

TP_FemaleSocketTreeNode::TP_FemaleSocketTreeNode(AbstractFemaleSocket* femaleSocket, QObject* parent)
 : DefaultMutableTreeNode(femaleSocket->getName(), parent){
    setObjectName("TP_FemaleSocketTreeNode");
    setExtra(femaleSocket);
 this->femaleSocket = femaleSocket;
}

//int TreePane_FemaleSocketTreeNode::getChildCount()
//{
// return this->femaleSocket->getChildCount();
//}

//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(TreeViewer.class);
