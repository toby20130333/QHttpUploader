
#include "QHttpUploader.h"
#include <QCoreApplication>
int main(int argc,char *argv[]){
	QCoreApplication a(argc,argv);
	QHttpUploader er("http://127.0.0.1/upload.php");
	//er.setUrl("http://127.0.0.1/upload.php");
	er.addItem("NAME","VALUE");
	QFile *f = new QFile("test.txt");
	er.addFile(f);
	QFile f2("test.png");
	er.addFile(f2);
	er.addFile("test2.png");
	er.upload();
	return a.exec();
}