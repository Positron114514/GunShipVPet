#ifndef QHEADERS_H
#define QHEADERS_H

// Macros
#define QT_INTERFACE_LOG "[QT]user interface:"
#define QT_BACKGROUND_LOG "[QT]background thread:"
#define QT_DEBUG_OUTPUT "[QT]debug output:"

// Windows native headers
#include <windows.h>
#include <dwmapi.h>

// OpenGL headers
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

// SDK headers

// Qt headers
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

#endif // QHEADERS_H
