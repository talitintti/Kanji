#ifndef COMPOSITEWORD_H
#define COMPOSITEWORD_H

#include <QList>
#include <word.h>

class Kanji;

class CompositeWord : public Word
{
public:
    using Word::Word;
    void setKanji(Kanji* kanji);
    QString getCharacters() const;
    QList<Kanji*> getRelated() const ;
    //QList<Word*> getRelatedWords() const override;
private:
    QList<Kanji*> related_kanji;

};

#endif // COMPOSITEWORD_H
