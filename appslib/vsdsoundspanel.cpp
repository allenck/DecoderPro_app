#include "vsdsoundspanel.h"
#include <QGridLayout>
#include "vsdecoderpane.h"
#include "logger.h"
#include "soundevent.h"
#include "vsdecoder.h"
#include <QAbstractButton>

//VSDSoundsPanel::VSDSoundsPanel(QWidget *parent) :
//  JmriPanel(parent)
//{
//}
/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 28746 $
 */
//import java.awt.GridLayout;
//import java.util.ArrayList;
//import jmri.util.swing.JmriPanel;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//@SuppressWarnings("serial")
///*public*/ class VSDSoundsPanel extends JmriPanel {

VSDSoundsPanel::VSDSoundsPanel(QWidget *parent) :
  JmriPanel(parent) {
        //super();
 common();
    }

    /*public*/ VSDSoundsPanel::VSDSoundsPanel(QString dec, VSDecoderPane* dad,QWidget *parent) :
  JmriPanel(parent) {
        //super();
 common();
        decoder_id = dec;
        main_pane = dad;
        initComponents();

    }
void VSDSoundsPanel::common()
{
 this->setObjectName("VSDSoundsPanel");
 log = new Logger("VSDSoundsPanel");
}
/*public*/ void VSDSoundsPanel::init() {
}

/*public*/ void VSDSoundsPanel::initContext(QVariant context) {
    initComponents();
}

/*public*/ void VSDSoundsPanel::initComponents() {

 //this.setLayout(new GridLayout(0, 3));
QGridLayout* thisLayout = new QGridLayout();

 if (main_pane->getDecoder() == NULL)
 {
     log->debug("No decoder!");
     return;
 }

 QList<SoundEvent*>* elist = new QList<SoundEvent*>(main_pane->getDecoder()->getEventList());
 foreach (SoundEvent* e, *elist)
 {
  if (e->getButton() != NULL)
  {
   log->debug("adding button " + e->getButton()->objectName());
  }
  thisLayout->addWidget(e->getButton());
 }
}
