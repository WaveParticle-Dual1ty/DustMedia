echo -e "--- start encode conv ---"
python ./Scripts/Format/EncodeConv.py Source/Example
python ./Scripts/Format/EncodeConv.py Source/MediaEngine
python ./Scripts/Format/EncodeConv.py Source/EmptyApp
python ./Scripts/Format/EncodeConv.py Source/Sandbox
python ./Scripts/Format/EncodeConv.py Source/DustImageViewer
echo -e "--- finish encode conv ---"

echo -e "\n"

echo -e "--- start clang-format ---"
python ./Scripts/Format/FormatFile.py Source/Example
python ./Scripts/Format/FormatFile.py Source/MediaEngine
python ./Scripts/Format/FormatFile.py Source/EmptyApp
python ./Scripts/Format/FormatFile.py Source/Sandbox
python ./Scripts/Format/FormatFile.py Source/DustImageViewer
echo -e "--- finish clang-format ---"
