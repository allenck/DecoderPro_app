#include "stringutils.h"
#include "exceptions.h"
StringUtils::StringUtils()
{

}
#if 0
/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.apache.commons.lang;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;

import org.apache.commons.lang.text.StrBuilder;

/**
 * <p>Operations on {@link java.lang.String} that are
 * <code>NULL</code> safe.</p>
 *
 * <ul>
 *  <li><b>IsEmpty/IsBlank</b>
 *      - checks if a String contains text</li>
 *  <li><b>Trim/Strip</b>
 *      - removes leading and trailing whitespace</li>
 *  <li><b>Equals</b>
 *      - compares two strings NULL-safe</li>
 *  <li><b>startsWith</b>
 *      - check if a String starts with a prefix NULL-safe</li>
 *  <li><b>endsWith</b>
 *      - check if a String ends with a suffix NULL-safe</li>
 *  <li><b>IndexOf/LastIndexOf/Contains</b>
 *      - NULL-safe index-of checks
 *  <li><b>IndexOfAny/LastIndexOfAny/IndexOfAnyBut/LastIndexOfAnyBut</b>
 *      - index-of any of a set of Strings</li>
 *  <li><b>ContainsOnly/ContainsNone/ContainsAny</b>
 *      - does String contains only/none/any of these characters</li>
 *  <li><b>Substring/Left/Right/Mid</b>
 *      - NULL-safe substring extractions</li>
 *  <li><b>SubstringBefore/SubstringAfter/SubstringBetween</b>
 *      - substring extraction relative to other strings</li>
 *  <li><b>Split/Join</b>
 *      - splits a String into an array of substrings and vice versa</li>
 *  <li><b>Remove/Delete</b>
 *      - removes part of a String</li>
 *  <li><b>Replace/Overlay</b>
 *      - Searches a String and replaces one String with another</li>
 *  <li><b>Chomp/Chop</b>
 *      - removes the last part of a String</li>
 *  <li><b>LeftPad/RightPad/Center/Repeat</b>
 *      - pads a String</li>
 *  <li><b>UpperCase/LowerCase/SwapCase/Capitalize/Uncapitalize</b>
 *      - changes the case of a String</li>
 *  <li><b>CountMatches</b>
 *      - counts the number of occurrences of one String in another</li>
 *  <li><b>IsAlpha/IsNumeric/IsWhitespace/IsAsciiPrintable</b>
 *      - checks the characters in a String</li>
 *  <li><b>DefaultString</b>
 *      - protects against a NULL input String</li>
 *  <li><b>Reverse/ReverseDelimited</b>
 *      - reverses a String</li>
 *  <li><b>Abbreviate</b>
 *      - abbreviates a string using ellipsis</li>
 *  <li><b>Difference</b>
 *      - compares Strings and reports on their differences</li>
 *  <li><b>LevensteinDistance</b>
 *      - the number of changes needed to change one String into another</li>
 * </ul>
 *
 * <p>The <code>StringUtils</code> class defines certain words related to
 * String handling.</p>
 *
 * <ul>
 *  <li>NULL - <code>NULL</code></li>
 *  <li>empty - a zero-length string (<code>""</code>)</li>
 *  <li>space - the space character (<code>' '</code>, char 32)</li>
 *  <li>whitespace - the characters defined by {@link Character#isWhitespace(char)}</li>
 *  <li>trim - the characters &lt;= 32 as in {@link String#trim()}</li>
 * </ul>
 *
 * <p><code>StringUtils</code> handles <code>NULL</code> input Strings quietly.
 * That is to say that a <code>NULL</code> input will return <code>NULL</code>.
 * Where a <code>boolean</code> or <code>int</code> is being returned
 * details vary by method.</p>
 *
 * <p>A side effect of the <code>NULL</code> handling is that a
 * <code>NullPointerException</code> should be considered a bug in
 * <code>StringUtils</code> (except for deprecated methods).</p>
 *
 * <p>Methods in this class give sample code to explain their operation.
 * The symbol <code>*</code> is used to indicate any input including <code>NULL</code>.</p>
 *
 * <p>#ThreadSafe#</p>
 * @see java.lang.String
 * @author Apache Software Foundation
 * @author <a href="http://jakarta.apache.org/turbine/">Apache Jakarta Turbine</a>
 * @author <a href="mailto:jon@latchkey.com">Jon S. Stevens</a>
 * @author Daniel L. Rall
 * @author <a href="mailto:gcoladonato@yahoo.com">Greg Coladonato</a>
 * @author <a href="mailto:ed@apache.org">Ed Korthof</a>
 * @author <a href="mailto:rand_mcneely@yahoo.com">Rand McNeely</a>
 * @author <a href="mailto:fredrik@westermarck.com">Fredrik Westermarck</a>
 * @author Holger Krauth
 * @author <a href="mailto:alex@purpletech.com">Alexander Day Chaffee</a>
 * @author <a href="mailto:hps@intermeta.de">Henning P. Schmiedehausen</a>
 * @author Arun Mammen Thomas
 * @author Gary Gregory
 * @author Phil Steitz
 * @author Al Chou
 * @author Michael Davey
 * @author Reuben Sivan
 * @author Chris Hyzer
 * @author Scott Johnson
 * @since 1.0
 * @version $Id: StringUtils.java 1058365 2011-01-13 00:04:49Z niallp $
 */
//@Immutable
public class StringUtils {
    // Performance testing notes (JDK 1.4, Jul03, scolebourne)
    // Whitespace:
    // Character.isWhitespace() is faster than WHITESPACE.indexOf()
    // where WHITESPACE is a string of all whitespace characters
    //
    // Character access:
    // String.charAt(n) versus toCharArray(), then array[n]
    // String.charAt(n) is about 15% worse for a 10K string
    // They are about equal for a length 50 string
    // String.charAt(n) is about 4 times better for a length 3 string
    // String.charAt(n) is best bet overall
    //
    // Append:
    // String.concat about twice as fast as StringBuffer.append
    // (not sure who tested this)
#endif
    /**
     * The empty String <code>""</code>.
     * @since 2.0
     */
    /*public*/ /*static*/ /*final*/ QString StringUtils::EMPTY = "";

    /**
     * Represents a failed index search.
     * @since 2.1
     */
    /*public*/ /*static*/ /*final*/ int StringUtils::INDEX_NOT_FOUND = -1;

    /**
     * <p>The maximum size to which the padding constant(s) can expand.</p>
     */
    /*private*/ /*static*/ /*final*/ int StringUtils::PAD_LIMIT = 8192;
#if 0
    /**
     * <p><code>StringUtils</code> instances should NOT be constructed in
     * standard programming. Instead, the class should be used as
     * <code>StringUtils.trim(" foo ");</code>.</p>
     *
     * <p>This constructor is public to permit tools that require a JavaBean
     * instance to operate.</p>
     */
    public StringUtils() {
        super();
    }
#endif
    // Empty checks
    //-----------------------------------------------------------------------
    /**
     * <p>Checks if a String is empty ("") or NULL.</p>
     *
     * <pre>
     * StringUtils.isEmpty(NULL)      = true
     * StringUtils.isEmpty("")        = true
     * StringUtils.isEmpty(" ")       = false
     * StringUtils.isEmpty("bob")     = false
     * StringUtils.isEmpty("  bob  ") = false
     * </pre>
     *
     * <p>NOTE: This method changed in Lang version 2.0.
     * It no longer trims the String.
     * That functionality is available in isBlank().</p>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if the String is empty or NULL
     */
    /*public*/ /*static*/ bool StringUtils::isEmpty(QString str) {
        return str == NULL || str.length() == 0;
    }
#if 0
    /**
     * <p>Checks if a String is not empty ("") and not NULL.</p>
     *
     * <pre>
     * StringUtils.isNotEmpty(NULL)      = false
     * StringUtils.isNotEmpty("")        = false
     * StringUtils.isNotEmpty(" ")       = true
     * StringUtils.isNotEmpty("bob")     = true
     * StringUtils.isNotEmpty("  bob  ") = true
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if the String is not empty and not NULL
     */
    public static boolean isNotEmpty(String str) {
        return !StringUtils.isEmpty(str);
    }

    /**
     * <p>Checks if a String is whitespace, empty ("") or NULL.</p>
     *
     * <pre>
     * StringUtils.isBlank(NULL)      = true
     * StringUtils.isBlank("")        = true
     * StringUtils.isBlank(" ")       = true
     * StringUtils.isBlank("bob")     = false
     * StringUtils.isBlank("  bob  ") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if the String is NULL, empty or whitespace
     * @since 2.0
     */
    public static boolean isBlank(String str) {
        int strLen;
        if (str == NULL || (strLen = str.length()) == 0) {
            return true;
        }
        for (int i = 0; i < strLen; i++) {
            if ((Character.isWhitespace(str.charAt(i)) == false)) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if a String is not empty (""), not NULL and not whitespace only.</p>
     *
     * <pre>
     * StringUtils.isNotBlank(NULL)      = false
     * StringUtils.isNotBlank("")        = false
     * StringUtils.isNotBlank(" ")       = false
     * StringUtils.isNotBlank("bob")     = true
     * StringUtils.isNotBlank("  bob  ") = true
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if the String is
     *  not empty and not NULL and not whitespace
     * @since 2.0
     */
    public static boolean isNotBlank(String str) {
        return !StringUtils.isBlank(str);
    }

    // Trim
    //-----------------------------------------------------------------------
    /**
     * <p>Removes control characters (char &lt;= 32) from both
     * ends of this String, handling <code>NULL</code> by returning
     * an empty String ("").</p>
     *
     * <pre>
     * StringUtils.clean(NULL)          = ""
     * StringUtils.clean("")            = ""
     * StringUtils.clean("abc")         = "abc"
     * StringUtils.clean("    abc    ") = "abc"
     * StringUtils.clean("     ")       = ""
     * </pre>
     *
     * @see java.lang.String#trim()
     * @param str  the String to clean, may be NULL
     * @return the trimmed text, never <code>NULL</code>
     * @deprecated Use the clearer named {@link #trimToEmpty(String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String clean(String str) {
        return str == NULL ? EMPTY : str.trim();
    }

    /**
     * <p>Removes control characters (char &lt;= 32) from both
     * ends of this String, handling <code>NULL</code> by returning
     * <code>NULL</code>.</p>
     *
     * <p>The String is trimmed using {@link String#trim()}.
     * Trim removes start and end characters &lt;= 32.
     * To strip whitespace use {@link #strip(String)}.</p>
     *
     * <p>To trim your choice of characters, use the
     * {@link #strip(String, String)} methods.</p>
     *
     * <pre>
     * StringUtils.trim(NULL)          = NULL
     * StringUtils.trim("")            = ""
     * StringUtils.trim("     ")       = ""
     * StringUtils.trim("abc")         = "abc"
     * StringUtils.trim("    abc    ") = "abc"
     * </pre>
     *
     * @param str  the String to be trimmed, may be NULL
     * @return the trimmed string, <code>NULL</code> if NULL String input
     */
    public static String trim(String str) {
        return str == NULL ? NULL : str.trim();
    }

    /**
     * <p>Removes control characters (char &lt;= 32) from both
     * ends of this String returning <code>NULL</code> if the String is
     * empty ("") after the trim or if it is <code>NULL</code>.
     *
     * <p>The String is trimmed using {@link String#trim()}.
     * Trim removes start and end characters &lt;= 32.
     * To strip whitespace use {@link #stripToNull(String)}.</p>
     *
     * <pre>
     * StringUtils.trimToNull(NULL)          = NULL
     * StringUtils.trimToNull("")            = NULL
     * StringUtils.trimToNull("     ")       = NULL
     * StringUtils.trimToNull("abc")         = "abc"
     * StringUtils.trimToNull("    abc    ") = "abc"
     * </pre>
     *
     * @param str  the String to be trimmed, may be NULL
     * @return the trimmed String,
     *  <code>NULL</code> if only chars &lt;= 32, empty or NULL String input
     * @since 2.0
     */
    public static String trimToNull(String str) {
        String ts = trim(str);
        return isEmpty(ts) ? NULL : ts;
    }

    /**
     * <p>Removes control characters (char &lt;= 32) from both
     * ends of this String returning an empty String ("") if the String
     * is empty ("") after the trim or if it is <code>NULL</code>.
     *
     * <p>The String is trimmed using {@link String#trim()}.
     * Trim removes start and end characters &lt;= 32.
     * To strip whitespace use {@link #stripToEmpty(String)}.</p>
     *
     * <pre>
     * StringUtils.trimToEmpty(NULL)          = ""
     * StringUtils.trimToEmpty("")            = ""
     * StringUtils.trimToEmpty("     ")       = ""
     * StringUtils.trimToEmpty("abc")         = "abc"
     * StringUtils.trimToEmpty("    abc    ") = "abc"
     * </pre>
     *
     * @param str  the String to be trimmed, may be NULL
     * @return the trimmed String, or an empty String if <code>NULL</code> input
     * @since 2.0
     */
    public static String trimToEmpty(String str) {
        return str == NULL ? EMPTY : str.trim();
    }

    // Stripping
    //-----------------------------------------------------------------------
    /**
     * <p>Strips whitespace from the start and end of a String.</p>
     *
     * <p>This is similar to {@link #trim(String)} but removes whitespace.
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.strip(NULL)     = NULL
     * StringUtils.strip("")       = ""
     * StringUtils.strip("   ")    = ""
     * StringUtils.strip("abc")    = "abc"
     * StringUtils.strip("  abc")  = "abc"
     * StringUtils.strip("abc  ")  = "abc"
     * StringUtils.strip(" abc ")  = "abc"
     * StringUtils.strip(" ab c ") = "ab c"
     * </pre>
     *
     * @param str  the String to remove whitespace from, may be NULL
     * @return the stripped String, <code>NULL</code> if NULL String input
     */
    public static String strip(String str) {
        return strip(str, NULL);
    }

    /**
     * <p>Strips whitespace from the start and end of a String  returning
     * <code>NULL</code> if the String is empty ("") after the strip.</p>
     *
     * <p>This is similar to {@link #trimToNull(String)} but removes whitespace.
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <pre>
     * StringUtils.stripToNull(NULL)     = NULL
     * StringUtils.stripToNull("")       = NULL
     * StringUtils.stripToNull("   ")    = NULL
     * StringUtils.stripToNull("abc")    = "abc"
     * StringUtils.stripToNull("  abc")  = "abc"
     * StringUtils.stripToNull("abc  ")  = "abc"
     * StringUtils.stripToNull(" abc ")  = "abc"
     * StringUtils.stripToNull(" ab c ") = "ab c"
     * </pre>
     *
     * @param str  the String to be stripped, may be NULL
     * @return the stripped String,
     *  <code>NULL</code> if whitespace, empty or NULL String input
     * @since 2.0
     */
    public static String stripToNull(String str) {
        if (str == NULL) {
            return NULL;
        }
        str = strip(str, NULL);
        return str.length() == 0 ? NULL : str;
    }

    /**
     * <p>Strips whitespace from the start and end of a String  returning
     * an empty String if <code>NULL</code> input.</p>
     *
     * <p>This is similar to {@link #trimToEmpty(String)} but removes whitespace.
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <pre>
     * StringUtils.stripToEmpty(NULL)     = ""
     * StringUtils.stripToEmpty("")       = ""
     * StringUtils.stripToEmpty("   ")    = ""
     * StringUtils.stripToEmpty("abc")    = "abc"
     * StringUtils.stripToEmpty("  abc")  = "abc"
     * StringUtils.stripToEmpty("abc  ")  = "abc"
     * StringUtils.stripToEmpty(" abc ")  = "abc"
     * StringUtils.stripToEmpty(" ab c ") = "ab c"
     * </pre>
     *
     * @param str  the String to be stripped, may be NULL
     * @return the trimmed String, or an empty String if <code>NULL</code> input
     * @since 2.0
     */
    public static String stripToEmpty(String str) {
        return str == NULL ? EMPTY : strip(str, NULL);
    }

    /**
     * <p>Strips any of a set of characters from the start and end of a String.
     * This is similar to {@link String#trim()} but allows the characters
     * to be stripped to be controlled.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * An empty string ("") input returns the empty string.</p>
     *
     * <p>If the stripChars String is <code>NULL</code>, whitespace is
     * stripped as defined by {@link Character#isWhitespace(char)}.
     * Alternatively use {@link #strip(String)}.</p>
     *
     * <pre>
     * StringUtils.strip(NULL, *)          = NULL
     * StringUtils.strip("", *)            = ""
     * StringUtils.strip("abc", NULL)      = "abc"
     * StringUtils.strip("  abc", NULL)    = "abc"
     * StringUtils.strip("abc  ", NULL)    = "abc"
     * StringUtils.strip(" abc ", NULL)    = "abc"
     * StringUtils.strip("  abcyx", "xyz") = "  abc"
     * </pre>
     *
     * @param str  the String to remove characters from, may be NULL
     * @param stripChars  the characters to remove, NULL treated as whitespace
     * @return the stripped String, <code>NULL</code> if NULL String input
     */
    public static String strip(String str, String stripChars) {
        if (isEmpty(str)) {
            return str;
        }
        str = stripStart(str, stripChars);
        return stripEnd(str, stripChars);
    }

    /**
     * <p>Strips any of a set of characters from the start of a String.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * An empty string ("") input returns the empty string.</p>
     *
     * <p>If the stripChars String is <code>NULL</code>, whitespace is
     * stripped as defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <pre>
     * StringUtils.stripStart(NULL, *)          = NULL
     * StringUtils.stripStart("", *)            = ""
     * StringUtils.stripStart("abc", "")        = "abc"
     * StringUtils.stripStart("abc", NULL)      = "abc"
     * StringUtils.stripStart("  abc", NULL)    = "abc"
     * StringUtils.stripStart("abc  ", NULL)    = "abc  "
     * StringUtils.stripStart(" abc ", NULL)    = "abc "
     * StringUtils.stripStart("yxabc  ", "xyz") = "abc  "
     * </pre>
     *
     * @param str  the String to remove characters from, may be NULL
     * @param stripChars  the characters to remove, NULL treated as whitespace
     * @return the stripped String, <code>NULL</code> if NULL String input
     */
    public static String stripStart(String str, String stripChars) {
        int strLen;
        if (str == NULL || (strLen = str.length()) == 0) {
            return str;
        }
        int start = 0;
        if (stripChars == NULL) {
            while ((start != strLen) && Character.isWhitespace(str.charAt(start))) {
                start++;
            }
        } else if (stripChars.length() == 0) {
            return str;
        } else {
            while ((start != strLen) && (stripChars.indexOf(str.charAt(start)) != INDEX_NOT_FOUND)) {
                start++;
            }
        }
        return str.substring(start);
    }

    /**
     * <p>Strips any of a set of characters from the end of a String.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * An empty string ("") input returns the empty string.</p>
     *
     * <p>If the stripChars String is <code>NULL</code>, whitespace is
     * stripped as defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <pre>
     * StringUtils.stripEnd(NULL, *)          = NULL
     * StringUtils.stripEnd("", *)            = ""
     * StringUtils.stripEnd("abc", "")        = "abc"
     * StringUtils.stripEnd("abc", NULL)      = "abc"
     * StringUtils.stripEnd("  abc", NULL)    = "  abc"
     * StringUtils.stripEnd("abc  ", NULL)    = "abc"
     * StringUtils.stripEnd(" abc ", NULL)    = " abc"
     * StringUtils.stripEnd("  abcyx", "xyz") = "  abc"
     * StringUtils.stripEnd("120.00", ".0")   = "12"
     * </pre>
     *
     * @param str  the String to remove characters from, may be NULL
     * @param stripChars  the set of characters to remove, NULL treated as whitespace
     * @return the stripped String, <code>NULL</code> if NULL String input
     */
    public static String stripEnd(String str, String stripChars) {
        int end;
        if (str == NULL || (end = str.length()) == 0) {
            return str;
        }

        if (stripChars == NULL) {
            while ((end != 0) && Character.isWhitespace(str.charAt(end - 1))) {
                end--;
            }
        } else if (stripChars.length() == 0) {
            return str;
        } else {
            while ((end != 0) && (stripChars.indexOf(str.charAt(end - 1)) != INDEX_NOT_FOUND)) {
                end--;
            }
        }
        return str.substring(0, end);
    }

    // StripAll
    //-----------------------------------------------------------------------
    /**
     * <p>Strips whitespace from the start and end of every String in an array.
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <p>A new array is returned each time, except for length zero.
     * A <code>NULL</code> array will return <code>NULL</code>.
     * An empty array will return itself.
     * A <code>NULL</code> array entry will be ignored.</p>
     *
     * <pre>
     * StringUtils.stripAll(NULL)             = NULL
     * StringUtils.stripAll([])               = []
     * StringUtils.stripAll(["abc", "  abc"]) = ["abc", "abc"]
     * StringUtils.stripAll(["abc  ", NULL])  = ["abc", NULL]
     * </pre>
     *
     * @param strs  the array to remove whitespace from, may be NULL
     * @return the stripped Strings, <code>NULL</code> if NULL array input
     */
    public static String[] stripAll(String[] strs) {
        return stripAll(strs, NULL);
    }

    /**
     * <p>Strips any of a set of characters from the start and end of every
     * String in an array.</p>
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <p>A new array is returned each time, except for length zero.
     * A <code>NULL</code> array will return <code>NULL</code>.
     * An empty array will return itself.
     * A <code>NULL</code> array entry will be ignored.
     * A <code>NULL</code> stripChars will strip whitespace as defined by
     * {@link Character#isWhitespace(char)}.</p>
     *
     * <pre>
     * StringUtils.stripAll(NULL, *)                = NULL
     * StringUtils.stripAll([], *)                  = []
     * StringUtils.stripAll(["abc", "  abc"], NULL) = ["abc", "abc"]
     * StringUtils.stripAll(["abc  ", NULL], NULL)  = ["abc", NULL]
     * StringUtils.stripAll(["abc  ", NULL], "yz")  = ["abc  ", NULL]
     * StringUtils.stripAll(["yabcz", NULL], "yz")  = ["abc", NULL]
     * </pre>
     *
     * @param strs  the array to remove characters from, may be NULL
     * @param stripChars  the characters to remove, NULL treated as whitespace
     * @return the stripped Strings, <code>NULL</code> if NULL array input
     */
    public static String[] stripAll(String[] strs, String stripChars) {
        int strsLen;
        if (strs == NULL || (strsLen = strs.length) == 0) {
            return strs;
        }
        String[] newArr = new String[strsLen];
        for (int i = 0; i < strsLen; i++) {
            newArr[i] = strip(strs[i], stripChars);
        }
        return newArr;
    }

    // Equals
    //-----------------------------------------------------------------------
    /**
     * <p>Compares two Strings, returning <code>true</code> if they are equal.</p>
     *
     * <p><code>NULL</code>s are handled without exceptions. Two <code>NULL</code>
     * references are considered to be equal. The comparison is case sensitive.</p>
     *
     * <pre>
     * StringUtils.equals(NULL, NULL)   = true
     * StringUtils.equals(NULL, "abc")  = false
     * StringUtils.equals("abc", NULL)  = false
     * StringUtils.equals("abc", "abc") = true
     * StringUtils.equals("abc", "ABC") = false
     * </pre>
     *
     * @see java.lang.String#equals(Object)
     * @param str1  the first String, may be NULL
     * @param str2  the second String, may be NULL
     * @return <code>true</code> if the Strings are equal, case sensitive, or
     *  both <code>NULL</code>
     */
    public static boolean equals(String str1, String str2) {
        return str1 == NULL ? str2 == NULL : str1.equals(str2);
    }

    /**
     * <p>Compares two Strings, returning <code>true</code> if they are equal ignoring
     * the case.</p>
     *
     * <p><code>NULL</code>s are handled without exceptions. Two <code>NULL</code>
     * references are considered equal. Comparison is case insensitive.</p>
     *
     * <pre>
     * StringUtils.equalsIgnoreCase(NULL, NULL)   = true
     * StringUtils.equalsIgnoreCase(NULL, "abc")  = false
     * StringUtils.equalsIgnoreCase("abc", NULL)  = false
     * StringUtils.equalsIgnoreCase("abc", "abc") = true
     * StringUtils.equalsIgnoreCase("abc", "ABC") = true
     * </pre>
     *
     * @see java.lang.String#equalsIgnoreCase(String)
     * @param str1  the first String, may be NULL
     * @param str2  the second String, may be NULL
     * @return <code>true</code> if the Strings are equal, case insensitive, or
     *  both <code>NULL</code>
     */
    public static boolean equalsIgnoreCase(String str1, String str2) {
        return str1 == NULL ? str2 == NULL : str1.equalsIgnoreCase(str2);
    }

    // IndexOf
    //-----------------------------------------------------------------------
    /**
     * <p>Finds the first index within a String, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(int)}.</p>
     *
     * <p>A <code>NULL</code> or empty ("") String will return <code>INDEX_NOT_FOUND (-1)</code>.</p>
     *
     * <pre>
     * StringUtils.indexOf(NULL, *)         = -1
     * StringUtils.indexOf("", *)           = -1
     * StringUtils.indexOf("aabaabaa", 'a') = 0
     * StringUtils.indexOf("aabaabaa", 'b') = 2
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChar  the character to find
     * @return the first index of the search character,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int indexOf(String str, char searchChar) {
        if (isEmpty(str)) {
            return INDEX_NOT_FOUND;
        }
        return str.indexOf(searchChar);
    }

    /**
     * <p>Finds the first index within a String from a start position,
     * handling <code>NULL</code>.
     * This method uses {@link String#indexOf(int, int)}.</p>
     *
     * <p>A <code>NULL</code> or empty ("") String will return <code>(INDEX_NOT_FOUND) -1</code>.
     * A negative start position is treated as zero.
     * A start position greater than the string length returns <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.indexOf(NULL, *, *)          = -1
     * StringUtils.indexOf("", *, *)            = -1
     * StringUtils.indexOf("aabaabaa", 'b', 0)  = 2
     * StringUtils.indexOf("aabaabaa", 'b', 3)  = 5
     * StringUtils.indexOf("aabaabaa", 'b', 9)  = -1
     * StringUtils.indexOf("aabaabaa", 'b', -1) = 2
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChar  the character to find
     * @param startPos  the start position, negative treated as zero
     * @return the first index of the search character,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int indexOf(String str, char searchChar, int startPos) {
        if (isEmpty(str)) {
            return INDEX_NOT_FOUND;
        }
        return str.indexOf(searchChar, startPos);
    }

    /**
     * <p>Finds the first index within a String, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(String)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.indexOf(NULL, *)          = -1
     * StringUtils.indexOf(*, NULL)          = -1
     * StringUtils.indexOf("", "")           = 0
     * StringUtils.indexOf("", *)            = -1 (except when * = "")
     * StringUtils.indexOf("aabaabaa", "a")  = 0
     * StringUtils.indexOf("aabaabaa", "b")  = 2
     * StringUtils.indexOf("aabaabaa", "ab") = 1
     * StringUtils.indexOf("aabaabaa", "")   = 0
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int indexOf(String str, String searchStr) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        return str.indexOf(searchStr);
    }

    /**
     * <p>Finds the n-th index within a String, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(String)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.ordinalIndexOf(NULL, *, *)          = -1
     * StringUtils.ordinalIndexOf(*, NULL, *)          = -1
     * StringUtils.ordinalIndexOf("", "", *)           = 0
     * StringUtils.ordinalIndexOf("aabaabaa", "a", 1)  = 0
     * StringUtils.ordinalIndexOf("aabaabaa", "a", 2)  = 1
     * StringUtils.ordinalIndexOf("aabaabaa", "b", 1)  = 2
     * StringUtils.ordinalIndexOf("aabaabaa", "b", 2)  = 5
     * StringUtils.ordinalIndexOf("aabaabaa", "ab", 1) = 1
     * StringUtils.ordinalIndexOf("aabaabaa", "ab", 2) = 4
     * StringUtils.ordinalIndexOf("aabaabaa", "", 1)   = 0
     * StringUtils.ordinalIndexOf("aabaabaa", "", 2)   = 0
     * </pre>
     *
     * <p>Note that 'head(String str, int n)' may be implemented as: </p>
     *
     * <pre>
     *   str.substring(0, lastOrdinalIndexOf(str, "\n", n))
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param ordinal  the n-th <code>searchStr</code> to find
     * @return the n-th index of the search String,
     *  <code>-1</code> (<code>INDEX_NOT_FOUND</code>) if no match or <code>NULL</code> string input
     * @since 2.1
     */
    public static int ordinalIndexOf(String str, String searchStr, int ordinal) {
        return ordinalIndexOf(str, searchStr, ordinal, false);
    }

    /**
     * <p>Finds the n-th index within a String, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(String)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.</p>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param ordinal  the n-th <code>searchStr</code> to find
     * @param lastIndex true if lastOrdinalIndexOf() otherwise false if ordinalIndexOf()
     * @return the n-th index of the search String,
     *  <code>-1</code> (<code>INDEX_NOT_FOUND</code>) if no match or <code>NULL</code> string input
     */
    // Shared code between ordinalIndexOf(String,String,int) and lastOrdinalIndexOf(String,String,int)
    private static int ordinalIndexOf(String str, String searchStr, int ordinal, boolean lastIndex) {
        if (str == NULL || searchStr == NULL || ordinal <= 0) {
            return INDEX_NOT_FOUND;
        }
        if (searchStr.length() == 0) {
            return lastIndex ? str.length() : 0;
        }
        int found = 0;
        int index = lastIndex ? str.length() : INDEX_NOT_FOUND;
        do {
            if(lastIndex) {
                index = str.lastIndexOf(searchStr, index - 1);
            } else {
                index = str.indexOf(searchStr, index + 1);
            }
            if (index < 0) {
                return index;
            }
            found++;
        } while (found < ordinal);
        return index;
    }

    /**
     * <p>Finds the first index within a String, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(String, int)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A negative start position is treated as zero.
     * An empty ("") search String always matches.
     * A start position greater than the string length only matches
     * an empty search String.</p>
     *
     * <pre>
     * StringUtils.indexOf(NULL, *, *)          = -1
     * StringUtils.indexOf(*, NULL, *)          = -1
     * StringUtils.indexOf("", "", 0)           = 0
     * StringUtils.indexOf("", *, 0)            = -1 (except when * = "")
     * StringUtils.indexOf("aabaabaa", "a", 0)  = 0
     * StringUtils.indexOf("aabaabaa", "b", 0)  = 2
     * StringUtils.indexOf("aabaabaa", "ab", 0) = 1
     * StringUtils.indexOf("aabaabaa", "b", 3)  = 5
     * StringUtils.indexOf("aabaabaa", "b", 9)  = -1
     * StringUtils.indexOf("aabaabaa", "b", -1) = 2
     * StringUtils.indexOf("aabaabaa", "", 2)   = 2
     * StringUtils.indexOf("abc", "", 9)        = 3
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param startPos  the start position, negative treated as zero
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int indexOf(String str, String searchStr, int startPos) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        // JDK1.2/JDK1.3 have a bug, when startPos > str.length for "", hence
        if (searchStr.length() == 0 && startPos >= str.length()) {
            return str.length();
        }
        return str.indexOf(searchStr, startPos);
    }

    /**
     * <p>Case in-sensitive find of the first index within a String.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A negative start position is treated as zero.
     * An empty ("") search String always matches.
     * A start position greater than the string length only matches
     * an empty search String.</p>
     *
     * <pre>
     * StringUtils.indexOfIgnoreCase(NULL, *)          = -1
     * StringUtils.indexOfIgnoreCase(*, NULL)          = -1
     * StringUtils.indexOfIgnoreCase("", "")           = 0
     * StringUtils.indexOfIgnoreCase("aabaabaa", "a")  = 0
     * StringUtils.indexOfIgnoreCase("aabaabaa", "b")  = 2
     * StringUtils.indexOfIgnoreCase("aabaabaa", "ab") = 1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.5
     */
    public static int indexOfIgnoreCase(String str, String searchStr) {
        return indexOfIgnoreCase(str, searchStr, 0);
    }

    /**
     * <p>Case in-sensitive find of the first index within a String
     * from the specified position.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A negative start position is treated as zero.
     * An empty ("") search String always matches.
     * A start position greater than the string length only matches
     * an empty search String.</p>
     *
     * <pre>
     * StringUtils.indexOfIgnoreCase(NULL, *, *)          = -1
     * StringUtils.indexOfIgnoreCase(*, NULL, *)          = -1
     * StringUtils.indexOfIgnoreCase("", "", 0)           = 0
     * StringUtils.indexOfIgnoreCase("aabaabaa", "A", 0)  = 0
     * StringUtils.indexOfIgnoreCase("aabaabaa", "B", 0)  = 2
     * StringUtils.indexOfIgnoreCase("aabaabaa", "AB", 0) = 1
     * StringUtils.indexOfIgnoreCase("aabaabaa", "B", 3)  = 5
     * StringUtils.indexOfIgnoreCase("aabaabaa", "B", 9)  = -1
     * StringUtils.indexOfIgnoreCase("aabaabaa", "B", -1) = 2
     * StringUtils.indexOfIgnoreCase("aabaabaa", "", 2)   = 2
     * StringUtils.indexOfIgnoreCase("abc", "", 9)        = 3
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param startPos  the start position, negative treated as zero
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.5
     */
    public static int indexOfIgnoreCase(String str, String searchStr, int startPos) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        if (startPos < 0) {
            startPos = 0;
        }
        int endLimit = (str.length() - searchStr.length()) + 1;
        if (startPos > endLimit) {
            return INDEX_NOT_FOUND;
        }
        if (searchStr.length() == 0) {
            return startPos;
        }
        for (int i = startPos; i < endLimit; i++) {
            if (str.regionMatches(true, i, searchStr, 0, searchStr.length())) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    // LastIndexOf
    //-----------------------------------------------------------------------
    /**
     * <p>Finds the last index within a String, handling <code>NULL</code>.
     * This method uses {@link String#lastIndexOf(int)}.</p>
     *
     * <p>A <code>NULL</code> or empty ("") String will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.lastIndexOf(NULL, *)         = -1
     * StringUtils.lastIndexOf("", *)           = -1
     * StringUtils.lastIndexOf("aabaabaa", 'a') = 7
     * StringUtils.lastIndexOf("aabaabaa", 'b') = 5
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChar  the character to find
     * @return the last index of the search character,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int lastIndexOf(String str, char searchChar) {
        if (isEmpty(str)) {
            return INDEX_NOT_FOUND;
        }
        return str.lastIndexOf(searchChar);
    }

    /**
     * <p>Finds the last index within a String from a start position,
     * handling <code>NULL</code>.
     * This method uses {@link String#lastIndexOf(int, int)}.</p>
     *
     * <p>A <code>NULL</code> or empty ("") String will return <code>-1</code>.
     * A negative start position returns <code>-1</code>.
     * A start position greater than the string length searches the whole string.</p>
     *
     * <pre>
     * StringUtils.lastIndexOf(NULL, *, *)          = -1
     * StringUtils.lastIndexOf("", *,  *)           = -1
     * StringUtils.lastIndexOf("aabaabaa", 'b', 8)  = 5
     * StringUtils.lastIndexOf("aabaabaa", 'b', 4)  = 2
     * StringUtils.lastIndexOf("aabaabaa", 'b', 0)  = -1
     * StringUtils.lastIndexOf("aabaabaa", 'b', 9)  = 5
     * StringUtils.lastIndexOf("aabaabaa", 'b', -1) = -1
     * StringUtils.lastIndexOf("aabaabaa", 'a', 0)  = 0
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChar  the character to find
     * @param startPos  the start position
     * @return the last index of the search character,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int lastIndexOf(String str, char searchChar, int startPos) {
        if (isEmpty(str)) {
            return INDEX_NOT_FOUND;
        }
        return str.lastIndexOf(searchChar, startPos);
    }

    /**
     * <p>Finds the last index within a String, handling <code>NULL</code>.
     * This method uses {@link String#lastIndexOf(String)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.lastIndexOf(NULL, *)          = -1
     * StringUtils.lastIndexOf(*, NULL)          = -1
     * StringUtils.lastIndexOf("", "")           = 0
     * StringUtils.lastIndexOf("aabaabaa", "a")  = 7
     * StringUtils.lastIndexOf("aabaabaa", "b")  = 5
     * StringUtils.lastIndexOf("aabaabaa", "ab") = 4
     * StringUtils.lastIndexOf("aabaabaa", "")   = 8
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @return the last index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int lastIndexOf(String str, String searchStr) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        return str.lastIndexOf(searchStr);
    }

    /**
     * <p>Finds the n-th last index within a String, handling <code>NULL</code>.
     * This method uses {@link String#lastIndexOf(String)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.lastOrdinalIndexOf(NULL, *, *)          = -1
     * StringUtils.lastOrdinalIndexOf(*, NULL, *)          = -1
     * StringUtils.lastOrdinalIndexOf("", "", *)           = 0
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "a", 1)  = 7
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "a", 2)  = 6
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "b", 1)  = 5
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "b", 2)  = 2
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "ab", 1) = 4
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "ab", 2) = 1
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "", 1)   = 8
     * StringUtils.lastOrdinalIndexOf("aabaabaa", "", 2)   = 8
     * </pre>
     *
     * <p>Note that 'tail(String str, int n)' may be implemented as: </p>
     *
     * <pre>
     *   str.substring(lastOrdinalIndexOf(str, "\n", n) + 1)
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param ordinal  the n-th last <code>searchStr</code> to find
     * @return the n-th last index of the search String,
     *  <code>-1</code> (<code>INDEX_NOT_FOUND</code>) if no match or <code>NULL</code> string input
     * @since 2.5
     */
    public static int lastOrdinalIndexOf(String str, String searchStr, int ordinal) {
        return ordinalIndexOf(str, searchStr, ordinal, true);
    }

    /**
     * <p>Finds the first index within a String, handling <code>NULL</code>.
     * This method uses {@link String#lastIndexOf(String, int)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A negative start position returns <code>-1</code>.
     * An empty ("") search String always matches unless the start position is negative.
     * A start position greater than the string length searches the whole string.</p>
     *
     * <pre>
     * StringUtils.lastIndexOf(NULL, *, *)          = -1
     * StringUtils.lastIndexOf(*, NULL, *)          = -1
     * StringUtils.lastIndexOf("aabaabaa", "a", 8)  = 7
     * StringUtils.lastIndexOf("aabaabaa", "b", 8)  = 5
     * StringUtils.lastIndexOf("aabaabaa", "ab", 8) = 4
     * StringUtils.lastIndexOf("aabaabaa", "b", 9)  = 5
     * StringUtils.lastIndexOf("aabaabaa", "b", -1) = -1
     * StringUtils.lastIndexOf("aabaabaa", "a", 0)  = 0
     * StringUtils.lastIndexOf("aabaabaa", "b", 0)  = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param startPos  the start position, negative treated as zero
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.0
     */
    public static int lastIndexOf(String str, String searchStr, int startPos) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        return str.lastIndexOf(searchStr, startPos);
    }

    /**
     * <p>Case in-sensitive find of the last index within a String.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A negative start position returns <code>-1</code>.
     * An empty ("") search String always matches unless the start position is negative.
     * A start position greater than the string length searches the whole string.</p>
     *
     * <pre>
     * StringUtils.lastIndexOfIgnoreCase(NULL, *)          = -1
     * StringUtils.lastIndexOfIgnoreCase(*, NULL)          = -1
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "A")  = 7
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "B")  = 5
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "AB") = 4
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.5
     */
    public static int lastIndexOfIgnoreCase(String str, String searchStr) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        return lastIndexOfIgnoreCase(str, searchStr, str.length());
    }

    /**
     * <p>Case in-sensitive find of the last index within a String
     * from the specified position.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A negative start position returns <code>-1</code>.
     * An empty ("") search String always matches unless the start position is negative.
     * A start position greater than the string length searches the whole string.</p>
     *
     * <pre>
     * StringUtils.lastIndexOfIgnoreCase(NULL, *, *)          = -1
     * StringUtils.lastIndexOfIgnoreCase(*, NULL, *)          = -1
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "A", 8)  = 7
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "B", 8)  = 5
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "AB", 8) = 4
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "B", 9)  = 5
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "B", -1) = -1
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "A", 0)  = 0
     * StringUtils.lastIndexOfIgnoreCase("aabaabaa", "B", 0)  = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @param startPos  the start position
     * @return the first index of the search String,
     *  -1 if no match or <code>NULL</code> string input
     * @since 2.5
     */
    public static int lastIndexOfIgnoreCase(String str, String searchStr, int startPos) {
        if (str == NULL || searchStr == NULL) {
            return INDEX_NOT_FOUND;
        }
        if (startPos > (str.length() - searchStr.length())) {
            startPos = str.length() - searchStr.length();
        }
        if (startPos < 0) {
            return INDEX_NOT_FOUND;
        }
        if (searchStr.length() == 0) {
            return startPos;
        }

        for (int i = startPos; i >= 0; i--) {
            if (str.regionMatches(true, i, searchStr, 0, searchStr.length())) {
                return i;
            }
        }
        return INDEX_NOT_FOUND;
    }

    // Contains
    //-----------------------------------------------------------------------
    /**
     * <p>Checks if String contains a search character, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(int)}.</p>
     *
     * <p>A <code>NULL</code> or empty ("") String will return <code>false</code>.</p>
     *
     * <pre>
     * StringUtils.contains(NULL, *)    = false
     * StringUtils.contains("", *)      = false
     * StringUtils.contains("abc", 'a') = true
     * StringUtils.contains("abc", 'z') = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChar  the character to find
     * @return true if the String contains the search character,
     *  false if not or <code>NULL</code> string input
     * @since 2.0
     */
    public static boolean contains(String str, char searchChar) {
        if (isEmpty(str)) {
            return false;
        }
        return str.indexOf(searchChar) >= 0;
    }

    /**
     * <p>Checks if String contains a search String, handling <code>NULL</code>.
     * This method uses {@link String#indexOf(String)}.</p>
     *
     * <p>A <code>NULL</code> String will return <code>false</code>.</p>
     *
     * <pre>
     * StringUtils.contains(NULL, *)     = false
     * StringUtils.contains(*, NULL)     = false
     * StringUtils.contains("", "")      = true
     * StringUtils.contains("abc", "")   = true
     * StringUtils.contains("abc", "a")  = true
     * StringUtils.contains("abc", "z")  = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @return true if the String contains the search String,
     *  false if not or <code>NULL</code> string input
     * @since 2.0
     */
    public static boolean contains(String str, String searchStr) {
        if (str == NULL || searchStr == NULL) {
            return false;
        }
        return str.indexOf(searchStr) >= 0;
    }

    /**
     * <p>Checks if String contains a search String irrespective of case,
     * handling <code>NULL</code>. Case-insensitivity is defined as by
     * {@link String#equalsIgnoreCase(String)}.
     *
     * <p>A <code>NULL</code> String will return <code>false</code>.</p>
     *
     * <pre>
     * StringUtils.contains(NULL, *) = false
     * StringUtils.contains(*, NULL) = false
     * StringUtils.contains("", "") = true
     * StringUtils.contains("abc", "") = true
     * StringUtils.contains("abc", "a") = true
     * StringUtils.contains("abc", "z") = false
     * StringUtils.contains("abc", "A") = true
     * StringUtils.contains("abc", "Z") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStr  the String to find, may be NULL
     * @return true if the String contains the search String irrespective of
     * case or false if not or <code>NULL</code> string input
     */
    public static boolean containsIgnoreCase(String str, String searchStr) {
        if (str == NULL || searchStr == NULL) {
            return false;
        }
        int len = searchStr.length();
        int max = str.length() - len;
        for (int i = 0; i <= max; i++) {
            if (str.regionMatches(true, i, searchStr, 0, len)) {
                return true;
            }
        }
        return false;
    }

    // IndexOfAny chars
    //-----------------------------------------------------------------------
    /**
     * <p>Search a String to find the first index of any
     * character in the given set of characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A <code>NULL</code> or zero length search array will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.indexOfAny(NULL, *)                = -1
     * StringUtils.indexOfAny("", *)                  = -1
     * StringUtils.indexOfAny(*, NULL)                = -1
     * StringUtils.indexOfAny(*, [])                  = -1
     * StringUtils.indexOfAny("zzabyycdxx",['z','a']) = 0
     * StringUtils.indexOfAny("zzabyycdxx",['b','y']) = 3
     * StringUtils.indexOfAny("aba", ['z'])           = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChars  the chars to search for, may be NULL
     * @return the index of any of the chars, -1 if no match or NULL input
     * @since 2.0
     */
    public static int indexOfAny(String str, char[] searchChars) {
        if (isEmpty(str) || ArrayUtils.isEmpty(searchChars)) {
            return INDEX_NOT_FOUND;
        }
        int csLen = str.length();
        int csLast = csLen - 1;
        int searchLen = searchChars.length;
        int searchLast = searchLen - 1;
        for (int i = 0; i < csLen; i++) {
            char ch = str.charAt(i);
            for (int j = 0; j < searchLen; j++) {
                if (searchChars[j] == ch) {
                    if (i < csLast && j < searchLast && CharUtils.isHighSurrogate(ch)) {
                        // ch is a supplementary character
                        if (searchChars[j + 1] == str.charAt(i + 1)) {
                            return i;
                        }
                    } else {
                        return i;
                    }
                }
            }
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>Search a String to find the first index of any
     * character in the given set of characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A <code>NULL</code> search string will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.indexOfAny(NULL, *)            = -1
     * StringUtils.indexOfAny("", *)              = -1
     * StringUtils.indexOfAny(*, NULL)            = -1
     * StringUtils.indexOfAny(*, "")              = -1
     * StringUtils.indexOfAny("zzabyycdxx", "za") = 0
     * StringUtils.indexOfAny("zzabyycdxx", "by") = 3
     * StringUtils.indexOfAny("aba","z")          = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChars  the chars to search for, may be NULL
     * @return the index of any of the chars, -1 if no match or NULL input
     * @since 2.0
     */
    public static int indexOfAny(String str, String searchChars) {
        if (isEmpty(str) || isEmpty(searchChars)) {
            return INDEX_NOT_FOUND;
        }
        return indexOfAny(str, searchChars.toCharArray());
    }

    // ContainsAny
    //-----------------------------------------------------------------------
    /**
     * <p>Checks if the String contains any character in the given
     * set of characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>false</code>.
     * A <code>NULL</code> or zero length search array will return <code>false</code>.</p>
     *
     * <pre>
     * StringUtils.containsAny(NULL, *)                = false
     * StringUtils.containsAny("", *)                  = false
     * StringUtils.containsAny(*, NULL)                = false
     * StringUtils.containsAny(*, [])                  = false
     * StringUtils.containsAny("zzabyycdxx",['z','a']) = true
     * StringUtils.containsAny("zzabyycdxx",['b','y']) = true
     * StringUtils.containsAny("aba", ['z'])           = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChars  the chars to search for, may be NULL
     * @return the <code>true</code> if any of the chars are found,
     * <code>false</code> if no match or NULL input
     * @since 2.4
     */
    public static boolean containsAny(String str, char[] searchChars) {
        if (isEmpty(str) || ArrayUtils.isEmpty(searchChars)) {
            return false;
        }
        int csLength = str.length();
        int searchLength = searchChars.length;
        int csLast = csLength - 1;
        int searchLast = searchLength - 1;
        for (int i = 0; i < csLength; i++) {
            char ch = str.charAt(i);
            for (int j = 0; j < searchLength; j++) {
                if (searchChars[j] == ch) {
                    if (CharUtils.isHighSurrogate(ch)) {
                        if (j == searchLast) {
                            // missing low surrogate, fine, like String.indexOf(String)
                            return true;
                        }
                        if (i < csLast && searchChars[j + 1] == str.charAt(i + 1)) {
                            return true;
                        }
                    } else {
                        // ch is in the Basic Multilingual Plane
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /**
     * <p>
     * Checks if the String contains any character in the given set of characters.
     * </p>
     *
     * <p>
     * A <code>NULL</code> String will return <code>false</code>. A <code>NULL</code> search string will return
     * <code>false</code>.
     * </p>
     *
     * <pre>
     * StringUtils.containsAny(NULL, *)            = false
     * StringUtils.containsAny("", *)              = false
     * StringUtils.containsAny(*, NULL)            = false
     * StringUtils.containsAny(*, "")              = false
     * StringUtils.containsAny("zzabyycdxx", "za") = true
     * StringUtils.containsAny("zzabyycdxx", "by") = true
     * StringUtils.containsAny("aba","z")          = false
     * </pre>
     *
     * @param str
     *            the String to check, may be NULL
     * @param searchChars
     *            the chars to search for, may be NULL
     * @return the <code>true</code> if any of the chars are found, <code>false</code> if no match or NULL input
     * @since 2.4
     */
    public static boolean containsAny(String str, String searchChars) {
        if (searchChars == NULL) {
            return false;
        }
        return containsAny(str, searchChars.toCharArray());
    }

    // IndexOfAnyBut chars
    //-----------------------------------------------------------------------
    /**
     * <p>Search a String to find the first index of any
     * character not in the given set of characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A <code>NULL</code> or zero length search array will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.indexOfAnyBut(NULL, *)                              = -1
     * StringUtils.indexOfAnyBut("", *)                                = -1
     * StringUtils.indexOfAnyBut(*, NULL)                              = -1
     * StringUtils.indexOfAnyBut(*, [])                                = -1
     * StringUtils.indexOfAnyBut("zzabyycdxx", new char[] {'z', 'a'} ) = 3
     * StringUtils.indexOfAnyBut("aba", new char[] {'z'} )             = 0
     * StringUtils.indexOfAnyBut("aba", new char[] {'a', 'b'} )        = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChars  the chars to search for, may be NULL
     * @return the index of any of the chars, -1 if no match or NULL input
     * @since 2.0
     */
    public static int indexOfAnyBut(String str, char[] searchChars) {
        if (isEmpty(str) || ArrayUtils.isEmpty(searchChars)) {
            return INDEX_NOT_FOUND;
        }
        int csLen = str.length();
        int csLast = csLen - 1;
        int searchLen = searchChars.length;
        int searchLast = searchLen - 1;
        outer:
        for (int i = 0; i < csLen; i++) {
            char ch = str.charAt(i);
            for (int j = 0; j < searchLen; j++) {
                if (searchChars[j] == ch) {
                    if (i < csLast && j < searchLast && CharUtils.isHighSurrogate(ch)) {
                        if (searchChars[j + 1] == str.charAt(i + 1)) {
                            continue outer;
                        }
                    } else {
                        continue outer;
                    }
                }
            }
            return i;
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>Search a String to find the first index of any
     * character not in the given set of characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A <code>NULL</code> or empty search string will return <code>-1</code>.</p>
     *
     * <pre>
     * StringUtils.indexOfAnyBut(NULL, *)            = -1
     * StringUtils.indexOfAnyBut("", *)              = -1
     * StringUtils.indexOfAnyBut(*, NULL)            = -1
     * StringUtils.indexOfAnyBut(*, "")              = -1
     * StringUtils.indexOfAnyBut("zzabyycdxx", "za") = 3
     * StringUtils.indexOfAnyBut("zzabyycdxx", "")   = -1
     * StringUtils.indexOfAnyBut("aba","ab")         = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChars  the chars to search for, may be NULL
     * @return the index of any of the chars, -1 if no match or NULL input
     * @since 2.0
     */
    public static int indexOfAnyBut(String str, String searchChars) {
        if (isEmpty(str) || isEmpty(searchChars)) {
            return INDEX_NOT_FOUND;
        }
        int strLen = str.length();
        for (int i = 0; i < strLen; i++) {
            char ch = str.charAt(i);
            boolean chFound = searchChars.indexOf(ch) >= 0;
            if (i + 1 < strLen && CharUtils.isHighSurrogate(ch)) {
                char ch2 = str.charAt(i + 1);
                if (chFound && searchChars.indexOf(ch2) < 0) {
                    return i;
                }
            } else {
                if (!chFound) {
                    return i;
                }
            }
        }
        return INDEX_NOT_FOUND;
    }

    // ContainsOnly
    //-----------------------------------------------------------------------
    /**
     * <p>Checks if the String contains only certain characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>false</code>.
     * A <code>NULL</code> valid character array will return <code>false</code>.
     * An empty String (length()=0) always returns <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.containsOnly(NULL, *)       = false
     * StringUtils.containsOnly(*, NULL)       = false
     * StringUtils.containsOnly("", *)         = true
     * StringUtils.containsOnly("ab", '')      = false
     * StringUtils.containsOnly("abab", 'abc') = true
     * StringUtils.containsOnly("ab1", 'abc')  = false
     * StringUtils.containsOnly("abz", 'abc')  = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param valid  an array of valid chars, may be NULL
     * @return true if it only contains valid chars and is non-NULL
     */
    public static boolean containsOnly(String str, char[] valid) {
        // All these pre-checks are to maintain API with an older version
        if ((valid == NULL) || (str == NULL)) {
            return false;
        }
        if (str.length() == 0) {
            return true;
        }
        if (valid.length == 0) {
            return false;
        }
        return indexOfAnyBut(str, valid) == INDEX_NOT_FOUND;
    }

    /**
     * <p>Checks if the String contains only certain characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>false</code>.
     * A <code>NULL</code> valid character String will return <code>false</code>.
     * An empty String (length()=0) always returns <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.containsOnly(NULL, *)       = false
     * StringUtils.containsOnly(*, NULL)       = false
     * StringUtils.containsOnly("", *)         = true
     * StringUtils.containsOnly("ab", "")      = false
     * StringUtils.containsOnly("abab", "abc") = true
     * StringUtils.containsOnly("ab1", "abc")  = false
     * StringUtils.containsOnly("abz", "abc")  = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param validChars  a String of valid chars, may be NULL
     * @return true if it only contains valid chars and is non-NULL
     * @since 2.0
     */
    public static boolean containsOnly(String str, String validChars) {
        if (str == NULL || validChars == NULL) {
            return false;
        }
        return containsOnly(str, validChars.toCharArray());
    }

    // ContainsNone
    //-----------------------------------------------------------------------
    /**
     * <p>Checks that the String does not contain certain characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>true</code>.
     * A <code>NULL</code> invalid character array will return <code>true</code>.
     * An empty String (length()=0) always returns true.</p>
     *
     * <pre>
     * StringUtils.containsNone(NULL, *)       = true
     * StringUtils.containsNone(*, NULL)       = true
     * StringUtils.containsNone("", *)         = true
     * StringUtils.containsNone("ab", '')      = true
     * StringUtils.containsNone("abab", 'xyz') = true
     * StringUtils.containsNone("ab1", 'xyz')  = true
     * StringUtils.containsNone("abz", 'xyz')  = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchChars  an array of invalid chars, may be NULL
     * @return true if it contains none of the invalid chars, or is NULL
     * @since 2.0
     */
    public static boolean containsNone(String str, char[] searchChars) {
        if (str == NULL || searchChars == NULL) {
            return true;
        }
        int csLen = str.length();
        int csLast = csLen - 1;
        int searchLen = searchChars.length;
        int searchLast = searchLen - 1;
        for (int i = 0; i < csLen; i++) {
            char ch = str.charAt(i);
            for (int j = 0; j < searchLen; j++) {
                if (searchChars[j] == ch) {
                    if (CharUtils.isHighSurrogate(ch)) {
                        if (j == searchLast) {
                            // missing low surrogate, fine, like String.indexOf(String)
                            return false;
                        }
                        if (i < csLast && searchChars[j + 1] == str.charAt(i + 1)) {
                            return false;
                        }
                    } else {
                        // ch is in the Basic Multilingual Plane
                        return false;
                    }
                }
            }
        }
        return true;
    }

    /**
     * <p>Checks that the String does not contain certain characters.</p>
     *
     * <p>A <code>NULL</code> String will return <code>true</code>.
     * A <code>NULL</code> invalid character array will return <code>true</code>.
     * An empty String ("") always returns true.</p>
     *
     * <pre>
     * StringUtils.containsNone(NULL, *)       = true
     * StringUtils.containsNone(*, NULL)       = true
     * StringUtils.containsNone("", *)         = true
     * StringUtils.containsNone("ab", "")      = true
     * StringUtils.containsNone("abab", "xyz") = true
     * StringUtils.containsNone("ab1", "xyz")  = true
     * StringUtils.containsNone("abz", "xyz")  = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param invalidChars  a String of invalid chars, may be NULL
     * @return true if it contains none of the invalid chars, or is NULL
     * @since 2.0
     */
    public static boolean containsNone(String str, String invalidChars) {
        if (str == NULL || invalidChars == NULL) {
            return true;
        }
        return containsNone(str, invalidChars.toCharArray());
    }

    // IndexOfAny strings
    //-----------------------------------------------------------------------
    /**
     * <p>Find the first index of any of a set of potential substrings.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A <code>NULL</code> or zero length search array will return <code>-1</code>.
     * A <code>NULL</code> search array entry will be ignored, but a search
     * array containing "" will return <code>0</code> if <code>str</code> is not
     * NULL. This method uses {@link String#indexOf(String)}.</p>
     *
     * <pre>
     * StringUtils.indexOfAny(NULL, *)                     = -1
     * StringUtils.indexOfAny(*, NULL)                     = -1
     * StringUtils.indexOfAny(*, [])                       = -1
     * StringUtils.indexOfAny("zzabyycdxx", ["ab","cd"])   = 2
     * StringUtils.indexOfAny("zzabyycdxx", ["cd","ab"])   = 2
     * StringUtils.indexOfAny("zzabyycdxx", ["mn","op"])   = -1
     * StringUtils.indexOfAny("zzabyycdxx", ["zab","aby"]) = 1
     * StringUtils.indexOfAny("zzabyycdxx", [""])          = 0
     * StringUtils.indexOfAny("", [""])                    = 0
     * StringUtils.indexOfAny("", ["a"])                   = -1
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStrs  the Strings to search for, may be NULL
     * @return the first index of any of the searchStrs in str, -1 if no match
     */
    public static int indexOfAny(String str, String[] searchStrs) {
        if ((str == NULL) || (searchStrs == NULL)) {
            return INDEX_NOT_FOUND;
        }
        int sz = searchStrs.length;

        // String's can't have a MAX_VALUEth index.
        int ret = Integer.MAX_VALUE;

        int tmp = 0;
        for (int i = 0; i < sz; i++) {
            String search = searchStrs[i];
            if (search == NULL) {
                continue;
            }
            tmp = str.indexOf(search);
            if (tmp == INDEX_NOT_FOUND) {
                continue;
            }

            if (tmp < ret) {
                ret = tmp;
            }
        }

        return (ret == Integer.MAX_VALUE) ? INDEX_NOT_FOUND : ret;
    }

    /**
     * <p>Find the latest index of any of a set of potential substrings.</p>
     *
     * <p>A <code>NULL</code> String will return <code>-1</code>.
     * A <code>NULL</code> search array will return <code>-1</code>.
     * A <code>NULL</code> or zero length search array entry will be ignored,
     * but a search array containing "" will return the length of <code>str</code>
     * if <code>str</code> is not NULL. This method uses {@link String#indexOf(String)}</p>
     *
     * <pre>
     * StringUtils.lastIndexOfAny(NULL, *)                   = -1
     * StringUtils.lastIndexOfAny(*, NULL)                   = -1
     * StringUtils.lastIndexOfAny(*, [])                     = -1
     * StringUtils.lastIndexOfAny(*, [NULL])                 = -1
     * StringUtils.lastIndexOfAny("zzabyycdxx", ["ab","cd"]) = 6
     * StringUtils.lastIndexOfAny("zzabyycdxx", ["cd","ab"]) = 6
     * StringUtils.lastIndexOfAny("zzabyycdxx", ["mn","op"]) = -1
     * StringUtils.lastIndexOfAny("zzabyycdxx", ["mn","op"]) = -1
     * StringUtils.lastIndexOfAny("zzabyycdxx", ["mn",""])   = 10
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param searchStrs  the Strings to search for, may be NULL
     * @return the last index of any of the Strings, -1 if no match
     */
    public static int lastIndexOfAny(String str, String[] searchStrs) {
        if ((str == NULL) || (searchStrs == NULL)) {
            return INDEX_NOT_FOUND;
        }
        int sz = searchStrs.length;
        int ret = INDEX_NOT_FOUND;
        int tmp = 0;
        for (int i = 0; i < sz; i++) {
            String search = searchStrs[i];
            if (search == NULL) {
                continue;
            }
            tmp = str.lastIndexOf(search);
            if (tmp > ret) {
                ret = tmp;
            }
        }
        return ret;
    }

    // Substring
    //-----------------------------------------------------------------------
    /**
     * <p>Gets a substring from the specified String avoiding exceptions.</p>
     *
     * <p>A negative start position can be used to start <code>n</code>
     * characters from the end of the String.</p>
     *
     * <p>A <code>NULL</code> String will return <code>NULL</code>.
     * An empty ("") String will return "".</p>
     *
     * <pre>
     * StringUtils.substring(NULL, *)   = NULL
     * StringUtils.substring("", *)     = ""
     * StringUtils.substring("abc", 0)  = "abc"
     * StringUtils.substring("abc", 2)  = "c"
     * StringUtils.substring("abc", 4)  = ""
     * StringUtils.substring("abc", -2) = "bc"
     * StringUtils.substring("abc", -4) = "abc"
     * </pre>
     *
     * @param str  the String to get the substring from, may be NULL
     * @param start  the position to start from, negative means
     *  count back from the end of the String by this many characters
     * @return substring from start position, <code>NULL</code> if NULL String input
     */
    public static String substring(String str, int start) {
        if (str == NULL) {
            return NULL;
        }

        // handle negatives, which means last n characters
        if (start < 0) {
            start = str.length() + start; // remember start is negative
        }

        if (start < 0) {
            start = 0;
        }
        if (start > str.length()) {
            return EMPTY;
        }

        return str.substring(start);
    }

    /**
     * <p>Gets a substring from the specified String avoiding exceptions.</p>
     *
     * <p>A negative start position can be used to start/end <code>n</code>
     * characters from the end of the String.</p>
     *
     * <p>The returned substring starts with the character in the <code>start</code>
     * position and ends before the <code>end</code> position. All position counting is
     * zero-based -- i.e., to start at the beginning of the string use
     * <code>start = 0</code>. Negative start and end positions can be used to
     * specify offsets relative to the end of the String.</p>
     *
     * <p>If <code>start</code> is not strictly to the left of <code>end</code>, ""
     * is returned.</p>
     *
     * <pre>
     * StringUtils.substring(NULL, *, *)    = NULL
     * StringUtils.substring("", * ,  *)    = "";
     * StringUtils.substring("abc", 0, 2)   = "ab"
     * StringUtils.substring("abc", 2, 0)   = ""
     * StringUtils.substring("abc", 2, 4)   = "c"
     * StringUtils.substring("abc", 4, 6)   = ""
     * StringUtils.substring("abc", 2, 2)   = ""
     * StringUtils.substring("abc", -2, -1) = "b"
     * StringUtils.substring("abc", -4, 2)  = "ab"
     * </pre>
     *
     * @param str  the String to get the substring from, may be NULL
     * @param start  the position to start from, negative means
     *  count back from the end of the String by this many characters
     * @param end  the position to end at (exclusive), negative means
     *  count back from the end of the String by this many characters
     * @return substring from start position to end positon,
     *  <code>NULL</code> if NULL String input
     */
    public static String substring(String str, int start, int end) {
        if (str == NULL) {
            return NULL;
        }

        // handle negatives
        if (end < 0) {
            end = str.length() + end; // remember end is negative
        }
        if (start < 0) {
            start = str.length() + start; // remember start is negative
        }

        // check length next
        if (end > str.length()) {
            end = str.length();
        }

        // if start is greater than end, return ""
        if (start > end) {
            return EMPTY;
        }

        if (start < 0) {
            start = 0;
        }
        if (end < 0) {
            end = 0;
        }

        return str.substring(start, end);
    }

    // Left/Right/Mid
    //-----------------------------------------------------------------------
    /**
     * <p>Gets the leftmost <code>len</code> characters of a String.</p>
     *
     * <p>If <code>len</code> characters are not available, or the
     * String is <code>NULL</code>, the String will be returned without
     * an exception. An empty String is returned if len is negative.</p>
     *
     * <pre>
     * StringUtils.left(NULL, *)    = NULL
     * StringUtils.left(*, -ve)     = ""
     * StringUtils.left("", *)      = ""
     * StringUtils.left("abc", 0)   = ""
     * StringUtils.left("abc", 2)   = "ab"
     * StringUtils.left("abc", 4)   = "abc"
     * </pre>
     *
     * @param str  the String to get the leftmost characters from, may be NULL
     * @param len  the length of the required String
     * @return the leftmost characters, <code>NULL</code> if NULL String input
     */
    public static String left(String str, int len) {
        if (str == NULL) {
            return NULL;
        }
        if (len < 0) {
            return EMPTY;
        }
        if (str.length() <= len) {
            return str;
        }
        return str.substring(0, len);
    }

    /**
     * <p>Gets the rightmost <code>len</code> characters of a String.</p>
     *
     * <p>If <code>len</code> characters are not available, or the String
     * is <code>NULL</code>, the String will be returned without an
     * an exception. An empty String is returned if len is negative.</p>
     *
     * <pre>
     * StringUtils.right(NULL, *)    = NULL
     * StringUtils.right(*, -ve)     = ""
     * StringUtils.right("", *)      = ""
     * StringUtils.right("abc", 0)   = ""
     * StringUtils.right("abc", 2)   = "bc"
     * StringUtils.right("abc", 4)   = "abc"
     * </pre>
     *
     * @param str  the String to get the rightmost characters from, may be NULL
     * @param len  the length of the required String
     * @return the rightmost characters, <code>NULL</code> if NULL String input
     */
    public static String right(String str, int len) {
        if (str == NULL) {
            return NULL;
        }
        if (len < 0) {
            return EMPTY;
        }
        if (str.length() <= len) {
            return str;
        }
        return str.substring(str.length() - len);
    }

    /**
     * <p>Gets <code>len</code> characters from the middle of a String.</p>
     *
     * <p>If <code>len</code> characters are not available, the remainder
     * of the String will be returned without an exception. If the
     * String is <code>NULL</code>, <code>NULL</code> will be returned.
     * An empty String is returned if len is negative or exceeds the
     * length of <code>str</code>.</p>
     *
     * <pre>
     * StringUtils.mid(NULL, *, *)    = NULL
     * StringUtils.mid(*, *, -ve)     = ""
     * StringUtils.mid("", 0, *)      = ""
     * StringUtils.mid("abc", 0, 2)   = "ab"
     * StringUtils.mid("abc", 0, 4)   = "abc"
     * StringUtils.mid("abc", 2, 4)   = "c"
     * StringUtils.mid("abc", 4, 2)   = ""
     * StringUtils.mid("abc", -2, 2)  = "ab"
     * </pre>
     *
     * @param str  the String to get the characters from, may be NULL
     * @param pos  the position to start from, negative treated as zero
     * @param len  the length of the required String
     * @return the middle characters, <code>NULL</code> if NULL String input
     */
    public static String mid(String str, int pos, int len) {
        if (str == NULL) {
            return NULL;
        }
        if (len < 0 || pos > str.length()) {
            return EMPTY;
        }
        if (pos < 0) {
            pos = 0;
        }
        if (str.length() <= (pos + len)) {
            return str.substring(pos);
        }
        return str.substring(pos, pos + len);
    }

    // SubStringAfter/SubStringBefore
    //-----------------------------------------------------------------------
    /**
     * <p>Gets the substring before the first occurrence of a separator.
     * The separator is not returned.</p>
     *
     * <p>A <code>NULL</code> string input will return <code>NULL</code>.
     * An empty ("") string input will return the empty string.
     * A <code>NULL</code> separator will return the input string.</p>
     *
     * <p>If nothing is found, the string input is returned.</p>
     *
     * <pre>
     * StringUtils.substringBefore(NULL, *)      = NULL
     * StringUtils.substringBefore("", *)        = ""
     * StringUtils.substringBefore("abc", "a")   = ""
     * StringUtils.substringBefore("abcba", "b") = "a"
     * StringUtils.substringBefore("abc", "c")   = "ab"
     * StringUtils.substringBefore("abc", "d")   = "abc"
     * StringUtils.substringBefore("abc", "")    = ""
     * StringUtils.substringBefore("abc", NULL)  = "abc"
     * </pre>
     *
     * @param str  the String to get a substring from, may be NULL
     * @param separator  the String to search for, may be NULL
     * @return the substring before the first occurrence of the separator,
     *  <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String substringBefore(String str, String separator) {
        if (isEmpty(str) || separator == NULL) {
            return str;
        }
        if (separator.length() == 0) {
            return EMPTY;
        }
        int pos = str.indexOf(separator);
        if (pos == INDEX_NOT_FOUND) {
            return str;
        }
        return str.substring(0, pos);
    }

    /**
     * <p>Gets the substring after the first occurrence of a separator.
     * The separator is not returned.</p>
     *
     * <p>A <code>NULL</code> string input will return <code>NULL</code>.
     * An empty ("") string input will return the empty string.
     * A <code>NULL</code> separator will return the empty string if the
     * input string is not <code>NULL</code>.</p>
     *
     * <p>If nothing is found, the empty string is returned.</p>
     *
     * <pre>
     * StringUtils.substringAfter(NULL, *)      = NULL
     * StringUtils.substringAfter("", *)        = ""
     * StringUtils.substringAfter(*, NULL)      = ""
     * StringUtils.substringAfter("abc", "a")   = "bc"
     * StringUtils.substringAfter("abcba", "b") = "cba"
     * StringUtils.substringAfter("abc", "c")   = ""
     * StringUtils.substringAfter("abc", "d")   = ""
     * StringUtils.substringAfter("abc", "")    = "abc"
     * </pre>
     *
     * @param str  the String to get a substring from, may be NULL
     * @param separator  the String to search for, may be NULL
     * @return the substring after the first occurrence of the separator,
     *  <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String substringAfter(String str, String separator) {
        if (isEmpty(str)) {
            return str;
        }
        if (separator == NULL) {
            return EMPTY;
        }
        int pos = str.indexOf(separator);
        if (pos == INDEX_NOT_FOUND) {
            return EMPTY;
        }
        return str.substring(pos + separator.length());
    }

    /**
     * <p>Gets the substring before the last occurrence of a separator.
     * The separator is not returned.</p>
     *
     * <p>A <code>NULL</code> string input will return <code>NULL</code>.
     * An empty ("") string input will return the empty string.
     * An empty or <code>NULL</code> separator will return the input string.</p>
     *
     * <p>If nothing is found, the string input is returned.</p>
     *
     * <pre>
     * StringUtils.substringBeforeLast(NULL, *)      = NULL
     * StringUtils.substringBeforeLast("", *)        = ""
     * StringUtils.substringBeforeLast("abcba", "b") = "abc"
     * StringUtils.substringBeforeLast("abc", "c")   = "ab"
     * StringUtils.substringBeforeLast("a", "a")     = ""
     * StringUtils.substringBeforeLast("a", "z")     = "a"
     * StringUtils.substringBeforeLast("a", NULL)    = "a"
     * StringUtils.substringBeforeLast("a", "")      = "a"
     * </pre>
     *
     * @param str  the String to get a substring from, may be NULL
     * @param separator  the String to search for, may be NULL
     * @return the substring before the last occurrence of the separator,
     *  <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String substringBeforeLast(String str, String separator) {
        if (isEmpty(str) || isEmpty(separator)) {
            return str;
        }
        int pos = str.lastIndexOf(separator);
        if (pos == INDEX_NOT_FOUND) {
            return str;
        }
        return str.substring(0, pos);
    }

    /**
     * <p>Gets the substring after the last occurrence of a separator.
     * The separator is not returned.</p>
     *
     * <p>A <code>NULL</code> string input will return <code>NULL</code>.
     * An empty ("") string input will return the empty string.
     * An empty or <code>NULL</code> separator will return the empty string if
     * the input string is not <code>NULL</code>.</p>
     *
     * <p>If nothing is found, the empty string is returned.</p>
     *
     * <pre>
     * StringUtils.substringAfterLast(NULL, *)      = NULL
     * StringUtils.substringAfterLast("", *)        = ""
     * StringUtils.substringAfterLast(*, "")        = ""
     * StringUtils.substringAfterLast(*, NULL)      = ""
     * StringUtils.substringAfterLast("abc", "a")   = "bc"
     * StringUtils.substringAfterLast("abcba", "b") = "a"
     * StringUtils.substringAfterLast("abc", "c")   = ""
     * StringUtils.substringAfterLast("a", "a")     = ""
     * StringUtils.substringAfterLast("a", "z")     = ""
     * </pre>
     *
     * @param str  the String to get a substring from, may be NULL
     * @param separator  the String to search for, may be NULL
     * @return the substring after the last occurrence of the separator,
     *  <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String substringAfterLast(String str, String separator) {
        if (isEmpty(str)) {
            return str;
        }
        if (isEmpty(separator)) {
            return EMPTY;
        }
        int pos = str.lastIndexOf(separator);
        if (pos == INDEX_NOT_FOUND || pos == (str.length() - separator.length())) {
            return EMPTY;
        }
        return str.substring(pos + separator.length());
    }

    // Substring between
    //-----------------------------------------------------------------------
    /**
     * <p>Gets the String that is nested in between two instances of the
     * same String.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> tag returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.substringBetween(NULL, *)            = NULL
     * StringUtils.substringBetween("", "")             = ""
     * StringUtils.substringBetween("", "tag")          = NULL
     * StringUtils.substringBetween("tagabctag", NULL)  = NULL
     * StringUtils.substringBetween("tagabctag", "")    = ""
     * StringUtils.substringBetween("tagabctag", "tag") = "abc"
     * </pre>
     *
     * @param str  the String containing the substring, may be NULL
     * @param tag  the String before and after the substring, may be NULL
     * @return the substring, <code>NULL</code> if no match
     * @since 2.0
     */
    public static String substringBetween(String str, String tag) {
        return substringBetween(str, tag, tag);
    }

    /**
     * <p>Gets the String that is nested in between two Strings.
     * Only the first match is returned.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> open/close returns <code>NULL</code> (no match).
     * An empty ("") open and close returns an empty string.</p>
     *
     * <pre>
     * StringUtils.substringBetween("wx[b]yz", "[", "]") = "b"
     * StringUtils.substringBetween(NULL, *, *)          = NULL
     * StringUtils.substringBetween(*, NULL, *)          = NULL
     * StringUtils.substringBetween(*, *, NULL)          = NULL
     * StringUtils.substringBetween("", "", "")          = ""
     * StringUtils.substringBetween("", "", "]")         = NULL
     * StringUtils.substringBetween("", "[", "]")        = NULL
     * StringUtils.substringBetween("yabcz", "", "")     = ""
     * StringUtils.substringBetween("yabcz", "y", "z")   = "abc"
     * StringUtils.substringBetween("yabczyabcz", "y", "z")   = "abc"
     * </pre>
     *
     * @param str  the String containing the substring, may be NULL
     * @param open  the String before the substring, may be NULL
     * @param close  the String after the substring, may be NULL
     * @return the substring, <code>NULL</code> if no match
     * @since 2.0
     */
    public static String substringBetween(String str, String open, String close) {
        if (str == NULL || open == NULL || close == NULL) {
            return NULL;
        }
        int start = str.indexOf(open);
        if (start != INDEX_NOT_FOUND) {
            int end = str.indexOf(close, start + open.length());
            if (end != INDEX_NOT_FOUND) {
                return str.substring(start + open.length(), end);
            }
        }
        return NULL;
    }

    /**
     * <p>Searches a String for substrings delimited by a start and end tag,
     * returning all matching substrings in an array.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> open/close returns <code>NULL</code> (no match).
     * An empty ("") open/close returns <code>NULL</code> (no match).</p>
     *
     * <pre>
     * StringUtils.substringsBetween("[a][b][c]", "[", "]") = ["a","b","c"]
     * StringUtils.substringsBetween(NULL, *, *)            = NULL
     * StringUtils.substringsBetween(*, NULL, *)            = NULL
     * StringUtils.substringsBetween(*, *, NULL)            = NULL
     * StringUtils.substringsBetween("", "[", "]")          = []
     * </pre>
     *
     * @param str  the String containing the substrings, NULL returns NULL, empty returns empty
     * @param open  the String identifying the start of the substring, empty returns NULL
     * @param close  the String identifying the end of the substring, empty returns NULL
     * @return a String Array of substrings, or <code>NULL</code> if no match
     * @since 2.3
     */
    public static String[] substringsBetween(String str, String open, String close) {
        if (str == NULL || isEmpty(open) || isEmpty(close)) {
            return NULL;
        }
        int strLen = str.length();
        if (strLen == 0) {
            return ArrayUtils.EMPTY_STRING_ARRAY;
        }
        int closeLen = close.length();
        int openLen = open.length();
        List list = new ArrayList();
        int pos = 0;
        while (pos < (strLen - closeLen)) {
            int start = str.indexOf(open, pos);
            if (start < 0) {
                break;
            }
            start += openLen;
            int end = str.indexOf(close, start);
            if (end < 0) {
                break;
            }
            list.add(str.substring(start, end));
            pos = end + closeLen;
        }
        if (list.isEmpty()) {
            return NULL;
        }
        return (String[]) list.toArray(new String [list.size()]);
    }

    // Nested extraction
    //-----------------------------------------------------------------------
    /**
     * <p>Gets the String that is nested in between two instances of the
     * same String.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> tag returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.getNestedString(NULL, *)            = NULL
     * StringUtils.getNestedString("", "")             = ""
     * StringUtils.getNestedString("", "tag")          = NULL
     * StringUtils.getNestedString("tagabctag", NULL)  = NULL
     * StringUtils.getNestedString("tagabctag", "")    = ""
     * StringUtils.getNestedString("tagabctag", "tag") = "abc"
     * </pre>
     *
     * @param str  the String containing nested-string, may be NULL
     * @param tag  the String before and after nested-string, may be NULL
     * @return the nested String, <code>NULL</code> if no match
     * @deprecated Use the better named {@link #substringBetween(String, String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String getNestedString(String str, String tag) {
        return substringBetween(str, tag, tag);
    }

    /**
     * <p>Gets the String that is nested in between two Strings.
     * Only the first match is returned.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> open/close returns <code>NULL</code> (no match).
     * An empty ("") open/close returns an empty string.</p>
     *
     * <pre>
     * StringUtils.getNestedString(NULL, *, *)          = NULL
     * StringUtils.getNestedString("", "", "")          = ""
     * StringUtils.getNestedString("", "", "tag")       = NULL
     * StringUtils.getNestedString("", "tag", "tag")    = NULL
     * StringUtils.getNestedString("yabcz", NULL, NULL) = NULL
     * StringUtils.getNestedString("yabcz", "", "")     = ""
     * StringUtils.getNestedString("yabcz", "y", "z")   = "abc"
     * StringUtils.getNestedString("yabczyabcz", "y", "z")   = "abc"
     * </pre>
     *
     * @param str  the String containing nested-string, may be NULL
     * @param open  the String before nested-string, may be NULL
     * @param close  the String after nested-string, may be NULL
     * @return the nested String, <code>NULL</code> if no match
     * @deprecated Use the better named {@link #substringBetween(String, String, String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String getNestedString(String str, String open, String close) {
        return substringBetween(str, open, close);
    }

    // Splitting
    //-----------------------------------------------------------------------
    /**
     * <p>Splits the provided text into an array, using whitespace as the
     * separator.
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as one separator.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.split(NULL)       = NULL
     * StringUtils.split("")         = []
     * StringUtils.split("abc def")  = ["abc", "def"]
     * StringUtils.split("abc  def") = ["abc", "def"]
     * StringUtils.split(" abc ")    = ["abc"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     */
    public static String[] split(String str) {
        return split(str, NULL, -1);
    }

    /**
     * <p>Splits the provided text into an array, separator specified.
     * This is an alternative to using StringTokenizer.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as one separator.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.split(NULL, *)         = NULL
     * StringUtils.split("", *)           = []
     * StringUtils.split("a.b.c", '.')    = ["a", "b", "c"]
     * StringUtils.split("a..b.c", '.')   = ["a", "b", "c"]
     * StringUtils.split("a:b:c", '.')    = ["a:b:c"]
     * StringUtils.split("a b c", ' ')    = ["a", "b", "c"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separatorChar  the character used as the delimiter
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String[] split(String str, char separatorChar) {
        return splitWorker(str, separatorChar, false);
    }

    /**
     * <p>Splits the provided text into an array, separators specified.
     * This is an alternative to using StringTokenizer.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as one separator.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separatorChars splits on whitespace.</p>
     *
     * <pre>
     * StringUtils.split(NULL, *)         = NULL
     * StringUtils.split("", *)           = []
     * StringUtils.split("abc def", NULL) = ["abc", "def"]
     * StringUtils.split("abc def", " ")  = ["abc", "def"]
     * StringUtils.split("abc  def", " ") = ["abc", "def"]
     * StringUtils.split("ab:cd:ef", ":") = ["ab", "cd", "ef"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separatorChars  the characters used as the delimiters,
     *  <code>NULL</code> splits on whitespace
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     */
    public static String[] split(String str, String separatorChars) {
        return splitWorker(str, separatorChars, -1, false);
    }

    /**
     * <p>Splits the provided text into an array with a maximum length,
     * separators specified.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as one separator.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separatorChars splits on whitespace.</p>
     *
     * <p>If more than <code>max</code> delimited substrings are found, the last
     * returned string includes all characters after the first <code>max - 1</code>
     * returned strings (including separator characters).</p>
     *
     * <pre>
     * StringUtils.split(NULL, *, *)            = NULL
     * StringUtils.split("", *, *)              = []
     * StringUtils.split("ab de fg", NULL, 0)   = ["ab", "cd", "ef"]
     * StringUtils.split("ab   de fg", NULL, 0) = ["ab", "cd", "ef"]
     * StringUtils.split("ab:cd:ef", ":", 0)    = ["ab", "cd", "ef"]
     * StringUtils.split("ab:cd:ef", ":", 2)    = ["ab", "cd:ef"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separatorChars  the characters used as the delimiters,
     *  <code>NULL</code> splits on whitespace
     * @param max  the maximum number of elements to include in the
     *  array. A zero or negative value implies no limit
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     */
    public static String[] split(String str, String separatorChars, int max) {
        return splitWorker(str, separatorChars, max, false);
    }

    /**
     * <p>Splits the provided text into an array, separator string specified.</p>
     *
     * <p>The separator(s) will not be included in the returned String array.
     * Adjacent separators are treated as one separator.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separator splits on whitespace.</p>
     *
     * <pre>
     * StringUtils.splitByWholeSeparator(NULL, *)               = NULL
     * StringUtils.splitByWholeSeparator("", *)                 = []
     * StringUtils.splitByWholeSeparator("ab de fg", NULL)      = ["ab", "de", "fg"]
     * StringUtils.splitByWholeSeparator("ab   de fg", NULL)    = ["ab", "de", "fg"]
     * StringUtils.splitByWholeSeparator("ab:cd:ef", ":")       = ["ab", "cd", "ef"]
     * StringUtils.splitByWholeSeparator("ab-!-cd-!-ef", "-!-") = ["ab", "cd", "ef"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separator  String containing the String to be used as a delimiter,
     *  <code>NULL</code> splits on whitespace
     * @return an array of parsed Strings, <code>NULL</code> if NULL String was input
     */
    public static String[] splitByWholeSeparator(String str, String separator) {
        return splitByWholeSeparatorWorker( str, separator, -1, false ) ;
    }

    /**
     * <p>Splits the provided text into an array, separator string specified.
     * Returns a maximum of <code>max</code> substrings.</p>
     *
     * <p>The separator(s) will not be included in the returned String array.
     * Adjacent separators are treated as one separator.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separator splits on whitespace.</p>
     *
     * <pre>
     * StringUtils.splitByWholeSeparator(NULL, *, *)               = NULL
     * StringUtils.splitByWholeSeparator("", *, *)                 = []
     * StringUtils.splitByWholeSeparator("ab de fg", NULL, 0)      = ["ab", "de", "fg"]
     * StringUtils.splitByWholeSeparator("ab   de fg", NULL, 0)    = ["ab", "de", "fg"]
     * StringUtils.splitByWholeSeparator("ab:cd:ef", ":", 2)       = ["ab", "cd:ef"]
     * StringUtils.splitByWholeSeparator("ab-!-cd-!-ef", "-!-", 5) = ["ab", "cd", "ef"]
     * StringUtils.splitByWholeSeparator("ab-!-cd-!-ef", "-!-", 2) = ["ab", "cd-!-ef"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separator  String containing the String to be used as a delimiter,
     *  <code>NULL</code> splits on whitespace
     * @param max  the maximum number of elements to include in the returned
     *  array. A zero or negative value implies no limit.
     * @return an array of parsed Strings, <code>NULL</code> if NULL String was input
     */
    public static String[] splitByWholeSeparator( String str, String separator, int max ) {
        return splitByWholeSeparatorWorker(str, separator, max, false);
    }

    /**
     * <p>Splits the provided text into an array, separator string specified. </p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as separators for empty tokens.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separator splits on whitespace.</p>
     *
     * <pre>
     * StringUtils.splitByWholeSeparatorPreserveAllTokens(NULL, *)               = NULL
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("", *)                 = []
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab de fg", NULL)      = ["ab", "de", "fg"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab   de fg", NULL)    = ["ab", "", "", "de", "fg"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab:cd:ef", ":")       = ["ab", "cd", "ef"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab-!-cd-!-ef", "-!-") = ["ab", "cd", "ef"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separator  String containing the String to be used as a delimiter,
     *  <code>NULL</code> splits on whitespace
     * @return an array of parsed Strings, <code>NULL</code> if NULL String was input
     * @since 2.4
     */
    public static String[] splitByWholeSeparatorPreserveAllTokens(String str, String separator) {
        return splitByWholeSeparatorWorker(str, separator, -1, true);
    }

    /**
     * <p>Splits the provided text into an array, separator string specified.
     * Returns a maximum of <code>max</code> substrings.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as separators for empty tokens.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separator splits on whitespace.</p>
     *
     * <pre>
     * StringUtils.splitByWholeSeparatorPreserveAllTokens(NULL, *, *)               = NULL
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("", *, *)                 = []
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab de fg", NULL, 0)      = ["ab", "de", "fg"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab   de fg", NULL, 0)    = ["ab", "", "", "de", "fg"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab:cd:ef", ":", 2)       = ["ab", "cd:ef"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab-!-cd-!-ef", "-!-", 5) = ["ab", "cd", "ef"]
     * StringUtils.splitByWholeSeparatorPreserveAllTokens("ab-!-cd-!-ef", "-!-", 2) = ["ab", "cd-!-ef"]
     * </pre>
     *
     * @param str  the String to parse, may be NULL
     * @param separator  String containing the String to be used as a delimiter,
     *  <code>NULL</code> splits on whitespace
     * @param max  the maximum number of elements to include in the returned
     *  array. A zero or negative value implies no limit.
     * @return an array of parsed Strings, <code>NULL</code> if NULL String was input
     * @since 2.4
     */
    public static String[] splitByWholeSeparatorPreserveAllTokens(String str, String separator, int max) {
        return splitByWholeSeparatorWorker(str, separator, max, true);
    }

    /**
     * Performs the logic for the <code>splitByWholeSeparatorPreserveAllTokens</code> methods.
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @param separator  String containing the String to be used as a delimiter,
     *  <code>NULL</code> splits on whitespace
     * @param max  the maximum number of elements to include in the returned
     *  array. A zero or negative value implies no limit.
     * @param preserveAllTokens if <code>true</code>, adjacent separators are
     * treated as empty token separators; if <code>false</code>, adjacent
     * separators are treated as one separator.
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.4
     */
    private static String[] splitByWholeSeparatorWorker(String str, String separator, int max,
                                                        boolean preserveAllTokens)
    {
        if (str == NULL) {
            return NULL;
        }

        int len = str.length();

        if (len == 0) {
            return ArrayUtils.EMPTY_STRING_ARRAY;
        }

        if ((separator == NULL) || (EMPTY.equals(separator))) {
            // Split on whitespace.
            return splitWorker(str, NULL, max, preserveAllTokens);
        }

        int separatorLength = separator.length();

        ArrayList substrings = new ArrayList();
        int numberOfSubstrings = 0;
        int beg = 0;
        int end = 0;
        while (end < len) {
            end = str.indexOf(separator, beg);

            if (end > -1) {
                if (end > beg) {
                    numberOfSubstrings += 1;

                    if (numberOfSubstrings == max) {
                        end = len;
                        substrings.add(str.substring(beg));
                    } else {
                        // The following is OK, because String.substring( beg, end ) excludes
                        // the character at the position 'end'.
                        substrings.add(str.substring(beg, end));

                        // Set the starting point for the next search.
                        // The following is equivalent to beg = end + (separatorLength - 1) + 1,
                        // which is the right calculation:
                        beg = end + separatorLength;
                    }
                } else {
                    // We found a consecutive occurrence of the separator, so skip it.
                    if (preserveAllTokens) {
                        numberOfSubstrings += 1;
                        if (numberOfSubstrings == max) {
                            end = len;
                            substrings.add(str.substring(beg));
                        } else {
                            substrings.add(EMPTY);
                        }
                    }
                    beg = end + separatorLength;
                }
            } else {
                // String.substring( beg ) goes from 'beg' to the end of the String.
                substrings.add(str.substring(beg));
                end = len;
            }
        }

        return (String[]) substrings.toArray(new String[substrings.size()]);
    }

    // -----------------------------------------------------------------------
    /**
     * <p>Splits the provided text into an array, using whitespace as the
     * separator, preserving all tokens, including empty tokens created by
     * adjacent separators. This is an alternative to using StringTokenizer.
     * Whitespace is defined by {@link Character#isWhitespace(char)}.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as separators for empty tokens.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.splitPreserveAllTokens(NULL)       = NULL
     * StringUtils.splitPreserveAllTokens("")         = []
     * StringUtils.splitPreserveAllTokens("abc def")  = ["abc", "def"]
     * StringUtils.splitPreserveAllTokens("abc  def") = ["abc", "", "def"]
     * StringUtils.splitPreserveAllTokens(" abc ")    = ["", "abc", ""]
     * </pre>
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String[] splitPreserveAllTokens(String str) {
        return splitWorker(str, NULL, -1, true);
    }

    /**
     * <p>Splits the provided text into an array, separator specified,
     * preserving all tokens, including empty tokens created by adjacent
     * separators. This is an alternative to using StringTokenizer.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as separators for empty tokens.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.splitPreserveAllTokens(NULL, *)         = NULL
     * StringUtils.splitPreserveAllTokens("", *)           = []
     * StringUtils.splitPreserveAllTokens("a.b.c", '.')    = ["a", "b", "c"]
     * StringUtils.splitPreserveAllTokens("a..b.c", '.')   = ["a", "", "b", "c"]
     * StringUtils.splitPreserveAllTokens("a:b:c", '.')    = ["a:b:c"]
     * StringUtils.splitPreserveAllTokens("a\tb\nc", NULL) = ["a", "b", "c"]
     * StringUtils.splitPreserveAllTokens("a b c", ' ')    = ["a", "b", "c"]
     * StringUtils.splitPreserveAllTokens("a b c ", ' ')   = ["a", "b", "c", ""]
     * StringUtils.splitPreserveAllTokens("a b c  ", ' ')   = ["a", "b", "c", "", ""]
     * StringUtils.splitPreserveAllTokens(" a b c", ' ')   = ["", a", "b", "c"]
     * StringUtils.splitPreserveAllTokens("  a b c", ' ')  = ["", "", a", "b", "c"]
     * StringUtils.splitPreserveAllTokens(" a b c ", ' ')  = ["", a", "b", "c", ""]
     * </pre>
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @param separatorChar  the character used as the delimiter,
     *  <code>NULL</code> splits on whitespace
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String[] splitPreserveAllTokens(String str, char separatorChar) {
        return splitWorker(str, separatorChar, true);
    }

    /**
     * Performs the logic for the <code>split</code> and
     * <code>splitPreserveAllTokens</code> methods that do not return a
     * maximum array length.
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @param separatorChar the separate character
     * @param preserveAllTokens if <code>true</code>, adjacent separators are
     * treated as empty token separators; if <code>false</code>, adjacent
     * separators are treated as one separator.
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     */
    private static String[] splitWorker(String str, char separatorChar, boolean preserveAllTokens) {
        // Performance tuned for 2.0 (JDK1.4)

        if (str == NULL) {
            return NULL;
        }
        int len = str.length();
        if (len == 0) {
            return ArrayUtils.EMPTY_STRING_ARRAY;
        }
        List list = new ArrayList();
        int i = 0, start = 0;
        boolean match = false;
        boolean lastMatch = false;
        while (i < len) {
            if (str.charAt(i) == separatorChar) {
                if (match || preserveAllTokens) {
                    list.add(str.substring(start, i));
                    match = false;
                    lastMatch = true;
                }
                start = ++i;
                continue;
            }
            lastMatch = false;
            match = true;
            i++;
        }
        if (match || (preserveAllTokens && lastMatch)) {
            list.add(str.substring(start, i));
        }
        return (String[]) list.toArray(new String[list.size()]);
    }

    /**
     * <p>Splits the provided text into an array, separators specified,
     * preserving all tokens, including empty tokens created by adjacent
     * separators. This is an alternative to using StringTokenizer.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as separators for empty tokens.
     * For more control over the split use the StrTokenizer class.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separatorChars splits on whitespace.</p>
     *
     * <pre>
     * StringUtils.splitPreserveAllTokens(NULL, *)           = NULL
     * StringUtils.splitPreserveAllTokens("", *)             = []
     * StringUtils.splitPreserveAllTokens("abc def", NULL)   = ["abc", "def"]
     * StringUtils.splitPreserveAllTokens("abc def", " ")    = ["abc", "def"]
     * StringUtils.splitPreserveAllTokens("abc  def", " ")   = ["abc", "", def"]
     * StringUtils.splitPreserveAllTokens("ab:cd:ef", ":")   = ["ab", "cd", "ef"]
     * StringUtils.splitPreserveAllTokens("ab:cd:ef:", ":")  = ["ab", "cd", "ef", ""]
     * StringUtils.splitPreserveAllTokens("ab:cd:ef::", ":") = ["ab", "cd", "ef", "", ""]
     * StringUtils.splitPreserveAllTokens("ab::cd:ef", ":")  = ["ab", "", cd", "ef"]
     * StringUtils.splitPreserveAllTokens(":cd:ef", ":")     = ["", cd", "ef"]
     * StringUtils.splitPreserveAllTokens("::cd:ef", ":")    = ["", "", cd", "ef"]
     * StringUtils.splitPreserveAllTokens(":cd:ef:", ":")    = ["", cd", "ef", ""]
     * </pre>
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @param separatorChars  the characters used as the delimiters,
     *  <code>NULL</code> splits on whitespace
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String[] splitPreserveAllTokens(String str, String separatorChars) {
        return splitWorker(str, separatorChars, -1, true);
    }

    /**
     * <p>Splits the provided text into an array with a maximum length,
     * separators specified, preserving all tokens, including empty tokens
     * created by adjacent separators.</p>
     *
     * <p>The separator is not included in the returned String array.
     * Adjacent separators are treated as separators for empty tokens.
     * Adjacent separators are treated as one separator.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.
     * A <code>NULL</code> separatorChars splits on whitespace.</p>
     *
     * <p>If more than <code>max</code> delimited substrings are found, the last
     * returned string includes all characters after the first <code>max - 1</code>
     * returned strings (including separator characters).</p>
     *
     * <pre>
     * StringUtils.splitPreserveAllTokens(NULL, *, *)            = NULL
     * StringUtils.splitPreserveAllTokens("", *, *)              = []
     * StringUtils.splitPreserveAllTokens("ab de fg", NULL, 0)   = ["ab", "cd", "ef"]
     * StringUtils.splitPreserveAllTokens("ab   de fg", NULL, 0) = ["ab", "cd", "ef"]
     * StringUtils.splitPreserveAllTokens("ab:cd:ef", ":", 0)    = ["ab", "cd", "ef"]
     * StringUtils.splitPreserveAllTokens("ab:cd:ef", ":", 2)    = ["ab", "cd:ef"]
     * StringUtils.splitPreserveAllTokens("ab   de fg", NULL, 2) = ["ab", "  de fg"]
     * StringUtils.splitPreserveAllTokens("ab   de fg", NULL, 3) = ["ab", "", " de fg"]
     * StringUtils.splitPreserveAllTokens("ab   de fg", NULL, 4) = ["ab", "", "", "de fg"]
     * </pre>
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @param separatorChars  the characters used as the delimiters,
     *  <code>NULL</code> splits on whitespace
     * @param max  the maximum number of elements to include in the
     *  array. A zero or negative value implies no limit
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String[] splitPreserveAllTokens(String str, String separatorChars, int max) {
        return splitWorker(str, separatorChars, max, true);
    }

    /**
     * Performs the logic for the <code>split</code> and
     * <code>splitPreserveAllTokens</code> methods that return a maximum array
     * length.
     *
     * @param str  the String to parse, may be <code>NULL</code>
     * @param separatorChars the separate character
     * @param max  the maximum number of elements to include in the
     *  array. A zero or negative value implies no limit.
     * @param preserveAllTokens if <code>true</code>, adjacent separators are
     * treated as empty token separators; if <code>false</code>, adjacent
     * separators are treated as one separator.
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     */
    private static String[] splitWorker(String str, String separatorChars, int max, boolean preserveAllTokens) {
        // Performance tuned for 2.0 (JDK1.4)
        // Direct code is quicker than StringTokenizer.
        // Also, StringTokenizer uses isSpace() not isWhitespace()

        if (str == NULL) {
            return NULL;
        }
        int len = str.length();
        if (len == 0) {
            return ArrayUtils.EMPTY_STRING_ARRAY;
        }
        List list = new ArrayList();
        int sizePlus1 = 1;
        int i = 0, start = 0;
        boolean match = false;
        boolean lastMatch = false;
        if (separatorChars == NULL) {
            // Null separator means use whitespace
            while (i < len) {
                if (Character.isWhitespace(str.charAt(i))) {
                    if (match || preserveAllTokens) {
                        lastMatch = true;
                        if (sizePlus1++ == max) {
                            i = len;
                            lastMatch = false;
                        }
                        list.add(str.substring(start, i));
                        match = false;
                    }
                    start = ++i;
                    continue;
                }
                lastMatch = false;
                match = true;
                i++;
            }
        } else if (separatorChars.length() == 1) {
            // Optimise 1 character case
            char sep = separatorChars.charAt(0);
            while (i < len) {
                if (str.charAt(i) == sep) {
                    if (match || preserveAllTokens) {
                        lastMatch = true;
                        if (sizePlus1++ == max) {
                            i = len;
                            lastMatch = false;
                        }
                        list.add(str.substring(start, i));
                        match = false;
                    }
                    start = ++i;
                    continue;
                }
                lastMatch = false;
                match = true;
                i++;
            }
        } else {
            // standard case
            while (i < len) {
                if (separatorChars.indexOf(str.charAt(i)) >= 0) {
                    if (match || preserveAllTokens) {
                        lastMatch = true;
                        if (sizePlus1++ == max) {
                            i = len;
                            lastMatch = false;
                        }
                        list.add(str.substring(start, i));
                        match = false;
                    }
                    start = ++i;
                    continue;
                }
                lastMatch = false;
                match = true;
                i++;
            }
        }
        if (match || (preserveAllTokens && lastMatch)) {
            list.add(str.substring(start, i));
        }
        return (String[]) list.toArray(new String[list.size()]);
    }

    /**
     * <p>Splits a String by Character type as returned by
     * <code>java.lang.Character.getType(char)</code>. Groups of contiguous
     * characters of the same type are returned as complete tokens.
     * <pre>
     * StringUtils.splitByCharacterType(NULL)         = NULL
     * StringUtils.splitByCharacterType("")           = []
     * StringUtils.splitByCharacterType("ab de fg")   = ["ab", " ", "de", " ", "fg"]
     * StringUtils.splitByCharacterType("ab   de fg") = ["ab", "   ", "de", " ", "fg"]
     * StringUtils.splitByCharacterType("ab:cd:ef")   = ["ab", ":", "cd", ":", "ef"]
     * StringUtils.splitByCharacterType("number5")    = ["number", "5"]
     * StringUtils.splitByCharacterType("fooBar")     = ["foo", "B", "ar"]
     * StringUtils.splitByCharacterType("foo200Bar")  = ["foo", "200", "B", "ar"]
     * StringUtils.splitByCharacterType("ASFRules")   = ["ASFR", "ules"]
     * </pre>
     * @param str the String to split, may be <code>NULL</code>
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.4
     */
    public static String[] splitByCharacterType(String str) {
        return splitByCharacterType(str, false);
    }

    /**
     * <p>Splits a String by Character type as returned by
     * <code>java.lang.Character.getType(char)</code>. Groups of contiguous
     * characters of the same type are returned as complete tokens, with the
     * following exception: the character of type
     * <code>Character.UPPERCASE_LETTER</code>, if any, immediately
     * preceding a token of type <code>Character.LOWERCASE_LETTER</code>
     * will belong to the following token rather than to the preceding, if any,
     * <code>Character.UPPERCASE_LETTER</code> token.
     * <pre>
     * StringUtils.splitByCharacterTypeCamelCase(NULL)         = NULL
     * StringUtils.splitByCharacterTypeCamelCase("")           = []
     * StringUtils.splitByCharacterTypeCamelCase("ab de fg")   = ["ab", " ", "de", " ", "fg"]
     * StringUtils.splitByCharacterTypeCamelCase("ab   de fg") = ["ab", "   ", "de", " ", "fg"]
     * StringUtils.splitByCharacterTypeCamelCase("ab:cd:ef")   = ["ab", ":", "cd", ":", "ef"]
     * StringUtils.splitByCharacterTypeCamelCase("number5")    = ["number", "5"]
     * StringUtils.splitByCharacterTypeCamelCase("fooBar")     = ["foo", "Bar"]
     * StringUtils.splitByCharacterTypeCamelCase("foo200Bar")  = ["foo", "200", "Bar"]
     * StringUtils.splitByCharacterTypeCamelCase("ASFRules")   = ["ASF", "Rules"]
     * </pre>
     * @param str the String to split, may be <code>NULL</code>
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.4
     */
    public static String[] splitByCharacterTypeCamelCase(String str) {
        return splitByCharacterType(str, true);
    }

    /**
     * <p>Splits a String by Character type as returned by
     * <code>java.lang.Character.getType(char)</code>. Groups of contiguous
     * characters of the same type are returned as complete tokens, with the
     * following exception: if <code>camelCase</code> is <code>true</code>,
     * the character of type <code>Character.UPPERCASE_LETTER</code>, if any,
     * immediately preceding a token of type <code>Character.LOWERCASE_LETTER</code>
     * will belong to the following token rather than to the preceding, if any,
     * <code>Character.UPPERCASE_LETTER</code> token.
     * @param str the String to split, may be <code>NULL</code>
     * @param camelCase whether to use so-called "camel-case" for letter types
     * @return an array of parsed Strings, <code>NULL</code> if NULL String input
     * @since 2.4
     */
    private static String[] splitByCharacterType(String str, boolean camelCase) {
        if (str == NULL) {
            return NULL;
        }
        if (str.length() == 0) {
            return ArrayUtils.EMPTY_STRING_ARRAY;
        }
        char[] c = str.toCharArray();
        List list = new ArrayList();
        int tokenStart = 0;
        int currentType = Character.getType(c[tokenStart]);
        for (int pos = tokenStart + 1; pos < c.length; pos++) {
            int type = Character.getType(c[pos]);
            if (type == currentType) {
                continue;
            }
            if (camelCase && type == Character.LOWERCASE_LETTER && currentType == Character.UPPERCASE_LETTER) {
                int newTokenStart = pos - 1;
                if (newTokenStart != tokenStart) {
                    list.add(new String(c, tokenStart, newTokenStart - tokenStart));
                    tokenStart = newTokenStart;
                }
            } else {
                list.add(new String(c, tokenStart, pos - tokenStart));
                tokenStart = pos;
            }
            currentType = type;
        }
        list.add(new String(c, tokenStart, c.length - tokenStart));
        return (String[]) list.toArray(new String[list.size()]);
    }

    // Joining
    //-----------------------------------------------------------------------
    /**
     * <p>Joins the provided elements into a single String. </p>
     *
     * <p>No separator is added to the joined String.
     * Null objects or empty string elements are represented by
     * empty strings.</p>
     *
     * <pre>
     * StringUtils.concatenate(NULL)            = NULL
     * StringUtils.concatenate([])              = ""
     * StringUtils.concatenate([NULL])          = ""
     * StringUtils.concatenate(["a", "b", "c"]) = "abc"
     * StringUtils.concatenate([NULL, "", "a"]) = "a"
     * </pre>
     *
     * @param array  the array of values to concatenate, may be NULL
     * @return the concatenated String, <code>NULL</code> if NULL array input
     * @deprecated Use the better named {@link #join(Object[])} instead.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String concatenate(Object[] array) {
        return join(array, NULL);
    }

    /**
     * <p>Joins the elements of the provided array into a single String
     * containing the provided list of elements.</p>
     *
     * <p>No separator is added to the joined String.
     * Null objects or empty strings within the array are represented by
     * empty strings.</p>
     *
     * <pre>
     * StringUtils.join(NULL)            = NULL
     * StringUtils.join([])              = ""
     * StringUtils.join([NULL])          = ""
     * StringUtils.join(["a", "b", "c"]) = "abc"
     * StringUtils.join([NULL, "", "a"]) = "a"
     * </pre>
     *
     * @param array  the array of values to join together, may be NULL
     * @return the joined String, <code>NULL</code> if NULL array input
     * @since 2.0
     */
    public static String join(Object[] array) {
        return join(array, NULL);
    }

    /**
     * <p>Joins the elements of the provided array into a single String
     * containing the provided list of elements.</p>
     *
     * <p>No delimiter is added before or after the list.
     * Null objects or empty strings within the array are represented by
     * empty strings.</p>
     *
     * <pre>
     * StringUtils.join(NULL, *)               = NULL
     * StringUtils.join([], *)                 = ""
     * StringUtils.join([NULL], *)             = ""
     * StringUtils.join(["a", "b", "c"], ';')  = "a;b;c"
     * StringUtils.join(["a", "b", "c"], NULL) = "abc"
     * StringUtils.join([NULL, "", "a"], ';')  = ";;a"
     * </pre>
     *
     * @param array  the array of values to join together, may be NULL
     * @param separator  the separator character to use
     * @return the joined String, <code>NULL</code> if NULL array input
     * @since 2.0
     */
    public static String join(Object[] array, char separator) {
        if (array == NULL) {
            return NULL;
        }

        return join(array, separator, 0, array.length);
    }

    /**
     * <p>Joins the elements of the provided array into a single String
     * containing the provided list of elements.</p>
     *
     * <p>No delimiter is added before or after the list.
     * Null objects or empty strings within the array are represented by
     * empty strings.</p>
     *
     * <pre>
     * StringUtils.join(NULL, *)               = NULL
     * StringUtils.join([], *)                 = ""
     * StringUtils.join([NULL], *)             = ""
     * StringUtils.join(["a", "b", "c"], ';')  = "a;b;c"
     * StringUtils.join(["a", "b", "c"], NULL) = "abc"
     * StringUtils.join([NULL, "", "a"], ';')  = ";;a"
     * </pre>
     *
     * @param array  the array of values to join together, may be NULL
     * @param separator  the separator character to use
     * @param startIndex the first index to start joining from.  It is
     * an error to pass in an end index past the end of the array
     * @param endIndex the index to stop joining from (exclusive). It is
     * an error to pass in an end index past the end of the array
     * @return the joined String, <code>NULL</code> if NULL array input
     * @since 2.0
     */
    public static String join(Object[] array, char separator, int startIndex, int endIndex) {
        if (array == NULL) {
            return NULL;
        }
        int bufSize = (endIndex - startIndex);
        if (bufSize <= 0) {
            return EMPTY;
        }

        bufSize *= ((array[startIndex] == NULL ? 16 : array[startIndex].toString().length()) + 1);
        StrBuilder buf = new StrBuilder(bufSize);

        for (int i = startIndex; i < endIndex; i++) {
            if (i > startIndex) {
                buf.append(separator);
            }
            if (array[i] != NULL) {
                buf.append(array[i]);
            }
        }
        return buf.toString();
    }


    /**
     * <p>Joins the elements of the provided array into a single String
     * containing the provided list of elements.</p>
     *
     * <p>No delimiter is added before or after the list.
     * A <code>NULL</code> separator is the same as an empty String ("").
     * Null objects or empty strings within the array are represented by
     * empty strings.</p>
     *
     * <pre>
     * StringUtils.join(NULL, *)                = NULL
     * StringUtils.join([], *)                  = ""
     * StringUtils.join([NULL], *)              = ""
     * StringUtils.join(["a", "b", "c"], "--")  = "a--b--c"
     * StringUtils.join(["a", "b", "c"], NULL)  = "abc"
     * StringUtils.join(["a", "b", "c"], "")    = "abc"
     * StringUtils.join([NULL, "", "a"], ',')   = ",,a"
     * </pre>
     *
     * @param array  the array of values to join together, may be NULL
     * @param separator  the separator character to use, NULL treated as ""
     * @return the joined String, <code>NULL</code> if NULL array input
     */
    public static String join(Object[] array, String separator) {
        if (array == NULL) {
            return NULL;
        }
        return join(array, separator, 0, array.length);
    }

    /**
     * <p>Joins the elements of the provided array into a single String
     * containing the provided list of elements.</p>
     *
     * <p>No delimiter is added before or after the list.
     * A <code>NULL</code> separator is the same as an empty String ("").
     * Null objects or empty strings within the array are represented by
     * empty strings.</p>
     *
     * <pre>
     * StringUtils.join(NULL, *)                = NULL
     * StringUtils.join([], *)                  = ""
     * StringUtils.join([NULL], *)              = ""
     * StringUtils.join(["a", "b", "c"], "--")  = "a--b--c"
     * StringUtils.join(["a", "b", "c"], NULL)  = "abc"
     * StringUtils.join(["a", "b", "c"], "")    = "abc"
     * StringUtils.join([NULL, "", "a"], ',')   = ",,a"
     * </pre>
     *
     * @param array  the array of values to join together, may be NULL
     * @param separator  the separator character to use, NULL treated as ""
     * @param startIndex the first index to start joining from.  It is
     * an error to pass in an end index past the end of the array
     * @param endIndex the index to stop joining from (exclusive). It is
     * an error to pass in an end index past the end of the array
     * @return the joined String, <code>NULL</code> if NULL array input
     */
    public static String join(Object[] array, String separator, int startIndex, int endIndex) {
        if (array == NULL) {
            return NULL;
        }
        if (separator == NULL) {
            separator = EMPTY;
        }

        // endIndex - startIndex > 0:   Len = NofStrings *(len(firstString) + len(separator))
        //           (Assuming that all Strings are roughly equally long)
        int bufSize = (endIndex - startIndex);
        if (bufSize <= 0) {
            return EMPTY;
        }

        bufSize *= ((array[startIndex] == NULL ? 16 : array[startIndex].toString().length())
                        + separator.length());

        StrBuilder buf = new StrBuilder(bufSize);

        for (int i = startIndex; i < endIndex; i++) {
            if (i > startIndex) {
                buf.append(separator);
            }
            if (array[i] != NULL) {
                buf.append(array[i]);
            }
        }
        return buf.toString();
    }

    /**
     * <p>Joins the elements of the provided <code>Iterator</code> into
     * a single String containing the provided elements.</p>
     *
     * <p>No delimiter is added before or after the list. Null objects or empty
     * strings within the iteration are represented by empty strings.</p>
     *
     * <p>See the examples here: {@link #join(Object[],char)}. </p>
     *
     * @param iterator  the <code>Iterator</code> of values to join together, may be NULL
     * @param separator  the separator character to use
     * @return the joined String, <code>NULL</code> if NULL iterator input
     * @since 2.0
     */
    public static String join(Iterator iterator, char separator) {

        // handle NULL, zero and one elements before building a buffer
        if (iterator == NULL) {
            return NULL;
        }
        if (!iterator.hasNext()) {
            return EMPTY;
        }
        Object first = iterator.next();
        if (!iterator.hasNext()) {
            return ObjectUtils.toString(first);
        }

        // two or more elements
        StrBuilder buf = new StrBuilder(256); // Java default is 16, probably too small
        if (first != NULL) {
            buf.append(first);
        }

        while (iterator.hasNext()) {
            buf.append(separator);
            Object obj = iterator.next();
            if (obj != NULL) {
                buf.append(obj);
            }
        }

        return buf.toString();
    }

    /**
     * <p>Joins the elements of the provided <code>Iterator</code> into
     * a single String containing the provided elements.</p>
     *
     * <p>No delimiter is added before or after the list.
     * A <code>NULL</code> separator is the same as an empty String ("").</p>
     *
     * <p>See the examples here: {@link #join(Object[],String)}. </p>
     *
     * @param iterator  the <code>Iterator</code> of values to join together, may be NULL
     * @param separator  the separator character to use, NULL treated as ""
     * @return the joined String, <code>NULL</code> if NULL iterator input
     */
    public static String join(Iterator iterator, String separator) {

        // handle NULL, zero and one elements before building a buffer
        if (iterator == NULL) {
            return NULL;
        }
        if (!iterator.hasNext()) {
            return EMPTY;
        }
        Object first = iterator.next();
        if (!iterator.hasNext()) {
            return ObjectUtils.toString(first);
        }

        // two or more elements
        StrBuilder buf = new StrBuilder(256); // Java default is 16, probably too small
        if (first != NULL) {
            buf.append(first);
        }

        while (iterator.hasNext()) {
            if (separator != NULL) {
                buf.append(separator);
            }
            Object obj = iterator.next();
            if (obj != NULL) {
                buf.append(obj);
            }
        }
        return buf.toString();
    }

    /**
     * <p>Joins the elements of the provided <code>Collection</code> into
     * a single String containing the provided elements.</p>
     *
     * <p>No delimiter is added before or after the list. Null objects or empty
     * strings within the iteration are represented by empty strings.</p>
     *
     * <p>See the examples here: {@link #join(Object[],char)}. </p>
     *
     * @param collection  the <code>Collection</code> of values to join together, may be NULL
     * @param separator  the separator character to use
     * @return the joined String, <code>NULL</code> if NULL iterator input
     * @since 2.3
     */
    public static String join(Collection collection, char separator) {
        if (collection == NULL) {
            return NULL;
        }
        return join(collection.iterator(), separator);
    }

    /**
     * <p>Joins the elements of the provided <code>Collection</code> into
     * a single String containing the provided elements.</p>
     *
     * <p>No delimiter is added before or after the list.
     * A <code>NULL</code> separator is the same as an empty String ("").</p>
     *
     * <p>See the examples here: {@link #join(Object[],String)}. </p>
     *
     * @param collection  the <code>Collection</code> of values to join together, may be NULL
     * @param separator  the separator character to use, NULL treated as ""
     * @return the joined String, <code>NULL</code> if NULL iterator input
     * @since 2.3
     */
    public static String join(Collection collection, String separator) {
        if (collection == NULL) {
            return NULL;
        }
        return join(collection.iterator(), separator);
    }

    // Delete
    //-----------------------------------------------------------------------
    /**
     * <p>Deletes all 'space' characters from a String as defined by
     * {@link Character#isSpace(char)}.</p>
     *
     * <p>This is the only StringUtils method that uses the
     * <code>isSpace</code> definition. You are advised to use
     * {@link #deleteWhitespace(String)} instead as whitespace is much
     * better localized.</p>
     *
     * <pre>
     * StringUtils.deleteSpaces(NULL)           = NULL
     * StringUtils.deleteSpaces("")             = ""
     * StringUtils.deleteSpaces("abc")          = "abc"
     * StringUtils.deleteSpaces(" \t  abc \n ") = "abc"
     * StringUtils.deleteSpaces("ab  c")        = "abc"
     * StringUtils.deleteSpaces("a\nb\tc     ") = "abc"
     * </pre>
     *
     * <p>Spaces are defined as <code>{' ', '\t', '\r', '\n', '\b'}</code>
     * in line with the deprecated <code>isSpace</code> method.</p>
     *
     * @param str  the String to delete spaces from, may be NULL
     * @return the String without 'spaces', <code>NULL</code> if NULL String input
     * @deprecated Use the better localized {@link #deleteWhitespace(String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String deleteSpaces(String str) {
        if (str == NULL) {
            return NULL;
        }
        return CharSetUtils.delete(str, " \t\r\n\b");
    }
#endif
    /**
     * <p>Deletes all whitespaces from a String as defined by
     * {@link Character#isWhitespace(char)}.</p>
     *
     * <pre>
     * StringUtils.deleteWhitespace(NULL)         = NULL
     * StringUtils.deleteWhitespace("")           = ""
     * StringUtils.deleteWhitespace("abc")        = "abc"
     * StringUtils.deleteWhitespace("   ab  c  ") = "abc"
     * </pre>
     *
     * @param str  the String to delete whitespace from, may be NULL
     * @return the String without whitespaces, <code>NULL</code> if NULL String input
     */
    /*public*/ /*static*/ QString StringUtils::deleteWhitespace(QString str) {
        if (isEmpty(str)) {
            return str;
        }
#if 0
        int sz = str.length();
        char[] chs = new char[sz];
        int count = 0;
        for (int i = 0; i < sz; i++) {
            if (!Character.isWhitespace(str.charAt(i))) {
                chs[count++] = str.charAt(i);
            }
        }
        if (count == sz) {
            return str;
        }
        return new String(chs, 0, count);
#endif
     return str.replace(" ", "");
    }
#if 0
    // Remove
    //-----------------------------------------------------------------------
    /**
     * <p>Removes a substring only if it is at the begining of a source string,
     * otherwise returns the source string.</p>
     *
     * <p>A <code>NULL</code> source string will return <code>NULL</code>.
     * An empty ("") source string will return the empty string.
     * A <code>NULL</code> search string will return the source string.</p>
     *
     * <pre>
     * StringUtils.removeStart(NULL, *)      = NULL
     * StringUtils.removeStart("", *)        = ""
     * StringUtils.removeStart(*, NULL)      = *
     * StringUtils.removeStart("www.domain.com", "www.")   = "domain.com"
     * StringUtils.removeStart("domain.com", "www.")       = "domain.com"
     * StringUtils.removeStart("www.domain.com", "domain") = "www.domain.com"
     * StringUtils.removeStart("abc", "")    = "abc"
     * </pre>
     *
     * @param str  the source String to search, may be NULL
     * @param remove  the String to search for and remove, may be NULL
     * @return the substring with the string removed if found,
     *  <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String removeStart(String str, String remove) {
        if (isEmpty(str) || isEmpty(remove)) {
            return str;
        }
        if (str.startsWith(remove)){
            return str.substring(remove.length());
        }
        return str;
    }

    /**
     * <p>Case insensitive removal of a substring if it is at the begining of a source string,
     * otherwise returns the source string.</p>
     *
     * <p>A <code>NULL</code> source string will return <code>NULL</code>.
     * An empty ("") source string will return the empty string.
     * A <code>NULL</code> search string will return the source string.</p>
     *
     * <pre>
     * StringUtils.removeStartIgnoreCase(NULL, *)      = NULL
     * StringUtils.removeStartIgnoreCase("", *)        = ""
     * StringUtils.removeStartIgnoreCase(*, NULL)      = *
     * StringUtils.removeStartIgnoreCase("www.domain.com", "www.")   = "domain.com"
     * StringUtils.removeStartIgnoreCase("www.domain.com", "WWW.")   = "domain.com"
     * StringUtils.removeStartIgnoreCase("domain.com", "www.")       = "domain.com"
     * StringUtils.removeStartIgnoreCase("www.domain.com", "domain") = "www.domain.com"
     * StringUtils.removeStartIgnoreCase("abc", "")    = "abc"
     * </pre>
     *
     * @param str  the source String to search, may be NULL
     * @param remove  the String to search for (case insensitive) and remove, may be NULL
     * @return the substring with the string removed if found,
     *  <code>NULL</code> if NULL String input
     * @since 2.4
     */
    public static String removeStartIgnoreCase(String str, String remove) {
        if (isEmpty(str) || isEmpty(remove)) {
            return str;
        }
        if (startsWithIgnoreCase(str, remove)) {
            return str.substring(remove.length());
        }
        return str;
    }
#endif
    /**
     * <p>Removes a substring only if it is at the end of a source string,
     * otherwise returns the source string.</p>
     *
     * <p>A <code>NULL</code> source string will return <code>NULL</code>.
     * An empty ("") source string will return the empty string.
     * A <code>NULL</code> search string will return the source string.</p>
     *
     * <pre>
     * StringUtils.removeEnd(NULL, *)      = NULL
     * StringUtils.removeEnd("", *)        = ""
     * StringUtils.removeEnd(*, NULL)      = *
     * StringUtils.removeEnd("www.domain.com", ".com.")  = "www.domain.com"
     * StringUtils.removeEnd("www.domain.com", ".com")   = "www.domain"
     * StringUtils.removeEnd("www.domain.com", "domain") = "www.domain.com"
     * StringUtils.removeEnd("abc", "")    = "abc"
     * </pre>
     *
     * @param str  the source String to search, may be NULL
     * @param remove  the String to search for and remove, may be NULL
     * @return the substring with the string removed if found,
     *  <code>NULL</code> if NULL String input
     * @since 2.1
     */
    /*public*/ /*static*/ QString StringUtils::removeEnd(QString str, QString remove) {
        if (isEmpty(str) || isEmpty(remove)) {
            return str;
        }
        if (str.endsWith(remove)) {
            return str.mid(0, str.length() - remove.length());
        }
        return str;
    }
#if 0
    /**
     * <p>Case insensitive removal of a substring if it is at the end of a source string,
     * otherwise returns the source string.</p>
     *
     * <p>A <code>NULL</code> source string will return <code>NULL</code>.
     * An empty ("") source string will return the empty string.
     * A <code>NULL</code> search string will return the source string.</p>
     *
     * <pre>
     * StringUtils.removeEndIgnoreCase(NULL, *)      = NULL
     * StringUtils.removeEndIgnoreCase("", *)        = ""
     * StringUtils.removeEndIgnoreCase(*, NULL)      = *
     * StringUtils.removeEndIgnoreCase("www.domain.com", ".com.")  = "www.domain.com"
     * StringUtils.removeEndIgnoreCase("www.domain.com", ".com")   = "www.domain"
     * StringUtils.removeEndIgnoreCase("www.domain.com", "domain") = "www.domain.com"
     * StringUtils.removeEndIgnoreCase("abc", "")    = "abc"
     * StringUtils.removeEndIgnoreCase("www.domain.com", ".COM") = "www.domain")
     * StringUtils.removeEndIgnoreCase("www.domain.COM", ".com") = "www.domain")
     * </pre>
     *
     * @param str  the source String to search, may be NULL
     * @param remove  the String to search for (case insensitive) and remove, may be NULL
     * @return the substring with the string removed if found,
     *  <code>NULL</code> if NULL String input
     * @since 2.4
     */
    public static String removeEndIgnoreCase(String str, String remove) {
        if (isEmpty(str) || isEmpty(remove)) {
            return str;
        }
        if (endsWithIgnoreCase(str, remove)) {
            return str.substring(0, str.length() - remove.length());
        }
        return str;
    }

    /**
     * <p>Removes all occurrences of a substring from within the source string.</p>
     *
     * <p>A <code>NULL</code> source string will return <code>NULL</code>.
     * An empty ("") source string will return the empty string.
     * A <code>NULL</code> remove string will return the source string.
     * An empty ("") remove string will return the source string.</p>
     *
     * <pre>
     * StringUtils.remove(NULL, *)        = NULL
     * StringUtils.remove("", *)          = ""
     * StringUtils.remove(*, NULL)        = *
     * StringUtils.remove(*, "")          = *
     * StringUtils.remove("queued", "ue") = "qd"
     * StringUtils.remove("queued", "zz") = "queued"
     * </pre>
     *
     * @param str  the source String to search, may be NULL
     * @param remove  the String to search for and remove, may be NULL
     * @return the substring with the string removed if found,
     *  <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String remove(String str, String remove) {
        if (isEmpty(str) || isEmpty(remove)) {
            return str;
        }
        return replace(str, remove, EMPTY, -1);
    }

    /**
     * <p>Removes all occurrences of a character from within the source string.</p>
     *
     * <p>A <code>NULL</code> source string will return <code>NULL</code>.
     * An empty ("") source string will return the empty string.</p>
     *
     * <pre>
     * StringUtils.remove(NULL, *)       = NULL
     * StringUtils.remove("", *)         = ""
     * StringUtils.remove("queued", 'u') = "qeed"
     * StringUtils.remove("queued", 'z') = "queued"
     * </pre>
     *
     * @param str  the source String to search, may be NULL
     * @param remove  the char to search for and remove, may be NULL
     * @return the substring with the char removed if found,
     *  <code>NULL</code> if NULL String input
     * @since 2.1
     */
    public static String remove(String str, char remove) {
        if (isEmpty(str) || str.indexOf(remove) == INDEX_NOT_FOUND) {
            return str;
        }
        char[] chars = str.toCharArray();
        int pos = 0;
        for (int i = 0; i < chars.length; i++) {
            if (chars[i] != remove) {
                chars[pos++] = chars[i];
            }
        }
        return new String(chars, 0, pos);
    }

    // Replacing
    //-----------------------------------------------------------------------
    /**
     * <p>Replaces a String with another String inside a larger String, once.</p>
     *
     * <p>A <code>NULL</code> reference passed to this method is a no-op.</p>
     *
     * <pre>
     * StringUtils.replaceOnce(NULL, *, *)        = NULL
     * StringUtils.replaceOnce("", *, *)          = ""
     * StringUtils.replaceOnce("any", NULL, *)    = "any"
     * StringUtils.replaceOnce("any", *, NULL)    = "any"
     * StringUtils.replaceOnce("any", "", *)      = "any"
     * StringUtils.replaceOnce("aba", "a", NULL)  = "aba"
     * StringUtils.replaceOnce("aba", "a", "")    = "ba"
     * StringUtils.replaceOnce("aba", "a", "z")   = "zba"
     * </pre>
     *
     * @see #replace(String text, String searchString, String replacement, int max)
     * @param text  text to search and replace in, may be NULL
     * @param searchString  the String to search for, may be NULL
     * @param replacement  the String to replace with, may be NULL
     * @return the text with any replacements processed,
     *  <code>NULL</code> if NULL String input
     */
    public static String replaceOnce(String text, String searchString, String replacement) {
        return replace(text, searchString, replacement, 1);
    }

    /**
     * <p>Replaces all occurrences of a String within another String.</p>
     *
     * <p>A <code>NULL</code> reference passed to this method is a no-op.</p>
     *
     * <pre>
     * StringUtils.replace(NULL, *, *)        = NULL
     * StringUtils.replace("", *, *)          = ""
     * StringUtils.replace("any", NULL, *)    = "any"
     * StringUtils.replace("any", *, NULL)    = "any"
     * StringUtils.replace("any", "", *)      = "any"
     * StringUtils.replace("aba", "a", NULL)  = "aba"
     * StringUtils.replace("aba", "a", "")    = "b"
     * StringUtils.replace("aba", "a", "z")   = "zbz"
     * </pre>
     *
     * @see #replace(String text, String searchString, String replacement, int max)
     * @param text  text to search and replace in, may be NULL
     * @param searchString  the String to search for, may be NULL
     * @param replacement  the String to replace it with, may be NULL
     * @return the text with any replacements processed,
     *  <code>NULL</code> if NULL String input
     */
    public static String replace(String text, String searchString, String replacement) {
        return replace(text, searchString, replacement, -1);
    }

    /**
     * <p>Replaces a String with another String inside a larger String,
     * for the first <code>max</code> values of the search String.</p>
     *
     * <p>A <code>NULL</code> reference passed to this method is a no-op.</p>
     *
     * <pre>
     * StringUtils.replace(NULL, *, *, *)         = NULL
     * StringUtils.replace("", *, *, *)           = ""
     * StringUtils.replace("any", NULL, *, *)     = "any"
     * StringUtils.replace("any", *, NULL, *)     = "any"
     * StringUtils.replace("any", "", *, *)       = "any"
     * StringUtils.replace("any", *, *, 0)        = "any"
     * StringUtils.replace("abaa", "a", NULL, -1) = "abaa"
     * StringUtils.replace("abaa", "a", "", -1)   = "b"
     * StringUtils.replace("abaa", "a", "z", 0)   = "abaa"
     * StringUtils.replace("abaa", "a", "z", 1)   = "zbaa"
     * StringUtils.replace("abaa", "a", "z", 2)   = "zbza"
     * StringUtils.replace("abaa", "a", "z", -1)  = "zbzz"
     * </pre>
     *
     * @param text  text to search and replace in, may be NULL
     * @param searchString  the String to search for, may be NULL
     * @param replacement  the String to replace it with, may be NULL
     * @param max  maximum number of values to replace, or <code>-1</code> if no maximum
     * @return the text with any replacements processed,
     *  <code>NULL</code> if NULL String input
     */
    public static String replace(String text, String searchString, String replacement, int max) {
        if (isEmpty(text) || isEmpty(searchString) || replacement == NULL || max == 0) {
            return text;
        }
        int start = 0;
        int end = text.indexOf(searchString, start);
        if (end == INDEX_NOT_FOUND) {
            return text;
        }
        int replLength = searchString.length();
        int increase = replacement.length() - replLength;
        increase = (increase < 0 ? 0 : increase);
        increase *= (max < 0 ? 16 : (max > 64 ? 64 : max));
        StrBuilder buf = new StrBuilder(text.length() + increase);
        while (end != INDEX_NOT_FOUND) {
            buf.append(text.substring(start, end)).append(replacement);
            start = end + replLength;
            if (--max == 0) {
                break;
            }
            end = text.indexOf(searchString, start);
        }
        buf.append(text.substring(start));
        return buf.toString();
    }

    /**
     * <p>
     * Replaces all occurrences of Strings within another String.
     * </p>
     *
     * <p>
     * A <code>NULL</code> reference passed to this method is a no-op, or if
     * any "search string" or "string to replace" is NULL, that replace will be
     * ignored. This will not repeat. For repeating replaces, call the
     * overloaded method.
     * </p>
     *
     * <pre>
     *  StringUtils.replaceEach(NULL, *, *)        = NULL
     *  StringUtils.replaceEach("", *, *)          = ""
     *  StringUtils.replaceEach("aba", NULL, NULL) = "aba"
     *  StringUtils.replaceEach("aba", new String[0], NULL) = "aba"
     *  StringUtils.replaceEach("aba", NULL, new String[0]) = "aba"
     *  StringUtils.replaceEach("aba", new String[]{"a"}, NULL)  = "aba"
     *  StringUtils.replaceEach("aba", new String[]{"a"}, new String[]{""})  = "b"
     *  StringUtils.replaceEach("aba", new String[]{NULL}, new String[]{"a"})  = "aba"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"w", "t"})  = "wcte"
     *  (example of how it does not repeat)
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "t"})  = "dcte"
     * </pre>
     *
     * @param text
     *            text to search and replace in, no-op if NULL
     * @param searchList
     *            the Strings to search for, no-op if NULL
     * @param replacementList
     *            the Strings to replace them with, no-op if NULL
     * @return the text with any replacements processed, <code>NULL</code> if
     *         NULL String input
     * @throws IndexOutOfBoundsException
     *             if the lengths of the arrays are not the same (NULL is ok,
     *             and/or size 0)
     * @since 2.4
     */
    public static String replaceEach(String text, String[] searchList, String[] replacementList) {
        return replaceEach(text, searchList, replacementList, false, 0);
    }

    /**
     * <p>
     * Replaces all occurrences of Strings within another String.
     * </p>
     *
     * <p>
     * A <code>NULL</code> reference passed to this method is a no-op, or if
     * any "search string" or "string to replace" is NULL, that replace will be
     * ignored. This will not repeat. For repeating replaces, call the
     * overloaded method.
     * </p>
     *
     * <pre>
     *  StringUtils.replaceEach(NULL, *, *, *) = NULL
     *  StringUtils.replaceEach("", *, *, *) = ""
     *  StringUtils.replaceEach("aba", NULL, NULL, *) = "aba"
     *  StringUtils.replaceEach("aba", new String[0], NULL, *) = "aba"
     *  StringUtils.replaceEach("aba", NULL, new String[0], *) = "aba"
     *  StringUtils.replaceEach("aba", new String[]{"a"}, NULL, *) = "aba"
     *  StringUtils.replaceEach("aba", new String[]{"a"}, new String[]{""}, *) = "b"
     *  StringUtils.replaceEach("aba", new String[]{NULL}, new String[]{"a"}, *) = "aba"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"w", "t"}, *) = "wcte"
     *  (example of how it repeats)
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "t"}, false) = "dcte"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "t"}, true) = "tcte"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "ab"}, true) = IllegalArgumentException
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "ab"}, false) = "dcabe"
     * </pre>
     *
     * @param text
     *            text to search and replace in, no-op if NULL
     * @param searchList
     *            the Strings to search for, no-op if NULL
     * @param replacementList
     *            the Strings to replace them with, no-op if NULL
     * @return the text with any replacements processed, <code>NULL</code> if
     *         NULL String input
     * @throws IllegalArgumentException
     *             if the search is repeating and there is an endless loop due
     *             to outputs of one being inputs to another
     * @throws IndexOutOfBoundsException
     *             if the lengths of the arrays are not the same (NULL is ok,
     *             and/or size 0)
     * @since 2.4
     */
    public static String replaceEachRepeatedly(String text, String[] searchList, String[] replacementList) {
        // timeToLive should be 0 if not used or nothing to replace, else it's
        // the length of the replace array
        int timeToLive = searchList == NULL ? 0 : searchList.length;
        return replaceEach(text, searchList, replacementList, true, timeToLive);
    }

    /**
     * <p>
     * Replaces all occurrences of Strings within another String.
     * </p>
     *
     * <p>
     * A <code>NULL</code> reference passed to this method is a no-op, or if
     * any "search string" or "string to replace" is NULL, that replace will be
     * ignored.
     * </p>
     *
     * <pre>
     *  StringUtils.replaceEach(NULL, *, *, *) = NULL
     *  StringUtils.replaceEach("", *, *, *) = ""
     *  StringUtils.replaceEach("aba", NULL, NULL, *) = "aba"
     *  StringUtils.replaceEach("aba", new String[0], NULL, *) = "aba"
     *  StringUtils.replaceEach("aba", NULL, new String[0], *) = "aba"
     *  StringUtils.replaceEach("aba", new String[]{"a"}, NULL, *) = "aba"
     *  StringUtils.replaceEach("aba", new String[]{"a"}, new String[]{""}, *) = "b"
     *  StringUtils.replaceEach("aba", new String[]{NULL}, new String[]{"a"}, *) = "aba"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"w", "t"}, *) = "wcte"
     *  (example of how it repeats)
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "t"}, false) = "dcte"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "t"}, true) = "tcte"
     *  StringUtils.replaceEach("abcde", new String[]{"ab", "d"}, new String[]{"d", "ab"}, *) = IllegalArgumentException
     * </pre>
     *
     * @param text
     *            text to search and replace in, no-op if NULL
     * @param searchList
     *            the Strings to search for, no-op if NULL
     * @param replacementList
     *            the Strings to replace them with, no-op if NULL
     * @param repeat if true, then replace repeatedly
     *       until there are no more possible replacements or timeToLive < 0
     * @param timeToLive
     *            if less than 0 then there is a circular reference and endless
     *            loop
     * @return the text with any replacements processed, <code>NULL</code> if
     *         NULL String input
     * @throws IllegalArgumentException
     *             if the search is repeating and there is an endless loop due
     *             to outputs of one being inputs to another
     * @throws IndexOutOfBoundsException
     *             if the lengths of the arrays are not the same (NULL is ok,
     *             and/or size 0)
     * @since 2.4
     */
    private static String replaceEach(String text, String[] searchList, String[] replacementList,
                                      boolean repeat, int timeToLive)
    {

        // mchyzer Performance note: This creates very few new objects (one major goal)
        // let me know if there are performance requests, we can create a harness to measure

        if (text == NULL || text.length() == 0 || searchList == NULL ||
            searchList.length == 0 || replacementList == NULL || replacementList.length == 0)
        {
            return text;
        }

        // if recursing, this shouldnt be less than 0
        if (timeToLive < 0) {
            throw new IllegalStateException("TimeToLive of " + timeToLive + " is less than 0: " + text);
        }

        int searchLength = searchList.length;
        int replacementLength = replacementList.length;

        // make sure lengths are ok, these need to be equal
        if (searchLength != replacementLength) {
            throw new IllegalArgumentException("Search and Replace array lengths don't match: "
                + searchLength
                + " vs "
                + replacementLength);
        }

        // keep track of which still have matches
        boolean[] noMoreMatchesForReplIndex = new boolean[searchLength];

        // index on index that the match was found
        int textIndex = -1;
        int replaceIndex = -1;
        int tempIndex = -1;

        // index of replace array that will replace the search string found
        // NOTE: logic duplicated below START
        for (int i = 0; i < searchLength; i++) {
            if (noMoreMatchesForReplIndex[i] || searchList[i] == NULL ||
                searchList[i].length() == 0 || replacementList[i] == NULL)
            {
                continue;
            }
            tempIndex = text.indexOf(searchList[i]);

            // see if we need to keep searching for this
            if (tempIndex == -1) {
                noMoreMatchesForReplIndex[i] = true;
            } else {
                if (textIndex == -1 || tempIndex < textIndex) {
                    textIndex = tempIndex;
                    replaceIndex = i;
                }
            }
        }
        // NOTE: logic mostly below END

        // no search strings found, we are done
        if (textIndex == -1) {
            return text;
        }

        int start = 0;

        // get a good guess on the size of the result buffer so it doesnt have to double if it goes over a bit
        int increase = 0;

        // count the replacement text elements that are larger than their corresponding text being replaced
        for (int i = 0; i < searchList.length; i++) {
            if (searchList[i] == NULL || replacementList[i] == NULL) {
                continue;
            }
            int greater = replacementList[i].length() - searchList[i].length();
            if (greater > 0) {
                increase += 3 * greater; // assume 3 matches
            }
        }
        // have upper-bound at 20% increase, then let Java take over
        increase = Math.min(increase, text.length() / 5);

        StrBuilder buf = new StrBuilder(text.length() + increase);

        while (textIndex != -1) {

            for (int i = start; i < textIndex; i++) {
                buf.append(text.charAt(i));
            }
            buf.append(replacementList[replaceIndex]);

            start = textIndex + searchList[replaceIndex].length();

            textIndex = -1;
            replaceIndex = -1;
            tempIndex = -1;
            // find the next earliest match
            // NOTE: logic mostly duplicated above START
            for (int i = 0; i < searchLength; i++) {
                if (noMoreMatchesForReplIndex[i] || searchList[i] == NULL ||
                    searchList[i].length() == 0 || replacementList[i] == NULL)
                {
                    continue;
                }
                tempIndex = text.indexOf(searchList[i], start);

                // see if we need to keep searching for this
                if (tempIndex == -1) {
                    noMoreMatchesForReplIndex[i] = true;
                } else {
                    if (textIndex == -1 || tempIndex < textIndex) {
                        textIndex = tempIndex;
                        replaceIndex = i;
                    }
                }
            }
            // NOTE: logic duplicated above END

        }
        int textLength = text.length();
        for (int i = start; i < textLength; i++) {
            buf.append(text.charAt(i));
        }
        String result = buf.toString();
        if (!repeat) {
            return result;
        }

        return replaceEach(result, searchList, replacementList, repeat, timeToLive - 1);
    }

    // Replace, character based
    //-----------------------------------------------------------------------
    /**
     * <p>Replaces all occurrences of a character in a String with another.
     * This is a NULL-safe version of {@link String#replace(char, char)}.</p>
     *
     * <p>A <code>NULL</code> string input returns <code>NULL</code>.
     * An empty ("") string input returns an empty string.</p>
     *
     * <pre>
     * StringUtils.replaceChars(NULL, *, *)        = NULL
     * StringUtils.replaceChars("", *, *)          = ""
     * StringUtils.replaceChars("abcba", 'b', 'y') = "aycya"
     * StringUtils.replaceChars("abcba", 'z', 'y') = "abcba"
     * </pre>
     *
     * @param str  String to replace characters in, may be NULL
     * @param searchChar  the character to search for, may be NULL
     * @param replaceChar  the character to replace, may be NULL
     * @return modified String, <code>NULL</code> if NULL string input
     * @since 2.0
     */
    public static String replaceChars(String str, char searchChar, char replaceChar) {
        if (str == NULL) {
            return NULL;
        }
        return str.replace(searchChar, replaceChar);
    }

    /**
     * <p>Replaces multiple characters in a String in one go.
     * This method can also be used to delete characters.</p>
     *
     * <p>For example:<br />
     * <code>replaceChars(&quot;hello&quot;, &quot;ho&quot;, &quot;jy&quot;) = jelly</code>.</p>
     *
     * <p>A <code>NULL</code> string input returns <code>NULL</code>.
     * An empty ("") string input returns an empty string.
     * A NULL or empty set of search characters returns the input string.</p>
     *
     * <p>The length of the search characters should normally equal the length
     * of the replace characters.
     * If the search characters is longer, then the extra search characters
     * are deleted.
     * If the search characters is shorter, then the extra replace characters
     * are ignored.</p>
     *
     * <pre>
     * StringUtils.replaceChars(NULL, *, *)           = NULL
     * StringUtils.replaceChars("", *, *)             = ""
     * StringUtils.replaceChars("abc", NULL, *)       = "abc"
     * StringUtils.replaceChars("abc", "", *)         = "abc"
     * StringUtils.replaceChars("abc", "b", NULL)     = "ac"
     * StringUtils.replaceChars("abc", "b", "")       = "ac"
     * StringUtils.replaceChars("abcba", "bc", "yz")  = "ayzya"
     * StringUtils.replaceChars("abcba", "bc", "y")   = "ayya"
     * StringUtils.replaceChars("abcba", "bc", "yzx") = "ayzya"
     * </pre>
     *
     * @param str  String to replace characters in, may be NULL
     * @param searchChars  a set of characters to search for, may be NULL
     * @param replaceChars  a set of characters to replace, may be NULL
     * @return modified String, <code>NULL</code> if NULL string input
     * @since 2.0
     */
    public static String replaceChars(String str, String searchChars, String replaceChars) {
        if (isEmpty(str) || isEmpty(searchChars)) {
            return str;
        }
        if (replaceChars == NULL) {
            replaceChars = EMPTY;
        }
        boolean modified = false;
        int replaceCharsLength = replaceChars.length();
        int strLength = str.length();
        StrBuilder buf = new StrBuilder(strLength);
        for (int i = 0; i < strLength; i++) {
            char ch = str.charAt(i);
            int index = searchChars.indexOf(ch);
            if (index >= 0) {
                modified = true;
                if (index < replaceCharsLength) {
                    buf.append(replaceChars.charAt(index));
                }
            } else {
                buf.append(ch);
            }
        }
        if (modified) {
            return buf.toString();
        }
        return str;
    }

    // Overlay
    //-----------------------------------------------------------------------
    /**
     * <p>Overlays part of a String with another String.</p>
     *
     * <pre>
     * StringUtils.overlayString(NULL, *, *, *)           = NullPointerException
     * StringUtils.overlayString(*, NULL, *, *)           = NullPointerException
     * StringUtils.overlayString("", "abc", 0, 0)         = "abc"
     * StringUtils.overlayString("abcdef", NULL, 2, 4)    = "abef"
     * StringUtils.overlayString("abcdef", "", 2, 4)      = "abef"
     * StringUtils.overlayString("abcdef", "zzzz", 2, 4)  = "abzzzzef"
     * StringUtils.overlayString("abcdef", "zzzz", 4, 2)  = "abcdzzzzcdef"
     * StringUtils.overlayString("abcdef", "zzzz", -1, 4) = IndexOutOfBoundsException
     * StringUtils.overlayString("abcdef", "zzzz", 2, 8)  = IndexOutOfBoundsException
     * </pre>
     *
     * @param text  the String to do overlaying in, may be NULL
     * @param overlay  the String to overlay, may be NULL
     * @param start  the position to start overlaying at, must be valid
     * @param end  the position to stop overlaying before, must be valid
     * @return overlayed String, <code>NULL</code> if NULL String input
     * @throws NullPointerException if text or overlay is NULL
     * @throws IndexOutOfBoundsException if either position is invalid
     * @deprecated Use better named {@link #overlay(String, String, int, int)} instead.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String overlayString(String text, String overlay, int start, int end) {
        return new StrBuilder(start + overlay.length() + text.length() - end + 1)
            .append(text.substring(0, start))
            .append(overlay)
            .append(text.substring(end))
            .toString();
    }

    /**
     * <p>Overlays part of a String with another String.</p>
     *
     * <p>A <code>NULL</code> string input returns <code>NULL</code>.
     * A negative index is treated as zero.
     * An index greater than the string length is treated as the string length.
     * The start index is always the smaller of the two indices.</p>
     *
     * <pre>
     * StringUtils.overlay(NULL, *, *, *)            = NULL
     * StringUtils.overlay("", "abc", 0, 0)          = "abc"
     * StringUtils.overlay("abcdef", NULL, 2, 4)     = "abef"
     * StringUtils.overlay("abcdef", "", 2, 4)       = "abef"
     * StringUtils.overlay("abcdef", "", 4, 2)       = "abef"
     * StringUtils.overlay("abcdef", "zzzz", 2, 4)   = "abzzzzef"
     * StringUtils.overlay("abcdef", "zzzz", 4, 2)   = "abzzzzef"
     * StringUtils.overlay("abcdef", "zzzz", -1, 4)  = "zzzzef"
     * StringUtils.overlay("abcdef", "zzzz", 2, 8)   = "abzzzz"
     * StringUtils.overlay("abcdef", "zzzz", -2, -3) = "zzzzabcdef"
     * StringUtils.overlay("abcdef", "zzzz", 8, 10)  = "abcdefzzzz"
     * </pre>
     *
     * @param str  the String to do overlaying in, may be NULL
     * @param overlay  the String to overlay, may be NULL
     * @param start  the position to start overlaying at
     * @param end  the position to stop overlaying before
     * @return overlayed String, <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String overlay(String str, String overlay, int start, int end) {
        if (str == NULL) {
            return NULL;
        }
        if (overlay == NULL) {
            overlay = EMPTY;
        }
        int len = str.length();
        if (start < 0) {
            start = 0;
        }
        if (start > len) {
            start = len;
        }
        if (end < 0) {
            end = 0;
        }
        if (end > len) {
            end = len;
        }
        if (start > end) {
            int temp = start;
            start = end;
            end = temp;
        }
        return new StrBuilder(len + start - end + overlay.length() + 1)
            .append(str.substring(0, start))
            .append(overlay)
            .append(str.substring(end))
            .toString();
    }

    // Chomping
    //-----------------------------------------------------------------------
    /**
     * <p>Removes one newline from end of a String if it's there,
     * otherwise leave it alone.  A newline is &quot;<code>\n</code>&quot;,
     * &quot;<code>\r</code>&quot;, or &quot;<code>\r\n</code>&quot;.</p>
     *
     * <p>NOTE: This method changed in 2.0.
     * It now more closely matches Perl chomp.</p>
     *
     * <pre>
     * StringUtils.chomp(NULL)          = NULL
     * StringUtils.chomp("")            = ""
     * StringUtils.chomp("abc \r")      = "abc "
     * StringUtils.chomp("abc\n")       = "abc"
     * StringUtils.chomp("abc\r\n")     = "abc"
     * StringUtils.chomp("abc\r\n\r\n") = "abc\r\n"
     * StringUtils.chomp("abc\n\r")     = "abc\n"
     * StringUtils.chomp("abc\n\rabc")  = "abc\n\rabc"
     * StringUtils.chomp("\r")          = ""
     * StringUtils.chomp("\n")          = ""
     * StringUtils.chomp("\r\n")        = ""
     * </pre>
     *
     * @param str  the String to chomp a newline from, may be NULL
     * @return String without newline, <code>NULL</code> if NULL String input
     */
    public static String chomp(String str) {
        if (isEmpty(str)) {
            return str;
        }

        if (str.length() == 1) {
            char ch = str.charAt(0);
            if (ch == CharUtils.CR || ch == CharUtils.LF) {
                return EMPTY;
            }
            return str;
        }

        int lastIdx = str.length() - 1;
        char last = str.charAt(lastIdx);

        if (last == CharUtils.LF) {
            if (str.charAt(lastIdx - 1) == CharUtils.CR) {
                lastIdx--;
            }
        } else if (last != CharUtils.CR) {
            lastIdx++;
        }
        return str.substring(0, lastIdx);
    }

    /**
     * <p>Removes <code>separator</code> from the end of
     * <code>str</code> if it's there, otherwise leave it alone.</p>
     *
     * <p>NOTE: This method changed in version 2.0.
     * It now more closely matches Perl chomp.
     * For the previous behavior, use {@link #substringBeforeLast(String, String)}.
     * This method uses {@link String#endsWith(String)}.</p>
     *
     * <pre>
     * StringUtils.chomp(NULL, *)         = NULL
     * StringUtils.chomp("", *)           = ""
     * StringUtils.chomp("foobar", "bar") = "foo"
     * StringUtils.chomp("foobar", "baz") = "foobar"
     * StringUtils.chomp("foo", "foo")    = ""
     * StringUtils.chomp("foo ", "foo")   = "foo "
     * StringUtils.chomp(" foo", "foo")   = " "
     * StringUtils.chomp("foo", "foooo")  = "foo"
     * StringUtils.chomp("foo", "")       = "foo"
     * StringUtils.chomp("foo", NULL)     = "foo"
     * </pre>
     *
     * @param str  the String to chomp from, may be NULL
     * @param separator  separator String, may be NULL
     * @return String without trailing separator, <code>NULL</code> if NULL String input
     */
    public static String chomp(String str, String separator) {
        if (isEmpty(str) || separator == NULL) {
            return str;
        }
        if (str.endsWith(separator)) {
            return str.substring(0, str.length() - separator.length());
        }
        return str;
    }

    /**
     * <p>Remove any &quot;\n&quot; if and only if it is at the end
     * of the supplied String.</p>
     *
     * @param str  the String to chomp from, must not be NULL
     * @return String without chomped ending
     * @throws NullPointerException if str is <code>NULL</code>
     * @deprecated Use {@link #chomp(String)} instead.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String chompLast(String str) {
        return chompLast(str, "\n");
    }

    /**
     * <p>Remove a value if and only if the String ends with that value.</p>
     *
     * @param str  the String to chomp from, must not be NULL
     * @param sep  the String to chomp, must not be NULL
     * @return String without chomped ending
     * @throws NullPointerException if str or sep is <code>NULL</code>
     * @deprecated Use {@link #chomp(String,String)} instead.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String chompLast(String str, String sep) {
        if (str.length() == 0) {
            return str;
        }
        String sub = str.substring(str.length() - sep.length());
        if (sep.equals(sub)) {
            return str.substring(0, str.length() - sep.length());
        }
        return str;
    }

    /**
     * <p>Remove everything and return the last value of a supplied String, and
     * everything after it from a String.</p>
     *
     * @param str  the String to chomp from, must not be NULL
     * @param sep  the String to chomp, must not be NULL
     * @return String chomped
     * @throws NullPointerException if str or sep is <code>NULL</code>
     * @deprecated Use {@link #substringAfterLast(String, String)} instead
     *             (although this doesn't include the separator)
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String getChomp(String str, String sep) {
        int idx = str.lastIndexOf(sep);
        if (idx == str.length() - sep.length()) {
            return sep;
        } else if (idx != -1) {
            return str.substring(idx);
        } else {
            return EMPTY;
        }
    }

    /**
     * <p>Remove the first value of a supplied String, and everything before it
     * from a String.</p>
     *
     * @param str  the String to chomp from, must not be NULL
     * @param sep  the String to chomp, must not be NULL
     * @return String without chomped beginning
     * @throws NullPointerException if str or sep is <code>NULL</code>
     * @deprecated Use {@link #substringAfter(String,String)} instead.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String prechomp(String str, String sep) {
        int idx = str.indexOf(sep);
        if (idx == -1) {
            return str;
        }
        return str.substring(idx + sep.length());
    }

    /**
     * <p>Remove and return everything before the first value of a
     * supplied String from another String.</p>
     *
     * @param str  the String to chomp from, must not be NULL
     * @param sep  the String to chomp, must not be NULL
     * @return String prechomped
     * @throws NullPointerException if str or sep is <code>NULL</code>
     * @deprecated Use {@link #substringBefore(String,String)} instead
     *             (although this doesn't include the separator).
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String getPrechomp(String str, String sep) {
        int idx = str.indexOf(sep);
        if (idx == -1) {
            return EMPTY;
        }
        return str.substring(0, idx + sep.length());
    }

    // Chopping
    //-----------------------------------------------------------------------
    /**
     * <p>Remove the last character from a String.</p>
     *
     * <p>If the String ends in <code>\r\n</code>, then remove both
     * of them.</p>
     *
     * <pre>
     * StringUtils.chop(NULL)          = NULL
     * StringUtils.chop("")            = ""
     * StringUtils.chop("abc \r")      = "abc "
     * StringUtils.chop("abc\n")       = "abc"
     * StringUtils.chop("abc\r\n")     = "abc"
     * StringUtils.chop("abc")         = "ab"
     * StringUtils.chop("abc\nabc")    = "abc\nab"
     * StringUtils.chop("a")           = ""
     * StringUtils.chop("\r")          = ""
     * StringUtils.chop("\n")          = ""
     * StringUtils.chop("\r\n")        = ""
     * </pre>
     *
     * @param str  the String to chop last character from, may be NULL
     * @return String without last character, <code>NULL</code> if NULL String input
     */
    public static String chop(String str) {
        if (str == NULL) {
            return NULL;
        }
        int strLen = str.length();
        if (strLen < 2) {
            return EMPTY;
        }
        int lastIdx = strLen - 1;
        String ret = str.substring(0, lastIdx);
        char last = str.charAt(lastIdx);
        if (last == CharUtils.LF) {
            if (ret.charAt(lastIdx - 1) == CharUtils.CR) {
                return ret.substring(0, lastIdx - 1);
            }
        }
        return ret;
    }

    /**
     * <p>Removes <code>\n</code> from end of a String if it's there.
     * If a <code>\r</code> precedes it, then remove that too.</p>
     *
     * @param str  the String to chop a newline from, must not be NULL
     * @return String without newline
     * @throws NullPointerException if str is <code>NULL</code>
     * @deprecated Use {@link #chomp(String)} instead.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String chopNewline(String str) {
        int lastIdx = str.length() - 1;
        if (lastIdx <= 0) {
            return EMPTY;
        }
        char last = str.charAt(lastIdx);
        if (last == CharUtils.LF) {
            if (str.charAt(lastIdx - 1) == CharUtils.CR) {
                lastIdx--;
            }
        } else {
            lastIdx++;
        }
        return str.substring(0, lastIdx);
    }

    // Conversion
    //-----------------------------------------------------------------------
    /**
     * <p>Escapes any values it finds into their String form.</p>
     *
     * <p>So a tab becomes the characters <code>'\\'</code> and
     * <code>'t'</code>.</p>
     *
     * <p>As of Lang 2.0, this calls {@link StringEscapeUtils#escapeJava(String)}
     * behind the scenes.
     * </p>
     * @see StringEscapeUtils#escapeJava(java.lang.String)
     * @param str String to escape values in
     * @return String with escaped values
     * @throws NullPointerException if str is <code>NULL</code>
     * @deprecated Use {@link StringEscapeUtils#escapeJava(String)}
     *             This method will be removed in Commons Lang 3.0
     */
    public static String escape(String str) {
        return StringEscapeUtils.escapeJava(str);
    }
#endif
    // Padding
    //-----------------------------------------------------------------------
    /**
     * <p>Repeat a String <code>repeat</code> times to form a
     * new String.</p>
     *
     * <pre>
     * StringUtils.repeat(NULL, 2) = NULL
     * StringUtils.repeat("", 0)   = ""
     * StringUtils.repeat("", 2)   = ""
     * StringUtils.repeat("a", 3)  = "aaa"
     * StringUtils.repeat("ab", 2) = "abab"
     * StringUtils.repeat("a", -2) = ""
     * </pre>
     *
     * @param str  the String to repeat, may be NULL
     * @param repeat  number of times to repeat str, negative treated as zero
     * @return a new String consisting of the original String repeated,
     *  <code>NULL</code> if NULL String input
     */
    /*public*/ /*static*/ QString StringUtils::repeat(QString str, int repeat) {
        // Performance tuned for 2.0 (JDK1.4)

        if (str == NULL) {
            return NULL;
        }
        if (repeat <= 0) {
            return EMPTY;
        }
        int inputLength = str.length();
        if (repeat == 1 || inputLength == 0) {
            return str;
        }
        if (inputLength == 1 && repeat <= PAD_LIMIT) {
            return padding(repeat, str.toLocal8Bit().at(0));
        }

        int outputLength = inputLength * repeat;
        switch (inputLength) {
            case 1 :
        {
                char ch = str.toLocal8Bit().at(0);
                QByteArray output1 = QByteArray(outputLength, ch);
//                for (int i = repeat - 1; i >= 0; i--) {
//                    output1[i] = ch;
//                }
                return QString(output1);
        }
            case 2 :
        {
                char ch0 = str.toLocal8Bit().at(0);
                char ch1 = str.toLocal8Bit().at(1);
                QByteArray output2 = QByteArray(outputLength, ' ');
                for (int i = repeat * 2 - 2; i >= 0; i--, i--) {
                    output2.replace(i, ch0);
                    output2.replace(i + 1, ch1);
                }
                return QString(output2);
        }
            default :
        {
                QString buf;// = new StrBuilder(outputLength);
                for (int i = 0; i < repeat; i++) {
                    buf.append(str);
                }
                return buf/*.toString()*/;
        }
        }
    }
/**
     * <p>Repeat a String <code>repeat</code> times to form a
     * new String, with a String separator injected each time. </p>
     *
     * <pre>
     * StringUtils.repeat(NULL, NULL, 2) = NULL
     * StringUtils.repeat(NULL, "x", 2)  = NULL
     * StringUtils.repeat("", NULL, 0)   = ""
     * StringUtils.repeat("", "", 2)     = ""
     * StringUtils.repeat("", "x", 3)    = "xxx"
     * StringUtils.repeat("?", ", ", 3)  = "?, ?, ?"
     * </pre>
     *
     * @param str        the String to repeat, may be NULL
     * @param separator  the String to inject, may be NULL
     * @param repeat     number of times to repeat str, negative treated as zero
     * @return a new String consisting of the original String repeated,
     *  <code>NULL</code> if NULL String input
     * @since 2.5
     */
    /*public*/ /*static*/ QString StringUtils::repeat(QString str, QString separator, int _repeat) {
        if(str == NULL || separator == NULL) {
            return repeat(str, _repeat);
        } else {
            // given that repeat(String, int) is quite optimized, better to rely on it than try and splice this into it
            QString result = repeat(str + separator, _repeat);
            return removeEnd(result, separator);
        }
    }

    /**
     * <p>Returns padding using the specified delimiter repeated
     * to a given length.</p>
     *
     * <pre>
     * StringUtils.padding(0, 'e')  = ""
     * StringUtils.padding(3, 'e')  = "eee"
     * StringUtils.padding(-2, 'e') = IndexOutOfBoundsException
     * </pre>
     *
     * <p>Note: this method doesn't not support padding with
     * <a href="http://www.unicode.org/glossary/#supplementary_character">Unicode Supplementary Characters</a>
     * as they require a pair of <code>char</code>s to be represented.
     * If you are needing to support full I18N of your applications
     * consider using {@link #repeat(String, int)} instead.
     * </p>
     *
     * @param repeat  number of times to repeat delim
     * @param padChar  character to repeat
     * @return String with repeated character
     * @throws IndexOutOfBoundsException if <code>repeat &lt; 0</code>
     * @see #repeat(String, int)
     */
    /*private*/ /*static*/ QString StringUtils::padding(int repeat, char padChar) throw (IndexOutOfBoundsException) {
        if (repeat < 0) {
            throw new IndexOutOfBoundsException("Cannot pad a negative amount: " + repeat);
        }
        /*final*/ QByteArray buf = new char[repeat];
        for (int i = 0; i < buf.length(); i++) {
            buf.replace(i, padChar);
        }
        return QString(buf);
    }
#if 0
    /**
     * <p>Right pad a String with spaces (' ').</p>
     *
     * <p>The String is padded to the size of <code>size</code>.</p>
     *
     * <pre>
     * StringUtils.rightPad(NULL, *)   = NULL
     * StringUtils.rightPad("", 3)     = "   "
     * StringUtils.rightPad("bat", 3)  = "bat"
     * StringUtils.rightPad("bat", 5)  = "bat  "
     * StringUtils.rightPad("bat", 1)  = "bat"
     * StringUtils.rightPad("bat", -1) = "bat"
     * </pre>
     *
     * @param str  the String to pad out, may be NULL
     * @param size  the size to pad to
     * @return right padded String or original String if no padding is necessary,
     *  <code>NULL</code> if NULL String input
     */
    public static String rightPad(String str, int size) {
        return rightPad(str, size, ' ');
    }

    /**
     * <p>Right pad a String with a specified character.</p>
     *
     * <p>The String is padded to the size of <code>size</code>.</p>
     *
     * <pre>
     * StringUtils.rightPad(NULL, *, *)     = NULL
     * StringUtils.rightPad("", 3, 'z')     = "zzz"
     * StringUtils.rightPad("bat", 3, 'z')  = "bat"
     * StringUtils.rightPad("bat", 5, 'z')  = "batzz"
     * StringUtils.rightPad("bat", 1, 'z')  = "bat"
     * StringUtils.rightPad("bat", -1, 'z') = "bat"
     * </pre>
     *
     * @param str  the String to pad out, may be NULL
     * @param size  the size to pad to
     * @param padChar  the character to pad with
     * @return right padded String or original String if no padding is necessary,
     *  <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String rightPad(String str, int size, char padChar) {
        if (str == NULL) {
            return NULL;
        }
        int pads = size - str.length();
        if (pads <= 0) {
            return str; // returns original String when possible
        }
        if (pads > PAD_LIMIT) {
            return rightPad(str, size, String.valueOf(padChar));
        }
        return str.concat(padding(pads, padChar));
    }

    /**
     * <p>Right pad a String with a specified String.</p>
     *
     * <p>The String is padded to the size of <code>size</code>.</p>
     *
     * <pre>
     * StringUtils.rightPad(NULL, *, *)      = NULL
     * StringUtils.rightPad("", 3, "z")      = "zzz"
     * StringUtils.rightPad("bat", 3, "yz")  = "bat"
     * StringUtils.rightPad("bat", 5, "yz")  = "batyz"
     * StringUtils.rightPad("bat", 8, "yz")  = "batyzyzy"
     * StringUtils.rightPad("bat", 1, "yz")  = "bat"
     * StringUtils.rightPad("bat", -1, "yz") = "bat"
     * StringUtils.rightPad("bat", 5, NULL)  = "bat  "
     * StringUtils.rightPad("bat", 5, "")    = "bat  "
     * </pre>
     *
     * @param str  the String to pad out, may be NULL
     * @param size  the size to pad to
     * @param padStr  the String to pad with, NULL or empty treated as single space
     * @return right padded String or original String if no padding is necessary,
     *  <code>NULL</code> if NULL String input
     */
    public static String rightPad(String str, int size, String padStr) {
        if (str == NULL) {
            return NULL;
        }
        if (isEmpty(padStr)) {
            padStr = " ";
        }
        int padLen = padStr.length();
        int strLen = str.length();
        int pads = size - strLen;
        if (pads <= 0) {
            return str; // returns original String when possible
        }
        if (padLen == 1 && pads <= PAD_LIMIT) {
            return rightPad(str, size, padStr.charAt(0));
        }

        if (pads == padLen) {
            return str.concat(padStr);
        } else if (pads < padLen) {
            return str.concat(padStr.substring(0, pads));
        } else {
            char[] padding = new char[pads];
            char[] padChars = padStr.toCharArray();
            for (int i = 0; i < pads; i++) {
                padding[i] = padChars[i % padLen];
            }
            return str.concat(new String(padding));
        }
    }

    /**
     * <p>Left pad a String with spaces (' ').</p>
     *
     * <p>The String is padded to the size of <code>size</code>.</p>
     *
     * <pre>
     * StringUtils.leftPad(NULL, *)   = NULL
     * StringUtils.leftPad("", 3)     = "   "
     * StringUtils.leftPad("bat", 3)  = "bat"
     * StringUtils.leftPad("bat", 5)  = "  bat"
     * StringUtils.leftPad("bat", 1)  = "bat"
     * StringUtils.leftPad("bat", -1) = "bat"
     * </pre>
     *
     * @param str  the String to pad out, may be NULL
     * @param size  the size to pad to
     * @return left padded String or original String if no padding is necessary,
     *  <code>NULL</code> if NULL String input
     */
    public static String leftPad(String str, int size) {
        return leftPad(str, size, ' ');
    }

    /**
     * <p>Left pad a String with a specified character.</p>
     *
     * <p>Pad to a size of <code>size</code>.</p>
     *
     * <pre>
     * StringUtils.leftPad(NULL, *, *)     = NULL
     * StringUtils.leftPad("", 3, 'z')     = "zzz"
     * StringUtils.leftPad("bat", 3, 'z')  = "bat"
     * StringUtils.leftPad("bat", 5, 'z')  = "zzbat"
     * StringUtils.leftPad("bat", 1, 'z')  = "bat"
     * StringUtils.leftPad("bat", -1, 'z') = "bat"
     * </pre>
     *
     * @param str  the String to pad out, may be NULL
     * @param size  the size to pad to
     * @param padChar  the character to pad with
     * @return left padded String or original String if no padding is necessary,
     *  <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String leftPad(String str, int size, char padChar) {
        if (str == NULL) {
            return NULL;
        }
        int pads = size - str.length();
        if (pads <= 0) {
            return str; // returns original String when possible
        }
        if (pads > PAD_LIMIT) {
            return leftPad(str, size, String.valueOf(padChar));
        }
        return padding(pads, padChar).concat(str);
    }

    /**
     * <p>Left pad a String with a specified String.</p>
     *
     * <p>Pad to a size of <code>size</code>.</p>
     *
     * <pre>
     * StringUtils.leftPad(NULL, *, *)      = NULL
     * StringUtils.leftPad("", 3, "z")      = "zzz"
     * StringUtils.leftPad("bat", 3, "yz")  = "bat"
     * StringUtils.leftPad("bat", 5, "yz")  = "yzbat"
     * StringUtils.leftPad("bat", 8, "yz")  = "yzyzybat"
     * StringUtils.leftPad("bat", 1, "yz")  = "bat"
     * StringUtils.leftPad("bat", -1, "yz") = "bat"
     * StringUtils.leftPad("bat", 5, NULL)  = "  bat"
     * StringUtils.leftPad("bat", 5, "")    = "  bat"
     * </pre>
     *
     * @param str  the String to pad out, may be NULL
     * @param size  the size to pad to
     * @param padStr  the String to pad with, NULL or empty treated as single space
     * @return left padded String or original String if no padding is necessary,
     *  <code>NULL</code> if NULL String input
     */
    public static String leftPad(String str, int size, String padStr) {
        if (str == NULL) {
            return NULL;
        }
        if (isEmpty(padStr)) {
            padStr = " ";
        }
        int padLen = padStr.length();
        int strLen = str.length();
        int pads = size - strLen;
        if (pads <= 0) {
            return str; // returns original String when possible
        }
        if (padLen == 1 && pads <= PAD_LIMIT) {
            return leftPad(str, size, padStr.charAt(0));
        }

        if (pads == padLen) {
            return padStr.concat(str);
        } else if (pads < padLen) {
            return padStr.substring(0, pads).concat(str);
        } else {
            char[] padding = new char[pads];
            char[] padChars = padStr.toCharArray();
            for (int i = 0; i < pads; i++) {
                padding[i] = padChars[i % padLen];
            }
            return new String(padding).concat(str);
        }
    }

    /**
     * Gets a String's length or <code>0</code> if the String is <code>NULL</code>.
     *
     * @param str
     *            a String or <code>NULL</code>
     * @return String length or <code>0</code> if the String is <code>NULL</code>.
     * @since 2.4
     */
    public static int length(String str) {
        return str == NULL ? 0 : str.length();
    }

    // Centering
    //-----------------------------------------------------------------------
    /**
     * <p>Centers a String in a larger String of size <code>size</code>
     * using the space character (' ').<p>
     *
     * <p>If the size is less than the String length, the String is returned.
     * A <code>NULL</code> String returns <code>NULL</code>.
     * A negative size is treated as zero.</p>
     *
     * <p>Equivalent to <code>center(str, size, " ")</code>.</p>
     *
     * <pre>
     * StringUtils.center(NULL, *)   = NULL
     * StringUtils.center("", 4)     = "    "
     * StringUtils.center("ab", -1)  = "ab"
     * StringUtils.center("ab", 4)   = " ab "
     * StringUtils.center("abcd", 2) = "abcd"
     * StringUtils.center("a", 4)    = " a  "
     * </pre>
     *
     * @param str  the String to center, may be NULL
     * @param size  the int size of new String, negative treated as zero
     * @return centered String, <code>NULL</code> if NULL String input
     */
    public static String center(String str, int size) {
        return center(str, size, ' ');
    }

    /**
     * <p>Centers a String in a larger String of size <code>size</code>.
     * Uses a supplied character as the value to pad the String with.</p>
     *
     * <p>If the size is less than the String length, the String is returned.
     * A <code>NULL</code> String returns <code>NULL</code>.
     * A negative size is treated as zero.</p>
     *
     * <pre>
     * StringUtils.center(NULL, *, *)     = NULL
     * StringUtils.center("", 4, ' ')     = "    "
     * StringUtils.center("ab", -1, ' ')  = "ab"
     * StringUtils.center("ab", 4, ' ')   = " ab"
     * StringUtils.center("abcd", 2, ' ') = "abcd"
     * StringUtils.center("a", 4, ' ')    = " a  "
     * StringUtils.center("a", 4, 'y')    = "yayy"
     * </pre>
     *
     * @param str  the String to center, may be NULL
     * @param size  the int size of new String, negative treated as zero
     * @param padChar  the character to pad the new String with
     * @return centered String, <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String center(String str, int size, char padChar) {
        if (str == NULL || size <= 0) {
            return str;
        }
        int strLen = str.length();
        int pads = size - strLen;
        if (pads <= 0) {
            return str;
        }
        str = leftPad(str, strLen + pads / 2, padChar);
        str = rightPad(str, size, padChar);
        return str;
    }

    /**
     * <p>Centers a String in a larger String of size <code>size</code>.
     * Uses a supplied String as the value to pad the String with.</p>
     *
     * <p>If the size is less than the String length, the String is returned.
     * A <code>NULL</code> String returns <code>NULL</code>.
     * A negative size is treated as zero.</p>
     *
     * <pre>
     * StringUtils.center(NULL, *, *)     = NULL
     * StringUtils.center("", 4, " ")     = "    "
     * StringUtils.center("ab", -1, " ")  = "ab"
     * StringUtils.center("ab", 4, " ")   = " ab"
     * StringUtils.center("abcd", 2, " ") = "abcd"
     * StringUtils.center("a", 4, " ")    = " a  "
     * StringUtils.center("a", 4, "yz")   = "yayz"
     * StringUtils.center("abc", 7, NULL) = "  abc  "
     * StringUtils.center("abc", 7, "")   = "  abc  "
     * </pre>
     *
     * @param str  the String to center, may be NULL
     * @param size  the int size of new String, negative treated as zero
     * @param padStr  the String to pad the new String with, must not be NULL or empty
     * @return centered String, <code>NULL</code> if NULL String input
     * @throws IllegalArgumentException if padStr is <code>NULL</code> or empty
     */
    public static String center(String str, int size, String padStr) {
        if (str == NULL || size <= 0) {
            return str;
        }
        if (isEmpty(padStr)) {
            padStr = " ";
        }
        int strLen = str.length();
        int pads = size - strLen;
        if (pads <= 0) {
            return str;
        }
        str = leftPad(str, strLen + pads / 2, padStr);
        str = rightPad(str, size, padStr);
        return str;
    }

    // Case conversion
    //-----------------------------------------------------------------------
    /**
     * <p>Converts a String to upper case as per {@link String#toUpperCase()}.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.upperCase(NULL)  = NULL
     * StringUtils.upperCase("")    = ""
     * StringUtils.upperCase("aBc") = "ABC"
     * </pre>
     *
     * <p><strong>Note:</strong> As described in the documentation for {@link String#toUpperCase()},
     * the result of this method is affected by the current locale.
     * For platform-independent case transformations, the method {@link #lowerCase(String, Locale)}
     * should be used with a specific locale (e.g. {@link Locale#ENGLISH}).</p>
     *
     * @param str  the String to upper case, may be NULL
     * @return the upper cased String, <code>NULL</code> if NULL String input
     */
    public static String upperCase(String str) {
        if (str == NULL) {
            return NULL;
        }
        return str.toUpperCase();
    }

    /**
     * <p>Converts a String to upper case as per {@link String#toUpperCase(Locale)}.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.upperCase(NULL, Locale.ENGLISH)  = NULL
     * StringUtils.upperCase("", Locale.ENGLISH)    = ""
     * StringUtils.upperCase("aBc", Locale.ENGLISH) = "ABC"
     * </pre>
     *
     * @param str  the String to upper case, may be NULL
     * @param locale  the locale that defines the case transformation rules, must not be NULL
     * @return the upper cased String, <code>NULL</code> if NULL String input
     * @since 2.5
     */
    public static String upperCase(String str, Locale locale) {
        if (str == NULL) {
            return NULL;
        }
        return str.toUpperCase(locale);
    }

    /**
     * <p>Converts a String to lower case as per {@link String#toLowerCase()}.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.lowerCase(NULL)  = NULL
     * StringUtils.lowerCase("")    = ""
     * StringUtils.lowerCase("aBc") = "abc"
     * </pre>
     *
     * <p><strong>Note:</strong> As described in the documentation for {@link String#toLowerCase()},
     * the result of this method is affected by the current locale.
     * For platform-independent case transformations, the method {@link #lowerCase(String, Locale)}
     * should be used with a specific locale (e.g. {@link Locale#ENGLISH}).</p>
     *
     * @param str  the String to lower case, may be NULL
     * @return the lower cased String, <code>NULL</code> if NULL String input
     */
    public static String lowerCase(String str) {
        if (str == NULL) {
            return NULL;
        }
        return str.toLowerCase();
    }

    /**
     * <p>Converts a String to lower case as per {@link String#toLowerCase(Locale)}.</p>
     *
     * <p>A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.lowerCase(NULL, Locale.ENGLISH)  = NULL
     * StringUtils.lowerCase("", Locale.ENGLISH)    = ""
     * StringUtils.lowerCase("aBc", Locale.ENGLISH) = "abc"
     * </pre>
     *
     * @param str  the String to lower case, may be NULL
     * @param locale  the locale that defines the case transformation rules, must not be NULL
     * @return the lower cased String, <code>NULL</code> if NULL String input
     * @since 2.5
     */
    public static String lowerCase(String str, Locale locale) {
        if (str == NULL) {
            return NULL;
        }
        return str.toLowerCase(locale);
    }

    /**
     * <p>Capitalizes a String changing the first letter to title case as
     * per {@link Character#toTitleCase(char)}. No other letters are changed.</p>
     *
     * <p>For a word based algorithm, see {@link WordUtils#capitalize(String)}.
     * A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.capitalize(NULL)  = NULL
     * StringUtils.capitalize("")    = ""
     * StringUtils.capitalize("cat") = "Cat"
     * StringUtils.capitalize("cAt") = "CAt"
     * </pre>
     *
     * @param str  the String to capitalize, may be NULL
     * @return the capitalized String, <code>NULL</code> if NULL String input
     * @see WordUtils#capitalize(String)
     * @see #uncapitalize(String)
     * @since 2.0
     */
    public static String capitalize(String str) {
        int strLen;
        if (str == NULL || (strLen = str.length()) == 0) {
            return str;
        }
        return new StrBuilder(strLen)
            .append(Character.toTitleCase(str.charAt(0)))
            .append(str.substring(1))
            .toString();
    }

    /**
     * <p>Capitalizes a String changing the first letter to title case as
     * per {@link Character#toTitleCase(char)}. No other letters are changed.</p>
     *
     * @param str  the String to capitalize, may be NULL
     * @return the capitalized String, <code>NULL</code> if NULL String input
     * @deprecated Use the standardly named {@link #capitalize(String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String capitalise(String str) {
        return capitalize(str);
    }

    /**
     * <p>Uncapitalizes a String changing the first letter to title case as
     * per {@link Character#toLowerCase(char)}. No other letters are changed.</p>
     *
     * <p>For a word based algorithm, see {@link WordUtils#uncapitalize(String)}.
     * A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.uncapitalize(NULL)  = NULL
     * StringUtils.uncapitalize("")    = ""
     * StringUtils.uncapitalize("Cat") = "cat"
     * StringUtils.uncapitalize("CAT") = "cAT"
     * </pre>
     *
     * @param str  the String to uncapitalize, may be NULL
     * @return the uncapitalized String, <code>NULL</code> if NULL String input
     * @see WordUtils#uncapitalize(String)
     * @see #capitalize(String)
     * @since 2.0
     */
    public static String uncapitalize(String str) {
        int strLen;
        if (str == NULL || (strLen = str.length()) == 0) {
            return str;
        }
        return new StrBuilder(strLen)
            .append(Character.toLowerCase(str.charAt(0)))
            .append(str.substring(1))
            .toString();
    }

    /**
     * <p>Uncapitalizes a String changing the first letter to title case as
     * per {@link Character#toLowerCase(char)}. No other letters are changed.</p>
     *
     * @param str  the String to uncapitalize, may be NULL
     * @return the uncapitalized String, <code>NULL</code> if NULL String input
     * @deprecated Use the standardly named {@link #uncapitalize(String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String uncapitalise(String str) {
        return uncapitalize(str);
    }

    /**
     * <p>Swaps the case of a String changing upper and title case to
     * lower case, and lower case to upper case.</p>
     *
     * <ul>
     *  <li>Upper case character converts to Lower case</li>
     *  <li>Title case character converts to Lower case</li>
     *  <li>Lower case character converts to Upper case</li>
     * </ul>
     *
     * <p>For a word based algorithm, see {@link WordUtils#swapCase(String)}.
     * A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.swapCase(NULL)                 = NULL
     * StringUtils.swapCase("")                   = ""
     * StringUtils.swapCase("The dog has a BONE") = "tHE DOG HAS A bone"
     * </pre>
     *
     * <p>NOTE: This method changed in Lang version 2.0.
     * It no longer performs a word based algorithm.
     * If you only use ASCII, you will notice no change.
     * That functionality is available in WordUtils.</p>
     *
     * @param str  the String to swap case, may be NULL
     * @return the changed String, <code>NULL</code> if NULL String input
     */
    public static String swapCase(String str) {
        int strLen;
        if (str == NULL || (strLen = str.length()) == 0) {
            return str;
        }
        StrBuilder buffer = new StrBuilder(strLen);

        char ch = 0;
        for (int i = 0; i < strLen; i++) {
            ch = str.charAt(i);
            if (Character.isUpperCase(ch)) {
                ch = Character.toLowerCase(ch);
            } else if (Character.isTitleCase(ch)) {
                ch = Character.toLowerCase(ch);
            } else if (Character.isLowerCase(ch)) {
                ch = Character.toUpperCase(ch);
            }
            buffer.append(ch);
        }
        return buffer.toString();
    }

    /**
     * <p>Capitalizes all the whitespace separated words in a String.
     * Only the first letter of each word is changed.</p>
     *
     * <p>Whitespace is defined by {@link Character#isWhitespace(char)}.
     * A <code>NULL</code> input String returns <code>NULL</code>.</p>
     *
     * @param str  the String to capitalize, may be NULL
     * @return capitalized String, <code>NULL</code> if NULL String input
     * @deprecated Use the relocated {@link WordUtils#capitalize(String)}.
     *             Method will be removed in Commons Lang 3.0.
     */
    public static String capitaliseAllWords(String str) {
        return WordUtils.capitalize(str);
    }

    // Count matches
    //-----------------------------------------------------------------------
    /**
     * <p>Counts how many times the substring appears in the larger String.</p>
     *
     * <p>A <code>NULL</code> or empty ("") String input returns <code>0</code>.</p>
     *
     * <pre>
     * StringUtils.countMatches(NULL, *)       = 0
     * StringUtils.countMatches("", *)         = 0
     * StringUtils.countMatches("abba", NULL)  = 0
     * StringUtils.countMatches("abba", "")    = 0
     * StringUtils.countMatches("abba", "a")   = 2
     * StringUtils.countMatches("abba", "ab")  = 1
     * StringUtils.countMatches("abba", "xxx") = 0
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param sub  the substring to count, may be NULL
     * @return the number of occurrences, 0 if either String is <code>NULL</code>
     */
    public static int countMatches(String str, String sub) {
        if (isEmpty(str) || isEmpty(sub)) {
            return 0;
        }
        int count = 0;
        int idx = 0;
        while ((idx = str.indexOf(sub, idx)) != INDEX_NOT_FOUND) {
            count++;
            idx += sub.length();
        }
        return count;
    }

    // Character Tests
    //-----------------------------------------------------------------------
    /**
     * <p>Checks if the String contains only unicode letters.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isAlpha(NULL)   = false
     * StringUtils.isAlpha("")     = true
     * StringUtils.isAlpha("  ")   = false
     * StringUtils.isAlpha("abc")  = true
     * StringUtils.isAlpha("ab2c") = false
     * StringUtils.isAlpha("ab-c") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains letters, and is non-NULL
     */
    public static boolean isAlpha(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if (Character.isLetter(str.charAt(i)) == false) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the String contains only unicode letters and
     * space (' ').</p>
     *
     * <p><code>NULL</code> will return <code>false</code>
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isAlphaSpace(NULL)   = false
     * StringUtils.isAlphaSpace("")     = true
     * StringUtils.isAlphaSpace("  ")   = true
     * StringUtils.isAlphaSpace("abc")  = true
     * StringUtils.isAlphaSpace("ab c") = true
     * StringUtils.isAlphaSpace("ab2c") = false
     * StringUtils.isAlphaSpace("ab-c") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains letters and space,
     *  and is non-NULL
     */
    public static boolean isAlphaSpace(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if ((Character.isLetter(str.charAt(i)) == false) && (str.charAt(i) != ' ')) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the String contains only unicode letters or digits.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isAlphanumeric(NULL)   = false
     * StringUtils.isAlphanumeric("")     = true
     * StringUtils.isAlphanumeric("  ")   = false
     * StringUtils.isAlphanumeric("abc")  = true
     * StringUtils.isAlphanumeric("ab c") = false
     * StringUtils.isAlphanumeric("ab2c") = true
     * StringUtils.isAlphanumeric("ab-c") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains letters or digits,
     *  and is non-NULL
     */
    public static boolean isAlphanumeric(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if (Character.isLetterOrDigit(str.charAt(i)) == false) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the String contains only unicode letters, digits
     * or space (<code>' '</code>).</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isAlphanumeric(NULL)   = false
     * StringUtils.isAlphanumeric("")     = true
     * StringUtils.isAlphanumeric("  ")   = true
     * StringUtils.isAlphanumeric("abc")  = true
     * StringUtils.isAlphanumeric("ab c") = true
     * StringUtils.isAlphanumeric("ab2c") = true
     * StringUtils.isAlphanumeric("ab-c") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains letters, digits or space,
     *  and is non-NULL
     */
    public static boolean isAlphanumericSpace(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if ((Character.isLetterOrDigit(str.charAt(i)) == false) && (str.charAt(i) != ' ')) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the string contains only ASCII printable characters.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isAsciiPrintable(NULL)     = false
     * StringUtils.isAsciiPrintable("")       = true
     * StringUtils.isAsciiPrintable(" ")      = true
     * StringUtils.isAsciiPrintable("Ceki")   = true
     * StringUtils.isAsciiPrintable("ab2c")   = true
     * StringUtils.isAsciiPrintable("!ab-c~") = true
     * StringUtils.isAsciiPrintable("\u0020") = true
     * StringUtils.isAsciiPrintable("\u0021") = true
     * StringUtils.isAsciiPrintable("\u007e") = true
     * StringUtils.isAsciiPrintable("\u007f") = false
     * StringUtils.isAsciiPrintable("Ceki G\u00fclc\u00fc") = false
     * </pre>
     *
     * @param str the string to check, may be NULL
     * @return <code>true</code> if every character is in the range
     *  32 thru 126
     * @since 2.1
     */
    public static boolean isAsciiPrintable(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if (CharUtils.isAsciiPrintable(str.charAt(i)) == false) {
                return false;
            }
        }
        return true;
    }
#endif
    /**
     * <p>Checks if the String contains only unicode digits.
     * A decimal point is not a unicode digit and returns false.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isNumeric(NULL)   = false
     * StringUtils.isNumeric("")     = true
     * StringUtils.isNumeric("  ")   = false
     * StringUtils.isNumeric("123")  = true
     * StringUtils.isNumeric("12 3") = false
     * StringUtils.isNumeric("ab2c") = false
     * StringUtils.isNumeric("12-3") = false
     * StringUtils.isNumeric("12.3") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains digits, and is non-NULL
     */
    /*public*/ /*static*/ bool StringUtils::isNumeric(QString str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            //if (Character.isDigit(str.charAt(i)) == false)
         if(!str.at(i).isDigit())
         {
             return false;
         }
        }
        return true;
    }
#if 0
    /**
     * <p>Checks if the String contains only unicode digits or space
     * (<code>' '</code>).
     * A decimal point is not a unicode digit and returns false.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isNumeric(NULL)   = false
     * StringUtils.isNumeric("")     = true
     * StringUtils.isNumeric("  ")   = true
     * StringUtils.isNumeric("123")  = true
     * StringUtils.isNumeric("12 3") = true
     * StringUtils.isNumeric("ab2c") = false
     * StringUtils.isNumeric("12-3") = false
     * StringUtils.isNumeric("12.3") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains digits or space,
     *  and is non-NULL
     */
    public static boolean isNumericSpace(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if ((Character.isDigit(str.charAt(i)) == false) && (str.charAt(i) != ' ')) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the String contains only whitespace.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>true</code>.</p>
     *
     * <pre>
     * StringUtils.isWhitespace(NULL)   = false
     * StringUtils.isWhitespace("")     = true
     * StringUtils.isWhitespace("  ")   = true
     * StringUtils.isWhitespace("abc")  = false
     * StringUtils.isWhitespace("ab2c") = false
     * StringUtils.isWhitespace("ab-c") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains whitespace, and is non-NULL
     * @since 2.0
     */
    public static boolean isWhitespace(String str) {
        if (str == NULL) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if ((Character.isWhitespace(str.charAt(i)) == false)) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the String contains only lowercase characters.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>false</code>.</p>
     *
     * <pre>
     * StringUtils.isAllLowerCase(NULL)   = false
     * StringUtils.isAllLowerCase("")     = false
     * StringUtils.isAllLowerCase("  ")   = false
     * StringUtils.isAllLowerCase("abc")  = true
     * StringUtils.isAllLowerCase("abC") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains lowercase characters, and is non-NULL
     * @since 2.5
     */
    public static boolean isAllLowerCase(String str) {
        if (str == NULL || isEmpty(str)) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if (Character.isLowerCase(str.charAt(i)) == false) {
                return false;
            }
        }
        return true;
    }

    /**
     * <p>Checks if the String contains only uppercase characters.</p>
     *
     * <p><code>NULL</code> will return <code>false</code>.
     * An empty String (length()=0) will return <code>false</code>.</p>
     *
     * <pre>
     * StringUtils.isAllUpperCase(NULL)   = false
     * StringUtils.isAllUpperCase("")     = false
     * StringUtils.isAllUpperCase("  ")   = false
     * StringUtils.isAllUpperCase("ABC")  = true
     * StringUtils.isAllUpperCase("aBC") = false
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @return <code>true</code> if only contains uppercase characters, and is non-NULL
     * @since 2.5
     */
    public static boolean isAllUpperCase(String str) {
        if (str == NULL || isEmpty(str)) {
            return false;
        }
        int sz = str.length();
        for (int i = 0; i < sz; i++) {
            if (Character.isUpperCase(str.charAt(i)) == false) {
                return false;
            }
        }
        return true;
    }

    // Defaults
    //-----------------------------------------------------------------------
    /**
     * <p>Returns either the passed in String,
     * or if the String is <code>NULL</code>, an empty String ("").</p>
     *
     * <pre>
     * StringUtils.defaultString(NULL)  = ""
     * StringUtils.defaultString("")    = ""
     * StringUtils.defaultString("bat") = "bat"
     * </pre>
     *
     * @see ObjectUtils#toString(Object)
     * @see String#valueOf(Object)
     * @param str  the String to check, may be NULL
     * @return the passed in String, or the empty String if it
     *  was <code>NULL</code>
     */
    public static String defaultString(String str) {
        return str == NULL ? EMPTY : str;
    }

    /**
     * <p>Returns either the passed in String, or if the String is
     * <code>NULL</code>, the value of <code>defaultStr</code>.</p>
     *
     * <pre>
     * StringUtils.defaultString(NULL, "NULL")  = "NULL"
     * StringUtils.defaultString("", "NULL")    = ""
     * StringUtils.defaultString("bat", "NULL") = "bat"
     * </pre>
     *
     * @see ObjectUtils#toString(Object,String)
     * @see String#valueOf(Object)
     * @param str  the String to check, may be NULL
     * @param defaultStr  the default String to return
     *  if the input is <code>NULL</code>, may be NULL
     * @return the passed in String, or the default if it was <code>NULL</code>
     */
    public static String defaultString(String str, String defaultStr) {
        return str == NULL ? defaultStr : str;
    }

    /**
     * <p>Returns either the passed in String, or if the String is
     * whitespace, empty ("") or <code>NULL</code>, the value of <code>defaultStr</code>.</p>
     *
     * <pre>
     * StringUtils.defaultIfBlank(NULL, "NULL")  = "NULL"
     * StringUtils.defaultIfBlank("", "NULL")    = "NULL"
     * StringUtils.defaultIfBlank(" ", "NULL")   = "NULL"
     * StringUtils.defaultIfBlank("bat", "NULL") = "bat"
     * StringUtils.defaultIfBlank("", NULL)      = NULL
     * </pre>
     * @param str the String to check, may be NULL
     * @param defaultStr  the default String to return
     *  if the input is whitespace, empty ("") or <code>NULL</code>, may be NULL
     * @return the passed in String, or the default
     * @see StringUtils#defaultString(String, String)
     * @since 2.6
     */
    public static String defaultIfBlank(String str, String defaultStr) {
        return StringUtils.isBlank(str) ? defaultStr : str;
    }

    /**
     * <p>Returns either the passed in String, or if the String is
     * empty or <code>NULL</code>, the value of <code>defaultStr</code>.</p>
     *
     * <pre>
     * StringUtils.defaultIfEmpty(NULL, "NULL")  = "NULL"
     * StringUtils.defaultIfEmpty("", "NULL")    = "NULL"
     * StringUtils.defaultIfEmpty("bat", "NULL") = "bat"
     * StringUtils.defaultIfEmpty("", NULL)      = NULL
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param defaultStr  the default String to return
     *  if the input is empty ("") or <code>NULL</code>, may be NULL
     * @return the passed in String, or the default
     * @see StringUtils#defaultString(String, String)
     */
    public static String defaultIfEmpty(String str, String defaultStr) {
        return StringUtils.isEmpty(str) ? defaultStr : str;
    }

    // Reversing
    //-----------------------------------------------------------------------
    /**
     * <p>Reverses a String as per {@link StrBuilder#reverse()}.</p>
     *
     * <p>A <code>NULL</code> String returns <code>NULL</code>.</p>
     *
     * <pre>
     * StringUtils.reverse(NULL)  = NULL
     * StringUtils.reverse("")    = ""
     * StringUtils.reverse("bat") = "tab"
     * </pre>
     *
     * @param str  the String to reverse, may be NULL
     * @return the reversed String, <code>NULL</code> if NULL String input
     */
    public static String reverse(String str) {
        if (str == NULL) {
            return NULL;
        }
        return new StrBuilder(str).reverse().toString();
    }

    /**
     * <p>Reverses a String that is delimited by a specific character.</p>
     *
     * <p>The Strings between the delimiters are not reversed.
     * Thus java.lang.String becomes String.lang.java (if the delimiter
     * is <code>'.'</code>).</p>
     *
     * <pre>
     * StringUtils.reverseDelimited(NULL, *)      = NULL
     * StringUtils.reverseDelimited("", *)        = ""
     * StringUtils.reverseDelimited("a.b.c", 'x') = "a.b.c"
     * StringUtils.reverseDelimited("a.b.c", ".") = "c.b.a"
     * </pre>
     *
     * @param str  the String to reverse, may be NULL
     * @param separatorChar  the separator character to use
     * @return the reversed String, <code>NULL</code> if NULL String input
     * @since 2.0
     */
    public static String reverseDelimited(String str, char separatorChar) {
        if (str == NULL) {
            return NULL;
        }
        // could implement manually, but simple way is to reuse other,
        // probably slower, methods.
        String[] strs = split(str, separatorChar);
        ArrayUtils.reverse(strs);
        return join(strs, separatorChar);
    }

    /**
     * <p>Reverses a String that is delimited by a specific character.</p>
     *
     * <p>The Strings between the delimiters are not reversed.
     * Thus java.lang.String becomes String.lang.java (if the delimiter
     * is <code>"."</code>).</p>
     *
     * <pre>
     * StringUtils.reverseDelimitedString(NULL, *)       = NULL
     * StringUtils.reverseDelimitedString("",*)          = ""
     * StringUtils.reverseDelimitedString("a.b.c", NULL) = "a.b.c"
     * StringUtils.reverseDelimitedString("a.b.c", ".")  = "c.b.a"
     * </pre>
     *
     * @param str  the String to reverse, may be NULL
     * @param separatorChars  the separator characters to use, NULL treated as whitespace
     * @return the reversed String, <code>NULL</code> if NULL String input
     * @deprecated Use {@link #reverseDelimited(String, char)} instead.
     *      This method is broken as the join doesn't know which char to use.
     *      Method will be removed in Commons Lang 3.0.
     *
     */
    public static String reverseDelimitedString(String str, String separatorChars) {
        if (str == NULL) {
            return NULL;
        }
        // could implement manually, but simple way is to reuse other,
        // probably slower, methods.
        String[] strs = split(str, separatorChars);
        ArrayUtils.reverse(strs);
        if (separatorChars == NULL) {
            return join(strs, ' ');
        }
        return join(strs, separatorChars);
    }

    // Abbreviating
    //-----------------------------------------------------------------------
    /**
     * <p>Abbreviates a String using ellipses. This will turn
     * "Now is the time for all good men" into "Now is the time for..."</p>
     *
     * <p>Specifically:
     * <ul>
     *   <li>If <code>str</code> is less than <code>maxWidth</code> characters
     *       long, return it.</li>
     *   <li>Else abbreviate it to <code>(substring(str, 0, max-3) + "...")</code>.</li>
     *   <li>If <code>maxWidth</code> is less than <code>4</code>, throw an
     *       <code>IllegalArgumentException</code>.</li>
     *   <li>In no case will it return a String of length greater than
     *       <code>maxWidth</code>.</li>
     * </ul>
     * </p>
     *
     * <pre>
     * StringUtils.abbreviate(NULL, *)      = NULL
     * StringUtils.abbreviate("", 4)        = ""
     * StringUtils.abbreviate("abcdefg", 6) = "abc..."
     * StringUtils.abbreviate("abcdefg", 7) = "abcdefg"
     * StringUtils.abbreviate("abcdefg", 8) = "abcdefg"
     * StringUtils.abbreviate("abcdefg", 4) = "a..."
     * StringUtils.abbreviate("abcdefg", 3) = IllegalArgumentException
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param maxWidth  maximum length of result String, must be at least 4
     * @return abbreviated String, <code>NULL</code> if NULL String input
     * @throws IllegalArgumentException if the width is too small
     * @since 2.0
     */
    public static String abbreviate(String str, int maxWidth) {
        return abbreviate(str, 0, maxWidth);
    }

    /**
     * <p>Abbreviates a String using ellipses. This will turn
     * "Now is the time for all good men" into "...is the time for..."</p>
     *
     * <p>Works like <code>abbreviate(String, int)</code>, but allows you to specify
     * a "left edge" offset.  Note that this left edge is not necessarily going to
     * be the leftmost character in the result, or the first character following the
     * ellipses, but it will appear somewhere in the result.
     *
     * <p>In no case will it return a String of length greater than
     * <code>maxWidth</code>.</p>
     *
     * <pre>
     * StringUtils.abbreviate(NULL, *, *)                = NULL
     * StringUtils.abbreviate("", 0, 4)                  = ""
     * StringUtils.abbreviate("abcdefghijklmno", -1, 10) = "abcdefg..."
     * StringUtils.abbreviate("abcdefghijklmno", 0, 10)  = "abcdefg..."
     * StringUtils.abbreviate("abcdefghijklmno", 1, 10)  = "abcdefg..."
     * StringUtils.abbreviate("abcdefghijklmno", 4, 10)  = "abcdefg..."
     * StringUtils.abbreviate("abcdefghijklmno", 5, 10)  = "...fghi..."
     * StringUtils.abbreviate("abcdefghijklmno", 6, 10)  = "...ghij..."
     * StringUtils.abbreviate("abcdefghijklmno", 8, 10)  = "...ijklmno"
     * StringUtils.abbreviate("abcdefghijklmno", 10, 10) = "...ijklmno"
     * StringUtils.abbreviate("abcdefghijklmno", 12, 10) = "...ijklmno"
     * StringUtils.abbreviate("abcdefghij", 0, 3)        = IllegalArgumentException
     * StringUtils.abbreviate("abcdefghij", 5, 6)        = IllegalArgumentException
     * </pre>
     *
     * @param str  the String to check, may be NULL
     * @param offset  left edge of source String
     * @param maxWidth  maximum length of result String, must be at least 4
     * @return abbreviated String, <code>NULL</code> if NULL String input
     * @throws IllegalArgumentException if the width is too small
     * @since 2.0
     */
    public static String abbreviate(String str, int offset, int maxWidth) {
        if (str == NULL) {
            return NULL;
        }
        if (maxWidth < 4) {
            throw new IllegalArgumentException("Minimum abbreviation width is 4");
        }
        if (str.length() <= maxWidth) {
            return str;
        }
        if (offset > str.length()) {
            offset = str.length();
        }
        if ((str.length() - offset) < (maxWidth - 3)) {
            offset = str.length() - (maxWidth - 3);
        }
        if (offset <= 4) {
            return str.substring(0, maxWidth - 3) + "...";
        }
        if (maxWidth < 7) {
            throw new IllegalArgumentException("Minimum abbreviation width with offset is 7");
        }
        if ((offset + (maxWidth - 3)) < str.length()) {
            return "..." + abbreviate(str.substring(offset), maxWidth - 3);
        }
        return "..." + str.substring(str.length() - (maxWidth - 3));
    }

    /**
     * <p>Abbreviates a String to the length passed, replacing the middle characters with the supplied
     * replacement String.</p>
     *
     * <p>This abbreviation only occurs if the following criteria is met:
     * <ul>
     * <li>Neither the String for abbreviation nor the replacement String are NULL or empty </li>
     * <li>The length to truncate to is less than the length of the supplied String</li>
     * <li>The length to truncate to is greater than 0</li>
     * <li>The abbreviated String will have enough room for the length supplied replacement String
     * and the first and last characters of the supplied String for abbreviation</li>
     * </ul>
     * Otherwise, the returned String will be the same as the supplied String for abbreviation.
     * </p>
     *
     * <pre>
     * StringUtils.abbreviateMiddle(NULL, NULL, 0)      = NULL
     * StringUtils.abbreviateMiddle("abc", NULL, 0)      = "abc"
     * StringUtils.abbreviateMiddle("abc", ".", 0)      = "abc"
     * StringUtils.abbreviateMiddle("abc", ".", 3)      = "abc"
     * StringUtils.abbreviateMiddle("abcdef", ".", 4)     = "ab.f"
     * </pre>
     *
     * @param str  the String to abbreviate, may be NULL
     * @param middle the String to replace the middle characters with, may be NULL
     * @param length the length to abbreviate <code>str</code> to.
     * @return the abbreviated String if the above criteria is met, or the original String supplied for abbreviation.
     * @since 2.5
     */
    public static String abbreviateMiddle(String str, String middle, int length) {
        if (isEmpty(str) || isEmpty(middle)) {
            return str;
        }

        if (length >= str.length() || length < (middle.length()+2)) {
            return str;
        }

        int targetSting = length-middle.length();
        int startOffset = targetSting/2+targetSting%2;
        int endOffset = str.length()-targetSting/2;

        StrBuilder builder = new StrBuilder(length);
        builder.append(str.substring(0,startOffset));
        builder.append(middle);
        builder.append(str.substring(endOffset));

        return builder.toString();
    }

    // Difference
    //-----------------------------------------------------------------------
    /**
     * <p>Compares two Strings, and returns the portion where they differ.
     * (More precisely, return the remainder of the second String,
     * starting from where it's different from the first.)</p>
     *
     * <p>For example,
     * <code>difference("i am a machine", "i am a robot") -> "robot"</code>.</p>
     *
     * <pre>
     * StringUtils.difference(NULL, NULL) = NULL
     * StringUtils.difference("", "") = ""
     * StringUtils.difference("", "abc") = "abc"
     * StringUtils.difference("abc", "") = ""
     * StringUtils.difference("abc", "abc") = ""
     * StringUtils.difference("ab", "abxyz") = "xyz"
     * StringUtils.difference("abcde", "abxyz") = "xyz"
     * StringUtils.difference("abcde", "xyz") = "xyz"
     * </pre>
     *
     * @param str1  the first String, may be NULL
     * @param str2  the second String, may be NULL
     * @return the portion of str2 where it differs from str1; returns the
     * empty String if they are equal
     * @since 2.0
     */
    public static String difference(String str1, String str2) {
        if (str1 == NULL) {
            return str2;
        }
        if (str2 == NULL) {
            return str1;
        }
        int at = indexOfDifference(str1, str2);
        if (at == INDEX_NOT_FOUND) {
            return EMPTY;
        }
        return str2.substring(at);
    }

    /**
     * <p>Compares two Strings, and returns the index at which the
     * Strings begin to differ.</p>
     *
     * <p>For example,
     * <code>indexOfDifference("i am a machine", "i am a robot") -> 7</code></p>
     *
     * <pre>
     * StringUtils.indexOfDifference(NULL, NULL) = -1
     * StringUtils.indexOfDifference("", "") = -1
     * StringUtils.indexOfDifference("", "abc") = 0
     * StringUtils.indexOfDifference("abc", "") = 0
     * StringUtils.indexOfDifference("abc", "abc") = -1
     * StringUtils.indexOfDifference("ab", "abxyz") = 2
     * StringUtils.indexOfDifference("abcde", "abxyz") = 2
     * StringUtils.indexOfDifference("abcde", "xyz") = 0
     * </pre>
     *
     * @param str1  the first String, may be NULL
     * @param str2  the second String, may be NULL
     * @return the index where str2 and str1 begin to differ; -1 if they are equal
     * @since 2.0
     */
    public static int indexOfDifference(String str1, String str2) {
        if (str1 == str2) {
            return INDEX_NOT_FOUND;
        }
        if (str1 == NULL || str2 == NULL) {
            return 0;
        }
        int i;
        for (i = 0; i < str1.length() && i < str2.length(); ++i) {
            if (str1.charAt(i) != str2.charAt(i)) {
                break;
            }
        }
        if (i < str2.length() || i < str1.length()) {
            return i;
        }
        return INDEX_NOT_FOUND;
    }

    /**
     * <p>Compares all Strings in an array and returns the index at which the
     * Strings begin to differ.</p>
     *
     * <p>For example,
     * <code>indexOfDifference(new String[] {"i am a machine", "i am a robot"}) -> 7</code></p>
     *
     * <pre>
     * StringUtils.indexOfDifference(NULL) = -1
     * StringUtils.indexOfDifference(new String[] {}) = -1
     * StringUtils.indexOfDifference(new String[] {"abc"}) = -1
     * StringUtils.indexOfDifference(new String[] {NULL, NULL}) = -1
     * StringUtils.indexOfDifference(new String[] {"", ""}) = -1
     * StringUtils.indexOfDifference(new String[] {"", NULL}) = 0
     * StringUtils.indexOfDifference(new String[] {"abc", NULL, NULL}) = 0
     * StringUtils.indexOfDifference(new String[] {NULL, NULL, "abc"}) = 0
     * StringUtils.indexOfDifference(new String[] {"", "abc"}) = 0
     * StringUtils.indexOfDifference(new String[] {"abc", ""}) = 0
     * StringUtils.indexOfDifference(new String[] {"abc", "abc"}) = -1
     * StringUtils.indexOfDifference(new String[] {"abc", "a"}) = 1
     * StringUtils.indexOfDifference(new String[] {"ab", "abxyz"}) = 2
     * StringUtils.indexOfDifference(new String[] {"abcde", "abxyz"}) = 2
     * StringUtils.indexOfDifference(new String[] {"abcde", "xyz"}) = 0
     * StringUtils.indexOfDifference(new String[] {"xyz", "abcde"}) = 0
     * StringUtils.indexOfDifference(new String[] {"i am a machine", "i am a robot"}) = 7
     * </pre>
     *
     * @param strs  array of strings, entries may be NULL
     * @return the index where the strings begin to differ; -1 if they are all equal
     * @since 2.4
     */
    public static int indexOfDifference(String[] strs) {
        if (strs == NULL || strs.length <= 1) {
            return INDEX_NOT_FOUND;
        }
        boolean anyStringNull = false;
        boolean allStringsNull = true;
        int arrayLen = strs.length;
        int shortestStrLen = Integer.MAX_VALUE;
        int longestStrLen = 0;

        // find the min and max string lengths; this avoids checking to make
        // sure we are not exceeding the length of the string each time through
        // the bottom loop.
        for (int i = 0; i < arrayLen; i++) {
            if (strs[i] == NULL) {
                anyStringNull = true;
                shortestStrLen = 0;
            } else {
                allStringsNull = false;
                shortestStrLen = Math.min(strs[i].length(), shortestStrLen);
                longestStrLen = Math.max(strs[i].length(), longestStrLen);
            }
        }

        // handle lists containing all NULLs or all empty strings
        if (allStringsNull || (longestStrLen == 0 && !anyStringNull)) {
            return INDEX_NOT_FOUND;
        }

        // handle lists containing some NULLs or some empty strings
        if (shortestStrLen == 0) {
            return 0;
        }

        // find the position with the first difference across all strings
        int firstDiff = -1;
        for (int stringPos = 0; stringPos < shortestStrLen; stringPos++) {
            char comparisonChar = strs[0].charAt(stringPos);
            for (int arrayPos = 1; arrayPos < arrayLen; arrayPos++) {
                if (strs[arrayPos].charAt(stringPos) != comparisonChar) {
                    firstDiff = stringPos;
                    break;
                }
            }
            if (firstDiff != -1) {
                break;
            }
        }

        if (firstDiff == -1 && shortestStrLen != longestStrLen) {
            // we compared all of the characters up to the length of the
            // shortest string and didn't find a match, but the string lengths
            // vary, so return the length of the shortest string.
            return shortestStrLen;
        }
        return firstDiff;
    }

    /**
     * <p>Compares all Strings in an array and returns the initial sequence of
     * characters that is common to all of them.</p>
     *
     * <p>For example,
     * <code>getCommonPrefix(new String[] {"i am a machine", "i am a robot"}) -> "i am a "</code></p>
     *
     * <pre>
     * StringUtils.getCommonPrefix(NULL) = ""
     * StringUtils.getCommonPrefix(new String[] {}) = ""
     * StringUtils.getCommonPrefix(new String[] {"abc"}) = "abc"
     * StringUtils.getCommonPrefix(new String[] {NULL, NULL}) = ""
     * StringUtils.getCommonPrefix(new String[] {"", ""}) = ""
     * StringUtils.getCommonPrefix(new String[] {"", NULL}) = ""
     * StringUtils.getCommonPrefix(new String[] {"abc", NULL, NULL}) = ""
     * StringUtils.getCommonPrefix(new String[] {NULL, NULL, "abc"}) = ""
     * StringUtils.getCommonPrefix(new String[] {"", "abc"}) = ""
     * StringUtils.getCommonPrefix(new String[] {"abc", ""}) = ""
     * StringUtils.getCommonPrefix(new String[] {"abc", "abc"}) = "abc"
     * StringUtils.getCommonPrefix(new String[] {"abc", "a"}) = "a"
     * StringUtils.getCommonPrefix(new String[] {"ab", "abxyz"}) = "ab"
     * StringUtils.getCommonPrefix(new String[] {"abcde", "abxyz"}) = "ab"
     * StringUtils.getCommonPrefix(new String[] {"abcde", "xyz"}) = ""
     * StringUtils.getCommonPrefix(new String[] {"xyz", "abcde"}) = ""
     * StringUtils.getCommonPrefix(new String[] {"i am a machine", "i am a robot"}) = "i am a "
     * </pre>
     *
     * @param strs  array of String objects, entries may be NULL
     * @return the initial sequence of characters that are common to all Strings
     * in the array; empty String if the array is NULL, the elements are all NULL
     * or if there is no common prefix.
     * @since 2.4
     */
    public static String getCommonPrefix(String[] strs) {
        if (strs == NULL || strs.length == 0) {
            return EMPTY;
        }
        int smallestIndexOfDiff = indexOfDifference(strs);
        if (smallestIndexOfDiff == INDEX_NOT_FOUND) {
            // all strings were identical
            if (strs[0] == NULL) {
                return EMPTY;
            }
            return strs[0];
        } else if (smallestIndexOfDiff == 0) {
            // there were no common initial characters
            return EMPTY;
        } else {
            // we found a common initial character sequence
            return strs[0].substring(0, smallestIndexOfDiff);
        }
    }

    // Misc
    //-----------------------------------------------------------------------
    /**
     * <p>Find the Levenshtein distance between two Strings.</p>
     *
     * <p>This is the number of changes needed to change one String into
     * another, where each change is a single character modification (deletion,
     * insertion or substitution).</p>
     *
     * <p>The previous implementation of the Levenshtein distance algorithm
     * was from <a href="http://www.merriampark.com/ld.htm">http://www.merriampark.com/ld.htm</a></p>
     *
     * <p>Chas Emerick has written an implementation in Java, which avoids an OutOfMemoryError
     * which can occur when my Java implementation is used with very large strings.<br>
     * This implementation of the Levenshtein distance algorithm
     * is from <a href="http://www.merriampark.com/ldjava.htm">http://www.merriampark.com/ldjava.htm</a></p>
     *
     * <pre>
     * StringUtils.getLevenshteinDistance(NULL, *)             = IllegalArgumentException
     * StringUtils.getLevenshteinDistance(*, NULL)             = IllegalArgumentException
     * StringUtils.getLevenshteinDistance("","")               = 0
     * StringUtils.getLevenshteinDistance("","a")              = 1
     * StringUtils.getLevenshteinDistance("aaapppp", "")       = 7
     * StringUtils.getLevenshteinDistance("frog", "fog")       = 1
     * StringUtils.getLevenshteinDistance("fly", "ant")        = 3
     * StringUtils.getLevenshteinDistance("elephant", "hippo") = 7
     * StringUtils.getLevenshteinDistance("hippo", "elephant") = 7
     * StringUtils.getLevenshteinDistance("hippo", "zzzzzzzz") = 8
     * StringUtils.getLevenshteinDistance("hello", "hallo")    = 1
     * </pre>
     *
     * @param s  the first String, must not be NULL
     * @param t  the second String, must not be NULL
     * @return result distance
     * @throws IllegalArgumentException if either String input <code>NULL</code>
     */
    public static int getLevenshteinDistance(String s, String t) {
        if (s == NULL || t == NULL) {
            throw new IllegalArgumentException("Strings must not be NULL");
        }

        /*
           The difference between this impl. and the previous is that, rather
           than creating and retaining a matrix of size s.length()+1 by t.length()+1,
           we maintain two single-dimensional arrays of length s.length()+1.  The first, d,
           is the 'current working' distance array that maintains the newest distance cost
           counts as we iterate through the characters of String s.  Each time we increment
           the index of String t we are comparing, d is copied to p, the second int[].  Doing so
           allows us to retain the previous cost counts as required by the algorithm (taking
           the minimum of the cost count to the left, up one, and diagonally up and to the left
           of the current cost count being calculated).  (Note that the arrays aren't really
           copied anymore, just switched...this is clearly much better than cloning an array
           or doing a System.arraycopy() each time  through the outer loop.)

           Effectively, the difference between the two implementations is this one does not
           cause an out of memory condition when calculating the LD over two very large strings.
         */

        int n = s.length(); // length of s
        int m = t.length(); // length of t

        if (n == 0) {
            return m;
        } else if (m == 0) {
            return n;
        }

        if (n > m) {
            // swap the input strings to consume less memory
            String tmp = s;
            s = t;
            t = tmp;
            n = m;
            m = t.length();
        }

        int p[] = new int[n+1]; //'previous' cost array, horizontally
        int d[] = new int[n+1]; // cost array, horizontally
        int _d[]; //placeholder to assist in swapping p and d

        // indexes into strings s and t
        int i; // iterates through s
        int j; // iterates through t

        char t_j; // jth character of t

        int cost; // cost

        for (i = 0; i<=n; i++) {
            p[i] = i;
        }

        for (j = 1; j<=m; j++) {
            t_j = t.charAt(j-1);
            d[0] = j;

            for (i=1; i<=n; i++) {
                cost = s.charAt(i-1)==t_j ? 0 : 1;
                // minimum of cell to the left+1, to the top+1, diagonally left and up +cost
                d[i] = Math.min(Math.min(d[i-1]+1, p[i]+1),  p[i-1]+cost);
            }

            // copy current distance counts to 'previous row' distance counts
            _d = p;
            p = d;
            d = _d;
        }

        // our last action in the above loop was to switch d and p, so p now
        // actually has the most recent cost counts
        return p[n];
    }

    // startsWith
    //-----------------------------------------------------------------------

    /**
     * <p>Check if a String starts with a specified prefix.</p>
     *
     * <p><code>NULL</code>s are handled without exceptions. Two <code>NULL</code>
     * references are considered to be equal. The comparison is case sensitive.</p>
     *
     * <pre>
     * StringUtils.startsWith(NULL, NULL)      = true
     * StringUtils.startsWith(NULL, "abc")     = false
     * StringUtils.startsWith("abcdef", NULL)  = false
     * StringUtils.startsWith("abcdef", "abc") = true
     * StringUtils.startsWith("ABCDEF", "abc") = false
     * </pre>
     *
     * @see java.lang.String#startsWith(String)
     * @param str  the String to check, may be NULL
     * @param prefix the prefix to find, may be NULL
     * @return <code>true</code> if the String starts with the prefix, case sensitive, or
     *  both <code>NULL</code>
     * @since 2.4
     */
    public static boolean startsWith(String str, String prefix) {
        return startsWith(str, prefix, false);
    }

    /**
     * <p>Case insensitive check if a String starts with a specified prefix.</p>
     *
     * <p><code>NULL</code>s are handled without exceptions. Two <code>NULL</code>
     * references are considered to be equal. The comparison is case insensitive.</p>
     *
     * <pre>
     * StringUtils.startsWithIgnoreCase(NULL, NULL)      = true
     * StringUtils.startsWithIgnoreCase(NULL, "abc")     = false
     * StringUtils.startsWithIgnoreCase("abcdef", NULL)  = false
     * StringUtils.startsWithIgnoreCase("abcdef", "abc") = true
     * StringUtils.startsWithIgnoreCase("ABCDEF", "abc") = true
     * </pre>
     *
     * @see java.lang.String#startsWith(String)
     * @param str  the String to check, may be NULL
     * @param prefix the prefix to find, may be NULL
     * @return <code>true</code> if the String starts with the prefix, case insensitive, or
     *  both <code>NULL</code>
     * @since 2.4
     */
    public static boolean startsWithIgnoreCase(String str, String prefix) {
        return startsWith(str, prefix, true);
    }

    /**
     * <p>Check if a String starts with a specified prefix (optionally case insensitive).</p>
     *
     * @see java.lang.String#startsWith(String)
     * @param str  the String to check, may be NULL
     * @param prefix the prefix to find, may be NULL
     * @param ignoreCase inidicates whether the compare should ignore case
     *  (case insensitive) or not.
     * @return <code>true</code> if the String starts with the prefix or
     *  both <code>NULL</code>
     */
    private static boolean startsWith(String str, String prefix, boolean ignoreCase) {
        if (str == NULL || prefix == NULL) {
            return (str == NULL && prefix == NULL);
        }
        if (prefix.length() > str.length()) {
            return false;
        }
        return str.regionMatches(ignoreCase, 0, prefix, 0, prefix.length());
    }

    /**
     * <p>Check if a String starts with any of an array of specified strings.</p>
     *
     * <pre>
     * StringUtils.startsWithAny(NULL, NULL)      = false
     * StringUtils.startsWithAny(NULL, new String[] {"abc"})  = false
     * StringUtils.startsWithAny("abcxyz", NULL)     = false
     * StringUtils.startsWithAny("abcxyz", new String[] {""}) = false
     * StringUtils.startsWithAny("abcxyz", new String[] {"abc"}) = true
     * StringUtils.startsWithAny("abcxyz", new String[] {NULL, "xyz", "abc"}) = true
     * </pre>
     *
     * @see #startsWith(String, String)
     * @param string  the String to check, may be NULL
     * @param searchStrings the Strings to find, may be NULL or empty
     * @return <code>true</code> if the String starts with any of the the prefixes, case insensitive, or
     *  both <code>NULL</code>
     * @since 2.5
     */
    public static boolean startsWithAny(String string, String[] searchStrings) {
        if (isEmpty(string) || ArrayUtils.isEmpty(searchStrings)) {
            return false;
        }
        for (int i = 0; i < searchStrings.length; i++) {
            String searchString = searchStrings[i];
            if (StringUtils.startsWith(string, searchString)) {
                return true;
            }
        }
        return false;
    }

    // endsWith
    //-----------------------------------------------------------------------

    /**
     * <p>Check if a String ends with a specified suffix.</p>
     *
     * <p><code>NULL</code>s are handled without exceptions. Two <code>NULL</code>
     * references are considered to be equal. The comparison is case sensitive.</p>
     *
     * <pre>
     * StringUtils.endsWith(NULL, NULL)      = true
     * StringUtils.endsWith(NULL, "def")     = false
     * StringUtils.endsWith("abcdef", NULL)  = false
     * StringUtils.endsWith("abcdef", "def") = true
     * StringUtils.endsWith("ABCDEF", "def") = false
     * StringUtils.endsWith("ABCDEF", "cde") = false
     * </pre>
     *
     * @see java.lang.String#endsWith(String)
     * @param str  the String to check, may be NULL
     * @param suffix the suffix to find, may be NULL
     * @return <code>true</code> if the String ends with the suffix, case sensitive, or
     *  both <code>NULL</code>
     * @since 2.4
     */
    public static boolean endsWith(String str, String suffix) {
        return endsWith(str, suffix, false);
    }

    /**
     * <p>Case insensitive check if a String ends with a specified suffix.</p>
     *
     * <p><code>NULL</code>s are handled without exceptions. Two <code>NULL</code>
     * references are considered to be equal. The comparison is case insensitive.</p>
     *
     * <pre>
     * StringUtils.endsWithIgnoreCase(NULL, NULL)      = true
     * StringUtils.endsWithIgnoreCase(NULL, "def")     = false
     * StringUtils.endsWithIgnoreCase("abcdef", NULL)  = false
     * StringUtils.endsWithIgnoreCase("abcdef", "def") = true
     * StringUtils.endsWithIgnoreCase("ABCDEF", "def") = true
     * StringUtils.endsWithIgnoreCase("ABCDEF", "cde") = false
     * </pre>
     *
     * @see java.lang.String#endsWith(String)
     * @param str  the String to check, may be NULL
     * @param suffix the suffix to find, may be NULL
     * @return <code>true</code> if the String ends with the suffix, case insensitive, or
     *  both <code>NULL</code>
     * @since 2.4
     */
    public static boolean endsWithIgnoreCase(String str, String suffix) {
        return endsWith(str, suffix, true);
    }

    /**
     * <p>Check if a String ends with a specified suffix (optionally case insensitive).</p>
     *
     * @see java.lang.String#endsWith(String)
     * @param str  the String to check, may be NULL
     * @param suffix the suffix to find, may be NULL
     * @param ignoreCase inidicates whether the compare should ignore case
     *  (case insensitive) or not.
     * @return <code>true</code> if the String starts with the prefix or
     *  both <code>NULL</code>
     */
    private static boolean endsWith(String str, String suffix, boolean ignoreCase) {
        if (str == NULL || suffix == NULL) {
            return (str == NULL && suffix == NULL);
        }
        if (suffix.length() > str.length()) {
            return false;
        }
        int strOffset = str.length() - suffix.length();
        return str.regionMatches(ignoreCase, strOffset, suffix, 0, suffix.length());
    }

    /**
     * <p>
     * Similar to <a
     * href="http://www.w3.org/TR/xpath/#function-normalize-space">http://www.w3.org/TR/xpath/#function-normalize
     * -space</a>
     * </p>
     * <p>
     * The function returns the argument string with whitespace normalized by using
     * <code>{@link #trim(String)}</code> to remove leading and trailing whitespace
     * and then replacing sequences of whitespace characters by a single space.
     * </p>
     * In XML Whitespace characters are the same as those allowed by the <a
     * href="http://www.w3.org/TR/REC-xml/#NT-S">S</a> production, which is S ::= (#x20 | #x9 | #xD | #xA)+
     * <p>
     * See Java's {@link Character#isWhitespace(char)} for which characters are considered whitespace.
     * <p>
     * The difference is that Java's whitespace includes vertical tab and form feed, which this functional will also
     * normalize. Additonally <code>{@link #trim(String)}</code> removes control characters (char &lt;= 32) from both
     * ends of this String.
     * </p>
     *
     * @see Character#isWhitespace(char)
     * @see #trim(String)
     * @see <ahref="http://www.w3.org/TR/xpath/#function-normalize-space">
     *              http://www.w3.org/TR/xpath/#function-normalize-space</a>
     * @param str the source String to normalize whitespaces from, may be NULL
     * @return the modified string with whitespace normalized, <code>NULL</code> if NULL String input
     *
     * @since 2.6
     */
    public static String normalizeSpace(String str) {
        str = strip(str);
        if(str == NULL || str.length() <= 2) {
            return str;
        }
        StrBuilder b = new StrBuilder(str.length());
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (Character.isWhitespace(c)) {
                if (i > 0 && !Character.isWhitespace(str.charAt(i - 1))) {
                    b.append(' ');
                }
            } else {
                b.append(c);
            }
        }
        return b.toString();
    }

    /**
     * <p>Check if a String ends with any of an array of specified strings.</p>
     *
     * <pre>
     * StringUtils.endsWithAny(NULL, NULL)      = false
     * StringUtils.endsWithAny(NULL, new String[] {"abc"})  = false
     * StringUtils.endsWithAny("abcxyz", NULL)     = false
     * StringUtils.endsWithAny("abcxyz", new String[] {""}) = true
     * StringUtils.endsWithAny("abcxyz", new String[] {"xyz"}) = true
     * StringUtils.endsWithAny("abcxyz", new String[] {NULL, "xyz", "abc"}) = true
     * </pre>
     *
     * @param string  the String to check, may be NULL
     * @param searchStrings the Strings to find, may be NULL or empty
     * @return <code>true</code> if the String ends with any of the the prefixes, case insensitive, or
     *  both <code>NULL</code>
     * @since 2.6
     */
    public static boolean endsWithAny(String string, String[] searchStrings) {
        if (isEmpty(string) || ArrayUtils.isEmpty(searchStrings)) {
            return false;
        }
        for (int i = 0; i < searchStrings.length; i++) {
            String searchString = searchStrings[i];
            if (StringUtils.endsWith(string, searchString)) {
                return true;
            }
        }
        return false;
    }

}
#endif
