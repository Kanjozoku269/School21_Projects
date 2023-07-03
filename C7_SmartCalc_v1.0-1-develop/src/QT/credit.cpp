#include "credit.h"

#include "mainwindow.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) : QMainWindow(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  setAttribute(Qt::WA_DeleteOnClose);
}

credit::~credit() { delete ui; }

void credit::calc_credit() {
  QPushButton *button = (QPushButton *)sender();
  QString summ = ui->INSUM->text();
  QString procent = ui->INSTAVKA->text();
  QString term = ui->INSROK->text();

  if (!(summ.isEmpty() && procent.isEmpty() && term.isEmpty())) {
    double summ_number = summ.toDouble();
    double procent_number = procent.toDouble();
    double term_number = term.toDouble();

    double pay_mounth = 0;
    double total_summ = 0;
    double number_inter = summ_number;

    QString first_mounth_pay;
    QString mounth_pay;

    if (button == ui->DIFF) {
      for (int i = 1; i <= term_number; ++i) {
        pay_mounth = summ_number / term_number +
                     number_inter * procent_number / 12.0 / 100;
        total_summ += pay_mounth;
        number_inter = summ_number - i * summ_number / term_number;
        mounth_pay = QString("%L1").arg(pay_mounth, 0, 'f', 2);
        if (i == 1) {
          first_mounth_pay = mounth_pay;
        }
        mounth_pay = first_mounth_pay + " - " + mounth_pay;
      }
    }
    if (button == ui->ANNUIT) {
      double proc_stavka = procent_number / 12 / 100;
      pay_mounth = summ_number *
                   (proc_stavka * pow(1 + proc_stavka, term_number)) /
                   (pow(1 + proc_stavka, term_number) - 1);
      total_summ = pay_mounth * term_number;
      mounth_pay = QString("%L1").arg(pay_mounth, 0, 'f', 2);
    }

    ui->OPLATA->setText(mounth_pay);
    double overPay = total_summ - summ_number;
    ui->ALLOPLATA->setText(QString("%L1").arg(total_summ, 0, 'f', 2));
    ui->PEREPLATA->setText(QString("%L1").arg(overPay, 0, 'f', 2));
  } else {
    QMessageBox::critical(this, "Fail", "Проверь поля для заполнения");
  }
}

void credit::on_ANNUIT_clicked() { calc_credit(); }

void credit::on_DIFF_clicked() { calc_credit(); }
