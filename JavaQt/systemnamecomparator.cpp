#include "systemnamecomparator.h"
#include "exceptions.h"

SystemNameComparator::SystemNameComparator(QObject *parent)
    //:    QObject()
{
}
/**
 * Comparator for JMRI System Names.
 * <P> A System Name is two letters
 * followed by either an alpha name or a number.
 * In the number case, this does a numeric comparison.
 * If the number is appended with letters, does the
 * numeric sort on the digits followed by a lexigraphic
 * sort on the remainder.
 *
 * @author	Bob Jacobsen   Copyright (C) 2004
 * @author  Howard Penny
 * @author  Pete Cressman
 * @version	$Revision: 17977 $
 */

// /*public*/ class SystemNameComparator implements Comparator<Object>, java.io.Serializable {
//    /*public*/ SystemNameComparator() {}

/*public*/ /*static*/ bool SystemNameComparator::compare(const QString &o1, const QString &o2)
{
 if (o1.length() <= 3 && o2.length() <= 3)
 {
  return o1 < (o2);
 }
 else if (/*!o1.regionMatches(0,o2,0,2)*/ o1.mid(0,2) != o2.mid(0,2))
 {
  return o1 < (o2);
 }
 else
 {
  // extract length of digits
  QString ch1 = o1.mid(2);
  QString ch2 = o2.mid(2);
  int numDigit1 = 0;
  int numDigit2 = 0;
  for (int i=0; i<ch1.length(); i++)
  {
   //if (Character.isDigit(ch1[i]))
   if(ch1.at(i).isDigit())
   {
   numDigit1++;
   }
   else
   {
    break;
   }
  }
  for (int i=0; i<ch2.length(); i++)
  {
   if (ch2.at(i).isDigit())
   {
    numDigit2++;
   }
   else
   {
    break;
   }
  }
  //if (numDigit1==numDigit2)
  if(numDigit1 > 0 && numDigit2 > 0)
  {
   try
   {
    //int diff = Integer.parseInt(new String(ch1, 0, numDigit1)) -                              Integer.parseInt(new String(ch2, 0, numDigit2));
    int diff = ch1.mid(0,numDigit1).toInt() - ch2.mid(0,numDigit2).toInt();
    if (diff != 0)
    {
     //return diff;
     if(diff < 0)
      return true;
     else return false;
    }
    return false;
#if 0
    if (numDigit1==ch1.length() && numDigit2==ch2.length())
    {
     //return diff;
     if(diff >= 0)
      return true;
     else return false;
    }
    else
    {
     if (numDigit1==ch1.length())
     {
      return -1;
     }
    // both have non-digit chars remaining
//    return new String(ch1, numDigit1, ch1.length-numDigit1) < (
//                    new String(ch2, numDigit2, ch2.length-numDigit2));
     return ch1.mid(numDigit1, ch1.length()-numDigit1) < ch2.mid(numDigit2, ch2.length()-numDigit2);
    }
#endif
   }
   catch (NumberFormatException* nfe)
   {
    return o1.compare(o2);
   }
   catch (IndexOutOfBoundsException ioob)
   {
    return o1.compare(o2);
   }
  }
  else
  {
   //return (numDigit1 - numDigit2);
   return o1 < o2;
  }
 }
}
//}
