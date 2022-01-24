#include "physicallocationpanel.h"
#include "loggerfactory.h"
#include "borderfactory.h"
#include "gridbaglayout.h"
#include "physicallocation.h"

/**
 * Provides a Swing component to show and/or edit a PhysicalLocation
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General public  License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General public  License
 * for more details.
 *
 * @author Mark Underwood Copyright (C) 2011
 */
// /*public*/  class PhysicalLocationPanel extends JPanel {



    /**
     * Constructor
     */
    /*public*/  PhysicalLocationPanel::PhysicalLocationPanel(QWidget* parent) : JPanel(parent) {
        //super();
        initComponents("");
    }

    /**
     * Constructor
     *
     * @param title (String) : Window title
     */
    /*public*/  PhysicalLocationPanel::PhysicalLocationPanel(QString title, QWidget* parent) : JPanel(parent) {
        //super();
        initComponents(title);
    }

    /*private*/ GridBagConstraints PhysicalLocationPanel::setConstraints(int x, int y, bool /*fill*/) {
        GridBagConstraints gbc1 = GridBagConstraints();
        gbc1.insets = new Insets(2, 2, 2, 2);
        gbc1.gridx = x;
        //gbc1.gridx = GridBagConstraints.RELATIVE;
        gbc1.gridy = y;
        gbc1.weightx = 100.0;
        gbc1.weighty = 100.0;
        gbc1.gridwidth = 1;
        gbc1.anchor = GridBagConstraints::LINE_START;
        return (gbc1);
    }

    /*protected*/ void PhysicalLocationPanel::initComponents(QString title) {

        tb = BorderFactory::createTitledBorder(BorderFactory::createEtchedBorder(EtchedBorder::LOWERED), title);
        tb->setTitlePosition(TitledBorder::DEFAULT_POSITION);
        GridBagLayout* thisLayout;
        this->setLayout(thisLayout = new GridBagLayout());

        this->setBorder(tb);


        xs = new JSpinner(new SpinnerNumberModel(spin_value, min_spin, max_spin, spin_inc));
        ys = new JSpinner(new SpinnerNumberModel(spin_value, min_spin, max_spin, spin_inc));
        zs = new JSpinner(new SpinnerNumberModel(spin_value, min_spin, max_spin, spin_inc));

        JLabel* xl = new JLabel("X");
        JLabel* yl = new JLabel("Y");
        JLabel* zl = new JLabel("Z");

        thisLayout->addWidget(xl, setConstraints(0, 0, false));
        thisLayout->addWidget(xs, setConstraints(GridBagConstraints::_RELATIVE, 0, true));
        thisLayout->addWidget(yl, setConstraints(GridBagConstraints::_RELATIVE, 0, false));
        thisLayout->addWidget(ys, setConstraints(GridBagConstraints::_RELATIVE, 0, true));
        thisLayout->addWidget(zl, setConstraints(GridBagConstraints::_RELATIVE, 0, false));
        thisLayout->addWidget(zs, setConstraints(GridBagConstraints::_RELATIVE, 0, true));

        this->setVisible(true);
        log->debug("initComponents() complete");
    }

    /**
     * Set the window tile
     *
     * @param t : new title
     */
    /*public*/  void PhysicalLocationPanel::setTitle(QString t) {
        tb->setTitle(t);
    }

    /**
     * Retrieve the window title
     *
     * @return (String) title
     */
    /*public*/  QString PhysicalLocationPanel::getTitle() {
        return (tb->getTitle());
    }

    /**
     * Set the value of the pane
     *
     * @param p (PhysicalLocation) : value to set
     */
    /*public*/  void PhysicalLocationPanel::setValue(PhysicalLocation* p) {
        xs->setValue(p->getX());
        ys->setValue(p->getY());
        zs->setValue(p->getZ());
    }

    /**
     * Set the value of the pane
     *
     * @param s (String) : value to set
     */
    /*public*/  void PhysicalLocationPanel::setValue(QString s) {
        PhysicalLocation* p = PhysicalLocation::parse(s);
        if (p != nullptr) {
            this->setValue(p);
        }
    }

    /**
     * Get the value of the pane
     *
     * @return PhysicalLocation : Current value of pane
     */
    /*public*/  PhysicalLocation* PhysicalLocationPanel::getValue() {
        float x = (float) ((SpinnerNumberModel*) xs->getModel())->getNumber().toFloat();
        float y = (float) ((SpinnerNumberModel*) ys->getModel())->getNumber().toFloat();
        float z = (float) ((SpinnerNumberModel*) zs->getModel())->getNumber().toFloat();
        return (new PhysicalLocation(x, y, z));

    }

    /*private*/ /*static*/ /*final*/ Logger* PhysicalLocationPanel::log = LoggerFactory::getLogger("PhysicalLocationPanel");
