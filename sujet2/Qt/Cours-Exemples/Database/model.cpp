#include <QtGui>
#include <QtSql>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
// #include "connection.h"

 void initializeModel(QSqlRelationalTableModel *model)
 {
     model->setTable("employee");

     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->setRelation(2, QSqlRelation("city", "id", "name"));
     model->setRelation(3, QSqlRelation("country", "id", "name"));

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("City"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Country"));

     model->select();
 }

 QTableView *createView(const QString &title, QSqlTableModel *model)
 {
     QTableView *view = new QTableView;œ
     view->setModel(model);
     view->setItemDelegate(new QSqlRelationalDelegate(view));
     view->setWindowTitle(title);
     return view;
 }

 void createRelationalTables()
 {
     QSqlQuery query;
     query.exec("create table employee(id int primary key, name varchar(20), city int, country int)");
     query.exec("insert into employee values(1, 'Toto', 5000, 47)");
     query.exec("insert into employee values(2, 'Harald', 80000, 49)");
     query.exec("insert into employee values(3, 'Sam', 100, 1)");
 
     query.exec("create table city(id int, name varchar(20))");
     query.exec("insert into city values(100, 'San Jose')");
     query.exec("insert into city values(5000, 'Oslo')");
     query.exec("insert into city values(80000, 'Munich')");

     query.exec("create table country(id int, name varchar(20))");
     query.exec("insert into country values(1, 'USA')");
     query.exec("insert into country values(47, 'Norway')");
     query.exec("insert into country values(49, 'Germany')");
 }

 int main(int argc, char *argv[])
 {
      QApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("toto");
//    db.setHostName("nedelec-lap1");
//    db.setUserName("nedelec");
//    QSqlDatabase db = QSqlDatabase::addDatabase("SQLITE");
//    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
//     if (!createConnection())
//         return 1;

     createRelationalTables();
     QSqlRelationalTableModel model;
     initializeModel(&model);
     QTableView *view = createView(QObject::tr("Relational Table Model"), &model);
     view->show();

/*
 QSqlQuery q("select * from employee");
 QSqlRecord rec = q.record();

 qDebug() << "Number of columns: " << rec.count();

 int nameCol = rec.indexOf("name"); // index of the field "name"
 while (q.next())
     qDebug() << q.value(nameCol).toString(); // output all names
*/

/*
QSqlQuery query("SELECT country FROM employee");
     while (query.next()) {
         QString country = query.value(0).toString();
         qDebug() << country;
     }
*/
     return app.exec();
 }
