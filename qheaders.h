#ifndef QHEADERS_H
#define QHEADERS_H

// qDebug Macros
#define QT_INTERFACE_LOG "[QT]user interface:"
#define QT_BACKGROUND_LOG "[QT]background thread:"
#define QT_DEBUG_OUTPUT "[QT]debug output:"

// Application based Macros
#define MAX_MODEL_WIDTH 500
#define MIN_MODEL_WIDTH 200
#define DEFAULT_MODEL_WIDTH 300
#define MODEL_PROPORTION 1.2
#define DEFAULT_FPS 30
#define DEFAULT_MODEL 0

// Windows native headers
#include <windows.h>
#include <dwmapi.h>

// OpenGL headers
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

// SDK headers

// Qt headers
#include <QDialog>
#include <QWidget>
#include <QOpenGLWidget>
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

#endif // QHEADERS_H
