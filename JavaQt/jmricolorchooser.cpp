#include "jmricolorchooser.h"
#include <QColorDialog>
#include "jcolorchooser.h"
#include "jmricolorchooserpanel.h"
#include "colorchooserdialog.h"
#include "colorchooserpanel.h"

/**
 * Display the Java color chooser that includes a custom JMRI panel.
 * The custom panel is provided by {@link JmriColorChooserPanel}.
 * <p>
 * Maintain a list of recently used colors.  This includes colors found
 * during loading and subsequent changes.
 * @author Dave Sand Copyright (C) 2018
 * @since 4.13.1
 */
// /*public*/ class JmriColorChooser {

    /**
     * The colors used by the current JMRI session.
     * The XML loading process creates the initial list and
     * subsequent activity will add new colors.
     */
    /*static*/ /*private*/ QList<QColor> JmriColorChooser::recentColors = QList<QColor>();

    /**
     * Add a new color to the recent list.
     * Null values and duplicates are not added.
     * @param color The color object to be added.
     */
    /*static*/ /*public*/ void JmriColorChooser::addRecentColor(QColor color) {
//        if (color == QColor() || !color.toString().contains("java.awt.Color")) {
//            // Ignore null or default system colors
//            return;
//        }
        if (!recentColors.contains(color)) {
            recentColors.append(color);
        }
    }

    /**
     * Provide a copy of the recent color list.
     * This is used by {@link JmriColorChooserPanel} to build
     * the recent color list.
     * @return the recent color list.
     */
    /*static*/ /*public*/ QList<QColor> JmriColorChooser::getRecentColors() {
        return QList<QColor>(recentColors);
    }

    /**
     * The number of tabs in the color chooser, 5 standard plus the custom JMRI tab
     */
    /*static*/ /*final*/ int JmriColorChooser::COLOR_TAB_COUNT = 6;
    /*static*/ QColor JmriColorChooser::color = QColor();

    /**
     * Display the customized color selection dialog.
     * The JMRI custom panel is added before the Java supplied panels so that
     * it will be the default panel.
     * @param comp The calling component.  It is not used but provided to simplify migration.
     * @param dialogTitle The title at the top of the dialog.
     * @param currentColor The color that will be set as the starting value for the dialog.
     * @return the selected color for a OK response, the orignal color for a Cancel response.
     */
    /*static*/ /*public*/ QColor JmriColorChooser::showDialog(QWidget* comp, QString dialogTitle, QColor currentColor) {
        color = currentColor == QColor() ? QColor(Qt::white) : currentColor;
        QString title = dialogTitle == "" ? "" : dialogTitle;
        JColorChooser* chooser = extendColorChooser(new JColorChooser(color));
        //JCCActionListener* listener = new JCCActionListener(chooser, this);
        JDialog* d = JColorChooser::createDialog(nullptr, title, true, chooser, nullptr,nullptr);
//            ((ActionEvent e) -> {
//                color = chooser.getColor();
//            }),
//            null);
        d->setVisible(true);

        //_chooser->setOption(QColorDialog::NoButtons);
        color = chooser->getColor();
        return color;
    }

    /**
     * Add or replace the JMRI custom panel at the beginning of the chooser tabs
     * @param chooser The chooser object to be updated.
     * @return the updated chooser object
     */
     /*static*/ /*public*/ JColorChooser* JmriColorChooser::extendColorChooser(JColorChooser* chooser) {
        QVector<AbstractColorChooserPanel*>* currPanels = chooser->getChooserPanels();
        QVector<AbstractColorChooserPanel*>* newPanels = new QVector<AbstractColorChooserPanel*>(COLOR_TAB_COUNT);

        newPanels->replace(0, new JmriColorChooserPanel());
        newPanels->at(0)->installChooserPanel(chooser);
        int idx = 1;
        for (int i = 0; i < currPanels->length(); i++) {
            if (currPanels->at(i)->getDisplayName() != ("JMRI")) {  // NOI18N
                // Copy non JMRI panels
                newPanels->replace(idx, currPanels->at(i));
                idx++;
            }
        }

        chooser->setChooserPanels(newPanels);
        return chooser;
    }
