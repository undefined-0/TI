# CCS中配置项目输出txt文件

### 1. 工具栏Project

![image-20240727152353002](CCS中配置项目输出txt文件.assets/image-20240727152353002.png)

### 2. 选择最下面Properties

![image-20240727152555146](CCS中配置项目输出txt文件.assets/image-20240727152555146.png)

### 3. Build -> MSP430 Hex Utility  -> 勾选Enable 'MSP430 Hex Utility'

![image-20240727153018053](CCS中配置项目输出txt文件.assets/image-20240727153018053.png)

### 4. Options Format Output -> Output format ->  选择最后一个：TI-TXT hex ( -- ti_txt)

![image-20240727153322600](CCS中配置项目输出txt文件.assets/image-20240727153322600.png)

### 5. 再次Build

![image-20240727153438222](CCS中配置项目输出txt文件.assets/image-20240727153438222.png)

console窗口显示的target后缀名显示为txt则以上步骤成功。

![image-20240727153707809](CCS中配置项目输出txt文件.assets/image-20240727153707809.png)

注：此txt文件在工程目录下的Debug文件夹内。
