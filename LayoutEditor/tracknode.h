#ifndef TRACKNODE_H
#define TRACKNODE_H

#include <QObject>
#include "tracksegment.h"

class TrackSegment;
class LIBLAYOUTEDITORSHARED_EXPORT TrackNode : public QObject
{
    Q_OBJECT
public:
    explicit TrackNode(QObject *parent = 0);
    /*public*/ TrackNode(QObject* node, int nodeType, TrackSegment* segment, bool endBumper, int nodeState);
    /**
     * Access methods
     */
    /*public*/ void setNode(QObject* node) {_Node = node;}
    /*public*/ QObject* getNode() {return _Node;}
    /*public*/ void setNodeType(int type) {_NodeType = type;}
    /*public*/ int getNodeType() {return _NodeType;}
    /*public*/ void setTrackSegment(TrackSegment* s) { _TrackSegment = s;}
    /*public*/ TrackSegment* getTrackSegment() {return _TrackSegment;}
    /*public*/ void setReachedEndBumper(bool end) {_ReachedEndBumper = end;}
    /*public*/ bool reachedEndOfTrack() {return _ReachedEndBumper;}
    /*public*/ int getNodeState() {return _NodeState;}
    /**
     * Returns the Block of the node QObject* at the nodeType position
     */
    /*public*/ Block* getNodeBlock();

signals:
    
public slots:
private:
    // instance variables
    QObject* _Node;// = NULL;
    int _NodeType;// = LayoutEditor::NONE;
    TrackSegment* _TrackSegment;// = NULL;
    bool _ReachedEndBumper;// = false;
    int _NodeState;// = 0;

};

#endif // TRACKNODE_H
