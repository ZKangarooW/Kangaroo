# JoanLab
 JoanLab
/************************************************************************************/
2022.02.09
1.DB2200：重写写了一遍，梯度和记忆都正常
/*
*****************************************************************
版本更改
2022-02-15：加了开机记忆模式
2022-03-29：改了NTC的阻止，和单加热的通用的，将显示优化了，时间冒号闪烁和图标闪烁，将P模式的操作改了！修复了时间清零改P模式不回跳出----，改了时间清零启动图标不显示
2022-03-31：烧录第一次数值出错，发现param里的初始化有问题，然后p模式调时闪烁问题
2022-03-31：老化测试之后开机数值改变，p-1成最后一次的数值
2022-07.12：记忆的参数变量太小了，超过65535S就错误了改成了int
2022-08.15：代码整理
2022-10.21：温度校准完成，增加报警功能，闪烁bug修复
*****************************************************************
*/
