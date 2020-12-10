#ifndef SIGNALHEAD_H
#define SIGNALHEAD_H
#include "namedbean.h"
#include "abstractnamedbean.h"
#include "libPr3_global.h"
#include <QVector>
#include "../Signal/signals.h"

class LIBPR3SHARED_EXPORT SignalHead /*: public NamedBean*/ : public Signals
{
 Q_OBJECT
public:
 explicit SignalHead(QObject *parent = 0)  : Signals(parent) {}
     SignalHead(QString systemName, QObject* parent) : Signals(systemName, parent) {}
     SignalHead(QString systemName, QString userName, QObject* parent) : Signals(systemName, userName, parent) {}
    /**
     * Represent a single signal head. (Try saying that ten times fast!)
     * A signal may have more than one of these
     * (e.g. a signal mast consisting of several heads)
     * when needed to represent more complex aspects, e.g. Diverging Appoach
     * etc.
     * <P>
     * Initially, this allows access to explicit appearance information. We
     * don't call this an Aspect, as that's a composite of the appearance
     * of several heads.
     * <P>
     * This class has three bound parameters:
     *<DL>
     *<DT>appearance<DD>The specific color being shown. Values are the
     * various color constants defined in the class.
     * <p>
     * The appearance constants form a bit mask, so they can
     * be used with hardware that can display e.g. more than one lit
     * color at a time.  Individual implementations may not be
     * able to handle that, however; most of the early ones
     * probably won't. If a particular implementation can't display
     * a commanded color, it doesn't try to replace it, but rather
     * just leaves that color off the resulting display.
     *<DT>lit<DD>Whether the head's lamps are lit or left dark.
     *<P>
     * This differs from the DARK color defined for the appearance
     * parameter, in that it's independent of that.  Lit is
     * intended to allow you to extinquish a signal head for
     * approach lighting, while still allowing it's color to be
     * set to a definite value for e.g. display on a panel or
     * evaluation in higher level logic.
     *
     *<DT>held<DD>Whether the head's lamps should be forced to the RED position
     * in higher-level logic.
     *<P>
     * For use in signaling systems, this is a convenient
     * way of storing whether a higher-level of control (e.g. non-vital
     * system or dispatcher) has "held" the signal at stop. It does
     * not effect how this signal head actually works; any appearance can
     * be set and will be displayed even when "held" is set.
     *</dl>
     *
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
     * @author			Bob Jacobsen Copyright (C) 2002, 2008
     * @version			$Revision: 21535 $
     */
//    virtual interface SignalHead extends NamedBean {

//        const static int DARK;//        = 0x00;
//        const static int RED;//         = 0x01;
//        const static int FLASHRED;//    = 0x02;
//        const static int YELLOW;//      = 0x04;
//        const static int FLASHYELLOW;// = 0x08;
//        const static int GREEN;//       = 0x10;
//        const static int FLASHGREEN;//  = 0x20;
//        const static int LUNAR;//       = 0x40;
//        const static int FLASHLUNAR;//  = 0x80;
//        const static int HELD;// 		= 0x0100;
      enum eState
      {
        DARK        = 0x00,
        RED         = 0x01,
        FLASHRED    = 0x02,
        YELLOW      = 0x04,
        FLASHYELLOW = 0x08,
        GREEN       = 0x10,
        FLASHGREEN  = 0x20,
        LUNAR       = 0x40,
        FLASHLUNAR  = 0x80,
        HELD 	    = 0x0100
      };
      Q_ENUM(eState)

      /**
       * Get the Signal Head Appearance.
       * Changes in this value can be listened to using the
       * {@literal Appearance} property.
       *
       * @return the appearance
       */
      /*public*/virtual int getAppearance() =0;


      /**
       * Set the Signal Head Appearance.
       *
       * @param newAppearance integer representing a valid Appearance for this head
       */
      /*public*/ virtual void setAppearance(int /*newAppearance*/) {}

      /*public*/ virtual QString getAppearanceName() {return "";}

      /*public*/ virtual QString getAppearanceName(int /*appearance*/) {return "";}

      /**
         * Lit is a bound parameter. It controls
         * whether the signal head's lamps are lit or left dark.
         */
        virtual bool getLit() {return false;}
        virtual void setLit(bool /*newLit*/) {}

        /**
         * Held is a bound parameter. It controls
         * what mechanisms can control the head's appearance.
         * The actual semantics are defined by those external mechanisms.
         */
        virtual bool getHeld() {return false;}
        virtual void setHeld(bool /*newHeld*/) {}

        virtual QVector<int> getValidStates() {return QVector<int>();}
      /**
       * Get an array of non-localized appearance keys valid for the mast type.
       * For GUI application consider using (capitalized) {@link #getValidStateNames()}
       *
       * @return array of translated appearance names available on this mast type
       */
      /*public*/ virtual QVector<QString> getValidStateKeys() {return QVector<QString>();}
      virtual QVector<QString> getValidStateNames() {return QVector<QString>();}

signals:
    
public slots:
    
};

#endif // SIGNALHEAD_H
