    #include<iostream>
    #include<string>
    #include<ctime>
    #include<fstream>

    using namespace std;

    class sinhvien
    {  
        private:

            string ten;
            string sdt;
            string ngaysinh;
            string phong;

        public:

            void nhap()
            {
                cout<<"----Nhap thong tin----\n";
                cout<<"Nhap ho va ten: ";
                cin.ignore(); 
                getline(cin, ten);
                cout<<"Ngay sinh: ";
                getline(cin, ngaysinh);
                cout<<"Nhap so phong: ";
                getline(cin, phong);
                cout<<"So dien thoai: ";
                getline(cin,sdt);
            }

            string getten(){return ten;}
            string getngaysinh(){ return ngaysinh;}
            string getsdt(){ return sdt;}
            string getphong(){ return phong;}

            void xuat()
            {
                cout<<"----Thong tin sinh vien----\n";
                cout<<"Ho va ten: "<<ten<<endl;
                cout<<"Ngay sinh: "<<ngaysinh<<endl;
                cout<<"Phong: "<<phong<<endl;
                cout<<"So dien thoai: "<<sdt<<endl;
                cout<<endl;
            }

    };

    class thektx: public sinhvien //ke thua class sinhvvien
    {
        private:

            string sothektx;
        
        public:

            string getSothektx()
            {
                return sothektx;
            }

            void nhap()
            {
                sinhvien::nhap();
                cout<<"Nhap so the KTX: ";
                getline(cin, sothektx);
            }

            void xuat()
            {
                sinhvien::xuat();
                cout<<"So the KTX: "<<sothektx<<endl;
            }
    };

    class quanly
    {
        private:

            thektx the;
            static int stt;
            string taikhoan;
            string matkhau;
            string username = "quanlyktx1";
            string password = "1111";

        public:

            string gettime();
            bool checktime(); 
            
            void themsinhvien();
            void xoasinhvien(const string&);
            void danhsachsinhvien();
             
            void luulichsuvao(thektx the);
            void luulichsura(thektx the);
            void xuatlichsu(const string&);

            void vaoktx();
            void raktx();

            void login();
            void changepassword();
            void changeusername();

            void loadstt();
            void savestt();

    };

    int quanly::stt = 1;

    //lay thoi gian cua he thong va chuyen doi thanh dang chuoi:

    string quanly::gettime()
    {   
        time_t now = time(0); // khai bao bien now = gia tri thoi gian hien tai
        char* time = ctime(&now);
        return time;
    }

    //Ham kiem tra thoi gian

    bool quanly::checktime()
    {
        int gio;
        time_t now = time(0);
        tm *t = localtime(&now);
        gio = t->tm_hour;
        if (gio >= 5 && gio <= 23)
        {
            return true;
        } else return false;
    }

    // Ham them sinh vien
    
    void quanly::themsinhvien()
    {
        cout<<"----Them sinh vien----"<<endl;
        the.nhap();
        ofstream outfile;
        outfile.open("DSSV.txt",ios::app); 
        if (outfile.is_open())
        {   
            outfile<<stt<<".";
            outfile << "So the KTX: "<<the.getSothektx()<<endl;
            outfile << "Ho va ten: " << the.getten() << endl;
            outfile << "Ngay sinh: " << the.getngaysinh() << endl;
            outfile << "Phong: " << the.getphong() << endl;
            outfile << "So dien thoai: " << the.getsdt() << endl;
            
            outfile.close();
            cout<<"Them sinh vien thanh cong!"<<endl;
            stt++;
            savestt();
        }
        else cout<<"Khong the mo file!"<<endl;

    }

    //Ham xoa sinh vien

    void quanly::xoasinhvien(const string& sothektx)
    {
        ifstream infile("DSSV.txt");  
        ofstream outfile("DSSV_temp.txt");

        if (infile.is_open() && outfile.is_open())
        {
            string line;
            bool found = false;

            while (getline(infile, line)) {
                
                if (line.find(sothektx) != string::npos)
                {
                    found = true;
                    
                    for (int i = 0; i < 4; i++) {
                        getline(infile, line);
                    }
                } else {
                    
                    outfile << line << endl;
                }
            }

            infile.close();
            outfile.close();
            remove("DSSV.txt");
            rename("DSSV_temp.txt", "DSSV.txt");

            if (found)
            {
                cout<<"Da xoa sinh vien co ma "<<sothektx<<endl;
            } else {
                cout<<"Khong tim thay sinh vien co ma "<<sothektx<<endl;
            }
        } else {
            cout<<"Loi: Khong the mo hoac tao tao file"<<endl;
        }
    }

    //Ham in ra danh sach sinh vien

    void quanly::danhsachsinhvien()
    {

        string ds;
        ifstream file;
        file.open("DSSV.txt");
        
        cout<<"----Danh sach sinh vien----\t"<<endl;
        
        while (getline(file, ds))
        {
            cout<<ds<<endl;
        }
        file.close();

    } 

    //2 ham luu lich su ra vao vao file

    void quanly::luulichsuvao(thektx the)
    {
        ofstream outfile;
        outfile.open("Lichsu.txt", ios::app);
        outfile<<"So the KTX: "<<the.getSothektx()<<endl;
        outfile<<"Ho va ten: "<< the.getten() << endl;
        outfile<<"Ngay sinh: "<< the.getngaysinh() << endl;
        outfile<<"Phong: "<<the.getphong() << endl;
        outfile<<"So dien thoai: "<<the.getsdt() << endl;
        outfile<<"Thoi gian vao ky tuc xa: "<<gettime()<<endl;
        outfile.close();
    }

    void quanly::luulichsura(thektx the)
    {
        ofstream outfile;
        outfile.open("Lichsu.txt", ios::app);
        outfile<<"So the KTX: "<<the.getSothektx()<<endl;
        outfile<<"Ho va ten: "<<the.getten() << endl;
        outfile<<"Ngay sinh: "<<the.getngaysinh() << endl;
        outfile<<"Phong: "<<the.getphong() << endl;
        outfile<<"So dien thoai: "<<the.getsdt() << endl;
        outfile<<"Thoi gian ra ky tuc xa: "<<gettime()<<endl;
        outfile.close();
    }

    //ham xuat lich su ra vao ra man hinh
    void quanly::xuatlichsu(const string& sothektx)
    {
        ifstream infile;
        infile.open("Lichsu.txt");
        string line;
        bool found = false;

        cout<<"Lich su ra vao cua sinh vien co so the KTX "<<sothektx<<":\n";

        while (getline(infile, line))
        {
            if (line.find("So the KTX: " + sothektx) != string::npos) 
            {
                found = true;
                cout<<"---------------------\n";
                cout<<"Thong tin sinh vien:\n";
                cout<<"---------------------\n";
                cout<<line<<endl;

                while (getline(infile, line)) 
                {
                    if (line.empty()) 
                    {
                        break;
                    }
                    cout<<line<<endl;
                }
            }
        }
        infile.close();
        
        if (!found) 
        {
            cout<<"Khong tim thay sinh vien co so the KTX "<<sothektx<<endl;
        }
    }

    // 2 Ham vao va ra ky tuc xa

    void quanly::vaoktx()
    {
        if (checktime())
        {
            the.nhap();
            system("cls");
            the.xuat(); 
            cout<<"Vao ky tuc xa luc: ";
            cout<<gettime();
            luulichsuvao(the);
            cout<<endl;
        } 
    }

    void quanly::raktx()
    {   
        if (checktime())
        {
            the.nhap();
            system("cls");
            the.xuat(); 
            cout<<"Ra ky tuc xa luc: ";
            cout<<gettime();
            luulichsura(the);
            cout<<endl;
        }
    }

    //Ham login danh cho nguoi quan ly

    void quanly::login()
    {   
        string taikhoan, matkhau;
        ifstream login;
        login.open("login.txt", ios::app);
        login>>username;
        login>>password;
        login.close();
        
        cout<<"------------ Dang nhap --------------"<<endl;
        do
            {   
                cout<<"Nhap tai khoan nguoi quan ly: ";
                cin>>taikhoan;
                cout<<"Nhap mat khau: ";
                cin>>matkhau;
            
                if (taikhoan != username || matkhau != password)
                {
                    system("cls");
                    cout<<"Sai tai khoan hoac mat khau, vui long nhap lai\n";
                }
                else
                {
                    system("cls");
                    cout<<"Dang nhap thanh cong\n";
                }
            } while (taikhoan != username || matkhau != password);
    }

    //Ham doi mat khau dang nhap

    void quanly::changepassword()
    {
        string mk, mkc, a[2];
        login();
        cout<<"Nhap mat khau moi: ";
        cin>>mk;
        cout<<"Nhap mat khau cu: ";
        cin>>mkc;
        
        ifstream inlogin;
        inlogin.open("login.txt");
        for (int i=0; i<2; i++)
        {
            inlogin>>a[i]; 
        }
        inlogin.close();
        a[1] = mk;
        
        ofstream outlogin;
        outlogin.open("login.txt");
        for (int i=0; i<2; i++)
        {
            outlogin<<a[i]<<endl; 
        }
        outlogin.close(); 
        
        while (mkc != password)
        {
            cout<<"Sai mat khau cu, vui long nhap lai: ";
            cin>>mkc;
        }
        password = mk;
        system("cls");
        cout<<"Doi mat khau thanh cong\n";
    }

    //Ham doi username

    void quanly::changeusername()
    {
        string tk, mk, a[2];
        login();
        cout<<"Nhap ten nguoi quan ly moi: ";
        cin>>tk;
        cout<<"Nhap mat khau: ";
        cin>>mk;
        
        ifstream inlogin;
        inlogin.open("login.txt");
        for (int i=0; i<2; i++)
        {
            inlogin>>a[i]; 
        }
        inlogin.close();
        a[0] = tk;
        
        ofstream outlogin;
        outlogin.open("login.txt");
        for (int i=0; i<2; i++)
        {
            outlogin<<a[i]<<endl; 
        }
        outlogin.close(); 
        
        while (mk != password)
        {
            cout<<"Sai mat khau, vui long nhap lai: ";
            cin>>mk;
        }
        username = tk;
        system("cls");
        cout<<"Doi ten nguoi quan ly thanh cong\n";
    }

    // ham luu so thu tu vao file

    void quanly::loadstt()
    {
        ifstream infile("stt.txt");
        if (infile.is_open())
        {
            infile>>stt;
            infile.close();
        }
    }

    void quanly::savestt()
    {
        ofstream outfile("stt.txt");
        if (outfile.is_open())
        {
            outfile<<stt;
            outfile.close();
        }
    }

    void chuongtrinhtong()
    {
        quanly ql;
        int x = -1;
        while (x != 4)
        {
            // system("cls");
            cout<<" _______________________________\n";
            cout<<"|                               |\n";
            cout<<"|    ----Chon chuc nang----     |\n";
            cout<<"|    1. Vao ky tuc xa           |\n";
            cout<<"|    2. Ra ky tuc xa            |\n";
            cout<<"|    3. Quan ly                 |\n";
            cout<<"|    4. Thoat chuong trinh      |\n";
            cout<<"|_______________________________|\n";
            cout<<" Chon: ";
            cin>>x;

            switch (x)
            {
                case 1:
                    system("cls");
                    ql.vaoktx();
                    break;
                case 2:
                    system("cls");
                    ql.raktx();
                    break;
                case 3:
                    {
                        int n = -1;
                        system("cls");
                        ql.login();
                        while (n != 0)
                        {
                            // system("cls");
                            cout<<" _______________________________________\n";
                            cout<<"|                                       |\n";
                            cout<<"|    ----Chon chuc nang quan ly:----    |\n";
                            cout<<"|        1. Them sinh vien              |\n";
                            cout<<"|        2. Xoa sinh vien               |\n";
                            cout<<"|        3. Lich su ra vao              |\n";
                            cout<<"|        4. Doi ten dang nhap           |\n";
                            cout<<"|        5. Doi mat khau dang nhap      |\n";
                            cout<<"|        6. Danh sach sinh vien         |\n";
                            cout<<"|        0. Quay lai                    |\n";
                            cout<<"|_______________________________________|\n";
                            cout<<" Chon: ";
                            cin>>n;
                            
                            switch (n)
                            {
                                case 1:
                                    system("cls");
                                    ql.themsinhvien();
                                    break;
                                case 2:
                                    {
                                        system("cls");
                                        string sothektx;
                                        cout<<"Nhap ma sinh vien can xoa: ";
                                        cin.ignore();
                                        getline(cin, sothektx);
                                        system("cls");
                                        ql.xoasinhvien(sothektx);
                                        break;
                                    }
                                case 3:
                                    {
                                        system("cls");
                                        string sothektx;
                                        cout << "Nhap so the KTX: ";
                                        cin.ignore();
                                        getline(cin, sothektx);
                                        ql.xuatlichsu(sothektx);
                                    }
                                    break;
                                case 4:
                                    system("cls");
                                    ql.changeusername();
                                    break;
                                case 5:
                                    system("cls");
                                    ql.changepassword();
                                    break;
                                case 6:
                                    system("cls");
                                    ql.danhsachsinhvien();
                                    break;
                                case 0:
                                    system("cls");
                                    break;
                                default:
                                    cout<<"Chon lai: ";
                                    break;
                            }
                        }
                        break;
                    }
                case 4:
                    break;
                default:
                    cout<<"Chon lai: ";
                    break;
            }
        }
        system("cls");
        cout<<"----Nhan phim bat ki de thoat----";
    }
    int main()
    {
        chuongtrinhtong();
        return 0;
    }
