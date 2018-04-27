#include "Library.h"
#include "HTML Template.h"
#include "CSV.h"

void main()
{
	string HTML; //Chuỗi chứa cấu trúc file HTML
	Info *SV = NULL; //Con trỏ cấu trúc thông tin sinh vien
	int TongSV; //Biến chứa tổng số sinh viên
	string *SinhVien = NULL; //Con trỏ chứa thông tin của sinh viên
	string *CtroSV = NULL; //Con trỏ chứa thuộc tính của sinh viên
	int SV_index; //Chỉ mục các thuộc tính các sinh viên
	int *ThongTin = NULL; //Con trỏ chứa số thuộc tính của các sinh viên

	//Lấy thông tin sinh viên
	int Test = LayInfo(SV, TongSV, SinhVien, CtroSV, ThongTin, SV_index);
	if (Test == 0) //Số sv không hợp lệ
	{
		cout << "Khong du bo nho." << endl << endl;
		system("pause");
		return;
	}

	//Lấy template từ file html
	GetTemplate(HTML);

	//Đưa thông tin trong struct vào file html
	for (int i = 0; i < TongSV; i++)
	{
		GhiThongTin(SV, HTML, i, ThongTin);
	}

	//Thông báo thành công
	cout << "Tao file html thanh cong. Xin hay xem thu." << endl << endl;

	//Giải phóng vùng nhớ
	delete[] SV;
	delete[] SinhVien;
	delete[] CtroSV;
	delete[] ThongTin;

	system("pause");
}