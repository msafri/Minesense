#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QGraphicsEllipseItem>
#include "selectableellipse.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    view(NULL)
{
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::triggered, [=]() {
        QStringList filters;
        filters << "Comma Separated (*.csv)"
                << "Any files (*)";

        QFileDialog fd(this);
        fd.setNameFilters(filters);
        if (fd.exec()) {
            fileName = fd.selectedFiles()[0];
            ui->statusBar->showMessage(QString("Loading: ") + fileName);

            connect(&dataModel, &Data::Loaded, [=] () {
                ui->statusBar->showMessage(QString("Editing: ") + fileName);
            });

            if (dataModel.LoadFile(fileName))
            {
                ui->statusBar->showMessage(QString("Editing: ") + fileName);
                connect(view, &View::DataChanged, [=] (int idx, float x, int y) {
                    DataPoint_t dp;
                    dp.energy = x;
                    dp.count = y;
                    dataModel.SetDataIdx(idx,dp);
                });
                view->SetData(dataModel.GetData());
                view->UpdateView();
            }
            else
            {
                ui->statusBar->showMessage(QString("Failed to load: ") + fileName);
            }
        }
    });

    connect(ui->actionSave, &QAction::triggered, [=] () {
        if (!dataModel.SaveFile(fileName)) {
            //message box
        }
    });

    connect(ui->actionClose, &QAction::triggered, [=] () {
        view->ClearData();
        dataModel.clear();
    });

    connect(ui->actionExit, &QAction::triggered, [=]() {
        // if file not saved warn user
        qApp->exit();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    if (view)
        delete view;
}

void MainWindow::showEvent(QShowEvent *event) {
    this->showMaximized();

    view = new View(this);
    setCentralWidget(view->view());

    fileName = "mvcdata.csv";
    if (dataModel.LoadFile(fileName))
    {
        connect(view, &View::DataChanged, [=] (int idx, float x, int y) {
            DataPoint_t dp;
            dp.energy = x;
            dp.count = y;
            dataModel.SetDataIdx(idx,dp);
        });

        view->SetData(dataModel.GetData());
        view->UpdateView();
    }
}
