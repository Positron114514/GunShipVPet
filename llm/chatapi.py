# This Python file uses the following encoding: utf-8

# if __name__ == "__main__":
#     pass

import os
import requests
import json
from dotenv import load_dotenv, find_dotenv

def load_wenxin_api_key():
    """
    解析 api.json 中的文心一言 apikey 和 secretKey
    返回值: 一个列表, 第0项为 apikey, 第一项为 secretCode
    (不知道合不合理)
    """
    with open("api.json") as f:
        data = json.load(f)

    return [data.get("wenxinApiKey"), data.get("wenxinSecretKey")]


def get_access_token():
    """
    使用 API Key，Secret Key 获取access_token，替换下列示例中的应用API Key、应用Secret Key
    """
    pass


def get_completion(prompt: str, access_token, temperature = 0.1):
    """一个封装文心大模型接口的函数，参数为 Prompt，返回对应结果

    Args:
        prompt (str): 模型的输入
        access_token (str): 密匙".
        temperature (int, optional): Defaults to 0.

    Returns:
        response
    """
    pass
