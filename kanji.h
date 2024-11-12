#ifndef KANJI_H
#define KANJI_H
#include <compositeword.h>
#include <word.h>

class Kanji : public Word
{
public:
    using Word::Word;
    ~Kanji();
    QString getCharacters() const;
    void setAppearsIn(CompositeWord *composite_word);
    QList<CompositeWord *> getRelated() const;
    QList<Word *> getRelatedWords() const override;

private:
    QList<CompositeWord *> appears_in;
};

#endif // KANJI_H
