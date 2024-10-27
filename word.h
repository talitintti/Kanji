#ifndef WORD_H
#define WORD_H
#include <QString>

class Word
{
public:
    Word(QString chars, QString reading, QString explanation, QString englishEquivalent)
        : characters(chars)
        , reading(reading)
        , explanation(explanation)
        , english_eq(englishEquivalent)
    {}
    virtual ~Word();
    QString getCharacters() const;
    QString getReading() const;
    QString getExplanation() const;
    QString getEnglishEquivalent() const;
    virtual QList<Word*> getRelatedWords() const = 0;

private:
    QString characters;
    QString reading;
    QString explanation;
    QString english_eq;
};

#endif // WORD_H
