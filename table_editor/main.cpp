
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include <QDebug>

#include <QTranslator>
#include <QMessageBox>

#include "win/main_window.h"

#include "data.h"

bool loadTraslation(QTranslator& translator)
{
    const char* aszTranslationDirs[] = {
        ".", "./CsvTableEditor", "../translations", ":/translations", 0
    };

    for (
        const char** ppszDir = aszTranslationDirs;
        *ppszDir != 0; ++ ppszDir) {
        bool bTranslationLoaded = translator.load(QLocale::system(), "lang", "_", *ppszDir);
        //        bool bTranslationLoaded = translator.load("lang_ru_RU");

        if (bTranslationLoaded) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    bool bTranslationLoaded = loadTraslation(translator);

    if (bTranslationLoaded) {
        app.installTranslator(&translator);
    } else {
        QMessageBox::warning(0, "Translation", "Not loaded");
    }

    QScopedPointer<MainWindow> mainWindow(new MainWindow);
    mainWindow->show();

    return app.exec();

    return 0;
}
