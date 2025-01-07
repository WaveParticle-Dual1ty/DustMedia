echo -e "--- start encode conv ---"
python ./Scripts/Format/EncodeConv.py Source/MediaEngine
python ./Scripts/Format/EncodeConv.py Source/Sandbox
echo -e "--- finish encode conv ---"

echo -e "\n"

echo -e "--- start clang-format ---"
python ./Scripts/Format/FormatFile.py Source/MediaEngine
python ./Scripts/Format/FormatFile.py Source/Sandbox
echo -e "--- finish clang-format ---"
