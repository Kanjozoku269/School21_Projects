#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

namespace Ui {
class credit;
}

class credit : public QMainWindow {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

  void calc_credit();

 private slots:
  void on_ANNUIT_clicked();
  void on_DIFF_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
