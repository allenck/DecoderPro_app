#include "control.h"
#include "xml.h"
#include "logger.h"
#include <QDomElement>

//Control::Control(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{
/**
 * Controls for operations developers. Debug Property changes and instance
 * creation, maximum panel width, etc.
 *
 * @author Daniel Boudreau Copyright (C) 2008
 *
 */
//@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "MS_CANNOT_BE_FINAL")
///*public*/ class Control {

    // debug flags
    /*public*/ /*static*/ /*final*/ bool Control::showProperty = false;
    /*public*/ /*static*/ /*final*/ bool Control::showInstance = false;

    // Default panel width
    /*public*/ /*static*/ /*final*/ int Control::panelWidth1025 = 1025;
    /*public*/ /*static*/ /*final*/ int Control::panelWidth700 = 700;
    /*public*/ /*static*/ /*final*/ int Control::panelWidth600 = 600;
    /*public*/ /*static*/ /*final*/ int Control::panelWidth500 = 500;
    /*public*/ /*static*/ /*final*/ int Control::panelWidth400 = 400;
    /*public*/ /*static*/ /*final*/ int Control::panelWidth300 = 300;

    // Default panel height
    /*public*/ /*static*/ /*final*/ int Control::panelHeight600 = 600;
    /*public*/ /*static*/ /*final*/ int Control::panelHeight500 = 500;
    /*public*/ /*static*/ /*final*/ int Control::panelHeight400 = 400;
    /*public*/ /*static*/ /*final*/ int Control::panelHeight300 = 300;
    /*public*/ /*static*/ /*final*/ int Control::panelHeight250 = 250;
    /*public*/ /*static*/ /*final*/ int Control::panelHeight200 = 200;
    /*public*/ /*static*/ /*final*/ int Control::panelHeight100 = 100;

    /*
     stati/ Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
     // Maximum panel height
     public static final int Control::panelMaxHeight = screenSize.height;
     */

    // Default panel edit locations
    /*public*/ /*static*/ /*final*/ int Control::panelX = 0;
    /*public*/ /*static*/ /*final*/ int Control::panelY = 0;

    // Train build parameters
    //@//edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "MS_SHOULD_BE_FINAL") // allow access for testing
    /*public*/ /*static*/ bool Control::fullTrainOnly = false;

    // Car and Engine attribute maximum string length
    /*public*/ /*static*/ int Control::max_len_string_attibute = 12;

    // Car and Engine number maximum string length
    /*public*/ /*static*/ int Control::max_len_string_road_number = 10;

    // Car and Engine number maximum string length when printing
    /*public*/ /*static*/ int Control::max_len_string_print_road_number = 6;

    // Location name maximum string length
    /*public*/ /*static*/ int Control::max_len_string_location_name = 25;

    // Track name maximum string length
    /*public*/ /*static*/ int Control::max_len_string_track_name = 25;

    // Track length maximum string length
    /*public*/ /*static*/ int Control::max_len_string_track_length_name = 5;

    // Car and Engine length maximum string length
    /*public*/ /*static*/ int Control::max_len_string_length_name = 4;

    // Car weight maximum string length
    /*public*/ /*static*/ int Control::max_len_string_weight_name = 4;

    // Car and Engine built date maximum string length
    /*public*/ /*static*/ int Control::max_len_string_built_name = 5;

    // Train name maximum string length
    /*public*/ /*static*/ int Control::max_len_string_train_name = 25;

    // Route name maximum string length
    /*public*/ /*static*/ int Control::max_len_string_route_name = 25;

    // Backward compatibility for xml saves (pre 2013 releases)
    // backward compatibility to false in 2014
    /*public*/ /*static*/ bool Control::backwardCompatible = false;

    /*public*/ /*static*/ int Control::reportFontSize = 10;

    /*public*/ /*static*/ QString Control::reportFontName = ""; // use default

    // must synchronize changes with operation-config.dtd
    /*public*/ /*static*/ QDomElement Control::store() {
        QDomElement values;
        QDomElement length;
        QDomElement e = doc.createElement(Xml::CONTROL);
        // backward compatibility default set to false as of 3.7.1 (early 2014)
        e.appendChild(values = doc.createElement(Xml::BACKWARD_COMPATIBILITY));
        values.setAttribute(Xml::SAVE_USING_PRE_2013_FORMAT, backwardCompatible ?Xml::_TRUE :Xml::_FALSE);
        // maximum string lengths
        e.appendChild(values = doc.createElement(Xml::MAXIMUM_STRING_LENGTHS));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_ATTRIBUTE));
        length.setAttribute(Xml::LENGTH, (max_len_string_attibute));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_ROAD_NUMBER));
        length.setAttribute(Xml::LENGTH, (max_len_string_road_number));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_PRINT_ROAD_NUMBER));
        length.setAttribute(Xml::LENGTH, (max_len_string_print_road_number));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_LOCATION_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_location_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_TRACK_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_track_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_TRACK_LENGTH_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_track_length_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_LENGTH_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_length_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_WEIGHT_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_weight_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_BUILT_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_built_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_TRAIN_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_train_name));
        values.appendChild(length = doc.createElement(Xml::MAX_LEN_STRING_ROUTE_NAME));
        length.setAttribute(Xml::LENGTH, (max_len_string_route_name));
        // reports
        e.appendChild(values = doc.createElement(Xml::REPORTS));
        values.setAttribute(Xml::FONT_SIZE, (reportFontSize));
        values.setAttribute(Xml::FONT_NAME, reportFontName);
        return e;
    }

    /*public*/ /*static*/ void Control::load(QDomElement e)
    {
        QDomElement eControl = e.firstChildElement(Xml::CONTROL);
        if (eControl == QDomElement()) {
            return;
        }
        QDomElement backwardCompatibility = eControl.firstChildElement(Xml::BACKWARD_COMPATIBILITY);
        if (backwardCompatibility != QDomElement()) {
            QString format;
            if ((format = backwardCompatibility.attribute(Xml::SAVE_USING_PRE_2013_FORMAT)) != NULL) {
                backwardCompatible = format==(Xml::_TRUE);
            }
        }
        QDomElement maximumStringLengths = eControl.firstChildElement(Xml::MAXIMUM_STRING_LENGTHS);
        if (maximumStringLengths != QDomElement())
        {
            QString length;
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_ATTRIBUTE) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_ATTRIBUTE).attribute(Xml::LENGTH)) != NULL)
            {
             max_len_string_attibute = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_ROAD_NUMBER) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_ROAD_NUMBER).attribute(Xml::LENGTH)) != NULL)
            {
             max_len_string_road_number = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_PRINT_ROAD_NUMBER) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_PRINT_ROAD_NUMBER).attribute(Xml::LENGTH)) != NULL)
            {
                max_len_string_print_road_number = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_LOCATION_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_LOCATION_NAME).attribute(Xml::LENGTH)) != NULL) {
                max_len_string_location_name = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_TRACK_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_TRACK_NAME).attribute(Xml::LENGTH)) != NULL)
            {
             max_len_string_track_name = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_TRACK_LENGTH_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_TRACK_LENGTH_NAME).attribute(Xml::LENGTH)) != NULL)
            {
             max_len_string_track_length_name = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_LENGTH_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_LENGTH_NAME).attribute(Xml::LENGTH)) != NULL)
            {
                max_len_string_length_name = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_WEIGHT_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_WEIGHT_NAME).attribute(Xml::LENGTH)) != NULL)
            {
                max_len_string_weight_name = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_BUILT_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_BUILT_NAME).attribute(Xml::LENGTH)) != NULL)
            {
                max_len_string_built_name = (length).toInt();
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_TRAIN_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_TRAIN_NAME).attribute(Xml::LENGTH)) != NULL)
            {
                max_len_string_train_name = (length.toInt());
            }
            if ((maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_ROUTE_NAME) != QDomElement())
                    && (length = maximumStringLengths.firstChildElement(Xml::MAX_LEN_STRING_ROUTE_NAME).attribute(Xml::LENGTH)) != NULL)
            {
                max_len_string_route_name = (length.toInt());
            }
        }
        QDomElement eReports = eControl.firstChildElement(Xml::REPORTS);
        if (eReports != QDomElement()) {
            QString a;
            if ((a = eReports.attribute(Xml::FONT_SIZE)) != NULL) {
                bool ok;
                    reportFontSize = a.toInt(&ok);
                    if(!ok)
                    {
                    Logger::error(tr("Report font size (%1) isn't a number").arg(a));
                }
            }
            if ((a = eReports.attribute(Xml::FONT_NAME)) != NULL) {
                reportFontName = a;
            }
        }
    }

 QDomDocument Control::doc = QDomDocument();

 void Control::setDoc(QDomDocument doc)
 {
  Control::doc = doc;
 }
}
