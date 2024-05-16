# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass

import os
import requests
import json
# from dotenv import load_dotenv, find_dotenv
from requests.exceptions import JSONDecodeError


def load_wenxin_api_key():
    """
    解析 api.json 中的文心一言 apikey 和 secretKey
    返回值: 一个列表, 第0项为 apikey, 第一项为 secretCode
    (不知道合不合理)
    """
    api_file_path = "api.json"

    # 检查文件是否存在
    if not os.path.exists(api_file_path):
        raise FileNotFoundError("api.json 文件未找到。")

    try:
        # 尝试打开并读取文件
        with open(api_file_path, 'r') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        raise ValueError(f"api.json 文件格式错误: {e}")

        # 获取 API 密钥和秘密键
    apikey = data.get("wenxinApiKey")
    secretkey = data.get("wenxinSecretKey")

    # 检查是否成功获取到密钥和秘密键
    if not apikey or not secretkey:
        raise ValueError("api.json 文件中缺少 API 密钥或秘密键。")

    return apikey, secretkey


def get_access_token(apikey, secretkey):
    """
    使用 API Key，Secret Key 获取access_token，替换下列示例中的应用API Key、应用Secret Key
    """
    # apikey, secretkey = load_wenxin_api_key()

    # 指定网址
    url = f"https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id={apikey}&client_secret={secretkey}"

    # 设置 POST 访问的 headers
    headers = {
        'Content-Type': 'application/json',
        'Accept': 'application/json'
    }

    # 通过 POST 访问获取账户对应的 access_token
    response = requests.post(url, headers=headers)

    # 检查响应状态码
    if response.status_code == 200:
        try:
            # 尝试解析 JSON
            return response.json().get("access_token")
        except JSONDecodeError as e:
            print(f"解析 JSON 失败: {e}")
            print("响应内容：", response.text)
            return "loadJsonFailed"
    else:
        print(f"请求失败，状态码：{response.status_code}")
        print("响应内容：", response.text)
        return "requestFailed"


def get_completion(prompt: str, access_token, temperature=0.1):
    """一个封装文心大模型接口的函数，参数为 Prompt，返回对应结果

    Args:
        prompt (str): 模型的输入
        access_token (str): "密匙".
        temperature (int, optional): Defaults to 0.

    Returns:
        response
    """
    url = f"https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions?access_token={access_token}"
    # 配置 POST 参数
    payload = json.dumps({
        "messages": [
            {
                "role": "user",  # user prompt
                "content": "{}".format(prompt)  # 输入的 prompt
            }
        ],
        "temperature": temperature
    })
    headers = {
        'Content-Type': 'application/json'
    }
    # 发起请求
    response = requests.request("POST", url, headers=headers, data=payload)
    print(response.text)
    # 返回的是一个 Json 字符串
    js = json.loads(response.text)

    return js["result"]


if __name__ == "__main__":
    print(get_completion('你好', get_access_token()))
