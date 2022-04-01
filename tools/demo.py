import subprocess
import json

r = subprocess.Popen(['/home/hehao/onebinary/remoteControl/IoT-MQTT-controller-cpp/build/remoteControl', 'pi001', '--status'], stdout=subprocess.PIPE, stderr=subprocess.PIPE) #List files on a linux system. Equivalent of dir on windows.
output, errs = r.communicate()

if len(output.decode()) > 0:
    print(json.loads(output.decode()))


if len(errs.decode()) > 0:
    print(json.loads(errs.decode()))
#os.system("../build/remoteControl")

#############################################

if len(output.decode()) == 0:
    print("err")
    exit(0)

_data = json.loads(output.decode())

print(_data.get("status"))

_status = _data.get("status")
if(_status < 0):
    #if(_data.get("msg"))
    print("status < 0")
else:
    print(_data["info"])