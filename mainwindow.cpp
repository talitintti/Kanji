#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "word.h"
#include "wordhandler.h"
#include <QMessageBox>
#include <QDebug>



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





QPoint MainWindow::DrawNext(QHash<Word *, bool> &is_drawn_already,
                            Word *word,
                            qsizetype number_to_draw,
                            QPoint &currentpos)
{
    if (is_drawn_already.size() == number_to_draw) {
        return currentpos;
    }

    if (!is_drawn_already.contains(word)) {
        is_drawn_already.insert(word, true);
        GraphicsItemWord *graphics_item = new GraphicsItemWord(word);
        graphics_item->setPos(currentpos);
        graphics_scene->addItem(graphics_item);

        QListIterator iter(word->getRelatedWords());
        while (iter.hasNext()) {
            QPoint next_pos = nextpos.Get();
            DrawNext(is_drawn_already, iter.next(), number_to_draw, next_pos);
        }
    }
    return currentpos;
}


void MainWindow::DrawMaster(qsizetype item_amount)
{
    QList<Word *> unified_list(word_handler.getAllWords());

    QHash<Word *, bool> is_drawn_already;


    QListIterator iter(unified_list);
    QPoint curr_point(0,0);
    //while (iter.hasNext()) {
    //    Word *next_word = iter.next();
    //    if (is_drawn_already.contains(next_word)) {
    //        continue;
    //    }
    //    curr_point = DrawNext(is_drawn_already, next_word, item_amount, curr_point);
    //}
    for (int i = 0; i <= 0; i++) {
        Word *next_word = unified_list.at(i);
        if (is_drawn_already.contains(next_word)) {
            continue;
        }
        curr_point = DrawNext(is_drawn_already, next_word, item_amount, curr_point);
    }
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
    DrawMaster(word_handler.getCompositeStorageSize() + word_handler.getKanjiStorageSize());
}

MainWindow::~MainWindow()
{
    delete ui;
}
