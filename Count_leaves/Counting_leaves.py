import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image,ImageFilter
plt.figure(figsize=[5,5])

def erode(cycles, image):
    for _ in range(cycles):
        image = image.filter(ImageFilter.MinFilter(3))
    return image

def dilate(cycles, image):
    for _ in range(cycles):
        image = image.filter(ImageFilter.MaxFilter(3))
    return image

def Mask(image):

    img = Image.fromarray(np.uint8(image)).convert('RGB')
    img = Image.fromarray(image.astype('uint8'), 'RGB')
    gray = img.convert('L')

    threshold = 80
    img_threshold = gray.point( lambda x: 255 if x > threshold else 0 )
    red, green, blue = img.split()
    threshold = 60
    img_threshold = green.point(lambda x: 255 if x > threshold else 0)
    # img_threshold = blue.point(lambda x: 255 if x > 50 else 0)
    img_threshold = img_threshold.convert("1")
    step_1 = erode(1, img_threshold)
    step_2 = dilate(1,step_1)
    mask = erode(1, step_2)
    mask2 = mask.convert("L")
    mask2 = mask2.filter(ImageFilter.BoxBlur(2))

    blank = img.point(lambda _: 0)
    segmented = Image.composite(img, blank, mask2)
    return np.array(segmented)

def Count_leaves(image,N):

    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # plt.imshow(gray, cmap='gray')
    blur = cv2.GaussianBlur(gray, (7,7), 0)
    canny = cv2.Canny(blur,155,80,155)
    dilated = cv2.dilate(canny, (1,1), iterations = 1)
    # plt.imshow(blur, cmap='gray')
    (cnt, heirarchy) = cv2.findContours(dilated.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    f1 = []
    for cont in cnt:
        # print(cv2.contourArea(cont))
        if cv2.contourArea(cont) > 60: 
            f1.append(cont)

    rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    sorted_contours = sorted(f1, key=cv2.contourArea, reverse= True)
    for i, cont in enumerate(f1,1):
        cv2.drawContours(rgb, cont, -1, (255,0,0), 1)
        # Display the position of contour in sorted list
        # cv2.putText(rgb, str(i), (cont[0,0,0], cont[0,0,1]-10), cv2.FONT_HERSHEY_SIMPLEX, 1.4, (255, 0, 0),2)
    # cv2.drawContours(rgb, cnt, -1, (0,255,255), 1)
    cv2.putText(rgb, (str('leaf:')+str(len(f1))), (5,15), cv2.FONT_HERSHEY_SIMPLEX, 0.5,(255,255,255),1)
    plt.imshow(rgb)

    print('leaf in plant',N+1,':', len(f1))
    plt.show()
    if cv2.waitKey(1) & 0xFF == ord('n'):
        cv2.destroyAllWindows()
    return len(cnt)

def leaf_value():
    listValue = []
    pass

    