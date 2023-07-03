#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>

extern "C" {
#include <../backend/backend.h>
}

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  void graph_expression(const char *line);

 private:
  Ui::Graph *ui;
};

#endif  // GRAPH_H
