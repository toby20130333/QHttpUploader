/**
 * QUploader 上传文件类
 * author: hetal 
 * email : hetao at hetao.name
 * date  : 2010-4-14
 */

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDebug>
#include <QFile>
#include <QNetworkReply>

class QHttpUploader:public QObject
{
	Q_OBJECT
private:
	QUrl _url;
	QString _boundary;
	QByteArray _data;
	QNetworkAccessManager _manager;
public:
	/**
	 * @param QString 上传地址
	 */
	QHttpUploader(QString);
	/**
	 * @param QUrl 上传地址
	 */
	QHttpUploader(QUrl);
	QHttpUploader();
	/**
	 * 设置上传地址
	 * @param QString 
	 */
	void setUrl(QString);
	/**
	 * 设置上传地址
	 * @param QUrl 
	 */
	void setUrl(QUrl);
	/**
	 * 设置cookie
	 * @param QNetworkCookieJar *
	 */
	void setCookie(QNetworkCookieJar *){};
	/**
	 * 增加参数
	 */
	void addItem (const QString key, const QString value );
	void addEncodedItem (const QByteArray key,const  QByteArray value );
	/*增加文件*/
	void addFile(QFile *);
	void addFile(QFile &);
	void addFile(QString &);
	void addFile(char*);
	/*上传*/
	void upload();

private slots:
	void	_postFinished ( QNetworkReply * reply );
signals:
	/*上传开始*/
	void started();
	/**
	 *上传完成
	 *你应该QNetworkReply::deleteLater() 
	 **/
	void finished(QNetworkReply*);
	/*上传失败*/
	void error(QNetworkReply::NetworkError);

};