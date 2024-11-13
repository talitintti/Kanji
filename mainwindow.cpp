#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "word.h"
#include "wordhandler.h"

// Checks the kanji according to the values on thisthis site
// http://www.rikai.com/library/kanjitables/kanji_codes.unicode.shtml
// hex value range [4e00, 9faf]
bool isKanji(QChar character)
{
    if (19968 < character.unicode() && character.unicode() < 40879) {
        return true;
    }
    return false;
}

// Returns true if there are stil items to draw.
// Returns false if we have drawn the given amount already
bool MainWindow::DrawNext(QHash<Word *, bool> &is_drawn_already,
                            Word *word,
                            qsizetype number_to_draw
                            )
{
    if ((is_drawn_already.size() == number_to_draw) ) {
        return false;
    }

    if (is_drawn_already.contains(word)) {
        return true;
    }

    QPoint next_pos = nextpos.Get();
    is_drawn_already.insert(word, true);
    GraphicsItemWord *graphics_item = new GraphicsItemWord(word);
    graphics_item->setPos(next_pos);
    graphics_scene->addItem(graphics_item);

    QListIterator iter(word->getRelatedWords());
    while (iter.hasNext()) {
        DrawNext(is_drawn_already, iter.next(), number_to_draw);
    }

    return true;
}

void MainWindow::DrawMaster(QList<Word*> & unified_list)
{
    qsizetype list_size = unified_list.size() ;
    QHash<Word *, bool> is_drawn_already;
    QListIterator iter(unified_list);

    while (iter.hasNext()) {
        Word *next_word = iter.next();
        if (!DrawNext(is_drawn_already, next_word, list_size)) {
            break;
        }
    }
    //for (int i = 0; i <= 20; i++) {
    //    Word *next_word = unified_list.at(i);
    //    QPoint curr_point = nextpos.Get();
    //    if (!DrawNext(is_drawn_already, next_word, item_amount, curr_point)) {
    //        break;
    //    }
    //}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    word_handler = WordHandler();
    graphics_scene = new QGraphicsScene();
    ui->graphicsView->setScene(graphics_scene);
    bool success = word_handler.ReadParse(QString("/home/momo/Desktop/core2k.txt"));
    word_handler.LinkWords();

    QList<Word *> unified_list(word_handler.getAllWords());
    DrawMaster(unified_list);
    qDebug() << nextpos.GetIterations();
    qDebug() << unified_list.size();
}

MainWindow::~MainWindow()
{
    delete ui;
}
