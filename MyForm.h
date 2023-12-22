#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <msclr/marshal_cppstd.h>
#include <string>
#include <cstdio>
//#include <experimental/filesystem>>
//#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

namespace baseform {

	using namespace std;
	using namespace msclr::interop;
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		int nezet = 0;
	private: System::Windows::Forms::Button^ button4;
	public:
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	public:
		String^ kivalasztott="";
		MyForm(void)
		{ 
			nezet = 0;
			InitializeComponent();
			nezetValtas(nezet);
			keszletekBeolvasasa();
			aktualizalas();
			inputText->Tag = "ures";
			inputTextKezeles(false);
			kepekFeldolgozasa("output.txt");


		}

		value struct LEGO_elem {
			public: String^ azon;
			public: String^ nev;
			public: String^ teljes;
			public: int db;
		};
		value struct Kep {
			public: String^ link;
			public: LEGO_elem^ nev;
		};

	private:
		List<String^>^ keszletek = gcnew List<String^>();
		List<LEGO_elem>^ megnyitott = gcnew List<LEGO_elem>();
		List<Kep>^ kepek = gcnew List<Kep>();
#pragma region fuggvenyek
		void nezetValtas(int nezetId) {
			switch (nezetId)
			{
			case 0: {
				this->Text = "LEGO alkatrész nyílvántartó";
				label4->Visible = false;
				label5->Visible = false;
				button4->Visible = true;
				button4->Text = "Indítás";
				button5->Visible = true;
				button5->Text = "Közremûködtek";
				button6->Visible = true;
				button6->Text = "Kilépés";
				button1->Visible = false;
				button2->Visible = false;
				button3->Visible = false;
				label1->Visible = false;
				lista->Visible = false;
				szamlalo->Visible = false;
				kep->Visible = true;
				inputText->Visible = false;
				button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F));
				button6->Location = System::Drawing::Point(21, 420);
				button6->Size = System::Drawing::Size(336, 70);
				kep->ImageLocation = "./LEGO_logo.png";
				label6->Visible = false;
				break;
			}
			case 1: { //szett hozzáadás/kiválasztás
				label4->Visible = false;
				label5->Visible = false;
				this->Text = "LEGO alkatrész nyílvántartó";
				button4->Visible = false;
				button5->Visible = false;
				//button6->Visible = false;
				lista->Visible = true;
				inputText->Visible = true;
				label1->Text = "Új készlet neve";
				label1->Visible = true;
				button1->Text = "Törlés";
				button1->Visible = true;
				button2->Text = "Készlet hozzáadása";
				button2->Visible = true;
				button3->Visible = false;
				szamlalo->Visible = false;
				kep->Visible = true;
				/*inputText->Text = "Új készlet neve";*/
				label6->Visible = false;
				button6->Size = System::Drawing::Size(49, 40);
				button6->Location = System::Drawing::Point(599, 9);
				button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.25F));
				button6->Text = "Fõmenû";
				break;
			}
			case 2: { //szett szerkesztése
				label4->Visible = false;
				label5->Visible = false;
				button4->Visible = false;
				button5->Visible = false;
				//button6->Visible = false;
				label1->Text = "Keresés";
				label1->Visible = true;
				button1->Visible = true;
				button1->Text = "Vissza";
				button2->Visible = true;
				button2->Text = "Mentés";
				button3->Visible = true;
				button3->Text = "Új kocka";
				szamlalo->Visible = true;
				kep->Visible = true;
				button6->Size = System::Drawing::Size(49, 40);
				button6->Location = System::Drawing::Point(599, 9);
				button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.25F));
				button6->Text = "Fõmenû";
				label6->Visible = true;
				break;
			}
			case 3: { //elem hozzáadás
				label4->Visible = false;
				label5->Visible = false;
				button4->Visible = false;
				button5->Visible = false;
				//button6->Visible = false;
				label1->Text = "Keresés";
				label1->Visible = true;
				button1->Text = "Vissza";
				button2->Visible = false;
				button3->Text = "Hozzáadás";
				button3->Visible = true;
				szamlalo->Visible = true;
				kep->Visible = true;
				button6->Size = System::Drawing::Size(49, 40);
				button6->Location = System::Drawing::Point(599, 9);
				button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.25F));
				button6->Text = "Fõmenû";
				label6->Visible = true;
				break;
			}
			case 4: {
				this->Text = "LEGO alkatrész nyílvántartó";
				inputText->Visible = false;
				lista->Visible = false;
				button1->Visible = false;
				button2->Visible = false;
				button3->Visible = false;
				button4->Visible = false;
				button5->Visible = false;
				button6->Visible = true;
				szamlalo->Visible = false;
				kep->Visible = false;
				button6->Size = System::Drawing::Size(49, 40);
				button6->Location = System::Drawing::Point(599, 9);
				button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.25F));
				button6->Text = "Fõmenû";
				label4->Visible = true;
				label5->Visible = true;
				label6->Visible = false;
			}
			default:
				break;
			}
			lista->Items->Clear();
		}
		void aktualizalas() {
			for each (String ^ item in keszletek)
			{
				lista->Items->Add(item);
			}
		}

		void keszletekBeolvasasa() {
			ifstream beolvas("keszletek.txt", ios::in);
			for (string keszletNeve; getline(beolvas, keszletNeve);)
			{
				keszletek->Add(marshal_as<String^>(keszletNeve));
			}
			beolvas.close();
		}

		void keszletekFajlba() {
			ofstream fajlba("keszletek.txt", ios::out | ios::trunc);
			for each (String ^ item in keszletek)
			{
				fajlba << marshal_as<string>(item->ToString()) << "\n";
			}
			fajlba.close();
		}

		void inputTextKezeles(bool focused) {
			if (focused) {
				inputText->Tag = "nemures";
				lista->SelectedIndex = -1;
				inputText->Text = "";
				return;
			}
			if (inputText->Text != "") {
				return;
			}
			else {
				inputText->Tag = "ures";
				return;
			}
			if (nezet == 1) {
				inputText->Text = "Új készlet neve";
				return;
			}
			else {
				inputText->Text = "Keresés";
				return;
			}
		}

		//fenyozoli ext.hpp
		vector<string> Split(string text, string separator) {
			vector<string> Res = {};
			while (text.find(separator) != string::npos) {
				Res.push_back(text.substr(0, text.find(separator)));
				text.erase(0, text.find(separator) + separator.length());
			}
			Res.push_back(text);
			return Res;
		}
		string Concat(vector<string> texts) {
			string Res = "";
			for (string n : texts) {
				Res += n;
			}
			return Res;
		}
		//

		void kivalasztottBeolvasasa(string fajlnev){
			megnyitott = gcnew List<LEGO_elem>();
			ifstream beolvas(fajlnev, ios::in);
			for (string adatsor; getline(beolvas, adatsor);) {
				//370526_Axle_4-Module_Black;1
				LEGO_elem elem;
				vector<string> tmp = Split(adatsor, "_");
				elem.azon = marshal_as<String^>(tmp[0].c_str());
				tmp.erase(tmp.begin());
				elem.nev = marshal_as<String^>(Split(Concat(tmp), ";")[0]);
				elem.teljes = elem.azon + "_" + elem.nev;
				elem.db = stoi(Split(Concat(tmp), ";").back());
				megnyitott->Add(elem);
			}
			beolvas.close();
			for each (LEGO_elem item in megnyitott) {
				lista->Items->Add(item.teljes);
			}
		}

		void kepekFeldolgozasa(string fajlnev) {
			ifstream beolvas(fajlnev, ios::in);
			vector<string> linkek = {};
			for (string adatsor; getline(beolvas, adatsor);) {
				linkek.push_back(adatsor);
			}
			/*String^ asd = "";
			for (const std::string& link : linkek) {
				asd += gcnew String(link.c_str()) + "\n";
			}
			MessageBox::Show(asd, "debug");*/
			for each (string link in linkek) {
				Kep kep;
				kep.link = marshal_as<String^>(link.c_str());
				LEGO_elem tmp;
				vector<string> tmpv = Split(Split(link, "\\").back(), "_");
				tmp.azon = marshal_as<String^>(tmpv[0].c_str());
				tmpv.erase(tmpv.begin());
				tmp.nev = marshal_as<String^>(Split(Split(Concat(tmpv), ";")[0], ".")[0]);
				tmp.teljes = tmp.azon + "_" + tmp.nev;
				kep.nev = tmp;
				kepek->Add(kep);
			}
			
		}

		//int kivalasztas() {
		//	for (int i = 0; i < kepek->Count; i++)
		//	{
		//		if (kepek[i].nev->teljes == lista->SelectedItem->ToString()) {
		//			/*MessageBox::Show(kepek[i].nev->teljes+"==?"+lista->SelectedItem->ToString(),"debug");*/
		//			return i;
		//			//break;
		//		}
		//	}
		//	return -1;
		//}

		void elemekMegjelenitese() {
			for each (Kep item in kepek) {
				lista->Items->Add(item.nev->teljes);
			}
		}

		int torlesIndex() {
			int index = -1;
			for (int i = 0; i < megnyitott->Count; i++) {
				bool talalat = false;
				for each (Object ^ item in lista->Items) {
					if (item->ToString() == megnyitott[i].teljes) {
						talalat = true;
						break;
					}
				}
				if (talalat) {
					continue;
				}
				index = i;
				break;
			}
			return index;
		}

		/*void kepekFajlba(const string& mappa, const string& fajlnev) {
			ofstream fajlba(fajlnev, ios::out | ios::trunc);
			if (!fajlba.is_open()) {
				perror("Hiba");
				return;
			}
			for (const auto& item : experimental::filesystem::directory_iterator(mappa)) {
				if (experimental::filesystem::is_regular_file(item)) {
					fajlnev << item.path().filename().string() << "\n";
				}
			}
		}*/

#pragma endregion
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ inputText;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ kep;

	private: System::Windows::Forms::ListBox^ lista;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::NumericUpDown^ szamlalo;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->inputText = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->kep = (gcnew System::Windows::Forms::PictureBox());
			this->lista = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->szamlalo = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kep))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->szamlalo))->BeginInit();
			this->SuspendLayout();
			// 
			// inputText
			// 
			this->inputText->Location = System::Drawing::Point(21, 29);
			this->inputText->Name = L"inputText";
			this->inputText->Size = System::Drawing::Size(336, 20);
			this->inputText->TabIndex = 0;
			this->inputText->TextChanged += gcnew System::EventHandler(this, &MyForm::inputText_TextChanged);
			this->inputText->Enter += gcnew System::EventHandler(this, &MyForm::inputText_Enter);
			this->inputText->Leave += gcnew System::EventHandler(this, &MyForm::inputText_Leave);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 1;
			// 
			// kep
			// 
			this->kep->Location = System::Drawing::Point(398, 71);
			this->kep->Name = L"kep";
			this->kep->Padding = System::Windows::Forms::Padding(2);
			this->kep->Size = System::Drawing::Size(250, 250);
			this->kep->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->kep->TabIndex = 2;
			this->kep->TabStop = false;
			// 
			// lista
			// 
			this->lista->FormattingEnabled = true;
			this->lista->Location = System::Drawing::Point(21, 71);
			this->lista->Name = L"lista";
			this->lista->Size = System::Drawing::Size(336, 472);
			this->lista->TabIndex = 3;
			this->lista->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::lista_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Wheat;
			this->button1->Location = System::Drawing::Point(400, 507);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(167, 35);
			this->button1->TabIndex = 4;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Wheat;
			this->button2->Location = System::Drawing::Point(400, 450);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(167, 35);
			this->button2->TabIndex = 5;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Gold;
			this->button3->Location = System::Drawing::Point(573, 413);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 129);
			this->button3->TabIndex = 6;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// szamlalo
			// 
			this->szamlalo->Location = System::Drawing::Point(398, 413);
			this->szamlalo->Name = L"szamlalo";
			this->szamlalo->Size = System::Drawing::Size(167, 20);
			this->szamlalo->TabIndex = 7;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->label2->Location = System::Drawing::Point(7, 555);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(206, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Készítette: Lugosi Ádám, 2023. 12. 22-27.";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 555);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 9;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::MintCream;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F));
			this->button4->Location = System::Drawing::Point(21, 263);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(336, 70);
			this->button4->TabIndex = 10;
			this->button4->Text = L"button4";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Ivory;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F));
			this->button5->Location = System::Drawing::Point(21, 344);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(336, 70);
			this->button5->TabIndex = 11;
			this->button5->Text = L"button5";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Salmon;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F));
			this->button6->Location = System::Drawing::Point(21, 420);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(336, 70);
			this->button6->TabIndex = 12;
			this->button6->Text = L"button6";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->label4->Location = System::Drawing::Point(176, 71);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(331, 68);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Fenyõ Zoltánnak, és Kiss Dávid Balázsnak\na debugolásban nyújtott segítségért, és "
				L"a sok-sok\negyéb technikai-logikai kérdésben való segítségért \n<3";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.25F));
			this->label5->Location = System::Drawing::Point(151, 29);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(406, 26);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Köszönetnyílvánítás a közremûködõknek";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(398, 394);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(60, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Darabszám";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGoldenrodYellow;
			this->ClientSize = System::Drawing::Size(672, 574);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->szamlalo);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->lista);
			this->Controls->Add(this->kep);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->inputText);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->kep))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->szamlalo))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region eventhandlerek
	private: System::Void lista_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		//MessageBox::Show("nezet: " + nezet + "\nSelectedIndex: " + lista->SelectedIndex);
		if (nezet == 1 && lista->SelectedIndex == -1) {
			button2->Text = "Készlet hozzáadása";
		}
		else if (nezet == 1 && lista->SelectedIndex != -1) {
			button2->Text = "Készlet betöltése";
		}
		else if (nezet == 2 && lista->SelectedIndex == -1) {
			button1->Text = "Vissza";
			button2->Text = "Mentés";
			//button2->Enabled = false;
		}
		else if (nezet == 2 && lista->SelectedIndex != -1) {
			button2->Enabled = true;
			button2->Text = "Módosítás";
			button1->Text = "Törlés";
		}
		
		if (nezet == 2 && lista->SelectedIndex != -1) {
			int darabszamSzamlalo = 0;
			for (int i = 0; i < megnyitott->Count; i++) {
				if (megnyitott[i].teljes == lista->SelectedItem->ToString()) {
					darabszamSzamlalo = megnyitott[i].db;
				}
			}
			szamlalo->Text = darabszamSzamlalo.ToString();
		}
		if ((nezet == 2 || nezet == 3) && lista->SelectedIndex != -1){
			int index = 0;
			for (int i = 0; i < kepek->Count; i++)
			{
				if (kepek[i].nev->teljes == lista->SelectedItem->ToString()) {
					/*MessageBox::Show(kepek[i].nev->teljes+"==?"+lista->SelectedItem->ToString(),"debug");*/
					index=i;
				}
			}
			kep->ImageLocation = "";
			kep->ImageLocation = kepek[index].link;
			/*MessageBox::Show(kepek[index].link, "debug");*/
		}

	}

	private: System::Void inputText_Enter(System::Object^ sender, System::EventArgs^ e) {
		inputTextKezeles(true);
	}
	private: System::Void inputText_Leave(System::Object^ sender, System::EventArgs^ e) {
		inputTextKezeles(false) ;
	}
		   
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		/*lista->Items->Add("proba");
		lista->Items->Add("proba2");*/
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		switch (nezet)
		{
		case 1: {
			if (inputText->Tag=="nemures" && lista->SelectedIndex == -1) {
				String^ keszletNeve= inputText->Text;
				string fajlnev= msclr::interop::marshal_as<string>(keszletNeve)+".txt";
				ofstream tmp(fajlnev, ios::out | ios::trunc);tmp.close();
				keszletek->Add(keszletNeve);
				lista->Items->Clear();
				aktualizalas();
				int aktualis= lista->Items->Count - 1;
				lista->SelectedIndex = aktualis;
				keszletekFajlba();
			}
			else if (inputText->Tag == "ures" && lista->SelectedIndex == -1) {
				MessageBox::Show("Nevezd el a készletet!", "Üzike", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else if (lista->SelectedIndex != -1) {
				inputText->Text = "";
				kivalasztott = lista->SelectedItem->ToString();
				string fajlnev = msclr::interop::marshal_as<string>(kivalasztott->ToString()) + ".txt";
				nezet = 2;
				nezetValtas(nezet);
				this->Text = kivalasztott;
				kivalasztottBeolvasasa(fajlnev);
			}

			break;
		}
		case 2: {
			if (lista->SelectedIndex == -1) {
				string fajlnev = msclr::interop::marshal_as<string>(kivalasztott->ToString()) + ".txt";
				ofstream fajlba(fajlnev, ios::out | ios::trunc);
				string asd = "";
			
				for each (LEGO_elem item in megnyitott) {
					asd = marshal_as<string>(item.teljes)+  ";" + marshal_as<string>(item.db.ToString())+ "\n";
					fajlba << asd;
				}
				fajlba.flush();
				fajlba.close();
			}
			else {
				int index = 0;
				for (int i = 0; i < megnyitott->Count; i++) {
					if (lista->Items[lista->SelectedIndex]->ToString() == megnyitott[i].teljes) {
						index = i;
						break;
					}
				}
				LEGO_elem uj = megnyitott[index];
				uj.db = stoi(marshal_as<string>(szamlalo->Text));
				megnyitott->RemoveAt(index);
				megnyitott->Insert(index, uj);
			}
			lista->SelectedIndex = -1;
			break;
		}
		case 3: {


			break;
		}
		default:
			break;
		}
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		switch (nezet)
		{
		case 1:
		{
			if (lista->SelectedIndex != -1)
			{
				String^ torlendo = nullptr;
				if (lista->SelectedItem != nullptr) {
					torlendo = lista->SelectedItem->ToString()+".txt";
					string fajlnev = msclr::interop::marshal_as<string>(torlendo);
					int tmp = lista->SelectedIndex;
					System::Windows::Forms::DialogResult confirm = MessageBox::Show("Biztosan törölni kívánja a fájlt?", "areusureaboutthat", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
					if (confirm == System::Windows::Forms::DialogResult::Yes) {
						if (remove(fajlnev.c_str()) == 0) {
							MessageBox::Show("Sikeres törlés!", "Üzike", MessageBoxButtons::OK, MessageBoxIcon::Information);
							keszletek->RemoveAt(tmp);
							lista->Items->RemoveAt(lista->SelectedIndex);
						}
						else {
							perror("Sikertelen");
							MessageBox::Show("Sikertelen törlés!", "Hiba", MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
					}
				}
				keszletekFajlba();
			}
			else
			{
				MessageBox::Show("Nincs kijelölve készlet!", "Hiba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			break;
		}
		case 2: {
			if (lista->SelectedIndex == -1) {
				nezet = 1;
				nezetValtas(nezet);
				aktualizalas();
			}
			else {
				int index = lista->SelectedIndex;
				lista->Items->RemoveAt(index);

				int index2 = 0;
				for (int i = 0; i < megnyitott->Count; i++) {
					bool talalat = false;
					for each (Object ^ item in lista->Items) {
						if (item->ToString() == megnyitott[i].teljes) {
							talalat = true;
							break;
						}
					}
					if (talalat) {
						continue;
					}
					index2 = i;
					break;
				}

				megnyitott->RemoveAt(index2);

			}

			break;
		}
		case 3: {
			nezet = 2;
			nezetValtas(nezet);
			for each (LEGO_elem item in megnyitott) {
				lista->Items->Add(item.teljes);
			}
			break;
		}
		default:
			break;
		}
	}

	private: System::Void inputText_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		if (inputText->Tag == "ures" || nezet == 1)
		{
			return;
		}
		string kereses = marshal_as<string>(inputText->Text->ToLower());
		String^ szamok = "0123456789";
		//MessageBox::Show(marshal_as<String^>(kereses), "debug");
		switch (nezet) {
			case 2: {
				lista->Items->Clear();
				if (inputText->Text == "") {
					for each (LEGO_elem item in megnyitott) {
						lista->Items->Add(item.teljes);
					}
					return;
				}
				if (szamok->Contains((Convert::ToInt32(kereses[0]) - 48).ToString())) {
					for each (LEGO_elem ^ item in megnyitott) {
						if (item->azon->StartsWith(marshal_as<String^>(kereses))) {
							lista->Items->Add(item->teljes);
						}
					}
				}
				else {
					for each (LEGO_elem ^ item in megnyitott) {
						//MessageBox::Show(marshal_as<String^>(kereses)+"\n"+ item->nev->ToLower()+"\n"+item->nev->ToLower()->StartsWith(marshal_as<String^>(kereses)), "debug");
						if (item->nev->ToLower()->StartsWith(marshal_as<String^>(kereses))) {
							lista->Items->Add(item->teljes);
						}
					}
				}
				break;
			}
			case 3: {
				lista->Items->Clear();
				if (inputText->Text == "") {
					//nem kepek felreertes miatt, hanem alkatresz de igy maradt
					for each (Kep item in kepek) {
						lista->Items->Add(item.nev->teljes);
					}
				}
				if (szamok->Contains((Convert::ToInt32(kereses[0]) - 48).ToString())) {
					for each (Kep ^ item in kepek) {
						if (item->nev->azon->StartsWith(marshal_as<String^>(kereses))) {
							lista->Items->Add(item->nev->teljes);
						}
					}
				}
				else {
					for each (Kep^ item in kepek){
						if (item->nev->nev->ToLower()->StartsWith(marshal_as<String^>(kereses))) {
							lista->Items->Add(item->nev->teljes);
						}
					}
				}
			}
		}
	}
#pragma endregion
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	switch (nezet) {
	case 2: {
		nezet = 3;
		nezetValtas(nezet);
		for each (Kep item in kepek) {
			lista->Items->Add(item.nev->teljes);
		}
		break;
	}
	case 3: {
		if (lista->SelectedIndex == -1) {
			MessageBox::Show("Nincs kijelölve elem!", "Hiba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else {
			int index = 0;
			for (int i = 0; i < kepek->Count; i++) {
				if (kepek[i].nev->teljes == lista->SelectedItem->ToString()) {
					index = i;
					break;
				}
			}
			LEGO_elem elem;
			String^ hozzafuzes = kepek[index].nev->teljes;
			vector<string> tmpv = Split(marshal_as<string>(hozzafuzes), "_");
			elem.azon = marshal_as<String^>(tmpv[0].c_str());
			tmpv.erase(tmpv.begin());
			elem.nev = marshal_as<String^>(Split(Concat(tmpv), ";")[0]);
			elem.teljes = elem.azon + "_" + elem.nev;
			elem.db = stoi(marshal_as<string>(szamlalo->Text));
			megnyitott->Add(elem);
			nezet = 2;
			nezetValtas(nezet);
			for each (LEGO_elem item in megnyitott) {
				lista->Items->Add(item.teljes);
			}
			return;
		}
		break;
	}
	default:
		break;
	}
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	nezet = 1;
	nezetValtas(nezet);
	//keszletekBeolvasasa();
	aktualizalas();

}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	switch (nezet) {
	case 0: {
		Application::Exit();
		break;
	}
	case 1: {
		nezet = 0;
		nezetValtas(nezet);
		break;
	}
	case 2: {
		nezet = 0;
		nezetValtas(nezet);
		break;
	}
	case 3: {
		nezet = 0;
		nezetValtas(nezet);
		break;
	}
	case 4: {
		nezet = 0;
		nezetValtas(nezet);
		break;
	}
	}
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	nezet = 4;
	nezetValtas(nezet);
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("easter egg >w<", "ggwp", MessageBoxButtons::OK, MessageBoxIcon::Stop);
}
};
}
