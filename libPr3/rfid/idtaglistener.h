#ifndef IDTAGLISTENER_H
#define IDTAGLISTENER_H
#include "idtag.h"

/**
 * Connect to an IdTag
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
/*public*/ /*interface*/class IdTagListener : public QObject{
Q_OBJECT
public:
 explicit IdTagListener(QObject *parent = 0);
    /*public*/ virtual void notify(IdTag* r)=0;

};
//Q_DECLARE_INTERFACE(IdTagListener, "IdTagListener")
#endif // IDTAGLISTENER_H
