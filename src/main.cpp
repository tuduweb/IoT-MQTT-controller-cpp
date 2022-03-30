#include <tencentcloud/core/Credential.h>
#include <tencentcloud/core/profile/ClientProfile.h>
#include <tencentcloud/core/profile/HttpProfile.h>
#include <tencentcloud/iotexplorer/v20190423/IotexplorerClient.h>
#include <tencentcloud/iotexplorer/v20190423/model/CallDeviceActionSyncRequest.h>
#include <tencentcloud/iotexplorer/v20190423/model/CallDeviceActionSyncResponse.h>
#include <iostream>
#include <string>
#include <vector>

#include "CommonTools.hpp"
#include "IoTPlaform.hpp"

#include <tencentcloud/core/utils/rapidjson/document.h>
#include <tencentcloud/core/utils/Utils.h>

#include "cxxopts.hpp"

using namespace TencentCloud;
using namespace TencentCloud::Iotexplorer::V20190423;
using namespace TencentCloud::Iotexplorer::V20190423::Model;
using namespace std;

using namespace rapidjson;


#include <codecvt>  
#include <string>  
  
// convert UTF-8 string to wstring  
std::wstring utf8_to_wstring(const std::string& str)  
{  
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;  
    return myconv.from_bytes(str);  
}  
  
// convert wstring to UTF-8 string  
std::string wstring_to_utf8(const std::wstring& str)  
{  
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;  
    return myconv.to_bytes(str);  
}

int main(int argc, char* argv[]) {

    cxxopts::Options options("remoteControl", "remoteControl for remote hardware device. Supported By onebinary.");

    options.add_options()
    ("help", "Print help")
    ("s,status", "Check remote device status")
    ("a,action", "publish a action", cxxopts::value<std::string>())
    ("d,saveto", "file save path", cxxopts::value<std::string>())
    //("u,update", "update app[dev]", cxxopts::value<std::string>())
    //("f,file", "File name", cxxopts::value<std::string>())
    ;

    if(argc == 1)
        return -1;
    else if(argc == 2) {
        cout << argv[1] << endl;
    }

    std::string deviceName = argv[1];

    auto result = options.parse(argc - 1, argv + 1);

    if (result.count("help"))
    {
      std::cout << options.help({"", "Group"}) << std::endl;
      exit(0);
    }


    /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Application @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

    /* System Init */
    rapidjson::Document _res;
    _res.SetObject();
    _res.AddMember("status", 0, _res.GetAllocator());


    /* TencentCloud Init */

    Credential cred = Credential("AKIDwkNo0xf8ML5ZnnY6PUJsCG4dy5wXw85n", "");

    HttpProfile httpProfile = HttpProfile();
    httpProfile.SetEndpoint("iotexplorer.tencentcloudapi.com");

    ClientProfile clientProfile = ClientProfile();
    clientProfile.SetHttpProfile(httpProfile);
    IotexplorerClient client = IotexplorerClient(cred, "ap-guangzhou", clientProfile);


    /* Device Status Check */
    if(result.count("status"))
    {
        DescribeDeviceRequest req = DescribeDeviceRequest();
        
        req.SetProductId("OLER6OOJDJ");
        req.SetDeviceName(deviceName);

        auto outcome = client.DescribeDevice(req);
        if (!outcome.IsSuccess())
        {

            _res["status"].SetInt(-2);

            rapidjson::Document _errorInfo;
            _errorInfo.SetObject();

            char _codeBuffer[100];
            int _codeLen = sprintf(_codeBuffer, "%s", outcome.GetError().GetErrorCode().c_str()); // dynamically created string.
            Value _codeBufferValue;
            _codeBufferValue.SetString(_codeBuffer, _codeLen, _errorInfo.GetAllocator());
            _errorInfo.AddMember("code", _codeBufferValue, _errorInfo.GetAllocator());

            char _msgBuffer[200];
            int _msgLen = sprintf(_msgBuffer, "%s", outcome.GetError().GetErrorMessage().c_str()); // dynamically created string.
            Value _msgBufferValue;
            _msgBufferValue.SetString(_msgBuffer, _msgLen, _errorInfo.GetAllocator());
            _errorInfo.AddMember("msg", _msgBufferValue, _errorInfo.GetAllocator());

            _res.AddMember("info", _errorInfo, _res.GetAllocator());

            StringBuffer _buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
            _res.Accept(writer);
            
            cout << _buffer.GetString() << endl;

            return -1;
        }

        DescribeDeviceResponse resp = outcome.GetResult();

        rapidjson::Document document;
        document.Parse(resp.ToJsonString().c_str());

        const auto& obj = document["Device"].GetObject();

        // for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr)
        // {
        //     //printf("Type of member %s => %d\n", itr->name.GetString(), itr->value.IsNumber());
        // }

        _res["status"].SetInt(-1);

        rapidjson::Document _errorInfo;
        _errorInfo.SetObject();

        // char _codeBuffer[100];
        // int _codeLen = sprintf(_codeBuffer, "%s", outcome.GetError().GetErrorCode().c_str()); // dynamically created string.
        // Value _codeBufferValue;
        // _codeBufferValue.SetString(_codeBuffer, _codeLen, _errorInfo.GetAllocator());
        // _errorInfo.AddMember("code", _codeBufferValue, _errorInfo.GetAllocator());

        // char _msgBuffer[200];
        // int _msgLen = sprintf(_msgBuffer, "%s", outcome.GetError().GetErrorMessage().c_str()); // dynamically created string.
        // Value _msgBufferValue;
        // _msgBufferValue.SetString(_msgBuffer, _msgLen, _errorInfo.GetAllocator());
        // _errorInfo.AddMember("msg", _msgBufferValue, _errorInfo.GetAllocator());

        // _res.AddMember("info", _errorInfo, _res.GetAllocator());

        

        Value::ConstMemberIterator itr = obj.FindMember("Status");
        if (itr != obj.MemberEnd())
        {
            _res["status"].SetInt(0);
            _errorInfo.AddMember("status", itr->value.GetInt(), _errorInfo.GetAllocator());
        }else{
            _res["status"].SetInt(-1);
            //_errorInfo.AddMember("status", itr->value.GetInt(), _errorInfo.GetAllocator());
        }
        _res.AddMember("info", _errorInfo, _res.GetAllocator());


        StringBuffer _buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
        _res.Accept(writer);

        cout << _buffer.GetString() << endl;

        return 0;

    }


    if(result.count("action")) {

        std::string actionId = result["action"].as<std::string>();

        CallDeviceActionSyncRequest req = CallDeviceActionSyncRequest();
    
        req.SetProductId("OLER6OOJDJ");
        req.SetDeviceName(deviceName);
        req.SetActionId(actionId);
        req.SetInputParams("{\"camera_id\": 0}");

        auto outcome = client.CallDeviceActionSync(req);
        if (!outcome.IsSuccess())
        {
            // //RequestId=bec777c4-6bbb-4f9a-a3b8-084825a24c59, ErrorCode=FailedOperation.Timeout, ErrorMessage=调用超时
            // //RequestId=6254ed73-15a6-4854-afd4-d47166f019d0, ErrorCode=ResourceNotFound.DeviceNotExist, ErrorMessage=设备未创建或是已删除
            //std::cout << outcome.GetError().PrintAll() << endl;
            //cout << outcome.GetError().GetErrorMessage() << outcome.GetError().GetErrorCode() << endl;

            _res["status"].SetInt(-2);

            rapidjson::Document _errorInfo;
            _errorInfo.SetObject();

            char _codeBuffer[100];
            int _codeLen = sprintf(_codeBuffer, "%s", outcome.GetError().GetErrorCode().c_str()); // dynamically created string.
            Value _codeBufferValue;
            _codeBufferValue.SetString(_codeBuffer, _codeLen, _errorInfo.GetAllocator());
            _errorInfo.AddMember("code", _codeBufferValue, _errorInfo.GetAllocator());

            char _msgBuffer[200];
            int _msgLen = sprintf(_msgBuffer, "%s", outcome.GetError().GetErrorMessage().c_str()); // dynamically created string.
            Value _msgBufferValue;
            _msgBufferValue.SetString(_msgBuffer, _msgLen, _errorInfo.GetAllocator());
            _errorInfo.AddMember("msg", _msgBufferValue, _errorInfo.GetAllocator());

            _res.AddMember("info", _errorInfo, _res.GetAllocator());

            StringBuffer _buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
            _res.Accept(writer);
            cout << _buffer.GetString() << endl;
            
            return -1;
        }

        //得到了返回结果，即调用成功
        CallDeviceActionSyncResponse resp = outcome.GetResult();

        //result to json
        rapidjson::Document document;
        document.Parse(resp.ToJsonString().c_str());

        if(document["Status"].IsNull()) {
            //"FailedOperation.ActionUnreachable 设备未响应

            _res["status"].SetInt(-1);

            rapidjson::Document _errorInfo;
            _errorInfo.SetObject();
            _errorInfo.AddMember("msg", "FailedOperation.DeviceNoResponse", _errorInfo.GetAllocator());

            _res.AddMember("info", _errorInfo, _res.GetAllocator());

            StringBuffer _buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
            _res.Accept(writer);
            cout << _buffer.GetString() << endl;
            
            return -1;
        }

        std::string _status = document["Status"].GetString();
        //cout << resp.ToJsonString() << endl;



        if(_status.find("FailedOperation") != string::npos) {
            //"FailedOperation.ActionUnreachable 设备未开机
            //cout << _status << endl;

            _res["status"].SetInt(-1);

            rapidjson::Document _errorInfo;
            _errorInfo.SetObject();
            _errorInfo.AddMember("msg", StringRef(_status.c_str()), _errorInfo.GetAllocator());
            _res.AddMember("info", _errorInfo, _res.GetAllocator());

            StringBuffer _buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
            _res.Accept(writer);
            cout << _buffer.GetString() << endl;


            return -1;
        }

        if(document["OutputParams"].IsString() && document["OutputParams"].GetStringLength() == 0) {

            _res["status"].SetInt(-1);

            rapidjson::Document _errorInfo;
            _errorInfo.SetObject();
            _errorInfo.AddMember("msg", "OutputParams is empty", _errorInfo.GetAllocator());
            _res.AddMember("info", _errorInfo, _res.GetAllocator());

            StringBuffer _buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
            _res.Accept(writer);
            cout << _buffer.GetString() << endl;

            return -1;
        }        

        string _outputParams = document["OutputParams"].GetString();
        rapidjson::Document outputDocument;
        outputDocument.Parse(_outputParams.c_str());

        //dump
        // for (Value::ConstMemberIterator itr = outputDocument.MemberBegin(); itr != outputDocument.MemberEnd(); ++itr)
        // {
        //     printf("Type of member %s => %d\n", itr->name.GetString(), itr->value.IsNumber());
        // }

        string _imageKey = outputDocument["imageKey"].GetString();
        //判断key是否带后缀, 不带后缀需要添加上

        std::string _savePath = "./";
        if(result.count("saveto")) {
            _savePath = result["saveto"].as<std::string>();
        }
        //判断目录是否存在


        //组装
        string _savedFileName = _savePath + _imageKey;

        int res = CommonTools::download_file("http://r9emzef08.hn-bkt.clouddn.com/" + _imageKey, _savedFileName);
        //cout << "调用[%s] 结果:" << res << endl;
        
        //--// printf("调用[%s] 结果:[%d] : 调用成功,图片保存为: %s\n", actionId.c_str(), res, _savedFileName.c_str());

        _res["status"].SetInt(0);

        rapidjson::Document _errorInfo;
        _errorInfo.SetObject();

        // char _codeBuffer[100];
        // int _codeLen = sprintf(_codeBuffer, "%s", outcome.GetError().GetErrorCode().c_str()); // dynamically created string.
        // Value _codeBufferValue;
        // _codeBufferValue.SetString(_codeBuffer, _codeLen, _errorInfo.GetAllocator());
        // _errorInfo.AddMember("code", _codeBufferValue, _errorInfo.GetAllocator());

        // char _msgBuffer[200];
        // int _msgLen = sprintf(_msgBuffer, "%s", outcome.GetError().GetErrorMessage().c_str()); // dynamically created string.
        // Value _msgBufferValue;
        //_msgBufferValue.SetString(_msgBuffer, _msgLen, _errorInfo.GetAllocator());
        _errorInfo.AddMember("imageKey", StringRef(_savedFileName.c_str()), _errorInfo.GetAllocator());

        _res.AddMember("info", _errorInfo, _res.GetAllocator());

        StringBuffer _buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(_buffer);
        _res.Accept(writer);
        
        cout << _buffer.GetString() << endl;

        return 0;
    }


    return -1;
}