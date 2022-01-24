#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include<QVector>
#include "javaqt_global.h"
#include <QTimeZone>

class QTimeZone;
class JAVAQTSHARED_EXPORT Calendar : public QObject
{
    Q_OBJECT
public:
enum Fields
{
     ERA = 0,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * year. This is a calendar-specific value; see subclass documentation.
     */
     YEAR = 1,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * month. This is a calendar-specific value. The first month of
     * the year in the Gregorian and Julian calendars is
     * <code>JANUARY</code> which is 0; the last depends on the number
     * of months in a year.
     *
     * @see #JANUARY
     * @see #FEBRUARY
     * @see #MARCH
     * @see #APRIL
     * @see #MAY
     * @see #JUNE
     * @see #JULY
     * @see #AUGUST
     * @see #SEPTEMBER
     * @see #OCTOBER
     * @see #NOVEMBER
     * @see #DECEMBER
     * @see #UNDECIMBER
     */
     MONTH = 2,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * week number within the current year.  The first week of the year, as
     * defined by <code>getFirstDayOfWeek()</code> and
     * <code>getMinimalDaysInFirstWeek()</code>, has value 1.  Subclasses define
     * the value of <code>WEEK_OF_YEAR</code> for days before the first week of
     * the year.
     *
     * @see #getFirstDayOfWeek
     * @see #getMinimalDaysInFirstWeek
     */
     WEEK_OF_YEAR = 3,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * week number within the current month.  The first week of the month, as
     * defined by <code>getFirstDayOfWeek()</code> and
     * <code>getMinimalDaysInFirstWeek()</code>, has value 1.  Subclasses define
     * the value of <code>WEEK_OF_MONTH</code> for days before the first week of
     * the month.
     *
     * @see #getFirstDayOfWeek
     * @see #getMinimalDaysInFirstWeek
     */
     WEEK_OF_MONTH = 4,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * day of the month. This is a synonym for <code>DAY_OF_MONTH</code>.
     * The first day of the month has value 1.
     *
     * @see #DAY_OF_MONTH
     */
     DATE = 5,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * day of the month. This is a synonym for <code>DATE</code>.
     * The first day of the month has value 1.
     *
     * @see #DATE
     */
     DAY_OF_MONTH = 5,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the day
     * number within the current year.  The first day of the year has value 1.
     */
     DAY_OF_YEAR = 6,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the day
     * of the week.  This field takes values <code>SUNDAY</code>,
     * <code>MONDAY</code>, <code>TUESDAY</code>, <code>WEDNESDAY</code>,
     * <code>THURSDAY</code>, <code>FRIDAY</code>, and <code>SATURDAY</code>.
     *
     * @see #SUNDAY
     * @see #MONDAY
     * @see #TUESDAY
     * @see #WEDNESDAY
     * @see #THURSDAY
     * @see #FRIDAY
     * @see #SATURDAY
     */
     DAY_OF_WEEK = 7,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * ordinal number of the day of the week within the current month. Together
     * with the <code>DAY_OF_WEEK</code> field, this uniquely specifies a day
     * within a month.  Unlike <code>WEEK_OF_MONTH</code> and
     * <code>WEEK_OF_YEAR</code>, this field's value does <em>not</em> depend on
     * <code>getFirstDayOfWeek()</code> or
     * <code>getMinimalDaysInFirstWeek()</code>.  <code>DAY_OF_MONTH 1</code>
     * through <code>7</code> always correspond to <code>DAY_OF_WEEK_IN_MONTH
     * 1</code>; <code>8</code> through <code>14</code> correspond to
     * <code>DAY_OF_WEEK_IN_MONTH 2</code>, and so on.
     * <code>DAY_OF_WEEK_IN_MONTH 0</code> indicates the week before
     * <code>DAY_OF_WEEK_IN_MONTH 1</code>.  Negative values count back from the
     * end of the month, so the last Sunday of a month is specified as
     * <code>DAY_OF_WEEK = SUNDAY, DAY_OF_WEEK_IN_MONTH = -1</code>.  Because
     * negative values count backward they will usually be aligned differently
     * within the month than positive values.  For example, if a month has 31
     * days, <code>DAY_OF_WEEK_IN_MONTH -1</code> will overlap
     * <code>DAY_OF_WEEK_IN_MONTH 5</code> and the end of <code>4</code>.
     *
     * @see #DAY_OF_WEEK
     * @see #WEEK_OF_MONTH
     */
     DAY_OF_WEEK_IN_MONTH = 8,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating
     * whether the <code>HOUR</code> is before or after noon.
     * E.g., at 10:04:15.250 PM the <code>AM_PM</code> is <code>PM</code>.
     *
     * @see #AM
     * @see #PM
     * @see #HOUR
     */
     AM_PM = 9,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * hour of the morning or afternoon. <code>HOUR</code> is used for the
     * 12-hour clock (0 - 11). Noon and midnight are represented by 0, not by 12.
     * E.g., at 10:04:15.250 PM the <code>HOUR</code> is 10.
     *
     * @see #AM_PM
     * @see #HOUR_OF_DAY
     */
     HOUR = 10,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * hour of the day. <code>HOUR_OF_DAY</code> is used for the 24-hour clock.
     * E.g., at 10:04:15.250 PM the <code>HOUR_OF_DAY</code> is 22.
     *
     * @see #HOUR
     */
     HOUR_OF_DAY = 11,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * minute within the hour.
     * E.g., at 10:04:15.250 PM the <code>MINUTE</code> is 4.
     */
     MINUTE = 12,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * second within the minute.
     * E.g., at 10:04:15.250 PM the <code>SECOND</code> is 15.
     */
     SECOND = 13,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * millisecond within the second.
     * E.g., at 10:04:15.250 PM the <code>MILLISECOND</code> is 250.
     */
     MILLISECOND = 14,

    /**
     * Field number for <code>get</code> and <code>set</code>
     * indicating the raw offset from GMT in milliseconds.
     * <p>
     * This field reflects the correct GMT offset value of the time
     * zone of this <code>Calendar</code> if the
     * <code>TimeZone</code> implementation subclass supports
     * historical GMT offset changes.
     */
     ZONE_OFFSET = 15,

    /**
     * Field number for <code>get</code> and <code>set</code> indicating the
     * daylight saving offset in milliseconds.
     * <p>
     * This field reflects the correct daylight saving offset value of
     * the time zone of this <code>Calendar</code> if the
     * <code>TimeZone</code> implementation subclass supports
     * historical Daylight Saving Time schedule changes.
     */
     DST_OFFSET = 16,

    /**
     * The number of distinct fields recognized by <code>get</code> and <code>set</code>.
     * Field numbers range from <code>0..FIELD_COUNT-1</code>.
     */
     FIELD_COUNT = 17
};
enum STAMPVALS
{
    // Special values of stamp[]
    /**
     * The corresponding fields[] has no value.
     */
    UNSET = 0,

    /**
     * The value of the corresponding fields[] has been calculated internally.
     */
    COMPUTED = 1,

    /**
     * The value of the corresponding fields[] has been set externally. Stamp
     * values which are greater than 1 represents the (pseudo) time when the
     * corresponding fields[] value was set.
     */
    MINIMUM_USER_STAMP = 2

};
/**
 * Value of the {@link #AM_PM} field indicating the
 * period of the day from midnight to just before noon.
 */
 /*public*/ /*final*/ static int AM ;//= 0;
/**
 * Value of the {@link #AM_PM} field indicating the
 * period of the day from noon to just before midnight.
 */
/*public*/ /*final*/ static int PM;// = 1;

/*public*/ int get(int field);
/*public*/ static Calendar* getInstance();
/*public*/ static Calendar* getInstance(QTimeZone zone);
/*public*/ static Calendar* getInstance(QLocale aLocale);
/*public*/ static Calendar* getInstance(QTimeZone zone, QLocale aLocale);
/*public*/ void set(int field, int value);
/*public*/ /*final*/ void set(int year, int month, int date);
/*public*/ /*final*/ void set(int year, int month, int date, int hourOfDay, int minute);
/*public*/ /*final*/ void set(int year, int month, int date, int hourOfDay, int minute,
                      int second);
/*public*/ /*final*/ QDateTime getTime();
/*public*/ /*final*/ void setTime(QDateTime date);


signals:

public slots:
private:
 bool sharedZone;
 QVector<int> fields;
 /*private*/ void updateTime();
 /*private*/ static Calendar* createCalendar(QTimeZone zone, QLocale aLocale);

 /**
  * True if all fields have been set.
  * @serial
  */
 /*transient*/ bool       areAllFieldsSet;
 QVector<bool> isSet;
 QVector<int>  stamp;
 QTimeZone zone;
 /*private*/ void setWeekCountData(QLocale desiredLocale);
 /*private*/ void internalSet(int field, int value);
 /*private*/ int             nextStamp;// = MINIMUM_USER_STAMP;
 /*private*/ void adjustStamp();

protected:
/*protected*/ Calendar(QObject* parent = 0);
 /*protected*/ /*final*/ int internalGet(int field);
 /*protected*/ void complete();
 /**
  * True if then the value of <code>time</code> is valid.
  * The time is made invalid by a change to an item of <code>field[]</code>.
  * @see #time
  * @serial
  */
 //@SuppressWarnings("ProtectedField")
 /*protected*/ bool       isTimeSet =false;
 /*protected*/ /*abstract*/ virtual void computeTime();
 /**
  * True if <code>fields[]</code> are in sync with the currently set time.
  * If false, then the next attempt to get the value of a field will
  * force a recomputation of all fields from the current value of
  * <code>time</code>.
  * @serial
  */
 //@SuppressWarnings("ProtectedField")
 /*protected*/ bool       areFieldsSet;
 /*protected*/ /*abstract*/ virtual void computeFields();
 /*protected*/ Calendar(QTimeZone zone, QLocale aLocale);

};

#endif // CALENDAR_H
