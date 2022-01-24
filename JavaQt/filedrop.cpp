#include "filedrop.h"
#include <QColor>
#include "borderfactory.h"
#include "matteborder.h"
#include "logger.h"
#include "droptarget.h"
#include <QMimeData>
#include "file.h"

//FileDrop::FileDrop()
//{

//}

/**
 * This class makes it easy to drag and drop files from the operating system to
 * a Java program. Any <tt>java.awt.Component</tt> can be dropped onto, but only
 * <tt>javax.swing.JComponent</tt>s will indicate the drop event with a changed
 * border.
 * <p>
 * To use this class, construct a new <tt>FileDrop</tt> by passing it the target
 * component and a <tt>Listener</tt> to receive notification when file(s) have
 * been dropped. Here is an example:
 * </p>
 * <pre><code>
 *      JPanel myPanel = new JPanel();
 *      new FileDrop( myPanel, new FileDrop.Listener()
 *      {   public void filesDropped( java.io.File[] files )
 *          {
 *              // handle file drop
 *              ...
 *          }   // end filesDropped
 *      }); // end FileDrop.Listener
 * </code></pre>
 *
 * You can specify the border that will appear when files are being dragged by
 * calling the constructor with a <tt>javax.swing.border.Border</tt>. Only
 * <tt>JComponent</tt>s will show any indication with a border.
 * <p>
 * You can turn on some debugging features by passing a <tt>PrintStream</tt>
 * object (such as <tt>System.out</tt>) into the full constructor. A
 * <tt>NULL</tt>
 * value will result in no extra debugging information being output.
 *
 *
 * <p>
 * I'm releasing this code into the Public Domain. Enjoy.
 * </p>
 * <p>
 * <em>Original author: Robert Harder, rharder@usa.net</em></p>
 * <p>
 * 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.</p>
 *
 * @author Robert Harder
 * @author rharder@users.sf.net
 * @version 1.0.1
 */
///*public*/ class FileDrop {

 // Default border color
 /*private*/ /*static*/ QColor FileDrop::defaultBorderColor = QColor(0, 0, 1, (int)(0.25*255));
 /*private*/ /*static*/ bool FileDrop::_supportsDnD = true;

/**
 * Constructs a {@link FileDrop} with a default light-blue border and, if
 * <var>c</var> is a {@link java.awt.Container}, recursively sets all
 * elements contained within as drop targets, though only the top level
 * container will change borders.
 *
 * @param c        Component on which files will be dropped.
 * @param listener Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop::FileDrop(
        Component* c,
        /*final*/ Listener* listener, QObject* parent)  : QObject(parent)
{
 common(NULL, // Logging stream
            c, // Drop target
            BorderFactory::createMatteBorder(2, 2, 2, 2, defaultBorderColor), // Drag border
            true, // Recursive
            listener);
}   // end constructor
#if 0
/**
 * Constructor with a default border and the option to recursively set drop
 * targets. If your component is a <tt>java.awt.Container</tt>, then each of
 * its children components will also listen for drops, though only the
 * parent will change borders.
 *
 * @param c         Component on which files will be dropped.
 * @param recursive Recursively set children as drop targets.
 * @param listener  Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop(
        final java.awt.Component c,
        final boolean recursive,
        final Listener listener) {
    this(NULL, // Logging stream
            c, // Drop target
            javax.swing.BorderFactory.createMatteBorder(2, 2, 2, 2, defaultBorderColor), // Drag border
            recursive, // Recursive
            listener);
}   // end constructor

/**
 * Constructor with a default border and debugging optionally turned on.
 * With Debugging turned on, more status messages will be displayed to
 * <tt>out</tt>. A common way to use this constructor is with
 * <tt>System.out</tt> or <tt>System.err</tt>. A <tt>NULL</tt> value for the
 * parameter <tt>out</tt> will result in no debugging output.
 *
 * @param out      PrintStream to record debugging info or NULL for no
 *                 debugging.
 * @param c        Component on which files will be dropped.
 * @param listener Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop(
        final java.io.PrintStream out,
        final java.awt.Component c,
        final Listener listener) {
    this(out, // Logging stream
            c, // Drop target
            javax.swing.BorderFactory.createMatteBorder(2, 2, 2, 2, defaultBorderColor),
            false, // Recursive
            listener);
}   // end constructor

/**
 * Constructor with a default border, debugging optionally turned on and the
 * option to recursively set drop targets. If your component is a
 * <tt>java.awt.Container</tt>, then each of its children components will
 * also listen for drops, though only the parent will change borders. With
 * Debugging turned on, more status messages will be displayed to
 * <tt>out</tt>. A common way to use this constructor is with
 * <tt>System.out</tt> or <tt>System.err</tt>. A <tt>NULL</tt> value for the
 * parameter <tt>out</tt> will result in no debugging output.
 *
 * @param out       PrintStream to record debugging info or NULL for no
 *                  debugging.
 * @param c         Component on which files will be dropped.
 * @param recursive Recursively set children as drop targets.
 * @param listener  Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop(
        final java.io.PrintStream out,
        final java.awt.Component c,
        final boolean recursive,
        final Listener listener) {
    this(out, // Logging stream
            c, // Drop target
            javax.swing.BorderFactory.createMatteBorder(2, 2, 2, 2, defaultBorderColor), // Drag border
            recursive, // Recursive
            listener);
}   // end constructor

/**
 * Constructor with a specified border
 *
 * @param c          Component on which files will be dropped.
 * @param dragBorder Border to use on <tt>JComponent</tt> when dragging
 *                   occurs.
 * @param listener   Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop(
        final java.awt.Component c,
        final javax.swing.border.Border dragBorder,
        final Listener listener) {
    this(
            NULL, // Logging stream
            c, // Drop target
            dragBorder, // Drag border
            false, // Recursive
            listener);
}   // end constructor

/**
 * Constructor with a specified border and the option to recursively set
 * drop targets. If your component is a <tt>java.awt.Container</tt>, then
 * each of its children components will also listen for drops, though only
 * the parent will change borders.
 *
 * @param c          Component on which files will be dropped.
 * @param dragBorder Border to use on <tt>JComponent</tt> when dragging
 *                   occurs.
 * @param recursive  Recursively set children as drop targets.
 * @param listener   Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop(
        final java.awt.Component c,
        final javax.swing.border.Border dragBorder,
        final boolean recursive,
        final Listener listener) {
    this(
            NULL,
            c,
            dragBorder,
            recursive,
            listener);
}   // end constructor

/**
 * Constructor with a specified border and debugging optionally turned on.
 * With Debugging turned on, more status messages will be displayed to
 * <tt>out</tt>. A common way to use this constructor is with
 * <tt>System.out</tt> or <tt>System.err</tt>. A <tt>NULL</tt> value for the
 * parameter <tt>out</tt> will result in no debugging output.
 *
 * @param out        PrintStream to record debugging info or NULL for no
 *                   debugging.
 * @param c          Component on which files will be dropped.
 * @param dragBorder Border to use on <tt>JComponent</tt> when dragging
 *                   occurs.
 * @param listener   Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop(
        final java.io.PrintStream out,
        final java.awt.Component c,
        final javax.swing.border.Border dragBorder,
        final Listener listener) {
    this(
            out, // Logging stream
            c, // Drop target
            dragBorder, // Drag border
            false, // Recursive
            listener);
}   // end constructor
#endif
/**
 * Full constructor with a specified border and debugging optionally turned
 * on. With Debugging turned on, more status messages will be displayed to
 * <tt>out</tt>. A common way to use this constructor is with
 * <tt>System.out</tt> or <tt>System.err</tt>. A <tt>NULL</tt> value for the
 * parameter <tt>out</tt> will result in no debugging output.
 *
 * @param out        PrintStream to record debugging info or NULL for no
 *                   debugging.
 * @param c          Component on which files will be dropped.
 * @param dragBorder Border to use on <tt>JComponent</tt> when dragging
 *                   occurs.
 * @param recursive  Recursively set children as drop targets.
 * @param listener   Listens for <tt>filesDropped</tt>.
 * @since 1.0
 */
/*public*/ FileDrop::FileDrop(
        PrintStream* out,
        Component* c,
        Border* dragBorder,
        bool recursive,
        Listener* listener, QObject* parent) : QObject(parent)
{
common(out, c, dragBorder, recursive, listener);
}

void FileDrop::common(PrintStream* out, Component* c, Border* dragBorder, bool recursive, Listener* listener)
{
 log = new Logger("FileDrop");
 this->out = out;
 this->listener = listener;
 this->c = c;
 this->dragBorder = dragBorder;

 if (supportsDnD())
 {   // Make a drop listener
#if 1
        dropListener = new MyDropTargetListener(this);
//        {
//            /*public*/ void dragEnter(java.awt.dnd.DropTargetDragEvent evt) {
//                log(out, "FileDrop: dragEnter event.");

//                // Is this an acceptable drag event?
//                if (isDragOk(out, evt)) {
//                    // If it's a Swing component, set its border
//                    if (c instanceof javax.swing.JComponent) {
//                        javax.swing.JComponent jc = (javax.swing.JComponent) c;
//                        normalBorder = jc.getBorder();
//                        log(out, "FileDrop: normal border saved.");
//                        jc.setBorder(dragBorder);
//                        log(out, "FileDrop: drag border set.");
//                    }   // end if: JComponent

//                    // Acknowledge that it's okay to enter
//                    //evt.acceptDrag( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
//                    evt.acceptDrag(java.awt.dnd.DnDConstants.ACTION_COPY);
//                    log(out, "FileDrop: event accepted.");
//                } // end if: drag ok
//                else {   // Reject the drag event
//                    evt.rejectDrag();
//                    log(out, "FileDrop: event rejected.");
//                }   // end else: drag not ok
//            }   // end dragEnter

//            /*public*/ void dragOver(java.awt.dnd.DropTargetDragEvent evt) {   // This is called continually as long as the mouse is
//                // over the drag target.
//            }   // end dragOver

//            @SuppressWarnings("unchecked")
//            /*public*/ void drop(java.awt.dnd.DropTargetDropEvent evt) {
//                log(out, "FileDrop: drop event.");
//                try {   // Get whatever was dropped
//                    java.awt.datatransfer.Transferable tr = evt.getTransferable();

//                    // Is it a file list?
//                    if (tr.isDataFlavorSupported(java.awt.datatransfer.DataFlavor.javaFileListFlavor)) {
//                        // Say we'll take it.
//                        //evt.acceptDrop ( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
//                        evt.acceptDrop(java.awt.dnd.DnDConstants.ACTION_COPY);
//                        log(out, "FileDrop: file list accepted.");

//                        // Get a useful list
//                        List<File> fileList = (List<File>) tr.getTransferData(java.awt.datatransfer.DataFlavor.javaFileListFlavor);

//                        // Convert list to array
//                        java.io.File[] filesTemp = new java.io.File[fileList.size()];
//                        fileList.toArray(filesTemp);
//                        final java.io.File[] files = filesTemp;

//                        // Alert listener to drop.
//                        if (listener != NULL) {
//                            listener.filesDropped(files);
//                        }

//                        // Mark that drop is completed.
//                        evt.getDropTargetContext().dropComplete(true);
//                        log(out, "FileDrop: drop complete.");
//                    } // end if: file list
//                    else // this section will check for a reader flavor.
//                    {
//                        // Thanks, Nathan!
//                        // BEGIN 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
//                        DataFlavor[] flavors = tr.getTransferDataFlavors();
//                        boolean handled = false;
//                        for (int zz = 0; zz < flavors.length; zz++) {
//                            if (flavors[zz].isRepresentationClassReader()) {
//                                // Say we'll take it.
//                                //evt.acceptDrop ( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
//                                evt.acceptDrop(java.awt.dnd.DnDConstants.ACTION_COPY);
//                                log(out, "FileDrop: reader accepted.");

//                                Reader reader = flavors[zz].getReaderForText(tr);

//                                BufferedReader br = new BufferedReader(reader);

//                                if (listener != NULL) {
//                                    listener.filesDropped(createFileArray(br, out));
//                                }

//                                // Mark that drop is completed.
//                                evt.getDropTargetContext().dropComplete(true);
//                                log(out, "FileDrop: drop complete.");
//                                handled = true;
//                                break;
//                            }
//                        }
//                        if (!handled) {
//                            log(out, "FileDrop: not a file list or reader - abort.");
//                            evt.rejectDrop();
//                        }
//                        // END 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
//                    }   // end else: not a file list
//                } // end try
//                catch (java.io.IOException io) {
//                    log(out, "FileDrop: IOException - abort:");
//                    io.printStackTrace(out);
//                    evt.rejectDrop();
//                } // end catch IOException
//                catch (java.awt.datatransfer.UnsupportedFlavorException ufe) {
//                    log(out, "FileDrop: UnsupportedFlavorException - abort:");
//                    ufe.printStackTrace(out);
//                    evt.rejectDrop();
//                } // end catch: UnsupportedFlavorException
//                finally {
//                    // If it's a Swing component, reset its border
//                    if (c instanceof javax.swing.JComponent) {
//                        javax.swing.JComponent jc = (javax.swing.JComponent) c;
//                        jc.setBorder(normalBorder);
//                        log(out, "FileDrop: normal border restored.");
//                    }   // end if: JComponent
//                }   // end finally
//            }   // end drop

//            /*public*/ void dragExit(java.awt.dnd.DropTargetEvent evt) {
//                log(out, "FileDrop: dragExit event.");
//                // If it's a Swing component, reset its border
//                if (c instanceof javax.swing.JComponent) {
//                    javax.swing.JComponent jc = (javax.swing.JComponent) c;
//                    jc.setBorder(normalBorder);
//                    log(out, "FileDrop: normal border restored.");
//                }   // end if: JComponent
//            }   // end dragExit

//            /*public*/ void dropActionChanged(java.awt.dnd.DropTargetDragEvent evt) {
//                log(out, "FileDrop: dropActionChanged event.");
//                // Is this an acceptable drag event?
//                if (isDragOk(out, evt)) {   //evt.acceptDrag( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
//                    evt.acceptDrag(java.awt.dnd.DnDConstants.ACTION_COPY);
//                    log(out, "FileDrop: event accepted.");
//                } // end if: drag ok
//                else {
//                    evt.rejectDrag();
//                    log(out, "FileDrop: event rejected.");
//                }   // end else: drag not ok
//            }   // end dropActionChanged
//        }; // end DropTargetListener
#endif
        // Make the component (and possibly children) drop targets
        makeDropTarget(out, c, recursive);

    } // end if: supports dnd
    else
    {
        log->warn(/*out,*/ "FileDrop: Drag and drop is not supported with this JVM");
    }   // end else: does not support DnD
}   // end constructor

/*private*/ /*static*/ bool FileDrop::supportsDnD() {   // Static Boolean
//        if (_supportsDnD == NULL) {
//            bool support = false;
//            try {
//                Class.forName("java.awt.dnd.DnDConstants");
//                support = true;
//            } // end try
//            catch (Exception* e) {
//                support = false;
//            }   // end catch
//            supportsDnD = Boolean.valueOf(support);
//        }   // end if: first time through
    return _supportsDnD;
}   // end supportsDnD

// BEGIN 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
/*private*/ static QString ZERO_CHAR_STRING = "" + (char) 0;
#if 0
/*private*/ static QList<File*> createFileArray(BufferedReader bReader, PrintStream out) {
    try {
        java.util.List<File> list = new java.util.ArrayList<File>();
        java.lang.String line = NULL;
        while ((line = bReader.readLine()) != NULL) {
            try {
                // kde seems to append a 0 char to the end of the reader
                if (ZERO_CHAR_STRING.equals(line)) {
                    continue;
                }

                java.io.File file = new java.io.File(new java.net.URI(line));
                list.add(file);
            } catch (java.net.URISyntaxException ex) {
                log(out, "FileDrop: URISyntaxException");
            }
        }

        return list.toArray(new File[list.size()]);
    } catch (IOException* ex) {
        log(out, "FileDrop: IOException");
    }
    return new File[0];
}
// END 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
#endif
/*private*/ void FileDrop::makeDropTarget(PrintStream* /*out*/, Component* c, bool /*recursive*/)
{
    // Make drop target
    DropTarget* dt = new DropTarget();
//    try {
        dt->addDropTargetListener(dropListener);
//    } // end try
//    catch (java.util.TooManyListenersException e) {
//        e.printStackTrace();
//        log(out, "FileDrop: Drop will not work due to previous error. Do you have another listener attached?");
//    }   // end catch

    // Listen for hierarchy changes and remove the drop target when the parent gets cleared out.
#if 0
    c->addHierarchyListener(new HierarchyListener()
    {
        /*public*/ void hierarchyChanged(HierarchyEvent evt)
        {
            log(out, "FileDrop: Hierarchy changed.");
            Component parent = c.getParent();
            if (parent == NULL) {
                c.setDropTarget(NULL);
                log(out, "FileDrop: Drop target cleared from component.");
            } // end if: NULL parent
            else {
                new DropTarget(c, dropListener);
                log(out, "FileDrop: Drop target added to component.");
            }   // end else: parent not NULL
        }   // end hierarchyChanged
    }); // end hierarchy listener
    if (c.getParent() != NULL) {
        new DropTarget(c, dropListener);
    }
#endif
#if 0 // TODO:
    if (recursive && (c instanceof java.awt.Container))
    {
        // Get the container
        java.awt.Container cont = (java.awt.Container) c;

        // Get it's components
        java.awt.Component[] comps = cont.getComponents();

        // Set it's components as listeners also
        for (int i = 0; i < comps.length; i++) {
            makeDropTarget(out, comps[i], recursive);
        }
    }   // end if: recursively set components as listener
#endif
    c->setDropTarget(dt);
}   // end dropListener

/**
 * Determine if the dragged data is a file list.
 */
/*private*/ bool FileDrop::isDragOk(PrintStream* /*out*/, /*final*/ QDropEvent* evt) {
#if 0
    bool ok = false;
    // Get data flavors being dragged
    java.awt.datatransfer.DataFlavor[] flavors = evt.getCurrentDataFlavors();


    // See if any of the flavors are a file list
    int i = 0;
    while (!ok && i < flavors.length) {
        // BEGIN 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
        // Is the flavor a file list?
        final DataFlavor curFlavor = flavors[i];
        if (curFlavor.equals(java.awt.datatransfer.DataFlavor.javaFileListFlavor)
                || curFlavor.isRepresentationClassReader()) {
            ok = true;
        }
        // END 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
        i++;
    }   // end while: through flavors

    // If logging is enabled, show data flavors
    if (out != NULL) {
        if (flavors.length == 0) {
            log(out, "FileDrop: no data flavors.");
        }
        for (i = 0; i < flavors.length; i++) {
            log(out, flavors[i].toString());
        }
    }   // end if: logging enabled

    return ok;
#else
    return evt->mimeData()->hasFormat("text/uri-list");
#endif
}   // end isDragOk
#if 0
/**
 * Outputs <tt>message</tt> to <tt>out</tt> if it's not NULL.
 */
private static void log(java.io.PrintStream out, String message) {   // Log message if requested
    if (out != NULL) {
        out.println(message);
    }
}   // end log
#endif
/**
 * Removes the drag-and-drop hooks from the component and optionally from
 * the all children. You should call this if you add and remove components
 * after you've set up the drag-and-drop. This will recursively unregister
 * all components contained within
 * <var>c</var> if <var>c</var> is a {@link java.awt.Container}.
 *
 * @param c The component to unregister as a drop target
 * @since 1.0
 */
/*public*/ /*static*/ bool FileDrop::remove(Component* c) {
    return remove(NULL, c, true);
}   // end remove

/**
 * Removes the drag-and-drop hooks from the component and optionally from
 * the all children. You should call this if you add and remove components
 * after you've set up the drag-and-drop.
 *
 * @param out       Optional {@link java.io.PrintStream} for logging drag
 *                  and drop messages
 * @param c         The component to unregister
 * @param recursive Recursively unregister components within a container
 * @since 1.0
 */
/*public*/ /*static*/ bool FileDrop::remove(PrintStream* /*out*/, Component* c, bool /*recursive*/)
{   // Make sure we support dnd.
     Logger* log = new Logger("FileDrop");
    if (supportsDnD()) {
        //log(out, "FileDrop: Removing drag-and-drop hooks.");
     log->info("FileDrop: Removing drag-and-drop hooks.");

        c->setDropTarget(NULL);
#if 0 // TODO recursive option
        if (recursive && (c instanceof java.awt.Container))
        {
            java.awt.Component[] comps = ((java.awt.Container) c).getComponents();
            for (int i = 0; i < comps.length; i++) {
                remove(out, comps[i], recursive);
            }
            return true;
        } // end if: recursive
        else {
            return false;
        }
#endif
    } // end if: supports DnD
    else {
        return false;
    }
}   // end remove
#if 0
/* ********  I N N E R   I N T E R F A C E   L I S T E N E R  ******** */
/**
 * Implement this inner interface to listen for when files are dropped. For
 * example your class declaration may begin like this:      <pre><code>
 *      public class MyClass implements FileDrop.Listener
 *      ...
 *      public void filesDropped( java.io.File[] files )
 *      {
 *          ...
 *      }   // end filesDropped
 *      ...
 * </code></pre>
 *
 * @since 1.0
 */
/*public*/ interface Listener {

    /**
     * This method is called when files have been successfully dropped.
     *
     * @param files An array of <tt>File</tt>s that were dropped.
     * @since 1.0
     */
    /*public*/ abstract void filesDropped(java.io.File[] files);
}   // end inner-interface Listener
#endif

MyDropTargetListener::MyDropTargetListener( FileDrop* fileDrop, QObject* parent)
 : DropTargetListener(parent)
{
 log = new Logger("MyDropTargetListener");
 this->fileDrop = fileDrop;
}

/*public*/ void MyDropTargetListener::dragEnter(QDragEnterEvent* evt) {
    //log(out, "FileDrop: dragEnter event.");
    log->info("FileDrop: dragEnter event.");

    // Is this an acceptable drag event?
    if (fileDrop->isDragOk(fileDrop->out, evt))
    {
        // If it's a Swing component, set its border
#if 1 // TODO: when Borders are implemented
        if (qobject_cast<JComponent*>(fileDrop->c)) {
            JComponent* jc = (JComponent*) fileDrop->c;
            fileDrop->normalBorder = jc->getBorder();
//            log(fileDrop->out, "FileDrop: normal border saved.");
            jc->setBorder(fileDrop->dragBorder);
//            log(fileDrop->out, "FileDrop: drag border set.");
        }   // end if: JComponent
#endif
        // Acknowledge that it's okay to enter
        //evt.acceptDrag( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
        //evt.acceptDrag(java.awt.dnd.DnDConstants.ACTION_COPY);
        evt->accept();
        //log(out, "FileDrop: event accepted.");
        log->info("FileDrop: event accepted.");
    } // end if: drag ok
    else {   // Reject the drag event
        //evt.rejectDrag();
        //log(out, "FileDrop: event rejected.");
     log->info("FileDrop: event rejected.");
    }   // end else: drag not ok
}   // end dragEnter

/*public*/ void MyDropTargetListener::dragOver(QDragMoveEvent* /*evt*/) {   // This is called continually as long as the mouse is
    // over the drag target.
}   // end dragOver

//@SuppressWarnings("unchecked")
/*public*/ void MyDropTargetListener::drop(QDropEvent* evt) {
    //log(out, "FileDrop: drop event.");
    log->info("FileDrop: drop event.");
//    try {   // Get whatever was dropped
//        Transferable* tr = evt.getTransferable();

        // Is it a file list?
//        if (tr.isDataFlavorSupported(java.awt.datatransfer.DataFlavor.javaFileListFlavor)) {
    if (evt->mimeData()->hasFormat("text/uri-list"))
    {
            //event->acceptProposedAction();

            // Say we'll take it.
            //evt.acceptDrop ( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
            //evt.acceptDrop(java.awt.dnd.DnDConstants.ACTION_COPY);
    evt->accept();
            //log(out, "FileDrop: file list accepted.");
            log->info("FileDrop: file list accepted.");

            // Get a useful list
//            List<File> fileList = (List<File>) tr.getTransferData(java.awt.datatransfer.DataFlavor.javaFileListFlavor);
            QString text = evt->mimeData()->text();
            text.replace("\r\n", "");
            QStringList sl = text.split(",");
            QList<File*> fileList = QList<File*>();
            foreach (QString s, sl)
            {
             fileList.append(new File(s.mid(7)));
            }

            // Convert list to array
            QVector<File*> filesTemp = QVector<File*>(fileList.size());
            for(int i = 0; i < fileList.count(); i++) {
             filesTemp.replace(i, fileList.at(i));
            }
            //fileList.toArray(filesTemp);
            QList<File*> files = filesTemp.toList();

            // Alert listener to drop.
//            if (fileDrop->listener != NULL) {
//                fileDrop->listener->filesDropped(files);
//            }
            emit fileDrop->dropFiles(files);

            // Mark that drop is completed.
//            evt.getDropTargetContext().dropComplete(true);
            //log(out, "FileDrop: drop complete.");
            log->info("FileDrop: drop complete.");
        } // end if: file list
#if 0 // TODO:
        else // this section will check for a reader flavor.
        {
            // Thanks, Nathan!
            // BEGIN 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
            DataFlavor[] flavors = tr.getTransferDataFlavors();
            boolean handled = false;
            for (int zz = 0; zz < flavors.length; zz++) {
                if (flavors[zz].isRepresentationClassReader()) {
                    // Say we'll take it.
                    //evt.acceptDrop ( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
                    evt.acceptDrop(java.awt.dnd.DnDConstants.ACTION_COPY);
                    log(out, "FileDrop: reader accepted.");

                    Reader reader = flavors[zz].getReaderForText(tr);

                    BufferedReader br = new BufferedReader(reader);

                    if (listener != NULL) {
                        listener.filesDropped(createFileArray(br, out));
                    }

                    // Mark that drop is completed.
                    evt.getDropTargetContext().dropComplete(true);
                    log(out, "FileDrop: drop complete.");
                    handled = true;
                    break;
                }
            }
            if (!handled) {
                log(out, "FileDrop: not a file list or reader - abort.");
                evt.rejectDrop();
            }
            // END 2007-09-12 Nathan Blomquist -- Linux (KDE/Gnome) support added.
        }   // end else: not a file list

    } // end try
    catch (java.io.IOException io) {
        log(out, "FileDrop: IOException - abort:");
        io.printStackTrace(out);
        evt.rejectDrop();
    } // end catch IOException
    catch (java.awt.datatransfer.UnsupportedFlavorException ufe) {
        log(out, "FileDrop: UnsupportedFlavorException - abort:");
        ufe.printStackTrace(out);
        evt.rejectDrop();
    } // end catch: UnsupportedFlavorException
    finally {
        // If it's a Swing component, reset its border
        if (c instanceof javax.swing.JComponent) {
            javax.swing.JComponent jc = (javax.swing.JComponent) c;
            jc.setBorder(normalBorder);
            log(out, "FileDrop: normal border restored.");
        }   // end if: JComponent
    }   // end finally
#endif
}   // end drop

/*public*/ void MyDropTargetListener::dragExit(QDragLeaveEvent* /*evt*/) {
    //log(out, "FileDrop: dragExit event.");
 log->info("FileDrop: dragExit event.");
#if 0 // TODO
 // If it's a Swing component, reset its border
    if (c instanceof javax.swing.JComponent) {
        javax.swing.JComponent jc = (javax.swing.JComponent) c;
        jc.setBorder(normalBorder);
        log(out, "FileDrop: normal border restored.");
    }   // end if: JComponent
#endif
}   // end dragExit

/*public*/ void MyDropTargetListener::dropActionChanged(QDropEvent* evt)
{
    //log(out, "FileDrop: dropActionChanged event.");
    log->info( "FileDrop: dropActionChanged event.");
    // Is this an acceptable drag event?
    if (fileDrop->isDragOk(fileDrop->out, evt)) {   //evt.acceptDrag( java.awt.dnd.DnDConstants.ACTION_COPY_OR_MOVE );
        //evt.acceptDrag(java.awt.dnd.DnDConstants.ACTION_COPY);
     evt->accept();
        //log(out, "FileDrop: event accepted.");
     log->info("FileDrop: event accepted.");
    } // end if: drag ok
    else {
        //evt.rejectDrag();
        //log(out, "FileDrop: event rejected.");
     log->info("FileDrop: event rejected.");
    }   // end else: drag not ok
}   // end dropActionChanged
