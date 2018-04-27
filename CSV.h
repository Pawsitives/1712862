#include "Library.h"

//Cấu trúc thông tin sinh viên
struct Info
{
	string MSSV, Ten, Khoa, Email, NS, Hinh, MoTa, *SoThich;
};

//Hàm chuẩn hóa chuỗi thông tin của sinh viên
//"ID", "NAME" => "ID"NAME"
void ChuanHoa(string &SinhVien)
{
	for (int i = 1; i < SinhVien.length() - 1; i++)
	{
		if (SinhVien[i] == ',' && SinhVien[i + 1] == ' ' && SinhVien[i - 1] == '\"')
		{
			SinhVien.erase(i, 3);
		}
	}
}

//Kiểm tra tổng số sinh viên
int KtraSoSV(int TongSV)
{
	ifstream Fcsv("SinhVien.csv");
	if (!Fcsv)
	{
		perror("Khong mo duoc file.\n");
	}

	//Đếm số sinh viên trong dữ liệu
	string temp;
	int Count = 0;
	while (!Fcsv.eof())
	{
		getline(Fcsv, temp);
		Count += 1;
	}

	//Kiểm tra tổng sinh viên với số sinh viên người dùng nhập
	if (TongSV > Count)
	{
		return 0;
	}
	return 1;
}

//Hàm tái cấp phát bộ nhớ
void CapPhat(string *&SinhVien_CT, int CtroSV)
{
	string *temp = new string[CtroSV];
	for (int i = 0; i < CtroSV; i++)
	{
		*(temp + i) = *(SinhVien_CT + i);
	}
	SinhVien_CT = new string[CtroSV + 1];
	for (int i = 0; i < CtroSV; i++)
	{
		*(SinhVien_CT + i) = *(temp + i);
	}
	delete[] temp;
}

//Hàm tách thông tin từ chuỗi thông tin các sinh viên
void TachThongTin(string SinhVien, Info SV[], int index, string *&SinhVien_CT, int CtroSV, int *&ThongTin)
{
	//Chuẩn hóa chuỗi thông tin
	ChuanHoa(SinhVien);

	char *c = (char*)SinhVien.c_str();
	char *nl = NULL;
	char temp[] = "\"";

	//Cấp phát vùng nhớ cho SinhVien_CT và gán số thuộc tính của sinh viên là 0
	SinhVien_CT = new string[1];
	ThongTin[index] = 0;

	//Tách dữ liệu từ file
	char *p = strtok_s(c, temp, &nl);
	while (p != NULL)
	{
		int n = strlen(p);
		for (int i = 0; i < n; i++)
		{
			SinhVien_CT[CtroSV].push_back(p[i]);
		}
		CtroSV++;
		CapPhat(SinhVien_CT, CtroSV);
		p = strtok_s(NULL, temp, &nl);
		//Cộng thuộc tính với số gia 1
		ThongTin[index] += 1;
	}

	//Đưa dữ liệu vào trong struct (trừ sở thích)
	SV[index].MSSV = SinhVien_CT[0];
	SV[index].Ten = SinhVien_CT[1];
	SV[index].Khoa = SinhVien_CT[2];
	SV[index].Email = SinhVien_CT[3];
	SV[index].NS = SinhVien_CT[4];
	SV[index].Hinh = SinhVien_CT[5];
	SV[index].MoTa = SinhVien_CT[6];

	//Đưa sở thích vào struct
	SV[index].SoThich = new string[CtroSV - 6];
	for (int i = 0; i < CtroSV - 6; i++)
	{
		SV[index].SoThich[i] = SinhVien_CT[i + 7];
	}
}

//Hàm lấy thông tin của sinh viên
int LayInfo(Info *&SV, int &TongSV, string *&SinhVien, string *&SinhVien_CT, int *&ThongTin, int &CtroSV)
{
	do
	{
		cout << "Nhap so luong sinh muon tao:  ";
		cin >> TongSV;
		cout << endl;
	} while (TongSV <= 0);

	//Kiểm tra tổng sinh viên có hợp lệ không
	int Test = KtraSoSV(TongSV);
	if (Test == 0)
	{
		return 0;
	}

	//Cấp phát bộ nhớ cho các con trỏ
	SV = new Info[TongSV];
	SinhVien = new string[TongSV];
	CtroSV = 0;
	ThongTin = new int[TongSV];

	//Lấy thông tin từ file csv đưa vào chuỗi thông tin các sinh viên
	ifstream Fcsv("SinhVien.csv");
	if (!Fcsv)
	{
		perror("Mo file that bai.\n");
	}

	for (int i = 0; i < TongSV; i++)
	{
		getline(Fcsv, SinhVien[i]);
		//Tách từ chuỗi tổng đưa vào các thuộc tính các sinh viên
		TachThongTin(SinhVien[i], SV, i, SinhVien_CT, CtroSV, ThongTin);
	}

	return 1;
}

//Hàm tải thông tin vào file html
void GhiThongTin(Info *&SV, string HTML, int index, int *ThongTin)
{
	string FileName;
	FileName = "Website/" + SV[index].MSSV + ".html";
	ofstream f1(FileName);

	//Đưa thông tin vào file
	//Họ tên
	int in = 0;
	char *temp;
	do
	{
		temp = (char*)SV[index].Ten.c_str();
		in = HTML.find("$name", in + 1, 5);
		if (in != std::string::npos)
		{
			HTML.replace(in, 5, temp);
		}
	} while (in != std::string::npos);

	//MSSV
	in = 0;
	do
	{
		temp = (char*)SV[index].MSSV.c_str();
		in = HTML.find("$id", in + 1, 3);
		if (in != std::string::npos)
		{
			HTML.replace(in, 3, temp);
		}
	} while (in != std::string::npos);

	//Khoa
	in = 0;
	do
	{
		temp = (char*)SV[index].Khoa.c_str();
		in = HTML.find("$faculty", in + 1, 8);
		if (in != std::string::npos)
		{
			HTML.replace(in, 8, temp);
		}
	} while (in != std::string::npos);

	//Ngày sinh
	in = 0;
	temp = (char*)SV[index].NS.c_str();
	in = HTML.find("$birthday");
	HTML.replace(in, 9, temp);

	//Mô tả
	in = 0;
	temp = (char*)SV[index].MoTa.c_str();
	in = HTML.find("$info");
	HTML.replace(in, 5, temp);

	//Hình ảnh
	in = 0;
	temp = (char*)SV[index].Hinh.c_str();
	in = HTML.find("$avatar");
	HTML.replace(in, 7, temp);

	//Email
	in = 0;
	do
	{
		temp = (char*)SV[index].Email.c_str();
		in = HTML.find("$mail");
		if (in != std::string::npos)
		{
			HTML.replace(in, 5, temp);
		}
	} while (in != std::string::npos);

	//Sở thích
	in = 0;
	int ThuocTinhSoThich = ThongTin[index] - 7;
	in = HTML.find("$hobbies");
	string Hobbies = "";
	for (int k = 0; k < ThuocTinhSoThich; k++)
	{
		Hobbies += "<li>" + SV[index].SoThich[k] + "</li>" + "\n";
	}
	temp = (char*)Hobbies.c_str();
	HTML.replace(in, 8, temp);

	//Đưa dữ liệu vào HTML
	f1 << HTML;
	f1.close();
}