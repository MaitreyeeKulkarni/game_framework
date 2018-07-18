#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayout>
#include <QApplication>
#include <QMessageBox>

bool turn = true, value = false;
int turn_count = 0;

typedef struct {
    int data;
    QPushButton *button_ptr;
}matrix;

matrix m[3][3];


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->maximumSize());

    connect(ui->pushButton_start_game,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void init_matrix()
{
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m[i][j].data = 0;
            m[i][j].button_ptr = NULL;
        }
    }
}

void MainWindow::update_move(int row, int col, QPushButton *btnptr)
{
    if(m[row][col].data == 0)
    {
        if(turn)
        {
            btnptr->setText("O");
            m[row][col].data = 1;
            m[row][col].button_ptr = btnptr;
        }
        else
        {
            btnptr->setText("X");
            m[row][col].data = 2;
            m[row][col].button_ptr = btnptr;
        }

       turn = !turn;

        if(btnptr->isChecked())
            btnptr->setEnabled(false);
    }

    check_win(row, col);
}

void MainWindow::check_win(int row, int col)
{
    int current_move;
    bool output;

    current_move = m[row][col].data;

    output = check_row_win(current_move, row);

    if(!output)
        output = check_column_win(current_move, col);
    if(!output)
        output = check_diagonal_win(current_move, 0);
    if(!output)
        output = check_diagonal_win(current_move, 1);

    if(output)
    {
    if(m[row][col].data == 1)
    QMessageBox::information(this, "Game Over", "Player 1 wins!!!!");
    else if(m[row][col].data == 2)
    QMessageBox::information(this, "Game Over", "Player 2 wins!!!!");

    QApplication::quit();
    }
}

bool MainWindow::check_row_win(int current_move, int row)
{
   for(int i = 0; i < 3; i++) //checking row
    {
        if(m[row][i].data == 0 || m[row][i].data != current_move)
            return false;
    }
    return true;
}

bool MainWindow::check_column_win(int current_move, int col)
{
   for(int i = 0; i < 3; i++) // checking column
    {
        if(m[i][col].data == 0 || m[i][col].data != current_move)
            return false;
    }
   return true;
}

bool MainWindow::check_diagonal_win(int current_move, int no)
{
    int i;
    if(no == 0)
    {
        for(i = 0; i < 3; i++) // checking diagonal one
        {
            if(m[i][i].data == 0 || m[i][i].data != current_move)
                return false;
        }
    }
    else if(no == 1)
    {
        for(i = 0; i < 3; i++) // checking diagonal one
            {
                if(m[i][2-i].data == 0 || m[i][2-i].data != current_move)
                    return false;
            }
    }
    return true;
}

void MainWindow::on_pushButton_pressed()
{
    init_matrix();
    myFunction();
}

void MainWindow::myFunction()
{
    QWidget *centralWidget = new QWidget;
    int i, j;
    QGridLayout *layout = new QGridLayout(centralWidget);
    const QSize btnSize = QSize(90, 90);
    const QSize winSize = QSize(270, 270);



    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
                button[i][j] = new QPushButton(" ");
                button[i][j]->maximumSize();
                button[i][j]->setFixedSize(btnSize);
                button[i][j]->setCheckable(true);
                connect(button[i][j], &QPushButton::clicked, this, [this, i , j]()
                        {
                            update_move(i, j, button[i][j]);

                        }
                );
                layout->addWidget(button[i][j], i, j);
                layout->setSpacing(0);
        }
    }

    centralWidget->setLayout(layout);
    centralWidget->setFixedSize(winSize);

    setCentralWidget(centralWidget);
    centralWidget->show();
}

