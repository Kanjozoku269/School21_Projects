#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <locale.h>

#include <QApplication>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QWindow>

extern "C" {
#include <../backend/backend.h>
}

#include "credit.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void result();
  void operations();
  void functions();
  void digit_numbers();
  void AC();
  void keyPressEvent(QKeyEvent *event) override;
  void on_GRAPHIC_clicked();
  void on_QCREDIT_clicked();
  void on_QDEBIT_clicked();
  void on_QCH_ZNAK_clicked();
};

#endif  // MAINWINDOW_H
