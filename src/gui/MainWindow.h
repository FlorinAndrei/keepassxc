/*
 *  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSX_MAINWINDOW_H
#define KEEPASSX_MAINWINDOW_H

#include <QActionGroup>
#include <QMainWindow>
#include <QSystemTrayIcon>

#include "core/SignalMultiplexer.h"
#include "gui/DatabaseWidget.h"
#include "gui/Application.h"

namespace Ui {
    class MainWindow;
}

class InactivityTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void openDatabase(const QString& fileName, const QString& pw = QString(),
                      const QString& keyFile = QString());
    void appExit();
    void displayGlobalMessage(const QString& text, MessageWidget::MessageType type, bool showClosebutton = true);
    void displayTabMessage(const QString& text, MessageWidget::MessageType type, bool showClosebutton = true);
    void hideGlobalMessage();
    void showYubiKeyPopup();
    void hideYubiKeyPopup();

protected:
     void closeEvent(QCloseEvent* event) override;
     void changeEvent(QEvent* event) override;

private slots:
    void setMenuActionState(DatabaseWidget::Mode mode = DatabaseWidget::None);
    void updateWindowTitle();
    void showAboutDialog();
    void switchToDatabases();
    void switchToSettings();
    void switchToPasswordGen(bool enabled);
    void switchToNewDatabase();
    void switchToOpenDatabase();
    void switchToDatabaseFile(QString file);
    void switchToKeePass1Database();
    void closePasswordGen();
    void databaseStatusChanged(DatabaseWidget *dbWidget);
    void databaseTabChanged(int tabIndex);
    void openRecentDatabase(QAction* action);
    void clearLastDatabases();
    void updateLastDatabasesMenu();
    void updateCopyAttributesMenu();
    void showEntryContextMenu(const QPoint& globalPos);
    void showGroupContextMenu(const QPoint& globalPos);
    void saveToolbarState(bool value);
    void rememberOpenDatabases(const QString& filePath);
    void applySettingsChanges();
    void trayIconTriggered(QSystemTrayIcon::ActivationReason reason);
    void hideWindow();
    void toggleWindow();
    void lockDatabasesAfterInactivity();
    void repairDatabase();
    void hideTabMessage();

private:
    static void setShortcut(QAction* action, QKeySequence::StandardKey standard, int fallback = 0);

    static const QString BaseWindowTitle;

    void saveWindowInformation();
    bool saveLastDatabases();
    void updateTrayIcon();
    bool isTrayIconEnabled() const;

    const QScopedPointer<Ui::MainWindow> m_ui;
    SignalMultiplexer m_actionMultiplexer;
    QAction* m_clearHistoryAction;
    QAction* m_searchWidgetAction;
    QActionGroup* m_lastDatabasesActions;
    QActionGroup* m_copyAdditionalAttributeActions;
    QStringList m_openDatabases;
    InactivityTimer* m_inactivityTimer;
    int m_countDefaultAttributes;
    QSystemTrayIcon* m_trayIcon;

    Q_DISABLE_COPY(MainWindow)

    bool appExitCalled;
};

#define KEEPASSXC_MAIN_WINDOW (qobject_cast<Application*>(qApp) ? \
                               qobject_cast<MainWindow*>(qobject_cast<Application*>(qApp)->mainWindow()) : nullptr)

#endif // KEEPASSX_MAINWINDOW_H
