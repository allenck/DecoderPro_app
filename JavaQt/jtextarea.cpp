#include "jtextarea.h"
#include "exceptions.h"
#include <QFontMetrics>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QMimeData>
#include <QFontDialog>

//JTextArea::JTextArea(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * A <code>JTextArea</code> is a multi-line area that displays plain text.
 * It is intended to be a lightweight component that provides source
 * compatibility with the <code>java.awt.TextArea</code> class where it can
 * reasonably do so.
 * You can find information and examples of using all the text components in
 * <a href="http://java.sun.com/docs/books/tutorial/uiswing/components/text.html">Using Text Components</a>,
 * a section in <em>The Java Tutorial.</em>
 *
 * <p>
 * This component has capabilities not found in the
 * <code>java.awt.TextArea</code> class.  The superclass should be
 * consulted for additional capabilities.
 * Alternative multi-line text classes with
 * more capabilities are <code>JTextPane</code> and <code>JEditorPane</code>.
 * <p>
 * The <code>java.awt.TextArea</code> internally handles scrolling.
 * <code>JTextArea</code> is different in that it doesn't manage scrolling,
 * but implements the swing <code>Scrollable</code> interface.  This allows it
 * to be placed inside a <code>JScrollPane</code> if scrolling
 * behavior is desired, and used directly if scrolling is not desired.
 * <p>
 * The <code>java.awt.TextArea</code> has the ability to do line wrapping.
 * This was controlled by the horizontal scrolling policy.  Since
 * scrolling is not done by <code>JTextArea</code> directly, backward
 * compatibility must be provided another way.  <code>JTextArea</code> has
 * a bound property for line wrapping that controls whether or
 * not it will wrap lines.  By default, the line wrapping property
 * is set to false (not wrapped).
 * <p>
 * <code>java.awt.TextArea</code> has two properties <code>rows</code>
 * and <code>columns</code> that are used to determine the preferred size.
 * <code>JTextArea</code> uses these properties to indicate the
 * preferred size of the viewport when placed inside a <code>JScrollPane</code>
 * to match the functionality provided by <code>java.awt.TextArea</code>.
 * <code>JTextArea</code> has a preferred size of what is needed to
 * display all of the text, so that it functions properly inside of
 * a <code>JScrollPane</code>.  If the value for <code>rows</code>
 * or <code>columns</code> is equal to zero,
 * the preferred size along that axis is used for
 * the viewport preferred size along the same axis.
 * <p>
 * The <code>java.awt.TextArea</code> could be monitored for changes by adding
 * a <code>TextListener</code> for <code>TextEvent</code>s.
 * In the <code>JTextComponent</code> based
 * components, changes are broadcasted from the model via a
 * <code>DocumentEvent</code> to <code>DocumentListeners</code>.
 * The <code>DocumentEvent</code> gives
 * the location of the change and the kind of change if desired.
 * The code fragment might look something like:
 * <pre>
 *    DocumentListener myListener = ??;
 *    JTextArea myArea = ??;
 *    myArea.getDocument().addDocumentListener(myListener);
 * </pre>
 * <p>
 * <dl>
 * <dt><b><font size=+1>Newlines</font></b>
 * <dd>
 * For a discussion on how newlines are handled, see
 * <a href="text/DefaultEditorKit.html">DefaultEditorKit</a>.
 * </dl>
 *
 * <p>
 * <strong>Warning:</strong> Swing is not thread safe. For more
 * information see <a
 * href="package-summary.html#threading">Swing's Threading
 * Policy</a>.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @beaninfo
 *   attribute: isContainer false
 * description: A multi-line area that displays plain text.
 *
 * @author  Timothy Prinzing
 * @see JTextPane
 * @see JEditorPane
 */
///*public*/ class JTextArea extends JTextComponent {

/**
 * @see #getUIClassID
 * @see #readObject
 */
//private static final String uiClassID = "TextAreaUI";

/**
 * Constructs a new TextArea.  A default model is set, the initial string
 * is NULL, and rows/columns are set to 0.
 */
/*public*/ JTextArea::JTextArea(QWidget *parent)
 : QTextEdit(parent)
{
 //this(NULL, NULL, 0, 0);
 common();
}
void JTextArea::common()
{
 doc = createDefaultModel();
 text = "";
 rows = 0;
 columns =0;
 wrap = false;
 textOption = QTextOption::WrapMode::NoWrap;
}
/**
 * Constructs a new TextArea with the specified text displayed.
 * A default model is created and rows/columns are set to 0.
 *
 * @param text the text to be displayed, or NULL
 */
/*public*/ JTextArea::JTextArea(QString text, QWidget */*parent*/)

{
 //this(NULL, text, 0, 0);
 common();
 setText(text);
}
/**
 * Constructs a new empty TextArea with the specified number of
 * rows and columns.  A default model is created, and the initial
 * string is NULL.
 *
 * @param rows the number of rows >= 0
 * @param columns the number of columns >= 0
 * @exception IllegalArgumentException if the rows or columns
 *  arguments are negative.
 */
/*public*/ JTextArea::JTextArea(int rows, int columns, QWidget * parent)
 : QTextEdit(parent)
{
    //this(NULL, NULL, rows, columns);
 common();
 this->rows = rows;
 setColumns(columns);
}

/**
 * Constructs a new TextArea with the specified text and number
 * of rows and columns.  A default model is created.
 *
 * @param text the text to be displayed, or NULL
 * @param rows the number of rows >= 0
 * @param columns the number of columns >= 0
 * @exception IllegalArgumentException if the rows or columns
 *  arguments are negative.
 */
/*public*/ JTextArea::JTextArea(QString text, int rows, int columns, QWidget *parent)
: QTextEdit(parent)
{
 // this(NULL, text, rows, columns);
 common();
 this->rows = rows;
 setColumns(columns);
 setText(text);
}

/**
 * Constructs a new JTextArea with the given document model, and defaults
 * for all of the other arguments (NULL, 0, 0).
 *
 * @param doc  the model to use
 */
/*public*/ JTextArea::JTextArea(Document* doc, QWidget */*parent*/) {
    //this(doc, NULL, 0, 0);
 common();
 setDocument(doc);
}

/**
 * Constructs a new JTextArea with the specified number of rows
 * and columns, and the given model.  All of the constructors
 * feed through this constructor.
 *
 * @param doc the model to use, or create a default one if NULL
 * @param text the text to be displayed, NULL if none
 * @param rows the number of rows >= 0
 * @param columns the number of columns >= 0
 * @exception IllegalArgumentException if the rows or columns
 *  arguments are negative.
 */
/*public*/ JTextArea::JTextArea(Document* doc, QString text, int rows, int columns, QWidget *parent) : QTextEdit(parent){
    //super();
 common();
    this->rows = rows;
    setColumns(columns);
    if (doc == NULL) {
        doc = createDefaultModel();
    }
    else
     setDocument(doc);
    if (text != NULL) {
        setText(text);
//        select(0, 0);
    }
    if (rows < 0) {
        throw new IllegalArgumentException("rows: " + QString::number(rows));
    }
    if (columns < 0) {
        throw new IllegalArgumentException("columns: " + QString::number(columns));
    }
#if 0
    LookAndFeel.installProperty(this,
                                "focusTraversalKeysForward",
                                JComponent.
                                getManagingFocusForwardTraversalKeys());
    LookAndFeel.installProperty(this,
                                "focusTraversalKeysBackward",
                                JComponent.
                                getManagingFocusBackwardTraversalKeys());
#endif
}

/**
 * Returns the class ID for the UI.
 *
 * @return the ID ("TextAreaUI")
 * @see JComponent#getUIClassID
 * @see UIDefaults#getUI
 */
///*public*/ String getUIClassID() {
//    return uiClassID;
//}

/**
 * Creates the default implementation of the model
 * to be used at construction if one isn't explicitly
 * given.  A new instance of PlainDocument is returned.
 *
 * @return the default document model
 */
/*protected*/ Document* JTextArea::createDefaultModel() {
//    return new PlainDocument();
 return (Document*)new QTextDocument(this);
}

/**
 * Sets the number of characters to expand tabs to.
 * This will be multiplied by the maximum advance for
 * variable width fonts.  A PropertyChange event ("tabSize") is fired
 * when the tab size changes.
 *
 * @param size number of characters to expand to
 * @see #getTabSize
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: the number of characters to expand tabs to
 */
///*public*/ void JTextArea::setTabSize(int size) {
//    Document* doc = document();
//    if (doc != NULL) {
//        int old = getTabSize();
//        doc.putProperty(PlainDocument.tabSizeAttribute, Integer.valueOf(size));
//        firePropertyChange("tabSize", old, size);
//    }
//}
void JTextArea::setTabSize(int size) { setTabStopWidth(size);}

#if 0
/**
 * Gets the number of characters used to expand tabs.  If the document is
 * NULL or doesn't have a tab setting, return a default of 8.
 *
 * @return the number of characters
 */
/*public*/ int getTabSize() {
    int size = 8;
    Document doc = getDocument();
    if (doc != NULL) {
        Integer i = (Integer) doc.getProperty(PlainDocument.tabSizeAttribute);
        if (i != NULL) {
            size = i.intValue();
        }
    }
    return size;
}
#endif
/**
 * Sets the line-wrapping policy of the text area.  If set
 * to true the lines will be wrapped if they are too long
 * to fit within the allocated width.  If set to false,
 * the lines will always be unwrapped.  A <code>PropertyChange</code>
 * event ("lineWrap") is fired when the policy is changed.
 * By default this property is false.
 *
 * @param wrap indicates if lines should be wrapped
 * @see #getLineWrap
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: should lines be wrapped
 */
/*public*/ void JTextArea::setLineWrap(bool wrap) {
 textOption = wordWrapMode();
    bool old = this->wrap;
    this->wrap = wrap;
    if(!wrap)
     textOption = QTextOption::NoWrap;
    else
    {
     if(textOption == QTextOption::NoWrap)
      textOption = QTextOption::WrapAtWordBoundaryOrAnywhere;
    }
     setWordWrapMode(textOption);
//    firePropertyChange("lineWrap", old, wrap);
}

/**
 * Gets the line-wrapping policy of the text area.  If set
 * to true the lines will be wrapped if they are too long
 * to fit within the allocated width.  If set to false,
 * the lines will always be unwrapped.
 *
 * @return if lines will be wrapped
 */
/*public*/ bool JTextArea::getLineWrap() {
    return wrap;
}

/**
 * Sets the style of wrapping used if the text area is wrapping
 * lines.  If set to true the lines will be wrapped at word
 * boundaries (whitespace) if they are too long
 * to fit within the allocated width.  If set to false,
 * the lines will be wrapped at character boundaries.
 * By default this property is false.
 *
 * @param word indicates if word boundaries should be used
 *   for line wrapping
 * @see #getWrapStyleWord
 * @beaninfo
 *   preferred: false
 *       bound: true
 * description: should wrapping occur at word boundaries
 */
/*public*/ void JTextArea::setWrapStyleWord(bool word) {
 textOption = wordWrapMode();
    bool old = this->word;
    this->word = word;
    if(word)
     textOption = QTextOption::WordWrap;
    else
     textOption = QTextOption::WordWrap;
    setWordWrapMode(textOption);
    //firePropertyChange("wrapStyleWord", old, word);
}

/**
 * Gets the style of wrapping used if the text area is wrapping
 * lines.  If set to true the lines will be wrapped at word
 * boundaries (ie whitespace) if they are too long
 * to fit within the allocated width.  If set to false,
 * the lines will be wrapped at character boundaries.
 *
 * @return if the wrap style should be word boundaries
 *  instead of character boundaries
 * @see #setWrapStyleWord
 */
/*public*/ bool JTextArea::getWrapStyleWord() {
 textOption = wordWrapMode();
 if(textOption == QTextOption::WordWrap || textOption == QTextOption::WrapAtWordBoundaryOrAnywhere)
  word = true;
 else
  word = false;

 return word;
}

/*public*/ void JTextArea::setOpaque(bool)
{
 // TODO:
}

#if 0
/**
 * Translates an offset into the components text to a
 * line number.
 *
 * @param offset the offset >= 0
 * @return the line number >= 0
 * @exception BadLocationException thrown if the offset is
 *   less than zero or greater than the document length.
 */
/*public*/ int getLineOfOffset(int offset) throws BadLocationException {
    Document doc = getDocument();
    if (offset < 0) {
        throw new BadLocationException("Can't translate offset to line", -1);
    } else if (offset > doc.getLength()) {
        throw new BadLocationException("Can't translate offset to line", doc.getLength()+1);
    } else {
        Element map = getDocument().getDefaultRootElement();
        return map.getElementIndex(offset);
    }
}

/**
 * Determines the number of lines contained in the area.
 *
 * @return the number of lines > 0
 */
/*public*/ int getLineCount() {
    Element map = getDocument().getDefaultRootElement();
    return map.getElementCount();
}

/**
 * Determines the offset of the start of the given line.
 *
 * @param line  the line number to translate >= 0
 * @return the offset >= 0
 * @exception BadLocationException thrown if the line is
 * less than zero or greater or equal to the number of
 * lines contained in the document (as reported by
 * getLineCount).
 */
/*public*/ int getLineStartOffset(int line) throws BadLocationException {
    int lineCount = getLineCount();
    if (line < 0) {
        throw new BadLocationException("Negative line", -1);
    } else if (line >= lineCount) {
        throw new BadLocationException("No such line", getDocument().getLength()+1);
    } else {
        Element map = getDocument().getDefaultRootElement();
        Element lineElem = map.getElement(line);
        return lineElem.getStartOffset();
    }
}

/**
 * Determines the offset of the end of the given line.
 *
 * @param line  the line >= 0
 * @return the offset >= 0
 * @exception BadLocationException Thrown if the line is
 * less than zero or greater or equal to the number of
 * lines contained in the document (as reported by
 * getLineCount).
 */
/*public*/ int getLineEndOffset(int line) throws BadLocationException {
    int lineCount = getLineCount();
    if (line < 0) {
        throw new BadLocationException("Negative line", -1);
    } else if (line >= lineCount) {
        throw new BadLocationException("No such line", getDocument().getLength()+1);
    } else {
        Element map = getDocument().getDefaultRootElement();
        Element lineElem = map.getElement(line);
        int endOffset = lineElem.getEndOffset();
        // hide the implicit break at the end of the document
        return ((line == lineCount - 1) ? (endOffset - 1) : endOffset);
    }
}

// --- java.awt.TextArea methods ---------------------------------

/**
 * Inserts the specified text at the specified position.  Does nothing
 * if the model is NULL or if the text is NULL or empty.
 *
 * @param str the text to insert
 * @param pos the position at which to insert >= 0
 * @exception IllegalArgumentException  if pos is an
 *  invalid position in the model
 * @see TextComponent#setText
 * @see #replaceRange
 */
/*public*/ void insert(String str, int pos) {
    Document doc = getDocument();
    if (doc != NULL) {
        try {
            doc.insertString(pos, str, NULL);
        } catch (BadLocationException e) {
            throw new IllegalArgumentException(e.getMessage());
        }
    }
}
#endif
/**
 * Appends the given text to the end of the document.  Does nothing if
 * the model is NULL or the string is NULL or empty.
 *
 * @param str the text to insert
 * @see #insert
 */
/*public*/ void JTextArea::append(QString str)
{
#if 0
 Document* doc = document();
 if (doc != NULL)
 {
//        try {
 // doc.insertString(doc.getLength(), str, NULL);
  QTextEdit::append(str);
//        } catch (BadLocationException e) {
//        }
 }
#endif
 if(str.endsWith('\n'))
  QTextEdit::append(str.replace('\n', ' '));
    else
 QTextEdit::append(str);
}
#if 0
/**
 * Replaces text from the indicated start to end position with the
 * new text specified.  Does nothing if the model is NULL.  Simply
 * does a delete if the new string is NULL or empty.
 *
 * @param str the text to use as the replacement
 * @param start the start position >= 0
 * @param end the end position >= start
 * @exception IllegalArgumentException  if part of the range is an
 *  invalid position in the model
 * @see #insert
 * @see #replaceRange
 */
/*public*/ void replaceRange(String str, int start, int end) {
    if (end < start) {
        throw new IllegalArgumentException("end before start");
    }
    Document doc = getDocument();
    if (doc != NULL) {
        try {
            if (doc instanceof AbstractDocument) {
                ((AbstractDocument)doc).replace(start, end - start, str,
                                                NULL);
            }
            else {
                doc.remove(start, end - start);
                doc.insertString(start, str, NULL);
            }
        } catch (BadLocationException e) {
            throw new IllegalArgumentException(e.getMessage());
        }
    }
}
#endif
/**
 * Returns the number of rows in the TextArea.
 *
 * @return the number of rows >= 0
 */
/*public*/ int JTextArea::getRows() {
    return rows;
}

/**
 * Sets the number of rows for this TextArea.  Calls invalidate() after
 * setting the new value.
 *
 * @param rows the number of rows >= 0
 * @exception IllegalArgumentException if rows is less than 0
 * @see #getRows
 * @beaninfo
 * description: the number of rows preferred for display
 */
/*public*/ void JTextArea::setRows(int rows) {
    int oldVal = this->rows;
    if (rows < 0) {
        throw new IllegalArgumentException("rows less than zero.");
    }
    if (rows != oldVal) {
        this->rows = rows;
//        invalidate();
    }
}

/**
 * Defines the meaning of the height of a row.  This defaults to
 * the height of the font.
 *
 * @return the height >= 1
 */
/*protected*/ int JTextArea::getRowHeight()
{
 if (rowHeight == 0)
 {
  QFontMetrics metrics = QFontMetrics(font());
  rowHeight = metrics.height();
 }
 return rowHeight;
}

/**
 * Returns the number of columns in the TextArea.
 *
 * @return number of columns >= 0
 */
/*public*/ int JTextArea::getColumns() {
    return columns;
}

/**
 * Sets the number of columns for this TextArea.  Does an invalidate()
 * after setting the new value.
 *
 * @param columns the number of columns >= 0
 * @exception IllegalArgumentException if columns is less than 0
 * @see #getColumns
 * @beaninfo
 * description: the number of columns preferred for display
 */
/*public*/ void JTextArea::setColumns(int columns) {
    int oldVal = this->columns;
    if (columns < 0) {
        throw new IllegalArgumentException("columns less than zero.");
    }
    if (columns != oldVal) {
        this->columns = columns;
//        invalidate();
    }
    setLineWidth(columns);
}

/**
 * Gets column width.
 * The meaning of what a column is can be considered a fairly weak
 * notion for some fonts.  This method is used to define the width
 * of a column.  By default this is defined to be the width of the
 * character <em>m</em> for the font used.  This method can be
 * redefined to be some alternative amount.
 *
 * @return the column width >= 1
 */
/*protected*/ int JTextArea::getColumnWidth() {
    if (columnWidth == 0) {
        QFontMetrics metrics = QFontMetrics(font());
        columnWidth = metrics.charWidth(QString("m"),0);
    }
    return columnWidth;
}
#if 0
// --- Component methods -----------------------------------------

/**
 * Returns the preferred size of the TextArea.  This is the
 * maximum of the size needed to display the text and the
 * size requested for the viewport.
 *
 * @return the size
 */
/*public*/ Dimension getPreferredSize() {
    Dimension d = super.getPreferredSize();
    d = (d == NULL) ? new Dimension(400,400) : d;
    Insets insets = getInsets();

    if (columns != 0) {
        d.width = Math.max(d.width, columns * getColumnWidth() +
                insets.left + insets.right);
    }
    if (rows != 0) {
        d.height = Math.max(d.height, rows * getRowHeight() +
                            insets.top + insets.bottom);
    }
    return d;
}

/**
 * Sets the current font.  This removes cached row height and column
 * width so the new font will be reflected, and calls revalidate().
 *
 * @param f the font to use as the current font
 */
/*public*/ void setFont(Font f) {
    super.setFont(f);
    rowHeight = 0;
    columnWidth = 0;
}


/**
 * Returns a string representation of this JTextArea. This method
 * is intended to be used only for debugging purposes, and the
 * content and format of the returned string may vary between
 * implementations. The returned string may be empty but may not
 * be <code>NULL</code>.
 *
 * @return  a string representation of this JTextArea.
 */
protected String paramString() {
    String wrapString = (wrap ?
                         "true" : "false");
    String wordString = (word ?
                         "true" : "false");

    return super.paramString() +
    ",colums=" + columns +
    ",columWidth=" + columnWidth +
    ",rows=" + rows +
    ",rowHeight=" + rowHeight +
    ",word=" + wordString +
    ",wrap=" + wrapString;
}

// --- Scrollable methods ----------------------------------------

/**
 * Returns true if a viewport should always force the width of this
 * Scrollable to match the width of the viewport.  This is implemented
 * to return true if the line wrapping policy is true, and false
 * if lines are not being wrapped.
 *
 * @return true if a viewport should force the Scrollables width
 * to match its own.
 */
/*public*/ boolean getScrollableTracksViewportWidth() {
    return (wrap) ? true : super.getScrollableTracksViewportWidth();
}

/**
 * Returns the preferred size of the viewport if this component
 * is embedded in a JScrollPane.  This uses the desired column
 * and row settings if they have been set, otherwise the superclass
 * behavior is used.
 *
 * @return The preferredSize of a JViewport whose view is this Scrollable.
 * @see JViewport#getPreferredSize
 */
/*public*/ Dimension getPreferredScrollableViewportSize() {
    Dimension size = super.getPreferredScrollableViewportSize();
    size = (size == NULL) ? new Dimension(400,400) : size;
    Insets insets = getInsets();

    size.width = (columns == 0) ? size.width :
            columns * getColumnWidth() + insets.left + insets.right;
    size.height = (rows == 0) ? size.height :
            rows * getRowHeight() + insets.top + insets.bottom;
    return size;
}

/**
 * Components that display logical rows or columns should compute
 * the scroll increment that will completely expose one new row
 * or column, depending on the value of orientation.  This is implemented
 * to use the values returned by the <code>getRowHeight</code> and
 * <code>getColumnWidth</code> methods.
 * <p>
 * Scrolling containers, like JScrollPane, will use this method
 * each time the user requests a unit scroll.
 *
 * @param visibleRect the view area visible within the viewport
 * @param orientation Either SwingConstants.VERTICAL or
 *   SwingConstants.HORIZONTAL.
 * @param direction Less than zero to scroll up/left,
 *   greater than zero for down/right.
 * @return The "unit" increment for scrolling in the specified direction
 * @exception IllegalArgumentException for an invalid orientation
 * @see JScrollBar#setUnitIncrement
 * @see #getRowHeight
 * @see #getColumnWidth
 */
/*public*/ int getScrollableUnitIncrement(Rectangle visibleRect, int orientation, int direction) {
    switch (orientation) {
    case SwingConstants.VERTICAL:
        return getRowHeight();
    case SwingConstants.HORIZONTAL:
        return getColumnWidth();
    default:
        throw new IllegalArgumentException("Invalid orientation: " + orientation);
    }
}

/**
 * See readObject() and writeObject() in JComponent for more
 * information about serialization in Swing.
 */
private void writeObject(ObjectOutputStream s) throws IOException {
    s.defaultWriteObject();
    if (getUIClassID().equals(uiClassID)) {
        byte count = JComponent.getWriteObjCounter(this);
        JComponent.setWriteObjCounter(this, --count);
        if (count == 0 && ui != NULL) {
            ui.installUI(this);
        }
    }
}

/////////////////
// Accessibility support
////////////////


/**
 * Gets the AccessibleContext associated with this JTextArea.
 * For JTextAreas, the AccessibleContext takes the form of an
 * AccessibleJTextArea.
 * A new AccessibleJTextArea instance is created if necessary.
 *
 * @return an AccessibleJTextArea that serves as the
 *         AccessibleContext of this JTextArea
 */
/*public*/ AccessibleContext getAccessibleContext() {
    if (accessibleContext == NULL) {
        accessibleContext = new AccessibleJTextArea();
    }
    return accessibleContext;
}

/**
 * This class implements accessibility support for the
 * <code>JTextArea</code> class.  It provides an implementation of the
 * Java Accessibility API appropriate to text area user-interface
 * elements.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 */
protected class AccessibleJTextArea extends AccessibleJTextComponent {

    /**
     * Gets the state set of this object.
     *
     * @return an instance of AccessibleStateSet describing the states
     * of the object
     * @see AccessibleStateSet
     */
    /*public*/ AccessibleStateSet getAccessibleStateSet() {
        AccessibleStateSet states = super.getAccessibleStateSet();
        states.add(AccessibleState.MULTI_LINE);
        return states;
    }
}
#endif
void JTextArea::setEditable(bool b)
{
 setEnabled(b);
}

/*public*/ void JTextArea::addFocusListener(FocusListener* l)
{
 //listeners.append(l);
 connect(this, SIGNAL(focusGained(FocusEvent*)), l, SLOT(focusGained(FocusEvent*)));

}

/*public*/ void JTextArea::removeFocusListener(FocusListener *l)
{
 //listeners.removeOne(l);
 disconnect(this, SIGNAL(focusLost(FocusEvent*)), l, SLOT(focusLost(FocusEvent*)));
}

/*protected*/ void JTextArea::focusInEvent(QFocusEvent* e)
{
 emit focusGained(new FocusEvent());
}

/*protected*/ void JTextArea::focusOutEvent(QFocusEvent* e)
{
 emit focusLost(new FocusEvent());
}
