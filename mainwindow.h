#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QRandomGenerator>
#include <graphicsitemword.h>
#include <nextpos.h>
#include <wordhandler.h>
#include <QGraphicsView>

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

private slots:
    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    WordHandler word_handler;
    NextPos nextpos;

    QGraphicsView *view_all;
    QGraphicsView *view_search;
    QGraphicsScene *graphics_scene_all;
    QGraphicsScene *graphics_scene_search;

    void CreateGraphicsItems();
    void DrawAll(QList<Word*> &unified_list);
    void DrawSearched(QList<Word*> drawables);
    bool DrawNext(QHash<Word *, bool> &is_drawn_already,
                    Word *word,
                    qsizetype number_to_draw,
                    QPoint last_point,
                    bool no_relation
                    );

    void DrawLine(QPoint pos1, QPoint pos2, QGraphicsScene *scene);
    void DrawWord(QPoint pos, Word* word, QGraphicsScene *scene);

    void SetStyles();
};
#endif // MAINWINDOW_H
