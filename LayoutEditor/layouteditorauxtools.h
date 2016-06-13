#ifndef LAYOUTEDITORAUXTOOLS_H
#define LAYOUTEDITORAUXTOOLS_H
#include "layouteditor.h"

#include <QObject>
class LayoutConnectivity;
class LayoutEditorAuxTools : public QObject
{
  friend class LayoutEditor;
    Q_OBJECT
public:
    //explicit LayoutEditorAuxTools(QObject *parent = 0);
    // constructor method
    /*public*/ LayoutEditorAuxTools(LayoutEditor* thePanel);

    // register a change in block connectivity that may require an update of connectivity list
    /*public*/ void setBlockConnectivityChanged();
    /**
     * Get Connectivity involving a specific Layout Block
     * <P>
     * This routine returns an QVector of BlockConnectivity objects involving the specified
     *		LayoutBlock.
     */
    /*public*/ QVector<LayoutConnectivity*>* getConnectivityList(LayoutBlock* blk);
    /**
     * Initializes the block connectivity (block boundaries) for a Layout Editor panel.
     * <P>
     * This routine sets up the LayoutConnectivity objects needed to show the current
     *		connectivity. It gets its information from arrays contained in LayoutEditor.
     * <P>
     * One LayoutConnectivity object is created for each block boundary -- connection
     *		points where two blocks join. Block boundaries can occur whereever a track segment
     *		in one block joins with:
     *		1) a track segment in another block -OR-
     *		2) a connection point in a layout turnout in another block -OR-
     *      3) a connection point in a level crossing in another block.
     * <P>
     * The first block is always a track segment.  The direction set in the LayoutConnectivity
     *		is the direction of the track segment alone for cases 2) and 3) above.  For case 1),
     *		two track segments, the direction reflects an "average" over the two track segments.
     *		See LayoutConnectivity for the allowed values of direction.
     * <P>
     *
     */
    /*public*/ void initializeBlockConnectivity ();
    /**
     * Searches for and adds BeanSetting's to a Path as needed.
     * <P>
     * This method starts at the entry point to the LayoutBlock given in the Path at
     *		the block boundary specified in the LayoutConnectivity. It follows the track
     *		looking for turnout settings that are required for a train entering on this
     *		block boundary point to exit the block. If a required turnout setting is found,
     *		the turnout and its required state are used to create a BeanSetting, which is
     *		added to the Path:: Such a setting can occur, for example, if a track enters
     *		a right-handed turnout from either the diverging track or the continuing track.
     * <P>
     * If the track branches into two tracks (for example, by entering a right-handed turnout
     *		via the throat track), the search is stopped. The search is also stopped when
     *		the track reaches a different block (or an undefined block), or reaches an end
     *		bumper.
     */
    /*public*/ void addBeanSettings(Path* p, LayoutConnectivity* lc, LayoutBlock* layoutBlock);

signals:
    
public slots:
private:
    /*private*/ LayoutEditor* layoutEditor;// = NULL;
    /*private*/ QVector<LayoutConnectivity*>* cList;// = new QVector<LayoutConnectivity*>(); //LayoutConnectivity list
    /*private*/ bool blockConnectivityChanged;// = false;  // true if block connectivity may have changed
    /*private*/ bool initialized;// = false;
Logger* log;
/**
 * Updates the block connectivity (block boundaries) for a Layout Editor panel after changes may have
 *		been made.
 */
/*private*/ void updateBlockConnectivity();
/*private*/ void checkConnectivity(LayoutConnectivity* c, QVector<bool> found);
// compute direction of vector from p1 to p2
/*private*/ int computeDirection(QPointF p1, QPointF p2);

};

#endif // LAYOUTEDITORAUXTOOLS_H
