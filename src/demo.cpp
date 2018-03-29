/*
 * demo.cpp
 *
 *  Created on: 2017��10��30��
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

DEFINE_string(sLogDir, "/dockerdata/lambdaji/ml_packages/DarwinAccelerator/log/", "log_dir");
DEFINE_string(sHashType, "MurmurHash", "hash type valid:{MurmurHash, CityHash, MD5}");
DEFINE_int32(iShuffle, 1, "is shuffle");
DEFINE_int32(iLayers, 3, "how many layers");

int main(int argc, char **argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);
  FLAGS_colorlogtostderr = true;

  cout << "log_dir: " << FLAGS_sLogDir << endl;
  cout << "hash type: " << FLAGS_sHashType << endl;
  cout << "shuffle: " << FLAGS_iShuffle << endl;
  cout << "layers: " << FLAGS_iLayers << endl;

  //DarwinAccelerator da;
  char buf[1024];
  string in_f = FLAGS_sLogDir+"guid.txt";
  ifstream ifs(in_f.c_str());
  string ou_f = FLAGS_sLogDir+FLAGS_sHashType+"_stat.txt";
  ofstream ofs(ou_f.c_str(),ios::app);

  ReqInfo req_info;
  req_info.set_layers(FLAGS_iLayers);
  req_info.set_shuffle(FLAGS_iShuffle);
  RspInfo rsp_info;

  boost::unordered_map<string,uint32_t> stat_map;
  auto m_iter = stat_map.begin();
  while(ifs.getline(buf,1024))
  {
	  rsp_info.Clear();
	  req_info.set_sguid(buf);
	  if (FLAGS_sHashType == "MurmurHash") {
		  doMurmurHash(req_info,rsp_info);
	  } else if(FLAGS_sHashType == "CityHash") {
		  doCityHash(req_info,rsp_info);
	  } else {
		  doMD5Hash(req_info,rsp_info);
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
