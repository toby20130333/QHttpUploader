/**
 * QUploader 上传文件类
 * author: hetal 
 * email : hetao at hetao.name
 * date  : 2010-4-14
 */

#include "QHttpUploader.h"
QHttpUploader::QHttpUploader(QUrl url){
	_url = url;
	_boundary = "---------------------------hetal-created-2010-4-14";
	connect(&_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(_postFinished(QNetworkReply*)));
}
QHttpUploader::QHttpUploader(QString url){
	_url = QUrl(url);
	_boundary = "---------------------------hetal-created-2010-4-14";
	connect(&_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(_postFinished(QNetworkReply*)));
}
QHttpUploader::QHttpUploader(){
	_boundary = "---------------------------hetal-created-2010-4-14";
	connect(&_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(_postFinished(QNetworkReply*)));
}
void QHttpUploader::addEncodedItem (const QByteArray key, const QByteArray value ){
	_data.append("--"+_boundary+"\r\n");
    _data.append("Content-Disposition: form-data; name=\""+key+"\"\r\n");
    _data.append("Content-Transfer-Encoding: binary\r\n\r\n");
    _data.append(value);
    _data.append("\r\n");
};
void QHttpUploader::addItem (const QString key,const QString value ){
	_data.append("--"+_boundary+"\r\n");
    _data.append("Content-Disposition: form-data; name=\""+key+"\"\r\n");
    _data.append("Content-Transfer-Encoding: binary\r\n\r\n");
    _data.append(value);
    _data.append("\r\n");
};
void QHttpUploader::addFile(QFile *file){
	if(!file->open(QIODevice::ReadOnly))return;
	_data.append("--"+_boundary+"\r\n");
    _data.append("Content-Disposition: form-data; name=\""+file->fileName()+"\"; filename=\"" + file->fileName()+ "\"\r\n");
    _data.append("Content-Transfer-Encoding: binary\r\n\r\n");
    _data.append(file->readAll());
    _data.append("\r\n");
	file->close();
}
void QHttpUploader::addFile(QFile & file){
	addFile(&file);
}
void QHttpUploader::addFile(QString & file){
	addFile(new QFile(file));
}
void QHttpUploader::addFile(char* file){
	addFile(QString(file));
}
void QHttpUploader::setUrl(QString url){
	_url = QUrl(url);
}
void QHttpUploader::setUrl(QUrl url){
	_url = url;
}
void QHttpUploader::upload(){
	emit started();
	qDebug()<<"UPLOAD STARTED";
	QNetworkRequest q(_url);
	q.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data, boundary="+_boundary);
	_data.append("--"+_boundary+"--\r\n");
	_manager.post(q,_data);
}
void QHttpUploader::_postFinished ( QNetworkReply * reply ){
	if(reply->error()!=QNetworkReply::NoError){
		qDebug()<<"UPLOAD ERROR("<<reply->error()<<")";
		emit error(reply->error());
		reply->deleteLater();
	}else{
		qDebug()<<"UPLOAD FINISHED";
		emit finished(reply);
	}
}
