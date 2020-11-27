#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "dirmodel.h"
#include "listfiles.h"
#include "analyzefile.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QCoreApplication::setApplicationName("Cpp Code Analyzer");
    QCoreApplication::setOrganizationDomain("No organisation");
    QCoreApplication::setOrganizationName("No organisation");
    QCoreApplication::setApplicationVersion("0.1");

    QQmlApplicationEngine engine;

    DirModel dirModel;
    engine.rootContext()->setContextProperty("dirModel", &dirModel);

    ListFiles listFiles;
    engine.rootContext()->setContextProperty("listFiles", &listFiles);

    AnalyzeFile analyzeFile;
    analyzeFile.start_analyzing_file("/home/szymon/git/cpp-code-analyzer/analyzefile.cpp");
    qDebug() << "Lines: " << analyzeFile.lines();
    qDebug() << "Lines no empty: " << analyzeFile.lines_no_empty();
    qDebug() << "Lines no comments: " << analyzeFile.lines_no_comments();

//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
