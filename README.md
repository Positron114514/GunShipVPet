# GunshipVPet 虚拟桌宠 

<img src="./resources/icons/logo-tmp.png" width = "50" height = "50" alt="Logo" align=center />

**by NJU EL 武装直升机组**

这是参与2024 NJU EL程序设计大赛交互组的作品，使用Qt和Cubism Live2D Native SDK构建

*Still WIP*

<br>

## About this project

该项目旨在使用Qt与Live2D构建一个可用的虚拟桌宠程序，基于Cubism开源的demo工程修改与完善；
并与*文心一言* API进行对接，实现与虚拟桌宠的实用性交互（如聊天、文本生成等功能）；
同时，计划使用*bert-vits（暂定）* 训练声音库，并实现TTS（Text to speak）功能

**Qt C++ SDK**

应用核心框架使用Qt6与qmake构建，并根据移植需要将Live2D demo工程中相关实现使用Qt提供的库与成员函数重载、改写与实现；
使用继承自QOpenGLWidget的自定义类接入Live2D图形渲染，并使用Qt标准控件实现除图形渲染外的界面与功能

工程需要使用MSVC2019编译

**Cubism Live2D Native SDK**

工程使用Cubism Live2D Native SDK完成模型渲染与交互功能，基于demo工程修改而来，根据需要修改了部分实现

**LLM API接入**

计划使用Python实现大语言模型API接入，并用Qt实现与Python程序交互的数据接口与交互界面

ps: 项目使用 python 3.8.10 进行大模型接入, 因此需要安装 python3.8.10 在工程目录下

**QSS美化**

移植自[QtMaterial](https://github.com/UN-GCPDS/qt-material)，并根据UI开发需要修改了qss样式表中内容

<br>

*更多功能开发与规划中* 详见[TodoList](https://github.com/Positron114514/GunShipVPet/blob/master/todolist.md)

<br>

## About Us

队长

[Positron Liu](https://github.com/Positron114514)

队员

[Aritx Zhou](https://github.com/AritxOnly)

[Haoming Liu](https://github.com/shadowpromax2)

[Pythia Han](https://github.com/Pythia111)
