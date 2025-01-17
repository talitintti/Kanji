#ifndef WORD_H
#define WORD_H
#include <QString>

class Word
{
public:
    Word(QString id, QString chars, QString reading, QString englishEquivalent, QString explanation, QString explanation_eng)
        : id(id)
        , characters(chars)
        , reading(reading)
        , english_eq(englishEquivalent)
        , explanation(explanation)
        , explanation_eng(explanation_eng)
    {}
    virtual ~Word();
    QString getCharacters() const;
    QString getReading() const;
    QString getExplanation() const;
    QString getEnglishEquivalent() const;
    virtual QList<Word *> getRelatedWords() const = 0;

private:
    QString id; //0
    QString characters; // 1
    QString reading; // 3
    QString english_eq; // 4
    QString explanation; // 6
    QString explanation_eng; // 9

};

#endif // WORD_H
