#include "jtreeutil.h"
#include "qvariant.h"
#include "defaultmutabletreenode.h"
#include "vptr.h"

JTreeUtil::JTreeUtil(QObject *parent)
    : GuiUtilBase{parent}
{

}
/**
 * Common utility methods for working with JTrees.
 * <p>
 * Chief among these is the loadTree method, for creating a tree from an XML
 * definition
 *
 * @author Bob Jacobsen Copyright 2003, 2010
 * @since 2.9.4
 */
// /*public*/ class JTreeUtil extends GuiUtilBase {

    /**
     * @param name    XML file to be read and processed
     * @param wi      WindowInterface to be passed to the nodes in the tree
     * @param context Blind context Object passed to the nodes in the tree
     * @return a mutable tree node
     */
    /*static*/ /*public*/ DefaultMutableTreeNode* JTreeUtil::loadTree(QString name, WindowInterface* wi, QObject *context) {
        QDomElement root = rootFromName(name);

        return treeFromElement(root, wi, context);
    }

    /**
     * @param main    Element  to be processed
     * @param wi      WindowInterface to be passed to the nodes in the tree
     * @param context Blind context Object passed to the nodes in the tree
     * @return a mutable tree node
     */
    /*static*/ DefaultMutableTreeNode* JTreeUtil::treeFromElement(QDomElement main, WindowInterface* wi, QObject* context) {
        QString name = "<none>";
        QDomElement e = main.firstChildElement("name");
        if (!e.isNull()) {
            name = e.text();
        }

        DefaultMutableTreeNode* node = new DefaultMutableTreeNode(name);
        node->setUserObject(VPtr<Action>::asQVariant(actionFromNode(main, wi, context)));

        //main.getChildren("node").stream().forEach((child) -> {
        QDomNodeList nl = main.childNodes();
        for(int i =0; i < nl.size(); i++)
        {
            QDomElement child = nl.at(i).toElement();
            node->add(treeFromElement(child, wi, context));
        };
        return node;
    }
