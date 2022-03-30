#pragma once

#include <tencentcloud/core/Credential.h>
#include <tencentcloud/core/profile/ClientProfile.h>
#include <tencentcloud/core/profile/HttpProfile.h>
#include <tencentcloud/iotexplorer/v20190423/IotexplorerClient.h>
#include <tencentcloud/iotexplorer/v20190423/model/CallDeviceActionSyncRequest.h>
#include <tencentcloud/iotexplorer/v20190423/model/CallDeviceActionSyncResponse.h>
#include <iostream>
#include <string>
#include <vector>

using namespace TencentCloud;
using namespace TencentCloud::Iotexplorer::V20190423;
using namespace TencentCloud::Iotexplorer::V20190423::Model;
using namespace std;


class IoTPlaform{

public:
    IoTPlaform();
    ~IoTPlaform();

    bool CallGrapImage(const std::string& _deviceName);

protected:
    IotexplorerClient* client;
    std::string deviceName;

};