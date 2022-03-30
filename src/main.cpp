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

using namespace TencentCloud;
using namespace TencentCloud::Iotexplorer::V20190423;
using namespace TencentCloud::Iotexplorer::V20190423::Model;
using namespace std;

using namespace rapidjson;

int main(int argc, char* argv[]) {

    Credential cred = Credential("", "");

    HttpProfile httpProfile = HttpProfile();
    httpProfile.SetEndpoint("iotexplorer.tencentcloudapi.com");

    ClientProfile clientProfile = ClientProfile();
    clientProfile.SetHttpProfile(httpProfile);
    IotexplorerClient client = IotexplorerClient(cred, "ap-guangzhou", clientProfile);


    {
            DescribeDeviceRequest req = DescribeDeviceRequest();
            
            req.SetProductId("OLER6OOJDJ");
            req.SetDeviceName("123");

            auto outcome = client.DescribeDevice(req);
            if (!outcome.IsSuccess())
            {
                cout << outcome.GetError().PrintAll() << endl;
                return -1;
            }
            DescribeDeviceResponse resp = outcome.GetResult();
            //cout << resp.ToJsonString() << endl;

            rapidjson::Document document;
            document.Parse(resp.ToJsonString().c_str());

            const auto& obj = document["Device"].GetObject();

            //std::cout << "status : " << document["Device"].GetObject().MemberBegin();
            for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr)
            {
                //printf("Type of member %s => %d\n", itr->name.GetString(), itr->value.IsNumber());
            }

            {
                Value::ConstMemberIterator itr = obj.FindMember("Status");
                if (itr != obj.MemberEnd())
                    printf("设备[%s] status : %s\n", req.GetDeviceName().c_str(), itr->value.GetInt() > 0 ? "已连接" : "未连接");
            }

    return 0;


    }





    CallDeviceActionSyncRequest req = CallDeviceActionSyncRequest();
    
    req.SetProductId("OLER6OOJDJ");
    req.SetDeviceName("test2");
    req.SetActionId("grapCamera");
    req.SetInputParams("{\"camera_id\": 0}");

    auto outcome = client.CallDeviceActionSync(req);
    if (!outcome.IsSuccess())
    {
        cout << outcome.GetError().PrintAll() << endl;
        return -1;
    }
    CallDeviceActionSyncResponse resp = outcome.GetResult();
    //cout << resp.ToJsonString() << endl;

    int res = CommonTools::download_file("http://r9emzef08.hn-bkt.clouddn.com/pic-1648543280.jpg?e=1648546881&token=MoVNHexgySseNvZuQvjR-aBPsRnOST06X1YVzXW9:cDQnr9F_teCl14WrRAClT_mSMXU=", "./1.jpg");
    //cout << "调用[%s] 结果:" << res << endl;
    printf("调用[%s] 结果:[%d] : 调用成功,图片保存为: %s\n", "grapCamera", res, "./output/1.jpg");
    return 0;
}