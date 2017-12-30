#ifndef PATTERN_H
#define PATTERN_H
#include "matcher.h"
#include "charsequence.h"
#include <QMap>
#include <QList>
#include "patternsyntaxexception.h"
#include <QVariant>

#include <QObject>
class TreeInfo;
/**
     * The following classes are the building components of the object
     * tree that represents a compiled regular expression. The object tree
     * is made of individual elements that handle constructs in the Pattern.
     * Each type of object knows how to match its equivalent construct with
     * the match() method.
     */

    /**
     * Base class for all node classes. Subclasses should override the match()
     * method as appropriate. This class is an accepting node, so its match()
     * always returns true.
     */
    /*static*/ class Node : public  QVariant {
        Node* next;
public:
        Node();
        bool match(Matcher* matcher, int i, CharSequence* seq);
        bool study(TreeInfo* info) ;
    };

    /*static*/ class LastNode : public Node {
public:
        /**
         * This method implements the classic accept node with
         * the addition of a check to see if the match occurred
         * using all of the input.
         */
        bool match(Matcher* matcher, int i, CharSequence* seq);
    };

    /**
     * Used for REs that can start anywhere within the input string.
     * This basically tries to match repeatedly at each spot in the
     * input string, moving forward after each try. An anchored search
     * or a BnM will bypass this node completely.
     */
    /*static*/ class Start : public Node {
        int minLength;
    public:
        Start(Node* node) ;
        bool match(Matcher* matcher, int i, CharSequence* seq);
        bool study(TreeInfo* info);
    };
#if 0
    /*
     * StartS supports supplementary characters, including unpaired surrogates.
     */
    static final class StartS extends Start {
        StartS(Node node) {
            super(node);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            if (i > matcher.to - minLength) {
                matcher.hitEnd = true;
                return false;
            }
            int guard = matcher.to - minLength;
            while (i <= guard) {
                //if ((ret = next.match(matcher, i, seq)) || i == guard)
                if (next.match(matcher, i, seq)) {
                    matcher.first = i;
                    matcher.groups[0] = matcher.first;
                    matcher.groups[1] = matcher.last;
                    return true;
                }
                if (i == guard)
                    break;
                // Optimization to move to the next character. This is
                // faster than countChars(seq, i, 1).
                if (Character.isHighSurrogate(seq.charAt(i++))) {
                    if (i < seq.length() &&
                        Character.isLowSurrogate(seq.charAt(i))) {
                        i++;
                    }
                }
            }
            matcher.hitEnd = true;
            return false;
        }
    }

    /**
     * Node to anchor at the beginning of input. This object implements the
     * match for a \A sequence, and the caret anchor will use this if not in
     * multiline mode.
     */
    static final class Begin extends Node {
        bool match(Matcher matcher, int i, CharSequence seq) {
            int fromIndex = (matcher.anchoringBounds) ?
                matcher.from : 0;
            if (i == fromIndex && next.match(matcher, i, seq)) {
                matcher.first = i;
                matcher.groups[0] = i;
                matcher.groups[1] = matcher.last;
                return true;
            } else {
                return false;
            }
        }
    }

    /**
     * Node to anchor at the end of input. This is the absolute end, so this
     * should not match at the last newline before the end as $ will.
     */
    static final class End extends Node {
        bool match(Matcher matcher, int i, CharSequence seq) {
            int endIndex = (matcher.anchoringBounds) ?
                matcher.to : matcher.getTextLength();
            if (i == endIndex) {
                matcher.hitEnd = true;
                return next.match(matcher, i, seq);
            }
            return false;
        }
    }

    /**
     * Node to anchor at the beginning of a line. This is essentially the
     * object to match for the multiline ^.
     */
    static final class Caret extends Node {
        bool match(Matcher matcher, int i, CharSequence seq) {
            int startIndex = matcher.from;
            int endIndex = matcher.to;
            if (!matcher.anchoringBounds) {
                startIndex = 0;
                endIndex = matcher.getTextLength();
            }
            // Perl does not match ^ at end of input even after newline
            if (i == endIndex) {
                matcher.hitEnd = true;
                return false;
            }
            if (i > startIndex) {
                char ch = seq.charAt(i-1);
                if (ch != '\n' && ch != '\r'
                    && (ch|1) != '\u2029'
                    && ch != '\u0085' ) {
                    return false;
                }
                // Should treat /r/n as one newline
                if (ch == '\r' && seq.charAt(i) == '\n')
                    return false;
            }
            return next.match(matcher, i, seq);
        }
    }

    /**
     * Node to anchor at the beginning of a line when in unixdot mode.
     */
    static final class UnixCaret extends Node {
        bool match(Matcher matcher, int i, CharSequence seq) {
            int startIndex = matcher.from;
            int endIndex = matcher.to;
            if (!matcher.anchoringBounds) {
                startIndex = 0;
                endIndex = matcher.getTextLength();
            }
            // Perl does not match ^ at end of input even after newline
            if (i == endIndex) {
                matcher.hitEnd = true;
                return false;
            }
            if (i > startIndex) {
                char ch = seq.charAt(i-1);
                if (ch != '\n') {
                    return false;
                }
            }
            return next.match(matcher, i, seq);
        }
    }

    /**
     * Node to match the location where the last match ended.
     * This is used for the \G construct.
     */
    static final class LastMatch extends Node {
        bool match(Matcher matcher, int i, CharSequence seq) {
            if (i != matcher.oldLast)
                return false;
            return next.match(matcher, i, seq);
        }
    }

    /**
     * Node to anchor at the end of a line or the end of input based on the
     * multiline mode.
     *
     * When not in multiline mode, the $ can only match at the very end
     * of the input, unless the input ends in a line terminator in which
     * it matches right before the last line terminator.
     *
     * Note that \r\n is considered an atomic line terminator.
     *
     * Like ^ the $ operator matches at a position, it does not match the
     * line terminators themselves.
     */
    static final class Dollar extends Node {
        bool multiline;
        Dollar(bool mul) {
            multiline = mul;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int endIndex = (matcher.anchoringBounds) ?
                matcher.to : matcher.getTextLength();
            if (!multiline) {
                if (i < endIndex - 2)
                    return false;
                if (i == endIndex - 2) {
                    char ch = seq.charAt(i);
                    if (ch != '\r')
                        return false;
                    ch = seq.charAt(i + 1);
                    if (ch != '\n')
                        return false;
                }
            }
            // Matches before any line terminator; also matches at the
            // end of input
            // Before line terminator:
            // If multiline, we match here no matter what
            // If not multiline, fall through so that the end
            // is marked as hit; this must be a /r/n or a /n
            // at the very end so the end was hit; more input
            // could make this not match here
            if (i < endIndex) {
                char ch = seq.charAt(i);
                 if (ch == '\n') {
                     // No match between \r\n
                     if (i > 0 && seq.charAt(i-1) == '\r')
                         return false;
                     if (multiline)
                         return next.match(matcher, i, seq);
                 } else if (ch == '\r' || ch == '\u0085' ||
                            (ch|1) == '\u2029') {
                     if (multiline)
                         return next.match(matcher, i, seq);
                 } else { // No line terminator, no match
                     return false;
                 }
            }
            // Matched at current end so hit end
            matcher.hitEnd = true;
            // If a $ matches because of end of input, then more input
            // could cause it to fail!
            matcher.requireEnd = true;
            return next.match(matcher, i, seq);
        }
        bool study(TreeInfo info) {
            next.study(info);
            return info.deterministic;
        }
    }

    /**
     * Node to anchor at the end of a line or the end of input based on the
     * multiline mode when in unix lines mode.
     */
    static final class UnixDollar extends Node {
        bool multiline;
        UnixDollar(bool mul) {
            multiline = mul;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int endIndex = (matcher.anchoringBounds) ?
                matcher.to : matcher.getTextLength();
            if (i < endIndex) {
                char ch = seq.charAt(i);
                if (ch == '\n') {
                    // If not multiline, then only possible to
                    // match at very end or one before end
                    if (multiline == false && i != endIndex - 1)
                        return false;
                    // If multiline return next.match without setting
                    // matcher.hitEnd
                    if (multiline)
                        return next.match(matcher, i, seq);
                } else {
                    return false;
                }
            }
            // Matching because at the end or 1 before the end;
            // more input could change this so set hitEnd
            matcher.hitEnd = true;
            // If a $ matches because of end of input, then more input
            // could cause it to fail!
            matcher.requireEnd = true;
            return next.match(matcher, i, seq);
        }
        bool study(TreeInfo info) {
            next.study(info);
            return info.deterministic;
        }
    }

    /**
     * Node class that matches a Unicode line ending '\R'
     */
    static final class LineEnding extends Node {
        bool match(Matcher matcher, int i, CharSequence seq) {
            // (u+000Du+000A|[u+000Au+000Bu+000Cu+000Du+0085u+2028u+2029])
            if (i < matcher.to) {
                int ch = seq.charAt(i);
                if (ch == 0x0A || ch == 0x0B || ch == 0x0C ||
                    ch == 0x85 || ch == 0x2028 || ch == 0x2029)
                    return next.match(matcher, i + 1, seq);
                if (ch == 0x0D) {
                    i++;
                    if (i < matcher.to && seq.charAt(i) == 0x0A)
                        i++;
                    return next.match(matcher, i, seq);
                }
            } else {
                matcher.hitEnd = true;
            }
            return false;
        }
        bool study(TreeInfo info) {
            info.minLength++;
            info.maxLength += 2;
            return next.study(info);
        }
    }

    /**
     * Abstract node class to match one character satisfying some
     * bool property.
     */
    private static abstract class CharProperty extends Node {
        abstract bool isSatisfiedBy(int ch);
        CharProperty complement() {
            return new CharProperty() {
                    bool isSatisfiedBy(int ch) {
                        return ! CharProperty.this.isSatisfiedBy(ch);}};
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            if (i < matcher.to) {
                int ch = Character.codePointAt(seq, i);
                return isSatisfiedBy(ch)
                    && next.match(matcher, i+Character.charCount(ch), seq);
            } else {
                matcher.hitEnd = true;
                return false;
            }
        }
        bool study(TreeInfo info) {
            info.minLength++;
            info.maxLength++;
            return next.study(info);
        }
    }

    /**
     * Optimized version of CharProperty that works only for
     * properties never satisfied by Supplementary characters.
     */
    private static abstract class BmpCharProperty extends CharProperty {
        bool match(Matcher matcher, int i, CharSequence seq) {
            if (i < matcher.to) {
                return isSatisfiedBy(seq.charAt(i))
                    && next.match(matcher, i+1, seq);
            } else {
                matcher.hitEnd = true;
                return false;
            }
        }
    }

    /**
     * Node class that matches a Supplementary Unicode character
     */
    static final class SingleS extends CharProperty {
        final int c;
        SingleS(int c) { this.c = c; }
        bool isSatisfiedBy(int ch) {
            return ch == c;
        }
    }

    /**
     * Optimization -- matches a given BMP character
     */
    static final class Single extends BmpCharProperty {
        final int c;
        Single(int c) { this.c = c; }
        bool isSatisfiedBy(int ch) {
            return ch == c;
        }
    }

    /**
     * Case insensitive matches a given BMP character
     */
    static final class SingleI extends BmpCharProperty {
        final int lower;
        final int upper;
        SingleI(int lower, int upper) {
            this.lower = lower;
            this.upper = upper;
        }
        bool isSatisfiedBy(int ch) {
            return ch == lower || ch == upper;
        }
    }

    /**
     * Unicode case insensitive matches a given Unicode character
     */
    static final class SingleU extends CharProperty {
        final int lower;
        SingleU(int lower) {
            this.lower = lower;
        }
        bool isSatisfiedBy(int ch) {
            return lower == ch ||
                lower == Character.toLowerCase(Character.toUpperCase(ch));
        }
    }

    /**
     * Node class that matches a Unicode block.
     */
    static final class Block extends CharProperty {
        final Character.UnicodeBlock block;
        Block(Character.UnicodeBlock block) {
            this.block = block;
        }
        bool isSatisfiedBy(int ch) {
            return block == Character.UnicodeBlock.of(ch);
        }
    }

    /**
     * Node class that matches a Unicode script
     */
    static final class Script extends CharProperty {
        final Character.UnicodeScript script;
        Script(Character.UnicodeScript script) {
            this.script = script;
        }
        bool isSatisfiedBy(int ch) {
            return script == Character.UnicodeScript.of(ch);
        }
    }

    /**
     * Node class that matches a Unicode category.
     */
    static final class Category extends CharProperty {
        final int typeMask;
        Category(int typeMask) { this.typeMask = typeMask; }
        bool isSatisfiedBy(int ch) {
            return (typeMask & (1 << Character.getType(ch))) != 0;
        }
    }

    /**
     * Node class that matches a Unicode "type"
     */
    static final class Utype extends CharProperty {
        final UnicodeProp uprop;
        Utype(UnicodeProp uprop) { this.uprop = uprop; }
        bool isSatisfiedBy(int ch) {
            return uprop.is(ch);
        }
    }

    /**
     * Node class that matches a POSIX type.
     */
    static final class Ctype extends BmpCharProperty {
        final int ctype;
        Ctype(int ctype) { this.ctype = ctype; }
        bool isSatisfiedBy(int ch) {
            return ch < 128 && ASCII.isType(ch, ctype);
        }
    }

    /**
     * Node class that matches a Perl vertical whitespace
     */
    static final class VertWS extends BmpCharProperty {
        bool isSatisfiedBy(int cp) {
            return (cp >= 0x0A && cp <= 0x0D) ||
                   cp == 0x85 || cp == 0x2028 || cp == 0x2029;
        }
    }

    /**
     * Node class that matches a Perl horizontal whitespace
     */
    static final class HorizWS extends BmpCharProperty {
        bool isSatisfiedBy(int cp) {
            return cp == 0x09 || cp == 0x20 || cp == 0xa0 ||
                   cp == 0x1680 || cp == 0x180e ||
                   cp >= 0x2000 && cp <= 0x200a ||
                   cp == 0x202f || cp == 0x205f || cp == 0x3000;
        }
    }

    /**
     * Base class for all Slice nodes
     */
    static class SliceNode extends Node {
        int[] buffer;
        SliceNode(int[] buf) {
            buffer = buf;
        }
        bool study(TreeInfo info) {
            info.minLength += buffer.length;
            info.maxLength += buffer.length;
            return next.study(info);
        }
    }

    /**
     * Node class for a case sensitive/BMP-only sequence of literal
     * characters.
     */
    static final class Slice extends SliceNode {
        Slice(int[] buf) {
            super(buf);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int[] buf = buffer;
            int len = buf.length;
            for (int j=0; j<len; j++) {
                if ((i+j) >= matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
                if (buf[j] != seq.charAt(i+j))
                    return false;
            }
            return next.match(matcher, i+len, seq);
        }
    }

    /**
     * Node class for a case_insensitive/BMP-only sequence of literal
     * characters.
     */
    static class SliceI extends SliceNode {
        SliceI(int[] buf) {
            super(buf);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int[] buf = buffer;
            int len = buf.length;
            for (int j=0; j<len; j++) {
                if ((i+j) >= matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
                int c = seq.charAt(i+j);
                if (buf[j] != c &&
                    buf[j] != ASCII.toLower(c))
                    return false;
            }
            return next.match(matcher, i+len, seq);
        }
    }

    /**
     * Node class for a unicode_case_insensitive/BMP-only sequence of
     * literal characters. Uses unicode case folding.
     */
    static final class SliceU extends SliceNode {
        SliceU(int[] buf) {
            super(buf);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int[] buf = buffer;
            int len = buf.length;
            for (int j=0; j<len; j++) {
                if ((i+j) >= matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
                int c = seq.charAt(i+j);
                if (buf[j] != c &&
                    buf[j] != Character.toLowerCase(Character.toUpperCase(c)))
                    return false;
            }
            return next.match(matcher, i+len, seq);
        }
    }

    /**
     * Node class for a case sensitive sequence of literal characters
     * including supplementary characters.
     */
    static final class SliceS extends SliceNode {
        SliceS(int[] buf) {
            super(buf);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int[] buf = buffer;
            int x = i;
            for (int j = 0; j < buf.length; j++) {
                if (x >= matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
                int c = Character.codePointAt(seq, x);
                if (buf[j] != c)
                    return false;
                x += Character.charCount(c);
                if (x > matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
            }
            return next.match(matcher, x, seq);
        }
    }

    /**
     * Node class for a case insensitive sequence of literal characters
     * including supplementary characters.
     */
    static class SliceIS extends SliceNode {
        SliceIS(int[] buf) {
            super(buf);
        }
        int toLower(int c) {
            return ASCII.toLower(c);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int[] buf = buffer;
            int x = i;
            for (int j = 0; j < buf.length; j++) {
                if (x >= matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
                int c = Character.codePointAt(seq, x);
                if (buf[j] != c && buf[j] != toLower(c))
                    return false;
                x += Character.charCount(c);
                if (x > matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
            }
            return next.match(matcher, x, seq);
        }
    }

    /**
     * Node class for a case insensitive sequence of literal characters.
     * Uses unicode case folding.
     */
    static final class SliceUS extends SliceIS {
        SliceUS(int[] buf) {
            super(buf);
        }
        int toLower(int c) {
            return Character.toLowerCase(Character.toUpperCase(c));
        }
    }

    private static bool inRange(int lower, int ch, int upper) {
        return lower <= ch && ch <= upper;
    }

    /**
     * Returns node for matching characters within an explicit value range.
     */
    private static CharProperty rangeFor(final int lower,
                                         final int upper) {
        return new CharProperty() {
                bool isSatisfiedBy(int ch) {
                    return inRange(lower, ch, upper);}};
    }

    /**
     * Returns node for matching characters within an explicit value
     * range in a case insensitive manner.
     */
    private CharProperty caseInsensitiveRangeFor(final int lower,
                                                 final int upper) {
        if (has(UNICODE_CASE))
            return new CharProperty() {
                bool isSatisfiedBy(int ch) {
                    if (inRange(lower, ch, upper))
                        return true;
                    int up = Character.toUpperCase(ch);
                    return inRange(lower, up, upper) ||
                           inRange(lower, Character.toLowerCase(up), upper);}};
        return new CharProperty() {
            bool isSatisfiedBy(int ch) {
                return inRange(lower, ch, upper) ||
                    ASCII.isAscii(ch) &&
                        (inRange(lower, ASCII.toUpper(ch), upper) ||
                         inRange(lower, ASCII.toLower(ch), upper));
            }};
    }

    /**
     * Implements the Unicode category ALL and the dot metacharacter when
     * in dotall mode.
     */
    static final class All extends CharProperty {
        bool isSatisfiedBy(int ch) {
            return true;
        }
    }

    /**
     * Node class for the dot metacharacter when dotall is not enabled.
     */
    static final class Dot extends CharProperty {
        bool isSatisfiedBy(int ch) {
            return (ch != '\n' && ch != '\r'
                    && (ch|1) != '\u2029'
                    && ch != '\u0085');
        }
    }

    /**
     * Node class for the dot metacharacter when dotall is not enabled
     * but UNIX_LINES is enabled.
     */
    static final class UnixDot extends CharProperty {
        bool isSatisfiedBy(int ch) {
            return ch != '\n';
        }
    }

    /**
     * The 0 or 1 quantifier. This one class implements all three types.
     */
    static final class Ques extends Node {
        Node atom;
        int type;
        Ques(Node node, int type) {
            this.atom = node;
            this.type = type;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            switch (type) {
            case GREEDY:
                return (atom.match(matcher, i, seq) && next.match(matcher, matcher.last, seq))
                    || next.match(matcher, i, seq);
            case LAZY:
                return next.match(matcher, i, seq)
                    || (atom.match(matcher, i, seq) && next.match(matcher, matcher.last, seq));
            case POSSESSIVE:
                if (atom.match(matcher, i, seq)) i = matcher.last;
                return next.match(matcher, i, seq);
            default:
                return atom.match(matcher, i, seq) && next.match(matcher, matcher.last, seq);
            }
        }
        bool study(TreeInfo info) {
            if (type != INDEPENDENT) {
                int minL = info.minLength;
                atom.study(info);
                info.minLength = minL;
                info.deterministic = false;
                return next.study(info);
            } else {
                atom.study(info);
                return next.study(info);
            }
        }
    }

    /**
     * Handles the curly-brace style repetition with a specified minimum and
     * maximum occurrences. The * quantifier is handled as a special case.
     * This class handles the three types.
     */
    static final class Curly extends Node {
        Node atom;
        int type;
        int cmin;
        int cmax;

        Curly(Node node, int cmin, int cmax, int type) {
            this.atom = node;
            this.type = type;
            this.cmin = cmin;
            this.cmax = cmax;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int j;
            for (j = 0; j < cmin; j++) {
                if (atom.match(matcher, i, seq)) {
                    i = matcher.last;
                    continue;
                }
                return false;
            }
            if (type == GREEDY)
                return match0(matcher, i, j, seq);
            else if (type == LAZY)
                return match1(matcher, i, j, seq);
            else
                return match2(matcher, i, j, seq);
        }
        // Greedy match.
        // i is the index to start matching at
        // j is the number of atoms that have matched
        bool match0(Matcher matcher, int i, int j, CharSequence seq) {
            if (j >= cmax) {
                // We have matched the maximum... continue with the rest of
                // the regular expression
                return next.match(matcher, i, seq);
            }
            int backLimit = j;
            while (atom.match(matcher, i, seq)) {
                // k is the length of this match
                int k = matcher.last - i;
                if (k == 0) // Zero length match
                    break;
                // Move up index and number matched
                i = matcher.last;
                j++;
                // We are greedy so match as many as we can
                while (j < cmax) {
                    if (!atom.match(matcher, i, seq))
                        break;
                    if (i + k != matcher.last) {
                        if (match0(matcher, matcher.last, j+1, seq))
                            return true;
                        break;
                    }
                    i += k;
                    j++;
                }
                // Handle backing off if match fails
                while (j >= backLimit) {
                   if (next.match(matcher, i, seq))
                        return true;
                    i -= k;
                    j--;
                }
                return false;
            }
            return next.match(matcher, i, seq);
        }
        // Reluctant match. At this point, the minimum has been satisfied.
        // i is the index to start matching at
        // j is the number of atoms that have matched
        bool match1(Matcher matcher, int i, int j, CharSequence seq) {
            for (;;) {
                // Try finishing match without consuming any more
                if (next.match(matcher, i, seq))
                    return true;
                // At the maximum, no match found
                if (j >= cmax)
                    return false;
                // Okay, must try one more atom
                if (!atom.match(matcher, i, seq))
                    return false;
                // If we haven't moved forward then must break out
                if (i == matcher.last)
                    return false;
                // Move up index and number matched
                i = matcher.last;
                j++;
            }
        }
        bool match2(Matcher matcher, int i, int j, CharSequence seq) {
            for (; j < cmax; j++) {
                if (!atom.match(matcher, i, seq))
                    break;
                if (i == matcher.last)
                    break;
                i = matcher.last;
            }
            return next.match(matcher, i, seq);
        }
        bool study(TreeInfo info) {
            // Save original info
            int minL = info.minLength;
            int maxL = info.maxLength;
            bool maxV = info.maxValid;
            bool detm = info.deterministic;
            info.reset();

            atom.study(info);

            int temp = info.minLength * cmin + minL;
            if (temp < minL) {
                temp = 0xFFFFFFF; // arbitrary large number
            }
            info.minLength = temp;

            if (maxV & info.maxValid) {
                temp = info.maxLength * cmax + maxL;
                info.maxLength = temp;
                if (temp < maxL) {
                    info.maxValid = false;
                }
            } else {
                info.maxValid = false;
            }

            if (info.deterministic && cmin == cmax)
                info.deterministic = detm;
            else
                info.deterministic = false;
            return next.study(info);
        }
    }

    /**
     * Handles the curly-brace style repetition with a specified minimum and
     * maximum occurrences in deterministic cases. This is an iterative
     * optimization over the Prolog and Loop system which would handle this
     * in a recursive way. The * quantifier is handled as a special case.
     * If capture is true then this class saves group settings and ensures
     * that groups are unset when backing off of a group match.
     */
    static final class GroupCurly extends Node {
        Node atom;
        int type;
        int cmin;
        int cmax;
        int localIndex;
        int groupIndex;
        bool capture;

        GroupCurly(Node node, int cmin, int cmax, int type, int local,
                   int group, bool capture) {
            this.atom = node;
            this.type = type;
            this.cmin = cmin;
            this.cmax = cmax;
            this.localIndex = local;
            this.groupIndex = group;
            this.capture = capture;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int[] groups = matcher.groups;
            int[] locals = matcher.locals;
            int save0 = locals[localIndex];
            int save1 = 0;
            int save2 = 0;

            if (capture) {
                save1 = groups[groupIndex];
                save2 = groups[groupIndex+1];
            }

            // Notify GroupTail there is no need to setup group info
            // because it will be set here
            locals[localIndex] = -1;

            bool ret = true;
            for (int j = 0; j < cmin; j++) {
                if (atom.match(matcher, i, seq)) {
                    if (capture) {
                        groups[groupIndex] = i;
                        groups[groupIndex+1] = matcher.last;
                    }
                    i = matcher.last;
                } else {
                    ret = false;
                    break;
                }
            }
            if (ret) {
                if (type == GREEDY) {
                    ret = match0(matcher, i, cmin, seq);
                } else if (type == LAZY) {
                    ret = match1(matcher, i, cmin, seq);
                } else {
                    ret = match2(matcher, i, cmin, seq);
                }
            }
            if (!ret) {
                locals[localIndex] = save0;
                if (capture) {
                    groups[groupIndex] = save1;
                    groups[groupIndex+1] = save2;
                }
            }
            return ret;
        }
        // Aggressive group match
        bool match0(Matcher matcher, int i, int j, CharSequence seq) {
            // don't back off passing the starting "j"
            int min = j;
            int[] groups = matcher.groups;
            int save0 = 0;
            int save1 = 0;
            if (capture) {
                save0 = groups[groupIndex];
                save1 = groups[groupIndex+1];
            }
            for (;;) {
                if (j >= cmax)
                    break;
                if (!atom.match(matcher, i, seq))
                    break;
                int k = matcher.last - i;
                if (k <= 0) {
                    if (capture) {
                        groups[groupIndex] = i;
                        groups[groupIndex+1] = i + k;
                    }
                    i = i + k;
                    break;
                }
                for (;;) {
                    if (capture) {
                        groups[groupIndex] = i;
                        groups[groupIndex+1] = i + k;
                    }
                    i = i + k;
                    if (++j >= cmax)
                        break;
                    if (!atom.match(matcher, i, seq))
                        break;
                    if (i + k != matcher.last) {
                        if (match0(matcher, i, j, seq))
                            return true;
                        break;
                    }
                }
                while (j > min) {
                    if (next.match(matcher, i, seq)) {
                        if (capture) {
                            groups[groupIndex+1] = i;
                            groups[groupIndex] = i - k;
                        }
                        return true;
                    }
                    // backing off
                    i = i - k;
                    if (capture) {
                        groups[groupIndex+1] = i;
                        groups[groupIndex] = i - k;
                    }
                    j--;

                }
                break;
            }
            if (capture) {
                groups[groupIndex] = save0;
                groups[groupIndex+1] = save1;
            }
            return next.match(matcher, i, seq);
        }
        // Reluctant matching
        bool match1(Matcher matcher, int i, int j, CharSequence seq) {
            for (;;) {
                if (next.match(matcher, i, seq))
                    return true;
                if (j >= cmax)
                    return false;
                if (!atom.match(matcher, i, seq))
                    return false;
                if (i == matcher.last)
                    return false;
                if (capture) {
                    matcher.groups[groupIndex] = i;
                    matcher.groups[groupIndex+1] = matcher.last;
                }
                i = matcher.last;
                j++;
            }
        }
        // Possessive matching
        bool match2(Matcher matcher, int i, int j, CharSequence seq) {
            for (; j < cmax; j++) {
                if (!atom.match(matcher, i, seq)) {
                    break;
                }
                if (capture) {
                    matcher.groups[groupIndex] = i;
                    matcher.groups[groupIndex+1] = matcher.last;
                }
                if (i == matcher.last) {
                    break;
                }
                i = matcher.last;
            }
            return next.match(matcher, i, seq);
        }
        bool study(TreeInfo info) {
            // Save original info
            int minL = info.minLength;
            int maxL = info.maxLength;
            bool maxV = info.maxValid;
            bool detm = info.deterministic;
            info.reset();

            atom.study(info);

            int temp = info.minLength * cmin + minL;
            if (temp < minL) {
                temp = 0xFFFFFFF; // Arbitrary large number
            }
            info.minLength = temp;

            if (maxV & info.maxValid) {
                temp = info.maxLength * cmax + maxL;
                info.maxLength = temp;
                if (temp < maxL) {
                    info.maxValid = false;
                }
            } else {
                info.maxValid = false;
            }

            if (info.deterministic && cmin == cmax) {
                info.deterministic = detm;
            } else {
                info.deterministic = false;
            }
            return next.study(info);
        }
    }

    /**
     * A Guard node at the end of each atom node in a Branch. It
     * serves the purpose of chaining the "match" operation to
     * "next" but not the "study", so we can collect the TreeInfo
     * of each atom node without including the TreeInfo of the
     * "next".
     */
    static final class BranchConn extends Node {
        BranchConn() {};
        bool match(Matcher matcher, int i, CharSequence seq) {
            return next.match(matcher, i, seq);
        }
        bool study(TreeInfo info) {
            return info.deterministic;
        }
    }
#endif
    /**
     * Handles the branching of alternations. Note this is also used for
     * the ? quantifier to branch between the case where it matches once
     * and where it does not occur.
     */
    /*static*/ /*final*/ class Branch : public Node
    {
        QVector<Node*>* atoms;// = new Node[2];
        int size;// = 2;
        Node* conn;
    public:
        Branch(Node* first, Node* second, Node* branchConn);
        void add(Node* node);
        bool match(Matcher* matcher, int i, CharSequence* seq);
        bool study(TreeInfo* info);
    };

    /**
     * The GroupHead saves the location where the group begins in the locals
     * and restores them when the match is done.
     *
     * The matchRef is used when a reference to this group is accessed later
     * in the expression. The locals will have a negative value in them to
     * indicate that we do not want to unset the group if the reference
     * doesn't match.
     */
    /*static*/ /*final*/ class GroupHead : public Node {
        int localIndex;
    public:
        GroupHead(int localCount);
        bool match(Matcher* matcher, int i, CharSequence* seq);
        bool matchRef(Matcher* matcher, int i, CharSequence* seq);
    };
#if 0
    /**
     * Recursive reference to a group in the regular expression. It calls
     * matchRef because if the reference fails to match we would not unset
     * the group.
     */
    static final class GroupRef extends Node {
        GroupHead head;
        GroupRef(GroupHead head) {
            this.head = head;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            return head.matchRef(matcher, i, seq)
                && next.match(matcher, matcher.last, seq);
        }
        bool study(TreeInfo info) {
            info.maxValid = false;
            info.deterministic = false;
            return next.study(info);
        }
    }

    /**
     * The GroupTail handles the setting of group beginning and ending
     * locations when groups are successfully matched. It must also be able to
     * unset groups that have to be backed off of.
     *
     * The GroupTail node is also used when a previous group is referenced,
     * and in that case no group information needs to be set.
     */
    static final class GroupTail extends Node {
        int localIndex;
        int groupIndex;
        GroupTail(int localCount, int groupCount) {
            localIndex = localCount;
            groupIndex = groupCount + groupCount;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int tmp = matcher.locals[localIndex];
            if (tmp >= 0) { // This is the normal group case.
                // Save the group so we can unset it if it
                // backs off of a match.
                int groupStart = matcher.groups[groupIndex];
                int groupEnd = matcher.groups[groupIndex+1];

                matcher.groups[groupIndex] = tmp;
                matcher.groups[groupIndex+1] = i;
                if (next.match(matcher, i, seq)) {
                    return true;
                }
                matcher.groups[groupIndex] = groupStart;
                matcher.groups[groupIndex+1] = groupEnd;
                return false;
            } else {
                // This is a group reference case. We don't need to save any
                // group info because it isn't really a group.
                matcher.last = i;
                return true;
            }
        }
    }

    /**
     * This sets up a loop to handle a recursive quantifier structure.
     */
    static final class Prolog extends Node {
        Loop loop;
        Prolog(Loop loop) {
            this.loop = loop;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            return loop.matchInit(matcher, i, seq);
        }
        bool study(TreeInfo info) {
            return loop.study(info);
        }
    }

    /**
     * Handles the repetition count for a greedy Curly. The matchInit
     * is called from the Prolog to save the index of where the group
     * beginning is stored. A zero length group check occurs in the
     * normal match but is skipped in the matchInit.
     */
    static class Loop extends Node {
        Node body;
        int countIndex; // local count index in matcher locals
        int beginIndex; // group beginning index
        int cmin, cmax;
        Loop(int countIndex, int beginIndex) {
            this.countIndex = countIndex;
            this.beginIndex = beginIndex;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            // Avoid infinite loop in zero-length case.
            if (i > matcher.locals[beginIndex]) {
                int count = matcher.locals[countIndex];

                // This block is for before we reach the minimum
                // iterations required for the loop to match
                if (count < cmin) {
                    matcher.locals[countIndex] = count + 1;
                    bool b = body.match(matcher, i, seq);
                    // If match failed we must backtrack, so
                    // the loop count should NOT be incremented
                    if (!b)
                        matcher.locals[countIndex] = count;
                    // Return success or failure since we are under
                    // minimum
                    return b;
                }
                // This block is for after we have the minimum
                // iterations required for the loop to match
                if (count < cmax) {
                    matcher.locals[countIndex] = count + 1;
                    bool b = body.match(matcher, i, seq);
                    // If match failed we must backtrack, so
                    // the loop count should NOT be incremented
                    if (!b)
                        matcher.locals[countIndex] = count;
                    else
                        return true;
                }
            }
            return next.match(matcher, i, seq);
        }
        bool matchInit(Matcher matcher, int i, CharSequence seq) {
            int save = matcher.locals[countIndex];
            bool ret = false;
            if (0 < cmin) {
                matcher.locals[countIndex] = 1;
                ret = body.match(matcher, i, seq);
            } else if (0 < cmax) {
                matcher.locals[countIndex] = 1;
                ret = body.match(matcher, i, seq);
                if (ret == false)
                    ret = next.match(matcher, i, seq);
            } else {
                ret = next.match(matcher, i, seq);
            }
            matcher.locals[countIndex] = save;
            return ret;
        }
        bool study(TreeInfo info) {
            info.maxValid = false;
            info.deterministic = false;
            return false;
        }
    }

    /**
     * Handles the repetition count for a reluctant Curly. The matchInit
     * is called from the Prolog to save the index of where the group
     * beginning is stored. A zero length group check occurs in the
     * normal match but is skipped in the matchInit.
     */
    static final class LazyLoop extends Loop {
        LazyLoop(int countIndex, int beginIndex) {
            super(countIndex, beginIndex);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            // Check for zero length group
            if (i > matcher.locals[beginIndex]) {
                int count = matcher.locals[countIndex];
                if (count < cmin) {
                    matcher.locals[countIndex] = count + 1;
                    bool result = body.match(matcher, i, seq);
                    // If match failed we must backtrack, so
                    // the loop count should NOT be incremented
                    if (!result)
                        matcher.locals[countIndex] = count;
                    return result;
                }
                if (next.match(matcher, i, seq))
                    return true;
                if (count < cmax) {
                    matcher.locals[countIndex] = count + 1;
                    bool result = body.match(matcher, i, seq);
                    // If match failed we must backtrack, so
                    // the loop count should NOT be incremented
                    if (!result)
                        matcher.locals[countIndex] = count;
                    return result;
                }
                return false;
            }
            return next.match(matcher, i, seq);
        }
        bool matchInit(Matcher matcher, int i, CharSequence seq) {
            int save = matcher.locals[countIndex];
            bool ret = false;
            if (0 < cmin) {
                matcher.locals[countIndex] = 1;
                ret = body.match(matcher, i, seq);
            } else if (next.match(matcher, i, seq)) {
                ret = true;
            } else if (0 < cmax) {
                matcher.locals[countIndex] = 1;
                ret = body.match(matcher, i, seq);
            }
            matcher.locals[countIndex] = save;
            return ret;
        }
        bool study(TreeInfo info) {
            info.maxValid = false;
            info.deterministic = false;
            return false;
        }
    }

    /**
     * Refers to a group in the regular expression. Attempts to match
     * whatever the group referred to last matched.
     */
    static class BackRef extends Node {
        int groupIndex;
        BackRef(int groupCount) {
            super();
            groupIndex = groupCount + groupCount;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int j = matcher.groups[groupIndex];
            int k = matcher.groups[groupIndex+1];

            int groupSize = k - j;
            // If the referenced group didn't match, neither can this
            if (j < 0)
                return false;

            // If there isn't enough input left no match
            if (i + groupSize > matcher.to) {
                matcher.hitEnd = true;
                return false;
            }
            // Check each new char to make sure it matches what the group
            // referenced matched last time around
            for (int index=0; index<groupSize; index++)
                if (seq.charAt(i+index) != seq.charAt(j+index))
                    return false;

            return next.match(matcher, i+groupSize, seq);
        }
        bool study(TreeInfo info) {
            info.maxValid = false;
            return next.study(info);
        }
    }

    static class CIBackRef extends Node {
        int groupIndex;
        bool doUnicodeCase;
        CIBackRef(int groupCount, bool doUnicodeCase) {
            super();
            groupIndex = groupCount + groupCount;
            this.doUnicodeCase = doUnicodeCase;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int j = matcher.groups[groupIndex];
            int k = matcher.groups[groupIndex+1];

            int groupSize = k - j;

            // If the referenced group didn't match, neither can this
            if (j < 0)
                return false;

            // If there isn't enough input left no match
            if (i + groupSize > matcher.to) {
                matcher.hitEnd = true;
                return false;
            }

            // Check each new char to make sure it matches what the group
            // referenced matched last time around
            int x = i;
            for (int index=0; index<groupSize; index++) {
                int c1 = Character.codePointAt(seq, x);
                int c2 = Character.codePointAt(seq, j);
                if (c1 != c2) {
                    if (doUnicodeCase) {
                        int cc1 = Character.toUpperCase(c1);
                        int cc2 = Character.toUpperCase(c2);
                        if (cc1 != cc2 &&
                            Character.toLowerCase(cc1) !=
                            Character.toLowerCase(cc2))
                            return false;
                    } else {
                        if (ASCII.toLower(c1) != ASCII.toLower(c2))
                            return false;
                    }
                }
                x += Character.charCount(c1);
                j += Character.charCount(c2);
            }

            return next.match(matcher, i+groupSize, seq);
        }
        bool study(TreeInfo info) {
            info.maxValid = false;
            return next.study(info);
        }
    }

    /**
     * Searches until the next instance of its atom. This is useful for
     * finding the atom efficiently without passing an instance of it
     * (greedy problem) and without a lot of wasted search time (reluctant
     * problem).
     */
    static final class First extends Node {
        Node atom;
        First(Node node) {
            this.atom = BnM.optimize(node);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            if (atom instanceof BnM) {
                return atom.match(matcher, i, seq)
                    && next.match(matcher, matcher.last, seq);
            }
            for (;;) {
                if (i > matcher.to) {
                    matcher.hitEnd = true;
                    return false;
                }
                if (atom.match(matcher, i, seq)) {
                    return next.match(matcher, matcher.last, seq);
                }
                i += countChars(seq, i, 1);
                matcher.first++;
            }
        }
        bool study(TreeInfo info) {
            atom.study(info);
            info.maxValid = false;
            info.deterministic = false;
            return next.study(info);
        }
    }

    static final class Conditional extends Node {
        Node cond, yes, not;
        Conditional(Node cond, Node yes, Node not) {
            this.cond = cond;
            this.yes = yes;
            this.not = not;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            if (cond.match(matcher, i, seq)) {
                return yes.match(matcher, i, seq);
            } else {
                return not.match(matcher, i, seq);
            }
        }
        bool study(TreeInfo info) {
            int minL = info.minLength;
            int maxL = info.maxLength;
            bool maxV = info.maxValid;
            info.reset();
            yes.study(info);

            int minL2 = info.minLength;
            int maxL2 = info.maxLength;
            bool maxV2 = info.maxValid;
            info.reset();
            not.study(info);

            info.minLength = minL + Math.min(minL2, info.minLength);
            info.maxLength = maxL + Math.max(maxL2, info.maxLength);
            info.maxValid = (maxV & maxV2 & info.maxValid);
            info.deterministic = false;
            return next.study(info);
        }
    }

    /**
     * Zero width positive lookahead.
     */
    static final class Pos extends Node {
        Node cond;
        Pos(Node cond) {
            this.cond = cond;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int savedTo = matcher.to;
            bool conditionMatched = false;

            // Relax transparent region boundaries for lookahead
            if (matcher.transparentBounds)
                matcher.to = matcher.getTextLength();
            try {
                conditionMatched = cond.match(matcher, i, seq);
            } finally {
                // Reinstate region boundaries
                matcher.to = savedTo;
            }
            return conditionMatched && next.match(matcher, i, seq);
        }
    }

    /**
     * Zero width negative lookahead.
     */
    static final class Neg extends Node {
        Node cond;
        Neg(Node cond) {
            this.cond = cond;
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int savedTo = matcher.to;
            bool conditionMatched = false;

            // Relax transparent region boundaries for lookahead
            if (matcher.transparentBounds)
                matcher.to = matcher.getTextLength();
            try {
                if (i < matcher.to) {
                    conditionMatched = !cond.match(matcher, i, seq);
                } else {
                    // If a negative lookahead succeeds then more input
                    // could cause it to fail!
                    matcher.requireEnd = true;
                    conditionMatched = !cond.match(matcher, i, seq);
                }
            } finally {
                // Reinstate region boundaries
                matcher.to = savedTo;
            }
            return conditionMatched && next.match(matcher, i, seq);
        }
    }

    /**
     * For use with lookbehinds; matches the position where the lookbehind
     * was encountered.
     */
    static Node lookbehindEnd = new Node() {
        bool match(Matcher matcher, int i, CharSequence seq) {
            return i == matcher.lookbehindTo;
        }
    };

    /**
     * Zero width positive lookbehind.
     */
    static class Behind extends Node {
        Node cond;
        int rmax, rmin;
        Behind(Node cond, int rmax, int rmin) {
            this.cond = cond;
            this.rmax = rmax;
            this.rmin = rmin;
        }

        bool match(Matcher matcher, int i, CharSequence seq) {
            int savedFrom = matcher.from;
            bool conditionMatched = false;
            int startIndex = (!matcher.transparentBounds) ?
                             matcher.from : 0;
            int from = Math.max(i - rmax, startIndex);
            // Set end boundary
            int savedLBT = matcher.lookbehindTo;
            matcher.lookbehindTo = i;
            // Relax transparent region boundaries for lookbehind
            if (matcher.transparentBounds)
                matcher.from = 0;
            for (int j = i - rmin; !conditionMatched && j >= from; j--) {
                conditionMatched = cond.match(matcher, j, seq);
            }
            matcher.from = savedFrom;
            matcher.lookbehindTo = savedLBT;
            return conditionMatched && next.match(matcher, i, seq);
        }
    }

    /**
     * Zero width positive lookbehind, including supplementary
     * characters or unpaired surrogates.
     */
    static final class BehindS extends Behind {
        BehindS(Node cond, int rmax, int rmin) {
            super(cond, rmax, rmin);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int rmaxChars = countChars(seq, i, -rmax);
            int rminChars = countChars(seq, i, -rmin);
            int savedFrom = matcher.from;
            int startIndex = (!matcher.transparentBounds) ?
                             matcher.from : 0;
            bool conditionMatched = false;
            int from = Math.max(i - rmaxChars, startIndex);
            // Set end boundary
            int savedLBT = matcher.lookbehindTo;
            matcher.lookbehindTo = i;
            // Relax transparent region boundaries for lookbehind
            if (matcher.transparentBounds)
                matcher.from = 0;

            for (int j = i - rminChars;
                 !conditionMatched && j >= from;
                 j -= j>from ? countChars(seq, j, -1) : 1) {
                conditionMatched = cond.match(matcher, j, seq);
            }
            matcher.from = savedFrom;
            matcher.lookbehindTo = savedLBT;
            return conditionMatched && next.match(matcher, i, seq);
        }
    }

    /**
     * Zero width negative lookbehind.
     */
    static class NotBehind extends Node {
        Node cond;
        int rmax, rmin;
        NotBehind(Node cond, int rmax, int rmin) {
            this.cond = cond;
            this.rmax = rmax;
            this.rmin = rmin;
        }

        bool match(Matcher matcher, int i, CharSequence seq) {
            int savedLBT = matcher.lookbehindTo;
            int savedFrom = matcher.from;
            bool conditionMatched = false;
            int startIndex = (!matcher.transparentBounds) ?
                             matcher.from : 0;
            int from = Math.max(i - rmax, startIndex);
            matcher.lookbehindTo = i;
            // Relax transparent region boundaries for lookbehind
            if (matcher.transparentBounds)
                matcher.from = 0;
            for (int j = i - rmin; !conditionMatched && j >= from; j--) {
                conditionMatched = cond.match(matcher, j, seq);
            }
            // Reinstate region boundaries
            matcher.from = savedFrom;
            matcher.lookbehindTo = savedLBT;
            return !conditionMatched && next.match(matcher, i, seq);
        }
    }

    /**
     * Zero width negative lookbehind, including supplementary
     * characters or unpaired surrogates.
     */
    static final class NotBehindS extends NotBehind {
        NotBehindS(Node cond, int rmax, int rmin) {
            super(cond, rmax, rmin);
        }
        bool match(Matcher matcher, int i, CharSequence seq) {
            int rmaxChars = countChars(seq, i, -rmax);
            int rminChars = countChars(seq, i, -rmin);
            int savedFrom = matcher.from;
            int savedLBT = matcher.lookbehindTo;
            bool conditionMatched = false;
            int startIndex = (!matcher.transparentBounds) ?
                             matcher.from : 0;
            int from = Math.max(i - rmaxChars, startIndex);
            matcher.lookbehindTo = i;
            // Relax transparent region boundaries for lookbehind
            if (matcher.transparentBounds)
                matcher.from = 0;
            for (int j = i - rminChars;
                 !conditionMatched && j >= from;
                 j -= j>from ? countChars(seq, j, -1) : 1) {
                conditionMatched = cond.match(matcher, j, seq);
            }
            //Reinstate region boundaries
            matcher.from = savedFrom;
            matcher.lookbehindTo = savedLBT;
            return !conditionMatched && next.match(matcher, i, seq);
        }
    }
#endif
/*static*/ /*final*/ class TreeInfo {
    int minLength;
    int maxLength;
    bool maxValid;
    bool deterministic;
public:
    TreeInfo() ;
    void reset();
};

class Pattern : public QObject
{
 Q_OBJECT
public:
 explicit Pattern(QObject *parent = 0);
enum MODES
{
 /**
  * Enables Unix lines mode.
  *
  * <p> In this mode, only the <tt>'\n'</tt> line terminator is recognized
  * in the behavior of <tt>.</tt>, <tt>^</tt>, and <tt>$</tt>.
  *
  * <p> Unix lines mode can also be enabled via the embedded flag
  * expression&nbsp;<tt>(?d)</tt>.
  */
 UNIX_LINES = 0x01,

 /**
  * Enables case-insensitive matching.
  *
  * <p> By default, case-insensitive matching assumes that only characters
  * in the US-ASCII charset are being matched.  Unicode-aware
  * case-insensitive matching can be enabled by specifying the {@link
  * #UNICODE_CASE} flag in conjunction with this flag.
  *
  * <p> Case-insensitive matching can also be enabled via the embedded flag
  * expression&nbsp;<tt>(?i)</tt>.
  *
  * <p> Specifying this flag may impose a slight performance penalty.  </p>
  */
 CASE_INSENSITIVE = 0x02,

 /**
  * Permits whitespace and comments in pattern.
  *
  * <p> In this mode, whitespace is ignored, and embedded comments starting
  * with <tt>#</tt> are ignored until the end of a line.
  *
  * <p> Comments mode can also be enabled via the embedded flag
  * expression&nbsp;<tt>(?x)</tt>.
  */
 COMMENTS = 0x04,

 /**
  * Enables multiline mode.
  *
  * <p> In multiline mode the expressions <tt>^</tt> and <tt>$</tt> match
  * just after or just before, respectively, a line terminator or the end of
  * the input sequence.  By default these expressions only match at the
  * beginning and the end of the entire input sequence.
  *
  * <p> Multiline mode can also be enabled via the embedded flag
  * expression&nbsp;<tt>(?m)</tt>.  </p>
  */
 MULTILINE = 0x08,

 /**
  * Enables literal parsing of the pattern.
  *
  * <p> When this flag is specified then the input string that specifies
  * the pattern is treated as a sequence of literal characters.
  * Metacharacters or escape sequences in the input sequence will be
  * given no special meaning.
  *
  * <p>The flags CASE_INSENSITIVE and UNICODE_CASE retain their impact on
  * matching when used in conjunction with this flag. The other flags
  * become superfluous.
  *
  * <p> There is no embedded flag character for enabling literal parsing.
  * @since 1.5
  */
 LITERAL = 0x10,

 /**
  * Enables dotall mode.
  *
  * <p> In dotall mode, the expression <tt>.</tt> matches any character,
  * including a line terminator.  By default this expression does not match
  * line terminators.
  *
  * <p> Dotall mode can also be enabled via the embedded flag
  * expression&nbsp;<tt>(?s)</tt>.  (The <tt>s</tt> is a mnemonic for
  * "single-line" mode, which is what this is called in Perl.)  </p>
  */
 DOTALL = 0x20,

 /**
  * Enables Unicode-aware case folding.
  *
  * <p> When this flag is specified then case-insensitive matching, when
  * enabled by the {@link #CASE_INSENSITIVE} flag, is done in a manner
  * consistent with the Unicode Standard.  By default, case-insensitive
  * matching assumes that only characters in the US-ASCII charset are being
  * matched.
  *
  * <p> Unicode-aware case folding can also be enabled via the embedded flag
  * expression&nbsp;<tt>(?u)</tt>.
  *
  * <p> Specifying this flag may impose a performance penalty.  </p>
  */
 UNICODE_CASE = 0x40,

 /**
  * Enables canonical equivalence.
  *
  * <p> When this flag is specified then two characters will be considered
  * to match if, and only if, their full canonical decompositions match.
  * The expression <tt>"a&#92;u030A"</tt>, for example, will match the
  * string <tt>"&#92;u00E5"</tt> when this flag is specified.  By default,
  * matching does not take canonical equivalence into account.
  *
  * <p> There is no embedded flag character for enabling canonical
  * equivalence.
  *
  * <p> Specifying this flag may impose a performance penalty.  </p>
  */
 CANON_EQ = 0x80,

 /**
  * Enables the Unicode version of <i>Predefined character classes</i> and
  * <i>POSIX character classes</i>.
  *
  * <p> When this flag is specified then the (US-ASCII only)
  * <i>Predefined character classes</i> and <i>POSIX character classes</i>
  * are in conformance with
  * <a href="http://www.unicode.org/reports/tr18/"><i>Unicode Technical
  * Standard #18: Unicode Regular Expression</i></a>
  * <i>Annex C: Compatibility Properties</i>.
  * <p>
  * The UNICODE_CHARACTER_CLASS mode can also be enabled via the embedded
  * flag expression&nbsp;<tt>(?U)</tt>.
  * <p>
  * The flag implies UNICODE_CASE, that is, it enables Unicode-aware case
  * folding.
  * <p>
  * Specifying this flag may impose a performance penalty.  </p>
  * @since 1.7
  */
 UNICODE_CHARACTER_CLASS = 0x100
};
/*public*/ QString pattern();
/*public*/ static Pattern* compile(QString regex);
/*public*/ static Pattern* compile(QString regex, int flags);
/*public*/ QString toString();
/*public*/ Matcher* matcher(CharSequence* input);
/*public*/ int flags();
/*public*/ static bool matches(QString regex, CharSequence* input);
/*public*/ QStringList* split(CharSequence* input, int limit);


signals:

public slots:

private:
/**
 * The original regular-expression pattern string.
 *
 * @serial
 */
/*private*/ QString _pattern;

/**
 * The original pattern flags.
 *
 * @serial
 */
/*private*/ int _flags;

/**
 * Boolean indicating this Pattern is compiled; this is necessary in order
 * to lazily compile deserialized Patterns.
 */
/*private*/ /*transient*/ /*volatile*/ bool compiled;// = false;

/**
 * The normalized pattern string.
 */
/*private*/ /*transient*/ QString normalizedPattern;

/**
 * The starting point of state machine for the find operation.  This allows
 * a match to start anywhere in the input.
 */
/*transient*/ Node* root;

/**
 * The root of object tree for a match operation.  The pattern is matched
 * at the beginning.  This may include a find that uses BnM or a First
 * node.
 */
/*transient*/ Node* matchRoot;

/**
 * Temporary storage used by parsing pattern slice.
 */
/*transient*/ QList<int> buffer;

/**
 * Map the "name" of the "named capturing group" to its group id
 * node.
 */
/*transient*/ /*volatile*/ QMap<QString, int> namedGroups;

/**
 * Temporary storage used while parsing group references.
 */
/*transient*/ QList<GroupHead*> groupNodes;

/**
 * Temporary null terminated code point array used by pattern compiling.
 */
/*private*/ /*transient*/ QVector<int>* temp;

/**
 * The number of capturing groups in this Pattern. Used by matchers to
 * allocate storage needed to perform a match.
 */
/*transient*/ int capturingGroupCount;

/**
 * The local variable count used by parsing tree. Used by matchers to
 * allocate storage needed to perform a match.
 */
/*transient*/ int localCount;

/**
 * Index into the pattern string that keeps track of how much has been
 * parsed.
 */
/*private*/ /*transient*/ int cursor;

/**
 * Holds the length of the pattern string.
 */
/*private*/ /*transient*/ int patternLength;

/**
 * If the Start node might possibly match supplementary characters.
 * It is set to true during compiling if
 * (1) There is supplementary char in pattern, or
 * (2) There is complement node of Category or Block
 */
/*private*/ /*transient*/ bool hasSupplementary;
/*private*/ bool has(int f);
/*private*/ void accept(int ch, QString s);
/*private*/ void mark(int c);
/*private*/ int peek();
/*private*/ int read();
/*private*/ int readEscaped();
/*private*/ int next();
/*private*/ int nextEscaped();
/*private*/ int peekPastWhitespace(int ch);
/*private*/ int parsePastWhitespace(int ch);
/*private*/ int parsePastLine();
/*private*/ int peekPastLine();
/*private*/ bool isLineSeparator(int ch);
/*private*/ int skip();
/*private*/ void unread();
/*private*/ PatternSyntaxException error(QString s);
/*private*/ bool findSupplementary(int start, int end);
/*private*/ /*static*/ /*final*/ bool isSupplementary(int ch);
/*private*/ Node* expr(Node* end);
/*private*/ Node* sequence(Node* end);
/*private*/ Node* atom();
/*private*/ void append(int ch, int len);
/*private*/ Node* ref(int refNum);
/*private*/ Pattern(QString p, int f);
/*private*/ void compile();
static Node* _accept;// = new Node();
static Node* _lastAccept;// = new LastNode();
/*private*/ void normalize();


friend class Matcher;
};

#endif // PATTERN_H
