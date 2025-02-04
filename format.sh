echo -e "--- start encode conv ---"
python3 ./Scripts/Format/EncodeConv.py Source/Example
python3 ./Scripts/Format/EncodeConv.py Source/MediaEngine
python3 ./Scripts/Format/EncodeConv.py Source/EmptyApp
python3 ./Scripts/Format/EncodeConv.py Source/Sandbox
python3 ./Scripts/Format/EncodeConv.py Source/DustImageViewer
echo -e "--- finish encode conv ---"

echo -e "\n"

echo -e "--- start clang-format ---"
python3 ./Scripts/Format/FormatFile.py Source/Example
python3 ./Scripts/Format/FormatFile.py Source/MediaEngine
python3 ./Scripts/Format/FormatFile.py Source/EmptyApp
python3 ./Scripts/Format/FormatFile.py Source/Sandbox
python3 ./Scripts/Format/FormatFile.py Source/DustImageViewer
echo -e "--- finish clang-format ---"
