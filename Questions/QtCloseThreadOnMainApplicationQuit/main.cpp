#include <QApplication>
#include "mainwindow.hpp"

#include <vld.h>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	MainWindow w;
	QObject::connect(&a, &QApplication::aboutToQuit, &w, &MainWindow::aboutToQuit);
	w.show();

	return a.exec();
}
