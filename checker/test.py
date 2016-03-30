# coding=utf-8
import os, sys, subprocess
import time
from easyprocess import EasyProcess

topo_name = "";
demand_name = "";
result_name = "";
sample_name = "";
testcase_dir = "./testcase/";
proc_dir = "./"
result_dir = "./result/";

def init(testcaseId):
	global topo_name, demand_name, sample_name, result_name, testcase_dir, result_dir;
	print "testcase" + str(testcaseId) + ":";
	topo_name = testcase_dir + "topo" + str(testcaseId) + ".csv";
	demand_name = testcase_dir + "demand" + str(testcaseId) + ".csv";
	sample_name = testcase_dir + "sample" + str(testcaseId) + ".csv";
	result_name = result_dir + "result" + str(testcaseId) + ".csv";

def run():
	global topo_name, demand_name, result_name, proc_dir;
	command = proc_dir + "future_net " + topo_name + " " + demand_name + " " + result_name;
	t0 = time.time();
	proc = EasyProcess(command).call(timeout = 10);
	t1 = time.time();
	RunResult = proc.return_code;
	RunTime = t1 - t0;
	if RunResult >= 0:
		print "run successfully!"
		RunResult = 0;
	else:
		print "runtime error!"
		RunResult = -1;
	print "run time: " + str(RunTime * 1000);
	return RunResult;

def check():
	global topo_name, demand_name, result_name, sample_name;
	command = "./checker/check " + topo_name + " " + demand_name + " " + result_name;
	user_result = int(EasyProcess(command).call().stdout);
	if user_result == 0:
		print "result error!"
	else:
		print "cost: " + str(user_result);
		command = "./checker/check " + topo_name + " " + demand_name + " " + sample_name;
		sample_result = int(EasyProcess(command).call().stdout);
		print "sample cost: " + str(sample_result);
		if (sample_result == 0) or (sample_result > user_result):
			command = "cp " + result_name + " " + sample_name;
			os.system(command);
		os.system("rm " + result_name);



def main_loop(testcaseNum):
	for i in xrange(1, testcaseNum + 1):
		init(i);
		if run() == 0:
			check();

if __name__ == '__main__':
	main_loop(1);
