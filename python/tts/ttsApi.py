import edge_tts
import asyncio

async def text_to_mp3_file(text, voice='zh-CN-YunyangNeural', rate='-4%', volume='+0%', filepath='./hello.mp3',):
    tts = edge_tts.Communicate(text=text, voice=voice, rate=rate, volume=volume)
    await tts.save(filepath)


if __name__ == '__main__':
    asyncio.run(text_to_mp3_file("你好，这是一条测试"))