/*
 * demo.cpp
 *
 *  Created on: 2017年10月30日
 *      Author: lambdaji
 */

#include "DarwinAccelerator.h"
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>

using namespace std;
using namespace boost;

DEFINE_string(log_dir, "/dockerdata/lambdaji/ml_packages/DarwinAccelerator/log/","log_dir");
DEFINE_string(hash_type, "MurmurHash CityHash MD5","hash type valid:{MurmurHash,CityHash,MD5}");
DEFINE_int32(shuffle, 1,"is shuffle");
DEFINE_int32(layers, 3,"how many layers");

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);
  FLAGS_colorlogtostderr = true; //输出彩色日志到stderr

  cout << "log_dir: " << FLAGS_log_dir << endl;
  cout << "hash type: " << FLAGS_hash_type << endl;
  cout << "shuffle: " << FLAGS_shuffle << endl;
  cout << "layers: " << FLAGS_layers << endl;

  DarwinAccelerator da;
  char buf[1024];
  string in_f = FLAGS_log_dir+"guid.txt";
  ifstream ifs(in_f.c_str());
  string ou_f = FLAGS_log_dir+FLAGS_hash_type+"_stat.txt";
  ofstream ofs(ou_f.c_str(),ios::app);

  ReqInfo req_info;
  req_info.set_layers(FLAGS_layers);
  req_info.set_shuffle(FLAGS_shuffle);
  RspInfo rsp_info;

  boost::unordered_map<string,uint32_t> stat_map;
  auto m_iter = stat_map.begin();
  while(ifs.getline(buf,1024))
  {
	  rsp_info.Clear();
	  req_info.set_sguid(buf);
	  if (FLAGS_hash_type == "MurmurHash") {
		  da.doMurmurHash(req_info,rsp_info);
	  } else if(FLAGS_hash_type == "CityHash") {
		  da.doCityHash(req_info,rsp_info);
	  } else {
		  da.doMD5Hash(req_info,rsp_info);
	  }

	  stringstream ss;
	  ss.str("");
	  for(size_t i = 0; i < rsp_info.exp_info_size(); i++)
	  {
		  const RspInfo_ExpLayerInfo& layer = rsp_info.exp_info(i);
		  ss << layer.exp_id() << "_";
	  }
	  m_iter = stat_map.find(ss.str());
	  if(m_iter != stat_map.end())
		  m_iter->second += 1;
	  else
		  stat_map[ss.str()] = 1;
  }

  for(m_iter = stat_map.begin(); m_iter != stat_map.end();m_iter++)
  {
	  ofs << m_iter->first << "|" << m_iter->second << endl;
	  //LOG(INFO) << m_iter->first << "|" << m_iter->second;
  }

  google::ShutdownGoogleLogging();
  return 0;
}
