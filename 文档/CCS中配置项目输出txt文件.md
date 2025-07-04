# CCS中配置项目输出txt文件

### 1. 工具栏Project

![image-20240727152353002](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202507041543175.png)

### 2. 选择最下面Properties

![image-20240727152555146](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202507041543176.png)

### 3. Build -> MSP430 Hex Utility  -> 勾选Enable 'MSP430 Hex Utility'

![image-20240727153018053](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202507041543177.png)

### 4. Options Format Output -> Output format ->  选择最后一个：TI-TXT hex ( -- ti_txt)

![image-20240727153322600](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202507041543178.png)

### 5. 再次Build

![image-20240727153438222](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202507041543179.png)

console窗口显示的target后缀名显示为txt则以上步骤成功。

![image-20240727153707809](https://raw.githubusercontent.com/undefined-0/image-store/main/PicGo/202507041543180.png)

注：此txt文件在工程目录下的Debug文件夹内。
