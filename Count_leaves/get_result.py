from time import sleep
import cv2
import numpy as np
import time
import matplotlib.pyplot as plt
from Counting_leaves import Count_leaves
from Counting_leaves import Mask
from send_firebase import Create_data
from send_firebase import Push_data
plt.figure(figsize=[5,5])

cap = cv2.VideoCapture('http://192.168.137.8:81/stream')
# cap = cv2.VideoCapture(0)   

list = []

while(True):
    ret, frame = cap.read()
    cv2.imshow('frame',frame)
    if len(list) >3 : break
    if cv2.waitKey(1) & 0xFF == ord('p'):
        mask = Mask(frame)
        No_leaf = Count_leaves(mask,len(list))
        list.append(No_leaf)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break   
cap.release()
cv2.destroyAllWindows()
print(list)
if len(list)==4: Push_data(Create_data(list))