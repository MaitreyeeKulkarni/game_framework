#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();
    void check();

private:
    Ui::MainWindow *ui;
    void myFunction();
    void update_move(int, int, QPushButton*);
    bool check_win(int, int);
    QSignalMapper *signalMapper;
    QPushButton *button[10][10];
};

#endif // MAINWINDOW_H
