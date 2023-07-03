#include "mainwindow.h"

#include "credit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)

{
  ui->setupUi(this);
  connect(ui->QRAVNO, SIGNAL(clicked()), this, SLOT(result()));
  connect(ui->Qint0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->Qint9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->QSKOBKA_L, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QSKOBKA_R, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QMINUS, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QKOREN, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QPLUS, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QDELENIE, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QSTEPEN, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QMULTIPLY, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QMOD, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QTOCHKA, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QSINUS, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QARKSIN, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QCOSINUS, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QARKCOS, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QTANGENS, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QARKTAN, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QLOG10, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QLOG, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->QAC, SIGNAL(clicked()), this, SLOT(AC()));
  connect(ui->QMOD, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->QIKS, SIGNAL(clicked()), this, SLOT(operations()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::result() {
  QString line = ui->VVOD->text();
  std::string current_locale_text = line.toStdString();
  const char *line_ptr = current_locale_text.c_str();
  double result = 0.0;
  smartCalc(line_ptr, &result);
  ui->VVOD->setText(QString::number(result, 'g', 8));
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->VVOD->text();
  if (button->text() == "÷" && !(ui->VVOD->text().endsWith("÷")) &&
      !(ui->VVOD->text().endsWith("/"))) {
    new_label += "/";
  } else if (button->text() == "×" && !(ui->VVOD->text().endsWith("x")) &&
             !(ui->VVOD->text().endsWith("*"))) {
    new_label += "*";
  } else if (button->text() == "+" && !(ui->VVOD->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" && !(ui->VVOD->text().endsWith("-"))) {
    new_label += "-";
  } else if (button->text() == "^" && !(ui->VVOD->text().endsWith("^"))) {
    new_label += "^";
  } else if (button->text() == "%" && !(ui->VVOD->text().endsWith("%"))) {
    new_label += "%";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  } else if (button->text() == "." && !(ui->VVOD->text().endsWith("."))) {
    new_label += ".";
  } else if (button->text() == "X" && !(ui->VVOD->text().endsWith("X"))) {
    new_label += "x";
  } else if (button->text() == "√" && !(ui->VVOD->text().endsWith("√"))) {
    new_label += "sqrt(";
  }
  ui->VVOD->setText(new_label);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->VVOD->text() + button->text() + "(";
  ui->VVOD->setText(new_label);
}

void MainWindow::digit_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->VVOD->text() + button->text();
  ui->VVOD->setText(new_label);
}

void MainWindow::AC() { ui->VVOD->setText(""); }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    ui->QRAVNO->click();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void MainWindow::on_GRAPHIC_clicked() {
  QString line = ui->VVOD->text();
  Graph *graphPlot = new Graph;
  graphPlot->graph_expression(line.toStdString().c_str());
  graphPlot->show();
}

void MainWindow::on_QCREDIT_clicked() {
  credit *creditcalc = new credit;
  creditcalc->show();
}

void MainWindow::on_QDEBIT_clicked() {
  QMessageBox::critical(this, "Fail", "В разработке :)");
}

void MainWindow::on_QCH_ZNAK_clicked() {
  QMessageBox::critical(this, "Fail", "В разработке :)");
}
