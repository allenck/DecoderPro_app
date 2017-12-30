#ifndef MATCHER_H
#define MATCHER_H

#include <QVector>
#include <QObject>

class CharSequence;
class Pattern;
class QString;
class Matcher
{
 //Q_OBJECT
public:
    Matcher();
    /*public*/ static QString quoteReplacement(QString s);
#if 0
    /*public*/ bool matches();
    /*public*/ bool find();
    /*public*/ bool find(int start);
    /*public*/ bool lookingAt();
    /*public*/ int start();
    /*public*/ int start(int group) ;
    /*public*/ int start(QString name);
    /*public*/ int end();
    /*public*/ int end(int group);
    /*public*/ int end(QString name);
    Matcher(Pattern* parent, CharSequence* text);
    /*public*/ Matcher* reset();
    /*public*/ int groupCount();

private:
    /**
     * The Pattern object that created this Matcher.
     */
    Pattern* parentPattern;

    /**
     * The storage used by groups. They may contain invalid values if
     * a group was skipped during the matching.
     */
    QVector<int>* groups;

    /**
     * The range within the sequence that is to be matched. Anchors
     * will match at these "hard" boundaries. Changing the region
     * changes these values.
     */
    int from, to;

    /**
     * Lookbehind uses this value to ensure that the subexpression
     * match ends at the point where the lookbehind was encountered.
     */
    int lookbehindTo;

    /**
     * The original string being matched.
     */
    CharSequence* text;

    /**
     * Matcher state used by the last node. NOANCHOR is used when a
     * match does not have to consume all of the input. ENDANCHOR is
     * the mode used for matching all the input.
     */
    static /*final*/ int ENDANCHOR;// = 1;
    static /*final*/ int NOANCHOR;// = 0;
    int acceptMode = NOANCHOR;

    /**
     * The range of string that last matched the pattern. If the last
     * match failed then first is -1; last initially holds 0 then it
     * holds the index of the end of the last match (which is where the
     * next search starts).
     */
    int first;// = -1
    int last;// = 0;

    /**
     * The end index of what matched in the last match operation.
     */
    int oldLast;// = -1;

    /**
     * The index of the last position appended in a substitution.
     */
    int lastAppendPosition;// = 0;

    /**
     * Storage used by nodes to tell what repetition they are on in
     * a pattern, and where groups begin. The nodes themselves are stateless,
     * so they rely on this field to hold state during a match.
     */
    QVector<int>*  locals;

    /**
     * Boolean indicating whether or not more input could change
     * the results of the last match.
     *
     * If hitEnd is true, and a match was found, then more input
     * might cause a different match to be found.
     * If hitEnd is true and a match was not found, then more
     * input could cause a match to be found.
     * If hitEnd is false and a match was found, then more input
     * will not change the match.
     * If hitEnd is false and a match was not found, then more
     * input will not cause a match to be found.
     */
    bool hitEnd;

    /**
     * Boolean indicating whether or not more input could change
     * a positive match into a negative one.
     *
     * If requireEnd is true, and a match was found, then more
     * input could cause the match to be lost.
     * If requireEnd is false and a match was found, then more
     * input might change the match but the match won't be lost.
     * If a match was not found, then requireEnd has no meaning.
     */
    bool requireEnd;

    /**
     * If transparentBounds is true then the boundaries of this
     * matcher's region are transparent to lookahead, lookbehind,
     * and boundary matching constructs that try to see beyond them.
     */
    bool transparentBounds;// = false;

    /**
     * If anchoringBounds is true then the boundaries of this
     * matcher's region match anchors such as ^ and $.
     */
    bool anchoringBounds;// = true;
    int getTextLength();
    int getMatchedGroupIndex(QString name);
    bool match(int from, int anchor);
    bool search(int from);
#endif
};

#endif // MATCHER_H
