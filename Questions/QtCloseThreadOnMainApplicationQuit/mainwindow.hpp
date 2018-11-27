#include <QMainWindow>
#include <QApplication>
#include <QTime>

#include "ui_mainwindow.h"
#include "threadclass.hpp"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR) : QMainWindow(parent) {
		ui.setupUi(this);
	}

	~MainWindow() {
		// here was my "delete th;" originally
	}

public slots:
	void on_actionQuit_triggered() {
		qDebug() << "QApplication::quit()";
		QApplication::quit();
	}

	void on_pB_make_things_clicked() {
		qDebug() << "started thread handler";
		th = new ThreadHandler(this);
		th->startThread();
	}

	void aboutToQuit() {
		// wait for thread in aboutToQuit and process all events afterwards
		// https://stackoverflow.com/questions/53468408
		// https://forum.qt.io/post/355466
		delete th;
		QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
	}

private:
	Ui::MainWindow ui;
	ThreadHandler *th;
};