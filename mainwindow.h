#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class MainWindow;
}

// Пример лямбда-выражения с параметрами и возвращаемым значением
// (лямбда-выражение представляет анонимную функцию,
// и оно не является методом класса, поэтому не может быть добавлено прямо в определение класса.
// Лямбда-выражение существует в пределах блока кода, в котором оно определено.)
auto addLambda = [](int a, int b) -> int {
    return a + b;
};

class SignalEmitter : public QObject {
    Q_OBJECT



public slots:
    void emitSignal(int a, int b) {
        emit calculationDone(addLambda(a, b));
    }

signals:
    void calculationDone(int result);

};

// Реализация класса для демонстрации
class SignalEmitter_v2 : public QObject {
    Q_OBJECT

public:
    int addMethod_v2(int a, int b) {
        return a + b;
    }

public slots:
    void emitSignal_v2(int a, int b) {
        emit calculationDone_v2(addMethod_v2(a, b));
    }

signals:
    void calculationDone_v2(int result);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SignalEmitter * emitter;
    SignalEmitter_v2 * emitter_v2;

private slots:
    void myFunctionTest();
};

#endif // MAINWINDOW_H
