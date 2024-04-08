## For all developers
Resources文件夹请放在Qt Creator编译后生成的exe的上层目录<br>
例如，若'''build-GunshipVPet-Desktop_Qt_6_6_0_MSVC2019_64bit-Release\Release\xxx.exe'''，生成的exe在Release文件夹内，Resources就放在'''build-GunshipVPet-Desktop_Qt_6_6_0_MSVC2019_64bit-Release\Resources'''目录下，只有如此才能正确读取，后续可以考虑修改文件读取的路径