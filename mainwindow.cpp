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

  /*  connect(ui->pushButton_00,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_01,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_02,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_10,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_11,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_12,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_20,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_21,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));
    connect(ui->pushButton_22,SIGNAL(released()),this,SLOT(on_pushButton_pressed()));

    ui->pushButton_00->setCheckable(true);
    ui->pushButton_01->setCheckable(true);
    ui->pushButton_02->setCheckable(true);
    ui->pushButton_10->setCheckable(true);
    ui->pushButton_11->setCheckable(true);
    ui->pushButton_12->setCheckable(true);
    ui->pushButton_20->setCheckable(true);
    ui->pushButton_21->setCheckable(true);
    ui->pushButton_22->setCheckable(true);*/

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
    bool output;

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

    output = check_win(row, col);

    if(output)
     {
        if(m[row][col].data == 1)
            QMessageBox::information(this, "Game Over", "Player 1 wins!!!!");
        else if(m[row][col].data == 2)
            QMessageBox::information(this, "Game Over", "Player 2 wins!!!!");

        QApplication::quit();
     }
}

bool MainWindow::check_win(int row, int col)
{
    int i, current_move;

    current_move = m[row][col].data;

    for(i = 0; i < 3; i++) //checking row
    {
        if(m[row][i].data == 0 || m[row][i].data != current_move)
            return false;
    }

    for(i = 0; i < 3; i++) // checking column
    {
        if(m[i][col].data == 0 || m[i][col].data != current_move)
            return false;
    }

    for(i = 0; i < 3; i++) // checking diagonal one
    {
        if(m[i][i].data == 0 || m[i][i].data != current_move)
            return false;
    }

    for(i = 0; i < 3; i++) // checking diagonal one
    {
        if(m[i][3-i].data == 0 || m[i][3-i].data != current_move)
            return false;
    }

    return true;
}

void MainWindow::on_pushButton_pressed()
{
    //QPushButton *button = (QPushButton*)sender();
   // updateMatrix(button);
    init_matrix();
    myFunction();
    //int output;
  //  if(turn){
    //    button->setText("O");
        //button->setIcon(QIcon("/home/maitreyee/ticTacToe/OIcon.png"));
        //button->setIconSize(QSize(65,65));
    //}
    //else
      //  button->setText("X");

   //turn = !turn;

    //if(button->isChecked())
      //  button->setEnabled(false);

    //output = checkwin();
}

void MainWindow::check()
{
  /*  QPushButton *button = (QPushButton*)sender();
    if(turn)
        button->setText("O");
    else
        button->setText("X");

   turn = !turn;

    if(button->isChecked())
        button->setEnabled(false);*/

}

void MainWindow::myFunction()
{
    QWidget *centralWidget = new QWidget;
    int count, i, j;
   // bool value = false;

    QGridLayout *layout = new QGridLayout(centralWidget);
    const QSize btnSize = QSize(90, 90);
    const QSize winSize = QSize(270, 270);



    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(count <= 9)
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
                count++;
            }
        }
    }

    centralWidget->setLayout(layout);
    centralWidget->setFixedSize(winSize);

        setCentralWidget(centralWidget);
        centralWidget->show();
}

