#include "IoTPlaform.hpp"

IoTPlaform::IoTPlaform() : client(nullptr) {

    Credential cred = Credential("AKIDwkNo0xf8ML5ZnnY6PUJsCG4dy5wXw85n", "VkkUxBBxShgRyGLCnAICqFNGtGOIxNXS");

    HttpProfile httpProfile = HttpProfile();
    httpProfile.SetEndpoint("iotexplorer.tencentcloudapi.com");

    ClientProfile clientProfile = ClientProfile();
    clientProfile.SetHttpProfile(httpProfile);
    client = new IotexplorerClient(cred, "ap-guangzhou", clientProfile);

}

bool IoTPlaform::CallGrapImage(const std::string& _deviceName) {
    CallDeviceActionSyncRequest req = CallDeviceActionSyncRequest();
    
    req.SetProductId("OLER6OOJDJ");
    req.SetDeviceName("test2");
    req.SetActionId("grapCamera");
    req.SetInputParams("{\"camera_id\": 0}");

    auto outcome = client->CallDeviceActionSync(req);
    if (!outcome.IsSuccess())
    {
        cout << outcome.GetError().PrintAll() << endl;
        return false;//return -1
    }
    CallDeviceActionSyncResponse resp = outcome.GetResult();
    cout << resp.ToJsonString() << endl;

    return true;
}

IoTPlaform::~IoTPlaform() {
    delete client;
    client = nullptr;
}