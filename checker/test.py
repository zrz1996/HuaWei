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
	print "\033[1;92m" + "testcase" + str(testcaseId) + ":" + "\033[0m";
	topo_name = testcase_dir + "a" + str(testcaseId) + ".txt";
	demand_name = testcase_dir + "b" + str(testcaseId) + ".txt";
	sample_name = testcase_dir + "sample" + str(testcaseId) + ".txt";
	result_name = result_dir + "result" + str(testcaseId) + ".txt";

def run():
	global topo_name, demand_name, result_name, proc_dir;
	command = proc_dir + "future_net " + topo_name + " " + demand_name + " " + result_name;
	t0 = time.time();
	proc = EasyProcess(command).call(timeout = 10);
	t1 = time.time();
	RunResult = proc.return_code;
	RunTime = t1 - t0;
	print RunResult;
	if RunResult >= 0:
		print "run successfully!"
		RunResult = 0;
	else:
		print "runtime error!"
		RunResult = -1;
	print "run time: %.2fms" % float(RunTime * 1000);
	return RunResult;

def check(RunResult):
	if RunResult < 0:
		print "\033[1;91m" + "score: 0" + "\033[0m";
		return 0;
	global topo_name, demand_name, result_name, sample_name;
	command = "./checker/check " + topo_name + " " + demand_name + " " + result_name;
	user_result = int(EasyProcess(command).call().stdout);
	if user_result == 0:
		print "result error!"
		print "\033[1;91m" + "score: 0" + "\033[0m";
		return 0;
	else:
		print "cost: " + str(user_result);
		command = "./checker/check " + topo_name + " " + demand_name + " " + sample_name;
		sample_result = int(EasyProcess(command).call().stdout);
		print "sample cost: " + str(sample_result);
		ratio = float(sample_result) * 1.0 / user_result * 10.0;
		if (sample_result == 0) or (sample_result > user_result):
			command = "cp " + result_name + " " + sample_name;
			os.system(command);
			ratio = 10.0;
		os.system("rm " + result_name);
		print "\033[1;91m" + "score: " + "%.2f" % ratio + "\033[0m";
		return ratio;

def main_loop():
	testcaseNum = 0;
	testfile = os.listdir("./testcase/");
	for f in testfile:
		if f[0] == 'a':
			testcaseNum = testcaseNum + 1;
	score = 0.0;
	for i in xrange(1, testcaseNum + 1):
		init(i);
		score += check(run());
	print "\033[1;91m" + "total score: " + "%.2f" % score + "\033[0m";

if __name__ == '__main__':
	main_loop();
