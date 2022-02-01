#include "swingconfiguratorinterface.h"
#include "jlabel.h"
/**
 * The parent interface for configuring classes with Swing.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  interface SwingConfiguratorInterface {



    /**
     * Parses the message and creates a list of components there the given
     * components are separated by JLabel components from the message.
     * @param message the message to be parsed
     * @param components the components
     * @return the components separated with JLabel components
     */
    /*public*/  /*static*/ QList<JComponent*> SwingConfiguratorInterface::parseMessage(QString message, QList<JComponent*> components) {
        QList<JComponent*> componentsToReturn = QList<JComponent*>();
        class QString sb = "";
        bool parseNumber = false;

        for (int index=0; index < message.length(); index++) {
            QChar character = message./*codePointAt*/at(index);

            if (parseNumber) {
                if (character == '}') {
                    int number = (sb.toInt());
                    componentsToReturn.append(components[number]);
                    sb = "";
                    parseNumber = false;
                } else if ((character >= '0') && (character <= '9')) {
                    sb./*appendCodePoint*/append(character);
                } else {
                    throw new IllegalArgumentException(
                            QString("left curly bracket must be followed by a digit but is followed by ")
                                    + /*Arrays.toString(Character.toChars*/(character));
                }
            } else {
                if (character == '{') {
                    parseNumber = true;
                    componentsToReturn.append(new JLabel(sb));
                    sb = "";
                } else {
                    sb.append/*CodePoint*/(character);
                }
            }
        }

        if (sb.length() > 0) componentsToReturn.append(new JLabel(sb));

        return componentsToReturn;
    }
