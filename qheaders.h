#ifndef QHEADERS_H
#define QHEADERS_H

// qDebug Macros
#define QT_INTERFACE_LOG "[QT]user interface:"
#define QT_BACKGROUND_LOG "[QT]background thread:"
#define QT_DEBUG_OUTPUT "[QT]debug output:"
#define QT_GL_CAPTURE_LOG "[OpenGL]thread:"

// Application based Macros
#define APP_NAME "GunshipVPet"
#define MAX_MODEL_WIDTH 500
#define MIN_MODEL_WIDTH 140
#define DEFAULT_MODEL_WIDTH 250
#define MODEL_PROPORTION 1.2
#define DEFAULT_FPS 30
#define DEFAULT_MODEL 0
#define LOG_DIR "log.txt"
#define CONFIG_DIR "config.json"

// System based macros
#define REG_AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

// Windows native headers
#include <windows.h>
#include <dwmapi.h>
#include <WinUser.h>
#include <shellapi.h>
#include <direct.h>
#include <io.h>

// OpenGL headers
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

// SDK headers

// Qt headers
#include <QDialog>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QTimer>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QPoint>
#include <QFlags>
#include <QCheckBox>
#include <QSlider>
#include <QStringList>
#include <QComboBox>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument> // 解析Json
#include <QJsonValue>
#include <QJsonParseError>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QMutex>
#include <QDateTime>
#include <QLoggingCategory>
#include <QFileInfo>
#include <QFileInfoList>
#include <QStandardPaths>
#include <QSettings>
#include <QDesktopServices>
#include <QMessageBox>


#endif // QHEADERS_H
