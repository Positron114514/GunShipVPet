# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass

# 用于初始化 api.json
# Todo: 加载其他模型api的接口

import json


def init_wenxin_api():
    wenxin_api_key = input("Enter wenxin_api_key: ")
    wenxin_secret_key = input("Enter wenxin_secret_key: ")
    api_key = {
        "wenxinApiKey": wenxin_api_key,
        "wenxinSecretKey": wenxin_secret_key
    }

    api_json_file = json.dumps(api_key)
    f = open("api.json", "w", encoding="utf-8")
    f.write(api_json_file)
    print("Saved successfully")
    f.close()


# Todo: 加载其他模型api, 添加到 json file 里


if __name__ == "__main__":
    init_wenxin_api()
