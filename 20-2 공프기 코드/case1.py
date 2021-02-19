'''
화면에 사람이 인식되면 모션과 함께 음성으로 인사를 하고
어떤일로 찾아왔는지 질문을 한다.
이때, 5초간 말이 없을 경우 -> 지금은 그냥 넘어가고 있음. 
(구현필요 : 다시 말씀해 주세요.)
(구현필요 : 위에서 얻은 답변으로 모션(케이스를 나눠서)을 실행한다.)
'''
#import numpy as np
import socket
import cv2
import time
import threading
#import multiprocessing
import ctypes
#import pyttsx3
#from gtts import gTTS
import os
import pickle
import numpy as np
import mtcnn
import matplotlib.pyplot as plt
import cv2
from sklearn.preprocessing import Normalizer
from keras.models import load_model
import win32com.client
from scipy.spatial.distance import cosine

from multiprocessing import Process, Pipe
import speech_recognition as sr

#engine = pyttsx3.init()

global flag
global end

#발견한 얼굴 예측값
def get_encode(face_encoder, face, size):
    face = normalize(face)
    face = cv2.resize(face, size)   
    encode = face_encoder.predict(np.expand_dims(face, axis=0))[0]
    return encode

#화면상에 등장한 얼굴 크랩
def get_face(img, box):
    x1, y1, width, height = box
    x1, y1 = abs(x1), abs(y1)
    x2, y2 = x1 + width, y1 + height
    face = img[y1:y2, x1:x2]
    return face, (x1, y1), (x2, y2)


l2_normalizer = Normalizer('l2')

#벡터값 노말라이즈
def normalize(img):
    mean, std = img.mean(), img.std()
    return (img - mean) / std


def plt_show(cv_img):
    img_rgb = cv2.cvtColor(cv_img, cv2.COLOR_BGR2RGB)
    plt.imshow(img_rgb)
    plt.show()


def load_pickle(path):
    with open(path, 'rb') as f:
        encoding_dict = pickle.load(f)
    return encoding_dict

#
def save_pickle(path, obj):
    with open(path, 'wb') as file:
        pickle.dump(obj, file)
        
##########################
#2020.09.27
#새로운 사람 등장하면 새폴더 만들기
def createFolder(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)
##########################


'''
MTCNN으로 찾은 얼굴(첫번째 파라미터 results)을 가지고

'''
def recognize(results,
              img,
              img_rgb,
              detector,
              encoder,
              encoding_dict,
              recognition_t=0.25, #0.4~0.5 // 0.1~0.2
              confidence_t=0.99,
              required_size=(160, 160), ):
    #img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    #results = detector.detect_faces(img_rgb)
    #print(results)
    i=0
    name = 'unknown'
    for res in results:
        if res['confidence'] < confidence_t:
            continue
            
        x1, y1, width, height = res['box']
        x1, y1 = abs(x1), abs(y1)
        x2, y2 = x1 + width, y1 + height
        #현재 얼굴 중심좌표 계산
        x_point = int((x1+x2)/2)
        y_point = int((y1+y2)/2)
        x_y_ = repr(x_point) +','+ repr(y_point)
        
        #얼굴 이미지와 위치 값을 get_face로 받음
        #face는 이미지임
        face, pt_1, pt_2 = get_face(img_rgb, res['box'])
        
        #찾은 얼굴을 벡터화 시킴
        encode = get_encode(encoder, face, required_size)
        encode = l2_normalizer.transform(encode.reshape(1, -1))[0]
        name = 'unknown'

        distance = float("inf")
        #db에 저장된 사람이랑 찾은 얼굴이랑 가장 유사한 얼굴을 찾음.
        for db_name, db_encode in encoding_dict.items():
            dist = cosine(db_encode, encode)
            if dist < recognition_t and dist < distance:
                name = db_name
                distance = dist
        
        #db에 비슷한 얼굴이 없으면
        if name == 'unknown':
            cv2.rectangle(img, pt_1, pt_2, (0, 0, 255), 2)
            cv2.putText(img,x_y_,(500,50+(i*50)),font, 0.9, (255,0,0),2)
            cv2.putText(img, name, pt_1, cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 1)
        #db에서 비슷한 얼굴을 찾으면
        else:
            cv2.rectangle(img, pt_1, pt_2, (0, 255, 0), 2)
            cv2.putText(img,x_y_,(500,50+(i*50)),font, 0.9, (255,0,0),2)
            cv2.putText(img, name + f'__{distance:.2f}', (pt_1[0], pt_1[1] - 5), cv2.FONT_HERSHEY_SIMPLEX, 1,
                        (0, 200, 200), 2)
        i+=1
    return img, name



#tts = _TTS()
#tts = gTTS(text="안녕하세요. 만나서 반가워요.", lang="ko")
##tts.start("안녕하세요. 만나서 반가워요.")
#del(tts)

#run은 음성인식서비스 제공하는 function
def run(con):
    print("HITHRED START")
    
    flag = 0
    end = 0
    a = 0
    
    name = 'UnKnown'
    sock_ip = "127.0.0.1"
    sock_port = 9999
    
    #c#과 통신할 socket 만들고 연결
    sock = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((sock_ip,sock_port))
    #val = ['1','8']
    val1 = '1'
    val2 = '8'
    val3 = '4'
    val4 = '2'
    val5 = '512'
    val6 = '256'
    
    data1 = val1.encode();
    data2 = val2.encode();
    data3 = val3.encode();
    data4 = val4.encode();
    data5 = val5.encode();
    data6 = val6.encode();
    
    #tts 모델로 SAPI.SpVoice
    tts = win32com.client.Dispatch("SAPI.SpVoice")
    #stt 모델 
    r = sr.Recognizer()
    file = sr.Microphone()
    
    #file = sr.Microphone(device_index=0 )
    while True:
        #pipe를 통해 parent로 부터 data를 입력받아 flag에 전달
        #flag는 integer와 string이 저장되어있음
        flag = con.recv()
        name = flag[1]
        #print(flag)
        
        #parent로부터 전달된 데이터를 보고
        #1이라는거는 사람이 발견 되었다는 뜻이므로
        #사람이 발견됨 = 이름이 있을 수도 있고 unknown일 수도 있음.
        if flag[0] == 1 :
            #print("안녕하세요")        
            print(name)
            #socket으로 C#으로 데이터 전달
            sock.send(data1) 
            time.sleep(1)
            if name == "unknown":
                tts.Speak("안녕하세요. 방문자님 만나서 반갑습니다.")
            else :
                tts.Speak("안녕하세요." + name + "님 만나서 반갑습니다.")
            time.sleep(3)
            sock.send(data2)
            tts.Speak("어떤일로 오셨나요?")
            with file as source:
                print("say something!!.....")
                #audio = r.adjust_for_ambient_noise(source)
                #stt 시작
                audio = r.listen(source,5)             
            try:
                recog = r.recognize_google(audio, language = 'ko-KR')
                #print("You said: " + recog)
                recog1 = recog      
                recog2 = recog1.replace(" ", "")
                print ("You said: " + recog2)
                
                if "소중대" in recog2:
                    sock.send(data3)
                    time.sleep(1)
                    tts.Speak("여기는 전산전자공학부입니다. 소프트웨어 중심 사업단은 2층에 있습니다.")
                if "어때" in recog2:
                    sock.send(data4)
                    time.sleep(1)
                    tts.Speak("정말 예쁘시네요. 비결이 뭔가요?")
                if "우편물" in recog2:     
                    sock.send(data5)
                    time.sleep(1)
                    tts.Speak("지금 제 맞은편에 우편함이 있습니다.")         
                time.sleep(2)
            except sr.UnknownValueError as u:
                print(u)
                print("Google Cloud Speech Recognition could not understand audio")
            except sr.RequestError as e:
                print("Could not request results from Google Cloud Speech Recognition service; {0}".format(e)) 
                
            with file as source:
                print("say something!!.....")
                #audio = r.adjust_for_ambient_noise(source)
                audio = r.listen(source,5)
                
            try:
                recog = r.recognize_google(audio, language = 'ko-KR')
                if "고마워" in recog:
                    sock.send(data6)
                    time.sleep(1)
                    tts.Speak("별말씀을요. 감사합니다.")
            except sr.UnknownValueError as u:
                print(u)
                print("Google Cloud Speech Recognition could not understand audio")
            except sr.RequestError as e:
                print("Could not request results from Google Cloud Speech Recognition service; {0}".format(e)) 

            '''
            with mic as source:
                audio = r.listen(source)
            print(audio)
            print(recog = r.recognize_google_cloud(audio,language='ko-KR'))
            #print(r.recognize_google(audio,language='ko-KR'))
            '''
            time.sleep(2)
            #위의 과정이 사람이 화면에 등장하면 한번 실행되는 과정임
            #사람등장 -> 로봇이 인사 -> 어떤일로 왔는지? 가 1cycle
            while True :
                #다시 parent로부터 data받음
                flag = con.recv()
                #print(flag)
                #print("HITHREAD" +str(flag))
                #print("CHILD" + str(con.recv()))
                
                #받은 데이터를 보고 만약 flag[0] == 0 이라면 results에
                #사람이 발견되지 않은 경우이므로 화면상 사람이 없는거임
                #그러므로 탈출 만약 이 경우가 아닌 경우 사용자에게 계속 서비스를
                #제공할 수 있도록 구현해야함.
                if flag[0] == 0 :#or flag[1] != name 
                    print("탈출탈출탈출탈출탈출탈출탈출탈출탈출탈출탈출탈출")
                    break
                if end == 1:
                    print("HI BREAK!!")
                    break    
        if end == 1:
            print("HI BREAK!!")
            break           
    con.close()
        

if __name__ == '__main__':
    
    #parent프로세스랑 child프로세스 간 데이터 통신을 위한 pipe 뚫는 작업
    parent_conn, child_conn = Pipe()
    numbers = [5, 10, 15, 20, 25]
    
    #child프로세스가 실행할 함수를 정해주는 작업
    proc = Process(target=run, args=(child_conn,)) 
    #proc.append(proc)
    #child프로세스가 돌기시작
    proc.start()
    
    encoder_model = 'data/model/facenet_keras.h5'
    people_dir = 'data/people'
    
    #db에 저장된 사람들의 얼굴을 숫자로 표시해두는 곳이 enconding.pkl임.
    encodings_path = 'data/encodings/encodings.pkl'
    required_size = (160, 160)

    face_detector = mtcnn.MTCNN()
    face_encoder = load_model(encoder_model)

    encoding_dict = dict()
    
    #가장 처음 프로그램이 시작될 때, 기존에 등록되어있던 사람의 얼굴을 encode해서 
    #encodings.pkl에 넣는 작업
    #기존에 등록되어있던 사람이 결국은 사진으로 저장으로 저장되어 있어서
    #results = face_detector.detect_faces(img_rgb)이 코드에서 각 사진에서 얼굴찾는 작업이 필요함
    #그래서 이 부분에서 프로그램을 실행시켰을 때 바로 화면이 뜨지 않고 딜레이가 생기는 원인임.
    for person_name in os.listdir(people_dir):
        person_dir = os.path.join(people_dir, person_name)
        encodes = []
        for img_name in os.listdir(person_dir):
            img_path = os.path.join(person_dir, img_name)
            img = cv2.imread(img_path)
            img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
            results = face_detector.detect_faces(img_rgb)
            if results:
                res = max(results, key=lambda b: b['box'][2] * b['box'][3])
                face, _, _ = get_face(img_rgb, res['box'])

                face = normalize(face)
                face = cv2.resize(face, required_size)
                encode = face_encoder.predict(np.expand_dims(face, axis=0))[0]
                encodes.append(encode)
        if encodes:
            encode = np.sum(encodes, axis=0)
            encode = l2_normalizer.transform(np.expand_dims(encode, axis=0))[0]
            encoding_dict[person_name] = encode


    for key in encoding_dict.keys():
        print(key)
    
    #encoding값을 저장하는 작업
    with open(encodings_path, 'bw') as file:
        pickle.dump(encoding_dict, file) 
    #face_thread = facethread('FACE')
    #hi_thread = hithread('HI')
    #face_thread.start()
    #hi_thread.start()
    prevTime = 0
    ##########################
    #2020.09.27
    #r키를 눌렀을 때, 폴더가 만들어질 위치 
    add = 'data/people/'
    count = 0
    ##########################
    cap = cv2.VideoCapture(0)
    a=0
    while True :
        #####fps구하는 코드####
        curTime = time.time()
        sec = curTime - prevTime
        prevTime = curTime
        fps = 1/(sec)
        fps_r = "FPS : %0.1f" % fps
        font = cv2.FONT_HERSHEY_SIMPLEX
        ############
        ret, frame = cap.read()
        width  = cap.get(cv2.CAP_PROP_FRAME_WIDTH ) # float
        height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT ) # float
        if not ret:
            print("no frame:(")
            break
        ##########################
        #2020.09.27       
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        #face_detector가 MTCNN임
        #MTCNN을 사용해서 사진(RGB형태)에서 얼굴을 Detect함.
        #사람이 여러명이면 다 찾아서 results에 넣음
        results = face_detector.detect_faces(frame_rgb)
        #print(results)
        a+=1
        
        #만약 화면에 사람이 없으면
        #child프로세스한테 0이랑 Unkonown을 보냄.
        if results == [] :
            #print("NO RESULTS!")
            parent_conn.send([0,'Unknown'])
            #print(parent_conn.send([0,'Unknown']))
          
        #누군지는 모르지만 누구가를 찾으면
        #child프로세스한테 1이랑 찾은 사람의 이름을 보냄
        else :
            #print("YES RESULTS!")           
            frame, name = recognize(results, frame, frame_rgb, face_detector, face_encoder, encoding_dict)
            parent_conn.send([1, name])
            #print(parent_conn.send([1,name])) 
        #frame = recognize(frame, face_detector, face_encoder, encoding_dict)

        key = cv2.waitKey(1) & 0xFF
        #q누르면 종료
        if key == ord('q'):
            end = 1
            break
        #r누르면 사용자 등록
        elif key == ord('r'):
            count+=1
            #신규 등록 및 폴더에 사진 업데이트
            face_id = input('\n enter user id end press <return> ==>  ')
            #frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            #results = face_detector.detect_faces(frame_rgb)
            mx = 0
            for res in results:
                x1, y1, width, height = res['box']
                if(mx < width * height):
                    mx = width * height
                    x = x1
                    y = y1
            #print(x, y)
            x, y = abs(x), abs(y)
            #print(x, y)
            x2, y2 = x + width, y + height
            img = cv2.rectangle(frame, (x, y), (x2, y2), (255, 0, 0), thickness=2)
           
            if os.path.exists(add + face_id):
                cv2.imwrite(add+ str(face_id)+'/'+str(face_id)+ '.'+ str(count) + ".jpg",img[y:y2, x:x2])
            else:
                createFolder(add+face_id)
                cv2.imwrite(add+ str(face_id)+'/'+str(face_id)+ '.' + str(count) + ".jpg",img[y:y2, x:x2])
            '''
            for res in results:
                x1, y1, width, height = res['box']
                x1, y1 = abs(x1), abs(y1)
                x2, y2 = x1 + width, y1 + height
                img = cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 0), thickness=2)
                if os.path.exists(add + face_id):
                    cv2.imwrite(add+ str(face_id)+'/'+str(face_id)+ '.'+ str(count) + ".jpg",img[y1:y2, x1:x2])
         qqq       else:
                    createFolder(add+face_id)
                    cv2.imwrite(add+ str(face_id)+'/'+str(face_id)+ '.' + str(count) + ".jpg",img[y1:y2, x1:x2])
            '''
            #새로운 사람을 등록하였으므로 people 폴더 데이터 갱신
            for person_name in os.listdir(people_dir):
                #위에서 등록하면서 입력한 사람 이름 = face_id임
                #이 if문에서 만약 새로 등록한 사람이 아니면 데이터 갱신할 필요
                #없으므로 continue
                if(person_name != face_id):
                    continue
                print(person_name)
                person_dir = os.path.join(people_dir, person_name)
                encodes = []
                i=0
                for img_name in os.listdir(person_dir):
                    print(i)
                    i+=1
                    img_path = os.path.join(person_dir, img_name)
                    img = cv2.imread(img_path)
                    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
                    results = face_detector.detect_faces(img_rgb)
                    if results:
                        print(person_name,i)
                        res = max(results, key=lambda b: b['box'][2] * b['box'][3])
                        #print(res)
                        face, _, _ = get_face(img_rgb, res['box'])
                        face = normalize(face)
                        #print(required_size)
                        face = cv2.resize(face, required_size)
                        #print(face)
                        encode = face_encoder.predict(np.expand_dims(face, axis=0))[0]
                        encodes.append(encode)
                if encodes:
                    encode = np.sum(encodes, axis=0)
                    encode = l2_normalizer.transform(np.expand_dims(encode, axis=0))[0]
                    encoding_dict[person_name] = encode


            for key in encoding_dict.keys():
                print(key)

            with open(encodings_path, 'bw') as file:
                pickle.dump(encoding_dict, file)
        cv2.line(frame, (int(width/2),0),(int(width/2),int(height)),(0,0,255),1)
        cv2.line(frame, (0,int(height/2)),(int(width),int(height/2)),(0,0,255),1)
        cv2.putText(frame,fps_r,(50,50),font, 0.5, (0,255,255),2)
        cv2.putText(frame,repr(int(width/2))+','+repr(int(height/2)),(500,400),font, 0.5, (0,0,255),2)
        cv2.imshow('camera', frame)
        ##########################
    cap.release()
    #parent, child pipe 닫음
    parent_conn.close()
    cv2.destroyAllWindows()
    #child 프로세스 끝날 때 까지 parent는 여기서 기다린 후 child 종료되면 종료
    proc.join()

    #face_thread.join()
    #print("FACE END")
    #hi_thread.join()
    print("HI END") 
    print("MAIN END")