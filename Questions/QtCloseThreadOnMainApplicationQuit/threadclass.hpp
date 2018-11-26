#include <QObject>
#include <QThread>
#include <QDebug>

class ThreadClass : public QObject {
    Q_OBJECT
public:
    explicit ThreadClass() {}
    virtual ~ThreadClass() {}
signals:
    void finished();
public slots:
    void scanAll() {
        for(long i = 0; i < 10000; i++){
			for (long k = 0; k < 1000000; k++);
			if(i%1000 == 0)
				qDebug() << "thread: " << i;
        }
    }
    void stop() {
        qDebug() << "STOP SIGNAL --> EMIT FINSIHED";
        emit finished();
    }
};

class ThreadHandler : public QObject {
	Q_OBJECT
public:
	explicit ThreadHandler(QObject *parent = 0) : parent(parent), my_thread(Q_NULLPTR) {}
	virtual ~ThreadHandler() {
		if (my_thread != Q_NULLPTR && my_thread->isRunning()) {
			my_thread->quit();
			my_thread->wait();
		}
		qDebug() << "ThreadHandler Destructor";
	}
	void startThread() {
		if (my_thread == Q_NULLPTR) {
			my_thread = new QThread;
			ThreadClass *my_threaded_class = new ThreadClass();
			my_threaded_class->moveToThread(my_thread);
			// start and finish
			QObject::connect(my_thread, &QThread::started, my_threaded_class, &ThreadClass::scanAll);
			// https://stackoverflow.com/questions/53468408
			QObject::connect(my_thread, &QThread::finished, my_threaded_class, &ThreadClass::stop);
			// finish cascade
			// https://stackoverflow.com/a/21597042/6411540
			QObject::connect(my_threaded_class, &ThreadClass::finished, my_threaded_class, &ThreadClass::deleteLater);
			QObject::connect(my_threaded_class, &ThreadClass::destroyed, my_thread, &QThread::quit);
			QObject::connect(my_thread, &QThread::finished, my_thread, &QThread::deleteLater);

			my_thread->start();
		}
	}
signals:
	void stopThread();
private:
	QObject *parent;
	QThread *my_thread;
};