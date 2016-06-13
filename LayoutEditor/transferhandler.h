#ifndef TRANSFERHANDLER_H
#define TRANSFERHANDLER_H

#include <QObject>

class TransferHandler : public QObject
{
    Q_OBJECT
public:
    explicit TransferHandler(QObject *parent = 0);
    /**
     * An <code>int</code> representing no transfer action.
     */
    /*public*/ static /*final*/ int NONE;// = DnDConstants::ACTION_NONE;

    /**
     * An <code>int</code> representing a &quot;copy&quot; transfer action.
     * This value is used when data is copied to a clipboard
     * or copied elsewhere in a drag and drop operation.
     */
    /*public*/ static /*final*/ int COPY;// = DnDConstants.ACTION_COPY;

    /**
     * An <code>int</code> representing a &quot;move&quot; transfer action.
     * This value is used when data is moved to a clipboard (i.e. a cut)
     * or moved elsewhere in a drag and drop operation.
     */
    /*public*/ static /*final*/ int MOVE;// = DnDConstants.ACTION_MOVE;

    /**
     * An <code>int</code> representing a source action capability of either
     * &quot;copy&quot; or &quot;move&quot;.
     */
    /*public*/ static /*final*/ int COPY_OR_MOVE;// = DnDConstants.ACTION_COPY_OR_MOVE;

    /**
     * An <code>int</code> representing a &quot;link&quot; transfer action.
     * This value is used to specify that data should be linked in a drag
     * and drop operation.
     *
     * @see java.awt.dnd.DnDConstants#ACTION_LINK
     * @since 1.6
     */
    /*public*/ static /*final*/ int LINK;// = DnDConstants.ACTION_LINK;

signals:

public slots:

};

#endif // TRANSFERHANDLER_H
