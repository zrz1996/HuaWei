#华为软件精英挑战赛

代码远程仓库。
##checker
* unix环境自动评测脚本，主要过程用python编写，需要调用[easyprocess](https://github.com/ponty/easyprocess#id6)。安装代码如下：
```
sudo apt-get install python-pip
sudo pip install EasyProcess
```
* testcase文件夹保存测试样例，文件名为：
	* aN.txt: topo.csv
	* bN.txt: demand.csv
	* sampleN.txt: 本组测试样例的答案，可以为空文件
	
	其中N用样例组数代替，比如第一组样例的文件名为a1.txt，b1.txt，sample1.txt。
	
* result文件夹保存出现结果错误的运行结果，文件名为resultN.txt，其中N用样例组数代替。
* 提交的代码future_net应放在本目录下，会自动编译。
* checker文件夹中check.cpp会计算解的代价，可以判断是否访问过所有关键点，但不会判断路径是否连续以及是否经过S和T。
* score的计算方式是每个测试点满分10分，得分为(用户程序的cost/sample的cost)*10。如果比sampleN.txt的解优则得10分，同时会将更优的解更新为sampleN.txt。
* 运行方式为```./test.sh```。会输出每个点的情况和得分。