# DateTimeConverter
Chuyển đổi ngày tháng năm dương lịch sang âm Lịch việt nam sử dụng look-up-table với 3 byte/năm
Sử dụng cho thư viện arduino.

# Thuật toán sử dụng
## Lưu data vào bảng tra
```
byte1:    [Ngay bat dau 1/1 AL - 5 bit][thang bat dau 1/1 AL - 1 bit][So ngay thang nhuan - 1 bit]
byte2:    [Thang nhuan - 4 bit][so ngay thang 12,11,10,9 - 4bit]
byte3:    [So ngay thang 8,7,6,5,4,3,2,1 - 8bit]

Ngay bat dau 1/1 AL  :  0x01->0x1F    1-31
thang bat dau 1/1 AL :  0             Thang 1
                        1             Thang 2
So ngay trong thang  :  0             29 ngay
                        1             30 ngay
```
Mốc là năm 2010:
## Sơ đồ thuật toán

1. Nếu ngày dương lịch nhỏ hơn ngày gốc -> trả về ngày hiện tại
1. lấy 3 byte liên tiếp từ bảng tra từ lut = `LUT[i, i+1, i+2]` với i = (năm dương lịch - 2016) * 3 
1. lấy ngày bắt đầu `sD` từ 5 bit đầu byte 1.
1. lấy tháng bắt đầu `sM` rừ bit thứ 6 (Đếm từ 1)
1. set `compareDay` với ngày = `sD`, tháng là `sM`, năm là năm của ngày dương lịch. `compareDay` là ngày dương lịch tướng ứng với ngày 1/1 của năm âm lịch
1. nếu ngày dương lịch nhỏ hơn ngày `compareDay` quay lại bước (2), với i-=3. (Lấy bảng tra của năm trước vì lúc này chưa sang năm mới)
1. start với tháng âm lịch `lm` = 1 
1. tính số ngày `aM` trong tháng `lm` từ 4 bit cuối byte 2 và 8 bit byte 3.
1. tăng `compareDay` thêm `aM` ngày gán vào biến tạm `TempDay`. `compareDay` là ngày dương lịch tương ứng với ngày 1 âm lịch của tháng kế tiếp.
1. nếu `compareDay` > ngày dương lịch thì thoát vòng lặp, trả về số tháng.
1. kiểm tra `lm` có tháng nhuận không. bằng cách so sánh với 4 bit đầu của byte 2. Vì tháng nhuận liền sau tháng chính, nên kiểm tra trước khi tăng thêm 1.
1. nếu `lm` là tháng nhuận, và chưa đếm tháng nhuận (cờ `CNN` = `true`), gán `aM` cho số ngày của tháng nhuận, và set cờ `CNN` thành `false` để tránh việc tháng nhuận bị tính nhiều lần. gán `TempDay` lại cho `compareDay` và quay lại bước 9.
1. Nếu `lm` không phải tháng nhuận, hoặc đã đếm tháng nhuận rồi, thì tăng `lm` lên 1.gán `TempDay` lại cho `compareDay` và quay lại bước 8.
1. Sau khi tính được tháng âm lịch `lm`, tính ngày âm lịch.
1. Kiểm tra, nếu tháng của compareDay = tháng hiện tại nghĩa là ngày dương lịch tướng ứng với ngày âm lịch cùng tháng với tháng hiện tại

ngày D tháng M tương ứng 1/m âm

 Mon | Tue | Wed | Thu | Fri | Sat | Sun
 --- | --- | --- | --- | --- | --- | --- |
D (_1/m_) | ~ | ~ | ~ | ~ | ~ | ~ 
~ | ~ | ~ | ~ | ~ | ~ | ~ 
~ | ~ | CD (_x/m_) | ~ | ~ | ~ | ~ 
~ | ~ | ~ | ~ | ~ | ~ | D + aM (_1/m+1_)

Theo bảng trên, 
```
x - 1 = CD - D
=> x = CD - D + 1
 ```
D/M là compare day và CD/M là ngày tháng hiện tại.

1. Trong tường hợp compareDay và tháng của ngày dương lịch khác nhau 
ngày D tháng M tương ứng 1/m âm

 Mon | Tue | Wed | Thu | Fri | Sat | Sun
 --- | --- | --- | --- | --- | --- | --- |
~ | ~ | ~ | ~ | ~ | ~ | D (_1/m_) 
~ | ~ | ~ | ~ | ~ | ~ | ~ 
~ | ~ | ~ | ~ | ~ | ~ | ~ 
~ | ~ | ~ | ~ | ~ | ~ | MaxDay ( _x-CD/m_ )


 Mon | Tue | Wed | Thu | Fri | Sat | Sun
 --- | --- | --- | --- | --- | --- | --- |
~ | ~ | ~ | ~ | ~ | CD (_x/m_) | ~ 
~ | ~ | ~ | ~ | ~ | ~ | D + aM (_1/m+1_) 
~ | ~ | ~| ~ | ~ | ~ | ~ 
~ | ~ | ~ | ~ | ~ | ~ | ~

Theo bảng trên,
```
x - CD - 1 = MaxDay - D
=> x = MaxDay + CD + 1 - D
``` 
