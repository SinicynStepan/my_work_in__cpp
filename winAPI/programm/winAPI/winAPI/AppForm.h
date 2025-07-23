#pragma once

namespace winAPI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class AppForm : public System::Windows::Forms::Form
	{
	public:
		AppForm(void)
		{
			InitializeComponent();
			this->textBox_input_squeeze->Validating += gcnew CancelEventHandler(this, &AppForm::textBox_input_squeeze_validating);
			this->textBox_input_stretch->Validating += gcnew CancelEventHandler(this, &AppForm::textBox_input_stretch_validating);
			this->textBox_input_stretch->Validating += gcnew CancelEventHandler(this, &AppForm::textBox_input_stretch_validating);
		}

	protected:
		~AppForm()
		{
			if (components)
				delete components;
		}
	private: 
		System::Windows::Forms::Label ^squeeze_label;
		System::Windows::Forms::Label ^stretch_label;
		System::Windows::Forms::Label ^rotate_label;
		System::Windows::Forms::OpenFileDialog ^openInputFileDialog;
		System::Windows::Forms::Button ^buttonPerform; 
		System::Windows::Forms::SaveFileDialog ^saveOutputFileDialog;
		System::Windows::Forms::TextBox ^textBox_input_squeeze;
		System::Windows::Forms::TextBox ^textBox_input_stretch;
		System::Windows::Forms::TextBox ^textBox_input_rotate;
		System::Windows::Forms::Button ^buttonOpenInput;
		System::Windows::Forms::Label ^label1;
		System::Windows::Forms::Label ^label2;
		System::Windows::Forms::Label ^label3;
		System::ComponentModel::Container ^components;

	private: System::Void buttonOpenInput_Click(System::Object ^sender, System::EventArgs ^e);
	private: System::Void buttonPerform_Click(System::Object ^sender, System::EventArgs ^e);
	private: System::Void textBox_input_squeeze_validating(Object ^sender, CancelEventArgs ^e);
	private: System::Void textBox_input_stretch_validating(Object ^sender, CancelEventArgs ^e);
	private: System::Void textBox_input_rotate_validating(Object ^sender, CancelEventArgs ^e);
		

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->squeeze_label = (gcnew System::Windows::Forms::Label());
			this->stretch_label = (gcnew System::Windows::Forms::Label());
			this->rotate_label = (gcnew System::Windows::Forms::Label());
			this->openInputFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->buttonPerform = (gcnew System::Windows::Forms::Button());
			this->buttonOpenInput = (gcnew System::Windows::Forms::Button());
			this->saveOutputFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->textBox_input_squeeze = (gcnew System::Windows::Forms::TextBox());
			this->textBox_input_stretch = (gcnew System::Windows::Forms::TextBox());
			this->textBox_input_rotate = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// squeeze_label
			// 
			this->squeeze_label->AutoSize = true;
			this->squeeze_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->squeeze_label->Location = System::Drawing::Point(128, 132);
			this->squeeze_label->Name = L"squeeze_label";
			this->squeeze_label->Size = System::Drawing::Size(128, 22);
			this->squeeze_label->TabIndex = 0;
			this->squeeze_label->Text = L"Сжать фигуру";
			// 
			// stretch_label
			// 
			this->stretch_label->AutoSize = true;
			this->stretch_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->stretch_label->Location = System::Drawing::Point(128, 167);
			this->stretch_label->Name = L"stretch_label";
			this->stretch_label->Size = System::Drawing::Size(159, 22);
			this->stretch_label->TabIndex = 1;
			this->stretch_label->Text = L"Растянуть фигуру";
			// 
			// rotate_label
			// 
			this->rotate_label->AutoSize = true;
			this->rotate_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->rotate_label->Location = System::Drawing::Point(128, 205);
			this->rotate_label->Name = L"rotate_label";
			this->rotate_label->Size = System::Drawing::Size(148, 22);
			this->rotate_label->TabIndex = 2;
			this->rotate_label->Text = L"Вращать фигуру";
			// 
			// openInputFileDialog
			// 
			this->openInputFileDialog->DefaultExt = L"txt";
			this->openInputFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt";
			this->openInputFileDialog->Title = L"Выберите файл";
			// 
			// buttonPerform
			// 
			this->buttonPerform->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->buttonPerform->Location = System::Drawing::Point(132, 292);
			this->buttonPerform->Name = L"buttonPerform";
			this->buttonPerform->Size = System::Drawing::Size(390, 36);
			this->buttonPerform->TabIndex = 7;
			this->buttonPerform->Text = L"Выполнить";
			this->buttonPerform->UseVisualStyleBackColor = true;
			this->buttonPerform->Click += gcnew System::EventHandler(this, &AppForm::buttonPerform_Click);
			// 
			// buttonOpenInput
			// 
			this->buttonOpenInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->buttonOpenInput->Location = System::Drawing::Point(132, 82);
			this->buttonOpenInput->Name = L"buttonOpenInput";
			this->buttonOpenInput->Size = System::Drawing::Size(390, 34);
			this->buttonOpenInput->TabIndex = 12;
			this->buttonOpenInput->Text = L"Выбрать файл с входными данными";
			this->buttonOpenInput->UseVisualStyleBackColor = true;
			this->buttonOpenInput->Click += gcnew System::EventHandler(this, &AppForm::buttonOpenInput_Click);
			// 
			// saveOutputFileDialog
			// 
			this->saveOutputFileDialog->DefaultExt = L"emf";
			this->saveOutputFileDialog->Filter = L"Enhanced Metafile (*.emf)|*.emf";
			this->saveOutputFileDialog->Title = L"Сохранить файл";
			// 
			// textBox_input_squeeze
			// 
			this->textBox_input_squeeze->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->textBox_input_squeeze->Location = System::Drawing::Point(419, 129);
			this->textBox_input_squeeze->Name = L"textBox_input_squeeze";
			this->textBox_input_squeeze->Size = System::Drawing::Size(71, 27);
			this->textBox_input_squeeze->TabIndex = 13;
			this->textBox_input_squeeze->Text = L"1";
			this->textBox_input_squeeze->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox_input_stretch
			// 
			this->textBox_input_stretch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->textBox_input_stretch->Location = System::Drawing::Point(419, 164);
			this->textBox_input_stretch->Name = L"textBox_input_stretch";
			this->textBox_input_stretch->Size = System::Drawing::Size(71, 27);
			this->textBox_input_stretch->TabIndex = 14;
			this->textBox_input_stretch->Text = L"1";
			this->textBox_input_stretch->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox_input_rotate
			// 
			this->textBox_input_rotate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->textBox_input_rotate->Location = System::Drawing::Point(419, 200);
			this->textBox_input_rotate->Name = L"textBox_input_rotate";
			this->textBox_input_rotate->Size = System::Drawing::Size(71, 27);
			this->textBox_input_rotate->TabIndex = 15;
			this->textBox_input_rotate->Text = L"0";
			this->textBox_input_rotate->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->label1->Location = System::Drawing::Point(496, 132);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 22);
			this->label1->TabIndex = 16;
			this->label1->Text = L"%";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13));
			this->label2->Location = System::Drawing::Point(496, 165);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 22);
			this->label2->TabIndex = 17;
			this->label2->Text = L"%";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->label3->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->label3->Location = System::Drawing::Point(496, 194);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(16, 17);
			this->label3->TabIndex = 18;
			this->label3->Text = L"o";
			// 
			// AppForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(671, 412);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox_input_rotate);
			this->Controls->Add(this->textBox_input_stretch);
			this->Controls->Add(this->textBox_input_squeeze);
			this->Controls->Add(this->buttonOpenInput);
			this->Controls->Add(this->buttonPerform);
			this->Controls->Add(this->rotate_label);
			this->Controls->Add(this->stretch_label);
			this->Controls->Add(this->squeeze_label);
			this->Name = L"AppForm";
			this->Text = L"Menu";
			this->Load += gcnew System::EventHandler(this, &AppForm::AppForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void AppForm_Load(System::Object ^sender, System::EventArgs ^e) {
		}
	};
}
