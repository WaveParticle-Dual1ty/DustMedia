import os
import sys
import codecs
import chardet
import time

file_types = [
    ".h",
    ".cpp",
    ]


def check_need_convert(file_name):
    for type in file_types:
        if file_name.lower().endswith(type):
            return True
    return False


total_cnt = 0
success_cnt = 0
unkown_cnt = 0
def conv_encoding_to_utf_8(filename):
    global total_cnt, success_cnt, unkown_cnt

    total_cnt += 1 

    content = codecs.open(filename, 'rb').read()
    detect = chardet.detect(content)
    source_encoding = detect['encoding']
    confidence = detect['confidence']
    if source_encoding.lower().startswith('iso-8859') and confidence < 0.9:
        source_encoding = 'GBK'
    if source_encoding == None:
        unkown_cnt+=1
        return
    
    print(source_encoding, filename)
    
    if source_encoding != 'UTF-8-SIG':
        str_content = content.decode(source_encoding)
        backup_filename = filename + '.tmp'
        codecs.open(backup_filename, 'wb').write(content)
        try:
            codecs.open(filename, 'w', encoding='UTF-8-SIG').write(str_content)
            os.remove(backup_filename)
        except Exception as e:
            print('conv error: ', e)
        success_cnt += 1



def convert_dir(root_dir):
    if os.path.exists(root_dir) == False:
        print("[error] not exist dir: ", root_dir)
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if check_need_convert(file):
                filename = os.path.join(root, file)
                try:
                    conv_encoding_to_utf_8(filename)
                except Exception as e:
                    print("[error] ", filename, e)

    print("total file: ", total_cnt)
    print("conv file: ", success_cnt)
    print("unkown file: ", unkown_cnt)


if __name__ == "__main__":
    if len(sys.argv) == 1:
        dir = os.getcwd() + '/Source'
    else:
        dir = sys.argv[1]
    convert_dir(dir)
    sys.exit(0)
