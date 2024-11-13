#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QRandomGenerator>
#include <graphicsitemword.h>
#include <nextpos.h>
#include <wordhandler.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WordHandler word_handler;
    NextPos nextpos;
    QGraphicsScene *graphics_scene;
    //QList<QSharedPointer<GraphicsItemWord>> graphics_items;

    void CreateGraphicsItems();
    void DrawMaster(QList<Word*> &unified_list);
    bool DrawNext(QHash<Word *, bool> &is_drawn_already,
                    Word *word,
                    qsizetype number_to_draw,
                    QPoint last_point,
                    bool no_relation
                    );

    void DrawLine(QPoint pos1, QPoint pos2);
    void DrawWord(QPoint pos, Word* word, QHash<Word*, bool> &is_drawn_already);
};
#endif // MAINWINDOW_H
