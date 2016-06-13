#include "jmriclockpropertylistener.h"
#include "instancemanager.h"

//JmriClockPropertyListener::JmriClockPropertyListener(QObject *parent) :
//    JmriSimplePropertyListener(parent)
//{
//}
/**
 * A service class for monitoring a bound property
 * in one of the JMRI Named beans
 * For use with properties having two states which are determined
 * by containment in an interval (e.g. Fast Clock ranges).
 * <P>
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
 * @author			Pete Cressman Copyright (C) 2009
 * @version			$Revision 1.0 $
 * @since           2.5.1
 */

///*public*/ class JmriClockPropertyListener extends JmriSimplePropertyListener
//{
    /*static*/ int JmriClockPropertyListener::SIZE = 10;

//@SuppressWarnings("deprecation")
JmriClockPropertyListener::JmriClockPropertyListener(QString propName, int type, QString name, int varType,
                          Conditional* client, int beginTime, int endTime, QObject *parent) : JmriSimplePropertyListener(propName, type, name, varType, client, parent)
{
 //super(propName, type, name, varType, client);
 numRanges = 0;
 _beginTimes = new QList<int>(); //[SIZE];
 _endTimes = new QList<int>();// [SIZE];
 _rangeList = new QList<bool>(); //[SIZE];
 for(int i=0; i < SIZE; i++)
 {
  _beginTimes->append(0);
  _endTimes->append(0);
  _rangeList->append(false);
 }

 _beginTimes->replace(0, fixMidnight(beginTime));
 _endTimes->replace(0, fixMidnight(endTime));
 _rangeList->replace(0, false);
 numRanges = 1;
 _fastClock = InstanceManager::timebaseInstance();
 QDateTime currentTime = _fastClock->getTime();
 _currentMinutes = (currentTime.time().hour()*60) + currentTime.time().minute();
}

/*private*/ int JmriClockPropertyListener::fixMidnight(int time) {
    if (time>24*60)
        time -= 24*60;
    return time;
}

/*public*/ void JmriClockPropertyListener::setRange(int beginTime, int endTime)
{
 if (numRanges >= _rangeList->length())
 {
     QList<int>* temp = new QList<int>(*_beginTimes); //[numRanges+SIZE];
     //System.arraycopy(_beginTimes, 0, temp, 0, _beginTimes.length);
     _beginTimes = temp;
      temp = new QList<int>(*_endTimes); //[numRanges+SIZE];
      //System.arraycopy(_endTimes, 0, temp, 0, _endTimes.length);
      _endTimes = temp;
      QList<bool>* bools = new QList<bool>(*_rangeList); //[numRanges+SIZE];
      //System.arraycopy(_rangeList, 0, bools, 0, _rangeList.length);
      _rangeList = bools;
    }
    _beginTimes->replace(numRanges, fixMidnight(beginTime));
    _endTimes->replace(numRanges,fixMidnight(endTime));
    _rangeList->replace(numRanges, false);
    numRanges++;
}

/**
 * Check if have entered/exited one of the Fast Clock Ranges
 * <P>
 * This method is invoked when the minute listener fires.
 */
//@SuppressWarnings("deprecation")
/*public*/ void JmriClockPropertyListener::propertyChange(PropertyChangeEvent* evt) {
    QDateTime currentTime = _fastClock->getTime();
    //int oldMinutes = _currentMinutes;
    _currentMinutes = (currentTime.time().hour()*60) + currentTime.time().minute();
    // check if we have entered or left one of the ranges
    QList<bool>* newRangeList = new QList<bool>(*_rangeList); //[_rangeList.length];
    for (int i=0; i<numRanges; i++) {
        // check if entered or left desired time range
        if (_beginTimes->at(i)<_endTimes->at(i)) {
            // range not crossing midnight, test ends of range
            if ( (_beginTimes->at(i)<=_currentMinutes) &&  (_currentMinutes<=_endTimes->at(i)) ) {
                newRangeList->replace(i, true);
            } else {
                newRangeList->replace(i, false);
            }
        }
        else { // range crosses midnight
            if ( (_beginTimes->at(i)<=_currentMinutes) ||  (_currentMinutes<=_endTimes->at(i)) ) {
                newRangeList->replace(i, true);
            } else {
                newRangeList->replace(i, false);
            }
        }
        //log.debug("currentMinutes= "+_currentMinutes+" beginTime= "+_beginTimes[i]+
        //          " endTime="+_endTimes[i]+"new= "+newRangeList[i]+" old= "+_rangeList[i]);
    }
    // check for changes
    for (int i=0; i<numRanges; i++) {
        if (_rangeList->at(i) != newRangeList->at(i)) {
            _rangeList = newRangeList;
            JmriSimplePropertyListener::propertyChange(evt);
        }
    }
}
