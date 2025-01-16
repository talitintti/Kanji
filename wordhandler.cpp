#include "wordhandler.h"
#include <QDebug>

// Checks the kanji according to the values on this site
// http://www.rikai.com/library/kanjitables/kanji_codes.unicode.shtml
// hex value range [4e00, 9faf]
static bool isKanji(QChar character)
{
    if (19968 < character.unicode() && character.unicode() < 40879) {
        return true;
    }
    return false;
}

static bool isHiragana(QChar character) {
    if (12352 < character.unicode() && character.unicode() < 12447) {
        return true;
    }
    return false;
}

static bool isKatakana(QChar character) {
    if (12448 < character.unicode() && character.unicode() < 12543) {
        return true;
    }
    return false;
}

WordHandler::WordHandler() {}

WordHandler::~WordHandler()
{
    QListIterator iter_comp(this->composite_storage);
    while (iter_comp.hasNext()) {
        delete iter_comp.next();
    }

    QListIterator iter_kanji(this->kanji_storage);
    while (iter_kanji.hasNext()) {
        delete iter_kanji.next();
    }
}

QList<Kanji *> WordHandler::getKanjiPointers()
{
    QList<Kanji *> kanji_storage_copy;
    for (Kanji *kanji : this->kanji_storage) {
        kanji_storage_copy.append(kanji);
    }
    return kanji_storage_copy;
}

QList<CompositeWord *> WordHandler::getCompositePointers()
{
    QList<CompositeWord *> composite_storage_copy;
    for (CompositeWord *composite : this->composite_storage) {
        composite_storage_copy.append(composite);
    }
    return composite_storage_copy;
}

// Just hack the line into three parts based on tabs
QList<QString> WordHandler::ProcessLine(QString line)
{
    QList<QString> word_data;

    if (line.isEmpty() || line.at(0) == QChar('#')) {
        return word_data;
    }

    static QRegularExpression e("\\t+|\\s\\s+");
    QList<QString> tokens = line.split(e);
    for (auto const &t : tokens) {
        word_data.append(t);
    }

    if (word_data.length() != 4) {
        qDebug() << "[NOTICE: line was broken into not four parts]"
                 << "\n"
                 << line << "\n";
    }

    return word_data;
}

bool WordHandler::ReadParse(QString ankideck_url)
{
    QFile file(ankideck_url);
    if (!file.exists()) {
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    while (!file.atEnd()) {
        QString line = file.readLine();
        QList<QString> data_per_word = ProcessLine(line);

        if (!data_per_word.isEmpty() && data_per_word.length() == 4) {
            QString the_word_itself(data_per_word.at(0));
            if (the_word_itself.length() > 1) {
                this->AddComposite(data_per_word.at(0),
                                   data_per_word.at(1),
                                   data_per_word.at(2),
                                   data_per_word.at(3));
            } else {
                this->AddKanji(data_per_word.at(0),
                               data_per_word.at(1),
                               data_per_word.at(2),
                               data_per_word.at(3));
            }
        }
    }
    return true;
}

void WordHandler::AddKanji(const QString &chars,
                           const QString &reading,
                           const QString &explanation,
                           const QString &englishEquivalent)
{
    Kanji *kanji = new Kanji(chars, reading, explanation, englishEquivalent);

    this->kanji_storage.append(kanji);
    this->kanji_map.insert(chars, kanji);
}

void WordHandler::AddComposite(const QString &chars,
                               const QString &reading,
                               const QString &explanation,
                               const QString &englishEquivalent)
{
    CompositeWord *composite = new CompositeWord(chars, reading, explanation, englishEquivalent);
    this->composite_storage.append(composite);
}

// Links the compositeword to know the pointers of its constituent kanji and kanji to know where it appears
// if a kanji in word is not a kanji card in deck we create a remnant kanji which is used for searching later
void WordHandler::LinkWords()
{
    for (CompositeWord *c_word : this->composite_storage) {
        const QString &c_word_const
            = c_word->getCharacters(); // apparently needed to not detach QString when iterating below
        for (auto const &current_char : c_word_const) {
            Kanji *corresponding_kanji = this->kanji_map.value(current_char);
            if (isKanji(current_char) && corresponding_kanji != NULL) {
                corresponding_kanji->setAppearsIn(c_word);
                c_word->setKanji(corresponding_kanji);
            }
            else if (isKanji(current_char)){
                Kanji *remnant = this->remnant_map.value(current_char);
                if (remnant == NULL) { // when two composit words dont have the same remnant
                    remnant = new Kanji(current_char, "", "", "");
                    remnant_map.value(current_char, remnant);
                }
                remnant->setAppearsIn(c_word);
                c_word->setKanji(remnant);
            }
        }
    }
}

qsizetype WordHandler::getKanjiStorageSize()
{
    return this->kanji_storage.size();
}
qsizetype WordHandler::getCompositeStorageSize()
{
    return this->composite_storage.size();
}

QList<Word *> WordHandler::getAllWords() const
{
    QList<Word *> list;
    for (CompositeWord *c_word : this->composite_storage) {
        Word *word = static_cast<Word *>(c_word);
        list.append(word);
    }
    for (Kanji *kanji : this->kanji_storage) {
        Word *word = static_cast<Word *>(kanji);
        list.append(word);
    }
    return list;
}

// Searches if there is a kanji that corresponds to search_key.
// If not empty list is give
// If yes the Kanji and it's first order related words are returned
QList<Word *> WordHandler::GetFirstOrderRelated(QString search_key) {
    Kanji *primary_kanji = this->kanji_map.value(search_key);
    auto a = kanji_map.keys();
    qDebug() << a.at(1) << "\n";
    Word *word = static_cast<Word *>(primary_kanji);
    if (primary_kanji != NULL) {
        qDebug() << word->getCharacters();
        auto related = GetRelated(word);
        related.push_front(word);

        return related;
    }

    primary_kanji = this->remnant_map.value(search_key);
    word = static_cast<Word *>(primary_kanji);
    if (word != NULL) {
        qDebug() << word->getCharacters();
        auto related = GetRelated(word);
        related.push_front(word);

        return related;
    }

    QList<Word *> returnables;
    return returnables;
}

QList<Word *> WordHandler::GetRelated(Word *kanji) {
    QList<Word *> related;
    for (Word *c_word : kanji->getRelatedWords()) {
        related.append(c_word);
    }
    return related;
}
