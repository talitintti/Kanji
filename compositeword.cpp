#include "compositeword.h"
#include <kanji.h>

QString CompositeWord::getCharacters() const
{
    return Word::getCharacters();
}

void CompositeWord::setKanji(Kanji *kanji)
{
    this->related_kanji.append(kanji);
}

QList<Kanji *> CompositeWord::getRelated() const
{
    QList<Kanji *> list(this->related_kanji);
    return list;
}

QList<Word*> CompositeWord::getRelatedWords() const {
    QList<Word*> list;
    for (Kanji* kanji : this->related_kanji) {
        Word* word = static_cast<Word*>(kanji);
        list.append(word);
    }
    return list;
}
