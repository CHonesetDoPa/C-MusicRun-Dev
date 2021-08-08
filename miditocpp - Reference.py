import mido
import time
from alive_progress import alive_bar

mid = mido.MidiFile()  # midi文件
file_name = ""  # 文件名
bpm = 0  # 速率
track_count=0#轨道数
note_count=0#音符数

note_list = []  # 频率表
dura_list = []  # 延时表


#88键频率对照表
fre_list = []#此处省略具体内容


def tick2time(bpm, tick):
    '''根据bpm计算音符持续时间（ms）'''
    t = 60*1000/bpm  # 拍时
    return round(tick/mid.ticks_per_beat*t)


def create_cpp():
    '''由midi文件生成对应cpp文件'''
    global track_count,note_count,note_list, dura_list  

    with alive_bar(len(mid.tracks)) as bar:
        for track in mid.tracks:
            bar()
            for i, msg in enumerate(track):
                if msg.type == "note_on":
                    if i == len(track)-1 or track[i+1].type == "note_off":
                        if msg.time != 0:
                            note_list.append(0)
                            dura_list.append(tick2time(bpm, msg.time))
                        note_list.append(fre_list[msg.note-21])

                elif msg.type == "note_off":
                    if i == len(track)-1 or track[i+1].type == "note_on":
                        dura_list.append(tick2time(bpm, msg.time))

            with open(file_name.split('.')[0]+f'--track_{track_count}'+'.cpp', 'w') as f:
                f.write(
                    f'\nint melody[{max(len(dura_list),len(note_list))+1}]='+str(note_list).replace('[', '{').replace(']', '}')+';')
                f.write(
                    f'\nint noteDurations[{max(len(dura_list),len(note_list))+1}]='+str(dura_list).replace('[', '{').replace(']', '}')+';')
                f.write('\nvoid setup() {')

                f.write('\n}')

                f.write('''\nvoid loop(){ 
            for(int thisNote = 0; thisNote < sizeof(melody)/4; thisNote ++){
                tone(8,melody[thisNote],noteDurations[thisNote]);
                delay(noteDurations[thisNote]);
                noTone(8);
            }
        }''')

            track_count+=1
            note_count+=len(note_list)
            note_list = []  
            dura_list = []  





if __name__ == "__main__":
    print("========================================================")
    print("Program started.\n")

    file_name = input('please input the file name (same path):')
    bpm = int(input('please input the playing speed (bpm):'))

    print('\n\nProcessing...\n')

    mid = mido.MidiFile(file_name)  # 打开midi文件

    create_cpp()

    print(f'\n\nCompleted.  \n{track_count} tracks found. \n{note_count} notes created in total.')
    print("\n========================================================")
    input("\nPress any key to exit...")