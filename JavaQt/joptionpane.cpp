#include "joptionpane.h"
#include "jdialog.h"
#include "exceptions.h"
#include "logger.h"
#include <limits>
#include <QBoxLayout>
#include "propertychangeevent.h"
#include "jrootpane.h"
#include "optionpaneui.h"
#include <QLabel>
#include "jtextfield.h"
#include "flowlayout.h"
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include "vptr.h"
#include "component.h"
#include <QMainWindow>
#include <QListWidget>

//JOptionPane::JOptionPane(QWidget *parent) : QWidget(parent)
//{

//}

/**
 * <code>JOptionPane</code> makes it easy to pop up a standard dialog box that
 * prompts users for a value or informs them of something.
 * For information about using <code>JOptionPane</code>, see
 * <a
 href="https://docs.oracle.com/javase/tutorial/uiswing/components/dialog.html">How to Make Dialogs</a>,
 * a section in <em>The Java Tutorial</em>.
 *
 * <p>
 *
 * While the <code>JOptionPane</code>
 * class may appear complex because of the large number of methods, almost
 * all uses of this class are one-line calls to one of the static
 * <code>showXxxDialog</code> methods shown below:
 * <blockquote>
 *
 *
 * <table border=1 summary="Common JOptionPane method names and their descriptions">
 * <tr>
 *    <th>Method Name</th>
 *    <th>Description</th>
 * </tr>
 * <tr>
 *    <td>showConfirmDialog</td>
 *    <td>Asks a confirming question, like yes/no/cancel.</td>
 * </tr>
 * <tr>
 *    <td>showInputDialog</td>
 *    <td>Prompt for some input.</td>
 * </tr>
 * <tr>
 *   <td>showMessageDialog</td>
 *   <td>Tell the user about something that has happened.</td>
 * </tr>
 * <tr>
 *   <td>showOptionDialog</td>
 *   <td>The Grand Unification of the above three.</td>
 * </tr>
 * </table>
 *
 * </blockquote>
 * Each of these methods also comes in a <code>showInternalXXX</code>
 * flavor, which uses an internal frame to hold the dialog box (see
 * {@link JInternalFrame}).
 * Multiple convenience methods have also been defined -- overloaded
 * versions of the basic methods that use different parameter lists.
 * <p>
 * All dialogs are modal. Each <code>showXxxDialog</code> method blocks
 * the caller until the user's interaction is complete.
 *
 * <table cellspacing=6 cellpadding=4 border=0 style="float:right" summary="layout">
 * <tr>
 *  <td style="background-color:#FFe0d0" rowspan=2>icon</td>
 *  <td style="background-color:#FFe0d0">message</td>
 * </tr>
 * <tr>
 *  <td style="background-color:#FFe0d0">input value</td>
 * </tr>
 * <tr>
 *   <td style="background-color:#FFe0d0" colspan=2>option buttons</td>
 * </tr>
 * </table>
 *
 * The basic appearance of one of these dialog boxes is generally
 * similar to the picture at the right, although the various
 * look-and-feels are
 * ultimately responsible for the final result.  In particular, the
 * look-and-feels will adjust the layout to accommodate the option pane's
 * <code>ComponentOrientation</code> property.
 * <br style="clear:all">
 * <p>
 * <b>Parameters:</b><br>
 * The parameters to these methods follow consistent patterns:
 * <blockquote>
 * <dl compact>
 * <dt>parentComponent<dd>
 * Defines the <code>Component</code> that is to be the parent of this
 * dialog box.
 * It is used in two ways: the <code>Frame</code> that contains
 * it is used as the <code>Frame</code>
 * parent for the dialog box, and its screen coordinates are used in
 * the placement of the dialog box. In general, the dialog box is placed
 * just below the component. This parameter may be <code>NULL</code>,
 * in which case a default <code>Frame</code> is used as the parent,
 * and the dialog will be
 * centered on the screen (depending on the {@literal L&F}).
 * <dt><a name=message>message</a><dd>
 * A descriptive message to be placed in the dialog box.
 * In the most common usage, message is just a <code>String</code> or
 * <code>String</code> constant.
 * However, the type of this parameter is actually <code>Object</code>. Its
 * interpretation depends on its type:
 * <dl compact>
 * <dt>Object[]<dd>An array of objects is interpreted as a series of
 *                 messages (one per object) arranged in a vertical stack.
 *                 The interpretation is recursive -- each object in the
 *                 array is interpreted according to its type.
 * <dt>Component<dd>The <code>Component</code> is displayed in the dialog.
 * <dt>Icon<dd>The <code>Icon</code> is wrapped in a <code>JLabel</code>
 *               and displayed in the dialog.
 * <dt>others<dd>The object is converted to a <code>String</code> by calling
 *               its <code>toString</code> method. The result is wrapped in a
 *               <code>JLabel</code> and displayed.
 * </dl>
 * <dt>messageType<dd>Defines the style of the message. The Look and Feel
 * manager may lay out the dialog differently depending on this value, and
 * will often provide a default icon. The possible values are:
 * <ul>
 * <li><code>ERROR_MESSAGE</code>
 * <li><code>INFORMATION_MESSAGE</code>
 * <li><code>WARNING_MESSAGE</code>
 * <li><code>QUESTION_MESSAGE</code>
 * <li><code>PLAIN_MESSAGE</code>
 * </ul>
 * <dt>optionType<dd>Defines the set of option buttons that appear at
 * the bottom of the dialog box:
 * <ul>
 * <li><code>DEFAULT_OPTION</code>
 * <li><code>YES_NO_OPTION</code>
 * <li><code>YES_NO_CANCEL_OPTION</code>
 * <li><code>OK_CANCEL_OPTION</code>
 * </ul>
 * You aren't limited to this set of option buttons.  You can provide any
 * buttons you want using the options parameter.
 * <dt>options<dd>A more detailed description of the set of option buttons
 * that will appear at the bottom of the dialog box.
 * The usual value for the options parameter is an array of
 * <code>String</code>s. But
 * the parameter type is an array of <code>Objects</code>.
 * A button is created for each object depending on its type:
 * <dl compact>
 * <dt>Component<dd>The component is added to the button row directly.
 * <dt>Icon<dd>A <code>JButton</code> is created with this as its label.
 * <dt>other<dd>The <code>Object</code> is converted to a string using its
 *              <code>toString</code> method and the result is used to
 *              label a <code>JButton</code>.
 * </dl>
 * <dt>icon<dd>A decorative icon to be placed in the dialog box. A default
 * value for this is determined by the <code>messageType</code> parameter.
 * <dt>title<dd>The title for the dialog box.
 * <dt>initialValue<dd>The default selection (input value).
 * </dl>
 * </blockquote>
 * <p>
 * When the selection is changed, <code>setValue</code> is invoked,
 * which generates a <code>PropertyChangeEvent</code>.
 * <p>
 * If a <code>JOptionPane</code> has configured to all input
 * <code>setWantsInput</code>
 * the bound property <code>JOptionPane.INPUT_VALUE_PROPERTY</code>
 *  can also be listened
 * to, to determine when the user has input or selected a value.
 * <p>
 * When one of the <code>showXxxDialog</code> methods returns an integer,
 * the possible values are:
 * <ul>
 * <li><code>YES_OPTION</code>
 * <li><code>NO_OPTION</code>
 * <li><code>CANCEL_OPTION</code>
 * <li><code>OK_OPTION</code>
 * <li><code>CLOSED_OPTION</code>
 * </ul>
 * <b>Examples:</b>
 * <dl>
 * <dt>Show an error dialog that displays the message, 'alert':
 * <dd><code>
 * JOptionPane.showMessageDialog(NULL, "alert", "alert", JOptionPane.ERROR_MESSAGE);
 * </code>
 * <dt>Show an internal information dialog with the message, 'information':
 * <dd><pre>
 * JOptionPane.showInternalMessageDialog(frame, "information",
 *             "information", JOptionPane.INFORMATION_MESSAGE);
 * </pre>
 * <dt>Show an information panel with the options yes/no and message 'choose one':
 * <dd><pre>JOptionPane.showConfirmDialog(NULL,
 *             "choose one", "choose one", JOptionPane.YES_NO_OPTION);
 * </pre>
 * <dt>Show an internal information dialog with the options yes/no/cancel and
 * message 'please choose one' and title information:
 * <dd><pre>JOptionPane.showInternalConfirmDialog(frame,
 *             "please choose one", "information",
 *             JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE);
 * </pre>
 * <dt>Show a warning dialog with the options OK, CANCEL, title 'Warning', and
 * message 'Click OK to continue':
 * <dd><pre>
 * Object[] options = { "OK", "CANCEL" };
 * JOptionPane.showOptionDialog(NULL, "Click OK to continue", "Warning",
 *             JOptionPane.DEFAULT_OPTION, JOptionPane.WARNING_MESSAGE,
 *             NULL, options, options[0]);
 * </pre>
 * <dt>Show a dialog asking the user to type in a String:
 * <dd><code>
 * String inputValue = JOptionPane.showInputDialog("Please input a value");
 * </code>
 * <dt>Show a dialog asking the user to select a String:
 * <dd><pre>
 * Object[] possibleValues = { "First", "Second", "Third" };<br>
 * Object selectedValue = JOptionPane.showInputDialog(NULL,
 *             "Choose one", "Input",
 *             JOptionPane.INFORMATION_MESSAGE, NULL,
 *             possibleValues, possibleValues[0]);
 * </pre><p>
 * </dl>
 * <b>Direct Use:</b><br>
 * To create and use an <code>JOptionPane</code> directly, the
 * standard pattern is roughly as follows:
 * <pre>
 *     JOptionPane pane = new JOptionPane(<i>arguments</i>);
 *     pane.set<i>.Xxxx(...); // Configure</i>
 *     JDialog dialog = pane.createDialog(<i>parentComponent, title</i>);
 *     dialog.show();
 *     Object selectedValue = pane.getValue();
 *     if(selectedValue == NULL)
 *       return CLOSED_OPTION;
 *     <i>//If there is <b>not</b> an array of option buttons:</i>
 *     if(options == NULL) {
 *       if(selectedValue instanceof Integer)
 *          return ((Integer)selectedValue).intValue();
 *       return CLOSED_OPTION;
 *     }
 *     <i>//If there is an array of option buttons:</i>
 *     for(int counter = 0, maxCounter = options.length;
 *        counter &lt; maxCounter; counter++) {
 *        if(options[counter].equals(selectedValue))
 *        return counter;
 *     }
 *     return CLOSED_OPTION;
 * </pre>
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
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @see JInternalFrame
 *
 * @beaninfo
 *      attribute: isContainer true
 *    description: A component which implements standard dialog box controls.
 *
 * @author James Gosling
 * @author Scott Violet
 */
///*public*/ class JOptionPane extends JComponent implements Accessible
//{

/**
 * @see #getUIClassID
 * @see #readObject
 */
/*private*/ /*static*/ /*final*/ QString JOptionPane::uiClassID = "OptionPaneUI";

/**
 * Indicates that the user has not yet selected a value.
 */
/*public*/ /*static*/ /*final*/ QVariant      JOptionPane::UNINITIALIZED_VALUE = "uninitializedValue";


/** Bound property name for <code>icon</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::ICON_PROPERTY = "icon";
/** Bound property name for <code>message</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::MESSAGE_PROPERTY = "message";
/** Bound property name for <code>value</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::VALUE_PROPERTY = "value";
/** Bound property name for <code>option</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::OPTIONS_PROPERTY = "options";
/** Bound property name for <code>initialValue</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::INITIAL_VALUE_PROPERTY = "initialValue";
/** Bound property name for <code>type</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::MESSAGE_TYPE_PROPERTY = "messageType";
/** Bound property name for <code>optionType</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::OPTION_TYPE_PROPERTY = "optionType";
/** Bound property name for <code>selectionValues</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::SELECTION_VALUES_PROPERTY = "selectionValues";
/** Bound property name for <code>initialSelectionValue</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::INITIAL_SELECTION_VALUE_PROPERTY = "initialSelectionValue";
/** Bound property name for <code>inputValue</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::INPUT_VALUE_PROPERTY = "inputValue";
/** Bound property name for <code>wantsInput</code>. */
/*public*/ /*static*/ /*final*/ QString      JOptionPane::WANTS_INPUT_PROPERTY = "wantsInput";




/**
 * Shows a question-message dialog requesting input from the user. The
 * dialog uses the default frame, which usually means it is centered on
 * the screen.
 *
 * @param message the <code>Object</code> to display
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ QString JOptionPane::showInputDialog(QVariant message)
    //throws HeadlessException
{
    return showInputDialog(NULL, message);
}

/**
 * Shows a question-message dialog requesting input from the user, with
 * the input value initialized to <code>initialSelectionValue</code>. The
 * dialog uses the default frame, which usually means it is centered on
 * the screen.
 *
 * @param message the <code>Object</code> to display
 * @param initialSelectionValue the value used to initialize the input
 *                 field
 * @since 1.4
 */
/*public*/ /*static*/ QString JOptionPane::showInputDialog(QVariant message, QVariant initialSelectionValue) {
    return showInputDialog(NULL, message, initialSelectionValue);
}

/**
 * Shows a question-message dialog requesting input from the user
 * parented to <code>parentComponent</code>.
 * The dialog is displayed on top of the <code>Component</code>'s
 * frame, and is usually positioned below the <code>Component</code>.
 *
 * @param parentComponent  the parent <code>Component</code> for the
 *          dialog
 * @param message  the <code>Object</code> to display
 * @exception HeadlessException if
 *    <code>GraphicsEnvironment.isHeadless</code> returns
 *    <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ QString JOptionPane::showInputDialog(QWidget* parentComponent,
    QVariant message) //throws HeadlessException
{
    return showInputDialog(parentComponent, message, /*UIManager.getString*/QString(
        "OptionPane.inputDialogTitle"/*, parentComponent*/), QUESTION_MESSAGE);
}

/**
 * Shows a question-message dialog requesting input from the user and
 * parented to <code>parentComponent</code>. The input value will be
 * initialized to <code>initialSelectionValue</code>.
 * The dialog is displayed on top of the <code>Component</code>'s
 * frame, and is usually positioned below the <code>Component</code>.
 *
 * @param parentComponent  the parent <code>Component</code> for the
 *          dialog
 * @param message the <code>Object</code> to display
 * @param initialSelectionValue the value used to initialize the input
 *                 field
 * @since 1.4
 */
/*public*/ /*static*/ QString JOptionPane::showInputDialog(QWidget* parentComponent, QVariant message, QVariant initialSelectionValue)
{
    return showInputDialog(parentComponent, message,
                  /*UIManager.getString*/QString("OptionPane.inputDialogTitle"/*,
                  parentComponent*/), QUESTION_MESSAGE, QIcon(), QList<QVariant>(),
                  initialSelectionValue).toString();
}

/**
 * Shows a dialog requesting input from the user parented to
 * <code>parentComponent</code> with the dialog having the title
 * <code>title</code> and message type <code>messageType</code>.
 *
 * @param parentComponent  the parent <code>Component</code> for the
 *                  dialog
 * @param message  the <code>Object</code> to display
 * @param title    the <code>String</code> to display in the dialog
 *                  title bar
 * @param messageType the type of message that is to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ QString JOptionPane::showInputDialog(QWidget* parentComponent,
    QVariant message, QString title, int messageType)
    //throws HeadlessException
{
    return showInputDialog(parentComponent, message, title,
                                   messageType, QIcon(), QList<QVariant>(), QVariant()).toString();
}

/**
 * Prompts the user for input in a blocking dialog where the
 * initial selection, possible selections, and all other options can
 * be specified. The user will able to choose from
 * <code>selectionValues</code>, where <code>NULL</code> implies the
 * user can input
 * whatever they wish, usually by means of a <code>JTextField</code>.
 * <code>initialSelectionValue</code> is the initial value to prompt
 * the user with. It is up to the UI to decide how best to represent
 * the <code>selectionValues</code>, but usually a
 * <code>JComboBox</code>, <code>JList</code>, or
 * <code>JTextField</code> will be used.
 *
 * @param parentComponent  the parent <code>Component</code> for the
 *                  dialog
 * @param message  the <code>Object</code> to display
 * @param title    the <code>String</code> to display in the
 *                  dialog title bar
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param icon     the <code>Icon</code> image to display
 * @param selectionValues an array of <code>Object</code>s that
 *                  gives the possible selections
 * @param initialSelectionValue the value used to initialize the input
 *                 field
 * @return user's input, or <code>NULL</code> meaning the user
 *                  canceled the input
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ QVariant JOptionPane::showInputDialog(QWidget* parentComponent,
    QVariant message, QString title, int messageType, QIcon icon,
    QList<QVariant> selectionValues, QVariant initialSelectionValue)
    //throws HeadlessException
{
    JOptionPane*    pane = new JOptionPane(message, messageType,
                                          OK_CANCEL_OPTION, icon,
                                          selectionValues,initialSelectionValue, parentComponent);

    pane->setWantsInput(true);
    if(selectionValues.count() == 1 && VPtr<QValidator>::asPtr(selectionValues.at(0)))
     pane->setValidator(VPtr<QValidator>::asPtr(selectionValues.at(0)));
    pane->setSelectionValues(selectionValues);
    pane->setInitialSelectionValue(initialSelectionValue);
//    pane->setComponentOrientation(((parentComponent == NULL) ?
//        getRootFrame() : parentComponent).getComponentOrientation());

    int style = styleFromMessageType(messageType);
    JDialog* dialog = pane->createDialog(parentComponent, title, style,0);

    pane->selectInitialValue();
    dialog->show();
    int rslt = dialog->exec();
    //dialog->/*dispose*/close();
//    if(rslt == QDialog::Rejected)
    if(rslt == JOptionPane::CANCEL_OPTION)
        return QVariant();

    QVariant value = pane->getInputValue();

    if (value == UNINITIALIZED_VALUE) {
        return QVariant();
    }
    return value;
}

/**
 * Brings up an information-message dialog titled "Message".
 *
 * @param parentComponent determines the <code>Frame</code> in
 *          which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ void JOptionPane::showMessageDialog(QWidget* parentComponent,
    QVariant message) //throws HeadlessException
{
    showMessageDialog(parentComponent, message, /*UIManager.getString*/QString(
                "Message"/*, parentComponent*/),
                INFORMATION_MESSAGE);
}

/**
 * Brings up a dialog that displays a message using a default
 * icon determined by the <code>messageType</code> parameter.
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ void JOptionPane::showMessageDialog(QWidget* parentComponent,
    QVariant message, QString title, int messageType)
    //throws HeadlessException
{
    showMessageDialog(parentComponent, message, title, messageType, QIcon());
}

/**
 * Brings up a dialog displaying a message, specifying all parameters.
 *
 * @param parentComponent determines the <code>Frame</code> in which the
 *                  dialog is displayed; if <code>NULL</code>,
 *                  or if the <code>parentComponent</code> has no
 *                  <code>Frame</code>, a
 *                  default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param icon      an icon to display in the dialog that helps the user
 *                  identify the kind of message that is being displayed
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ void JOptionPane::showMessageDialog(QWidget* parentComponent,
    QVariant message, QString title, int messageType, QIcon icon)
    //throws HeadlessException
{
    showOptionDialog(parentComponent, message, title, DEFAULT_OPTION,
                     messageType, icon, QList<QVariant>(), QVariant());
}

#if 1
/**
 * Brings up a dialog with the options <i>Yes</i>,
 * <i>No</i> and <i>Cancel</i>; with the
 * title, <b>Select an Option</b>.
 *
 * @param parentComponent determines the <code>Frame</code> in which the
 *                  dialog is displayed; if <code>NULL</code>,
 *                  or if the <code>parentComponent</code> has no
 *                  <code>Frame</code>, a
 *                  default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @return an integer indicating the option selected by the user
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ int JOptionPane::showConfirmDialog(QWidget* parentComponent,
    QVariant message) throw (HeadlessException)
{
    return showConfirmDialog(parentComponent, message,
                             /*UIManager.getString*/("OptionPane.titleText"),
                             YES_NO_CANCEL_OPTION);
}

/**
 * Brings up a dialog where the number of choices is determined
 * by the <code>optionType</code> parameter.
 *
 * @param parentComponent determines the <code>Frame</code> in which the
 *                  dialog is displayed; if <code>NULL</code>,
 *                  or if the <code>parentComponent</code> has no
 *                  <code>Frame</code>, a
 *                  default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param optionType an int designating the options available on the dialog:
 *                  <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  or <code>OK_CANCEL_OPTION</code>
 * @return an int indicating the option selected by the user
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ int JOptionPane::showConfirmDialog(QWidget* parentComponent,
    QVariant message, QString title, int optionType)
    throw (HeadlessException) {
    return showConfirmDialog(parentComponent, message, title, optionType,
                             QUESTION_MESSAGE);
}

/**
 * Brings up a dialog where the number of choices is determined
 * by the <code>optionType</code> parameter, where the
 * <code>messageType</code>
 * parameter determines the icon to display.
 * The <code>messageType</code> parameter is primarily used to supply
 * a default icon from the Look and Feel.
 *
 * @param parentComponent determines the <code>Frame</code> in
 *                  which the dialog is displayed; if <code>NULL</code>,
 *                  or if the <code>parentComponent</code> has no
 *                  <code>Frame</code>, a
 *                  default <code>Frame</code> is used.
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param optionType an integer designating the options available
 *                   on the dialog: <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  or <code>OK_CANCEL_OPTION</code>
 * @param messageType an integer designating the kind of message this is;
 *                  primarily used to determine the icon from the pluggable
 *                  Look and Feel: <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @return an integer indicating the option selected by the user
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ int JOptionPane::showConfirmDialog(QWidget* parentComponent,
    QVariant message, QString title, int optionType, int messageType)
    throw (HeadlessException) {
    return showConfirmDialog(parentComponent, message, title, optionType,
                            messageType, QIcon());
}

/**
 * Brings up a dialog with a specified icon, where the number of
 * choices is determined by the <code>optionType</code> parameter.
 * The <code>messageType</code> parameter is primarily used to supply
 * a default icon from the look and feel.
 *
 * @param parentComponent determines the <code>Frame</code> in which the
 *                  dialog is displayed; if <code>NULL</code>,
 *                  or if the <code>parentComponent</code> has no
 *                  <code>Frame</code>, a
 *                  default <code>Frame</code> is used
 * @param message   the Object to display
 * @param title     the title string for the dialog
 * @param optionType an int designating the options available on the dialog:
 *                  <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  or <code>OK_CANCEL_OPTION</code>
 * @param messageType an int designating the kind of message this is,
 *                  primarily used to determine the icon from the pluggable
 *                  Look and Feel: <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param icon      the icon to display in the dialog
 * @return an int indicating the option selected by the user
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ int JOptionPane::showConfirmDialog(QWidget* parentComponent,
    QVariant message, QString title, int optionType,
    int messageType, QIcon icon) throw (HeadlessException) {
    return showOptionDialog(parentComponent, message, title, optionType,
                            messageType, icon, QList<QVariant>(), QVariant());
}
#endif
/**
 * Brings up a dialog with a specified icon, where the initial
 * choice is determined by the <code>initialValue</code> parameter and
 * the number of choices is determined by the <code>optionType</code>
 * parameter.
 * <p>
 * If <code>optionType</code> is <code>YES_NO_OPTION</code>,
 * or <code>YES_NO_CANCEL_OPTION</code>
 * and the <code>options</code> parameter is <code>NULL</code>,
 * then the options are
 * supplied by the look and feel.
 * <p>
 * The <code>messageType</code> parameter is primarily used to supply
 * a default icon from the look and feel.
 *
 * @param parentComponent determines the <code>Frame</code>
 *                  in which the dialog is displayed;  if
 *                  <code>NULL</code>, or if the
 *                  <code>parentComponent</code> has no
 *                  <code>Frame</code>, a
 *                  default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param optionType an integer designating the options available on the
 *                  dialog: <code>DEFAULT_OPTION</code>,
 *                  <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  or <code>OK_CANCEL_OPTION</code>
 * @param messageType an integer designating the kind of message this is,
 *                  primarily used to determine the icon from the
 *                  pluggable Look and Feel: <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param icon      the icon to display in the dialog
 * @param options   an array of objects indicating the possible choices
 *                  the user can make; if the objects are components, they
 *                  are rendered properly; non-<code>String</code>
 *                  objects are
 *                  rendered using their <code>toString</code> methods;
 *                  if this parameter is <code>NULL</code>,
 *                  the options are determined by the Look and Feel
 * @param initialValue the object that represents the default selection
 *                  for the dialog; only meaningful if <code>options</code>
 *                  is used; can be <code>NULL</code>
 * @return an integer indicating the option chosen by the user,
 *                  or <code>CLOSED_OPTION</code> if the user closed
 *                  the dialog
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ /*static*/ int JOptionPane::showOptionDialog(QWidget* parentComponent,
    QVariant message, QString title, int optionType, int messageType,
    QIcon icon, QList<QVariant> options, QVariant initialValue)
    //throws HeadlessException
{
 JOptionPane* pane = new JOptionPane(message, messageType,
                                     optionType, icon,
                                     options, initialValue,parentComponent);

 pane->setInitialValue(initialValue);
//    pane->setComponentOrientation(((parentComponent == NULL) ?
//        getRootFrame() : parentComponent).getComponentOrientation());

 int style = styleFromMessageType(messageType);
 JDialog* dialog = pane->createDialog(parentComponent, title, style, optionType);
 QWidget* w = VPtr<QListWidget>::asPtr(message);
 if(w)
 {
  QListWidget* list = w->findChild<QListWidget*>();
  if(list)
  {
   connect(list, &QListWidget::doubleClicked, [=]{
    dialog->accept();
   });
  }
 }
 pane->selectInitialValue();
#if 1
 //dialog->show();
 int rslt = dialog->exec();
 //dialog->/*dispose*/close();
if(options.count() >0)
 return rslt;
 QVariant selectedValue = pane->getValue();

 if(selectedValue == QVariant())
     return CLOSED_OPTION;
 if(selectedValue == "uninitializedValue")
  return rslt;
 if(options == QList<QVariant>())
 {
     //if(selectedValue instanceof Integer)
  if(selectedValue.type() == QVariant::Int)
         return (selectedValue).toInt();
     return CLOSED_OPTION;
 }
 for(int counter = 0, maxCounter = options.length();
     counter < maxCounter; counter++) {
     if(options[counter] == (selectedValue))
         return counter;
 }
 return CLOSED_OPTION;
#else
 dialog->show();

// if (pane->getValue() instanceof Integer)
//   return ((Integer) pane.getValue()).intValue();
 if(pane->getValue().canConvert(QMetaType::Int))
    return pane->getValue().toInt();
 return -1;
#endif
}
#if 1
/**
 * Creates and returns a new <code>JDialog</code> wrapping
 * <code>this</code> centered on the <code>parentComponent</code>
 * in the <code>parentComponent</code>'s frame.
 * <code>title</code> is the title of the returned dialog.
 * The returned <code>JDialog</code> will not be resizable by the
 * user, however programs can invoke <code>setResizable</code> on
 * the <code>JDialog</code> instance to change this property.
 * The returned <code>JDialog</code> will be set up such that
 * once it is closed, or the user clicks on one of the buttons,
 * the optionpane's value property will be set accordingly and
 * the dialog will be closed.  Each time the dialog is made visible,
 * it will reset the option pane's value property to
 * <code>JOptionPane.UNINITIALIZED_VALUE</code> to ensure the
 * user's subsequent action closes the dialog properly.
 *
 * @param parentComponent determines the frame in which the dialog
 *          is displayed; if the <code>parentComponent</code> has
 *          no <code>Frame</code>, a default <code>Frame</code> is used
 * @param title     the title string for the dialog
 * @return a new <code>JDialog</code> containing this instance
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ JDialog* JOptionPane::createDialog(QWidget* parentComponent, QString title)
    /*throw HeadlessException*/ {
    int style = styleFromMessageType(getMessageType());
    return createDialog(parentComponent, title, style, 0);
}

/**
 * Creates and returns a new parentless <code>JDialog</code>
 * with the specified title.
 * The returned <code>JDialog</code> will not be resizable by the
 * user, however programs can invoke <code>setResizable</code> on
 * the <code>JDialog</code> instance to change this property.
 * The returned <code>JDialog</code> will be set up such that
 * once it is closed, or the user clicks on one of the buttons,
 * the optionpane's value property will be set accordingly and
 * the dialog will be closed.  Each time the dialog is made visible,
 * it will reset the option pane's value property to
 * <code>JOptionPane.UNINITIALIZED_VALUE</code> to ensure the
 * user's subsequent action closes the dialog properly.
 *
 * @param title     the title string for the dialog
 * @return a new <code>JDialog</code> containing this instance
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 * @since 1.6
 */
/*public*/ JDialog* JOptionPane::createDialog(QString title) /*throws HeadlessException */{
    int style = styleFromMessageType(getMessageType());
    JDialog* dialog = new JDialog( NULL, title, true);
    initDialog(dialog, style, NULL);
    return dialog;
}
#endif
/*private*/ JDialog* JOptionPane::createDialog(QWidget* parentComponent, QString title,
        int style, int optionType)
        //throws HeadlessException
{

    /*final*/ JDialog* dialog;
 setObjectName("JOptionPaneDialog");

   // Window window = JOptionPane::getWindowForComponent(parentComponent);
    QWidget* window;
    if(parentComponent == NULL)
     window = QApplication::desktop()->window();
    else
    window = parentComponent->window();
#if 0
    if (window instanceof Frame)
    {
        dialog = new JDialog((Frame)window, title, true);
    } else {
        dialog = new JDialog((Dialog)window, title, true);
    }
    if (window instanceof SwingUtilities.SharedOwnerFrame) {
        WindowListener ownerShutdownListener =
                SwingUtilities.getSharedOwnerFrameShutdownListener();
        dialog.addWindowListener(ownerShutdownListener);
    }
#endif
    setOptionType(optionType);
    dialog = new JDialog(window, title, true);
    initDialog(dialog, style, parentComponent);
    return dialog;
}

/*private*/ void JOptionPane::initDialog(/*final*/ JDialog* dialog, int /*style*/, QWidget* parentComponent) {
 dialog->setModal(true);
//    dialog.setComponentOrientation(this->getComponentOrientation());
    QWidget* contentPane = dialog->getContentPane();
//QVBoxLayout* contentPaneLayout;
//    contentPane->setLayout(contenPaneLayout = new /*BorderLayout()*/QVBoxLayout);
    ((QVBoxLayout*)contentPane->layout())->addWidget(layoutPane(dialog), /*BorderLayout.CENTER*/0, Qt::AlignCenter);
//    dialog.setResizable(false);
//    if (JDialog.isDefaultLookAndFeelDecorated()) {
//        boolean supportsWindowDecorations =
//          UIManager.getLookAndFeel().getSupportsWindowDecorations();
//        if (supportsWindowDecorations) {
//            dialog.setUndecorated(true);
//            getRootPane().setWindowDecorationStyle(style);
//        }
//    }
    dialog->adjustSize();
    dialog->setLocationRelativeTo(parentComponent);

//    /*final*/ PropertyChangeListener listener = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent event) {
//            // Let the defaultCloseOperation handle the closing
//            // if the user closed the window without selecting a button
//            // (newValue = NULL in that case).  Otherwise, close the dialog.
//            if (dialog.isVisible() && event.getSource() == JOptionPane.this &&
//                    (event.getPropertyName().equals(VALUE_PROPERTY)) &&
//                    event.getNewValue() != NULL &&
//                    event.getNewValue() != JOptionPane.UNINITIALIZED_VALUE) {
//                dialog.setVisible(false);
//            }
//        }
//    };

//    WindowAdapter adapter = new WindowAdapter() {
//        private boolean gotFocus = false;
//        /*public*/ void windowClosing(WindowEvent we) {
//            setValue(NULL);
//        }

//        /*public*/ void windowClosed(WindowEvent e) {
//            removePropertyChangeListener(listener);
//            dialog.getContentPane().removeAll();
//        }

//        /*public*/ void windowGainedFocus(WindowEvent we) {
//            // Once window gets focus, set initial focus
//            if (!gotFocus) {
//                selectInitialValue();
//                gotFocus = true;
//            }
//        }
//    };
//    dialog.addWindowListener(adapter);
//    dialog.addWindowFocusListener(adapter);
//    dialog.addComponentListener(new ComponentAdapter() {
//        /*public*/ void componentShown(ComponentEvent ce) {
//            // reset value to ensure closing works properly
//            setValue(JOptionPane.UNINITIALIZED_VALUE);
//        }
//    });

    //addPropertyChangeListener(listener);
}
/*public*/ void JOptionPane::propertyChange(PropertyChangeEvent* event) {
    // Let the defaultCloseOperation handle the closing
    // if the user closed the window without selecting a button
    // (newValue = NULL in that case).  Otherwise, close the dialog.
#if 1
    if (_dialog->isVisible() && event->getSource() == this &&
            (event->getPropertyName() == VALUE_PROPERTY) &&
            event->getNewValue() != QVariant() &&
            event->getNewValue() != JOptionPane::UNINITIALIZED_VALUE) {
        _dialog->setVisible(false);
    }
#endif
}

#if 0
/**
 * Brings up an internal confirmation dialog panel. The dialog
 * is a information-message dialog titled "Message".
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the object to display
 */
/*public*/ static void showInternalMessageDialog(Component parentComponent,
                                             Object message) {
    showInternalMessageDialog(parentComponent, message, UIManager.
                             getString("OptionPane.messageDialogTitle",
                             parentComponent), INFORMATION_MESSAGE);
}

/**
 * Brings up an internal dialog panel that displays a message
 * using a default icon determined by the <code>messageType</code>
 * parameter.
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 */
/*public*/ static void showInternalMessageDialog(Component parentComponent,
                                             Object message, QString title,
                                             int messageType) {
    showInternalMessageDialog(parentComponent, message, title, messageType,NULL);
}

/**
 * Brings up an internal dialog panel displaying a message,
 * specifying all parameters.
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @param title     the title string for the dialog
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param icon      an icon to display in the dialog that helps the user
 *                  identify the kind of message that is being displayed
 */
/*public*/ static void showInternalMessageDialog(Component parentComponent,
                                     Object message,
                                     QString title, int messageType,
                                     Icon icon){
    showInternalOptionDialog(parentComponent, message, title, DEFAULT_OPTION,
                             messageType, icon, NULL, NULL);
}

/**
 * Brings up an internal dialog panel with the options <i>Yes</i>, <i>No</i>
 * and <i>Cancel</i>; with the title, <b>Select an Option</b>.
 *
 * @param parentComponent determines the <code>Frame</code> in
 *          which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the <code>Object</code> to display
 * @return an integer indicating the option selected by the user
 */
/*public*/ static int showInternalConfirmDialog(Component parentComponent,
                                            Object message) {
    return showInternalConfirmDialog(parentComponent, message,
                             UIManager.getString("OptionPane.titleText"),
                             YES_NO_CANCEL_OPTION);
}

/**
 * Brings up a internal dialog panel where the number of choices
 * is determined by the <code>optionType</code> parameter.
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the object to display in the dialog; a
 *          <code>Component</code> object is rendered as a
 *          <code>Component</code>; a <code>String</code>
 *          object is rendered as a string; other objects
 *          are converted to a <code>String</code> using the
 *          <code>toString</code> method
 * @param title     the title string for the dialog
 * @param optionType an integer designating the options
 *          available on the dialog: <code>YES_NO_OPTION</code>,
 *          or <code>YES_NO_CANCEL_OPTION</code>
 * @return an integer indicating the option selected by the user
 */
/*public*/ static int showInternalConfirmDialog(Component parentComponent,
                                            Object message, QString title,
                                            int optionType) {
    return showInternalConfirmDialog(parentComponent, message, title, optionType,
                                     QUESTION_MESSAGE);
}

/**
 * Brings up an internal dialog panel where the number of choices
 * is determined by the <code>optionType</code> parameter, where
 * the <code>messageType</code> parameter determines the icon to display.
 * The <code>messageType</code> parameter is primarily used to supply
 * a default icon from the Look and Feel.
 *
 * @param parentComponent determines the <code>Frame</code> in
 *          which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the object to display in the dialog; a
 *          <code>Component</code> object is rendered as a
 *          <code>Component</code>; a <code>String</code>
 *          object is rendered as a string; other objects are
 *          converted to a <code>String</code> using the
 *          <code>toString</code> method
 * @param title     the title string for the dialog
 * @param optionType an integer designating the options
 *          available on the dialog:
 *          <code>YES_NO_OPTION</code>, or <code>YES_NO_CANCEL_OPTION</code>
 * @param messageType an integer designating the kind of message this is,
 *          primarily used to determine the icon from the
 *          pluggable Look and Feel: <code>ERROR_MESSAGE</code>,
 *          <code>INFORMATION_MESSAGE</code>,
 *          <code>WARNING_MESSAGE</code>, <code>QUESTION_MESSAGE</code>,
 *          or <code>PLAIN_MESSAGE</code>
 * @return an integer indicating the option selected by the user
 */
/*public*/ static int showInternalConfirmDialog(Component parentComponent,
                                    Object message,
                                    QString title, int optionType,
                                    int messageType) {
    return showInternalConfirmDialog(parentComponent, message, title, optionType,
                                     messageType, NULL);
}

/**
 * Brings up an internal dialog panel with a specified icon, where
 * the number of choices is determined by the <code>optionType</code>
 * parameter.
 * The <code>messageType</code> parameter is primarily used to supply
 * a default icon from the look and feel.
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the parentComponent has no Frame, a
 *          default <code>Frame</code> is used
 * @param message   the object to display in the dialog; a
 *          <code>Component</code> object is rendered as a
 *          <code>Component</code>; a <code>String</code>
 *          object is rendered as a string; other objects are
 *          converted to a <code>String</code> using the
 *          <code>toString</code> method
 * @param title     the title string for the dialog
 * @param optionType an integer designating the options available
 *          on the dialog:
 *          <code>YES_NO_OPTION</code>, or
 *          <code>YES_NO_CANCEL_OPTION</code>.
 * @param messageType an integer designating the kind of message this is,
 *          primarily used to determine the icon from the pluggable
 *          Look and Feel: <code>ERROR_MESSAGE</code>,
 *          <code>INFORMATION_MESSAGE</code>,
 *          <code>WARNING_MESSAGE</code>, <code>QUESTION_MESSAGE</code>,
 *          or <code>PLAIN_MESSAGE</code>
 * @param icon      the icon to display in the dialog
 * @return an integer indicating the option selected by the user
 */
/*public*/ static int showInternalConfirmDialog(Component parentComponent,
                                    Object message,
                                    QString title, int optionType,
                                    int messageType, Icon icon) {
    return showInternalOptionDialog(parentComponent, message, title, optionType,
                                    messageType, icon, NULL, NULL);
}
#endif
/**
 * Brings up an internal dialog panel with a specified icon, where
 * the initial choice is determined by the <code>initialValue</code>
 * parameter and the number of choices is determined by the
 * <code>optionType</code> parameter.
 * <p>
 * If <code>optionType</code> is <code>YES_NO_OPTION</code>, or
 * <code>YES_NO_CANCEL_OPTION</code>
 * and the <code>options</code> parameter is <code>NULL</code>,
 * then the options are supplied by the Look and Feel.
 * <p>
 * The <code>messageType</code> parameter is primarily used to supply
 * a default icon from the look and feel.
 *
 * @param parentComponent determines the <code>Frame</code>
 *          in which the dialog is displayed; if <code>NULL</code>,
 *          or if the <code>parentComponent</code> has no
 *          <code>Frame</code>, a default <code>Frame</code> is used
 * @param message   the object to display in the dialog; a
 *          <code>Component</code> object is rendered as a
 *          <code>Component</code>; a <code>String</code>
 *          object is rendered as a string. Other objects are
 *          converted to a <code>String</code> using the
 *          <code>toString</code> method
 * @param title     the title string for the dialog
 * @param optionType an integer designating the options available
 *          on the dialog: <code>YES_NO_OPTION</code>,
 *          or <code>YES_NO_CANCEL_OPTION</code>
 * @param messageType an integer designating the kind of message this is;
 *          primarily used to determine the icon from the
 *          pluggable Look and Feel: <code>ERROR_MESSAGE</code>,
 *          <code>INFORMATION_MESSAGE</code>,
 *          <code>WARNING_MESSAGE</code>, <code>QUESTION_MESSAGE</code>,
 *          or <code>PLAIN_MESSAGE</code>
 * @param icon      the icon to display in the dialog
 * @param options   an array of objects indicating the possible choices
 *          the user can make; if the objects are components, they
 *          are rendered properly; non-<code>String</code>
 *          objects are rendered using their <code>toString</code>
 *          methods; if this parameter is <code>NULL</code>,
 *          the options are determined by the Look and Feel
 * @param initialValue the object that represents the default selection
 *          for the dialog; only meaningful if <code>options</code>
 *          is used; can be <code>NULL</code>
 * @return an integer indicating the option chosen by the user,
 *          or <code>CLOSED_OPTION</code> if the user closed the Dialog
 */
/*public*/ /*static*/ int JOptionPane::showInternalOptionDialog(Component* parentComponent,
                                   QVariant message,
                                   QString title, int /*optionType*/,
                                   int messageType, QIcon icon,
                                   QVariantList options, QVariant initialValue)
{
 QWidget* internalWidget = new QWidget();
 QVBoxLayout* layout = new QVBoxLayout(internalWidget);
 QLabel* label = new QLabel(message.toString());
 layout->addWidget(label);
 QListWidget* widget = new QListWidget();
 layout->addWidget(widget);
 foreach (QVariant option, options)
 {
   widget->addItem(new QListWidgetItem(option.toString()));
 }

    JOptionPane* pane = new JOptionPane(VPtr<QWidget>::asQVariant(internalWidget), messageType,
            OK_CANCEL_OPTION, icon, options, initialValue);
//    pane.putClientProperty(PopupFactory_FORCE_HEAVYWEIGHT_POPUP,
//            Boolean.TRUE);
//    Component fo = KeyboardFocusManager.getCurrentKeyboardFocusManager().
//            getFocusOwner();

    pane->setInitialValue(initialValue);
#if 0
    JInternalFrame dialog =
        pane.createInternalFrame(parentComponent, title);
    pane.selectInitialValue();
    dialog.setVisible(true);

    /* Since all input will be blocked until this dialog is dismissed,
     * make sure its parent containers are visible first (this component
     * is tested below).  This is necessary for JApplets, because
     * because an applet normally isn't made visible until after its
     * start() method returns -- if this method is called from start(),
     * the applet will appear to hang while an invisible modal frame
     * waits for input.
     */
    if (dialog.isVisible() && !dialog.isShowing()) {
        Container parent = dialog.getParent();
        while (parent != NULL) {
            if (parent.isVisible() == false) {
                parent.setVisible(true);
            }
            parent = parent.getParent();
        }
    }

    // Use reflection to get Container.startLWModal.
    try {
        Method method = AccessController.doPrivileged(new ModalPrivilegedAction(
                Container.class, "startLWModal"));
        if (method != NULL) {
            method.invoke(dialog, (Object[])NULL);
        }
    } catch (IllegalAccessException ex) {
    } catch (IllegalArgumentException ex) {
    } catch (InvocationTargetException ex) {
    }

    if (parentComponent instanceof JInternalFrame) {
        try {
            ((JInternalFrame)parentComponent).setSelected(true);
        } catch (java.beans.PropertyVetoException e) {
        }
    }

    Object selectedValue = pane.getValue();

    if (fo != NULL && fo.isShowing()) {
        fo.requestFocus();
    }
    if (selectedValue == NULL) {
        return CLOSED_OPTION;
    }
    if (options == NULL) {
        if (selectedValue instanceof Integer) {
            return ((Integer)selectedValue).intValue();
        }
        return CLOSED_OPTION;
    }
    for(int counter = 0, maxCounter = options.length;
        counter < maxCounter; counter++) {
        if (options[counter].equals(selectedValue)) {
            return counter;
        }
    }
    return CLOSED_OPTION;
#else
    JDialog* dialog = new JDialog(parentComponent, title, true);
    QWidget* p =pane->layoutPane(dialog);
    dialog->getContentPane()->setLayout(new QVBoxLayout());
    dialog->layout()->addWidget(p);
    dialog->show();
#endif
    return dialog->result();
}
#if 0
/**
 * Shows an internal question-message dialog requesting input from
 * the user parented to <code>parentComponent</code>. The dialog
 * is displayed in the <code>Component</code>'s frame,
 * and is usually positioned below the <code>Component</code>.
 *
 * @param parentComponent  the parent <code>Component</code>
 *          for the dialog
 * @param message  the <code>Object</code> to display
 */
/*public*/ static QString showInternalInputDialog(Component parentComponent,
                                             Object message) {
    return showInternalInputDialog(parentComponent, message, UIManager.
           getString("OptionPane.inputDialogTitle", parentComponent),
           QUESTION_MESSAGE);
}

/**
 * Shows an internal dialog requesting input from the user parented
 * to <code>parentComponent</code> with the dialog having the title
 * <code>title</code> and message type <code>messageType</code>.
 *
 * @param parentComponent the parent <code>Component</code> for the dialog
 * @param message  the <code>Object</code> to display
 * @param title    the <code>String</code> to display in the
 *          dialog title bar
 * @param messageType the type of message that is to be displayed:
 *                    ERROR_MESSAGE, INFORMATION_MESSAGE, WARNING_MESSAGE,
 *                    QUESTION_MESSAGE, or PLAIN_MESSAGE
 */
/*public*/ static QString showInternalInputDialog(Component parentComponent,
                         Object message, QString title, int messageType) {
    return (String)showInternalInputDialog(parentComponent, message, title,
                                   messageType, NULL, NULL, NULL);
}

/**
 * Prompts the user for input in a blocking internal dialog where
 * the initial selection, possible selections, and all other
 * options can be specified. The user will able to choose from
 * <code>selectionValues</code>, where <code>NULL</code>
 * implies the user can input
 * whatever they wish, usually by means of a <code>JTextField</code>.
 * <code>initialSelectionValue</code> is the initial value to prompt
 * the user with. It is up to the UI to decide how best to represent
 * the <code>selectionValues</code>, but usually a
 * <code>JComboBox</code>, <code>JList</code>, or
 * <code>JTextField</code> will be used.
 *
 * @param parentComponent the parent <code>Component</code> for the dialog
 * @param message  the <code>Object</code> to display
 * @param title    the <code>String</code> to display in the dialog
 *          title bar
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>, <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>, or <code>PLAIN_MESSAGE</code>
 * @param icon     the <code>Icon</code> image to display
 * @param selectionValues an array of <code>Objects</code> that
 *                  gives the possible selections
 * @param initialSelectionValue the value used to initialize the input
 *                  field
 * @return user's input, or <code>NULL</code> meaning the user
 *          canceled the input
 */
/*public*/ static Object showInternalInputDialog(Component parentComponent,
        Object message, QString title, int messageType, Icon icon,
        Object[] selectionValues, Object initialSelectionValue) {
    JOptionPane pane = new JOptionPane(message, messageType,
            OK_CANCEL_OPTION, icon, NULL, NULL);
    pane.putClientProperty(PopupFactory_FORCE_HEAVYWEIGHT_POPUP,
            Boolean.TRUE);
    Component fo = KeyboardFocusManager.getCurrentKeyboardFocusManager().
            getFocusOwner();

    pane.setWantsInput(true);
    pane.setSelectionValues(selectionValues);
    pane.setInitialSelectionValue(initialSelectionValue);

    JInternalFrame dialog =
        pane.createInternalFrame(parentComponent, title);

    pane.selectInitialValue();
    dialog.setVisible(true);

    /* Since all input will be blocked until this dialog is dismissed,
     * make sure its parent containers are visible first (this component
     * is tested below).  This is necessary for JApplets, because
     * because an applet normally isn't made visible until after its
     * start() method returns -- if this method is called from start(),
     * the applet will appear to hang while an invisible modal frame
     * waits for input.
     */
    if (dialog.isVisible() && !dialog.isShowing()) {
        Container parent = dialog.getParent();
        while (parent != NULL) {
            if (parent.isVisible() == false) {
                parent.setVisible(true);
            }
            parent = parent.getParent();
        }
    }

    // Use reflection to get Container.startLWModal.
    try {
        Method method = AccessController.doPrivileged(new ModalPrivilegedAction(
                Container.class, "startLWModal"));
        if (method != NULL) {
            method.invoke(dialog, (Object[])NULL);
        }
    } catch (IllegalAccessException ex) {
    } catch (IllegalArgumentException ex) {
    } catch (InvocationTargetException ex) {
    }

    if (parentComponent instanceof JInternalFrame) {
        try {
            ((JInternalFrame)parentComponent).setSelected(true);
        } catch (java.beans.PropertyVetoException e) {
        }
    }

    if (fo != NULL && fo.isShowing()) {
        fo.requestFocus();
    }
    Object value = pane.getInputValue();

    if (value == UNINITIALIZED_VALUE) {
        return NULL;
    }
    return value;
}

/**
 * Creates and returns an instance of <code>JInternalFrame</code>.
 * The internal frame is created with the specified title,
 * and wrapping the <code>JOptionPane</code>.
 * The returned <code>JInternalFrame</code> is
 * added to the <code>JDesktopPane</code> ancestor of
 * <code>parentComponent</code>, or components
 * parent if one its ancestors isn't a <code>JDesktopPane</code>,
 * or if <code>parentComponent</code>
 * doesn't have a parent then a <code>RuntimeException</code> is thrown.
 *
 * @param parentComponent  the parent <code>Component</code> for
 *          the internal frame
 * @param title    the <code>String</code> to display in the
 *          frame's title bar
 * @return a <code>JInternalFrame</code> containing a
 *          <code>JOptionPane</code>
 * @exception RuntimeException if <code>parentComponent</code> does
 *          not have a valid parent
 */
/*public*/ JInternalFrame createInternalFrame(Component parentComponent,
                             QString title) {
    Container parent =
            JOptionPane.getDesktopPaneForComponent(parentComponent);

    if (parent == NULL && (parentComponent == NULL ||
            (parent = parentComponent.getParent()) == NULL)) {
        throw new RuntimeException("JOptionPane: parentComponent does " +
                "not have a valid parent");
    }

    // Option dialogs should be closable only
    /*final*/ JInternalFrame  iFrame = new JInternalFrame(title, false, true,
                                                       false, false);

    iFrame.putClientProperty("JInternalFrame.frameType", "optionDialog");
    iFrame.putClientProperty("JInternalFrame.messageType",
                             Integer.valueOf(getMessageType()));

    iFrame.addInternalFrameListener(new InternalFrameAdapter() {
        /*public*/ void internalFrameClosing(InternalFrameEvent e) {
            if (getValue() == UNINITIALIZED_VALUE) {
                setValue(NULL);
            }
        }
    });
    addPropertyChangeListener(new PropertyChangeListener() {
        /*public*/ void propertyChange(PropertyChangeEvent event) {
            // Let the defaultCloseOperation handle the closing
            // if the user closed the iframe without selecting a button
            // (newValue = NULL in that case).  Otherwise, close the dialog.
            if (iFrame.isVisible() &&
                    event.getSource() == JOptionPane.this &&
                    event.getPropertyName().equals(VALUE_PROPERTY)) {
            // Use reflection to get Container.stopLWModal().
            try {
                Method method = AccessController.doPrivileged(
                    new ModalPrivilegedAction(
                        Container.class, "stopLWModal"));
                if (method != NULL) {
                    method.invoke(iFrame, (Object[])NULL);
                }
            } catch (IllegalAccessException ex) {
            } catch (IllegalArgumentException ex) {
            } catch (InvocationTargetException ex) {
            }

            try {
                iFrame.setClosed(true);
            }
            catch (java.beans.PropertyVetoException e) {
            }

            iFrame.setVisible(false);
            }
        }
    });
    iFrame.getContentPane().add(this, BorderLayout.CENTER);
    if (parent instanceof JDesktopPane) {
        parent.add(iFrame, JLayeredPane.MODAL_LAYER);
    } else {
        parent.add(iFrame, BorderLayout.CENTER);
    }
    Dimension iFrameSize = iFrame.getPreferredSize();
    Dimension rootSize = parent.getSize();
    Dimension parentSize = parentComponent.getSize();

    iFrame.setBounds((rootSize.width - iFrameSize.width) / 2,
                     (rootSize.height - iFrameSize.height) / 2,
                     iFrameSize.width, iFrameSize.height);
    // We want dialog centered relative to its parent component
    Point iFrameCoord =
      SwingUtilities.convertPoint(parentComponent, 0, 0, parent);
    int x = (parentSize.width - iFrameSize.width) / 2 + iFrameCoord.x;
    int y = (parentSize.height - iFrameSize.height) / 2 + iFrameCoord.y;

    // If possible, dialog should be fully visible
    int ovrx = x + iFrameSize.width - rootSize.width;
    int ovry = y + iFrameSize.height - rootSize.height;
    x = Math.max((ovrx > 0? x - ovrx: x), 0);
    y = Math.max((ovry > 0? y - ovry: y), 0);
    iFrame.setBounds(x, y, iFrameSize.width, iFrameSize.height);

    parent.validate();
    try {
        iFrame.setSelected(true);
    } catch (java.beans.PropertyVetoException e) {}

    return iFrame;
}

/**
 * Returns the specified component's <code>Frame</code>.
 *
 * @param parentComponent the <code>Component</code> to check for a
 *          <code>Frame</code>
 * @return the <code>Frame</code> that contains the component,
 *          or <code>getRootFrame</code>
 *          if the component is <code>NULL</code>,
 *          or does not have a valid <code>Frame</code> parent
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see #getRootFrame
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ static Frame getFrameForComponent(Component parentComponent)
    throws HeadlessException {
    if (parentComponent == NULL)
        return getRootFrame();
    if (parentComponent instanceof Frame)
        return (Frame)parentComponent;
    return JOptionPane.getFrameForComponent(parentComponent.getParent());
}
#endif
/**
 * Returns the specified component's toplevel <code>Frame</code> or
 * <code>Dialog</code>.
 *
 * @param parentComponent the <code>Component</code> to check for a
 *          <code>Frame</code> or <code>Dialog</code>
 * @return the <code>Frame</code> or <code>Dialog</code> that
 *          contains the component, or the default
 *          frame if the component is <code>NULL</code>,
 *          or does not have a valid
 *          <code>Frame</code> or <code>Dialog</code> parent
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*static*/ QWidget* JOptionPane::getWindowForComponent(QWidget* parentComponent)
    throw (HeadlessException) {
//    if (parentComponent == NULL)
//        return getRootFrame();
//    if (parentComponent instanceof Frame || parentComponent instanceof Dialog)
//        return (Window)parentComponent;
//    return JOptionPane.getWindowForComponent(parentComponent.getParent());
 return parentComponent->window();
}

#if 0
/**
 * Returns the specified component's desktop pane.
 *
 * @param parentComponent the <code>Component</code> to check for a
 *          desktop
 * @return the <code>JDesktopPane</code> that contains the component,
 *          or <code>NULL</code> if the component is <code>NULL</code>
 *          or does not have an ancestor that is a
 *          <code>JInternalFrame</code>
 */
/*public*/ static JDesktopPane getDesktopPaneForComponent(Component parentComponent) {
    if(parentComponent == NULL)
        return NULL;
    if(parentComponent instanceof JDesktopPane)
        return (JDesktopPane)parentComponent;
    return getDesktopPaneForComponent(parentComponent.getParent());
}

private static /*final*/ Object sharedFrameKey = JOptionPane.class;

/**
 * Sets the frame to use for class methods in which a frame is
 * not provided.
 * <p>
 * <strong>Note:</strong>
 * It is recommended that rather than using this method you supply a valid parent.
 *
 * @param newRootFrame the default <code>Frame</code> to use
 */
/*public*/ static void setRootFrame(Frame newRootFrame) {
    if (newRootFrame != NULL) {
        SwingUtilities.appContextPut(sharedFrameKey, newRootFrame);
    } else {
        SwingUtilities.appContextRemove(sharedFrameKey);
    }
}

/**
 * Returns the <code>Frame</code> to use for the class methods in
 * which a frame is not provided.
 *
 * @return the default <code>Frame</code> to use
 * @exception HeadlessException if
 *   <code>GraphicsEnvironment.isHeadless</code> returns
 *   <code>true</code>
 * @see #setRootFrame
 * @see java.awt.GraphicsEnvironment#isHeadless
 */
/*public*/ static Frame getRootFrame() throws HeadlessException {
    Frame sharedFrame =
        (Frame)SwingUtilities.appContextGet(sharedFrameKey);
    if (sharedFrame == NULL) {
        sharedFrame = SwingUtilities.getSharedOwnerFrame();
        SwingUtilities.appContextPut(sharedFrameKey, sharedFrame);
    }
    return sharedFrame;
}
#endif
/**
 * Creates a <code>JOptionPane</code> with a test message.
 */
/*public*/ JOptionPane::JOptionPane(QWidget *parent) : QWidget(parent)
{
 common("JOptionPane message");
}

/**
 * Creates a instance of <code>JOptionPane</code> to display a
 * message using the
 * plain-message message type and the default options delivered by
 * the UI.
 *
 * @param message the <code>Object</code> to display
 */
/*public*/ JOptionPane::JOptionPane(QVariant message, QWidget* parent) : QWidget(parent)
{
    common(message, PLAIN_MESSAGE);
}

/**
 * Creates an instance of <code>JOptionPane</code> to display a message
 * with the specified message type and the default options,
 *
 * @param message the <code>Object</code> to display
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 */
/*public*/ JOptionPane::JOptionPane(QVariant message, int messageType, QWidget* parent) : QWidget(parent) {
    common(message, messageType, DEFAULT_OPTION);
}

/**
 * Creates an instance of <code>JOptionPane</code> to display a message
 * with the specified message type and options.
 *
 * @param message the <code>Object</code> to display
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param optionType the options to display in the pane:
 *                  <code>DEFAULT_OPTION</code>, <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  <code>OK_CANCEL_OPTION</code>
 */
/*public*/ JOptionPane::JOptionPane(QVariant message, int messageType, int optionType, QWidget* parent)  : QWidget(parent){
    common(message, messageType, optionType, QIcon());
}

/**
 * Creates an instance of <code>JOptionPane</code> to display a message
 * with the specified message type, options, and icon.
 *
 * @param message the <code>Object</code> to display
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param optionType the options to display in the pane:
 *                  <code>DEFAULT_OPTION</code>, <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  <code>OK_CANCEL_OPTION</code>
 * @param icon the <code>Icon</code> image to display
 */
/*public*/ JOptionPane::JOptionPane(QVariant message, int messageType, int optionType, QIcon icon, QWidget* parent) : QWidget(parent)
{
    common(message, messageType, optionType, icon, QList<QVariant>());
}

/**
 * Creates an instance of <code>JOptionPane</code> to display a message
 * with the specified message type, icon, and options.
 * None of the options is initially selected.
 * <p>
 * The options objects should contain either instances of
 * <code>Component</code>s, (which are added directly) or
 * <code>Strings</code> (which are wrapped in a <code>JButton</code>).
 * If you provide <code>Component</code>s, you must ensure that when the
 * <code>Component</code> is clicked it messages <code>setValue</code>
 * in the created <code>JOptionPane</code>.
 *
 * @param message the <code>Object</code> to display
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param optionType the options to display in the pane:
 *                  <code>DEFAULT_OPTION</code>,
 *                  <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  <code>OK_CANCEL_OPTION</code>
 * @param icon the <code>Icon</code> image to display
 * @param options  the choices the user can select
 */
/*public*/ JOptionPane::JOptionPane(QVariant message, int messageType, int optionType, QIcon icon, QList<QVariant> options, QWidget* parent) : QWidget(parent)
{
    common(message, messageType, optionType, icon, options, QVariant());
}

/**
 * Creates an instance of <code>JOptionPane</code> to display a message
 * with the specified message type, icon, and options, with the
 * initially-selected option specified.
 *
 * @param message the <code>Object</code> to display
 * @param messageType the type of message to be displayed:
 *                  <code>ERROR_MESSAGE</code>,
 *                  <code>INFORMATION_MESSAGE</code>,
 *                  <code>WARNING_MESSAGE</code>,
 *                  <code>QUESTION_MESSAGE</code>,
 *                  or <code>PLAIN_MESSAGE</code>
 * @param optionType the options to display in the pane:
 *                  <code>DEFAULT_OPTION</code>,
 *                  <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  <code>OK_CANCEL_OPTION</code>
 * @param icon the Icon image to display
 * @param options  the choices the user can select
 * @param initialValue the choice that is initially selected; if
 *                  <code>NULL</code>, then nothing will be initially selected;
 *                  only meaningful if <code>options</code> is used
 */
/*public*/ JOptionPane::JOptionPane(QVariant message, int messageType, int optionType,  QIcon icon, QList<QVariant> options, QVariant initialValue, QWidget* parent) : QWidget(parent)
{
 common(message, messageType, optionType, icon, options, initialValue);
}

void JOptionPane::common(QVariant message, int messageType, int optionType, QIcon icon, QList<QVariant> options, QVariant initialValue)
{
 setObjectName("JOptionPane");
 changeSupport = new PropertyChangeSupport(this);
 wantsInput = false;
    this->message = message;
    this->options = options;
    this->initialValue = initialValue;
    this->icon = icon;
    setMessageType(messageType);
    setOptionType(optionType);
    value = UNINITIALIZED_VALUE;
    inputValue = UNINITIALIZED_VALUE;
//    updateUI();
}
#if 0
/**
 * Sets the UI object which implements the {@literal L&F} for this component.
 *
 * @param ui  the <code>OptionPaneUI</code> {@literal L&F} object
 * @see UIDefaults#getUI
 * @beaninfo
 *       bound: true
 *      hidden: true
 * description: The UI object that implements the optionpane's LookAndFeel
 */
/*public*/ void JOptionPane::setUI(OptionPaneUI* ui) {
    if (this->ui != ui) {
//        super.setUI(ui);
        invalidate();
    }
}

/**
 * Returns the UI object which implements the {@literal L&F} for this component.
 *
 * @return the <code>OptionPaneUI</code> object
 */
/*public*/ OptionPaneUI getUI() {
    return (OptionPaneUI)ui;
}

/**
 * Notification from the <code>UIManager</code> that the {@literal L&F} has changed.
 * Replaces the current UI object with the latest version from the
 * <code>UIManager</code>.
 *
 * @see JComponent#updateUI
 */
/*public*/ void updateUI() {
    setUI((OptionPaneUI)UIManager.getUI(this));
}


/**
 * Returns the name of the UI class that implements the
 * {@literal L&F} for this component.
 *
 * @return the string "OptionPaneUI"
 * @see JComponent#getUIClassID
 * @see UIDefaults#getUI
 */
/*public*/ QString getUIClassID() {
    return uiClassID;
}

#endif
/**
 * Sets the option pane's message-object.
 * @param newMessage the <code>Object</code> to display
 * @see #getMessage
 *
 * @beaninfo
 *   preferred: true
 *   bound: true
 * description: The optionpane's message object.
 */
/*public*/ void JOptionPane::setMessage(QVariant newMessage) {
    QVariant           oldMessage = message;

    message = newMessage;
    firePropertyChange(MESSAGE_PROPERTY, oldMessage, message);
}

/**
 * Returns the message-object this pane displays.
 * @see #setMessage
 *
 * @return the <code>Object</code> that is displayed
 */
/*public*/ QVariant JOptionPane::getMessage() {
    return message;
}
/**
 * Support for reporting bound property changes for Object properties.
 * This method can be called when a bound property has changed and it will
 * send the appropriate PropertyChangeEvent to any registered
 * PropertyChangeListeners.
 *
 * @param propertyName the property whose value has changed
 * @param oldValue the property's previous value
 * @param newValue the property's new value
 */
/*protected*/ void JOptionPane::firePropertyChange(QString propertyName,
                                  QVariant oldValue, QVariant newValue) {
//    PropertyChangeSupport changeSupport;
//    synchronized (getObjectLock()) {
//        changeSupport = this.changeSupport;
//    }
//    if (changeSupport == null ||
//        (oldValue != null && newValue != null && oldValue.equals(newValue))) {
//        return;
//    }
    changeSupport->firePropertyChange(propertyName, oldValue, newValue);
}

/**
 * Sets the icon to display. If non-<code>NULL</code>, the look and feel
 * does not provide an icon.
 * @param newIcon the <code>Icon</code> to display
 *
 * @see #getIcon
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The option pane's type icon.
 */
/*public*/ void JOptionPane::setIcon(QIcon newIcon) {
    QVariant              oldIcon = icon;

    icon = newIcon;
    firePropertyChange(ICON_PROPERTY, oldIcon, icon);
}

/**
 * Returns the icon this pane displays.
 * @return the <code>Icon</code> that is displayed
 *
 * @see #setIcon
 */
/*public*/ QIcon JOptionPane::getIcon() {
    return icon;
}

/**
 * Sets the value the user has chosen.
 * @param newValue  the chosen value
 *
 * @see #getValue
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The option pane's value object.
 */
/*public*/ void JOptionPane::setValue(QVariant newValue) {
    QVariant               oldValue = value;

    value = newValue;
    firePropertyChange(VALUE_PROPERTY, oldValue, value);
}

/**
 * Returns the value the user has selected. <code>UNINITIALIZED_VALUE</code>
 * implies the user has not yet made a choice, <code>NULL</code> means the
 * user closed the window with out choosing anything. Otherwise
 * the returned value will be one of the options defined in this
 * object.
 *
 * @return the <code>Object</code> chosen by the user,
 *         <code>UNINITIALIZED_VALUE</code>
 *         if the user has not yet made a choice, or <code>NULL</code> if
 *         the user closed the window without making a choice
 *
 * @see #setValue
 */
/*public*/ QVariant JOptionPane::getValue() {
    return value;
}

/**
 * Sets the options this pane displays. If an element in
 * <code>newOptions</code> is a <code>Component</code>
 * it is added directly to the pane,
 * otherwise a button is created for the element.
 *
 * @param newOptions an array of <code>Objects</code> that create the
 *          buttons the user can click on, or arbitrary
 *          <code>Components</code> to add to the pane
 *
 * @see #getOptions
 * @beaninfo
 *       bound: true
 * description: The option pane's options objects.
 */
/*public*/ void JOptionPane::setOptions(QList<QVariant> newOptions) {
    QList<QVariant>          oldOptions = options;

    options = newOptions;
    firePropertyChange(OPTIONS_PROPERTY, oldOptions, options);
}

/**
 * Returns the choices the user can make.
 * @return the array of <code>Objects</code> that give the user's choices
 *
 * @see #setOptions
 */
/*public*/ QList<QVariant> JOptionPane::getOptions() {
    if(options != QList<QVariant>()) {
        int             optionCount = options.length();
        QVector<QVariant>        retOptions = QVector<QVariant>(optionCount);//new Object[optionCount];

        //System.arraycopy(options, 0, retOptions, 0, optionCount);
        for(int i=0; i < optionCount; i++)
        {
         retOptions.replace(i, options.at(i));
        }
        return retOptions.toList();
    }
    return options;
}

/**
 * Sets the initial value that is to be enabled -- the
 * <code>Component</code>
 * that has the focus when the pane is initially displayed.
 *
 * @param newInitialValue the <code>Object</code> that gets the initial
 *                         keyboard focus
 *
 * @see #getInitialValue
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The option pane's initial value object.
 */
/*public*/ void JOptionPane::setInitialValue(QVariant newInitialValue) {
    QVariant            oldIV = initialValue;

    initialValue = newInitialValue;
    firePropertyChange(INITIAL_VALUE_PROPERTY, oldIV, initialValue);
}

/**
 * Returns the initial value.
 *
 * @return the <code>Object</code> that gets the initial keyboard focus
 *
 * @see #setInitialValue
 */
/*public*/ QVariant JOptionPane::getInitialValue() {
    return initialValue;
}

/**
 * Sets the option pane's message type.
 * The message type is used by the Look and Feel to determine the
 * icon to display (if not supplied) as well as potentially how to
 * lay out the <code>parentComponent</code>.
 * @param newType an integer specifying the kind of message to display:
 *                <code>ERROR_MESSAGE</code>, <code>INFORMATION_MESSAGE</code>,
 *                <code>WARNING_MESSAGE</code>,
 *                <code>QUESTION_MESSAGE</code>, or <code>PLAIN_MESSAGE</code>
 * @exception RuntimeException if <code>newType</code> is not one of the
 *          legal values listed above

 * @see #getMessageType
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The option pane's message type.
 */
/*public*/ void JOptionPane::setMessageType(int newType) {
    if(newType != ERROR_MESSAGE && newType != INFORMATION_MESSAGE &&
       newType != WARNING_MESSAGE && newType != QUESTION_MESSAGE &&
       newType != PLAIN_MESSAGE)
        /*throw new RuntimeException*/Logger::error("JOptionPane: type must be one of JOptionPane.ERROR_MESSAGE, JOptionPane.INFORMATION_MESSAGE, JOptionPane.WARNING_MESSAGE, JOptionPane.QUESTION_MESSAGE or JOptionPane.PLAIN_MESSAGE");

    int           oldType = messageType;

    messageType = newType;
    firePropertyChange(MESSAGE_TYPE_PROPERTY, oldType, messageType);
}

/**
 * Returns the message type.
 *
 * @return an integer specifying the message type
 *
 * @see #setMessageType
 */
/*public*/ int JOptionPane::getMessageType() {
    return messageType;
}

/**
 * Sets the options to display.
 * The option type is used by the Look and Feel to
 * determine what buttons to show (unless options are supplied).
 * @param newType an integer specifying the options the {@literal L&F} is to display:
 *                  <code>DEFAULT_OPTION</code>,
 *                  <code>YES_NO_OPTION</code>,
 *                  <code>YES_NO_CANCEL_OPTION</code>,
 *                  or <code>OK_CANCEL_OPTION</code>
 * @exception RuntimeException if <code>newType</code> is not one of
 *          the legal values listed above
 *
 * @see #getOptionType
 * @see #setOptions
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The option pane's option type.
  */
/*public*/ void JOptionPane::setOptionType(int newType) {
    if(newType != DEFAULT_OPTION && newType != YES_NO_OPTION &&
       newType != YES_NO_CANCEL_OPTION && newType != OK_CANCEL_OPTION)
        /*throw new RuntimeException*/Logger::error("JOptionPane: option type must be one of JOptionPane.DEFAULT_OPTION, JOptionPane.YES_NO_OPTION, JOptionPane.YES_NO_CANCEL_OPTION or JOptionPane.OK_CANCEL_OPTION");

    int            oldType = optionType;

    optionType = newType;
    firePropertyChange(OPTION_TYPE_PROPERTY, oldType, optionType);
}

/**
 * Returns the type of options that are displayed.
 *
 * @return an integer specifying the user-selectable options
 *
 * @see #setOptionType
 */
/*public*/ int JOptionPane::getOptionType() {
    return optionType;
}

/**
 * Sets the input selection values for a pane that provides the user
 * with a list of items to choose from. (The UI provides a widget
 * for choosing one of the values.)  A <code>NULL</code> value
 * implies the user can input whatever they wish, usually by means
 * of a <code>JTextField</code>.
 * <p>
 * Sets <code>wantsInput</code> to true. Use
 * <code>setInitialSelectionValue</code> to specify the initially-chosen
 * value. After the pane as been enabled, <code>inputValue</code> is
 * set to the value the user has selected.
 * @param newValues an array of <code>Objects</code> the user to be
 *                  displayed
 *                  (usually in a list or combo-box) from which
 *                  the user can make a selection
 * @see #setWantsInput
 * @see #setInitialSelectionValue
 * @see #getSelectionValues
 * @beaninfo
 *       bound: true
 * description: The option pane's selection values.
 */
/*public*/ void JOptionPane::setSelectionValues(QList<QVariant> newValues) {
   QList<QVariant>           oldValues = selectionValues;

    selectionValues = newValues;
    firePropertyChange(SELECTION_VALUES_PROPERTY, oldValues, newValues);
    if(!selectionValues.isEmpty())
        setWantsInput(true);
}

/**
 * Returns the input selection values.
 *
 * @return the array of <code>Objects</code> the user can select
 * @see #setSelectionValues
 */
/*public*/ QList<QVariant> JOptionPane::getSelectionValues() {
    return selectionValues;
}

/**
 * Sets the input value that is initially displayed as selected to the user.
 * Only used if <code>wantsInput</code> is true.
 * @param newValue the initially selected value
 * @see #setSelectionValues
 * @see #getInitialSelectionValue
 * @beaninfo
 *       bound: true
 * description: The option pane's initial selection value object.
 */
/*public*/ void JOptionPane::setInitialSelectionValue(QVariant newValue) {
    QVariant          oldValue = initialSelectionValue;

    initialSelectionValue = newValue;
    firePropertyChange(INITIAL_SELECTION_VALUE_PROPERTY, oldValue,
                       newValue);
}

/**
 * Returns the input value that is displayed as initially selected to the user.
 *
 * @return the initially selected value
 * @see #setInitialSelectionValue
 * @see #setSelectionValues
 */
/*public*/ QVariant JOptionPane::getInitialSelectionValue() {
    return initialSelectionValue;
}

/**
 * Sets the input value that was selected or input by the user.
 * Only used if <code>wantsInput</code> is true.  Note that this method
 * is invoked internally by the option pane (in response to user action)
 * and should generally not be called by client programs.  To set the
 * input value initially displayed as selected to the user, use
 * <code>setInitialSelectionValue</code>.
 *
 * @param newValue the <code>Object</code> used to set the
 *          value that the user specified (usually in a text field)
 * @see #setSelectionValues
 * @see #setInitialSelectionValue
 * @see #setWantsInput
 * @see #getInputValue
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: The option pane's input value object.
 */
/*public*/ void JOptionPane::setInputValue(QVariant newValue) {
    QVariant              oldValue = inputValue;

    inputValue = newValue;
    firePropertyChange(INPUT_VALUE_PROPERTY, oldValue, newValue);
}

/**
 * Returns the value the user has input, if <code>wantsInput</code>
 * is true.
 *
 * @return the <code>Object</code> the user specified,
 *          if it was one of the objects, or a
 *          <code>String</code> if it was a value typed into a
 *          field
 * @see #setSelectionValues
 * @see #setWantsInput
 * @see #setInputValue
 */
/*public*/ QVariant JOptionPane::getInputValue() {
    return inputValue;
}

/**
 * Returns the maximum number of characters to place on a line in a
 * message. Default is to return <code>Integer.MAX_VALUE</code>.
 * The value can be
 * changed by overriding this method in a subclass.
 *
 * @return an integer giving the maximum number of characters on a line
 */
/*public*/ int JOptionPane::getMaxCharactersPerLineCount() {
    return INT_MAX;
}

/**
 * Sets the <code>wantsInput</code> property.
 * If <code>newValue</code> is true, an input component
 * (such as a text field or combo box) whose parent is
 * <code>parentComponent</code> is provided to
 * allow the user to input a value. If <code>getSelectionValues</code>
 * returns a non-<code>NULL</code> array, the input value is one of the
 * objects in that array. Otherwise the input value is whatever
 * the user inputs.
 * <p>
 * This is a bound property.
 *
 * @see #setSelectionValues
 * @see #setInputValue
 * @beaninfo
 *   preferred: true
 *       bound: true
 * description: Flag which allows the user to input a value.
 */
/*public*/ void JOptionPane::setWantsInput(bool newValue) {
    bool            oldValue = wantsInput;

    wantsInput = newValue;
    firePropertyChange(WANTS_INPUT_PROPERTY, oldValue, newValue);
}

/**
 * Returns the value of the <code>wantsInput</code> property.
 *
 * @return true if an input component will be provided
 * @see #setWantsInput
 */
/*public*/ bool JOptionPane::getWantsInput() {
    return wantsInput;
}

/**
 * Requests that the initial value be selected, which will set
 * focus to the initial value. This method
 * should be invoked after the window containing the option pane
 * is made visible.
 */
/*public*/ void JOptionPane::selectInitialValue() {
#if 0
    OptionPaneUI         ui = getUI();
    if (ui != NULL) {
        ui.selectInitialValue(this);
    }
#endif
}


/*private*/ /*static*/ int JOptionPane::styleFromMessageType(int messageType) {
    switch (messageType) {
    case ERROR_MESSAGE:
        return JRootPane::ERROR_DIALOG;
    case QUESTION_MESSAGE:
        return JRootPane::QUESTION_DIALOG;
    case WARNING_MESSAGE:
        return JRootPane::WARNING_DIALOG;
    case INFORMATION_MESSAGE:
        return JRootPane::INFORMATION_DIALOG;
    case PLAIN_MESSAGE:
    default:
        return JRootPane::PLAIN_DIALOG;
    }
}
//this code isn't part of the original Java.
QWidget* JOptionPane::layoutPane(JDialog* dialog)
{
 QWidget* p = new QWidget();
 QVBoxLayout* pLayout = new QVBoxLayout(p);
 _dialog = dialog;

 QHBoxLayout* ll = new QHBoxLayout();
 QIcon icon;
 switch(getMessageType())
 {
 case ERROR_MESSAGE:
  icon = style()->standardIcon(QStyle::SP_MessageBoxCritical);
  break;
 case INFORMATION_MESSAGE:
  icon =style()->standardIcon(QStyle::SP_MessageBoxInformation);
  break;
 case WARNING_MESSAGE:
  icon =style()->standardIcon(QStyle::SP_MessageBoxWarning);
  break;
 case QUESTION_MESSAGE:
  icon =style()->standardIcon(QStyle::SP_MessageBoxQuestion);
  break;
 default:
  break;
 }
 QLabel* iconLabel = new QLabel();
 iconLabel->setPixmap(icon.pixmap(64,64));
 ll->addWidget(iconLabel);
 if(VPtr<QWidget>::asPtr(message) != NULL)
 {
  ll->addWidget(VPtr<QWidget>::asPtr(message));
 }
 else if(message != QVariant())
 {
  ll->addWidget(new QLabel(getMessage().toString()));
 }
 if(getWantsInput())
 {
  if(options.count() == 1)
  {
   f = new JTextField();
   if(getInitialValue() != QVariant())
    f->setText(getInitialValue().toString());
   ll->addWidget(f);
   connect(f, SIGNAL(editingFinished()), this, SLOT(handleTextInput()));
  }
  else
  {
   QListWidget* lw = new QListWidget();
   foreach (QVariant v, options) {
    lw->addItem(v.toString());
   }
   if(getInitialValue() != QVariant())
    lw->setCurrentItem(new QListWidgetItem(getInitialValue().toString()));
   ll->addWidget(lw);
   connect(lw, &QListWidget::itemClicked, [=]{
    setValue(lw->currentItem()->text());
    inputValue = QVariant(lw->currentItem()->text());
   });
  }
 }
 pLayout->addLayout(ll);
 FlowLayout* fl = new FlowLayout();
 fl->setAlignment(Qt::AlignCenter);
 if(optionType == DEFAULT_OPTION)
 {
  btnOk = new QPushButton(tr("Ok"));
  btnOk->setObjectName("btnOk");
  fl->addWidget(btnOk);
  pLayout->addLayout(fl);
  connect(btnOk, SIGNAL(clicked(bool)), this, SLOT(handleOk()));
 }
 else if(options.count()> 0 && (optionType != QUESTION_MESSAGE) && (optionType != OK_CANCEL_OPTION))
 {
  QSignalMapper* mapper = new QSignalMapper();
  for(int i = 0; i < options.count(); i ++)
  {
   QPushButton* btn = new QPushButton(options.at(i).toString());
   btn->setObjectName("options_"+options.at(i).toString());
   mapper->setMapping(btn,i);
   connect(btn,SIGNAL(clicked()), mapper, SLOT(map()));
   fl->addWidget(btn);
  }
  connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleOptionButton(int)));
  pLayout->addLayout(fl);
 }
 else if (optionType == YES_NO_OPTION || optionType == YES_NO_CANCEL_OPTION)
 {
  btnYes = new QPushButton(tr("Yes"));
  btnYes->setObjectName("btnYes");
  fl->addWidget(btnYes);
  connect(btnYes, SIGNAL(clicked(bool)), this, SLOT(handleYes()));
  btnNo = new QPushButton(tr("No"));
  btnNo->setObjectName("btnNo");
  fl->addWidget(btnNo);
  connect(btnNo, SIGNAL(clicked(bool)), this, SLOT(handleNo()));
  if(optionType == YES_NO_CANCEL_OPTION)
  {
   btnCancel = new QPushButton(tr("Cancel"));
   btnCancel->setObjectName("btnCancel");
   fl->addWidget(btnCancel);
   connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(handleCancel()));
  }
  pLayout->addLayout(fl);
 }
 else if(getOptionType() == OK_CANCEL_OPTION || optionType == OK_CANCEL_OPTION)
 {
   btnOk = new QPushButton(tr("Ok"));
   btnOk->setObjectName("btnOk");
   btnCancel = new QPushButton(tr("Cancel"));
   btnCancel->setObjectName("btnCancel");
   fl->addWidget(btnOk);
   fl->addWidget(btnCancel);
   pLayout->addLayout(fl);
   connect(btnOk, SIGNAL(clicked(bool)), this, SLOT(handleOk()));
   connect(btnCancel, SIGNAL(clicked(bool)), this, SLOT(handleCancel()));
 }
 return p;
}

/*public*/ void JOptionPane::setValidator(QValidator* val)
{
 if(!getWantsInput())
  throw IllegalArgumentException(tr("can't set validator if not wanting input"));
 f->setValidator(val);
}

void JOptionPane::handleTextInput()
{
 setValue(f->text());
 inputValue = QVariant(f->text());
}
void JOptionPane::handleOk()
{
 //_dialog->accept();
 _dialog->done(OK_OPTION);
}
void JOptionPane::handleOptionButton(int i)
{
 _dialog->done(i);
}
void JOptionPane::handleCancel()
{
 //setValue(CANCEL_OPTION);
 _dialog->done(CANCEL_OPTION);
}
void JOptionPane::handleYes()
{
 setValue(YES_OPTION);
 _dialog->done(YES_OPTION);
}
void JOptionPane::handleNo()
{
 //setValue(NO_OPTION);
 _dialog->done(NO_OPTION);
}

#if 0
// Serialization support.
private void writeObject(ObjectOutputStream s) throws IOException {
    Vector<Object> values = new Vector<Object>();

    s.defaultWriteObject();
    // Save the icon, if its Serializable.
    if(icon != NULL && icon instanceof Serializable) {
        values.addElement("icon");
        values.addElement(icon);
    }
    // Save the message, if its Serializable.
    if(message != NULL && message instanceof Serializable) {
        values.addElement("message");
        values.addElement(message);
    }
    // Save the treeModel, if its Serializable.
    if(options != NULL) {
        Vector<Object> serOptions = new Vector<Object>();

        for(int counter = 0, maxCounter = options.length;
            counter < maxCounter; counter++)
            if(options[counter] instanceof Serializable)
                serOptions.addElement(options[counter]);
        if(serOptions.size() > 0) {
            int             optionCount = serOptions.size();
            Object[]        arrayOptions = new Object[optionCount];

            serOptions.copyInto(arrayOptions);
            values.addElement("options");
            values.addElement(arrayOptions);
        }
    }
    // Save the initialValue, if its Serializable.
    if(initialValue != NULL && initialValue instanceof Serializable) {
        values.addElement("initialValue");
        values.addElement(initialValue);
    }
    // Save the value, if its Serializable.
    if(value != NULL && value instanceof Serializable) {
        values.addElement("value");
        values.addElement(value);
    }
    // Save the selectionValues, if its Serializable.
    if(selectionValues != NULL) {
        boolean            serialize = true;

        for(int counter = 0, maxCounter = selectionValues.length;
            counter < maxCounter; counter++) {
            if(selectionValues[counter] != NULL &&
               !(selectionValues[counter] instanceof Serializable)) {
                serialize = false;
                break;
            }
        }
        if(serialize) {
            values.addElement("selectionValues");
            values.addElement(selectionValues);
        }
    }
    // Save the inputValue, if its Serializable.
    if(inputValue != NULL && inputValue instanceof Serializable) {
        values.addElement("inputValue");
        values.addElement(inputValue);
    }
    // Save the initialSelectionValue, if its Serializable.
    if(initialSelectionValue != NULL &&
       initialSelectionValue instanceof Serializable) {
        values.addElement("initialSelectionValue");
        values.addElement(initialSelectionValue);
    }
    s.writeObject(values);
}

private void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException {
    s.defaultReadObject();

    Vector          values = (Vector)s.readObject();
    int             indexCounter = 0;
    int             maxCounter = values.size();

    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("icon")) {
        icon = (Icon)values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("message")) {
        message = values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("options")) {
        options = (Object[])values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("initialValue")) {
        initialValue = values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("value")) {
        value = values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("selectionValues")) {
        selectionValues = (Object[])values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("inputValue")) {
        inputValue = values.elementAt(++indexCounter);
        indexCounter++;
    }
    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("initialSelectionValue")) {
        initialSelectionValue = values.elementAt(++indexCounter);
        indexCounter++;
    }
    if (getUIClassID().equals(uiClassID)) {
        byte count = JComponent.getWriteObjCounter(this);
        JComponent.setWriteObjCounter(this, --count);
        if (count == 0 && ui != NULL) {
            ui.installUI(this);
        }
    }
}


/**
 * Returns a string representation of this <code>JOptionPane</code>.
 * This method
 * is intended to be used only for debugging purposes, and the
 * content and format of the returned string may vary between
 * implementations. The returned string may be empty but may not
 * be <code>NULL</code>.
 *
 * @return  a string representation of this <code>JOptionPane</code>
 */
/*protected*/ QString paramString() {
    QString iconString = (icon != NULL ?
                         icon.toString() : "");
    QString initialValueString = (initialValue != NULL ?
                                 initialValue.toString() : "");
    QString messageString = (message != NULL ?
                            message.toString() : "");
    QString messageTypeString;
    if (messageType == ERROR_MESSAGE) {
        messageTypeString = "ERROR_MESSAGE";
    } else if (messageType == INFORMATION_MESSAGE) {
        messageTypeString = "INFORMATION_MESSAGE";
    } else if (messageType == WARNING_MESSAGE) {
        messageTypeString = "WARNING_MESSAGE";
    } else if (messageType == QUESTION_MESSAGE) {
        messageTypeString = "QUESTION_MESSAGE";
    } else if (messageType == PLAIN_MESSAGE)  {
        messageTypeString = "PLAIN_MESSAGE";
    } else messageTypeString = "";
    QString optionTypeString;
    if (optionType == DEFAULT_OPTION) {
        optionTypeString = "DEFAULT_OPTION";
    } else if (optionType == YES_NO_OPTION) {
        optionTypeString = "YES_NO_OPTION";
    } else if (optionType == YES_NO_CANCEL_OPTION) {
        optionTypeString = "YES_NO_CANCEL_OPTION";
    } else if (optionType == OK_CANCEL_OPTION) {
        optionTypeString = "OK_CANCEL_OPTION";
    } else optionTypeString = "";
    QString wantsInputString = (wantsInput ?
                               "true" : "false");

    return super.paramString() +
    ",icon=" + iconString +
    ",initialValue=" + initialValueString +
    ",message=" + messageString +
    ",messageType=" + messageTypeString +
    ",optionType=" + optionTypeString +
    ",wantsInput=" + wantsInputString;
}

/**
 * Retrieves a method from the provided class and makes it accessible.
 */
private static class ModalPrivilegedAction implements PrivilegedAction<Method> {
    private Class<?> clazz;
    private QString methodName;

    /*public*/ ModalPrivilegedAction(Class<?> clazz, QString methodName) {
        this->clazz = clazz;
        this->methodName = methodName;
    }

    /*public*/ Method run() {
        Method method = NULL;
        try {
            method = clazz.getDeclaredMethod(methodName, (Class[])NULL);
        } catch (NoSuchMethodException ex) {
        }
        if (method != NULL) {
            method.setAccessible(true);
        }
        return method;
    }
}



///////////////////
// Accessibility support
///////////////////

/**
 * Returns the <code>AccessibleContext</code> associated with this JOptionPane.
 * For option panes, the <code>AccessibleContext</code> takes the form of an
 * <code>AccessibleJOptionPane</code>.
 * A new <code>AccessibleJOptionPane</code> instance is created if necessary.
 *
 * @return an AccessibleJOptionPane that serves as the
 *         AccessibleContext of this AccessibleJOptionPane
 * @beaninfo
 *       expert: true
 *  description: The AccessibleContext associated with this option pane
 */
/*public*/ AccessibleContext getAccessibleContext() {
    if (accessibleContext == NULL) {
        accessibleContext = new AccessibleJOptionPane();
    }
    return accessibleContext;
}

/**
 * This class implements accessibility support for the
 * <code>JOptionPane</code> class.  It provides an implementation of the
 * Java Accessibility API appropriate to option pane user-interface
 * elements.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 */
/*protected*/ class AccessibleJOptionPane extends AccessibleJComponent {

    /**
     * Get the role of this object.
     *
     * @return an instance of AccessibleRole describing the role of the object
     * @see AccessibleRole
     */
    /*public*/ AccessibleRole getAccessibleRole() {
        switch (messageType) {
        case ERROR_MESSAGE:
        case INFORMATION_MESSAGE:
        case WARNING_MESSAGE:
            return AccessibleRole.ALERT;

        default:
            return AccessibleRole.OPTION_PANE;
        }
    }

} // inner class AccessibleJOptionPane
#endif
