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

private:
    Ui::MainWindow *ui;
    void myFunction();
    void update_move(int, int, QPushButton*);
    void check_win(int, int);
    bool check_row_win(int, int);
    bool check_column_win(int, int);
    bool check_diagonal_win(int, int);
    QPushButton *button[10][10];
};

#endif // MAINWINDOW_H
