#include "graph.h"

#include "mainwindow.h"
#include "ui_graph.h"

#define LEN 1000000

Graph::Graph(QWidget* parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  setFixedSize(width(), height());
  setAttribute(Qt::WA_DeleteOnClose);
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

Graph::~Graph() { delete ui; }

void Graph::graph_expression(const char* line) {
  double min_X = -10000;
  double max_X = 10000;

  QList<double> x_line(LEN);
  QList<double> y_line(LEN);

  double step = (fabs(min_X) + fabs(max_X)) / LEN;

  for (int i = 0; i < LEN; i++) {
    x_line[i] = step * i + min_X;
  }

  int res = graphic(line, x_line.data(), y_line.data(), LEN);
  if (res) {
    QMessageBox::critical(this, "ERROR",
                          "Упс! Что-то пошло не так... Пример: cos(x)");
    close();
  } else {
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x_line, y_line);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->xAxis->setRange(-10, 10);
    ui->widget->yAxis->setRange(-2.5, 2.5);
    ui->widget->replot();
  }
}
