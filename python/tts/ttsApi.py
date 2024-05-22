import edge_tts
import asyncio

async def text_to_mp3_file_async(text, voice='zh-CN-YunyangNeural', rate='-4%', volume='+0%', filepath='./hello.mp3'):
    tts = edge_tts.Communicate(text=text, voice=voice, rate=rate, volume=volume)
    await tts.save(filepath)

def text_to_mp3_file(text, voice='zh-CN-YunyangNeural', rate='-4%', volume='+0%', filepath='./hello.mp3'):
    asyncio.run(text_to_mp3_file_async(text, voice, rate, volume, filepath))

if __name__ == '__main__':
    text_to_mp3_file("你好，这是一条测试")