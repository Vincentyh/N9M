/*
* Copyright (c) 2017,  重庆锐明信息技术有限公司软件一部
* All rights reserved.
*
* 文件名称：QueryHandle.h
* 文件标识：
* 摘 要：查询处理模块的头文件
*
* 当前版本：1.0
* 作 者：杨杭
* 完成日期：2017年08月30日
*
*/


#ifndef QUERYHANDLE_H
#define QUERYHANDLE_H
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

typedef struct
{
    char inquire_kind; //查询种类 0代表H264，后面可做扩展用
    char inquire_type;//查询数据类型 0-查询数据是否存在，1-返回帧头数据
    string inquire_data; //要查询的数据和返回的结果，串口解析模块往里填充查询命令，264查询模块往里填充查找结果
}InquireInterface;

class QueryHandle
{
public:
    QueryHandle();
    ~QueryHandle();
    void handle_msg();

private:
    //char *rev_msg; //用于接收CS模块发送的消息
    //string send_msg; //用于给CS发送消息
   // UdsClient *uds_client; //与CS通信进行通信的类
    void print_queryby_ari_time();
    void print_input_ari_time();
    void print_input_time();
    void print_input_moment();

    int find_char(string &input, char fchar);  //查找某个字符串中，包含fchar的个数
    int check_input_1(string &input, int type);  //查询是否存在视频数据时，判断用户输入是否正确,正确返回0
    int check_input_2(string &input);  //查询视频帧头时，判断用户输入是否正确，正确返回0
    void print_result(string &input, int print_type); //根据用户的输入查询方式，打印返回的查询结果
    void split_string(string &input);


    InquireInterface inquireInterface;

    int input_type; //用于判定用户的输入查询方式
    vector<string> result_buf;

};

#endif // QUERYHANDLE_H
