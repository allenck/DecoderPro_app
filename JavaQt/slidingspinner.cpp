#include "slidingspinner.h"
#include "colorpanel.h"
#include "jcomponent.h"
#include "jslider.h"
#include "jspinner.h"
#include "spinnernumbermodel.h"

SlidingSpinner::SlidingSpinner(QObject *parent) : ChangeListener()
{

}
/*
 * Copyright (c) 2008, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General publicLicense
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

//package javax.swing.colorchooser;

//import javax.swing.JComponent;
//import javax.swing.JSlider;
//import javax.swing.JSpinner;
//import javax.swing.JSpinner.DefaultEditor;
//import javax.swing.SpinnerNumberModel;
//import javax.swing.event.ChangeEvent;
//import javax.swing.event.ChangeListener;

///*final*/ class SlidingSpinner implements ChangeListener {


SlidingSpinner::SlidingSpinner(ColorPanel* panel, QWidget* label, QObject *parent)
 : ChangeListener() {
 model = new SpinnerNumberModel();
 slider = new JSlider();
 spinner = new JSpinner(this->model);

    this->panel = panel;
    this->label = label;
    this->slider->addChangeListener(this);
    this->spinner->addChangeListener(this);
//    DefaultEditor editor = (DefaultEditor) this->spinner.getEditor();
//    ValueFormatter.init(3, false, editor.getTextField());
//    editor.setFocusable(false);
//    this->spinner.setFocusable(false);
}

QWidget *SlidingSpinner::getLabel() {
    return this->label;
}

JSlider* SlidingSpinner::getSlider() {
    return this->slider;
}

JSpinner* SlidingSpinner::getSpinner() {
    return this->spinner;
}

float SlidingSpinner::getValue() {
    return this->value;
}

void SlidingSpinner::setValue(float value) {
    int min = this->slider->minimum();
    int max = this->slider->maximum();
    this->internal = true;
    this->slider->setValue(min + (int) (value * (float) (max - min)));
    this->spinner->setValue((this->slider->getValue()));
    this->internal = false;
    this->value = value;
}

void SlidingSpinner::setRange(int min, int max) {
    this->internal = true;
    this->slider->setMinimum(min);
    this->slider->setMaximum(max);
    this->model->setMinimum((min));
    this->model->setMaximum((max));
    this->internal = false;
}

void SlidingSpinner::setVisible(bool visible) {
//    ((QWidget*)this->label)->setVisible(visible);
    slider->setVisible(visible);
    spinner->setVisible(visible);
}

bool SlidingSpinner::isVisible() {
    return this->slider->isVisible();
}

/*public*/ void SlidingSpinner::stateChanged(ChangeEvent* event)
{
 if (!this->internal) {
    if (this->spinner == event->getSource()) {
        /*Object*/int value = this->spinner->getValue();
        //if (value instanceof Integer) {
            this->internal = true;
            this->slider->setValue( value);
            this->internal = false;
        }
    }
    int value = this->slider->getValue();
    this->internal = true;
    this->spinner->setValue((value));
    this->internal = false;
    int min = this->slider->minimum();
    int max = this->slider->maximum();
    this->value = (float) (value - min) / (float) (max - min);
    this->panel->colorChanged();
}

