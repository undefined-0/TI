# CCS工程添加头文件路径

### 1. 右键工程名，选择最后一项 Properties

![image-20240727210113022](CCS工程添加头文件路径.assets/image-20240727210113022.png)

### 2. Build -> Include Options -> 点击右侧添加按钮 -> 输入要包含的头文件路径

![image-20240727210947311](CCS工程添加头文件路径.assets/image-20240727210947311.png)

注：若你的工程文件夹名为test，想要引入test/src文件夹的头文件，则在④处输入：`${PROJECT_ROOT}/src`