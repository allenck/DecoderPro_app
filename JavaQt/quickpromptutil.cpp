#include "quickpromptutil.h"
#include "component.h"
#include "joptionpane.h"
#include <QIntValidator>
#include "vptr.h"

QuickPromptUtil::QuickPromptUtil(QObject *parent) : QObject(parent)
{

}

/**
 * A collection of utilities related to prompting for values
 *
 * @author George Warner Copyright: (c) 2017
 */
///*public*/ class QuickPromptUtil {

/**
 * Utility function to prompt for new string value
 *
 * @param message  the prompt message
 * @param title    the dialog title
 * @param oldValue the original string value
 * @return the new string value
 */
/*static*/ /*public*/ QString QuickPromptUtil::promptForString(Component* parentComponent, QString message, QString title, QString oldValue) {
    QString result = oldValue;
    QString newValue =  JOptionPane::showInputDialog(parentComponent,
            message, title, JOptionPane::PLAIN_MESSAGE,
            QIcon(), QVariantList(), oldValue).toString();
    if (newValue != "") {
        result = newValue;
    }
    return result;
}

/**
 * Utility function to prompt for new integer value
 *
 * @param message  the prompt message
 * @param title    the dialog title
 * @param oldValue the original integer value
 * @return the new integer value
 */
/*static*/ /*public*/ int QuickPromptUtil::promptForInt(Component* parentComponent, QString message, QString title, int oldValue) {
    int result = oldValue;
    QString newValue = promptForString(parentComponent, message, title, QString::number(oldValue));
    if (newValue != "") {
        bool bok;
            result = (newValue.toInt(&bok));
        if(!bok) {
            result = oldValue;
        }
    }
    return result;
}
/**
 * Utility function to prompt for new integer value. Allows to constrain
 * values using a Predicate (validator).
 * <p>
 * The validator may throw an {@link IllegalArgumentException} whose
 * {@link IllegalArgumentException#getLocalizedMessage()} will be displayed.
 * The Predicate may also simply return {@code false}, which causes just
 * general message (the value is invalid) to be printed. If the Predicate
 * rejects the input, the OK button is disabled and the user is unable to
 * confirm the dialog.
 * <p>
 * The function returns the original value if the dialog was cancelled or
 * the entered value was empty or invalid. Otherwise, it returns the new
 * value entered by the user.
 *
 * @param parentComponent the parent component
 * @param message         the prompt message.
 * @param title           title for the dialog
 * @param oldValue        the original value
 * @param validator       the validator instance. May be {@code null}
 * @return the updated value, or the original one.
 */
/*public*/ /*static*/ int QuickPromptUtil::promptForInteger(Component* parentComponent, /*@Nonnull*/ QString message, /*@Nonnull*/ QString title, int oldValue, /*@CheckForNull*/ QIntValidator* validator) {
    int result = oldValue;
    int newValue = 0;
//    int newValue = promptForData(parentComponent, message, title, oldValue, validator, (val) -> {
//        try {
//            return Integer.valueOf(Integer.parseInt(val));
//        } catch (NumberFormatException* ex) {
//            // original exception ignored; wrong message.
//            throw new NumberFormatException(Bundle.getMessage("InputDialogNotNumber"));
//        }
//    });
    QVariantList l = QVariantList() << VPtr<QValidator>::asQVariant(validator);
    QVariant val = JOptionPane::showInputDialog(parentComponent, message, title, JOptionPane::PLAIN_MESSAGE, QIcon(), l, oldValue);
    newValue = val.toInt();
    if (newValue != 0) {
        result = newValue;
    }
    return result;
}

/**
     * Utility function to prompt for new integer value. Allows to constrain
     * values using a Predicate (validator).
     * <p>
     * The validator may throw an {@link IllegalArgumentException} whose
     * {@link IllegalArgumentException#getLocalizedMessage()} will be displayed.
     * The Predicate may also simply return {@code false}, which causes just
     * general message (the value is invalid) to be printed. If the Predicate
     * rejects the input, the OK button is disabled and the user is unable to
     * confirm the dialog.
     * <p>
     * The function returns the original value if the dialog was cancelled or
     * the entered value was empty or invalid. Otherwise, it returns the new
     * value entered by the user.
     *
     * @param parentComponent the parent component
     * @param message         the prompt message.
     * @param title           title for the dialog
     * @param oldValue        the original value
     * @param validator       the validator instance. May be {@code null}
     * @return the updated value, or the original one.
     */
    /*public*/ /*static*/ int QuickPromptUtil::promptForInteger(Component* parentComponent, /*@Nonnull*/ QString message, /*@Nonnull*/ QString title,
                                           int oldValue, /*@CheckForNull*/ Predicate<int> /*validator*/) {
        int result = oldValue;
        int newValue = 0;
//        int newValue = promptForData(parentComponent, message, title, oldValue, validator, (val) -> {
//            try {
//                return Integer.valueOf(Integer.parseInt(val));
//            } catch (NumberFormatException* ex) {
//                // original exception ignored; wrong message.
//                throw new NumberFormatException(Bundle.getMessage("InputDialogNotNumber"));
//            }
//        });
        QVariant val = JOptionPane::showInputDialog(parentComponent, message, title, JOptionPane::PLAIN_MESSAGE, QIcon(), QList<QVariant>(), oldValue);
        newValue = val.toInt();
        if (newValue != 0) {
            result = newValue;
        }
        return result;

        if (newValue != 0) {
            result = newValue;
        }
        return result;
    }

#if 0
template<class T>
/*private*/ static  T promptForData(Component* parentComponent,
            /*@Nonnull*/ QString message, /*@Nonnull*/ QString title, T oldValue,
            @CheckForNull Predicate<T> validator,
            @CheckForNull Function<String, T> converter) {
        String result = oldValue == null ? "" : oldValue.toString(); // NOI18N
        JButton okOption = new JButton(Bundle.getMessage("InputDialogOK")); // NOI18N
        JButton cancelOption = new JButton(Bundle.getMessage("InputDialogCancel")); // NOI18N
        okOption.setDefaultCapable(true);

        ValidatingInputPane<T> validating = new ValidatingInputPane<T>(converter)
                .message(message)
                .validator(validator)
                .attachConfirmUI(okOption);
        validating.setText(result);
        JOptionPane pane = new JOptionPane(validating, JOptionPane.PLAIN_MESSAGE,
                OK_CANCEL_OPTION, null, new Object[]{okOption, cancelOption});

        pane.putClientProperty("OptionPane.buttonOrientation", SwingConstants.RIGHT); // NOI18N
        JDialog dialog = pane.createDialog(parentComponent, title);
        dialog.getRootPane().setDefaultButton(okOption);
        dialog.setResizable(true);

        class AL implements ActionListener {

            boolean confirmed;

            @Override
            public void actionPerformed(ActionEvent e) {
                Object s = e.getSource();
                if (s == okOption) {
                    confirmed = true;
                    dialog.setVisible(false);
                }
                if (s == cancelOption) {
                    dialog.setVisible(false);
                }
            }
        }

        AL al = new AL();
        okOption.addActionListener(al);
        cancelOption.addActionListener(al);

        dialog.setVisible(true);
        dialog
          return oldValue;
      }.dispose();

        if (al.confirmed) {
            T res = validating.getValue();
            if (res != null) {
                return res;
            }
        }
#endif
#if 0
/**
 * Utility function to prompt for new float value
 *
 * @param message  the prompt message
 * @param title    the dialog title
 * @param oldValue the original float value
 * @return the new float value
 */
static /*public*/ float promptForFloat(Component parentComponent, String message, String title, float oldValue) {
    float result = oldValue;
    String newValue = promptForString(parentComponent, message, title, Float.toString(oldValue));
    if (newValue != null) {
        try {
            result = Float.parseFloat(newValue);
        } catch (NumberFormatException* e) {
            result = oldValue;
        }
    }
    return result;
}

/**
 * Utility function to prompt for new double value
 *
 * @param message  the prompt message
 * @param title    the dialog title
 * @param oldValue the original double value
 * @return the new double value
 */
static /*public*/ double promptForDouble(Component parentComponent, String message, String title, double oldValue) {
    double result = oldValue;
    String newValue = promptForString(parentComponent, message, title, Double.toString(oldValue));
    if (newValue != null) {
        try {
            result = Double.parseDouble(newValue);
        } catch (NumberFormatException* e) {
            result = oldValue;
        }
    }
    return result;
}
#endif
/**
 * Creates a min/max predicate which will check the bounds. Suitable for
 * {@link #promptForInteger(java.awt.Component, java.lang.String, java.lang.String, Integer, java.util.function.Predicate)}.
 *
 * @param min        minimum value. Use {@link Integer#MIN_VALUE} to disable
 *                   check.
 * @param max        maximum value, inclusive. Use {@link Integer#MAX_VALUE}
 *                   to disable check.
 * @param valueLabel label to be included in the message. Must be already
 *                   I18Ned.
 * @return predicate instance
 */
/*public*/ /*static*/ QIntValidator* QuickPromptUtil::checkIntRange(int min, int max, QString /*valueLabel*/) {
    //return new IntRangePredicate(min, max, valueLabel);
 return new QIntValidator(min, max);
}
// initialize logging
// private final static Logger log = LoggerFactory.getLogger(QuickPromptUtil.class);
