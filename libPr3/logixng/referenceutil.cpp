#include "referenceutil.h"
#include "exceptions.h"
#include "memory.h"
#include "memorymanager.h"
#include "instancemanager.h"
#include "namedtablemanager.h"

/**
 * Utility methods to handle references
 */
// /*public*/  class ReferenceUtil {

    // The methods in this class are protected instead of private to let the
    // test class ReferenceUtilTest access the methods.

    /**
     * Checks if the parameter is a reference or not.
     * @param value the string to check
     * @return true if value has a reference. falsw otherwise
     */
    /*static*/ /*public*/  bool ReferenceUtil::isReference(QString value) {
        if (value == "") return false;
        // A reference starts with { and ends with }
        return value.startsWith("{")
                && value.endsWith("}")
                && value.length() > 2;
    }

    /*static*/ /*protected*/ QString ReferenceUtil::unescapeString(QString value, int startIndex, int endIndex) {
        bool escaped = false;

        QString sb;// = new StringBuilder();
        for (int i=startIndex; i < endIndex; i++) {
            if (value.at(i) == '\\') escaped = !escaped;
            else escaped = false;

            if (! escaped) sb.append(value.at(i));
        }

        return sb;
    }

    /**
     * Get the value.
     * The value ends either with end of string, or with any of the characters
     * comma, left square bracket, right square bracket or right curly bracket.
     * These characters may be escaped and should then be ignored.
     * @param reference the reference
     * @param startIndex where in the string the value starts, since the
     * reference string may contain several references.
     * @param endIndex index of the end of the value. This is an output parameter.
     * @return the value
     */
    /*static*/ /*protected*/ QString ReferenceUtil::getValue(QString reference, int startIndex, IntRef* endIndex) {
        bool escapeFound = false;
        bool escaped = false;
        int end = startIndex;
        while (end < reference.length()
                && (escaped ||
                    (reference.at(end) != ','
                    && reference.at(end) != '['
                    && reference.at(end) != ']'
                    && reference.at(end) != '{'
                    && reference.at(end) != '}'))) {
            if (reference.at(end) == '\\') {
                escaped = !escaped;
                escapeFound = true;
            } else {
                escaped = false;
            }
            end++;
        }
        endIndex->v = end;

        if (startIndex == end) throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        if (escapeFound) return unescapeString(reference, startIndex, end);
        else return reference.mid(startIndex, end);
    }

    /**
     * Get the reference or the value.The value ends either with end of string,
     * or with any of the characters comma, left square bracket, right square
     * bracket or right curly bracket.
     * These characters may be escaped and should then be ignored.
     *
     * @param symbolTable the symbol table
     * @param reference the reference
     * @param startIndex where in the string the value starts, since the
     * reference string may contain several references.
     * @param endIndex index of the end of the value. This is an output parameter.
     * @return the value
     */
    /*static*/ /*protected*/ QString ReferenceUtil::getReferenceOrValue(SymbolTable* symbolTable, QString reference, int startIndex, IntRef* endIndex) {

        while ((startIndex < reference.length()-1)
                && (reference.at(startIndex).isSpace())) {
            startIndex++;
        }

        QString result;

        // Do we have a new reference?
        if (reference.at(startIndex) == '{') {
            result = getReference(symbolTable, reference, startIndex, endIndex);
        } else {
            result = getValue(reference, startIndex, endIndex);
        }

        // Skip spaces
        while ((endIndex->v < reference.length()) && reference.at(endIndex->v).isSpace()) {
            endIndex->v++;
        }

        return result;
    }

    /**
     * Get the value of a reference
     * @param symbolTable the symbol table
     * @param reference the reference
     * @param startIndex where in the string the reference starts, since the
     * reference string may contain several references.
     * @param endIndex index of the end of the reference. This is an output parameter.
     * @return the value of the reference
     */
    /*static*/ /*protected*/ QString ReferenceUtil::getReference(
            SymbolTable* symbolTable, QString reference, int startIndex, IntRef* endIndex) {

        // A reference must start with the char {
        if (reference.at(startIndex) != '{') {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }

        QString leftValue;
        QString column;
        QString row;

        startIndex++;

        leftValue = getReferenceOrValue(symbolTable, reference, startIndex, endIndex);

        if (endIndex->v == reference.length()) {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }

        if ((reference.at(endIndex->v) != '}') && (reference.at(endIndex->v) != '[')) {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }


        endIndex->v++;

        if ((endIndex->v == reference.length()) || (reference.at(endIndex->v-1) == '}')) {

            if ((symbolTable != nullptr) && symbolTable->hasValue(leftValue)) {
                return /*TypeConversionUtil::convertToString*/(symbolTable->getValue(leftValue).toString()/*, false*/);
            }
            MemoryManager* memoryManager = (MemoryManager*)InstanceManager::getDefault("MemoryManager");
            Memory* m = (Memory*)memoryManager->getNamedBean(leftValue.trimmed())->self();
            if (m != nullptr) {
                if (m->getValue() != QVariant()) return m->getValue().toString();
                else throw new IllegalArgumentException("Memory '"+leftValue+"' has no value");
            }
            else throw new IllegalArgumentException("Memory '"+leftValue+"' is not found");
        }

        // If we are here, we have a table reference. Find out column and row.
        if (reference.at(endIndex->v-1) != '[') {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }


        // If we are here, we have a table reference. Find out column and row.
        row = getReferenceOrValue(symbolTable, reference, endIndex->v, endIndex);

        endIndex->v++;

        // Skip spaces
        while ((endIndex->v-2 < reference.length()) && /*Character.isSpaceChar*/(reference.at(endIndex->v-1).isSpace())) {
            endIndex->v++;
        }

        int lastEndIndV = endIndex->v;

        // Skip spaces
        while ((endIndex->v < reference.length()) && /*Character.isSpaceChar*/(reference.at(endIndex->v).isSpace())) {
            endIndex->v++;
        }

        if ((reference.at(lastEndIndV-1) == ']')
                && (reference.at(endIndex->v) == '}')) {

            endIndex->v++;

            NamedTableManager* tableManager = (NamedTableManager*)
                    InstanceManager::getDefault("NamedTableManager");

            NamedTable* table = (NamedTable*)tableManager->getNamedBean(leftValue)->self();
            if (table != nullptr) {
                QVariant cell = table->getCell(row.trimmed());
                return cell != QVariant() ? cell.toString() : nullptr;
            } else {
                throw new IllegalArgumentException("Table '"+leftValue+"' is not found");
            }
        }

        if (endIndex->v == reference.length() || reference.at(lastEndIndV-1) != ',') {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }

        column = getReferenceOrValue(symbolTable, reference, endIndex->v, endIndex);

        // Skip spaces
        while ((endIndex->v < reference.length()) && /*Character.isSpaceChar*/(reference.at(endIndex->v).isSpace())) {
            endIndex->v++;
        }

        if (endIndex->v == reference.length() || reference.at(endIndex->v) != ']') {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }

//        if (((reference.at(endIndex->v) == ']')
//                && (reference.at(endIndex->v+1) == '}'))) {
        if ((reference.at(endIndex->v) == ']')) {

            endIndex->v++;

            NamedTableManager* tableManager = (NamedTableManager*)
                    InstanceManager::getDefault("NamedTableManager");

            NamedTable* table = (NamedTable*)tableManager->getNamedBean(leftValue)->self();
            if (table != nullptr) {
                QVariant cell = table->getCell(row.trimmed(),column.trimmed());
                // Skip spaces
                while ((endIndex->v < reference.length()) && /*Character.isSpaceChar*/(reference.at(endIndex->v).isSpace())) {
                    endIndex->v++;
                }
                endIndex->v++;
                return cell != QVariant() ? cell.toString() : nullptr;
            } else {
                throw new IllegalArgumentException("Table '"+leftValue+"' is not found");
            }
        }

        throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
    }

    //@CheckReturnValue
    //@Nonnull
    /*static*/ /*public*/  QString ReferenceUtil::getReference(SymbolTable* symbolTable, QString reference) {
        if (!isReference(reference)) {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }

        IntRef* endIndex = new IntRef();
        QString ref = getReference(symbolTable, reference, 0, endIndex);

        if (endIndex->v != reference.length()) {
            throw new IllegalArgumentException("Reference '"+reference+"' is not a valid reference");
        }

        return ref;
    }


