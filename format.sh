echo -e "--- start encode conv ---"
python ./Scripts/Format/EncodeConv.py Source/MediaPlayer
python ./Scripts/Format/EncodeConv.py Source/MediaEngine
python ./Scripts/Format/EncodeConv.py Source/Sandbox
python ./Scripts/Format/EncodeConv.py Source/Examples
echo -e "--- finish encode conv ---"

echo -e "\n"

echo -e "--- start clang-format ---"
python ./Scripts/Format/FormatFile.py Source/MediaPlayer
python ./Scripts/Format/FormatFile.py Source/MediaEngine
python ./Scripts/Format/FormatFile.py Source/Sandbox
python ./Scripts/Format/FormatFile.py Source/Examples
echo -e "--- finish clang-format ---"
