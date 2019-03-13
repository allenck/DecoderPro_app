#include "quickpromptutil.h"
#include "component.h"
#include "joptionpane.h"

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
        } catch (NumberFormatException e) {
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
        } catch (NumberFormatException e) {
            result = oldValue;
        }
    }
    return result;
}
#endif
// initialize logging
// private final static Logger log = LoggerFactory.getLogger(QuickPromptUtil.class);
