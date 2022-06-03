#ifndef DEFAULTMUTABLETREENODE_H
#define DEFAULTMUTABLETREENODE_H
#include "mutabletreenode.h"
#include <QStack>
#include "exceptions.h"
#include <QVariant>
#include <QQueue>
#include "javaqt_global.h"

class Logger;
class CatalogTreeNode;
//class QQueue<QObject*>;
//class QNode;
class JAVAQTSHARED_EXPORT DefaultMutableTreeNode : public MutableTreeNode
{
    Q_OBJECT
public:
    explicit DefaultMutableTreeNode(QObject *oparent = 0);
    /*public*/ DefaultMutableTreeNode(QVariant userObject, QObject* oparent = 0);
    /*public*/ DefaultMutableTreeNode(QVariant userObject, bool allowsChildren, QObject* oparent = 0);
    /*public*/ void insert(MutableTreeNode* newChild, int childIndex)override;
    /*public*/ void remove(int childIndex) override;
    /*public*/ void setParent(MutableTreeNode* newParent)override;
    /*public*/ MutableTreeNode* getParent()override;
    /*public*/ MutableTreeNode* getChildAt(int index) override;
    /*public*/ int getChildCount()override;
    /*public*/ int getIndex(MutableTreeNode *aChild) override;
    /*public*/ QVectorIterator<MutableTreeNode *> *children() override;
    /*public*/ void setAllowsChildren(bool allows) ;
    /*public*/ bool getAllowsChildren()override;
    /*public*/ void setUserObject(QVariant userObject)override;
    /*public*/ QVariant getUserObject();
    /*public*/ void removeFromParent()override;
    /*public*/ void remove(MutableTreeNode* aChild)override;
    /*public*/ void removeAllChildren();
    /*public*/ void add(MutableTreeNode* newChild);
    /*public*/ bool isNodeAncestor(MutableTreeNode* anotherNode);
    /*public*/ bool isNodeDescendant(DefaultMutableTreeNode* anotherNode);
    /*public*/ TreeNode* getSharedAncestor(DefaultMutableTreeNode* aNode);
    /*public*/ bool isNodeRelated(DefaultMutableTreeNode* aNode);
    /*public*/ int getDepth() ;
    /*public*/ int getLevel() ;
    /*public*/ QVector<MutableTreeNode *> *getPath();
    /*public*/ QVector<QVariant>* getUserObjectPath();
    /*public*/ MutableTreeNode* getRoot();
    /*public*/ bool isRoot();
    /*public*/ DefaultMutableTreeNode* getNextNode();
    /*public*/ DefaultMutableTreeNode* getPreviousNode();
    /*public*/ QVectorIterator<TreeNode*>* preorderEnumeration() ;
    /*public*/ QVectorIterator<TreeNode*>* postorderEnumeration();
    /*public*/ QVectorIterator<TreeNode*>* breadthFirstEnumeration() ;
    /*public*/ QVectorIterator<TreeNode*>* depthFirstEnumeration();
    /*public*/ QVectorIterator<TreeNode*>* pathFromAncestorEnumeration(TreeNode* ancestor);
    /*public*/ bool isNodeChild(TreeNode* aNode) ;
    /*public*/ MutableTreeNode* getFirstChild() ;
    /*public*/ MutableTreeNode *getLastChild();
    /*public*/ MutableTreeNode *getChildAfter(MutableTreeNode *aChild);
    /*public*/ MutableTreeNode *getChildBefore(MutableTreeNode *aChild);
    /*public*/ bool isNodeSibling(TreeNode* anotherNode);
    /*public*/ int getSiblingCount();
    /*public*/ DefaultMutableTreeNode* getNextSibling();
    /*public*/ DefaultMutableTreeNode* getPreviousSibling();
    /*public*/ bool isLeaf()override;
    /*public*/ DefaultMutableTreeNode* getFirstLeaf();
    /*public*/ DefaultMutableTreeNode* getLastLeaf();
    /*public*/ DefaultMutableTreeNode* getNextLeaf();
    /*public*/ DefaultMutableTreeNode* getPreviousLeaf();
    /*public*/ int getLeafCount();
    /*public*/ virtual QString toString();
    /*public*/ QObject* clone();
    /**
     * An enumeration that is always empty. This is used when an enumeration
     * of a leaf node's children is requested.
     */
    static /*public*/ /*final*/ QVectorIterator<MutableTreeNode*>* EMPTY_ENUMERATION;// =  QVectorIterator<TreeNode*>(QVector<TreeNode*>());

    QObject* tself() override {return (QObject*)this;}
signals:

public slots:
private:
    Logger* log;
    void common(QVariant userObject, bool allowsChildren);
//    /*private*/ void writeObject(ObjectOutputStream s) /*throw (IOException)*/ ;
//    /*private*/ void readObject(ObjectInputStream s) /*throw (IOException)*/, (ClassNotFoundException);

protected:
    /** this node's parent, or null if this node has no parent */
    /*protected*/ MutableTreeNode*   _parent= nullptr;

    /** array of children, may be null if this node has no children */
    /*protected*/ QVector<MutableTreeNode*>* _children = nullptr;

    /** optional user object */
    /*transient*/ /*protected*/ QVariant  userObject = QVariant();

    /** true if the node is able to have children */
    /*protected*/ bool           allowsChildren;
    /*protected*/ QVector<MutableTreeNode *> *getPathToRoot(MutableTreeNode *aNode, int depth);

friend class ItemPalette;
};

/*private*/ /*final*/ class PreorderEnumeration : public QObject
{
    Q_OBJECT
    /*private*/ /*final*/ QStack< QVectorIterator<MutableTreeNode*>* >* stack;// = new Stack<QList<CatalogTreeNode*>*>();
public:
    /*public*/ PreorderEnumeration(MutableTreeNode *rootNode);
    /*public*/ bool hasMoreElements();
    /*public*/ MutableTreeNode* nextElement();

};  // End of class PreorderEnumeration



/*final*/ class PostorderEnumeration : public QObject
{
    Q_OBJECT
protected:
    /*protected*/ TreeNode* root;
    /*protected*/ QVectorIterator<MutableTreeNode*>* children;
    /*protected*/ QVectorIterator<MutableTreeNode*>* subtree;
public:
    /*public*/ PostorderEnumeration(MutableTreeNode *rootNode);
    /*public*/ bool hasMoreElements();
    /*public*/ TreeNode* nextElement();
};  // End of class PostorderEnumeration



/*final*/ class BreadthFirstEnumeration : public QObject
{
    Q_OBJECT
public:
    // A simple queue with a linked list data structure.
//    /*final*/ class Queue {

//        /*final*/ class QNode {
//            /*public*/ QObject*   object;
//            /*public*/ QNode*    next;   // NULL if end
//            /*public*/ QNode(QObject* object, QNode* next)
//            {
//                this->object = object;
//                this->next = next;
//            }
//            friend class Queue;
//        };

//        /*public*/ void enqueue(QObject* anObject) {
//            if (head == NULL) {
//                head = tail = new QNode(anObject, NULL);
//            } else {
//                tail->next = new QNode(anObject, NULL);
//                tail = tail->next;
//            }
//        }

//        /*public*/ QObject* dequeue() {
//            if (head == NULL) {
//                throw new NoSuchElementException("No more elements");
//            }

//            QObject* retval = head->object;
//            QNode* oldHead = head;
//            head = head->next;
//            if (head == NULL) {
//                tail = NULL;
//            } else {
//                oldHead->next = NULL;
//            }
//            return retval;
//        }

//        /*public*/ QObject* firstObject() {
//            if (head == NULL) {
//                throw new NoSuchElementException("No more elements");
//            }

//            return head->object;
//        }

//        /*public*/ bool isEmpty() {
//            return head == NULL;
//        }
//        QNode* head; // NULL if empty
//        QNode* tail;
//     friend class QNode;
//     friend class BreadthFirstEnumeration;
//    }; // End of class Queue

    /*public*/ BreadthFirstEnumeration(MutableTreeNode *rootNode);
    /*public*/ bool hasMoreElements() ;
    /*public*/ MutableTreeNode *nextElement();
protected: QQueue<QVectorIterator<MutableTreeNode*>*>* queue;

};  // End of class BreadthFirstEnumeration



/*final*/ class PathBetweenNodesEnumeration : public QObject
{
    Q_OBJECT
protected: QStack<TreeNode*>* stack;
public:
    /*public*/ PathBetweenNodesEnumeration(TreeNode* ancestor,
                                       TreeNode* descendant);
    /*public*/ bool hasMoreElements();
    /*public*/ TreeNode* nextElement() ;
}; // End of class PathBetweenNodesEnumeration

#endif // DEFAULTMUTABLETREENODE_H
