# D3D9 Blank Proxy
This dll serves as a completely blank 'proxy' dll for d3d9. The purpose of this dll is to purposefully break Origin in-game (from EA) overlay. By using this proxy dll, the byte pattern Origin looks for can't be found, and Origin in-game overlay fails to hook into the process. This dll doesn't do anything beyond simply loading the real d3d9.dll file.

How to install:
Put next to your game's binary file. For Mass effect games, it's in the Binaries folder under the root of the game directory. For ME3 specifically, it's in the win32 subdirectory.
