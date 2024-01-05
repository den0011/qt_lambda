#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Обычная функция с использованием SIGNAL и SLOT
    connect(ui->pushButton_test_1, SIGNAL(clicked()), this, SLOT(myFunctionTest()));

    // Обычная функция
    QObject::connect(ui->pushButton_test_1, &QPushButton::clicked, this, &MainWindow::myFunctionTest);

    // Лямбда-выражение
    QObject::connect(ui->pushButton_test_2, &QPushButton::clicked, []() {
        qDebug() << "Сигнал был обработан лямбда-выражением!";
        QMessageBox::information(nullptr,QString(),QString("Сигнал был обработан лямбда-выражением!"));
    });

    // Лямбда-выражение с захватом переменной из окружающей области видимости
    int x = 10;
    QObject::connect(ui->pushButton_test_3, &QPushButton::clicked, [x]() {
        qDebug() << "Захваченная переменная x: " << x;
        QMessageBox::information(nullptr,QString(),QString("Захваченная переменная x: %1").arg(x));
    });



    emitter = new SignalEmitter;
    QObject::connect(ui->pushButton_test_4, &QPushButton::clicked, emitter, [=]() {
        // Передаем значения a и b
        emitter->emitSignal(20,30);
    });


    // Создаем соединение для реакции на результат лямбда-выражения
    QObject::connect(emitter, &SignalEmitter::calculationDone, [](int result) {
        qDebug() << "Результат вычисления (a+b): " << result;
        QMessageBox::information(nullptr,QString(),QString("Результат вычисления (a+b):  %1").arg(result));
    });




    emitter_v2 = new SignalEmitter_v2;

    QObject::connect(ui->pushButton_test_5, &QPushButton::clicked, [=]() {
        int a = 200;
        int b = 300;

        // Вызываем метод emitSignal у объекта emitter с передачей нужных значений
        emitter_v2->emitSignal_v2(a, b);
    });

    // Создаем соединение для реакции на результат лямбда-выражения
    QObject::connect(emitter_v2, &SignalEmitter_v2::calculationDone_v2, [=](int result) {
        qDebug() << "Результат вычисления (a+b): " << result;
        QMessageBox::information(nullptr,QString(),QString("Результат вычисления (a+b):  %1").arg(result));
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myFunctionTest()
{
     qDebug() << "Сигнал был обработан обычной функцией!";
     QMessageBox::information(nullptr,QString(),QString("Сигнал был обработан обычной функцией!"));
}
