Chương trình sẽ bắt đầu bằng việc hiện ra menu để người dùng lựa chọn thao tác mong muốn gồm: nhập khóa, sinh khóa tự động, mã hóa, giải mã và kết thúc chương trình.

Nhập khóa sẽ yêu cầu người dùng nhập 2 số nguyên tố p và q để tính giá trị n và phiN. Nếu người dùng nhập sai kiểu dữ liệu hoặc nhập hợp số hoặc nhập 2 số nguyên tố giống nhau, chương trình sẽ thông báo lỗi nhập của người dùng và yêu cầu người dùng nhập lại. Sau đó, chương trình yêu cầu người dùng nhập số mũ công khai e, nếu người dùng nhập sai kiểu dữ liệu hoặc nhập số mũ không nguyên tố cùng nhau với phiN thì chương trình sẽ thông báo lỗi nhập của người dùng và yêu cầu người dùng nhập lại. Sau cùng, chương trình sẽ tính giá trị d là nghịch đảo của e.

Sinh khóa sẽ yêu cầu người dùng nhập giá trị tối thiểu cho 2 số nguyên tố và độ chênh lệch giữa 2 số nguyên tố đó, chương trình sẽ sinh 2 số nguyên tố nhỏ nhất thỏa điều kiện và tính các giá trị n, phiN, e và d.

thao tác mã hóa và giải mã sử dụng chung một hàm crypting. Hàm này lấy tham số là chuỗi "encrypt" hoặc "decrypt", chương trình sẽ yêu cầu người dùng nhập tên file cần mã hóa/giải mã và xác định giá trị số nguyên của toàn bộ nội dung file. Nếu giá trị này lớn hơn N thì file không được giải mã/mã hóa. Ngược lại, chương trình sẽ tiếp tục thực hiện việc mã hóa/giải mã. Tùy vào tham số chuỗi nhập vào hàm mà chương trình sẽ chọn số mũ e hoặc d để mã hóa/giải mã nội dung file nhập. Chương trình sử dụng hàm powerMod để tính giá trị của đã qua mã hóa/giải mã và lưu giá trị vừa tính được dưới dạng chuỗi ký tự vào một file mới có tên là tên của file nhập dữ liệu cộng thêm chuỗi tham số nhập vào hàm crypting. Nếu file xuất kết quả không mở được thì chương trình sẽ báo lỗi và kết thúc quá trình chạy hàm

để chạy thì cần dùng giao diện developer prompt và dùng cl để chạy: cl main.cpp largeInt.cpp -o ./main.exe

do sử dụng string kém hiệu quả về tốc độ và lưu trữ, nên đối tượng số nguyên lớn dưới dạng list<char> đang được thiết kế trong branch main.
