#include "notchtransition.h"

//NotchTransition::NotchTransition()
//{
//}
/* NotchTransition
 *
 * This class holds the information needed about a transitional sound
 * between notches of a Diesel locomotive engine.
 */
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
 * @version			$Revision: 18233 $
 */
//class NotchTransition extends SoundBite {


/*public*/ NotchTransition::NotchTransition(QString name, QObject*parent) : SoundBite(name, parent) {
        //super(name);
        prev_notch = 0;
        next_notch = 0;
        length = 0;
    }

    /*public*/ NotchTransition::NotchTransition(VSDFile* vf, QString filename, QString sname, QString uname, QObject*parent) : SoundBite(vf, filename, sname, uname, parent) {
        //super(vf, filename, sname, uname);
        prev_notch = 0;
        next_notch = 0;
        this->setLength();
    }

    /*public*/ int NotchTransition::getPrevNotch() {
        return (prev_notch);
    }

    /*public*/ int NotchTransition::getNextNotch() {
        return (next_notch);
    }

    /*public*/ void NotchTransition::setPrevNotch(int p) {
        prev_notch = p;
    }

    /*public*/ void NotchTransition::setNextNotch(int p) {
        next_notch = p;
    }
