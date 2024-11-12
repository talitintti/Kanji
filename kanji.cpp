#include "kanji.h"

Kanji::~Kanji() {}

QString Kanji::getCharacters() const
{
    return Word::getCharacters();
}

void Kanji::setAppearsIn(CompositeWord *composite_word)
{
    this->appears_in.append(composite_word);
}

QList<CompositeWord *> Kanji::getRelated() const
{
    QList<CompositeWord *> list(this->appears_in);
    return list;
}

QList<Word *> Kanji::getRelatedWords() const
{
    QList<Word *> list;
    for (CompositeWord *comp : this->appears_in) {
        Word *word = static_cast<Word *>(comp);
        list.append(word);
    }
    return list;
}
