#include "cvutil.h"
#include "loggerfactory.h"
#include "paneprogframe.h"
#include "stringutil.h"

CvUtil::CvUtil(QObject *parent) : QObject(parent)
{

}
/**
 * Common utility methods for working with CVs
 * <p>
 * We needed a place to refactor common CV-processing idioms in JMRI code, so
 * this class was created. It's more of a library of procedures than a real
 * class, as (so far) all of the operations have needed no state information.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Dave Heap Copyright (C) 2016
 */
// /*public*/ class CvUtil {

    /**
     *
     *
     * @param cvString a string that may contain one <em><strong>and only
     *                 one</strong></em> instance <em><strong>one</strong></em>
     * of the following expandable forms;
     * <br>
     * (parentheses can be used to limit numeric boundaries and/or restrict the
     * portions to be expanded):
     * <ul>
     * <li> A comma-separated list. Examples:<pre>
     * "1,5,7" expands to [1, 5, 7]
     * "16.3.25(1,2,5,7)" expands to [16.3.251, 16.3.252, 16.3.255, 16.3.257]
     * </pre></li>
     * <li> A hyphen-separated numeric range, in either direction. Examples:
     * <pre>
     * "16.3.25(1-7)" expands to [16.3.251, 16.3.252, 16.3.253, 16.3.254, 16.3.255, 16.3.256, 16.3.257]
     * "16.3.2(53-48)" expands to [16.3.253, 16.3.252, 16.3.251, 16.3.250, 16.3.249, 16.3.248]
     * "16.3(1-7).25" expands to [16.31.25, 16.32.25, 16.33.25, 16.34.25, 16.35.25, 16.36.25, 16.37.25]
     * "98-103" expands to [98, 99, 100, 101, 102, 103]
     * </pre></li>
     * <li> A numeric starting value, followed by a colon and a count, in either
     * direction. Examples:
     * <pre>
     * "25.3.250:4" expands to [25.3.250, 25.3.251, 25.3.252, 25.3.253]
     * "25.3.250:-4" expands to [25.3.250, 25.3.249, 25.3.248, 25.3.247]
     * </pre></li>
     * </ul>
     *
     * @return A list of CVs produced by expanding the string
     * <br><strong>or</strong><br>
     * an empty list if nothing to expand.
     */
    /*public*/ /*static*/ QList<QString> CvUtil::expandCvList(QString cvString) {
        QList<QString> ret = QList<QString>();
        QRegularExpression pattern;
        QRegularExpressionMatch matcher;
        QString prefix = "";
        QString theString = cvString;
        QString suffix = "";
        pattern = QRegularExpression("[(),\\-:]");
        matcher = pattern.match(theString);
        if (matcher.hasMatch()) {
            pattern = QRegularExpression("^([^(),\\-:]*?)\\(??([^()]*)\\)??([^(),\\-:]*?)$");
            matcher = pattern.match(theString);
            if (matcher.hasMatch()) {
                prefix = matcher.captured(1);
                theString = matcher.captured(2);
                suffix = matcher.captured(3);
            }
            pattern = QRegularExpression("^([^(),\\-:]+?)(,[^(),\\-:]+?)+?$");
            matcher = pattern.match(theString);
            if (matcher.hasMatch()) {
                QStringList theArray = theString.split(",");
                for (int i = 0; i < theArray.length(); i++) {
                    ret.append(prefix + theArray[i] + suffix);
                }
                return ret;
            }
            pattern = QRegularExpression("^([^(),\\-:]*?)(\\d+)-(\\d+)([^(),\\-:]*?)$");
            matcher = pattern.match(theString);
            if (matcher.hasMatch()) {
                QString subPrefix = matcher.captured(1);
                int start = matcher.captured(2).toInt();
                int end = matcher.captured(3).toInt();
                int inc = 0;
                QString subSuffix = matcher.captured(4);
                if (start < end) {
                    inc = 1;
                } else if (start > end) {
                    inc = -1;
                }
                int j = start;
                do {
                    ret.append(prefix + subPrefix + QString::number(j) + subSuffix + suffix);
                    j = j + inc;
                } while (j != (end + inc));
                return ret;
            }
            pattern = QRegularExpression("^([^(),\\-:]*?)(\\d+):(-?\\d+)([^(),\\-:]*?)$");
            matcher = pattern.match(theString);
            if (matcher.hasMatch()) {
                QString subPrefix = matcher.captured(1);
                int start = matcher.captured(2).toInt();
                int count = matcher.captured(3).toInt();
                int inc = 0;
                QString subSuffix = matcher.captured(4);
                if (count > 0) {
                    inc = 1;
                } else if (count < 0) {
                    inc = -1;
                }
                int j = start;
                do {
                    ret.append(prefix + subPrefix + QString::number(j) + subSuffix + suffix);
                    j = j + inc;
                } while (j != (start + count));
                return ret;
            }
            pattern = QRegularExpression("[(),\\-:]");
            matcher = pattern.match(theString);
            if (!matcher.hasMatch()) {
                ret.append(prefix + theString + suffix);
            } else {
                log->error(tr("Invalid string '%1'").arg(cvString));
            }
        }
        return ret;
    }

    /**
     * Optionally add CV numbers and bit numbers to tool tip text based on
     * Roster Preferences setting.
     *
     * @param toolTip       The tool tip text. It can be plain text or HTML
     *                      format.
     * @param cvDescription The CV description text.
     * @param mask          The bit mask, a (list of) string containing only the
     *                      characters 'V' &amp; 'X', with 'V' signifying a used
     *                      bit.
     * @return The original tool tip text plus (if the Roster Preferences allow)
     *         a parenthesized CV and bit mask description.
     */
    /*public*/ /*static*/ QString CvUtil::addCvDescription(QString toolTip, QString cvDescription, QString mask) {
        QString descString = cvDescription;
        QString maskDescString = getMaskDescription(mask);
        if (maskDescString.length() > 0 && !cvDescription.endsWith(".")) {
            // skip overridden getCvDescription() that already includes maskDescription, eg SplitVariableValue
            descString = descString + " " + maskDescString;
        }
        if (PaneProgFrame::getShowCvNumbers() && (descString != "")) {
            if (toolTip == "" || toolTip.length() < 1) {
                toolTip = descString;
            } else {
                toolTip = StringUtil::concatTextHtmlAware(toolTip, " (" + descString + ")");
            }
        } else if (toolTip == "") {
            toolTip = "";

        }
        return toolTip;
    }

    /**
     * Generate bit numbers from a bit mask if applicable.
     *
     * @param mask A string containing only the characters 'V' &amp; 'X',
     *             with 'V' signifying a used bit.
     * @return A plain text description of the used bits. (For example, "bits
     *         0-3,7" from the string "VXXXVVVV".) Empty String
     *         if not applicable
     */
    /*public*/ /*static*/ QString CvUtil::getMaskDescription(QString mask) {
        QString maskDescString;// = new StringBuilder();
        if ((mask != "") && (mask.contains("X"))) {
            int lastBit = mask.length() - 1;
            int lastV = -2;
            if (mask.contains("V")) {
                if (mask.indexOf('V') == mask.lastIndexOf('V')) {
                    maskDescString.append("bit ").append(QString::number(lastBit - mask.indexOf('V')));
                } else {
                    maskDescString.append("bits ");
                    for (int i = 0; i <= lastBit; i++) {
                        QChar descStringLastChar = maskDescString.at(maskDescString.length() - 1);
                        if (mask.at(lastBit - i) == 'V') {
                            if (descStringLastChar == ' ') {
                                maskDescString.append(QString::number(i));
                            } else if (lastV == (i - 1)) {
                                if (descStringLastChar != '-') {
                                    maskDescString.append("-");
                                }
                            } else {
                                maskDescString.append(",").append(QString::number(i));
                            }
                            lastV = i;
                        }
                        descStringLastChar = maskDescString.at(maskDescString.length() - 1);
                        if ((descStringLastChar == '-') && ((mask.at(lastBit - i) != 'V') || (i == lastBit))) {
                            maskDescString.append(QString::number(lastV));
                        }
                    }
                }
            } else {
                maskDescString.append("no bits");
            }
            log->trace(tr("%1 Mask:%2").arg(maskDescString).arg(mask));
        }
        return maskDescString/*.toString()*/;
    }

    /*private*/ /*final*/ /*static*/ Logger* CvUtil::log = LoggerFactory::getLogger("CvUtil");
